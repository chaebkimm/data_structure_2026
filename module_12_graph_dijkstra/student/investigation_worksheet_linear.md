# Stage C - Investigation Worksheet: Least Total Cost

Name: ____________________________
Date: ____________________________

Preserve Sections A through F before opening Stage D. Sections G through I
are later testing, autopsy, and synthesis work. This linear form contains
the same facts, questions, and scoring as the standard form.

## Quick reference

`dist[v]` is vertex `v`'s current modeled cost. `pred[v]` is its predecessor.
`INF` equals `SIZE_MAX` and marks no finite representable path currently
known. A snapshot `v/d` saves vertex `v` and distance `d`.

For an edge from `u` to `v`, add `dist[u]` and its weight only after the
range guard. Update only when the candidate is smaller than `dist[v]`. A
popped snapshot is stale when its saved distance differs from `dist[u]`.
Return `DIJKSTRA_COST_RANGE` if a sum would overflow or equal `INF`.

## Canonical six-vertex graph

IDs are `A=0, B=1, C=2, D=3, E=4, F=5`. A is the source.

The directed weighted edges are:

1. A to B has weight 9;
2. A to C has weight 2;
3. A to E has weight 14;
4. B to D has weight 0;
5. B to E has weight 8;
6. C to B has weight 2;
7. C to D has weight 2; and
8. D to E has weight 2.

Outgoing edges are inspected by increasing destination ID.

## A. Contrast BFS with total cost

### A1. Run the earlier layer rule

Ignoring weights, state the BFS path from A to E and its edge count.

Response: ___________________________________________________________

### A2. Add its cost

Add the weights on that BFS path.

Response: ___________________________________________________________

### A3. Check the longer path

For A to C to D to E, state edge count and total cost. Explain why it
defeats the claim that fewer edges always means lower total cost.

Response: ___________________________________________________________

### A4. State both promises

State what BFS minimizes and what Dijkstra minimizes.

Response: ___________________________________________________________

## B. Trace Dijkstra exactly

### B1. Initialize

State the source, distance, predecessor, finalized, and frontier state
before the first pop.

Response: ___________________________________________________________

### B2. Process A and C

For current pops `A/0` and `C/2`, state every successful relaxation, all
distances, and the frontier after each pop.

Why do both `B/9` and `B/4` remain stored?

Response: ___________________________________________________________

### B3. Process the equal-distance tie

`B/4` was inserted before `D/4`, so the stable Queue removes B first.

For B to D, state the candidate, comparison with `dist[D]`, predecessor
decision, and insertion decision.

For B to E, record the successful change.

Response: ___________________________________________________________

### B4. Finish current snapshots

Trace `D/4` and `E/6`. State when each distance becomes finalized.

Response: ___________________________________________________________

### B5. Skip stale snapshots

For `B/9`, `E/12`, and `E/14`, state the current distance, whether the
snapshot is stale, and the action.

Response: ___________________________________________________________

## C. Explain state and counts

### C1. Separate tentative and finalized

Why is B's value 9 tentative after A, while B's value 4 becomes finalized
only when `B/4` is removed?

Response: ___________________________________________________________

### C2. Track predecessors

List every predecessor change for B, D, and E. Why does strict relaxation
leave D's predecessor unchanged on the equal proposal?

Response: ___________________________________________________________

### C3. Count the canonical run

State:

1. relaxation attempts;
2. successful relaxations;
3. snapshot pushes, including source;
4. snapshot pops;
5. stale skips;
6. peak frontier size; and
7. normal Heap record comparisons.

Response: ___________________________________________________________

### C4. Explain lazy duplicates

Why does a stale check make decrease-key unnecessary in this version?

Response: ___________________________________________________________

## D. Reconstruct and verify

### D1. Record the result arrays

Write final distances and predecessors for A through F.

Response: ___________________________________________________________

### D2. Reconstruct E

Write the backward predecessor chain, reverse it, and independently add the
edge weights.

Response: ___________________________________________________________

### D3. Handle equal-cost alternatives

Show that A to C to B to D to E also costs 6. Why is the returned
predecessor path correct without being the only least-cost path?

Response: ___________________________________________________________

### D4. Handle A and F

State the path and cost from A to A. Then state the status for a requested
path from A to F and what that claim is limited to.

Response: ___________________________________________________________

## E. Enforce preconditions and numeric safety

### E1. Explain finalization

Why do zero-or-greater weights prevent a later unfinished route from
lowering the current smallest tentative distance?

Response: ___________________________________________________________

### E2. Reject negative text

