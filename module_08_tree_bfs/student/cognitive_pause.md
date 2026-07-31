# Stage B — Five-Minute Cognitive Pause

Read the starting definitions and tree with the instructor before timing
begins. Then use no notes, slides, classmates, vocabulary file, or coding
tools for five minutes. The vocabulary remains closed until all three
responses are preserved.

You may draw, type, dictate, or answer in numbered sentences. An approved
extended-time or asynchronous version uses the same fixture and exactly the
same three targets. Speed, handwriting, and drawing quality are not
assessed.

## Starting definitions

A **tree** is a hierarchy of nodes. Its one starting node is the **root**,
and a **child** is a node directly below another.

**Breadth-first search (BFS)** visits smaller node depths before larger
depths. **Depth** is the child-link count from the root; the root has depth
0. At one depth, this course visits left before right.

A node is **discovered** when it is reached and placed in the waiting Queue.
The **frontier** is a Queue of discovered, unvisited work records. Each
record contains a node and its depth. A **Queue** removes the earliest-added
waiting record first. List the frontier from front to back.

The **width** of a level is the number of nodes at that depth. `w` means
maximum width. **Edge height** is the greatest downward-link count from a
node to a leaf; a leaf has height 0, an empty tree has height -1, and `h`
means tree height. **Auxiliary space** is temporary working storage separate
from the tree and output. **Depth-first search (DFS)** follows one branch
before returning to another. `O(x)`, read “order x,” means storage grows in
proportion to quantity `x`.

## Starting tree

```text
P0(60)
├─ left: P1(14)
│  ├─ left: P3(7)
│  └─ right: P4(35)
│     └─ left: P6(92)
└─ right: P2(83)
   └─ right: P5(14)
```

Exact linear equivalent:

1. `P0`, value 60, is the root.
2. `P0` has left child `P1`, value 14, and right child `P2`, value 83.
3. `P1` has left child `P3`, value 7, and right child `P4`, value 35.
4. `P2` has no left child and has right child `P5`, value 14.
5. `P4` has left child `P6`, value 92, and no right child.
6. `P3`, `P5`, and `P6` have no children.

## Target 1 — Trace waiting work

State:

1. the initial frontier;
2. the frontier immediately after visiting `P0`;
3. the frontier immediately after visiting `P1`; and
4. the complete visit sequence, including every node label and depth.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 — Choose the shallowest match

The search target is stored value `14`.

State:

1. the node label returned;
2. its depth; and
3. why the other node storing 14 is not returned.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 — Measure shape and working space

State:

1. the width at every depth, beginning with depth 0;
2. maximum width `w`;
3. edge height `h`; and
4. the BFS auxiliary-space expression using `w` and the DFS
   auxiliary-space expression using `h`.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

When the instructor releases the expert model:

1. preserve your initial response;
2. check reasoning that remains correct;
3. label each correction `frontier`, `depth`, `match`, `width`, `height`, or
   `space`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
