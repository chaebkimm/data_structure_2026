# Chapter 7. Linked Lists

Chapter 1 keeps values in consecutive active array slots. Here we change their logical order without shifting the values. The current `lab.c` uses ten array slots and integer links. We apply the same links to a Stack and a queue.

[한글 교재](textbook_korean.md) · [Class workbook](class_material.md) · [Concept slides](ppt_material.md) · [Lab slides](ppt_lab_material.md) · [Question slides](ppt.md) · [Lab](lab.md)

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

We want to put 23 between 17 and 31. The old successor of slot 0 is slot 2. First give the new node that successor. Then make slot 0 point to the new node. `simple_link_lnode_to_prev(0, 1)` performs these two writes:

```text
lnodes[1].next = lnodes[0].next   // 2
lnodes[0].next = 1
Result: first=0; 0(17) → 1(23) → 2(31) → -1
```

Reversing the writes first replaces the only link from slot 0 to slot 2. The second write then copies 1 into `lnodes[1].next`, creating a self-cycle. Preserve the old successor before replacing the predecessor's link.

`simple_link_lnode_to_prev(prev,node)` neither obtains a slot nor searches for a value. The caller supplies two valid, distinct indices that are already assigned for use. The predecessor belongs to an ordinary list, not the queue. The inserted node must be outside every active chain and the chain of unused nodes, with `next=-1`. Inserting a node already in a chain can create a cycle or mix two lists.

### How do we remove the middle node?

The predecessor must point past the removed node. `simple_delink_next_lnode_from_prev(0)` saves index 1, changes `lnodes[0].next` to 2, clears `lnodes[1].next` to `-1`, and returns 1.

```text
Before: first=0; 0(17) → 1(23) → 2(31) → -1
After:  first=0; 0(17) → 2(31) → -1
Returned: 1; lnodes[1].next = -1
```

The removed node is **detached**: the active chain no longer reaches it. Its `next` is now `-1`, so it is isolated from the remaining nodes. The caller retains the returned index until the node is used elsewhere or returned for reuse. Removing the link does not make the slot available automatically.

With a valid predecessor that has no successor, `simple_delink_next_lnode_from_prev(prev)` returns `-1` and changes nothing. The function does not search for a matching value. It also cannot update the caller's `first`. The predecessor must belong to an ordinary list, not the queue. Removing the first node requires the caller to save the old first index and advance `first` to that node's successor. Set the old first's `next` to `-1` before recycling or inserting it elsewhere.

### Can several lists use one array?

We can change the middle of a list without moving the following values. We need its predecessor first. To find the third node, start at `first` and follow two links. The expression `lnodes[2]` means physical slot 2, not the third node in logical order. Each node also spends one integer on its following link.

Suppose two lists need different amounts of space over time. Reserving five of ten slots for each prevents the first list from using a sixth slot even when the second uses only one. Instead, let either list take any available slot. Each list keeps its own first index. Their active nodes stay separate. The array still holds only ten nodes in total. Sharing unused space does not increase that capacity.

### Where does an available node come from?

Before adding a record, we need an unused slot. Scanning the whole array would repeat the same search on every request. Link the available slots together instead. This chain is a **free list**. The fixed array of reusable nodes is a **node pool**. Give its size a name so the declarations and loops use the same limit. `enum { CAPACITY = 10 };` attaches the name `CAPACITY` to the integer constant 10.

`free_head` holds the first available index. The first `init_lnodes_pool()` call constructs this chain:

