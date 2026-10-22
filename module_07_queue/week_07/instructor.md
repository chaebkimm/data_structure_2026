# Week 7 instructor plan — 180 minutes

Use [the current weekly package](README.md), not the original circular-Queue
implementation assignment. Borrow linked-node diagrams from Module 14 only
as needed; DSU is introduced in Week 13.

| Activity | Minutes |
|---|---:|
| Arrival-order inquiry and FIFO/Stack contrast | 20 |
| Nodes, pointers, traversal, allocation, ownership, destruction | 40 |
| Implement the two linked-Queue TODOs | 55 |
| Supplied circular-array trace and comparison | 35 |
| Tests, debugging correction, and BFS transfer | 30 |
| **Total** | **180** |

Preserve the existing inquiry-first practice: ask the starting question before
releasing names or code; preserve three predictions (append to empty, remove
last, allocation failure); calibrate with link diagrams; then release the
lesson, scaffold, and tests. Permit structured text instead of drawings.
Do not distribute `code/solution` or this plan in student archives.

Key answers: the last dequeue clears both pointers; allocation happens before
link mutation; no failed enqueue changes old links; destruction saves next
before free. Linked `tail` points to the last node, while circular-array tail
is a calculated insertion index. A traversal validator costs O(n) and must
not be hidden in an O(1) enqueue/dequeue cost claim. Allocator runtime is
separate from constant pointer work.

Reference check: `make -C code solution-core`. Starter compile should pass;
its behavioral tests should fail until students implement the TODOs.
No second circular implementation, general list library, or mandatory
extension packet is assigned. Collect the single artifact described in the lab.
