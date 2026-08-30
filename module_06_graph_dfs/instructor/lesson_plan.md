# Instructor Lesson Plan — Module 6: Graph Depth-First Search

## 14-week delivery override - Week 6 (180 minutes)

Use iterative graph DFS as the required implementation and keep recursive
graph DFS as an extension. Practical 1 replaces the ordinary Module 6 lab
and submission; do not collect both. The longer plan below remains a
resource. See the
[14-week delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).

| Minutes | Required live work |
|---:|---|
| 0-12 | Retrieve the adjacency matrix, Stack rule, and tree-to-graph transfer question. |
| 12-28 | Reveal discovered/visited state and the mark-on-successful-push invariant. |
| 28-45 | Trace iterative DFS through the canonical cycle and explain the isolated vertex. |
| 45-55 | Run the exactly-three-target pause and calibrate the trace. |
| 55-70 | Read the iterative public contract, error promises, and neighbor-order rule. |
| 70-90 | Complete a guided iterative DFS core and run the cycle/reachability tests. |
| 90-100 | Brief Practical 1 and identify the evidence it replaces. |
| 100-170 | Run Practical 1 as the Week 6 assessed implementation/reasoning task. |
| 170-180 | Preserve test output, complete the practical checklist, and make one submission. |

Recursive DFS code, recursive call traces, and a separate Module 6 Stage E
submission are extensions. Connected-component reasoning may appear in the
practical, but a second implementation is not added outside its scope.

## Purpose and limits

This module completes the second Linear → Tree → Graph spiral. It retrieves:

- the directed integer adjacency-matrix idea from Module 3;
- the last-in, first-out Stack behavior from Module 4; and
- recursive and explicit-Stack depth-first traversal from Module 5.

Students add one essential graph rule: mark a vertex as soon as it is
successfully scheduled so that a cycle or second route cannot schedule it
again. A **scheduled vertex** is one that is either waiting to be processed
or has already been processed. Recording is separate: recursive DFS records
on entry, while iterative DFS records on pop.

The canonical directed graph is an expanded Module 6 synthetic service graph:

```text
0 Gateway   1 Web   2 Admin   3 Database   4 Monitor   5 Archive

0 → 1   0 → 2   1 → 3   2 → 3   3 → 4   4 → 1
```

Vertex 5 is isolated. The cycle is `1 → 3 → 4 → 1`. With ascending
out-neighbor scanning, recursive DFS from 0 visits:

```text
0, 1, 3, 4, 2
```

Vertices 0 through 4 are reachable from 0; vertex 5 is not.

For component work, use a separate undirected practice graph with the same
endpoint pairs:

```text
{0,1}, {0,2}, {1,3}, {2,3}, {3,4}, {4,1}
```

It has components `{0,1,2,3,4}` and `{5}`. Do not describe this as silently
removing direction from the policy graph. It is a different model built for
an undirected question.

By the end of the module, students should be able to:

1. explain why a graph traversal needs one seen mark per active vertex;
2. mark a vertex before following its outgoing edges;
3. trace recursive DFS on a cycle;
4. trace iterative DFS with a typed vertex-ID Stack;
5. distinguish scheduled vertices from the completed visit order;
6. report all vertices reachable from one source;
7. count connected components only in an undirected graph;
8. explain why correct DFS orders can differ under different neighbor rules;
9. preserve outputs after invalid input, invalid graph, Stack-limit, or
   allocation failure; and
10. compare adjacency-matrix `O(V²)` traversal with adjacency-list
    `O(V + E)` traversal.

All graphs are small, synthetic, and held in memory. A permission-path model
does not prove routing, authorization, exploitability, compromise, or attack
success.

## Beginner language sequence

Introduce or briefly retrieve each term immediately before students need it.

