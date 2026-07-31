# Lab — Minimum-Hop Graph Search

## Purpose

You will complete three operations over small synthetic graphs:

1. breadth-first search on an adjacency matrix;
2. path reconstruction from a completed result; and
3. the same search on an adjacency list.

**Breadth-first search (BFS)** processes smaller hop counts before larger
hop counts from one source. A **hop** follows one edge. A **source** is the
starting vertex.

## 1. Work only in the student files

Read:

- `code/include/graph_bfs.h` — public BFS result and contracts;
- `code/include/graph_matrix.h` — supplied matrix graph;
- `code/include/graph_adj_list.h` — supplied dynamic-neighbor-array graph;
- `code/include/vertex_queue.h` — supplied Queue that stores vertex IDs;
- `code/README.md` — build guide;
- `code/starter/graph_bfs.c` — three unfinished tasks; and
- `code/tests/test_student.c` — three unfinished tests.

A **TODO** marks an unfinished task. Edit only:

- the three numbered TODO tasks in `code/starter/graph_bfs.c`;
- private `static` helpers in that starter file when useful; a `static`
  helper here is a small function usable only inside that source file; and
- the three TODO test bodies in `code/tests/test_student.c`.

Do not change public headers, supplied graph/Queue support, supplied tests,
or their expected results.

## 2. Read the result types

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

A **struct** groups named values called fields. `size_t` is C's
nonnegative type for sizes and indexes. `bool` stores `true` or `false`.
An **ID** is an identifying number.

The maximum vertex count is 16. The named sentinels are:

```text
GRAPH_BFS_NO_VERTEX   = 16
GRAPH_BFS_NO_DISTANCE = 16
```

A **sentinel** is a value representing a special case. Every unused
`visit_order` or path position contains 16. Every inactive or unreachable
distance/predecessor position contains 16.

## 3. Use the supplied Queue

A **Queue** removes the earliest-added item first. `enqueue` adds at the
back and `dequeue` removes from the front. The **frontier** is the Queue of
discovered vertices still waiting.

Use only:

```c
vertex_queue_init
vertex_queue_enqueue
vertex_queue_dequeue
```

`VertexQueue` has a fixed 16-ID array directly inside its object. This
**inline** storage requires no allocation or destroy call. A Queue limit may
be 0 through 16.

The explicit full validator scans queued IDs. Enqueue and dequeue use
constant-time checks under the requirement that the Queue already satisfies
its complete rules. Do not call the full validator inside every loop step.
Store each dequeued ID in a separate `size_t` variable, never in
`queue.data`; otherwise reporting an output could overwrite pending work.

Map `VERTEX_QUEUE_LIMIT` to `GRAPH_BFS_LIMIT`. Empty dequeue returns
`VERTEX_QUEUE_UNDERFLOW`, which normally ends traversal. Another unexpected
Queue failure maps to `GRAPH_BFS_INVALID_ARGUMENT`.

## 4. Initialize a complete candidate

A **candidate** is a temporary possible output. To **commit** means to copy
it to caller output only after all required work succeeds. A **caller** is
code asking a function to run.

Before traversal:

1. copy graph vertex count and source;
2. set `visit_count` to 0;
3. set all 16 visit positions to no vertex;
4. set all 16 discovered values to false;
5. set all 16 distances to no distance; and
6. set all 16 predecessors to no vertex.

Every failure returns without committing. Do not partially initialize the
caller's old result.

## 5. TODO 1 — Matrix BFS

Complete:

```c
GraphBfsStatus graph_bfs_matrix(
    const Graph *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);
```

Use this decision order:

1. reject a `NULL` output;
2. call `graph_validate`;
3. map a `NULL` graph to `GRAPH_BFS_INVALID_ARGUMENT`;
4. map another validation failure to `GRAPH_BFS_INVALID_GRAPH`;
5. reject an inactive source with `GRAPH_BFS_OUT_OF_RANGE`;
6. initialize the Queue, mapping an excessive limit;
7. enqueue the source;
8. only after success, discover source at distance 0;
9. dequeue and record each vertex;
10. scan matrix destinations from 0 upward;
11. for an unseen destination, enqueue first;
12. after success, assign discovery, distance, and predecessor;
13. stop normally at Queue underflow; and
14. commit the complete result.

The matrix uses:

```text
adjacency[from][to]
```

Directed BFS follows outgoing edges only. Never overwrite distance or
predecessor for an already discovered destination.

## 6. TODO 2 — Reconstruct a path

Complete:

```c
GraphBfsStatus graph_bfs_reconstruct_path(
    const GraphBfsResult *result,
    size_t destination_vertex,
    GraphBfsPath *out_path);
```

Follow this contract:

1. reject a `NULL` output;
2. call `graph_bfs_result_validate`;
3. preserve `GRAPH_BFS_INVALID_ARGUMENT` for a `NULL` result;
4. map another validation failure to `GRAPH_BFS_INVALID_RESULT`;
5. reject an inactive destination with `GRAPH_BFS_OUT_OF_RANGE`;
6. report `GRAPH_BFS_UNREACHABLE` for an undiscovered destination;
7. follow predecessors backward into a temporary array;
8. reject more than `vertex_count` entries;
9. stop at the source;
10. reverse into a sentinel-filled temporary path; and
11. commit.

A **path** is a route that does not repeat a vertex. It includes source and
destination. The source-to-source path has count 1 and zero hops.

The result validator checks stored relationships but receives no graph. A
test with the graph must still verify that every consecutive path edge
exists.

