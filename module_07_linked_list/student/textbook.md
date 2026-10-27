# Chapter 7. Linked Lists

Chapter 1 keeps values in consecutive active array slots. Here we change their logical order without shifting the values. The current `lab.c` uses ten array slots and integer links. We apply the same links to a Stack and a queue.

[한글 교재](textbook_korean.md) · [Class workbook](class_material.md) · [Concept slides](ppt_material.md) · [Lab](lab.md)

## Thinking Logically

### Can the order change without shifting values?

Suppose records contain 17, 23, and 31. We want to insert and remove a record between two others. In an array list, inserting into the active middle shifts the following values. Instead, let each record remember which record follows it. Changing that recorded destination changes the order.

A record containing a value and a following link is a **node**. A sequence formed by following one link per node is a **singly linked list**. A link can hold an address, but this lab uses an array index. The physical array still exists. The logical order follows links rather than neighboring positions.

Each node has two integer fields. `data` holds the value. `next` holds the next node's index. Valid indices are 0 through 9. The value `-1` means there is no next node. Never use `-1` as an array index. Keep the first index separately in a caller variable such as `first`. An empty list has `first=-1`.

For now, suppose slots 0, 1, and 2 have been set aside for us. Slot 1 is separate while slots 0 and 2 form a list.

```text
Physical slots:  lnodes[0]       lnodes[1]       lnodes[2]
Fields:         data=17,next=2  data=23,next=-1 data=31,next=-1
first = 0
Logical order:  0 → 2 → -1
Values:         17 → 31
Separate node:  1(23) → -1
```

Following links must eventually reach `-1`. A link back to an earlier node would create a cycle and prevent that walk from ending. The simple lists in this chapter have no cycles. In a nonempty list, following links from any node in the list reaches its last node.

Indices and values have different jobs. The value 23 is stored at index 1. Reusing slot 1 can change its value while keeping the same index.

### How do we insert after a known node?

We want to put 23 between 17 and 31. The old successor of slot 0 is slot 2. First give the new node that successor. Then make slot 0 point to the new node. `link_lnode(0, 1)` performs these two writes:

```text
lnodes[1].next = lnodes[0].next   // 2
lnodes[0].next = 1
Result: first=0; 0(17) → 1(23) → 2(31) → -1
```

Reversing the writes first replaces the only link from slot 0 to slot 2. The second write then copies 1 into `lnodes[1].next`, creating a self-cycle. Preserve the old successor before replacing the predecessor's link.

`link_lnode(prev,node)` neither obtains a slot nor searches for a value. The caller supplies two valid, distinct indices that are already assigned for use. The inserted node must be outside every active chain and the chain of unused nodes. Inserting a node already in a chain can create a cycle or mix two lists.

### How do we remove the middle node?

The predecessor must point past the removed node. `delete_next_lnode(0)` saves index 1, changes `lnodes[0].next` to 2, and returns 1.

```text
Before: first=0; 0(17) → 1(23) → 2(31) → -1
After:  first=0; 0(17) → 2(31) → -1
Returned: 1; lnodes[1].next is still 2
```

The removed node is **detached**: the active chain no longer reaches it. Its stored `next` is unchanged. The caller retains the returned index until the node is used elsewhere or returned for reuse. Removing the link does not make the slot available automatically.

With a valid predecessor that has no successor, `delete_next_lnode(prev)` returns `-1` and changes nothing. The function does not search for a matching value. It also cannot update the caller's `first`. Removing the first node requires the caller to save the old first index and advance `first` to that node's successor.

### Can several lists use one array?

We can change the middle of a list without moving the following values. We need its predecessor first. To find the third node, start at `first` and follow two links. The expression `lnodes[2]` means physical slot 2, not the third node in logical order. Each node also spends one integer on its following link.

Suppose two lists need different amounts of space over time. Reserving five of ten slots for each prevents the first list from using a sixth slot even when the second uses only one. Instead, let either list take any available slot. Each list keeps its own first index. Their active nodes stay separate. The array still holds only ten nodes in total. Sharing unused space does not increase that capacity.

### Where does an available node come from?

Before adding a record, we need an unused slot. Scanning the whole array would repeat the same search on every request. Link the available slots together instead. This chain is a **free list**. The fixed array of reusable nodes is a **node pool**.

`free_head` holds the first available index. `init_lnodes_pool()` sets every value to zero and constructs this chain:

