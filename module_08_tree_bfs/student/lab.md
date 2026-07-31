# Lab — Visit Nearer Tree Nodes First

## Purpose

You will complete three breadth-first operations over small synthetic trees:

1. record every node in level order;
2. find the shallowest node whose key matches a target; and
3. calculate edge height.

**Breadth-first search (BFS)** visits smaller depths before larger depths.
**Depth** is the number of child links from the root. **Level order** is
this BFS visit order on a tree. **Shallowest** means having the smallest
depth. A **Queue** uses first-in, first-out (FIFO) access: the
earliest-added waiting item leaves first. Synthetic trees are invented for
safe practice.

## 1. Work only in the student files

Read:

- `code/include/tree_bfs.h` — public tree types and contracts;
- `code/include/tree_work_queue.h` — supplied typed Queue contract;
- `code/README.md` — package and build guide;
- `code/starter/tree_bfs.c` — three unfinished operations; and
- `code/tests/test_student.c` — three student-test sections.

Edit only:

1. `tree_level_order`;
2. `tree_find_shallowest`;
3. `tree_height_bfs`; and
4. the three assigned sections in `test_student.c`.

Do not change the public types, the supplied Queue, its 64-record storage,
or supplied construction and cleanup helpers.

## 2. Read the tree and output types

```c
typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
    size_t depth;
} TreeBfsVisit;

typedef struct {
    TreeBfsVisit items[TREE_BFS_MAX_NODES];
    size_t count;
} TreeBfsOrder;

typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeBfsMatch;
```

A **struct** groups named values called fields. A **pointer** identifies an
object's memory location. `int` is C's whole-number type. A **key** is the
whole number used for search. `bool` stores `true` or `false`; a **flag** is
a stored yes-or-no marker. `size_t` is a nonnegative type for counts,
indexes, and depths. `NULL` is the pointer value meaning “no object.”

One `TreeBfsVisit` copies a key, flag, and depth. `TreeBfsOrder` stores at
most 64 visits. The **caller** is code asking a function to run. A
`TreeBfsMatch` contains a **borrowed pointer**: the caller owns the matched
tree node and must keep the tree alive while using that pointer.

## 3. Use only the supplied work Queue

A node is **discovered** when it is reached and placed in the waiting Queue.
The **frontier** is the discovered work still waiting. `TreeWorkQueue`
stores records of this form:

```c
typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeWorkItem;
```

Use only:

```c
tree_work_queue_init
tree_work_queue_enqueue
tree_work_queue_dequeue
```

The Queue has a fixed 64-item array directly inside its local object. It
does not allocate storage, own nodes, or need destruction. Its active
`limit` may be 0 through 64.

A **status code** is a named result reporting success or one kind of
failure. Map `WORK_QUEUE_LIMIT` to `TREE_BFS_LIMIT`. **Underflow** means removal was
requested from an empty Queue. Empty dequeue reports
`WORK_QUEUE_UNDERFLOW`; that normally means the traversal has finished.
Unexpected Queue argument or state errors map to
`TREE_BFS_INVALID_ARGUMENT`.

Do not inspect or change `data`, `head`, or `size` from a BFS function.
Using only public Queue operations keeps the algorithm separate from one
Queue representation.

## 4. TODO 1 — level-order traversal

A **contract** states what a function accepts, changes, reports, and
preserves. A **candidate** is a temporary possible result. To **commit** a
candidate means to copy it into the caller's output after required work
succeeds.

Complete:

```c
TreeBfsStatus tree_level_order(
    const TreeNode *root,
    size_t queue_limit,
    TreeBfsOrder *out_order
);
```

Follow this contract:

1. reject a `NULL` output pointer;
2. initialize a local Queue with `queue_limit`;
3. initialize a local empty `TreeBfsOrder` candidate;
4. enqueue `(root, 0)` only when root is non-`NULL`;
5. repeatedly dequeue one item;
6. reject a 65th reached node with `TREE_BFS_LIMIT`;
7. append its key, flag, and depth to the candidate;
8. enqueue its non-`NULL` left child before its non-`NULL` right child, each
   at parent depth plus one;
9. finish when dequeue reports underflow; and
10. copy the candidate to `*out_order` only after full success.

A `NULL` root succeeds with `count == 0`, even with Queue limit 0. A
nonempty root with limit 0 reports `TREE_BFS_LIMIT`. Every failure preserves
the caller's previous `TreeBfsOrder`.

## 5. TODO 2 — shallowest-value search

Complete:

```c
TreeBfsStatus tree_find_shallowest(
    const TreeNode *root,
    int target,
    size_t queue_limit,
    TreeBfsMatch *out_match
);
```

Use the same Queue rule. Check a node's key immediately after dequeue.
Stop at the first equal key and commit both match fields together.

This is correct because Queue removal uses nondecreasing depth. Equal-depth
ties follow the left-before-right enqueue order.

- A `NULL` root reports `TREE_BFS_NOT_FOUND`.
- A missing key reports `TREE_BFS_NOT_FOUND`.
- Not found, limit failure, and invalid input preserve the old match.
- Search may succeed without inspecting the rest of the tree.
- Count reached nodes so a 65th reached node reports `TREE_BFS_LIMIT`.

## 6. TODO 3 — edge height with BFS

Complete:

```c
TreeBfsStatus tree_height_bfs(
    const TreeNode *root,
    size_t queue_limit,
    int *out_height
);
```

**Edge height** is the greatest downward-link count from a node to a leaf.
This module fixes:

```text
height(NULL) = -1
height(leaf) = 0
```

