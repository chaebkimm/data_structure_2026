# Instructor Answer Key — Module 3 Graph

## Release control

Keep this file instructor-only through the student submission window. Stage A
answers are intentionally broad because students have not yet received graph
terminology. Evaluate whether the relationship facts are preserved, not
whether a student guesses the professional words.

The canonical six-vertex model used after Stage A is:

| ID | Vertex label | Directed out-neighbors |
|---:|---|---|
| `0` | Gateway | `1, 2` |
| `1` | Web | `3` |
| `2` | Admin | `3` |
| `3` | Database | `4` |
| `4` | Monitor | `1` |
| `5` | Archive | none |

Its directed edge set is:

```text
{(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (4, 1)}
```

An **edge set** is the mathematical collection of graph edges. It is not the
same object as an **edge-list representation**, which is a stored sequence of
endpoint records. The ordered pairs inside the set preserve edge direction;
the order in which the set’s pairs are written has no graph meaning.

---

# Stage A — Initial Inquiry

## A. Reconstruct the starting arrangement

Accept a drawing or text equivalent to:

```text
Gateway leads to Web.
Gateway leads to Admin.
Web leads to Database.
Database leads to Monitor.
Archive is separate.
```

- starting item: `Gateway`;
- separate item: `Archive`;
- route from Gateway to Monitor before the cross-link:
  `Gateway, Web, Database, Monitor`.

Do not require vertex, edge, graph, path, or isolated at this stage.

## B. Add relationships beyond the hierarchy

After `Admin` leads to `Database`:

- two immediate ways lead into Database: one from Web and one from Admin;
- Database no longer has one unique item directly above it;
- the relationship therefore does not fit the course tree rule of exactly
  one parent for every non-root node.

After `Monitor` leads to `Web`, the repeating route is:

```text
Web, Database, Monitor, Web, Database, Monitor, ...
```

A program that follows this route without remembering prior work or applying
a stopping rule may repeat forever and never finish.

## C. Direction

“Web leads to Database” does not prove “Database leads to Web.” The first
statement is one-way.

Accept any internally consistent examples. Common answers include:

- one-way: a software permission, web link, prerequisite, or one-way street;
- two-way: a direct friendship in a simplified model or a two-way road.

The quality test is whether reversing the endpoints preserves the intended
meaning.

## D. Macro-Question

Accept a first model that separately records:

- every object, including the separate Archive object;
- which two objects each relationship joins;
- which direction or directions are allowed; and
- enough information to preserve cross-links and the returning loop.

A student may invent a table, list, card system, or diagram. Do not require
the word graph before Gate B.

## E. Storage brainstorm

Expected ideas:

- one-way relationship fact: its starting item and destination;
- direct yes/no question: consult a table cell, pair record, or equivalent
  stored fact for that ordered pair;
- opposite directions: one direction does not automatically prove the
  reverse, so separate facts may be required;
- Archive: preserve it in the object collection even though it has no
  relationship record;
- open question: answers vary; retain it as evidence of the student’s current
  model.

---

# Stage B — Representation and Cognitive Pause

## Representation-reveal checks

The canonical matrix uses row as source and column as destination:

| from \ to | `0` | `1` | `2` | `3` | `4` | `5` |
|---:|---:|---:|---:|---:|---:|---:|
| `0` | 0 | 1 | 1 | 0 | 0 | 0 |
| `1` | 0 | 0 | 0 | 1 | 0 | 0 |
| `2` | 0 | 0 | 0 | 1 | 0 | 0 |
| `3` | 0 | 0 | 0 | 0 | 1 | 0 |
| `4` | 0 | 1 | 0 | 0 | 0 | 0 |
| `5` | 0 | 0 | 0 | 0 | 0 | 0 |

There are six arrows, six ordered pairs, and six true cells. Row and column
`5` are all zero because Archive has no entering or leaving edge.

## Five-minute Cognitive Pause

The activity has exactly three targets.

### Target 1 — Selected cells and row

- `[0][1] = 1` because edge `0 → 1` exists;
- `[1][0] = 0` because the reverse edge is not in the directed edge set;
- `[2][3] = 1` because edge `2 → 3` exists;
- row `5` is `0 0 0 0 0 0` because vertex `5` has no outgoing edge.

