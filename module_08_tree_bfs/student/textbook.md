# Nearer Nodes First

## Essential question

> How can we guarantee that every node close to the root is inspected before
> any deeper node?

## 1. The problem

A **tree** is a hierarchy of connected objects. Each object is a **node**,
and the one starting node is the **root**. A node directly below another is
its **child**. A **binary tree** gives each node at most two child
positions, named left and right.

A **synthetic** tree is invented for study. If it repeats a
value, following one branch deeply can return a farther match first.

## 2. Breadth-first order

An **algorithm** is a precise, repeatable set of steps. A **traversal** is an
algorithm that visits tree nodes in a stated order.

**Breadth-first search (BFS)** visits nodes nearer the root before nodes
farther from it. **Depth** is the number of child links from the root to a
node. The root has depth 0, its children have depth 1, and their children
have depth 2.

A **level** contains all nodes at one depth. Tree BFS is also called
**level-order traversal** because it completes smaller depths before larger
depths. This course visits a left child before a right child when both have
the same depth.

## 3. The Queue holds unfinished work

A **Queue** is a collection with **first-in, first-out (FIFO)** access: the
earliest-added waiting item leaves first. `enqueue` adds at the back, and
`dequeue` removes the front.

A node is **discovered** when it is reached and placed in the waiting Queue.
The **frontier** is the discovered work still waiting to be visited. One
**work record** pairs a node pointer with its depth. A **pointer** identifies
an object's memory location.

```text
enqueue (root, 0) if the root exists

while the Queue is not empty:
    dequeue (node, depth)
    visit node
    enqueue a non-NULL left child at depth + 1
    enqueue a non-NULL right child at depth + 1
```

`NULL` is the pointer value meaning “no node.” Children enter behind every
record already waiting. A larger-depth child therefore cannot pass a
smaller-depth record. Left enters before right, so it also leaves first.

The supplied typed Queue stores at most 64 records in an array directly
inside a local Queue object. An **array** is a numbered row of same-type
values. This Queue requests no separate storage and needs no destruction.
It stores node pointers temporarily but does not own or change the nodes.

## 4. Trace the course tree

Labels distinguish objects. Parentheses contain key and flag. A **key** is a
stored whole number used for search. A **flag** is a stored yes-or-no marker.
Repeated keys are deliberate.

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

Numeric order controls neither its links nor BFS visits.

| Completed visit | Frontier from front to back |
|---|---|
| none | `C0@0` |
| `C0` | `C1@1, C2@1` |
| `C1` | `C2@1, C3@2, C4@2` |
| `C2` | `C3@2, C4@2, C5@2, C6@2` |
| `C3` | `C4@2, C5@2, C6@2` |
| `C4` | `C5@2, C6@2, C7@3` |
| `C5` | `C6@2, C7@3` |
| `C6` | `C7@3, C8@3` |
| `C7` | `C8@3` |
| `C8` | empty |

The complete key order is:

```text
42, 17, 68, 23, 91, 17, 5, 44, 44
```

The depths are:

```text
0, 1, 1, 2, 2, 2, 2, 3, 3
```

The largest Queue count in this trace is 4.

## 5. Shallowest match

A **shallowest match** has the smallest depth among matching nodes.
`tree_find_shallowest` checks each node immediately after removing its work
record.

For target 17, `C1` is removed at depth 1 before `C5` at depth 2. For target
44, both matches have depth 3, but `C7` was discovered first under the
left-before-right rule. It is returned before `C8`.

Target 99 is absent. The procedure visits all nine nodes and reports
`TREE_BFS_NOT_FOUND`. The previous match output remains unchanged.

This guarantee depends on first-in, first-out work. An ordinary
depth-first search (DFS), which follows one branch before returning, does
not guarantee that its first match has minimum depth.

## 6. Width and edge height

The **width** of a level is its node count. The course tree has widths:

```text
depth 0: 1
depth 1: 2
depth 2: 4
depth 3: 2
```

Its **maximum width**, written `w`, is 4.

The **edge height** of a node is the greatest downward-link count from that
node to a leaf. This course uses:

```text
height(NULL) = -1
height(leaf) = 0
height(node) = 1 + greater child height
```

