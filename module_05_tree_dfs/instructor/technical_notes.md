# Module 5 Technical Notes

## Representation and integration

The [lab](../student/lab.c) includes Chapter 2's tree and Chapter 4's stack
using paths relative to itself. Both earlier files define `capacity`; a
temporary macro names the stack's version `stack_capacity`. The lab defines
`is_digit()` for its writer. This permits direct classroom compilation;
header-based separation is a later refactoring topic.

`nodes[10]` stores characters and child indices. `nodes_size` counts
initialized/constructed slots, not reachable nodes. `alphabet_init()`
initializes ten nodes; `tree_connect()` reaches seven from root 5 (`F`).
Changing capacity variables does not resize the arrays. Construction
reuses these nodes and destroys the earlier links.

## Recursion and explicit traversal

`tree_traversal()` first checks `i < 0`, then visits before, between, and
after its two unconditional child calls. Leaves make two empty-child calls.
Final globals are `G G F`; tracing assignments reveals full orders.

The iterative version uses shared `stack[10]` and `progress[10]`. Progress
advances before scheduling a child: 0 preorder/push-left, 1 inorder/push-right,
2 postorder/pop. A negative top is popped immediately. After one run,
reached progress entries are 3. The wrapper clears the stack but not
progress; a second traversal cannot pop a completed root. Reset progress
before reuse in the extension. Only call the one-step helper on a nonempty
stack. A ten-node chain needs an eleventh entry for its sentinel; the
supplied tree's maximum stack use is five, including the sentinel.

## Reconstruction and construction

Preorder plus inorder uniquely reconstructs the slides' tree when labels
are distinct: `ABDECFG` and `DBEAFCG` yield root `A`, children `B, C`, and
leaves `D, E, F, G`. This conceptual activity is not a lab function.

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

## Writer and extensions

`_write_infix()` emits bare inorder symbols. `write_infix()` appends a null
terminator without resetting `infix_pos`; use it once from position zero.
`123*+` gives `1+2*3`, final position 6. `12+3*` gives the same text and
loses grouping. The alphabet tree is not valid writer input; require digit
leaves and binary operators with two children, plus a valid nonempty root.

The slides propose parentheses around operator children when the parent's
precedence is greater on the left, or greater than or equal on the right.
`prec()` returns 1 for `+ -`, 2 for `* / %`, and 0 otherwise, including
digits. Exclude digits with `is_digit()`. Open before the child call and
close afterward. For repeated writes reset position in the wrapper and
terminate each result; child calls share the cursor.

The current seven-token output needs eight bytes including termination,
fitting `infix[10]`. Adding grouping can exceed it: `1234+++` needs
`1+(2+(3+4))`, twelve bytes including termination. Resize or check output
capacity for that extension. The classroom code checks neither output
bounds nor positive tree-index bounds and does not detect cycles/shared
children.

## Costs and checks

Both traversals and writing take linear time in reachable nodes; building
takes linear time in tokens. Height `h` edges gives `h + 1` real-node
frames/path entries, plus one empty-child frame or sentinel. Iterative
progress reserves one entry per node slot, separate from used path space.
Generalized construction can need linear token stack space. Inorder scans
in reconstruction can be quadratic; a position map allows linear work.

Run `make lecture` from `code` for one traversal of each kind and one
conversion/build/write pipeline. Strict flags may warn about definitions
in the included earlier labs. The pointer starter/solution, tests, and
copy/print/evaluate autopsy are a separate package and do not verify this
array lab. Use [the answer key](answer_key.md) for worksheet traces.
