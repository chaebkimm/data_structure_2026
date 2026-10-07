# Stage B — Representation Reveal: Indices, Visits, and Saved Progress

The implementation is [`lab.c`](lab.c), with explanations and code in the
[textbook](textbook.md). The lesson order follows [the slides](ppt_material.md).

## Follow and visit

`nodes[10]` stores characters and integer child indices; `-1` is absent.
`alphabet_init()` sets `nodes_size` to 10. `tree_connect()` returns root
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

| Position | Order | Assignment sequence | Final value |
| --- | --- | --- | --- |
| Before children | Preorder | `F A B D E C G` | `G` |
| Between children | Inorder | `D B E A C F G` | `G` |
| After children | Postorder | `D E B C A G F` | `F` |

The globals retain only final values. `tree_traversal(i)` returns when
`i < 0`; each leaf calls both absent children. At `D`, four real-node
calls are active along `F → A → B → D`, with one additional frame while
an empty-child call is active.

## Resume with an explicit stack

`tree_traversal_with_stack()` pushes the root and repeatedly processes the
current top. `progress[i]++` records where that node will resume:

| Old progress | Visit | Action |
| --- | --- | --- |
| 0 | Preorder | Push left child |
| 1 | Inorder | Push right child |
| 2 | Postorder | Pop current node |

A top entry of `-1` is popped without reading its progress. Thus a leaf
pushes and removes two empty-child entries before its own removal. The
stack holds the unfinished path. Reached nodes finish with progress 3;
the current wrapper does not reset progress and supports only one run.

## Reconstruct from two orders

The slides' separate tree has preorder `ABDECFG`, inorder `DBEAFCG`, and
postorder `DEBFGCA`. Root `A` splits inorder into `DBE` and `FCG`; their
sizes select preorder segments `BDE` and `CFG`. Repeating gives `B` with
children `D, E` and `C` with children `F, G`. Distinct labels make the
split unambiguous. This reconstruction is not implemented in the lab.

## Build from postfix

Prepare the initially empty shared `postfix` first. For `123*+`, stack
states after each token are `[0]`, `[0,1]`, `[0,1,2]`, `[0,3]`, and `[4]`.
Each operator pops right then left and pushes its own index. The builder
returns the final root by popping it: root 4, `nodes_size == 5`,
`top == -1`. Peak stack usage is three. The nodes replace the alphabet
tree; construction stores digit characters and does not calculate values.

## Write once; extend grouping later

`_write_infix()` writes left expression, operator, right expression without
parentheses. `write_infix()` appends `'\0'` but does not reset `infix_pos`.
For `123*+`, it writes `1+2*3` and finishes at position 6. For `12+3*`,
it also writes `1+2*3`, losing the intended grouping `(1+2)*3`.

The slides' extension adds parentheses around operator children when
parent precedence is greater on the left, or greater than or equal on the
right. Chapter 4's `prec()` returns 0 for digits; exclude them using
`is_digit()`. Reset the position before repeated complete writes, never
inside child calls. These changes are exercises, not current behavior.

## Limits and costs

Valid nonempty input consists of up to seven single-character tokens in
`postfix[8]`, using digits and binary `+ - * / %`, without spaces. The
builder assumes valid input and the writer assumes a nonempty expression
tree. Neither checks bounds. The current writer fits the input limit;
the extension's `1+(2+(3+4))` needs twelve bytes including its terminator,
exceeding `infix[10]`. A ten-node chain plus an empty-child sentinel also
exceeds `stack[10]` during iterative traversal.

Traversal and writing take linear time in reachable nodes; construction
takes linear time in tokens. Recursive frames and used iterative path
entries require `O(h + 1)` space for height `h` edges. The progress array
reserves one entry per node slot, separately from the path stack.
