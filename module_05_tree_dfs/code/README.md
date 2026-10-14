# Module 5 C Code

## Current classroom lab

[`lecture/lab_demo.c`](lecture/lab_demo.c) and
[`tests/test_lab.c`](tests/test_lab.c) include the current
[`student/lab.c`](../student/lab.c) directly. Compile each driver alone;
do not also compile the included lab sources as separate translation units.

From this `code` directory:

```sh
make
make lecture
make lab-tests
```

The default target is the current lecture demo. Use `make CC=clang lecture
lab-tests` to select Clang. The build adds the repository root to the include
search path so the lab can reuse Chapter 2's index-based tree and Chapter 4's
integer stack. During the stack include, the lab temporarily renames its
`capacity` global to `stack_capacity` to avoid a duplicate definition.

For PowerShell with Clang, GCC, or Microsoft C available:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lecture
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab-tests -Sanitize
```

Microsoft C requires a Visual Studio Developer PowerShell or Command Prompt.
`-Sanitize` enables the compiler's supported memory checks. The `lecture` and
`lab-tests` targets do not accept `-Extensions` or `-StudentTests`; those
switches belong to the optional pointer API below.

Manual GCC or Clang compilation:

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -I../.. lecture/lab_demo.c -o build/lab_demo
./build/lab_demo
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -I../.. tests/test_lab.c -o build/lab_tests
./build/lab_tests
```

For AddressSanitizer and UndefinedBehaviorSanitizer, add
`-fsanitize=address,undefined -fno-omit-frame-pointer`. Strict compilation
reports existing classroom warnings, including empty parameter lists,
integer-to-character conversions, and an unused variable in Chapter 2.

## Expected lecture output

```text
Recursive traversal complete (visit comments).
Stack progress (A-G): 3 3 3 3 3 3 3
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
1234+++ -> 1+(2+(3+4))
12+3* -> (1+2)*3
831-/ -> 8/(3-1)
```

The lab's preorder, inorder, and postorder positions are comments. They
perform no visit output or assignment. Add an observable action at these
positions when collecting full traversal sequences. The driver calls the
recursive traversal and then reports the stack traversal's final progress
for the reachable A-G nodes; each completed node has progress 3.

The builder uses a stack of subtree-root indices, pops the right child before
the left child, and returns the final root. The canonical seven-token example
has root 6, seven nodes, and an empty stack. The writer uses `prec2()` to give
digit leaves precedence 3; it groups a left child when its precedence is lower
and a right child when its precedence is lower or equal. `write_infix()` resets
`infix_pos` on each call and null-terminates `infix[20]`. The extra examples
exercise grouping and successive builds and writes.

## Lab input assumptions and checks

The input contract is nonempty valid postfix in `postfix[8]`, up to seven
tokens: single digits and binary `+ - * / %`, with no spaces, unary operators,
or multidigit operands. The builder assumes two available subtree roots per
operator and one final root. The writer expects digit leaves and binary
operators with two valid children. These classroom functions do not validate
input or check capacity; the supplied valid expressions fit their buffers.

Stack traversal requires fresh zeroes in `progress` before each run. It resets
`top` itself, but leaves progress at 3 for completed nodes. Another run without
a caller reset can fail to terminate. A path of `h` nodes can use `h + 1`
stack entries because a missing-child `-1` is pushed too; a nine-node chain
fits `stack[10]`, while a ten-node chain does not.

`make lab-tests` executes the actual lab with seven groups of checks: missing
roots, parent resumption and sentinels, fresh traversal runs, a nine-node chain,
exact canonical tree links, precedence and operand order, and repeated writes
after rebuilding a smaller tree. Add justified cases here for the current lab.

## Optional earlier pointer API

The separate assignment contract remains in `include/tree_dfs.h`.
`support/tree_support.c` provides its fixed node pool. The TODOs in
`starter/tree_dfs.c` implement preorder copy, inorder formatting, and postorder
evaluation; `solution/tree_dfs.c` is its reference. It accepts digits, `+`,
and `*`, with explicit validation and failure contracts.

```sh
make starter-core
make starter-student-tests
make solution-core solution-extension solution-student-tests
make autopsy
```

The starter is expected to compile and fail behavioral tests until completed.
`tests/test_student.c` also contains three TODO tests and returns failure until
students supply them, even when linked with the reference solution.
These tests and the copy-failure autopsy exercise the pointer API. PowerShell
supports `-Target starter`, `-Target solution`, or `-Target autopsy`, with the
original test switches where applicable.

`lecture/iterative_traversals.c` is a separate pointer-stack comparison using
the expression `3+5*2`. Compile it on its own:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude lecture/iterative_traversals.c -o build/iterative_traversals
./build/iterative_traversals
```
