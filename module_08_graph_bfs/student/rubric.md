# Module 8 Rubric — Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Assess one combined submission using the [lab](lab.md) and [evidence template](evidence_template.md).

| Criterion | Points | Full-credit evidence |
| --- | ---: | --- |
| Queue representations | 25 | Module 8 local value adapters over Module 7 node operations, Boolean full-pool failure without mutation, automatic recycling, raw/public distinction, valid -1 payload, and unchecked array predicates; 25-write linear limit; 24-value circular limit and wraparound FIFO trace |
| Tree BFS bridge | 20 | Exact F, A, G, B, C, D, E order and pending queues; same Module 7 linked queue; public value dequeue with automatic recycling before left-before-right insertion; empty/single-node cases; valid-tree assumptions; comparison with graph discovery |
| Graph BFS discovery and routes | 25 | Coordinate/ID mapping; skip/equality/discovery branches; linked worklist payload/slot distinction; mark before enqueue; all shortest predecessors; goal distance 8 and three routes; one valid recovered route |
| Source use and reproducible checks | 20 | Direct combined build; array resets between comparisons; all-free pool and qhead/qtail checks between BFS runs; restored ten free slots; maze metadata reset; original queue/tree/maze assertions; observed compiler/test output |
| Costs, assumptions, and correction | 10 | Counts 7 nodes/14 child checks and 20 passages/80 direction checks; separates initialization/storage/output cost; states border/capacity rules and peak four/six versus 20 total insertions; preserves a corrected prediction |
| **Total** | **100** | |

No overflow, invalid start, cycle, or shared-child test is executed outside the source contracts. Distance 25 is not an invalid ID. Linked `enqueue(value)` returns Boolean success; array mutations remain unchecked and public linked dequeue requires nonempty input. Empty root -1 returns 0. The optional checked matrix/list API is not required evidence.

Drawings, numbered text, oral explanation, dictation, and instructor-run checks receive equivalent credit. Speed, handwriting, and drawing quality are not criteria. Preserved errors with explained corrections earn correction credit. Extension work does not replace any of the three required parts.
