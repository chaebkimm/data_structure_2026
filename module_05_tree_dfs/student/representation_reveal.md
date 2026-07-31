# Stage B — Formal Tree-Visiting Methods

Open this file only after preserving the Stage A inquiry.

## 1. Name the overall task

An **algorithm** is a precise, repeatable set of steps. A **tree traversal**
is an algorithm that visits the nodes of a tree in a stated order. To
**visit** a node means to perform the current task at that node. The task
might record its key, inspect a marker, or release its storage.

**Depth-first search (DFS)** explores one subtree as far as it can before
returning to unfinished choices. A **subtree** is one node together with all
the nodes below it. To **backtrack** means to return to an earlier unfinished
choice.

Use this small tree for the reveal:

```text
    8
   / \
  3  10
```

The stored number in a node is its **key**, used to identify or compare that
node.

The example is deliberately different from the Cognitive Pause.

## 2. Choose when to visit

The three course DFS orders differ only in when the current node is visited.

- **Preorder** uses node, left subtree, right subtree.
- **Inorder** uses left subtree, node, right subtree.
- **Postorder** uses left subtree, right subtree, node.

For the small tree:

| Order | Rule | Keys |
|---|---|---|
| Preorder | node, left, right | `8, 3, 10` |
| Inorder | left, node, right | `3, 8, 10` |
| Postorder | left, right, node | `3, 10, 8` |

“Left” and “right” mean complete subtrees, not only immediate children.
Each order reaches every node once in a valid tree.

## 3. Let function calls remember unfinished work

A **function** is a named group of instructions that performs one task.
**Recursion** occurs when a function calls itself, directly or through other
functions. One request for a function to run is a **function call**. A
recursive traversal makes a new call for each subtree.

Every recursive method needs a stopping rule. A **base case** is an input
that stops the repeated calls. The course base case is a `NULL` subtree.
`NULL` is the pointer value meaning “no node here.” A call given `NULL`
returns immediately and visits nothing.

Preorder can be written as steps:

```text
preorder(node):
    if node is NULL:
        return
    visit node
    preorder(node's left child)
    preorder(node's right child)
```

The C implementation commonly keeps information for active calls in a
**runtime call stack**. A **call frame** is the saved information for one
active call. It includes where that call must resume. On the small tree,
while the call for key 3 is active, the older call for key 8 still remembers
that its right subtree at key 10 remains unfinished.

The runtime call stack belongs to the C implementation. The traversal asks
for recursive calls; it does not directly push or pop these call frames.

## 4. Store unfinished nodes in an explicit Stack

A **Stack abstract data type (Stack ADT)** is a collection with last-in,
first-out access. The most recently pushed item is the first item popped.
An **explicit Stack** is a Stack object created and operated by the program.

A **pointer** stores a memory address. `const TreeNode *` means a pointer
through which code may inspect, but not change, a tree node. This module’s
explicit Stack stores `const TreeNode *` values, not the characters stored
by the Module 4 Stack.

An **iterative algorithm** repeats steps with a loop instead of using
recursive calls. A **loop** repeats a group of instructions while its stated
condition holds. Iterative left-first preorder follows these steps:

```text
push the root if it is not NULL
while the Stack is not empty:
    pop one node
    visit it
    push its right child if present
    push its left child if present
```

Why is right pushed first? Last-in, first-out access makes the later left
push come out first.

For the small tree, list Stack items from bottom to top:

```text
Start:                         8
Visit 8; push 10, then 3:      10, 3
Visit 3:                       10
Visit 10:                      empty
```

Recursive preorder and iterative preorder can produce the same visit order.
They remember unfinished work through different mechanisms.

## 5. Read the public data types

A **data type** states what kind of value is stored. A **struct** groups
named values called **fields**. `bool` is C’s yes-or-no type: its values are
`true` and `false`. A **flag** is a stored yes-or-no marker.

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

The `#define` line gives the number 64 a fixed name:
`TREE_DFS_MAX_NODES`. It is the output limit. `int` stores a whole number.
`size_t` is a nonnegative whole-number type for counts and indexes.

One `TreeVisit` is a copied visit record. A `TreeOrder` stores up to 64 visit
records and its current `count`. Each public traversal records every visited
node, including its key and flag. The output stores copies, not node
pointers. Code may later filter those records by flag.

## 6. Read the exact public operations

A **public operation** is a function intended for other program parts to
call. A **caller** is the code asking a function to run. A **status code** is
a named result reporting success or one kind of failure.

```c
TreeDfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);
void tree_node_release(TreeNode *node);

TreeDfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);

TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
);

TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root,
    size_t stack_limit,
    TreeOrder *out_order
);

TreeDfsStatus tree_bst_search(
    const TreeNode *root,
    int target,
    const TreeNode **out_node
);

TreeDfsStatus tree_destroy_postorder(TreeNode **root);
const char *tree_dfs_status_name(TreeDfsStatus status);
```

`const TreeNode *` means the function may inspect the pointed-to node but not
change it through that pointer. `TreeNode **` is the address of a node
pointer; it lets a function replace the caller’s root pointer.

The `TreeDfsStatus` values appear in this order:

1. `TREE_DFS_OK`: the requested operation succeeded.
2. `TREE_DFS_INVALID_ARGUMENT`: a required pointer was `NULL`.
3. `TREE_DFS_LIMIT`: the 64-visit limit or explicit Stack limit prevented
   completion.
4. `TREE_DFS_ALLOCATION`: requested node or Stack storage could not be
   obtained.
5. `TREE_DFS_DUPLICATE`: insertion found that the key already exists.
6. `TREE_DFS_NOT_FOUND`: search reached a missing subtree without finding
   the target.

Traversal outputs remain unchanged when a traversal fails. A `NULL` root is
a valid empty traversal. Iterative preorder accepts a Stack limit from 0
through 64; a larger value reports `TREE_DFS_LIMIT`. The constructor leaves
`out_node` unchanged if an invalid argument or allocation failure is
reported. A **constructor** prepares a new object; `tree_node_create` is this
module’s constructor. A **binary search tree (BST)** keeps lower keys in left
subtrees and higher keys in right subtrees. **Insertion** adds a key while
preserving that rule. `tree_node_release` is the supplied function that
releases one node; postorder destruction uses it after the node’s children
are handled. The constructor and insertion are supplied as a **baseline**,
meaning a working starting point. Later work concentrates on traversal,
search, and safe cleanup.

## 7. Prepare for the Cognitive Pause

Be ready to:

1. apply three visit orders to a new tree;
2. explain the `NULL` base case and saved work in active calls; and
3. trace the first states of an explicit TreeNode-pointer Stack.

Do not solve the pause examples before the timer begins.
