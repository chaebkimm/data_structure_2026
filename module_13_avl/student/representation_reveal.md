# Stage B — Representation Reveal: Ordered Nodes and AVL Repair

## 1. Give the placement rule a name

A lookup can skip one whole branch when every key in that branch lies on
the same side of the current key. A **key** is the value used for ordering.
A **binary search tree (BST)** keeps this rule in every subtree. A subtree
is a node together with all nodes reached below it.

The supplied [lab.c](lab.c) sends a new key left when it is smaller **or
equal**, and right when it is larger. Rotations can later put an equal
key on either side. The invariant for this lab is therefore:

- every key in the left subtree is less than or equal to the current key;
- every key in the right subtree is greater than or equal to it; and
- an inorder traversal produces a nondecreasing sequence, including repeats.

The seven-key experiments use distinct letters so their order is strictly
increasing. Equal letters belong to different nodes; inserting the same
node ID twice is outside the contract.

## 2. Reuse Module 2's records

The records already exist in a fixed array. The source includes
`module_02_binary_tree/student/lab.c`, which supplies:

```c
struct TreeNode {
    char data;
    int left;
    int right;
};
struct TreeNode nodes[10];
```

Each link is a node **index**, an integer position from 0 through 9.
`-1` means no child. The key is `nodes[i].data`; the index `i` is its
identity. A rotation changes links and the local root, not node identities
or key values. `alphabet_init()` prepares A through J with both links `-1`.
Its `nodes_size == 10` describes prepared records, not how many a selected
tree reaches. The caller separately tracks the IDs inserted into that tree.

## 3. Keep a short note about each subtree

Following one route is useful only when the route stays short. **Edge
height** counts links on a longest downward route. This lab defines
`get_height(-1) == -1`; a leaf has height 0. The separate `height[10]`
array holds each node's **stored height**, its saved edge height.

`set_height(i,l,r)` reads the two child heights and stores their maximum
plus one. The **balance factor** is left height minus right height.
An **AVL tree** keeps every factor in `{-1,0,1}`. Saving exact heights
lets a local repair use child heights without scanning whole subtrees.

## 4. Reconnect a small part

A **rotation** rearranges a few links while preserving inorder order.
The four three-key arrival orders finish with B above A and C:

| Case | Arrival order | Helper called by `_add` |
| --- | --- | --- |
| LL | C, B, A | `rotate_ll(i,l,lr)` |
| RR | A, B, C | `rotate_rr(i,r,rl)` |
| LR | C, A, B | `rotate_lr(i,l,lr,lrl,lrr)` |
| RL | A, C, B | `rotate_rl(i,r,rl,rll,rlr)` |

LL and RR correspond to one geometric rotation. LR and RL correspond to
two, performed by one direct helper in this source. Helpers only rewire
links. `_add` then updates heights from the lower nodes to the new root:
LL `i,l`; RR `i,r`; LR `i,l,lr`; RL `i,r,rl`.

The middle subtree must stay reachable. In LL, the captured `lr` becomes
`nodes[i].left`; in RR, `rl` becomes `nodes[i].right`. Capturing these
indices before overwriting links preserves their exact identities.

## 5. Return the local root

Recursive insertion descends to a missing link. **Recursion** means that
a function calls itself on a smaller part of the problem. `_add(-1,id)`
sets the fresh leaf's height to 0 and returns its ID. While calls return,
the parent saves the returned child root into both its link and local
`l` or `r`, computes balance, repairs if necessary, and returns its root.
The caller must keep the returned root:

```c
root = _add(root, new_node);
```

The source is complete. Required work is prediction, tracing, and original
assertion tests. Search, the plain-BST comparison, and independent checks
belong to test drivers. The lab has no allocation, duplicate rejection,
input-validation status, node deletion, or cleanup operation.

## 6. Compare shape and limit the claim

For seven distinct keys A through G, ascending and descending plain BSTs
have height 6. The fixed mixed order `D,B,F,A,C,E,G` has height 2. All
three AVL builds finish at key D with height 2. A deepest successful search
or suitable missing search takes 7 comparisons in a sorted plain chain
and 3 in these balanced trees.

**Algorithmic-complexity denial of service** describes valid chosen input
that makes an operation perform much more work. A tall plain BST models
one such risk. This does not by itself show **memory corruption**, an
invalid memory access, or prove broad **resource exhaustion**, using up a
limited resource. AVL balance addresses shape; it does not validate node
IDs, enforce access permissions, or establish whole-system security.

A binary Heap keeps parent priority. It does not impose whole-subtree
search order. AVL retains BST search order and adds a height bound.
