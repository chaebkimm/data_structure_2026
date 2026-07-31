# Stage C — Investigation Worksheet: Nearer Tree Nodes First

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.
Sections A through F are required core work. Preserve them before opening
Stage D. Sections G through I are extension work for the announced
independent-work window.

## Quick reference

A **tree** is a hierarchy of nodes with one starting **root**.
**Breadth-first search (BFS)** visits nodes in nondecreasing depth: depth may
stay the same or increase, but it never decreases. **Depth** is the number
of child links from the root. **Level order** is the resulting tree order.
A node is **discovered** when it is reached and placed in the waiting Queue.
The **frontier** is a Queue of discovered nodes waiting to be visited. Each
Queue record contains a node pointer and its depth. A **pointer** identifies
an object's memory location. A Queue removes the earliest-added work first.

`NULL` means “no node.” The course procedure removes the front record,
visits it, then adds its non-`NULL` left child before its non-`NULL` right
child. A **valid course tree** has no cycle, meaning a route back, and no
shared node reached through two parent links.

This is the canonical course tree. Labels identify objects; repeated stored
values are deliberate. `T` means the flag is true and `F` means false.
Numeric values do not control its links, and BFS does not sort them.

```text
C0(42,F)
├─ left: C1(17,T)
│  ├─ left: C3(23,F)
│  └─ right: C4(91,T)
│     └─ left: C7(44,T)
└─ right: C2(68,F)
   ├─ left: C5(17,T)
   └─ right: C6(5,F)
      └─ right: C8(44,F)
```

## A. Apply the Queue-controlled rule

### A1. Complete the procedure

Complete the blanks.

```text
if the root exists:
    enqueue (__________________, depth ______)

while the Queue is not empty:
    __________________ one work record
    visit its node
    enqueue its non-NULL __________________ child at parent depth + 1
    enqueue its non-NULL __________________ child at parent depth + 1
```

### A2. Explain nondecreasing depth

Why can a newly discovered child not pass a smaller-depth record already
waiting in the Queue?

____________________________________________________________________

### A3. Explain the equal-depth tie

Why does adding the left child before the right child make the left child
leave first?

____________________________________________________________________

### A4. Explain the valid-tree boundary

Why does this valid tree need no visited record? Name the kind of
relationship that would make a visited record necessary.

____________________________________________________________________

## B. Trace and search the canonical tree

Complete the frontier from front to back. Include every node label and
depth.

| Completed visit | Complete frontier after adding children |
|---|---|
| none | `C0@0` |
| `C0` | |
| `C1` | |
| `C2` | |
| `C3` | |
| `C4` | |
| `C5` | |
| `C6` | |
| `C7` | |
| `C8` | |

### B1. Complete visit records

Write the complete visit order. For each visit, give node label, stored
value, flag, and depth.

____________________________________________________________________

____________________________________________________________________

### B2. Find the peak Queue count

What is the largest Queue count in this trace? Identify one state that has
that count. Why should this one example not be used to claim that Queue
count always equals one level's width?

____________________________________________________________________

### B3. Search for repeated value 17

Using Queue limit 2, which node is returned, at what depth, and which nodes
are inspected through the successful match?

____________________________________________________________________

### B4. Search for repeated value 44

Using Queue limit 4, both matches have equal depth. Which node is returned,
and which left-before-right decision explains the result?

____________________________________________________________________

### B5. Search for missing value 99

Using Queue limit 4, which status should be reported? What must happen to
the caller's previous match output?

____________________________________________________________________

## C. Measure depth, width, height, and balance

The **width** of one level is its node count. Maximum width is `w`.
**Edge height** is the greatest downward-link count to a leaf:
`height(NULL) == -1` and `height(leaf) == 0`. A **balance factor** is left
child height minus right child height.

### C1. Record every depth

Complete the table.

| Node | `C0` | `C1` | `C2` | `C3` | `C4` | `C5` | `C6` | `C7` | `C8` |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Depth | | | | | | | | | |

### C2. Record every level width

Give the width at each depth and identify maximum width `w`.

____________________________________________________________________

### C3. Calculate heights from the leaves upward

Give the height of every node and the height of the complete tree.

____________________________________________________________________

### C4. Apply the edge-height convention

What are the heights of an empty tree, one leaf, and an `n`-node one-child
chain?

____________________________________________________________________

### C5. Calculate balance factors

Give the balance factor of every nonleaf node in the canonical tree.

____________________________________________________________________

## D. Compare BFS and DFS

**Depth-first search (DFS)** follows one branch before returning to another.
A **subtree** is one node together with everything below it. Left-first
preorder uses node, left subtree, right subtree.
**Time complexity** describes how work grows. **Auxiliary space** is
temporary working storage separate from the tree and output.
`O(x)`, read “order x,” means work or storage grows in proportion to `x`.

### D1. Compare visit orders

Write left-first preorder for the canonical tree, then state one exact
difference from its BFS order.

____________________________________________________________________

### D2. Compare search guarantees

Why does the first BFS match have minimum depth? Why does an ordinary DFS
first match not make that guarantee?

____________________________________________________________________

### D3. State full-traversal costs

Let `n` be node count, `w` maximum width, and `h` edge height. State BFS
time and auxiliary space, then DFS time and auxiliary space.

____________________________________________________________________

