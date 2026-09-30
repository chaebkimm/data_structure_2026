# Chapter 5. Depth-First Traversal and Expression Trees

## Starting Question

> After a child call finishes, what work remains for the node that called it?

**Expected answer:** The caller resumes where it paused. Depending on the
visit position, it may still visit itself, process its right subtree, or
finish its final visit. Preserve students' first predictions before naming
the traversal orders.

## Why We Need This

Chapter 2 introduced child links stored as array indices. Chapter 4 used a
stack to remember waiting values. The current [lab.c](../module_05_tree_dfs/student/lab.c)
uses recursive calls to follow a tree and a separate explicit stack of
indices to build an expression tree from postfix notation.

The [textbook](../module_05_tree_dfs/student/textbook.md) develops three visit
positions, then asks how inorder output can preserve an expression's
grouping. The lab builds and formats expressions; it does not evaluate or
copy them.

## Board Walkthrough

Call `alphabet_init()` before `tree_connect()`. Draw the returned root at
index `5`, containing `F`:

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

`size` is 10 after initialization, but only seven nodes are reachable from
this root. `H`, `I`, and `J` remain unconnected. Links change; the nodes do
not move between array slots. Each missing child has index `-1`.

Reveal one call or return at a time. Keep each visit sequence separate from
the globals' current contents:

| Visit position | Assignment sequence | Final global value |
| --- | --- | --- |
| Before the left call | `F A B D E C G` | `pre_data == 'G'` |
| Between child calls | `D B E A C F G` | `in_data == 'G'` |
| After the right call | `D E B C A G F` | `post_data == 'F'` |

At `B`, pause after `D` returns. Ask what statement runs next before
revealing the assignment to `in_data`, the call on `E`, and the assignment
to `post_data`. The function assigns character codes to three `int`
globals; it does not print or retain the sequences.

Next trace `eq_tree()` on `123*+`. Stack entries are node indices, with the
top on the right:

| Token | New node links | Stack after the token |
| --- | --- | --- |
| `1` at 0 | Leaf | `[0]` |
| `2` at 1 | Leaf | `[0, 1]` |
| `3` at 2 | Leaf | `[0, 1, 2]` |
| `*` at 3 | Right 2, then left 1 | `[0, 3]` |
| `+` at 4 | Right 3, then left 0 | `[4]` |

The returned root is 4, `size` is 5, and `top` is 0. Contrast stored digit
characters with numeric values: the builder connects nodes without doing
arithmetic. Use `12-` to reason about why the first pop supplies the right
child.

Compare the infix results `1+2*3`, `(1+2)*3`, and `1-(2-3)`. The writer
visits left expression, operator, then right expression. It parenthesizes
the left child when `prec(c) > prec(l_data)` and the right child when
`prec(c) >= prec(r_data)`. The unequal comparisons preserve the grouping
of equal-precedence operators, which associate from left to right. The
child indices `l` and `r` are `int`; their stored symbols `l_data` and
`r_data` are `char`.

Finish by formatting a shorter expression. `start_write_infix(root)` resets
`pos`, calls the writer, and appends `'\0'`. For `1+2*3`, five visible
characters are written and `pos` ends at 6 because the terminator also
increments it. Child calls share the advancing position and must not reset
it.

## Common First Thoughts

- “The root is always node 0.”
- “`size == 10` means this traversal visits ten nodes.”
- “The three globals store three complete traversal sequences.”
- “The postfix stack stores the values of the expressions.”
- “The first popped root becomes the left child.”
- “Inorder symbols always preserve the expression's grouping.”
- “Equal-precedence children use the same parentheses rule on both sides.”
- “Resetting `pos` is enough to finish a shorter output string.”
- “An input assumption means the function checks that input.”

## Neutral Questions

- Which indices can be reached by following links from the returned root?
- Which statement executes after the call on `D` returns?
- What information remains in each global when all calls finish?
- What does each entry in the construction stack represent?
- For `12-`, which operand belongs on each side of the operator?
- What grouping does the unparenthesized expression `1-2-3` describe?
- After formatting a shorter expression, which byte marks its end?
- Which source statements, if any, reject a malformed postfix expression?

## Vocabulary Rules

**Words we can use:** Array, character, index, count, binary tree, root,
child, leaf, subtree, height, recursion, stack, LIFO, postfix, infix,
operand, operator, precedence, associativity, and null terminator.

**Names developed in this chapter:** Traversal, visit, depth-first search,
preorder, inorder, postorder, call stack, subtree root, and invariant.
Distinguish an assignment sequence from the final stored value, and the
runtime call stack from `eq_tree()`'s local array stack.

**Deferred or optional:** The separate
[iterative traversal example](../module_05_tree_dfs/code/lecture/iterative_traversals.c)
uses pointers and explicit traversal stacks. Allocation, copy/evaluation
APIs, failure rollback, and the existing legacy exercise package are not
requirements of this lecture. Graph cycle detection is developed later.

## Scope and Evidence

Core input is a nonempty, well-formed postfix expression with single-digit
operands and binary `+ - * / %`, no spaces or unary operators, and at most
five tokens plus the terminator in `post_eq[6]`. The builder relies on these
conditions. It performs no malformed-input or capacity checks.

With this limit, at most one pair of parentheses is added: five tokens,
two parentheses, and `'\0'` need at most eight bytes of `infix[10]`.
Expanding input or supplying a larger manually built expression requires
reconsidering that capacity. The alphabet tree must not be passed to the
expression writer.

Use the [lecture driver](../module_05_tree_dfs/code/lecture/lab_demo.c) with
`make lecture` from `module_05_tree_dfs/code`. Students first predict the
visits, stack states, and formatted text, then compare them with traces and
the demo. Standard and linear activities require the same reasoning.

For `r` reachable nodes, traversal and formatting take `O(r)` time. With
height `h` measured in edges, recursion uses `O(h + 1)` active calls.
Construction takes `O(n)` time for `n` input tokens; its explicit stack can
use `O(n)` entries in a generalized version. Keep the full week's lesson,
practice, and checks within 180 minutes; the
[lesson plan](../module_05_tree_dfs/instructor/lesson_plan.md) allocates 160.

## Final Check

> For postfix `123--`, how are the children connected, what text is written,
> and what does `pos` count when formatting finishes?

**Minimum answer:** The `-` at index 3 connects left 1 (`2`) and right 2
(`3`). The `-` at index 4 connects left 0 (`1`) and right 3. The right child
has equal precedence, so the text is `1-(2-3)`. The wrapper terminates the
seven-character string, leaving `pos == 8`.
