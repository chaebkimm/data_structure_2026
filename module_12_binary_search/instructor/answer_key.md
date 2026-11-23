# Module 13 Answer Key

Keep this faculty copy separate from the student archive. Read with the [workbook](../student/class_material.md) and [lab](../student/lab.md).

## Common searches

Original `[31,23,17,8,17,42]`: first 17 is index 2 after three value comparisons; 99 is absent after six. Sorting produces `[8,17,17,23,31,42]`; first 17 is index 1. Sorted indices do not preserve original positions.

Binary first-match trace for 17: `(lo,hi,mid,value)` is `(0,6,3,23)`, `(0,3,1,17)`, `(0,1,0,8)`, then `lo=hi=1`. The first two comparisons set hi, the third sets lo. The final in-range equality confirms 17. This is three interval decisions and one equality, not fewer key comparisons than the original linear query. For absent 99: `(0,6,3,23)`, `(4,6,5,42)`, then boundary 6. The bounds test prevents a read at index 6. Searches do not mutate input.

The invariant is that all positions before lo are below key, all positions at/after hi are at least key, and the first position at least key remains at the candidate boundary. On equality hi=mid continues toward the first duplicate. A range may be empty; its right endpoint is not a readable value.

## Insertion and stability

| Pass | Result | Right shifts | Value comparisons |
| ---: | --- | ---: | ---: |
| 1 | 23,31,17,8,17,42 | 1 | 1 |
| 2 | 17,23,31,8,17,42 | 2 | 2 |
| 3 | 8,17,23,31,17,42 | 3 | 3 |
| 4 | 8,17,17,23,31,42 | 2 | 3 |
| 5 | 8,17,17,23,31,42 | 0 | 1 |
| **Total** | | **8** | **10** |

Value comparisons count the strict greater-than checks that execute, including a failed one; a short-circuited bounds condition does not compare keys. Five final saved-key writes are separate from eight shifts. Strict `>` does not move 17A past the later 17B. Using `>=` would break that identity order even though integer output looks identical.

## Merge and scratch

The initial halves are `[31,23,17A]` and `[8,17B,42]`. Sorted halves are `[17A,23,31]` and `[8,17B,42]`. Final choices are right 8, left 17A on equality, right 17B, left 23, left 31, remaining right 42. Scratch receives that order before copy-back. The same caller-owned n-int buffer is reused at every level. Both sources must remain readable while output is produced, so scratch must not overlap values. Left-on-equality plus induction over the smaller stable ranges proves stability; a plain integer oracle cannot observe record identity.

## Workload selections

- One short unsorted lookup: scan avoids preparation. An early match can be cheaper than binary search after sorting.
- Many unchanged-snapshot lookups: merge-sort-plus-binary can share preparation; compare it with a hash index's distribution, space, and exact-key scope. No universal winner follows without frequencies and constraints.
- Frequent ordered updates: AVL balance maintains short paths; array updates may shift many records. A hash index alone does not provide ordered range iteration.
- Known predecessor: local linked insertion/detachment is fixed work; finding that predecessor or indexing by rank can still be linear.
- Repeated minimum: a heap exposes its root cheaply and repairs in logarithmic removal work. It neither fully orders all positions nor provides constant arbitrary-key lookup.
- Graph questions: FIFO BFS fits unit-hop layers; Stack DFS follows deep work; Dijkstra selects minimum distance under its weight contract. A lookup table does not replace graph traversal.

Accept any alternative justified by explicit workload assumptions. Generalized bounds are not claims that earlier fixed-capacity teaching functions accept arbitrary sizes or malformed input.

## Submission check

Require original search/sort/boundary groups, valid caller states, exact predicted/observed outcomes, complete source/build evidence, tagged stability reasoning, selection explanations, concrete counts, and a corrected prediction. No DSU knowledge or extra structure implementation is required. Module 14 supplies its edge sorter and teaches connectivity selection separately.
