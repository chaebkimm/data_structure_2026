# Module 15 C Package

This package computes a **minimum spanning forest**: the lowest-total-cost
set of input edges that connects every vertex that can be connected, without
creating a cycle. A disconnected graph produces one tree per connected
component.

## Input representation

The graph is undirected, so an edge can be followed both ways. It has at
most 16 vertices and 120 logical edges. Every logical edge owns two incident
records, one for each endpoint. A self-loop owns two identical records.
Parallel edges remain separate through distinct dense edge IDs.

Weights use signed `int64_t`. Negative weights, `INT64_MIN`, and
`INT64_MAX` are valid. `mst_parse_weight` accepts one signed decimal value
with optional surrounding ASCII whitespace. Malformed and out-of-range text
preserves its output.

`mst_graph_add_edge` accepts self-loops and parallel edges, assigns the next
dense ID, and preserves the graph on failure. The complete input validator
checks count bounds, endpoints, dense IDs, reciprocal records, equal mirror
weights, and zero inactive storage.

## Prim

Prim grows one tree from a reached region. A vertex's **key** is the weight
of its cheapest known edge from that region. `has_best[]` records whether a
key exists, so no legal number must be reserved as infinity.

The supplied indexed adjacency view is built in `O(V + E)` time. Each
vertex's incident edge IDs are ascending. Prim therefore does not rescan the
flat 240-record input for every selected vertex.

The supplied binary minimum Heap stores signed keys. Equal keys leave in
insertion order. A strict improvement pushes a new snapshot before changing
the best-key state. The old snapshot becomes **stale**, meaning it no longer
matches the current key, parent, and edge ID. Pop processing rejects a stale
tuple before checking `in_tree`.

Equal keys do not replace the earlier proposal. After one component's Heap
drains, Prim uses a monotone cursor to find the smallest unvisited vertex, so
earlier IDs are not rescanned for every component. Roots, one per component,
and strict improvements cause at most `E + c <= E + V = 136` pushes.

## Kruskal

Kruskal examines a local edge-list copy sorted by:

1. signed weight;
2. normalized endpoint `u`;
3. endpoint `v`; and
4. logical edge ID.

The supplied `qsort` comparator uses relational comparisons and never
subtracts fields. This avoids signed overflow and truncation.

For each non-loop edge, Kruskal finds both current DSU representative roots.
Equal roots mean the edge would create a cycle. For different roots, it
checks result capacity, stores the edge, then calls `union` and verifies that
the merge succeeded. The input graph and caller output never hold partially
completed work.

## Forest result and total

`MstForest` stores input counts, up to 15 selected input edges, the component
count, and a signed 64-bit total. A graph with `V` vertices and `c`
components must select `V - c` edges. The empty graph has zero components;
a singleton has one component and no selected edge.

The supplied total helper is independent of selection order. It converts
positive and negative weights to unsigned magnitudes, cancels opposite
signs, then checks the remaining same-sign magnitude. It handles
`INT64_MIN` without negating it. A final mathematical total outside
`int64_t` returns `MST_TOTAL_OUT_OF_RANGE`; every algorithm failure preserves
the complete caller output.

The explicit `mst_forest_validate` diagnostic checks:

- selected records exactly match distinct input edge IDs;
- no selected self-loop or cycle;
- input and result component partitions agree;
- the edge count is `V - c`;
- inactive slots and the checked total are canonical; and
- no unselected edge is lighter than the heaviest selected edge on the
  corresponding forest path.

The last check is the cycle-property certificate for minimum cost. The
bounded validator costs `O(V + E + EV)` and is deliberately not called
inside either normal algorithm.

## Canonical evidence

```text
ID 0 A-B  4       ID 4 C-D  2
ID 1 A-C  4       ID 5 C-E  3
ID 2 B-C  1       ID 6 D-E  3
ID 3 B-D  5       ID 7 A-E 10
```

Prim starts at A and selects IDs `0,2,4,5`, total 10. Its counters are:

```text
pushes 8, pops 8, stale 3, already-in-tree 0, peak 5
incident scans 16, eligible crossing tests 8, improvements 7
```

Kruskal selects IDs `2,4,5,0`, total 10. It examines all eight edges and
skips four cycle-producing edges. Equal-cost forests may contain different
edge IDs; algorithms must agree on the minimum total, not necessarily the
exact selected set.

## Student-controlled work

The starter has exactly three numbered task clusters:

1. Prim component restart, pop filtering, and selection;
2. Prim indexed relaxation with push-before-commit; and
3. Kruskal's root comparison, store, and union loop.

The student test template has exactly three categories: Prim lazy/restart
behavior, Kruskal filtering/ties, and boundary/preservation/validation.
Graph parsing and validation, indexed adjacency, the stable Heap, DSU,
sorting, checked total, full forest validation, core tests, extension tests,
and the safe cycle autopsy are supplied.

## Cost

Let `V` be vertices and `E` logical undirected edges.

- indexed adjacency construction: `O(V + E)`;
- Prim: `O(V + E log(E + 1))`;
- Kruskal: `O(E log E)` sorting plus near-linear DSU work;
- algorithm workspace: `O(V + E)`;
- explicit minimum-forest diagnostic: `O(V + E + EV)`.

## Build commands

The default uses the completed solution:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The starter compiles but its tests fail until all three clusters are done:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The autopsy is fully bounded and safe to run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make targets include:

```text
make
make solution-extension
make starter-compile
make starter-student-tests
make autopsy
```
