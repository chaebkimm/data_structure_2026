# Stage C — Investigation Worksheet: Linear Accessible Format

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.
Sections A through F are required core work. Preserve them before opening
Stage D. Sections G through I are extension work for the announced
independent-work window.

This version states relationships and traces in numbered sentences. It has
the same IDs, values, questions, order, and assessment weight as the
standard worksheet.

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

1. `C0` stores value 42, flag F, and is the root.
2. `C0` has left child `C1` and right child `C2`.
3. `C1` stores 17, flag T; it has left child `C3` and right child `C4`.
4. `C2` stores 68, flag F; it has left child `C5` and right child `C6`.
5. `C3` stores 23, flag F, and has no children.
6. `C4` stores 91, flag T; it has left child `C7` and no right child.
7. `C5` stores 17, flag T, and has no children.
8. `C6` stores 5, flag F; it has no left child and right child `C8`.
9. `C7` stores 44, flag T, and has no children.
10. `C8` stores 44, flag F, and has no children.

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

Response:

### A3. Explain the equal-depth tie

Why does adding the left child before the right child make the left child
leave first?

Response:

### A4. Explain the valid-tree boundary

Why does this valid tree need no visited record? Name the kind of
relationship that would make a visited record necessary.

Response:

## B. Trace and search the canonical tree

Complete each frontier from front to back. Include every node label and
depth.

1. Before any visit, the frontier is `C0@0`.
2. After visiting `C0`, the frontier is ______________________________.
3. After visiting `C1`, the frontier is ______________________________.
4. After visiting `C2`, the frontier is ______________________________.
5. After visiting `C3`, the frontier is ______________________________.
6. After visiting `C4`, the frontier is ______________________________.
7. After visiting `C5`, the frontier is ______________________________.
8. After visiting `C6`, the frontier is ______________________________.
9. After visiting `C7`, the frontier is ______________________________.
10. After visiting `C8`, the frontier is _____________________________.

### B1. Complete visit records

Write the complete visit order. For each visit, give node label, stored
value, flag, and depth.

Response:

### B2. Find the peak Queue count

What is the largest Queue count in this trace? Identify one state that has
that count. Why should this one example not be used to claim that Queue
count always equals one level's width?

Response:

### B3. Search for repeated value 17

Using Queue limit 2, which node is returned, at what depth, and which nodes
are inspected through the successful match?

Response:

### B4. Search for repeated value 44

Using Queue limit 4, both matches have equal depth. Which node is returned,
and which left-before-right decision explains the result?

Response:

### B5. Search for missing value 99

Using Queue limit 4, which status should be reported? What must happen to
the caller's previous match output?

Response:

## C. Measure depth, width, height, and balance

The **width** of one level is its node count. Maximum width is `w`.
**Edge height** is the greatest downward-link count to a leaf:
`height(NULL) == -1` and `height(leaf) == 0`. A **balance factor** is left
child height minus right child height.

### C1. Record every depth

Record the depth of `C0`, `C1`, `C2`, `C3`, `C4`, `C5`, `C6`, `C7`, and
`C8`, in that order.

Response:

### C2. Record every level width

Give the width at each depth and identify maximum width `w`.

Response:

### C3. Calculate heights from the leaves upward

Give the height of every node and the height of the complete tree.

Response:

### C4. Apply the edge-height convention

What are the heights of an empty tree, one leaf, and an `n`-node one-child
chain?

Response:

### C5. Calculate balance factors

Give the balance factor of every nonleaf node in the canonical tree.

Response:

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

Response:

### D2. Compare search guarantees

Why does the first BFS match have minimum depth? Why does an ordinary DFS
first match not make that guarantee?

Response:

### D3. State full-traversal costs

Let `n` be node count, `w` maximum width, and `h` edge height. State BFS
time and auxiliary space, then DFS time and auxiliary space.

Response:

### D4. Compare wide and skewed shapes

Which method may need more working storage on a very wide shallow tree?
Which may need more on a long one-child chain? Explain with `w` and `h`.

Response:

### D5. Separate output from working storage

Why is the `TreeBfsOrder` result not included in the `O(w)` auxiliary-space
claim?

Response:

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

