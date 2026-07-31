# Student Notes — Remembering a Path Through a Tree

## Essential question

> How can one method visit every tree node, remember unfinished branches, and
> stop safely?

## 1. One tree, three orders

A binary tree gives each node at most two child positions, left and right.
This module reuses the Module 2 tree:

```text
       50
      /  \
  * 30    70 *
    / \
   20 40 *
```

A key is a stored whole number used to identify or compare a node. An
asterisk is a true flag, a stored yes-or-no marker. A directory organizes
entries so stored items can be located. A policy is a set of rules. This
example is synthetic—created for safe study, not taken from a real system.

An algorithm is a precise set of steps. A **tree traversal** is an algorithm
that visits tree nodes in a stated order. To visit means to perform the
current task. Every public traversal here copies each node’s key and flag.

**Depth-first search (DFS)** finishes one subtree before moving to another. A
subtree is one node and everything below it. Three tree DFS orders differ
only in when the node is recorded:

- **Preorder:** node, left subtree, right subtree.
- **Inorder:** left subtree, node, right subtree.
- **Postorder:** left subtree, right subtree, node.

```text
Preorder:  50, 30, 20, 40, 70
Inorder:   20, 30, 40, 50, 70
Postorder: 20, 40, 30, 70, 50
```

All five nodes are recorded. Filtering the copied flags afterward reports
30, 40, 70 in preorder. An unflagged node cannot justify skipping its
subtree.

## 2. Recursive DFS

A function is a named group of instructions. **Recursion** occurs when a
function calls itself.

```text
preorder(node):
    if node is NULL:
        return
    record node
    preorder(node's left child)
    preorder(node's right child)
```

`NULL` is the pointer value meaning “no node.” A **base case** is an input
that stops more calls. A `NULL` subtree returns immediately and records
nothing.

A call is active after it starts and before it returns. The C implementation
commonly manages active calls in a runtime call stack. A **call frame** saves
information for one active call, including where to resume.

When recursive preorder reaches key 20, the active non-`NULL` calls are 50,
30, 20. The frame for 30 remembers its right subtree at 40. The frame for 50
remembers its right subtree at 70. Inorder and postorder use the same calls
and base case; only the record step moves.

## 3. Iterative DFS

An iterative algorithm repeats with a loop instead of recursive calls. It
can use an **explicit Stack**, a Stack object directly operated by the
program. A pointer stores a memory address. This Stack stores
`const TreeNode *` values: pointers used to inspect, but not change, nodes.

The **Stack abstract data type (Stack ADT)** gives last-in, first-out access.
It is the general Module 4 rule. The explicit TreeNode-pointer Stack is one
use of that rule. It is not the runtime call stack. `push` adds an item;
`pop` removes the newest item.

```text
push the root if it is not NULL
while the explicit Stack is not empty:
    pop one node
    record it
    push its right child if present
    push its left child if present
```

Right is pushed first so the later left push is popped first. States below
are bottom to top:

```text
After visiting 50: 70, 30
After visiting 30: 70, 40, 20
After visiting 20: 70, 40
After visiting 40: 70
After visiting 70: empty
```

The output matches recursive preorder, although the storage mechanism
differs.

## 4. Nodes and output

A struct groups named fields. `int` is C’s type for a whole number. `bool`
is C’s yes-or-no type. An array is a numbered row of same-type values.

```c
#define TREE_DFS_MAX_NODES 64U

typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;
```

`TREE_DFS_MAX_NODES` names the 64-record maximum. One `TreeVisit` copies a
key and flag. `TreeOrder` stores the visit array and its count. `size_t` is a
nonnegative whole-number type. To own storage means to be responsible for
releasing it. Output records do not own nodes.

## 5. Exact public contract

A contract states what a function accepts, changes, reports, and preserves.
A caller is the code asking a function to run. An output parameter is
caller-provided storage for a result. `TreeNode **` is the address of a node
pointer, so a function can replace that pointer. `const TreeNode *` permits
inspection but not change through that pointer.

