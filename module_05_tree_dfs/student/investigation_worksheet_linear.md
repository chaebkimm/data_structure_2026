# Stage C — Investigation Worksheet: Linear Accessible Format

## How to use this version

This version has exactly the same learning targets and prompt IDs as the
standard investigation. It avoids response tables and drawing requirements.
It is suitable for a **screen reader**—software that reads on-screen text
aloud—keyboard navigation, speech input, or a response containing only text.

Open this file after completing and preserving the Cognitive Pause.

**Sections A–F are the Stage C core investigation. Complete them before
opening Stage D notes. Sections G–I are later extension and reflection.**

A **policy** is a set of rules. A computer **directory** organizes entries
so stored items can be located. These examples are synthetic: they are
invented for safe practice and do not inspect a real computer.

## Quick reference

A **traversal** is a planned method for visiting nodes. **Depth-first search
(DFS)** finishes one subtree before moving to another. A **recursive**
function calls itself. Its **base case** stops further calls; here, a `NULL`
subtree returns immediately. A **call frame** remembers one active call. An
**iterative** method uses repetition instead of recursive calls. An
**explicit Stack** is a last-in, first-out collection directly operated by
the program.

The public types are:

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

The exact public functions are:

```c
TreeDfsStatus tree_node_create(
    int key, bool flagged, TreeNode **out_node);
void tree_node_release(TreeNode *node);
TreeDfsStatus tree_bst_insert(TreeNode **root, int key, bool flagged);
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

The status values, in order, are:

```text
TREE_DFS_OK
TREE_DFS_INVALID_ARGUMENT
TREE_DFS_LIMIT
TREE_DFS_ALLOCATION
TREE_DFS_DUPLICATE
TREE_DFS_NOT_FOUND
```

## A. Trace the three DFS orders

Use the course tree in every prompt in this section:

```text
       50
      /  \
  * 30    70 *
    / \
   20 40 *
