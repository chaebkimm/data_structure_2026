# Instructor Technical Notes - Module 16

## Fixed scope

Module 16 reuses, rather than asks students to rewrite:

- Module 14 DSU;
- the signed undirected logical-edge builder and relational comparator;
- dynamic stable minimum-Heap storage;
- graph validation and indexed-adjacency construction;
- order-independent signed-total arithmetic; and
- full structural/minimum validation.

Students complete two Prim clusters and one Kruskal cluster. Directed
minimum arborescences, decrease-key, dynamic MST maintenance, resilience
optimization, and live data are outside core scope.

## Public headers and limits

Headers:

```text
dsu.h
undirected_edge_list.h
prim_frontier.h
minimum_spanning_forest.h
```

Fixed bounds:

```text
UNDIRECTED_EDGE_LIST_MAX_VERTICES          16
UNDIRECTED_EDGE_LIST_MAX_LOGICAL_EDGES    120
UNDIRECTED_EDGE_LIST_MAX_INCIDENT_RECORDS 240
MST_MAX_SELECTED_EDGES                     15
PRIM_FRONTIER_MAX_ENTRIES                 136
MST_NO_VERTEX                              16
MST_NO_EDGE                               120
```

Do not rename public types, constants, statuses, fields, or functions.

## Graph and edge representations

Public records:

```c
typedef struct {
    size_t from;
    size_t to;
    int64_t weight;
    size_t edge_id;
} UndirectedIncidentRecord;

typedef struct {
    size_t u;
    size_t v;
    int64_t weight;
    size_t edge_id;
} UndirectedEdge;
```

`UndirectedIncidentGraph` stores `vertex_count`, `logical_edge_count`,
`incident_count`, and 240 bounded incident slots. Each dense logical edge ID
occurs exactly twice:

- ordinary edge: reciprocal endpoint records with equal weight;
- self-loop: two identical records;
- parallel edge: a distinct ID, even when endpoints and weight match; and
- inactive slot: exact zero record.

`UndirectedEdgeList` contains one normalized `u<=v` record per logical ID.
The public comparator orders relationally by:

1. signed `int64_t` weight;
2. `u`;
3. `v`; and
4. edge ID.

It never subtracts numeric fields. Sorting validates before `qsort`;
invalid input remains unchanged.

`MstAdjacencyIndex` stores vertex offsets and logical edge IDs. Each vertex
slice is ordered by edge ID. A self-loop occurs twice. Building the index is
`O(V+E)` and commits only on success.

Prim must use this index. Scanning all 240 flat records once for every
selected vertex would add `O(VE)` and invalidate the required complexity
claim.

## Graph construction API

Exact functions:

```c
MstStatus mst_graph_init(
    UndirectedIncidentGraph *graph,
    size_t vertex_count
);

MstStatus mst_graph_add_edge(
    UndirectedIncidentGraph *graph,
    size_t u,
    size_t v,
    int64_t weight
);

MstStatus mst_graph_validate(
    const UndirectedIncidentGraph *graph
);

MstStatus mst_parse_weight(
    const char *text,
    int64_t *out_weight
);

MstStatus mst_adjacency_index_build(
    const UndirectedIncidentGraph *graph,
    const UndirectedEdgeList *edge_list,
    MstAdjacencyIndex *out_index
);
```

`mst_graph_add_edge` assigns the next dense edge ID and adds both incident
records all-or-nothing. Endpoints are checked before indexing. Self-loops
and parallel edges are accepted.

The parser accepts surrounding ASCII whitespace, one optional leading sign,
and an exact signed decimal `int64_t`. It accepts `INT64_MIN` and
`INT64_MAX`. It distinguishes malformed text from range failure and
preserves output on failure.

## Status contract

Exact `MstStatus` values:

```text
MST_OK
MST_INVALID_ARGUMENT
MST_OUT_OF_RANGE
MST_LIMIT
MST_INVALID_GRAPH
MST_INVALID_WEIGHT_TEXT
MST_WEIGHT_OUT_OF_RANGE
MST_ALLOCATION
MST_TOTAL_OUT_OF_RANGE
MST_INVALID_RESULT
MST_NOT_MINIMUM
MST_INVALID_STATE
```

