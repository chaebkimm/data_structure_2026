# Instructor Lesson Plan — Module 3: Graph Models and Representations

## Purpose and limits

This module introduces a **graph**, a collection of objects and relationships.
One object is a **vertex**. One relationship is an **edge**. Unlike a tree, a
graph may have crossing relationships, several relationships entering one
vertex, cycles, and separate groups.

Students first reason with diagrams and tables. They then implement a small,
fixed-size, unweighted graph in C. **Fixed-size** means that the maximum
number of vertices does not change while the program runs. **Unweighted**
means that an edge records only whether a relationship exists; it does not
store a distance, cost, or other number.

This module does not teach a formal procedure for visiting a graph. A
**procedure** is an ordered set of steps. Depth-first search (DFS) and
breadth-first search (BFS), two later procedures for visiting reachable
vertices, are deliberately deferred.

By the end of the module, students should be able to:

1. distinguish directed from undirected graphs and weighted from unweighted
   graphs;
2. use vertex, edge, neighbor, degree, path, cycle, connected component, and
   reachability accurately;
3. translate one graph among a diagram, an edge list, an adjacency list, and
   an adjacency matrix;
4. implement and test bounded matrix-based graph operations;
5. compare the storage and operation trade-offs of three representations;
6. state that a synthetic network edge models a connection or permission,
   not proof that an attack can succeed.

## Beginner language sequence

Introduce each word immediately before students need it. Repeat a short
definition rather than assuming that seeing a word once made it familiar.

| Word | First-use explanation |
|---|---|
| object | One distinct thing represented by the program |
| relationship | A connection from one object to another object |
| graph | A collection of objects and relationships |
| vertex | One object in a graph; several objects are called vertices |
| vertex ID | A small number used to name one vertex |
| edge | One relationship between two vertices |
| directed edge | A one-way relationship, written with an arrow such as `0 → 1` |
| undirected edge | A two-way relationship, written without an arrow such as `{0, 1}` |
| weight | A number attached to an edge, such as a cost, distance, or time |
| weighted graph | A graph whose edges have weights |
| unweighted graph | A graph whose edges record only presence or absence |
| neighbor | A vertex directly joined by an edge |
| out-neighbor | A vertex at the arrow end of an edge leaving the selected vertex |
| in-neighbor | A vertex at the arrow start of an edge entering the selected vertex |
| degree | The number of edges touching a vertex in an undirected graph |
| out-degree | The number of directed edges leaving a vertex |
| in-degree | The number of directed edges entering a vertex |
| route | A sequence of vertices in which each consecutive pair has the required edge |
| path | A route that does not repeat a vertex |
| cycle | A route that returns to its starting vertex without repeating another vertex |
| reachable | Able to be arrived at by following zero or more allowed edges |
| connected component | A largest group in an undirected graph in which every vertex can reach every other vertex |
| representation | A chosen way to record the same information |
| edge list | A sequence containing one endpoint pair for each edge |
| adjacency list | One neighbor list for each vertex |
| adjacency matrix | A square table whose row and column identify a possible edge |
| row | A horizontal line of table cells |
| column | A vertical line of table cells |
| symmetric matrix | A matrix in which cell `[u][v]` equals cell `[v][u]` |
| self-loop | An edge from a vertex to itself |
| duplicate edge | An attempt to add an edge that is already present |
| simple graph | The course graph model: no self-loops and no duplicate edges |
| invariant | A rule that must be true whenever a completed structure is used |
| application programming interface (API) | The named types and functions that other code may use |
| contract | What a function accepts, returns, changes, and leaves unchanged |
| validator | A function that checks whether stated rules hold |
| Boolean value | A value that is either `true` or `false` |
| output | A result written into a variable supplied by the caller |
| caller | Code that asks a function to run |
| synthetic | Invented for a safe learning exercise rather than copied from an operating network |

