# Module 2 Binary-Tree Models

Every diagram includes a text equivalent. Nodes are ordinary local
`struct TreeNode` variables. Links store their addresses; the diagrams show
relationships, not physical memory order.

## 1. Two named child positions

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

```text
one node
+-----------------------+
| data                  |
| left  -> node or NULL |
| right -> node or NULL |
+-----------------------+
```

Text equivalent: every node stores one integer and two independent child
pointers. Left and right are named positions, not positions that slide when
another link is removed. There is no upward link stored in this structure.

## 2. The canonical expression tree

```text
             root:'*'
             /       \
        left/         \right
        plus:'+'       two:2
          /   \
     three:3 five:5
```

Text equivalent: the root stores `'*'`. Its left child stores `'+'`, and its
right child stores `2`. The plus node's left child stores `3`, and its right
child stores `5`. Nodes 3, 5, and 2 have no children. The links encode
`(3 + 5) * 2`; swapping left and right operands can change an expression's
meaning, so their positions are deliberate.

| Local variable | Data | `left` stores | `right` stores |
|---|---|---|---|
| `root` | `'*'` | `&plus` | `&two` |
| `plus` | `'+'` | `&three` | `&five` |
| `three` | `3` | `NULL` | `NULL` |
| `five` | `5` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

This is an expression tree, not a binary search tree. The stored value does
not tell `tree_find` which side it may skip. Binary operators in this fixture
have two operands, but the general `TreeNode` representation still permits a
valid node with exactly one child.

## 3. An object and its address

```c
struct TreeNode root;
struct TreeNode plus;

root.data = '*';
root.left = NULL;
root.right = NULL;

plus.data = '+';
plus.left = NULL;
plus.right = NULL;

root.left = &plus;
struct TreeNode *p = &root;
```

| Expression | Meaning |
|---|---|
| `root` | the local node object |
| `&root` | the address of that object |
| `root.data` | its integer field, containing the character value `'*'` |
| `root.left` | the address `&plus` stored in its left field |
| `p` | a pointer storing `&root` |
| `p->data` | the data field reached through `p` |
| `p->left` | the same child address as `root.left` |
| `NULL` | no node at this child position |

Text equivalent: the dot selects a field of a node variable. The arrow
selects a field through a node pointer. Taking an address does not copy or
move the node.

All linked node variables must remain alive while the tree uses their
addresses. Returning the address of a local variable whose function has
ended would not meet that requirement.

## 4. Empty, left-only, and right-only states

```text
leaf                 left-only           right-only
  A                      A                   A
 / \                    / \                 / \
-   -                  B   -               -   B
```

Text equivalent: a leaf has both links `NULL`. A node with only a left
child is valid, and a node with only a right child is equally valid. Both
one-child nodes are non-leaves. A right child does not need a left child.

## 5. Paths, depth, and height

```text
root:'*' --left--> plus:'+' --left--> three:3
depth 0            depth 1              depth 2

height(root) = 2
height(plus) = 1
height(three) = 0
```

Text equivalent: depth counts links from the chosen root to a node. Height
counts links on the longest downward route to a leaf. A leaf has height
zero. These are reasoning tasks, not additional required functions.

A parent is a relationship visible in the whole tree even though a node
does not store a pointer to its parent. To describe an upward relationship,
use the known diagram or a path from the root.

## 6. Recursive current-left-right search

For target `2` in the canonical tree:

```text
check '*'
  search left: check '+'
    search left: check 3 -> no match
    search right: check 5 -> no match
  search right: check 2 -> match; return its address

visited data: '*', '+', 3, 5, 2
```

Text equivalent: inspect the current node first, search its complete left
subtree next, and search its right subtree only if no match was found.
An empty link returns `NULL`. A non-`NULL` match returns immediately through
the pending calls.

A missing value visits the same five nodes. A search for `5` stops before
visiting `two`. If equal data occurs in several nodes, return the first
matching node in this search order, not an arbitrary match.

## 7. Clear a branch and remove its link

Start again with the canonical tree. Clear the branch at `root.left`, then
set that selected link to `NULL`.

```text
branch reset order: three, five, plus
each becomes: data = 0, left = NULL, right = NULL

surviving tree:
       root:'*'
       /      \
     NULL     two:2
```

Text equivalent: visit descendants before resetting their containing node.
The local objects `three`, `five`, and `plus` still exist while their scope is
active; their contents have been reset. The removed branch is no longer
reachable through the root's left link.

The original right link still points to `two`. It never moves into the
left position. Clearing the contents of a node and detaching the link above
it are distinct actions: a child-only node cannot detach itself. These links
still form a valid general binary tree, but they no longer form a completed
binary expression because the `'*'` node has only one operand.

## 8. Stage C transfer model

```text
                  root:'*'
                  /       \
             minus:'-'    plus:'+'
               /   \       /   \
          eight:8 three:3 four:4 two:2
```

Text equivalent: this fresh Stage C tree represents `(8 - 3) * (4 + 2)`.
The root stores `'*'`; its left child `minus` stores `'-'` with operands 8
and 3, and its right child `plus` stores `'+'` with operands 4 and 2. The four
number nodes are leaves.

Use the named sides to trace paths and operations. In particular, the
subtraction operands cannot exchange sides without changing the expression.
This expression structure still supplies no binary-search ordering rule.

## 9. Local checks and caller preconditions

A direct `if` check can inspect a selected child link and avoid overwriting
it. It cannot infer all incoming links to a node from its two downward fields.

Before an operation, the caller must ensure that:

- all involved node addresses identify initialized, live objects;
- the complete structure has no cycle;
- no node is shared by two child links; and
- linking a proposed child preserves those whole-tree rules.

A successful local check is not a complete graph-validation result. Keep
invalid-cycle examples on paper; do not run ordinary recursive search or
clear on a cyclic structure.

## 10. Counting work

Let `n` be the number of reachable nodes, `k` the number in a selected
branch, and `h` the longest root-to-leaf path measured in links.

| Operation | Time | Extra call-stack space |
|---|---:|---:|
| initialize one existing node | `O(1)` | `O(1)` |
| inspect the two child positions | `O(1)` | `O(1)` |
| attach to a known empty side | `O(1)` | `O(1)` |
| recursive find | `O(n)` worst case | `O(h + 1)` |
| clear a branch | `O(k)` | proportional to branch height plus one |
| detach one known side alone | `O(1)` | `O(1)` |
| clear and remove a branch | `O(k)` | proportional to branch height plus one |

Text equivalent: setup and local checks touch a fixed number of fields.
Search may visit every reachable node. Clearing visits every node in the
selected branch once. Pending recursive calls follow the deepest active
route, not every node at the same time.
