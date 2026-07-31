# Stage B - Five-Minute Cognitive Pause

Read the locked definitions and states before timing begins. Then use no
notes, slides, vocabulary file, classmates, or coding tools. Preserve the
first response when correction begins.

A weighted undirected graph stores two-way edges with numeric weights. A
minimum spanning tree (MST) connects every vertex without a cycle and has
minimum selected-edge total. A minimum spanning forest (MSF) contains one
minimum tree per connected **component**, a largest connected group.

Prim stores one crossing-edge weight in `key[v]`; this is not Dijkstra's
source-to-vertex distance. **Disjoint-set union (DSU)** tracks groups; a
**representative root** is the ID naming one group. Kruskal adds a sorted
edge only when its endpoint roots differ. For `V` vertices and `c`
components, a spanning forest has `V-c` selected edges.

`INF` is a named marker meaning no finite key is known. A dash (`-`) means
no parent is recorded. A **snapshot** is one saved pending record. The
**frontier** is all pending snapshots. A push adds one; a pop removes one.

A **signed weight** may be negative, zero, or positive. **Normalized
endpoints** place the smaller vertex ID first. An **incident scan** examines
one stored view of an edge from one endpoint.

The canonical graph is:

```text
ID0 A-B 4    ID1 A-C 4    ID2 B-C 1    ID3 B-D 5
ID4 C-D 2    ID5 C-E 3    ID6 D-E 3    ID7 A-E 10
```

## Target 1 - Separate two minimum goals

Dijkstra from A records edges `AB, AC, CD, CE`. A proposed spanning result
uses `AB, BC, CD, CE`.

State:

1. the selected-edge total for each set;
2. the A-to-C path and cost in each set;
3. which set answers the source-route question;
4. which set answers the whole-network question; and
5. the required selected-edge count for this connected five-vertex graph.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Finish the lazy Prim trace

Use this locked state after A has entered the tree:

```text
in tree: A
keys:    B=4/A, C=4/A, D=INF/-, E=10/A
frontier removal order: B/4, C/4, E/10
```

Equal keys leave in insertion order. A strict improvement must be smaller.
A popped snapshot is skipped if its vertex is already in the tree or its
saved key differs from the current key.

State:

1. every later current pop and selected edge;
2. every key/parent improvement;
3. why D-to-E at weight 3 causes no change;
4. the three obsolete pops;
5. final selected IDs and total; and
6. pushes, pops, peak size, incident scans, eligible crossing tests, and key
   improvements.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Sort, merge, restart, and limit the claim

For the canonical graph, process edges by signed weight, normalized
endpoints, then edge ID. State every add/skip decision and the DSU groups
after each added edge.

Then add isolated F. State:

1. `V`, `c`, and `V-c`;
2. whether the honest result is an MST or MSF;
3. what Prim must do after its frontier empties; and
4. why minimum total cost neither supplies a backup route nor proves that
   the stored weights are trustworthy.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `objective`, `key`,
`strict tie`, `stale`, `DSU root`, `forest count`, or `resilience`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
