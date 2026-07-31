# Stage C — Investigation Worksheet: Graph Depth-First Search

Open this file after completing and preserving the Cognitive Pause.

**Sections A–F are the core investigation. Complete them before opening
Stage D notes. Sections G–I are later extension and reflection.**

You may replace a diagram or table with a numbered list containing the same
facts. Drawing quality and response speed are not assessed.

## Quick reference

A **graph** stores vertices and their direct relationships, called edges. A
**directed edge** works in one direction. An **out-neighbor** is the
destination of an edge leaving the current vertex.

**Depth-first search (DFS)** follows one available route deeply before
returning to an unfinished choice. The **source** is its starting vertex. A
vertex is **reachable** when a directed route leads to it from the source.

A **visited array** stores one Boolean, or true-or-false value, for every
vertex. In this module, a marked vertex has been discovered and scheduled.
It may still be waiting to be recorded. The **frontier** contains scheduled
vertices whose processing is unfinished.

The lab uses the adjacency-matrix `Graph` from Module 3. An **adjacency
matrix** is a row-and-column grid in which cell `[u][v]` says whether
`u → v` exists.

An **iterative algorithm** repeats with a loop. A **loop** repeats
instructions while its condition holds. A **Stack** is a last-in,
first-out collection. `push` adds one item; `pop` removes the newest item.
A **pointer** stores a memory address. A **caller** is code that requests a
function. A **field** is one named value inside a stored C object.

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

`GraphDfsOrder` stores recorded vertex numbers and their count. `size_t` is
a nonnegative whole-number type used for counts and indexes.

## Course directed graph

The graph has six services:

```text
0 Gateway   1 Web   2 Admin
3 Database  4 Monitor  5 Archive
```

Its directed edges are:

```text
0 → 1   0 → 2   1 → 3
2 → 3   3 → 4   4 → 1
```

Equivalent outgoing-neighbor lists:

```text
0:[1, 2]   1:[3]   2:[3]   3:[4]   4:[1]   5:[]
```

In words, Gateway leads to Web and Admin; Web and Admin each lead to
Database; Database leads to Monitor; Monitor leads to Web; and Archive has
no edge.

## A. Explain why marks are needed

### A1. Read outgoing choices

List the out-neighbors of vertex 0 and the out-neighbors of vertex 4.

____________________________________________________________________

### A2. Find the repeated route

Starting at vertex 1, write the directed cycle. A **cycle** is a route that
returns to an earlier vertex.

____________________________________________________________________

What could happen if each reached destination always created new work?

____________________________________________________________________

### A3. State the mark rule

Complete the sentence:

> A vertex is marked when __________________________________________.

Why must iterative DFS mark a destination only after its push succeeds?

____________________________________________________________________

### A4. Separate marked from recorded

Immediately after iterative DFS processes vertex 0, vertices 1 and 2 have
been pushed. Which vertices are marked? Which have been recorded?

Marked: ____________________________________________________________

Recorded: __________________________________________________________

### A5. Decide reachability

Starting at 0, which vertex is not reachable? Explain from the edge list.

____________________________________________________________________

## B. Trace recursive DFS

**Recursion** occurs when a function calls itself. A **call frame** stores
information for one active call. Recursive DFS marks and records a vertex
on entry, then checks possible destinations from lower number to higher
number.

### B1. Complete the order

Write the complete recursive output from source 0:

____________________________________________________________________

### B2. Complete the event trace

| Event | Visited vertices after event | Recorded order |
|---|---|---|
| Enter 0 | | |
| Enter 1 | | |
| Enter 3 | | |
| Enter 4 | | |
| Check edge `4 → 1` | | |
| Later enter 2 | | |
| Check edge `2 → 3` | | |

What happens at each edge whose destination is already marked?

____________________________________________________________________

### B3. Explain saved work

When the call for vertex 4 is active, list the active calls from oldest to
newest.

____________________________________________________________________

What outgoing choice at vertex 0 still needs attention later?

____________________________________________________________________

### B4. Compare the tree stopping rule

`NULL` is C's pointer value meaning “points to no object.” Tree DFS returned
at a `NULL` child. This graph is stored in a matrix, so it has no child
pointer.

When does one graph DFS call return?

