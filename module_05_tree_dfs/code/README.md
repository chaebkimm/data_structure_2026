# Module 5 C Package

The public contract is in `include/tree_dfs.h`. `support/tree_support.c`
provides the fixed node pool and node creation. Students implement three TODOs
in `starter/tree_dfs.c`: preorder copy, inorder formatting, and postorder
evaluation. `solution/tree_dfs.c` is the instructor reference.

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The starter is expected to compile and fail behavioral tests until completed.
Use `make clean` before switching implementations.
