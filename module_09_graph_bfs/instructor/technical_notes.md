# Instructor Technical Notes — Module 9 Graph BFS

## Source of truth

The public headers are authoritative for names, field order, status order,
limits, parameters, and ownership. These notes explain that contract without
adding another public operation.

The common graph maximum remains:

```c
#define GRAPH_MAX_VERTICES 16U
```

Active vertex identifiers are the integers from `0` through
`vertex_count - 1`. Sixteen is therefore outside every valid vertex range
and above every possible minimum-hop distance in a simple graph of at most
16 vertices.

```c
#define GRAPH_BFS_NO_VERTEX ((size_t)GRAPH_MAX_VERTICES)
#define GRAPH_BFS_NO_DISTANCE ((size_t)GRAPH_MAX_VERTICES)
```

The two names currently have the same stored value, 16, but communicate
different meanings. Student prose should say `no predecessor` or
`unreachable`, not merely “16.”

## Public BFS result and path

```c
typedef struct {
    size_t vertex_count;
    size_t source;
    size_t visit_order[GRAPH_MAX_VERTICES];
    size_t visit_count;
    bool discovered[GRAPH_MAX_VERTICES];
    size_t distance[GRAPH_MAX_VERTICES];
    size_t predecessor[GRAPH_MAX_VERTICES];
} GraphBfsResult;

typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphBfsPath;
```

`visit_order` records dequeue order. A vertex is **discovered** after its
first successful enqueue. A vertex is **processed** when it is dequeued.
Thus a discovered vertex may still be waiting.

For a successful result:

1. `vertex_count` equals the input graph count;
2. `source` is active;
3. the source is discovered, has distance 0, and has no predecessor;
4. every other discovered vertex has a distance from 1 through 15;
5. every discovered nonsource vertex has one active, discovered predecessor
   whose distance is exactly one smaller;
6. every undiscovered active vertex has no distance and no predecessor;
7. `visit_order[0..visit_count)` contains every discovered vertex exactly
   once;
8. visit distances are nondecreasing; and
9. unused array slots have the header-defined sentinel state.

Only active prefixes and explicitly documented sentinel slots carry public
meaning. Do not compare whole structures byte for byte as a semantic claim:
C may add padding bytes. Compare named fields, or use a byte snapshot only
when testing failure preservation of the exact caller object.

`GraphBfsPath` contains source through destination, including both
endpoints. Its hop count is `count - 1` when count is positive. A path from
the source to itself contains one vertex and has zero hops.

## Exact BFS status contract

The status order is:

```c
typedef enum {
    GRAPH_BFS_OK = 0,
    GRAPH_BFS_INVALID_ARGUMENT,
    GRAPH_BFS_OUT_OF_RANGE,
    GRAPH_BFS_INVALID_GRAPH,
    GRAPH_BFS_LIMIT,
    GRAPH_BFS_UNREACHABLE,
    GRAPH_BFS_INVALID_RESULT
} GraphBfsStatus;
```

Exact readable names:

| Status | `graph_bfs_status_name` result |
|---|---|
| `GRAPH_BFS_OK` | `"ok"` |
| `GRAPH_BFS_INVALID_ARGUMENT` | `"invalid argument"` |
| `GRAPH_BFS_OUT_OF_RANGE` | `"source or destination vertex out of range"` |
| `GRAPH_BFS_INVALID_GRAPH` | `"graph does not satisfy required representation rules"` |
| `GRAPH_BFS_LIMIT` | `"vertex Queue limit reached or requested limit too large"` |
| `GRAPH_BFS_UNREACHABLE` | `"destination is unreachable from the source"` |
| `GRAPH_BFS_INVALID_RESULT` | `"BFS result is invalid"` |
| any unknown value | `"unknown GraphBfsStatus"` |

There is deliberately no BFS allocation status. The typed Queue is inline
and the result is caller-provided. Allocation belongs to the supplied
adjacency-list construction API, not to either BFS loop.

Public declarations:

```c
GraphBfsStatus graph_bfs_matrix(
    const Graph *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);

GraphBfsStatus graph_bfs_list(
    const GraphAdjList *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);

GraphBfsStatus graph_bfs_reconstruct_path(
    const GraphBfsResult *result,
    size_t destination_vertex,
    GraphBfsPath *out_path);

GraphBfsStatus graph_bfs_result_validate(
    const GraphBfsResult *result);

const char *graph_bfs_status_name(GraphBfsStatus status);
```

