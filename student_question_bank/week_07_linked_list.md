# Week 7 — Linked Lists, Shared Pool, and Linked Stack/Queue: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Use the current `module_07_linked_list/student/lab.c`: ten fixed nodes in
`lnodes[10]`, integer `next` links, a free chain, and separate detachment and
recycling. Follow the updated concept slides through acyclic chains and a saved
first index, safe predecessor insertion/deletion, shared-pool advantages and
costs, allocation/exhaustion, recycling errors and stale access, linked Stack
LIFO, and linked Queue FIFO. Both applications belong in the same artifact.
The linked Stack composes existing primitives in the caller; there is no supplied
linked push/pop API.
The older `malloc`/`free` list API and its destruction exercise are optional;
DSU is introduced with Kruskal in Week 14. [Week 8](week_08_bfs.md) compares
array queues and reuses this exact linked queue for tree BFS and graph BFS.
The raw node operations expose pool slots. The public `enqueue(value)`
allocates a slot and returns `false` on exhaustion; `dequeue()` returns the
stored value and recycles the removed slot. Check `is_empty_queue()` before
public dequeue. Payload `-1` is valid, so it is not an empty-queue result.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| Linked list | A sequence whose order is recorded by links between nodes. |
| Singly linked | Each node stores one link to its following node. |
| Node | One `struct Linked_Node` record in `lnodes[]`, containing integer `data` and `next` fields. |
| Node index | A slot number from 0 through 9, distinct from its stored data. |
| Next link | An integer node index identifying the following node, or `-1`. |
| `-1` sentinel | The value meaning no node; it must not be used as an array index. |
| Acyclic chain | A sequence whose next links never return to a previously reached node. |
| First index | The caller-saved starting node of one list, or `-1` when empty. |
| Shared node pool | One array whose free slots can be allocated to any of several disjoint live lists. |
| Free chain | The linked sequence of pool slots available for allocation. |
| `free_head` | The first available slot index, or `-1` when the pool is exhausted. |
| `init_lnodes_pool` | The function connecting slots 0 through 9 into the initial free chain. |
| `new_lnode` | The function taking a free slot, storing data, and setting its next link to the supplied `next_value`. |
| Pool exhaustion | No free slot remains; `new_lnode` returns `-1` without changing the pool. |
| `free_lnode` | The pool function putting a detached valid slot back at the free-chain front. |
| Recycling | Making a detached slot available again; this does not release array storage. |
| Predecessor | The node immediately before an insertion or detachment position. |
| `link_lnode` | The function inserting a detached allocated node after a predecessor. |
| `delete_next_lnode` | The function bypassing and returning the node after a predecessor, without recycling it. |
| Detachment | Removing a node from a live sequence before reusing or recycling it. |
| Reachability | A node can be reached by following links from a starting index. |
| Invariant | A rule preserved in every valid representation state. |
| Precondition | A requirement the caller must satisfy before an operation. |
| Stale index | An old slot number that no longer conveys ownership after its node is returned. |
| Linked Stack | A list application that adds and removes at the first node. |
| last in, first out (LIFO) | Remove the newest saved item first. |
| Queue | A waiting collection that adds at the back and removes from the front. |
| first in, first out (FIFO) | Remove waiting items in their arrival order. |
| Linked queue | A linked-list application with oldest and newest endpoint indices. |
| `head` | The oldest linked-queue pool slot, or `-1` when empty. |
| `tail` | The newest linked-queue pool slot, or `-1` when empty. |
| `enqueue_lnode` | Append an allocated, detached pool node whose `next` is `-1`. |
| `dequeue_lnode` | Return the oldest pool slot without recycling or clearing its link; return `-1` when empty. |
| `is_empty_queue` | Report whether `head == -1`; call before public dequeue. |
| `enqueue` | Allocate and append a value; return `false` without changes when no pool slot remains. |
| `dequeue` | Remove the oldest value, recycle its pool slot, and return the value; require a nonempty queue. |

## Anticipated student questions

### Acyclic chains and saved first indices

