# Module 15 Models - Prim, Kruskal, and Minimum Connection

Every numbered model includes the same information in a visual or tabular
form and an ordered linear text equivalent. No answer depends on color,
spacing, or drawing quality.

## Model 1 - Canonical weighted undirected graph

```text
        4(ID0)
    A -------- B
    | \       / \
 4  |  \10  1   \5
ID1 | ID7\ ID2   \ID3
    |     \ /     \
    C -----       D
     \ 2(ID4)    /
      \          / 3(ID6)
    3  \        /
   ID5  \      /
         E
```

All eight exact records appear below.

| ID | Endpoints | Weight |
|---:|:---:|---:|
| 0 | A-B | 4 |
| 1 | A-C | 4 |
| 2 | B-C | 1 |
| 3 | B-D | 5 |
| 4 | C-D | 2 |
| 5 | C-E | 3 |
| 6 | D-E | 3 |
| 7 | A-E | 10 |

### Linear equivalent 1

There are five vertices A, B, C, D, and E. The eight logical undirected
edges are, in edge-ID order: ID0 A-B weight 4; ID1 A-C weight 4; ID2 B-C
weight 1; ID3 B-D weight 5; ID4 C-D weight 2; ID5 C-E weight 3; ID6 D-E
weight 3; and ID7 A-E weight 10.

## Model 2 - One graph, two storage views

Edge-list view:

```text
0: A B 4    1: A C 4    2: B C 1    3: B D 5
4: C D 2    5: C E 3    6: D E 3    7: A E 10
```

Indexed adjacency-list view:

```text
A: ID0 B/4, ID1 C/4, ID7 E/10
B: ID0 A/4, ID2 C/1, ID3 D/5
C: ID1 A/4, ID2 B/1, ID4 D/2, ID5 E/3
D: ID3 B/5, ID4 C/2, ID6 E/3
E: ID5 C/3, ID6 D/3, ID7 A/10
```

The edge list has 8 logical records. The adjacency rows have 16 incident
records.

### Linear equivalent 2

The edge list stores exactly one record for each of IDs 0 through 7: A-B4,
A-C4, B-C1, B-D5, C-D2, C-E3, D-E3, and A-E10. The indexed adjacency list
stores ID0 in rows A and B; ID1 in A and C; ID2 in B and C; ID3 in B and D;
ID4 in C and D; ID5 in C and E; ID6 in D and E; and ID7 in A and E. Thus
there are 8 logical records and 16 incident records.

## Model 3 - Shortest-path tree versus MST

| Question | Selected edges | Edge sum | A-to-C path | A-to-C cost |
|---|---|---:|---|---:|
| Dijkstra from A | AB, AC, CD, CE | 13 | A-C | 4 |
| One MST | AB, BC, CD, CE | 10 | A-B-C | 5 |

### Linear equivalent 3

Dijkstra from A selects AB, AC, CD, and CE. Their weights sum to 13, and
its A-to-C path is A-C with cost 4. One MST selects AB, BC, CD, and CE.
Their weights sum to 10, and its A-to-C path is A-B-C with cost 5. The
first result minimizes source paths; the second minimizes selected-edge
total.

## Model 4 - Tree, cycle, and forest

```text
Tree T:       AB, BC, CD, CE
T plus AC:   cycle A-B-C-A

Boundary forest:
component 1  {A,B,C}
component 2  {D,E}
component 3  {F}
V=6, c=3, selected edges=V-c=3
```

### Linear equivalent 4

The edge set AB, BC, CD, CE connects A through E without a cycle, so it is
a tree. Adding AC produces the cycle A-B-C-A. In the boundary graph, the
three components are A-B-C, D-E, and isolated F. With V equal to 6 and c
equal to 3, a spanning forest contains 3 selected edges.

## Model 5 - Prim state after processing A

| Vertex | Key | Parent | In tree? |
|:---:|---:|:---:|:---:|
| A | 0 | - | yes |
| B | 4 | A | no |
| C | 4 | A | no |
| D | INF | - | no |
| E | 10 | A | no |

Expected frontier removal order:

```text
B/4, C/4, E/10
```

### Linear equivalent 5

After A is processed, A has key 0, no parent, and is in the tree. B has key
4 and parent A. C has key 4 and parent A. D has unknown key INF and no
parent. E has key 10 and parent A. B, C, D, and E are outside the tree. The
frontier's expected removal order is B/4, C/4, then E/10.

## Model 6 - Complete lazy Prim trace

| Pop | Action | Improvements |
|---|---|---|
| A/0 | start component | B=4/A, C=4/A, E=10/A |
| B/4 | select ID0 AB | C=1/B, D=5/B |
| C/1 | select ID2 BC | D=2/C, E=3/C |
| D/2 | select ID4 CD | E proposal 3 is equal; no change |
| E/3 | select ID5 CE | none |
| C/4 | stale; skip | none |
| D/5 | stale; skip | none |
| E/10 | stale; skip | none |

```text
selected IDs 0,2,4,5       total 10
pushes 8                   pops 8
stale pops 3               already-in-tree pops 0
frontier peak 5            incident scans 16
eligible crossing tests 8  key improvements 7
```

### Linear equivalent 6

Prim pops A/0 and records B=4 through A, C=4 through A, and E=10 through A.
It pops B/4, selects ID0 AB, improves C to 1 through B, and gives D key 5
through B. It pops C/1, selects ID2 BC, improves D to 2 through C, and
improves E to 3 through C. It pops D/2, selects ID4 CD, and leaves E
unchanged on the equal proposal 3. It pops E/3 and selects ID5 CE. It then
skips stale C/4, D/5, and E/10. Selected IDs are 0, 2, 4, and 5; total 10.
There are 8 pushes, 8 pops, 3 stale pops, 0 already-in-tree pops, peak 5,
16 incident scans, 8 eligible crossing tests, and 7 key improvements.

