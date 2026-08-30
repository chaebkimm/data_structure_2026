# Instructor Answer Key — Module 6 Graph DFS

## Macro-Question synthesis

> Tree branches do not reconnect. What must change when a graph route can
> lead back to a vertex already reached?

A strong response says that graph DFS stores one yes-or-no visited mark for
each active vertex. It marks a vertex when that vertex is first discovered
and successfully scheduled. An edge to an already marked destination
creates no new call or Stack push. This prevents cycles and multiple routes
from processing the same vertex repeatedly.

Recursive calls or an explicit Stack still remember unfinished work. The
visited array is the new graph-specific state. One source reaches only its
reachable region; an undirected component sweep starts again at each
remaining unmarked vertex.

---

## Stage A inquiry

The standard and linear prompts contain the same questions in the same
order. Stage A precedes the formal visited-array and graph-DFS vocabulary.
Accept accurate plain language.

### A. Read the service relationships

1. Immediately after Gateway, choose Web or Admin:

   ```text
   vertices 1 and 2
   ```

2. Database can be entered from both Web and Admin:

   ```text
   vertex 3
   ```

3. Archive is separate from every edge:

   ```text
   vertex 5
   ```

### B. Follow one route

Starting at Web, the first five names are:

```text
Web, Database, Monitor, Web, Database
```

Equivalent vertex indexes:

```text
1, 3, 4, 1, 3
```

The cycle `Web → Database → Monitor → Web` begins repeating. A program that
continues without remembering prior vertices may never terminate. A
recursive version can exhaust the runtime call stack; an iterative version
can continue consuming time indefinitely even when its current frontier is
small.

### C. Invent the missing memory

Accept a yes-or-no fact such as:

> Has this vertex already been reached and arranged for processing?

It should change when the vertex is first scheduled—before recursively
following its outgoing edges, or immediately after an explicit push
succeeds. An edge to a vertex whose fact is already true is skipped.

At this gate, do not require the terms visited, discovered, scheduled,
recursive, or Stack.

### D. Remember choices still waiting

- While the program continues through Web, the choice through Admin must
  wait.
- After Web leads to Database, Admin is still waiting.
- Accept any repeatable saved-choice policy that does not lose work.
  The later canonical policy returns to the newest unfinished choice, using
  active recursive calls or last-in, first-out storage.

Students may describe a list of waiting vertex numbers, a return point, or
physical cards. Do not require a specific C representation at Gate A.

### E. Decide what one start can cover

No directed route from Gateway reaches Archive. Vertex 5 has no entering
edge.

To inspect every vertex, check every active vertex after the first route
search. Whenever one has not yet been inspected or scheduled, begin another
search there. In the canonical graph, the additional start is vertex 5.

### F. Transfer from the tree

Still useful:

- follow one route deeply;
- remember unfinished choices; and
- return to the newest unfinished choice.

New problem:

- a cycle can return to an earlier vertex; and
- multiple incoming routes can reach the same vertex.

A valid pure tree has neither condition.

### G. Macro-Question

Canonical Stage A language:

> Remember one yes-or-no fact for every vertex. Change it the first time the
> vertex is saved for inspection. Follow one route deeply, but skip an edge
> whose destination was already saved. After one start finishes, begin again
> at any still-unsaved vertex if coverage of every vertex is required.

Do not retroactively penalize a coherent preserved initial model that used
different words.

Open questions vary. Useful questions concern when to change the mark, how
waiting choices are stored, how direction affects reachability, whether
orders can differ, or how much work a matrix requires.

---

## Stage B Cognitive Pause

The pause contains exactly three targets. Keep this key, vocabulary, hints,
and correctness feedback closed until the initial response is preserved.

The pause graph is:

```text
0 → 1   0 → 2   1 → 3   3 → 1   2 → 4
```

### Target 1 — Trace recursive DFS

Ascending destination checks give:

```text
0, 1, 3, 2, 4
```

