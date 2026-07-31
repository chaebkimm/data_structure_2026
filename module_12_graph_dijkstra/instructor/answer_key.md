# Instructor Answer Key - Module 12

Student wording may differ. Require the exact rule, state, or evidence
rather than memorized prose. Preserve first attempts and label corrections.

## Stage A - Informal inquiry

### A. Layer plan

The fewest-link route is A,E. It uses one link and costs 14 minutes.

### B. Longer route

`A,C,D,E` uses three links and costs:

```text
2 + 2 + 2 = 6
```

Fewest links and least total time are different goals because link times
are unequal.

### C. Best-total cards

After A:

| Place | Best total | Came from |
|:---:|---:|:---:|
| B | 9 | A |
| C | 2 | A |
| D | blank | blank |
| E | 14 | A |
| F | blank | blank |

C/2 is handled next because it has the smallest waiting total.

From C:

```text
B proposal 2+2 = 4, replacing 9; came from C
D proposal 2+2 = 4, replacing blank; came from C
```

### D. Old and equal cards

`B/9` is old because B's current best total is 4. B to D proposes `4+0=4`,
equal to D's existing total, so it does not replace D's came-from mark.
B to E proposes `4+8=12`, improving 14.

### E. Trust and limits

Zero-or-greater additions cannot make a later continuation smaller than the
current smallest waiting total. F's blank card means no route from A using
the listed directions has been found. It says nothing about unlisted or
real routes. Model limitations include changing time, parallel work,
inaccurate input, congestion, or nonadditive effects.

### F. Initial synthesis

Strong response:

> Keep a best total and came-from mark for each place. Repeatedly handle the
> smallest current waiting total, use its outgoing routes to propose
> improvements, and ignore old cards. This reasoning depends on every added
> time being zero or greater.

## Stage B - Cognitive Pause

All frontier lists below show expected removal order, not the Heap's internal
array layout.

### Target 1 - Separate edge count from total cost

The prior layer method is BFS. It chooses A,E because it minimizes edge
count. That route has one edge but cost 14; A,C,D,E has three edges and cost
6, so BFS does not minimize total weight.

### Target 2 - Finalize and relax strictly

B/4 leaves before D/4 because it was inserted first at the equal distance.
B becomes finalized at 4.

```text
B->D: candidate 4+0 = 4
4 < dist[D] is false
pred[D] stays C
no push

B->E: candidate 4+8 = 12
12 < 14 is true
dist[E] = 12
pred[E] = B
push E/12
```

Resulting frontier:

```text
D/4, B/9, E/12, E/14
```

### Target 3 - Skip, reconstruct, and limit the claim

`B/9` is stale because 9 differs from current `dist[B]` 4. Skip it before
scanning B's edges.

```text
backward E,D,C,A
forward  A,C,D,E
cost     2+2+2 = 6
```

F's `INF` means no finite representable directed path from A exists in the
stored validated graph. It does not prove real-world impossibility.

## Stage C - Investigation

### A. BFS contrast

```text
BFS path       A,E
edge count     1
cost           14

Dijkstra path  A,C,D,E
edge count     3
cost           6
```

BFS minimizes edge count. Dijkstra minimizes total nonnegative weight.

### B. Exact trace

Initialization:

```text
distance     0,INF,INF,INF,INF,INF
predecessor  -, -, -, -, -, -
finalized    false,false,false,false,false,false
frontier     A/0
```

After A/0:

```text
relax A->B: B=9 pred A, push B/9
relax A->C: C=2 pred A, push C/2
relax A->E: E=14 pred A, push E/14

distance 0,9,2,INF,14,INF
frontier C/2,B/9,E/14
```

After C/2:

```text
relax C->B: B=4 pred C, push B/4
relax C->D: D=4 pred C, push D/4

distance 0,4,2,4,14,INF
frontier B/4,D/4,B/9,E/14
```

Both B snapshots remain because this is lazy duplication.

After B/4:

```text
B->D: candidate 4 equals 4; no change
B->E: candidate 12 improves 14; pred E=B; push E/12

frontier D/4,B/9,E/12,E/14
```

After D/4:

```text
D->E: candidate 6 improves 12; pred E=D; push E/6
frontier E/6,B/9,E/12,E/14
```

E/6 is current and finalizes E. B/9, E/12, and E/14 are stale and skipped.

### C. State and counts

B=9 is tentative because a later path through C improves it. B=4 becomes
finalized only on the current minimum pop.

Predecessor changes:

```text
B: none -> A -> C
D: none -> C
E: none -> A -> B -> D
```

D remains C on equality because strict relaxation requires smaller, not
smaller-or-equal.

Canonical counts:

```text
relaxation attempts        8
successful relaxations     7
pushes including source    8
pops                       8
stale skips                3
peak Frontier size         4
normal Heap comparisons   17
```

Lazy duplicates avoid decrease-key by adding a new snapshot. The stale
test recognizes and skips the superseded one.

### D. Reconstruction

Final:

```text
distance     0,4,2,4,6,INF
predecessor  -,C,A,C,D,-
```

E:

```text
backward E,D,C,A
forward  A,C,D,E
cost 2+2+2 = 6
```

Alternative A,C,B,D,E costs `2+2+0+2=6`. The predecessor path is correct
but not unique.

Source-to-source path is A with cost 0. F path request returns
`DIJKSTRA_UNREACHABLE` and preserves output.

### E. Preconditions and safety

Nonnegative additions cannot reduce an unfinished route below the current
smallest tentative distance.

Negative counterexample:

```text
S->X 2
S->Y 5
Y->X -10
true X cost -5
```