Any one of those explanations satisfies the explanation request.

### Target 2 — Added reverse direction

- new ordered pair: `(1, 0)`;
- changed cell: `[1][0]`;
- reason: a directed edge is one-way, so `0 → 1` and `1 → 0` are two
  independent facts.

### Target 3 — Undirected mirror

- cells: `[2][4]` and `[4][2]`;
- required relationship:

  ```text
  adjacency[2][4] == adjacency[4][2] == true
  ```

These cells are mirrors across the matrix diagonal. One undirected edge
requires both.

Do not deduct for an incorrect timed response when the student preserved it
and made an evidence-based correction.

---

# Stage C — Investigation

The standard and linear worksheets have matching question labels. A verbal
description that preserves every relationship is equivalent to a diagram.

## Section A — Three curriculum representations

### A1. Diagram or diagram-equivalent description

Required vertices and arrows:

```text
0 Gateway → 1 Web
0 Gateway → 2 Admin
1 Web → 3 Database
2 Admin → 3 Database
3 Database → 4 Monitor
4 Monitor → 1 Web
5 Archive has no arrow.
```

### A2. Edge set

```text
{(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (4, 1)}
```

### A3. Adjacency matrix

Use the six-by-six matrix in the Stage B section above.

### A4. Equivalence

- arrows: `6`;
- ordered pairs: `6`;
- true matrix cells in this directed graph: `6`.

Archive appears as a labeled but disconnected mark in the diagram, appears
through the declared vertex set even though no pair names it, and has an
all-zero row and column in the matrix.

## Section B — Direction, symmetry, and weight

### B1. One undirected edge

For `{1, 4}`, cells `[1][4]` and `[4][1]` are both `1`.

### B2. Symmetry

An undirected edge can be used both ways, so every true cell must have a true
mirror. Every false cell likewise has a false mirror in a valid completed
undirected matrix. The directed edge `0 → 1` does not require `1 → 0`
because direction is part of the first relationship.

### B3. Weight boundary

No. A Boolean cell has only present and absent states. A 12-millisecond
delay requires numeric weight storage and an unambiguous way to distinguish
“no edge” from an edge whose weight is a number. The Module 3 C type is not
changed.

## Section C — Immediate relationships

### C1. Database, vertex 3

- in-neighbors: `1, 2`;
- out-neighbor: `4`.

### C2. Web, vertex 1

- in-degree: `2`, counting `0 → 1` and `4 → 1`;
- out-degree: `1`, counting `1 → 3`.

### C3. Archive, vertex 5

In-degree `0`; out-degree `0`.

### C4. Undirected degree

Degree `3`, one for each edge touching the selected vertex.

## Section D — Routes, paths, cycles, and reachability

A **route** may revisit vertices. A **path** is a route that does not repeat
a vertex. A **cycle** returns to its start without repeating another vertex.

### D1. Path

Yes. `0 → 1`, `1 → 3`, and `3 → 4` all exist, and the vertex sequence
contains no repeat.

### D2. Cycle

Yes. `1 → 3`, `3 → 4`, and `4 → 1` exist. The route returns to `1` and does
not repeat another vertex.

### D3. Reachability from Gateway

```text
{0, 1, 2, 3, 4}
```

Vertex `0` reaches itself with zero edges. Vertex `5` is not reachable from
`0`.

### D4. Direction matters

One path from `2` to `1` is:

```text
2 → 3 → 4 → 1
```

Vertex `1` cannot reach vertex `2` in the given model. Its reachable
vertices are `1, 3, 4`; the cycle among them creates no edge to `2`.

## Section E — Undirected connected components

### E1. Groups

For undirected edges `{0, 1}`, `{1, 2}`, and `{3, 4}` with isolated vertex
`5`, the connected components are:

```text
{0, 1, 2}
{3, 4}
{5}
```

An isolated vertex forms a one-vertex connected component.

### E2. Directed language

Preferred sentence:

> Starting at vertex 0 and following directed edges, vertices 0, 1, 2, 3,
> and 4 are reachable; vertex 5 is not.

Direction makes the unqualified word “connected” unclear because a route
from `u` to `v` does not guarantee a route from `v` to `u`. This module does
not introduce advanced directed-component definitions.

## Section F — Course rules

### F1. Proposed additions

