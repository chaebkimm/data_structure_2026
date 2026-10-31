# Module 11 Technical Notes — Current Indexed-Heap Lab

## Authoritative source and compilation unit

The required implementation is [student/lab.c](../student/lab.c). Keep it
unchanged when updating teaching material or adding tests. It includes
`module_03_graph/student/lab.c`, which supplies `struct GraphNode`, `nodes`,
`nodes_size`, and earlier graph routines. The imported adjacency rows store
neighbor IDs, not weighted-edge records.

Compile a test driver that includes the Module 11 lab, with the repository
root on the compiler include path. Do not also compile either included lab
as another translation unit: their globals/functions would be defined twice.
The imported graph already declares `parent[10]`; the heap helper is named
`heap_parent` to avoid a C name collision. It is not a graph predecessor.

## Required representation

| Source name | Meaning and valid use |
|---|---|
| `nodes[10]` | Imported node records; each `adj_list` contains outgoing IDs. |
| `nodes_size` | Driver's active graph count; `min_dist` does not consult it. |
| `edge_length[10][10]` | Separate positive `int` cost for each listed adjacency. |
| `node_dist[10]` | `-1` if undiscovered; otherwise best known source cost. |
| `found[10]` | 1 after a node is removed; the loop writes but never reads it. |
| `heap[10]` | One node ID per pending node, in positions `0..size-1`. |
| `size` | Number of live heap entries, between 0 and 10 for valid use. |
| `node_heap_pos[10]` | Inverse map for nodes currently in the live heap only. |

`alphabet_nodes_init()` clears adjacency counts and assigns labels A–J.
It does not set edge weights. `init_dist(start_node)` resets all ten heap-map,
distance, and found entries, then adds the source at distance 0. It does not
clear or rebuild the loaded graph. Module 03's `edges_init()` installs a
separate hard-coded undirected fixture; it must not be mixed into the
canonical directed setup.

For every listed arc u→v, both an adjacency entry v in u's row and the desired
`edge_length[u][v]` must exist. A positive matrix cell alone does not create
an arc. For an undirected fixture, the driver installs both adjacency entries
and both matching weights. No source validator enforces these relationships.

## Indexed heap invariants

For every active position i:

```text
0 <= heap[i] < 10
node_heap_pos[heap[i]] == i
```

Each active node appears once. For each active nonroot position i:

```text
node_dist[heap[heap_parent(i)]] <= node_dist[heap[i]]
```

The source comparator uses strict `<`, so `comp(parent,child)` returns false
on an equal-key parent-child pair even though that pair is a valid minimum
heap. Test helpers should compare keys non-strictly or ask whether the child
is strictly smaller. Heap order does not sort siblings or the whole array.

`comp(i,j)` takes positions, reads IDs through `heap`, and then reads keys
through `node_dist`. `swap(i,j)` also takes positions and updates the two
moved IDs' inverse-map entries. `update_value(node,value)` takes an ID and
uses the map to find its current position. Confusing those domains was the
central bug exposed during development.

`heapify_up` caches its parent before swapping. `heapify_down` caches the
selected child before swapping and continues at that cached position. Once
a swap changes keys at positions, selecting a child again can choose a
different branch. The current implementation follows the displaced node.

A key change at the root repairs downward. At other positions, a key whose
parent is strictly smaller repairs downward; otherwise it repairs upward.
This supports increasing and decreasing active keys, although `min_dist`
only decreases an already discovered distance. Equal keys may swap during
either repair. No sequence field or stable arrival/ID tie guarantee exists.

## Removal and the map boundary

`remove_root()` requires `size>0`. It saves `heap[0]`, exchanges positions 0
and `--size`, repairs downward, and returns the saved ID. The exchanged last
slot is no longer active. `swap` updates both IDs' maps, including the
removed ID's map to the now-inactive position.

Consequently, only maps of live nodes are authoritative. The source does not
set the removed ID's map to `-1`. That stale value can later coincide with a
position occupied by another node. Do not use `node_heap_pos[node]>=0` as a
membership test, update a removed node, or assert that every absent node has
map `-1`. Initialization gives all maps `-1`; removal does not preserve that
absent-node convention.

A valid singleton removal leaves `size=0` and still calls `heapify_down(0)`.
Both child helpers return `-1`, so no comparison or array access occurs in
the loop. Another removal from that empty state would be invalid.

## Dijkstra loop and proof obligations

The required loop has these steps:

1. Reset algorithm state and insert the source with key 0.
2. Remove the currently smallest queued node and set its `found` flag.
3. Inspect that node's outgoing adjacency entries in stored order.
4. Compute `new_dist = node_dist[node] + edge_length[node][adj]`.
5. If the neighbor's distance is `-1`, insert it with that candidate.
6. Otherwise, if the candidate is strictly smaller, change the queued key
   through `update_value`.
