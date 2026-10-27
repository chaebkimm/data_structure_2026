# Module 07 Vocabulary Reference

Keep closed until the Cognitive Pause is preserved. Definitions follow
[lab.c](lab.c), whose links are integer indices.

| Term | Meaning in this lab |
|---|---|
| node | One `struct Linked_Node` record with `data` and `next`. |
| index | Slot number 0–9, distinct from stored data. |
| sentinel | Reserved `-1`, meaning no node; never an array subscript. |
| singly linked list | Acyclic sequence reached by following one `next` per node, ending at `-1` in this lab. |
| first-node index | Caller's starting index for a standalone list. |
| traversal | Follow links until `-1`. |
| predecessor / successor | Node immediately before / after another in a chain. |
| pool | Ten reusable slots in `lnodes[10]`. |
| free chain | Available slots linked through `next`. |
| `free_head` | First available index, or `-1` when exhausted. |
| allocate | `new_lnode` removes a free slot, writes data and the supplied next argument, returns its index. |
| detached node | Allocated slot held by its caller, outside active/free chains; its link may be stale. |
| recycle | `free_lnode` pushes a detached allocated slot onto the free chain. |
| shared pool | Several disjoint lists draw from one free chain and keep separate first indices. |
| missing return | A detached slot remains allocated because its caller never recycles it. |
| stale access | An old index is used after recycling; its slot may now belong to the free chain or another list. |
| double recycling | Recycling an already-free slot, potentially cycling the free chain. |
| invariant | Condition every valid observable state satisfies. |
| precondition | Condition the caller must establish before a call. |
| physical slot | Actual array position; removed data may remain stored there. |
| `O(1)` | Constant number of operations independent of chain length. |
| `O(n)` | Work proportional to visited nodes. |
| linked Stack | Prepend and remove at the caller-owned first index. |
| LIFO | Last in, first out: 17,23,31 leave as 31,23,17. |
| linked queue | Linked-list application that appends at the tail and removes from the head. |
| FIFO | First in, first out: preserve arrival order. |
| `head` / `tail` | Oldest / newest queued node index; both `-1` when empty. |
| `enqueue_lnode` | Append an allocated detached node whose next is `-1`. |
| `dequeue_lnode` | Detach and return the oldest node index without recycling; -1 on an empty queue. |
| `is_empty_queue` | Report whether `head == -1`; check before public dequeue. |
| `enqueue(value)` | Allocate/append internally and return true; false on exhausted pool without changes. |
| `dequeue()` | Return the oldest value and recycle its node; requires a nonempty queue. |
| assertion | A diagnostic condition removed when NDEBUG is defined; do not hide necessary operations inside it. |

`free_lnode` is a pool operation, not C's `free`. Pointer ownership, DSU,
and Kruskal belong to the optional library and
Week 14.
