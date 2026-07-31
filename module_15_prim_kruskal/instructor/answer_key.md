# Instructor Answer Key - Module 15

Student wording may differ. Require exact decisions, totals, contracts, and
evidence rather than memorized prose. Preserve first attempts and label
corrections.

## Stage A - Informal inquiry

### A. Separate two goals

The lowest-price A-to-E route is IDs 1 and 5:

```text
A-C-E: 4+3=7
```

It includes only A, C, and E. It does not connect B or D into one shared
plan.

### B. Buy best A-routes separately

```text
B: ID0 AB, cost 4
C: ID1 AC, cost 4
D: IDs1,4 AC-CD, cost 6
E: IDs1,5 AC-CE, cost 7
```

Distinct purchased IDs are 0, 1, 4, and 5, totaling:

```text
4+4+2+3=13
```

### C. Grow from reached sites

| Step | ID | Reached afterward | Running total |
|---:|---:|---|---:|
| 1 | 0 AB4 | A,B | 4 |
| 2 | 2 BC1 | A,B,C | 5 |
| 3 | 4 CD2 | A,B,C,D | 7 |
| 4 | 5 CE3 | A,B,C,D,E | 10 |

ID0 wins the initial weight-4 tie. ID5 wins the final weight-3 tie. Sharing
BC permits a lower total than independently buying the best A-route edges.

### D. Join separate groups

Offer order is IDs `2,4,5,6,0,1,3,7`.

```text
ID2 add:  {A} {B,C} {D} {E}, total1
ID4 add:  {A} {B,C,D} {E}, total3
ID5 add:  {A} {B,C,D,E}, total6
ID6 skip: D and E already joined
ID0 add:  {A,B,C,D,E}, total10
```

The prompt may stop here. The formal full Kruskal trace later also skips IDs
1, 3, and 7. Equal choices allow exactly four total-10 plans: fixed BC and
CD, either AB or AC, and either CE or DE.

### E. Missing and broken

With isolated F, the honest result connects A through E and leaves F alone.
Removing any one of IDs 0, 2, 4, or 5 disconnects the selected four-edge
plan. Lowest build price does not promise backup service.

## Stage B - Cognitive Pause

### Target 1 - Two goals

```text
Dijkstra edges AB,AC,CD,CE: sum13
Dijkstra A-C path: A-C, cost4

MST edges AB,BC,CD,CE: total10
MST A-C path: A-B-C, cost5
```

Dijkstra answers the source-route question. The MST answers the
whole-network edge-total question. A connected five-vertex result has
`5-1=4` selected edges.

### Target 2 - Prim

```text
A/0: B=4/A, C=4/A, E=10/A
B/4: select ID0; C=1/B, D=5/B
C/1: select ID2; D=2/C, E=3/C
D/2: select ID4; D-E proposal3 equals E key3, no change
E/3: select ID5
C/4, D/5, E/10: stale
```

Exact result:

```text
IDs 0,2,4,5                 total10
pushes8                     pops8
stale3                      already-in-tree0
peak5                       incident scans16
eligible crossings8         key improvements7
```

### Target 3 - Kruskal, forest, and scope

The full canonical decision order is:

```text
BC1 add, CD2 add, CE3 add, DE3 skip,
AB4 add, AC4 skip, BD5 skip, AE10 skip
```

With isolated F, `V=6`, `c=2`, and `V-c=4`; the result is an MSF. Prim
restarts at the smallest unvisited vertex. Minimum total neither adds a
backup edge nor authenticates stored weights.

## Stage C - Investigation

### A. Objectives and representations

Adjacency rows:

```text
A: ID0 B4, ID1 C4, ID7 E10
B: ID0 A4, ID2 C1, ID3 D5
C: ID1 A4, ID2 B1, ID4 D2, ID5 E3
D: ID3 B5, ID4 C2, ID6 E3
E: ID5 C3, ID6 D3, ID7 A10
```

The edge list stores 8 logical records; adjacency stores 16 incident
records. Negative weights are accepted. Self-loops remain input but are
never selected. Parallel IDs remain separate. Invalid endpoints are
rejected before indexing. The standard MST contract is undirected.

The objective contrast is the Target 1 result above.

### B. Exact Prim trace

Before the first pop:

