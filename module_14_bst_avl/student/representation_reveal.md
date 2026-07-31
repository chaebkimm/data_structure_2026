# Stage B - Representation Reveal: From BST Ordering to AVL Balance

## 1. Name the structure

A **binary tree** is a branching structure in which each **node**, one
stored record, has at most two links. The first node is the **root**. A
linked node directly below another is its **child**. A **subtree** is one
node together with every node below it.

A **Binary Search Tree (BST)** stores a **key**, the value used for
ordering, in each node. This module requires strict, unique keys:

- every key in a node's left subtree is smaller; and
- every key in its right subtree is larger.

An equal-key insertion is rejected without changing the structure. The
teaching **implementation**, the C version used in this lab, holds at most
64 nodes.

An **inorder traversal** visits the left subtree, then the current node,
then the right subtree. Because of the BST invariant—an **invariant** is a
rule true for every valid state—inorder traversal produces increasing keys.

## 2. Measure shape

**Edge height** is the number of links on the longest downward route.
This course defines:

```text
height(NULL) = -1
height(leaf) = 0
```

A **memory address** identifies a storage location. A **pointer** is a C
value that stores an address; `NULL` means it stores no object's address. A
**leaf** has no children. A 15-node chain therefore has height 14.

The **balance factor** of a node is:

```text
left-subtree height - right-subtree height
```

An **AVL tree** is a BST whose every node has balance factor `-1`, `0`, or
`1`. It stores each node's height so repair does not repeatedly measure a
whole subtree.

## 3. Repair locally

A **rotation** is a local link rearrangement that changes shape while
preserving inorder key order. It must also preserve **ownership**, meaning
which structure is responsible for eventually releasing each allocation.
An **allocation** is storage reserved while a program runs.

There are four first-unbalanced patterns:

```text
LL: 30,20,10       RR: 10,20,30
LR: 30,10,20       RL: 10,30,20
```

LL uses one right rotation. RR uses one left rotation. LR first rotates
left at the left child, then right. RL first rotates right at the right
child, then left. All four end with root 20, left child 10, right child 30,
root height 1, and leaf heights 0.

The middle subtree matters. During a left rotation at `old_root`, the new
root's former left subtree becomes `old_root->right`. Saving that pointer
before overwriting a link prevents a leak—a **memory leak** is allocated
storage that the owner can no longer reach.

## 4. Connect to the C files

An **interface** is the declared set of operations available to other
files. Read the three supplied interfaces:

```text
code/include/tree_model.h
code/include/bst_baseline.h
code/include/avl_tree.h
```

The recursive BST baseline is supplied. **Recursive** means an operation
calls itself on a smaller part. The supplied validators check ordering,
stored heights, AVL balance, count, and pointer shape. A **validator** is
a diagnostic operation that reports whether representation rules hold.
The supplied destroy operation is iterative: a loop performs cleanup
without deep recursive calls.

Students implement only:

```text
code/starter/avl_rotations.c
code/starter/avl_tree.c
```

Full AVL deletion is an extension, not core work.

## 5. State the security claim precisely

**Algorithmic-complexity denial of service** means an attacker chooses
otherwise valid input that makes an operation perform much more work. A
plain BST built from ascending or descending keys becomes a height-14
chain at 15 nodes; a deepest or carefully chosen missing search makes 15
comparisons. The fixed mixed order has height 3 and needs 4 comparisons.
AVL insertion keeps all three 15-key orders at height 3, with root 8; a
deepest or suitable missing search needs 4 comparisons.

This slowdown is not **memory corruption**, which is an invalid read,
write, or release. It is also narrower than **resource exhaustion**, which
means memory, storage, or processing time is used up. AVL balance controls
this lookup-shape risk; it does not prove that the whole system is secure.

## 6. Contrast the Heap

A **binary Heap** keeps only a parent-before-children priority rule. It
does not place every smaller key on one side and every larger key on the
other, so it is good for repeatedly selecting one extreme but not arbitrary
key lookup. A BST has **whole-subtree search order**: every smaller key is
left and every larger key is right. AVL adds a shape bound to that BST
order.