```text
free_head = 0
free chain: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

`new_lnode(value, -1)` removes the first free slot. It advances `free_head`, writes the requested value, and stores its second argument as `next`. Passing `-1` creates a separate node. The return value is an index, not the stored data. If the free chain is empty, it returns `-1` and changes nothing. Check that result before indexing.

| Request after initialization | Returned index | `free_head` | Chosen node |
| --- | ---: | ---: | --- |
| `new_lnode(17, -1)` | 0 | 1 | `data=17, next=-1` |
| `new_lnode(23, -1)` | 1 | 2 | `data=23, next=-1` |
| `new_lnode(31, -1)` | 2 | 3 | `data=31, next=-1` |

These nodes are **allocated**: removed from the free chain and assigned to the caller. None of these functions calls C's `malloc` or `free`. To reproduce the insertion above, call `link_lnode(0,2)` and then `link_lnode(0,1)`.

The same allocations can instead form two lists: `first_a=0` with `0(17)→2(31)→-1`, and `first_b=1` with `1(23)→-1`. Both use the free chain beginning at 3. An allocation for either list takes the first available slot. Initialize the pool only when no live user owns any slot. Initializing while either list is live overwrites both lists' records.

### When can a removed slot be reused?

Return to the one-list example `0(17)→1(23)→2(31)→-1`, with `free_head=3`. After `delete_next_lnode(0)`, index 1 is detached and `free_head` is still 3. Read any needed value before calling `free_lnode(1)`. That call prepends the slot to the free chain:

```text
free_head = 1
free chain: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode` overwrites `next` and leaves `data` unchanged. The next `new_lnode(8,-1)` returns index 1 with `data=8, next=-1`. Another list can receive that slot.

The caller controls **ownership**: responsibility for keeping a slot in one state at a time. A slot belongs to the free chain, to one active chain, or to the caller as a detached allocation. Those states must not overlap. A detached slot that is never returned stays unavailable. Losing its saved index can exhaust the pool even when fewer than ten nodes remain in active lists.

Returning an active node overwrites a link still used by its list. Returning slot 1 twice consecutively makes `lnodes[1].next=1`, a cycle in the free chain. `free_lnode` rejects out-of-range indices, but cannot detect these in-range ownership mistakes. Diagnose them on paper rather than executing corrupted chains.

After returning slot 1, the old caller must stop using that slot as its record. Before reuse, `next` belongs to the free chain and `data` may still hold 23. After reuse, a read can see 8 from another list. Writing `next` can corrupt that list or the free chain. Writing `data` can change another caller's value. Save the needed value and successor before returning a node.

### How can the last value added come out first?

Chapter 4 removes the last value added. Keep that same LIFO rule using links. Add each new record at the first node and remove from the same end. A Stack built from linked nodes is a **linked Stack**. The caller's `first` marks its top.

Start an independent pool with `first=-1`. To add a value, allocate a separate node and check success. Set its `next` to the old `first`, then set `first` to the new index. If allocation returns `-1`, leave `first` and the existing links unchanged.

To remove a value, check `first!=-1`. Save the old first index, its value, and its successor. Advance `first` to the successor, then return the old slot with `free_lnode`. There is no predecessor to pass to `delete_next_lnode` at this end. The caller performs the first-index update directly.

| Action in a fresh pool | `first` | Stack from its top | `free_head` |
| --- | ---: | --- | ---: |
| add 17 | 0 | 0(17) → -1 | 1 |
| add 23 | 1 | 1(23) → 0(17) → -1 | 2 |
| add 31 | 2 | 2(31) → 1(23) → 0(17) → -1 | 3 |
| remove 31 and recycle slot 2 | 1 | 1(23) → 0(17) → -1 | 2 |
| remove 23 and recycle slot 1 | 0 | 0(17) → -1 | 1 |
| remove 17 and recycle slot 0 | -1 | empty | 0 |

The output is 31, 23, 17. The last removal makes `first=-1`. No node can be removed from an empty list. This Stack is caller code using the existing node functions. `lab.c` supplies no separate Stack API.

### How can one linked list preserve arrival order?

Now requests 17, 23, and 31 must be processed in the order they arrive. Insert each record after the last and remove the first. Remember both ends so neither action needs a search. This first-in, first-out rule is **FIFO**. A **queue** uses that rule. The linked queue applies the same nodes from this chapter.

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. The appended node has `next=-1`. With a nonempty queue, the old tail points to it and `tail` moves to it. With an empty queue, both endpoints become that node. Pool exhaustion returns `false` without changing the pool or queue.

`dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index. Removing the only node sets both `head` and `tail` to `-1`.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot whose `next` must be `-1`; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it. `assert(enqueue(value))` would remove the insertion when assertions are disabled.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

