# Module 11 — Dijkstra with an Indexed Minimum Heap

The required Week 11 lesson follows [`student/lab.c`](student/lab.c).
The complete source reuses Module 3's adjacency lists and stores pending
node IDs in a ten-position minimum heap. When a route improves, the program
finds the existing entry through `node_heap_pos` and repairs its position.
Students predict states, trace the supplied code, and write assertion tests.
There are no required implementation TODOs.

**Practical 2 is the sole Week 11 submission.** The investigation, tests,
and same-graph BFS/linear-selection/heap comparison form one artifact within
180 minutes. Follow the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
The optional lazy-duplicate library does not add another assignment.

## Teaching materials

| Material | Purpose |
| --- | --- |
| [Textbook](student/textbook.md) · [Vocabulary](student/vocabulary.md) | Explain costs, relaxation, and indexed heap state |
| [Initial inquiry](student/inquiry_prompt.md) · [Linear version](student/inquiry_prompt_linear.md) | Preserve a route-cost model before naming the method |
| [Representation reveal](student/representation_reveal.md) · [Cognitive Pause](student/cognitive_pause.md) | Connect the model to names and retrieve three ideas |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Trace distances, heap IDs, and live inverse positions |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | Build one Practical 2 submission |
| [Autopsy](student/dijkstra_autopsy.md) · [Models](diagrams/dijkstra_models.md) | Explain failures and state transitions |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_11.md) | Deliver the unit in 180 minutes |
| [Code guide](code/README.md) · [Release manifest](release/release_manifest.md) | Build and distribute the actual lab |

## Input and state contract

The included `module_03_graph/student/lab.c` supplies `nodes[10]`, with
`adj_list` holding neighboring node IDs and `adj_size` counting them.
`edge_length[u][v]` supplies the cost for each stored direction. A matrix
entry alone does not create a connection. For an undirected edge, add both
adjacency entries and both matching weights. The canonical fixture below is
directed and is loaded manually rather than through Module 3's `edges_init()`.

Callers provide valid node IDs, adjacency lengths within ten slots,
strictly positive edge costs, and path-cost additions that fit in `int`.
The source does not validate input or guard signed addition. Its fixed
arrays are not a dynamically allocated graph or a parser API.

| State | Meaning |
| --- | --- |
| `node_dist[v] == -1` | No route to `v` has been discovered |
| `node_dist[v] >= 0` | Best source-to-`v` cost found so far |
| `heap[0..size-1]` | Live pending node IDs, ordered by their current distances |
| `node_heap_pos[v]` | Position of `v`, guaranteed only while `v` is in the live heap |
| `found[v]` | Set to 1 after `v` is removed and its minimum cost is finalized |

For every live position `i`, `node_heap_pos[heap[i]] == i`.
`swap(i,j)` receives positions and updates the maps of both node IDs.
`comp(i,j)` compares `node_dist[heap[i]]` and `node_dist[heap[j]]`.
`heap_parent` avoids a name collision with Module 3's `parent[]` array.

`init_heap()` resets size and all map entries. `init_dist(start_node)` calls
it, resets all ten distances and `found` entries, and inserts the source at
cost zero. Neither function clears the unused heap buffer or graph inputs.
A new `min_dist` call starts a fresh run over the currently loaded graph.

## Discover once, improve in place

`min_dist` removes the cheapest pending node and inspects its adjacency list.
For each neighbor it computes `new_dist`:

- `node_dist[adj] == -1`: discover it with `add_node(adj,new_dist)`;
- a strictly smaller cost: call `update_value(adj,new_dist)`;
- an equal or larger cost: keep the current distance.

Each reachable node is inserted and removed once. Improvements edit an
existing entry; they do not insert duplicate snapshots. `update_value`
locates the node through its inverse position, then selects upward or
downward repair. Dijkstra only decreases keys, although the helper can also
repair an increase from a valid live entry.

`remove_root()` swaps positions 0 and `--size`, repairs the remaining heap,
and returns the saved node ID. It leaves the removed node's map entry at
an inactive position. Do not use that entry to detect membership or call
`update_value` on a removed node. The current code writes `found` but does
not test it: with positive weights and minimum-first removal, a finalized
node cannot later receive a smaller distance. A negative edge invalidates
this argument and can expose the stale map entry.

The comparator uses strict `<`. Equal-distance values can swap during
repair; neither insertion-order stability nor ID-order stability is promised.
A singleton removal safely calls `heapify_down(0)` after size becomes zero,
because both child helpers then return `-1`. Callers still require `size>0`
before removal and `size<10` before insertion, and must not insert duplicate
live IDs.

## Shared positive-weight fixture

Use IDs `A=0` through `F=5`, with these adjacency entries in this order:

```text
A -> B 9, C 2, E 14
B -> D 1, E 8
C -> B 3, D 2
D -> E 2
E -> none
F -> none
```

From A, the final distances are `[0,5,2,4,6,-1]` and the removal order is
`A,C,D,B,E`. Both the result and exact heap states can be checked in the
[models](diagrams/dijkstra_models.md). The run uses five `add_node` calls,
five removals, two updates (`B:9->5`, `E:14->6`), eight adjacency inspections,
and a peak live heap size of three. These are trace observations, not
counters exported by `lab.c`.

The route `A,C,D,E` witnesses cost 6; the direct one-hop route costs 14.
The lab returns distances and finalization marks, with no predecessor array
or path-reconstruction function. F remains `node_dist[F]==-1` and
`found[F]==0`; unused IDs 6 through 9 also remain undiscovered.

## Build and submission

From the repository root:

```sh
make -C module_11_graph_dijkstra/code lab-compile core student-tests
```

The drivers include the actual `student/lab.c`. Add original tests to
`code/tests/test_lab_student.c`; do not alter the supplied lab to hide a
failure. Compile the driver alone with include paths for the student folder
and repository root, which resolves the Module 3 dependency. See the
[code guide](code/README.md) for compiler and PowerShell commands.

Run `make -C module_11_graph_dijkstra/code comparison` for the supplied
`code/tests/compare_lab.c` BFS/linear-selection/indexed-heap comparison.

Submit the driver, output, canonical state trace, one independent distance
check, an equal-cost or boundary test, and the BFS/linear-selection/heap
comparison in the [evidence record](student/evidence_template.md).

## Cost and optional reference

For generalized `V` nodes and `E` stored adjacency entries, initialization
and scanning cost `O(V+E)`. At most `V` insertions, `V` removals, and `E`
improvements use `O(log V)` repair each, giving
`O(V + (V+E) log V)` time for `V>=2`. Pending heap and node arrays use
`O(V)` auxiliary space. The separate weight matrix uses `O(V^2)` input
storage; a generalized adjacency list uses `O(V+E)`. Actual arrays cap the
lab at ten nodes, so distinguish scalable analysis from fixed bounds.

`code/include`, `code/starter`, `code/solution`, `code/support`, the older
library tests, and `code/autopsy` retain a separate optional C API. That
library uses nonnegative `size_t` costs, a reserved infinity sentinel,
dynamic stable lazy snapshots, checked arithmetic, and predecessor paths.
Its sixteen-node capacity, stale-pop counts, parser TODOs, and failure
contracts do not describe the required `student/lab.c`. Named reference
build targets remain available in [code/README.md](code/README.md).
