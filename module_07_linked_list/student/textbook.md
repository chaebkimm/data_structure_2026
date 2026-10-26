# Chapter 7. Linked Lists

Chapter 1 keeps values in consecutive active array slots. Here we change their logical order without shifting the values. The current `lab.c` uses ten array slots and integer links.

[한글 교재](textbook_korean.md) · [Class workbook](class_material.md) · [Concept slides](ppt_material.md) · [Lab slides](ppt_lab_material.md)

## Thinking Logically

### Can the order change without shifting values?

Suppose three records contain 17, 23, and 31. We want to follow them in that order. Later we want to insert another record between two existing records. In an array list, inserting into the active middle shifts the following values. Instead, let each record remember which record follows it. Changing that recorded destination changes the order.

A record containing a value and a following link is a **node**. A sequence formed by following one link per node is a **singly linked list**. A link can hold an address, but this lab uses an array index. The physical array still exists; the logical order follows links rather than neighboring positions.

Each node has two integer fields. `data` holds the value. `next` holds the next node's index. Valid indices are 0 through 9. The value `-1` means there is no next node. Never use `-1` as an array index.

```text
Physical slots:  lnodes[0]       lnodes[1]       lnodes[2]
Fields:         data=17,next=1  data=23,next=2  data=31,next=-1
Logical order:  0 → 1 → 2 → -1
Values:         17 → 23 → 31
```

Indices and values have different jobs. The value 23 is stored at index 1. Reusing slot 1 can change its value while keeping the same index.

### Where does an available node come from?

Before adding a record, we need an unused slot. Scanning the whole array would repeat the same search on every allocation. Link the available slots together instead. This chain is a **free list**. The fixed array of reusable nodes is a **node pool**.

`free_head` holds the first available index. `init_lnodes_pool()` sets every value to zero and constructs this chain:

