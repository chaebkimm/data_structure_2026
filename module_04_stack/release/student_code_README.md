# Module 4 Student Code

The teaching source is `../student/lab.c`. Read `../student/lab.md` for the
required tracing, experiments, and submission evidence. The source implements
the stack and expression functions; it has no `main` function.

- `lab_demo.c` supplies a small `main` for the expression demonstration.
- `tests/test_lab.c` supplies six baseline test groups. Add three justified
  student cases to this file, preserving the supplied checks.
- `autopsy/faulty_top.c` is an isolated program with a deliberate logical
  defect. Predict its output before running it.

The baseline groups cover integer LIFO order, full/empty predicates and valid boundary operations,
canonical conversion, precedence and operand order, repeated seven-character
conversion with shared-state resets, and character digits versus integer values. Record the original
behavior before making source changes or adding tests.

## Representation and input limits

`int stack[10]` stores operator codes and a bottom `'\0'` sentinel during
conversion, then numeric operands/results during evaluation. `size` is the
shared item count and next insertion index. Push writes `stack[size++]`;
pop returns `stack[--size]`; peek returns `stack[size - 1]`. The predicates
`is_full()` and `is_empty()` report boundaries but do not guard operations.
Callers must avoid full push and empty reads, which have undefined behavior.

Both phases reset `size`. Conversion also initializes local `pos = 0` and
pushes the sentinel. Its final drain writes that sentinel to `eq_re[7]`,
advancing `pos` to 8; visible token length is 7. Evaluation reuses the same
integer array without a sentinel, then returns the final pop and leaves
`size == 0`.

The default pipeline is `1-2*3+4` → `123*-4+` → `-1`. Supported expressions
have exactly seven characters: four single digits alternating with three
binary `+ - * / %` operators. `eq[7]` holds the terminator. Shorter expressions
are unsupported because both loops run seven times. Exclude spaces,
parentheses, unary signs, multi-digit operands, zero divisors, and arithmetic
outside C `int`. The source assumes these conditions without validating them.

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