Final visited vertices:

```text
{0,1,2,3,4}
```

### Target 2 — Stop the returning edge

At vertex 3 while examining `3 → 1`:

```text
visited[1] == true
```

Skip the edge and make no recursive call. Without the visited check, the
route `1 → 3 → 1 → 3 → ...` repeats.

### Target 3 — Trace the first frontier states

Stack rows are bottom to top:

| Completed processing | Visited vertices | Stack | Output |
|---|---|---|---|
| 0 | `{0,1,2}` | `2,1` | `0` |
| 1 | `{0,1,2,3}` | `2,3` | `0,1` |

Destinations are scanned from high to low. From 0, vertex 2 is pushed before
vertex 1. Vertex 1 is therefore the newest item, so last-in, first-out
removal selects it next. The same rule leaves 3 above 2 after processing 1.

### Calibration statement

Accept any specific statement tied to evidence, for example:

> The visited check at `3 → 1` prevents another call, and the bottom-to-top
> Stack trace shows why vertex 1 leaves before vertex 2.

---

## Stage C investigation

The standard and linear worksheets are prompt-for-prompt equivalent.
Sections A–F are core; G–I are later extension and reflection.

### A. Explain why marks are needed

#### A1. Read outgoing choices

```text
out-neighbors of 0: 1, 2
out-neighbors of 4: 1
```

#### A2. Find the repeated route

```text
1 → 3 → 4 → 1
```

If every reached destination creates new work, those vertices are scheduled
again and again. The operation may not terminate and may exhaust time or
runtime call-stack resources.

#### A3. State the mark rule

Complete:

> A vertex is marked when it is first discovered and successfully scheduled
> for processing.

Recursive DFS marks on entry before scanning outgoing edges. Iterative DFS
pushes first and marks immediately after that push succeeds. If a failed
push were followed by a mark, the vertex would appear scheduled even though
no frontier item could later process it. A later route would then skip
needed work.

#### A4. Separate marked from recorded

After iterative processing of 0:

```text
marked:  {0,1,2}
recorded: {0}
```

#### A5. Decide reachability

Vertex 5 is not reachable from source 0. It has no entering edge, so no
directed route from the source can arrive there.

### B. Trace recursive DFS

#### B1. Complete the order

```text
0, 1, 3, 4, 2
```

#### B2. Complete the event trace

| Event | Visited vertices after event | Recorded order |
|---|---|---|
| Enter 0 | `{0}` | `0` |
| Enter 1 | `{0,1}` | `0,1` |
| Enter 3 | `{0,1,3}` | `0,1,3` |
| Enter 4 | `{0,1,3,4}` | `0,1,3,4` |
| Check edge `4 → 1` | `{0,1,3,4}` | `0,1,3,4` |
| Later enter 2 | `{0,1,2,3,4}` | `0,1,3,4,2` |
| Check edge `2 → 3` | `{0,1,2,3,4}` | `0,1,3,4,2` |

An edge to an already marked destination creates no call and changes
neither visited state nor output.

#### B3. Explain saved work

When the call for 4 is active, active calls oldest to newest are:

```text
0, 1, 3, 4
```

The call for 0 must later continue its row scan and examine outgoing choice
2.

#### B4. Compare the tree stopping rule

A graph DFS call returns after it has scanned the complete active row and no
unmarked out-neighbor remains to be processed.

An already marked destination creates no call because it is already
scheduled or complete. Calling again would duplicate work and could repeat a
cycle.

#### B5. Start at the isolate

```text
5
```

The source is reachable from itself and is marked and recorded. Its row has
no outgoing edge, so the call then returns.

### C. Trace iterative DFS

#### C1. Complete the canonical trace

