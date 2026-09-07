# Representation Reveal — One Tree, Three Orders

Use the tree for `(3+5)*2`.

| Operation | Order | Trace |
|---|---|---|
| Copy | node, left, right | `* + 3 5 2` |
| Print | left, node, right | `3 + 5 * 2`, with parentheses around `3+5` |
| Evaluate | left, right, node | `3 5 + 2 *` |

Recursive calls remember the path from the root to the current node. The
`NULL` child is the stopping case. The maximum number of active calls depends
on tree height, so traversal uses `O(h)` call space.

The node pool owns the copied nodes. Copying succeeds only when the complete
copy fits. A failed attempt rewinds the pool to its starting position.
