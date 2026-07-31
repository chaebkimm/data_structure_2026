# Student Code Package

You will complete exactly three numbered `TODO` clusters:

1. in `starter/avl_rotations.c`, complete left and right rotations;
2. in `starter/avl_rotations.c`, complete four-case local rebalancing; and
3. in `starter/avl_tree.c`, complete recursive AVL insertion.

You will also complete exactly three test categories in
`tests/test_student.c`. Do not change public headers, supplied support, or
supplied core tests.

The three test categories are:

1. both rotations with a non-null middle subtree, then the four canonical
   cases and exact heights;
2. ascending, descending, and mixed 15-key insertion, validation, height,
   root, and comparison evidence; and
3. duplicate, full, and allocation-failure preservation, isolated validator
   faults, and leak-free cleanup.

## Words used in the code

A **binary search tree**, or **BST**, stores keys so every key in a node's
left subtree is smaller and every key in its right subtree is larger. A
**node** is one allocated record containing a key, two links, and a stored
height. A **subtree** is a node together with everything reachable below it.

An **AVL tree** is a BST that repairs its shape after insertion. A
**rotation** is a small reassignment of links that preserves sorted key
order. An **invariant** is a rule that every valid state must satisfy.

## Public contract

`BST_AVL_MAX_NODES` is 64. Keys are `int`; counts use `size_t`.

- A null link has edge-height `-1`.
- A leaf has edge-height `0`.
- A live AVL node stores its exact current edge-height. The plain BST
  baseline measures actual link height and does not require cached heights
  to remain current.
- Balance factor means left-subtree height minus right-subtree height.
- An AVL factor must be `-1`, `0`, or `1`.
- Keys are strict: duplicate insertion returns `TREE_DUPLICATE` without
  changing the tree.
- A full tree returns `TREE_FULL` without changing the tree.
- Allocation failure returns `TREE_ALLOCATION_FAILED` without changing the
  tree.
- Successful insertion adds exactly one node and increments size exactly
  once.
- Detected invalid arguments or state are rejected before mutation. Ordinary
  operations require a valid BST or AVL input and perform only shallow or
  search-route checks; use the explicit validators for a full diagnosis.
- Destruction releases every owned allocation and restores the canonical
  empty state.

A **status** is the named outcome returned by an operation. The supplied
status values are:

```text
TREE_OK
TREE_INVALID_ARGUMENT
TREE_FULL
TREE_DUPLICATE
TREE_ALLOCATION_FAILED
TREE_INVALID_STATE
```

The complete supplied baseline includes `tree_init`,
`bst_insert_baseline`, `bst_search`, `tree_validate_bst`, allocation helpers,
measurement helpers, and iterative destruction. The AVL interface includes
`avl_node_height`, `avl_balance_factor`, `avl_rotate_left`,
`avl_rotate_right`, `avl_rebalance`, `avl_insert`, and
`tree_validate_avl`.

## Rotation rules

Use these exact triples:

```text
LL: 30, 20, 10
RR: 10, 20, 30
LR: 30, 10, 20
RL: 10, 30, 20
```

All four cases finish as:

```text
      20
     /  \
   10    30
```

The root height is 1 and both leaf heights are 0. LL and RR each use one
rotation. LR and RL each use two. Update the lower node's height before the
new higher node's height.

## Required measurement experiment

Insert these exact orders:

```text
ascending:  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
descending: 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
mixed:      8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
```

Required plain-BST evidence:

| Order | Edge-height | Present search | Missing search |
|---|---:|---:|---:|
| ascending | 14 | 15 takes 15 comparisons | 16 takes 15 comparisons |
| descending | 14 | 1 takes 15 comparisons | 0 takes 15 comparisons |
| mixed | 3 | 15 takes 4 comparisons | 16 takes 4 comparisons |

Every AVL order must finish as the same perfect 15-node tree with root 8 and
edge-height 3. Each corresponding listed search takes 4 comparisons.

## Build and run

Run public core tests from this directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three test categories:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Add `-Sanitize` when the selected compiler supports sanitizers. A
**sanitizer** is a compiler runtime check that can report some memory and
undefined-behavior defects.

The isolated autopsy contains an intentional faulty left rotation. The
ordinary command defines `AUTOPSY_INSPECT_ONLY`, explains the defect, runs
the corrected bounded example, and exits safely:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Compiling the actual faulty branch requires both explicit permission and
sanitizers:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy -UnsafeAutopsy -Sanitize
```

That command prints the binary path but deliberately does not run it. Do not
run the binary outside an instructor-controlled disposable environment.
Never link either autopsy mode into a core or student-test build.

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
make autopsy-unsafe
```

`make autopsy` runs only the safe inspection branch.
`make autopsy-unsafe` adds `SANITIZER_FLAGS`, compiles the actual defect, and
prints its path without running it.

The starter is intentionally incomplete. A failed first core-test run is
expected. Fix the earliest failed requirement without weakening a test or
changing a supplied interface. Full AVL deletion is not part of this
package.
