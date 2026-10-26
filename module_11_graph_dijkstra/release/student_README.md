# Module 11 — Indexed-Heap Dijkstra

Start with [the lab](student/lab.md) and the supplied
[`student/lab.c`](student/lab.c). The source is complete. Trace it and extend
`code/tests/test_lab_student.c`; there are no required implementation TODOs.

The program uses at most ten nodes, strictly positive `int` weights,
`-1` for undiscovered distances, and a minimum heap of node IDs with an
inverse position map. It updates queued distances in place. There are no
lazy duplicates, stable tie promises, predecessor outputs, input validators,
or overflow guards in this lab. Use valid indices and representable sums.

The included `module_03_graph/student/lab.c` supplies adjacency lists.
Keep that dependency in its packaged location. Compile a driver that includes
the lab; do not compile both included C files separately.

From the extracted directory:

```sh
make -C code lab-compile core student-tests comparison
```

Or run `code/build.ps1` with PowerShell. See
[code/README.md](code/README.md) for compiler selection and sanitizers.

The shared directed A-through-F fixture has edges
`A->B9,A->C2,A->E14,B->D1,B->E8,C->B3,C->D2,D->E2`.
Distances from A are `[0,5,2,4,6,-1]`. One run inserts and removes five
nodes, updates B and E, inspects eight adjacency entries, and peaks at
three pending nodes. These are manually traced counts, not exported metrics.

Use the [textbook](student/textbook.md), [models](diagrams/dijkstra_models.md),
[worksheet](student/investigation_worksheet.md), and
[evidence template](student/evidence_template.md) to build one Practical 2
submission. The linear inquiry and worksheet carry equivalent targets.
The [Stage A](release/stage_a_README.md) through
[Stage E](release/stage_e_README.md) notes are opening-order checkpoints,
not additional assignments. This archive contains the full current set;
the instructor manages when each resource is opened.
