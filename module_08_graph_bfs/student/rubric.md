# Module 8 Rubric — Queues, Tree BFS, and Graph BFS

Assess one combined submission using the [lab](lab.md) and [evidence template](evidence_template.md).

| Criterion | Points | Full-credit evidence |
| --- | ---: | --- |
| Queue representations | 25 | Retrieval of Module 7's value API, Boolean full-pool failure without mutation, automatic recycling, raw/public distinction, valid -1 payload, and unchecked array predicates; 25-write linear limit; 24-value circular limit and wraparound FIFO trace |
| Tree BFS bridge | 20 | Exact F, A, G, B, C, D, E order and pending queues; same Module 7 linked queue; public value dequeue with automatic recycling before left-before-right insertion; empty/single-node cases; valid-tree assumptions; comparison with graph discovery |
| Graph BFS discovery and routes | 25 | Coordinate/ID mapping; skip/equality/discovery branches; linked worklist payload/slot distinction; mark before enqueue; all shortest predecessors; goal distance 8 and three routes; one valid recovered route |
| Source use and reproducible checks | 20 | Direct combined build; array resets between comparisons; unowned pool/head/tail resets between BFS runs; restored ten free slots; maze metadata reset; original queue/tree/maze assertions; observed compiler/test output |
| Costs, assumptions, and correction | 10 | Counts 7 nodes/14 child checks and 20 passages/80 direction checks; separates initialization/storage/output cost; states border/capacity rules and peak four/six versus 20 total insertions; preserves a corrected prediction |
| **Total** | **100** | |

No overflow, invalid start, cycle, or shared-child test is executed outside the source contracts. Distance 25 is not an invalid ID. Linked `enqueue(value)` returns Boolean success; array mutations remain unchecked and public linked dequeue requires nonempty input. Empty root -1 returns 0. The optional checked matrix/list API is not required evidence.

Drawings, numbered text, oral explanation, dictation, and instructor-run checks receive equivalent credit. Speed, handwriting, and drawing quality are not criteria. Preserved errors with explained corrections earn correction credit. Extension work does not replace any of the three required parts.
