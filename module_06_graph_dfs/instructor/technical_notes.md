# Instructor Technical Notes — Module 6 Graph DFS

## Source-of-truth contract

The public headers, not slides or prose summaries, are the implementation
source of truth. Module 6 reuses Module 3’s bounded adjacency-matrix graph:

```c
#define GRAPH_MAX_VERTICES 16U

typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;
```

An **active vertex** has an index from zero through
`graph->vertex_count - 1`. The graph remains simple and unweighted:
self-loops and repeated edges are rejected; an undirected matrix must be
symmetric.

The DFS result is:

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

Only `vertices[0]` through `vertices[count - 1]` have public meaning. Every
vertex reachable from the selected source appears exactly once. The result
does not retain the internal seen array.

The exact status order and spelling are:

```c
typedef enum {
    GRAPH_DFS_OK = 0,
    GRAPH_DFS_INVALID_ARGUMENT,
    GRAPH_DFS_OUT_OF_RANGE,
    GRAPH_DFS_INVALID_GRAPH,
    GRAPH_DFS_REQUIRES_UNDIRECTED,
    GRAPH_DFS_LIMIT,
    GRAPH_DFS_ALLOCATION
} GraphDfsStatus;
```

The exact public declarations are:

```c
GraphDfsStatus graph_dfs_recursive(
    const Graph *graph,
    size_t start_vertex,
    GraphDfsOrder *out_order);

GraphDfsStatus graph_dfs_iterative(
    const Graph *graph,
    size_t start_vertex,
    size_t stack_limit,
    GraphDfsOrder *out_order);

GraphDfsStatus graph_count_connected_components(
    const Graph *graph,
    size_t *out_component_count);

const char *graph_dfs_status_name(GraphDfsStatus status);
```

Do not add a public visited-array or reachability-query function to student
requirements. A target is reachable exactly when its index occurs in a
successful `GraphDfsOrder`.

## Validation and status mapping

Every DFS public function validates the complete active graph before doing
algorithm work. Map Module 3 validation results as follows:

| Module 3 result | DFS result |
|---|---|
| `GRAPH_OK` | Continue |
| `GRAPH_ERR_INVALID_ARGUMENT` | `GRAPH_DFS_INVALID_ARGUMENT` |
| Any other graph-validation failure, including invalid stored vertex count, kind, diagonal, or symmetry | `GRAPH_DFS_INVALID_GRAPH` |

After successful validation, traversal requires
`start_vertex < graph->vertex_count`. Only failure of this source-index
check returns `GRAPH_DFS_OUT_OF_RANGE`. An invalid stored
`graph->vertex_count` is a malformed graph and maps to
`GRAPH_DFS_INVALID_GRAPH`. An empty graph therefore has no valid source.

Component counting has no source index. It accepts an empty undirected graph
and writes zero on success. A valid directed graph returns
`GRAPH_DFS_REQUIRES_UNDIRECTED` without changing its output.

The standalone self-loop test should verify the Module 3 constructor
contract:

```text
graph_add_edge(graph, v, v) → GRAPH_ERR_SELF_LOOP
```

A manually corrupted diagonal presented to a DFS operation is instead a
whole-graph validation failure:

```text
GRAPH_DFS_INVALID_GRAPH
```

These checks are complementary, not contradictory.

## Internal seen invariant

The implementation uses one Boolean entry for each possible vertex. Define
its meaning precisely:

> `seen[v] == true` means active vertex `v` has been successfully scheduled
> or has already been processed.

Required invariant during a successful traversal:

1. every vertex in the result is active and has `seen[v] == true`;
2. every vertex waiting in the explicit Stack has `seen[v] == true`;
3. no vertex is entered recursively or pushed more than once;
4. `order.count <= graph->vertex_count <= GRAPH_MAX_VERTICES`; and
5. an edge to a seen destination creates no new call or push.

“Seen” and “recorded” coincide at recursive function entry. They differ
temporarily in iterative DFS because a seen vertex may still be waiting in
the Stack.

## Recursive DFS

The public function first validates its arguments and graph, then builds a
local zeroed candidate. Its helper follows:

```text
visit(v):
    seen[v] = true
    append v
    for neighbor = 0 through V - 1:
        if adjacency[v][neighbor] and not seen[neighbor]:
            visit(neighbor)
```

The public start is active and unseen when the helper is first called. Each
recursive child call is made only for an active unseen out-neighbor. Marking
occurs before scanning that vertex’s row.

The canonical directed fixture is:

```text
0 → 1   0 → 2   1 → 3   2 → 3   3 → 4   4 → 1
5 is isolated
```

Ascending scanning gives:

```text
0, 1, 3, 4, 2
```

At the deepest cycle point, active calls are:

```text
0, 1, 3, 4
```

The edge `4 → 1` is ignored because 1 is already seen. After those calls
return, the call for 0 reaches 2. Its edge `2 → 3` is also ignored.

The recursive stopping condition differs from tree DFS. There is no `NULL`
child. A call returns after its complete matrix row contains no unseen
out-neighbor.

The candidate order is copied to `*out_order` only after the helper
completes. Although a validated 16-vertex graph cannot overflow the fixed
order, candidate-and-commit keeps the failure-atomic contract explicit.

## Typed vertex Stack

`vertex_stack.h` defines:

```c
#define VERTEX_STACK_MAX_LIMIT GRAPH_MAX_VERTICES

typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
    size_t limit;
} VertexStack;

typedef enum {
    VERTEX_STACK_OK = 0,
    VERTEX_STACK_INVALID_ARGUMENT,
    VERTEX_STACK_LIMIT,
    VERTEX_STACK_UNDERFLOW,
    VERTEX_STACK_ALLOCATION,
    VERTEX_STACK_INVALID_STATE
} VertexStackStatus;
```

Exact operations:

```c
VertexStackStatus vertex_stack_init(
    VertexStack *stack,
    size_t limit);

VertexStackStatus vertex_stack_validate(
    const VertexStack *stack);

VertexStackStatus vertex_stack_push(
    VertexStack *stack,
    size_t vertex);

VertexStackStatus vertex_stack_pop(
    VertexStack *stack,
    size_t *out_vertex);

void vertex_stack_destroy(VertexStack *stack);

const char *vertex_stack_status_name(VertexStackStatus status);
```

Testing builds also expose:

```c
void vertex_stack_test_fail_next_allocation(void);
```

The Stack owns only its growable `size_t` array. Its invariant is:

1. `limit <= 16`;
2. `size <= capacity`;
3. `capacity <= limit`;
4. `capacity == 0` exactly when `data == NULL`; and
5. every occupied value is a possible vertex ID from 0 through 15.

Capacity grows lazily:

```text
0 → 4 → 8 → 16
```

Growth is clipped to `limit`. A zero limit is valid. Push at the limit
returns `VERTEX_STACK_LIMIT`. Push of a value at least 16 returns
`VERTEX_STACK_INVALID_ARGUMENT`. Allocation failure preserves the complete
Stack. Empty pop returns `VERTEX_STACK_UNDERFLOW` and preserves its output.
Destroy releases the array and resets every field.

## Iterative DFS

The iterative algorithm is:

```text
initialize Stack with stack_limit
push start
if push succeeded:
    mark start seen
while pop succeeds:
    append popped vertex
    for neighbor from V - 1 down through 0:
        if adjacency[vertex][neighbor] and not seen[neighbor]:
            push neighbor
            if push succeeded:
                mark neighbor seen
destroy Stack
commit candidate only on success
```

Marking after successful push is essential. Marking before a failed push
would make internal state claim that an unscheduled vertex was handled.
Candidate-and-commit still protects the public result, but the algorithmic
invariant should remain correct on every path.

Descending scanning does not promise that iterative order equals recursive
ascending order for every graph. It makes a lower-index neighbor the next
pop when no cross-link or already scheduled work changes the frontier.
Correctness requires the documented iterative rule and the same reachable
set, not universal order equality.

Canonical bottom-to-top states:

```text
initial:                 0
after visiting 0:        2, 1
after visiting 1:        2, 3
after visiting 3:        2, 4
after visiting 4:        2
after visiting 2:        empty
```

Canonical visit order:

```text
0, 1, 3, 4, 2
```

The maximum simultaneous Stack size is two. Therefore:

- `stack_limit == 2` succeeds;
- `stack_limit == 1` returns `GRAPH_DFS_LIMIT`; and
- `stack_limit > 16` returns `GRAPH_DFS_LIMIT`.

Map Stack results:

| Stack result | DFS meaning |
|---|---|
| `VERTEX_STACK_OK` | Continue |
| `VERTEX_STACK_UNDERFLOW` during the pop loop | Normal completion |
| `VERTEX_STACK_LIMIT` | `GRAPH_DFS_LIMIT` |
| `VERTEX_STACK_ALLOCATION` | `GRAPH_DFS_ALLOCATION` |
| Invalid argument/state or another impossible internal error | `GRAPH_DFS_INVALID_ARGUMENT` |