Queue removal uses nondecreasing depth. Therefore, the depth in the most
recently removed item is the current greatest depth. Begin the local height
candidate at `-1`, update it after each successful dequeue, and commit only
after full success.

Apply the same Queue and 64-node limits as level order. A failed operation
must preserve the caller's old integer.

## 7. Use the canonical checkpoint

Build this general binary tree with separately created nodes and direct
child assignments:

```text
C0(42,F)
├─ C1(17,T)
│  ├─ C3(23,F)
│  └─ C4(91,T)
│     └─ C7(44,T)
└─ C2(68,F)
   ├─ C5(17,T)
   └─ C6(5,F)
      └─ C8(44,F)
```

A **binary search tree (BST)** keeps every key below a left child lower and
every key below a right child higher. This fixture is not a BST. Do not use
`tree_bst_insert` to build it. Repeated keys are intentional.

Required checkpoints:

- level-order keys are `42,17,68,23,91,17,5,44,44`;
- depths are `0,1,1,2,2,2,2,3,3`;
- every copied flag matches the source node;
- target 17 returns `C1` at depth 1;
- target 44 returns `C7` at depth 3;
- target 99 reports not found and preserves the old match;
- edge height is 3;
- full level order and height succeed with Queue limit 4;
- full level order and height report `TREE_BFS_LIMIT` with limit 3 and
  preserve output;
- searches for 44 and 99 likewise need limit 4; and
- the early search for 17 succeeds with limit 2.

The largest Queue count happens to be 4 in this tree. Do not turn that
observation into a general equality with level width: a Queue can contain
records from two adjacent depths during a transition.

## 8. Construct and release nodes safely

**Allocation** is storage requested while a program runs. **Ownership**
means responsibility for releasing it.

`tree_node_create` allocates one node and changes its output only on success.
After you connect separately created nodes, the root owns the valid tree for
this lab. **Postorder** handles children before their parent.
`tree_destroy_postorder(&root)` releases the tree in that order and sets
root to `NULL`.

`tree_bst_insert` is a supplied helper for a **strict BST**, a BST that
rejects equal keys. It reports
`TREE_BFS_DUPLICATE` for an equal key and leaves the BST unchanged. The
status `TREE_BFS_ALLOCATION` belongs to these supplied node-construction
helpers; the three BFS TODO operations allocate nothing.

Release every successfully created node on every test return path. Do not
destroy an arena node, a local node variable, a shared-node structure, or a
cycle.

## 9. Run supplied tests

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter builds but fails required checks until TODOs are complete. Work
from the earliest failed requirement. Do not weaken a supplied test.

When supported, run extra memory and invalid-operation checks:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

A **compiler** translates C into a runnable program. A **warning** identifies
code that may be mistaken. A **sanitizer** detects some invalid memory and
arithmetic operations while a program runs.

## 10. Write the three student tests

Complete the existing test functions in this exact order. Explain the new
claim each test contributes.

### Test 1 — level order and depths

Use a small synthetic tree to check one exact left-first level order. Check
every copied key, flag, and depth.

### Test 2 — shallowest duplicate and missing preservation

Repeat a key at two locations. Check the selected shallowest match, then
check that a missing key preserves the previous `TreeBfsMatch`.

### Test 3 — height and Queue boundary

Check exact edge height. Then make the Queue limit too small and prove
`TREE_BFS_LIMIT` preserves the prior height output.

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

## 11. Trace balance without implementing it

For the strict BST `30 ← 20 ← 10`, heights are measured with the same edge
convention. A **balance factor** is left height minus right height.

Trace the instructor-supplied right rotation at 30. **Inorder** visits
everything below the left child, then the node, then everything below the
right child. Confirm that the new root is 20, its children are 10 and 30,
inorder remains `10,20,30`, and every new balance factor is 0.

An **AVL tree** is a BST kept within balance factors `-1` through `1`. Do
not implement rotation selection, balancing, or AVL insertion here.

## 12. Complete the autopsy

Complete `student/tree_bfs_autopsy.md` before running the isolated autopsy
target. Predict its exact visit order and returned equal-depth node. Record
the first broken ordering decision, smallest repair, and a regression test.

The standalone program is bounds-checked and does not modify the course
implementation.

## 13. Cost and safe scope

Let `n` be node count, `w` maximum width, and `h` edge height.
`O(x)`, read “order x,” means work or storage grows in proportion to `x`.

- Full BFS uses `O(n)` time and `O(w)` auxiliary space.
- Full DFS uses `O(n)` time and `O(h)` auxiliary space.
- Returned traversal output uses `O(n)` storage and is counted separately.

The input must be finite, **acyclic**, meaning no child-link route returns
to an earlier node, and **unshared**, meaning each nonroot node has one
parent. A **visited record** stores that an item was reached before. These
BFS operations do not keep one. A **graph** is a general network whose
routes may reconnect or loop; it requires graph rules, visited state, and an
explicit permission boundary. Do not adapt this lab to live systems.

## Completion checklist

- [ ] All three TODO operations satisfy the public header.
- [ ] Left children enter before right children.
- [ ] Exact level order/depth, repeated, missing, height, and limit cases
      pass.
- [ ] Every failure preserves its caller output.
- [ ] Canonical full traversal/height use the exact limit-4/limit-3
      distinction; early search 17 succeeds with limit 2.
- [ ] The Queue is used only through its public operations.
- [ ] Every owned node is released exactly once.
- [ ] Three student tests state distinct claims.
- [ ] The rotation remains a trace, not an implementation.
- [ ] The autopsy identifies the first broken decision.
