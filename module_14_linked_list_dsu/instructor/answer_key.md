# Instructor Answer Key - Module 14

## Macro-Question expert synthesis

A linked list preserves one reachable owned chain by saving the successor
before changing or releasing a node. DSU represents whole undirected
components with parent and component-size arrays. Two-pass find safely
replaces a long parent path with direct root links; union by size changes
one root link and two size/count fields. These local changes preserve the
global partition invariant. Kruskal will later use the same-root result to
reject a cycle-producing edge.

## Stage A - Informal inquiry

### A. Follow the records

- A1: R, Q, P; stored numbers 17, 23, 31; stop at END.
- A2: S says continue at R; the first-place marker changes from R to S.
- A3: copy P from Q's continuation before discarding Q; change R's
  continuation from Q to P.
- A4: at each record, preserve its continuation before discarding the
  current record; continue from the preserved place; stop at END. Track
  discarded places to ensure each is handled once.

### B. Maintain groups

| Report | Groups after the report |
|---:|---|
| 1, A with B | `{A,B}`, `{C}`, `{D}`, `{E}`, `{F}`, `{G}`, `{H}` |
| 2, C with D | `{A,B}`, `{C,D}`, `{E}`, `{F}`, `{G}`, `{H}` |
| 3, A with C | `{A,B,C,D}`, `{E}`, `{F}`, `{G}`, `{H}` |
| 4, E with F | `{A,B,C,D}`, `{E,F}`, `{G}`, `{H}` |
| 5, G with H | `{A,B,C,D}`, `{E,F}`, `{G,H}` |
| 6, E with G | `{A,B,C,D}`, `{E,F,G,H}` |
| 7, A with E | `{A,B,C,D,E,F,G,H}` |

B2: D and H are already in the one final group, so the later report does
not combine separate groups.

B3: many informal schemes are acceptable. Strong answers keep one current
leader for each group and a short way for each card to reach that leader.
Do not require formal DSU wording at this gate.

### C. Limit the claim

Supported: processed reports place the two device cards in one modeled
group. Unsupported examples: authorization, trust, compromise, route
quality, shortest route, resilience, or truth of the reports.

### D. Initial synthesis

Accept a clear initial rule that preserves a later record before discarding
the current one and updates a compact group record after each relationship.
It need not be the final algorithm.

## Stage B - Cognitive Pause

### Target 1 - Delete 23

```text
previous=R
victim=Q
successor=P
```

Save `Q->next` as P while Q is live. Set `R->next=P`, release Q, then
decrease size to 2. Exact result:

```text
head=R, size=2, limit=4
R(17)->P(31)->NULL
```

Reading `Q->next` after release is a use-after-free because Q's lifetime
has ended.

### Target 2 - Find H

First-pass path:

```text
H->G->E->A
```

The second pass assigns A to H, G, and E. E already stores A, so the actual
changed entries are H and G.

```text
parent:         [A,A,A,C,A,E,A,A]
component_size: [8,0,0,0,0,0,0,0]
components:     1
```

Only parent shortcuts change. All eight IDs remain in A's component.

### Target 3 - Union D-H

D follows `D->C->A`; compression changes D's parent to A. H follows
`H->A`. Both roots are A, so union succeeds with `merged=false`.

```text
parent:         [A,A,A,A,A,E,A,A]
component_size: [8,0,0,0,0,0,0,0]
components:     1
```

The new undirected relationship is cycle-producing because an earlier
route already joins D and H. Any one correct limitation/trust warning earns
the scope item.

## Stage C - Investigation

## A. Read the linked representation - 10 points

### A1. Traverse

Node labels R, Q, P; values 17, 23, 31; stop when P's `next` is `NULL`.

### A2. Interpret symbols

- `LinkedNode *head`: head stores a `LinkedNode` address.
- `R->next`: access R's next-pointer field through R's pointer.
- `NULL`: no following node.

### A3. Check the invariant

The state is valid: nonnull head agrees with size 3; R, Q, P are three
distinct reachable nodes followed by `NULL`; `3<=4<=16`; no node repeats;
and the one list owns all three nodes.

## B. Trace safe list mutations - 15 points

### B1. Reconstruct the pushes

| Operation | Allocation | New `next` | Head | Size | Limit |
|---|---|---|---|---:|---:|
| initialize | none | none | `NULL` | 0 | 4 |
| push 31 | P | `NULL` | P | 1 | 4 |
| push 23 | Q | P | Q | 2 | 4 |
| push 17 | R | Q | R | 3 | 4 |

### B2. Remove the first 23

Compare R then Q. Use `previous=R`, `victim=Q`, `successor=P`. Save P,
relink R to P, release Q, decrement size. The result is
`R(17)->P(31)->NULL`, size 2, limit 4.

### B3. Destroy

Iteration 1 saves P and releases R. Iteration 2 saves `NULL` and releases
P. Exact final state:

```text
head=NULL, size=0, limit=0
```

## C. Diagnose ownership and failure - 10 points

### C1. Find the lifetime error

The read `victim->next` is the first invalid action because the preceding
`free(victim)` ended the object's lifetime. Repair: save successor, relink
the live predecessor or head, release victim, decrement size.

### C2. Preserve failures

Invalid argument/state, full, and allocation failures preserve head, size,
limit, node identities, values, and links. An absent removal is successful
with `out_removed=false`; it preserves topology and values.

### C3. Separate claims

Examples:

- memory safety: no released node is dereferenced;
- ownership: each allocated node has one release responsibility;
- integrity: exactly size distinct nodes lead to `NULL`;
- unsupported application claim: the incident record is true or
  authorized.

## D. Build and read the DSU forest - 15 points

### D1. Make eight singleton sets

