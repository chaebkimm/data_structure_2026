# Lab — Build and Check a Small Permission Model

## Purpose

**Code** means instructions written for a computer. A **program** is a group
of instructions a computer can run, and a **function** is a named block of
code that performs one task. **C** is the programming language used in this
course. A **service** is a program that provides a function to other
programs.

A **representation** is a chosen way to store or show information, and a
**model** is a simplified representation used for reasoning. A **graph** is
a model of objects and their relationships. One object is a **vertex** and
one direct relationship is an **edge**.

Build a small graph of permitted communication between invented services. An
edge in this model means “communication is permitted”; it does not prove that
communication occurred or that a service can be exploited.
**Exploitability** means whether a weakness can actually be used to cause
harm.

A **matrix** is a rectangular arrangement of values in rows and columns.
**Fixed** means its dimensions do not grow during the activity. **Bounded**
means that a stated limit cannot be exceeded. The graph uses a fixed,
bounded matrix and does not request memory while the program runs.

## Files

You receive:

- `code/include/graph_matrix.h`
- `code/starter/graph_matrix.c`
- `code/tests/test_core.c`
- `code/tests/test_student.c`
- `code/build.ps1`
- `code/Makefile`

A **header** is a C file ending in `.h` that lists names and functions other
files may use. A **test** is code that runs one case and checks its result. A
**build script** or **Makefile** contains commands that translate source
files—files containing written code—into a runnable program.

Edit only:

- `code/starter/graph_matrix.c`
- `code/tests/test_student.c`

Do not change the supplied header or tests unless the instructor
authorizes it.

## Words used in this lab

- A **graph** is a set of objects and relationships.
- A **vertex** is one object in a graph. Its plural is **vertices**.
- An **active vertex** is a vertex included in the current graph.
- An **edge** is one relationship between vertices.
- A **directed edge** has a direction, such as `1 → 3`.
- An **undirected edge** has no direction, such as `{1, 3}`.
- A **directed graph** uses directed edges. An **undirected graph** uses
  undirected edges.
- A **neighbor** of a vertex is another vertex joined to it by an edge.
- The **source** is where a directed edge starts; the **destination** is where
  it ends.
- An **out-neighbor** is the destination of an edge leaving a vertex.
- **Out-degree** counts edges leaving a vertex; **in-degree** counts edges
  entering it.
- An **unweighted graph** records whether an edge exists but stores no cost
  on that edge. A **weighted graph** also stores a number such as distance or
  cost. This lab implements only an unweighted graph.
- A **Boolean value** is either `true` or `false`.
- A **row** runs across a matrix; a **column** runs down it.
- A **cell** is one position in a matrix.
- The **diagonal** contains cells whose row and column indexes are equal.
- **Mirrored cells** trade their row and column indexes: `[u][v]` and
  `[v][u]`.
- An **index** is a numbered position. C indexes begin at zero.
- A **function** is a named block of code that performs one task.
- An **operation** is one task provided by the graph code. To **initialize**
  a graph means to create its valid starting state.
- An **argument** is a value given to a function when asking it to run.
- A **type** describes the kind of value C stores. A **variable** is named
  storage for a value.
- An **output** is a result written into a variable supplied by the caller.
  The **caller** is the code that asks a function to run.
- A **contract** states what a function accepts, changes, returns, and
  preserves.
- An **invariant** is a rule that is true in every valid completed state.
- An **enum** is a C type whose allowed choices have names.
- A **struct** is a C type that groups named values called **fields**.
- An **array** is a numbered row of matching values. A **two-dimensional
  array** is an array of rows.
- A **pointer** is a C value that can refer to another object. A **null
  pointer** deliberately refers to no object.
- `typedef` creates a shorter type name. `#define` gives a fixed name to text
  used by the program.
- `bool` is C's type for a Boolean value.
- `const` states that a function promises not to change an object through
  that particular pointer.
- A **query** asks for stored information without changing it.

## Public representation

Here **public** means that the supplied files may use these names. `size_t`
is a nonnegative whole-number type used for counts and indexes. The suffix
`U` marks `16` as unsigned, meaning not negative. `GRAPH_MAX_VERTICES` names
the limit of 16 vertices. `GraphKind` names the direction choice, and
`GraphNeighbors` names a neighbor result.

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

