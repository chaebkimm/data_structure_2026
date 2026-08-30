# Instructor Lesson Plan — Module 3: Directed Graph Matrices

## Purpose and limits

This module introduces graphs as objects plus relationships that may enter
one vertex from several sources or form cycles. The C lab implements one
bounded, directed, unweighted adjacency matrix. It does not implement
undirected mutation, weights, edge lists, adjacency lists, components, or a
formal traversal.

Students know one-dimensional fixed arrays from Module 1 and child links from
Module 2. Introduce two-dimensional indexing, graph vocabulary, and
row-as-source/column-as-destination explicitly.

The module uses two 90-minute meetings, five gated releases, three distinct
student tests, and a 100-point rubric.

## Learning targets

Students will be able to:

1. identify vertices, directed edges, paths, cycles, and out-degree;
2. translate a three-vertex graph among a diagram, ordered edge set, and
   adjacency matrix;
3. distinguish `grid[u][v]` from its reverse `grid[v][u]`;
4. initialize a fixed graph and clear all 256 cells;
5. add and remove directed edges idempotently while preserving failures;
6. reject a self-loop addition and inactive endpoint safely;
7. guard direct matrix lookup and implement checked out-degree;
8. distinguish active vertices from the physical capacity;
9. explain matrix invariants and operation costs; and
10. compare the implemented model conceptually with other graph types and
    representations.

## Exact C boundary

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};

int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

All four functions return 1 on success and 0 on rejection. A direct guarded
lookup is core caller code, not another API. Do not add status names, graph
kinds, Boolean fields, validation helpers, in-degree, or neighbor collection.

## Canonical model

Active IDs:

```text
0 Web
1 App
2 Database
```

Directed edges:

```text
0 -> 1
1 -> 2
1 -> 0
```

Active matrix:

```text
0 1 0
1 0 1
0 0 0
```

The edges `0 -> 1` and `1 -> 0` are distinct and form a valid length-two
cycle. After removing `1 -> 2`, row 1 is `[1, 0, 0]` and its out-degree
is 1.

## Selected beginner first-use sequence

The student vocabulary reference contains the authoritative list of 30
required terms. This shorter table highlights terms that need special timing
in the lesson.

| Term | First-use explanation |
|---|---|
| graph | objects together with relationships among them |
| vertex | one object in a graph |
| vertex ID | an active integer from zero through count minus one |
| edge | one direct relationship |
| directed edge | one-way relationship from a source to a destination |
| path | sequence of vertices connected in arrow direction |
| cycle | path that returns to its starting vertex |
| out-degree | number of edges leaving one vertex |
| adjacency matrix | square table recording possible endpoint pairs |
| active | currently represents a vertex or edge cell |
| inactive | physically present but outside the current vertex count |
| idempotent | repeating a valid request reaches the same state and succeeds |
| self-loop | edge from a vertex directly to itself |
| unweighted | records only presence or absence, not cost |
| undirected | conceptual relationship with no arrow direction |
| weight | cost, distance, or time attached to an edge |
| edge list | stored sequence of endpoint pairs |
| adjacency list | outgoing-neighbor collection for each vertex |
| component | undirected group joined by paths |
| output parameter | address where a function writes a result |

Use ordinary explanations as correct evidence. Do not require formal graph
notation before it is introduced.

## Five release gates

| Gate | Release time | Give students | Hold back |
|---|---|---|---|
| A — Initial inquiry | before Meeting A | standard or linear relationship prompt | graph terms, matrix, code, answers |
| B — Model and pause | after the first response is saved | matrix reveal, vocabulary, three-target Cognitive Pause | calibration and investigation |
| C — Investigation | after the pause and calibration | standard or linear directed-matrix investigation | worked notes, code, answers |
| D — Textbook and models | after the Stage C attempt is saved | textbook and correct diagram/text models | lab, autopsy prediction answer, instructor materials |
| E — Lab and evidence | Meeting B | lab, rubric, evidence, autopsy, header, starter, public tests, build files | solution, extension tests, answer key |

Preserve “attempt, compare, correct.” Vocabulary begins at Stage B. Approved
accessible or extended-time versions use the same targets. Stage D may teach
the full-clear rule generally but must not reveal the exact Stage E autopsy
outcome.

# Meeting A — Model and Reason (90 minutes)

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–15 | Stage A relationship inquiry | Preserved initial model |
| 15–30 | Stage B reveal: directed edges and row/column matrix | Three-form translation |
| 30–35 | Five-minute, three-target Cognitive Pause | Independent response |
| 35–43 | Calibrate pause and vocabulary | Labeled corrections |
| 43–75 | Stage C investigation | Matrix, operation, invariant, and comparison responses |
| 75–90 | Stage D textbook/models and exit synthesis | Annotated corrections and exit answer |

## Stage B pause — exactly three targets

Start from the canonical three-vertex graph and consider each requested
change from the state stated in the prompt.

