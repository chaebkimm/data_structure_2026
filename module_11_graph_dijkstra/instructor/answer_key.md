# Instructor Answer Key — Module 11 Indexed-Heap Dijkstra

Use [the supplied lab](../student/lab.c) as the source of truth. Require the
reasoning and reproducible state, not memorized phrasing. Preserve each first
prediction and label the correction. The required work is one Practical 2
submission; students trace supplied functions and write a test driver.

## Canonical fixture

IDs are A=0 through F=5. Initialize the imported node array, set
`nodes_size=6`, and load these directed adjacency lists in the written order.
Set the matching entries of `edge_length`; do not call Module 03's unrelated
`edges_init()` fixture.

```text
A -> B 9, C 2, E 14
B -> D 1, E 8
C -> B 3, D 2
D -> E 2
E -> none
F -> none
```

All listed weights are positive. Every candidate sum must fit in `int`.
Unused matrix cells do not create edges: only the adjacency lists are scanned.

## Stage A — Few connections versus least cost

The fewest-edge route from A to E is A,E. It has one edge and cost 14.
The route A,C,D,E has three edges and cost `2+2+2=6`.
BFS minimizes the number of edges, so its route need not minimize weight.

After A is processed, the waiting totals are B9, C2, and E14. C is next
because 2 is the smallest waiting total. Through C, B improves from 9 to
`2+3=5`, and D is first discovered at `2+2=4`. D is next.

An acceptable informal model keeps one current total per place, repeatedly
chooses the smallest unfinished total, and tests the outgoing connections.
The reasoning assumes that continuing along a connection cannot reduce the
already accumulated cost. The current lab requires positive weights.

F has no directed path from A in this stored graph. That conclusion does not
prove anything about unlisted routes, changing costs, or real availability.

## Stage B — Three-target Cognitive Pause

### Target 1: separate objectives

BFS chooses A,E: one edge, cost 14. A,C,D,E has three edges and cost 6.
Fewer edges and smaller total weight are different objectives.

### Target 2: update one queued node

After processing C:

```text
node_dist A..F: 0,5,2,4,14,-1
live heap IDs: D,E,B
heap keys:     4,14,5
live maps:    node_heap_pos[D]=0
              node_heap_pos[E]=1
              node_heap_pos[B]=2
```

B is already queued, so `update_value(B,5)` changes its shared distance and
repairs its position. No second B is inserted. The later insertion of D
moves D above B. The next root is D4; the heap array is not a sorted list.

### Target 3: improve, reject, and limit the claim

Removing D leaves `[B,E]`. D proposes `4+2=6` for E, improving 14 in place.
B is then removed at 5. Its proposals are D6 and E13; neither is smaller
than D4 or E6. No insertion or update follows either proposal.

Final distances are `[0,5,2,4,6,-1]`. F's `-1` means unreachable from A in
the loaded graph. The lab has no parser or arithmetic guard: the caller
must supply valid IDs, positive weights, and representable candidate sums.

## Stage C — Investigation answers

### A. Objective contrast

The BFS comparison counts edges. The Dijkstra comparison sums the same
listed weights. A manually checked route A,C,D,E certifies that cost 6 is
achievable. The current `min_dist` function returns no route; it writes
`node_dist` and `found`. It stores no predecessor array.

### B. Complete distance and live-array trace

Each row is after all outgoing edges of the removed node have been inspected.
`heap` contains node IDs; keys are read through `node_dist`.

| Event | Distances A,B,C,D,E,F | Live `heap` | Live keys |
|---|---|---|---|
| `init_dist(A)` | `0,-1,-1,-1,-1,-1` | `[A]` | `[0]` |
| remove A; inspect A | `0,9,2,-1,14,-1` | `[C,B,E]` | `[2,9,14]` |
| remove C; inspect C | `0,5,2,4,14,-1` | `[D,E,B]` | `[4,14,5]` |
| remove D; inspect D | `0,5,2,4,6,-1` | `[B,E]` | `[5,6]` |
| remove B; inspect B | `0,5,2,4,6,-1` | `[E]` | `[6]` |
| remove E; inspect E | `0,5,2,4,6,-1` | `[]` | `[]` |

Finalization order is A,C,D,B,E. That order is a trace observation, not a
stored output array. Final `found[A..F]` is `[1,1,1,1,1,0]`. Distances for
unused IDs G through J remain `-1`, and their `found` entries remain 0.

### C. Node IDs, positions, and inverse maps

After C, position 0 contains node D, whose numeric ID is 3. Thus
`heap[0]==3`, `node_dist[heap[0]]==4`, and `node_heap_pos[3]==0`.
`comp(0,2)` compares D4 with B5; it does not compare the distances of A and C.