typedef struct {
    size_t count;
    size_t vertices[GRAPH_MAX_VERTICES];
} GraphNeighbors;
```

`adjacency` is the matrix:

```c
graph.adjacency[from][to]
```

The first index selects a row and the second selects a column. `true` means
that the edge `from → to` exists. `false` means that it does not.

`GraphNeighbors` stores a count followed by vertex indexes in increasing
order.

A **status code** is a named result that reports success or a kind of
failure. **Malformed** means that stored values break at least one completed
graph rule.

| Status | Meaning |
|---|---|
| `GRAPH_OK` | The operation succeeded |
| `GRAPH_ERR_INVALID_ARGUMENT` | A required pointer is null or an initialization choice is unknown |
| `GRAPH_ERR_OUT_OF_RANGE` | A count or vertex index is outside its allowed range |
| `GRAPH_ERR_SELF_LOOP` | The requested edge would join a vertex to itself |
| `GRAPH_ERR_EDGE_EXISTS` | The requested edge already exists |
| `GRAPH_ERR_EDGE_ABSENT` | The requested edge does not exist |
| `GRAPH_ERR_INVALID_GRAPH` | The stored graph is malformed |

## Completed-graph rules

A **self-loop** connects a vertex to itself. The **endpoints** are the
vertices at the ends of an edge. **Parallel edges** are repeated edges with
the same endpoints and, in a directed graph, the same direction. A **simple
graph** forbids self-loops and parallel edges.

A completed course graph satisfies all these rules:

1. `vertex_count` is at most `GRAPH_MAX_VERTICES`.
2. `kind` is `GRAPH_DIRECTED` or `GRAPH_UNDIRECTED`.
3. Active vertex indexes are exactly `0` through `vertex_count - 1`.
   The **active square** is the part of the matrix in those active rows and
   columns.
4. Every diagonal cell `adjacency[v][v]` is `false`, so no self-loop exists.
5. In an undirected graph, `adjacency[u][v]` equals
   `adjacency[v][u]`. This equality across the diagonal is called
   **symmetry**.
6. One Boolean cell represents one possible directed edge, so the matrix
   cannot store parallel copies.

A **route** is a vertex sequence in which every consecutive pair has the
required edge. A **path** is a route that does not repeat a vertex. A
**cycle** is a route that returns to its start without repeating another
vertex. A **tree** is a restricted graph with one starting vertex called its
**root**, one immediately preceding vertex called a **parent** for every
other vertex, and no cycle. An **isolated vertex** has no edges. Cycles are
allowed here, and a graph may also have several routes to one vertex or an
isolated vertex.

## Core checkpoints

### 1. Initialize the graph

Complete `graph_init`.

- Reject a null graph pointer.
- Reject a vertex count above 16.
- Reject a `GraphKind` value other than the two named choices.
- On success, store the count and kind and set every matrix cell to `false`.
- On failure, leave the caller's graph unchanged.

You do not need to understand every supplied helper function. Use its written
contract and edit only marked `TODO` regions. `TODO` labels work that remains
to be completed.

### 2. Add an edge

Complete `graph_add_edge`.

- Both vertex indexes must be active.
- Reject a self-loop.
- Reject an edge that already exists.
- For a directed graph, set only `adjacency[from][to]`.
- For an undirected graph, set both mirrored cells.
- Make no change after an error.

The two cells are **mirrored** because their row and column indexes trade
places.

### 3. Remove and query an edge

Complete `graph_remove_edge` and `graph_has_edge`.

Removing a missing edge reports `GRAPH_ERR_EDGE_ABSENT`. Querying writes
`true` or `false` to the output only after every check succeeds.

For an undirected edge, both mirrored cells must agree before the operation.
If they disagree, return `GRAPH_ERR_INVALID_GRAPH`.

### 4. Count incoming and outgoing edges

Complete `graph_out_degree` and `graph_in_degree`.

- Out-degree counts `true` cells across one row.
- In-degree counts `true` cells down one column.
- In an undirected graph, the two counts are equal.
- Change the output only after the complete count succeeds.

### 5. Report out-neighbors

Complete `graph_out_neighbors`.

Scan columns from index zero upward. Store each `true` destination in
`GraphNeighbors.vertices`; the result must therefore be in increasing order.
Copy the result to the output only after all checks succeed.

The supplied demonstration can print this returned list. Your function does
not need to perform screen output.

### 6. Use the supplied whole-graph validator

A **validator** is a function that checks rules. `graph_validate` checks the
full active matrix for diagonal self-loops and, for an undirected graph,
symmetry.

Ordinary operations check the selected edge or vertex. They do not scan
unrelated matrix positions. Therefore a defect elsewhere may remain unseen
until `graph_validate` checks the whole graph.

### 7. Interpret operation costs

**Operation cost** describes how work grows as the graph grows. Let `V` mean
the number of vertices. **Big-O notation** is the `O(...)` shorthand below
for that growth.

- Querying, adding, or removing one edge examines a fixed number of cells:
  `O(1)`, or constant work.
- Counting degree or reporting neighbors scans one row or column: `O(V)`.
- Full validation scans the matrix: `O(V²)`, meaning up to `V × V` cells.
- A general matrix for `V` vertices uses `O(V²)` cells. This bounded lab
  always reserves `16 × 16 = 256` cells, and only its active `V × V` square
  describes graph edges.

These costs are for the supplied representation. Formal methods for
exploring a graph appear later.

### 8. Design three tests

Inspect the supplied tests. Add three cases that are not direct copies:

A **boundary case** uses a value at or near an allowed limit. **Invalid
input** breaks a function's contract. A test **rationale** is a short
explanation of why the test adds useful evidence.

- one boundary or invalid-input case;
- one directed-versus-undirected case; and
- one additional contract or invariant risk you identify.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The execution-policy option applies only to the PowerShell started by that
command.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

A **compiler** translates C source into a program the computer can run. If no
compiler is available, use the instructor's approved CI or classroom
compiler. **CI**, or continuous integration, means another computer
automatically builds and tests submitted code. A compiler **warning** is a
message about code that may be mistaken even when translation can continue.

## Constraints

- Do not request or release **dynamic memory**, meaning storage obtained or
  returned while the program runs.
- Do not change `GRAPH_MAX_VERTICES`.
- Do not treat an edge as proof of real communication activity or
  exploitability.
- Do not change a caller's output after an error.
- Do not implement **depth-first search (DFS)** or **breadth-first search
  (BFS)**. Both are planned methods for exploring a graph and appear later.

## Required submission

**Spiral 1** is the course's first Linear → Tree → Graph sequence.

1. completed `graph_matrix.c`;
2. supplied-test transcript, meaning saved text printed by the test run;
3. three passing student-authored tests with rationale;
4. compiler-warning or instructor-CI evidence;
5. completed evidence record;
6. Matrix Symmetry Autopsy;
7. corrected Cognitive Pause; and
8. Spiral 1 structure-choice comparison.
