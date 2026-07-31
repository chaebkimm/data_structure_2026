# Module 2 Student Code

## Files you edit

- `starter/tree_arena.c`
- `tests/test_student.c`

Do not edit the public header or supplied core tests unless your instructor
authorizes it.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The first command builds the supplied core tests. The second builds your three
student-designed tests.

A **compiler** translates C source into a program the computer can run. The
script looks for Clang, GCC, and then Microsoft C. Use a Visual Studio
Developer PowerShell when building with Microsoft C.

Add `-Sanitize` when supported. A **sanitizer** adds checks that can report
certain memory mistakes while the program runs. The execution-policy option
applies only to the child PowerShell process used for that command.

## GNU Make

GNU Make is a program that runs written build commands. In Git Bash, MSYS2,
WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

The Makefile defaults to GCC. Use `make CC=clang starter-core` to select
Clang.

## Isolated autopsy

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The autopsy intentionally creates links that do not form a pure tree. It is
an observation exercise and is never part of the passing test suite.
