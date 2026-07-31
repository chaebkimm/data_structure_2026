# Student Notes — Remembering Where a Graph Has Been

## Essential question

> Tree branches do not reconnect. What must change when a route can lead
> back to a vertex already reached?

## 1. The graph problem

A **graph** stores items and their direct relationships. One item is a
**vertex**. One direct relationship is an **edge**. A **directed edge** works
in one direction, so `0 → 1` does not also mean `1 → 0`.

```text
0 Gateway   1 Web   2 Admin
3 Database  4 Monitor  5 Archive
```

Edges:

```text
0 → 1   0 → 2   1 → 3
2 → 3   3 → 4   4 → 1
```

Neighbor lists:

```text
0:[1,2]  1:[3]  2:[3]  3:[4]  4:[1]  5:[]
```

An **out-neighbor** is the destination of an edge leaving the current
vertex. A **route** is a sequence that follows stated edges. The route
`1 → 3 → 4 → 1` is a **cycle**, a route that returns to an earlier vertex.

**Depth-first search (DFS)** follows one available route deeply before
returning to an unfinished choice. A **source** is its chosen starting
vertex. A vertex is **reachable** when a directed route leads to it from the
source. A source reaches itself.

From source 0, vertices 0 through 4 are reachable. Vertex 5 is not.

## 2. The essential addition: visited state

A **Boolean** value is either `true` or `false`. A **visited array** stores
one Boolean for every vertex.

Course rule:

> `visited[v]` becomes true when vertex `v` is discovered and scheduled.

To **discover** means to reach for the first time. To **schedule** means to
arrange for the vertex's work to happen. To **mark** means to change a
visited value to true. To **record** means to append the vertex number to
the output. A marked vertex may not yet be recorded.

When an edge leads to a marked vertex, DFS skips that destination. Thus edge
`4 → 1` does not restart work at 1. The same check also prevents two routes
to vertex 3 from recording it twice.

## 3. Recursive graph DFS

A **function** is a named group of instructions. **Recursion** means a
function calls itself. A **call frame** saves one active call's unfinished
work.

Recursive DFS marks and records a vertex when its call begins. The course
checks possible destinations from lower number to higher number.

```text
DFS at vertex u:
    mark u
    record u
    for v from 0 through V - 1:
        if edge u → v exists and v is not marked:
            DFS at v
    return
```

`V` means active vertex count; active means included in the current graph. A
**pointer** stores a memory address. `NULL` is C's pointer value meaning
“points to no object.” Unlike tree DFS, this method receives no `NULL` child
pointer. It makes no call for a marked destination and returns after
checking all possible destinations.

The course recursive trace from source 0 is:

```text
enter 0
enter 1
enter 3
enter 4; skip 4 → 1
return to 0 and enter 2; skip 2 → 3
```

Recorded order: `0, 1, 3, 4, 2`. The final visited set is
`{0, 1, 2, 3, 4}`; vertex 5 remains false.

## 4. Iterative graph DFS

An **iterative algorithm** uses a loop instead of recursive calls. A
**loop** repeats instructions while its condition holds. A **Stack** is a
last-in, first-out collection: the newest item is removed first. `push` adds
one item; `pop` removes the newest item.

An **explicit vertex-ID Stack** is a program-operated Stack of vertex
numbers. It differs from the runtime call stack used for function calls.

The **frontier** contains marked vertices still waiting to be processed.
The explicit Stack stores it.

```text
push source
if push succeeds, mark source

while the Stack is not empty:
    pop u
    record u
    check v from V - 1 down through 0
    for each edge u → v whose v is unmarked:
        push v
        if push succeeds, mark v
```

Mark only after a successful push; otherwise later work could skip a vertex
that was never scheduled.

Check destinations high to low so the later lower-numbered push leaves
first. Stack items below are bottom to top.

| Completed processing | Visited vertices | Frontier Stack | Output |
|---|---|---|---|
| none | `{0}` | `0` | empty |
| 0 | `{0,1,2}` | `2,1` | `0` |
| 1 | `{0,1,2,3}` | `2,3` | `0,1` |
| 3 | `{0,1,2,3,4}` | `2,4` | `0,1,3` |
| 4 | `{0,1,2,3,4}` | `2` | `0,1,3,4` |
| 2 | `{0,1,2,3,4}` | empty | `0,1,3,4,2` |

