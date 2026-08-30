# Module 3 Directed-Graph Models

Every diagram includes a text equivalent. The implemented graph is directed,
unweighted, and stored in a fixed integer matrix.

## 1. Row means from; column means to

```text
                  destination vertex
                 0       1       2
source 0      grid[0][0] [0][1]  [0][2]
vertex 1      grid[1][0] [1][1]  [1][2]
       2      grid[2][0] [2][1]  [2][2]
```

Text equivalent: the row identifies the edge's starting vertex and the
column identifies its ending vertex. Cell `grid[u][v]` stores 1 when
`u -> v` exists and 0 when it does not.

## 2. Canonical three-vertex graph

```text
0 -----> 1 -----> 2
^        |
|        |
+--------+

edges: 0 -> 1, 1 -> 2, 1 -> 0
```

```text
       to
       0  1  2
from 0 0  1  0
     1 1  0  1
     2 0  0  0
```

Text equivalent: row 0 records the edge to 1. Row 1 records edges to 0 and
2. Row 2 records no outgoing edges. The diagonal is zero because direct
self-loops are not allowed.

The edges `0 -> 1` and `1 -> 0` are independent and together form the
valid directed cycle `0 -> 1 -> 0`. A cycle of two or more edges is allowed.

## 3. Removal preserves direction

Remove only `1 -> 2`:

```text
       to
       0  1  2
from 0 0  1  0
     1 1  0  0
     2 0  0  0
```

Text equivalent: only `grid[1][2]` changes from 1 to 0. The opposite edge
`0 -> 1` and every other cell remain unchanged. Removing an edge that is
already absent leaves the same matrix and is still a successful idempotent
request.

## 4. Direct guarded lookup

For a valid completed graph:

```c
int edge_exists = 0;

if (from < graph.vertex_count && to < graph.vertex_count) {
    edge_exists = graph.grid[from][to];
}
```

Text equivalent: check that both IDs are active before using them as array
indexes. The selected integer is already 0 or 1. The lookup reads one cell
and does not change the graph. A production caller must also hold a valid
initialized graph object whose count is at most 16.

## 5. Out-degree scans one active row

Before removal:

```text
vertex 1 row: [1, 0, 1]
                  ^     ^
outgoing edges: 1 -> 0 and 1 -> 2
out-degree(1) = 2
```

After removing `1 -> 2`:

```text
vertex 1 row: [1, 0, 0]
out-degree(1) = 1
```

Text equivalent: count the 1 values from column 0 through
`vertex_count - 1` in the selected row. Do not scan inactive columns as
vertices. Incoming degree would conceptually scan a column, but it is not a
required library function.

## 6. Active and inactive positions

A graph initialized with `vertex_count == 3` has active IDs 0, 1, and 2.

```text
16 x 16 physical grid

        columns 0..2       columns 3..15
rows 0..2    active square     inactive: all 0
rows 3..15   inactive: all 0   inactive: all 0
```

Text equivalent: the complete object contains 256 matrix cells.
Initialization clears every one. Only the top-left
`vertex_count × vertex_count` square can contain edges. All inactive rows
and columns remain zero.

## 7. Rejection preserves state

| Request | Result | State |
|---|---|---|
| initialize more than 16 vertices | reject | supplied object unchanged |
| add with an endpoint outside the active range | reject | graph unchanged |
| add `v -> v` | reject | diagonal stays zero |
| add an existing valid edge | success | same graph |
| remove an existing valid edge | success | selected cell becomes zero |
| remove an absent valid edge | success | same graph |
| ask degree with an invalid graph, vertex, or output pointer | reject | output unchanged |

Text equivalent: finish every failure check before writing. Idempotence means
a repeated valid request reaches the same correct state and still reports
success.

## 8. Implemented invariants

For a valid completed object:

```text
0 <= vertex_count <= 16
every grid value is 0 or 1
grid[v][v] == 0 for every active v
inactive row or inactive column => cell is 0
```

Text equivalent: direction does not require symmetry. Opposite active
off-diagonal cells may differ. Raw external writes are outside the four
functions' protection; use the public initialization and mutation rules.

## 9. Conceptual undirected comparison

An undirected relationship between 0 and 1 has no arrow. If represented in
a matrix, it uses matching mirror cells:

```text
undirected {0, 1}: cell[0][1] == cell[1][0] == 1
```

Text equivalent: symmetry belongs to the conceptual undirected model, not
the implemented `struct DirectedGraph`. Students do not implement an
undirected mutation or a graph-kind switch in this module.

## 10. Other conceptual representations

For the directed edges `0 -> 1`, `1 -> 2`, and `1 -> 0`:

```text
ordered edge list:
(0,1), (1,2), (1,0)

adjacency-list concept:
0: 1
1: 0, 2
2: none
```

Text equivalent: an edge-list representation stores endpoint pairs. An
adjacency-list representation stores each vertex's outgoing neighbors.
The C lab implements neither representation.

A weighted edge would store an additional cost such as time or distance.
The implemented matrix stores only 0 or 1. A connected component is discussed
only for an undirected graph. Computing components requires a later traversal
procedure and is not a Chapter 3 code task.

## 11. Representation costs

Let `V` be the active vertex count and let the fixed maximum be `M = 16`.

| Operation or resource | Cost |
|---|---:|
| initialize all physical cells | `O(M²)`: exactly 256 writes |
| add or remove one checked edge | `O(1)` |
| direct guarded lookup | `O(1)` |
| out-degree | `O(V)` |
| scan every active cell | `O(V²)` |
| fixed matrix storage | `O(M²)`: 256 integers |

Text equivalent: direct indexing locates one edge cell in constant time.
Out-degree scans one active row. The matrix reserves every possible pair at
the fixed maximum even when few edges exist.
