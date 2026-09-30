# Stage B — Representation Reveal: Indices, Visits, and Expressions

The implementation is [`lab.c`](lab.c); the full explanation is in the
[textbook](textbook.md).

## Array links and three visit positions

`struct TreeNode` stores `char data`, `int left`, and `int right`. Child
links select entries in `nodes[10]`; `-1` means absent. `alphabet_init()`
initializes all ten entries and sets `size` to 10. `tree_connect()` returns
root index 5 (`F`), with these links:

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

Only seven nodes are reachable. `H`, `I`, and `J` remain unconnected.
Assignments to child indices do not move nodes.

| Visit position in `tree_traversal` | Formal name | Assignment sequence |
| --- | --- | --- |
| `pre_data`, before either child | Preorder | `F A B D E C G` |
| `in_data`, between children | Inorder | `D B E A C F G` |
| `post_data`, after both children | Postorder | `D E B C A G F` |

The globals are overwritten on each visit. Their final contents are
`'G'`, `'G'`, and `'F'`; the function does not store or print whole sequences.
Trace the assignments or observe them with a debugger to see each order.

At `D`, the active node calls are `F → A → B → D`. Calls return to the
saved next step in their parent. The parent checks for `-1` before calling
a child; `tree_traversal(-1)` is not a supported empty-tree call. A leaf
still performs all three assignments.

## A stack of subtree roots

`eq_tree()` reads `post_eq = "123*+"`. A token at input index `i` becomes
`nodes[i]`; digit leaves have two `-1` child links. The local `stack[10]`
holds node indices, with its top on the right below.

| Token | Stack after processing | New child links |
| --- | --- | --- |
| `'1'` at 0 | `[0]` | Leaf |
| `'2'` at 1 | `[0, 1]` | Leaf |
| `'3'` at 2 | `[0, 1, 2]` | Leaf |
| `'*'` at 3 | `[0, 3]` | Left 1, right 2 |
| `'+'` at 4 | `[4]` | Left 0, right 3 |

Each operator pops its right root first and its left root second, then
pushes its own index. The final root is 4, `size` is 5, and `top` is 0.
`size` counts constructed nodes; `top + 1` counts currently stacked roots.
This constructs a tree; it does not calculate a value. Reusing `nodes`
replaces the earlier alphabet tree.

## Write the tree's grouping

`prec()` returns 1 for `+` and `-`, 2 for `*`, `/`, and `%`, and 3 for
digits. For an operator, `write_infix()` writes left subtree, operator,
right subtree. It surrounds a child expression with parentheses as follows:

| Side | Parentheses condition | Example |
| --- | --- | --- |
| Left | Parent precedence `>` child precedence | `12+3*` → `(1+2)*3` |
| Right | Parent precedence `>=` child precedence | `123--` → `1-(2-3)` |

Equal-precedence operators associate left to right. The asymmetric checks
preserve the tree's grouping: `12-3-` becomes `1-2-3`, but `123--` needs
right-side parentheses. Even `123++` becomes `1+(2+3)`; the writer does not
simplify expressions. The default `123*+` becomes `1+2*3`.

`start_write_infix(root)` resets `pos`, runs the recursive writer, then
appends `'\0'`. Child calls share the current next-write position. The
terminator prevents a shorter new result from retaining an old suffix.
After formatting `1+2*3`, `pos` is 6 because the wrapper increments it for
the terminator too.

## Limits and costs

The lab assumes a nonempty, well-formed postfix string of single digits
and binary `+`, `-`, `*`, `/`, or `%`, without spaces, fitting `post_eq[6]`.
The builder does not validate those conditions. The writer requires a
valid expression root; the alphabet tree is not input to it.

At most five tokens fit. A valid five-token binary expression has two
operators and at most one operator below another. Thus the writer adds at
most one pair of parentheses: five tokens, two parentheses, and a
terminator need eight characters, fitting `infix[10]`. A larger input or
manually built expression requires a new capacity analysis; the writer
does not check its output bounds.

For `n` reachable nodes, traversal and formatting take `O(n)` time. For
`t` postfix tokens, construction takes `O(t)` time. Height `h` counts edges,
so a deepest path has `h + 1` active node calls and uses `O(h + 1)` recursive
space. The alphabet tree's height is 3 and its peak is four node calls;
the default expression tree's height is 2 and its peak is three node calls.
The wrapper adds one constant frame to formatting. The explicit construction
stack reserves ten entries; it uses at most three for `123*+`. A builder
with capacities that grow with the input can need `O(t)` stack entries.
