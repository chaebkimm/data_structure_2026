# Module 4 Student Code

## Files you edit

- `starter/char_stack.c`
- `starter/delimiter_validator.c`
- `tests/test_student.c`

Do not edit the public headers, supplied tests, autopsy, or build files unless
your instructor explicitly authorizes it.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Add `-Sanitize` when the installed compiler supports it. A **sanitizer** is a
compiler feature that watches a running program for certain memory errors.
The script searches for Clang, GCC, and then MSVC. Use a Visual Studio
Developer PowerShell when building with MSVC.

## GNU Make

The Makefile is for Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

It defaults to GCC. For Clang, run `make CC=clang starter-core`.

The starter is intentionally incomplete. A failing starter test is a prompt
to investigate the first failed requirement, not a reason to edit the
supplied test.