After successful initialization, every return path calls
`vertex_stack_destroy`. Only a completely successful candidate is copied to
the caller.

## Connected-component counting

A **connected component** is a largest set in an undirected graph in which
each vertex can reach every other by an undirected path.

The component operation:

```text
validate graph
require GRAPH_UNDIRECTED
clear one seen array
candidate_count = 0
for v = 0 through V - 1:
    if not seen[v]:
        candidate_count += 1
        recursively mark every vertex reachable from v
commit candidate_count
```

Reuse one seen array for the complete sweep. Clearing it for every start
would count overlapping routes as new components.

For the separate undirected fixture:

```text
{0,1}, {0,2}, {1,3}, {2,3}, {3,4}, {4,1}
```

the ascending recursive sweep is:

```text
0, 1, 3, 2, 4 | 5
```

and the count is 2. The vertical bar is an explanatory boundary, not part
of a public output.

## Failure atomicity

| Operation | Failure | Caller-visible preservation |
|---|---|---|
| Recursive DFS | null pointer, invalid graph, invalid source | Complete `GraphDfsOrder` unchanged |
| Iterative DFS | null pointer, invalid graph/source, invalid limit, Stack limit/allocation | Complete `GraphDfsOrder` unchanged; temporary Stack destroyed |
| Component count | null pointer, invalid graph, directed kind | Output count unchanged |
| Vertex-Stack initialization | invalid pointer or limit | Stack object unchanged |
| Vertex-Stack push | invalid state/value, limit, allocation | Stack unchanged |
| Vertex-Stack pop | invalid state/output or underflow | Stack and output unchanged |

A DFS or component operation never changes the supplied `Graph`, on success
or failure. The `const Graph *` parameter permits inspection only.

A strong test initializes every byte of a `GraphDfsOrder` to a known pattern,
copies it, triggers failure, and compares the complete object byte for byte.
Checking only `count` is insufficient.

## Complexity

Let:

- `V` be the active vertex count;
- `E` be the edge count; and
- `R` be the number of vertices reachable from one selected source.

| Operation | Time | Auxiliary space | Reason |
|---|---:|---:|---|
| Public one-source matrix recursive DFS | `O(V²)` | `O(V)` | Full validation scans the active matrix; the traversal core then scans `V` cells for each of `R` reached vertices |
| Public one-source matrix iterative DFS | `O(V²)` | `O(V)` | Full validation is `O(V²)`; after it, each reached vertex scans one row and is pushed once |
| Matrix connected-component sweep | `O(V²)` | `O(V)` | Every vertex is reached once and every active row is scanned |
| Adjacency-list DFS or full sweep | `O(V + E)` | `O(V)` | It examines stored neighbors rather than absent matrix cells |

The public order is output, not auxiliary working space. The seen array,
recursive calls, and explicit Stack are auxiliary.

If graph validity is already established outside the timed traversal, the
one-source matrix traversal core is `O(RV)`, where `R` is the reached vertex
count. The published API deliberately performs its own full `O(V²)`
validation, so the complete public call remains `O(V²)`.

For an undirected adjacency list, each edge normally appears in two neighbor
lists. That constant factor does not change `O(V + E)`.

The matrix itself reserves fixed `16 × 16` storage in this package. When
describing growth beyond the fixed teaching bound, a general `V × V`
adjacency matrix uses `O(V²)` representation space.

## Status-name behavior

`graph_dfs_status_name` returns:

| Status | Exact text |
|---|---|
| `GRAPH_DFS_OK` | `ok` |
| `GRAPH_DFS_INVALID_ARGUMENT` | `invalid argument` |
| `GRAPH_DFS_OUT_OF_RANGE` | `start vertex out of range` |
| `GRAPH_DFS_INVALID_GRAPH` | `graph does not satisfy required representation rules` |
| `GRAPH_DFS_REQUIRES_UNDIRECTED` | `operation requires an undirected graph` |
| `GRAPH_DFS_LIMIT` | `vertex Stack limit reached or requested limit too large` |
| `GRAPH_DFS_ALLOCATION` | `allocation failed` |
| Unknown value | `unknown GraphDfsStatus` |

The vertex Stack uses its separate `VertexStackStatus` names. Its exact
texts are `ok`, `invalid argument`,
`Stack limit reached or requested limit too large`, `Stack is empty`,
`allocation failed`, `Stack representation is invalid`, and
`unknown VertexStackStatus`. Do not expose a Stack status directly from a
public DFS operation.

