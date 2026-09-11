# Stage C — Investigation: Linear Accessible Format

This version has the same facts, questions, and learning targets as the
standard investigation. It replaces the drawing and table response spaces
with line-by-line text. Open it after preserving the Cognitive Pause and
completing calibration. The 30 numbered core entries in `vocabulary.md` may
now be used. Complete and preserve Sections A–E before opening the Stage D
textbook or the vocabulary supplement.

## A. Translate the canonical model

Use accounts 0 Mina, 1 Joon, 2 Sora, 3 Dae, 4 Hana, 5 Leo, and 6 Nuri.
The complete edge set is `0 → 1`, `1 → 2`, `2 → 0`, `2 → 3`, `4 → 5`,
and `5 → 4`. Each arrow points from the follower to the followed account.

Unless a question states a change, use this original seven-account graph.
Treat hypothetical changes in different questions independently.

### A1. Equivalent representations

Describe every arrow line by line and write the edge set as ordered pairs.

Response:

State all seven active matrix rows, each with columns 0 through 6 in order.

Response:

How many arrows, ordered pairs, and `1` cells should agree?

Response:

### A2. Row and column meaning

What question does row 2 answer about Sora? What different question does
column 2 answer?

Response:

Why does `grid[0][1]` not by itself prove anything about `grid[1][0]`?

Response:

## B. Count and change local relationships

### B1. Degree by inspection

Give Sora's out-degree and Mina's in-degree. Name the cells counted in each
answer.

Response:

### B2. One-cell removal

Predict the active matrix rows after Sora unfollows Dae by removing `2 → 3`.
Which cells must remain unchanged? What is Sora's new out-degree?

Response:

### B3. Idempotent updates

Why does setting an existing edge to `1` again leave the same graph? Why does
setting an absent edge to `0` again do the same?

Response:

## C. Audit the invariant

The physical grid has capacity 16 while `vertex_count` may be smaller.

### C1. Active versus physically in bounds

For `vertex_count == 7`, list the active indexes. Explain why index 7 is
physically in the grid but is not a valid endpoint.

Response:

### C2. Classify completed states

For each independent stored fact, write `valid` or `invalid` and name the
relevant rule:

1. `grid[2][0] == 1`
2. `grid[2][2] == 1`
3. `grid[7][1] == 1` when `vertex_count == 7`
4. `grid[0][2] == 2`

Response:

### C3. Clean the whole grid

Why must initialization clear all 16 rows and 16 columns instead of only the
active square?

Response:

What must add, remove, and out-degree preserve when an argument is invalid?

Response:

## D. Reason about graph relationships

### D1. Routes and cycles

State one route from Mina to Dae. State the cycle through Mina, Joon, and
Sora. Why must a procedure following links remember where it has already
been?

Response:

### D2. Shared destinations

Suppose Mina also follows Dae while Sora continues to follow Dae. Why are
these two incoming edges valid in a graph but incompatible with a one-parent
tree model?

Response:

### D3. Isolated, followed, or inactive

Describe Nuri's row and column. Compare them with Dae's row and column in the
original graph: why is Nuri isolated but Dae is not? How are both accounts
different from inactive index 7?

Response:

## E. Compare representations without expanding the lab

### E1. Directed, undirected, and weighted

How would two opposite directed cells represent a two-way relationship? Why
does that comparison leave `struct DirectedGraph` directed?

Response:

Why can the course’s binary cell not also store an interaction count?

Response:

### E2. Matrix, edge list, and adjacency list

For each representation, describe one direct edge lookup, finding outgoing
neighbors, and storage when few edges exist:

1. adjacency matrix;
2. edge list; and
3. adjacency list.

Response:

Which representation best matches a small fixed graph with frequent direct
edge questions? Give one tradeoff.

Response:

### E3. Transfer and model boundary

Choose a fixed ArrayList, a binary tree, or a directed graph for each and give
one reason:

1. event codes kept in numbered order;
2. a hierarchy with meaningful left and right child positions; and
3. follow relationships that may lead back to an earlier account.

Response:

An edge here means “the source account follows the destination account.”
Name one conclusion about the accounts or their posts that it does not
support.

Response:

## Stage C exit sentence

Complete: “The matrix cell at row __________, column __________ records
__________; a valid completed graph also guarantees __________.”