The course root has height 3. An `n`-node one-child chain has height
`n - 1`.

A **balance factor** is:

```text
height(left child) - height(right child)
```

The root's factor is 0 because its left and right child heights are both 2.
Balance factors preview Module 14; they do not change BFS order.

## 7. Output types and contracts

A **struct** is a C type that groups named fields. `int` is C's whole-number
type. `bool` is C's yes-or-no type. `size_t` is a nonnegative whole-number
type.

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

`TreeBfsVisit` copies one key, flag, and depth. `TreeBfsOrder` stores up to
64 visits. `TreeBfsMatch` points to one existing node; it does not own it.

A **contract** states what a function accepts, changes, reports, and
preserves.

```c
TreeBfsStatus tree_level_order(
    const TreeNode *root, size_t queue_limit, TreeBfsOrder *out_order);
TreeBfsStatus tree_find_shallowest(
    const TreeNode *root, int target, size_t queue_limit,
    TreeBfsMatch *out_match);
TreeBfsStatus tree_height_bfs(
    const TreeNode *root, size_t queue_limit, int *out_height);
```

Students complete these three operations. `const TreeNode *` permits
inspection but not change through that pointer. `queue_limit` may be 0
through 64. A larger value reports `TREE_BFS_LIMIT`.

A **caller** is code requesting a function. An **allocation** is storage
requested while a program runs. A **status code** is a named result:

```text
TREE_BFS_OK                 success
TREE_BFS_INVALID_ARGUMENT   a required output pointer is NULL
TREE_BFS_LIMIT              Queue or 64-node limit reached
TREE_BFS_ALLOCATION         supplied node construction failed
TREE_BFS_DUPLICATE          strict-BST insertion found an equal key
TREE_BFS_NOT_FOUND          search target absent
```

A `NULL` root is a valid empty tree. Level order succeeds with count 0.
Height succeeds with `-1`. Search reports `TREE_BFS_NOT_FOUND` and preserves
the old match. A nonempty tree with limit 0 reports `TREE_BFS_LIMIT`.

Canonical full level order and height succeed with limit 4 but fail with
limit 3, preserving output. Searches for 44 or 99 also need 4; early target
17 succeeds with 2. **Failure preservation** means a failed operation leaves
the caller's previous output unchanged. Build a local candidate and copy it
to the output only after the required result is known.

The three BFS operations themselves request no allocation.

## 8. Cost and the DFS comparison

**Time complexity** describes how work grows. Let `n` be the node count. A
complete BFS visits each node once, so its time is `O(n)`, read “order n”:
work grows in proportion to `n`.

**Auxiliary space** is temporary working storage separate from the tree and
returned output. BFS needs `O(w)`, read “order w,” auxiliary space: working
storage grows in proportion to maximum width `w`. DFS needs `O(h)`, read
“order h”: its working storage grows in proportion to height `h`.

`O(w)` does not mean peak Queue count always equals one level's width.
During a transition, the Queue can contain unvisited nodes from one depth
and discovered children from the next. The bound means Queue need grows in
proportion to width.

BFS may use more working space on a wide shallow tree. DFS may use more on a
long one-child chain.

## 9. Balance preview

Consider the strict **binary search tree (BST)** `30 ← 20 ← 10`. A BST keeps
every key below a left child lower and every key below a right child higher.
**Strict** means equal keys are not allowed. Its root height is 2 and root
balance factor is 2.

A **rotation** is a small link rearrangement that preserves binary-search
order. One supplied right rotation makes 20 the root, with left child 10 and
right child 30. Height becomes 1 and all balance factors become 0.
**Inorder** visits everything below the left child, then the node, then
everything below the right child; its result remains `10, 20, 30`.

Rotation selection and implementation wait until Module 14.

## 10. Safe input boundary

These operations require a valid, acyclic, unshared tree. **Acyclic** means
no child-link route returns to an earlier node. **Unshared** means every
nonroot node has one parent.

A **graph** is a general network that may provide several routes to one item
or a route back. Graph BFS therefore uses a **visited record**, a stored mark
showing that an item was reached before. Graph BFS and unweighted paths are
the next spiral step.

**Key sentence:** FIFO work records make BFS process nondecreasing depth, so
the first left-first match is shallowest.