| Completed processing | Visited vertices | Stack, bottom to top | Output |
|---|---|---|---|
| none; source pushed | `{0}` | `0` | empty |
| 0 | `{0,1,2}` | `2,1` | `0` |
| 1 | `{0,1,2,3}` | `2,3` | `0,1` |
| 3 | `{0,1,2,3,4}` | `2,4` | `0,1,3` |
| 4 | `{0,1,2,3,4}` | `2` | `0,1,3,4` |
| 2 | `{0,1,2,3,4}` | empty | `0,1,3,4,2` |

#### C2. Explain decreasing destination order

Row 0 is checked from high to low. Vertex 2 is pushed first; vertex 1 is
pushed second and becomes the newest item. Last-in, first-out removal
therefore pops 1 before 2.

#### C3. Compare the two implementations

Iterative output:

```text
0, 1, 3, 4, 2
```

It equals recursive output on this fixture. One matching example does not
prove universal equality. Different neighbor orders and already scheduled
cross-route destinations can change the order while preserving the same
reachable set.

#### C4. Apply the Stack limit

Limit 1 can hold source 0. After 0 is popped, vertex 2 is pushed and fills
the one available frontier position. The subsequent push of vertex 1
therefore fails.

The caller’s complete prior output remains:

```text
count 1, vertex 9
```

The destination whose push failed—vertex 1 in this trace—must remain
unmarked.

#### C5. Clean up temporary storage

After successful Stack initialization, destroy it exactly once on every
later exit path: ordinary completion, limit failure, allocation failure, or
another mapped failure.

### D. Apply the public contract

#### D1. Match statuses

1. Success: `GRAPH_DFS_OK`
2. Required pointer is `NULL`: `GRAPH_DFS_INVALID_ARGUMENT`
3. Source is not active: `GRAPH_DFS_OUT_OF_RANGE`
4. The supplied Module 6 graph rules are broken: `GRAPH_DFS_INVALID_GRAPH`
5. Component count receives directed input:
   `GRAPH_DFS_REQUIRES_UNDIRECTED`
6. Stack bound cannot be met: `GRAPH_DFS_LIMIT`
7. Stack storage unavailable: `GRAPH_DFS_ALLOCATION`

#### D2. Order the checks

A malformed graph may have an invalid vertex count, kind, self-loop, or
asymmetric undirected pair. Exploring it would rely on relationships that do
not satisfy the published representation. Validate first so the operation
returns one clear failure and publishes no misleading partial result.

#### D3. Preserve outputs on failure

After `GRAPH_DFS_OUT_OF_RANGE`, `GRAPH_DFS_LIMIT`, or
`GRAPH_DFS_ALLOCATION`, the order remains:

```text
count 1, vertex 9
```

The entire object, including unused bytes, remains unchanged.

After `GRAPH_DFS_REQUIRES_UNDIRECTED`, component output remains:

```text
99
```

#### D4. Keep the graph unchanged

DFS answers a question about the supplied relationship model. Adding or
removing an edge during the search would change the question, violate the
read-only `const` contract, and make results depend on traversal side
effects.

#### D5. Distinguish an empty graph

An empty undirected graph has:

```text
0 components
```

Traversal from source 0 returns `GRAPH_DFS_OUT_OF_RANGE` because the active
index condition is `start_vertex < vertex_count`, and `0 < 0` is false.

### E. Count undirected connected components

#### E1. Identify the groups

```text
{0,1,2,3,4}
{5}
count = 2
```

#### E2. Explain the outer scan

New searches begin at:

```text
0 and 5
```

The search from 0 marks vertices 0 through 4. Outer indexes 1 through 4
therefore do not begin new searches. Vertex 5 remains unmarked and begins
the second one.

#### E3. Compare valid orders

Ascending recursive sweep:

```text
0, 1, 3, 2, 4 | 5
```

Iterative sweep under the module’s push/mark rule:

```text
0, 1, 3, 4, 2 | 5
```

The scheduling mechanisms and tie behavior differ, but both mark the same
first component and then start at isolated vertex 5. Thus both produce
component count 2.

#### E4. Keep directed language precise

