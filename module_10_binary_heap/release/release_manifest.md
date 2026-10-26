# Module 10 Current Student Release

The current required package follows [student/lab.c](../student/lab.c).
It replaces the older opening-baseline and five-archive distribution.
The Stage A–E readmes remain optional teaching checkpoints within one
180-minute lesson. They are not separate implementation assignments.

Create the standalone archive with Python 3 from the module directory:

```sh
python3 release/prepare_student_release.py
```

The default output is `dist/module_10_binary_heap.zip`. For a repeat
verification, use `--output /path/to/new/module_10_binary_heap.zip`.
The PowerShell wrapper accepts `-OutputPath` for the same option.
Existing output files are never overwritten.

The archive contains:

- the student release README and a generated `MANIFEST.txt`;
- every current `student/*.md` file and the exact `student/lab.c` bytes;
- `diagrams/binary_heap_models.md`;
- student-only `code/README.md`, `Makefile`, and `build.ps1`;
- `code/tests/test_lab.c` and `code/tests/test_lab_student.c`.

The package preserves the `student/`, `diagrams/`, and `code/` relative
layout. The tests include the supplied lab directly. No original
repository checkout is needed. The ZIP uses deterministic entry metadata
and verifies its inventory and bytes before writing the destination.

The archive excludes `instructor/`, the optional alert-record headers and
implementations, `priority_queue_baseline/`, old library tests and autopsy
code, release tooling, binaries, build directories, and private tests.
The lab is already complete; it is intentionally included in full.

Before delivery, build `lab-compile`, `core`, and `student-tests`, run the
core and student tests under sanitizers where supported, compare every
archive entry to its source, check relative document links, extract into
a new directory and run the same targets, and verify that a second
packaging attempt refuses to overwrite the archive without changing it.
The retained optional library targets can be checked separately; they do
not define the current Week 10 assessment.