| Term | First-use explanation |
|---|---|
| graph | Objects and the direct relationships between them |
| vertex | One object in a graph |
| directed edge | A relationship that goes from one stated vertex to another |
| out-neighbor | A vertex reached by one outgoing edge |
| adjacency matrix | A row-and-column table whose cells record possible edges |
| path | A route that follows edges |
| cycle | A route that can lead back to an earlier vertex |
| reachable | Able to be reached from a stated starting vertex |
| depth-first search (DFS) | Explore one route deeply before returning to newer saved choices |
| Boolean | A value that is either true or false |
| visited array | One Boolean per vertex saying whether it is already scheduled or completed |
| seen | The short internal variable name used by the starter for visited state |
| visit order | The order in which DFS actually processes vertices |
| recursive function | A function that calls itself directly or indirectly |
| active call | A function call that has started but has not returned |
| base or stopping case | A condition that ends one recursive branch |
| explicit Stack | A last-in, first-out collection directly operated by program code |
| schedule | Save a vertex so it will be processed |
| frontier | Reached vertices that are still waiting to be processed |
| connected component | A largest group joined by undirected paths |
| component sweep | Checking every vertex and starting DFS at each still-unvisited vertex |
| tie rule | A stated rule for choosing among several available neighbors |
| `V` | The active vertex count |
| `E` | The edge count |
| auxiliary space | Temporary working storage separate from the graph and result |
| failure atomicity | A failed operation leaves caller-visible output unchanged |
| allocation | Requesting storage while the program runs |
| synthetic | Invented for safe study rather than collected from a live system |

Use **visited state** in learner explanations. Point out once that the
starter names its private visited array `seen`. Use **visit order** for
`GraphDfsOrder`. The public result does not expose the internal Boolean
array. A vertex is reachable exactly when it appears once in the successful
order.

## Five release gates

A **release gate** is a planned point when the next materials become
available. Students preserve an initial response before calibration.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A — Cycle inquiry | Start of Meeting A | Standard or linear inquiry prompt | Seen-array solution, formal graph-DFS procedure, exact canonical order, code, answers |
| B — Representation | After each initial response is preserved | Representation reveal and exactly-three-target Cognitive Pause | Vocabulary during the pause; investigation answers, textbook, code |
| C — Investigation | After the timed pause and comparison | Standard or linear investigation worksheet | Textbook, completed models, code |
| D — Calibrated explanation | After preserved Stage C core Sections A–F | Beginner notes and equivalent diagrams/text models | Lab package and instructor materials |
| E — Lab and evidence | After retrieval and Gate D calibration in Meeting B | Lab, evidence form, rubric, autopsy, public headers, supplied support, starter, public tests, student-test template, build files | Reference solution, extension tests, answer key |

The vocabulary file remains closed for the complete Cognitive Pause.
Instructors may repeat directions and provide approved access support, but
may not provide a definition, hint, correctness check, or fourth target.

An accommodation may change time, response method, room, lighting, or
assistive technology. It does not reverse the sequence:

```text
attempt → preserve → compare → correct
```

Stage C core is Sections A–F. Later sections may continue in the announced
completion window.

---

# Meeting A — Discover Why a Graph Must Remember (90 minutes)

## Macro-Question