For every active position `i`, require:

```text
0 <= i < size
node_heap_pos[heap[i]] == i
```

The root removal exchanges positions `0` and `--size`. The saved return
value is a node ID. Swapping at that node ID instead of position 0 is wrong.

Only live entries have a valid inverse-position guarantee. Removal leaves
the removed node's map at its former last position. After removing C, for
example, `node_heap_pos[C]` can be 2 while position 2 now holds B. A nonnegative
map value alone does not prove membership. Do not assert that every removed
entry is reset to `-1`; the supplied source does not do that.

### D. Repair direction and strict comparisons

`heapify_up` caches the parent before a swap. `heapify_down` caches the chosen
child before a swap, then follows that same child position. Recomputing the
child after the swap can select another branch.

`update_value` receives a node ID, finds its current position, writes the
new distance, then repairs upward or downward. An arbitrary active-node key
increase may need downward repair; the Dijkstra loop only requests decreases.

Equal candidates do not call `update_value`: the condition is strictly
`node_dist[adj] > new_dist`. Equal heap keys may still swap because `comp`
uses `<`. Such movement preserves minimum-heap order. There is no promised
arrival order or ID order for equal keys. A checker must use non-strict
parent-key ordering, not require `comp(parent,child)` to be true for ties.

### E. Caller assumptions and finalized state

`init_dist` calls `init_heap`, resets all ten distances and flags, then adds
the source with key 0. Repeated calls start fresh algorithm state but retain
the loaded graph and weight matrix.

`found[node]=1` records removal/finalization. The loop never reads `found`.
Under the positive-weight, correct-heap, representable-arithmetic assumptions,
a removed minimum cannot later improve. Therefore the algorithm never calls
`update_value` using a removed node's stale map. This is a proof obligation,
not a runtime check. Negative weights invalidate the argument.

The source contains no checks for invalid IDs, full insertion, empty removal,
negative weights, or overflow. Prevent those calls in the test setup. Do not
award rejection or output-preservation guarantees that are absent from the
source. A singleton removal is valid: the child helpers return `-1` after
`size` becomes 0, so the subsequent downward repair does nothing.

### F. Counts and comparison

| Canonical operation | Count |
|---|---:|
| `add_node`, including source | 5 |
| `remove_root` | 5 |
| `update_value` during relaxation | 2 |
| successful edge relaxations | 6 |
| inspected adjacency entries | 8 |
| peak live heap size | 3 |
| duplicate entries / stale pops | 0 / 0 |

The five adds are A,B,C,E,D. The six successful edge relaxations are four
first discoveries plus the two updates B9→5 and E14→6; source insertion is
separate. The lab does not
store counters; record these from the trace or an independent driver. Do not
claim a supplied comparison-count API or reuse the optional library's counts.

A linear minimum-selection reference finds the same distances using scans.
BFS chooses the fewest-hop route, whose cost to E is 14 here. The Priority
Queue ADT describes choosing a minimum; a scan and a heap are alternative
implementations of that choice. The heap's map supports editing the one
queued copy of a node.

## Stage E — Driver and evidence calibration

From the repository root:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests
```

The actual source is included by the drivers; students do not implement new
Dijkstra TODOs. Original assertions belong in `code/tests/test_lab_student.c`.
Require a focused regression plus saved output, the canonical state/map
trace, a same-graph comparison, assumptions, and a labeled correction in one
Practical 2 artifact. Additional independent tests may cover:

- heap ordering and active maps after upward and downward repairs;
- a parent with only a left child, tied keys, and guarded singleton removal;
- a nonzero source, an isolated source, disconnected nodes, and repeated runs;
- agreement with an independent linear shortest-distance reference.

For ties, assert minimum keys and valid active maps; do not invent stable
removal order. For the removed position map, explain its limited contract
rather than demanding behavior the source does not provide.

## Complexity answers

The literal arrays fix ten nodes and a 10×10 weight matrix. Under generalized
bounds, initialization is `O(V)`, each node enters and leaves the heap at most
once, and each successful later improvement repairs one heap path. The work
is `O(V + (V+E) log V)` with `O(V)` heap/distance/map/flag storage. The weight
matrix separately reserves `O(V²)` storage. A linear minimum-selection
Dijkstra reference takes `O(V²+E)` work; BFS takes `O(V+E)` but optimizes hops.

## Optional library boundary

The existing `code/include`, `starter`, `solution`, and `support` files retain
a separate dynamic lazy-duplicate implementation. Its `size_t`, `SIZE_MAX`,
parser, predecessors, path reconstruction, statuses, stable sequence rule,
stale snapshots, and `arc_count+1` frontier limit are optional API topics.
They are not fields or guarantees of this required `student/lab.c` lesson.
