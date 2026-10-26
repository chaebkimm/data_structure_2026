# Stage E — Trace and Test Indexed AVL Insertion

## What changes when a search tree leans?

An ordered tree narrows a search by choosing one child at each visited
node. Inserting sorted labels into an ordinary binary search tree can
leave only one useful child at every step. The supplied [lab.c](lab.c)
keeps the labels ordered and repairs the shape during insertion.

Use the complete source as supplied. Your work is to predict its states,
trace each repair, and add original assertion tests. The baseline, search
counter, and independent validator are provided by test drivers. All work
forms one Week 12 submission; there are no required implementation TODOs.

## Which values are labels and which are links?

Module 2 supplies `nodes[10]`, with `char data` and integer `left`/`right`
links. IDs are `0..9`; `-1` means an empty link or empty root.
`alphabet_init()` initializes A through J and all empty links. It sets
`nodes_size` to 10, which does not count inserted records.

`height[id]` stores edge height separately: missing subtree `-1`, leaf `0`.
Balance is left height minus right height. After each insertion every
reachable node must have the correct stored height and balance in `[-1,1]`.

Supply a fresh ID with both child links `-1`, then retain the returned root:

```c
alphabet_init();
int root = -1;
root = _add(root, 2);
root = _add(root, 0);
root = _add(root, 1);
```

This inserts C, A, B and finishes at ID 1, label B. `_add` takes an ID,
not a label or a request to allocate memory. Use each ID once per build,
stay within ten slots, and start with a valid AVL subtree and heights.
There is no rejected-eleventh-insertion result to test.

Different IDs may hold equal labels. `<=` routes a new equal label left,
but a later rotation can place an equal label on the right. Check a
nondecreasing inorder sequence and preserve all inserted IDs.

## How do we run the actual source?

From the repository root:

```sh
make -C module_12_bst_avl/code lab-compile core student-tests comparison
```

In the extracted standalone student release, run
`make -C code lab-compile core student-tests comparison` from its root.
The archive bundles the same Module 2 source under its original include path.

From `module_12_bst_avl/code` in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Comparison
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

Read [code/README.md](../code/README.md) for standalone compiler commands.
The lab has no `main`; compile one driver, which includes the lab once.
Keep the repository-root include path for the Module 2 dependency. Record
compiler warnings and sanitizer output. Module 2 currently contributes
warnings about older declarations, a character conversion, and an unused
local; preserve those results with your evidence.

## 1. Which links and heights change in each repair?

Use A=0, B=1, C=2. Predict before executing:

| Case | Label order | ID order |
| --- | --- | --- |
| LL | C, B, A | 2, 1, 0 |
| RR | A, B, C | 0, 1, 2 |
| LR | C, A, B | 2, 0, 1 |
| RL | A, C, B | 0, 2, 1 |

Record `i`, `l`, `r`, the relevant grandchildren, balance, returned root,
and changed child links. All four builds must end with root ID 1, left ID
0, right ID 2, heights `1,0,0`, and inorder A, B, C.

Explain why `l = nodes[i].left = _add(l,new_node)` updates both destinations.
Explain why a caller must use the return value even when no rotation occurs.

The `rotate_*` helpers only change links. `_add` refreshes heights after
the links have changed, in these orders:

```text
LL: i, l        RR: i, r
LR: i, l, lr    RL: i, r, rl
```

The first two updates of a double repair are independent; its new root
must be last. Do not reuse old child lists for the new shape.

Add an original regression with a nonempty transferred subtree. For
example, F,D,G,B,E,A causes an LL repair that moves E to `F.left`.
Predict the full resulting links and heights before running it. Verify
that every inserted ID remains reachable exactly once.

## 2. How much search work does the repair save?

Build each seven-label order twice, resetting between the ordinary BST
and AVL runs:

```text
ascending:  A B C D E F G
descending: G F E D C B A
mixed:      D B F A C E G
```

The driver support uses the same `nodes` representation for the unbalanced
baseline. It measures actual height from links rather than trusting the
baseline's unused cached heights. Count one logical comparison for each
visited record, including a match, and none for the terminal `-1` link.

| Order | Present / missing | BST height | BST comparisons per probe | AVL height | AVL comparisons per probe |
| --- | --- | ---: | ---: | ---: | ---: |
| ascending | G / H | 6 | 7 | 2 | 3 |
| descending | A / @ | 6 | 7 | 2 | 3 |
| mixed | G / H | 2 | 3 | 2 | 3 |

Every listed AVL build finishes with D at ID 3 above B and F. Record the
visited labels for one present and one missing search. Compare the driver
output with that independent trace; do not just copy its numbers.

## 3. What must stay true with duplicates and ten slots?

Extend the three numbered groups in
`code/tests/test_lab_student.c`:

1. **Rotations and transferred subtrees:** exact root, links, stored heights,
   sorted inorder, and preservation of a nonempty middle subtree.
2. **Measurements:** ascending, descending, and mixed builds, independently
   predicted heights and visited-label search counts.
3. **Duplicates and valid boundaries:** empty/singleton states, different
   IDs with equal labels, all ten IDs, and reset/rebuild evidence.

State each original claim before its assertions. The supplied checks are
smoke examples. Passing them alone is not original evidence.

`tests/lab_test_support.h` supplies `reset_lab`, `insert_lab`,
`assert_lab_tree`, `assert_lab_shape`, `build_lab_order`,
`baseline_add`, and `search_comparisons`. These are driver helpers, not
source operations. `assert_lab_tree` checks the exact inserted-ID set,
no cycles/shared children, nondecreasing inorder, exact stored heights,
and AVL balance. It traverses links independently of the cached heights.
`build_lab_order` resets before loading an order. `insert_lab` checks
fresh-ID preconditions before calling `_add`.

Never use an invalid ID or reinsert a linked ID as a supposed rejection
test. The lab has no guards for those calls. Rebuild from detached nodes
when changing labels or starting another order.

## Which costs belong to the algorithm?

A repair changes a fixed number of links and heights. It costs `O(1)`.
Insertion visits one downward path and returns through the same frames:
`O(h+1)` time and active call space for height `h`. AVL keeps that height
logarithmic in a generalized node count `n`; sorted plain-BST insertion
can create height `n-1`. The full driver validator visits every node in
`O(n)` time. Keep that diagnostic scan out of insertion/search counts.
The actual source reserves two fixed ten-slot arrays, not dynamic nodes.

Sorted input can increase plain-BST work through its shape. Distinguish
that algorithmic-complexity problem from invalid memory access and from
exhausting a finite resource. AVL balance does not validate external input.
Compare ordered-tree search with the Heap's parent/child priority rule
and the Hash Table's bucket-based exact lookup.

## What goes into the submission?

Submit the three original test groups and output, four canonical traces,
one nonempty transferred-subtree trace, the exact seven-label comparison,
duplicate and ten-slot evidence, and a completed
[evidence record](evidence_template.md). Include one diagnosis from the
[rotation autopsy](tree_rotation_autopsy.md), commands and warning/sanitizer
results, cost reasoning, and the Heap/Hash/BST/AVL contrast.

The older 64-node pointer library remains an optional reference. Its
allocation failures, duplicate rejection, iterative destruction, and TODO
clusters are not requirements of this lab.