> Tree DFS terminates because branches do not reconnect. What must change
> when a path can lead back to a vertex already reached?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–7 | Retrieve the graph | Recall Module 3's three-server directed matrix, then construct this module's six-service graph, out-neighbors, and cycle. Retrieve only the plain idea of following one route deeply; do not reveal seen tracking or the explicit Stack procedure. | Correct vertices and edges |
| 7–20 | Gate A inquiry | Release one accessible format. Require an individual preserved response before discussion. Let the unguarded route expose `1 → 3 → 4 → 1`. | Initial stopping/memory model |
| 20–30 | Compare without erasing | Ask what repeats, what one-bit fact would prevent repetition, and why source 0 misses Archive. Accept speech, cards, typing, or drawing. | Annotated first model |
| 30–41 | Gate B representation | Define graph DFS, seen marks, ascending neighbor scanning, recursive entry, and explicit scheduling. Keep vocabulary closed. | Labeled state model |
| 41–46 | Five-minute Cognitive Pause | Release exactly the three targets below. Repeat directions only. | Preserved three-target response |
| 46–56 | Calibration | Open vocabulary only after every response is preserved. Compare and annotate. Read diagrams aloud as edge lists and Stack rows. | Corrected response |
| 56–68 | Recursive canonical trace | Mark and record on entry, scan outgoing neighbors 0 through `V-1`, and skip already-seen destinations. Name active calls at the cycle edge. | Exact order and seen states |
| 68–80 | Iterative canonical trace | Retrieve LIFO. Mark only after a push succeeds, record on pop, and scan neighbors from high to low so lower indexes are popped first. | Exact Stack trace |
| 80–86 | Reachability and order | Read reachability from the completed order. Compare a different legal tie rule without calling one universal order “the DFS order.” | Same set, justified orders |
| 86–90 | Exit and Gate C | Ask why one start cannot reach vertex 5 and what an all-vertex outer loop might do. Release investigation. | Component prediction |

## Stage B Cognitive Pause — exactly three targets

The pause uses this graph, which differs from the reveal and canonical graph:

```text
V = 5
0 → 1   0 → 2   1 → 3   3 → 1   2 → 4
```

State before timing:

- recursive DFS scans outgoing neighbors in ascending index order;
- iterative DFS scans them in descending order before pushing;
- a successful push is followed immediately by a seen mark; and
- Stack contents are written bottom to top.

The exact three targets are:

1. Give the recursive visit order from 0 and the final visited vertices.
2. At vertex 3 while examining `3 → 1`, state vertex 1’s visited value, the
   exact next action, and what repeats without that check.
3. For iterative DFS, give the visited set, Stack, and output after
   processing 0 and scheduling its neighbors, then after processing 1 and
   scheduling its neighbor; explain why descending scanning makes a lower
   index leave first.

Private responses:

1. order `0, 1, 3, 2, 4`; visited `{0,1,2,3,4}`;
2. `visited[1]` is `true`, so skip the edge and make no call; without that
   check, `1, 3, 1, 3, ...` repeats; and
3. after 0: visited `{0,1,2}`, Stack `2,1`, output `0`; after 1: visited
   `{0,1,2,3}`, Stack `2,3`, output `0,1`. Descending scanning pushes the
   smaller index later, and last-in, first-out removal therefore selects it
   sooner.

Do not add another target or provide these answers during the pause.

## Canonical recursive trace

Teach this language-independent pattern:

```text
visit(vertex):
    mark vertex seen
    record vertex
    for each possible outgoing neighbor in ascending order:
        if the edge exists and the neighbor is not seen:
            visit(neighbor)
```

From vertex 0:

| Event | Active calls, oldest first | Seen | Order |
|---|---|---|---|
| enter 0 | `0` | `{0}` | `0` |
| enter 1 | `0,1` | `{0,1}` | `0,1` |
| enter 3 | `0,1,3` | `{0,1,3}` | `0,1,3` |
| enter 4 | `0,1,3,4` | `{0,1,3,4}` | `0,1,3,4` |
| inspect `4 → 1` | unchanged | unchanged | unchanged |
| enter 2 after returning to 0 | `0,2` | `{0,1,2,3,4}` | `0,1,3,4,2` |
| inspect `2 → 3` | unchanged | unchanged | unchanged |

The graph stopping condition is not a `NULL` child. A recursive branch ends
after its row contains no unseen out-neighbor. The seen check prevents a
call along a returning or duplicate route.

## Canonical iterative trace

Teach:

```text
initialize vertex Stack
push start; after success, mark start seen
while pop succeeds:
    record popped vertex
    scan possible outgoing neighbors from high index to low:
        if the edge exists and the neighbor is not seen:
            push neighbor
            only after successful push, mark neighbor seen
destroy the Stack
commit output only after complete success
```

Required states, bottom to top:

