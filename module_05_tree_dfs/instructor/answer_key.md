# Module 5 Answer Key

These answers correspond to [student/lab.c](../student/lab.c), the
[textbook](../student/textbook.md), and the current lecture inquiry
activities. They do not replace the separate legacy exercise contracts.

## Alphabet tree and visit positions

After `alphabet_init()`, ten nodes are initialized and `size == 10`.
After `tree_connect()`, the returned root is index 5 (`F`). Its left child
is `A [0]`, its right child is `G [6]`, `A` has children `B [1]` and
`C [2]`, and `B` has children `D [3]` and `E [4]`. Exactly seven nodes are
reachable. `H`, `I`, and `J` stay unconnected.

| Assignment | Complete assignment sequence | Final stored character |
| --- | --- | --- |
| `pre_data` before either child | `F A B D E C G` | `G` |
| `in_data` between child calls | `D B E A C F G` | `G` |
| `post_data` after both children | `D E B C A G F` | `F` |

On return from `D`, the call on `B` assigns `B` to `in_data`, visits `E`,
and finally assigns `B` to `post_data`. A leaf makes all three assignments
without another call. The globals contain only the latest values; the
function does not emit these sequences.

## Postfix construction

For the default input `123*+`, each token becomes the node at the same
index. Stack contents below are indices, bottom to top:

| Token | Child links of the new node | Stack | `top` | `size` |
| --- | --- | --- | ---: | ---: |
| `1` at 0 | `left = right = -1` | `[0]` | 0 | 1 |
| `2` at 1 | `left = right = -1` | `[0, 1]` | 1 | 2 |
| `3` at 2 | `left = right = -1` | `[0, 1, 2]` | 2 | 3 |
| `*` at 3 | Right 2, left 1 | `[0, 3]` | 1 | 4 |
| `+` at 4 | Right 3, left 0 | `[4]` | 0 | 5 |

The returned root is 4. The stack stores completed subtree roots, not
arithmetic values. Its maximum use is three entries. `size` counts created
nodes, whereas `top + 1` counts the roots currently waiting on the stack.

For `12-`, the first popped index is 1 (the digit `2`), so it must become
the right child. The second pop is index 0 (the digit `1`), the left child.
Reversing those assignments would construct `2-1`.

## Parentheses and the output wrapper

| Postfix | Expected infix | Reason | Final `pos` |
| --- | --- | --- | ---: |
| `123*+` | `1+2*3` | Right child has higher precedence | 6 |
| `12+3*` | `(1+2)*3` | Left child has lower precedence | 8 |
| `12-3-` | `1-2-3` | Equal precedence on the left follows left associativity | 6 |
| `123--` | `1-(2-3)` | Equal precedence on the right requires grouping | 8 |
| `123++` | `1+(2+3)` | Preserve the right subtree's grouping | 8 |
| `123/%` | `1%(2/3)` | Preserve the equal-precedence right subtree | 8 |
| `123//` | `1/(2/3)` | Preserve the right subtree's grouping | 8 |
| `12+` | `1+2` | Both children are digits | 4 |
| `7` | `7` | A digit is written directly | 2 |

These are formatting examples, not evaluation cases. `prec()` returns
1 for `+ -`, 2 for `* / %`, 3 for digits, and 0 for unsupported characters.
The left comparison is `prec(c) > prec(l_data)`; the right comparison is
`prec(c) >= prec(r_data)`. Child indices `l` and `r` are integers; child
symbols `l_data` and `r_data` are characters.

`start_write_infix()` resets `pos = 0`, calls the recursive writer, and
appends `'\0'`. For `123++` followed by `12+`, the first string is
`1+(2+3)` (terminator at index 7, final `pos == 8`) and the second is
`1+2` (terminator at index 3, final `pos == 4`). The new terminator excludes
the old suffix. Resetting in a child call would overwrite the partially written
expression. Final `pos` counts every written byte including the terminator,
so it is one greater than the visible string length.

For the chapter guide's final check, `123--` creates node 3 with left 1
and right 2, then node 4 with left 0 and right 3. The returned root is 4;
the result is `1-(2-3)`, and final `pos == 8`.

## Demo output

Run `make lecture` from `module_05_tree_dfs/code` using
[the lecture driver](../code/lecture/lab_demo.c):

```text
Last visits: G G F
123*+ -> 1+2*3
12+3* -> (1+2)*3
123-- -> 1-(2-3)
12+ -> 1+2
```

The first line reports the final values of the visit globals. It is not
three complete traversal sequences. Rebuilding an expression reuses the
node array, replacing the previous tree.

## Preconditions and efficiency

The builder assumes a nonempty, well-formed postfix expression using
single digits and binary `+ - * / %`, with at most five tokens and a
terminator in `post_eq[6]`. Each operator needs two available roots and
exactly one root must remain at completion. There are no spaces, unary
operators, or multidigit numbers. The implementation does not validate
these conditions. A fallback precedence of 0 does not validate a token.

The writer requires a valid expression tree and sufficient output space.
The alphabet tree is not an expression tree. None of the recursive
routines checks for invalid indices or cycles, and `-1` is not an accepted
root argument.

At most five valid tokens contain at most two binary operators. Only one
operator can be another operator's child, allowing at most one pair of
parentheses. Five tokens plus two parentheses plus `'\0'` use at most
eight bytes, so `infix[10]` fits the current input limit. A larger input
or manually built expression needs a new capacity argument.

Construction takes `O(n)` time for `n` tokens. Traversal and formatting
take `O(r)` time for `r` reachable nodes. With height `h` measured in
edges, recursive call space is `O(h + 1)`; the alphabet tree has a longest
path of four nodes and three edges. A generalized postfix builder can use
`O(n)` stack entries, though this lab reserves exactly ten. Tree height,
not the total number of allocated slots, determines simultaneous node
calls.

## Interpreting student evidence

Accept a diagram, table, linear state log, or oral explanation that
identifies the same links, waiting work, visit positions, and output
decisions. Look for a preserved prediction followed by a revision tied to
an actual source statement. Do not require pointer copy independence,
numeric evaluation, rollback, or legacy autopsy outputs as evidence for
this lecture.