## Starter assignment boundary

Keep responsibilities explicit:

- supplied retrieval support: Module 3 graph operations and validation;
- supplied infrastructure: the complete typed vertex-ID Stack;
- TODO 1: complete the private `recursive_visit` helper; the supplied public
  `graph_dfs_recursive` wrapper validates, creates local state, calls the
  helper, and commits its candidate;
- TODO 2: complete `graph_dfs_iterative` after its supplied validation and
  Stack initialization;
- TODO 3: complete `graph_count_connected_components` after its supplied
  request check;
- student evidence: three tests covering traversal/reachability,
  failure-output preservation, and connected components; and
- private verification: `solution/graph_dfs.c` and
  `tests/test_extension.c`.

Do not ask students to redesign the adjacency matrix or Stack during this
module. The learning target is visited-aware graph traversal.

## Test matrix

The full verification matrix should include:

1. exact canonical recursive order `0,1,3,4,2`;
2. exact canonical iterative order and Stack-limit behavior;
3. source 5 gives `5`;
4. source 2 gives `2,3,4,1`;
5. cycles and converging paths produce no duplicate;
6. directed and undirected one-source traversal;
7. invalid source and null output preserve a nonzero sentinel order;
8. malformed vertex count, kind, diagonal, and undirected symmetry;
9. iterative limits zero, one, exact two, 16, and above 16;
10. forced first allocation and growth allocation failures;
11. vertex-Stack invariant, lazy/clipped growth, underflow, invalid value,
    allocation failure, and output preservation;
12. connected counts for empty, one vertex, canonical two components, all
    isolated, and one connected graph;
13. directed component rejection with unchanged count;
14. maximum 16-vertex paths/cycles;
15. status-name coverage including unknown values; and
16. standalone Module 3 self-loop rejection.

Testing allocation hooks are one-shot and available only under
`GRAPH_DFS_TESTING`. They are deterministic teaching seams, not production
configuration.

## Autopsy requirements

The faulty program is bounded to eight entered calls. Never ask students to
run uncontrolled recursive code on a cycle. Its exact trace is:

```text
enter 0
enter 1
enter 2
enter 0
enter 1
enter 2
enter 0
enter 1
STOP: safety budget exhausted before DFS finished.
```

The defect is the placement of `seen[vertex] = true` after the recursive
neighbor loop. The first call for vertex 0 is still unmarked when vertex 2
examines `2 → 0`, so the cycle begins again.

Move the mark before the neighbor loop. The corrected output is
`0,1,2`, with each vertex entered once. A regression test should check the
exact count, order, and lack of duplicates. The call budget is a diagnostic
guard only; increasing it is not a repair.

## Modeling and security boundary

The graph records only the relationships explicitly inserted. Reachability
in this model does not prove:

- that a network packet can travel on a real route;
- that authentication or authorization succeeds;
- that a service contains a vulnerability;
- that a vulnerability is exploitable;
- that an attack occurred; or
- that the modeled policy is correct or current.

Do not adapt the exercise into live scanning. Use instructor-created or
student-created synthetic graphs only.

## Instructor verification commands

From `module_06_graph_dfs/code` on Windows:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target solution -Extensions
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target self-loop
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make equivalents:

```text
make solution-core
make solution-extension
make solution-self-loop
make autopsy
```

Use warning-enabled builds. Add the sanitizer option when supported.
The unfinished starter is expected to compile and fail behavioral tests
until its three TODOs are completed.

## Instructor implementation audit

- [ ] `GRAPH_MAX_VERTICES` remains 16.
- [ ] Public status order and function names match exactly.
- [ ] Every traversal validates the graph and source before work.
- [ ] Recursive DFS marks and records before scanning ascending neighbors.
- [ ] The cycle edge `4 → 1` creates no call.
- [ ] Iterative DFS scans descending and records on pop.
- [ ] Iterative seen marks occur only after successful pushes.
- [ ] No vertex is pushed or recorded twice.
- [ ] Limit 2 succeeds and limit 1 fails on the canonical graph.
- [ ] Every initialized Stack is destroyed on every path.
- [ ] Public outputs are committed only on full success.
- [ ] Component count accepts only undirected graphs.
- [ ] One seen array is reused for the full component sweep.
- [ ] Empty undirected graph reports zero components.
- [ ] Matrix and adjacency-list costs are stated correctly.
- [ ] The self-loop test checks the Module 3 API independently.
- [ ] The autopsy is bounded.
- [ ] No example overstates synthetic policy reachability.
