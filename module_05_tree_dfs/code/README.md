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

The current lab has three parameterless definitions written with `()` and
an implicit `int`-to-`char` conversion in `alphabet_init()`. Strict C11
settings may warn about those lines. The lecture driver does not change
the lab's source or hide these warnings.

## Expected lecture output

```text
Last visits: G G F
123*+ -> 1+2*3
12+3* -> (1+2)*3
123-- -> 1-(2-3)
12+ -> 1+2
```

The first line reports the final contents of `pre_data`, `in_data`, and
`post_data`; it does not print the complete traversal sequences. Trace the
three assignment positions to obtain those sequences.

Each expression rebuilds the shared node array. `eq_tree()` resets `size`;
`start_write_infix()` resets `pos` and writes a final `'\0'`. The last case
shows that formatting a shorter expression replaces the previous string.
The wrapper leaves `pos` equal to the visible output length plus one.

The valid-input contract is nonempty postfix text with single digits and
binary `+`, `-`, `*`, `/`, or `%`, at most five tokens plus `'\0'` in
`post_eq[6]`. There are no spaces, unary signs, or multidigit operands.
Operators have two child subtrees. The builder assumes this contract; it
does not validate malformed input. The formatter records grouping and does
not evaluate arithmetic.

With this input limit, at most seven visible output characters and a
terminator are needed, so `infix[10]` fits. Larger manually built trees need
a separate capacity analysis. The writer does not check bounds.

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