Students implement only `graph_bfs_matrix`,
`graph_bfs_reconstruct_path`, and `graph_bfs_list`. Result validation,
both representations, adjacency-list ownership, and the typed Queue are
supplied.

## Graph contracts reused and introduced

Both representations store the same bounded, simple, unweighted graph:

- the kind is exactly directed or undirected;
- active identifiers are in range;
- self-loops are absent;
- duplicate or parallel edges are absent; and
- an undirected logical edge is represented in both directions.

The matrix retains Module 3's convention:

```text
adjacency[from][to]
```

A true cell records one directed edge. Directed rows are independent.
Undirected mirror cells must agree.

The reused matrix kind and status order are:

```c
typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

typedef enum {
    GRAPH_OK = 0,
    GRAPH_ERR_INVALID_ARGUMENT,
    GRAPH_ERR_OUT_OF_RANGE,
    GRAPH_ERR_SELF_LOOP,
    GRAPH_ERR_EDGE_EXISTS,
    GRAPH_ERR_EDGE_ABSENT,
    GRAPH_ERR_INVALID_GRAPH
} GraphStatus;
```

Exact matrix status names:

| Status | `graph_status_name` result |
|---|---|
| `GRAPH_OK` | `"ok"` |
| `GRAPH_ERR_INVALID_ARGUMENT` | `"invalid argument"` |
| `GRAPH_ERR_OUT_OF_RANGE` | `"vertex count or index out of range"` |
| `GRAPH_ERR_SELF_LOOP` | `"self-loops are not allowed"` |
| `GRAPH_ERR_EDGE_EXISTS` | `"edge already exists"` |
| `GRAPH_ERR_EDGE_ABSENT` | `"edge does not exist"` |
| `GRAPH_ERR_INVALID_GRAPH` | `"graph does not satisfy required representation rules"` |
| any unknown value | `"unknown GraphStatus"` |

The new adjacency list is not a linked list. It is an array with one dynamic
neighbor array per possible source:

```c
typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
} GraphNeighborArray;

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    GraphNeighborArray neighbors[GRAPH_MAX_VERTICES];
} GraphAdjList;
```

For each active row, live destinations occupy `data[0..size)` in strictly
ascending order. Every destination is active and differs from its source.
Strict order also proves uniqueness. An inactive row is canonical empty.
For an undirected graph, every stored `u -> v` entry has a stored reciprocal
`v -> u` entry.

Each non-NULL row allocation belongs to the `GraphAdjList`. Copying the
outer struct would make a dangerous shallow copy. The supplied destroy
operation releases every owned row and resets the complete object.

## Supplied adjacency-list API boundary

The separate status type is:

```c
typedef enum {
    GRAPH_ADJ_LIST_OK = 0,
    GRAPH_ADJ_LIST_INVALID_ARGUMENT,
    GRAPH_ADJ_LIST_OUT_OF_RANGE,
    GRAPH_ADJ_LIST_SELF_LOOP,
    GRAPH_ADJ_LIST_EDGE_EXISTS,
    GRAPH_ADJ_LIST_EDGE_ABSENT,
    GRAPH_ADJ_LIST_INVALID_GRAPH,
    GRAPH_ADJ_LIST_ALLOCATION
} GraphAdjListStatus;
```

Exact readable names:

| Status | `graph_adj_list_status_name` result |
|---|---|
| `GRAPH_ADJ_LIST_OK` | `"ok"` |
| `GRAPH_ADJ_LIST_INVALID_ARGUMENT` | `"invalid argument"` |
| `GRAPH_ADJ_LIST_OUT_OF_RANGE` | `"vertex count or index out of range"` |
| `GRAPH_ADJ_LIST_SELF_LOOP` | `"self-loops are not allowed"` |
| `GRAPH_ADJ_LIST_EDGE_EXISTS` | `"edge already exists"` |
| `GRAPH_ADJ_LIST_EDGE_ABSENT` | `"edge does not exist"` |
| `GRAPH_ADJ_LIST_INVALID_GRAPH` | `"graph does not satisfy adjacency-list representation rules"` |
| `GRAPH_ADJ_LIST_ALLOCATION` | `"allocation failed"` |
| any unknown value | `"unknown GraphAdjListStatus"` |

