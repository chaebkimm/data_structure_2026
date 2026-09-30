# Stage A — Initial Inquiry: Linear Format

Use [`lab.c`](lab.c) without naming traversal methods yet. Its `nodes[10]`
array stores characters and integer child indices. Missing child links are
`-1`. The starting node is `F` at index 5. Its left child is `A` at index 0
and its right child is `G` at index 6. `A` has left child `B` at index 1 and
right child `C` at index 2. `B` has left child `D` at index 3 and right child
`E` at index 4. `C`, `D`, `E`, and `G` have no children. The initialized
entries `H`, `I`, and `J`, at indices 7, 8, and 9, have no links from this
root.

1. Identify the root index and all reachable entries. Explain why
   `size == 10` need not equal the reachable count. Does connecting a child
   move it to another array slot?
2. Always finish the left branch before the right. Write separate symbol
   sequences for recording the current node before either branch, between
   branches, and after both branches. If each recording replaces one
   variable, what remains at the end? Does it contain the whole sequence?
3. While processing `D` at index 3, list the waiting calls and the work each
   must resume. Explain what a parent does for a child index of `-1`.
   Count links and active node calls along the deepest path.
4. Read `123*+` left to right, creating each node at its input character's
   index. Keep completed subtree roots on a stack. Explain how an operator
   joins the latest two roots. Use `12-` to decide which child comes from
   each pop. State what the stack stores and how that differs from Chapter
   4's value stack for calculating an expression.
5. Describe the trees for `123*+`, `12+3*`, and `123--`. Write each with
   operators between operands and the necessary parentheses. Explain
   whether a nested operator of equal priority behaves the same on the
   left and on the right.
6. A character array receives a longer expression and then a shorter one.
   Explain what must happen to the next-write position before writing,
   how a C string marks its new end, and why a child call continues at the
   current position.
7. Inputs are well-formed, nonempty postfix expressions with single digits
   and binary `+`, `-`, `*`, `/`, or `%`, with no spaces. They must fit in
   `post_eq[6]`, including `'\0'`. Determine the maximum number of tokens
   and operators. Use those limits to reason about tokens, parentheses,
   and the terminator in `infix[10]`. Explain what must be reconsidered if
   the input array grows.
