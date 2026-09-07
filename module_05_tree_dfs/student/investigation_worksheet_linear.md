# Stage C — Investigation Worksheet: Linear Format

The root is `*`. Its left child is `+`; its right child is `2`. The `+` node
has children `3` and `5`.

1. Write the preorder symbol sequence.
2. Write the inorder symbol sequence and final parenthesized expression.
3. Write the postorder symbol sequence and returning value sequence.
4. Explain the `NULL` base case.
5. Explain what active calls remember while processing `3`.
6. Define `NodePool.used` and explain copy rollback after pool exhaustion.
7. Explain why caller outputs change only on success.
8. Design tests for copy independence, insufficient text capacity, and an
   operator missing one child.
9. Explain `O(n)` time and `O(h)` call space.
