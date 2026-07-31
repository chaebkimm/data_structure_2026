# Student Textbook - Dijkstra's Algorithm

## 1. Same routes, different goal

A **synthetic** example is invented. A **graph** stores
**vertices** (items) and **edges** (connections). A **directed** edge works
only in its stated direction.

**Breadth-first search (BFS)** uses a first-in, first-out **Queue** to process
edge-count layers and find a path with the fewest edges. A **path** follows
edges.

An edge's **weight** is its numeric cost. The direct path A to E has
one edge and weight 14. Path A,C,D,E has three edges and total weight 6.
BFS answers the edge-count question, not the least-total-weight question.

A **weighted directed graph** stores a weight with every directed edge.
**Path cost** is the sum of its edge weights. An **adjacency list** stores
each vertex's outgoing destination/weight pairs together, allowing
inspection of only its edges.

## 2. Dijkstra's promise

An **algorithm** is a precise, finite procedure. **Dijkstra's algorithm**
finds least total path costs from one **source**, or starting vertex. It
requires **nonnegative** weights, meaning every weight is zero or greater.

Here **distance** means modeled total path cost, not physical separation. A
**tentative distance** is the best cost known so far and can improve. A
distance becomes **finalized** when its current smallest value is removed
for processing.

This is safe because later extensions add zero or more and cannot lower the
smallest current value. A negative edge breaks that reasoning.

The loop is:

1. set the source to 0 and every other distance to not yet known;
2. remove the smallest saved vertex/distance record;
3. skip it if its saved value is out of date;
4. otherwise finalize its vertex;
5. scan that vertex's outgoing edges; and
6. save a new record whenever a smaller value is found.

Stop when no saved record remains. A vertex without a known distance was
never finalized.

## 3. Stored path facts

An **array** is a numbered row. `dist[v]` means the current distance for
vertex `v`; brackets select its array position. A **predecessor** is the
previous vertex on the recorded path, stored in `pred[v]`.

`INF` is a **sentinel**, or named marker, meaning no finite path cost that
fits in storage is currently known. Here:

```text
INF = SIZE_MAX
```

`size_t` is C's nonnegative whole-number type for sizes. `SIZE_MAX` is its
largest value. The source starts at 0 with no predecessor; all others start
at `INF`.

The **caller** is code that requests work; **output** stores its answer. An
**allocation** reserves storage, and **capacity** is its entry limit. Build
in temporary storage. Failure leaves caller output
unchanged and releases it; **ownership** means responsibility for that
release.

## 4. Edge test

To **relax** directed edge `u->v` is to test whether going through `u`
improves `v`; `->` means from left to right. The **candidate distance** is
the current distance to `u` plus the edge weight.

Here `<` means smaller than.

```text
if candidate < dist[v]:
    save v with candidate for later
    dist[v] = candidate
    pred[v] = u
```

This is **strict relaxation** because equality changes nothing. C first
gives D cost 4; B later proposes equal cost `4+0`.
D keeps predecessor C, and no new work is saved. Either path may be correct;
strictness keeps the first found. Change distance and predecessor only after
saving the improved record succeeds.

## 5. Saved Heap records

The **frontier** is pending work not yet finalized. A **Priority Queue**
removes its first-ranked record. The Module 11 minimum **Heap**, a
tree-shaped Priority Queue, removes the smallest saved distance.

A **snapshot** saves a vertex and distance; `B/9` means vertex B, distance 9.
This version uses **lazy duplicates**: when B improves to 4, it inserts
`B/4` without editing `B/9`. Editing an existing priority is
**decrease-key**, which this version does not use.

A snapshot is **stale** when its saved distance differs from current
`dist`. On a **pop**, or removal, compare first; `!=` means not equal:

```text
if popped_distance != dist[u]:
    skip u
```

Stale work never scans outgoing edges. A current pop finalizes the vertex.
The Queue is **stable**: earlier equal entries leave first.

## 6. Canonical trace

Use number labels, or **IDs**, `A=0` through `F=5` and edges:

```text
A->B 9   A->C 2   A->E 14
B->D 0   B->E 8
C->B 2   C->D 2
D->E 2
```

No path reaches F from A. Trace:

```text
pop A/0: B=9, C=2, E=14
pop C/2: B=4, D=4
pop B/4: D proposal 4 is equal; E=12
pop D/4: E=6
pop E/6: no outgoing edge
pop B/9: stale
pop E/12: stale
pop E/14: stale
```

Final distances are `0,4,2,4,6,INF`. Predecessors are
`-,C,A,C,D,-`. The run makes 8 relaxation attempts, 7 successful
relaxations, 8 snapshot insertions including A, 8 pops, 3 stale skips, and
reaches peak frontier size 4. Heap work makes 17 record comparisons.

Finalized order is A,C,B,D,E. B's predecessor changes A to C; E's changes A
to B to D. D stays C on B's equal proposal.

## 7. Reject unsafe numbers

A **parser** converts input text into stored values. It must reject negative
text before an **unsigned conversion**, or conversion to a type that cannot
represent negative values.

**Overflow** means an arithmetic result exceeds its type's range. Never add
from `INF`. Before addition, require the weight to be no greater than
`INF-dist[u]`. If the sum would overflow or equal the reserved `INF` marker,
return `DIJKSTRA_COST_RANGE`. Preserve caller output. Silently calling that
vertex unreachable would confuse a cost too large to store with no path.

Zero-weight edges are valid. Negative edges are not. For example, edges
`S->X 2`, `S->Y 5`, and `Y->X -10` make the true X cost -5 after X might
already have been finalized at 2.

## 8. Recover and check

To **reconstruct** a path is to follow predecessors backward, then reverse
them. For E:

```text
backward E,D,C,A
forward  A,C,D,E
cost     2+2+2 = 6
```

Follow at most `V` vertices, where `V` means active vertex count. That bound
detects a malformed **cycle**, a chain returning to an earlier vertex.
Verify that every predecessor edge exists and that its weights add to the
reported distance. This supports the result but does not prove the input
describes reality.

`dijkstra_result_validate` checks visible array, count, sentinel, and trace
relationships without receiving the graph. It cannot prove a claimed
predecessor edge existed. A test receiving the graph must look up every
consecutive edge and independently add its weight. The source-to-source path
is `[A]` with cost 0. Requesting F returns `DIJKSTRA_UNREACHABLE` while
preserving path output.

## 9. Cost and scope

Let `E` mean directed-edge count. `O(n)` means work may grow with all `n`
items. `O(log n)` grows with Heap height. Lazy duplicates permit at most one
successful relaxation per edge, so Heap time is
`O(V + E log(E + 1))`.

**Auxiliary state** is extra storage beyond input. Arrays use `O(V)` and
snapshots use `O(E)`, totaling `O(V+E)`. A **parallel edge** repeats a
start/end pair; a **self-loop** returns to its starting vertex. A **simple
graph** has neither, giving `O(V + E log V)`. A **backend** is a collection's
storage method. Module 10's linear backend can take `O(V+E^2)`. Do not claim
a decrease-key bound.

With 16 vertices, a simple directed graph can have 240 edges and 241
snapshot insertions. Module 11 capacity 64 cannot guarantee fit. Return an
explicit limit failure; never drop pending work.

Graph building/validation adds `O(V+E)` here; its fixed 16-by-16 checking
table is constant. If generalized, a `V`-by-`V` table adds work proportional
to `V` times `V`.

Weights assume costs are known, **static** (unchanging), and **additive**
(combined by addition). It cannot prove input authenticity, future
conditions, parallel effects, fairness, severity, or security. `INF` for F
describes only the stored directed model.