The course definition requires paths that work both ways within the group.
A directed arrow does not automatically provide its reverse. Rather than
silently changing edge meaning, the API rejects directed input.

For directed graphs, use:

```text
reachable from a stated source
```

### F. Analyze costs and transfer the model

#### F1. Complete the cost table

| Representation and task | Time | Auxiliary space | Reason |
|---|---:|---:|---|
| Full DFS with adjacency matrix | `O(V²)` | `O(V)` | Each reached vertex scans `V` possible destinations; visited state and calls/Stack hold at most `V` entries |
| Full DFS with adjacency lists | `O(V+E)` | `O(V)` | Each vertex and stored neighbor entry is processed; visited state and calls/Stack are bounded by `V` |

#### F2. Transfer from tree DFS

| Question | Tree DFS | Graph DFS |
|---|---|---|
| Current item | node | vertex |
| Next choices | left/right children | unmarked out-neighbors |
| Start | root | selected source |
| Repeated-route risk | none in a valid tree | cycles and multiple incoming routes |
| New memory | not required | visited array |
| Unfinished work | recursive calls or explicit Stack | recursive calls or explicit vertex-ID Stack |
| Complete coverage | root covers the tree | one source covers only its reachable region; an outer scan is needed for all components |

#### F3. State the safe meaning

A recorded route proves only that the synthetic graph contains a directed
edge sequence from Gateway to that modeled vertex.

It does not prove a real network route, successful authentication,
authorization, vulnerability, exploitability, compromise, attack, or
correct current policy.

### G. Design three tests — later extension

Many concrete tests are valid. One complete set follows.

#### G1. Traversal order or reachability

```text
Graph: canonical directed six-vertex graph
Source: 2
Expected order: 2,3,4,1
Expected reachability: 1,2,3,4 present once; 0 and 5 absent
```

This adds a direction-sensitive source not exercised by the canonical
source-0 trace. Its reachable region still contains the cycle.

#### G2. Failure preserves output

```text
Failure: recursive traversal of a valid nonempty three-vertex graph with
         start_vertex 3
Old output: count 1, vertex 9, with a copied before-image
Expected: GRAPH_DFS_OUT_OF_RANGE and byte-for-byte unchanged output
```

#### G3. Undirected component count

```text
Graph: five undirected vertices with edges {0,1} and {2,3}; vertex 4 isolated
Expected count: 3
```

The isolate proves that a component may contain one vertex, and the count
differs from the supplied companion fixture. Another genuinely new graph is
also acceptable.

### H. Explore order choices — later extension

#### H1. Change neighbor order

The reachable set must not change. The recorded order may change. Descending
recursive scanning of the canonical directed graph can produce:

```text
0, 2, 3, 4, 1
```

#### H2. Explain early marking

A successfully pushed vertex is marked while it waits. If a deeper route
later finds an edge to that pending vertex, it skips another push. This can
change which frontier item is processed next compared with recursive calls,
while still processing every reachable vertex exactly once.

#### H3. Change representation

No. An adjacency list changes how outgoing neighbors are stored and
enumerated. Cycles and multiple routes still exist, so visited state remains
necessary.

### I. Exit reflection — later extension

#### I1. Essential graph addition

Graph DFS adds one visited Boolean per vertex. It prevents a cycle or second
route from scheduling a vertex repeatedly.

#### I2. Two storage mechanisms

Recursive DFS leaves active calls waiting; each call frame remembers the
current row and where its scan resumes. Iterative DFS explicitly pushes
vertex IDs into a last-in, first-out Stack. Both preserve unfinished work,
but program code directly controls only the explicit Stack.

#### I3. Components

An isolated vertex cannot join another vertex by an undirected path, but it
is reachable from itself. It therefore forms a maximal connected group of
one and increases the count.

#### I4. Correction

Answers vary. Require one accurate initial claim and one specific piece of
trace, test, or contract evidence that changed or strengthened it.

---

