# Module 09 lab driver

Read `../student/lab.md`. The supplied implementation is
`../student/lab.c`. Its include of `module_07_linked_list/student/lab.c`
resolves through the extracted release root. Keep the sibling Module 07
and Module 09 directories together.

From the release root:

```sh
make -C module_09_hash_table/code lab-compile core student-tests
```

From this code directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
```

Add `-Sanitize` if the compiler supports sanitizers. For Make, pass
`CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer'`.
Record compiler diagnostics as well as assertion output. Supplied sources
may produce warnings about old-style empty parameter lists or shadowed names.

`tests/test_lab_core.c` checks the actual lab. Extend
`tests/test_lab_student.c` with three original groups: hashing/chains,
pool lifecycle, and two sum. The initial smoke test alone is incomplete.
Compile only the driver when it includes the lab sources.
