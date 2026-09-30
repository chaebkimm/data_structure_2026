# Module 4 C Code

## Current lab

[../student/lab.c](../student/lab.c) defines a forward-growing global
integer Stack and two expression phases. `lab_demo.c` supplies `main`;
`tests/test_lab.c` checks its documented behavior. Compile either harness
with the lab source, not both harnesses together.

The [lab guide](../student/lab.md) connects this source to the
[Korean textbook](../student/textbook_korean.md): 추가 (`push`), 확인 (`peek`),
삭제 (`pop`), 데이터, 규칙, and 마지막 데이터. Its parentheses trace follows
`infix_to_postfix_parentheses()` in the current lab.

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

The supplied lab still uses `()` for seven parameterless definitions. Some
compilers warn about these missing prototypes and int-to-char conversions; use `(void)` when revising
them. A successful build is not
evidence that the expression parser checks invalid inputs.

## Demo output

```text
infix: 1-2*3+4
postfix: 123*-4+
result: -1
infix with parentheses: 1+(2+3)
postfix: 123++
result: 6
```

The tests cover eight groups: integer LIFO, full/empty predicates and valid boundary operations,
canonical conversion, precedence and operand order, repeated
conversion with shared-state resets, character digits versus integer values,
shorter null-terminated inputs, and balanced parentheses. An unchanged
baseline ends with `8 lab test(s), 0 failure(s)`. Add three justified cases
to this file and record predictions as part of the lab evidence.

## Input assumptions and shared state

Use nonempty valid expressions of at most seven characters plus `'\0'`
in `eq[8]` or `eq_paren[8]`. Scans stop at the terminator, so shorter
expressions such as `2+3` and `7` work. Operands are single digits and
binary operators are `+ - * / %`. `convert_to_postfix()` reads `eq` without
parentheses; `infix_to_postfix_parentheses()` reads `eq_paren` and also
accepts balanced parentheses. Exclude spaces, unary signs, multi-digit
operands, zero divisors, and nonrepresentable arithmetic results.

`int stack[10]` is shared by both phases. Push writes `stack[++top]`; pop
returns `stack[top--]`; peek returns `stack[top]`. Empty is `top == -1`;
item count and next insertion index are `top + 1`. Full/empty predicates
only report state. Callers must avoid full push and empty reads: these helpers
have no guards or safe rejection contract. `capacity` affects the full
predicate without resizing storage or stopping push.

Each converter resets `top = -1` and initializes local `pos = 0`, without
a sentinel. Its operator loops use `while (!is_empty())` before reading or
popping. The precedence check stops with `break` when a waiting operator
has lower precedence; otherwise that operator is written to `postfix`.
After the final drain, `postfix[pos++] = '\0'` explicitly ends the string.
For `1-2*3+4`, that write uses `postfix[7]`, leaving `pos == 8` and
`top == -1`. For `1+(2+3)`, parentheses are discarded and the terminator
goes to `postfix[5]`, leaving `pos == 6`.
Evaluation resets `top = -1` again, reuses `stack` for integers, scans
postfix tokens until the terminator, and returns its final `pop()`, leaving
`top == -1`.

The conversion guards do not validate syntax: unmatched closing parentheses
can be silently ignored, and unmatched opening parentheses can enter output.
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
