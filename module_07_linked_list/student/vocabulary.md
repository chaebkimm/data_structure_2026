# Module 07 Vocabulary Reference

Keep closed until the Cognitive Pause is preserved. These names follow [lab.c](lab.c). The [lab slides](ppt_lab_material.md) use shorter teaching aliases; executable callers use the source names.

| Term | Meaning in this lab |
| --- | --- |
| node | One `struct Linked_Node` record with integer data and next. |
| node index | Slot 0–9, distinct from payload. |
| sentinel | -1 means no node; never subscript it. |
| singly linked list | Acyclic chain following one next link per node to -1. |
| first index | Caller-saved beginning of a standalone list. |
| traversal | Follow next links until -1. |
| predecessor / successor | Immediately preceding / following node. |
| pool | Ten reusable records in `lnodes[CAPACITY]`. |
| free chain | Available slots linked through next. |
| free_head | First available index, or -1 when exhausted. |
| init_lnodes_pool | Initialize links once; later calls preserve every field. |
| static initialization guard | Function-local flag that persists between calls. |
| new_lnode | Take one free slot, set next=-1, retain data, return index. |
| pool exhaustion | Allocation returns -1 unchanged; init cannot reset it. |
| detached node | Allocated unreferenced isolated slot held by a caller. |
| isolation | An owned detached node has next=-1. |
| free_lnode | Return an isolated allocation; -1 is a no-op; other preconditions unchecked. |
| shared pool | Disjoint lists draw from one free chain. |
| missing return | An owned detached slot remains unavailable. |
| stale index | Former owner accesses a slot after recycling. |
| double recycling | Return an already-free slot, corrupting the free chain. |
| invariant | Rule true in every valid completed representation. |
| precondition | Condition the caller establishes before calling. |
| physical slot | Array location; retained bits do not establish ownership. |
| O(1) | Fixed work independent of chain length. |
| O(n) | Work proportional to visited nodes. |
| simple_link_lnode_to_prev | Insert an isolated allocation after a valid distinct non-queue predecessor. |
| simple_delink_next_lnode_from_prev | Bypass and isolate successor; return index without recycling, or -1. |
| linked Stack | Caller prepends/removes at first; no supplied push/pop API. |
| LIFO | Last in, first out: 17,23,31 leave 31,23,17. |
| linked Queue | Append at tail, remove from head. |
| FIFO | First in, first out: preserve arrival order. |
| qhead / qtail | Oldest/newest node index; both -1 when empty. |
| enqueue_lnode | Append isolated allocated index; -1 is a no-op; returns void. |
| dequeue_lnode | Return isolated oldest index without recycling, or -1 when empty. |
| is_empty_queue | Report qhead==-1; payload -1 is still valid data. |

`free_lnode` is a pool operation, not C `free`. Pointer ownership/DSU/Kruskal are optional references and Week 14 work.
