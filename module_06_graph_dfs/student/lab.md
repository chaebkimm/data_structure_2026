# Lab — Follow Routes Without Repeating Vertices

## Purpose

You will complete exactly three implementation tasks:

1. the private recursive visit used by recursive depth-first search;
2. iterative depth-first search; and
3. undirected connected-component counting.

You will also write exactly three student tests, one in each required
category later in this guide.

## 1. Read the graph

A **graph** stores items and direct relationships. Each item is a
**vertex**. Each direct relationship is an **edge**. A **directed edge**
works in one direction.

The course graph has these directed edges:

```text
0 → 1   0 → 2   1 → 3
2 → 3   3 → 4   4 → 1
```

Equivalent outgoing-neighbor lists:

```text
0:[1,2]  1:[3]  2:[3]  3:[4]  4:[1]  5:[]
```

In words, 0 leads to 1 and 2; 1 and 2 each lead to 3; 3 leads to 4; 4 leads
back to 1; and 5 has no edge.

An **out-neighbor** is the destination of an edge leaving the current
vertex. A **cycle** is a route that returns to an earlier vertex. The edges
`1 → 3 → 4 → 1` form a cycle.

## 2. Apply the shared search rule

**Depth-first search (DFS)** follows one available route deeply before
returning to an unfinished choice. Its **source** is the starting vertex. A
vertex is **reachable** when a directed route leads to it from that source.

A **Boolean** is a `true` or `false` value. A **visited array** stores one
Boolean for each vertex. In this lab, marked means discovered and scheduled.
To **record** a vertex means to append its number to the output.

Use these exact rules:

- never schedule a marked vertex;
- recursive DFS marks and records on entry;
- recursive DFS checks destination numbers from low to high;
- iterative DFS records on pop;
- iterative DFS checks destination numbers from high to low; and
- iterative DFS marks a destination only after its push succeeds.

From source 0, both implementations record:

```text
0, 1, 3, 4, 2
```

Vertex 5 is not reachable from 0.

## 3. Read the public output

A **struct** is a C type grouping named values called fields. `size_t` is a
nonnegative whole-number type for counts and indexes.

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

`GraphDfsOrder` stores at most 16 recorded vertex numbers. `count` says how
many positions contain output.

An **API** is the public types and functions other code may use. A
**contract** states what a function accepts, changes, reports, and
preserves.

```c
GraphDfsStatus graph_dfs_recursive(
    const Graph *graph,
    size_t start_vertex,
    GraphDfsOrder *out_order
);

GraphDfsStatus graph_dfs_iterative(
    const Graph *graph,
    size_t start_vertex,
    size_t stack_limit,
    GraphDfsOrder *out_order
);

GraphDfsStatus graph_count_connected_components(
    const Graph *graph,
    size_t *out_component_count
);

const char *graph_dfs_status_name(GraphDfsStatus status);
```

A **pointer** stores a memory address. `const Graph *` permits inspection but
not change through that pointer. A **caller** is code that requests a
function. An **output parameter** is caller-provided storage in which a
function writes an answer.

## 4. Read the status meanings

A **status code** is a named result. `NULL` is C's pointer value meaning
“points to no object.” An **allocation** is storage requested while a
program runs.

```text
GRAPH_DFS_OK                    success
GRAPH_DFS_INVALID_ARGUMENT      a required pointer is NULL
GRAPH_DFS_OUT_OF_RANGE          source is not an active vertex
GRAPH_DFS_INVALID_GRAPH         graph rules are broken
GRAPH_DFS_REQUIRES_UNDIRECTED   component input is directed
GRAPH_DFS_LIMIT                 Stack limit, or maximum, cannot be met
GRAPH_DFS_ALLOCATION            temporary Stack storage unavailable
```

Check required pointers first. Then validate the entire active stored graph
with the supplied Module 3 operation before checking a source or Stack
limit.
**Validation** means checking whether all stored graph rules hold.

Every caller output changes only on `GRAPH_DFS_OK`. **Failure preservation**
means any failed operation leaves the caller's complete old output
unchanged. Build results in local variables, then copy them to caller output
only after complete success.

## TODO 1 — `recursive_visit`

**Recursion** occurs when a function calls itself. A **call frame** stores
information for one active call. The **runtime call stack** is bookkeeping
commonly used by C for active call frames.

The supplied `graph_dfs_recursive` wrapper checks pointers, validates the
graph, checks the source, prepares local output, and commits that output only
after success. A **wrapper** is a function that prepares and checks work
around a smaller helper.

```text
recursive helper at u:
    mark u
    append u to the local output
    for v from 0 through vertex_count - 1:
        if edge u → v exists and v is unmarked:
            call the helper at v
    return
```

A **private helper** is used only inside its implementation file. Complete
the existing private `recursive_visit` helper used by that wrapper.

The supplied wrapper must continue to:

1. reject a required `NULL` pointer;
2. validate the entire active stored graph;
3. reject an inactive source;
4. begin with every visited value false; and
5. commit `out_order` only after success.

Your helper must:

1. mark and record its current vertex;
2. scan outgoing destinations in increasing order;
3. call itself only for an unmarked destination; and
4. return to its caller after the row is finished.

An **isolated vertex** has no edge. Starting at isolated vertex 5 succeeds
with the one-vertex order `{5}`. An empty graph has no active source, so
source 0 reports
`GRAPH_DFS_OUT_OF_RANGE`.

## TODO 2 — `graph_dfs_iterative`

