# Instructor Technical Notes - Module 12

## Fixed public surface

Do not rename public types, constants, statuses, or functions.

Headers:

```text
weighted_graph.h
dijkstra_frontier.h
dijkstra.h
```

Weighted graph types and limits:

```text
WeightedGraphKind
WeightedEdge
WeightedEdgeArray
WeightedGraph
WeightedGraphStatus
WEIGHTED_GRAPH_MAX_VERTICES = 16
WEIGHTED_GRAPH_MAX_ARCS = 240
```

Public graph functions:

```text
weighted_graph_init
weighted_graph_validate
weighted_graph_parse_weight
weighted_graph_add_edge
weighted_graph_add_edge_text
weighted_graph_get_weight
weighted_graph_destroy
weighted_graph_status_name
```

Frontier types and limit:

```text
DijkstraFrontierEntry
DijkstraFrontier
DijkstraFrontierStatus
DIJKSTRA_FRONTIER_MAX_ENTRIES = 241
```

Public Frontier functions:

```text
dijkstra_frontier_init
dijkstra_frontier_validate
dijkstra_frontier_is_min_heap
dijkstra_frontier_push
dijkstra_frontier_pop
dijkstra_frontier_destroy
dijkstra_frontier_status_name
```

Dijkstra types, constants, and functions:

```text
DijkstraPopEvent
DijkstraResult
DijkstraPath
DijkstraStatus
DIJKSTRA_NO_VERTEX = 16
DIJKSTRA_NO_SEQUENCE = SIZE_MAX
DIJKSTRA_INF = SIZE_MAX
DIJKSTRA_MAX_POP_EVENTS = 241

dijkstra_shortest_paths
dijkstra_result_validate
dijkstra_reconstruct_path
dijkstra_status_name
```

## Weighted graph contract

`WeightedGraph` owns every non-NULL outgoing-row allocation. Active
destinations are sorted, unique, in range, and never self-loops. Weights are
below `SIZE_MAX`. Inactive rows are canonical empty rows.

`arc_count` counts stored directed arcs. An undirected connection stores two
matching arcs and increments the count by two.

Every mutation stages allocation before commit. Every failure preserves the
complete graph. Destroy restores the all-zero directed state.

## Parser contract

`weighted_graph_parse_weight` accepts:

- surrounding ASCII whitespace;
- one leading plus; and
- one or more decimal digits representing 0 through `SIZE_MAX-1`.

It distinguishes:

```text
leading minus       WEIGHTED_GRAPH_NEGATIVE_WEIGHT
bad or empty text   WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT
overflow/SIZE_MAX   WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE
```

Reject the minus before unsigned conversion. Detect digit accumulation
without overflow. Publish `out_weight` last.

## Frontier contract

The Frontier is a stable binary minimum Heap over:

```text
distance, then insertion_sequence
```

Vertex ID never ranks an entry. The caller chooses limit 0 through 241. The
first successful push grows capacity from 0 to the smaller of 8 and the
limit. Later growth doubles through 16, 32, 64, and 128, then clips to the
configured limit. Draining retains the allocation and `next_sequence`; only
destroy resets both.

The Heap checker scans entries but intentionally does not change
`comparison_count`. Dijkstra stores normal Heap-operation comparisons only.

All Frontier failures preserve fields, entries, and output. Dijkstra maps
allocation failure to `DIJKSTRA_ALLOCATION` and capacity/sequence failure to
`DIJKSTRA_LIMIT`.

## Result canonical state

`DijkstraResult` uses all 16 slots so validation can check inactive state.
A successful complete run records:

- graph vertex and arc counts;
- source;
- distances;
- predecessors;
- finalized flags and order;
- every bounded pop event;
- push, pop, stale, peak, relaxation, and Heap-comparison counts.

Inactive distance slots use `DIJKSTRA_INF`; inactive predecessor/order slots
use `DIJKSTRA_NO_VERTEX`; inactive finalized flags are false; unused pop
events use `DIJKSTRA_NO_SEQUENCE` and the other canonical empty values.

Every Dijkstra failure preserves `out_result` and the input graph. Temporary
Frontier storage is destroyed on every exit.

## Dijkstra loop

Required order:

1. reject NULL output;
2. validate graph;
3. reject source outside active range;
4. initialize the complete local result;
5. initialize Frontier limit `arc_count + 1`;
6. set source distance 0 and push source;
7. pop and record one event;
8. compare snapshot distance with current distance;
9. mark/count stale and continue before scanning when unequal;
10. finalize the current vertex and append its order;
11. scan outgoing edges in stored destination order;
12. count each relaxation attempt;
13. guard cost arithmetic;
14. on strict improvement, prepare and push the snapshot first;
15. only after push success, commit distance/predecessor and success count;
16. track counters and peak;
17. drain, destroy, validate local result, and publish last.

Strict relaxation is:

```text
candidate < distance[to]
```

Equality changes neither predecessor nor Frontier.

## Cost-range contract

Never add from `DIJKSTRA_INF`.

For finite `d` and weight `w`:

```text
if w > SIZE_MAX - d:
    DIJKSTRA_COST_RANGE
candidate = d + w
if candidate == DIJKSTRA_INF:
    DIJKSTRA_COST_RANGE
```

This is an explicit whole-operation failure with output preservation. It
does not silently convert an unrepresentable path into unreachable.

## Why finalization needs nonnegative weights