```text
key       A=0, B=INF, C=INF, D=INF, E=INF
parent    A=-, B=-,   C=-,   D=-,   E=-
in_tree   false for all
frontier  A/0
```

Expected removal-order views:

```text
after A: B4,C4,E10
after B: C1,C4,D5,E10
after C: D2,E3,C4,D5,E10
after D: E3,C4,D5,E10
after E: C4,D5,E10
then:    D5,E10
then:    E10
then:    empty
```

The complete result and counters are those under Target 2. The D-to-E
proposal is equal, and strict improvement requires smaller, so E retains
parent C and ID5.

Boundary graph:

```text
ID0 AB4, ID1 BC-2, ID2 AC3,
ID3 DE1, ID4 DE1, ID5 EE-9, F isolated
```

Prim behavior:

```text
root A: select ID2 AC3, then ID1 BC-2
root D: select ID3 DE1; ID4 equality changes nothing
root F: no edge
```

Exact boundary result:

```text
selected order 2,1,3        total2
roots A,D,F                 components3
selected3                   V-c=6-3=3
pushes7 / pops7             stale1 / already0
peak2                       incident scans12
eligible crossings5         improvements4
```

### C. Exact Kruskal trace

Canonical:

| Edge | Roots before | Decision | Groups after | Total |
|---|---|---|---|---:|
| ID2 BC1 | B,C | add | {A}{BC}{D}{E} | 1 |
| ID4 CD2 | BC,D | add | {A}{BCD}{E} | 3 |
| ID5 CE3 | BCD,E | add | {A}{BCDE} | 6 |
| ID6 DE3 | same | cycle skip | unchanged | 6 |
| ID0 AB4 | A,BCDE | add | {ABCDE} | 10 |
| ID1 AC4 | same | cycle skip | unchanged | 10 |
| ID3 BD5 | same | cycle skip | unchanged | 10 |
| ID7 AE10 | same | cycle skip | unchanged | 10 |

```text
selected order 2,4,5,0
examined8, cycle skips4, self-loop skips0, components1, total10
```

The comparator compares weight, `u`, `v`, and edge ID relationally. Numeric
subtraction can overflow at `INT64_MIN` and `INT64_MAX`.

Boundary Kruskal order:

```text
ID5 EE-9 self-loop skip
ID1 BC-2 add
ID3 DE1 add
ID4 DE1 cycle skip
ID2 AC3 add
ID0 AB4 cycle skip
```

It selects `1,3,2`, examines 6, has 2 cycle skips and 1 self-loop skip,
three components, three selected edges, and total 2.

### D. Structural and minimum validation

Structural checks:

- graph and count ranges;
- selected records exactly match distinct input IDs;
- normalized valid endpoints;
- no selected self-loop or DSU cycle;
- selected partition equals the input partition;
- selected count equals `V-c`;
- inactive records are zero; and
- recorded total equals the order-independent mathematical sum.

These do not alone prove minimum cost.

For canonical selected IDs `0,2,4,5`, exchange checks are:

```text
ID1 AC4: path A-B-C maximum4; equality permits an alternative
ID3 BD5: path B-C-D maximum2; 5 is larger
ID6 DE3: path D-C-E maximum3; equality permits an alternative
ID7 AE10: path A-B-C-E maximum4; 10 is larger
```

No unselected edge is lighter than its path maximum, so the tree is
minimum. A smaller unselected weight proves `MST_NOT_MINIMUM`; equality
permits another MST; a larger value cannot improve by that exchange.

All-weight-1 square:

```text
ID0 AD, ID1 CD, ID2 AB, ID3 BC
Prim:     IDs0,2,1 = AD,AB,CD, total3
Kruskal:  IDs2,0,3 = AB,AD,BC, total3
```

Totals and component partitions agree; edge IDs may differ.

### E. Cost, representation, and resilience

```text
indexed lazy Prim time    O(V + E log(E+1))
Prim extra storage       O(V+E)
Kruskal sort             O(E log E)
Kruskal DSU              near-linear after sorting
explicit full validator  O(V + E + EV)
```

Scanning all incident records for each selected vertex incorrectly adds
`O(VE)`. The supplied indexed adjacency view is built once in `O(V+E)`.

