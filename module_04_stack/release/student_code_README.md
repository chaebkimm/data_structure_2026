# Module 4 Student Code

The teaching source is `../student/lab.c`. Read `../student/lab.md` for the
required tracing, experiments, and submission evidence. The source implements
the stack and expression functions; it has no `main` function.

- `lab_demo.c` supplies a small `main` for the expression demonstration.
- `tests/test_lab.c` supplies eight baseline test groups. Add three justified
  student cases to this file, preserving the supplied checks.
- `autopsy/faulty_top.c` is an isolated program with a deliberate logical
  defect. Predict its output before running it.

The baseline groups cover integer LIFO order, full/empty predicates and valid boundary operations,
canonical conversion, precedence and operand order, repeated
conversion with shared-state resets, character digits versus integer values,
shorter null-terminated inputs, and balanced parentheses. Record the original
behavior before making source changes or adding tests.

## Representation and input limits

`int stack[10]` stores waiting operator codes and any opening parentheses
during conversion, then numeric operands/results during evaluation. `top` is the
shared last active index; it is -1 when empty. The item count and next
insertion index are `top + 1`. Push writes `stack[++top]`;
pop returns `stack[top--]`; peek returns `stack[top]`. The predicates
`is_full()` and `is_empty()` report boundaries but do not guard operations.
Callers must avoid full push and empty reads, which have undefined behavior.

Both phases reset `top = -1`. Each converter also initializes local
`pos = 0`. There is no sentinel. Conversion checks `!is_empty()` before
reading or popping a waiting item. Lower precedence stops the operator loop
with `break`; equal or higher precedence causes another output write.
After the final operator drain, `postfix[pos++] = '\0'` writes the
terminator explicitly. For `1-2*3+4`, it goes to `postfix[7]`, advancing
`pos` to 8; visible token length is 7. For `1+(2+3)`, parentheses are
discarded and the terminator goes to `postfix[5]`, leaving `pos == 6`.
Evaluation scans to the terminator, reuses the same integer array, then
returns the final pop and leaves `top == -1`.

The default pipeline is `1-2*3+4` → `123*-4+` → `-1`. Supported expressions
have at most seven characters plus a null terminator, with single-digit
operands and binary `+ - * / %` operators. `convert_to_postfix()` scans
`eq` without parentheses. `infix_to_postfix_parentheses()` scans `eq_paren`
and accepts balanced parentheses; `1+(2+3)` becomes `123++` and evaluates
to 6. Shorter valid expressions work because loops stop at the terminator.
Exclude empty input, spaces, unary signs, multi-digit operands, zero
divisors, and arithmetic outside C `int`. The source assumes these conditions without validating them. Empty-stack
guards in conversion do not check matching parentheses or operand counts.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab-tests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

The default target is `lab`. Add `-Sanitize` when the installed compiler
supports it. A sanitizer watches a running program for certain memory and
undefined-behavior errors. The script searches for Clang, GCC, and then MSVC.
Use a Visual Studio Developer PowerShell when building with MSVC. PowerShell
7 users can substitute `pwsh` for `powershell`.

## GNU Make

The Makefile is for Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make lab-demo
make lab-tests
make autopsy
```

The default target runs the demonstration. The compiler defaults to GCC;
use `make CC=clang lab-tests` for Clang. For Clang or GCC with sanitizers:

```sh
make CC=clang CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -fsanitize=address,undefined -fno-omit-frame-pointer' lab-tests
```

Compilers may warn about empty parameter lists such as `is_full()` and
about narrowing integer operator codes to `char`. A `(void)` parameter list explicitly declares no
parameters in C11. The supplied source is not claimed to be warning-clean.
Run `make clean` to remove generated files in `build`.
