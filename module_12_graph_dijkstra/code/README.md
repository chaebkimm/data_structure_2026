# Module 12 C Package

This package finds minimum-cost routes in a small weighted graph.

An **edge** is one modeled connection. Its **weight** is the nonnegative cost
of following it. An **arc** is one stored direction: an undirected edge owns
two arcs. An **adjacency list** stores each vertex's outgoing edges together.

## Weighted graph contract

`WeightedGraph` owns up to sixteen sorted dynamic rows. The graph is simple:
self-loops and parallel edges are forbidden. A directed graph can store at
most `16 * 15 = 240` arcs. An undirected edge stores matching weights in both
directions and adds two to `arc_count`.

Each row grows through capacities `0, 4, 8, 16`. Live destinations are
strictly ascending. The complete validator checks row ownership fields,
destination bounds, unique ordering, weights, inactive rows, `arc_count`,
and reverse arcs for an undirected graph.

`size_t` is C's unsigned type for sizes and indexes. The typed edge function
therefore cannot receive a negative value. The public text parser rejects a
leading minus before unsigned conversion. It also rejects malformed decimal
text, arithmetic overflow, and `SIZE_MAX`, which this module reserves as
infinity. Every parse failure preserves its output.

Undirected insertion stages both possible row allocations before changing
either side. Every graph failure preserves the complete graph.

## Dijkstra in plain language

Dijkstra's algorithm repeatedly chooses the unfinished vertex with the
smallest known route cost.

- The **Frontier** is pending work.
- To **relax** an edge means testing whether it creates a cheaper route.
- A vertex is **finalized** when its minimum route cost is proven.
- A **predecessor** is the prior vertex on the chosen route.

This implementation uses a stable binary minimum Heap. Stable means equal
distances leave in insertion order; vertex ID never breaks a tie.

When relaxation improves a distance, the algorithm inserts a new Heap entry
instead of finding and editing an old entry. This is the **lazy duplicate**
method. An older entry is **stale** when its stored distance differs from the
current distance, so it is popped and skipped.

Equal-cost alternatives do not replace a predecessor:

```text
candidate < current distance     improve and push
candidate == current distance    keep the earlier route
```

The new Frontier entry is pushed before distance and predecessor change.
An allocation failure therefore cannot leave a half-committed improvement.

## Frontier capacity proof

The Frontier limit is `arc_count + 1`, at most 241. The source causes one
push. Each successful strict relaxation can be charged to the one stored arc
being inspected, and each arc is inspected only when its source is finalized.
Thus at most `E + 1` entries are pushed.

Capacity grows geometrically:

```text
0 -> min(8, limit) -> 16 -> 32 -> 64 -> 128 -> limit
```

Every step is clipped to the exact limit. This is a dedicated Dijkstra
Frontier, not Module 11's teaching Heap capped at 64.

## Numeric range rule

`DIJKSTRA_INF` is `SIZE_MAX`. Before computing finite distance `d` plus
weight `w`, the algorithm requires:

```text
d != DIJKSTRA_INF
w <= DIJKSTRA_INF - d
```

It then rejects a safe sum equal to `DIJKSTRA_INF`, because that value is the
unreachable sentinel. Either case returns `DIJKSTRA_COST_RANGE`. It does not
silently treat an out-of-range reachable route as unreachable. Every failure
preserves the caller's result; the input graph is always `const` and unchanged.

## Canonical trace

The six-vertex directed graph is:

```text
0: (1,9) (2,2) (4,14)
1: (3,0) (4,8)
2: (1,2) (3,2)
3: (4,2)
4:
5:
```

From source 0:

```text
distance:  0 4 2 4 6 INF
predecessor: NO 2 0 2 3 NO
finalized order: 0 2 1 3 4
```

Pop events are written `vertex/distance/sequence`:

```text
0/0/s0 current
2/2/s2 current
1/4/s4 current
3/4/s5 current
4/6/s7 current
1/9/s1 stale
4/12/s6 stale
4/14/s3 stale
```

There are 8 relaxation attempts, 7 improvements, 8 pushes, 8 pops, 3 stale
pops, a peak Frontier size of 4, and exactly 17 stable Heap comparisons.
The selected route to 4 is `0, 2, 3, 4` with cost 6. The equal route through
vertex 1 does not rewrite predecessor 3. Vertex 5 is unreachable.

## Results and paths

`DijkstraResult` records final distances, predecessors, finalized state and
order, the bounded pop trace, and counters. Inactive and unused slots hold
explicit sentinels. The supplied validator checks these visible
relationships without reading the original graph; it cannot prove that a
predecessor edge existed without receiving that graph.

Path reconstruction returns source through destination, including both
endpoints. The source-to-source path has one vertex and cost zero.
Unreachable, out-of-range, and malformed-result failures preserve the prior
path output.

## Cost

Let `V` be active vertices and `E` stored arcs.

- Weighted adjacency-list validation scans `O(V + E)` state after
  constant-size 16-by-16 scratch initialization. A generalized `V`-by-`V`
  scratch table would add `O(V^2)` initialization.
- Heap push and pop are `O(log(E + 1))`.
- Dijkstra is `O(V + E log(E + 1))`.
- The simple-graph bound also permits `O(V + E log V)`.
- Graph, result, and lazy Frontier storage total `O(V + E)`.

Geometric growth may make one push copy `O(E)` entries; across all growth
steps, copying is amortized, meaning its total is spread across the pushes.
Graph construction cost is separate.

## Student-controlled work

`starter/dijkstra.c` contains exactly three numbered tasks:

1. nonnegative decimal weight parsing;
2. Heap-backed Dijkstra with lazy stale entries and checked cost range; and
3. predecessor-path reconstruction.

The student test file contains exactly three additional categories covering
parser/range preservation, stale/equal relaxation, and path boundaries.
Graph mutation and validation, the stable Frontier Heap, result validation,
status helpers, core tests, extension tests, and the safe overflow autopsy
are supplied.

## Build commands

From this `code` directory on Windows:

```powershell
# Starter scaffold: compiles, then tests fail until completed.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1

# Instructor reference and extension tests.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions

# Student-authored tests and isolated autopsy.
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The script selects Clang, GCC, or Microsoft C from `PATH`. `-Sanitize` adds
runtime checks where the selected compiler supports them.

With GNU Make:

```sh
make starter-core
make starter-student-tests
make solution-core
make solution-extension
make autopsy
```

The Makefile is intended for Git Bash, MSYS2, WSL, Linux, or macOS.
