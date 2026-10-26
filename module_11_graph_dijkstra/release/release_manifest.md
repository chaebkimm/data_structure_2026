# Module 11 Current Student Release

The required package follows the exact updated [student/lab.c](../student/lab.c).
It replaces the older five-archive lazy-duplicate distribution. Stage A–E
remain teaching checkpoints within one 180-minute Practical 2 block, not
separate implementation assignments. The full archive does not enforce
withholding; the instructor controls opening order.

From the module directory, create the standalone ZIP with Python 3:

```sh
python3 release/prepare_student_release.py
```

The default output is `dist/module_11_graph_dijkstra.zip`. For a repeated
verification, choose a new path with `--output /path/to/new/release.zip`.
The PowerShell wrapper accepts `-OutputPath` for the same option. Existing
archives are never overwritten.

## Included materials

- The student README, generated SHA-256 inventory `MANIFEST.txt`, and every
  current `student/*.md` file.
- The exact `student/lab.c` and its exact
  `module_03_graph/student/lab.c` dependency at the archive root.
- `diagrams/dijkstra_models.md` and Stage A–E opening-order notes.
- Student-only `code/README.md`, `Makefile`, and `build.ps1`.
- `code/tests/test_lab.c`, `code/tests/test_lab_student.c`, and the supplied
  same-graph BFS/linear-selection/heap driver `code/tests/compare_lab.c`.

The dependency path lets `lab.c` retain its original include unchanged.
The released Makefile supplies the student-folder and archive-root include
paths. No original repository checkout is required.

The archive excludes instructor keys, the optional lazy-duplicate headers,
starter/solution/support API, old library tests and overflow autopsy,
release tooling, binaries, and build directories. The required lab is
already complete and is deliberately included in full.

## Teaching checkpoints

1. Stage A: preserve an initial route-cost model using either inquiry format.
2. Stage B: reveal names and preserve the three-target Cognitive Pause.
3. Stage C: trace distances, node IDs, heap positions, and live inverse maps.
4. Stage D: compare the textbook/models with preserved predictions.
5. Stage E: run current-lab tests and assemble one Practical 2 artifact.

The shared directed fixture uses only positive costs. Its distances from A
are `[0,5,2,4,6,-1]`; removals are `A,C,D,B,E`. Observed calls are five
insertions, five removals, two updates, eight adjacency inspections, and a
peak live heap size of three. The raw source exports none of these counters.
It has no predecessor-path output or stale duplicate pops.

## Verification before delivery

Build `lab-compile`, `core`, `student-tests`, and `comparison`, then run core and student
tests under sanitizers where supported. Verify heap order and maps only in
the live prefix, singleton removal, equal priorities without a stability
assumption, repeated runs, nonzero sources, and independent distance checks.

The Python packager reads source bytes before writing, rejects unsafe entry
names, uses deterministic metadata, and checks the ZIP inventory and every
entry's bytes in memory. Verify the extracted package independently with
the same targets, check local links, and confirm that a repeated destination
is refused without changing the original archive. Optional reference API
checks do not define the current practical's assessment.