| Request | Decision | Rule |
|---|---|---|
| `2 → 2` | reject | self-loop |
| another `0 → 1` | reject | duplicate existing edge |
| `1 → 0` | accept | valid separate reverse edge in a directed graph |
| `4 → 0` | accept | endpoints are active, distinct, and edge is absent |
| an edge using index `6` when count is `6` | reject | active indexes are only `0` through `5` |

### F2. Boolean limitation

One Boolean cell records only “edge absent” or “edge present.” It has no
count field for two parallel copies.

### F3. Whole-model check

An undirected defect may occur at any active endpoint pair, so a
whole-graph validator must compare active mirrored cells throughout the
matrix. Checking only one selected edge cannot prove whole-matrix symmetry.

## Section G — Three storage choices

### G1. Sparse model

A matrix reserves one cell for every possible ordered pair, even when most
cells are false. A large graph with few edges therefore reserves many cells
for absent relationships.

### G2. Frequent direct questions

The adjacency matrix gives the most direct edge query: inspect
`adjacency[u][v]`.

### G3. Process every edge

An edge-list representation is especially direct when the task reads every
stored edge once.

### G4. Neighbor work

An adjacency-list representation directly stores one vertex’s neighbors and
can avoid scanning an entire matrix row when that list is short.

Accept this comparison:

| Representation | Typical one-edge query | Storage description |
|---|---:|---|
| Adjacency matrix | `O(1)` | `V × V` Boolean cells |
| Edge-list representation | `O(E)` basic scan | `E` endpoint records |
| Adjacency-list representation | scan the selected neighbor list | `V` list heads plus edge entries |

`O(1)` means fixed work. `O(E)` means work proportional to the number of
edges. This is a conceptual comparison; students do not implement the two
list forms in Module 3.

## Section H — Tree transfer

### H1. Shared destination

Edges `1 → 3` and `2 → 3` give vertex `3` two incoming relationships. That
violates the course tree rule that every non-root node has exactly one
parent.

### H2. Back-link

`4 → 1` completes the cycle `1 → 3 → 4 → 1`. A course tree has no cycle.

### H3. Shared correctness rule

Accept one accurate rule, such as:

- indexes must remain within the fixed storage;
- the selected active count must not exceed capacity;
- the representation’s completed-state invariant must hold; or
- a failed checked operation must not leave a partial change.

Do not accept “both forbid cycles”; the graph allows cycles.

### H4. Transfer sentence

Example:

> A tree is useful when the relationships form one rooted, one-parent,
> cycle-free hierarchy; a general graph is needed when relationships may
> share destinations, return to earlier objects, or leave separate groups.

## Section I — Security-model boundary

### I1. Supported conclusion

The invented model permits communication from Web, vertex `1`, to Database,
vertex `3`.

### I2. Unsupported conclusion

The edge does not prove any of the following:

- communication actually occurred;
- a real network route currently works;
- a service is running;
- credentials are available;
- a vulnerability exists;
- a vulnerability can be exploited; or
- an attack would succeed.

One accurate unsupported claim is sufficient.

## Section J — Synthesis

### J1. Manual reachability record

One valid record is:

```text
0: start vertex; zero-edge route
1: 0 → 1
2: 0 → 2
3: 0 → 1 → 3
4: 0 → 1 → 3 → 4
```

The alternative route `0 → 2 → 3` also justifies vertex `3`. No route
justifies vertex `5`. Students are inspecting the tiny model manually, not
implementing a general search.

### J2. Structure choices

1. arrival-ordered event codes: ArrayList;
2. strict one-parent folder hierarchy: tree;
3. permissions with several routes and loops: graph.

### J3. Exit sentence

Example:

> The model is no longer a tree because Database has several incoming
> relationships and Web lies on a cycle; the Boolean matrix records whether
> each possible direct directed edge exists.

---

# Stage E — C Lab

## Exact type choices

```c
#define GRAPH_MAX_VERTICES 16U

typedef enum {
    GRAPH_DIRECTED = 0,
    GRAPH_UNDIRECTED
} GraphKind;

typedef enum {
    GRAPH_OK = 0,
    GRAPH_ERR_INVALID_ARGUMENT,
    GRAPH_ERR_OUT_OF_RANGE,
    GRAPH_ERR_SELF_LOOP,
    GRAPH_ERR_EDGE_EXISTS,
    GRAPH_ERR_EDGE_ABSENT,
    GRAPH_ERR_INVALID_GRAPH
} GraphStatus;
```