```c
TreeDfsStatus tree_node_create(
    int key, bool flagged, TreeNode **out_node);
void tree_node_release(TreeNode *node);
TreeDfsStatus tree_bst_insert(
    TreeNode **root, int key, bool flagged);
TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root, size_t stack_limit, TreeOrder *out_order);
TreeDfsStatus tree_bst_search(
    const TreeNode *root, int target, const TreeNode **out_node);
TreeDfsStatus tree_destroy_postorder(TreeNode **root);
const char *tree_dfs_status_name(TreeDfsStatus status);
```

A status code is a named result. Its values, in exact order, are:

```text
TREE_DFS_OK                 success
TREE_DFS_INVALID_ARGUMENT   a required pointer is NULL
TREE_DFS_LIMIT              output or explicit-Stack limit reached
TREE_DFS_ALLOCATION         requested node or Stack storage unavailable
TREE_DFS_DUPLICATE          insertion key already present
TREE_DFS_NOT_FOUND          search target absent
```

A `NULL` root is a valid empty traversal with count zero. Traversals record
at most 64 nodes. Iterative `stack_limit` may be 0 through 64; a larger value
reports `TREE_DFS_LIMIT`. A failed traversal leaves the previous `TreeOrder`
unchanged. This promise is failure atomicity. Not-found search leaves
`out_node` unchanged. Node creation also leaves `out_node` unchanged after
invalid input or allocation failure.

## 6. Build and search a strict BST

**Dynamic allocation** obtains storage while a program runs.
`tree_node_create` writes one new node pointer to `out_node`. A constructor
prepares a new object; this function is the module’s constructor.

**Ownership** is responsibility for releasing requested storage. After
successful insertion, the tree owns the node. `tree_node_release` is the
supplied function that releases one node. The constructor and insertion
functions are supplied baseline code—a working starting point.

A **binary search tree (BST)** keeps every left-subtree key lower and every
right-subtree key higher. Strict ordering rejects equal keys. Inserting
another 40 reports `TREE_DFS_DUPLICATE` without changing the tree.

Search compares the target with one current key. Equal succeeds; lower goes
left; higher goes right:

```text
target 40: 50 → 30 → 40 → TREE_DFS_OK
target 35: 50 → 30 → 40 → NULL → TREE_DFS_NOT_FOUND
```

Strict ordering lets search choose one route. A full traversal must reach
both subtrees.

## 7. Release children before parents

Postorder safely destroys an owned tree because it handles children before
their parent:

```text
20, 40, 30, 70, 50
```

A parent must remain alive while its child pointers are read.
`tree_destroy_postorder` releases each node through `tree_node_release`, then
sets the caller’s root to `NULL`. Releasing 50 first and later reading
`50->left` would use a dangling pointer—an address of released storage.

## 8. Costs and boundaries

**Time complexity** describes how work grows. Let `n` be node count. A full
traversal visits each node once, so it takes `O(n)` time: work grows in
proportion to `n`.

Let `h` be height, the greatest downward-link count from root to leaf. At
most `h + 1` non-`NULL` calls or pending explicit-Stack items exist
together. This is conventionally `O(h)`: storage grows in proportion to
height. **Auxiliary space** is extra working storage.

The 64-node check also bounds recursive traversal depth. Recursive
destruction creates no visit records and has no such check, so use it only
with the small course trees. A very deep owned tree could exhaust the
runtime call stack.

The 64-record limit bounds output. `stack_limit` separately bounds pending
pointers. A nonempty iterative traversal with limit 0 reports
`TREE_DFS_LIMIT` without changing output. These limits bound the teaching
program; success does not prove a real policy correct or authorized.

## 9. When the structure is no longer a tree

An alias is another route to an existing target. A symbolic link is a
directory entry that refers elsewhere. A cycle is a route back to an earlier
node. Sharing or a link back can give several routes or a cycle, so the model
becomes a graph—a general relationship structure.

A graph traversal needs a visited set, stored marks showing which nodes were
already reached. Checking it prevents repeated visits and endless cycles.
Pure-tree DFS here intentionally has no visited set; graph DFS is the next
spiral step.
