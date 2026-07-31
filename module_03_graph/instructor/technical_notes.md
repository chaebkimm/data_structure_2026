# Technical Notes — Module 3 Graph

## Scope

These notes define the instructor-facing behavior of the Module 3 C package.
The implementation uses a fixed Boolean adjacency matrix. An **adjacency
matrix** is a square table in which row `u` and column `v` record whether edge
`u → v` exists. A **Boolean** value is either `true` or `false`.

The course graph is:

- bounded to at most 16 vertices;
- directed or undirected;
- unweighted;
- simple, meaning that self-loops and duplicate edges are rejected.

A **self-loop** is an edge from a vertex to itself. A **duplicate edge** is an
attempt to add an edge already present. A **weight** is a number attached to
an edge, such as a distance or cost; the Boolean matrix has no field for one.

The module teaches representation and bounded operations. Do not add DFS,
BFS, recursion, a work queue, a work stack, or another formal graph-search
mechanism to the student requirements.

## Canonical public interface

Keep these names and values synchronized across the header, starter,
solution, tests, lab, answer key, and evidence form.

```c
#include <stdbool.h>
#include <stddef.h>

#define GRAPH_MAX_VERTICES 16U

typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

typedef enum {
    GRAPH_OK = 0,
    GRAPH_ERR_INVALID_ARGUMENT,
    GRAPH_ERR_OUT_OF_RANGE,
    GRAPH_ERR_SELF_LOOP,
    GRAPH_ERR_EDGE_EXISTS,
    GRAPH_ERR_EDGE_ABSENT,
    GRAPH_ERR_INVALID_GRAPH
} GraphStatus;

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;

typedef struct {
    size_t count;
    size_t vertices[GRAPH_MAX_VERTICES];
} GraphNeighbors;

GraphStatus graph_init(Graph *graph, size_t vertex_count, GraphKind kind);
GraphStatus graph_validate(const Graph *graph);
GraphStatus graph_add_edge(Graph *graph, size_t from, size_t to);
GraphStatus graph_remove_edge(Graph *graph, size_t from, size_t to);
GraphStatus graph_has_edge(
    const Graph *graph, size_t from, size_t to, bool *out_has_edge);
GraphStatus graph_out_degree(
    const Graph *graph, size_t vertex, size_t *out_degree);
GraphStatus graph_in_degree(
    const Graph *graph, size_t vertex, size_t *out_degree);
GraphStatus graph_out_neighbors(
    const Graph *graph, size_t vertex, GraphNeighbors *out_neighbors);
const char *graph_status_name(GraphStatus status);
```

`size_t` is C’s nonnegative integer type for sizes and indexes. `enum`
declares a fixed set of named choices. `struct` combines named fields into
one value. An **output parameter** is a pointer through which a function
writes a result. The degree output parameter is named `out_degree` in both
degree functions because “out” describes the direction of data leaving the
function, not the direction of a graph edge.

## Matrix convention and active area

Use one convention everywhere:

```text
adjacency[from][to]
```

Rows are sources, and columns are destinations. In a directed graph,
`adjacency[u][v]` and `adjacency[v][u]` are independent. In an undirected
graph, they are mirror cells that must be equal.

Let `V` be `graph->vertex_count`. Only indexes `0` through `V - 1` are
**active**, meaning they currently name graph vertices. Only the active
`V × V` square represents edges. `graph_init` clears the full `16 × 16`
array to produce a predictable object, but `graph_validate` ignores cells
outside the active square. A true inactive cell alone does not invalidate the
graph. Every public edge or vertex operation rejects an inactive index with
`GRAPH_ERR_OUT_OF_RANGE`.

Zero vertices is a valid graph when `kind` is valid. Its active matrix is
empty.

## Whole-graph invariant

An **invariant** is a rule that must hold whenever a completed structure is
used. `graph_validate` checks all of these rules:

1. the graph pointer is not `NULL`;
2. `vertex_count <= GRAPH_MAX_VERTICES`;
3. `kind` is exactly `GRAPH_DIRECTED` or `GRAPH_UNDIRECTED`;
4. every active diagonal cell `adjacency[v][v]` is `false`;
5. for an undirected graph, every active cell equals its mirror cell:
   `adjacency[u][v] == adjacency[v][u]`.

`NULL` is C’s special pointer value meaning “no object.” A **diagonal cell**
has the same row and column index. Requiring false diagonal cells rejects
self-loops.

The Boolean matrix cannot represent two parallel copies of an edge.
**Parallel edges** are separate edges with the same endpoints. The operation
contract makes this limitation visible by returning
`GRAPH_ERR_EDGE_EXISTS` on duplicate insertion.

Directed matrices need not be symmetric. Do not reject a valid one-way edge
because its reverse cell is false.

