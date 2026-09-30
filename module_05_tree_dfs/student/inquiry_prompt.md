# Stage A — Initial Inquiry: Follow, Build, and Write a Tree

Use this tree from [`lab.c`](lab.c) without naming traversal methods yet.
Brackets show indices in `nodes[10]`; missing child links contain `-1`.
The other initialized entries, `H [7]`, `I [8]`, and `J [9]`, have no links
from this root.

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

## A. Follow the links

What is the root index? Which entries can be reached from it? Explain why
`size == 10` need not equal the number of entries reached. Does connecting
a child move it to another array slot?

## B. Change the moment of recording

Always finish the left branch before the right. Record a separate symbol
sequence for each rule: record the current node before either branch;
record it between the branches; record it after both branches.

If each recording action replaces the value of one variable, what remains
in that variable at the end? Does it contain the whole sequence?

## C. Remember unfinished work

While processing `D [3]`, which earlier calls are waiting? What work does
each still have to do? What should a parent do when its child index is `-1`?
Count the links and the active node calls along the deepest path.

## D. Build instead of calculate

Read `123*+` from left to right. Create one node per character at that
character's index, and keep completed subtree roots on a stack. How should
an operator join the latest two roots? Use `12-` to decide which pop must
become its left child and which must become its right child.

What does the stack store? How is that different from the value stack used
to calculate an expression in Chapter 4?

## E. Preserve the grouping

Draw the trees described by `123*+`, `12+3*`, and `123--`. Write each as an
expression with the operator between its operands. Where are parentheses
needed? For two equal-priority operators, does putting the nested operator
on the left have the same effect as putting it on the right?

## F. Write twice

Suppose one character array first contains a longer expression and then
receives a shorter one. What must happen to the next-write position before
writing, and how does a C string mark its new end? Why should a child call
continue at the current position?

## G. State the limits

The input is a well-formed, nonempty postfix expression with single digits
and binary `+`, `-`, `*`, `/`, or `%`, with no spaces. It must fit in
`post_eq[6]`, including `'\0'` (the null terminator).

How many input characters fit? How many operators can a valid expression
of that length contain? Use that limit to reason about the space needed for
tokens, parentheses, and the terminator in `infix[10]`. What would need to
be reconsidered if the input array grew?