### D4. Compare wide and skewed shapes

Which method may need more working storage on a very wide shallow tree?
Which may need more on a long one-child chain? Explain with `w` and `h`.

____________________________________________________________________

### D5. Separate output from working storage

Why is the `TreeBfsOrder` result not included in the `O(w)` auxiliary-space
claim?

____________________________________________________________________

## E. Apply the public contracts

A **contract** states what a function accepts, changes, reports, and
preserves. The **caller** is the code asking a function to run. An
**allocation** is storage requested while a program runs. A **status code**
is a named result. The statuses, in header-file order, are:

1. `TREE_BFS_OK`;
2. `TREE_BFS_INVALID_ARGUMENT`;
3. `TREE_BFS_LIMIT`;
4. `TREE_BFS_ALLOCATION`;
5. `TREE_BFS_DUPLICATE`; and
6. `TREE_BFS_NOT_FOUND`.

Match each independent request to its status and output promise.

| Request | Status | Required output effect |
|---|---|---|
| level order of `NULL`, Queue limit 0 | | |
| level order of a nonempty tree, Queue limit 0 | | |
| canonical level order, Queue limit 4 | | |
| canonical level order, Queue limit 3 | | |
| any BFS operation with Queue limit 65 | | |
| shallowest search of `NULL` for 17, Queue limit 0 | | |
| shallowest search of the canonical tree for 17, Queue limit 2 | | |
| shallowest search of the canonical tree for 99, Queue limit 4 | | |
| canonical height, Queue limit 4 | | |
| canonical height, Queue limit 3 | | |
| height of `NULL`, Queue limit 0 | | |
| a required output pointer is `NULL` | | |
| supplied node creation cannot allocate a node | | |
| insert a duplicate key into a strict BST | | |

### E1. Name the three TODO operations

Write the exact names and one-sentence purpose of the three functions
students complete.

____________________________________________________________________

### E2. Explain failure preservation

Why should traversal, search, and height build a local candidate and commit
the caller's output only after the operation's required result is known?

____________________________________________________________________

### E3. State Queue storage and ownership

Where is the supplied typed Queue's fixed work array stored? Does the Queue
allocate, release, own, or change any tree node?

____________________________________________________________________

### E4. State tree nonmutation

**Nonmutation** means inspecting an input without changing it. What may
these functions read, and what tree fields may they change?

____________________________________________________________________

### E5. State the input precondition

A **precondition** is a fact the caller must ensure before an operation.
Why must the caller provide an acyclic, unshared tree? What could happen if
links reconnect without a visited record?

____________________________________________________________________

## F. Preview imbalance and one rotation

This separate fixture is a strict **binary search tree (BST)**: lower keys
are in left subtrees and higher keys are in right subtrees. Strict means
equal keys are rejected.

```text
    30
   /
  20
 /
10
```

A **rotation** is a small rearrangement of links that preserves BST order.
This module traces one supplied rotation; it does not implement balancing.

### F1. Measure the skewed BST

Give each node's height and balance factor before any link changes.

____________________________________________________________________

### F2. Identify the imbalance

An **AVL tree** is a BST kept within balance factors `-1` through `1`. Which
node is outside that later AVL range?

____________________________________________________________________

### F3. Trace one right rotation

After an instructor-supplied right rotation at 30, state the root and every
left/right child relationship.

____________________________________________________________________

### F4. Check what remains true

State the inorder sequence, new root height, and all new balance factors.

____________________________________________________________________

### F5. Respect the preview boundary

List two balancing topics that this module deliberately does not require.

____________________________________________________________________

## G. Design three tests — extension

A **test** runs a case and checks an expected result. A **regression test**
is retained so a repaired defect does not return. Design tests in this exact
order.

### G1. Level order and depths

Use a small synthetic tree to check an exact left-first level order. Check
every copied key, flag, and depth.

____________________________________________________________________

### G2. Shallowest duplicate and missing preservation

Repeat a key at two locations. Check the selected shallowest match, then
check that a missing-key result preserves the previous match output.

____________________________________________________________________

### G3. Height and Queue boundary

Check exact edge height. Then use a too-small Queue limit and prove
`TREE_BFS_LIMIT` preserves the prior height output.

____________________________________________________________________

## H. Conduct an autopsy and transfer to graphs — extension

### H1. Predict the isolated program

In the Tree BFS Autopsy, predict the complete faulty visit order and which
equal-depth node is returned for value 44.

____________________________________________________________________

### H2. Locate the first broken decision

Record the first decision that breaks the published course order, the
smallest repair, and one regression test.

____________________________________________________________________

### H3. Transfer to graph BFS

A **graph** is a general network whose routes may reconnect. Why must graph
BFS usually record an item as visited even though this valid tree traversal
does not?

____________________________________________________________________

## I. Exit reflection — extension

### I1. Answer the macro-question

In two sentences, explain how BFS guarantees that nodes close to the root
are inspected before deeper nodes.

____________________________________________________________________

### I2. Compare the spiral steps

Name one Queue idea reused from Module 7, one tree idea reused from Modules
2 or 5, and one BFS idea that is new.

____________________________________________________________________

### I3. Preserve and correct

Preserve one initial Stage A claim, then write a labeled correction
supported by a frontier trace, search result, measurement, or test.

____________________________________________________________________
