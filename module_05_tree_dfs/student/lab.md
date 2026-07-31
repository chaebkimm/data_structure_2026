# Lab — Follow One Branch: Tree Depth-First Traversal

## Purpose

You will visit a small tree in three exact orders, build preorder in two
different ways, search a binary search tree, and release every constructed
node.

A **tree** is a collection of values connected in a parent-child shape. Each
stored value is a **node**. The first node is the **root**. A node directly
below another is its **child**. A node with no children is a **leaf**.

This is the lab’s main tree:

```text
        50
       /  \
     30    70
    /  \
   20  40
```

The numbers are called **keys**: values used to identify and compare nodes.
Each node also stores a Boolean `flagged` value. A **Boolean** is either
`true` or `false`.

## What “depth-first” means

A **traversal** is a planned visit to nodes. **Depth-first search (DFS)**
follows one branch before returning to visit another branch. “Search” is in
the traditional name, although a traversal may collect every node rather
than stop at one target.

For a node with a left and right child, three depth-first orders are:

- **preorder:** node, left part, right part;
- **inorder:** left part, node, right part; and
- **postorder:** left part, right part, node.

For the main tree, the exact key orders are:

```text
preorder:  50, 30, 20, 40, 70
inorder:   20, 30, 40, 50, 70
postorder: 20, 40, 30, 70, 50
```

A visit records both the key and its flag. In preorder, the flagged keys are
`30, 40, 70`.

## Read the representation

A **representation** is how an idea is stored in code.

```c
typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
```

A **pointer** stores the location of an object. `left` and `right` point to
child nodes. `NULL` is a special pointer value meaning “no object here.”

This lab accepts at most 64 visits:

```c
typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;
```

`TreeOrder` is an output record. `items` stores visits. `count` says how many
positions are meaningful. A traversal of `NULL` produces `count == 0`.

## Public results

An **API** is the public types and functions that other code may use. A
**status** is a named result returned by a function.

```c
typedef enum {
    TREE_DFS_OK = 0,
    TREE_DFS_INVALID_ARGUMENT,
    TREE_DFS_LIMIT,
    TREE_DFS_ALLOCATION,
    TREE_DFS_DUPLICATE,
    TREE_DFS_NOT_FOUND
} TreeDfsStatus;
```

- `TREE_DFS_OK` means success.
- `TREE_DFS_INVALID_ARGUMENT` means a required pointer was `NULL`.
- `TREE_DFS_LIMIT` means a traversal or its Stack cannot remain within its
  stated bound.
- `TREE_DFS_ALLOCATION` means the program could not reserve requested memory.
- `TREE_DFS_DUPLICATE` means an insertion key already exists.
- `TREE_DFS_NOT_FOUND` means BST search reached no matching key.

An **output parameter** is a pointer through which a function reports a
result. Traversal functions change `out_order` only on success. Therefore,
build a local candidate first:

```c
TreeOrder candidate = {0};
```

Copy `candidate` to `*out_order` only after the complete traversal succeeds.
This is **failure preservation**: a failed operation leaves the caller’s old
output unchanged.

## Checkpoint 1 — Recursive preorder

**Recursion** means a function calls itself on a smaller version of the same
problem. A tree naturally contains smaller left and right trees.

The stopping rule, often called the **base case**, is:

```c
if (node == NULL) {
    return TREE_DFS_OK;
}
```

The starter then uses `count_reached_node` before following either child.
Keep this supplied check. Reaching a 65th non-`NULL` node reports
`TREE_DFS_LIMIT` before recursion goes deeper, even when another traversal
order would record that node later.

The recursive preorder helper then:

1. appends the current node’s key and flag;
2. visits the left child tree;
3. visits the right child tree; and
4. immediately passes any failure back to its caller.

Complete TODO 1 in the recursive preorder helper. Do not edit the supplied
inorder and postorder functions. Compare the three helpers and explain how
moving one append step changes the order.

Before running code, trace preorder by hand. For each visit, write:

```text
current node | appended key | next call
```

## Checkpoint 2 — Iterative preorder with a Stack

**Iterative** code repeats with a loop rather than making recursive calls.
The supplied `TreeNodeStack` stores `const TreeNode *` values: pointers
through which code may inspect, but not change, tree nodes.

A **Stack** is a last-in, first-out collection: the newest pushed item is the
first item popped. `push` adds one item; `pop` removes the newest item.
**Underflow** means a pop was requested when the Stack was empty.

For preorder:

1. initialize the Stack with `stack_limit`;
2. if the root exists, push it;
3. repeatedly pop a node and append its key and flag;
4. push its right child first, if present;
5. push its left child second, if present; and
6. finish successfully when pop reports `NODE_STACK_UNDERFLOW`.

Why right before left? Because left is then newer, so left pops first.

Use only these Stack functions:

```c
tree_node_stack_init
tree_node_stack_push
tree_node_stack_pop
tree_node_stack_destroy
```

Do not inspect `stack.data`, `stack.size`, or another Stack field inside the
traversal. This keeps the traversal dependent on Stack behavior rather than
one storage choice.

