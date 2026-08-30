# Stage C — Investigation: Linear Accessible Format

This version has the same facts, questions, and learning targets as the
standard investigation. It replaces the drawing and table response spaces
with line-by-line text. Open it after preserving the Cognitive Pause;
`vocabulary.md` may now be used. Complete Sections A–E before Stage D.

## A. Translate the canonical model

Use vertices 0 Web, 1 App, and 2 Database with directed edges `0 → 1`,
`1 → 2`, and `1 → 0`.

### A1. Equivalent representations

Describe every arrow line by line and write the edge set as ordered pairs.

Response:

State three active matrix rows, each with columns 0, 1, and 2 in order.

Response:

How many arrows, ordered pairs, and `1` cells should agree?

Response:

### A2. Row and column meaning

What question does row 1 answer? What different question does column 1
answer?

Response:

Why does `grid[0][1]` not by itself prove anything about `grid[1][0]`?

Response:

## B. Count and change local relationships

### B1. Degree by inspection

Give App’s out-degree and Web’s in-degree. Name the cells counted in each
answer.

Response:

### B2. One-cell removal

Predict the active matrix rows after removing `1 → 2`. Which cells must remain
unchanged? What is App’s new out-degree?

Response:

### B3. Idempotent updates

Why does setting an existing edge to `1` again leave the same graph? Why does
setting an absent edge to `0` again do the same?

Response:

## C. Audit the invariant

The physical grid has capacity 16 while `vertex_count` may be smaller.

### C1. Active versus physically in bounds

For `vertex_count == 3`, list the active indexes. Explain why index 3 is
physically in the grid but is not a valid endpoint.

Response:

### C2. Classify completed states

For each independent stored fact, write `valid` or `invalid` and name the
relevant rule:

1. `grid[2][0] == 1`
2. `grid[2][2] == 1`
3. `grid[3][1] == 1` when `vertex_count == 3`
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

State one route from Web to Database. State the cycle formed by Web and App.
Why must a procedure following links remember where it has already been?

Response:

### D2. Shared destinations

Suppose Web and App both had edges to Database. Why is that valid in a graph
but incompatible with a one-parent tree model?

Response:

### D3. An isolated active vertex

Describe the row and column of an isolated active vertex. How is that vertex
different from an inactive index?

Response:

## E. Compare representations without expanding the lab

### E1. Directed, undirected, and weighted

How would two opposite directed cells represent a two-way relationship? Why
does that comparison leave `struct DirectedGraph` directed?

Response:

Why can the course’s binary cell not also store a delay or cost?

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
3. permissions that may return to an earlier service.

Response:

An edge here means “communication is permitted.” Name one conclusion that it
does not support.

Response:

## Stage C exit sentence

Complete: “The matrix cell at row __________, column __________ records
__________; a valid completed graph also guarantees __________.”