Consider S to X with weight 2, S to Y with weight 5, and Y to X with weight
-10. What is the true cost to X, and why could early finalization of X at 2
fail?

Why must a parser reject `-10` before converting it to `size_t`?

Response: ___________________________________________________________

### E3. Guard INF and overflow

State the checks required before `dist[u] + weight` is formed. Why must a
candidate equal to `INF` return `DIJKSTRA_COST_RANGE` rather than become an
ordinary distance?

Response: ___________________________________________________________

### E4. Preserve failures

The **caller** is code requesting work; its **output** is where the answer is
written. An **allocation** reserves storage. **Ownership** means
responsibility for releasing that storage.

For invalid vertices, invalid graph state, negative text, allocation or
Queue limit failure, and cost-range failure, state what happens to caller
output and owned temporary storage.

Response: ___________________________________________________________

## F. Analyze code choices and scope

### F1. Derive actual complexity

Let `V` mean active vertices and `E` mean directed edges. `O(n)` means work
may grow with all `n` items; `O(log n)` grows with Heap height.

A **backend** is the storage method behind a collection. A **parallel edge**
repeats a start/end pair; a **self-loop** returns to its starting vertex. A
**simple graph** has neither. **Auxiliary state** is extra storage beyond
the input. **Decrease-key** means lowering a priority already stored. An
**implementation** is the code and storage choice that performs an
operation.

Explain:

1. lazy Heap time is `O(V + E log(E + 1))`;
2. auxiliary state is `O(V + E)`;
3. simple-graph time is `O(V + E log V)`; and
4. the linear lazy backend is `O(V + E^2)`.

Response: ___________________________________________________________

### F2. Avoid a decrease-key claim

Why would quoting a decrease-key complexity misdescribe this code?

Response: ___________________________________________________________

### F3. State the 241-versus-64 boundary

A **capacity** is the maximum number of records storage can hold.

A simple directed 16-vertex graph can have 240 non-self edges. The source
plus at most one successful relaxation per edge permits 241 snapshot
insertions, and `O(E)` may be pending. Why does Module 11's capacity 64 not
prove general completion? State the required response to `FULL`.

Response: ___________________________________________________________

### F4. Limit model and security claims

State four assumptions or facts Dijkstra cannot prove about real inspection
work, input authenticity, changing conditions, parallel work, or system
security.

Response: ___________________________________________________________

### F5. Spiral 4 synthesis

**Synthesis** means combining earlier ideas. An **abstract data type (ADT)**
states what operations do without requiring one storage method. An
**application programming interface (API)** is the set of named operations
code calls.

Use the same canonical graph and source A for all three runs. For BFS,
ignore weights and complete the full reachable-vertex run; do not stop at E.

For each run below, record the A-to-E path, add/remove call counts, priority
comparison count or `not applicable`, and API operation names:

1. BFS ignoring weights;
2. Dijkstra with the Module 10 linear Priority Queue; and
3. Dijkstra with the Heap Priority Queue.

Response: ___________________________________________________________

For the linear run, record each Priority Queue size just before removal and
show the comparison sum.

Response: ___________________________________________________________

State the shared Priority Queue ADT behavior, the storage-specific
implementation details, and how linear `insert`/`extract-min` calls
correspond to Heap `push`/`pop` calls. Explain why one small comparison count
does not settle which implementation grows better on large input.

Response: ___________________________________________________________

## G. Design exactly three tests - later work

### G1. Parser and range preservation

Cover accepted zero/plus/whitespace, negative and malformed text, decimal
overflow, reserved `SIZE_MAX`, exact statuses, and output preservation.

Response: ___________________________________________________________

### G2. Lazy stale trace and equal predecessor

Run the canonical graph. Assert exact arrays, finalization/pop traces,
counters, three stale skips, and D predecessor C after the equal proposal.

Response: ___________________________________________________________

### G3. Paths, source, unreachable, and preservation

Reconstruct E and A. Request F, an invalid destination, and a malformed
result. Assert exact statuses and complete path-output preservation.

Response: ___________________________________________________________

## H. Analyze the bounded overflow autopsy - later work

Before running the supplied program, predict the faulty wrapped candidate
and correct `DIJKSTRA_COST_RANGE` result in `dijkstra_autopsy.md`.

## I. Exit synthesis - later work

### I1. Answer the macro-question

Use BFS objective, strict relaxation, finalized distance, stale snapshots,
and path reconstruction.

Response: ___________________________________________________________

### I2. Correct three false claims

> Fewer edges always cost less. Equal candidates should replace the
> predecessor. A passing run proves the stored times describe reality.

Response: ___________________________________________________________
