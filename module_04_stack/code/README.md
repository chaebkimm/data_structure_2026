# Module 4 C Code

## Current lab

[../student/lab.c](../student/lab.c) defines a forward-growing global
integer Stack and two expression phases. `lab_demo.c` supplies `main`;
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
compilers warn about these missing prototypes and int-to-char conversions; use `(void)` when revising
them. A successful build is not
evidence that the expression parser checks invalid inputs.

## Demo output

```text
infix: 1-2*3+4
postfix: 123*-4+
result: -1
```

The tests cover six groups: integer LIFO, full/empty predicates and valid boundary operations,
canonical conversion, precedence and operand order, repeated seven-character
conversion with shared-state resets, and character digits versus integer values. An unchanged
baseline ends with `6 lab test(s), 0 failure(s)`. Add three justified cases
to this file and record predictions as part of the lab evidence.

## Input assumptions and shared state

Use exactly seven expression characters: four single digits alternating with
three binary `+ - * / %` operators, with `'\0'` in `eq[7]`. Both expression
loops run seven iterations, so shorter strings are unsupported. Exclude
spaces, parentheses, unary signs, multi-digit operands, zero divisors, and
nonrepresentable arithmetic results.

`int stack[10]` is shared by both phases. Push writes `stack[size++]`; pop
returns `stack[--size]`; peek returns `stack[size - 1]`. Full/empty predicates
only report state. Callers must avoid full push and empty reads: the source
has no guards or safe rejection contract. `capacity` affects the full
predicate without resizing storage or stopping push.

Conversion resets `size`, initializes local `pos = 0`, and pushes `'\0'`.
The final drain writes that sentinel to `eq_re[7]`, ending with `pos == 8`
and `size == 0`. Evaluation resets `size` again, reuses `stack` for integers,
processes seven tokens, and returns its final `pop()`, leaving `size == 0`.

Malformed syntax, output bounds, operand counts, division/remainder by zero,
and signed overflow are unchecked. Tests exercise supported inputs and
valid Stack calls only; discuss unsupported cases as paper diagnoses.

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
