# Copy-Failure Autopsy

`faulty_preorder.c` ignores the result of `tree_node_create`. When the pool is
full, the returned pointer remains `NULL`; the next child assignment
dereferences it. Diagnose the unchecked result, then explain why the correct
copy restores the pool's `used` count and preserves the caller's output.