```text
free_head = 0
free chain: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

An initializer that rewrites this chain on every call could overwrite nodes already in use. The local `static int initialized` keeps its value between calls. It starts at 0 once, becomes 1 on the first call, and makes later calls return without changes. This initializer does not reset a used pool. It writes links, not payloads. Global array storage begins with zero values when the program starts; later calls do not clear the data.

`new_lnode()` calls the initializer, then removes the first free slot. It advances `free_head` and sets that slot's `next=-1`. It accepts no arguments and does not set `data`. Check the returned index, then assign the desired payload. If the free chain is empty, it returns `-1` and changes nothing.

| Request and caller assignment in a fresh program | Returned index | `free_head` | Chosen node |
| --- | ---: | ---: | --- |
| allocate; check index; store 17 | 0 | 1 | `data=17, next=-1` |
| allocate; check index; store 23 | 1 | 2 | `data=23, next=-1` |
| allocate; check index; store 31 | 2 | 3 | `data=31, next=-1` |

Each assignment above requires checking the returned index against `-1` first. These nodes are **allocated**: removed from the free chain and assigned to the caller. None of these functions calls C's `malloc` or `free`. To reproduce the insertion above, call `simple_link_lnode_to_prev(0,2)` and then `simple_link_lnode_to_prev(0,1)`.

The same allocations can instead form two lists: `first_a=0` with `0(17)→2(31)→-1`, and `first_b=1` with `1(23)→-1`. Both use the free chain beginning at 3. An allocation for either list takes the first available slot. Calling `init_lnodes_pool()` again preserves both lists and the current free chain. To make nodes available again, detach and return them; another initializer call does not reclaim them.

### When can a removed slot be reused?

Return to the one-list example `0(17)→1(23)→2(31)→-1`, with `free_head=3`. After `simple_delink_next_lnode_from_prev(0)`, index 1 is detached and `free_head` is still 3. Read any needed value before calling `free_lnode(1)`. That call prepends the slot to the free chain:

```text
free_head = 1
free chain: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode` overwrites `next` and leaves `data` unchanged. The next `new_lnode()` returns index 1 with `next=-1` and the old payload 23. The new caller writes `lnodes[1].data=8` before using the record. Another list can receive that slot.

The caller controls **ownership**: responsibility for keeping a slot in one state at a time. A slot belongs to the free chain, to one active chain, or to the caller as a detached allocation. Those states must not overlap. A detached slot that is never returned stays unavailable. Losing its saved index can exhaust the pool even when fewer than ten nodes remain in active lists.

Returning an active node overwrites a link still used by its list. Returning slot 1 twice consecutively makes `lnodes[1].next=1`, a cycle in the free chain. `free_lnode(-1)` does nothing. Any other argument must be an in-range, allocated, unreferenced node with `next=-1`. The function checks neither bounds nor ownership for such arguments. Diagnose them on paper rather than executing corrupted chains.

After returning slot 1, the old caller must stop using that slot as its record. Before reuse, `next` belongs to the free chain and `data` may still hold 23. After reuse, a read can see 8 from another list. Writing `next` can corrupt that list or the free chain. Writing `data` can change another caller's value. Save the needed value and successor before returning a node.

### How can the last value added come out first?

Chapter 4 removes the last value added. Keep that same LIFO rule using links. Add each new record at the first node and remove from the same end. A Stack built from linked nodes is a **linked Stack**. The caller's `first` marks its top.

Start a fresh program with `first=-1`. To add a value, allocate a separate node and check success. Write its `data`, set its `next` to the old `first`, then set `first` to the new index. If allocation returns `-1`, leave `first` and the existing links unchanged.

To remove a value, check `first!=-1`. Save the old first index, its value, and its successor. Advance `first` to the successor and set the old slot's `next=-1`. Then return the old slot with `free_lnode`. There is no predecessor to pass to `simple_delink_next_lnode_from_prev` at this end. The caller performs the first-index update directly.

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

The source keeps global `qhead` and `qtail`, both initially `-1`. To insert a value, call `new_lnode()`, check its index, write its `data`, and pass that index to `enqueue_lnode(node)`. The node must be allocated, unreferenced, and isolated with `next=-1`. With a nonempty queue, the old tail points to it and `qtail` moves to it. With an empty queue, both endpoints become that node. The append itself allocates nothing and returns no success value. `enqueue_lnode(-1)` does nothing.

`dequeue_lnode()` returns the oldest **node index**, not its payload. It advances `qhead`, clears the returned node's `next` to `-1`, and leaves the node allocated to the caller. Removing the only node also sets `qtail=-1`. On an empty queue it returns `-1` without changes. Check the returned index before reading `lnodes[node].data`, then return the detached node with `free_lnode(node)` when finished.

A payload of `-1` is valid. The empty marker applies to node indices, not stored values. The source provides no value-based `enqueue` or `dequeue` wrapper. Allocation, data assignment, append, removal, data read, and recycling remain separate steps in the caller.

| Action in a fresh program | Returned node | `qhead` | `qtail` | Queue slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| allocate 0, store 17, append 0 | allocation: 0 | 0 | 0 | 0 → -1 | 1 |
| allocate 1, store 23, append 1 | allocation: 1 | 0 | 1 | 0 → 1 → -1 | 2 |
| allocate 2, store 31, append 2 | allocation: 2 | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue_lnode()` | 0; read value 17 | 1 | 2 | 1 → 2 → -1 | 3 |
| `free_lnode(0)` | none | 1 | 2 | 1 → 2 → -1 | 0 |
| allocate 0, store 8, append 0 | allocation: 0 | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| remove, read, recycle 23, 31, 8 | indices 1, 2, 0 | -1 | -1 | empty | 0 (all ten free) |