Let current vertex `u` have the smallest tentative distance `d`. Any path
reaching `u` through an unfinished vertex first has a prefix at least `d`;
adding a nonnegative suffix cannot lower it below `d`. Therefore a current
pop may finalize `u`.

Counterexample:

```text
S->X 2
S->Y 5
Y->X -10
```

X may be finalized at 2 before Y, although the path through Y costs -5.
Reject negative text before converting to `size_t`.

## Canonical fixture

IDs:

```text
A=0 B=1 C=2 D=3 E=4 F=5
```

Directed edges, inserted in this order:

```text
A->B 9
A->C 2
A->E 14
B->D 0
B->E 8
C->B 2
C->D 2
D->E 2
```

Outgoing storage is sorted by destination.

## Canonical trace

Initialization:

```text
distance     0,INF,INF,INF,INF,INF
predecessor  -, -, -, -, -, -
frontier     A/0
```

After current A:

```text
distance     0,9,2,INF,14,INF
predecessor  -,A,A,-,A,-
frontier     C/2,B/9,E/14
```

After current C:

```text
distance     0,4,2,4,14,INF
predecessor  -,C,A,C,A,-
frontier     B/4,D/4,B/9,E/14
```

Stable insertion order places B/4 before D/4.

After current B:

```text
B->D candidate 4 equals distance[D]: no change, no push
B->E candidate 12 improves 14

distance     0,4,2,4,12,INF
predecessor  -,C,A,C,B,-
frontier     D/4,B/9,E/12,E/14
```

After current D:

```text
E improves 12 to 6
predecessor[E] becomes D
frontier E/6,B/9,E/12,E/14
```

After E/6, remaining pops are stale B/9, E/12, E/14.

Final:

```text
finalized order  A,C,B,D,E
distance         0,4,2,4,6,INF
predecessor      -,C,A,C,D,-
attempts         8
successes        7
pushes           8
pops             8
stale pops       3
frontier peak    4
Heap comparisons 17
```

## BFS contrast

BFS ignores weights and returns direct A,E:

```text
1 edge
cost 14
```

Dijkstra reconstructs:

```text
A,C,D,E
3 edges
cost 2+2+2 = 6
```

Equal-cost alternative `A,C,B,D,E` also costs 6. Strict relaxation and
stored order retain predecessor D=C. Do not claim uniqueness.

## Path reconstruction

`dijkstra_reconstruct_path` validates the result, rejects an invalid
destination, and returns `DIJKSTRA_UNREACHABLE` before modifying output when
distance is `DIJKSTRA_INF`.

For reachable input, collect at most `vertex_count` vertices backward,
reject repetition/range/missing-source defects, reverse locally, set
`total_cost` from the result, and publish last.

Checkpoints:

```text
E: A,C,D,E cost 6
A: A cost 0
F: DIJKSTRA_UNREACHABLE
```

The result-only validator cannot prove that predecessor edges exist. Tests
with the graph must verify edge existence and sum.

## Actual complexity

Let `V` be active vertices and `E` stored arcs. Each current vertex scans
its outgoing row once. Strict relaxation succeeds at most once per scanned
edge, so at most `E+1` snapshots are pushed and popped.

```text
Heap lazy time        O(V + E log(E + 1))
auxiliary state       O(V + E)
simple graph          O(V + E log V)
linear lazy backend   O(V + E^2)
```

The linear bound describes the same lazy duplicate strategy over the
Module 10 unsorted backend. Standard direct-array Dijkstra would be a
different implementation. No decrease-key occurs, so do not quote a
decrease-key bound.

## Capacity boundary

With 16 vertices and no self-loops, a simple directed graph has at most:

```text
16 * 15 = 240 arcs
source + one success per arc = 241 possible snapshot insertions
```

Module 11's cap 64 is not sufficient. The supplied Module 12 Frontier
supports 241 entries. Any smaller configured limit must produce
`DIJKSTRA_LIMIT`; pending work is never dropped.

## Integrity and security scope

Controls:

- graph validation before scanning;
- negative-text rejection;
- strict relaxation;
- stale skip before edge access;
- guarded addition;
- bounded pop trace;
- bounded predecessor traversal;
- output-last failure preservation; and
- cleanup on every exit.

They cannot prove authentic or complete input, accurate/static/additive
weights, sequential real work, fairness, availability, absence of
adversarial manipulation, or overall system security. All course fixtures
remain synthetic.

## Exactly three student tests

Required categories:

1. parser and range preservation;
2. lazy stale trace and equal predecessor; and
3. paths, source, unreachable, and preservation.

Core/private coverage supplies allocation injection, Frontier limits,
invalid graphs/sources, cost-range failure, broader workload order, and
reference comparisons.

## Instructor release checklist

- [ ] Stage A contains none of the locked formal vocabulary or answers.
- [ ] Standard and linear headings and semantic tasks match.
- [ ] Pause has exactly three Target headings and locked states.
- [ ] Canonical order, arrays, and all seven counters are exact.
- [ ] B/D stable tie and strict equal proposal are distinguished.
- [ ] Negative text is rejected before unsigned conversion.
- [ ] Overflow or candidate `INF` returns `DIJKSTRA_COST_RANGE`.
- [ ] Failed operations preserve output and release local ownership.
- [ ] Student TODOs and three tests match code.
- [ ] Autopsy wraps to 1 and correct behavior preserves state.
- [ ] Complexity matches lazy duplicates and no decrease-key.
- [ ] The 241-versus-64 distinction is explicit.
- [ ] Model and security claims remain bounded.
