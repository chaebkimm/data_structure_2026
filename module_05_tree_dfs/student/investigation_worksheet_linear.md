# Stage C — Investigation Worksheet: Linear Format

Use [`lab.c`](lab.c) and the [textbook](textbook.md). Record predictions
before running the [lecture demo](../code/lecture/lab_demo.c). From
`module_05_tree_dfs/code`, use `make lecture` (or `./build.ps1 -Target lecture`
in PowerShell). Inputs are well-formed, nonempty postfix strings with at
most five tokens: single digits and binary `+`, `-`, `*`, `/`, or `%`, with
no spaces. Keep answers in a separate numbered record.

1. Run `alphabet_init()` and `tree_connect()` on paper. Record the root
   index and character, `size`, reachable count, and unreachable characters.
   Explain `-1` child links and why connecting a child does not move it.
   Trace the full assignment sequence and final character for each of
   `pre_data`, `in_data`, and `post_data`. Explain whether the globals save
   whole sequences.
2. While processing `D`, list all active node calls and the work each older
   call must resume. Explain what happens at a leaf and why passing `-1`
   as a root is different from seeing it as a child link. Give the alphabet
   tree's height in edges and maximum number of active node calls.
3. Trace `123*+`, processing `'1'` at index 0, `'2'` at 1, `'3'` at 2,
   `'*'` at 3, and `'+'` at 4. After each token record its left and right
   indices, the stack from bottom to top, and `size`. Record both child
   links as `-1` for digits. Give the returned root, final `top`, and peak
   stack usage. Distinguish `size` from `top + 1`. Use `12-` to explain why
   the first pop becomes the right child. State whether construction
   calculates a value and what it does to the earlier alphabet tree.
4. Predict the infix strings for `123*+`, `12+3*`, `123--`, `12-3-`,
   `123++`, and `123/%`. Explain the parentheses in each. Explain the left
   `>` comparison, the right `>=` comparison, and the precedence value for
   digits. Does the fallback value 0 from `prec()` permit unsupported input?
5. Trace `start_write_infix()` for `123++`, then rebuild and format `12+`.
   For each call record all characters including `'\0'`, the terminator's
   index, and final `pos`. Explain why resetting and terminating are both
   needed and why child calls must not reset `pos`. Predict the complete
   lecture demo output and explain its first line before running it. Choose
   another valid expression fitting the input array, predict its output,
   and try it in a scratch driver.
6. State the tree shape and valid-root assumptions. Explain why the alphabet
   tree is unsuitable for `write_infix()`. State whether `eq_tree()`
   validates input and whether the writer checks output capacity. Derive
   the maximum tokens, operators, parentheses, and total characters
   including `'\0'` for `post_eq[6]`. Explain whether this bound also covers
   every larger tree that could fit in `nodes[10]`.
7. Let `n` count reachable nodes, `t` count postfix tokens, and `h` count
   height in edges. Explain traversal and formatting time, construction
   time, and maximum active node calls. Distinguish the ten reserved slots
   in `stack[10]` from the slots used by `123*+`, and from the space needed
   by a general builder with capacities that grow with input.
