# Module 4 C Code

## Current lab

[../student/lab.c](../student/lab.c) defines a forward-growing global
character Stack and two expression phases. `lab_demo.c` supplies `main`;
`tests/test_lab.c` checks its documented behavior. Compile either harness
with the lab source, not both harnesses together.

From this `code` directory:

```sh
make                 # same as make lab-demo
make lab-tests
make autopsy
```

For Clang use `make CC=clang lab-tests`. GNU Make and a C11 compiler are
needed; the recipe works in suitable Windows shells, Linux, and macOS.

## PowerShell

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab-tests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

The default target is `lab`. The script searches for Clang, GCC, then MSVC.
MSVC requires a Visual Studio Developer PowerShell or Developer Command
Prompt. Add `-Sanitize` when supported. The lab targets do not accept the
older `-StudentTests` or `-Extensions` switches; extend `tests/test_lab.c`
for student evidence.

## Manual build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  ../student/lab.c lab_demo.c -o build/lab_demo
./build/lab_demo

cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  ../student/lab.c tests/test_lab.c -o build/lab_tests
./build/lab_tests
```

The supplied lab still uses `()` for six parameterless definitions. Some
compilers warn about these missing prototypes; use `(void)` when revising
them. With `-Wshadow`, local `value_size` also warns because it hides global `size`.
These are separate variables for the two Stacks. A successful build is not
evidence that the expression parser checks invalid inputs.

## Demo output

```text
infix: 1-2*3+4
postfix: 123*-4+
postfix_size: 7
result: -1
```

The tests cover six groups: character LIFO, full/empty boundaries,
canonical conversion, precedence and operand order, repeated/shorter
conversion, and character digits versus integer values. An unchanged
baseline ends with `6 lab test(s), 0 failure(s)`. Add three justified cases
to this file and record predictions as part of the lab evidence.

## Input assumptions

Use nonempty expressions of alternating single digits and binary
`+`, `-`, `*`, `/`, `%`. The eight-character string arrays allow at most
seven expression characters and their null terminator. The operator Stack
starts empty. Exclude whitespace, parentheses, unary operators, multi-digit
operands, zero divisors, and nonrepresentable arithmetic results.

The current functions do not validate these assumptions or return failure
status. Unsupported characters can overrun the postfix buffer; malformed
operands can underflow the local integer Stack; division/remainder by zero
and overflow are unchecked. The core tests stay within the supported
domain. Discuss rejection checks as extensions before expecting invalid
inputs to run safely.

Global `size` is the next insertion index and character count, `postfix_size` counts
postfix characters without the terminator, and local `value_size` counts integer
values during evaluation. The two `size` variables are separate. `capacity`
is initialized to 10 and controls the full check; the array has ten cells.

## Isolated autopsy

`make autopsy` builds an intentional wrong-index read using the current
forward representation. Follow [autopsy/README.md](autopsy/README.md) and
preserve predictions before running. Changing `lab.c` cannot change this
separate program's result.

## Optional earlier checked API

The `include/`, `starter/`, and `solution/` directories and older test files
belong to a different exercise: caller-owned integer arrays with a
size-based active prefix and a checked `+`/`*` evaluator. They remain for
comparison, with their original contracts and commands:

```sh
make starter-core              # intentionally incomplete
make starter-student-tests     # earlier exercise's placeholders
make solution-core
make solution-extension
```

PowerShell supports `-Target starter` or `-Target solution`, with
`-StudentTests` or `-Extensions` as applicable. These targets do not test
`student/lab.c`; their passing results must not be used as current lab
evidence. The Stage E student package excludes this optional track.