____________________________________________________________________

Why does an already marked destination create no new call?

____________________________________________________________________

### B5. Start at the isolate

An **isolated vertex** has no entering or leaving edge. What output does
recursive DFS produce from source 5? Why?

____________________________________________________________________

## C. Trace iterative DFS

An **explicit Stack** is a Stack operated directly by the program.

Iterative DFS checks destination numbers from high to low. It records on
pop. It pushes an unmarked destination and marks that destination only after
the push succeeds. Stack contents below are listed bottom to top.

### C1. Complete the course trace

| Completed processing | Visited vertices | Complete Stack, bottom to top | Output |
|---|---|---|---|
| none; source pushed | | | |
| 0 | | | |
| 1 | | | |
| 3 | | | |
| 4 | | | |
| 2 | | | |

### C2. Explain decreasing destination order

Why does checking higher destinations first make vertex 1 leave the Stack
before vertex 2?

____________________________________________________________________

### C3. Compare the two implementations

State the complete iterative output. Does it equal the recursive output on
this graph?

____________________________________________________________________

Does one matching example prove that every correct recursive and iterative
DFS must always record the same order? Explain.

____________________________________________________________________

### C4. Apply the Stack limit

A **limit** is a stated maximum. The course graph succeeds with Stack
limit 2. It fails with limit 1 while scheduling the choices from vertex 0.

Why can limit 1 hold the starting vertex but not finish the traversal?

____________________________________________________________________

If the caller's old output is `{9}`, what must remain after the limit
failure?

____________________________________________________________________

Which vertex must remain unmarked if its push fails?

____________________________________________________________________

### C5. Clean up temporary storage

The explicit Stack obtains temporary storage while the program runs.
**Cleanup** means releasing storage when it is no longer needed. To destroy
the Stack means to release the memory it owns and reset its fields.

When must the iterative function destroy its Stack?

____________________________________________________________________

## D. Apply the public contract

