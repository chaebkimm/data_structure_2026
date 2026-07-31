# Module 5 C Package

This package studies depth-first traversal of a small binary tree in C.
**Depth-first traversal** means following one branch as far as the chosen
rule requires before returning to another branch.

## Supplied and student-controlled code

The instructor supplies:

- `include/tree_dfs.h`: public tree types and function promises;
- `include/tree_node_stack.h`: the public typed Stack interface;
- `support/tree_support.c`: node construction and strict-BST insertion;
- `support/tree_node_stack.c`: a tested Stack of node pointers;
- complete recursive inorder and postorder functions in the starter;
- `tests/test_core.c`: visible required behavior;
- `tests/test_extension.c`: instructor-only boundary tests; and
- `autopsy/faulty_preorder.c`: an isolated faulty program.

Students edit only:

- `starter/tree_dfs.c`; and
- `tests/test_student.c`.

The starter TODOs are recursive preorder, iterative preorder, BST search, and
postorder destruction. `solution/tree_dfs.c` is the instructor reference.

## Build commands

From this `code` directory on Windows:

```powershell
# Expected to compile but fail until the starter TODOs are completed.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference checks.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-authored tests and isolated autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script chooses Clang, GCC, or Microsoft `cl` from `PATH`. With GNU Make:

```sh
make starter-core
make solution-core
make solution-extension
make starter-student-tests
make autopsy
```

Warning checks use C11 plus common high-value warnings. `-Sanitize` adds
memory and undefined-behavior checks where the selected compiler supports
them.

## Test-only controls

Core and extension builds define `TREE_DFS_TESTING`. That definition exposes:

- a one-shot node-allocation failure;
- a count of constructed nodes not yet released; and
- a one-shot node-Stack allocation failure.

These controls make rare failure paths repeatable. They are absent from
normal builds.