Reusing slot 0 behind waiting slots preserves arrival order even though array-index order changes. A later BFS caller can store tree-node or graph-vertex IDs in `data`. That stored ID still differs from the pool-slot index returned by `dequeue_lnode()`.

### Which rules must remain true?

Once the pool is initialized, account for every slot and every endpoint after each complete operation. These continuing rules are **invariants**.

- Every active chain and the free chain uses indices 0–9, has no repeated node, and ends at `-1`.
- Each of the ten slots belongs to exactly one active chain, the free chain, or a caller as a detached allocation. Different owners do not overlap. A detached node is isolated with `next=-1`.
- Each ordinary list keeps its first index separately. The queue is empty exactly when `qhead == -1 && qtail == -1`.
- In a nonempty queue, `qtail` is the last node reached from `qhead`, and `lnodes[qtail].next == -1`.
- Appending at the tail and removing at the head preserves FIFO order. A removed node remains allocated until the caller returns it exactly once.

These are conditions after a helper or complete caller update. A helper does not check all of them. Use the documented preconditions before calling it. In particular, use queue helpers for queued nodes; ordinary predecessor helpers would leave the queue endpoints out of date.

## Calculating Efficiency

### How much work changes one link?

After initialization, allocation removes the first free index. Recycling prepends one index. Insertion after a known predecessor changes two links. Deletion after a known predecessor reads one successor, bypasses it, and sets the removed node's link to `-1`. None scans the chain, so each operation takes O(1) work. Searching for a predecessor by value may inspect all `n` active nodes, so that separate search takes O(n).

The first node needs no link traversal to reach. The third needs two `next` steps. The last of `n` nodes needs `n-1` steps from the first. Finding a position by its logical order can therefore take O(n), while accessing a known physical array index takes O(1).

### How much memory do the links use?

Each node stores one integer value and one extra integer link. The lab reserves ten two-integer records plus `free_head`, `qhead`, `qtail`, and the persistent initialization flag, regardless of how many records are active. Several lists can share unused slots, but each additional list needs its own first index. A slot cannot count toward two active lists at once.

The first initialization of capacity `C` writes each link once: O(C). Here `C=10`. If `new_lnode()` performs that first initialization, that first allocation is O(C). Later initializer calls and allocations take O(1). The pool uses O(C) storage and O(1) additional local storage per operation. Allocation failure means the free chain is exhausted. No operating-system heap request occurs.

### How much work keeps a Stack or queue in order?

A linked Stack changes `first` and a fixed number of node fields. Adding or removing its first record takes O(1). The queue helpers append at the saved tail and detach the saved head with a fixed number of writes. Both take O(1). After initialization, the caller's allocation, data assignment, payload read, and recycling also take O(1) each.

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
| detach / 분리 | removing a node from an active chain and setting its `next=-1`, without recycling it |
| recycle / 반환 | adding an allocated, detached slot to the free chain |
| ownership / 소유 책임 | responsibility for keeping a slot in exactly one valid state |
| stale index / 이전 소유자의 인덱스 | an index kept after returning a node, which no longer identifies that caller's record |
| linked Stack / 연결 스택 | a linked list that adds and removes at its first node |
| LIFO | taking out the most recently added value first |
| linked queue / 연결 큐 | a linked list that appends at `qtail` and removes at `qhead` |
| FIFO | processing records in their arrival order |
| enqueue / 삽입 | `enqueue_lnode` appends an allocated isolated node index |
| dequeue / 제거 | `dequeue_lnode` returns an isolated node index; the caller reads and recycles it |
| invariant / 불변식 | a rule preserved after complete operations |
| `enum` / 열거 상수 | gives a name such as `CAPACITY` to an integer constant |
| `static` local / 정적 지역 변수 | keeps its value between calls; initialization happens once |

