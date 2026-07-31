# Stage B — Formal Graph-Visiting Methods

Open this file only after preserving the Stage A inquiry.

## 1. Name the task

A **graph** stores items and direct relationships. A **vertex** is one item.
A **directed edge** works in one direction. A **route** is a sequence that
follows stated edges.

An **algorithm** is a precise, repeatable set of steps. **Depth-first search
(DFS)** is an algorithm that follows one available route deeply before
returning to an unfinished choice.

A **source** is the chosen starting vertex. A vertex is **reachable** when a
route of directed edges leads to it from the source. The source is reachable
from itself without using an edge.

An **out-neighbor** is the destination of an edge leaving the current
vertex. Out-neighbors play the role that children played in tree DFS, but a
graph vertex may have several incoming routes or a route back to an earlier
vertex.

## 2. Add visited state

A **Boolean** value is either `true` or `false`. A **visited array** stores
one Boolean for every vertex.

In this module, `visited[v] == true` has one exact meaning:

> Vertex `v` has been discovered and scheduled for processing.

To **discover** a vertex means to reach it for the first time. To
**schedule** it means to arrange for its work to occur. To **record** a
vertex means to append its number to the output.

Visited and recorded are not synonyms. A scheduled vertex may still be
waiting. Marking means changing its visited value from `false` to `true`.
A recursive call marks its vertex immediately on entry, before following an
outgoing edge. Iterative DFS marks a vertex immediately after its Stack push
succeeds. An edge to an already marked vertex is skipped.

This rule prevents the same vertex from being scheduled more than once. It
also stops a **cycle**, a directed route that returns to an earlier vertex,
from causing endless work.

## 3. Use a small reveal graph

This graph is different from the Cognitive Pause graph. It has four
vertices and these directed edges:

```text
0 → 1
1 → 2
2 → 0
0 → 3
```

Equivalent outgoing-neighbor lists:

```text
0:[1, 3]   1:[2]   2:[0]   3:[]
```

In words, 0 leads to 1 and 3; 1 leads to 2; 2 leads back to 0; and 3 has no
outgoing edge.

The course **neighbor-order rule** states which choice comes first.
Recursive DFS checks vertex numbers from lower to higher. This makes small
examples reproducible.

## 4. Recursive DFS

A **function** is a named group of instructions. **Recursion** occurs when a
function calls itself. One request for a function to run is a **function
call**. A **call frame** is saved information for one active call. Active
means started but not finished.

```text
recursive DFS at vertex u:
    mark u
    record u
    for each possible vertex v, from low to high:
        if edge u → v exists and v is not marked:
            continue recursively at v
    return when no unmarked out-neighbor remains
```

Starting at 0 in the reveal graph:

```text
record 0
record 1
record 2
skip 2 → 0 because 0 is marked
return to 0
record 3
```

The output is `0, 1, 2, 3`. A **pointer** stores a memory address. `NULL` is
C's pointer value meaning “points to no object.” Unlike tree DFS, there is no
`NULL` child position. An already marked destination gets no new call, and a
call returns after checking all possible destinations.

## 5. Iterative DFS

An **iterative algorithm** repeats steps with a loop instead of recursive
calls. A **loop** repeats instructions while its condition holds. A
**Stack** is a last-in, first-out collection: the newest stored item is
removed first. `push` adds one item at the top. `pop` removes the top item.

An **explicit vertex-ID Stack** is a Stack directly operated by the program
whose items are vertex numbers. It is not the runtime call stack that a C
implementation commonly uses for function-call information.

The **frontier** is the collection of discovered vertices still waiting to
be processed. Here, the explicit Stack stores the frontier.

```text
push the source; if the push succeeds, mark the source
while the Stack is not empty:
    pop u
    record u
    check possible destinations from high to low
    for each existing edge u → v whose v is not marked:
        push v
        if the push succeeds, mark v
```

The decreasing check order makes the lower-numbered destination newer, so
it leaves the Stack first. Stack items below are listed bottom to top.

| Completed processing | Visited vertices | Frontier Stack, bottom to top | Output |
|---|---|---|---|
| none | `{0}` | `0` | empty |
| 0 | `{0, 1, 3}` | `3, 1` | `0` |
| 1 | `{0, 1, 2, 3}` | `3, 2` | `0, 1` |
| 2 | `{0, 1, 2, 3}` | `3` | `0, 1, 2` |
| 3 | `{0, 1, 2, 3}` | empty | `0, 1, 2, 3` |

Linear equivalent:

1. Initially, 0 is marked and waiting; output is empty.
2. After processing 0, vertices 0, 1, and 3 are marked; the Stack is 3 then
   1 from bottom to top; output is 0.
3. After processing 1, all four vertices are marked; the Stack is 3 then 2;
   output is 0, 1.
4. After processing 2, only 3 waits; output is 0, 1, 2.
5. After processing 3, the Stack is empty; output is 0, 1, 2, 3.

The visited collection may contain both recorded vertices and frontier
vertices. For example, vertex 3 is marked before it is recorded.

## 6. Read the output and public operations

A **struct** is a C type that groups named values called fields. `size_t` is
a nonnegative whole-number type used for counts and indexes. An **array** is
a numbered row of values.

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

`GraphDfsOrder` stores at most 16 recorded vertex numbers. Its `count` says
how many array positions contain output.

A **public operation** is a function intended for other program parts to
call. A **caller** is the code requesting a function. An **output
parameter** is caller-provided storage in which a function writes an answer.

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

`Graph` is the Module 3 type that stores an **adjacency matrix**, a
row-and-column table of possible edges. `const Graph *` permits inspection
but not change through that pointer. An **active vertex** is included in the
graph's current vertex count. Traversal starts at one active vertex.

An **undirected edge** connects both ways. A **connected component** is one
separate group in an undirected graph whose vertices have routes to one
another. Component counting is defined only for a valid undirected graph.

Every caller output changes only after complete success. A failed operation
leaves the caller's previous output unchanged.

A **status code** is a named result reporting success or one kind of
failure. The exact values appear in this order:

1. `GRAPH_DFS_OK`: the operation succeeded.
2. `GRAPH_DFS_INVALID_ARGUMENT`: a required pointer is `NULL`.
3. `GRAPH_DFS_OUT_OF_RANGE`: the source is not an active vertex.
4. `GRAPH_DFS_INVALID_GRAPH`: the Module 3 graph rules are broken.
5. `GRAPH_DFS_REQUIRES_UNDIRECTED`: component counting received a directed
   graph.
6. `GRAPH_DFS_LIMIT`: the requested or needed Stack limit, or maximum,
   cannot be met.
7. `GRAPH_DFS_ALLOCATION`: an allocation—storage requested while the
   program runs—could not be obtained for the temporary Stack.

## 7. Prepare for the Cognitive Pause

Be ready to:

1. trace recursive DFS and its final visited set on a new cyclic graph;
2. explain the check at an edge leading to an already marked vertex; and
3. give two visited-and-frontier states for iterative DFS.

Do not solve the pause graph before timing begins.
