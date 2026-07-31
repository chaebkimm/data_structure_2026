# Stage B — Formal Names and a Storage Choice

Open this file only after preserving the Stage A inquiry.

A **representation** is a chosen way to store or show information.
**Equivalent** representations show the same facts in different forms.

## 1. Name the general structure

A **model** is a simplified description used for reasoning. A **graph** is a
model made of objects and the relationships between them.

- A **vertex** is one object in a graph. The plural is **vertices**.
- An **edge** is one direct relationship between two vertices.
- The two vertices named by an edge are its **endpoints**.
- A **directed edge** has one direction. The arrow `0 → 1` goes from vertex
  0 to vertex 1.
- An **undirected edge** has no direction. The notation `{0, 1}` connects
  vertices 0 and 1 both ways.
- A **directed graph** uses directed edges.
- An **undirected graph** uses undirected edges.

A **program** is a group of instructions a computer can run. A **service**
is a program that performs a task for other programs.

The six Stage A services become these vertices:

- 0: Gateway
- 1: Web
- 2: Admin
- 3: Database
- 4: Monitor
- 5: Archive

Having no edge is called **isolated**. Archive is isolated.

## 2. List the edges

A **set** is a collection in which an item appears at most once. An
**ordered pair** is a pair whose first and second positions have different
roles. An **edge set** lists a graph’s edges.

The Stage A one-way relationships form this directed edge set:

```text
{(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (4, 1)}
```

The ordered pair `(2, 3)` means the directed edge `2 → 3`. Reversing the
positions would name the different edge `3 → 2`.

## 3. Store direct answers in a grid

**Adjacent** vertices share a direct edge. A **matrix** is a rectangular grid
of values arranged in horizontal rows and vertical columns. An **adjacency
matrix** uses one row and one column for each vertex. A **cell** is one
position in the grid. An **index** is a numbered position; C begins indexes
at zero.

For a directed graph, the cell in row `from` and column `to` answers:

> Does the edge `from → to` exist?

A **Boolean value** has only two choices: `true` or `false`. The table below
uses `1` for `true` and `0` for `false`.

| From \ To | 0 | 1 | 2 | 3 | 4 | 5 |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 0 | 1 | 1 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 2 | 0 | 0 | 0 | 1 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 | 1 | 0 |
| 4 | 0 | 1 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 |

An **outgoing edge** leaves a vertex. For example:

- row 2, column 3 is `1`, so `2 → 3` exists;
- row 3, column 2 is `0`, so `3 → 2` does not exist; and
- row 5 contains only `0`, so Archive has no outgoing edge.

## 4. See how direction changes the matrix

Let `u` and `v` stand for two different vertex indexes. In an undirected
graph, one edge connects both ways. Storing `{u, v}`
therefore sets both row `u`, column `v` and row `v`, column `u` to `true`.

The two cells `[u][v]` and `[v][u]` are **mirrored cells** because their row
and column positions trade places.

The top-left-to-bottom-right **diagonal** contains cells whose row and column
numbers match. A matrix is **symmetric** when every cell has the same value
as the cell across that diagonal. An undirected adjacency matrix is symmetric
because each edge is recorded in both mirrored cells.

The directed matrix above need not be symmetric. It stores `0 → 1` without
claiming that `1 → 0` exists.

## 5. Separate numbers from existence

A **weight** is a number attached to an edge, such as distance, time, or
cost. A **weighted graph** stores edge weights. An **unweighted graph**
records only whether an edge exists.

This module implements an unweighted graph. Each matrix cell is Boolean, so
it cannot also store a weight. Weighted graphs are a concept in this module;
their step-by-step methods and C storage come later.

## 6. Preview the stored form

**C** is the programming language used in this course. A **type** describes
the kind of value C stores. A **variable** is named storage for a value. A
**struct** is a C type that groups related variables, and a **field** is one
named variable inside a struct.

An **enum** is a C type whose allowed choices have names. An **array** is a
numbered row of matching values. A **two-dimensional array** is an array of
rows, so it can represent a matrix. `size_t` is a nonnegative whole-number
type used for counts and indexes. `bool` is C’s Boolean type. `typedef`
creates a shorter type name.

`#define` gives a fixed name to text used by the program. Here,
`GRAPH_MAX_VERTICES` names the storage limit. The suffix `U` marks `16` as
an unsigned value, which means a value that is not negative.

```c
#define GRAPH_MAX_VERTICES 16U

typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;
```

An **active vertex** is included in the current graph. `vertex_count` stores
how many vertex indexes are active. `kind` records
whether edges are directed or undirected. `adjacency[from][to]` stores the
Boolean answer for the possible edge `from → to`. The fixed matrix reserves
16 rows and 16 columns; this module does not resize it.

## 7. Prepare for individual thinking

Review how one edge appears in an edge set and in a matrix. Do not open
`vocabulary.md` until after the five-minute individual activity has been
completed and preserved.

One representation question:

____________________________________________________________________
