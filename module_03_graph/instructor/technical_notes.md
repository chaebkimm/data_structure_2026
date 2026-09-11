# Instructor Technical Notes — Module 3

## Exact scope and public contract

The implementation is one bounded, directed, unweighted adjacency matrix.
The header is `code/include/graph_matrix.h`; implementations are
`code/starter/graph_matrix.c` and `code/solution/graph_matrix.c`.

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
);
int graph_remove_edge(
    struct DirectedGraph *graph,
    size_t from,
    size_t to
);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

These are the only public functions. Do not add a type alias, Boolean field,
enumeration, status type, graph-kind field, validator, edge-query helper,
in-degree operation, neighbor collection, or undirected mutation.

Every function returns 1 for success and 0 for rejection. There are no
separate error codes. Direct guarded matrix lookup is core caller code, not
another required function.

## Matrix meaning and invariant

Cell `grid[from][to]` represents exactly one directed fact. In the SNS
example, `from` follows `to`. The cell is 1 when the follow exists and 0
when absent. The reverse cell is independent.

For a valid completed graph:

1. `vertex_count <= GRAPH_MAX_VERTICES`;
2. every grid cell is 0 or 1;
3. every active diagonal cell is 0;
4. every cell with an inactive row or inactive column is 0; and
5. active vertex IDs are the contiguous range
   `0` through `vertex_count - 1`.

A cell is inactive when either index is at least `vertex_count`. The
physical matrix always has 16 rows and 16 columns. A zero-vertex graph is
valid and has no active cells.

The public operations establish and preserve these rules from valid inputs.
There is no public whole-graph validator. Raw field edits that violate the
invariant are outside the ordinary operation contract.

The matrix represents at most one edge per ordered pair. Repeated addition
therefore describes the same edge rather than a parallel edge.

## Initialization

`graph_init(graph, vertex_count)`:

- rejects `NULL`;
- rejects a count greater than 16;
- leaves a supplied graph completely unchanged on rejected count; and
- on success, clears all 256 cells before or along with storing the count.

Clearing only the active square is incorrect. A later increase in
`vertex_count` could make an uncleared inactive cell represent a false
connection. Full clearing also makes reuse deterministic.

Initialization takes `O(M²)` cell writes for maximum `M = 16`: exactly 256
writes. With the compiled maximum fixed, this is bounded constant work, but
`O(M²)` explains how the representation scales with its configured bound.

## Common validation order

For add and remove:

1. reject a null graph;
2. reject metadata with `vertex_count > 16`;
3. reject `from >= vertex_count` or `to >= vertex_count`; and
4. perform the operation-specific behavior.

All rejection paths return 0 before any write. Values of type `size_t`
cannot be negative, so a separate negative-index check is neither possible
nor required.

The functions assume the rest of a non-null graph satisfies the documented
invariant. They do not scan unrelated cells as hidden validation work.

## Idempotent directed addition

`graph_add_edge(graph, from, to)` additionally rejects `from == to`.
That rejection preserves the diagonal and the complete graph.

For distinct valid endpoints, assign:

```c
graph->grid[from][to] = 1;
```

If the cell was already 1, the function still returns 1. The state is already
the requested state, so repeated addition is successful and idempotent.
Only the one directed cell is relevant; do not write its reverse.

A cycle with two or more edges is valid. For example, `4 -> 5` and
`5 -> 4` coexist even though `4 -> 4` and `5 -> 5` are rejected. The
cycle `0 -> 1 -> 2 -> 0` is also valid.

## Idempotent directed removal

For valid endpoints, including equal endpoints, assign:

```c
graph->grid[from][to] = 0;
```

Return 1 whether the edge was present or already absent. Repeated removal is
idempotent. Permitting equal endpoints lets removal preserve or restore the
required zero diagonal; only addition rejects a self-loop request.

Do not clear the reverse cell. Removing `2 -> 3` says nothing about
`3 -> 2`.

## Direct guarded lookup

There is no public edge-query function. A caller with a valid initialized
object uses the same row/column convention after checking active bounds:

```c
int edge_exists = 0;

if (from < graph.vertex_count && to < graph.vertex_count) {
    edge_exists = graph.grid[from][to];
}
```

When demonstrating robust caller code, first establish
`graph.vertex_count <= GRAPH_MAX_VERTICES`. The read is `O(1)`, changes no
state, and yields 0 or 1 under the graph invariant.

A failed guard has no function return convention because this is direct
caller code. The caller chooses how to report an inactive ID and must not
perform the bracket access.

## Out-degree

`graph_out_degree(graph, vertex, out_degree)` checks, in externally
indistinguishable order:

- `out_degree != NULL`;
- `graph != NULL`;
- `graph->vertex_count <= 16`; and
- `vertex < graph->vertex_count`.

Any failure returns 0 and leaves a non-null output unchanged. Compute the
count into a local `size_t`; write `*out_degree` only after successful
validation and row scanning.

Scan active columns only. Increment for cells exactly equal to 1:

```c
size_t degree = 0;

for (size_t to = 0; to < graph->vertex_count; to = to + 1) {
    if (graph->grid[vertex][to] == 1) {
        degree = degree + 1;
    }
}

*out_degree = degree;
return 1;
```

Out-degree is `O(V)` for active vertex count `V`. An isolated or
sink-only vertex has out-degree zero and still returns success.