The Stack owns its pointer array. It does not own tree nodes. Always call
`tree_node_stack_destroy` after successful initialization, including after a
later failure. **Cleanup** means releasing a resource when it is no longer
needed.

Map a Stack limit to `TREE_DFS_LIMIT` and Stack allocation failure to
`TREE_DFS_ALLOCATION`. The canonical tree succeeds with Stack limit 3. It
fails with limit 2, and the caller’s output must stay unchanged.

## Checkpoint 3 — BST search

A **binary search tree (BST)** orders keys so every key in a node’s left part
is smaller and every key in its right part is larger. This lab uses a
**strict BST**, meaning duplicate keys are forbidden.

Search begins at the root:

```text
target smaller than current key -> move left
target larger than current key  -> move right
equal                           -> found
NULL                            -> not found
```

Complete the supplied loop in `tree_bst_search`. On success, set
`*out_node`. On `TREE_DFS_NOT_FOUND`, leave the caller’s old output pointer
unchanged.

The supplied `tree_bst_insert` builds a strict BST. Inserting a duplicate or
failing to allocate a new node leaves the existing tree unchanged.

## Checkpoint 4 — Postorder destruction

**Dynamic allocation** reserves memory while a program runs.
`tree_node_create` constructs one dynamically allocated node.
`tree_node_release` releases exactly one such node and does not follow its
children.

To release a whole valid tree safely:

1. destroy the left child tree;
2. destroy the right child tree;
3. release the current node.

That is postorder. Children are handled while their pointers are still
available. After all nodes are released, set the caller’s root to `NULL`.
An empty tree succeeds. A `NULL` pointer-to-root is an invalid argument.

Use this destroy function only when every reachable node came from
`tree_node_create` or `tree_bst_insert` and belongs only to that tree. Do
not pass nodes declared as ordinary local variables or array elements;
`tree_node_release` may release only dynamically allocated nodes.
Because destruction is recursive, use it only with the small course trees.
A very deep tree could exhaust the runtime call stack; this function does
not detect that separate machine limit.

Complete `tree_destroy_postorder`.

## Checkpoint 5 — Run supplied tests

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter compiles but initially fails because TODOs remain. Work from the
earliest failed requirement. Do not weaken a supplied test.

The visible tests include:

- empty, single-node, canonical, and one-sided trees;
- exact preorder, inorder, and postorder visits, including flags;
- equality of recursive and iterative preorder;
- Stack limits 3 and 2;
- repeatable allocation failures and unchanged outputs;
- duplicate insertion;
- found and missing BST searches; and
- postorder cleanup with a count of live constructed nodes.

When your compiler supports **sanitizers**, extra runtime checks for memory
and invalid operations, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

## Checkpoint 6 — Write three tests

Complete `code/tests/test_student.c`. Add a comment explaining what each test
contributes beyond the visible suite.

Your three categories are:

1. traversal order or flag preservation;
2. a boundary or failure that preserves an output; and
3. BST search or postorder cleanup.

Use a small **synthetic tree**, meaning one made only for this exercise. Make
every expected key and flag explicit. Clean up each constructed node.

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
```

## Checkpoint 7 — Autopsy

Complete `student/tree_dfs_autopsy.md` before running:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Identify the predicted output, the first broken push decision, the smallest
fix, and one regression test.

## Cost

Let `n` mean the number of nodes. Each traversal performs constant work per
node, so its time is **O(n)**. This notation describes how work grows as the
input grows.

Let `h` mean tree height: the greatest number of downward links on a
root-to-leaf path. Recursive DFS uses at most `h + 1` active function calls.
Iterative DFS uses at most `h + 1` Stack entries for these tree shapes. Both
are conventionally called O(h) as height grows. This temporary working space
is called **additional memory** because it is separate from the tree and
output.

Strict-BST search takes O(h) time. A **balanced** shape, whose left and right
sides stay at roughly similar heights, keeps `h` smaller. A one-sided
`n`-node tree has height `n - 1`.

## Safe scope: a tree is not every hierarchy

Use only instructor-provided or student-created synthetic nodes. Do not scan
a live filesystem, production service, or private data source.

A filesystem-looking hierarchy can contain **aliases**, meaning multiple
names for the same destination, and **symbolic links**, special entries that
redirect to another path. Such connections may create sharing or cycles. A
cycle is a route that eventually returns to an earlier object. This lab’s
functions assume an acyclic, non-shared tree and would not be safe for that
graph-shaped input.

A graph traversal needs a **visited set**, a collection recording objects
already seen, plus an explicit policy for links and permissions. That is a
later spiral. Do not adapt this lab to a live filesystem.

## Completion criteria

- the four TODO operations satisfy the public header;
- recursive and iterative preorder record identical keys and flags;
- every failure preserves the required output;
- iterative preorder uses only public Stack operations and always cleans up;
- BST search follows comparisons and preserves a missing output;
- postorder destroy releases every constructed node and nulls the root;
- all three student-test categories pass; and
- the autopsy identifies the first broken decision.
