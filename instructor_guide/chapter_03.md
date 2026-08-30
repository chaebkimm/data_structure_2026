# Chapter 3. Storing Relationships in Multiple Directions

## Starting Question

> How can one fixed table record relationships that may cross branches, share destinations, or form cycles?

**Expected answer:** Number the vertices. Store `1` at row `from` and column
`to` when that directed edge exists. Store `0` when it does not.

## Why We Need This

Chapter 1 supplied fixed arrays and indexed access. Chapter 2 supplied
structs and showed why a tree forbids shared children and cycles. A graph
allows multiple incoming edges and cycles. Module 3 combines an explicit
struct with a two-dimensional fixed array.

The implemented model is one directed, unweighted graph. It does not
implement undirected updates, weights, edge lists, adjacency lists, graph
search, or connected-component counting. Those ideas are comparisons or
previews in this chapter.

## Board Walkthrough

Use the textbook's three-server example throughout:

```text
Vertices: 0 Web, 1 App, 2 Database
Directed edges: 0 -> 1, 1 -> 2, 1 -> 0

grid:
    to 0  1  2
from
  0    0  1  0
  1    1  0  1
  2    0  0  0
```

Rows name sources and columns name destinations. Opposite cells are
independent: `grid[0][1] == 1` does not by itself determine
`grid[1][0]`. After removing `1 -> 2`, row 1 is `[1, 0, 0]` and vertex 1's
out-degree is 1.

The fixed C representation is:

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

The array always reserves 16 by 16 integer cells. With three active
vertices, only the leading 3 by 3 square describes possible active edges.

## Core Invariants and Preconditions

A valid completed graph satisfies these rules:

1. `vertex_count <= GRAPH_MAX_VERTICES`.
2. Active vertex indexes are `0` through `vertex_count - 1`.
3. Every grid entry is 0 or 1.
4. Every inactive row and column remains zero.
5. Every diagonal entry is zero because this model forbids self-loops.

An active isolated vertex may also have an all-zero row and column.
`vertex_count`, not the presence of a `1`, determines whether the vertex
exists. Cycles involving two or more vertices and multiple edges entering
one destination are valid.

The four functions maintain these rules when given a valid initialized
graph. They do not scan the entire matrix for unrelated corruption.

## Public Operations

```c
int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(
    struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(
    struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree);
```

Initialization clears all 256 cells before storing the active count. Adding
sets one active, off-diagonal cell to 1. Removing sets one active cell to 0.
Both assignments are idempotent: repeating a valid request succeeds and
leaves the selected cell at the requested value.

Invalid pointers, invalid stored counts, and inactive endpoints are rejected
before a write. Addition also rejects a self-loop. A rejected mutation
returns 0 and changes no grid cell. A failed degree query returns 0 and
leaves its output unchanged.

Guarded direct grid lookup remains a core operation rather than a fifth
library function.

## Common First Thoughts

- “Every connection works both ways.” Opposite directed cells are separate.
- “The numbers impose a value order.” Vertex numbers only select positions.
- “An all-zero row means the vertex does not exist.” An isolated active
  vertex also has no outgoing edges.
- “Every cycle is invalid because cycles broke Chapter 2's tree.” Graph
  cycles longer than a self-loop are allowed here.
- “The three-vertex example reserves only nine cells.” The fixed object
  reserves 256 cells; nine are active.
- “Adding an existing edge must be an error.” This simple assignment is
  idempotent and keeps the cell equal to 1.
- “The functions validate an arbitrary matrix.” They check their arguments
  and metadata while assuming the remaining graph invariant.

## Vocabulary Boundaries

**Already available:** fixed arrays, size versus capacity, indexed access,
structs, pointers, bounds checks, paths, cycles, and invariants.

**Introduce here:** graph, vertex, edge, directed and undirected graphs,
in-degree and out-degree, self-loop, weight, unweighted graph, edge list,
adjacency list, adjacency matrix, isolated vertex, connected component,
symmetric matrix, two-dimensional arrays, and `size_t`.

**Deferred:** Boolean graph storage, graph-kind enums, status-code APIs,
whole-graph validators, neighbor-result containers, DFS/BFS, visited state,
dynamic adjacency lists, weighted-path algorithms, and component algorithms.

## Operation Summary

| Operation | Main idea | Work |
|---|---|---:|
| Initialize fixed storage | Clear all 16 by 16 cells | Fixed 256 writes |
| Add or remove one edge | Check indexes, then update one cell | Constant |
| Check one edge directly | Read one guarded cell | Constant |
| Count outgoing edges | Scan one active row | Proportional to active vertices |
| Inspect the active topology | Scan its active square | Proportional to vertices squared |

## Final Check

> Why can `grid[0][1]` and `grid[1][0]` have different values?

**Minimum answer:** They represent two different directed edges.

> How can vertex 2 exist when row 2 and column 2 are all zero?

**Minimum answer:** `vertex_count == 3` makes indexes 0, 1, and 2 active.
Zeros mean no edges, not no vertex.

> What defect can an uncleared inactive row preserve?

**Minimum answer:** If the count grows later, a stale 1 can reappear as a
connection that was never added to the new active graph.