Public status-name fallback must remain defined. Invalid arguments, graph
defects, numeric failures, allocation failure, and internal-state failure
preserve complete caller output. Inputs are read-only during algorithms.

## Result contract

Exact result fields:

```c
typedef struct {
    size_t vertex_count;
    size_t input_edge_count;
    UndirectedEdge selected_edges[15];
    size_t selected_count;
    size_t component_count;
    int64_t total_weight;
} MstForest;

typedef struct {
    MstForest forest;
    size_t push_count;
    size_t pop_count;
    size_t stale_pop_count;
    size_t already_in_tree_pop_count;
    size_t frontier_peak;
    size_t incident_scan_count;
    size_t eligible_crossing_count;
    size_t key_improvement_count;
} PrimResult;

typedef struct {
    MstForest forest;
    size_t examined_edge_count;
    size_t cycle_skip_count;
    size_t self_loop_skip_count;
} KruskalResult;
```

Selected edges retain exact input IDs and weights. Prim stores selection
order; Kruskal stores sorted decision order. Inactive selected slots are
zero. Empty input succeeds with zero components. A singleton succeeds with
one component and no selected edges.

## Stable Prim Frontier

`PrimFrontierEntry` stores:

```text
vertex, signed key, parent, edge_id, insertion_sequence
```

The Heap compares signed key first and insertion sequence second. Vertex,
parent, and edge ID never break an equal-key tie. Draining retains allocation
and the global insertion sequence; only destroy resets sequence state.

The runtime limit is exactly `E+V`, at most 136:

- at most one root snapshot per component, bounded by `V`; and
- at most one strict key improvement per logical edge, bounded by `E`.

Frontier allocation and limit failures map to the corresponding MST status.
Destroy runs on every Prim exit.

## Prim algorithm contract

Exact API:

```c
MstStatus prim_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    PrimResult *out_result
);
```

The supplied wrapper:

1. builds the logical edge list;
2. builds one indexed adjacency view;
3. sets the result's input counts;
4. initializes a frontier with limit `E+V`;
5. calls the student component loop;
6. calculates the selected-edge total with the supplied helper;
7. destroys the frontier; and
8. commits output only on success.

TODO 1 must:

1. keep one monotone cursor, an index that moves only forward, and use it to
   restart at the smallest unvisited vertex when the frontier is empty;
2. push a root with key zero and no parent/edge;
3. pop and increment `pop_count`;
4. compare saved key, parent, and edge ID with the complete current best
   tuple first;
5. count a missing or mismatched tuple as stale and continue;
6. then count a current entry already in the tree;
7. store the exact parent edge for a current nonroot;
8. increment component count only for roots;
9. mark the vertex selected; and
10. invoke adjacency relaxation.

The stale-before-membership order is required. On the canonical graph it
produces stale count 3 and already-in-tree count 0.

TODO 2 must scan exactly the current vertex slice:

1. count every incident record;
2. ignore a self-loop or already-selected neighbor;
3. count every remaining eligible crossing;
4. require strict `weight < best_key[v]`;
5. push the complete snapshot before committing best state;
6. commit key, parent, edge ID, counter, and peak only after push success;
   and
7. preserve output after every failure.

Equal weight does not replace parent or edge ID.

Let `E` mean logical edges. Each incident record is scanned once when its
vertex enters the forest, so scanning is `O(V+E)`. Lazy Heap work is
`O(E log(E+1))`; root work adds `O(V)`. Total time is
`O(V + E log(E+1))`, and auxiliary storage is `O(V+E)`.

## Kruskal algorithm contract

Exact API:

```c
MstStatus kruskal_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    KruskalResult *out_result
);
```

The supplied wrapper validates/builds and sorts the logical edge list,
creates one DSU set per vertex, calls the student selection loop, computes
the checked total, and commits output last.

TODO 3 scans every sorted edge:

1. increment examined count;
2. count and skip a self-loop before root lookup;
3. find both representative roots;
4. count and skip equal roots;
5. check selected-edge capacity;
6. store the edge before union;
7. union and require that a merge occurred; and
8. copy final DSU component count.

