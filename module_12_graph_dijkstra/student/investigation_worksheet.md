# Stage C - Investigation Worksheet: Least Total Cost

Name: ____________________________
Date: ____________________________

Preserve Sections A through F before opening Stage D. Sections G through I
are later testing, autopsy, and synthesis work.

## Quick reference

`dist[v]` is vertex `v`'s current modeled cost. `pred[v]` is its predecessor.
`INF` equals `SIZE_MAX` and marks no finite representable path currently
known. A snapshot `v/d` saves vertex `v` and distance `d`.

For edge `u->v`:

```text
candidate = dist[u] + weight(u,v)
update only when candidate < dist[v]
stale when popped distance != dist[u]
```

The arrow `->` means from left to right, `<` means smaller than, and `!=`
means not equal.

Guard the addition and return `DIJKSTRA_COST_RANGE` if it would overflow or
equal `INF`.

## Canonical six-vertex graph

IDs are `A=0, B=1, C=2, D=3, E=4, F=5`. A is the source.

| From | To | Weight |
|:---:|:---:|---:|
| A | B | 9 |
| A | C | 2 |
| A | E | 14 |
| B | D | 0 |
| B | E | 8 |
| C | B | 2 |
| C | D | 2 |
| D | E | 2 |

Outgoing edges are inspected by increasing destination ID.

## A. Contrast BFS with total cost

### A1. Run the earlier layer rule

Ignoring weights, state the BFS path from A to E and its edge count.

____________________________________________________________________

### A2. Add its cost

Add the weights on that BFS path.

____________________________________________________________________

### A3. Check the longer path

For `A,C,D,E`, state edge count and total cost. Explain why it defeats the
claim that fewer edges always means lower total cost.

____________________________________________________________________

### A4. State both promises

Complete:

```text
BFS minimizes:
Dijkstra minimizes:
```

## B. Trace Dijkstra exactly

### B1. Initialize

Complete the source, distance, predecessor, finalized, and frontier state
before the first pop.

____________________________________________________________________

### B2. Process A and C

Complete:

| Current pop | Successful relaxations | Distances after | Frontier after |
|---|---|---|---|
| `A/0` | | | |
| `C/2` | | | |

Why do both `B/9` and `B/4` remain stored?

____________________________________________________________________

### B3. Process the equal-distance tie

`B/4` was inserted before `D/4`, so the stable Queue removes B first.

For B to D, write the candidate, comparison with `dist[D]`, predecessor
decision, and insertion decision.

____________________________________________________________________

For B to E, record the successful change.

____________________________________________________________________

### B4. Finish current snapshots

Trace `D/4` and `E/6`. State when each distance becomes finalized.

____________________________________________________________________

### B5. Skip stale snapshots

For each remaining snapshot, compare its saved value with current `dist`.

| Snapshot | Current distance | Current or stale? | Action |
|---|---:|---|---|
| `B/9` | | | |
| `E/12` | | | |
| `E/14` | | | |

## C. Explain state and counts

### C1. Separate tentative and finalized

Why is B's value 9 tentative after A, while B's value 4 becomes finalized
only when `B/4` is removed?

____________________________________________________________________

### C2. Track predecessors

List every predecessor change for B, D, and E. Why does strict relaxation
leave D's predecessor unchanged on the equal proposal?

____________________________________________________________________

### C3. Count the canonical run

Complete:

```text
relaxation attempts:
successful relaxations:
snapshot pushes, including source:
snapshot pops:
stale skips:
peak frontier size:
normal Heap record comparisons:
```

### C4. Explain lazy duplicates

Why does a stale check make decrease-key unnecessary in this version?

____________________________________________________________________

## D. Reconstruct and verify

### D1. Record the result arrays

Write final distances and predecessors for A through F.

____________________________________________________________________

### D2. Reconstruct E

Write the backward predecessor chain, reverse it, and independently add the
edge weights.

____________________________________________________________________

### D3. Handle equal-cost alternatives

Show that `A,C,B,D,E` also costs 6. Why is the returned predecessor path
correct without being the only least-cost path?

____________________________________________________________________

### D4. Handle A and F

State the path and cost from A to A. Then state the status for a requested
path from A to F and what that claim is limited to.

