# Module 14 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` clusters across
  `code/starter/linked_list.c` and `code/starter/dsu.c`; and
- the three `TODO` test categories in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete.

Students complete:

1. bounded linked-list front insertion, first-match deletion, and destruction;
2. make-set initialization plus iterative two-pass find; and
3. union by component size, including the smaller-root tie rule and the
   already-together result.

The list has a configurable limit no larger than 16. Adding at the front is
failure-atomic: a full limit or failed allocation leaves the complete list
unchanged. Deletion and destruction preserve the following link before
freeing a node. The canonical list uses limit 4 with three initial live
nodes, leaving one spare slot for the forced-allocation-failure test.
Destruction resets the head, size, and limit to the exact all-zero state.

The DSU uses dense IDs, `parent[]`, and `component_size[]`. Every ID is
checked before indexing. Roots store positive sizes; nonroots store zero.
Path compression changes parents only.

For A through H, the required relationship order is:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

The required arrays before an explicit find are:

```text
parent          [A, A, A, C, A, E, E, G]
component_size  [8, 0, 0, 0, 0, 0, 0, 0]
```

Finding H changes the parent array to `[A, A, A, C, A, E, A, A]`. Processing
D-H next performs no merge, identifies a cycle-producing relationship, and
compresses D.

The supplied edge builder validates exactly two incident records per logical
edge ID. Reciprocal records describe a non-self edge; two identical records
describe a self-loop. Parallel IDs remain distinct. Its `qsort` comparator
uses relational comparisons on signed 64-bit weights, endpoints, and ID; it
never subtracts weights. Students test this support but do not implement
Kruskal or an MST.

The autopsy—a careful investigation after a failure—contains an actual
bounded use-after-free branch. It is compiled separately and never linked
into normal tests. The ordinary autopsy target defines
`AUTOPSY_INSPECT_ONLY` and runs a safe inspection. The unsafe target requires
sanitizers, compiles the actual defect, prints its path, and deliberately does
not run it. Never execute that binary outside an instructor-controlled
disposable environment.

Submit the files and evidence listed in the lab, then complete
`student/evidence_template.md`.