Finalizing X at 2 is wrong. The parser must detect the leading minus before
unsigned conversion.

Arithmetic order:

```text
reject/skip dist[u] == DIJKSTRA_INF
if weight > DIJKSTRA_INF - dist[u]: DIJKSTRA_COST_RANGE
candidate = dist[u] + weight
if candidate == DIJKSTRA_INF: DIJKSTRA_COST_RANGE
then apply strict relaxation
```

Every failure preserves caller output and destroys temporary Frontier
storage. The graph is unchanged.

### F. Complexity and scope

```text
Heap lazy time        O(V + E log(E + 1))
auxiliary state       O(V + E)
simple graph          O(V + E log V)
linear lazy backend   O(V + E^2)
```

There are at most `E+1` pushes because strict relaxation succeeds at most
once per scanned edge, plus the source. No decrease-key is implemented.

A 16-vertex directed simple graph allows `16*15=240` arcs and up to 241
snapshot insertions. Module 11 capacity 64 is insufficient. Module 12
supplies capacity 241. A configured smaller limit returns `DIJKSTRA_LIMIT`;
no work is dropped.

The result cannot prove authenticity, completeness, static or additive
weights, parallel-work behavior, fairness, operational availability, or
system security.

### F5. Spiral 4 synthesis

Use a full reachable-vertex BFS run so the call counts are unambiguous.
An **abstract data type (ADT)** states behavior independent of storage. An
**application programming interface (API)** is the set of named operations
code calls. An **implementation** is the code and storage choice that
performs those operations.

| Run | A-to-E path | Add/remove calls | Record comparisons | API calls |
|---|---|---:|---:|---|
| BFS, weights ignored | A,E | 5 enqueue, 5 dequeue | not applicable | `vertex_queue_enqueue`, `vertex_queue_dequeue` |
| Dijkstra, Module 10 linear Queue | A,C,D,E | 8 insert, 8 extract-min | 14 | `alert_priority_queue_insert`, `alert_priority_queue_extract_min` |
| Dijkstra, Heap Frontier | A,C,D,E | 8 push, 8 pop | 17 | `dijkstra_frontier_push`, `dijkstra_frontier_pop` |

The linear Queue's sizes before its removals are:

```text
1,3,4,4,4,3,2,1
```

Because insert makes zero record comparisons, its extraction total is:

```text
0+2+3+3+3+2+1+0 = 14
```

The shared Priority Queue ADT behavior is to add a record and remove the
stable minimum: equal distances leave in insertion order. API call roles map
linear `insert`/`extract-min` to Heap `push`/`pop`. The Module 10 alert
record is adapted by treating its ID as the vertex and its priority as the
distance; this is a comparison activity, not a new Module 12 coding task.

The unsorted linear implementation scans all pending records during
extraction. The Heap implementation restores tree-shaped order after
insertion and removal. The Heap's 17 comparisons exceed the linear Queue's
14 on this small fixture; this does not contradict the Heap's better
large-input growth bound.

### G. Exactly three tests

Required categories:

1. parser and range preservation;
2. lazy stale trace and equal predecessor; and
3. paths, source, unreachable, and preservation.

### H. Autopsy

Frozen:

```text
dist[u] = SIZE_MAX - 3
weight = 5
old dist[v] = 20
```

Unchecked unsigned addition wraps to 1. Faulty strict relaxation accepts
`1 < 20`, corrupts distance/predecessor, and pushes false work.

Correct:

```text
DIJKSTRA_INF - dist[u] = 3
5 <= 3 is false
status DIJKSTRA_COST_RANGE
caller state preserved
```

All indexes remain valid; this is an arithmetic integrity defect.

### I. Synthesis

Model response:

> BFS minimizes edge count, while Dijkstra repeatedly finalizes the current
> smallest tentative modeled cost. Strict relaxation adds lazy snapshots
> only for improvements, and stale snapshots are skipped. Predecessors
> reconstruct one least-cost path under nonnegative, representable,
> additive stored weights.

Corrections:

- Fewer edges need not cost less.
- Equality does not replace predecessor or add a snapshot.
- Passing tests proves only the stated synthetic model and contracts.

## Stage E implementation key

### TODO 1 - parser

Accept ASCII space, optional plus, and decimal 0 through `SIZE_MAX-1`.
Distinguish negative, malformed, and range statuses. Preserve output.

### TODO 2 - shortest paths

Use complete local result state, limit `arc_count+1`, output-last commit, and
one cleanup path. Record every pop before stale handling. Count outgoing
edge attempts only for current pops. Guard arithmetic before addition. Push
an improved snapshot before committing local distance/predecessor.

### TODO 3 - reconstruction

Validate result and destination, reject `INF`, follow at most `vertex_count`
predecessors, detect repetition/range defects, reverse locally, set total
cost, and publish last.

## Canonical lab checkpoint

```text
finalized A,C,B,D,E
distance 0,4,2,4,6,INF
predecessor -,C,A,C,D,-
pop trace A/0,C/2,B/4,D/4,E/6,B/9*,E/12*,E/14*
attempts 8, successes 7
pushes 8, pops 8, stale 3, peak 4
Heap comparisons 17
E path A,C,D,E cost 6
```

`*` marks stale.

## Final gate

Require:

- exact objective contrast and canonical trace;
- strict equality behavior;
- stale-before-scan logic;
- negative and numeric range safety;
- output preservation and cleanup;
- exact three TODOs/tests;
- bounded reconstruction;
- actual lazy complexity;
- 241-versus-64 explanation; and
- honest model/security limits.
