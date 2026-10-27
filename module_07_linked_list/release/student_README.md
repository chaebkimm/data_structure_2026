# Module 7 — Linked Lists

Read the [English textbook](student/textbook.md) or
[Korean textbook](student/textbook_korean.md). Use the
[class workbook](student/class_material.md) and
[concept slides](student/ppt_material.md) with the supplied source.

Complete the [lab](student/lab.md) and check the [rubric](student/rubric.md).
The supplied [student/lab.c](student/lab.c) is complete. Trace it and add
three original safe test groups in `code/tests/test_lab_student.c`.

From the extracted root, run:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

PowerShell users can run `./code/build.ps1` and
`./code/build.ps1 -StudentTests`. Add `-Sanitize` where supported.

The tests include `student/lab.c` directly. No repository checkout or faculty
source is needed. The pointer-list and DSU reference library is optional
and is not included in this release.

Follow the slides through acyclic chains, safe insertion/deletion, shared-pool
reuse, a linked stack, and a linked queue. Keep live lists disjoint in the pool.
After recycling a slot, its former owner must stop accessing it. The linked
stack uses a caller-owned `first` and the existing node primitives; there is
no supplied stack API. Insert at the first position, guard empty removal,
save the value and successor, then recycle. Compare output 31,23,17 from a
stack with 17,23,31 from a queue after the same input sequence. Include both
within the three original test groups and the single lab artifact.

The linked queue example is included in the same `student/lab.c`. Its caller checks bool enqueue status and queue emptiness. Public dequeue returns a value and recycles internally; raw node helpers expose indices and separate recycling. Initialize the unused pool and reset `head = tail = -1` for an independent run. Module 8 reuses these functions.