An **iterative algorithm** uses a loop instead of recursive calls. A
**loop** repeats instructions while its condition holds. An explicit
**Stack** is a last-in, first-out collection operated by the program.
`push` adds the newest item. `pop` removes it. **Underflow** means a pop was
requested from an empty Stack.

The supplied `VertexStack` stores `size_t` vertex numbers. Use its public
operations:

```c
vertex_stack_init
vertex_stack_push
vertex_stack_pop
vertex_stack_destroy
```

Do not inspect or change the Stack's `data`, `size`, `capacity`, or `limit`
fields inside DFS.

The Stack owns its temporary allocation, meaning it is responsible for that
memory. To destroy the Stack means to release that memory and reset its
fields.

Complete `graph_dfs_iterative`.

Required behavior:

1. perform the same pointer, validation, and source checks;
2. initialize the Stack with `stack_limit`;
3. push the source and mark it only after the push succeeds;
4. pop and record one vertex;
5. scan possible destinations from high to low;
6. push each unmarked destination and mark it only after success;
7. treat `VERTEX_STACK_UNDERFLOW` as normal completion;
8. map Stack limit and allocation failures to the matching graph-DFS
   statuses;
9. destroy the Stack after successful initialization on every exit; and
10. commit `out_order` only after complete success.

The Stack limit may be 0 through 16. A larger request reports
`GRAPH_DFS_LIMIT`. A nonempty traversal with limit 0 also reports
`GRAPH_DFS_LIMIT`.

For the course graph, list Stack contents bottom to top:

```text
start:              0
after processing 0: 2, 1
after processing 1: 2, 3
after processing 3: 2, 4
after processing 4: 2
after processing 2: empty
```

Limit 2 succeeds. Limit 1 fails while scheduling vertex 0's two choices.
The failed destination must not be marked, the Stack must be destroyed, and
the caller's old output must remain unchanged.

## TODO 3 — `graph_count_connected_components`

An **undirected edge** connects both ways. A **connected component** is one
separate group in an undirected graph whose vertices have routes to one
another. An isolated vertex is a component of one.

Complete `graph_count_connected_components`.

Required behavior:

1. reject a required `NULL` pointer;
2. validate the entire active stored graph;
3. reject a directed graph with `GRAPH_DFS_REQUIRES_UNDIRECTED`;
4. begin with every visited value false;
5. scan possible starts from 0 upward;
6. when a start is unmarked, add one component and mark its whole reachable
   group; and
7. commit the count only after success.

Use one visited array across the entire outer scan. Resetting it for each
start would count the same group repeatedly.

The separate undirected practice graph uses the same six pairs of vertex
numbers as the course directed graph, but each relationship connects both
ways:

```text
{0,1}  {0,2}  {1,3}  {2,3}  {3,4}  {4,1}
```

Vertices 0 through 4 form one component. Isolated vertex 5 forms another.
The count is 2. An empty undirected graph succeeds with count 0.

## Checkpoint 4 — Run supplied tests

From the `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

The starter builds but initially fails because the three TODO operations are
unfinished. Fix the earliest failed requirement without weakening a test.

Visible tests cover:

- a single vertex;
- a cycle;
- the course directed graph;
- source 5 and an inactive source;
- Stack limits 2, 1, 0, and above 16;
- allocation failure and unchanged output;
- rejection of a graph that breaks its stored rules;
- directed component rejection;
- an isolated component; and
- an empty undirected graph.

A **compiler** translates C into a runnable program. When your compiler
supports **sanitizers**, extra checks for invalid memory operations, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -Sanitize
```

## Checkpoint 5 — Write exactly three tests

Complete `code/tests/test_student.c`. A **test** supplies input and checks an
expected result. Add one comment explaining what each test contributes.

Your exact categories are:

1. traversal order or reachability, including a cycle or disconnected case;
2. a failure that preserves the caller's old output; and
3. undirected component count, including an isolate or empty graph.

Run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make self-loop
make autopsy
```

## Checkpoint 6 — Autopsy

Complete `student/graph_dfs_autopsy.md` before running:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The isolated faulty program has a safe step budget, a fixed maximum number
of entries, so it stops instead of exhausting the runtime call stack.
Identify the earliest state or check decision that causes repeated entry,
the smallest fix, and one regression test. A **regression test** is kept to
prevent a known defect from returning.

## Cost

**Time complexity** describes how work grows. **Big-O notation** writes a
growth pattern as `O(...)`. Let `V` be vertex count and `E` be edge count.

The adjacency matrix scans `V` possible destinations for every vertex, so a
full traversal takes `O(V²)` time. An **adjacency list**, one stored neighbor
list per vertex, supports `O(V+E)` full traversal.

**Auxiliary space** is temporary working storage separate from graph and
output. The visited array plus recursive calls or explicit Stack uses
`O(V)` auxiliary space.

## Safe scope

The service graph is synthetic, meaning invented for practice. A recorded
route proves only that the route exists in the invented graph. It does not
prove that real communication occurred or real access is possible.

Do not connect this lab to real-use services, private data, or a live
network. Use only small graphs created for the course.

## Completion criteria

- exactly the three required TODO functions satisfy their contract;
- recursive and iterative course-example orders are exact;
- cycles terminate and vertices are not repeated;
- every failure preserves caller output;
- iterative DFS marks only after successful pushes and always cleans up;
- component counting accepts only valid undirected graphs;
- exactly three required student-test categories pass;
- the autopsy identifies the earliest decision causing repeated entry; and
- warning-enabled compiler or instructor-run build evidence is saved.
