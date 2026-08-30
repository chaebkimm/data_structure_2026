# Chapter 2. Organizing Data in a Hierarchy

## Starting Question

> How can local node variables represent the expression `(3 + 5) * 2` as a
> hierarchy with distinct left and right positions?

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

The example uses the portable C character constants `'*'` and `'+'`, which
have type `int`, in the same `data` field as the small numeric operands. This
is a simplified structural model, not a type-safe expression evaluator. The
lab introduces structs, addresses, pointers, and recursive processing; it
does not introduce allocated node storage or expression evaluation.

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
  type `int`; this chapter uses that simplified encoding without evaluating it.
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
`&`, `.`, `->`, `NULL`, character constants used as integer labels, node
lifetime, recursion, a stopping case, and cascading clearance.

**Deferred:** expression evaluation and typed expression payloads, node
allocation and release, parent-pointer/root-comparison APIs, status-code
interfaces, binary-search ordering, rotations, and balance. Formal DFS and
named traversal-order comparisons belong to Module 5.

## Operation Summary

| Operation | Main idea | Worst-case work |
|---|---|---|
| Initialize a local node | Set data and both child links | Constant |
| Attach a fresh child | Check the known side, then assign its address | Constant, under the caller preconditions |
| `tree_find` | Check current node, then left and right subtrees | Proportional to the number of searched nodes |
| `tree_clear` | Clear children before resetting the current node | Proportional to the selected subtree size |
| Detach a child | Set the selected parent link to `NULL` | Constant |

Search and clearance can each use temporary call-stack space proportional
to tree height. Initialization, attachment, and detachment remain direct
operations. Only `tree_find` and `tree_clear` are library functions.

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