Reusing slot 0 behind waiting slots preserves arrival order even though array-index order changes. Module 8 stores tree-node or graph-vertex IDs as queue values and uses the same `enqueue` and `dequeue` functions. Its BFS caller does not allocate or recycle queue nodes directly.

## Calculating Efficiency

### How much work changes one link?

Allocation removes the first free index. Recycling prepends one index. Insertion after a known predecessor changes two links. Deletion after a known predecessor reads one successor and changes at most one link. None scans the chain, so each operation takes O(1) work. Searching for a predecessor by value may inspect all `n` active nodes, so that separate search takes O(n).

The first node needs no link traversal to reach. The third needs two `next` steps. The last of `n` nodes needs `n-1` steps from the first. Finding a position by its logical order can therefore take O(n), while accessing a known physical array index takes O(1).

### How much memory do the links use?

Each node stores one integer value and one extra integer link. The lab reserves ten two-integer records plus `free_head`, `head`, and `tail`, regardless of how many records are active. Several lists can share unused slots, but each additional list needs its own first index. A slot cannot count toward two active lists at once.

Initializing capacity `C` writes each slot once: O(C). Here `C=10`. The pool uses O(C) storage and O(1) additional local storage per operation. Allocation failure means the free chain is exhausted. No operating-system heap request occurs.

### How much work keeps a Stack or queue in order?

A linked Stack changes `first` and a fixed number of node fields. Adding or removing its first record takes O(1). A queue adds constant pool-allocation work to the saved-tail append. Its value removal copies one value and adds constant recycling work to the saved-head removal. Both queue operations take O(1).

Ten slots limit simultaneous allocated records across every user of the pool. The pool does not limit the total processed over repeated add/remove cycles. A Stack using three slots leaves at most seven for a queue sharing that pool. Module 8 uses the difference between simultaneous occupancy and total processed values for BFS.

## Glossary

The following names describe the mechanisms traced above.

| Term | Meaning in this lab |
| --- | --- |
| node / 노드 | one `data` field and one `next` field |
| singly linked list / 단일 연결 리스트 | a sequence whose nodes each record one following index |
| first / 시작 노드 | separately saved index of the list's first node, or `-1` when empty |
| cycle / 순환 | a link path that returns to a previously visited node |
| traversal / 순회 | repeatedly following `next` until `-1` |
| node pool / 노드 풀 | the fixed `lnodes[10]` storage shared by its users |
| free list / 가용 리스트 | available indices linked from `free_head` |
| allocation / 할당 | removing a slot from the free chain for use |
| detach / 분리 | removing a node from an active chain without recycling it |
| recycle / 반환 | adding an allocated, detached slot to the free chain |
| ownership / 소유 책임 | responsibility for keeping a slot in exactly one valid state |
| stale index / 이전 소유자의 인덱스 | an index kept after returning a node, which no longer identifies that caller's record |
| linked Stack / 연결 스택 | a linked list that adds and removes at its first node |
| LIFO | taking out the most recently added value first |
| linked queue / 연결 큐 | a linked list that appends at `tail` and removes at `head` |
| FIFO | processing records in their arrival order |
| public enqueue / dequeue | accept a value and return success / return a value and recycle its node |
| node helpers | `enqueue_lnode` and `dequeue_lnode` act on slot indices |

## Coding Plan

Build the mechanisms in the order that makes their dependencies visible.

1. Define `Linked_Node` and `lnodes[10]`. Keep each list's first index separately. End each active chain with `-1` and prevent cycles.
2. Preserve the predecessor's old successor in the inserted node, then change the predecessor's link. Remove a successor by pointing past it and retain its index.
3. Link all ten unused slots from `free_head`. Allocate with `new_lnode(data_value,next_value)`. Pass `-1` to obtain a detached node and check the result before indexing.
4. Read needed data before returning a detached node with `free_lnode`. Return exactly once, then stop accessing that node as the old owner.
5. Build a linked Stack in caller code. Insert at `first`, guard empty removal, save the old first's value and successor, advance `first`, then recycle.
6. Trace queue endpoint changes through raw node helpers, then use value-based `enqueue` and `dequeue`. Check insertion status and queue emptiness in the caller.
7. Test exhaustion, deletion after a tail, shared-pool separation, Stack order, queue empty transitions, and reuse from independent valid states. Diagnose missing return, duplicate return, and stale access on paper.

