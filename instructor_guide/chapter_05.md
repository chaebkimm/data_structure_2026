# Chapter 5. Traversing a Tree with a Stack

## Starting Question

> "After following a child link, what must we save to finish the remaining branches without recursion?"

**Expected Answer:** Save node addresses in an explicit stack. For delayed
visits, also remember whether the node's remaining subtree has finished.

## Why We Need This

Chapter 2 introduces recursion through expression-tree construction and
evaluation, with a brief DFS example. Chapter 4 supplies stack operations.
Chapter 5 makes the waiting work explicit and compares preorder, inorder,
and postorder with loops. All three traversal implementations are required
textbook content.

## Board Walkthrough

Use the expression `3+5*2` from Chapter 2 throughout the walkthrough.

```text
        +
       / \
      3   *
         / \
        5   2
```

Write stacks with the bottom on the left and the top on the right. Keep the
printed output separate from the waiting addresses.

| Traversal | Printed symbols | What the stack remembers |
| --- | --- | --- |
| Preorder | `+ 3 * 5 2` | Roots of subtrees that have not started. |
| Inorder | `3 + 5 * 2` | Nodes waiting to print after their left subtrees. |
| Postorder | `3 5 2 * +` | Nodes waiting for both subtrees to finish. |

Trace these decisions:

- Preorder: after printing `+`, push `*` and then `3`. The stack is `[*, 3]`,
  so `3` is next.
- Inorder: after printing `+`, the stack is empty but `current` points to
  `*`. The loop must continue.
- Postorder: after printing `5`, the stack is `[+, *]` and `last_visited`
  points to `5`. Keep `*` waiting and enter its right child `2`. After
  printing `2`, the right subtree is complete, so pop and print `*`.

The largest stack sizes are 2 for preorder, 2 for inorder, and 3 for
postorder. Each algorithm pushes and pops all five nodes once. Generalize to
`O(n)` work and at most `O(h + 1)` used stack entries. The sample reserves an
array of 100 pointers even when fewer entries are used.

## Common First Thoughts

- "Push the left child first to visit it first."
- "The traversal ends whenever the stack is empty."
- "Postorder can pop a parent as soon as the left subtree finishes."
- "Compare stored symbols to decide whether a right subtree has finished."
- "Removing recursion removes the need for extra memory."
- "Inorder symbols alone always recover the expression's grouping."

## Neutral Questions

- Which child is on top after the two preorder pushes?
- After inorder prints `+`, where does `current` point?
- What address must `last_visited` equal before postorder prints `*`?
- Can two different nodes store the same symbol?
- Why do `3+5*2` and `(3+5)*2` need different trees despite the same bare
  inorder symbol sequence?

## Vocabulary Rules

**Words we can use:** Binary tree, node, root, left and right child, subtree,
height, recursion, stopping case, expression tree, basic DFS, and stack.

**Names developed in this chapter:** Traversal, visit, explicit stack,
iterative traversal, preorder, inorder, postorder, and loop invariant.
Distinguish reaching a node from printing it.

**Scope:** Teach the three explicit-stack algorithms in
`module_05_tree_dfs/code/lecture/iterative_traversals.c`. Use preorder's
reversed child pushes, inorder's `current` pointer, and postorder's
`last_visited` pointer. The separate existing copy/print/evaluate lab retains
its recursive reference; it does not replace the textbook's loop-based
implementations. Graph visit history, allocation, and tree balancing are
outside this lesson.

## Final Check

> "In postorder, what happens immediately after printing `5`, and how does the algorithm know when it can print `*`?"

**Minimum Expected Answer:** `*` stays on the stack while traversal enters
its right child `2`. After `2` is printed, `last_visited` equals `*`'s right
child address. Both subtrees are finished, so the algorithm pops and prints
`*`. The stack stores the work that recursive calls remembered in Chapter 2.
