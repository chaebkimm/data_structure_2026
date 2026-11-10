# Module 09 lab driver

Read `../student/lab.md`. The supplied implementation is the self-contained
`../student/lab.c`. It has ten `{key,data,next}` nodes and fifteen buckets.
No other module is needed.

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
Record compiler diagnostics as well as assertion output.

`tests/test_lab_core.c` checks the actual lab. Extend
`tests/test_lab_student.c` with three original groups: hashing/chains,
capacity/reset/reuse, and two sum. The initial smoke test alone is incomplete.
Compile only the driver when it includes `lab.c`. Call `initialize()` before
direct table operations; `two_sum_ht` initializes itself on every call.