The exact public declarations are in `graph_matrix.h`. Do not accept a
changed capacity, reversed matrix convention, or renamed public function as
an equivalent submission unless an accommodation explicitly authorizes it.

## `graph_init`

Required results:

- `NULL` graph: `GRAPH_ERR_INVALID_ARGUMENT`;
- count greater than 16: `GRAPH_ERR_OUT_OF_RANGE`;
- unknown kind: `GRAPH_ERR_INVALID_ARGUMENT`;
- success: assign count and kind, clear all `16 × 16` cells, return
  `GRAPH_OK`;
- every failure with a non-`NULL` destination: leave the `Graph` unchanged.

Checks must happen before the first write.

## `graph_validate`

This is the whole-graph check. Expected results:

- `NULL`: `GRAPH_ERR_INVALID_ARGUMENT`;
- stored count above 16 or stored unknown kind:
  `GRAPH_ERR_INVALID_GRAPH`;
- true active diagonal cell: `GRAPH_ERR_INVALID_GRAPH`;
- unequal active mirror cells in an undirected graph:
  `GRAPH_ERR_INVALID_GRAPH`;
- otherwise: `GRAPH_OK`.

Only the active `V × V` square is validated. A true inactive cell does not
make the graph invalid. Initialization still clears all physical cells.

## Add, remove, and query

Common status order:

1. a required `NULL` pointer gives `GRAPH_ERR_INVALID_ARGUMENT`;
2. malformed stored count or kind gives `GRAPH_ERR_INVALID_GRAPH`;
3. an inactive endpoint gives `GRAPH_ERR_OUT_OF_RANGE`;
4. equal endpoints give `GRAPH_ERR_SELF_LOOP`;
5. inspect the selected directed cell or selected undirected mirror pair.

For a directed graph:

- add absent edge: set one cell, `GRAPH_OK`;
- add present edge: `GRAPH_ERR_EDGE_EXISTS`;
- remove present edge: clear one cell, `GRAPH_OK`;
- remove absent edge: `GRAPH_ERR_EDGE_ABSENT`;
- query: report the selected cell.

For an undirected graph:

- unequal relevant mirror cells: `GRAPH_ERR_INVALID_GRAPH`;
- add absent edge: set both mirrors;
- add present edge from either endpoint order:
  `GRAPH_ERR_EDGE_EXISTS`;
- remove present edge from either endpoint order: clear both mirrors;
- remove absent edge: `GRAPH_ERR_EDGE_ABSENT`;
- query: report the agreed cell value.

No failure changes the graph or query output.

## Degree and neighbor answers

- out-degree scans one row;
- in-degree scans one column;
- both are equal for a valid undirected graph;
- `graph_out_neighbors` scans one row and reports true-column indexes in
  increasing order;
- a relevant true diagonal or relevant asymmetric undirected pair gives
  `GRAPH_ERR_INVALID_GRAPH`;
- failures preserve the output.

For the canonical directed graph:

| Vertex | Out-degree | In-degree | Out-neighbor result |
|---:|---:|---:|---|
| `0` | `2` | `0` | `[1, 2]` |
| `1` | `1` | `2` | `[3]` |
| `2` | `1` | `1` | `[3]` |
| `3` | `1` | `2` | `[4]` |
| `4` | `1` | `1` | `[1]` |
| `5` | `0` | `0` | empty |

## Status-name text

The reference strings are:

| Status | Text |
|---|---|
| `GRAPH_OK` | `ok` |
| `GRAPH_ERR_INVALID_ARGUMENT` | `invalid argument` |
| `GRAPH_ERR_OUT_OF_RANGE` | `vertex count or index out of range` |
| `GRAPH_ERR_SELF_LOOP` | `self-loops are not allowed` |
| `GRAPH_ERR_EDGE_EXISTS` | `edge already exists` |
| `GRAPH_ERR_EDGE_ABSENT` | `edge does not exist` |
| `GRAPH_ERR_INVALID_GRAPH` | `graph does not satisfy required representation rules` |
| unknown status value | `unknown GraphStatus` |

## Required operation costs

