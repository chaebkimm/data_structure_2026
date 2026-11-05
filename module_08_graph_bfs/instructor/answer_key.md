# Instructor Answer Key — Chapter 8: Processing data in stored order

Use the current [lesson plan](lesson_plan.md), [lab](../student/lab.md), and [workbook](../student/class_material.md). All maze pairs below mean `{y,x}`. The main lab stores whole points in a linear queue and records distances only.

The frozen [Korean textbook](../student/textbook_korean.md), **저장된 순서대로 데이터 처리하기**, and the read-only PPTs set the lesson's scope. The textbook has 14 concept topics, two efficiency topics, 15 glossary terms, four invariant questions, five coding-plan steps, three new C explanations, and seven code blocks. The numerical traces here are classroom evidence; keep them outside the textbook's dry concept prose.

## Queue and tree checkpoints

Three enqueues from reset leave front 0/rear 2. Three dequeues return the same points in arrival order and leave front 3/rear 2. After 25 writes and removals, front 25/rear 24 is empty but cannot accept another write without reset. Removing data does not reclaim linear write positions.

The first insertion belongs at index 0. Since enqueue increments `rear` first, `rear` must start at -1. Enqueue leaves `front` unchanged, so it starts at 0. A singleton has equal front/rear; an empty reachable state has `front == rear + 1`. In a nonempty queue the indices identify the first and last data. Each enqueue/dequeue copies one fixed-size point and changes one index without shifting other data, so each takes constant time. Reserved memory is proportional to array capacity; a linear run needs enough positions for all enqueues since reset.

For the paper circular convention, front is the index of the first queued data and rear is the index of the last queued data when nonempty. An empty queue has neither first nor last data. Empty is `front == (rear + 1) % 25`; full is `front == (rear + 2) % 25`. Reserving one slot allows 24 pending values. Fill labels 0–23, remove 0/1, append 24/25: front 2/rear 0. Remaining labels are 2–25 in order.

For the illustrative tree A→B/C, B→D/E, C→F, the queues after A/B/C/D/E/F are `[B,C]`, `[C,D,E]`, `[D,E,F]`, `[E,F]`, `[F]`, `[]`. Order A/B/C/D/E/F has depths 0/1/1/2/2/2. Six nodes are processed and twelve binary child positions checked. A valid tree has one parent per nonroot node and no cycles; a general graph needs discovery tracking. Level can be stored alongside a queued node or advanced after processing a saved level count.

For the graph stack comparison, an already waiting but unprocessed node may receive a newer stack entry. Process only the first entry popped for that node, mark it processed before expanding it, and skip later copies. A new entry sits above its old copy and can change which branch is handled next. This pending-node iterative policy differs from Chapter 6's recursive implementation. BFS records discovery before enqueue, so waiting and already processed copies are both rejected.

## Four invariant questions

- **Rule:** distances are equal or increase from the front to the back of the pending queue.
- **Benefit:** with unit-cost moves, a first-discovered neighbor's distance is final. A shorter path would already have exposed that neighbor while an earlier layer was processed.
- **Broken case:** using a stack or unequal move costs no longer guarantees increasing cost order. A later shorter route requires a distance update and propagation to affected neighbors; simply skipping every old discovery would be incorrect.
- **Preservation:** remove at the front, inspect each neighbor, and record an undiscovered neighbor's distance as current distance plus one before adding it at the back. Record the start's zero distance before its insertion as well.

`INF` is a marker for no known distance, even though it is written into the array. Discovered includes both waiting and processed nodes; processed means the node has been removed and its neighbors checked. The currently examined node is also discovered.

## Three new C explanations

- **Two-dimensional initialization:** each inner brace pair initializes one row. Selecting a row and then a column is review from Chapter 6; nested row initializers are the new part.
- **Structure values:** `struct point p = cur_point;` copies both integer members. Changing the local `p.x` does not alter `cur_point.x`. `enqueue` receives a point value; `dequeue` and `next_iter` return point values.
- **Short-circuit OR:** if `is_wall(p)` is true, `get_distance(p) != INF` is not evaluated. If either condition is true, the surrounding `if` takes `continue`, skipping the update and enqueue. This does not check bounds; the start and closed-border conditions establish valid indices before the expression is reached.

