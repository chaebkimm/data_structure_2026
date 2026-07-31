# Stage E - C Lab: Dijkstra with Lazy Heap Snapshots

## Purpose

Extend the supplied adjacency-list graph with nonnegative weights, compute
least modeled costs, and reconstruct recorded paths. The lab has exactly
three marked unfinished tasks, called **TODOs**: parse weight text, run
Dijkstra, and reconstruct a path.

To **parse** means convert input text into a stored value. To
**reconstruct** means recover a recorded path.

All places, routes, and weights are synthetic. Do not connect this program
to live logs, accounts, hosts, feeds, devices, or networks.

## Supplied support and limits

`weighted_graph.h` is a **public header**, a C file declaring names student
code may use. It supplies `WeightedGraph`, sorted outgoing `WeightedEdge`
arrays, validation, all-or-nothing edge changes, and cleanup.

**Capacity** is the maximum number of stored entries.

```text
WEIGHTED_GRAPH_MAX_VERTICES = 16
WEIGHTED_GRAPH_MAX_ARCS = 240
```

A stored **arc** is one directed edge. An **undirected** connection works
both ways and stores two arcs. A **self-loop** returns to its starting
vertex; a **parallel edge** repeats an existing start/end pair. Both are
rejected. Every stored weight is below `SIZE_MAX`.

The **Frontier** is pending work. `dijkstra_frontier.h` supplies a **stable**
minimum binary Heap; stable means equal priorities leave in insertion order.
A **Priority Queue** removes its first-ranked record. A **Heap** is a
tree-shaped Priority Queue; **binary** means each position has at most two
children. A `DijkstraFrontierEntry` stores vertex, distance, and a sequence
number that records insertion order. Vertex ID never breaks an equal tie.
Removing every entry keeps reserved storage and the next sequence number;
`dijkstra_frontier_destroy` resets both.

```text
DIJKSTRA_FRONTIER_MAX_ENTRIES = 241
```

The Frontier is supplied support, not a student TODO. Its separate
`dijkstra_frontier_is_min_heap` function performs **debug checking**, extra
checking used to find defects, and is not part of normal Dijkstra comparison
totals.

## Required result behavior

`dijkstra.h` defines:

```c
DijkstraStatus dijkstra_shortest_paths(
    const WeightedGraph *graph,
    size_t source_vertex,
    DijkstraResult *out_result
);

DijkstraStatus dijkstra_reconstruct_path(
    const DijkstraResult *result,
    size_t destination_vertex,
    DijkstraPath *out_path
);
```

In these C declarations, `*` marks an address-based parameter, `const` means
read-only through that parameter, and `NULL` means no valid object address.
`DijkstraStatus` is a named outcome code.

`DijkstraResult` stores graph/source facts, all 16 distance, predecessor,
and finalized slots, finalized order, every bounded pop event, and exact
operation counters. Unused slots use required false values or **sentinels**,
named markers with special meanings.

```text
DIJKSTRA_NO_VERTEX = 16
DIJKSTRA_NO_SEQUENCE = SIZE_MAX
DIJKSTRA_INF = SIZE_MAX
DIJKSTRA_MAX_POP_EVENTS = 241
```

`DIJKSTRA_NO_VERTEX` marks no vertex, `DIJKSTRA_NO_SEQUENCE` marks no
insertion sequence, and `DIJKSTRA_INF` marks no finite representable cost.

The **caller** is code requesting work; **output** is where its answer is
written. An **allocation** reserves storage while the program runs.
**Ownership** means responsibility for releasing it. Every failure preserves
caller output, the input graph is never changed, and every temporary
allocation is released. To **publish** means copy a completed answer to
output.

## Files and build

To **build** means compile source code into a runnable program.

Edit only the three numbered starter TODO regions and the three student-test
functions named by the supplied template. Do not change public headers or
supplied Frontier/graph support.

Use the warning-enabled commands documented by the code package. The
standard package commands are:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Preserve command and output evidence. Run the smallest relevant test after
each change.

## TODO 1 - Parse weight text

Implement `weighted_graph_parse_weight`:

```c
WeightedGraphStatus weighted_graph_parse_weight(
    const char *text,
    size_t *out_weight
);
```

Required behavior:

1. reject invalid arguments and preserve output;
2. accept surrounding **ASCII whitespace**, meaning ordinary spaces, tabs,
   or line breaks;
3. accept one optional leading plus;
4. require at least one decimal digit and no trailing nonspace text;
5. return `WEIGHTED_GRAPH_NEGATIVE_WEIGHT` for a leading minus before any
   **unsigned conversion**, which changes a value to a type with no negative
   values;
6. detect arithmetic range failure while reading digits;
7. reject `SIZE_MAX`, which is reserved as `DIJKSTRA_INF`;
8. return `WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE` for an unrepresentable or
   reserved value;
9. return `WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT` for malformed text; and
10. publish output only on `WEIGHTED_GRAPH_OK`.

Checkpoint: `"  +0 "` and `"14"` succeed; `"-1"`, `""`, `"4x"`,
overflowing decimal text, and decimal `SIZE_MAX` fail without changing the
output marker.

## TODO 2 - Run Dijkstra

Implement `dijkstra_shortest_paths` with local state:

1. reject NULL output before graph validation;
2. validate the complete weighted graph and source ID;
3. initialize every result slot, counter, and sentinel locally;
4. initialize a Frontier whose limit safely covers `arc_count + 1`;
5. set source distance 0 and push its snapshot;
6. pop until the Frontier is empty;
7. record every bounded `DijkstraPopEvent`;
8. mark an event stale when its snapshot distance differs from current
   distance, increment the stale count, and continue before edge scanning;
