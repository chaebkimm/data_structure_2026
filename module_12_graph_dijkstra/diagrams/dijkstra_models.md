# Dijkstra Models and Exact Linear Equivalents

Every visual is followed by an exact linear text equivalent. No meaning
depends on color, line thickness, drawing quality, or spatial position.

## Model 1 - Canonical weighted directed graph

A **vertex** is one stored place. A **directed edge** is a connection usable
only in its shown direction. A **weight** is its numeric modeled cost.

```text
A --9--> B
A --2--> C
A --14--> E
B --0--> D
B --8--> E
C --2--> B
C --2--> D
D --2--> E
E: no outgoing edge
F: no outgoing edge; no path from A
```

Exact linear equivalent:

1. IDs are A=0, B=1, C=2, D=3, E=4, and F=5.
2. A has edges to B weight 9, C weight 2, and E weight 14.
3. B has edges to D weight 0 and E weight 8.
4. C has edges to B weight 2 and D weight 2.
5. D has one edge to E weight 2.
6. E and F have no outgoing edges.
7. No directed path from A reaches F.

## Model 2 - BFS and Dijkstra answer different questions

**Breadth-first search (BFS)** processes vertices by edge-count layers.
**Dijkstra's algorithm** processes current least modeled cost when weights
are **nonnegative**, meaning zero or greater.

```text
BFS:
A --------14--------> E
1 edge, cost 14

Dijkstra:
A --2--> C --2--> D --2--> E
3 edges, cost 6
```

Exact linear equivalent:

1. BFS chooses direct path A,E because it has one edge.
2. The direct path costs 14.
3. Path A,C,D,E has three edges.
4. Its cost is 2+2+2, which equals 6.
5. Fewer edges need not mean lower total weight.
6. BFS minimizes edge count; Dijkstra minimizes total nonnegative weight.

## Model 3 - Tentative and finalized state

A **tentative distance** is the best cost known so far and may improve. A
distance is **finalized** when its current smallest snapshot is removed. A
**predecessor** is the previous vertex on the recorded path.

```text
after A:
B distance 9, tentative, predecessor A

after C:
B distance 4, tentative, predecessor C

pop B/4:
B distance 4, finalized, predecessor C
```

Exact linear equivalent:

1. A first proposes B cost 9 through A.
2. C later proposes B cost 2+2=4.
3. Strict improvement replaces distance 9 and predecessor A.
4. B remains tentative until current snapshot B/4 is removed.
5. Removing B/4 finalizes B at 4.
6. Old snapshot B/9 remains pending but cannot finalize B again.

## Model 4 - Strict relaxation has three cases

To **relax** an edge is to test whether it improves a distance. A
**candidate** is the proposed new cost. Strict relaxation updates only for a
smaller candidate.

```text
candidate < old:
push snapshot; after success, update distance and predecessor

candidate = old:
change nothing; push nothing

candidate > old:
change nothing; push nothing
```

Canonical equality:

```text
dist[B] + weight(B,D) = 4 + 0 = 4
dist[D] = 4
4 < 4 is false
pred[D] remains C
```

Exact linear equivalent:

1. A smaller candidate first prepares and pushes one new snapshot.
2. Only a successful push commits distance and predecessor.
3. An equal candidate changes nothing.
4. A larger candidate changes nothing.
5. B proposes D cost 4.
6. D already has cost 4 through C.
7. D keeps predecessor C and no duplicate D/4 is added.

## Model 5 - Complete canonical pop timeline

The **frontier** is pending work. A **snapshot** saves one vertex and
distance. A **pop** means removing the first-ranked snapshot. A **Heap** is
a tree-shaped Priority Queue. **Stable** means equal distances leave in
insertion order.

```text
pop A/0   current   push B/9,C/2,E/14
pop C/2   current   push B/4,D/4
pop B/4   current   push E/12
pop D/4   current   push E/6
pop E/6   current   push nothing
pop B/9   stale     skip
pop E/12  stale     skip
pop E/14  stale     skip
```

Exact linear equivalent:

1. Finalized order is A,C,B,D,E.
2. Stable insertion order removes B/4 before equal-distance D/4.
3. B's equal proposal for D creates no snapshot.
4. Current pops scan all eight outgoing edges once.
5. Seven relaxation attempts succeed.
6. Eight snapshots are pushed, including the source.
7. Eight snapshots are popped.
8. Three pops are stale.
9. Peak Frontier size is 4.
10. Normal Heap operations use 17 record comparisons.

## Model 6 - Lazy duplicate and stale test