- How does a linked sequence in `lnodes[10]` differ from an ArrayList's active prefix even though both use contiguous arrays?
- Why is a node's index different from the integer stored in its `data` field?
- Why must every valid list in this lesson end at `-1` without revisiting a node?
- Why must traversal stop at `-1` before indexing `lnodes[]`?
- Why does each separate list need a saved first index?

### Predecessor link changes

- Why must `link_lnode(prev, node)` copy the predecessor's old next link before replacing it?
- Which links change when a new node is inserted between two existing nodes?
- How can reversing the insertion writes make the new node point to itself and lose the old successor?
- What does `delete_next_lnode(prev)` return when the predecessor has no following node?
- Why does `delete_next_lnode(prev)` neither recycle the detached node nor clear its old next link?
- Why must the caller manage a separate list-head change instead of passing `-1` as a predecessor?
- Why are known-predecessor insertion and detachment constant work while finding that predecessor can take O(n)?

### Shared pool, costs, and recycling

- Why can separate lists draw any available slot from one free chain without reserving a fixed array partition for each list?
- How do the extra next field and saved endpoints increase storage compared with values alone?
- How many next links must be followed to reach zero-based position i from the first node?
- What chain does `init_lnodes_pool()` create, and why does slot 9 end in `-1`?
- Why does initialization visit every reserved slot while one allocation uses a fixed number of updates?
- What happens to live links if `init_lnodes_pool()` is called while any list still owns a slot?
- How do `free_head` and the chosen node change when `new_lnode(17, -1)` succeeds?
- What remains unchanged when an eleventh allocation returns `-1` from an exhausted pool?
- Why does `free_lnode(node)` change the free chain without releasing C array storage?
- Why must a node leave every live list before it is recycled?
- How does detaching a node without returning it reduce the shared pool's available capacity?
- Why can recycling the same valid index twice corrupt the free chain even though the bounds check passes?
- If A returns slot 0 and B allocates 8 into slot 0, why can A's stale read see 8 and A's stale write damage B?
- Why must all live and detached allocations across every list fit within the same ten slots?

### Linked Stack from first-node operations

- How does prepending 17,23,31 produce LIFO output 31,23,17 without a tail index?
- Why must a caller check `new_lnode(value,first)` before replacing `first`?
- Why must removal check `first != -1` before accessing the first node?
- Which old index, data, and next values must be saved before advancing first and recycling the removed slot?
- Why must a caller avoid reading or modifying the removed slot after it has been returned?
- How do these caller-side steps implement a linked Stack even though `lab.c` supplies no linked push/pop API?

### Linked Queue from opposite-end operations

- How does FIFO order differ from the linked Stack's LIFO order for values 17,23,31?
- How does the first `enqueue(value)` allocate a node and set both `head` and `tail` to its pool slot?
- Why does public `enqueue` allocate with next `-1`, and what remains unchanged when it returns `false` from an exhausted pool?
- Which tail link changes when `enqueue_lnode` appends another detached node, and why is no tail search needed?
- How does removing the only queued value restore both endpoints to `-1` and return its slot to the free chain?
- How do the raw `dequeue_lnode()` pool-slot result and the public `dequeue()` value result differ, especially when the stored value is `-1`?
- Why does public `dequeue()` copy the payload before recycling, and why must the caller avoid recycling that slot a second time?
- Why must the caller check `is_empty_queue()` before public dequeue even though a debug assertion diagnoses an empty request?
- Why must `enqueue(value)` run outside an `assert` expression when builds may define `NDEBUG`?
- Which shared-pool, linked Stack LIFO, and linked Queue FIFO/endpoint evidence belongs inside the same three original test groups and single Week 7 artifact?

## Sources

- [Updated concept slides](../module_07_linked_list/student/ppt_material.md)
- [Current lab source](../module_07_linked_list/student/lab.c)
- [Student textbook](../module_07_linked_list/student/textbook.md)
- [Class workbook](../module_07_linked_list/student/class_material.md)
- [Module 7 lesson, lab, and release](../module_07_linked_list/README.md)
- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