## Coding Plan

Build the mechanisms in the order that makes their dependencies visible.

1. Define `Linked_Node` and `lnodes[CAPACITY]`, where `enum { CAPACITY = 10 };` names the integer constant 10. Keep each list's first index separately. End each active chain with `-1` and prevent cycles.
2. Preserve the predecessor's old successor in the inserted node, then change the predecessor's link. Remove a successor by pointing past it, isolate it with `next=-1`, and retain its index.
3. Link all ten unused slots from `free_head` on the first initializer call. Keep the local `static` flag so later calls preserve the pool. Allocate with `new_lnode()`, check its index, and write `data` in the caller.
4. Read needed data before returning an allocated, unreferenced, isolated node with `free_lnode`. Return exactly once, then stop accessing that node as the old owner.
5. Build a linked Stack in caller code. Insert at `first`, guard empty removal, save the old first's value and successor, advance `first`, isolate the old node, then recycle.
6. Keep queue endpoints in `qhead` and `qtail`. Allocate, write data, and append with `enqueue_lnode`. Detach with `dequeue_lnode`, check the index, read the payload, then recycle. Restore both empty endpoints after the last removal.
7. Test exhaustion, deletion after a tail, repeated initialization, shared-pool separation, Stack order, queue empty transitions, and reuse from valid states. Use separate programs for fresh-pool fixtures. Diagnose missing return, duplicate return, and stale access on paper.

## C Code

The following code is the complete current `lab.c`, including the linked queue example. Include this source once in a driver; it defines no `main`. `enum` gives the integer constant 10 the name `CAPACITY`. The lab slides use shorter names for the same ideas:

| Lab-slide name | Current `lab.c` name |
| --- | --- |
| `arr`, `CAP`, `fhead` | `lnodes`, `CAPACITY`, `free_head` |
| `link_node`, `del_next_node` | `simple_link_lnode_to_prev`, `simple_delink_next_lnode_from_prev` |
| `init_nodes_pool`, `new_node`, `free_node` | `init_lnodes_pool`, `new_lnode`, `free_lnode` |
| `enqueue_node`, `dequeue_node`, `is_empty` | `enqueue_lnode`, `dequeue_lnode`, `is_empty_queue` |

The slides clear the new tail's `next` inside `enqueue_node`. The source requires the caller to supply an isolated node whose `next` is already `-1`. Follow that source precondition in executable drivers.

```c
enum { CAPACITY = 10 };

struct Linked_Node {
  int data;
  int next;
};
struct Linked_Node lnodes[CAPACITY];

/* Unchecked: caller guarantees 0 <= prev, node < CAPACITY,
 * prev != node, prev is an allocated non-queue node,
 * and node is allocated, unreferenced, and isolated (lnodes[node].next == -1). */
void simple_link_lnode_to_prev(int prev, int node) {
	lnodes[node].next = lnodes[prev].next;
	lnodes[prev].next = node;
}

/* Unchecked: caller guarantees 0 <= prev < CAPACITY and prev is an
 * allocated non-queue node.
 * Returns the detached node index (or -1 if none); caller owns the returned node. */
int simple_delink_next_lnode_from_prev(int prev) {
	int node = lnodes[prev].next;
	if (node != -1) {
		lnodes[prev].next = lnodes[node].next;
		lnodes[node].next = -1;
	}
	return node;
}

int free_head = -1;

/* Initializes the free list on first use; does not reset an active pool. */
void init_lnodes_pool(void) {
	static int initialized = 0;
	if (initialized) { return; }
	initialized = 1;

	for (int i = 0; i < CAPACITY - 1; i++) {
		lnodes[i].next = i + 1;
	}
	lnodes[CAPACITY - 1].next = -1;
	free_head = 0;
}

int new_lnode(void) {
	init_lnodes_pool();
	if (free_head == -1) {
		return -1;
	}
	int node = free_head;
	free_head = lnodes[free_head].next;
	lnodes[node].next = -1;
	return node;
}

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void free_lnode(int node) {
	if (node == -1) {
		return;
	}
	lnodes[node].next = free_head;
	free_head = node;
}

int qhead = -1;
int qtail = -1;

int is_empty_queue(void) { return qhead == -1; }

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void enqueue_lnode(int node) {
	if (node == -1) {
		return;
	}
	if (is_empty_queue()) {
		qhead = qtail = node;
	} else {
		lnodes[qtail].next = node;
		qtail = node;
	}
}

/* Returns the detached node index (or -1 if none); caller owns the returned node. */
int dequeue_lnode(void) {
	if (is_empty_queue()) {
		return -1;
	}
	int oldest = qhead;
	qhead = lnodes[qhead].next;
	if (qhead == -1) {
		qtail = -1;
	}
	lnodes[oldest].next = -1;
	return oldest;
}
```

