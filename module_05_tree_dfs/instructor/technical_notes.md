# Module 5 Technical Notes

## Current representation and preconditions

The lecture source is [student/lab.c](../student/lab.c), explained in the
[textbook](../student/textbook.md). `struct TreeNode` stores `char data` and
integer child indices. `nodes[10]` owns ten fixed slots; `-1` represents an
absent child. Changing the global `capacity` does not resize that array.
Keep its supplied value 10 for this lab.

`alphabet_init()` initializes `A` through `J`, sets all child links to `-1`,
and sets `size = 10`. `tree_connect()` then makes the fixed tree rooted at
index 5 (`F`), with seven reachable nodes. Nodes 7 through 9 remain
unconnected. Initialize before connecting. `eq_tree()` resets `size` and
reuses the same node array, so the prior alphabet tree is no longer a
usable tree after expression construction.

Tree operations require a valid initialized root index, valid present
child indices, no cycles, and one parent per non-root node. They do not
accept `-1` as an empty-tree root or validate those properties.
`write_infix()` additionally requires digit leaves and supported binary
operators with two children; the alphabet tree is not a valid input to it.

## Recursive visits

`tree_traversal(i)` assigns `pre_data` before either child, `in_data` after
the left child, and `post_data` after the right child. Each child call is
guarded by a `!= -1` test. The runtime call stack remembers each waiting
node and the point where it will resume.

The globals have type `int` and hold character codes. They are overwritten
on every visit, so after the alphabet traversal their values are `'G'`,
`'G'`, and `'F'`. The routine does not print or save complete sequences.
Tracing assignments or using breakpoints reveals those sequences.

## Postfix construction

The accepted input assumption is a nonempty, well-formed postfix expression
of single-digit operands and binary `+`, `-`, `*`, `/`, or `%`. There are
no spaces, unary operators, or multidigit operands. Each operator has two
roots available, exactly one root remains at completion, and the complete
input including `'\0'` fits `post_eq[6]` (at most five tokens).

These are caller preconditions, not checks performed by the implementation.
Every nondigit is treated as an operator by `eq_tree()`; `prec()` returning
0 for unsupported characters is not validation. Do not claim malformed
input is rejected safely or use it as an ordinary lecture run.

The node for input position `i` is `nodes[i]`. Digits remain characters;
there is no `c - '0'` conversion and no evaluator. The local `int stack[10]`
stores roots of completed subexpressions. `top = -1` marks the empty stack,
`stack[++top] = i` pushes, and `stack[top--]` pops. The first pop supplies
the right child, the second the left. After each token, the stack contains
the complete subexpression roots represented by the processed prefix.

For `123*+`, the stack states are `[0]`, `[0, 1]`, `[0, 1, 2]`, `[0, 3]`,
and `[4]`. The root is 4, `size == 5`, `top == 0`, and maximum stack use is
three entries. `size` counts nodes; `top + 1` counts waiting roots.

## Infix formatting and output state

`prec()` returns 1 for `+ -`, 2 for `* / %`, 3 for digits, and 0 otherwise.
The formatter uses the parent symbol `c`, integer child indices `l` and
`r`, and `char` child symbols `l_data` and `r_data`.

- Parenthesize the left child when `prec(c) > prec(l_data)`.
- Parenthesize the right child when `prec(c) >= prec(r_data)`.

All supported operators associate to the left at equal precedence. The
strict left comparison permits `1-2-3` for `(1-2)-3`; the non-strict right
comparison preserves `1-(2-3)`. The same rule preserves an equal-precedence
right subtree such as `1+(2+3)` even when arithmetic identities could allow
fewer parentheses. The goal is the tree's grouping, not algebraic
simplification. Digits have higher comparison precedence than operators,
so digit leaves receive no parentheses.

During `write_infix()`, `pos` is the next output index. Every recursive
call contributes to one string; resetting the cursor inside the helper
would overwrite earlier output. Call `start_write_infix(root)` for a
complete conversion. It resets `pos`, invokes the helper, and writes
`infix[pos++] = '\0'`. The final cursor includes the terminator: `1+2*3`
has visible length 5 and final `pos == 6`. Termination is also necessary
when a later output is shorter; stale bytes beyond the new terminator are
not part of the string.

The formatter performs no capacity checks. A valid expression of at most
five tokens has at most two operators, hence at most one operator child
link that can require parentheses. Its maximum output uses five tokens,
two parentheses, and one terminator: eight bytes. `infix[10]` is therefore
sufficient for the current input limit. A larger manually constructed
expression or expanded input requires a new output bound; ten node slots
do not imply that every possible formatted tree fits ten characters.

## Cost model

Let `n` be the number of input tokens, `r` the number of nodes reachable
from the supplied root, and `h` the tree height in edges.

| Operation | Time | Temporary storage |
| --- | --- | --- |
| `alphabet_init()` | `O(capacity)` | `O(1)` |
| `tree_connect()` | `O(1)` for its six fixed links | `O(1)` |
| `eq_tree()` | `O(n)` | Up to `O(n)` used stack entries in a generalized builder |
| `tree_traversal()` | `O(r)` | `O(h + 1)` active recursive calls |
| `start_write_infix()` | `O(r)` | `O(h + 1)` active recursive calls, plus output |

Three assignments per node and a constant amount of punctuation per link
do not change linear time. A balanced tree has logarithmic height; a very
unbalanced tree can have linear height and linear call-stack use. The node
array, construction stack, and output buffer reserve ten entries each;
the input reserves six characters. The asymptotic statements describe how
the algorithms scale if capacities are generalized. The alphabet tree's
longest path `F, A, B, D` has three edges and four simultaneous node calls.

## Running and related material

`lab.c` supplies operations and has no `main`. Run `make lecture` from
`module_05_tree_dfs/code` to use [the lecture driver](../code/lecture/lab_demo.c).
The driver reports final global values and four formatted expressions;
full visit orders are obtained by tracing the assignments.

The [pointer-based iterative example](../code/lecture/iterative_traversals.c)
is optional. The existing `tree_dfs.h` starter/solution, legacy graded
tests, autopsy, and copy/print/evaluate contracts belong to a separate
exercise package. Their allocation, validation, and rollback behavior
must not be attributed to the current array-based lab.
