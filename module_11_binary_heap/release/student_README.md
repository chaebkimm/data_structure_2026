# Module 10 — Integer Heaps and a Common On Time

Use the supplied [lab.c](student/lab.c) with the
[textbook](student/textbook.md), [lab instructions](student/lab.md), and
[heap diagrams](diagrams/binary_heap_models.md). The first part is a
ten-integer min/max heap. The second part finds the earliest common time
across ten sequences of closed intervals using two heaps and position maps.

From this extracted root, run:

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

PowerShell users can run `./code/build.ps1` and
`./code/build.ps1 -StudentTests`. Add `-Sanitize` where supported.
The [code guide](code/README.md) explains compiler options and test coverage.

Add three original safe test groups in `code/tests/test_lab_student.c`.
Submit the tests and output, state traces, [evidence record](student/evidence_template.md),
and corrected [Cognitive Pause](student/cognitive_pause.md).
Use the [rubric](student/rubric.md) to check the result.

The source has no `main`; test drivers include it once. The older alert
Priority Queue library and scan baseline are optional faculty references
and are not included in this archive.
