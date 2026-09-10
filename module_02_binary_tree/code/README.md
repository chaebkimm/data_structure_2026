# Module 2 C Code

The lab implements the expression tree in the English and Korean Chapter 2
textbooks. Every node stores a character and two integer child indices in
`nodes[20]`. A child index of `-1` means no child; index `0` is a valid node.
Digits are stored as characters such as `'2'`; evaluation converts them to
integers by subtracting `'0'`.

For `1+2*3`, the root stores `'+'`, its left child stores `'1'`, and its right
child stores `'*'`. That multiplication has leaves `'2'` and `'3'`. Evaluation
returns `7` without changing the operator characters or child links.

## Core work and coding plan

Complete the four `TODO(core)` functions in `starter/binary_tree.c`:

1. `new_node(char data)`: use the next unused array position, initialize both
   children to `-1`, advance `size`, and return the reserved index.
2. `term(void)`: consume a digit and any following `*`-digit pairs. Each new
   `'*'` parents the old root and the next digit. Leave `'+'` or `'\0'` unread.
3. `terms(void)`: build a complete term, then combine complete terms under
   each `'+'`. Calling `term()` for each operand gives multiplication its
   higher precedence. Return the final root index.
4. `eval_tree(int node)`: return a digit's integer value, or recursively
   evaluate the two children and combine their returned answers. The stored
   tree remains unchanged.

Both builders share `pos`, the next unread position in `eq`. The globals
start as `nodes[20]`, `size = 0`, `eq[20] = "1+2*3"`, and `pos = 0`.
`include/binary_tree.h` declares these objects and the function contracts.

## Valid input and independent runs

Use a nonempty expression containing single digits alternating with `+` or
`*`, no whitespace or parentheses, and at most 19 characters so `eq[20]` has
room for `'\0'`. Every intermediate result and the final answer must fit in
an `int`. Input validation, extra operators, and overflow handling are not
part of this chapter's implementation.

Before each independent expression, reset the used count and cursor and copy
the valid expression. For example, with `<string.h>` included:

```c
size = 0;
pos = 0;
strcpy(eq, "2*3+4"); /* Known valid text that fits in eq. */
int root = terms();
int answer = eval_tree(root); /* 10 */
```

Old root indices become obsolete when the array is reused. The next build
initializes every node it reserves, so clearing the entire array is
unnecessary. Evaluate only a completed subtree with a valid root index;
`eval_tree(-1)` is not an empty-tree operation.

## Targets

- `starter-core`: compile the scaffold and run eight required tests;
- `starter-student-tests`: run the three student-designed placeholders;
- `starter-extension`: run five extra checks against the starter;
- `solution-core`: run the reference core tests;
- `solution-extension`: run boundary and repeated-build tests;
- `lecture`: link the textbook example to the solution and print its answer;
- `autopsy`: demonstrate faulty precedence with two safe tree fixtures; and
- `clean`: remove generated executables.

The default Make target is the starter core. Its tests intentionally fail
until the four functions are implemented. The three student placeholders
also fail until students replace them with their own assertions.
`tests/test_helpers.h` provides reset, assertion, and structural checks for
the test harness. These checks prevent test code from following an invalid
returned root; they are not additional student implementation tasks.

## PowerShell

Run from this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions -Sanitize
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target lecture
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

`-ExecutionPolicy Bypass` applies only to this PowerShell process. The script
searches for Clang, GCC, and then Microsoft C (`cl`). Microsoft C needs a
Visual Studio Developer PowerShell or Command Prompt. `-Sanitize` enables
supported run-time memory checks.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make lecture
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS. It
defaults to `gcc`; override it with `make CC=clang solution-core` when needed.

## Manual GCC or Clang build

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude solution/binary_tree.c tests/test_core.c \
  -o build/solution_core

./build/solution_core
```

To check boundary expressions with Clang or GCC:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  -Iinclude solution/binary_tree.c tests/test_extension.c \
  -o build/solution_extension_sanitized

./build/solution_extension_sanitized
```

## Manual Microsoft C build

From a Visual Studio Developer PowerShell:

```powershell
New-Item -ItemType Directory -Force build | Out-Null
cl /nologo /std:c11 /W4 /Zi /Iinclude `
  solution\binary_tree.c tests\test_core.c `
  /Fe:build\solution_core.exe

.\build\solution_core.exe
```

## Expected reference output

```text
PASS node allocation and empty links
PASS term leaves plus unread
PASS multiplication chain keeps previous root
PASS textbook precedence and complete input
PASS addition chain keeps previous root
PASS digit evaluation including zero
PASS recursive evaluation preserves nodes
PASS reset and reuse for another expression

8 core test(s), 0 failure(s)
```

The extension suite reports five passing tests: maximum-length addition and
multiplication chains, mixed precedence including zero-valued terms, shared
cursor continuation, and repeated builds. All expressions satisfy the input
contract, including the requirement that every intermediate result fits.

`make lecture` prints `1+2*3 = 7`. `make autopsy` reports the faulty result `9`
and the correct result `7`, then exits successfully when the planned fault
has been demonstrated. Its standalone code is available without the solution.