Do not stop at `V-c`; the complete ledger and skip counters require all
logical edges to be examined. A parallel edge remains a candidate and may
later be skipped because its roots match.

Sorting is `O(E log E)`. Path-compressed, size-weighted DSU work is
`O(E alpha(V))` amortized; `alpha` is the extraordinarily slow-growing
inverse-Ackermann function. State this as near-linear after sorting, not as
constant worst-case work per call.

## Order-independent total

Exact helper:

```c
MstStatus mst_forest_total_checked(
    const UndirectedEdge *edges,
    size_t edge_count,
    int64_t *out_total
);
```

The helper computes the mathematical sum independent of selected-edge
order:

1. obtain unsigned magnitudes for positive and negative values;
2. handle `INT64_MIN` without signed negation;
3. cancel opposite-sign magnitudes;
4. accumulate only the remaining same-sign magnitude within its bound; and
5. commit output only when the final mathematical value fits `int64_t`.

Do not replace this with selection-order signed addition. A fitting result
may have a nonrepresentable intermediate prefix.

Required examples:

```text
2,000,000,000 + 2,000,000,000 = 4,000,000,000
INT64_MAX + INT64_MAX + INT64_MIN = INT64_MAX - 1
INT64_MAX + 1 = MST_TOTAL_OUT_OF_RANGE
INT64_MIN - 1 = MST_TOTAL_OUT_OF_RANGE
```

The first two succeed; the last two preserve output.

## Full validator

Exact API:

```c
MstStatus mst_forest_validate(
    const UndirectedIncidentGraph *graph,
    const MstForest *forest
);
```

This is an explicit supplied `O(V + E + EV)` diagnostic. Its minimum-cost
phase is `O(EV)`. Prim and Kruskal do not call it internally.

Structural phase:

- validate graph and result counts;
- require zero inactive slots;
- match every selected record exactly to one unique input edge ID;
- reject selected self-loops;
- use a local DSU to reject cycles;
- independently obtain the input component partition;
- require the same selected partition;
- require selected count `V-c`; and
- recompute and compare the order-independent total.

Structural failures return `MST_INVALID_RESULT`.

Minimum phase:

- for every unselected non-loop input edge;
- find the unique selected-forest path between its endpoints in bounded
  `O(V)` work;
- obtain the maximum selected edge weight on that path; and
- return `MST_NOT_MINIMUM` when the unselected edge is lighter.

An equal unselected edge permits an alternative minimum result. The scan of
up to `E` edges with an `O(V)` path check gives `O(EV)` for this phase.

## Canonical connected fixture

```text
ID0 AB4  ID1 AC4  ID2 BC1  ID3 BD5
ID4 CD2  ID5 CE3  ID6 DE3  ID7 AE10
```

Prim:

```text
selected IDs              0,2,4,5
total                     10
push/pop                  8/8
stale/already             3/0
peak                      5
incident/eligible/improve 16/8/7
```

Kruskal:

```text
selected IDs              2,4,5,0
total                     10
examined/cycle/loop       8/4/0
```

Both validators return `MST_OK`.

Canonical exchange checks for selected IDs 0,2,4,5:

```text
AC4 versus path maximum4   equal alternative
BD5 versus path maximum2   no improvement
DE3 versus path maximum3   equal alternative
AE10 versus path maximum4  no improvement
```

Exactly four MSTs choose AB/AC and CE/DE while retaining BC and CD.

## Boundary forest fixture

Six vertices A through F:

```text
ID0 AB4
ID1 BC-2
ID2 AC3
ID3 DE1
ID4 DE1 parallel
ID5 EE-9 self-loop
F isolated
```

Expected:

```text
Prim selected IDs        2,1,3
Kruskal selected IDs     1,3,2
components               3
selected                 3
total                    2
Prim push/pop            7/7
Prim stale/already       1/0
Prim peak                2
Prim incident/eligible   12/5
Prim improvements        4
Kruskal examined         6
Kruskal cycle/loop       2/1
```

Validators return `MST_OK`.

## Equal-alternative fixture

All weights are 1:

```text
ID0 AD
ID1 CD
ID2 AB
ID3 BC
```

Stable Prim from A selects IDs `0,2,1`. Relationally sorted Kruskal selects
IDs `2,0,3`. Both totals are 3 and both validate.

This fixture is mandatory evidence that agreement concerns minimum total and
component partition, not exact selected IDs.

## Dijkstra contrast

On the canonical undirected graph, Dijkstra from A records AB, AC, CD, and
CE, whose selected-edge sum is 13. Its A-C path costs 4. The canonical MST
total is 10, but its A-B-C route costs 5.

Dijkstra distance is a complete source path cost and requires nonnegative
weights. Prim key is one crossing-edge weight, so negative MST edges are
valid.

## Safe cycle autopsy

Isolated file:

```text
autopsy/faulty_endpoint_cycle.c
```

Fixture:

```text
ID0 AB1
ID1 BC2
ID2 AC3
```

The faulty raw-endpoint inequality accepts all three:

```text
IDs0,1,2, count3, total6, cycle
```

The correct representative-root comparison skips ID2:

```text
IDs0,1, count2, total3, component1, MST_OK
```

The faulty result is `MST_INVALID_RESULT`. The program contains no undefined
behavior and is safe to run. It remains isolated from normal tests.

## Exactly three implementation clusters

1. Prim restart, pop, stale-first filtering, and selection.
2. Prim indexed scan, strict improvement, and push-before-commit.
3. Kruskal full sorted DSU scan.

Solution files contain no TODO markers. Starter files contain exactly these
three markers.

## Exactly three student-test categories

1. Prim lazy entries and disconnected restart.
2. Kruskal cycles, ties, loops, parallel edges, and negative weights.
3. Boundaries, preservation, totals, validation, and cross-validation.

Visible core tests freeze all canonical facts and public status categories.
Together, visible core tests and instructor extensions cover:

- frontier allocation failure and live-allocation restoration;
- frontier limit, sequence, and internal-state cases;
- invalid inactive slots and duplicate selected IDs;
- self-loop selected-result corruption;
- declared component-count corruption;
- structurally spanning but nonminimum result;
- `INT64_MIN`/`INT64_MAX` comparator fields;
- order-independent cancellation in differing selected-edge orders;
- both positive and negative final total overflow; and
- status-name fallbacks.

## Build matrix

PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make:

```text
solution-core
solution-extension
solution-student-tests
starter-compile
starter-core
starter-extension
starter-student-tests
autopsy
```

Use strict warnings and sanitizers where supported. Do not report native
runtime success when only static parsing was available.

## Security and claim boundary

Every scenario is synthetic and authorized. Bounds checks, output
preservation, relational sorting, checked totals, cycle prevention, and
validation support result integrity.

An MST or MSF does not establish:

- input origin or authorization;
- weight accuracy, freshness, or additivity;
- link capacity or latency behavior;
- independent failures;
- backup routes or availability;
- safe concurrent access; or
- overall system security.

Every selected tree edge is a bridge. Resilience requires an additional
objective, such as explicitly required alternate routes.

## Instructor verification checklist

- [ ] Stage A standard/linear content and scoring match.
- [ ] Stage A embargo scan is empty.
- [ ] Cognitive Pause has exactly three targets.
- [ ] Textbook is 1,050 through 1,200 words under both assigned counts.
- [ ] Twelve models have twelve exact linear equivalents.
- [ ] Canonical and boundary results/counters are exact.
- [ ] Tie square returns different IDs but equal totals.
- [ ] Negative, loop, parallel, disconnected, empty, and singleton inputs
      follow the fixed contract.
- [ ] Total checking is mathematical and order-independent.
- [ ] Full validator is explicit `O(V + E + EV)`, not hidden in algorithm
      metrics.
- [ ] Starter code has exactly three implementation TODOs.
- [ ] Student template has exactly three test TODOs.
- [ ] Autopsy is safe, isolated, and root-comparison focused.
- [ ] All failures preserve complete caller output.
- [ ] Lesson plan totals two 90-minute meetings.
- [ ] No student material claims minimum cost implies resilience.
