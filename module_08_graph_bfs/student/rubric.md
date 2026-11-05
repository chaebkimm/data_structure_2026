# Module 8 Rubric — Processing data in stored order

Assess one combined submission using the [lab](lab.md) and [evidence template](evidence_template.md).

| Criterion | Points | Full-credit evidence |
| --- | ---: | --- |
| Queue representations | 25 | FIFO recall; whole-point array entries; correct front/rear, `0 <= front <= rear + 1 <= N*N`, and increment timing; nonempty/read and available-write preconditions; 25 total linear writes per reset; a consistent 24-value circular comparison and wraparound trace |
| Tree BFS bridge | 20 | Illustrative A/B/C/D/E/F order and pending queues; depths 0/1/1/2/2/2; left-before-right insertion; child distance recorded before enqueue; valid-tree assumptions; compare stack order, graph-stack duplicate pending entries with processed-pop skips, and BFS discovery |
| Graph discovery and shortest distances | 25 | y/x coordinates, four-direction iterator, correct 5×5 trace; distance-before-enqueue, one entry per passage, and nondecreasing pending distances; skip walls and all discovered passages; target distance 4; one four-move paper route and clear separation of conceptual predecessor storage from the actual source |
| Source use and reproducible checks | 20 | Current lab driver and actual output; automatic per-call reset; explain the three new syntax topics: row-by-row brace initialization, whole-structure copying/passing/returning, and short-circuit OR; reverse start, in-bounds wall start, isolation/restoration, and one original valid check in a separate driver; source and PPTs preserved |
| Costs, assumptions, and correction | 10 | 25 initializations, eight enqueues/dequeues, 32 neighbor checks; three peak pending versus eight total writes; final front 8/rear 7; O(RC) reset/storage and O(P) traversal; in-bounds start and zero border; explained correction |
| **Total** | **100** | |

Do not execute overflow, empty dequeue, out-of-range coordinates, or a modified open border. A wall start within the array is supported and leaves every distance `INF`. No tree implementation, circular-queue implementation, predecessor-array implementation, or optional checked-library exercise is required.

Drawings, numbered text, oral explanation, dictation, and instructor-run checks receive equivalent credit. Speed, handwriting, and drawing quality are not criteria. Preserved errors with explained corrections earn correction credit. Extension work does not replace the three required parts.