## Status meanings

`GraphStatus` is a named result that distinguishes success from different
failures:

| Status | Meaning |
|---|---|
| `GRAPH_OK` | The requested operation succeeded. |
| `GRAPH_ERR_INVALID_ARGUMENT` | A required pointer is `NULL`, or an initialization choice is not a supported `GraphKind`. |
| `GRAPH_ERR_OUT_OF_RANGE` | A count exceeds 16, or a requested vertex ID is not active. |
| `GRAPH_ERR_SELF_LOOP` | An edge operation names the same start and end vertex. |
| `GRAPH_ERR_EDGE_EXISTS` | An insertion requests an edge already present. |
| `GRAPH_ERR_EDGE_ABSENT` | A removal requests an edge not present. |
| `GRAPH_ERR_INVALID_GRAPH` | Existing graph metadata or relevant matrix cells violate the graph invariant. |

`graph_status_name` returns a short stable description for every named
status. It should return a safe “unknown graph status” description for an
integer value not represented by the enumeration.

## Initialization

`graph_init` checks all failure conditions before changing the destination:

1. `graph` must not be `NULL`;
2. `vertex_count` must not exceed `GRAPH_MAX_VERTICES`;
3. `kind` must be `GRAPH_DIRECTED` or `GRAPH_UNDIRECTED`.

On success, assign the count and kind and set all `16 × 16` Boolean cells to
`false`. Clearing all cells keeps later reuse deterministic, meaning the same
valid call produces the same state regardless of the object’s previous
contents.

On a rejected initialization request, preserve the destination object when
one was supplied. **Preserve** means leave its bytes and logical state
unchanged.

## Full validation versus operation checks

`graph_validate` is the explicit whole-graph operation. It scans the active
diagonal and, for an undirected graph, checks active mirror pairs. A clear
implementation may use a nested loop over all active rows and columns.

Do not make every other operation call `graph_validate`. Edge query,
insertion, and removal need constant work. Degree and neighbor queries need
one row or column scan. Calling the full validator inside them would change
their promised work cost and conceal the difference between a local
operation and whole-structure validation.

A **local relevant check** examines the metadata and only the cells needed by
the requested operation:

- all operations check the graph pointer, count, and kind;
- an edge operation checks its two endpoint IDs and diagonal request;
- an undirected edge operation checks the requested cell and its mirror;
- a directed degree query checks the selected row or column, including its
  diagonal cell;
- an undirected degree or neighbor query checks each selected cell against
  its mirror while scanning the selected row.

This design may accept a local operation when an unrelated part of the graph
is malformed. That is intentional. Call `graph_validate` explicitly after
raw data is imported, after direct field edits, or whenever the whole object
must be trusted.

## Edge insertion

`graph_add_edge(graph, from, to)` uses this sequence:

1. reject a `NULL` graph;
2. reject invalid count or kind metadata as
   `GRAPH_ERR_INVALID_GRAPH`;
3. reject an endpoint not lower than `vertex_count` as
   `GRAPH_ERR_OUT_OF_RANGE`;
4. reject `from == to` as `GRAPH_ERR_SELF_LOOP`;
5. inspect the requested cell.

For a directed graph:

- if `adjacency[from][to]` is already `true`, return
  `GRAPH_ERR_EDGE_EXISTS`;
- otherwise set that one cell to `true`.

For an undirected graph:

- if the requested cell and mirror cell differ, return
  `GRAPH_ERR_INVALID_GRAPH`;
- if both are already `true`, return `GRAPH_ERR_EDGE_EXISTS`;
- if both are `false`, set both to `true`.

Perform every failure check before the first write. The undirected operation
then changes its two cells as one successful logical update.

## Edge removal

`graph_remove_edge(graph, from, to)` uses the same argument, metadata, range,
self-loop, and relevant-symmetry checks.

For a directed graph:

- if `adjacency[from][to]` is `false`, return
  `GRAPH_ERR_EDGE_ABSENT`;
- otherwise set that cell to `false`.

For an undirected graph:

- unequal mirror cells mean `GRAPH_ERR_INVALID_GRAPH`;
- two false cells mean `GRAPH_ERR_EDGE_ABSENT`;
- two true cells are both cleared on success.

A rejected removal must not change the matrix.

## Edge query

`graph_has_edge` requires a non-`NULL` graph and a non-`NULL`
`out_has_edge`. Apply the same metadata, range, self-loop, and
undirected-mirror checks used by the other edge operations. Write the output
only after all checks succeed.

For a directed graph, the answer is `adjacency[from][to]`. For an undirected
graph, the two equal mirror cells give the same answer. A failed query leaves
the caller’s previous output value unchanged.