Treat `enum` (Chapter 7), prefix/postfix increments (Chapter 3), `switch`/`break` (Chapters 4–5), and `continue` (Chapter 6) as review when prompted by the code slides.

## Current maze checkpoints

The source uses `N = 5`, point fields y then x, direct point queue entries, `distance[N][N]`, and `INF = 25`. Every `bfs` resets queue positions and all 25 distances. A passage start is marked 0 before enqueue. The zero border keeps every queued passage interior. Start coordinates themselves must be in bounds.

From `{1,1}`, the exact trace is:

| Processed point | Distance | Queue after processing, front to back |
| --- | ---: | --- |
| Initial | — | `[{1,1}]` |
| `{1,1}` | 0 | `[{2,1}]` |
| `{2,1}` | 1 | `[{2,2},{3,1}]` |
| `{2,2}` | 2 | `[{3,1},{2,3},{3,2}]` |
| `{3,1}` | 2 | `[{2,3},{3,2}]` |
| `{2,3}` | 3 | `[{3,2},{3,3},{1,3}]` |
| `{3,2}` | 3 | `[{3,3},{1,3}]` |
| `{3,3}` | 4 | `[{1,3}]` |
| `{1,3}` | 4 | `[]` |

The final distances are:

```text
INF INF INF INF INF
INF   0 INF   4 INF
INF   1   2   3 INF
INF   2   3   4 INF
INF INF INF INF INF
```

The baseline reaches eight passages, performs eight writes/removals, and checks 32 neighbors. Peak pending is three. Final front/rear are 8/7. Total writes, not peak pending alone, bound this linear queue. The array reserves 25 point entries; discovery-before-enqueue ensures at most one write per cell between resets.

At `{3,1}→{3,2}`, the neighbor already has distance 3 while waiting. It is skipped. At `{3,2}→{3,3}`, the neighbor already has distance 4 and is also skipped. No additional predecessor is saved. FIFO ensures all distance-d cells are processed before distance-(d+1) cells; any shorter route would have caused an earlier discovery.

The iterator from `{2,2}` returns `{2,3}`, `{2,1}`, `{3,2}`, `{1,2}`, with states 1,2,3,4 afterward. Every call starts with a fresh copy of `cur_point`. Removing the first `break` would allow the following west case to undo the east move before stopping.

## Fresh runs and conceptual routes

A reverse start `{3,3}` gives distance 4 at `{1,1}`. An in-bounds wall start `{0,0}` leaves all distances `INF`, front 0, rear -1. Setting `maze[2][1] = 0` at runtime isolates valid start `{1,1}`: only that point has distance 0, the still-open goal stays `INF`, and endpoints finish at 1/0. Restore `maze[2][1] = 1` before the baseline rerun. `INF` alone does not distinguish a wall from an unreachable passage.

One four-move route is `{1,1}→{2,1}→{2,2}→{2,3}→{3,3}`. If one previous point were saved at first discovery, this would be the route selected by the current direction order. Follow from target to source, then reverse the sequence. Other equally short routes can exist. The actual lab has no previous-point records or path printer; the route explanation is conceptual.

A shortest route never needs a repeated vertex, so with at most 25 cells its finite distance is at most 24. Thus 25 can represent unseen. For R×C cells and P reached passages, initialization and reserved queue/distance storage are O(RC), and traversal is O(P). A path printer would add work proportional to the route it prints.

The current [lecture driver](../code/tests/test_lecture.c) checks the actual maze; run `make -C module_08_graph_bfs/code lecture`. Do not describe checked-library tests below as tests of this source.

## Optional checked-graph answer key

Keep this file instructor-only until revision closes. Accept equivalent
plain-language reasoning. Do not require memorized terms when a response
accurately explains the state change.

## Stage A — Initial inquiry

The familiar directed graph is:

```text
0:[1,2]  1:[3]  2:[3]  3:[4]  4:[1]  5:[]
```

### A. Read the relationships

- Immediate choices after 0: vertices 1 and 2.
- Vertex reached directly from both 1 and 2: vertex 3.
- Repeating directed route: `1 -> 3 -> 4 -> 1`.
- Separate vertex: 5.

### B. Invent the inspection rule

An acceptable initial rule says:

1. begin with 0 waiting;
2. handle the earliest-added waiting vertex;
3. when handling a vertex, add each lower-numbered unseen outgoing
   destination before a higher-numbered one;
