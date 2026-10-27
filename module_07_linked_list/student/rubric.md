# Module 07 Assessment Rubric

Total: 100 points. This rubric and both investigation formats assess [lab.c](lab.c). Typed, spoken, tabular, and diagram explanations receive equivalent credit.

## A. Pool representation and lifecycle — 30 points

- 10: distinguishes index, data, sentinel, and complete ten-slot free chain;
- 10: exact two-argument allocation, exhaustion, and unchanged-state evidence;
- 10: accounts for active, detached, and free slots without overlap or cycles across multiple lists sharing the pool; explains missing returns.

## B. Insertion and traversal — 25 points

- 10: preserves the old successor and gives both insertion writes in order;
- 10: exact resulting links, traversal values, caller-owned first indices, linked Stack first insertion and LIFO trace, and linked Queue head/tail trace;
- 5: explains valid indices, membership conditions, and a reversed-write defect.

## C. Detachment and recycling — 25 points

- 10: exact detached index, unchanged free chain, and stale next field;
- 10: correct recycling/reuse, valid tail-deletion boundary, and raw-index versus public-value FIFO lifecycle with automatic public recycling;
- 5: diagnoses active-node or duplicate recycling and stale access after another list reuses a slot; explains guarded first removal with data/next saved before recycling.

## D. Tests, costs, and revision — 20 points

- 12: three original groups with expected/observed state: allocation/exhaustion, insertion/traversal, detachment/recycling/reuse including shared-pool ownership, linked Stack LIFO and empty/full guards, linked Queue endpoints, FIFO values, full status, and automatic recycling;
- 4: fixed local mutation work versus traversal, i-th-node access and initialization, plus extra link storage;
- 4: reproducible build evidence, preserved prediction, and justified correction.

A crash-free run or clean sanitizer report does not prove chain membership. Keep invalid unchecked calls as paper diagnoses. Test out-of-range input only where `free_lnode` defines that behavior.

Linked Stack and Queue are required examples of the same list operations. The Stack uses caller-side first-node changes; no Stack API is added to the supplied source. Module 8 reuses the linked Queue for BFS; array queue comparisons and BFS algorithms belong there. Pointer-list, DSU, edge builder, and Kruskal implementations earn no required Week 7 points.