```text
free_head = 0
free chain: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

`new_lnode(value, -1)` removes the first free slot. It advances `free_head`, writes the requested value, and stores its second argument as `next`. Passing `-1` creates a detached node. The return value is an index, not the stored data. If the free chain is empty, it returns `-1` and changes nothing.

| Request after initialization | Returned index | `free_head` | Chosen node |
| --- | ---: | ---: | --- |
| `new_lnode(17, -1)` | 0 | 1 | `data=17, next=-1` |
| `new_lnode(23, -1)` | 1 | 2 | `data=23, next=-1` |
| `new_lnode(31, -1)` | 2 | 3 | `data=31, next=-1` |

These three nodes are allocated but still separate. **Allocated** here means removed from the free chain and assigned to the caller. The program does not request heap storage. None of these functions calls C's `malloc` or `free`.

### How do we insert after a known node?

We have three separate nodes. First call `link_lnode(0, 1)`. Then call `link_lnode(1, 2)`. The result is the chain containing 17, 23, and 31 shown above. Keep the first index separately, for example in a caller variable named `first`.

To insert a node after `prev`, first copy the previous node's old link into the inserted node. Then point `prev` at the inserted node:

```text
lnodes[node].next = lnodes[prev].next
lnodes[prev].next = node
```

Reversing these writes loses the old successor and can make the new node point to itself. `link_lnode` neither allocates a slot nor searches for a value. The caller supplies two valid, distinct allocated indices. The inserted node must be detached from every other active chain and absent from the free chain.

### Does removing a link also recycle its node?

Now remove the node after index 0. `delete_next_lnode(0)` saves index 1, changes `lnodes[0].next` to 2, and returns 1.

```text
Before: first=0; 0(17) → 1(23) → 2(31) → -1
After:  first=0; 0(17) → 2(31) → -1
Returned: 1; lnodes[1].next is still 2; free_head is still 3
```

The removed node is **detached**: the active chain no longer reaches it. Detaching does not add it to the free chain. The caller can inspect `lnodes[1].data`, then call `free_lnode(1)` to recycle the slot:

```text
free_head = 1
free chain: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode` overwrites `next` and leaves `data` unchanged. The next `new_lnode(8, -1)` returns index 1 with `data=8, next=-1`. The old value 23 no longer belongs to a live record.

The caller controls **ownership**: responsibility for keeping a slot in one state at a time. A slot belongs to the free chain, to one active chain, or to the caller as a detached allocation. Those states must not overlap. Returning an active node corrupts its links. Returning the same node twice can make a cycle in the free chain. The range check in `free_lnode` does not detect these mistakes.

`delete_next_lnode(prev)` returns `-1` without changing links when a valid predecessor has no successor. It does not search for the first matching value and cannot directly delete the first node without a predecessor. Changing a separate first index is the caller's job.


### How can one linked list preserve arrival order?

Suppose requests 17, 23, and 31 must be processed in the order they arrive. Insert each record after the last and remove the first. Remember both ends so neither action needs a search. This first-in, first-out rule is **FIFO**. A **queue** uses that rule. The linked queue applies the same nodes from this chapter.

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

The first insertion sets both endpoints; the last removal restores both to `-1`. Reusing slot 0 behind waiting slots preserves arrival order even though array-index order changes. Module 8 stores tree-node or graph-vertex IDs as queue values and uses the same `enqueue` and `dequeue` functions. Its BFS code no longer allocates or recycles queue nodes directly.

## Calculating Efficiency


### How much work changes one link?

Allocation removes the first free index. Recycling prepends one index. Insertion after a known predecessor changes two links. Deletion after a known predecessor reads one successor and changes at most one link. None scans the chain, so each operation takes O(1) work. Searching for a predecessor by value may inspect all `n` active nodes, so that separate search takes O(n).

Initializing a capacity of `C` slots writes each slot once: O(C). The lab fixes `C=10`. The pool reserves storage for ten two-integer node records regardless of how many are active. It uses O(C) storage and O(1) additional local storage per operation. Allocation failure means the free chain is exhausted; it does not mean the operating system refused a heap request.

### How much work keeps the queue in arrival order?

Public enqueue adds constant pool-allocation work to the saved-tail append. Public dequeue copies one value and adds constant recycling work to the saved-head removal. Both take O(1) work. Ten slots limit simultaneous allocated records, not the total processed over repeated value enqueue/dequeue cycles. Module 8 uses this distinction for BFS.

## Glossary


The following names describe the mechanisms traced above.

| Term | Meaning in this lab |
| --- | --- |
| node / 노드 | one `data` field and one `next` field |
| singly linked list / 단일 연결 리스트 | a sequence whose nodes each record one following index |
| node pool / 노드 풀 | the fixed `lnodes[10]` storage |
| free list / 가용 리스트 | available indices linked from `free_head` |
| allocation / 할당 | removing a slot from the free chain for use |
| detach / 분리 | removing a node from an active chain without recycling it |
| recycle / 반환 | adding an allocated, detached slot to the free chain |
| ownership / 소유 책임 | responsibility for keeping a slot in exactly one valid state |
| traversal / 순회 | repeatedly following `next` until `-1` |
| linked queue / 연결 큐 | the linked-list example that appends at `tail` and removes at `head` |
| FIFO | processing records in their arrival order |
| public enqueue / dequeue | accept a value and return success / return a value and recycle its node |
| node helpers | `enqueue_lnode` and `dequeue_lnode` act on slot indices |


## Coding Plan

Build the mechanisms in the order that makes their dependencies visible.

1. Define `Linked_Node`, `lnodes[10]`, and `free_head`. Link all ten free slots, ending at `-1`.
2. Allocate with `new_lnode(data_value, next_value)`. Pass `-1` as the second argument to obtain a detached node.
3. Preserve the predecessor's old successor in the inserted node, then change the predecessor's link.
4. Return the detached successor's index. Recycle it with `free_lnode` only after its use is complete.
5. Keep the first-node index in the caller. Check returned indices and stop before indexing `-1`.
6. Test exhaustion, deletion after a tail, and detach/recycle/reuse from independent valid states.
7. Trace raw node helpers, then hide allocation and recycling behind value-based `enqueue` and `dequeue`. Check insertion status and queue emptiness in the caller.

## C Code

The following code is the complete current `lab.c`, including the linked queue example. A driver must include this source only once; later modules protect their shared import at the include boundary. It defines no `main`; the test driver includes it. Allocation stores the second argument directly in `next`. The caller must provide a valid successor index or `-1`.

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

To allocate three detached slots and connect them, use the following caller. Run it in a new process or when no active node users remain. Check every allocation result before using its index.

```c
#include <assert.h>
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = new_lnode(17, -1);
    int middle = new_lnode(23, -1);
    int last = new_lnode(31, -1);
    assert(first != -1 && middle != -1 && last != -1);
    link_lnode(first, last);
    link_lnode(first, middle);
    int removed = delete_next_lnode(first);
    assert(removed == middle && lnodes[first].next == last);
    free_lnode(removed);
    int reused = new_lnode(8, -1);
    assert(reused == middle && lnodes[reused].next == -1);
    return 0;
}
```

### Apply the same nodes to a queue

Start a fresh independent pool. The following caller uses values, checks insertion success, and leaves node recycling inside `dequeue()`. Its operations still execute with `NDEBUG`.

```c
#include <assert.h>
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
    assert(is_empty_queue() && head == -1 && tail == -1);
    bool added = enqueue(-1);
    if (!added || is_empty_queue()) return 1;
    int value = dequeue();
    if (value != -1 || !is_empty_queue()) return 1;
    return 0;
}
```
