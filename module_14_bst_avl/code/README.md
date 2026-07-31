# Module 14 C Package

This package starts with an ordinary Binary Search Tree (BST), measures how
insertion order can make it tall, and then adds AVL rotations to keep the
same keys balanced.

A **BST** is a binary tree whose keys are strictly ordered: every key in a
node's left subtree is smaller, and every key in its right subtree is
larger. An **AVL tree** is a BST that also keeps the heights of its two child
subtrees within one.

## Representation contract

`Tree` owns at most 64 separately allocated nodes. Keys are unique. `root`
is `NULL` exactly when `size` is zero.

`TreeNode.height` uses edge height:

```text
NULL: -1
leaf:  0
```

The BST baseline deliberately ignores stored heights after a leaf is
created. `tree_actual_height` recursively measures links instead.

`tree_validate_bst` checks the complete bounded representation:

- root and size agree;
- no node is repeated, so cycles and shared nodes are rejected;
- whole left subtrees are strictly smaller and whole right subtrees are
  strictly larger; and
- the reachable count equals `size`.

It deliberately does not check cached heights. `tree_validate_avl` checks
all BST rules, every exact cached height, and every balance factor. A
**balance factor** is left height minus right height and must be `-1`, `0`,
or `1`.

The full validators are explicit diagnostics. Their bounded pointer-history
scan costs `O(n^2)` for at most 64 nodes. Ordinary insert and search require a
valid input tree and use shallow plus bounded search-path checks so they
remain `O(h)`, where `h` is actual height.

## Baseline and search evidence

`bst_insert_baseline` and `bst_search` are supplied recursive operations.
Search reports one comparison for each visited node.

For keys `1` through `15`:

```text
insertion order       BST height   target / miss       comparisons
ascending             14           15 / 16             15 / 15
descending            14            1 /  0             15 / 15
fixed mixed            3           15 / 16              4 /  4
```

The fixed mixed order is:

```text
8 4 12 2 6 10 14 1 3 5 7 9 11 13 15
```

AVL insertion produces the same perfect final tree for all three orders:
root `8`, height `3`, and four comparisons for each listed target or miss.
`bst_search` works for either tree because every AVL tree is also a BST.

## Rotations and recursive insertion

A rotation changes links without changing sorted key order. The left
rotation:

```text
    lower                 upper
       \                  /
       upper     ->     lower
       /                    \
    middle                 middle
```

must preserve `middle`. It refreshes the lower node's height before the new
upper node's height. Right rotation is the mirror image.

`avl_rebalance` handles four cases:

- LL: one right rotation;
- RR: one left rotation;
- LR: left rotation on the left child, then right rotation; and
- RL: right rotation on the right child, then left rotation.

The canonical three-key inputs `30,20,10`, `10,20,30`, `30,10,20`, and
`10,30,20` all finish with root `20`, children `10` and `30`, root height
`1`, and leaf heights `0`.

Recursive AVL insertion allocates only at a `NULL` link. It reconnects and
rebalances only after the recursive call succeeds. Duplicate, full, and
allocation failures therefore preserve every old link, height, and size.

The test-only allocation hook fails exactly the next real allocation once.
Duplicate and full checks occur first and do not consume it. The live-node
counter supports deterministic leak checks. `tree_destroy_iterative`
releases a valid owned shape without recursive cleanup calls.

## Student-controlled work

The starter has exactly three numbered task clusters:

1. left and right rotations;
2. four-case rebalance; and
3. recursive AVL insertion.

The student test template has exactly three categories: rotation structure,
height/comparison traces, and atomicity/validation/cleanup. The BST baseline,
full diagnostics, recursive actual-height measurement, allocator hooks, and
iterative destruction are supplied.

## Cost

For a valid tree of `n` nodes and actual height `h`:

- BST or AVL search: `O(h)`;
- baseline BST insertion: `O(h)`;
- one rotation: `O(1)`;
- AVL insertion: `O(h)`, which is `O(log n)` under the AVL invariant;
- recursive actual-height measurement: `O(n)`;
- iterative destruction: `O(n)` time with a fixed 64-pointer stack
  (`O(1)` under this course cap, or `O(n)` capacity if scaled); and
- full validation in this teaching implementation: `O(n^2)`.

## Build commands

The default build uses the completed reference solution:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The starter compiles, but tests fail until all three clusters are complete:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The ordinary autopsy target runs only its safe inspection branch:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

`-Target autopsy -UnsafeAutopsy -Sanitize` compiles, but never runs, the
actual isolated middle-subtree leak.

With GNU Make:

```sh
make
make solution-extension
make starter-compile
make autopsy
make autopsy-unsafe
```
