# Module 12 Student Code — Indexed AVL Lab

The required source is [../student/lab.c](../student/lab.c). It includes the
bundled [Module 2 source](../module_02_binary_tree/student/lab.c), defining
`nodes[10]` with `char data` and integer child links. Missing links use `-1`.
The AVL source has no `main`; each driver includes it exactly once.

## Build with GNU Make

From this `code` directory:

```sh
make lab-compile core student-tests comparison
```

`lab-compile` compiles the actual lab to an object without linking a main
function. `core` runs supplied correctness checks. `student-tests` runs
student-authored assertions in `tests/test_lab_student.c`. `comparison`
runs the seven-key plain-BST/AVL experiment in `tests/compare_lab.c`.

The Makefile passes both `-I../student` and `-I..`. The second include path
resolves the source's original root-relative Module 2 include. Set `CC`
explicitly if needed, for example `make CC=clang core`. Keep compiler
warnings in the evidence. With strict Clang flags, the included Module 2
demonstration currently warns about older no-argument declarations, an
`int`-to-`char` assignment, and an unused `data_read` local. These inherited
warnings are separate from an AVL assertion failure. Do not define
`NDEBUG`: the drivers require active assertions.

For sanitizer checks with a supported Clang or GCC:

```sh
make BUILD_DIR=build-sanitize CC=clang \
  CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -fsanitize=address,undefined -fno-omit-frame-pointer' \
  core student-tests
```

## Direct compiler commands

From `code`, create `build` and compile one driver at a time:

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -g -I../student -I.. \
  tests/test_lab_core.c -o build/lab_core
./build/lab_core
cc -std=c11 -Wall -Wextra -Wpedantic -g -I../student -I.. \
  tests/test_lab_student.c -o build/lab_student
./build/lab_student
```

Do not add `student/lab.c` or the Module 2 source as another translation
unit to these commands; their definitions are already included.

## PowerShell

From `code` with a configured Clang, GCC, or Visual Studio C compiler:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Comparison
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -CompileOnly
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests -Sanitize
```

`-CompileOnly` compiles the selected driver but does not run it. GNU/Clang
sanitizers check address and undefined behavior; Visual Studio uses its
available address sanitizer. Save the actual compiler command and result.

## Source contract and tests

Use IDs `0..9`, a root initialized to `-1`, and fresh node child links
initialized to `-1`. Insert each ID once and keep the returned root:

```c
root = _add(root, new_node);
```

The source does not guard invalid IDs or capacity. Height uses edges:
`get_height(-1)==-1`, leaf height `0`, and balance left height minus right
height. Every valid AVL node has balance `-1`, `0`, or `1`.

Equal characters descend left during insertion. A rotation can put an
equal value on either side; validate nondecreasing inorder order rather
than a permanent "equals only on the left" rule.

The four `rotate_*` functions only rewire links. `_add` then refreshes
heights in child-before-parent order. Calling a rotation helper alone does
not refresh its cached heights. The independent validator in
`tests/lab_test_support.h`, the plain BST baseline, and measured search
helpers are driver support; they are not functions exported by the lab.

Add the original tests required by [the lab](../student/lab.md). Check
nonempty transferred subtrees, all cached heights, reachable IDs, sorted
inorder data, duplicates, and valid ten-node capacity. Test preconditions
through guarded setup; invalid index calls are not rejection tests.
The optional repository pointer library is excluded from this package.