## Canonical API reference

### Result and status

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

Exact status order:

```text
GRAPH_DFS_OK
GRAPH_DFS_INVALID_ARGUMENT
GRAPH_DFS_OUT_OF_RANGE
GRAPH_DFS_INVALID_GRAPH
GRAPH_DFS_REQUIRES_UNDIRECTED
GRAPH_DFS_LIMIT
GRAPH_DFS_ALLOCATION
```

Exact operations:

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

`GRAPH_MAX_VERTICES` is 16. A successful order contains each reachable
vertex exactly once. All failed operations preserve caller outputs.

### Canonical source results

| Source | Directed order | Reachable set |
|---:|---|---|
| 0 | `0,1,3,4,2` | `{0,1,2,3,4}` |
| 2 | `2,3,4,1` | `{1,2,3,4}` |
| 5 | `5` | `{5}` |

### Boundary behavior

| Input or event | Result |
|---|---|
| Required graph or output pointer is `NULL` | `GRAPH_DFS_INVALID_ARGUMENT` |
| Source is outside active indexes | `GRAPH_DFS_OUT_OF_RANGE` |
| Graph invariant is broken | `GRAPH_DFS_INVALID_GRAPH` |
| Component count receives directed graph | `GRAPH_DFS_REQUIRES_UNDIRECTED` |
| Iterative Stack cannot stay within limit | `GRAPH_DFS_LIMIT` |
| Stack allocation fails | `GRAPH_DFS_ALLOCATION` |
| Empty undirected component graph | `GRAPH_DFS_OK`, count 0 |
| Empty graph traversal from 0 | `GRAPH_DFS_OUT_OF_RANGE` |

## Lab and test guidance

Students complete three algorithm areas in `starter/graph_dfs.c`:

1. TODO 1, the private `recursive_visit` helper, with mark/record on entry
   and ascending neighbor scans;
2. TODO 2, `graph_dfs_iterative`, with descending scans, push-then-mark,
   complete Stack cleanup, and candidate output; and
3. TODO 3, `graph_count_connected_components`, with one visited array across
   the outer sweep.

The Module 6 graph operations and typed vertex Stack are supplied. Students
must use the public Stack operations rather than inspect or change its
fields inside DFS.

Three student-authored test categories are required:

1. traversal order or reachability;
2. a boundary/failure that proves output preservation; and
3. connected-component counting.

Strong tests state exact expected values, explain what is new beyond the
public suite, and leave no allocated Stack storage live.

## Evidence-record reference

### 1. Core language

- **Depth-first search:** follow one available route deeply before returning
  to a waiting choice.
- **Visited state:** one Boolean per vertex saying whether it has been
  discovered and scheduled.
- **Marked versus recorded:** marked includes waiting or completed vertices;
  recorded includes only vertices already appended to the output.
- **Frontier:** marked vertices whose processing is not finished.
- **Reachable:** having a directed route from the stated source; the source
  reaches itself.

### 2. Canonical directed trace

```text
recursive order: 0,1,3,4,2
final visited: {0,1,2,3,4}
skipped marked edges: 4→1 and 2→3
```

Iterative evidence:

| Completed processing | Visited | Stack | Output |
|---|---|---|---|
| none; source pushed | `{0}` | `0` | empty |
| 0 | `{0,1,2}` | `2,1` | `0` |
| 1 | `{0,1,2,3}` | `2,3` | `0,1` |
| 3 | `{0,1,2,3,4}` | `2,4` | `0,1,3` |
| 4 | `{0,1,2,3,4}` | `2` | `0,1,3,4` |
| 2 | `{0,1,2,3,4}` | empty | `0,1,3,4,2` |

High-to-low scanning pushes the lower destination later, making it the next
last-in, first-out removal. Marking only after successful push prevents an
unscheduled destination from being falsely marked.

### 3. Recursive and explicit storage

- Recursive calls remember the current vertex, the row position at which
  scanning resumes, and the caller to which control returns.