The following caller reproduces insertion, detachment, and reuse. It also checks that repeated initialization preserves live nodes and that allocation leaves the previous payload unchanged. Run each driver below as a separate program, so each begins with fresh program storage. Save a driver beside `lab.c` and compile the driver alone. The checks and state changes execute with or without `NDEBUG`.

```c
#include "lab.c"

int main(void) {
    int first = new_lnode();
    int middle = new_lnode();
    int last = new_lnode();
    if (first == -1 || middle == -1 || last == -1) return 1;
    lnodes[first].data = 17;
    lnodes[middle].data = 23;
    lnodes[last].data = 31;
    simple_link_lnode_to_prev(first, last);
    simple_link_lnode_to_prev(first, middle);
    int saved_free_head = free_head;
    init_lnodes_pool(); /* This repeated call must preserve live links. */
    if (free_head != saved_free_head || lnodes[first].next != middle) return 1;
    int removed = simple_delink_next_lnode_from_prev(first);
    if (removed != middle || lnodes[first].next != last) return 1;
    if (lnodes[removed].next != -1 || lnodes[removed].data != 23) return 1;
    free_lnode(removed);
    int reused = new_lnode();
    if (reused != middle || lnodes[reused].next != -1) return 1;
    if (lnodes[reused].data != 23) return 1;
    lnodes[reused].data = 8;
    free_lnode(reused);
    removed = simple_delink_next_lnode_from_prev(first);
    if (removed != last || lnodes[first].next != -1) return 1;
    free_lnode(removed);
    if (simple_delink_next_lnode_from_prev(first) != -1) return 1;
    free_lnode(first);
    return 0;
}
```

### Apply the same nodes to a Stack

The caller keeps its own `first`. It saves the value and successor, advances `first`, isolates the old first, then recycles it. This example adds 17, 23, 31 and checks the output 31, 23, 17. A failed allocation leaves the existing Stack unchanged.

```c
#include "lab.c"

int main(void) {
    int first = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode();
        if (node == -1) return 1;
        lnodes[node].data = values[i];
        lnodes[node].next = first;
        first = node;
    }
    for (int i = 2; i >= 0; --i) {
        if (first == -1) return 1;
        int old_first = first;
        int value = lnodes[old_first].data;
        int next = lnodes[old_first].next;
        first = next;
        lnodes[old_first].next = -1;
        free_lnode(old_first);
        if (value != values[i]) return 1;
    }
    if (first != -1 || free_head != 0) return 1;
    return 0;
}
```

### Apply the same nodes to a queue

The caller allocates and fills each node before append. It checks every returned index, reads the data, and recycles the detached slot. The output is 17, 23, 31. A payload `-1` is also valid; an empty dequeue returns the index marker `-1` instead.

```c
#include "lab.c"

int main(void) {
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode();
        if (node == -1) return 1;
        lnodes[node].data = values[i];
        enqueue_lnode(node);
    }
    for (int i = 0; i < 3; ++i) {
        int node = dequeue_lnode();
        if (node == -1) return 1;
        int value = lnodes[node].data;
        if (lnodes[node].next != -1) return 1;
        free_lnode(node);
        if (value != values[i]) return 1;
    }
    if (!is_empty_queue() || qhead != -1 || qtail != -1) return 1;
    if (dequeue_lnode() != -1) return 1;
    int node = new_lnode();
    if (node == -1) return 1;
    lnodes[node].data = -1;
    enqueue_lnode(node);
    node = dequeue_lnode();
    if (node == -1) return 1;
    int value = lnodes[node].data;
    free_lnode(node);
    if (value != -1 || !is_empty_queue() || qtail != -1) return 1;
    return 0;
}
```
