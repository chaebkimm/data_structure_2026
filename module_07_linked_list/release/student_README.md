# Module 7 — Linked Lists

Read the [English textbook](student/textbook.md) or
[Korean textbook](student/textbook_korean.md). Use the
[class workbook](student/class_material.md),
[concept slides](student/ppt_material.md), and
[lab slides](student/ppt_lab_material.md) with the supplied source.

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

The linked queue example is included in the same `student/lab.c`. Its caller checks bool enqueue status and queue emptiness. Public dequeue returns a value and recycles internally; raw node helpers expose indices and separate recycling. Initialize the unused pool and reset `head = tail = -1` for an independent run. Module 8 reuses these functions.