The supplied operations are:

```c
graph_adj_list_init
graph_adj_list_validate
graph_adj_list_add_edge
graph_adj_list_remove_edge
graph_adj_list_has_edge
graph_adj_list_out_neighbors
graph_adj_list_destroy
graph_adj_list_status_name
```

Initialization accepts an all-zero or destroyed receiver, sets the vertex
count and kind, and allocates no neighbor storage. Edge insertion grows only
the affected row or rows, keeps destinations sorted, and commits only after
all required allocation succeeds. An undirected insertion stages both
possible row growths before changing either logical direction. Removal
shifts later destinations but does not need to shrink capacity.

Accepted row capacities follow the supplied growth sequence:

```text
0 -> 4 -> 8 -> 16
```

Initialization must receive `GraphAdjList graph = {0};` or an object already
reset by destroy. It does not accept arbitrary uninitialized bytes.

Every failed mutation preserves the complete graph. Failed queries preserve
their output. Destroy accepts `NULL` as a no-op; every other receiver must
be initialized or already destroyed.

Testing builds expose a deterministic allocation-failure hook and a live
row-allocation count. These are instructor/test seams, not learner
configuration.

Students read and test this representation but do not implement its growth,
sorting, reciprocal update, or cleanup. Their list BFS only enumerates the
already sorted live entries of the current row.

## Supplied typed Queue

```c
typedef struct {
    size_t data[GRAPH_MAX_VERTICES];
    size_t limit;
    size_t head;
    size_t size;
} VertexQueue;
```

Exact internal status order:

```c
typedef enum {
    VERTEX_QUEUE_OK = 0,
    VERTEX_QUEUE_INVALID_ARGUMENT,
    VERTEX_QUEUE_LIMIT,
    VERTEX_QUEUE_UNDERFLOW,
    VERTEX_QUEUE_INVALID_STATE
} VertexQueueStatus;
```

The Queue uses an inline circular array and owns no dynamic storage.
Accepted limits are 0 through 16. Logical item `k` is at:

```text
(head + k) % limit
```

only when `limit > 0` and `k < size`. A full check must occur before a
remainder operation, because a valid limit-zero Queue is also full.

Required representation rules:

```text
limit <= 16
size <= limit
size == 0 requires head == 0
size > 0 requires limit > 0 and head < limit
every live item is below 16
```

`vertex_queue_validate` is the explicit full validator. It checks shape and
scans every live item, so its cost is `O(size)`. Enqueue and dequeue do not
call that full validator on every operation. Under their documented
precondition that the Queue already satisfies its complete invariant, they
perform constant-time shape checks; enqueue also checks the new identifier,
and dequeue checks the identifier at the head. Each operation is therefore
`O(1)`. This distinction keeps a list traversal from accidentally rescanning
the complete frontier at every edge.

Enqueue at the selected limit reports `VERTEX_QUEUE_LIMIT` and preserves
the Queue. Empty dequeue reports `VERTEX_QUEUE_UNDERFLOW` and preserves its
output. Removing the final item normalizes `head` to zero. There is no
allocation or destroy operation.

The dequeue output must be separate from the Queue's inline `data` array.
Writing a removed ID through an alias to a still-pending slot could change
the remaining FIFO sequence. This is a caller precondition, not a new
status.

Exact readable names:

| Status | `vertex_queue_status_name` result |
|---|---|
| `VERTEX_QUEUE_OK` | `"ok"` |
| `VERTEX_QUEUE_INVALID_ARGUMENT` | `"invalid argument"` |
| `VERTEX_QUEUE_LIMIT` | `"vertex Queue limit reached"` |
| `VERTEX_QUEUE_UNDERFLOW` | `"vertex Queue is empty"` |
| `VERTEX_QUEUE_INVALID_STATE` | `"vertex Queue representation is invalid"` |
| any unknown value | `"unknown VertexQueueStatus"` |

BFS maps a Queue-limit result to `GRAPH_BFS_LIMIT`. An unexpected Queue
argument or representation error maps to `GRAPH_BFS_INVALID_ARGUMENT`;
it indicates an internal defect, not a new public BFS status.

