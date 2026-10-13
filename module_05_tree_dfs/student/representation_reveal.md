# Stage B — Representation Reveal: Indices, Visits, and Saved Progress

Open this after preserving the Stage A inquiry. The implementation is
[`lab.c`](lab.c); [the lab slides](ppt_lab_material.md) give its four steps:
recursive traversal, stack traversal, postfix construction, and infix writing.

## Follow and visit

`nodes[10]` stores characters and integer child indices; `-1` is absent.
`alphabet_init()` initializes ten slots. `tree_connect()` returns root
5 (`F`), reaching seven nodes and leaving `H`, `I`, and `J` unconnected.

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

| Position of the visit hook | Order | Trace if symbols are recorded |
| --- | --- | --- |
| Before children | Preorder | `F A B D E C G` |
| Between children | Inorder | `D B E A C F G` |
| After children | Postorder | `D E B C A G F` |

The source marks these positions with comments. It does not print symbols
or save visit globals. Add an assigned recording action at a hook to observe
its order; a single overwritten variable would retain only the last symbol.
`tree_traversal(i)` returns before accessing `nodes[i]` when `i < 0`.
At `D`, four real-node calls are active along `F → A → B → D`, plus one
frame while an empty-child call is active.

## Resume with an explicit stack

`tree_traversal_with_stack(root_index)` resets `top`, pushes the root, and
calls `tree_traversal_proceed(peek())` while the stack is nonempty. The
helper receives a node index. `progress[i]++` saves its old value as `step`
and advances progress before the selected action:

| Old progress | Visit hook | Action |
| --- | --- | --- |
| 0 | Preorder | Push left child |
| 1 | Inorder | Push right child |
| 2 | Postorder | Pop current node |

A top entry of `-1` is popped before accessing data or progress. A leaf
therefore pushes and removes two empty-child entries. The stack holds the
unfinished path; reached nodes finish with progress 3. The wrapper does not
reset `progress`. Before another stack traversal, reset its entries to zero,
even if a new tree now occupies the same node slots.

## Build from postfix

Prepare the initially empty shared `postfix` first, using Chapter 4's
converter or a valid postfix string. For `123*+`, stack states after each
token are `[0]`, `[0,1]`, `[0,1,2]`, `[0,3]`, and `[4]`. Each operator
pops right then left and pushes its own index. The builder's final pop
returns root 4, with `nodes_size == 5` and `top == -1`. Peak stack usage
is three. Construction replaces the alphabet tree and stores digit
characters; it does not calculate an arithmetic result.

## Write inorder while preserving grouping

`prec2()` gives digits precedence 3, `* / %` precedence 2, and `+ -`
precedence 1. At an operator node, `_write_infix()` writes the left subtree,
current operator, and right subtree. It surrounds the left child when
`prec2(left) < prec2(parent)` and the right child when
`prec2(right) <= prec2(parent)`. Digits need no parentheses because their
precedence is higher than every supported operator.

Thus `123*+` writes `1+2*3`, `12+3*` writes `(1+2)*3`, and `123--`
writes `1-(2-3)`. The right-side equality rule preserves the tree's grouping
under left associativity, including cases such as `1+(2+3)`.

`write_char(c)` writes at `infix_pos` and advances it. `write_infix(root)`
resets `infix_pos = 0`, calls the helper, then appends `'\0'`. Writing
`1+2*3` places the terminator at index 5 and ends with `infix_pos == 6`.
Repeated complete writes restart at zero; child calls share the cursor.
A negative root produces an empty string, but a malformed operator with
missing children is still unsafe because the helper reads child data.

## Optional reconstruction exercise

The general slides' separate tree has preorder `ABDECFG`, inorder
`DBEAFCG`, and postorder `DEBFGCA`. Root `A` splits inorder into `DBE`
and `FCG`; their sizes select preorder segments `BDE` and `CFG`.
Repeating gives `B` with children `D, E` and `C` with children `F, G`.
Distinct labels make the split unambiguous. This reconstruction is not
implemented in the lab and is separate from its four core steps.

## Limits and costs

Use nonempty valid postfix of at most seven single-character tokens in
`postfix[8]`, with digits and binary `+ - * / %`, without spaces. The
builder does not validate grammar, operand counts, supported operators,
or bounds. The writer assumes valid expression-node shapes. `infix[20]`
provides room for the grouping parentheses in this input range; for example,
`1+(2+(3+4))` uses twelve cells including its terminator. No capacity checks
are implemented. A ten-node chain plus an empty-child sentinel exceeds
`stack[10]` during iterative traversal.

Traversal and writing take linear time in reachable nodes; construction
takes linear time in tokens. Recursive frames and used iterative path
entries require `O(h + 1)` space for height `h` edges. Progress reserves
one entry per node slot, separately from the path stack.