____________________________________________________________________

## E. Enforce preconditions and numeric safety

### E1. Explain finalization

Why do zero-or-greater weights prevent a later unfinished route from
lowering the current smallest tentative distance?

____________________________________________________________________

### E2. Reject negative text

Consider `S->X` weight 2, `S->Y` weight 5, and `Y->X` weight -10. What is
the true cost to X, and why could early finalization of X at 2 fail?

Why must a parser reject `-10` before converting it to `size_t`?

____________________________________________________________________

### E3. Guard INF and overflow

State the checks required before `dist[u] + weight` is formed. Why must a
candidate equal to `INF` return `DIJKSTRA_COST_RANGE` rather than become an
ordinary distance?

____________________________________________________________________

### E4. Preserve failures

The **caller** is code requesting work; its **output** is where the answer is
written. An **allocation** reserves storage. **Ownership** means
responsibility for releasing that storage.

For invalid vertices, invalid graph state, negative text, allocation or
Queue limit failure, and cost-range failure, state what happens to caller
output and owned temporary storage.

____________________________________________________________________

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

```text
lazy Heap time:       O(V + E log(E + 1))
auxiliary state:      O(V + E)
simple-graph time:    O(V + E log V)
linear lazy backend:  O(V + E^2)
```

____________________________________________________________________

### F2. Avoid a decrease-key claim

Why would quoting a decrease-key complexity misdescribe this code?

____________________________________________________________________

### F3. State the 241-versus-64 boundary

A **capacity** is the maximum number of records storage can hold.

A simple directed 16-vertex graph can have 240 non-self edges. The source
plus at most one successful relaxation per edge permits 241 snapshot
insertions, and `O(E)` may be pending. Why does Module 11's capacity 64 not
prove general completion? State the required response to `FULL`.

____________________________________________________________________

### F4. Limit model and security claims

State four assumptions or facts Dijkstra cannot prove about real inspection
work, input authenticity, changing conditions, parallel work, or system
security.

____________________________________________________________________

### F5. Spiral 4 synthesis

**Synthesis** means combining earlier ideas. An **abstract data type (ADT)**
states what operations do without requiring one storage method. An
**application programming interface (API)** is the set of named operations
code calls.

Use the same canonical graph and source A for all three runs. For BFS,
ignore weights and complete the full reachable-vertex run; do not stop at E.

| Run | Path A to E | Add/remove call counts | Priority comparisons | API operation names |
|---|---|---|---:|---|
| BFS ignoring weights | | | not applicable | |
| Dijkstra with Module 10 linear Priority Queue | | | | |
| Dijkstra with Heap Priority Queue | | | | |

For the linear run, record each Priority Queue size just before removal and
show the comparison sum.

____________________________________________________________________

State the shared Priority Queue ADT behavior, the storage-specific
implementation details, and how linear `insert`/`extract-min` calls
correspond to Heap `push`/`pop` calls. Explain why one small comparison count
does not settle which implementation grows better on large input.

____________________________________________________________________

## G. Design exactly three tests - later work

### G1. Parser and range preservation

Cover accepted zero/plus/whitespace, negative and malformed text, decimal
overflow, reserved `SIZE_MAX`, exact statuses, and output preservation.

____________________________________________________________________

### G2. Lazy stale trace and equal predecessor

Run the canonical graph. Assert exact arrays, finalization/pop traces,
counters, three stale skips, and D predecessor C after the equal proposal.

____________________________________________________________________

### G3. Paths, source, unreachable, and preservation

Reconstruct E and A. Request F, an invalid destination, and a malformed
result. Assert exact statuses and complete path-output preservation.

____________________________________________________________________

## H. Analyze the bounded overflow autopsy - later work

Before running the supplied program, predict the faulty wrapped candidate
and correct `DIJKSTRA_COST_RANGE` result in `dijkstra_autopsy.md`.

## I. Exit synthesis - later work

### I1. Answer the macro-question

Use BFS objective, strict relaxation, finalized distance, stale snapshots,
and path reconstruction.

____________________________________________________________________

### I2. Correct three false claims

> Fewer edges always cost less. Equal candidates should replace the
> predecessor. A passing run proves the stored times describe reality.

____________________________________________________________________
