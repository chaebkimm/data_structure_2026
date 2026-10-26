# Week 7 — Linked Lists with a Linked Queue Example: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Use the current `module_07_linked_list/student/lab.c`: ten fixed nodes in
`lnodes[10]`, integer `next` links, a free chain, and separate detachment and
recycling. Trace initialization, allocation, insertion after a predecessor,
detachment, exhaustion, and slot reuse. Then use a linked FIFO queue as a
concrete example of changing list endpoints in the same artifact.
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

### Representation and free-chain initialization

- How does a linked sequence in `lnodes[10]` differ from an ArrayList's active prefix even though both use contiguous arrays?
- Why is a node's index different from the integer stored in its `data` field?
- What chain does `init_lnodes_pool()` create, and why does slot 9 end in `-1`?
- Why must traversal stop at `-1` before indexing `lnodes[]`?
- What happens to live links if `init_lnodes_pool()` is called while the pool is still in use?
- Why does initialization visit every reserved slot while one allocation uses a fixed number of updates?

### Allocation, detachment, and recycling

- How do `free_head` and the chosen node change when `new_lnode(17, -1)` succeeds?
- What remains unchanged when an eleventh allocation returns `-1` from an exhausted pool?
- Why does `free_lnode(node)` change the free chain without releasing C array storage?
- Why must a node leave every live list before it is recycled?
- Why can recycling the same valid index twice corrupt the free chain even though the bounds check passes?
- Which returned index is used next after allocating slots 0 and 1, recycling slot 0, and allocating again?

### Predecessor link changes

- Why must `link_lnode(prev, node)` copy the predecessor's old next link before replacing it?
- Which links change when a new node is inserted between two existing nodes?
- What does `delete_next_lnode(prev)` return when the predecessor has no following node?
- Why does `delete_next_lnode(prev)` neither recycle the detached node nor clear its old next link?
- Why must the caller manage a separate list-head change instead of passing `-1` as a predecessor?
- Why are known-predecessor insertion and detachment constant work while finding that predecessor can take O(n)?

### Linked queue as a linked-list example

- How does FIFO order differ from the Stack's LIFO order for values 17, 23, and 31?
- How does the first `enqueue(value)` allocate a node and set both `head` and `tail` to its pool slot?
- Why does public `enqueue` allocate with next `-1`, and what remains unchanged when it returns `false` from an exhausted pool?
- Which tail link changes when `enqueue_lnode` appends another detached node, and why is no tail search needed?
- How does removing the only queued value restore both endpoints to `-1` and return its slot to the free chain?
- How do the raw `dequeue_lnode()` pool-slot result and the public `dequeue()` value result differ, especially when the stored value is `-1`?
- Why does public `dequeue()` copy the payload before recycling, and why must the caller avoid recycling that slot a second time?
- Why must the caller check `is_empty_queue()` before public dequeue even though a debug assertion diagnoses an empty request?
- Why must `enqueue(value)` run outside an `assert` expression when builds may define `NDEBUG`?
- Which endpoint, live-chain, free-chain, and full-queue traces show public FIFO behavior and automatic slot reuse in the single Week 7 artifact?

## Sources

- [Current lab source](../module_07_linked_list/student/lab.c)
- [Student textbook](../module_07_linked_list/student/textbook.md)
- [Class workbook](../module_07_linked_list/student/class_material.md)
- [Module 7 lesson, lab, and release](../module_07_linked_list/README.md)
- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