4. remember a destination as soon as it is successfully added;
5. never add an already remembered destination; and
6. stop when no work waits.

The resulting order is:

```text
0,1,2,3,4
```

Vertex 5 is absent because no directed route leads to it from 0.

### C. Remember unfinished work

Lists are oldest to newest:

```text
initial:        [0]
after handling 0: [1,2]
after handling 1: [2,3]
after handling 2: [3]
after handling 3: [4]
after handling 4: []
```

At vertex 2, destination 3 must not be added again because it is already
remembered and waiting. At vertex 4, destination 1 is already handled.

### D. Record first arrival

The first-arrival table is:

| Vertex | Links from 0 | First previous vertex |
|---:|---:|---:|
| 0 | 0 | none |
| 1 | 1 | 0 |
| 2 | 1 | 0 |
| 3 | 2 | 1 |
| 4 | 3 | 3 |
| 5 | unreachable | none |

The selected route to Monitor, vertex 4, is:

```text
0 -> 1 -> 3 -> 4
```

The route through 2 has the same link count. The lower-numbered tie rule
makes vertex 1 discover 3 first.

### E. Cover all vertices

One-source work correctly leaves 5 unhandled. To cover every vertex, scan
identifiers from low to high after the first run and begin again at each
still-unremembered identifier, without clearing the shared record. In this
directed graph that produces a traversal forest; it does not establish a
weakly or strongly connected component.

### F. Macro-question

Model answer:

> Keep newly reached, not-yet-handled vertices in earliest-added order.
> Remember each one when it is first added. Store its link count and the
> vertex that first reached it. This handles every smaller link count before
> a larger one and prevents merging or cyclic routes from adding the same
> work repeatedly.

For F2, accept a genuine question the current model leaves open, such as
how unequal link costs, missing relationship data, or real-world permission
would change the conclusion. Formal future-module vocabulary is not
required.

## Stage B — Cognitive Pause

Pause graph:

```text
0:[1,3]
1:[2,4]
2:[0]
3:[2,5]
4:[5]
5:[]
6:[]
```

### Target 1 — Trace Queue and state

Queue is front to back:

```text
initial: [0]
after 0: [1,3]
after 1: [3,2,4]
after 3: [2,4,5]
after 2: [4,5]
after 4: [5]
after 5: []
```

```text
visit order: 0,1,3,2,4,5
discovered:  true,true,true,true,true,true,false
distance:    0,1,2,1,2,2,unreachable
predecessor: none,0,1,0,1,3,none
```

### Target 2 — Stop duplicate waiting work

When vertex 3 checks `3 -> 2`, vertex 2 is already discovered because
vertex 1 successfully enqueued it. The edge creates no enqueue and changes
no distance or predecessor. If discovery waited until dequeue, another 2
could enter behind vertices 2 and 4.

### Target 3 — Reconstruct and report

```text
backward chain: 5,3,0
forward path:   0,3,5
hop count:      2
vertex 6:       unreachable from source 0
```

## Stage C — Investigation

Canonical graph:

```text
0:[1,2]
1:[3,4]
2:[4,5]
3:[6]
4:[6]
5:[4]
6:[1]
7:[]
```

### A. Apply the discovery invariant

#### A1. Initial state

After the source enqueue succeeds:

```text
Queue:       [0]
discovered:  {0}
distance[0]: 0
predecessor[0]: 16, meaning none
visit order: empty
```

#### A2. After vertex 0

```text
Queue: [1,2]
new discoveries: 1,2
distance[1] = distance[2] = 1
predecessor[1] = predecessor[2] = 0
visit order: 0
```

#### A3. After vertex 1

```text
Queue: [2,3,4]
new discoveries: 3,4
distance[3] = distance[4] = 2
predecessor[3] = predecessor[4] = 1
visit order: 0,1
```

#### A4. Meanings

- Discovered: successfully enqueued before or already processed.
- Processed: removed from the Queue and recorded.
- Frontier: discovered vertices still waiting.
- First discovery is permanent; no later edge overwrites distance or
  predecessor.

### B. Complete the canonical trace

#### B1. Queue

```text
initial: [0]
after 0: [1,2]
after 1: [2,3,4]
after 2: [3,4,5]
after 3: [4,5,6]
after 4: [5,6]
after 5: [6]
after 6: []
```

#### B2. Final result

