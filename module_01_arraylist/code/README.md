# Module 1 C Code

## Targets

- `starter`: compiling scaffold; core tests initially fail.
- `solution`: instructor reference; core tests should pass.
- `-Extensions`: builds the insert/remove test executable.
- `-StudentTests`: builds the student-authored test template.
- `-AllocationFailure`: instructor-only deterministic allocation-failure test.
- `autopsy`: isolated intentional defect; never part of normal tests.

## PowerShell

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -AllocationFailure
```

Omitting `-Target` builds the starter core. The process-scoped execution-policy
flag works on machines whose normal policy blocks unsigned local scripts; it
does not change the user or machine policy. Add `-Sanitize` when the installed
Clang/GCC/MSVC supports it.

The script searches for Clang, GCC, then MSVC. MSVC must be launched from a Developer PowerShell/Command Prompt.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make solution-allocation-failure
make autopsy
```

The Makefile uses POSIX recipes and is intended for Git Bash, MSYS2, WSL,
Linux, or macOS. It defaults to `gcc`; use a command-line override such as
`make CC=clang starter-core` when needed. `make autopsy` builds but does not
run the intentional fault.

## Manual GCC/Clang core build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/int_list.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

## Manual MSVC core build

From a Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\int_list.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

Core:

```text
PASS null arguments
PASS initialization and destroy
PASS empty access and reserve zero
PASS first append
PASS repeated growth and values
PASS reserve preservation and no shrink
PASS boundaries and invalid shape
PASS overflow rejection preserves state

8 test(s), 0 failure(s)
```

Extension:

```text
PASS insert positions
PASS remove positions and discard
PASS invalid operations preserve state
PASS deterministic differential sequence

4 extension test(s), 0 failure(s)
```

Instructor allocation-failure test:

```text
PASS forced allocation failure preserves the entire list
```