7. Ignore equal or larger candidates and continue until the heap is empty.

A node is inserted only on its first discovery. Later improvements edit its
single existing entry; there are no copied distance snapshots, duplicate
entries, or stale-pop checks. A queued key changes in the shared distance
array, so the immediate heap repair is essential.

A removed minimum has its final shortest distance. With positive weights,
a later continuation cannot improve that node. The loop therefore never
enters `update_value` for an already removed node. This proof is what makes
its active-only map safe: the `found` array supplies no enforcement because
it is never read. Dijkstra's general nonnegative-weight theorem is broader
than this source's documented positive-weight input contract; the required
fixtures follow the source contract.

There are at most ten live nodes and at most one insertion/removal per
reachable node. Every reachable source row is inspected once. A positive
cycle proposes larger distances and does not cause reinsertion. An isolated
source is added and removed once, then the run ends with only its distance 0.

## Numeric and input assumptions

All IDs passed to functions and stored in adjacency rows must be in 0–9
(and within the driver's intended active graph). All row counts must fit the
10-entry arrays. Callers prevent inserting a duplicate node, adding when
`size==10`, removing when empty, and updating a node outside the live heap.

Listed edge weights are positive `int` values. All candidate additions,
including candidates that will later be rejected as too large, must fit in
`int`. The source computes before comparing and contains no overflow check.
Signed overflow is not an alternative unreachable result. No parser, status,
allocation failure, protected-output, or range-rejection contract exists.
Use bounded valid inputs in executable tests. State assumptions explicitly
instead of running negative/overflow cases to demand nonexistent rejection.

## Canonical exact state

Use the arc order A→B9,C2,E14; B→D1,E8; C→B3,D2; D→E2. E and F have no
outgoing arcs. The active-prefix arrays after each row is processed are:

```text
initialize: heap[A],       dist[0,-1,-1,-1,-1,-1]
after A:    heap[C,B,E],   dist[0,9,2,-1,14,-1]
after C:    heap[D,E,B],   dist[0,5,2,4,14,-1]
after D:    heap[B,E],     dist[0,5,2,4,6,-1]
after B:    heap[E],       dist[0,5,2,4,6,-1]
after E:    heap[],        dist[0,5,2,4,6,-1]
```

Observed finalization order is A,C,D,B,E. Canonical counts are five adds,
five removals, two updates, eight adjacency inspections, and peak size three.
Six edge relaxations succeed: four first discoveries plus two updates;
the source insertion is separate.
The code stores no operation counters or finalization-order list. It stores
no predecessor or returned path; A,C,D,E at cost 6 is a manual path witness.
F's final distance is `-1`, and `found[F]` remains 0.

## Meaningful checks and generalized costs

Current-lab checks are `lab-compile`, `core`, and `student-tests` in
[code/README.md](../code/README.md). Test active order and maps after every
heap operation. Exercise key changes in both directions, equal keys without
stable-order assertions, one-child and singleton cases, nonzero and isolated
sources, disconnected graphs, and repeated calls. The core suite compares
complete distance arrays with an independent matrix repeated-relaxation
reference on bounded positive fixtures. The separate supplied comparison
driver uses linear minimum selection. Never change the lab to satisfy a
test that expects a stronger contract.

For generalized V and E, initialization is `O(V)`, node insertion/removal
costs `O(V log V)` in total, and successful later improvements cost at most
`O(E log V)`. Thus work is `O(V + (V+E) log V)`. Heap, map, distance, and flags
use `O(V)` state. The separate matrix reserves `O(V²)` storage regardless of
how few arcs are traversed. Literal source arrays are fixed at ten nodes.

## Separate optional reference API

The retained C library under `code/include`, `starter`, `solution`, and
`support` implements a different strategy. Its dynamic frontier stores
stable `(distance, sequence)` snapshots, uses lazy duplicates and stale-pop
skipping, reserves `SIZE_MAX` as infinity, parses text, guards arithmetic,
and records predecessors and paths. Its frontier can require `O(E)` space.
Those contracts apply only to its named reference targets. They must not be
claimed for `student/lab.c` or assessed as additional Practical 2 TODOs.

The supplied `code/tests/compare_lab.c` provides the independent linear
minimum-selection Dijkstra and same-graph BFS/heap comparison. The separate
core-test oracle in `test_lab.c` uses repeated relaxation over a matrix;
these are two different references. Run the comparison with
`make -C module_11_graph_dijkstra/code comparison` from the repository root.
