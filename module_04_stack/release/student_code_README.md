# Module 4 Student Code

The teaching source is `../student/lab.c`. Read `../student/lab.md` for the
required tracing, experiments, and submission evidence. The source implements
the stack and expression functions; it has no `main` function.

- `lab_demo.c` supplies a small `main` for the expression demonstration.
- `tests/test_lab.c` supplies six baseline test groups. Add three justified
  student cases to this file, preserving the supplied checks.
- `autopsy/faulty_top.c` is an isolated program with a deliberate logical
  defect. Predict its output before running it.

The baseline groups cover character LIFO order, full/empty boundaries,
canonical conversion, precedence and operand order, repeated/shorter
conversion, and character digits versus integer values. Record the original
behavior before making source changes or adding tests.

## Representation and input limits

`char stack[10]` stores pending operators. Empty means `top == 10`; full means
`top == 0`. Pushing decrements `top` before writing, and popping reads before
incrementing it. `size` counts postfix tokens; it is not the operator-stack
size. Postfix evaluation uses a separate local `int values[10]` with `pos` as
the next free position.

The default pipeline is `1-2*3+4` → `123*-4+` → `-1`. Supported experiments
use syntactically valid expressions of at most seven characters, single-digit
operands, and binary `+`, `-`, `*`, `/`, or `%` operators. Start with an empty
operator stack, avoid zero divisors, and keep integer results representable.
Spaces, parentheses, unary signs, multi-digit operands, and malformed input
are outside this implementation. The program does not check all of these
preconditions; passing valid-input tests does not establish safe handling of
invalid input.

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

Some compilers warn about the current source's old-style empty parameter
lists, such as `is_full()`. A `(void)` parameter list explicitly declares no
parameters in C11. The supplied source is not claimed to be warning-clean.
Run `make clean` to remove generated files in `build`.
