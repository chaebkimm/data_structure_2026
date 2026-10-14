# Module 5 Answer Key

These answers match the current [lab](../student/lab.c),
[lab slides](../student/ppt_lab_material.md), [textbook](../student/textbook.md),
and both worksheet formats. The lab marks visit positions with comments,
writes grouping-preserving infix, and resets its writer cursor. A progress
reset for repeated stack traversal remains an extension. The legacy
pointer exercise has its own contracts.

## A–B. Alphabet tree and recursion

`nodes_size == 10`; root 5 contains `F`; seven nodes are reachable and
`H, I, J` are unconnected. Changing links does not move array entries.

| Visit position | Complete trace | Last node at that position |
| --- | --- | --- |
| Preorder | `F A B D E C G` | `G` |
| Inorder | `D B E A C F G` | `G` |
| Postorder | `D E B C A G F` | `F` |

These are traces of the visit comment positions. The current lab neither
records them nor defines `pre_data`, `in_data`, or `post_data`. A student
can add printing, appending, or another data-processing action at each
position; the last node alone would not retain a complete order.

At `D`, the real-node calls are `F, A, B, D`; height is three edges.
Each caller still needs its inorder visit, right subtree, and postorder
visit. A leaf makes two empty-child calls; `tree_traversal(-1)` returns
before reading the array. Four real-node frames can be active, plus one
empty-child frame.

## C. Explicit traversal

Beginning stack trace, bottom to top:

```text
[5] → [5,0] → [5,0,1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3] → [5,0,1] → [5,0,1,4]
```

Before pushing each child, the parent's progress advances. Steps 0, 1,
and 2 mark preorder/push-left, inorder/push-right, and postorder/pop.
The wrapper reads the top and passes it to `tree_traversal_proceed(int i)`
on every iteration. Negative top entries are popped without reading
progress. Final progress is 3 for each reached node and 0 for unconnected
nodes. A second run starts at step 3, matches no case, and does not remove
the root; continued increments can overflow `int`. Reset all progress
entries to zero before reuse. The wrapper itself resets only `top`.

## D. Postfix construction

| Token/index | Left | Right | Stack after token | `nodes_size` |
| --- | ---: | ---: | --- | ---: |
| `1` / 0 | -1 | -1 | `[0]` | 1 |
| `2` / 1 | -1 | -1 | `[0,1]` | 2 |
| `3` / 2 | -1 | -1 | `[0,1,2]` | 3 |
| `*` / 3 | 1 | 2 | `[0,3]` | 4 |
| `+` / 4 | 0 | 3 | `[4]` | 5 |

The final pop returns root 4 and leaves `top == -1`; peak usage is three.
For `12-`, index 1 (`2`) is popped first and belongs on the right, with
index 0 (`1`) on the left. Construction replaces the shared nodes without
calculating a value. The included `postfix` initially is empty; use
conversion or supply a valid string before building.

## E. Inorder output with grouping

| Postfix | Current writer output |
| --- | --- |
| `123*+` | `1+2*3` |
| `12+3*` | `(1+2)*3` |
| `123--` | `1-(2-3)` |
| `12-3-` | `1-2-3` |
| `123++` | `1+(2+3)` |
| `123/%` | `1%(2/3)` |
| `831-/` | `8/(3-1)` |

Open before and close after a child call. Parenthesize when child
precedence is lower on the left, or lower than or equal to the parent's
on the right. Equal-precedence supported operators group left to right.
`prec()` returns 0 for digits, but the implemented `prec2()` returns 3,
so digits never receive parentheses. Operator precedences are at most 2.
The writer preserves the tree's grouping, including `1+(2+3)`, without
using arithmetic identities to simplify it.

If parentheses were omitted, `12+3*` would produce `1+2*3` and lose its
left subtree's grouping; `123--` would produce `1-2-3` and lose its right
subtree's grouping. Those bare strings are comparison examples, not the
updated writer's output.

## F. Output state and demo

For `123*+`, characters are `1 + 2 * 3 \0`; the terminator is at index 5
and final `infix_pos` is 6. The wrapper resets the position before writing.
A second complete call begins at index 0 and writes its own terminator,
so even a shorter expression replaces the old visible string. Recursive
child calls share the cursor and must not reset it. `write_infix(-1)`
writes an empty string because the helper's negative-index guard returns.

The demo's expected output is:

```text
Recursive traversal complete (visit comments).
Stack progress (A-G): 3 3 3 3 3 3 3
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
1234+++ -> 1+(2+(3+4))
12+3* -> (1+2)*3
831-/ -> 8/(3-1)
```

The first line confirms that recursion returned; it does not show visit
orders. The progress line confirms completion for the seven reached nodes.
The default converted expression has seven nodes and root 6. The builder's
final pop empties the stack. Subsequent examples demonstrate the implemented
parentheses and repeated writes.

## G. Assumptions, capacity, and efficiency

Tree links must form an acyclic tree with one parent per non-root node
and valid present indices. Traversal handles negative indices; nonempty
writer input must have digit leaves and binary operators with two children.
Valid postfix uses single digits and binary `+ - * / %`, no spaces, with
two available roots per operator and one final root. The code does not
validate input or bounds.

`postfix[8]` allows seven tokens plus its terminator. `infix[20]` holds
the grouped `1+(2+(3+4))`, which requires twelve bytes including termination.
Seven-token valid expressions have at most three binary operators and
at most two non-root operator subtrees requiring parentheses, so twelve
bytes is the current maximum. Longer generalized input needs new capacity
checks. A ten-node path plus its empty-child sentinel requires eleven
stack entries; increase capacity or skip pushing absent children in an
extension.

Traversal and writing are linear in reachable nodes; construction is
linear in tokens. Used recursive/path storage is `O(h + 1)`; progress
storage is separate, one integer per node slot. A generalized postfix
builder can use linear stack space in tokens. Supplemental reconstruction
by repeated inorder scans can take quadratic time; precomputed positions
permit linear time with distinct labels.

## H. Optional transfer: reconstruction

Root `A` splits inorder into `DBE` and `FCG`. Each subtree has three nodes,
selecting preorder `BDE` and `CFG`. Their roots `B` and `C` split into
children `D, E` and `F, G`. Postorder is `DEBFGCA`. Distinct labels allow
unique splits; repeated labels can be ambiguous. This is the companion
concept slides' `A`-rooted tree, unlike Chapter 2's `F`-rooted tree.
Reconstruction supplements the lab slides' four-step sequence. No
reconstruction function is supplied in `lab.c`.

Assess preserved predictions and revisions justified by source statements.
Do not attribute the pointer exercise's copying, evaluation, validation,
or rollback behavior to this classroom lab.