Linear equivalent: begin with 0 waiting. Processing 0 leaves 2 then 1
waiting; processing 1 leaves 2 then 3; processing 3 leaves 2 then 4;
processing 4 leaves only 2; processing 2 empties the Stack.

Here both methods match. Even with both course order rules fixed, another
graph's links between routes can produce different valid recursive and
iterative orders. Their reachable sets must still match.

The course traversal needs at most two simultaneous Stack items. A Stack
limit of 2 succeeds. Limit 1 fails while the two choices from vertex 0 are
being scheduled, and the caller's old output remains unchanged.

## 5. Reachability and connected components

To cover an entire graph, check each vertex and start another search at
every still-unmarked vertex.

An **undirected edge** connects both ways. A **connected component** is one
separate undirected group whose vertices have routes to one another. An
**isolated vertex** has no edge and forms a component of one.

Now use a separate undirected practice graph with the same six pairs of
vertex numbers. Vertices 0 through 4 form one component; isolated vertex 5
forms another. The component count is 2.

With increasing neighbor checks, the recursive whole-graph order is:

```text
0, 1, 3, 2, 4 | 5
```

With the explicit Stack rule, the order is:

```text
0, 1, 3, 4, 2 | 5
```

The vertical line separates components. Both orders identify the same
groups. Use “connected component” only for undirected graphs; for a directed
graph, state the source and reachable vertices.

## 6. Public C contract

An **API** is the public types and functions other code may use. A
**contract** states what a function accepts, changes, reports, and
preserves. A **caller** is code that requests a function. An **output
parameter** is caller-provided storage in which a function writes an answer.

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

`size_t` is a nonnegative whole-number type for counts and indexes. The
output holds at most 16 vertices.

```c
GraphDfsStatus graph_dfs_recursive(
    const Graph *graph, size_t start_vertex,
    GraphDfsOrder *out_order);

GraphDfsStatus graph_dfs_iterative(
    const Graph *graph, size_t start_vertex,
    size_t stack_limit, GraphDfsOrder *out_order);

GraphDfsStatus graph_count_connected_components(
    const Graph *graph, size_t *out_component_count);

const char *graph_dfs_status_name(GraphDfsStatus status);
```

`const Graph *` permits inspection but not change through that pointer.
**Validation** checks whether stored graph rules hold. After required
pointers are checked, each operation validates the entire active stored
graph before using a source or Stack limit. Component counting accepts only
an undirected graph. An empty undirected graph has zero components.

A **status code** is a named result. An **allocation** is storage requested
while a program runs.

```text
GRAPH_DFS_OK                    success
GRAPH_DFS_INVALID_ARGUMENT      a required pointer is NULL
GRAPH_DFS_OUT_OF_RANGE          source is not an active vertex
GRAPH_DFS_INVALID_GRAPH         graph rules are broken
GRAPH_DFS_REQUIRES_UNDIRECTED   component input is directed
GRAPH_DFS_LIMIT                 Stack limit, or maximum, cannot be met
GRAPH_DFS_ALLOCATION            temporary Stack storage unavailable
```

Every output changes only on `GRAPH_DFS_OK`; failure leaves the old output
unchanged. This is **failure preservation**. The Stack owns its temporary
allocation. To destroy it means to release that memory and reset its stored
values. Iterative DFS does so after success or later failure.

## 7. Costs depend on storage

**Time complexity** describes how work grows. **Big-O notation** writes that
growth as `O(...)`. Let `V` mean vertex count and `E` mean edge count.
**Auxiliary space** is temporary working storage separate from the graph and
output.

An adjacency matrix is a `V`-by-`V` grid. Full DFS scans one row of `V`
possible destinations for each vertex, so its time is `O(V²)`.

An **adjacency list** stores only each vertex's outgoing neighbors. Full DFS
then takes `O(V+E)` time: work grows with vertices plus stored edges.

Both versions use `O(V)` auxiliary space for the visited array and active
calls or frontier Stack.

## 8. Tree-to-graph transfer and safe scope

| Tree DFS | Graph DFS |
|---|---|
| current tree node | current graph vertex |
| left and right children | outgoing neighbors |
| fixed root | chosen source |
| no route repeats in a valid tree | sharing and cycles may repeat routes |
| no visited array needed | one visited Boolean per vertex |
| root covers the tree | one source may cover only part of the graph |

The service graph is synthetic—invented for safe practice. A recorded route
proves only that the route exists in this invented graph. It does not prove
that real communication occurred or access is possible. Do not connect this
lab to real-use services or private data.