## C Code

The following code is the complete current `lab.c`, including the linked queue example. A driver must include this source only once. Later modules protect their shared import at the include boundary. The source defines no `main`. The test driver includes it. Allocation stores the second argument directly in `next`. The caller must provide a valid successor index or `-1`.

```c
#include <stdbool.h>
#include <assert.h>

struct Linked_Node {
    int data;
    int next;
};

struct Linked_Node lnodes[10];

void link_lnode(int prev, int node) {
    lnodes[node].next = lnodes[prev].next;
    lnodes[prev].next = node;
}

int delete_next_lnode(int prev) {
    int node = lnodes[prev].next;
    if (node != -1) {
        lnodes[prev].next = lnodes[node].next;
    }
    return node;
}

int free_head = -1;

void init_lnodes_pool(void) {
    for (int i = 0; i < 9; i++) {
        lnodes[i].data = 0;
        lnodes[i].next = i + 1;
    }
    lnodes[9].data = 0;
    lnodes[9].next = -1;
    free_head = 0;
}

int new_lnode(int data_value, int next_value) {
    if (free_head == -1) {
        return -1;
    }
    int node = free_head;
    free_head = lnodes[free_head].next;
    lnodes[node].data = data_value;
    lnodes[node].next = next_value;
    return node;
}

void free_lnode(int node) {
    if (node < 0 || node >= 10) {
        return;
    }
    lnodes[node].next = free_head;
    free_head = node;
}

int head = -1;
int tail = -1;

bool is_empty_queue(void) {
    return head == -1;
}

void enqueue_lnode(int node) {
    if (is_empty_queue()) {
        head = tail = node;
    } else {
        lnodes[tail].next = node;
        tail = node;
    }
}

int dequeue_lnode(void) {
    if (is_empty_queue()) {
        return -1;
    }
    int oldest = head;
    if (head == tail) {
        head = tail = -1;
    } else {
        head = lnodes[head].next;
    }
    return oldest;
}

bool enqueue(int value) {
    int node = new_lnode(value, -1);
    if (node == -1) {return false;}
    enqueue_lnode(node);
    return true;
}

int dequeue(void) {
    int node = dequeue_lnode();
    assert(node != -1);
    int value = lnodes[node].data;
    free_lnode(node);
    return value;
}
```

The following caller reproduces the middle insertion, detachment, and reuse. Run each driver below as a separate program with a fresh pool. Save each code block beside `lab.c` and compile the driver alone. All checks and state changes still execute with `NDEBUG`.

```c
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = new_lnode(17, -1);
    int middle = new_lnode(23, -1);
    int last = new_lnode(31, -1);
    if (first == -1 || middle == -1 || last == -1) return 1;
    link_lnode(first, last);
    link_lnode(first, middle);
    int removed = delete_next_lnode(first);
    if (removed != middle || lnodes[first].next != last) return 1;
    free_lnode(removed);
    int reused = new_lnode(8, -1);
    if (reused != middle || lnodes[reused].next != -1) return 1;
    return 0;
}
```

### Apply the same nodes to a Stack

The caller keeps its own `first`. It saves the value and successor before recycling the old first slot. This example adds 17, 23, 31 and checks the output 31, 23, 17. A failed allocation leaves the existing Stack unchanged.

```c
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode(values[i], -1);
        if (node == -1) return 1;
        lnodes[node].next = first;
        first = node;
    }
    for (int i = 2; i >= 0; --i) {
        if (first == -1) return 1;
        int old_first = first;
        int value = lnodes[old_first].data;
        int next = lnodes[old_first].next;
        first = next;
        free_lnode(old_first);
        if (value != values[i]) return 1;
    }
    if (first != -1 || free_head != 0) return 1;
    return 0;
}
```

### Apply the same nodes to a queue

This caller checks insertion success and queue emptiness. `dequeue()` recycles the slot internally. The output is 17, 23, 31. It also checks that the payload `-1` is a valid value.

```c
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    head = tail = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        bool added = enqueue(values[i]);
        if (!added) return 1;
    }
    for (int i = 0; i < 3; ++i) {
        if (is_empty_queue()) return 1;
        int value = dequeue();
        if (value != values[i]) return 1;
    }
    if (!is_empty_queue() || head != -1 || tail != -1) return 1;
    bool added = enqueue(-1);
    if (!added || is_empty_queue()) return 1;
    int value = dequeue();
    if (value != -1 || !is_empty_queue()) return 1;
    return 0;
}
```
