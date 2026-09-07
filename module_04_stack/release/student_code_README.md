# Module 4 Student Code

## Files you edit

- `starter/int_stack.c`
- `starter/expression_evaluator.c`
- `tests/test_student.c`

Do not edit public headers, supplied core tests, autopsy files, or build files
unless your instructor explicitly authorizes it. The reference solution and
instructor extension tests are intentionally absent from this package.

The Stack functions borrow caller-owned fixed storage. They do not change its
extent or erase it. The evaluator accepts only the grammar documented in
`include/expression_evaluator.h`.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Add `-Sanitize` when the installed compiler supports it. A sanitizer is a
compiler feature that watches a running program for certain memory and
undefined-behavior errors. The script searches for Clang, GCC, and then MSVC.
Use a Visual Studio Developer PowerShell when building with MSVC.

## GNU Make

The Makefile is for Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

It defaults to GCC. For Clang, run `make CC=clang starter-core`.

The starter is intentionally incomplete. A failing test is a prompt to
investigate the first unmet requirement, not a reason to edit the supplied
test. Predict and record the autopsy result before running it; its deliberate
logical defect is independent of the starter.