## 7. TODO 3 — Adjacency-list BFS

Complete:

```c
GraphBfsStatus graph_bfs_list(
    const GraphAdjList *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result);
```

Use the same decision order, Queue state, candidate, discovery timing, and
commit rule as matrix BFS. Replace only how outgoing neighbors are read:

```text
for index from 0 through neighbors[vertex].size - 1:
    neighbor = neighbors[vertex].data[index]
```

The supplied lists are already strictly ascending. Equivalent matrix and
list graphs must produce equal named result values.

## 8. Build the canonical checkpoint

Create both directed representations with the ten edges in this order:

```text
0 -> 1   0 -> 2   1 -> 3   1 -> 4   2 -> 4
2 -> 5   3 -> 6   4 -> 6   5 -> 4   6 -> 1
```

Vertex 7 has no edge.

Required result from source 0:

```text
visit_count: 7
visit_order: 0,1,2,3,4,5,6
discovered:  true,true,true,true,true,true,true,false
distance:    0,1,1,2,2,2,3,16
predecessor: 16,0,0,1,1,2,3,16
```

Required paths:

```text
destination 6: 0,1,3,6
destination 0: 0
destination 7: GRAPH_BFS_UNREACHABLE; old path unchanged
```

Check every named matrix/list result field. Do not make complete-struct
comparison the meaning of equality because a C compiler may add unused
storage between fields.

## 9. Check the Queue boundary

The canonical maximum pending count is 3.

- Limit 3 succeeds.
- Limit 2 fails while processing vertex 1.
- Vertex 2 is already waiting.
- Enqueueing 3 fills the selected limit.
- Enqueueing 4 reports `GRAPH_BFS_LIMIT`.
- Caller output remains completely unchanged.

A valid nonempty graph at limit 0 fails when the source cannot be enqueued.
A requested limit above 16 also reports `GRAPH_BFS_LIMIT`.

## 10. Use and clean up the supplied adjacency list

A **dynamic array** uses adjacent memory slots in an **allocation**, a block
obtained while a program runs. `GraphAdjList` owns each non-NULL neighbor
row allocation.

Use supplied operations to initialize, add, query, remove, validate, and
destroy. Rows remain sorted and duplicate-free. An undirected add updates
both directions or neither. Students do not implement growth or cleanup.

Begin with:

```c
GraphAdjList list = {0};
```

Initialization accepts only an all-zero or previously destroyed object.
Passing uninitialized storage breaks the function's required starting
condition.

Call `graph_adj_list_destroy` on every path after successful initialization.
Do not shallow-copy a live list: the copied pointers would claim the same
allocations.

## 11. Run supplied tests

From the `code` directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter compiles but fails behavior tests until all TODOs are complete.
Do not weaken a supplied test.

When supported:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

A **compiler** translates C into a runnable program. A **warning** identifies
code that may be mistaken. A **sanitizer** detects some invalid memory or
arithmetic operations while code runs.

## 12. Complete exactly three student tests

### Test 1 — Cycle and merge state

Use a small graph containing a merge and a cycle. Check exact visit order,
all discovered values, distances, predecessors, and absence of duplicates.

### Test 2 — Reachable, source, and unreachable paths

Check one multi-hop path, the one-vertex source path, and an unreachable
result that preserves a previously marked `GraphBfsPath`.

### Test 3 — Representation equality and Queue boundary

Build equivalent matrix/list graphs. Compare every named result value, then
use one too-small Queue limit and prove complete output preservation.

State in a comment what each test adds beyond supplied examples.

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

## 13. Trace disconnected input on paper

For the undirected graph:

```text
{0,1}  {1,2}  {3,4}  {4,5}; vertex 6 isolated
```

scan possible roots upward while keeping one shared discovered array.
Record forest order, roots, and connected-component count. Forest code is
not a TODO.

For directed input, the same outer idea is only a traversal forest. Do not
claim that its trees are weakly or strongly connected components.

## 14. Complete the bounded autopsy

Complete `student/graph_bfs_autopsy.md` before running:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The standalone Queue has eight checked slots and the graph has five
synthetic vertices. Preserve its bounds and checked maximum number of
removals. Identify the first duplicate scheduling decision, smallest
repair, and one regression test.

A **regression test** is retained so a repaired defect does not return.

## 15. State costs and safe meaning

Let `V` mean vertices currently in the graph and `E` mean edges.

```text
matrix public BFS:          O(V²)
adjacency-list public BFS:  O(V+E)
BFS auxiliary space:        O(V)
path reconstruction:        O(V)
```

Construction cost is separate. A matrix-to-list conversion that scans all
cells costs `O(V²)`.

This synthetic result proves only facts about inserted edges. Minimum hops
does not prove real communication, permission, flaw presence, successful
takeover, probability, or danger. Do not scan a live system.

## Completion checklist

- [ ] The three numbered starter TODOs are complete.
- [ ] Discovery follows every first successful enqueue.
- [ ] Recording occurs on dequeue.
- [ ] Distances and predecessors are never overwritten.
- [ ] All 16 output slots receive their required value or sentinel.
- [ ] Matrix and list canonical results match by named fields.
- [ ] Limit 3 succeeds and limit 2 preserves output.
- [ ] Paths to 6, 0, and 7 satisfy the contract.
- [ ] Every initialized adjacency list is destroyed.
- [ ] Exactly three student tests state distinct claims.
- [ ] The paper forest uses precise undirected language.
- [ ] The autopsy preserves its safety guards.
