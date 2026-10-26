# Week 14 instructor plan — 180 minutes

DSU is new this week. Introduce it through the cycle decision in Kruskal,
then use the [combined lesson and lab](README.md). Do not assume an earlier
DSU assignment or add the optional Module 7 list-repair extension.

Retrieve Module 13's distinction between searching for an item and sorting
candidates. Kruskal sorts edges by weight before selecting them, but sorted
order alone cannot detect a cycle. The supplied comparator and sorting step
let this lesson focus on DSU and edge decisions.

| Activity | Minutes |
|---|---:|
| Components, MST objective, and cycle inquiry | 20 |
| Parent/size arrays and find/compression/union trace | 30 |
| Implement and test the two DSU TODOs | 40 |
| Sorted-edge trace and Kruskal implementation/tests | 50 |
| Instructor-supplied Prim demonstration | 10 |
| Individual synthesis and capstone integration checkpoint | 20 |
| Correction and submission | 10 |
| **Total** | **180** |

Preserve the staged inquiry: ask whether A–C should be purchased before
revealing DSU; record three predictions (same-component union, compression,
and disconnected result); correct using arrays and an edge ledger; then
release the implementation scaffold. Structured text is equivalent to diagrams.

Supply make-set, bounded helpers, loading/building, safe sorting, totals,
validation, and complete Prim. The student TODOs are find, union, and the
Kruskal selection loop. At code release, run `python prepare_release.py`;
the archive excludes DSU/Kruskal solutions and the original DSU backend.
The repository's `make -C code solution-core` checks the combined reference
against the DSU trace tests and the full MST suite. Existing faculty solution
paths remain available only in the repository Makefile.

Canonical DSU: unions A–B, C–D, A–C, E–F, G–H, E–G, A–E yield
`parent = [A,A,A,C,A,E,E,G]`, root size 8, and one component. Find H
compresses H and G to A. D–H performs no merge. The opening four-edge MST
selects A–B, B–C, C–D for total 7. The full package fixture has total 10.

Use the Prim demonstration to compare objectives and total cost; there are
no Prim implementation checkpoints or separate comparison submission.
Fold the brief synthesis and integration record into the single artifact.
Keep longer algorithm-selection essays, full Prim implementation, and list
repair optional. The defense is outside this block in the final-assessment
period. Require incremental capstone assembly during earlier labs so this
checkpoint remains a bounded integration exercise.
