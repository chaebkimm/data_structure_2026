# Module 11 — Stage E: Test and Assemble Practical 2

Follow [the lab](../student/lab.md), run the supplied current-source tests,
and extend `code/tests/test_lab_student.c`. Keep `student/lab.c` unchanged;
it is complete and has no required TODOs. The standalone archive includes
its Module 3 adjacency-list dependency.

Use positive `int` costs and representable additions. Check indexed-heap
repairs, live position maps, disconnected nodes, and repeated runs. Compare
the same graph using BFS, linear minimum selection, and the indexed heap.
The shared fixture's distances are `[0,5,2,4,6,-1]`; its peak pending heap
contains three nodes. There are no lazy duplicate entries or predecessor
outputs in this source.

Submit one [evidence record](../student/evidence_template.md), original test
driver, saved output, state trace, and corrected explanation. The optional
lazy-duplicate API and its parser/path/overflow exercises are outside this
required release.