1. Level order of `NULL`, Queue limit 0.
2. Level order of a nonempty tree, Queue limit 0.
3. Canonical level order, Queue limit 4.
4. Canonical level order, Queue limit 3.
5. Any BFS operation with Queue limit 65.
6. Shallowest search of `NULL` for 17, Queue limit 0.
7. Shallowest search of the canonical tree for 17, Queue limit 2.
8. Shallowest search of the canonical tree for 99, Queue limit 4.
9. Canonical height, Queue limit 4.
10. Canonical height, Queue limit 3.
11. Height of `NULL`, Queue limit 0.
12. A required output pointer is `NULL`.
13. Supplied node creation cannot allocate a node.
14. Insert a duplicate key into a strict BST.

For every numbered request, record:

```text
status:
required output effect:
```

### E1. Name the three TODO operations

Write the exact names and one-sentence purpose of the three functions
students complete.

Response:

### E2. Explain failure preservation

Why should traversal, search, and height build a local candidate and commit
the caller's output only after the operation's required result is known?

Response:

### E3. State Queue storage and ownership

Where is the supplied typed Queue's fixed work array stored? Does the Queue
allocate, release, own, or change any tree node?

Response:

### E4. State tree nonmutation

**Nonmutation** means inspecting an input without changing it. What may
these functions read, and what tree fields may they change?

Response:

### E5. State the input precondition

A **precondition** is a fact the caller must ensure before an operation.
Why must the caller provide an acyclic, unshared tree? What could happen if
links reconnect without a visited record?

Response:

## F. Preview imbalance and one rotation

This separate fixture is a strict **binary search tree (BST)**: lower keys
are in left subtrees and higher keys are in right subtrees. Strict means
equal keys are rejected.

The relationships are:

1. root key 30 has left child key 20 and no right child;
2. key 20 has left child key 10 and no right child; and
3. key 10 has no children.

A **rotation** is a small rearrangement of links that preserves BST order.
This module traces one supplied rotation; it does not implement balancing.

### F1. Measure the skewed BST

Give each node's height and balance factor before any link changes.

Response:

### F2. Identify the imbalance

An **AVL tree** is a BST kept within balance factors `-1` through `1`. Which
node is outside that later AVL range?

Response:

### F3. Trace one right rotation

After an instructor-supplied right rotation at 30, state the root and every
left/right child relationship.

Response:

### F4. Check what remains true

State the inorder sequence, new root height, and all new balance factors.

Response:

### F5. Respect the preview boundary

List two balancing topics that this module deliberately does not require.

Response:

## G. Design three tests — extension

A **test** runs a case and checks an expected result. A **regression test**
is retained so a repaired defect does not return. Design tests in this exact
order.

### G1. Level order and depths

Use a small synthetic tree to check an exact left-first level order. Check
every copied key, flag, and depth.

Response:

### G2. Shallowest duplicate and missing preservation

Repeat a key at two locations. Check the selected shallowest match, then
check that a missing-key result preserves the previous match output.

Response:

### G3. Height and Queue boundary

Check exact edge height. Then use a too-small Queue limit and prove
`TREE_BFS_LIMIT` preserves the prior height output.

Response:

## H. Conduct an autopsy and transfer to graphs — extension

### H1. Predict the isolated program

In the Tree BFS Autopsy, predict the complete faulty visit order and which
equal-depth node is returned for value 44.

Response:

### H2. Locate the first broken decision

Record the first decision that breaks the published course order, the
smallest repair, and one regression test.

Response:

### H3. Transfer to graph BFS

A **graph** is a general network whose routes may reconnect. Why must graph
BFS usually record an item as visited even though this valid tree traversal
does not?

Response:

## I. Exit reflection — extension

### I1. Answer the macro-question

In two sentences, explain how BFS guarantees that nodes close to the root
are inspected before deeper nodes.

Response:

### I2. Compare the spiral steps

Name one Queue idea reused from Module 7, one tree idea reused from Modules
2 or 5, and one BFS idea that is new.

Response:

### I3. Preserve and correct

Preserve one initial Stage A claim, then write a labeled correction
supported by a frontier trace, search result, measurement, or test.

Response:
