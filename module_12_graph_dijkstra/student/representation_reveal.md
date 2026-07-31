# Stage B - Formal Name and State

Open this file only after preserving Stage A.

## 1. Retrieve the earlier search goal

A **graph** stores items called **vertices** and connections called
**edges**. A **directed edge** may be followed only in its stated direction.
**Breadth-first search (BFS)** uses a first-in, first-out **Queue** to process
vertices in layers. It minimizes edge count from a starting vertex; it does
not minimize unequal numeric costs.

The **source** is the starting vertex. A **destination** is a requested goal.
A **path** follows directed edges. The direct path A to E has one edge but
costs 14 minutes. A to C to D to E has three edges but costs 6.

## 2. Add weights

A **weight** is the numeric cost assigned to an edge. A **weighted directed
graph** has directed edges with weights. A path's cost is the sum of its
edge weights. Here, each weight is an invented number of inspection
minutes.

The canonical IDs are:

```text
A=0, B=1, C=2, D=3, E=4, F=5
```

Its edges are:

```text
A->B 9   A->C 2   A->E 14
B->D 0   B->E 8
C->B 2   C->D 2
D->E 2
```

The arrow `->` means a one-way edge from its left vertex to its right
vertex.

An **adjacency list** stores each vertex's outgoing edges together. F has no
path from A.

## 3. Name Dijkstra's algorithm

An **algorithm** is a precise, finite procedure. **Dijkstra's algorithm**
finds least total path costs from one source when every weight is
**nonnegative**, meaning zero or greater.

A **distance** in this module means modeled total path cost, not physical
separation. A **tentative distance** is the best cost known so far and may
still improve. A distance becomes **finalized** when the current smallest
tentative value is removed for processing.

Finalization is safe because every unfinished extension adds zero or more.
A negative edge could later lower a value already declared final, so
negative weights are rejected.

## 4. Store distance and predecessor

An **array** is a numbered row. `dist[v]` stores the current cost for vertex
`v`. Brackets select an array position. A **predecessor** is the previous
vertex on the recorded path; `pred[v]` stores it.

`INF` is a **sentinel**, or named marker, meaning no finite representable
path is currently known. This module defines:

```text
INF = SIZE_MAX
```

`size_t` is C's nonnegative whole-number type for sizes. `SIZE_MAX` is its
largest value. Source A begins with distance 0 and no predecessor. Every
other distance begins at `INF`.

## 5. Keep a frontier of snapshots

The **frontier** is pending work not yet finalized. A **Priority Queue** is
a collection that removes the record ranked first. This module uses the
minimum binary **Heap** from Module 11, so the smallest saved cost leaves
first. **Binary** means each stored position can have at most two children.
The Queue is **stable**, meaning equal costs leave in snapshot insertion
order.

Course frontier lists show expected removal order. A Heap's internal array
may have a different order while representing the same Priority Queue.

A **snapshot** is one saved vertex/cost pair such as `B/9`. This version
uses **lazy duplicates**: when B improves to 4, it inserts
`B/4` without editing `B/9`. Editing a stored priority would be
**decrease-key**; this version does not perform it.

A snapshot is **stale** when its saved cost differs from the current
`dist` value. After removing `B/9`, test:

```text
9 != dist[B]
```

The symbol `!=` means not equal. Because `dist[B]` is 4, skip the stale
snapshot without scanning B's edges.

## 6. Relax one edge strictly

To **relax** edge `u->v` is to test whether the path through `u` improves
`v`. The **candidate distance** is `dist[u] + weight(u,v)`.

Relaxation is **strict**:

```text
if candidate < dist[v]:
    insert snapshot v/candidate
    dist[v] = candidate
    pred[v] = u
```

The symbol `<` means smaller than. Commit distance and predecessor only
after snapshot insertion succeeds. If candidate equals `dist[v]`, change
nothing and insert nothing. In the canonical trace, C first gives D cost 4.
Later B plus its zero-cost edge also proposes 4. D keeps predecessor C.

## 7. Guard text and arithmetic

A **parser** converts input text into stored values. It must reject negative
text before an **unsigned conversion**, which would convert the value into
a type that cannot represent negatives.

**Overflow** occurs when an arithmetic result exceeds the type's range.
Before addition:

1. do not form a candidate from `INF`;
2. require `weight <= INF - dist[u]`, where `<=` means no greater than;
3. add only after that check; and
4. return `DIJKSTRA_COST_RANGE` if the sum would overflow or equal `INF`.

The **caller** is code requesting work; its **output** is where the answer
is written. That explicit status preserves the caller's output. It must not
silently report the destination as unreachable.

## 8. Reconstruct a path

To **reconstruct** is to recover the recorded path. Start at the
destination, follow predecessors backward to the source, then reverse the
collected vertices. Stop and reject a malformed chain after at most `V`
vertices, where `V` means active vertex count.

For E:

```text
backward: E,D,C,A
forward:  A,C,D,E
cost:     2+2+2 = 6
```

Keep the vocabulary reference closed until all three Cognitive Pause
targets are preserved.
