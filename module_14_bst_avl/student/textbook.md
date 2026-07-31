# Student Textbook - From BST Search to AVL Balance

## 1. Start with three keys

Insert 20, then 10, then 30.

```text
    20
   /  \
 10    30
```

A **binary tree** is a branching structure in which each **node**, one
stored record, has at most two links. The first node is the **root**. A
directly lower node is a **child**. A **subtree** is one node and
everything below it.

A **Binary Search Tree (BST)** orders a **key**, the value used for
searching. Every key in a left subtree is smaller than its node's key.
Every key in a right subtree is larger. This rule is the BST
**invariant**, meaning a rule true for every valid state. This module uses
unique keys; inserting an equal key is rejected without change.

Searching compares the requested key with the current key. Equal means
found. Smaller continues left; larger continues right. Reaching `NULL`
means absent. A **memory address** names a storage location. A **pointer**
stores an address in C; `NULL` stores none.

## 2. Why inorder is sorted

An **inorder traversal** visits the left subtree, current node, then right
subtree. For the example, it prints `10,20,30`. The ordering invariant
makes every left value smaller and every right value larger, so this
traversal is increasing.

The supplied BST **baseline**, a simple reference version used for
comparison, uses **recursion**, meaning an operation calls itself on a
smaller part. It is bounded to 64 nodes in this lab. A supplied iterative
destroy uses a loop to release nodes without deep recursive cleanup.

## 3. Arrival order changes shape

Insert 1 through 15 in ascending order. Every new key goes right. The
result is one chain. Descending order makes a left chain.

**Edge height** counts links on the longest downward route:

```text
height(NULL) = -1
height(leaf) = 0
```

A **leaf** has no children. Both 15-node chains have height 14. Finding the
deepest key compares 15 nodes. A deliberately difficult missing key also
compares 15.

Now insert:

```text
8,4,12,2,6,10,14,1,3,5,7,9,11,13,15
```

This shape has height 3. Its deepest and suitable missing searches need
four comparisons. The keys are identical; only arrival order changed the
work.

## 4. Add the AVL rule

The **balance factor** is:

```text
left-subtree height - right-subtree height
```

An **AVL tree** is a BST in which every node's balance factor is `-1`, `0`,
or `1`. Each node stores its height. After changing a child link, compute:

```text
1 + larger(left height, right height)
```

Stored heights make local repair efficient. A diagnostic
**validator**, an operation that checks structure rules, confirms ordering,
stored heights, balance factors, count, and no repeated or circular links.

## 5. Repair LL and RR

Insert `30,20,10`. Node 30 has factor `2`: the extra depth is left of its
left child. This is the LL case. A right **rotation**, a local link
rearrangement, makes 20 the root:

```text
    20
   /  \
 10    30
```

Insert `10,20,30`. Node 10 has factor `-2`: the extra depth is right of its
right child. This RR case uses a left rotation and reaches the same result.

Update the lower node's height first, then the new local root's height.
The final heights are 1 at 20 and 0 at both leaves.

## 6. Repair LR and RL

Insert `30,10,20`. The extra depth turns right inside the left side. This
LR case needs two steps: rotate left at 10, then right at 30.

Insert `10,30,20`. The extra depth turns left inside the right side. This
RL case rotates right at 30, then left at 10.

All four cases finish with root 20 and children 10 and 30. Inorder remains
`10,20,30`, so BST order is preserved.

## 7. Do not lose the middle subtree

Consider a left rotation at old root X with right child Y. Y may already
have a left subtree M. Save M first. Then make M the right subtree of X,
and make X the left child of Y.

```text
before: X ->right Y, Y ->left M
after:  Y ->left X, X ->right M
```

Every key in M is larger than X and smaller than Y, so its new position is
correct. This is also an **ownership** rule: the structure remains
responsible for releasing every allocated node. An **allocation** is
storage reserved while a program runs. Overwriting the only pointer to M
causes a **memory leak**, meaning owned storage can no longer be reached
and released.

The right rotation is the mirror image. Save the new root's middle
subtree, connect it to the old root, connect the old root below the new
root, then update heights.

## 8. Insert and rebalance

AVL insertion first follows ordinary BST search. If the key is absent and
fewer than 64 nodes exist, it creates one leaf. As recursive calls return,
each visited node updates its height and checks its factor.

Use the current factor and the factor of the child on the taller side:

- factor above `1`, left-child factor nonnegative: LL;
- factor below `-1`, right-child factor nonpositive: RR;
- factor above `1`, left-child factor negative: LR; and
- factor below `-1`, right-child factor positive: RL.

During a paper insertion trace, the inserted key can reveal the same case.
The supplied `avl_rebalance` operation receives only the current node, so
its implementation uses child factors.

A successful operation stores the repaired root and new count. A
duplicate, full structure, invalid argument, or failed allocation preserves
the earlier state. An **argument** is an input passed to an operation. Full
AVL deletion, meaning key removal, is later optional work because it can
require repeated repair.

For ascending, descending, and fixed mixed keys 1 through 15, the completed
AVL result has height 3 and root 8. A deepest or suitable missing search
uses four comparisons.

## 9. State cost and threat clearly

`O(1)`, read “constant time,” means work has a fixed bound. `O(h)` means
work can grow with structure height `h`. `O(n)` means it can grow with node
count `n`. Plain BST search and insertion are `O(h)`. A hostile order can
make `h=n-1`, giving `O(n)` work. AVL keeps height `O(log n)`, meaning it
grows with the number of times the size can be halved, so search and
insertion are `O(log n)`. Actual-height measurement and destroy remain
`O(n)`. `O(n^2)`, read “quadratic time,” means work can grow like `n`
multiplied by `n`. The supplied validator has that bound because each node
scans a list of already-seen pointers to detect sharing or a cycle.

**Algorithmic-complexity denial of service** occurs when attacker-chosen
valid input forces unexpectedly large work. A skewed BST demonstrates that
risk. It is not **memory corruption**, an invalid read, write, or release.
It also does not by itself prove **resource exhaustion**, which means
memory, storage, or processing time is used up.
AVL addresses one shape-based slowdown, not all security concerns.

## 10. Contrast the Heap

A binary Heap is a priority structure: its parent-before-children rule ranks
which record comes first. It quickly selects one minimum or maximum but does
not direct arbitrary key lookup.
A BST supplies whole-subtree search order: every smaller key is left and
every larger key is right. An AVL tree preserves that order and also
limits height.