For a directed graph, avoid the unqualified word “neighbor” when direction
matters. Say “out-neighbor” or “in-neighbor.” Use “connected component” only
for an undirected graph in this module. For a directed graph, ask whether one
specified vertex is reachable from another.

## Five release gates

A **release gate** is a planned point when the instructor gives students the
next set of materials. The order preserves the students’ first reasoning
before they see formal answers.

| Gate | Release time | Give students | Hold back |
|---|---|---|---|
| A — Initial inquiry | Before formal graph vocabulary in Meeting A | Standard or linear inquiry prompt | Official graph terms, representation reveal, rules, completed models, code |
| B — Representation | After each student preserves a first relationship model | Representation reveal and the exactly-three-target Cognitive Pause | Investigation answers, beginner notes, completed models, code |
| C — Investigation | After the five-minute pause and short instructor explanation | Standard or linear investigation worksheet | Beginner notes, completed models, code |
| D — Notes and models | After the student submits or preserves the Stage C core | Example-first beginner notes and graph models | Lab package and instructor materials |
| E — Lab and evidence | At the start of Meeting B | Lab, evidence form, rubric, autopsy, public header, starter, public tests, student-test template, and build files | Reference solution, instructor tests, answer key |

The answer key and solution remain instructor-only until the
instructor-selected review time. Students receiving an accommodation may
receive materials on a different clock, but the sequence remains: attempt,
preserve, then compare with an explanation.

The Gate A core is all Section A responses; Section B's immediate-way count,
repeating route, and loop explanation; Section C's first direction question;
and the Section D Macro-Question. Section E may wait for independent work.

---

# Meeting A — Model Relationships (90 minutes)

## Macro-Question

> What representation is needed when useful relationships may cross
> branches, point backward, or form cycles?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–5 | Welcome and boundary | State that this meeting is about modeling relationships, not writing a search procedure. | Student restates the boundary |
| 5–21 | Gate A inquiry | Give the synthetic relationship situation without graph vocabulary. Require the announced Gate A core; Section E may wait for the independent window. | Preserved first model |
| 21–28 | Tree comparison | Recall that a tree gives each non-root node one parent and forbids cycles. Add a shared destination and a backward relationship. Ask which tree rules no longer fit. | Two named differences |
| 28–39 | Gate B representation reveal | Define graph, vertex, edge, directed, undirected, row, column, and adjacency matrix. Establish the convention: row is the edge start and column is the edge end. | Two diagram-to-cell translations |
| 39–44 | Five-minute Cognitive Pause | Students complete exactly the three released targets below without help. Permit a table, structured list, tactile markers, or spoken response. | Individual three-target response |
| 44–52 | Compare and correct | Students compare exact edge directions in pairs. Then show the instructor model. Corrections remain beside the first response. | Annotated correction |
| 52–63 | Local graph language | Define out-neighbor, in-neighbor, degree, out-degree, in-degree, path, and cycle. Continue with the six-vertex pause graph. | One degree calculation and one cycle |
| 63–72 | Separate groups and direction | Define connected component only on an undirected example. Define reachable on a directed example. Do not call a directed reachable set a component. | Correct term chosen for two prompts |
| 72–78 | Weights | Contrast an unweighted permission edge with a weighted travel-time edge. State that the C lab stores only unweighted edges. | One appropriate weight example |
| 78–84 | Curriculum translation | Translate the six-vertex example among a diagram, mathematical edge set, and adjacency matrix. | Three equivalent forms |
| 84–87 | Storage comparison | Distinguish the mathematical edge set from an edge-list representation stored as a sequence. Then compare edge-list, matrix, and adjacency-list storage. | Completed representation comparison |
| 87–90 | Exit ticket and Gate C | Release the investigation. Ask: “What does matrix cell `[u][v]` mean, and what changes in an undirected graph?” | Two-sentence exit response |

## Stage B Cognitive Pause — exactly three targets

Read this starting state before starting the timer:

```text
Vertices:
0 Gateway, 1 Web, 2 Admin, 3 Database, 4 Monitor, 5 Archive

Directed edge set:
{(0, 1), (0, 2), (1, 3), (2, 3), (3, 4), (4, 1)}
```

Students then have five uninterrupted minutes for exactly these targets:

1. State the values of cells `[0][1]`, `[1][0]`, and `[2][3]`, state every
   value in row `5`, and explain one of those answers.
2. Suppose directed edge `1 → 0` is added while `0 → 1` remains. State the
   ordered pair added to the edge set, the one matrix cell changed to `1`,
   and why the two opposite edges are separate facts.
3. Suppose a new undirected graph contains edge `{2, 4}`. State the two
   matrix cells that become `1` and the equality they must satisfy across the
   diagonal.

Do not add a fourth prompt during the pause. Do not correct answers until the
five minutes end.

## Meeting A checks

Before moving on, verify that students can state:

- an arrow’s direction changes the relationship’s meaning;
- `matrix[u][v]` records the edge from `u` to `v`;
- an undirected edge requires equal mirror cells;
- degree means different things in directed and undirected graphs;
- connected component is being used only for an undirected graph;
- a directed reachability statement must name a starting vertex;
- a weight is separate information that the course C structure does not
  store;
- none of these manual observations is yet a formal search procedure.

## Between meetings — finish, preserve, then read

The complete Stage C investigation is longer than the remaining classroom
time. Allow about 60–75 minutes for independent completion. The Gate D core
is explicitly:

- Section A, questions A1–A4: diagram or diagram-equivalent description,
  edge set, matrix, and equivalence check;
- Section B, questions B1–B3: undirected mirror cells, symmetry and
  direction, and the weight boundary;
- Section D, questions D1–D4: path, cycle, and directed reachability;
- Section E, questions E1–E2: undirected connected components and precise
  directed language; and
- Section G, questions G1–G4: representation comparison.

A student must submit or preserve those exact responses before receiving
Gate D. Sections C, F, H, I, and J can be completed in the transparent
independent window before or after Gate D as the instructor’s schedule
allows.

After Gate D opens, students read the example-first notes and inspect the
models. They label corrections without erasing their first work. Offer an
instructor-supported completion period or an equivalent remote help window.

---

# Meeting B — Build and Verify (90 minutes)

## Scope reminder

The lab uses an adjacency matrix made of Boolean values. It can hold at most
16 vertices. It represents a simple, unweighted, directed or undirected
graph. Students implement local operations and use a supplied or completed
whole-graph validator. Formal DFS and BFS remain out of scope.

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Gate E and retrieval | Release the lab. With editors closed, ask students to explain row-as-start, column-as-end, symmetry, self-loop, and duplicate edge. | Five short retrieval statements |
| 8–19 | C representation | Define `size_t` as a nonnegative integer type used for sizes and indexes, `bool` as C’s Boolean type, `enum` as a named set of choices, and `struct` as one value composed of named fields. Read each `Graph` field aloud. | Field-to-meaning table |
| 19–29 | Initialization and whole validation | Contrast `graph_init`, which creates a clean state, with `graph_validate`, which checks a completed state. Show that validation examines the active square of the matrix. | Two predicted statuses |
| 29–43 | Add an edge | Students implement or inspect bounds, kind, self-loop, and duplicate checks. Directed insertion changes one cell; undirected insertion changes two mirror cells. | Focused add-edge tests |
| 43–52 | Remove an edge | Require an existing edge. Show that failed removal makes no change. For an undirected graph, remove both mirror cells. | Before-and-after matrix |
| 52–61 | Ask about an edge | Use `graph_has_edge`. Define output and require the output value to remain unchanged when the request fails. | Query tests |
| 61–72 | Degree and neighbors | Scan one row for out-degree and out-neighbors. Scan one column for in-degree. State the work cost without introducing a visit order. | Degree and neighbor results |
| 72–80 | Test invalid states | Test an out-of-range vertex, self-loop, duplicate insertion, absent removal, and asymmetric undirected matrix. | Status table |
| 80–86 | Representation trade-offs | Compare a matrix with the equivalent edge list and adjacency list. Separate storage cost from edge-query cost. | One justified choice |
| 86–89 | Synthetic network boundary | Ask what an edge proves. Required answer: only the modeled connection or permission, not a vulnerability, exploit, route availability, or successful attack. | Boundary statement |
| 89–90 | Submission check | Review the required code, tests, representation evidence, and written explanation. | Completion checklist |