```text
vertex_count: 8
source:       0
visit_count:  7
visit_order:  0,1,2,3,4,5,6
discovered:   true,true,true,true,true,true,true,false
distance:     0,1,1,2,2,2,3,16
predecessor:  16,0,0,1,1,2,3,16
```

#### B3. Skipped edges

| Edge | State when checked | Action |
|---|---|---|
| `2 -> 4` | 4 is discovered and pending | skip |
| `4 -> 6` | 6 is discovered and pending | skip |
| `5 -> 4` | 4 is discovered and processed | skip |
| `6 -> 1` | 1 is discovered and processed | skip |

No distance or predecessor changes at any skipped edge.

### C. Explain minimum hops and paths

#### C1. Why first discovery is minimum

Every edge contributes one hop. FIFO Queue removal processes
nondecreasing distances. Therefore a neighbor first reached from a
distance-`d` vertex receives `d + 1`, and no route with fewer hops can be
found later. Enqueue-time discovery ensures later routes do not reschedule
or overwrite it.

#### C2. Path to vertex 6

```text
backward: 6,3,1,0
forward:  0,1,3,6
hops:     3
```

Certificate checks:

- `0 -> 1`, `1 -> 3`, and `3 -> 6` exist;
- endpoints are source 0 and destination 6; and
- three edges equal `distance[6]`.

#### C3. Equal-hop alternatives

`0,1,4,6` and `0,2,4,6` also use three hops. Ascending processing causes
3 to discover 6 before 4 does. The result promises one deterministic
minimum-hop path, not a unique path.

#### C4. Source and unreachable

- Path from 0 to 0: `[0]`, count 1, zero hops.
- Path from 0 to 7: `GRAPH_BFS_UNREACHABLE`; old output path unchanged.
- Predecessor 16 alone is ambiguous: source and unreachable vertices both
  use it. The discovered and distance fields distinguish them.

### D. Reason about disconnected graphs

#### D1. One-source result

The canonical call succeeds even though 7 is unreachable. An unreachable
active vertex is represented in the successful result; it does not make
the traversal itself fail.

#### D2. Undirected paper forest

For:

```text
{0,1}, {1,2}, {3,4}, {4,5}; vertex 6 isolated
```

the ascending outer scan gives:

```text
0,1,2 | 3,4,5 | 6
roots: 0,3,6
components: {0,1,2}, {3,4,5}, {6}
count: 3
```

One shared discovered array must persist across all roots.

#### D3. Directed wording

For directed input, say “traversal forest” and describe directed
reachability. Do not infer weak or strong components from its trees.

### E. Apply the public contract

#### E1. Status cases

| Case | Status |
|---|---|
| missing required output | `GRAPH_BFS_INVALID_ARGUMENT` |
| malformed matrix/list | `GRAPH_BFS_INVALID_GRAPH` |
| source or destination not active | `GRAPH_BFS_OUT_OF_RANGE` |
| requested limit above 16 | `GRAPH_BFS_LIMIT` |
| needed Queue count exceeds selected limit | `GRAPH_BFS_LIMIT` |
| path destination undiscovered | `GRAPH_BFS_UNREACHABLE` |
| malformed stored result | `GRAPH_BFS_INVALID_RESULT` |

An empty graph has no active source, so one-source traversal reports
`GRAPH_BFS_OUT_OF_RANGE`.

#### E2. Failure preservation

Matrix BFS, list BFS, and path reconstruction create local candidates.
They copy to the caller only on `GRAPH_BFS_OK`. All named fields of a
sentinel output therefore remain unchanged after failure.

#### E3. Result validator boundary

The validator can check bounds, sentinels, order uniqueness,
discovery/order agreement, nondecreasing distance, and predecessor distance
steps. It cannot prove an original graph edge existed because no graph is
stored in `GraphBfsResult`.

#### E4. Queue limits

- Canonical limit 3 succeeds.
- Limit 2 fails while processing 1: with 2 waiting, enqueue 3 fills the
  selected capacity and enqueue 4 fails.
- Caller output remains unchanged even though the local candidate already
  contains visits 0 and 1.
- A nonempty traversal at limit 0 fails on the source enqueue.

#### E5. Ownership

The matrix owns no allocation. The adjacency list owns each non-NULL
neighbor row and must be destroyed exactly once. The inline Queue owns no
graph vertices and needs no destroy operation. BFS takes `const` graph
pointers and changes neither representation.