```

In linear form: root 50 has left child 30 and right child 70. Node 30 has
left child 20 and right child 40. Nodes 20, 40, and 70 have no children.

An asterisk means `flagged == true`. Thus keys 30, 40, and 70 are flagged.
Preorder is node-left-right. Inorder is left-node-right. Postorder is
left-right-node.

### A1. Preorder

List all keys in recursive preorder.

Response:

### A2. Inorder

List all keys in recursive inorder.

Response:

### A3. Postorder

List all keys in recursive postorder.

Response:

### A4. Flagged preorder

The traversal records every node’s key and flag. Read that complete preorder
output and report only the keys whose copied flag is true. Explain why an
unflagged node cannot justify skipping its whole subtree.

Response:

### A5. Empty traversal

A `NULL` root is a valid empty traversal. What should `out_order->count` be
after success, and which status should be returned?

Response:

## B. Explain recursive saved work

Recursive preorder follows:

```text
preorder(node):
    if node is NULL:
        return
    record node
    preorder(node's left child)
    preorder(node's right child)
```

Use the course tree. The call for key 20 is currently active.

### B1. Base case

What does the call given key 20’s `NULL` left child do? Why must it stop
without making another call?

Response:

### B2. Active calls

List the active non-`NULL` calls from oldest to newest.

Response:

### B3. Saved work

What unfinished work is remembered by the call frame for key 30? What is
remembered by the frame for key 50?

Response:

### B4. Moving the visit

Preorder records before the two child calls, inorder records between them,
and postorder records after them. Explain why moving only the record step
changes the order without changing the child links.

Response:

## C. Trace iterative preorder

The iterative method uses an explicit Stack of `const TreeNode *` values:
pointers through which code may inspect, but not change, nodes. Stack states
are listed from bottom to top.

```text
push root if root is not NULL
while the Stack is not empty:
    pop a node
    record it
    push its right child if present
    push its left child if present
```

### C1. First two states

For the course tree:

1. Give the Stack after visiting 50 and pushing its children.
2. Give the Stack after next visiting 30 and pushing its children.

Response:

### C2. Right before left

Why does pushing the right child before the left child produce left-first
preorder?

Response:

### C3. Complete iterative trace

Continue until the Stack is empty. For each step, state the popped key, the
recorded order so far, and the complete Stack state.

Response:

### C4. Stack limit

`stack_limit` may be from 0 through 64. What should happen when a nonempty
root must be pushed but `stack_limit` is 0? What must happen to the caller’s
existing `TreeOrder`?

Response:

### C5. Two different mechanisms

Compare recursive preorder with iterative preorder. Identify what each
method uses to remember unfinished work, and explain why an explicit
TreeNode-pointer Stack is not the runtime call stack.

Response:

## D. Apply the public contracts

A **contract** states what a function accepts, changes, reports, and
preserves. An **output parameter** is caller-provided storage in which a
function writes a result. **Failure atomicity** means a failed operation
leaves the prior valid output unchanged.

All traversal outputs remain unchanged on failure. A successful traversal
may write at most 64 visits. A `NULL` root is valid and produces an empty
order. `tree_preorder_iterative` accepts a Stack limit from 0 through 64; a
larger value reports `TREE_DFS_LIMIT`. Search result
`TREE_DFS_NOT_FOUND` leaves `out_node` unchanged.

### D1. Type roles

Describe the purpose of `TreeNode`, `TreeVisit`, and `TreeOrder`. Why does a
visit record copy a key and flag instead of owning a node?

Response:

### D2. Status matching

Match each situation to the exact status:

1. A traversal succeeds.
2. A required output pointer is `NULL`.
3. More than 64 visits would be required.
4. Node creation needed by insertion cannot obtain memory.
5. Insertion requests an existing key.
6. Search reaches `NULL` without finding the target.

Response:

### D3. Unchanged traversal output

Suppose `out_order` already contains two records. An iterative traversal
reaches its Stack limit before completion. Which status is required, and
what must remain unchanged?

Response:

### D4. Unchanged search output

Suppose `out_node` already stores a recognizable marker pointer used only to
detect unwanted changes. Such a test value is called a **sentinel**. A search
does not find its target. Which status is required, and what must happen to
the sentinel?

Response:

### D5. Boundary distinction

Explain the difference between the fixed 64-visit output limit and the
caller-selected iterative `stack_limit`.

Response:

## E. Search a strict binary search tree

A **binary search tree (BST)** uses strict ordering: every key in a node’s
left subtree is lower, and every key in its right subtree is higher.
“Strict” means duplicate keys are not allowed. The supplied insertion
baseline creates this ordering. A **baseline** is a working starting point.

Search compares the target with the current key:

- equal means found;
- lower continues left;
- higher continues right;
- reaching `NULL` means not found.

### E1. Found path

Trace `tree_bst_search` for target 40 in the course tree. List every compared
key and the final status.

Response:

### E2. Missing path

Trace search for target 35. List every compared key, state where `NULL` is
reached, and give the final status.

Response:

### E3. Strict insertion

What should `tree_bst_insert` report if asked to insert key 40 again? Why
must the existing tree remain unchanged?

Response:

### E4. Search versus full traversal

Why can strict BST search choose only one child at each comparison, while a
general traversal must reach both subtrees?

Response:

## F. Release owned nodes safely

**Dynamic allocation** obtains storage while a program runs. **Ownership**
is responsibility for eventually releasing that storage. In this module,
each successful `tree_node_create` call writes one separately allocated node
pointer to `out_node`. The tree then owns that node. `tree_node_release` is
the supplied function that releases one such allocation. A **dangling
pointer** is an address of storage that has already been released.

`tree_destroy_postorder` releases a node only after releasing its left and
right subtrees. On success, it writes `NULL` to the caller’s root pointer.

### F1. Child before parent

Give the postorder release sequence for the course tree. Explain why the
parent must still exist while its child pointers are being read.

Response:

### F2. Unsafe early release

Suppose key 50 is released first. Why can reading `50->left` afterward be
unsafe?

Response:

### F3. Root reset

Why should successful destruction set the caller’s root pointer to `NULL`?

Response:

### F4. Complexity

Let `n` be the node count. Let `h` be tree height: the greatest number of
downward links from the root to a leaf. At most `h + 1` non-`NULL` recursive
calls or pending explicit-Stack items are needed at once. This is
conventionally reported as `O(h)` as height grows. Explain why a full
traversal takes
`O(n)` time and why recursive calls or an explicit Stack require `O(h)`
auxiliary space. **Auxiliary space** is extra working storage used by an
algorithm.

Response:

### F5. Reliability boundary

The 64-node limit bounds this teaching implementation. Does a successful
synthetic policy-tree traversal prove that a real computer’s policy is
correct or authorized? Explain.

Response:

## G. Design tests — later extension

### G1. Shape coverage

Propose expected preorder, inorder, and postorder results for each case:
empty tree, one node, only-left chain, only-right chain, and the course tree.

Response:

### G2. Failure preservation

Design one test that proves a failed traversal leaves every field and
existing record in a nonempty `TreeOrder` unchanged.

Response:

### G3. Agreement

How could a test compare recursive and iterative preorder without assuming
that their internal storage mechanisms are the same?

Response:

## H. Transfer from a tree to a graph — later extension

A **graph** is a general structure of nodes and relationships. A
**symbolic link** is a directory entry that refers to another location. If a
directory-like model permits shared targets or links back to ancestors, it
no longer follows this module’s pure-tree rules.

### H1. Shared target

Why could two parent-like entries pointing to one target cause a tree method
to visit that target more than once?

Response:

### H2. Link back

Why could a link back to an ancestor prevent a tree method from finishing?

Response:

### H3. Visited tracking

A **visited set** records which nodes have already been reached. Explain how
checking it before further exploration addresses both repeated routes and
cycles.

Response:

## I. Exit reflection — later extension

### I1. Three orders

State the node/left/right rule for preorder, inorder, and postorder.

Response:

### I2. Two ways to remember

Distinguish recursive call frames, an explicit TreeNode-pointer Stack, and
the general Stack ADT.

Response:

### I3. Safe cleanup

Why is postorder suitable for releasing a dynamically allocated tree?

Response:

### I4. Open question

State one question you still have.

Response:
