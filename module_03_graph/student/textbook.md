# Student Notes — Graphs and Their Representations

## Essential question

> How can a computer store relationships that may cross, point backward, or
> return to where they began?

## 1. The problem

Imagine six services. A service is a computer program that performs a task
for another program. A program is a set of instructions a computer can run.
A communication permission says which service may contact another.

More than one service may contact the same destination. A permission may
also point back toward an earlier service. A tree cannot represent these
facts without breaking its one-parent or no-cycle rules.

A graph represents objects and their relationships:

- a vertex is one object;
- an edge is one direct relationship.

A directed edge works one way. The arrow `0 → 1` starts at vertex 0 and ends
at vertex 1. It does not also mean `1 → 0`. A directed graph uses directed
edges.

## 2. One graph, four views

A representation is a way to show or store information. Two representations
are equivalent when they preserve the same facts.

The six vertices are:

```text
0 Gateway   1 Web   2 Admin   3 Database   4 Monitor   5 Archive
```

Each vertex represents one service.

The companion graph-model file shows the diagram. Its exact arrow
description is:

```text
0 → 1   0 → 2   1 → 3   2 → 3   3 → 4   4 → 1
```

Vertex 5 is isolated: no edge enters or leaves it.

### Edge set

A set is a collection in which an item appears at most once. For a directed
edge, an ordered pair records the start first and the end second.

```text
{(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (4, 1)}
```

For example, `(2, 3)` records `2 → 3`. The braces above form a mathematical
edge set, whose written order does not matter. An edge-list representation
uses numbered storage for the same pairs. It also stores the vertex count 6,
because isolated vertex 5 appears in no edge pair.

### Adjacency list

Adjacent vertices are directly joined by an edge. Adjacency records these
direct connections. Because direction matters here, each adjacency list
below stores out-neighbors: the destinations of edges leaving one vertex.

```text
0:[1, 2]   1:[3]   2:[3]   3:[4]   4:[1]   5:[]
```

The empty list `[]` preserves vertex 5 even though it has no outgoing edge.

### Adjacency matrix

A matrix is a grid of rows and columns. A cell is one position in the grid.
An adjacency matrix uses one row and one column for every vertex:

```text
adjacency[from][to]
```

The row is the source, where the edge starts. The column is the destination,
where it ends. Each cell holds a Boolean value: `true` or `false`. The table
uses `1` for `true` and `0` for `false`.

| from \ to | 0 | 1 | 2 | 3 | 4 | 5 |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 0 | 1 | 1 | 0 | 0 | 0 |
| 1 | 0 | 0 | 0 | 1 | 0 | 0 |
| 2 | 0 | 0 | 0 | 1 | 0 | 0 |
| 3 | 0 | 0 | 0 | 0 | 1 | 0 |
| 4 | 0 | 1 | 0 | 0 | 0 | 0 |
| 5 | 0 | 0 | 0 | 0 | 0 | 0 |

- Cell `[0][2]` is `1`, so `0 → 2` exists.
- Cell `[2][0]` is `0`, so the reverse edge does not exist.
- Row and column 5 contain only zeroes, so vertex 5 is isolated.

## 3. Reading the graph

Direction gives us precise words:

- an out-neighbor is reached by an edge leaving the selected vertex;
- an in-neighbor has an edge entering the selected vertex;
- out-degree counts leaving edges;
- in-degree counts entering edges.

Database (3) has in-neighbors 1 and 2 and out-neighbor 4. Its in-degree is 2
and its out-degree is 1.

A path follows available edges without repeating a vertex:

```text
0 → 1 → 3 → 4
```

A cycle follows edges back to its starting vertex without repeating any
other vertex:

```text
1 → 3 → 4 → 1
```

A vertex is reachable from a stated start when a path can lead to it.
Starting at 0, vertices 0, 1, 2, 3, and 4 are reachable. Vertex 5 is not.
The starting vertex is reachable from itself without using an edge.

An undirected edge works both ways. In an undirected graph, degree counts all
edges touching a vertex. In a connected component, every vertex is joined to
every other by an undirected path, and no outside vertex can be added while
keeping that true. For example, edges `{0, 1}`, `{1, 2}`, and `{3, 4}`
produce components `{0, 1, 2}`, `{3, 4}`, and the isolated component `{5}`.

Use connected-component language only for undirected graphs in this module.
For a directed graph, name the starting vertex and use reachable.

An algorithm is a precise step-by-step method. Depth-first search (DFS) and
breadth-first search (BFS) are later algorithms for exploring reachable
vertices. This module reads only small examples by hand.

## 4. Representation invariant

The course lab stores at most 16 vertices. It uses a simple, unweighted
graph:

- simple means no self-loops or repeated copies of an edge;
- a self-loop is an edge from a vertex to itself;
- unweighted means an edge stores only present or absent.

A weight is a number attached to an edge, such as cost or travel time. A
weighted graph stores that number; this lab does not.

For the undirected edge `{2, 4}`, both `[2][4]` and `[4][2]` are `true`.
These are mirror cells because the row and column trade places. An
undirected matrix is symmetric: every cell equals its mirror. Its diagonal,
made of cells such as `[0][0]`, remains `false` because self-loops are
rejected.

An invariant is a rule that must be true in every valid completed graph:

1. `vertex_count` is from 0 through 16.
2. The graph is directed or undirected.
3. Active indexes run from 0 through `vertex_count - 1`.
4. Every active diagonal cell is `false`.
5. Every active mirror pair agrees in an undirected graph.

If `vertex_count` is 6, indexes 0 through 5 are active and index 6 is
inactive. If `vertex_count` is 0, there are no active indexes. Each Boolean
cell says only absent or present, so the lab rejects an attempt to add an
edge that is already present.

## 5. C representation and contracts

Read this code for the field meanings. You do not need to memorize its syntax
yet.

```c
typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;
```

A `struct` groups named fields:

- `typedef struct ... Graph` tells C to call this grouped value a `Graph`;
- `vertex_count` uses `size_t`, a nonnegative whole-number type for counts
  and indexes;
- `GraphKind` names a choice that is either directed or undirected, and
  `kind` stores that choice;
- `adjacency` is a two-dimensional array, meaning an array of rows;
- `bool` is C's Boolean type, so every matrix cell is `true` or `false`;
- `GRAPH_MAX_VERTICES` is the named constant for the fixed limit of 16.

A function is a named block of code that performs one task. Its contract
states what it accepts, changes, reports, and preserves. An output is an
answer written into a variable supplied by the calling code.

| Function | Successful effect | Failure promise |
|---|---|---|
| `graph_init` | Creates the requested 0–16 vertices with no edges | Leaves the supplied graph unchanged |
| `graph_validate` | Confirms the complete active matrix obeys the rules | Does not change the graph |
| `graph_add_edge` | Sets one directed cell or two undirected cells | Leaves the graph unchanged |
| `graph_remove_edge` | Clears one directed cell or two undirected cells | Leaves the graph unchanged |
| `graph_has_edge` | Reports whether one edge exists | Leaves its output unchanged |
| `graph_in_degree`, `graph_out_degree` | Report an incoming or outgoing count | Leave their output unchanged |
| `graph_out_neighbors` | Reports out-neighbors in increasing index order | Leaves its output unchanged |

A status code is a named result such as success, out of range, self-loop,
edge already present, edge absent, or invalid graph. Adding rejects a vertex
number outside the active range, a self-loop, or an existing edge. Removing
rejects an absent edge. These checks occur before a change, so failure
preserves the previous graph and output.

`graph_validate` checks the whole active matrix. Edge operations check only
their selected cells; degree and neighbor operations check only their
relevant row or column. These are bounded checks because they never inspect
more than the fixed limit or active vertex count.

The `GraphNeighbors` output has a `count` field and a `vertices` array. The
function `graph_status_name` changes a status code into readable text.

## 6. Costs and choices

Big-O notation describes how work grows. Let `V` mean the active vertex
count:

- `O(1)` means the same amount of work;
- `O(V)` means work grows with the vertex count;
- `O(V²)` means rows times columns.

| Operation | Cost | Reason |
|---|---:|---|
| Add, remove, or ask about one edge | `O(1)` | A fixed number of cells is checked |
| Report degree or out-neighbors | `O(V)` | One row or column is scanned |
| Validate the active graph | `O(V²)` | Up to `V × V` cells are checked |

The lab always reserves `16 × 16 = 256` cells. Only the active `V × V`
square describes edges.

| Representation | Useful strength | Main cost |
|---|---|---|
| Adjacency matrix | One cell answers whether an edge exists | Reserves cells for missing edges |
| Edge list | Simple when processing every edge | One-edge lookup may scan all pairs |
| Adjacency list | Direct access to a vertex's out-neighbors | Its C storage is more involved |

When only a few possible edges exist, an edge list or adjacency list may use
less memory. No representation is always best; choose from the operations
the program needs.

## 7. Spiral connection and modeling limit

| Need | Choose | Reason |
|---|---|---|
| Items in one numbered order | ArrayList | The main fact is position |
| One-parent hierarchy | Tree | Each non-root item has one parent |
| Relationships that may cross or return | Graph | General edges are allowed |

The example uses synthetic data, meaning invented data used for safe
teaching. A permission edge proves only what this small model records. It
does not prove that communication occurred, that a real route works, or that
a vulnerability exists, an exploit works, or an attack succeeded. A
vulnerability is a system weakness; an exploit is a method that uses a
weakness; an attack is an action intended to gain access or cause harm.

## 8. Vocabulary

- **graph:** objects plus their relationships;
- **vertex:** one object in a graph;
- **edge:** one direct relationship;
- **adjacency matrix:** a row-and-column table of possible edges;
- **path:** vertices joined by edges without a repeated vertex;
- **cycle:** edges that return to their start without another repeated vertex;
- **reachable:** able to be reached from a stated starting vertex;
- **connected component:** a connected group that cannot include another
  vertex while remaining connected;
- **invariant:** a rule every valid completed structure must satisfy.

**Key sentence:** a graph separates the objects from the relationship facts,
and its representation determines how those facts are stored and checked.