| Event | Stack | Seen | Order |
|---|---|---|---|
| initial push | `0` | `{0}` | empty |
| visit 0; push 2, then 1 | `2,1` | `{0,1,2}` | `0` |
| visit 1; push 3 | `2,3` | `{0,1,2,3}` | `0,1` |
| visit 3; push 4 | `2,4` | `{0,1,2,3,4}` | `0,1,3` |
| visit 4; skip 1 | `2` | unchanged | `0,1,3,4` |
| visit 2; skip 3 | empty | unchanged | `0,1,3,4,2` |

Stack limit 2 succeeds. Limit 1 fails while vertex 0 tries to schedule its
second neighbor. The failed call publishes no partial order.

## Meeting A checks

Before Meeting B, verify that students can state:

- without seen tracking, `1 → 3 → 4 → 1` repeats;
- recursive DFS marks and records a vertex before scanning its row;
- iterative DFS marks immediately after a successful push;
- seen means waiting or completed, while the order contains completed
  visits;
- the canonical order is `0, 1, 3, 4, 2`;
- its reachable vertices are 0 through 4, not 5;
- Stack contents are written bottom to top;
- descending push order lets a smaller index pop first;
- a different documented tie rule may produce a different correct order;
  and
- one source does not cover a disconnected graph.

---

# Meeting B — Implement Checked Graph DFS (90 minutes)

## Coding question

> How can recursive calls or a vertex Stack explore every reachable vertex
> once and preserve every public contract?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval | Without notes, reproduce the canonical recursive order, the first two iterative Stack states, and the cycle skip. Preserve before comparison. | Retrieval trace |
| 8–15 | Gate D calibration | Open notes and models. Correct mark timing, direction, Stack orientation, and reachable-set language. | Annotated correction |
| 15–21 | Gate E orientation | Define public header, supplied support, starter, public test, extension test, and testing hook before naming files. | Package map |
| 21–31 | Public model and statuses | Read `Graph`, `GraphDfsOrder`, and `GraphDfsStatus`. Establish `V <= 16`, whole-graph validation, and unchanged-output promises. | Contract table |
| 31–43 | Recursive DFS | Build a local candidate, clear internal seen state, mark/record start, scan ascending outgoing neighbors, and commit only on success. | Recursive tests |
| 43–57 | Iterative DFS | Initialize the supplied vertex Stack, push/then-mark, record on pop, scan descending, map failures, destroy on every initialized path, and commit only on success. | Order, limit, allocation tests |
| 57–67 | Components | Require an undirected graph. Reuse one seen array across an ascending outer sweep; increment once for each unseen start. | Counts 2, 0, and isolated cases |
| 67–74 | Costs and representation | Count one full matrix-row scan per reached vertex. Contrast stored-neighbor iteration in an adjacency list. | `O(V²)`, `O(V+E)`, `O(V)` |
| 74–81 | Contract tests | Test invalid source, malformed graph, wrong kind, Stack limit, allocation failure, and byte-for-byte output preservation. | Boundary evidence |
| 81–86 | Safe autopsy | Predict bounded faulty output, locate the first missing or late seen decision, repair the decision, and name a regression test. | Autopsy record |
| 86–90 | Scope and submission | State synthetic scope, three student-test categories, evidence requirements, and completion window. | Submission checklist |

## Canonical public model

The public header is the source of truth:

```c
typedef struct {
    size_t vertices[GRAPH_MAX_VERTICES];
    size_t count;
} GraphDfsOrder;
```

The status enumeration appears in this exact order:

```text
GRAPH_DFS_OK
GRAPH_DFS_INVALID_ARGUMENT
GRAPH_DFS_OUT_OF_RANGE
GRAPH_DFS_INVALID_GRAPH
GRAPH_DFS_REQUIRES_UNDIRECTED
GRAPH_DFS_LIMIT
GRAPH_DFS_ALLOCATION
```

The exact public functions are:

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

`GRAPH_MAX_VERTICES` keeps Module 3's capacity of 16. `GraphDfsOrder.count` is from
zero through the graph’s active vertex count. Each reachable vertex appears
exactly once. Unused array positions have no public meaning.

