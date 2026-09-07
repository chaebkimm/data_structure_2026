# Lab — Copy, Print, and Evaluate an Expression Tree

## Goal

Implement three depth-first operations for this tree:

```text
        *
       / \
      +   2
     / \
    3   5
```

Its printed expression is `(3+5)*2`. Its value is `16`.

## Representation

```c
typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node nodes[TREE_DFS_POOL_CAPACITY];
    size_t used;
} NodePool;
```

A digit must be a leaf. An operator must have two children. This module accepts
only single-digit operands, `+`, and `*`.

## TODO 1 — Preorder copy

Create the current copy before attaching copied children. A `NULL` subtree
copies to `NULL`. If the pool fills, restore its old `used` value and do not
change `*out_copy`.

## TODO 2 — Inorder printing

Write the left expression, current symbol, and right expression. Add
parentheses when omitting them would change the tree's grouping. Never write
past `output_capacity`; return `TREE_DFS_OUTPUT_TOO_SMALL` instead.

## TODO 3 — Postorder evaluation

Return a digit's numeric value. For an operator, evaluate both children before
applying the operator. Reject invalid shapes and preserve `*out_value` on
failure.

## Evidence

Run the core tests, add three focused tests, and record:

1. the creation order of the copied nodes;
2. the exact formatted expression;
3. the order in which values reach the evaluator; and
4. one failure case whose caller-owned state remains unchanged.
