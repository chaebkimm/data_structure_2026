# Tree DFS Models

These diagrams show results for the current [`lab.c`](../student/lab.c).

## Array indices and recursive visits

```text
          F [5]                 root = 5, size = 10
         /     \               reachable nodes = 7
      A [0]   G [6]             unconnected: H [7], I [8], J [9]
      /   \
   B [1] C [2]                 absent child index = -1
   /   \
D [3] E [4]

pre_data assignments:   F A B D E C G    final: G
in_data assignments:    D B E A C F G    final: G
post_data assignments:  D E B C A G F    final: F
```

These are assignment traces. `tree_traversal()` only leaves the last value
in each global; it does not save or print these full sequences.

## Active node calls while visiting D

```text
F [5]  waiting for A; then assign in_data, visit G, assign post_data
└── A [0]  waiting for B; then assign in_data, visit C, assign post_data
    └── B [1]  waiting for D; then assign in_data, visit E, assign post_data
        └── D [3]  current leaf: three assignments, no child calls
```

The alphabet tree has height 3 edges and four active node calls at this
point. In general, a path of `h` edges has `h + 1` node calls, using
`O(h + 1)` space. Parents skip child links equal to `-1`; passing `-1` as a
root is unsupported. Traversal takes `O(n)` time for `n` reachable nodes.

## Constructing the default expression

```text
Input:  1       2         3           *        +
Index:  0       1         2           3        4
Stack: [0] -> [0,1] -> [0,1,2] -> [0,3] -> [4]
                               right=2    right=3
                               left=1     left=0

          + [4]             root = 4, size = 5, final top = 0
         /     \            stack entries are indices, not values
      1 [0]   * [3]
              /   \
           2 [1] 3 [2]
```

Each operator pops right first, left second, and pushes its own index.
The explicit stack reserves ten entries and uses at most three here.
Construction takes linear time in the number of input tokens. This tree's
height is 2 edges, so a deepest path has three active writer node calls.

## Parentheses preserve the expression tree

```text
postfix      infix           reason
123*+        1+2*3           right child has higher precedence
12+3*        (1+2)*3         parent > left child
12-3-        1-2-3           equal precedence on left groups correctly
123--        1-(2-3)         parent >= right child
123++        1+(2+3)         preserve grouping even when simplification is possible
```

`prec` assigns 1 to `+ -`, 2 to `* / %`, and 3 to digits. The left child
gets parentheses when parent precedence is `>` its own; the right child
gets them when the comparison is `>=`.

## The output wrapper

```text
start_write_infix(root)
    pos = 0
    write_infix(root)     child calls continue the same output
    infix[pos++] = '\0'

123++  ->  1 + ( 2 + 3 ) \0       final pos = 8
12+    ->  1 + 2 \0               final pos = 4
```

The new terminator ends the shorter string before any old suffix. The
wrapper contributes one additional, constant call frame.

Valid nonempty postfix input is limited by `post_eq[6]` to five tokens
(single digits and binary `+ - * / %`, no spaces). At most two operators
allow at most one parenthesized child expression: five tokens plus two
parentheses plus the terminator need eight characters. This fits
`infix[10]`; larger inputs require a fresh bound. The lab does not validate
input or check output capacity.
