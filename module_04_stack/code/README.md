# Module 4 C Code

## What this code contains

- checked operations for a caller-owned, fixed-capacity integer Stack;
- `expression_evaluate`, a checked evaluator for single digits, `+`, and `*`;
- starter implementations with marked TODOs;
- an instructor reference solution;
- eight public core tests and five instructor extension tests;
- three student-test placeholders; and
- a separate, solution-independent top-index autopsy.

The Stack operations accept an array together with its current `size` and
fixed `capacity`. Valid metadata satisfies `0 <= size <= capacity`. Push
returns the new size or the original size when rejected. Peek returns `1` or
`0`. Pop returns the new size or the original size when rejected. Rejected
operations preserve the array and caller output, and pop never erases the
inactive slot.

The evaluator accepts a nonempty null-terminated expression matching:

```text
digit (('+' | '*') digit)*
```

It uses normal precedence and left associativity. Each internal Stack has ten
slots, and every push is checked. Total input length is not capped: slots are
reused as operators are applied. Malformed input, a live-capacity failure, or
`int` arithmetic overflow returns `0` without changing the caller's result.

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
compiler supports it. The script searches for Clang, GCC, and then MSVC. MSVC
must run from a Visual Studio Developer PowerShell or Developer Command
Prompt.

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
  -Iinclude \
  solution/int_stack.c solution/expression_evaluator.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

## Expected reference output

Core:

```text
PASS push adds at the top
PASS peek reads without mutation
PASS pop reports LIFO without erasing
PASS full push preserves array
PASS empty and zero capacity fail safely
PASS invalid arguments preserve state
PASS expression precedence and associativity
PASS invalid expressions preserve result

8 core test(s), 0 failure(s)
```

Extension:

```text
PASS every capacity through ten
PASS deterministic stack model
PASS valid expression table and long input
PASS invalid expression table
PASS checked integer overflow

5 extension test(s), 0 failure(s)
```

The supplied starter is intentionally incomplete, so its tests should compile
but fail until the TODOs are implemented.