## Discovery invariant

At each completed loop boundary:

1. `discovered[v]` means `v` was successfully enqueued earlier;
2. every queued vertex is discovered but not processed;
3. every processed vertex is discovered and occurs once in visit order;
4. no active vertex is enqueued more than once;
5. Queue distances are nondecreasing from front to back;
6. the Queue contains vertices from at most two adjacent distances;
7. first discovery fixes distance and predecessor permanently; and
8. `visit_count <= vertex_count <= 16`.

The source is enqueued first. Only after that enqueue succeeds may the
source be marked discovered and assigned distance 0.

For an outgoing edge `u -> v`:

```text
if v is not discovered:
    enqueue v
    if enqueue succeeds:
        discovered[v] = true
        distance[v] = distance[u] + 1
        predecessor[v] = u
```

Do not mark before a possibly failing enqueue: that would claim unscheduled
work exists. Do not wait until dequeue: two processed vertices could then
enqueue the same pending destination.

## Matrix BFS

Language-independent core:

```text
validate request, complete matrix, source, and Queue limit
initialize a local candidate with sentinels
enqueue source; then discover source at distance 0

while dequeue succeeds:
    append u to candidate visit order
    for v from 0 through V - 1:
        if matrix[u][v] is true and v is not discovered:
            enqueue v
            discover v at distance[u] + 1 with predecessor u

commit the candidate only after complete success
```

Directed traversal follows outgoing edges only. An undirected matrix
contains both directions, so the same loop works without a second
algorithm.

## Adjacency-list BFS

The state transitions are identical. Only neighbor enumeration changes:

```text
for i from 0 through neighbors[u].size - 1:
    v = neighbors[u].data[i]
    if v is not discovered:
        enqueue v
        discover v at distance[u] + 1 with predecessor u
```

Because list rows are sorted, matrix and list traversal inspect destinations
in the same order. They must therefore produce equal named result fields,
not merely equal reachable sets.

Do not convert the matrix during a timed list traversal. Construction is a
separate operation with separate allocation and failure behavior.

## Why first discovery is minimum-hop

The guarantee uses three facts together:

1. every edge contributes exactly one hop;
2. FIFO removal processes nondecreasing distances; and
3. a vertex is discovered only once, when first enqueued.

When a distance-`d` vertex first reaches an unseen neighbor, the new route
has `d + 1` hops. No undiscovered route with fewer hops can appear later,
because every vertex at a smaller distance was already ahead in the Queue.
Thus first discovery fixes a minimum hop count.

FIFO alone is not a weighted shortest-path algorithm. If edge costs differ,
fewer edges may cost more. Dijkstra and weighted relaxation wait until
Module 12.

## Result validation

`graph_bfs_result_validate` checks visible relationships in the stored
result without reading either graph representation. It checks bounds,
sentinels, uniqueness, source state, visit/discovery agreement,
nondecreasing distances, and predecessor distance steps.

It cannot prove that `predecessor[v] -> v` was an edge in the original
graph, because the result stores no graph. Therefore it validates a bounded
predecessor certificate structurally, not against the original edge set.
Tests that still have the graph should independently verify every path
edge.

## Path reconstruction

The path operation:

1. rejects a missing result or output;
2. validates the complete result;
3. rejects a destination outside `result->vertex_count`;
4. reports `GRAPH_BFS_UNREACHABLE` when the destination is undiscovered;
5. follows predecessors from destination back to source into a local reverse
   array;
6. stops safely within at most `vertex_count` vertices;
7. reverses that sequence into a local `GraphBfsPath`; and
8. commits only after success.

The source predecessor is the no-vertex sentinel. An unreachable result,
invalid destination, or malformed result preserves the caller's old path.
The bounded validator prevents a malformed predecessor cycle from causing
unbounded work.

## Failure preservation and input immutability

Both BFS functions build a complete local candidate. Their exact public
decision order is:

1. reject a missing required output pointer;
2. validate the complete representation;
3. map a `NULL` graph from the representation validator to
   `GRAPH_BFS_INVALID_ARGUMENT`;
4. map every other non-successful structural validation to
   `GRAPH_BFS_INVALID_GRAPH`;
