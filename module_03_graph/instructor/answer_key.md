# Instructor Answer Key — Module 3

Keep this file instructor-only. Students preserve Stage A, Cognitive Pause,
Stage C, and autopsy predictions before seeing worked answers.

## Macro-question synthesis

A directed adjacency matrix stores one yes-or-no fact for every ordered pair
of active vertex IDs. Row identifies the source, column the destination.
Graphs allow several incoming edges and routes that return to an earlier
vertex, so they represent relationships that do not fit the Module 2 tree.

The implemented graph is fixed, directed, and unweighted. Comparisons with
other graph forms do not expand the four-function API.

## Stage A — Initial inquiry

### A. Three-tier system

```text
Web 0 -----> App 1 -----> Database 2
  ^           |
  +-----------+
```

Immediate directed relationships:

- Web to App, or `0 -> 1`;
- App to Database, or `1 -> 2`; and
- App to Web, or `1 -> 0`.

Do not add Database to App or another unstated reverse edge.

### B. Direction

Starting at Web, the repeating route is Web -> App -> Web -> App and so on.
The edge App -> Database gives no evidence for Database -> App. Web -> App
and App -> Web have opposite sources and destinations and therefore require
two separate facts.

### C. Tree limits

App -> Web creates the returning route Web -> App -> Web, which conflicts
with a tree's no-cycle rule. If both Web and App led to Database, Database
would have two incoming relationships, conflicting with the one-incoming-link
tree rule.

### D–E. Storage brainstorm

The program must remember whether a relationship exists from each selected
source to each selected destination. Rows can name sources and columns can
name destinations. A missing relationship stores 0. Accept equivalent
plain-language models without requiring graph terms during Stage A.

## Stage B — Matrix reveal and Cognitive Pause

Canonical matrix:

```text
       to
       0  1  2
from 0 0  1  0
     1 1  0  1
     2 0  0  0
```

### Target 1

The rows are `[0, 1, 0]`, `[1, 0, 1]`, and `[0, 0, 0]`.
Cells `[0][1]` and `[1][0]` represent different directed questions. Both
happen to contain 1 because both opposite edges were explicitly supplied.

### Target 2

Removing `1 -> 2` changes only `grid[1][2]` from 1 to 0. New row 1 is
`[1, 0, 0]`; its out-degree is 1.

### Target 3

Consider each request from the original three-vertex state:

| Addition | Result | Reason |
|---|---|---|
| `2 -> 2` | reject, return 0 | self-loop addition |
| `3 -> 1` | reject, return 0 | vertex 3 is inactive |
| `2 -> 0` | accept, return 1 | distinct active endpoints |

A rejection changes no metadata or cell. Successful `2 -> 0` sets only
`grid[2][0]` to 1.

## Stage C — Investigation

### A1. Equivalent representations

Diagram:

```text
0 -----> 1 -----> 2
^        |
+--------+
```

Ordered edge set:

```text
{(0, 1), (1, 2), (1, 0)}
```

Matrix:

| From \ To | 0 | 1 | 2 |
|---:|---:|---:|---:|
| 0 | 0 | 1 | 0 |
| 1 | 1 | 0 | 1 |
| 2 | 0 | 0 | 0 |

There are three arrows, three ordered pairs, and three cells containing 1.

### A2. Row and column

Row 1 asks which edges leave App. Its 1 cells are `grid[1][0]` and
`grid[1][2]`. Column 1 asks which edges enter App; its only 1 is
`grid[0][1]`.

`grid[0][1]` records only `0 -> 1`; it does not imply `1 -> 0`.
The reverse happens to exist because it is separately in the edge set.

### B1. Degree

- App out-degree: 2, counting `grid[1][0]` and `grid[1][2]`.
- Web in-degree: 1, counting `grid[1][0]` in column 0.

In-degree is conceptual here; there is no matching required function.

### B2. Removal

After removing `1 -> 2`:

```text
0 1 0
1 0 0
0 0 0
```

Only cell `[1][2]` changes. App out-degree becomes 1. All other cells,
including the independent reverse pair `[0][1]` and `[1][0]`, remain
unchanged.

### B3. Idempotence

Setting an existing edge cell to 1 again produces the requested existing-edge
state. Setting an absent edge cell to 0 again produces the requested
absent-edge state. Both are successful requests returning 1, with no further
state change.

### C1. Active versus physical

For count 3, active IDs are 0, 1, and 2. Index 3 is below the physical bound
16 but is not below `vertex_count`, so it cannot be used as an endpoint.

### C2. Completed-state classifications

| Stored fact | Classification | Rule |
|---|---|---|
| `grid[2][0] == 1` | valid | distinct active endpoints; edge `2 -> 0` |
| `grid[2][2] == 1` | invalid | active diagonal must remain zero |
| `grid[3][1] == 1` with count 3 | invalid | a cell involving an inactive ID must be zero |
| `grid[0][2] == 2` | invalid | every cell must be exactly 0 or 1 |

These are state classifications, not requests to pass malformed objects to
ordinary functions.

### C3. Full clearing and preservation

Initialization must clear all 16 rows and 16 columns so a previously stored
inactive cell cannot become a ghost edge if a later graph uses more vertices.

A rejected add or remove preserves the complete graph. A rejected out-degree
request preserves a non-null caller output. Initialization with count above
16 preserves a supplied graph.

### D1. Routes and cycles