## Model 7 - Complete Kruskal decision ledger

| Sorted edge | Roots differ? | Decision | Running total |
|---|:---:|---|---:|
| ID2 BC1 | yes | add | 1 |
| ID4 CD2 | yes | add | 3 |
| ID5 CE3 | yes | add | 6 |
| ID6 DE3 | no | cycle skip | 6 |
| ID0 AB4 | yes | add | 10 |
| ID1 AC4 | no | cycle skip | 10 |
| ID3 BD5 | no | cycle skip | 10 |
| ID7 AE10 | no | cycle skip | 10 |

```text
selected IDs in decision order: 2,4,5,0
examined 8, cycle skips 4, self-loop skips 0
```

### Linear equivalent 7

Kruskal examines ID2 BC1 first; its roots differ, so it adds the edge and
the total becomes 1. It adds ID4 CD2 for total 3, then ID5 CE3 for total 6.
It skips ID6 DE3 because the roots match. It adds ID0 AB4 for total 10. It
skips IDs 1 AC4, 3 BD5, and 7 AE10 because each endpoint pair already has
one root. The selected order is 2, 4, 5, 0. It examines 8 edges, makes 4
cycle skips, and makes 0 self-loop skips.

## Model 8 - Kruskal's changing DSU groups

| Moment | Groups |
|---|---|
| start | {A} {B} {C} {D} {E} |
| after BC | {A} {B,C} {D} {E} |
| after CD | {A} {B,C,D} {E} |
| after CE | {A} {B,C,D,E} |
| after skipped DE | {A} {B,C,D,E} |
| after AB | {A,B,C,D,E} |
| after remaining skips | {A,B,C,D,E} |

### Linear equivalent 8

Kruskal begins with five one-vertex groups A, B, C, D, and E. Adding BC
creates group B-C. Adding CD creates B-C-D. Adding CE creates B-C-D-E.
Skipping DE leaves those groups unchanged. Adding AB creates one group
A-B-C-D-E. Skipping AC, BD, and AE leaves that final group unchanged.

## Model 9 - Four canonical MSTs

Every minimum result contains:

```text
required: BC1 and CD2
choose one: AB4 or AC4
choose one: CE3 or DE3
```

| MST | Selected edges | Total |
|---:|---|---:|
| 1 | BC, CD, AB, CE | 10 |
| 2 | BC, CD, AB, DE | 10 |
| 3 | BC, CD, AC, CE | 10 |
| 4 | BC, CD, AC, DE | 10 |

### Linear equivalent 9

All four canonical MSTs contain BC weight 1 and CD weight 2. MST 1 adds AB
weight 4 and CE weight 3. MST 2 adds AB and DE weight 3. MST 3 adds AC
weight 4 and CE. MST 4 adds AC and DE. Each has four edges and total 10.

## Model 10 - Equal totals, different deterministic edges

All-weight-1 square:

```text
ID0 A-D    ID1 C-D    ID2 A-B    ID3 B-C
```

| Algorithm | Selected IDs | Selected edges | Total |
|---|---|---|---:|
| Prim from A | 0, 2, 1 | AD, AB, CD | 3 |
| Kruskal | 2, 0, 3 | AB, AD, BC | 3 |

### Linear equivalent 10

The square has ID0 AD, ID1 CD, ID2 AB, and ID3 BC, all with weight 1.
Stable Prim from A selects IDs 0, 2, and 1: AD, AB, and CD. Kruskal's
normalized-endpoint order selects IDs 2, 0, and 3: AB, AD, and BC. The edge
sets differ, but each total is 3.

## Model 11 - Negative, parallel, loop, and isolated boundaries

| ID | Edge | Weight | Kruskal decision |
|---:|:---:|---:|---|
| 5 | E-E | -9 | self-loop skip |
| 1 | B-C | -2 | add |
| 3 | D-E | 1 | add |
| 4 | D-E | 1 | parallel cycle skip |
| 2 | A-C | 3 | add |
| 0 | A-B | 4 | cycle skip |

F is isolated.

```text
Prim selected order:     ID2, ID1, ID3
Kruskal selected order:  ID1, ID3, ID2
components 3, selected 3, total 2
```

### Linear equivalent 11

The boundary graph has ID0 AB4, ID1 BC-2, ID2 AC3, IDs 3 and 4 as parallel
DE1 edges, ID5 as self-loop EE-9, and isolated F. Kruskal first skips ID5,
adds ID1, adds ID3, skips parallel ID4, adds ID2, and skips ID0. Prim
selects IDs 2, 1, and 3; Kruskal selects IDs 1, 3, and 2. Both produce three
components, three selected edges, and total 2.

## Model 12 - Minimum cost versus one-edge resilience

Canonical MST:

```text
A -- B -- C -- D
          |
          E
```

Selected edges are AB, BC, CD, and CE.

| Change | Result |
|---|---|
| remove BC | groups {A,B} and {C,D,E} |
| add AC before removing BC | A-C is a backup around BC |
| add AC before removing AB | A-C-B is a backup around AB |
| add only AC, then remove CD | D is still separated |

### Linear equivalent 12

The canonical MST contains AB, BC, CD, and CE. Removing BC separates A-B
from C-D-E. If unselected AC is also built, AC supplies a backup around a
BC failure, and A-C-B supplies a backup around an AB failure. Adding only AC
does not protect CD: removing CD still separates D. Therefore one extra
edge protects only the tree edges on its newly created cycle, not the whole
network.
