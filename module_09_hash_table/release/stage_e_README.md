# Module 09 — Stage E: Lab and Evidence

Read `module_09_hash_table/student/lab.md`. Trace the supplied implementation
and extend `module_09_hash_table/code/tests/test_lab_student.c` with three
original test groups. Submit one driver and its evidence.

The `module_09_hash_table/` directory contains the self-contained lab,
instructions, test drivers, and build files. From the extracted root:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

Compile a driver once; do not separately compile the `lab.c` it includes.
Call `initialize()` before direct `insert`/`find` experiments. It resets all
fifteen heads and the allocation counter; it leaves old node fields and
`answer` unchanged. Each `two_sum_ht` call initializes automatically.
The old open-addressed map and deletion demo are not in this release.
