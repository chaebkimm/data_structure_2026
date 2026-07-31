# Instructor Answer Key — Module 9 Graph BFS

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

- Module 7 event Queue: pending item means an event waiting for service.
- Module 8 tree BFS: pending item means a uniquely reached tree node waiting
  at a known depth.
- Module 9 graph BFS: pending item means a discovered vertex waiting at a
  known hop distance; discovery state prevents repeated scheduling.

Model synthesis:

> FIFO controls the order in all three settings. For graph minimum-hop
> distance, FIFO must be combined with unit edges and discovery at
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
