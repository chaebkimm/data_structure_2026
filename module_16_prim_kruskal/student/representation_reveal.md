# Stage B - Representation Reveal: Connect Every Site

## 1. Name the stored model

A **representation** is a chosen way to store or show information. A
**graph** represents items and their relationships. Each item is a
**vertex**; each relationship is an **edge**. An **undirected edge** works
in both directions. A **weight** is the numeric cost stored on an edge.

This module uses a **weighted undirected graph**: every edge is two-way and
has a **signed** whole-number weight, meaning the weight may be negative,
zero, or positive. Each **logical edge** is one relationship with one edge
ID. An **incident record** is one stored view of an edge from one endpoint,
so the endpoint-based stored form has two incident records per logical edge.

The canonical graph is:

```text
ID0 A-B 4    ID1 A-C 4    ID2 B-C 1    ID3 B-D 5
ID4 C-D 2    ID5 C-E 3    ID6 D-E 3    ID7 A-E 10
```

An **edge list** stores one record per logical edge. An **adjacency list**
stores the edges touching each vertex together. A **self-loop** has the same
vertex at both ends. **Parallel edges** are different edge IDs with the
same endpoints. This module preserves parallel edges and ignores self-loops
when selecting a result.

## 2. Name the connection goal

A **path** is a sequence of adjoining edges. Vertices are **connected** when
a path joins them. A **cycle** is a nonempty route that returns to its
starting vertex without reusing an edge.

A **tree** is connected and has no cycle. A **spanning tree** includes every
vertex of a connected graph. A **minimum spanning tree (MST)** is a spanning
tree whose selected edge weights have the smallest possible total.

A **component** is a largest connected part. A disconnected graph has no
single spanning tree. A **forest** is a collection of trees. A **minimum
spanning forest (MSF)** gives one MST for each component, including a
one-vertex tree for an isolated vertex.

If `V` is the number of vertices and `c` is the number of components, a
spanning forest has:

```text
V - c selected edges
```

The connected canonical graph has five vertices, one component, four
selected edges, and minimum total 10.

## 3. Separate an MST from shortest paths

A **source** is a chosen starting vertex. A **shortest-path tree** records
one least-cost path from one source to every reachable vertex. Its goal is
not to minimize the sum of the tree's edges.

From source A, Dijkstra selects AB, AC, CD, and CE. Their edge sum is 13,
and the A-to-C path costs 4. One canonical MST selects AB, BC, CD, and CE.
Its total is 10, but its A-to-C path costs 5 through B.

An **array** is a numbered row; brackets select one position. Dijkstra's
`distance[v]` is a whole path cost from the source. Prim's `key[v]` will be
one edge weight. The similar-looking arrays answer different questions.

## 4. Grow one tree with Prim

An **algorithm** is a finite step-by-step procedure. **Prim's algorithm**
starts one tree and repeatedly adds a cheapest edge that reaches a new
vertex.

A **cut** separates the vertices into two groups. A **crossing edge** has
one endpoint in each group. A **safe edge** can be added while leaving some
minimum result possible. Prim chooses a minimum-weight edge crossing from
the current tree to the vertices outside it.

For a vertex outside the tree:

- `key[v]` stores the cheapest crossing-edge weight known for `v`;
- `parent[v]` stores the other endpoint of that edge; and
- `in_tree[v]` records whether `v` has already been added.

The **frontier** is pending work. A **Priority Queue** is a collection that
removes its first-ranked record. A binary **Heap** is a tree-shaped Priority
Queue; binary means each stored position has at most two children.

This module uses **lazy duplicates**. When a key improves, a new snapshot is
pushed without removing the old one. A snapshot is **stale**, or out of
date, when its saved key differs from the current key. A popped record for a
vertex already in the tree is also skipped.

Equal key proposals cause no change. The stable Heap removes earlier
equal-key snapshots first. If the frontier empties while an unvisited vertex
remains, Prim restarts at the smallest such vertex. That produces an MSF.

## 5. Merge groups with Kruskal

**Kruskal's algorithm** reads all logical edges from smallest weight to
largest. **Normalized endpoints** place the smaller vertex ID first. Equal
weights are ordered by normalized endpoints and then edge ID.

A **comparator** is a function that decides which of two records comes
first. The supplied comparator uses relational less-than and greater-than
tests. It never subtracts weights, because subtracting extreme signed
values can exceed the numeric range.

**Disjoint-set union (DSU)**, also called **Union-Find**, maintains groups
that do not overlap. Each group has a **representative root**, an ID naming
that group. `find` obtains a root. `union` combines two groups.

Kruskal adds an edge only when its endpoint roots differ, then unions those
groups. Equal roots mean the edge would create a cycle, so it is skipped. A
self-loop immediately has equal roots. Parallel edges remain separate
candidates.

## 6. Verify and limit the result

An **invariant** is a rule true for every valid state. A **validator** is a
diagnostic operation that checks rules. Structural validation checks valid
distinct selected IDs, no selected self-loop, no cycle, correct component
membership, exactly `V-c` edges, and an exact total.

Structure alone does not prove minimum cost. Independent Prim and Kruskal
runs must agree on total weight, though ties may give different edge sets.
A stronger minimum check asks whether replacing an edge could lower the
total.

`int64_t` is C's signed 64-bit whole-number type. **Overflow** occurs when a
result exceeds its range. The final mathematical total is checked and stored
only when it fits; the check does not reject a fitting total merely because
one array order first forms a running subtotal outside that range.

**Density** describes how many possible edges are present. Kruskal fits an
edge-list input naturally. Heap Prim fits an adjacency-list input. A
**matrix** stores one position for every vertex pair. For a dense graph,
meaning one with many possible edges present, matrix Prim can avoid sorting
all edges; that version is comparison work, not this lab.

**Resilience** is the ability to continue required service after a failure.
Every edge of a tree is a **bridge**, an edge whose removal increases the
number of components. An MST minimizes modeled build cost; it does not
provide backup routes, prove that stored input came from a genuine
authorized source, or prove system security.

Keep the vocabulary reference closed until all three Cognitive Pause
targets are preserved.