## After Meeting B — transparent completion window

The 90-minute meeting establishes each core operation, but it is not expected
to absorb every student’s debugging and documentation time. Allow about
60–90 additional minutes to finish the starter tasks, run public tests, write
original tests, complete the autopsy, compare representations, and fill in
the evidence form. Provide a staffed lab period or equivalent remote help.

## Canonical C API

An **enumeration**, written `enum` in C, gives readable names to a fixed set
of choices. A **constant** is a named value that does not change.

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

typedef struct {
    size_t vertex_count;
    GraphKind kind;
    bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;

typedef struct {
    size_t count;
    size_t vertices[GRAPH_MAX_VERTICES];
} GraphNeighbors;
```

The public functions are:

```c
GraphStatus graph_init(Graph *graph, size_t vertex_count, GraphKind kind);
GraphStatus graph_validate(const Graph *graph);
GraphStatus graph_add_edge(Graph *graph, size_t from, size_t to);
GraphStatus graph_remove_edge(Graph *graph, size_t from, size_t to);
GraphStatus graph_has_edge(
    const Graph *graph, size_t from, size_t to, bool *out_has_edge);
GraphStatus graph_out_degree(
    const Graph *graph, size_t vertex, size_t *out_degree);
GraphStatus graph_in_degree(
    const Graph *graph, size_t vertex, size_t *out_degree);
GraphStatus graph_out_neighbors(
    const Graph *graph, size_t vertex, GraphNeighbors *out_neighbors);
const char *graph_status_name(GraphStatus status);
```

The parameter name `out_degree` in both degree declarations means “the
address where this function writes its answer.” It does not change the
meaning of `graph_in_degree`.

Use these operation contracts:

- `graph_init` accepts a count from zero through
  `GRAPH_MAX_VERTICES`, accepts one of the two named kinds, and clears every
  matrix cell.
- `graph_validate` checks the complete active graph. The **active square**
  consists of rows and columns below `vertex_count`.
- `graph_add_edge` rejects an out-of-range endpoint, a self-loop, and an edge
  already present. It changes one cell for a directed graph and two mirror
  cells for an undirected graph.
- `graph_remove_edge` rejects an absent edge and otherwise clears the same
  one or two cells.
- `graph_has_edge` reports whether the requested edge exists.
- `graph_out_degree` counts `true` cells in one row.
- `graph_in_degree` counts `true` cells in one column.
- `graph_out_neighbors` reports, in increasing vertex-ID order, each column
  whose cell in the selected row is `true`.
- `graph_status_name` returns readable text for a status.

The add, remove, query, degree, and neighbor operations perform bounded checks
relevant to their requested rows, columns, or cells. They do not call the
full validator. A **bounded check** examines no more than the fixed maximum
or the active vertex count.

## Required invariants

For every valid completed graph:

1. `vertex_count` is at most `GRAPH_MAX_VERTICES`;
2. `kind` is `GRAPH_DIRECTED` or `GRAPH_UNDIRECTED`;
3. every active diagonal cell `adjacency[v][v]` is `false`, so there are no
   self-loops;
4. if the graph is undirected, every active cell equals its mirror:
   `adjacency[u][v] == adjacency[v][u]`.

A Boolean matrix stores only one yes-or-no fact for each ordered endpoint
pair, so it cannot store **parallel edges**, meaning separate copies of an
edge with the same endpoints. The API reports `GRAPH_ERR_EDGE_EXISTS` when
insertion requests an edge already present.

## Hint ladder

Reveal only one hint at a time:

1. Which vertex is the row, and which is the column?
2. Are both vertex IDs below `vertex_count`?
3. Are the two IDs equal?
4. Is the graph directed or undirected?
5. Which one cell answers the directed question?
6. Which mirror cell must agree in an undirected graph?
7. Does a degree question scan a row or a column?
8. Has the function changed an output or graph before all failure checks
   passed?

## Common misconceptions

| Misconception | Diagnostic question | Correction |
|---|---|---|
| Every relationship is two-way | “Does `u → v` also state `v → u`?” | No. A directed edge records one direction. |
| A directed matrix is symmetric | “Must the reverse permission exist?” | No. Only an undirected matrix must be symmetric. |
| Matrix row means destination | “How did we read `[u][v]`?” | Row `u` is the start; column `v` is the end. |
| Degree has one meaning in every graph | “Does the arrow enter or leave?” | Directed graphs distinguish in-degree and out-degree. |
| Any group in a directed graph is a component | “From which starting vertex are you following arrows?” | In this module, use reachability for directed graphs and connected component only for undirected graphs. |
| A path must use every vertex | “What does the definition require between consecutive vertices?” | It requires the needed edges, not every graph vertex. |
| A repeated insertion creates a parallel edge | “What can one Boolean cell store?” | Only present or absent; the API rejects the duplicate. |
| Removing an absent edge succeeds silently | “Which contract result names absence?” | Return `GRAPH_ERR_EDGE_ABSENT` and make no change. |
| Every operation must run `graph_validate` | “Which cells can this operation affect or inspect?” | Use the operation’s local relevant checks; reserve the full scan for explicit validation. |
| A permission edge proves an attack path works | “What real facts are missing?” | The model omits vulnerabilities, credentials, service state, controls, and many other facts. |

## Accessibility and pacing

- Pair every diagram with an exact table, edge set, matrix, or numbered text
  equivalent.
- Do not rely on color, arrow shape alone, or spatial position alone.
- Read `u → v` aloud as “a directed edge starts at u and ends at v.”
- Permit drawing, typing, dictation, tactile cards, or spoken descriptions.
- State the row-as-start convention every time a new matrix appears.
- Read the Cognitive Pause starting state before timing it.
- Give five uninterrupted minutes and keep it to exactly three targets.
- Provide the investigation and lab completion windows openly; do not imply
  that every student should finish all work during the two meetings.
- Grade relationship reasoning and code behavior, not drawing quality or
  typing speed.

## Evidence collected

1. the preserved Stage A relationship model;
2. the three-target Stage B pause and visible corrections;
3. equivalent diagram, edge list, adjacency list, and adjacency matrix;
4. accurate directed reachability and undirected connected-component
   language;
5. tested implementations of the bounded graph API;
6. original tests for success and rejection cases;
7. a representation comparison;
8. the synthetic-network modeling boundary in the student’s own words.

## Instructor completion checklist

- [ ] Stage A reveals no formal graph answer or representation rule.
- [ ] Stage B includes exactly three timed targets.
- [ ] Students preserve the Stage C core before receiving Stage D.
- [ ] Every technical term is explained at first use.
- [ ] Every visual has a precise text equivalent.
- [ ] Directed and undirected edge meanings remain distinct.
- [ ] Weighted graphs are introduced, but the C lab remains unweighted.
- [ ] “Connected component” is used only for undirected graphs.
- [ ] Directed questions use explicit reachability from a named start.
- [ ] Matrix rows are sources and columns are destinations.
- [ ] The simple-graph API rejects self-loops and duplicate edges.
- [ ] Undirected matrices are symmetric.
- [ ] Local operations do not claim to perform full validation.
- [ ] DFS, BFS, and formal graph search are deferred.
- [ ] Network edges are described as modeled permissions or connections, not
      proof of exploitability.
