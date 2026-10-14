# Module 5 Technical Notes

## Representation and integration

The [lab](../student/lab.c) and [lab slides](../student/ppt_lab_material.md)
reuse Chapter 2's tree and Chapter 4's stack. `nodes[10]` stores characters
and integer child indices; `-1` marks an absent child. `nodes_size` counts
initialized/constructed slots, not reachable nodes. `alphabet_init()`
initializes ten nodes; `tree_connect()` reaches seven from root 5 (`F`).
Changing capacity variables does not resize the arrays. Construction
reuses these nodes and replaces the earlier links.

Directly including the earlier `.c` files is a classroom shortcut. Both
earlier files define `capacity`; the lab temporarily renames the stack's
identifier to `stack_capacity` during inclusion. Its include paths start
at the repository root, so compilation supplies that root as an include
directory. See the [code guide](../code/README.md) for the runnable driver.
Reusable projects should separate declarations into headers.

## Recursion and explicit traversal

`tree_traversal()` first checks `i < 0`, then marks visits before, between,
and after its two unconditional child calls. The three visit comments are
positions for data processing; they do not execute an action or assign
visit globals. For the alphabet tree the potential orders are preorder
`FABDECG`, inorder `DBEACFG`, and postorder `DEBCAGF`. Leaves make two
empty-child calls.

The iterative version uses shared `stack[10]` and `progress[10]`. The
wrapper passes the current top to `tree_traversal_proceed(int i)`.
Progress advances before scheduling a child: 0 preorder/push-left,
1 inorder/push-right, 2 postorder/pop. A negative top is popped before
indexing progress. After one run, reached progress entries are 3. The
wrapper clears the stack but not progress; a second traversal starts at
step 3, matches no case, and leaves the root on the stack. Continued
increments can eventually overflow `int`. Reset progress before reuse;
do not demonstrate the unchanged second run by executing it. Call the
one-step helper only for the top of a nonempty stack.

A ten-node chain needs an eleventh entry for its sentinel; the supplied
tree's maximum stack use is five, including the sentinel. Per-node
progress also assumes links form a tree without shared children or cycles.

## Postfix construction and supplemental reconstruction

`postfix[8]` initially is empty. Convert Chapter 4's default `eq` to obtain
`123*-4+`, or supply valid postfix. `build_tree_from_postfix()` resets
`top` and `nodes_size`, creates one node per token, pops right before left,
and returns its final root with `pop()`. For `123*+`, root is 4, count 5,
final `top == -1`, and peak stack use is three. Stack entries are subtree
indices, not calculated values.

Require nonempty valid postfix of up to seven tokens: single digits and
binary `+ - * / %`, no spaces or unary/multidigit operands. Every operator
needs two roots and exactly one root remains before the final pop. Every
nondigit is treated as an operator; the builder performs no validation.

The companion concept slides reconstruct a tree from preorder and
inorder, assuming distinct labels: `ABDECFG` and `DBEAFCG` yield root `A`,
children `B, C`, and leaves `D, E, F, G`. This supplemental activity is
separate from the lab slides' four core steps; no reconstruction function
is supplied.

## Precedence-aware writer

`prec2()` returns 3 for digits and otherwise uses Chapter 4's `prec()`:
1 for `+ -`, 2 for `* / %`. Thus digit children do not need a separate
exclusion test. `_write_infix()` writes a digit leaf immediately. At an
operator it surrounds the left subtree when `prec2(left) < prec2(parent)`
and the right subtree when `prec2(right) <= prec2(parent)`. Opening and
closing parentheses surround the recursive child call; the parent symbol
is written between children. The right-side equality preserves grouping
under left associativity, even when arithmetic could simplify it.

`write_char()` appends one character and advances the shared cursor.
`write_infix()` resets `infix_pos` to zero, calls the helper, and appends
`'\0'`. Repeated writes therefore replace the visible string, including
when a new result is shorter. Child calls must not reset the cursor.
`123*+` produces `1+2*3`, with the terminator at index 5 and final position
6; `12+3*` produces `(1+2)*3`; `123--` produces `1-(2-3)`.

The helper returns on a negative root, so `write_infix(-1)` writes an
empty string. For nonempty expressions require digit leaves and binary
operators with two valid children: the helper reads child data before
recursing and does not validate malformed expression trees. The alphabet
tree is unsuitable writer input. Unsupported characters receive precedence
0 from `prec()`; this is not validation.

`infix[20]` accommodates the current valid input scope. With at most seven
tokens there are at most three binary operators, and at most two non-root
operator subtrees can receive parentheses: at most twelve bytes including
termination. `1234+++` reaches that bound with `1+(2+(3+4))`. A generalized
writer must still check remaining output capacity. The classroom code
checks neither output bounds nor positive tree-index bounds and does not
detect cycles/shared children.

## Costs and checks

Both traversals and writing take linear time in reachable nodes; building
takes linear time in tokens. Parentheses add constant work per child link.
Height `h` edges gives `h + 1` real-node frames/path entries, plus one
empty-child frame or sentinel for traversal. The writer's digit base case
avoids empty-child calls. Iterative progress reserves one entry per node
slot, separate from used path space. Generalized construction can need
linear token stack space. Inorder scans in supplemental reconstruction can
be quadratic; a position map allows linear work with distinct labels.

Run `make lecture` from `code` for traversal and conversion/build/write
demonstrations, and `make lab-tests` for checks of the classroom lab.
Strict flags may warn about definitions in the included earlier labs.
The pointer starter/solution, its tests, and copy/print/evaluate autopsy
are a separate package. Use [the answer key](answer_key.md) for worksheet
traces.
