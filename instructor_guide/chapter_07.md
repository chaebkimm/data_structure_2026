# Chapter 7. Change Order by Changing Links

Use the [Module 7 instructor plan](../module_07_linked_list/instructor/lesson_plan.md) for the 180-minute lesson, the updated [concept slides](../module_07_linked_list/student/ppt_material.md) for the conceptual sequence, and [student/lab.c](../module_07_linked_list/student/lab.c) for exact behavior. Module 7 teaches linked lists, shared-pool lifecycle, and linked Stack/Queue applications.

## Starting Question

> If records stay in their numbered slots, how can we change their order?

Compare shifting an ArrayList's active suffix with remembering the following record's index. Introduce a node and a singly linked list after students describe that link. Save a first index for each list; require every valid chain to reach `-1` without a cycle. Proceed through safe predecessor rewiring, shared-pool benefits and costs, lifecycle errors, linked Stack, then linked Queue as in the slides.

## Board Walkthrough

Initialize `lnodes[10]` with `init_lnodes_pool()`. Draw free chain 0→1→2→3→4→5→6→7→8→9→-1. Allocate 17,23,31 with `new_lnode(value,-1)`; expect indices 0,1,2 and free head 3. The second argument is stored directly as next.

From 0→2→-1 and detached 1, `link_lnode(0,1)` first saves successor 2 in 1.next, then writes 0.next=1. Trace the two writes separately. Reversing them creates a self-link.

`delete_next_lnode(0)` returns 1 and leaves 0→2→-1. The removed next remains 2 and free head remains 3. `free_lnode(1)` puts 1 before 3. `new_lnode(8,-1)` reuses 1 with new data and requested next.

For an independent shared-pool example, let A own `0(17)` and B own `1(23)`, both ending at `-1`, with `free_head=2`. After A safely detaches and returns 0, B can allocate 8 at 0 and prepend it to 1. A's stale index 0 now identifies B's node. Reading it yields replacement data; writing it can corrupt B. Missing returns consume capacity; duplicate returns can cycle the free chain. Use paper traces for invalid actions.

## Neutral Questions

- Which number is an index, and which is stored data?
- What exactly remains unchanged after an exhausted allocation?
- Which write preserves the predecessor's old successor?
- Is the detached slot already in the free chain?
- Why does a numeric range check fail to prove membership?
- Who changes the first-node index when removing the first node?
- Why can two lists use the same free chain without sharing an active node?
- Which list owns an old index after that slot has been returned and allocated again?
- Why do first-position additions and removals give LIFO order?

## Vocabulary and Costs

Use node, integer next link, singly linked list, traversal, shared node pool, free chain, allocation, detachment, recycling, stale index, linked Stack/LIFO, linked Queue/FIFO, and caller precondition through the actions above. Follow exact `lnodes`/`*_lnode` names. Initialization visits every slot; known-predecessor mutations and first-position Stack operations change fixed fields; predecessor search may inspect all live nodes. Reaching zero-based position i follows i links. Next fields and saved endpoints add storage.

## Final Check

Require exact pool/list states, allocation exhaustion and tail-deletion boundaries, shared-pool ownership, linked Stack LIFO and linked Queue FIFO/endpoint evidence, three original safe test groups, reproducible output, and one corrected prediction. Use the [rubric](../module_07_linked_list/student/rubric.md): A30/B25/C25/D20. All work remains in one artifact.

Module 8 reuses this linked queue for tree BFS and graph BFS and compares array queue representations. Pointer lists and DSU stay optional references; DSU assessment belongs to Week 14.

## Linked Stack Example

In a fresh independent pool with `first=-1`, use `new_lnode(value,first)` to prepend 17,23,31. Replace `first` only after successful allocation. The chain is `2(31)→1(23)→0(17)→-1`. Check `first != -1` before each removal. Save the old first's index, data, and next; advance first; recycle the detached slot. Values leave 31,23,17, and the final first is `-1`. This caller-side composition uses no supplied linked push/pop API and no tail search. Empty removal is skipped. Never recover data or next through a recycled slot.

## Linked Queue Example

Requests 17, 23, and 31 must leave in arrival order. Ask students which end receives new records and which end supplies the next record. Remember both ends, then name FIFO and linked queue. In a fresh independent pool reset `head = tail = -1`. Public `enqueue(value)` allocates with next -1 and reports success. Check its boolean result after the call. Trace head/tail after all additions and the singleton removal.

Compare a raw helper removal, which returns an index and leaves recycling to its caller, with public `dequeue()`, which returns data and recycles internally. Check `is_empty_queue()` before public removal, check bool enqueue status, and execute enqueue outside assert. Reusing index 0 behind waiting nodes must preserve arrival order. Module 8 imports these exact functions with vertex IDs as payloads. Keep this example inside the existing lab and lifecycle test group.