5. reject a source outside the now-valid active range;
6. initialize the Queue, which rejects a requested limit above 16; and
7. traverse, mapping a full Queue to `GRAPH_BFS_LIMIT`.

A missing pointer, invalid graph, inactive source, excessive or
insufficient Queue limit, or unexpected internal Queue error leaves every
named caller-result field unchanged. The matrix or list also remains
unchanged because its parameter is `const`.

Path reconstruction likewise commits a local path only on
`GRAPH_BFS_OK`. Unreachable is an expected negative answer, not partial
success; the previous path remains unchanged.

An empty valid graph has no active source, so a one-source traversal reports
`GRAPH_BFS_OUT_OF_RANGE`. A singleton graph from source 0 succeeds with
order `[0]`, distance 0, no predecessor, and a one-vertex path to itself.

## Authoritative Stage A fixture

```text
0 Gateway:  [1,2]
1 Web:      [3]
2 Admin:    [3]
3 Database: [4]
4 Monitor:  [1]
5 Archive:  []
```

From source 0:

```text
visit order:  0,1,2,3,4
distance:     0,1,1,2,3,unreachable
predecessor:  none,0,0,1,3,none
path to 4:   0,1,3,4
```

Stage A asks for these ideas in ordinary language but reveals none of the
formal state names or exact answers.

## Authoritative Stage B reveal fixture

```text
0:[1,2]  1:[3]  2:[3,4]  3:[0]  4:[]
```

```text
initial: [0]
after 0: [1,2]
after 1: [2,3]
after 2: [3,4]
after 3: [4]
after 4: []

order:       0,1,2,3,4
distance:    0,1,1,2,2
predecessor: none,0,0,1,2
path to 4:  0,2,4
```

At `2 -> 3`, 3 is already discovered while pending. At `3 -> 0`, the
source is already discovered.

## Authoritative Cognitive Pause fixture

```text
0:[1,3]
1:[2,4]
2:[0]
3:[2,5]
4:[5]
5:[]
6:[]
```

Exactly three scored targets:

1. Queue and state trace;
2. discovery timing at `3 -> 2`; and
3. path to 5 plus unreachable vertex 6.

Answers:

```text
initial: [0]
after 0: [1,3]
after 1: [3,2,4]
after 3: [2,4,5]

order:       0,1,3,2,4,5
distance:    0,1,2,1,2,2,unreachable
predecessor: none,0,1,0,1,3,none
path to 5:  0,3,5
vertex 6:   unreachable
```

When 3 checks 2, vertex 2 was already enqueued by vertex 1. It is skipped.

## Canonical lab fixture

| ID | Synthetic label | Ascending outgoing neighbors |
|---:|---|---|
| 0 | Gateway | 1, 2 |
| 1 | Web | 3, 4 |
| 2 | Admin | 4, 5 |
| 3 | Database | 6 |
| 4 | LogCollector | 6 |
| 5 | VPN | 4 |
| 6 | Monitor | 1 |
| 7 | Archive | none |

The ten directed edges are:

```text
0->1  0->2  1->3  1->4  2->4
2->5  3->6  4->6  5->4  6->1
```

Exact trace:

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

Exact result:

```text
visit_count: 7
visit order: 0,1,2,3,4,5,6
discovered:  true,true,true,true,true,true,true,false
distance:    0,1,1,2,2,2,3,16
predecessor: 16,0,0,1,1,2,3,16
```

Skipped established work:

```text
2->4  because 4 is pending
4->6  because 6 is pending
5->4  because 4 is processed
6->1  because 1 is processed
```

Paths:

```text
to 6: 0,1,3,6; 3 hops
to 4: 0,1,4;   2 hops
to 7: unreachable
```

Other equal-hop routes exist. The ascending rule selects one deterministic
predecessor tree; do not call that route unique.

The maximum pending count is 3. Queue limit 3 succeeds. At limit 2,
processing vertex 1 leaves vertex 2 waiting, enqueues vertex 3, and then
cannot enqueue vertex 4. The public result remains unchanged.

## Paper-only disconnected forest

Use a separate undirected graph:

```text
vertices: 0 through 6
edges: {0,1}, {1,2}, {3,4}, {4,5}
vertex 6 is isolated
```

