# Joining groups to build a minimum-cost network

## Start with the decision

Suppose A, B, C, and D are sites. Process offers in this order:

| Edge | Cost |
|---|---:|
| A–B | 1 |
| B–C | 2 |
| A–C | 3 |
| C–D | 4 |

After accepting A–B and B–C, should we buy A–C? Explain your initial answer
before reading further. A and C are already connected through B, so adding
that edge would make a cycle. C–D instead joins a separate site. The selected
edges cost 7 in total. This asks for minimum total network cost, unlike
Dijkstra's minimum route cost from one chosen source.

## Remember groups without searching all accepted edges

A **disjoint-set union (DSU)**, also called **Union-Find**, remembers groups
that do not overlap. Each vertex has a dense integer ID. `parent[x]` points
to another ID in the same group; a root satisfies `parent[r] == r`.
A root's `component_size` counts its members; nonroots store zero here.
`component_count` counts roots.

**Make-set** creates a singleton group. It is supplied in this week's code.
**Find** follows parents to the representative root. **Union** joins groups
only when their roots differ. If roots already match, union succeeds with
`merged == false`; the graph edge would create a cycle.

Use **union by size**: attach the smaller group under the larger group's
root, adding their sizes, clearing the losing root's size, and decreasing
component count once. On equal sizes, choose the smaller root ID.
**Path compression** redirects a searched path to its root without changing
membership, root sizes, or component count.

Trace `A–B, C–D, A–C, E–F, G–H, E–G, A–E`, with A=0 through H=7:

```text
parent:         A A A C A E E G
component_size: 8 0 0 0 0 0 0 0
components:     1
```

Finding H follows H → G → E → A. A second pass sets H and G directly to A.
Keep a node's old parent before changing it so you can continue the walk.
A later D–H relationship does not merge groups.

Our supplied first-pass helper bounds the walk and validates IDs. Locate
both union roots before mutating either path so an invalid second endpoint
cannot cause a partial update. Then compress the valid paths and merge if
needed. Caller outputs are committed only on success. Read `dsu.h` for the
full bounds and output non-aliasing contract; DSU owns no dynamic storage.

## Use the groups in Kruskal

A **minimum spanning tree (MST)** connects all vertices of a connected,
weighted undirected graph at minimum total edge cost. For disconnected input,
compute a **minimum spanning forest (MSF)**, one tree per component.

**Kruskal's algorithm** scans edges in nondecreasing weight order. It accepts
an edge precisely when it joins two different current DSU components.
The cut property explains safety: a lightest edge crossing a cut that
respects the accepted forest can be included in some MST. Cycles are rejected
because their endpoints are already connected. DSU supplies the connectivity
decision; sorting supplies the weight order. DSU alone does not minimize cost.

The supplied edge-list builder emits one record per logical undirected edge,
retaining distinct parallel edges. Sorting compares weights relationally,
then endpoints and logical IDs for deterministic ties; subtracting signed
weights could overflow. You implement the selection loop, not loading or sorting.

For each edge, count the examination; skip self-loops; find both roots; skip
matching roots; check result capacity; append the edge; and union its endpoints.
At completion, copy DSU's component count. The scaffold computes a checked
`int64_t` total and publishes the result only after success. Its temporary
candidate can be discarded on failure. Scan all edges for the required ledger.

The invariant is that accepted edges form a forest and DSU groups are exactly
its connected components. With V vertices and c components, the result has
V−c edges. A connected graph therefore yields V−1 edges. Negative weights
are valid here; Dijkstra's nonnegative-weight restriction does not apply.

## Costs, comparison, and interpretation

Union by size plus compression gives amortized O(alpha(V)) DSU operations.
This describes an operation sequence, not a promise of one array read per
find. Sorting dominates ordinary Kruskal work: O(V + E log(E+1) + E alpha(V)).
DSU storage is O(V), in addition to the edge list and output. Full diagnostic
validation is separate from these operation costs.

The instructor demonstrates supplied **Prim**, which grows a tree across
its boundary using a priority queue. Both methods minimize total forest
cost; ties can produce different edge sets with the same minimum total.
Prim implementation is optional. A minimum-cost tree offers no redundant
route if an edge fails, and shared DSU membership does not prove trust or
authorization. DSU also cannot return a graph path or handle arbitrary edge
deletions without a different design.
