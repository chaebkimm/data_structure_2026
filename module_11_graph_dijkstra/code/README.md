# Module 11 C Package — Indexed-Heap Dijkstra

The required lesson and default builds use [`../student/lab.c`](../student/lab.c).
The source is supplied complete. Students trace the actual arrays, explain
why cheaper routes repair the existing heap entry, and write a separate
assertion driver. There are no required implementation TODOs in this source.

## Current source contract

The first include imports Module 03's `GraphNode`, `nodes[10]`, and graph
helpers. Each node stores neighbor IDs in `adj_list`; `edge_length[u][v]`
stores the positive `int` weight of that stored direction. `alphabet_nodes_init()`
resets labels and adjacency counts, but does not load weights. `edges_init()`
loads Module 03's separate unweighted, undirected fixture; do not call it for
the directed fixture below. Load adjacency and matching weights explicitly.
For an undirected connection, load both directions and both weights.

The caller supplies node IDs in 0–9, valid adjacency counts and neighbors,
strictly positive weights, and candidate sums that fit in `int`. The lab has
no input validator, parser, allocation, checked-addition guard, or error
status API. Do not execute invalid calls to test for rejection. The graph
is unchanged by a run; the global distance, heap, position, and found arrays
are shared work state, so runs are sequential.

| State | Meaning |
| --- | --- |
| `node_dist[id]` | Best discovered cost; `-1` means undiscovered or unreachable after a complete run |
| `heap[i]` | Node ID at live heap position `i`, where `0 <= i < size` |
| `node_heap_pos[id]` | Inverse position for an ID currently in the live heap |
| `found[id]` | Records that the ID has been removed and finalized |
| `edge_length[u][v]` | Cost used only when `v` is in `nodes[u].adj_list` |

`comp(i,j)` compares the distances of the IDs at two heap positions.
`heap_parent`, `left`, and `right` return positions; `-1` means no relative.
`heap_parent` avoids the `parent[10]` name already used by Module 03.
`swap(i,j)` updates both the heap and the two IDs' inverse positions.

Only live IDs satisfy `heap[node_heap_pos[id]] == id` with a position less
than `size`. `init_heap()` sets every position to `-1`. `remove_root()` swaps
the root into the inactive suffix and does not clear its map entry; therefore
`node_heap_pos[id] != -1` is not a membership test after removals.

Call `add_node` only for a new live ID with `size < 10`, `remove_root` only
when `size > 0`, and `update_value` only for a live ID. Updates can repair
upward or downward, although Dijkstra only decreases an existing cost.
The strict `<` comparator can swap equal priorities; arrival-order stability
and an ID-based tie order are not promised. After a singleton removal, the
empty heap's child helpers return `-1`, so the downward repair stops safely.

## Dijkstra run

`init_dist(source)` calls `init_heap()`, clears all ten distances and found
flags, then inserts the source at cost zero. `min_dist(source)` repeatedly
removes the smallest known cost and inspects that node's adjacency list.
A first discovery calls `add_node`; a strictly smaller later candidate calls
`update_value`. Equal costs do nothing. There is one live entry per pending
node, not one snapshot per improvement. There are no lazy duplicate entries
or stale-pop checks in this lab.

`found` records finalization but is never consulted by the supplied loop.
Under the positive-weight and representable-sum assumptions, a finalized
node cannot later receive a smaller cost, so an update never targets its
inactive map entry. The source returns distance zero; unreachable nodes
remain `-1` and `found == 0`. A run stores distances, not predecessors or
paths, and repeated calls reset work state while retaining the loaded graph.

## Shared directed fixture

Use six nodes, `A=0` through `F=5`, after `alphabet_nodes_init()`. Set
`nodes_size=6` and load these neighbors in the listed order:

```text
A: B/9 C/2 E/14
B: D/1 E/8
C: B/3 D/2
D: E/2
E:
F:
```

From A, the live heap after each removed node's adjacency scan is:

| Removed | Live heap IDs | Distances A through F |
| --- | --- | --- |
| A | `[C,B,E]` | `[0,9,2,-1,14,-1]` |
| C | `[D,E,B]` | `[0,5,2,4,14,-1]` |
| D | `[B,E]` | `[0,5,2,4,6,-1]` |
| B | `[E]` | `[0,5,2,4,6,-1]` |
| E | `[]` | `[0,5,2,4,6,-1]` |

