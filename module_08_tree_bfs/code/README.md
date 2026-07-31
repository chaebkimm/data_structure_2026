# Module 8 C Code

This package performs breadth-first work on small synthetic binary trees.
**Breadth-first** means nearer depths are processed before deeper depths. The
supplied `TreeWorkQueue` stores a node pointer together with its depth.

The Queue has a caller-selected active limit from 0 through 64. It uses a
fixed internal array, requests no memory, and owns no tree nodes. The BFS
functions enqueue a node's left child before its right child. A shallowest
search checks a node when it is removed, so the first match has the least
depth and equal-depth ties follow that left-first order.

## What students complete

The starter contains exactly three implementation tasks:

1. `tree_level_order`;
2. `tree_find_shallowest`; and
3. `tree_height_bfs`.

The typed Queue, node constructor, strict-BST insertion helper, postorder
cleanup, and status-name function are supplied.

## Important contracts

- `TREE_BFS_MAX_NODES` is 64.
- A `NULL` root is a valid empty tree.
- Empty level order succeeds with zero visits.
- Empty search returns `TREE_BFS_NOT_FOUND`.
- Edge height is `-1` for an empty tree and `0` for one node.
- A Queue limit above 64 returns `TREE_BFS_LIMIT`.
- A nonempty tree with Queue limit zero returns `TREE_BFS_LIMIT`.
- Reaching a 65th node returns `TREE_BFS_LIMIT`.
- Every failed operation preserves its caller-provided output.
- Traversal never changes or owns the input tree.

The input must be a valid tree: child links are acyclic, and no node is
shared by two parents. Repeated keys are allowed in general traversal
fixtures. Only `tree_bst_insert` enforces unique, strictly ordered keys.

The Queue's peak pending count is not always identical to one level's width:
during a transition it may contain nodes from two adjacent depths. For a
binary tree it is still `O(w)` auxiliary space, where `w` is maximum width.

## Targets

- `starter`: compiling scaffold whose core tests initially fail;
- `solution`: instructor reference;
- `-StudentTests`: three student-authored test categories;
- `-Extensions`: private boundary and representation checks; and
- `autopsy`: separate bounded child-order observation.

## PowerShell

From this `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script tries Clang, GCC, and then Microsoft C. Add `-Sanitize` when the
selected compiler supports run-time address and undefined-behavior checks.

## GNU Make

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is for Git Bash, MSYS2, WSL, Linux, or macOS. It defaults to
`gcc`; for example, use `make CC=clang solution-core` to select Clang.

## Ownership

The BFS functions borrow read-only node pointers. `TreeBfsOrder` copies key,
flag, and depth values. `TreeBfsMatch.node` remains a borrowed alias and is
valid only while the caller keeps that tree node alive.

Trees built with `tree_node_create` or `tree_bst_insert` own individually
allocated nodes. Release a complete valid owned tree with
`tree_destroy_postorder`. Do not pass local array nodes to that function.