Incoming degree can be reasoned about by scanning a column, but it is not a
required function.

## Canonical SNS follower trace

The inquiry, activities, textbooks, and lab use the same seven accounts:
0 Mina, 1 Joon, 2 Sora, 3 Dae, 4 Hana, 5 Leo, and 6 Nuri. Initialize
`vertex_count` to 7 and add these follows:

```text
0 -> 1
1 -> 2
2 -> 0
2 -> 3
4 -> 5
5 -> 4
```

The active matrix is:

```text
0 1 0 0 0 0 0
0 0 1 0 0 0 0
1 0 0 1 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 1 0 0
0 0 0 0 0 0 0
```

- `grid[0][1] == 1`;
- `grid[1][0] == 0`;
- `grid[2][0] == 1` and `grid[2][3] == 1`;
- Sora's out-degree is 2;
- `0 -> 1 -> 2 -> 0` is a valid directed cycle;
- Dae's out-degree is 0 and in-degree is 1, so Dae is not isolated; and
- Nuri has no incoming or outgoing edges and is isolated.

After `graph_remove_edge(&graph, 2, 3)`, row 2 is
`[1, 0, 0, 0, 0, 0, 0]` and Sora's out-degree is 1. Dae becomes isolated.
All other cells retain their prior values. The active square has 49 cells;
the object always reserves 256. Index 7 is physically within the array but
inactive.

## Conceptual comparisons only

Use these ideas to compare representations without adding C requirements.
Keep worked component and feed reasoning in Stage D after the Stage C attempt:

- an undirected matrix records one relationship with two symmetric cells;
- a weighted edge carries a cost, distance, or time rather than only 0/1;
- an edge-list representation stores endpoint pairs;
- an adjacency-list representation stores outgoing neighbors per vertex;
- an undirected connected component is a maximal group joined by paths;
- a weakly connected component applies that rule after ignoring directed
  edges' arrow directions;
- a strongly connected component is a maximal group with directed paths in
  both directions between every pair; and
- directed reachability must name a starting vertex.

No undirected mutation, weight storage, representation conversion, component
algorithm, DFS, or BFS belongs in the starter.

In the original canonical graph, weak components are `{0,1,2,3}`, `{4,5}`,
and `{6}`; strong components are `{0,1,2}`, `{3}`, `{4,5}`, and `{6}`.
Removing `2 -> 3` isolates Dae and splits the first weak component into
`{0,1,2}` and `{3}`, leaving strong component memberships unchanged. A
singleton component needs no self-loop; a vertex reaches itself using a path
of length zero. Strong connectivity requires mutual directed reachability,
not direct reciprocal follows between every pair. Weak connectivity ignores
directions only for analysis; it does not change the directed matrix.

Treat the feed discussion as an illustrative design before the unfollow.
Mina directly follows Joon. Sora is in Mina's strong component and could
supply additional recommendation candidates. Dae is in the same weak
component but another strong component and could supply broader candidates.
Public posts from Hana or Leo may match Mina's interests despite being
outside her weak component. Nuri's lack of links motivates using stated
interests or other signals for a new account.

Component labels do not establish a common topic or dense connections. They
are neither ranking scores nor access permissions. Eligibility and ranking
need separate rules. Do not claim that a particular SNS uses these component
rules. The edge's direction describes the follow relation, not the movement
of a post toward its readers. Stage D provides both
`student/textbook.md` and `student/textbook_korean.md`.

## Complexity

Let `V` be the active count and `M = 16` the physical bound.

| Operation or resource | Time or space |
|---|---:|
| full initialization | `O(M²)`, exactly 256 writes |
| add edge | `O(1)` |
| remove edge | `O(1)` |
| direct guarded lookup | `O(1)` |
| out-degree | `O(V)` |
| inspect every active cell | `O(V²)` |
| fixed matrix storage | `O(M²)`, 256 integers |

A sparse graph may use only a few of the reserved cells; the matrix still
stores every possible pair at the fixed bound. That contrast motivates the
later adjacency-list representation.

## Matrix Autopsy boundary

The standalone source is `code/autopsy/faulty_ghost_connection.c`, built as
`ghost_connection_autopsy`. It demonstrates why initialization must clear
inactive as well as active positions. All array accesses remain within the
physical 16-by-16 grid; a crash is not expected.

Keep the exact fixture prediction and observed values in the instructor
answer key. Stage D may explain the full-clear invariant generically but must
not expose the Stage E autopsy result.

## Toolchain and validation

Preferred GCC/Clang flags:

```text
-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
```

Supported runtime checks:

```text
-fsanitize=address,undefined -fno-omit-frame-pointer
```

Microsoft C uses `/nologo /std:c11 /W4 /Zi`. Provide instructor CI or a
debugger/invariant alternative when a local runtime checker is unavailable.

Before release, verify:

- the exact explicit structure and four prototypes match the header;
- reference core and extension suites pass without warnings;
- all failures preserve graph state or out-degree output as documented;
- duplicate add and missing remove are successful idempotent requests;
- direct lookup is guarded and not presented as another API;
- three student tests match the rubric;
- vocabulary appears in Stage B, not Stage A;
- Stage D contains no worked Matrix Autopsy result;
- release paths use `faulty_ghost_connection.c`; and
- Stage E excludes the solution, extension tests, and answer key.