A **lazy duplicate** is a new snapshot added without editing an older one.
A snapshot is **stale** when its saved distance differs from current
`dist`.

```text
stored snapshots: B/4 and B/9
current dist[B]:  4

pop B/9
9 != 4
skip before scanning B edges
```

Exact linear equivalent:

1. B/9 was inserted after A first reached B.
2. B/4 was inserted after C improved B.
3. This version performs no **decrease-key**, or lowering a priority already
   stored.
4. B/4 is current and finalizes B.
5. Later B/9 differs from current distance 4.
6. B/9 is stale and causes no edge scan.
7. E/12 and E/14 are skipped for the same reason after E becomes 6.

## Model 7 - Predecessor path reconstruction

To **reconstruct** is to follow predecessors backward and then reverse them.
`V` means the active vertex count.

```text
pred[E] = D
pred[D] = C
pred[C] = A

backward: E,D,C,A
reverse:  A,C,D,E
cost:     2+2+2 = 6
```

Exact linear equivalent:

1. Begin at destination E.
2. Follow predecessor E to D, D to C, and C to source A.
3. Reverse the collected order.
4. The returned path is A,C,D,E.
5. Independently verify edges A->C, C->D, and D->E.
6. Their weights sum to 6.
7. A result-only check cannot prove those graph edges existed.
8. A malformed predecessor walk is rejected after at most V vertices.

## Model 8 - Why negative weights are rejected

**Nonnegative** means zero or greater.

An **unsigned conversion** changes a value to a numeric type that cannot
represent negatives.

```text
S --2--> X
 \
  \5
   v
   Y --- -10 ---> X
```

Exact linear equivalent:

1. Direct S to X costs 2.
2. S to Y costs 5.
3. Y to X has negative weight -10.
4. S,Y,X therefore costs -5.
5. Dijkstra may finalize X at 2 before processing Y at 5.
6. The later negative edge invalidates finalization.
7. Text beginning with minus must be rejected before unsigned conversion.
8. Zero-weight edges remain valid.

## Model 9 - Overflow autopsy

`size_t` is C's nonnegative whole-number type for sizes. `INF` equals
`SIZE_MAX`, its largest value. **Overflow** is a result beyond the type's
range.

```text
dist[u] = SIZE_MAX - 3
weight  = 5
old dist[v] = 20

faulty unchecked sum wraps to 1
1 < 20 causes false improvement

correct:
INF - dist[u] = 3
5 <= 3 is false
DIJKSTRA_COST_RANGE
```

Exact linear equivalent:

1. The mathematical sum exceeds `SIZE_MAX`.
2. Unsigned storage wraps the unchecked sum to 1.
3. The faulty code treats 1 as cheaper than old distance 20.
4. Every vertex index can remain valid despite the false cost.
5. Correct code subtracts before adding.
6. Weight 5 exceeds remaining range 3.
7. The whole operation returns `DIJKSTRA_COST_RANGE`.
8. The **caller** is code requesting work; its **output**, where the answer
   is written, remains unchanged with predecessor and Frontier state.

## Model 10 - Actual cost, storage limit, and scope

Let `V` be active vertices and `E` stored directed edges.
`O(n)` describes how work or storage may grow with `n`; `log n` grows with
Heap height. **Auxiliary state** is extra storage beyond the input. A
**parallel edge** repeats a start/end pair; a **self-loop** returns to its
starting vertex. A **simple graph** has neither. A **backend** is a
collection's storage method. **Capacity** is its maximum entry count.

```text
Heap lazy time        O(V + E log(E + 1))
auxiliary state       O(V + E)
simple graph          O(V + E log V)
linear lazy backend   O(V + E^2)

16 vertices * 15 possible destinations = 240 arcs
source + at most one success per arc = 241 snapshot insertions
Module 11 capacity = 64
Module 12 capacity = 241
```

Exact linear equivalent:

1. Strict relaxation succeeds at most once per scanned edge.
2. Lazy work therefore creates at most E+1 snapshots.
3. Heap push/pop height depends on at most E+1 entries.
4. Arrays need O(V) extra state and snapshots need O(E).
5. A simple graph has E bounded by a multiple of V squared, so the logarithm
   simplifies to log V.
6. The linear lazy backend repeatedly scans pending snapshots and may take
   O(V+E squared).
7. This version performs no decrease-key.
8. Module 11's cap 64 does not cover the Module 12 graph contract.
9. Module 12 supplies a 241-entry Frontier; smaller limits fail explicitly.
10. Results depend on authentic, **static** (unchanging), **additive**
    (combined by addition) weights and cannot prove real-world availability,
    fairness, or system security.
