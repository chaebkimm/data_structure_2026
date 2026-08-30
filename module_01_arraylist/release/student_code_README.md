# Module 1 Student Code

## Files you edit

- `starter/int_list.c`
- `tests/test_student.c`

Do not edit the public header or supplied tests unless your instructor
authorizes it.

## Fixed-capacity model

Use a plain ten-position integer array, a size count, and capacity ten.
Active items occupy indexes zero through size minus one. Capacity does not
change.

Complete `int_list_valid_index`, `int_list_find`, `int_list_append`,
`int_list_insert`, and `int_list_remove`. Use the valid-index helper before
direct reads and updates. Save each mutator's returned size; a rejected
request returns the original size and leaves every array element unchanged.

Insertion shifts right from back to front. Removal shifts left from front to
back. Both are core work. Extensions add only extra boundary and sequence
tests for the same operations.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Extensions
```

Add `-Sanitize` when supported. The execution-policy setting applies only to
the child process used by that command. The script searches for Clang, GCC,
and then Microsoft C; use a Visual Studio Developer PowerShell for Microsoft
C.

## GNU Make

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make starter-extension
```

The Makefile defaults to GCC. Use `make CC=clang starter-core` for Clang.

## Isolated Bounds and Invariant Autopsy

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Or run `make autopsy` in a POSIX-like shell.

The demonstration uses ten usable positions plus one extra physical guard
slot. Before running it, follow `../student/segfault_autopsy.md` and preserve
your prediction of the affected position and returned size. Then compare the
output with your prediction and explain the condition that needs repair.
The fixture stays within its actual backing array; a crash is not expected.
The guard is not additional usable list capacity.