One shared discovered array and an ascending outer scan produce:

```text
0,1,2 | 3,4,5 | 6
roots: 0,3,6
connected-component count: 3
```

The vertical bars are explanatory tree boundaries, not stored vertex
values. No public forest function or code TODO exists.

For a directed graph, an analogous outer scan covers every vertex, but its
trees depend on edge direction and scan order. They are not automatically
weakly or strongly connected components.

## Complexity boundary

Let:

- `V` be active vertex count;
- `E` be logical edge count;
- `R` be the count reached from one source; and
- `E_R` be outgoing entries inspected from reached vertices.

For an already valid matrix, the traversal core initializes `V` state and
scans `V` destinations for each reached vertex:

```text
O(V + RV), worst case O(V²)
```

Complete matrix validation is also `O(V²)`, so the public matrix call is
`O(V²)`.

For an already valid adjacency list, the traversal core is:

```text
O(V + E_R), worst case O(V+E)
```

The supplied list validator scans row metadata and stored entries and uses
bounded scratch information to check undirected reciprocity in `O(V+E)`.
Thus the public list call remains `O(V+E)`.

Both traversals use `O(V)` auxiliary state: Queue, discovery, distances,
predecessors, and the local candidate. The returned result is output and is
accounted for separately.

Representation storage differs:

```text
matrix:         O(V²)
adjacency list: O(V+E)
```

An undirected logical edge produces two stored list entries; this constant
factor does not change the expression.

Graph construction, sorted insertion, possible allocation, and any
matrix-to-list conversion are separate from traversal. A conversion that
scans a complete matrix is `O(V²)` and must not be included in a claim that
an already-built list traversal is `O(V+E)`.

## Starter assignment and test partition

Student TODOs:

1. matrix BFS;
2. predecessor-based path reconstruction; and
3. adjacency-list BFS.

Visible core tests should cover:

- exact canonical matrix and list results;
- field-for-field matrix/list equality;
- canonical limit-3 success and limit-2 preservation;
- repeated-route suppression and permanent predecessors;
- path to 6, source path, and unreachable 7;
- empty, singleton, invalid source, excessive limit, and null output;
- malformed matrix and malformed adjacency-list rejection;
- result-validator rejection of bad bounds, duplicate order, bad sentinel,
  bad distance step, and predecessor cycles;
- supplied Queue FIFO, wrap, full, underflow, and state validation;
- supplied list sorted insertion, queries, removal, undirected reciprocity,
  cleanup, and status-name behavior; and
- standalone bounded autopsy output.

Private extensions should add:

- every Queue limit from 0 through 16;
- a 16-vertex chain that succeeds with limit 1, reaches distance 15, and
  reconstructs a 16-vertex path;
- a 16-vertex star whose limit 15 succeeds and limit 14 preserves output;
- maximum 16-vertex cycles;
- all result fields preserved after every failure category;
- graph nonmutation snapshots;
- list growth, first forced allocation failure, second staged allocation
  failure, and return to the live-row-allocation baseline;
- undirected two-row allocation atomicity;
- inactive-row and reciprocal-edge corruption;
- multiple equal-hop predecessor ties;
- path rejection for every malformed-result category; and
- status-name fallbacks.

Exactly three student-authored categories:

1. a cyclic, converging graph with exact order, distances, predecessors,
   and no duplicate;
2. one reachable path certificate plus unreachable-output preservation; and
3. the same disconnected sparse graph in both representations with equal
   named results.

## Safe autopsy

The standalone fixture is:

```text
0:[1,2]
1:[3,4]
2:[3,4]
3:[0]
4:[]
```

Correct enqueue-time discovery:

```text
initial: [0]
after 0: [1,2]
after 1: [2,3,4]
after 2: [3,4]
order: 0,1,2,3,4
predecessor[3] = 1
predecessor[4] = 1
```

When 3 is processed, its edge to already processed source 0 is skipped.

The supplied faulty program delays discovery until dequeue:

```text
after 2: [3,4,3,4]
faulty order: 0,1,2,3,4,3,4
faulty predecessor[3] = 2
faulty predecessor[4] = 2
```

The first broken state is the duplicate enqueue of 3 while its first record
is already pending. The minimum repair is to mark and assign state
immediately after the first successful enqueue, including for the source.

