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

Use the textbook's follower network on a social networking service (SNS).
Each vertex is an account. An edge `u -> v` means account `u` follows
account `v`. The arrow records the follow action. Posts from `v` may then
be candidates for `u`'s feed.

```text
Vertices: 0 Mina, 1 Joon, 2 Sora, 3 Dae, 4 Hana, 5 Leo, 6 Nuri
Directed edges: 0 -> 1, 1 -> 2, 2 -> 0, 2 -> 3, 4 -> 5, 5 -> 4

grid:
    to 0  1  2  3  4  5  6
from
  0    0  1  0  0  0  0  0
  1    0  0  1  0  0  0  0
  2    1  0  0  1  0  0  0
  3    0  0  0  0  0  0  0
  4    0  0  0  0  0  1  0
  5    0  0  0  0  1  0  0
  6    0  0  0  0  0  0  0
```

Rows name sources and columns name destinations. Opposite cells are
independent: `grid[0][1] == 1` does not by itself determine
`grid[1][0]`. Sora's row contains two 1s, so her out-degree is 2. After
removing `2 -> 3`, row 2 is `[1, 0, 0, 0, 0, 0, 0]` and her out-degree
is 1.

Dae initially has out-degree 0 and in-degree 1. Dae is not isolated
because Sora follows Dae. Nuri has no incoming or outgoing edges and is
isolated. After removing `2 -> 3`, Dae is also isolated.

The fixed C representation is:

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

The array always reserves 16 by 16 integer cells. With seven active
vertices, only the leading 7 by 7 square describes possible active edges.
Both textbook editions, the lab worksheets, and the canonical core test use
these seven accounts. Boundary tests and the standalone autopsy use their
own small fixtures. Stage D offers English and Korean editions as reading
alternatives after the Stage C attempt is preserved.

## Which Accounts Belong to One Connected Group?

A direct follow answers a question about two accounts. To describe a
larger group, follow paths through several accounts. Begin with the graph
before removing `2 -> 3`.

Mina can reach Sora through Joon. Sora can return to Mina directly.
Every account in `{0, 1, 2}` can reach every other account in that set by
following arrows. Dae cannot return to those accounts. No other vertex
can join the group while preserving directed paths in both directions
between every pair. Such a group is a **strongly connected component
(SCC)**. The group is maximal: it cannot grow while keeping the required
property. A graph can have several such groups of different sizes.

For a broader grouping, temporarily ignore arrow direction when tracing
paths. Dae is then connected to Sora, Joon, and Mina. A maximal group
connected by paths under that rule is a **weakly connected component
(WCC)**. No vertex outside the group can join through such a path.
Ignoring direction is an analysis step. It does not add reverse follows
or change the stored matrix.

| Kind | Components before removing `2 -> 3` |
|---|---|
| Strongly connected | `{0, 1, 2}`, `{3}`, `{4, 5}`, `{6}` |
| Weakly connected | `{0, 1, 2, 3}`, `{4, 5}`, `{6}` |

Strong connectivity requires paths in both directions. It does not
require every pair to follow each other directly. The cycle
`0 -> 1 -> 2 -> 0` demonstrates the difference. A single vertex is also
a component when no other vertex can join it. A path from a vertex to
itself can use zero edges, so no self-loop is required.

Removing `2 -> 3` splits the weak component `{0, 1, 2, 3}` into
`{0, 1, 2}` and `{3}`. The strong component groups stay the same. Use
hand-traced paths to establish these groups. Component algorithms are
deferred.

## How Could These Groups Help a Feed?

A feed needs candidate posts before it can choose their display order.
Use Mina's feed before Sora unfollows Dae to separate these two steps.
Mina directly follows Joon, so Joon's posts can enter a feed based on
followed accounts. If the feed also includes recommendations,
connectivity can help organize additional candidates.

- Sora belongs to Mina's strong component and could supply recommendation
  candidates reached through the follow network.
- Dae belongs to Mina's weak component but a different strong component.
  Dae could supply candidates from a broader connected group.
- Hana and Leo belong to another weak component. Their public posts could
  still be useful candidates if they match Mina's interests.
- Nuri has no follow links. A feed for a new account such as Nuri may need
  stated interests or other signals to find its first candidates.

These are possible teaching designs, not claims about a particular
platform. Component membership does not prove shared interests or dense
connections. Labels do not supply ranking scores or viewing permission.
A feed still needs separate rules for which posts the viewer may see
and which candidates are useful, timely, and worth displaying. Component
labels can help find or group candidates; they do not define the whole
feed. Feed construction remains conceptual and adds no C API here.

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
- “An all-zero row means the vertex does not exist or is isolated.” Dae
  initially has an all-zero row but an incoming follow from Sora.
- “Every cycle is invalid because cycles broke Chapter 2's tree.” Graph
  cycles longer than a self-loop are allowed here.
- “The seven-account example reserves only 49 cells.” The fixed object
  reserves 256 cells; 49 are active.
- “A strong component requires direct mutual follows between every pair.”
  Paths through other accounts also count.
- “A weak component makes follows work both ways.” Only the path analysis
  ignores direction. The stored follows stay directed.
- “Accounts in the same component must have the same interests.” Paths
  describe connectivity, not interests or post quality.
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
strongly and weakly connected components, symmetric matrix,
two-dimensional arrays, and `size_t`.

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

> How can Nuri exist when row 6 and column 6 are all zero?

**Minimum answer:** `vertex_count == 7` makes indexes 0 through 6 active.
Zeros mean no edges, not no vertex.

> Before removing `2 -> 3`, why is Dae not isolated?

**Minimum answer:** Sora follows Dae. An empty outgoing row does not rule
out an incoming edge.

> Why are Mina, Joon, and Sora one strong component without direct mutual follows?

**Minimum answer:** The cycle `0 -> 1 -> 2 -> 0` supplies directed paths
between every pair. No other account can join while preserving that rule.

> What changes when Sora unfollows Dae?

**Minimum answer:** Sora's out-degree falls from 2 to 1. Dae becomes
isolated. One weak component splits into `{0, 1, 2}` and `{3}`. The strong
components stay the same.

> Does belonging to Mina's weak component guarantee a place in Mina's feed?

**Minimum answer:** No. Membership can help gather candidates, but it does
not determine ranking or permission to view a post. Useful public posts
may also come from outside the component.

> What defect can an uncleared inactive row preserve?

**Minimum answer:** If the count grows later, a stale 1 can reappear as a
connection that was never added to the new active graph.