Both traversal functions require a valid active start index. Therefore an
empty graph has no valid DFS start. In contrast, connected-component count
on an empty undirected graph succeeds with zero.

All output parameters change only on `GRAPH_DFS_OK`. Validate the complete
graph before traversal. Connected-component counting additionally requires
`GRAPH_UNDIRECTED`.

The supplied typed Stack uses these exact operations:

```c
vertex_stack_init
vertex_stack_validate
vertex_stack_push
vertex_stack_pop
vertex_stack_destroy
vertex_stack_status_name
```

Its statuses are `VERTEX_STACK_OK`, `VERTEX_STACK_INVALID_ARGUMENT`,
`VERTEX_STACK_LIMIT`, `VERTEX_STACK_UNDERFLOW`,
`VERTEX_STACK_ALLOCATION`, and `VERTEX_STACK_INVALID_STATE`. Its valid limit
is 0 through 16. It grows lazily from 0 to 4, 8, and 16, clipped to the
chosen limit. DFS treats underflow during its pop loop as normal completion,
maps Stack limit/allocation failures to graph-DFS statuses, and never exposes
a `VertexStackStatus` to its caller.

Failure-preservation summary:

| Operation | Failure examples | Preserved result |
|---|---|---|
| Recursive DFS | null pointer, malformed graph, inactive source | Complete prior `GraphDfsOrder` |
| Iterative DFS | the same, invalid/insufficient Stack limit, allocation failure | Complete prior `GraphDfsOrder`; initialized Stack is destroyed |
| Component count | null pointer, malformed graph, directed graph | Prior component count |

## Connected-component model

```text
clear seen
count = 0
for vertex from 0 through V - 1:
    if vertex is not seen:
        count += 1
        recursively mark everything reachable from vertex
```

For the companion graph:

```text
component 1: 0, 1, 3, 2, 4
component 2: 5
count: 2
```

The word component is restricted here to an undirected graph. On a directed
graph, ask which vertices are reachable from a stated source instead.

## Hint ladder

Reveal only one hint at a time:

1. Which vertex is current?
2. Which row represents its outgoing edges?
3. Has this destination already been scheduled or completed?
4. When must the seen mark be set relative to following the edge?
5. What does the completed order contain that the internal seen array does
   not expose?
6. For recursion, which calls are active and which row scan resumes next?
7. For iteration, what is the Stack bottom to top?
8. Which index should be popped next, and therefore which scanning direction
   should be used before pushes?
9. Did the push succeed before the seen mark changed?
10. Has every initialized Stack path reached destroy?
11. Can a result be committed before all work succeeds?
12. For components, is the graph undirected, and is one seen array reused
    across the complete outer sweep?
13. How many matrix cells are inspected for each reached vertex?

Stop after the first hint that restores productive work. Hint use guides
future instruction; it is not automatically a grade penalty.

## Common misconceptions

| Misconception | Diagnostic question | Correction |
|---|---|---|
| A graph can use the tree’s `NULL` stopping rule alone | “What happens at `4 → 1`?” | The edge returns to a real vertex; a seen check stops the repeat. |
| Mark after exploring all neighbors | “Can another route schedule this vertex first?” | Mark when the vertex is entered or immediately after its push succeeds. |
| Iterative code should mark before push | “What if that push fails?” | Push first; mark only after success. |
| Seen means already popped | “Why is vertex 2 seen while still in the Stack?” | Seen means scheduled or completed. |
| Stack contents are the visit order | “Has every stacked vertex been processed?” | The Stack is waiting work; order records popped vertices. |
| Scan ascending before iterative pushes | “Which pushed index will LIFO remove first?” | Scan descending when lower indexes should be processed first. |
| Recursive and iterative DFS must always have identical orders | “Could a pending seen vertex change later scheduling?” | They must reach the same set; exact order follows each stated rule. |
| DFS from one source visits the entire graph | “How is isolated vertex 5 reached?” | It is not; a component sweep starts again at unseen vertices. |
| Directed graphs have the same components used here | “Does an arrow work both ways?” | This module counts components only for undirected graphs. |
| A matrix DFS is `O(V+E)` | “How are absent neighbors discovered?” | Each visited row scans all `V` columns, giving worst-case `O(V²)`. |
| The output contains Boolean visited flags | “What fields exist in `GraphDfsOrder`?” | It contains only vertex indexes and a count. Membership means reachable. |
| A Stack-limit failure may return a partial order | “What does failure atomicity promise?” | Every failure leaves the caller’s entire output unchanged. |
| Reachability proves a security flaw | “What does one synthetic edge mean?” | It proves only reachability in the stated model. |