The program uses checked fixed arrays and a fixed processing budget. It is
memory-safe and terminates. Bounds safety does not imply scheduling
correctness. Do not claim this particular defect changes hop distance: the
duplicate routes shown have equal length. It does waste work and overwrite
the published deterministic predecessor.

## Security and systems boundary

The authorized-communication graph is invented. A returned path certifies
only that consecutive modeled edges exist and that the path length matches
the stored BFS distance.

It does not prove:

- current physical reachability;
- authentication or authorization;
- vulnerability or exploitability;
- attack likelihood;
- successful compromise;
- complete or current policy data; or
- real operational risk.

Do not adapt the lab into live network discovery. Fewer modeled hops is not
a risk score.

## Deferred topics

Do not add to core:

- weighted edges, relaxation, Dijkstra, Priority Queues, or Heaps;
- adjacency linked nodes;
- student implementation of list allocation or growth;
- recursive, bidirectional, or all-pairs BFS;
- enumeration of every minimum-hop path;
- topological sorting;
- weakly or strongly connected component algorithms;
- public forest code;
- generic `void *` containers; or
- live system input.

## Five release gates

1. **Stage A:** standard and linear inquiry only. Withhold BFS, Queue,
   frontier, discovered, distance, predecessor, adjacency-list
   representation, formulas, code, method, and answers.
2. **Stage B:** formal reveal, exactly-three-target Cognitive Pause, and
   vocabulary. Vocabulary remains closed until the pause is preserved.
3. **Stage C:** matching standard and linear investigation. Sections A–F
   are core; G–I remain closed or ungraded until the announced later work.
4. **Stage D:** 1,100–1,250-word beginner textbook and models with exact
   linear equivalents, released only after Stage C A–F is preserved.
5. **Stage E:** lab, rubric, evidence, bounded autopsy, public/supplied code,
   starter, visible core tests, student-test template, and build files.

Stage E excludes instructor files, solution, private extensions, earlier
stages, forest code, live data, generated binaries, and unbounded faults.

## Accessibility requirements

- Standard and linear files use identical question IDs, vertex IDs, edges,
  operation order, targets, and scoring.
- Every graph picture has a numbered vertex table, ordered edge list, and
  ascending outgoing-neighbor-list equivalent.
- Queue state always says “front to back.”
- Write `true`, `false`, `none`, and `unreachable`; never rely on color,
  arrow shape, spatial position, or a checkmark alone.
- Define `u -> v`, brackets, sentinel 16, `V`, `E`, and `O(...)` before use.
- Linear versions use ASCII arrows.
- Students may draw, use structured tables, dictate numbered sentences, or
  use an accessible editor.
- Approved extended-time pause work uses the same three targets.
- Grade reasoning, contracts, and evidence rather than speed, handwriting,
  drawing aesthetics, typing, or spoken fluency.

## Instructor validation checklist

- [ ] All code/prose use maximum 16 and sentinel 16.
- [ ] Status order and exact readable BFS names match the header.
- [ ] There is no BFS allocation status.
- [ ] Only three BFS/path operations are student TODOs.
- [ ] Matrix and list validate before traversal.
- [ ] The Queue is supplied, inline, circular, and allocation-free.
- [ ] Source and neighbor discovery occur only after successful enqueue.
- [ ] Every predecessor and distance is assigned once.
- [ ] Ascending neighbor order is consistent across representations.
- [ ] Canonical order and all arrays are exact.
- [ ] Canonical limit 3 succeeds; limit 2 preserves output.
- [ ] Path 0,1,3,6 and unreachable 7 are exact.
- [ ] Result validation never claims to verify original graph edges.
- [ ] Matrix/list outputs are called field-for-field equal, not byte equal.
- [ ] Matrix validation/traversal are `O(V²)`.
- [ ] List validation/traversal are `O(V+E)`.
- [ ] Construction cost is separate from traversal.
- [ ] Paper forest makes component claims only for undirected input.
- [ ] Autopsy is bounded and does not overclaim a distance error.
- [ ] Textbook remains within 1,100–1,250 words.
- [ ] Pause contains exactly three target headings.
- [ ] Standard and linear materials are semantically identical.
- [ ] No synthetic hop result is presented as real risk.
