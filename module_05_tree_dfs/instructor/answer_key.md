# Module 5 Answer Key

## Running example

- Preorder: `* + 3 5 2`
- Inorder: `3 + 5 * 2`; grouping requires `(3+5)*2`
- Postorder: `3 5 + 2 *`
- Evaluation trace: `3`, `5`, `8`, `2`, `16`

## Core explanations

Preorder creates the parent first, giving copied children a destination link.
Inorder places each operator between its operands. Parentheses preserve tree
grouping when precedence alone would produce a different tree. Postorder
produces both child values before applying the operator.

Every node is processed once, so the time is `O(n)`. Active calls hold one
root-to-current path, so extra space is `O(h)`. Balanced height is
`O(log n)`; a chain has height `O(n)`.

## Failure contracts

- Pool exhaustion restores `destination->used`.
- `*out_copy` changes only after the complete copy succeeds.
- Invalid printing clears the text candidate to an empty string.
- Failed evaluation preserves `*out_value`.

The autopsy crashes because it ignores `tree_node_create` returning
`TREE_DFS_POOL_FULL` and dereferences the unchanged `NULL` pointer.
