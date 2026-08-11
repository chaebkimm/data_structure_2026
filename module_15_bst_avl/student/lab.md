# Stage E - C Lab: BST-to-AVL Synthesis

## Purpose

Measure how insertion order changes a plain Binary Search Tree (BST), then
implement AVL rotations, rebalancing, and insertion. A BST places every
smaller key in the left subtree and every larger key in the right subtree.
An AVL tree preserves that rule while limiting the difference between
left and right subtree heights.

All keys and threat examples are synthetic. Do not connect this lab to
live accounts, devices, files, logs, or networks.

## Locked contract

Read these supplied interfaces before editing:

```text
code/include/tree_model.h
code/include/bst_baseline.h
code/include/avl_tree.h
```

The structure owns at most `BST_AVL_MAX_NODES`, exactly 64, separately
allocated `TreeNode` records. Keys are unique integers. Equal-key insertion
returns `TREE_DUPLICATE` without changing state.

Edge height uses:

```text
height(NULL) = -1
height(leaf) = 0
balance factor = left height - right height
```

AVL balance permits only `-1`, `0`, or `1`. A successful insertion updates
every affected stored height. Duplicate, full, allocation, invalid-argument,
and invalid-state failures preserve the complete earlier structure.

The recursive instructor BST baseline is supplied. So are
`tree_validate_bst`, `tree_validate_avl`, actual-height measurement, node
allocation helpers, and iterative destruction. The current complete
pointer-shape validator scans its seen-pointer list and may take `O(n^2)`;
keep that diagnostic cost separate from insertion cost.

## Files and build

Edit only:

```text
code/starter/avl_rotations.c
code/starter/avl_tree.c
code/tests/test_student.c
```

Use the warning-enabled commands in `code/README.md`. From the student
`code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users may run:

```text
make starter-core
make starter-student-tests
make autopsy
```

Preserve commands and output. Run the smallest relevant test after each
change.

## TODO 1 - Left and right rotations

Complete `avl_rotate_left` and `avl_rotate_right` in
`code/starter/avl_rotations.c`.

For a left rotation at old root X:

1. return X unchanged if X or its required right child is `NULL`;
2. save right child Y;
3. save Y's left subtree M;
4. set `X->right` to M;
5. set `Y->left` to X;
6. refresh X's height first;
7. refresh Y's height second; and
8. return Y.

The right rotation is the mirror image. A **middle subtree** is the subtree
between the two promoted keys. It must remain reachable and in its correct
ordering interval.

Checkpoints:

- LL `30,20,10` uses one right rotation;
- RR `10,20,30` uses one left rotation; and
- both finish at root 20, children 10 and 30, with heights `1,0,0`.

## TODO 2 - Refresh and rebalance

Complete `avl_rebalance` in `code/starter/avl_rotations.c`.

1. treat `NULL` as already repaired;
2. refresh the current node's stored height;
3. compute its balance factor;
4. if the factor is above 1, inspect the left child's factor:
   nonnegative means LL; negative means LR;
5. if the factor is below -1, inspect the right child's factor:
   nonpositive means RR; positive means RL;
6. perform the required single or double rotation; and
7. return the new local root.

The public operation receives no inserted key, so classification uses the
child's balance factor. An inserted-key shortcut can help a paper trace,
but it is not this interface's rule.

Checkpoints:

- LR `30,10,20` rotates left at 10, then right at 30;
- RL `10,30,20` rotates right at 30, then left at 10; and
- all four cases finish with inorder `10,20,30`, root 20, and valid stored
  heights.

## TODO 3 - Recursive AVL insertion

Complete `insert_recursive` in `code/starter/avl_tree.c`.

1. at a `NULL` link, request one leaf with `tree_node_create`;
2. on allocation failure, return the old `NULL` link and preserve the
   result **status**, the operation's named outcome;
3. for a smaller key, recurse into the left link;
4. reconnect the returned left link only after success;
5. for a larger key, do the symmetric right work;
6. return the old node unchanged after any failure;
7. on success, call `avl_rebalance` while returning upward; and
8. let the public operation commit the new root and size only after full
   success.

Duplicate and full checks already occur before allocation. Do not add full
AVL deletion; it is extension work.

Checkpoints for all three 15-key orders:

```text
final AVL root: 8
final AVL height: 3
deepest successful search: 4 comparisons
suitable missing search: 4 comparisons
```

The plain ascending and descending BSTs have height 14 and corresponding
deepest/missing searches of 15 comparisons. The plain fixed mixed BST has
height 3 and four comparisons.

## Exactly three student-authored test categories

Write exactly three numbered test functions. State each claim before its
**assertions**, checks that must be true.

1. **Four rotations and middle-subtree ownership:** cover LL, RR, LR, and
   RL exact roots, links, heights, inorder order, both validators, and a
   nonempty middle subtree that remains reachable.
2. **Ascending, descending, and mixed measurements:** build all three 15-key
   orders with the supplied BST baseline and AVL insertion; assert exact
   roots, heights, deepest/missing comparison counts, and root 8 for every
   AVL result.
3. **Preservation, boundary, and cleanup:** cover duplicate insertion,
   capacity 64, forced allocation failure, invalid argument/state, exact
   unchanged-state evidence, iterative destroy, and restoration of the
   live-node allocation count.

Empty/single-node states, helper-operation edge cases, malformed shapes
that repeat a node, and additional height corruption are covered by
supplied or private tests. Three renamed copies of one test setup earn
credit once.

## Safe autopsy

Complete `tree_rotation_autopsy.md` before and after the bounded autopsy.
The supplied `code/autopsy/faulty_left_rotation.c` first puts the wrong
value in the old root's right link, then overwrites the remaining link to a
nonempty middle subtree. The lost node is leaked; the demonstration does
not intentionally dereference invalid storage.

The default build only inspects or safely checks the source according to
`code/README.md`. Never hide the leak by removing the middle subtree from
the test setup. Repair the pointer order in your implementation and add a
**regression test**, which checks that a fixed defect does not return.

## Cost and security scope

One rotation changes a fixed number of links and fields, so it is `O(1)`.
Plain BST search/insertion is `O(h)`, where `h` is edge height, and becomes
`O(n)` when a node count `n` forms one chain. AVL keeps height `O(log n)`,
so search and insertion are `O(log n)`. Actual-height measurement and
iterative destruction are `O(n)`. The supplied complete validator may be
`O(n^2)` because it checks prior seen pointers.

Attacker-controlled sorted input can create
**algorithmic-complexity denial of service** in a plain BST: valid requests
force linear work. This is not **memory corruption**, an invalid memory
read, write, or release. It is also not proof of broad **resource
exhaustion**, which means memory, storage, processing time, or another
resource is used up.

AVL balance addresses this shape-based slowdown. It does not prove that
input is genuine, users have permission, the service stays reachable,
simultaneous operations are safe, saved data lasts, or the whole system is
secure.

## Heap contrast

A binary Heap keeps a parent-before-children priority rule. It is useful
for repeatedly selecting one extreme, but it does not place every smaller
key in one subtree and every larger key in the other. A BST supplies that
whole-subtree search order; AVL adds a height bound.

## Submission

Submit:

- all three TODO clusters;
- exactly three student-test categories;
- core and student-test output;
- all four canonical rotation traces;
- exact BST-versus-AVL measurements;
- validator and iterative-destroy evidence;
- a completed evidence record;
- the completed safe autopsy;
- warning/sanitizer evidence, or results from the instructor's automated
  test system;
- a Heap/BST/AVL contrast; and
- a concise threat statement with the required distinctions.
