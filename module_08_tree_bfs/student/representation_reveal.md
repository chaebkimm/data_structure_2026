# Stage B — Formal Name and Stored Work

Open this file only after preserving the Stage A inquiry.

## 1. Name the visiting rule

An **algorithm** is a precise, repeatable set of steps. A **tree traversal**
is an algorithm that visits tree nodes in a stated order.

**Breadth-first search (BFS)** visits nodes nearer the root before nodes
farther from the root. On a tree, this order is also called **level order**.
A **level** contains nodes with the same depth. **Depth** is the number of
child links from the root to a node, so the root has depth 0.

The course order is fixed:

1. visit smaller depths before larger depths; and
2. at the same depth, visit a left child before a right child.

## 2. Reuse the Queue rule

A **Queue** removes items in first-in, first-out order: the earliest-added
waiting item leaves first. `enqueue` adds at the back; `dequeue` removes the
front.

A node is **discovered** when it is reached and placed in the waiting Queue.
The **frontier** is the collection of discovered nodes not yet visited. A
**work record** stores:

- a pointer to one node; and
- that node's depth.

A **pointer** is a value identifying an object's memory location. The typed
Queue supplied in this module accepts only work records. Its fixed work
array is stored directly inside a local Queue object. An **allocation** is
storage requested while a program runs. **Ownership** is responsibility for
releasing storage; **destruction** performs that release. This Queue requests
no allocation, needs no destruction, and does not own or change tree nodes.

## 3. Follow the exact procedure

`NULL` is the pointer value meaning “no node.” For a nonempty tree:

```text
enqueue (root, depth 0)

while the Queue is not empty:
    dequeue one work record
    visit its node
    if the left child is not NULL:
        enqueue (left child, parent depth + 1)
    if the right child is not NULL:
        enqueue (right child, parent depth + 1)
```

Children enter behind all work already waiting. Therefore, work at a larger
depth cannot pass work at a smaller depth. Adding left before right fixes
the order for equal-depth choices.

A valid course tree has one route from the root to each node and no route
back to an earlier node. BFS therefore does not need a **visited record**, a
stored mark saying a node was reached before. Graph BFS will add that record
because a **graph** is a general network whose routes may reconnect.

## 4. Trace a separate reveal tree

The labels `R0` through `R4` distinguish node objects. The number in
parentheses is the node's stored value. A **binary tree** gives each node at
most two child positions, left and right. This is a general binary tree:
numeric order does not control the links or visits.

```text
R0(26)
├─ left: R1(4)
│  └─ right: R3(58)
└─ right: R2(73)
   └─ left: R4(11)
```

Exact linear relationships:

1. `R0`, value 26, is the root.
2. `R0` has left child `R1`, value 4, and right child `R2`, value 73.
3. `R1` has no left child and has right child `R3`, value 58.
4. `R2` has left child `R4`, value 11, and no right child.
5. `R3` and `R4` have no children.

List the frontier from front to back:

| Completed visit | Complete frontier | Recorded visit |
|---|---|---|
| none | `R0@0` | none |
| `R0` | `R1@1, R2@1` | `R0@0` |
| `R1` | `R2@1, R3@2` | `R1@1` |
| `R2` | `R3@2, R4@2` | `R2@1` |
| `R3` | `R4@2` | `R3@2` |
| `R4` | empty | `R4@2` |

The `@` symbol reads “at depth.” The complete order is:

```text
R0@0, R1@1, R2@1, R3@2, R4@2
```

Notice that a frontier may contain two adjacent depths at once. After
visiting `R1`, it contains `R2@1` and `R3@2`.

## 5. Store visits and matches

A **struct** is a C type grouping named values called fields. `int` is C's
whole-number type. `bool` is C's yes-or-no type. `size_t` is a nonnegative
whole-number type used for counts, indexes, and depths.

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

A **key** is the stored whole number used for comparison or search. A
**flag** is a stored yes-or-no marker. A `TreeBfsVisit` copies key, flag, and
depth. A `TreeBfsOrder` stores at most 64 copied visits. A `TreeBfsMatch`
identifies one existing node and its depth; it does not own that node.
`TREE_BFS_MAX_NODES` is the fixed name for the number 64. `const` in
`const TreeNode *` permits inspection but not change through that pointer.

A **shallowest match** is a matching node with the smallest depth. If values
repeat, the first matching work record removed by this left-first procedure
is the required result.

## 6. Preview width, height, and cost

The **width** of one level is its node count. The **maximum width**, written
`w`, is the greatest level width. The reveal tree has widths 1, 2, and 2.

The **edge height** of a node is the greatest number of downward links from
that node to a leaf. A leaf has height 0; the empty tree has height -1. The
reveal root has height 2.

**Auxiliary space** is temporary working storage separate from the tree and
output. BFS uses `O(w)` auxiliary space, read “order w”: its Queue need
grows in proportion to maximum width. This does not mean the peak Queue
count must equal one level's width, because adjacent depths may coexist.

**Depth-first search (DFS)** follows one branch before returning to another.
Using `h` for tree height, its saved work uses `O(h)` auxiliary space, read
“order h.” This retrieves the Module 5 comparison.

## 7. Prepare for the Cognitive Pause

Be ready to:

1. trace frontier and visit/depth order on a new tree;
2. identify the shallowest of two equal values; and
3. calculate level widths, edge height, and space expressions.

Keep the vocabulary file closed until all three pause targets are preserved.
Do not solve the pause fixture before timing begins.