1. Write all three active matrix rows and explain why opposite cells are
   independent.
2. Remove `1 -> 2`; identify the changed cell, new row 1, and new
   out-degree of vertex 1.
3. Classify additions `2 -> 2`, `3 -> 1`, and `2 -> 0`, identifying
   self-loop, inactive endpoint, or success and stating failure preservation.

Do not introduce a fourth target or correct students during the five-minute
pause.

## Calibration prompts

- Which ID supplies the row? The edge's source.
- Which ID supplies the column? The destination.
- Does `0 -> 1` imply `1 -> 0`? No.
- Is `0 -> 1 -> 0` allowed? Yes; only direct self-loop addition is rejected.
- Is physical row 3 active when the count is 3? No.
- Does a repeated valid addition fail? No; it succeeds with the same state.
- Does removing an absent valid edge fail? No; it succeeds with the same state.
- What does an output failure change? Nothing in the caller's output.

## Stage C checks

Use the same Web/App/Database graph. Require students to:

- translate its diagram, ordered edge set, and three matrix rows;
- map a row to outgoing edges and a column to incoming edges conceptually;
- trace removal, out-degree, and idempotent repetitions;
- distinguish active count 3 from physical capacity 16;
- classify direct edits that create a valid edge, self-loop, inactive ghost,
  or nonbinary cell;
- explain full initialization and rejected-state preservation;
- identify a directed route, length-two cycle, shared destination, and
  isolated vertex;
- compare conceptual undirected, weighted, edge-list, and adjacency-list
  models; and
- state the difference among ArrayList, tree, and graph relationships.

The matrix happens to be small; students still justify every row and column.
Do not introduce DFS or BFS as the method for answering these supplied
small-graph observations.

## Formative checks

- A vertex may have several incoming edges.
- A cycle longer than one edge is valid.
- Directional matrices need not be symmetric.
- A diagonal 1 is invalid under this module's policy.
- All inactive cells stay zero.
- A value other than 0 or 1 violates the matrix representation.
- Equal endpoint addition is rejected, but removal may safely clear a
  diagonal position.
- An edge models only the chosen relationship; it does not prove a
  vulnerability, authorization decision, or successful network route.

# Between meetings

1. Preserve the Stage C attempt before Stage D.
2. Ask students to annotate rather than replace earlier work.
3. Release Stage E for Meeting B.
4. Validate reference tests and isolated autopsy before class.

# Meeting B — Implement, Test, and Explain (90 minutes)

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–10 | Read the exact four-function contract | Header annotations |
| 10–25 | Implement full initialization | Active/inactive clearing tests |
| 25–47 | Implement checked idempotent add and remove | Directed sequence tests |
| 47–60 | Implement out-degree and direct guarded lookup | Output/lookup evidence |
| 60–74 | Run public tests and finish three distinct student tests | Transcripts and rationales |
| 74–83 | Preserve autopsy prediction, run, and explain | Matrix incident record |
| 83–90 | Complete evidence and rubric check | Submission record |

## Implementation coaching

Ask one question at a time:

- Which cells must initialization clear?
- Has every rejection check finished before the first write?
- Which one directed cell represents this request?
- Does “already present” mean error or requested state already reached?
- Why does only addition reject equal endpoints?
- Which columns are active during this row scan?
- Has the output been written before success is certain?
- Is a direct bracket read guarded by both active IDs?

Do not coach toward extra functions or statuses. Tests should observe the
documented 1/0 results and complete state, not imagined error categories.

## Required three tests

The three student slots, in order, cover:

1. full initialization, including inactive positions;
2. one coherent directed sequence with idempotent operations, guarded lookup,
   and out-degree; and
3. either a rejected self-loop or inactive endpoint with an unchanged graph,
   or a rejected out-degree request with an unchanged output.

Each test states a distinct claim and keeps supplied fixtures valid except
for the rejected request itself. Do not require a fourth coded test for the
autopsy.

## Rubric alignment

| Criterion | Points |
|---|---:|
| Representation and translation | 15 |
| Full initialization | 20 |
| Directed add and remove | 20 |
| Out-degree and guarded lookup | 15 |
| Bounds and invariant reasoning | 10 |
| Three tests and tool evidence | 15 |
| Matrix Autopsy | 5 |
| Total | 100 |

Instructor extension tests add boundaries and sequences for the same four
functions. They do not add undirected mutation, weights, traversal, or
another API.

## Matrix Autopsy boundary

Students preserve the requested inactive-cell prediction before running the
isolated fixture. They then explain the first incorrect count-only state change,
the difference between physical and active positions, the later visible
connection, and the violated inactive-zero invariant.

Keep exact observed values in the instructor answer key. The autopsy uses
physical in-bounds cells, so a crash is neither expected nor required.
Provide verbal, linear-text, debugger, or instructor-CI alternatives where
appropriate.