```text
parent:         [A,B,C,D,E,F,G,H]
component_size: [1,1,1,1,1,1,1,1]
element_count:  8
components:     8
inactive positions 8..15: parent 16, size 0
```

### D2. Trace the seven unions

| Operation | Roots | Winner | `parent[A..H]` | `component_size[A..H]` | Components |
|---|---|---|---|---|---:|
| A-B | A,B | A | `[A,A,C,D,E,F,G,H]` | `[2,0,1,1,1,1,1,1]` | 7 |
| C-D | C,D | C | `[A,A,C,C,E,F,G,H]` | `[2,0,2,0,1,1,1,1]` | 6 |
| A-C | A,C | A | `[A,A,A,C,E,F,G,H]` | `[4,0,0,0,1,1,1,1]` | 5 |
| E-F | E,F | E | `[A,A,A,C,E,E,G,H]` | `[4,0,0,0,2,0,1,1]` | 4 |
| G-H | G,H | G | `[A,A,A,C,E,E,G,G]` | `[4,0,0,0,2,0,2,0]` | 3 |
| E-G | E,G | E | `[A,A,A,C,E,E,E,G]` | `[4,0,0,0,4,0,0,0]` | 2 |
| A-E | A,E | A | `[A,A,A,C,A,E,E,G]` | `[8,0,0,0,0,0,0,0]` | 1 |

### D3. State the DSU invariant

Every active parent is an active ID. Following parents reaches a
self-parent root within the active count. Each root's component size equals
its membership count; each nonroot's size is zero. Inactive positions use
parent 16 and size zero. `component_count` equals the number of roots.

## E. Compress and classify - 15 points

### E1. Find H

Path `H->G->E->A`. Assign A to H, G, E; E is already A. Result:

```text
parent:         [A,A,A,C,A,E,A,A]
component_size: [8,0,0,0,0,0,0,0]
```

### E2. Union D and H

D follows `D->C->A` and compresses to A. H follows `H->A`. Roots match,
`merged=false`, component count stays 1, and final parent is
`[A,A,A,A,A,E,A,A]`.

### E3. Reject before indexing

ID 7 is valid H. IDs 8 and 16 are out of range when `element_count=8`.
Checking first prevents an out-of-bounds read. Failure preserves the DSU
and output.

## F. Analyze cost, scope, and the spiral - 10 points

### F1. Match actual costs

| Operation | Cost |
|---|---:|
| push-front mutation core | `O(1)` |
| search/remove by value | `O(n)` |
| destroy/full list validation | `O(n)` |
| create all singleton sets | `O(n)` |
| optimized find/union sequence | amortized `O(alpha(n))` each |

Amortized means average across a sequence, accounting for occasional
longer operations. `alpha` grows extraordinarily slowly; no derivation is
required.

### F2. Do not hide validator cost

A complete scan before every operation adds its scan cost. It would make a
public push or DSU call no longer match the core bound being claimed.

### F3. Connect local changes

- list relink: one predecessor/head field changes; one owned acyclic chain
  remains reachable;
- compression: parent fields on one path change; the partition is
  identical;
- root attachment: one root parent, two size fields, and component count
  change; two whole components become one valid component.

### F4. Limit DSU claims

DSU stores a partition summary, not original relationships, directions,
weights, routes, permissions, redundancy, or efficient deletion history.

## G. Exactly three tests - 9 points

Strong examples:

1. canonical list plus duplicate-first removal, forced allocation failure,
   all-zero destroy, and zero live-node count;
2. make A–H, exact H compression, smaller-root tie, invalid ID/output
   preservation, and inactive sentinels;
3. relationship stream followed by repeated D-H and a self-loop, checking
   cycle flags, component counts, connected queries, final state, and trust
   scope.

Each must add at least one assertion not present in visible core tests.

## H. Isolated autopsy - 6 points

The first invalid action is reading `victim->next` after Q's release.
Correct order: save P, relink R to P, release Q, decrement size. Regression
result: values 17,31; size 2; two live nodes before destroy and zero after.

## I. Edge pre-lab and synthesis - 10 points

### I1. Build one logical list

Each edge ID occurs exactly twice. Ten incident records therefore represent
five logical edges. The two A-B edges have different IDs, so both survive.

### I2. Sort safely

```text
ID 0: A-B weight 1
ID 3: B-C weight 2
ID 2: A-C weight 3
ID 1: A-B weight 4
ID 4: C-D weight 5
```

Relational comparison never computes `left-right`, so extreme signed
values cannot make that subtraction overflow.

### I3. Preview Kruskal

Accept A-B/1, then B-C/2. A and C now share a root, so A-C/3 is the first
cycle-producing sorted edge. A-B/4 is also cycle-producing later.

### I4. Exit synthesis

A complete answer connects safe successor preservation, path compression,
root attachment, invariant preservation, and Kruskal's future same-root
cycle check without claiming DSU returns routes or trust.

## Stage E implementation key

### TODO 1 - linked list

Push allocates before commit. Removal uses `current` and `previous`, saves
`current->next`, repairs head or predecessor, releases the victim, then
decrements size. Destroy saves the successor before each release and zeros
all three public fields.

### TODO 2 - make-set and find

Make-set uses `new_element=element_count`, verifies the inactive sentinel,
then commits parent, size, both counts, and output. Find locates a bounded
valid root without mutation, compresses only after success, then publishes
the root.

### TODO 3 - union

Locate both roots before mutation. Same-root success compresses both input
paths and publishes false. Otherwise verify component sizes and safe sum,
compress paths, select size winner/smaller-ID tie winner, attach the loser,
move its size, decrement component count, and publish true.

## Final gate

Do not approve final evidence until list cleanup reaches the all-zero
state, exact arrays match, all three test categories add value, and the
student states that shared DSU membership is not authorization or trust.
