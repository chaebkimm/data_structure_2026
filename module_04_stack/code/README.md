# Module 4 C Code

## What this code contains

- `CharStack`: an ArrayList-backed stack of characters;
- `delimiter_validate`: a checker for `()`, `[]`, and `{}`;
- a starter with marked TODOs;
- an instructor reference solution;
- public core tests and instructor extension tests;
- a student test template; and
- a separate, solution-independent autopsy.

The public tests compile with `CHAR_STACK_TESTING`, which exposes a small test
seam that makes the next allocation fail. A **test seam** is a controlled hook
used to reproduce a difficult condition. Production and student-test builds
do not expose it.

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
  -Target autopsy
```

Omitting `-Target` builds the starter core. Add `-Sanitize` when the installed
compiler supports it. A **sanitizer** is a compiler feature that watches a
running program for certain memory and undefined-behavior errors.

The script searches for Clang, GCC, and then MSVC. MSVC must run from a Visual
Studio Developer PowerShell or Developer Command Prompt.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS. It
defaults to GCC. For Clang, use `make CC=clang solution-core`.

## Manual GCC/Clang reference build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -DCHAR_STACK_TESTING -Iinclude \
  solution/char_stack.c solution/delimiter_validator.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

## Expected reference output

Core:

```text
PASS initialization, limits, and destroy
PASS zero limit and empty outputs
PASS LIFO push, peek, and pop
PASS geometric growth and clipping
PASS small limits clip first growth
PASS allocation failure preserves stack
PASS invalid states preserve outputs
PASS valid delimiter texts and ignored characters
PASS delimiter error categories and indexes
PASS delimiter depth limit
PASS delimiter nonreporting failures preserve output

11 core test(s), 0 failure(s)
```

Extension:

```text
PASS every small limit and capacity step
PASS deterministic stack model
PASS maximum delimiter depth
PASS delimiter case table
PASS status names cover public values

5 extension test(s), 0 failure(s)
```
