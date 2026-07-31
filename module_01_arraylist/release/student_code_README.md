# Module 1 Student Code

## Files you edit

- `starter/int_list.c`
- `tests/test_student.c`

Do not edit the public header or instructor tests unless your instructor
authorizes it.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Extensions
```

Add `-Sanitize` when the installed compiler supports it. The
`-ExecutionPolicy Bypass` setting applies only to the child process used for
that command.

The script searches for Clang, GCC, and then MSVC. Use a Visual Studio
Developer PowerShell when building with MSVC.

## GNU Make

The Makefile is for Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make starter-extension
```

It defaults to GCC. For Clang, run `make CC=clang starter-core`.

## Isolated autopsy

Inspect first:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy -InspectOnly
```

The run without `-InspectOnly` deliberately invokes undefined behavior and
must remain separate from normal tests.