9. finalize each current vertex and record its order;
10. inspect each outgoing edge and count one relaxation attempt;
11. reject a sum that overflows or equals `DIJKSTRA_INF`;
12. on strict improvement, push the prepared new snapshot first;
13. only after a successful push, commit local distance/predecessor and
    count success;
14. map Frontier allocation or limit failures to the matching Dijkstra
    status;
15. save peak size and normal Heap comparison count;
16. destroy the Frontier on every exit; and
17. publish the complete result only on `DIJKSTRA_OK`.

Do not push an equal candidate. Do not scan edges from a stale snapshot. Do
not silently drop a snapshot after `FULL`.

Canonical checkpoint:

```text
finalized order: A,C,B,D,E
distance:        0,4,2,4,6,INF
predecessor:     -,C,A,C,D,-
attempts:        8
successes:       7
pushes:          8
pops:            8
stale pops:      3
frontier peak:   4
Heap comparisons: 17
```

The stale pop trace ends `B/9, E/12, E/14`.

## TODO 3 - Reconstruct a path

Implement `dijkstra_reconstruct_path`:

1. reject NULL output before result validation;
2. validate all visible result relationships;
3. reject a destination outside the active range;
4. return `DIJKSTRA_UNREACHABLE` when its distance is `DIJKSTRA_INF`;
5. follow predecessors backward from destination;
6. reject an out-of-range marker, repeated vertex, or chain longer than
   `vertex_count`;
7. require the chain to reach the source;
8. reverse locally into source-to-destination order;
9. set total cost from the validated result distance; and
10. publish output only on `DIJKSTRA_OK`.

Checkpoints:

```text
E path: A,C,D,E  cost 6
A path: A        cost 0
F: DIJKSTRA_UNREACHABLE, output preserved
```

The result-only validator cannot prove that predecessor edges exist in the
original graph. Tests with the graph must independently verify each edge and
sum.

## Exactly three student-authored test categories

Write exactly three numbered test functions. An **assertion** is a test
check that must be true. State the claim before its assertions.

1. **Parser and range preservation:** cover accepted zero/plus/whitespace,
   negative text, malformed text, decimal overflow, reserved `SIZE_MAX`,
   exact statuses, and unchanged output on every failure.
2. **Lazy stale trace and equal predecessor:** run the canonical graph;
   assert exact arrays, finalized/pop traces, all counters including 17 Heap
   comparisons, three stale skips, and D predecessor C after B's equal
   zero-edge proposal.
3. **Paths, source, unreachable, and preservation:** reconstruct E and A;
   request F, an invalid destination, and a malformed result; prove exact
   statuses and complete output preservation.

Forced allocation failure, responsibility for releasing graph storage,
Frontier `FULL`, invalid source, candidate range failure, undirected
storage, and broader reference sequences are covered by supplied instructor
tests. Three renamed copies of one fixture earn credit once.

## Safe autopsy

Complete `dijkstra_autopsy.md` before and after running
`faulty_overflow.c`. Its frozen values are:

```text
dist[u] = SIZE_MAX - 3
weight = 5
old dist[v] = 20
unchecked wrapped candidate = 1
```

All indexes remain bounded. The correct result is
`DIJKSTRA_COST_RANGE` with caller state preserved.

## Actual complexity

Let `V` mean active vertices and `E` mean stored directed arcs. Lazy strict
relaxation creates at most `E+1` snapshots.
`O(n)` means work or storage may grow with all `n` items; `log n` grows with
Heap height. **Auxiliary state** is extra storage beyond the input.

```text
Heap time:          O(V + E log(E + 1))
auxiliary state:    O(V + E)
simple-graph time: O(V + E log V)
linear lazy time:  O(V + E^2)
```

This code inserts lazy duplicates and never performs **decrease-key**, which
means lowering a priority already stored. Do not claim a decrease-key bound.
Debug Heap checking is separate work.

## Storage limits, trustworthy state, and scope

A **simple graph** has neither parallel edges nor self-loops. With 16
vertices, a simple directed graph permits 240 arcs and up to 241 snapshot
insertions. Module 11's 64-record teaching Heap is insufficient for that
contract. The supplied Module 12 Frontier supports 241. Any configured
smaller limit must return `DIJKSTRA_LIMIT`; it must never discard work.

Strict relaxation, stale checking, range guards, graph validation, and
bounded reconstruction support **result integrity**, meaning stored state
obeys its required rules. They do not prove:

- input authenticity or completeness;
- weights are accurate, static, or additive;
- real work occurs sequentially;
- fairness or absence of starvation;
- operational availability;
- safe simultaneous use; or
- overall system security.

`DIJKSTRA_UNREACHABLE` means no stored directed path under the validated
model. It is not a real-world impossibility claim.

## Submission

An **abstract data type (ADT)** states behavior independent of storage. An
**application programming interface (API)** is the set of named operations
code calls. An **implementation** is the code and storage choice performing
those operations.

Submit:

- all three TODOs;
- exactly three student-test categories;
- core and student-test output with no compiler warnings;
- canonical arrays, pop trace, counters, and Heap comparisons;
- reconstructed paths and independent costs;
- parser/range preservation evidence;
- same-graph BFS/linear/Heap paths, calls, comparisons, and API names;
- Priority Queue ADT behavior versus linear/Heap implementation details and
  actual complexity;
- completed evidence record and safe autopsy; and
- corrected Cognitive Pause.