One route from Web to Database is `0 -> 1 -> 2`. Web and App form
`0 -> 1 -> 0`. A later traversal must remember visited vertices or it could
revisit this cycle forever. This is conceptual preparation, not a required
Chapter 3 search algorithm.

### D2. Shared destination

Edges `0 -> 2` and `1 -> 2` are both valid graph relationships. Vertex 2
then has two incoming edges, whereas the child-only tree requires one
incoming link for each non-root node.

### D3. Isolated active vertex

An isolated active vertex has zero in every active cell of its row and
column. Its ID is still below `vertex_count`. An inactive index is not a
vertex at all, and every physical cell involving it is also required to be
zero.

### E1. Directed, undirected, and weighted

A conceptual undirected relationship between 0 and 1 can be represented by
two matching opposite cells, both 1. The implemented structure has no kind
field and its mutation functions always update one directed cell; the
comparison does not add an undirected mode.

A binary cell stores existence only. A delay or cost requires an additional
value and a different contract.

### E2. Representation comparison

| Question | Matrix | Edge list | Adjacency list |
|---|---|---|---|
| one direct edge lookup | direct cell, `O(1)` | scan pairs, `O(E)` | scan source's list, commonly `O(out-degree)` |
| outgoing neighbors | scan row, `O(V)` | scan edges, `O(E)` | inspect source's list, `O(out-degree)` |
| storage with few edges | reserves pair grid, `O(V²)` conceptually | `O(E)` | `O(V + E)` |

For a small fixed graph with frequent direct-edge questions, the matrix is a
reasonable choice because lookup is direct. Its tradeoff is reserved storage
for every possible pair.

### E3. Transfer and boundary

1. Fixed ArrayList: event codes kept in numbered sequence.
2. Binary tree: hierarchy with meaningful left and right child positions.
3. Directed graph: permissions that may return to an earlier service.

A permission edge establishes only the modeled permission. It does not prove
a vulnerability, successful exploit, authenticated identity, or actual
end-to-end route.

A suitable exit sentence is: “The matrix cell at row `from`, column `to`
records the directed edge `from -> to`; a valid completed graph also keeps
all cells binary, its diagonal zero, and inactive cells zero.”

## Exact C contract answers

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

### Initialization

- Null graph: return 0.
- Count greater than 16: return 0 and preserve a supplied graph.
- Valid count including zero: clear all 256 cells, store count, return 1.

### Addition

Validate graph pointer, metadata, and both active endpoints before writing.
Reject equal endpoints with 0. For valid distinct endpoints, set exactly
`grid[from][to] = 1` and return 1, including when it was already 1.

### Removal

Validate pointer, metadata, and endpoints. For valid endpoints, including
equal endpoints, set exactly `grid[from][to] = 0` and return 1, including
when it was already 0.

### Out-degree

Reject a null output, null graph, invalid metadata, or inactive vertex with
0 and leave any non-null output unchanged. Count active-row cells exactly
equal to 1, commit the local result, and return 1.

### Direct lookup

There is no fifth query function. Establish a valid graph and check both IDs
against `vertex_count` before reading `grid[from][to]`. The read is
constant time and makes no change.

## Complexity answers

Let `V` be active count and `M = 16` be the fixed bound.

| Operation | Cost |
|---|---:|
| initialize | `O(M²)`, exactly 256 writes |
| add | `O(1)` |
| remove | `O(1)` |
| guarded direct lookup | `O(1)` |
| out-degree | `O(V)` |
| inspect active topology | `O(V²)` |
| fixed storage | `O(M²)`, 256 integers |

## Ghost-Connection Autopsy — instructor answers

The fixture starts with four active vertices and `grid[3][1] == 1`.
The first bad completed state occurs when faulty code changes only
`vertex_count` from 4 to 3. At that moment vertex 3 is inactive but
`grid[3][1]` remains 1.

Expected output:

```text
before shrinking: vertex 3 -> 1 = 1
after shrinking to 3 vertices:
vertex 3 is inactive: yes
inactive cell [3][1] is still 1
after growing back to 4 without clearing:
ghost connection 3 -> 1 reappears: yes
```

The capacity makes the access physically in bounds; it does not make vertex 3
active. The later change back to count 4 reveals the stale connection but is
not the first cause.

For this module, use `graph_init` for a new vertex count; it clears all 256
cells. A hypothetical resize operation would need its own contract that
clears every newly inactive row and column before committing a smaller count
and preserves state on failure. No such resize is a required API.

A regression can initialize four vertices, add `3 -> 1`, initialize the same
object with count 3, assert all 256 cells are zero, initialize with count 4,
and assert that `grid[3][1]` is still zero. This may be a rationale attached
to one of the three student tests; the autopsy does not require a fourth.

## Assessment alignment

| Criterion | Points |
|---|---:|
| Directed representation and vocabulary | 15 |
| Initialization | 20 |
| Directed edge operations | 20 |
| Out-degree and direct lookup | 15 |
| Invariants and boundary safety | 10 |
| Tests and tool evidence | 15 |
| Ghost autopsy and reflection | 5 |
| Total | 100 |

The three authored-test slots cover full initialization including inactive
cells; a coherent directed/idempotent/lookup/degree sequence; and rejected
self-loop/inactive mutation with a preserved graph or a rejected degree query
with a preserved output. Require distinct claims and rationales.

Accept standard or linear responses, everyday vocabulary, and approved
compiler, debugger, or instructor-CI evidence. Do not penalize an initial
misconception that was preserved and meaningfully corrected.
