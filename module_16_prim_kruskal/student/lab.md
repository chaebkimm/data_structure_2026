# Stage E - C Lab: Prim and Kruskal Minimum Spanning Forests

## Purpose

Complete and test two algorithms that connect every available vertex at
minimum selected-edge total. Prim uses a **frontier**, or pending work,
stored in a tree-shaped Priority Queue called a **Heap**. Kruskal sorts
logical edges and uses **disjoint-set union (DSU)**, a structure that
maintains separate groups, to prevent cycles.

All graphs, site names, and weights are synthetic. Do not connect this
program to live logs, accounts, hosts, devices, feeds, or networks.

The lab has exactly three marked implementation clusters: two for Prim and
one for Kruskal. **Ownership** means responsibility for releasing reserved
storage. Graph ownership, adjacency indexing, edge-list sorting, Heap
storage, DSU storage, total arithmetic, and full result validation are
supplied.

## Public files and fixed limits

A **public header** is a C file declaring names other files may use. An
**application programming interface (API)** is that set of named operations.
Read:

```text
code/include/dsu.h
code/include/undirected_edge_list.h
code/include/prim_frontier.h
code/include/minimum_spanning_forest.h
```

A **capacity** is a fixed maximum count.

```text
vertices                 16
logical undirected edges 120
incident records         240
selected forest edges     15
Prim frontier records    136
```

`size_t` is C's nonnegative whole-number type for counts and positions.
`int64_t` is C's signed 64-bit whole-number type for edge weights and final
totals.

An `UndirectedIncidentGraph` stores two incident records per logical edge.
Ordinary records are reciprocal. A self-loop has two identical records.
Parallel edges keep different dense IDs; **dense IDs** are consecutive from
zero through `logical_edge_count-1`.

Supplied graph operations are:

```c
mst_graph_init
mst_graph_add_edge
mst_parse_weight
mst_graph_validate
```

To **parse** means convert input text into a stored value. Invalid endpoints
are rejected before indexing. Every failed graph operation preserves its
protected output.

## Results, statuses, and preservation

A **status** is a named outcome. `MstStatus` has these exact values:

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

The public algorithms are:

```c
MstStatus prim_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    PrimResult *out_result
);

MstStatus kruskal_minimum_spanning_forest(
    const UndirectedIncidentGraph *graph,
    KruskalResult *out_result
);

MstStatus mst_forest_validate(
    const UndirectedIncidentGraph *graph,
    const MstForest *forest
);
```

A **memory address** identifies a storage location. A **pointer** stores an
address; `*` marks a pointer type here. `const` means the graph is read-only
through that pointer. `NULL` means no valid object address. The **caller** is
code requesting work; `out_result` is its output object.

Every failure preserves the complete caller output and input graph. An
**allocation** is storage reserved while a program runs. Temporary
allocations are released on every exit.

`MstForest` stores:

```text
vertex_count
input_edge_count
selected_edges[15]
selected_count
component_count
total_weight
```

Each selected `UndirectedEdge` stores `u`, `v`, signed `weight`, and
`edge_id`. Inactive slots are exact zero records.

`PrimResult` adds:

```text
push_count
pop_count
stale_pop_count
already_in_tree_pop_count
frontier_peak
incident_scan_count
eligible_crossing_count
key_improvement_count
```

`KruskalResult` adds:

```text
examined_edge_count
cycle_skip_count
self_loop_skip_count
```

A Prim **snapshot** is one saved vertex/key/parent/edge candidate. It is
**stale**, or out of date, when that tuple differs from the current best
tuple. A counter is a stored number of events; `frontier_peak` is the
largest number of pending snapshots held at once.

The supplied total logic computes the order-independent mathematical sum.
It cancels positive and negative magnitudes before bounded same-sign
accumulation and handles `INT64_MIN` without negating it. A fitting final
total succeeds even when one selected-edge array order first forms a running
subtotal outside the type's range. Only a final mathematical total outside
`int64_t` returns `MST_TOTAL_OUT_OF_RANGE`.

## Explicit validation

`mst_forest_validate` is a supplied, explicit `O(V + E + EV)`
diagnostic. Its minimum-cost phase is `O(EV)`. It checks:

1. the complete graph and result shape;
2. selected-edge input membership and unique IDs;
3. no selected self-loop or cycle;
4. the same component partition as the input;
5. exactly `V-c` selected edges;
6. exact inactive fields and order-independent total; and
7. minimum cost by testing every unselected non-loop edge against the
   greatest selected edge on its unique forest path.

It returns `MST_NOT_MINIMUM` when structure is valid but a lighter exchange
exists. Prim and Kruskal do not hide this full diagnostic inside their
ordinary runs. Tests call it explicitly, so the advertised algorithm costs
remain accurate.

## Files and build commands

Edit only:

```text
code/starter/prim.c
code/starter/kruskal.c
code/tests/test_student.c
```

To **build** means compile source into a runnable program. From `code/`, use:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make equivalents are:

```text
make starter-core
make starter-student-tests
make autopsy
```

Preserve warning-enabled commands and output. A **sanitizer** is a runtime
checker for selected memory and arithmetic defects; use `-Sanitize` where
the installed compiler supports it.

## TODO 1 - Prim restart, pop, filter, and select

Complete the marked cluster in `starter/prim.c`.

Required behavior:

1. validate arguments and graph before work;
2. build the supplied `O(V+E)` indexed adjacency view once;
3. initialize every local key, parent, selected-edge ID, membership flag,
   forest field, and counter;
4. keep one forward-only cursor (an index that never moves backward); when
   the frontier is empty, use it to find and push the smallest unvisited
   vertex as a new component root with key 0 and no parent edge;
5. pop one snapshot and count it;
6. compare the saved key, parent, and edge ID with the current best tuple
   first; count and skip a missing or mismatched tuple as stale;
7. then count and skip a current snapshot whose vertex is already in the
   tree;
8. for a current nonroot vertex, store its exact parent edge;
9. mark the current vertex in the tree; and
10. continue until every vertex belongs to a component.

A restart adds no selected edge and no weight. An empty graph succeeds with
zero components. A singleton succeeds with one component and zero selected
edges.

## TODO 2 - Prim scan, improve, and push before commit

Complete the second marked cluster in `starter/prim.c`.

For every indexed incident record of the newly selected vertex:

1. increment the incident-scan count;
2. ignore a self-loop or destination already in the tree;
3. count every remaining crossing test;
4. require `edge.weight < key[v]`; equality changes nothing;
5. prepare a snapshot with vertex, proposed key, parent, and logical edge
   ID;
6. push the snapshot before changing local key/parent/ID state;
7. on successful push, commit the improvement and count it; and
8. on allocation or limit failure, clean up and preserve caller output.

Do not scan the flat 240-record array once per selected vertex. That would
add `O(VE)` work. Do not commit an improvement before a push that can fail.

Canonical checkpoint:

```text
selected IDs:              0,2,4,5
total:                     10
pushes / pops:             8 / 8
stale / already selected:  3 / 0
frontier peak:             5
incident scans:            16
eligible crossing tests:  8
key improvements:          7
validator:                 MST_OK
```

## TODO 3 - Kruskal sorted DSU scan

Complete the marked cluster in `starter/kruskal.c`.

Required behavior:

1. validate graph and output arguments;
2. build and sort one logical edge list with supplied operations;
3. initialize one DSU set per vertex and local forest state;
4. examine every sorted edge, even after `V-c` edges have been selected;
5. count and skip a self-loop before a root comparison;
6. obtain both representative roots;
7. count and skip an edge whose roots match;
8. store the exact edge only when roots differ;
9. union the two groups after successful storage;
10. derive the final component count and order-independent total; and
11. store the complete result in caller output only on success.

Canonical checkpoint:

```text
selected IDs in decision order: 2,4,5,0
total:                          10
examined edges:                  8
cycle skips:                     4
self-loop skips:                 0
validator:                       MST_OK
```

Prim and Kruskal must agree on component partition and minimum total, not
necessarily selected-edge order or IDs.

## Exactly three student-authored test categories

An **assertion** is a test check that must be true. Write exactly three
numbered test functions in `test_student.c`.

### Test 1 - Prim lazy trace and restart

Assert the complete canonical result and every counter. Cover strict
equal-key preservation, stale-before-already-selected filtering, the
six-vertex boundary graph, ascending restart roots, negative weight,
parallel tie, self-loop, and isolated F.

### Test 2 - Kruskal filtering and ties

Assert the complete canonical sorted ledger and counters. Cover the
all-weight-1 square with a different valid edge set, negative weight,
parallel IDs, self-loop, comparator behavior at `INT64_MIN` and
`INT64_MAX`, and full scanning after enough edges are selected.

### Test 3 - Boundaries, preservation, and cross-validation

**Cross-validation** compares independent methods on the same input. Cover
empty and singleton graphs, invalid endpoint/state, limits, forced
allocation failure, fitting cancellation, truly out-of-range total,
structural corruption, a structurally valid nonminimum forest, complete
unchanged output on failure, and Prim/Kruskal agreement.

Three renamed copies of one fixture earn credit once.

## Safe cycle autopsy

Complete `student/mst_cycle_autopsy.md` before and after running the isolated
program. For sorted ID0 AB1, ID1 BC2, and ID2 AC3, raw endpoint inequality
wrongly selects all three edges. Representative-root comparison skips ID2.

```text
faulty:  IDs 0,1,2  count 3  total 6  invalid cycle
correct: IDs 0,1    count 2  total 3  MST_OK
```

The autopsy is safe to run and is never linked into normal tests.

## Actual cost and scope

Let `V` mean vertices and `E` mean logical edges.

```text
lazy indexed Prim time:  O(V + E log(E + 1))
Prim extra storage:      O(V + E)
Kruskal sorting:         O(E log E)
Kruskal DSU work:        near-linear
full explicit validator: O(V + E + EV)
```

Here **near-linear** means the DSU work grows almost in direct proportion to
the number of examined edges under its long-sequence analysis.

A minimum forest proves only the minimum selected-edge total under the
validated stored model. It does not prove that weights came from an
authorized source, remain current, represent capacity, provide backup
routes, or make the whole system secure.

## Submission

Submit:

- all three implementation clusters;
- exactly three student-test functions;
- warning-clean core and student-test output;
- exact canonical Prim and Kruskal evidence;
- disconnected, negative, loop, parallel, tie, and numeric evidence;
- explicit validator results;
- completed evidence record and safe cycle autopsy;
- representation-and-density recommendation; and
- corrected Cognitive Pause.
