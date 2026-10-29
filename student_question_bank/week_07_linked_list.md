# Week 7 — Linked Lists, Shared Pool, and Linked Stack/Queue: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Follow all three slide Markdown sources and exact Module7 lab.c: acyclic chains and saved first indices, safe predecessor changes, shared-pool lifecycle, linked Stack, then linked Queue. new_lnode() returns an isolated allocation with retained data; callers write payload. Detachment isolates without recycling. Pool initialization happens once through a static guard. The Queue exchanges node indices; caller copies data and recycles. Module8 defines local value adapters for BFS. One artifact, three original groups, 180 minutes, 100 points. Pointer-library/DSU work is optional; DSU belongs to Week14.

## Vocabulary students will learn

| Term | Working meaning |
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

## Anticipated student questions

### Acyclic chains and saved first indices

- How does a linked sequence in `lnodes[10]` differ from an ArrayList's active prefix even though both use contiguous arrays?
- Why is a node's index different from the integer stored in its `data` field?
- Why must every valid list in this lesson end at `-1` without revisiting a node?
- Why must traversal stop at `-1` before indexing `lnodes[]`?
- Why does each separate list need a saved first index?

### Predecessor link changes

- Why must `simple_link_lnode_to_prev(prev,node)` copy the predecessor's old next before replacing it?
- Which links change when a node is inserted between two existing nodes?
- How can reversing insertion writes create a self-link and lose the old successor?
- What does `simple_delink_next_lnode_from_prev(prev)` return after a tail?
- Why does detachment clear the removed next to -1 without recycling the node?
- Why must the caller manage first-node changes instead of passing -1 as a predecessor?
- Why is known-predecessor mutation constant work while finding the predecessor can take O(n)?

### Shared pool, costs, and recycling

- Why can disjoint lists draw any available slot without fixed per-list partitions?
- How do next fields and saved endpoints increase storage compared with values alone?
- How many links reach zero-based position i from first?
- What free chain does the first init_lnodes_pool call create?
- Why is first initialization O(C) while later calls are O(1)?
- How does the function-local static guard make repeated initialization a no-op, even when exhausted?
- How do free_head, next, and retained data change when new_lnode() succeeds?
- What remains unchanged on an eleventh allocation from an exhausted pool?
- Why does free_lnode change links without releasing C array storage?
- Why must a recyclable node be allocated, unreferenced, and isolated?
- How does a missing return reduce available shared capacity?
- Why can double recycling corrupt the free chain even for an in-range index?
- If B reallocates A's returned slot and writes 8, why can A's stale access observe or damage B?
- Why must all active and isolated allocations across lists fit within ten slots?

### Linked Stack from first-node operations

- How does prepending 17,23,31 give LIFO output 31,23,17 without a tail?
- Why must the caller check new_lnode() before assigning data/next and replacing first?
- Why must removal check first!=-1 before array access?
- Which old data/next must be saved before advancing first, isolating the old node, and recycling?
- Why must the old owner stop reading or writing a recycled node?
- How do these caller actions implement Stack despite no supplied push/pop API?

### Linked Queue from opposite-end operations

- How does FIFO output differ from Stack LIFO for 17,23,31?
- How does the first enqueue_lnode(index) set both qhead and qtail?
- Why must allocation/check/data assignment occur before the void enqueue_lnode call?
- Which tail link changes on append, and why must the appended node already be isolated?
- How does removing the sole queued node clear both endpoints while leaving it allocated?
- How does dequeue_lnode's returned index differ from payload -1 and from its empty index -1?
- Why must the caller copy data and explicitly recycle once after successful dequeue?
- Which empty dequeue and sentinel enqueue/free calls are defined no-ops, and which other invalid indices are outside contract?
- Why must mutations run outside assert when NDEBUG may remove assertions?
- Which shared-pool, Stack LIFO, and Queue FIFO/endpoint evidence belongs inside three test groups and one artifact?

## Sources

- [Question outline](../module_07_linked_list/student/ppt.md)
- [Concept slides](../module_07_linked_list/student/ppt_material.md)
- [Lab slides](../module_07_linked_list/student/ppt_lab_material.md)
- [Current source](../module_07_linked_list/student/lab.c)
- [Textbook](../module_07_linked_list/student/textbook.md)
- [Workbook](../module_07_linked_list/student/class_material.md)
- [Module](../module_07_linked_list/README.md)
- [14-week guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