| Operation | Time cost |
|---|---:|
| full `graph_validate` | `O(V²)` |
| add one edge | `O(1)` |
| remove one edge | `O(1)` |
| query one edge | `O(1)` |
| in-degree or out-degree | `O(V)` |
| out-neighbors | `O(V)` |

Do not give full credit to an implementation that calls
`graph_validate` inside every add, remove, or query. That changes the
operation from constant work to matrix-wide work. Local operations check the
metadata and relevant cells; explicit validation checks the whole active
matrix.

## Student-authored tests

The student template requests:

1. a directed edge whose reverse has a separate result;
2. an undirected update that checks both mirrors and a preserving failure;
3. a degree, ascending-neighbor, or boundary case tied to a stated contract.

Accept different tests when all three are accurate, use a new input or
combination rather than copying a public case, and explain a distinct claim.
Merely changing vertex numbers in a public test is not new evidence.

---

# Matrix Symmetry Autopsy

The intended undirected relationship is `{0, 1}`.

1. required cells: `[0][1]` and `[1][0]`;
2. first invalid completed state: immediately after
   `graph.adjacency[0][1] = true;`;
3. broken rule:

   ```text
   adjacency[0][1] == adjacency[1][0]
   ```

4. predicted printed results:

   ```text
   Gateway reports Web as connected: yes
   Web reports Gateway as connected: no
   mirror cells agree: no
   ```

5. a row-counted degree would report degree `1` for vertex `0` and degree
   `0` for vertex `1`, even though the intended undirected edge touches both;
6. missing repair:

   ```c
   graph.adjacency[1][0] = true;
   ```

7. suitable regression tests:
   - add one undirected edge and verify both mirror cells plus queries in
     both endpoint orders;
   - form an asymmetric pair directly and require
     `graph_validate` to return `GRAPH_ERR_INVALID_GRAPH`.

“Update both as one operation” means perform all rejection checks first and
then write both cells, so no caller-visible successful state contains only
one half of an undirected edge.

---

# Evidence Record and Rubric Guidance

## Completed-graph invariant

The complete answer must include:

- count no greater than 16;
- kind is one of the two named choices;
- active indexes are `0` through `vertex_count - 1`;
- active diagonal cells are false;
- active mirror cells are equal for an undirected graph;
- a Boolean cell stores at most one edge fact.

Cycles, isolated vertices, and several incoming directed edges are allowed.
Only the full validator proves all active diagonal and symmetry rules.
Ordinary operations check their requested pair, row, or column.

## Representation-cost table

| Representation | One-edge query | Storage | Useful when |
|---|---|---|---|
| Adjacency matrix | `O(1)` | `O(V²)` cells | frequent direct queries or many edges |
| Edge-list representation | basic `O(E)` scan | `O(E)` records | processing every edge in sequence |
| Adjacency-list representation | scan one endpoint’s neighbor list | `O(V + E)` conceptual storage | few edges and frequent neighbor work |

## Spiral 1 structure choices

| Scenario | Choice | Central rule | Example cost | Example risk |
|---|---|---|---|---|
| Ordered event log | ArrayList | logical items occupy indexes below size | indexed access `O(1)` | confusing size with capacity or unsafe growth |
| One-parent directory hierarchy | tree | one root, one parent per other node, no cycle | direct child field read `O(1)` | shared child, cycle, or invalid pointer |
| Services with shared and returning links | graph | active bounds, false diagonal, and undirected symmetry when applicable | matrix edge query `O(1)` | reversed direction, asymmetric update, or out-of-range index |

Equivalent accurate rules, costs, and risks receive credit.

## Security-model sentence

Full-credit example:

> The edge records a permission in invented data. It does not show that
> communication occurred or provide the service state, credentials,
> vulnerability, defenses, or other evidence needed to establish
> exploitability.

## Grading cautions

- Grade the preserved-and-corrected pause as evidence of revision, not as a
  speed test.
- Accept diagrams, exact text equivalents, tactile demonstrations, or spoken
  descriptions.
- Do not reward use of “connected component” for a directed reachable set.
- Do not require adjacency-list C code.
- Do not require a weighted matrix extension.
- Do not require DFS, BFS, or any formal graph search.
- Do not accept a statement that a synthetic edge proves an exploitable
  route.
