# Module 3 Directed-Graph Models

Every diagram includes a text equivalent. The implemented graph is directed,
unweighted, and stored in a fixed integer matrix.

All worked models use the same seven-account SNS follower network as the
textbooks and lab. An arrow runs from the follower to the followed account.
These models are released at Stage D, after the Stage C attempt is saved.

## 1. Row means from; column means to

```text
                     destination vertex
                 0       1       2       3       4       5       6
source 0      grid[0][0] [0][1]  [0][2]  [0][3]  [0][4]  [0][5]  [0][6]
vertex 1      grid[1][0] [1][1]  [1][2]  [1][3]  [1][4]  [1][5]  [1][6]
       2      grid[2][0] [2][1]  [2][2]  [2][3]  [2][4]  [2][5]  [2][6]
       3      grid[3][0] [3][1]  [3][2]  [3][3]  [3][4]  [3][5]  [3][6]
       4      grid[4][0] [4][1]  [4][2]  [4][3]  [4][4]  [4][5]  [4][6]
       5      grid[5][0] [5][1]  [5][2]  [5][3]  [5][4]  [5][5]  [5][6]
       6      grid[6][0] [6][1]  [6][2]  [6][3]  [6][4]  [6][5]  [6][6]
```

Text equivalent: the row identifies the edge's starting vertex and the
column identifies its ending vertex. Cell `grid[u][v]` stores 1 when
`u -> v` exists and 0 when it does not.

## 2. Canonical SNS follower graph

```text
0 Mina -> 1 Joon -> 2 Sora -> 3 Dae
   ^                  |
   +------------------+

4 Hana <-> 5 Leo       6 Nuri (isolated)

edges: 0 -> 1, 1 -> 2, 2 -> 0, 2 -> 3, 4 -> 5, 5 -> 4
```

```text
       to
       0  1  2  3  4  5  6
from 0 0  1  0  0  0  0  0
     1 0  0  1  0  0  0  0
     2 1  0  0  1  0  0  0
     3 0  0  0  0  0  0  0
     4 0  0  0  0  0  1  0
     5 0  0  0  0  1  0  0
     6 0  0  0  0  0  0  0
```

Text equivalent: Mina follows Joon, Joon follows Sora, and Sora follows Mina
and Dae. Hana and Leo follow each other. Nuri has no incoming or outgoing
follow. Dae has no outgoing follow but has an incoming follow from Sora, so
Dae is not isolated. The diagonal is zero because direct self-loops are not
allowed.

The edges `4 -> 5` and `5 -> 4` are independent and together form the
valid directed cycle `4 -> 5 -> 4`. The cycle `0 -> 1 -> 2 -> 0` is also
valid. A cycle of two or more edges is allowed.

## 3. Removal preserves direction

Remove only `2 -> 3`, meaning Sora unfollows Dae:

```text
       to
       0  1  2  3  4  5  6
from 0 0  1  0  0  0  0  0
     1 0  0  1  0  0  0  0
     2 1  0  0  0  0  0  0
     3 0  0  0  0  0  0  0
     4 0  0  0  0  0  1  0
     5 0  0  0  0  1  0  0
     6 0  0  0  0  0  0  0
```

Text equivalent: only `grid[2][3]` changes from 1 to 0. Reverse cell
`grid[3][2]` and every other cell remain unchanged. Dae's row and column now
contain only zeros, so Dae becomes isolated. Removing an edge that is already
absent leaves the same matrix and is still a successful idempotent request.

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
Sora, vertex 2 row: [1, 0, 0, 1, 0, 0, 0]
outgoing edges: 2 -> 0 and 2 -> 3
out-degree(2) = 2
```

After removing `2 -> 3`:

```text
Sora, vertex 2 row: [1, 0, 0, 0, 0, 0, 0]
out-degree(2) = 1
```

Text equivalent: count the 1 values from column 0 through
`vertex_count - 1` in the selected row. Do not scan inactive columns as
vertices. Incoming degree would conceptually scan a column, but it is not a
required library function.

## 6. Active and inactive positions

A graph initialized with `vertex_count == 7` has active IDs 0 through 6.

```text
16 x 16 physical grid

             columns 0..6       columns 7..15
rows 0..6    active square      inactive: all 0
rows 7..15   inactive: all 0    inactive: all 0
```

Text equivalent: the complete object contains 256 matrix cells.
Initialization clears every one. The active square has 49 cells. Only the top-left
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

For the six directed follows in the original graph:

```text
ordered edge list:
(0,1), (1,2), (2,0), (2,3), (4,5), (5,4)

adjacency-list concept:
0: 1
1: 2
2: 0, 3
3: none
4: 5
5: 4
6: none
```

Text equivalent: an edge-list representation stores endpoint pairs. An
adjacency-list representation stores each vertex's outgoing neighbors.
The C lab implements neither representation.

A weighted edge would store an additional cost such as time or distance.
The implemented matrix stores only 0 or 1. Section 12 compares ways to group
connected accounts. Computing those groups requires more than reading the
matrix cells and is not a Chapter 3 code task.

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

## 12. Components and feed candidates

Start with the original graph in section 2, before the unfollow. Accounts
can be grouped by the paths connecting them.

| Rule | Initial components |
|---|---|
| Weak: ignore arrow direction while tracing paths | `{0, 1, 2, 3}`, `{4, 5}`, `{6}` |
| Strong: directed paths connect every pair in both directions | `{0, 1, 2}`, `{3}`, `{4, 5}`, `{6}` |

Text equivalent: Mina, Joon, Sora, and Dae form one weak component. Mina,
Joon, and Sora form one strong component, while Dae forms another. Hana and
Leo are together under either rule. Nuri is a singleton under either rule.

Each component is maximal: no other vertex can join it while preserving its
connectivity rule. A single account can form a component without a self-loop.
Dae is initially not isolated because Sora follows Dae. Strong connectivity
requires directed paths, not direct mutual follows between every pair.
Ignoring direction for weak connectivity does not insert reverse follows.
Dae belongs to the first weak component but cannot follow any directed path
back to Mina, Joon, or Sora, so Dae forms a separate strong component.

Removing `2 -> 3` changes row 2's out-degree from 2 to 1 and isolates Dae.
The final weak components are `{0, 1, 2}`, `{3}`, `{4, 5}`, and `{6}`;
the strong component memberships stay the same.

In an illustrative feed design before the unfollow, Mina's direct-follow
source is Joon. Sora is in Mina's strong component and could supply additional
recommendation candidates. Dae is in the same weak component but another
strong component and could supply broader candidates. Public posts from Hana
or Leo may match Mina's interests despite being outside her weak component.
Nuri's lack of links motivates using stated interests or other signals for a
new account.

Component membership does not prove a common topic or dense connections.
Labels are neither ranking scores nor access permissions. Choosing eligible
posts and ranking them require additional rules. This is a possible teaching
design, not a claim that a particular SNS uses these component rules. The
lab keeps four matrix functions and does not implement components or a feed.

Both [the English textbook](../student/textbook.md) and
[the Korean textbook](../student/textbook_korean.md) explain these models.
