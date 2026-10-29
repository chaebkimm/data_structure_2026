# Module 07 Assessment Rubric

Total: 100 points. Both investigation formats assess [lab.c](lab.c). Typed, spoken, tabular, and diagram explanations receive equivalent credit. One artifact; three original test groups.

## A. Pool representation and lifecycle — 30 points

- 10: distinguish index, data, sentinel, first free chain, and retained data;
- 10: exact no-argument allocation/exhaustion, unchanged state, and one-time static initialization;
- 10: account for free, active, and isolated allocations across disjoint shared-pool lists; explain missing returns.

## B. Insertion and traversal — 25 points

- 10: preserve the old successor and give both insertion writes in order;
- 10: exact links/traversal, caller first indices, Stack prepend/LIFO, and Queue qhead/qtail;
- 5: valid/distinct allocated indices, isolation/ownership/non-queue predecessor preconditions, and reversed-write defect.

## C. Detachment and recycling — 25 points

- 10: exact detached index, next=-1, unchanged free chain, and caller ownership;
- 10: explicit data assignment, recycling/reuse, tail boundary, and node-index FIFO lifecycle with separate caller recycling;
- 5: diagnose active/double recycling and stale access; guard/save/advance/isolate before first-node recycling.

## D. Tests, costs, and revision — 20 points

- 12: three original groups with expected/observed exact state, repeated-init preservation, shared ownership, Stack LIFO/guards, Queue FIFO/endpoints, empty sentinel, exhausted allocation, payload -1, and explicit caller recycling;
- 4: fixed local work versus search/traversal, first versus repeated initialization, and link storage;
- 4: reproducible build evidence, preserved prediction, and justified correction.

A crash-free or sanitizer-clean run does not prove ownership. Invalid non-sentinel indices and invalid membership calls are paper diagnoses; only defined -1 no-ops and empty/tail results are executable boundaries. Keep mutations outside assert and return all owned slots between tests or use separate processes.

Stack/Queue are required applications within this artifact. The source supplies no Stack API or value Queue wrappers. Module 8 adds local adapters for BFS and compares array queues. Pointer-list/DSU/edge-builder/Kruskal implementations earn no required Week 7 points.