An **API** is the public types and operations that other code may use. A
**contract** states what an operation accepts, changes, reports, and
preserves. A **status code** is a named result. An **allocation** is storage
requested while a program runs. `NULL` means a pointer points to no object.

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
```

The exact statuses are:

```text
GRAPH_DFS_OK
GRAPH_DFS_INVALID_ARGUMENT
GRAPH_DFS_OUT_OF_RANGE
GRAPH_DFS_INVALID_GRAPH
GRAPH_DFS_REQUIRES_UNDIRECTED
GRAPH_DFS_LIMIT
GRAPH_DFS_ALLOCATION
```

### D1. Match statuses to plain meanings

Write the status beside each meaning.

1. Success: ________________________________________________________
2. A required pointer is `NULL`: ___________________________________
3. The source is not an active vertex: ______________________________
4. The Module 3 graph rules are broken: _____________________________
5. Component counting received a directed graph: ____________________
6. The requested or needed Stack limit cannot be met: _______________
7. Temporary Stack storage could not be obtained: ___________________

### D2. Order the checks

After required pointers are checked, the entire active stored graph is
validated before the source or Stack limit is used.

Why should a graph that breaks its stored rules not be partly explored?

____________________________________________________________________

### D3. Preserve outputs on failure

**Failure preservation** means a failed operation leaves the caller's old
output unchanged.

If `out_order` initially contains count 1 and vertex 9, what must it contain
after `GRAPH_DFS_OUT_OF_RANGE`, `GRAPH_DFS_LIMIT`, or
`GRAPH_DFS_ALLOCATION`?

____________________________________________________________________

If component output initially equals 99, what must it equal after
`GRAPH_DFS_REQUIRES_UNDIRECTED`?

____________________________________________________________________

### D4. Keep the graph unchanged

`const Graph *` permits inspection but not change through the pointer. Why
should a search not add or remove graph edges?

____________________________________________________________________

### D5. Distinguish an empty graph

An empty undirected graph has zero active vertices. What component count
should it report?

____________________________________________________________________

Why would traversal with source 0 on that graph report
`GRAPH_DFS_OUT_OF_RANGE`?

____________________________________________________________________

## E. Count undirected connected components

An **undirected edge** connects both ways. A **connected component** is one
separate group in an undirected graph: every vertex in the group has an
undirected route to every other, and no outside vertex connects to the
group. An isolated vertex forms a component of one.

This section uses a separate undirected practice graph. It uses the same six
pairs of vertex numbers as the course directed graph, but every relationship
now connects both ways.

```text
{0,1}  {0,2}  {1,3}  {2,3}  {3,4}  {4,1}
```

Equivalent neighbor lists:

```text
0:[1,2]       1:[0,3,4]   2:[0,3]
3:[1,2,4]     4:[1,3]     5:[]
```

### E1. Identify the groups

List each component as a set of vertex numbers. Then state the count.

____________________________________________________________________

### E2. Explain the outer scan

Component counting checks possible starting vertices from 0 through 5. It
starts DFS only at an unmarked vertex.

Which starting vertices create new searches?

____________________________________________________________________

Why do the other indexes not create new searches?

____________________________________________________________________

### E3. Compare valid orders

Complete the whole recursive sweep, placing `|` between components:

____________________________________________________________________

Complete the whole iterative sweep:

____________________________________________________________________

Why may the two valid orders differ while the component result agrees?

____________________________________________________________________

### E4. Keep directed language precise

Why does `graph_count_connected_components` reject a directed graph with
`GRAPH_DFS_REQUIRES_UNDIRECTED`?

____________________________________________________________________

What word should be used for vertices obtainable from one source in a
directed graph?

____________________________________________________________________

## F. Analyze costs and transfer the ideas

**Time complexity** describes how work grows as input grows. Let `V` mean
vertex count and `E` mean edge count. **Auxiliary space** is temporary
working storage separate from the graph and output.

An **adjacency list** stores one list of outgoing neighbors for each vertex.

### F1. Complete the cost comparison

| Representation and task | Time | Auxiliary space | Reason |
|---|---:|---:|---|
| Full DFS with adjacency matrix | | | |
| Full DFS with adjacency lists | | | |

Use `O(V²)`, `O(V+E)`, and `O(V)` where they apply. Big-O notation describes
an upper pattern for growth, not an exact stopwatch time.

### F2. Transfer from tree DFS

| Question | Tree DFS | Graph DFS |
|---|---|---|
| Current item | node | |
| Next choices | left/right children | |
| Start | root | |
| Repeated-route risk | none in a valid tree | |
| New memory | not required | |
| Unfinished work | recursive calls or explicit Stack | |
| Complete coverage | root covers the tree | |

### F3. State the safe meaning

The graph is synthetic, meaning invented for practice. If DFS records a
route from Gateway to a protected service, what does that prove?

____________________________________________________________________

What does it not prove about a real system?

____________________________________________________________________

## G. Design three tests — later extension

A **test** supplies input and checks an expected result. A **regression
test** is kept to prevent a known defect from returning.

Write one test in each required category.

### G1. Traversal order or reachability

Include a cycle or a disconnected case.

Graph and source: __________________________________________________

Expected output or reachable set: __________________________________

Why this test matters: _____________________________________________

### G2. Failure preserves output

Failure used: ______________________________________________________

Old output that must remain: _______________________________________

Why this test matters: _____________________________________________

### G3. Undirected component count

Include an isolate or an empty graph.

Graph: _____________________________________________________________

Expected component count: __________________________________________

Why this test matters: _____________________________________________

## H. Explore order choices — later extension

### H1. Change neighbor order

If recursive DFS checks higher vertex numbers first, must its reachable set
change? May its recorded order change?

____________________________________________________________________

### H2. Explain early marking

Why can marking a successfully pushed frontier vertex cause iterative and
recursive DFS to record different valid orders when several routes reach
the same vertices?

____________________________________________________________________

### H3. Change representation

Would replacing the matrix with adjacency lists remove the need for visited
state? Explain.

____________________________________________________________________

## I. Exit reflection — later extension

### I1. Essential graph addition

What one piece of state did graph DFS add to the tree DFS ideas, and why?

____________________________________________________________________

### I2. Two storage mechanisms

How do recursive calls and an explicit vertex-ID Stack each preserve
unfinished work?

____________________________________________________________________

### I3. Components

Why can an isolated vertex increase an undirected component count?

____________________________________________________________________

### I4. Correction

My initial thinking:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
