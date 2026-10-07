# Module 5 Answer Key

These answers match the current [lab](../student/lab.c),
[textbook](../student/textbook.md), and both worksheet formats. Parentheses
and repeated-run resets are extensions; the legacy pointer exercise has
its own contracts.

## A–B. Alphabet tree and recursion

`nodes_size == 10`; root 5 contains `F`; seven nodes are reachable and
`H, I, J` are unconnected. Changing links does not move array entries.

| Visit | Complete assignment sequence | Final global |
| --- | --- | --- |
| Preorder | `F A B D E C G` | `G` |
| Inorder | `D B E A C F G` | `G` |
| Postorder | `D E B C A G F` | `F` |

At `D`, the real-node calls are `F, A, B, D`; height is three edges.
Each caller still needs its inorder visit, right subtree, and postorder
visit. A leaf makes two empty-child calls; `tree_traversal(-1)` returns
before reading the array. Four real-node frames can be active, plus one
empty-child frame. The globals do not retain whole sequences.

## C. Explicit traversal

Beginning stack trace, bottom to top:

```text
[5] → [5,0] → [5,0,1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3] → [5,0,1] → [5,0,1,4]
```

Before pushing each child, the parent's progress advances. Steps 0, 1,
and 2 perform preorder/push-left, inorder/push-right, and postorder/pop.
Negative top entries are popped without reading progress. Final progress
is 3 for each reached node and 0 for the unconnected nodes. A second run
starts at step 3, matches no case, and never removes the root. Reset all
progress entries to zero before reuse.

## D. Reconstruction

Root `A` splits inorder into `DBE` and `FCG`. Each subtree has three nodes,
selecting preorder `BDE` and `CFG`. Their roots `B` and `C` split into
children `D, E` and `F, G`. Postorder is `DEBFGCA`. Distinct labels allow
unique splits; repeated labels can be ambiguous. This is the slides'
`A`-rooted tree, not Chapter 2's `F`-rooted tree. No reconstruction function
is supplied in `lab.c`.

## E. Postfix construction

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

## F. Current output versus grouping extension

| Postfix | Current output | Grouping-preserving extension |
| --- | --- | --- |
| `123*+` | `1+2*3` | `1+2*3` |
| `12+3*` | `1+2*3` | `(1+2)*3` |
| `123--` | `1-2-3` | `1-(2-3)` |
| `12-3-` | `1-2-3` | `1-2-3` |
| `123++` | `1+2+3` | `1+(2+3)` |
| `123/%` | `1%2/3` | `1%(2/3)` |

Use independent runs for current outputs. In the extension, open before
and close after a child call. Parenthesize operator children when parent
precedence is greater on the left or greater than or equal on the right.
Equal precedence groups left to right. `prec()` returns 0 for digits, so
exclude digits with `is_digit()` rather than comparing their precedence.
Unsupported characters also return 0; this is not validation.

## G. Output state and demo

For `123*+`, characters are `1 + 2 * 3 \0`; the terminator is at index 5
and final `infix_pos` is 6. The wrapper does not reset the position. Another
write starts after the old terminator, retaining the old visible string
and potentially overrunning the array. Reset `infix_pos` before each
complete write for reuse; never reset it in recursive child calls.

The demo performs one stack traversal and one write:

```text
Recursive last visits: G G F
Stack last visits: G G F
123*-4+ -> 1-2*3+4
Root: 6; nodes: 7; top: -1
```

Visit lines show only final globals. The converted expression has seven
nodes and root 6. The builder's final pop empties the stack.

## H. Assumptions, capacity, and efficiency

Tree links must form an acyclic tree with one parent per non-root node
and valid present indices. Traversal handles negative indices; the writer
requires a nonempty expression tree. Valid postfix uses single digits and
binary `+ - * / %`, no spaces, with two available roots per operator and
one final root. The code does not validate input or bounds.

`postfix[8]` allows seven tokens plus its terminator. The current writer
needs at most eight bytes. The parentheses extension's `1+(2+(3+4))`
requires twelve bytes including the terminator, exceeding `infix[10]`.
A ten-node path plus its empty-child sentinel requires eleven stack
entries; increase capacity or skip pushing absent children in an extension.

Traversal and writing are linear in reachable nodes; construction is
linear in tokens. Used recursive/path storage is `O(h + 1)`; progress
storage is separate, one integer per node slot. A generalized postfix
builder can use linear stack space in tokens. Reconstruction by repeated
inorder scans can take quadratic time; precomputed positions permit linear
time with distinct labels.

Assess preserved predictions and revisions justified by source statements.
Do not attribute the pointer exercise's copying, evaluation, validation,
or rollback behavior to this classroom lab.
