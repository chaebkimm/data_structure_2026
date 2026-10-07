# Module 5 C Code

## Current lecture

[`lecture/lab_demo.c`](lecture/lab_demo.c) supplies a `main` for the current
[`student/lab.c`](../student/lab.c). It includes that source directly, so
compile the demo alone. The demo uses the lab's functions rather than a
second implementation of them.

From this `code` directory:

```sh
make lecture
```

Use `make CC=clang lecture` to select Clang. The existing default `make`
target remains `starter-core` for the separate earlier assignment.

For PowerShell with Clang, GCC, or Microsoft C available:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lecture
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lecture -Sanitize
```

Microsoft C requires a Visual Studio Developer PowerShell or Command Prompt.
`-Sanitize` enables the compiler's supported memory checks. The lecture
target does not accept `-Extensions` or `-StudentTests`.

Manual GCC or Clang compilation:

```sh
mkdir -p build
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  lecture/lab_demo.c -o build/lab_demo
./build/lab_demo
```

For AddressSanitizer and UndefinedBehaviorSanitizer, add
`-fsanitize=address,undefined -fno-omit-frame-pointer` to that compile command.
Do not also pass `../student/lab.c`; its definitions are already included.

The lab includes Chapter 2 and Chapter 4 through relative paths, renames
the stack's duplicate `capacity` to `stack_capacity` during inclusion,
and defines `is_digit()`. Strict flags may still warn about classroom
code in the earlier labs, including an unused variable in Chapter 2.

## Expected lecture output

```text
Recursive last visits: G G F
Stack last visits: G G F
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
```

Both visit lines report final globals, not full sequences. The driver
runs each traversal once, calls `convert_to_postfix()` for Chapter 4's
`1-2*3+4`, builds seven nodes with root 6, and writes infix once. The
builder's final pop leaves `top == -1`.

The input contract is nonempty valid postfix in `postfix[8]`, up to seven
tokens: single digits and binary `+ - * / %`, no spaces, unary operators,
or multidigit operands. The builder assumes two roots per operator and
one final root; it does not validate input. The writer requires digit
leaves and binary operators with two children and adds no parentheses.

The stack traversal does not reset `progress`; another run can loop
forever. The writer does not reset `infix_pos`; another write appends after
the old terminator and can overrun the buffer. Repeated-run resets and
parentheses are extension tasks. Adding grouping for `1234+++` requires
twelve bytes for `1+(2+(3+4))` including its terminator, exceeding the
current ten-character output buffer. A ten-node traversal chain also
needs an extra stack entry for its sentinel. The supplied example fits.

## Optional iterative comparison

[`lecture/iterative_traversals.c`](lecture/iterative_traversals.c) retains
the earlier pointer-based example for optional comparison. It uses `Node`
from `tree_dfs.h`, explicit stacks of node addresses, and the expression
`3+5*2`. Its output and stack states differ from the current lab. Compile
it separately:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g \
  -Iinclude lecture/iterative_traversals.c -o /tmp/tree_dfs_iterative
/tmp/tree_dfs_iterative
```

## Separate copy, print, and evaluate package

The public contract for the earlier pointer-based assignment is in
`include/tree_dfs.h`. `support/tree_support.c` provides its fixed node pool.
The three TODOs in `starter/tree_dfs.c` implement preorder copy, inorder
formatting, and postorder evaluation; `solution/tree_dfs.c` is its reference.
These functions have their own validation and failure contracts.

Its existing commands remain available:

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The starter is expected to compile and fail behavioral tests until
completed. PowerShell supports `-Target starter`, `-Target solution`, or
`-Target autopsy`, with the original test switches where applicable. These
tests and the autopsy exercise the earlier API; they provide no verification
of `student/lab.c`.