- The explicit Stack stores vertex IDs for marked work still waiting. Its
  top is the next item removed.

### 4. Expected test evidence

| Case | Expected result |
|---|---|
| Single vertex | `GRAPH_DFS_OK`, order `0` |
| Directed three-cycle | Each of `0,1,2` appears once |
| Canonical recursive DFS | `GRAPH_DFS_OK`, `0,1,3,4,2` |
| Canonical iterative DFS, limit 2 | `GRAPH_DFS_OK`, `0,1,3,4,2` |
| Isolated source 5 | `GRAPH_DFS_OK`, order `5` |
| Inactive source | `GRAPH_DFS_OUT_OF_RANGE`, output unchanged |
| Stack limit 2 | Canonical traversal succeeds |
| Stack limit 1 | `GRAPH_DFS_LIMIT`, output unchanged |
| Stack allocation failure | `GRAPH_DFS_ALLOCATION`, output unchanged |
| Invalid graph | `GRAPH_DFS_INVALID_GRAPH`, output unchanged |
| Directed component request | `GRAPH_DFS_REQUIRES_UNDIRECTED`, count unchanged |
| Companion undirected graph | `GRAPH_DFS_OK`, count 2 |
| Empty undirected graph | `GRAPH_DFS_OK`, count 0 |

Actual output and pass columns must come from the student’s run rather than
this key.

### 5. Failure preservation and cleanup

After a Stack-limit failure, the prepared old order remains byte-for-byte
unchanged. A student can support cleanup through:

- source control-flow showing one `vertex_stack_destroy` on every path after
  successful initialization; and
- a sanitizer or instructor-CI run with no reported leak.

Passing ordinary functional tests alone does not prove the absence of a
leak.

### 6. Connected components

```text
components: {0,1,2,3,4} and {5}
count: 2
recursive sweep: 0,1,3,2,4 | 5
iterative sweep: 0,1,3,4,2 | 5
```

Directed component counting is rejected because the course definition
requires two-way undirected paths. Use reachability from a source for
directed graphs.

### 7. Costs

| Representation | Full DFS time | Auxiliary space | Reason |
|---|---:|---:|---|
| Adjacency matrix | `O(V²)` | `O(V)` | Scan `V` cells for each vertex; visited state and calls/Stack hold at most `V` entries |
| Adjacency lists | `O(V+E)` | `O(V)` | Process vertices and stored neighbor entries; use the same bounded working state |

### 8. Tree-to-graph transfer

Recursive calls or an explicit last-in, first-out Stack still remember
unfinished work. Graph DFS adds visited state because cycles and multiple
routes can reach an earlier vertex. One source may miss vertices when no
directed route from that source reaches them.

### 9. Safe meaning

A completed order proves only that a route exists in the supplied synthetic
graph. It does not prove real communication, authentication, authorization,
vulnerability, exploitability, compromise, or attack.

### 10. Correction note

Answers vary. Require a preserved initial model and one specific trace,
test, or contract fact that changed or strengthened it.

## Autopsy reference

Keep the faulty execution bounded. Before running it, students must predict
the repeated sequence and distinguish the diagnostic step budget from a true
repair.

The exact output is:

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

The first broken decision is the placement of:

```c
seen[vertex] = true;
```

after the recursive neighbor loop. When the first call at vertex 2 examines
`2 → 0`, the older call for 0 has not yet marked itself. It therefore makes
another call at 0.

The smallest repair is to move the mark before the loop and before any
recursive neighbor call:

```c
seen[vertex] = true;

for (...) {
    /* inspect neighbors */
}
```

Then `2 → 0` finds `seen[0] == true` and makes no call. The intended order is:

```text
0, 1, 2
```

A regression test constructs the exact three-cycle, requires count 3 and
order `0,1,2`, and counts occurrences to prove each vertex appears exactly
once. Merely increasing the call budget is not a repair.