## Accessibility and pacing

- Pair every graph picture with its vertex list and exact edge list.
- Pair every recursive drawing with an oldest-to-newest active-call table.
- Pair every vertical Stack drawing with a bottom-to-top row.
- Pair seen marks with explicit sets such as `{0,1,3}`; do not rely on color.
- Read `adjacency[from][to]` aloud as “the cell for an edge from this row
  vertex to this column vertex.”
- Read `O(V²)` as “order V squared” and define it before using the notation.
- Permit cards, tactile markers, speech, typing, handwriting, or a scribe.
- Supply the linear inquiry and investigation when spatial layout is a
  barrier.
- During the pause, read all three targets and permit approved extended
  time, but provide no vocabulary access or content hint.
- Accept a numbered edge list, event list, or table instead of a drawing.
- Grade state transitions and contract reasoning, not drawing quality,
  typing speed, visual memory, or spoken fluency.
- Announce the independent completion window before coding starts.

## Evidence collected

1. preserved Gate A cycle and memory model;
2. exactly-three-target Cognitive Pause with later corrections;
3. canonical recursive call/seen trace;
4. canonical explicit-Stack trace;
5. reachable set from sources 0, 2, and 5;
6. recursive and iterative implementations;
7. undirected component trace and count;
8. invalid-input, wrong-kind, Stack-limit, allocation, and unchanged-output
   evidence;
9. matrix/list time and `O(V)` auxiliary-space explanation;
10. three original tests covering traversal/reachability, failure
    preservation, and components;
11. autopsy prediction, first bad decision, repair, and regression test; and
12. tree-to-graph and synthetic-security boundary statements.

## After Meeting B — transparent completion window

Allow approximately 75–105 additional minutes for students to finish
starter functions, run tests, write three original tests, complete the
autopsy, and submit the evidence form. Offer a staffed lab or equivalent
remote support. Public tests illustrate the contract but do not reveal every
instructor check. Instructor tests must exercise only published behavior.

## Instructor readiness checklist

- [ ] Stage A withholds the seen-array solution and exact canonical answer.
- [ ] The Stage B vocabulary remains closed during the pause.
- [ ] The pause has exactly three targets and uses its distinct five-vertex
      graph.
- [ ] The canonical directed graph is identified as Module 6's expanded fixture.
- [ ] Recursive DFS scans ascending and visits `0,1,3,4,2`.
- [ ] Iterative DFS scans descending, marks after successful push, and gives
      the required Stack states.
- [ ] Stack limit 2 succeeds and limit 1 fails atomically.
- [ ] The undirected fixture is explicitly a separate graph.
- [ ] Its components are `{0,1,2,3,4}` and `{5}`.
- [ ] Gate D follows a preserved Stage C A–F attempt.
- [ ] Gate E follows retrieval and Gate D calibration.
- [ ] Public types, status order, function names, and limit 16 match headers.
- [ ] Every failed public operation preserves its output.
- [ ] Empty graph DFS and empty graph component behavior are distinguished.
- [ ] Directed component counting is rejected.
- [ ] The autopsy is bounded and cannot recurse forever.
- [ ] Visual models have equivalent text or table forms.
- [ ] Synthetic scope and the completion window are announced.