## Degree queries

For a directed graph:

- `graph_out_degree` counts `true` cells in row `vertex`;
- `graph_in_degree` counts `true` cells in column `vertex`.

For an undirected graph, both functions report the same degree. An
implementation may scan the row in both cases, provided it verifies each
selected cell against its mirror. One undirected edge is counted once for
the selected vertex.

Reject a true selected diagonal cell as `GRAPH_ERR_INVALID_GRAPH`. Reject
asymmetric relevant cells in an undirected graph. Write the output count only
after the scan succeeds, so failure preserves the caller’s previous value.

Do not sum both row and column for an undirected degree. That would count
every touching edge twice.

## Out-neighbor query

`graph_out_neighbors` reports the out-neighbors of one selected vertex.
Inspect row `vertex` from column zero upward. Every `true` cell contributes
its column ID, so the successful result is in increasing vertex-ID order.

For an undirected graph, “out-neighbor” is operational API wording; because
each edge is two-way, it is the ordinary neighbor set. Check each row cell
against its mirror. Reject a true diagonal cell.

Build the answer in a temporary `GraphNeighbors`, then copy it to the caller
only after the scan passes. A **temporary value** is a short-lived value used
inside a function. Set `count` to the number found. Clearing unused positions
to zero is recommended for deterministic test evidence, but callers must use
only entries below `count`.

No valid graph can overflow `vertices[16]`, because there are at most 16
active vertices and the self-loop position is false.

## Work-cost requirements

**Time complexity** describes how the amount of work grows as the input size
grows. `O(1)` means a fixed amount of work. `O(V)` means work proportional to
the number of active vertices. `O(V²)` means work proportional to the number
of active vertices multiplied by itself.

| Function | Required time | Reason |
|---|---:|---|
| `graph_validate` | `O(V²)` | It may inspect every active matrix cell. |
| `graph_add_edge` | `O(1)` | It examines and changes at most one directed cell or two mirror cells. |
| `graph_remove_edge` | `O(1)` | It examines and changes at most one directed cell or two mirror cells. |
| `graph_has_edge` | `O(1)` | One requested cell, plus one mirror when needed, answers the query. |
| `graph_out_degree` | `O(V)` | It scans one active row. |
| `graph_in_degree` | `O(V)` | It scans one active column, or one row for the equivalent undirected result. |
| `graph_out_neighbors` | `O(V)` | It scans one active row. |
| `graph_status_name` | `O(1)` | A fixed selection returns one text value. |

`graph_init` clears the fixed `16 × 16` capacity. It therefore performs
bounded constant work for this exact course type; expressed using the named
maximum, it performs `O(GRAPH_MAX_VERTICES²)` writes.

Do not claim that edge operations are `O(V²)` by having them call the full
validator. Do not claim that matrix neighbor reporting is `O(degree)`: it
must examine all `V` row cells even if few are true.

## Representation comparison

Let `E` be the number of edges.

Keep an **edge set** distinct from an **edge-list representation**. An edge
set is the mathematical collection of relationships; it contains no repeated
edge, and the collection’s written order has no graph meaning. An edge-list
representation is a concrete stored sequence with one endpoint record per
edge. The sequence has storage positions even though changing their order
does not change the represented graph.

- An adjacency matrix reserves `V × V` cells. A particular edge query is
  `O(1)`, while neighbor reporting is `O(V)`.
- An edge list stores about `E` endpoint pairs. A basic scan for one
  particular edge is `O(E)`.
- An adjacency list stores one list per vertex plus neighbor entries
  corresponding to edges. Reporting one vertex’s outgoing neighbors is
  proportional to the number reported, assuming its list is directly
  available.

An undirected edge commonly appears twice in an adjacency-list
implementation, once in each endpoint’s list. It appears as two true mirror
cells in a matrix but still represents one logical undirected edge.

A **sparse graph** has few edges compared with the number of possible edges.
An edge list or adjacency list may use less storage for a sparse graph. A
**dense graph** contains many possible edges, making the matrix’s reserved
space less wasteful. Keep the comparison conceptual; dynamic adjacency-list
implementation is deferred.

## Weighted-graph boundary

The `bool adjacency[16][16]` field cannot distinguish a five-minute edge from
a ten-minute edge. It also has no separate “no edge” marker plus numeric
weight. Do not overload `false` or `true` as a numeric weight.

Students should be able to identify a situation where weights matter and to
state that a different field type and an explicit absence representation
would be needed. They do not extend the C API in this module.

## Testing priorities

Public tests should include:

- valid empty directed and undirected initialization;
- initialization at exactly 16 vertices;
- `NULL` pointer rejection;
- count 17 rejection;
- unsupported `GraphKind` rejection;
- one directed insertion and asymmetric reverse query;
- one undirected insertion and both-direction queries;
- self-loop rejection;
- duplicate insertion rejection;
- present removal and absent removal;
- out-of-range endpoints;
- unchanged graph after rejected mutation;
- unchanged output after rejected query;
- directed in-degree and out-degree that differ;
- increasing-order out-neighbor output;
- isolated-vertex degree and neighbor result.

Instructor and extension tests should additionally include:

- invalid `vertex_count` in an already formed `Graph`;
- invalid existing `kind`;
- true active diagonal cell;
- asymmetric active cells in an undirected graph;
- a true cell outside the active square that validation deliberately ignores;
- a local directed operation that does not scan an unrelated malformed cell;
- a relevant undirected asymmetric pair rejected by add, remove, query,
  degree, and neighbor operations as appropriate;
- maximum directed out-degree of 15;
- maximum undirected degree of 15;
- preservation of every output and graph object on failure;
- safe text for an unknown `GraphStatus`.

The reference solution should compile with warnings enabled. A **compiler**
is a program that translates C source code into an executable program. A
**warning** is a compiler message about code that may be mistaken even when
translation can continue.

## C safety notes

- Loop while `i < vertex_count`, not `i <= vertex_count`. The second form
  accesses one position beyond the active range.
- Check every pointer before using `->` or `*` to access its target.
- Use `size_t` for vertex IDs and counts to match the public declarations.
- Perform checks before writes so rejected changes are atomic from the
  caller’s viewpoint. **Atomic** here means the logical change happens fully
  or not at all.
- The graph contains its matrix directly; it owns no separately allocated
  memory. Do not call `malloc`, `realloc`, or `free`. These functions request,
  resize, and release dynamic memory.
- Never infer an edge from vertex labels or array proximity. Only an active
  matrix cell records an edge.

## Synthetic network interpretation

The canonical six-vertex network contains:

```text
Vertices:
0 Gateway, 1 Web, 2 Admin, 3 Database, 4 Monitor, 5 Archive

Directed permission edges:
0 → 1
0 → 2
1 → 3
2 → 3
3 → 4
4 → 1
```

Vertex `5` is isolated. The cycle `1 → 3 → 4 → 1` is permitted by the model.
The graph says only which directed relationships the exercise records. It
does not prove that services are running, credentials are available,
vulnerabilities exist, defenses fail, packets arrive, or an exploit
succeeds. Grade “proof of exploitability” claims as model-boundary errors.

## Directed and undirected language

Use these distinctions consistently:

| Undirected graph | Directed graph |
|---|---|
| neighbor | out-neighbor or in-neighbor |
| degree | out-degree or in-degree |
| connected component | reachable from a named starting vertex |
| edge `{u, v}` | edge `u → v` |
| symmetric matrix | symmetry is not required |

There are advanced directed notions called strongly and weakly connected
components. Do not introduce them here. Their early use encourages students
to treat direction as optional. Use reachability questions with explicit
starts and destinations.

## Deferred topics

Explicitly defer:

- DFS and BFS;
- recursive or iterative graph traversal;
- visited arrays as student-implemented search bookkeeping;
- adjacency-list allocation and freeing;
- weighted C storage;
- shortest paths;
- spanning trees;
- strongly connected components;
- multigraphs, which permit parallel edges;
- graph mutation during a search.

Students may manually identify a small path, cycle, or reachable destination
from a displayed graph. Manual identification is evidence about the model,
not implementation of a general search algorithm.

## Instructor validation checklist

- [ ] Header, starter, solution, tests, and prose use the exact public names.
- [ ] `GRAPH_MAX_VERTICES` is `16U`.
- [ ] The matrix convention is row `from`, column `to`.
- [ ] Validation inspects only the active `V × V` square.
- [ ] Inactive true cells alone do not invalidate a graph.
- [ ] Initialization clears the full physical matrix.
- [ ] Directed matrices may be asymmetric.
- [ ] Undirected active matrices must be symmetric.
- [ ] Every active diagonal cell is false.
- [ ] Duplicate insertion and self-loops are rejected.
- [ ] Failed mutations and queries preserve prior state or output.
- [ ] Full validation is `O(V²)`.
- [ ] Add, remove, and edge query are `O(1)`.
- [ ] Degree and neighbor queries are `O(V)`.
- [ ] Local operations do not call the full validator.
- [ ] Out-neighbor IDs are returned in increasing order.
- [ ] Connected components appear only in undirected examples.
- [ ] Directed examples use reachability from a named start.
- [ ] Weighted graphs are compared but not implemented.
- [ ] DFS, BFS, and formal search remain deferred.
- [ ] Synthetic network edges are not presented as proof of exploitability.