### F. Compare representations and costs

#### F1. Same outgoing work

For vertex 2:

```text
matrix: scan cells [2][0] through [2][7]; true at 4 and 5
list:   read live entries neighbors[2].data[0] and [1], values 4 and 5
```

The list metadata fields mean:

- `data`: address of the owned destination array;
- `size`: live destination count;
- `capacity`: allocated destination slots.

#### F2. Cost table

| Quantity | Matrix | Adjacency list |
|---|---:|---:|
| Public BFS time | `O(V²)` | `O(V+E)` |
| Representation storage | `O(V²)` | `O(V+E)` |
| BFS auxiliary state | `O(V)` | `O(V)` |

Matrix validation and traversal each have the stated square bound. List
validation and traversal each scan metadata plus stored entries.

#### F3. Construction boundary

Building, sorted insertion, allocation, and matrix-to-list conversion are
not traversal. A conversion that scans all matrix cells costs `O(V²)`.
Measure or analyze BFS only after each representation is valid and built.

#### F4. Security interpretation

Minimum modeled hop count does not establish real reachability,
authorization, vulnerability, exploitability, likelihood, compromise, or
risk. Only synthetic authorized data belongs in the exercise.

### G. Three student tests

Full-credit designs:

1. Cyclic/converging graph: assert each reached vertex occurs once and check
   all distances and predecessors.
2. Path/unreachable: verify every edge of one reconstructed path, its hop
   count, and unchanged output on unreachable.
3. Disconnected sparse graph: build identical matrix and list inputs, then
   compare all named results and explicit undiscovered vertices.

Tests must add claims not already duplicated verbatim by supplied tests.

### H. Autopsy and order extension

#### H1. Correct and faulty states

Fixture:

```text
0:[1,2]  1:[3,4]  2:[3,4]  3:[0]  4:[]
```

Correct:

```text
after 2: [3,4]
order: 0,1,2,3,4
predecessor[3] = predecessor[4] = 1
```

Faulty:

```text
after 2: [3,4,3,4]
order: 0,1,2,3,4,3,4
predecessor[3] = predecessor[4] = 2
```

The first broken decision is enqueueing a second 3 while the first 3 is
pending. Move discovery and first-state assignment to immediately after
successful enqueue. Edge `3 -> 0` remains safely skipped because source 0
was already processed and marked.

#### H2. Changing neighbor order

Descending neighbor order may change visit order and equal-hop
predecessors, but not the reachable set or minimum distances. Matrix and
list only remain field-for-field equal if they follow the same order.

### I. Spiral synthesis

- Module 8 FIFO Queue: a pending item waits for earlier-added items to be
  removed; FIFO alone gives no graph-distance or duplicate-prevention claim.
- Module 5 tree DFS Stack: pending records describe unfinished node and
  ancestor work; the most recent unfinished record is considered first.
- Module 8 graph BFS: pending item means a discovered vertex waiting at a
  known hop distance; discovery state prevents repeated scheduling.

Model synthesis:

> The tree DFS Stack uses LIFO; ordinary Queues and the BFS frontier use FIFO. For graph
> minimum-hop distance, FIFO must be combined with unit edges and discovery at
> successful enqueue. None of those facts alone is the complete guarantee.

## Stage E canonical lab checkpoints

Students should report:

```text
matrix canonical status: ok
list canonical status: ok
matrix/list named fields equal: true
limit 3: success
limit 2: limit, prior result preserved
path 6: 0,1,3,6
path 7: unreachable, prior path preserved
adjacency-list live rows after destroy: baseline
```

The matrix and list may have different physical storage, but their public
BFS result fields match.

## Graph BFS Autopsy conclusion

Expected prediction and observation:

```text
faulty Queue after 2: [3,4,3,4]
faulty order: 0,1,2,3,4,3,4
faulty predecessor[3]: 2
faulty predecessor[4]: 2
first broken decision: duplicate enqueue of pending vertex 3
smallest repair: discover and assign immediately after successful enqueue
regression: exact order 0,1,2,3,4; each count once; predecessors 3=1,4=1
```

The fixed bounds make the program memory-safe, not logically correct. The
duplicate routes in this fixture have equal length, so do not report a
wrong distance as the observed defect.