An edge list, especially an already sorted one, naturally favors Kruskal.
An indexed adjacency list naturally favors Heap Prim. Very dense simple
input can favor `O(V^2)` matrix Prim over sorting `O(V^2)` edges, but that is
not the lab implementation. Include `O(V+E)` view building and
`O(E log E)` sorting when the actual interface performs them.

Removing BC from the canonical MST yields `{A,B}` and `{C,D,E}`. Adding AC
creates cycle A-B-C-A and protects AB and BC against a single failure. It
does not protect CD or CE. One extra edge protects only edges on its cycle.

### F. Numeric and spiral contracts

Large triangle:

```text
AB 2,000,000,000
BC 2,000,000,000
AC 2,100,000,000
```

The MST uses AB and BC for `4,000,000,000`, which exceeds signed 32-bit
range and fits `int64_t`.

The mathematical sum of `INT64_MAX, 1, -1` is `INT64_MAX`. A validator must
accept it regardless of array order by canceling signs before bounded
same-sign accumulation. `INT64_MAX+1` without cancellation is outside the
final range and returns `MST_TOTAL_OUT_OF_RANGE` with output preserved.

Roles:

- Heap: remove the minimum pending Prim key;
- DSU: track changing Kruskal components;
- Dijkstra distance: total cost from one source;
- Prim key: one candidate crossing-edge weight; and
- AVL invariant: ordered search plus bounded balance.

Local safe-edge/root decisions preserve a global minimum model but establish
neither trust nor resilience.

### G. Exactly three tests

Required categories:

1. Prim lazy trace and restart;
2. Kruskal filtering and ties; and
3. boundaries, preservation, and cross-validation.

Each adds a meaningful assertion beyond visible core tests.

### H. Cycle autopsy

For IDs 0 AB1, 1 BC2, and 2 AC3:

```text
after AB: {AB}{C}
after BC: {ABC}
AC raw endpoints differ, but representative roots match
```

The faulty code selects IDs 0,1,2, count 3, total 6, and a cycle.
The corrected order is find both roots, compare, skip equal roots, otherwise
store the edge, then union. It selects IDs 0,1, count 2, total 3,
component count 1, and validates as `MST_OK`. The faulty result returns
`MST_INVALID_RESULT`.

### I. Synthesis

A strong algorithm-selection memo names the existing representation,
density, conversion cost, and actual implementation bound. A structurally
valid forest satisfies shape and partition rules; a minimum forest also
passes the exchange check; resilience and trustworthy input are separate
requirements.

Strong macro response:

> Prim repeatedly adds a minimum crossing edge, while Kruskal repeatedly
> adds the next sorted edge joining different DSU roots. Both minimize the
> total selected weight across each component. Dijkstra instead minimizes
> source-to-vertex path costs, and none of these modeled results alone
> supplies backup service or trustworthy real-world input.

## Stage E implementation key

### Cluster 1 - Prim restart/pop/filter/select

- validate and build the indexed view;
- initialize complete local state;
- use one forward-only cursor to restart at the smallest unvisited ID when
  empty;
- compare saved key before the membership test;
- count stale and already-selected skips separately;
- store a nonroot's exact parent edge; and
- store caller output only after complete success.

### Cluster 2 - Prim scan/improve/push

- scan only the current indexed adjacency row;
- count every incident and eligible crossing;
- ignore loops and already-selected destinations;
- require strict smaller weight;
- push the prepared snapshot before committing key/parent/ID; and
- preserve output after allocation or limit failure.

### Cluster 3 - Kruskal sorted DSU scan

- build and relationally sort one logical edge list;
- examine all edges;
- count self-loops separately;
- compare representative roots, not raw endpoints;
- store before union;
- retain parallel IDs; and
- calculate the final total order-independently.

## Status and preservation checkpoints

Expected exact names:

```text
MST_OK
MST_INVALID_ARGUMENT
MST_OUT_OF_RANGE
MST_LIMIT
MST_INVALID_GRAPH
MST_INVALID_WEIGHT_TEXT
MST_WEIGHT_OUT_OF_RANGE
MST_ALLOCATION
MST_TOTAL_OUT_OF_RANGE
MST_INVALID_RESULT
MST_NOT_MINIMUM
MST_INVALID_STATE
```

All failure statuses preserve the complete caller output. Full validation is
explicit and does not change ordinary Prim or Kruskal complexity.