The run uses 5 insertions including the source, 5 removals, 2 value updates
(B: 9 to 5; E: 14 to 6), and 8 adjacency inspections. Peak heap size is 3.
The removal order is A, C, D, B, E; F remains unreachable. These are driver
trace counts, not counters stored by `lab.c`. No predecessor path is returned.

## Build and verify

From the repository root:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests
make -C module_11_graph_dijkstra/code comparison
```

`lab-compile` compiles the supplied source to an object. `core` compiles and
runs `tests/test_lab.c`; `student-tests` compiles and runs
`tests/test_lab_student.c`. The default `make` target runs both drivers.
Override `CC` or `CFLAGS` when your compiler setup requires it.
The source includes Module 03 using a repository-relative path, so the
Makefile supplies both the student directory and repository root as include
paths. Each driver includes `lab.c` once: do not additionally compile or link
`student/lab.c` or Module 03's source into that same executable.

The supplied core suite checks independent heap order and live-map
invariants, ID/position distinctions, both update directions, equal keys,
full capacity, guarded singleton removal, repeated calls, unreachable nodes,
nonzero sources, undirected storage, and 80 small positive-weight graphs
against a matrix-based repeated-relaxation reference. The student driver
starts with smoke tests; add one focused original regression and save its output.
Do not count the supplied smoke tests as original regression evidence.

The supplied `comparison` target runs `tests/compare_lab.c` on the same
canonical graph. It prints BFS hop counts and BFS-selected route costs,
then asserts that an independent linear minimum-selection Dijkstra and the
actual indexed-heap lab produce matching weighted distances. BFS returns
hops `[0,1,1,2,1,-1]`; its selected routes cost `[0,9,2,10,14,-1]`.
The driver measures 5 BFS queue pops and 8 adjacency inspections. The
linear reference measures 36 selection-slot inspections across 6 rounds
(including the final unsuccessful scan), 5 selected nodes, 8 adjacency
inspections, and 6 strict improvements. Heap call counts are explicitly
labeled as manual trace values because `lab.c` exports no counters.
This comparison is supplied evidence for Practical 2, not another
implementation assignment. Use `make comparison` inside the extracted
release's `code/` directory; PowerShell switches select the core or student
test drivers only.

From this `code` directory on Windows:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -CompileOnly
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

The script defaults to `-Target lab`. `-CompileOnly` builds the selected
driver without executing it. Clang, GCC, and Microsoft C are supported;
`-Sanitize` adds available runtime checks. The supplied source may produce
non-prototype and Module 03 label-conversion warnings; record them without
rewriting the teaching source to hide them. Run `make clean` to remove builds.
The extracted release has the same commands from its `code/` directory and
includes the required Module 03 source under the release root.

## Costs

For a generalized graph with `V` vertices and `E` stored adjacency entries,
there are at most `V` live heap entries, at most `V` insertions and removals,
and at most `E` decreases. Heap repair is `O(log V)`, giving
`O((V + E) log V)` algorithm time with `O(V)` heap/work arrays. The actual
lab fixes those arrays at ten slots. Graph storage also includes the
`edge_length` matrix: generalized total graph and work storage is
`O(V^2 + E)`, not just the heap's `O(V)` space. Building or clearing that
matrix is setup work, separate from `min_dist()`.

## Optional lazy-duplicate library

`include/`, `starter/`, `solution/`, `support/`, the older tests, and
`autopsy/faulty_overflow.c` retain a separate library for optional study.
That API uses a dynamic weighted graph, `size_t`/`SIZE_MAX`, a stable
snapshot frontier, lazy duplicates, validated statuses, guarded arithmetic,
and predecessor-path reconstruction. Those behaviors do not describe the
current `student/lab.c` and are not additional required Practical 2 work.

The named reference targets remain available:

```sh
make starter-core starter-extension starter-student-tests
make solution-core solution-extension solution-student-tests
make autopsy
```

Starter tests compile and fail until that optional scaffold is implemented.
The optional `*-student-tests` targets also require completion of their older
student-authored test template; they are separate from current-lab `student-tests`.
PowerShell equivalents use `-Target starter`, `-Target solution`, or
`-Target autopsy`; `-Extensions` and `-StudentTests` select library suites.
The current-lab target does not accept `-Extensions`.
