# Chapter 2. Organizing Data in a Hierarchy

## Starting Question

> How can a tree record which operation happens first, and how can the same
> function calculate the answer for every subtree?

**Expected answer:** The final `*` operation is the root. Its left child is
the `+` sub-expression and its right child is `2`; the `+` node links to `3`
on the left and `5` on the right. Each child field stores an address, and a
missing child is represented by `NULL`. No parent pointer is stored.

## Why We Need This

Chapter 1 stores an ordered list in one fixed array. Chapter 2 stores
relationships between separate local node variables. A generic binary-tree
node may have zero, one, or two children, with left and right remaining
distinct. In a completed binary expression tree, an operator has exactly two
operands and a numeric operand is a leaf.

The examples use portable C character constants such as `'*'` and `'+'`,
which have type `int`, in the same `data` field as small numeric operands.
The textbook now carries this model through recursive expression building
and evaluation. Number leaves hold values `0` through `9`; the parser
converts a digit character by subtracting `'0'`.

The existing lab still introduces structs, addresses, recursive search, and
field clearance using local nodes. The additional textbook program uses a
global array of 20 nodes. It requires no dynamic allocation and does not
change the lab's two required functions.

## Board Walkthrough

Use the textbook's five-node expression tree throughout the reveal:

```text
*
|-- left: +
|   |-- left: 3
|   `-- right: 5
`-- right: 2
```

Each label belongs to a distinct local `struct TreeNode` variable. Translate
the picture into `root.left = &plus;`, `plus.left = &three;`,
`plus.right = &five;`, and `root.right = &two;`. Initialize every field before
linking. The expression determines operand position; left and right are not
interchangeable in general.

Ask students to predict:

- the current-node, left-subtree, right-subtree search sequence:
  `'*', '+', 3, 5, 2`;
- the address returned when searching for `5`;
- which nodes change when the subtree rooted at `'+'` is cleared;
- why `root.left` must be set to `NULL` separately; and
- why the right operand `2` stays on the right and is otherwise unchanged.

After detachment, the links still form a valid generic binary tree, but the
root no longer represents a complete binary expression. Keep that semantic
expression rule separate from the structural rules enforced by the caller.

## From Text to a Tree

Contrast the manually grouped `(3 + 5) * 2` with the parser input `3+5*2`.
The first has `*` at the root and gives `16`. The second has `+` at the root,
with `3` on the left and the subtree `5*2` on the right, and gives `13`.
Use the second expression throughout the parser and evaluation trace.

Write one shared cursor under the input. The top call starts with minimum
precedence `1`. After reading `3` and consuming `+`, it calls the right
parser with minimum `2`. That call consumes `5*2`; its child call at minimum
`3` reads `2` and returns. Assemble `*`, then `+`, while the calls return.

Trace `8-3-2` next. The right call at minimum `2` must leave the second `-`
unconsumed. The outer call then attaches the completed `8-3` tree on the
left of the second subtraction. Ask why removing the `+ 1` from the minimum
would change the result. Use `8/4/2` to check the same reasoning for division.

The accepted language is single-digit operands joined by binary `+`, `-`,
`*`, and `/`, with no spaces or parentheses. Do not present the manually
grouped example as accepted parser input. The checked node helper rejects
exhausted capacity before indexing outside the array. A failed build resets
the used count and returns `NULL`; it does not preserve an earlier tree.
Every build reuses the same array.

## Recursion and a First DFS Trace

For `3+5*2`, record entry order `+, 3, *, 5, 2` separately from result order
`3, 5, 2, *, +`. The `+` call retains its own left result `3` while the `*`
call computes `10`. Only then can the root produce `13`.

Introduce recursion through the smaller-subtree problem and the number-leaf
base case. Explain depth-first search as finishing one branch before moving
to an unfinished branch. Name preorder for current-node-first search and
postorder for child-results-first evaluation. Keep the three-order
comparison and explicit-stack implementation for Chapter 5.

Use the two explicit child-call statements in `eval_tree` to show exactly
where the parent resumes. Each call has its own `left` and `right` locals.
The evaluator uses `double`, so `3/2` gives `1.5`, and rejects division by
zero without overwriting the caller's prior result. Do not equate an
operator's entry with applying its arithmetic.

## Core Invariant and Caller Duties

A valid nonempty tree has one root. Every other node appears in exactly one
child position. No child-link route returns to a node already on that route.
A node cannot be shared by two parents or used in both sides of one parent.

Every reachable node must be initialized and remain alive while its address
is used. The direct-link examples and recursive functions assume these
conditions; they do not validate arbitrary graphs. Construct the examples
from fresh, distinct node variables. Discuss malformed links with drawings
or the bounded autopsy, not unbounded recursive execution.

