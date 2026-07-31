# Module 3 Student Code

The **starter** is the file you complete. A **header** is a `.h` file that
lists names and functions other files may use. A **test** runs one case and
checks its result; the **core tests** check the required work.

## Files you edit

- `starter/graph_matrix.c`
- `tests/test_student.c`

Do not edit the supplied header or core tests unless your instructor
authorizes it.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The first command builds the supplied core tests. The second builds your
three student-designed tests.

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

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The autopsy intentionally creates a one-sided undirected relationship. It is
an observation exercise and is never part of the passing test suite.