There is no packed-prefix rule: a missing left child does not require a
right child to move. One-child nodes are valid generic binary-tree states,
even though a completed binary expression cannot leave an operator with one
operand.

## Common First Thoughts

- “Left and right operands are interchangeable.” Subtraction and division
  show why their positions matter.
- “A binary tree always has zero or two children.” That is the completed
  expression example's semantic rule, not the generic representation rule.
- “The character `'*'` needs a different field.” A C character constant has
  type `int`; number leaves hold numeric values, and operator branches hold
  character constants. The parser converts `'5'` into `5` with `- '0'`.
- “The next operator always becomes the root immediately.” Its precedence
  determines which call consumes it and how far its right operand extends.
- “The right call may consume another equal-precedence operator.” Passing
  precedence plus one leaves that operator for the earlier call.
- “Every recursive call shares the same local answer variables.” Each call
  has separate locals; only the parser's reading position is shared through `q`.
- “Clearing a child also removes the parent's link.” The caller must detach it.
- “Clearing destroys the node variable.” Its fields reset; its storage remains live.
- “Zero means no node.” Zero is ordinary data; only a `NULL` link means no child.
- “The recursive functions reject shared nodes or cycles.” Valid structure is a caller precondition.

## Vocabulary Boundaries

**Already available:** C variables, functions, arrays, loops, conditions,
bounds, and invariants from Chapter 1.

**Introduce here:** hierarchy, expression-tree example, binary tree, node,
root, parent, child, left/right operand position, sibling, ancestor,
descendant, leaf, subtree, path, depth, height, address, pointer, `struct`,
`&`, `.`, `->`, `NULL`, character constants used as integer labels, digit
conversion, node lifetime, recursion, a stopping case, brief DFS, preorder
search, postorder evaluation, precedence, left associativity, parsing, a
shared `char **` reading position, and cascading clearance.

**Deferred:** multi-digit and parenthesized parsing, unary operators, typed
expression payloads, dynamic node allocation and release,
parent-pointer/root-comparison APIs, binary-search ordering, rotations, and
balance. Detailed preorder/inorder/postorder comparisons and explicit-stack
traversal belong to Module 5. A `1`/`0` success return and an output pointer
are explained locally for the textbook evaluator.

## Operation Summary

| Operation | Main idea | Worst-case work |
|---|---|---|
| Initialize a local node | Set data and both child links | Constant |
| Attach a fresh child | Check the known side, then assign its address | Constant, under the caller preconditions |
| `tree_find` | Check current node, then left and right subtrees | Proportional to the number of searched nodes |
| `tree_clear` | Clear children before resetting the current node | Proportional to the selected subtree size |
| Detach a child | Set the selected parent link to `NULL` | Constant |
| `build_expression` | Consume characters and link one fresh node per character | Proportional to accepted input length |
| `eval_tree` | Get both child results, then apply the operator | Proportional to expression-tree size |

Search and clearance can each use temporary call-stack space proportional
to tree height. Initialization, attachment, and detachment remain direct
operations. Only `tree_find` and `tree_clear` are library functions.

Evaluation also needs temporary call space proportional to height. With
only two precedence levels and no parentheses, parser calls nest at
minimum values `1`, `2`, and `3`; a long chain of equal-precedence operators
does not make its call depth grow with the tree height. The lecture program
is in `module_02_binary_tree/code/lecture/expression_tree.c`; its build and
run commands are in the textbook.

## Final Check

> What does `tree_clear(root.left)` change in the canonical expression tree,
> and what remains to be done?

**Minimum answer:** The `'+'`, `3`, and `5` nodes have data zero and both
links `NULL`. Their local variables still exist. `root.left` still contains
`&plus`, so the caller must assign `root.left = NULL;`. The right operand `2`
remains unchanged. The resulting links form a tree but no longer encode a
complete multiplication expression.

> Why can a missing-value search inspect every node?

**Minimum answer:** The `data` values are not search-ordered, so a comparison
cannot rule out either subtree.

> Why can two child links to the same node be wrong even without a cycle?

**Minimum answer:** A non-root node must appear in only one child position.
Clearing through one link would unexpectedly change the node seen through
the other link.

> Why does the parser build `3+5*2` with `+` at the root, and why is that
> operator evaluated last?

**Minimum answer:** The right parser at minimum `2` consumes `5*2` as one
subtree. The outer call attaches it below `+`. Evaluation then waits for
the left result `3` and the right result `10` before returning `13`.

> What does `char **q` share, and what remains separate between calls?

**Minimum answer:** It shares the cursor pointing at the next unread
character. Each parser call still has its own `node`, `parent`, and minimum
precedence. Each evaluator call has its own child results.
