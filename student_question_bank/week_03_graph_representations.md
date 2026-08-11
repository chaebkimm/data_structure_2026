# Week 3 — Graph Models and Representations: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: distinguish major graph kinds, translate among diagrams, edge sets, and adjacency matrices, implement and validate a bounded unweighted matrix Graph, and compare matrix, edge-list, and adjacency-list trade-offs. DFS, BFS, weighted search, and dynamic adjacency-list construction are deferred.

Sources: [Module 3 teaching-package overview](../module_03_graph/README.md), [Module 3 full vocabulary reference](../module_03_graph/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| graph | A model made of vertices and the relationships between them. |
| vertex | One object in a graph; the plural is vertices. |
| edge | One direct relationship between two vertices. |
| endpoint | Either vertex named by an edge. |
| edge set | The collection of all edges in a graph. |
| directed edge | An edge with a source and destination, written `(u, v)` or `u → v`. |
| directed graph | A graph whose edges have direction. |
| undirected edge | An edge that connects its endpoints without a direction. |
| undirected graph | A graph whose edges have no direction. |
| weight | A number attached to an edge, such as cost, time, or distance. |
| weighted graph | A graph that stores a weight for each edge. |
| unweighted graph | A graph that records edge existence without edge weights. |
| adjacent | Directly joined by an edge. |
| neighbor | A vertex directly joined to another vertex. |
| source | The vertex where a directed edge begins. |
| destination | The vertex where a directed edge ends. |
| out-neighbor | The destination of an edge leaving a vertex. |
| in-neighbor | The source of an edge entering a vertex. |
| degree | The number of edges touching a vertex in an undirected graph. |
| out-degree | The number of directed edges leaving a vertex. |
| in-degree | The number of directed edges entering a vertex. |
| route | A vertex sequence in which every consecutive pair has the required edge. |
| path | A route that does not repeat a vertex. |
| cycle | A route that returns to its start without repeating another vertex. |
| reachable | Able to be reached from a stated start by following edges. |
| connected | Joined by a route in an undirected graph. |
| connected component | A largest group of mutually connected vertices in an undirected graph. |
| isolated vertex | A vertex with no incident edge. |
| adjacency matrix | A matrix where cell `[u][v]` records whether edge `u → v` exists. |
| Boolean value | A value with exactly two choices: `true` or `false`. |
| diagonal | Matrix cells whose row and column indexes are equal. |
| mirrored cells | Cells `[u][v]` and `[v][u]`. |
| symmetric matrix | A matrix in which every cell equals its mirror across the diagonal. |
| equivalent representations | Different storage or pictures that describe exactly the same graph. |
| fixed vertex set | A vertex collection whose count is chosen at initialization and does not later change. |
| active vertex index | An index from zero through one less than the graph’s vertex count. |
| self-loop | An edge from a vertex to itself. |
| parallel edges | Repeated edges with the same endpoints and direction. |
| simple graph | A graph with no self-loops and no parallel edges. |
| contract | Rules stating what an operation accepts, changes, reports, and preserves. |
| invariant | A rule that holds in every valid completed graph state. |
| validator | Code that checks whether stated representation rules hold. |
| malformed graph | A stored graph whose values break its invariant. |
| adjacency-list representation | A representation storing a collection of outgoing neighbors for each vertex. |
| edge-list representation | A sequence containing one endpoint pair per edge. |
| sparse graph | A graph with few edges compared with the number possible. |
| dense graph | A graph with many of its possible edges present. |
| `V` | The number of vertices used in a complexity expression. |
| `E` | The number of edges used in a complexity expression. |
| `O(V^2)` | Work that may grow with every row-and-column pair in a `V`-vertex matrix. |

## Anticipated student questions

### Meaning and mental model

- What can a graph represent that a tree cannot represent safely?
- What is the difference among a vertex, edge, neighbor, path, cycle, degree, and connected component?
- How do directed and undirected relationships differ in meaning?
- How is an unweighted graph different from a weighted graph even if both have the same endpoints?

### Representation and invariants

- What does `adjacency[from][to] == true` mean in a directed graph?
- Why must an undirected adjacency matrix be symmetric?
- Why must active diagonal cells be false under this course’s no-self-loop contract?
- What must be true of `vertex_count`, `kind`, active cells, and inactive cells immediately after `graph_init`, and which facts does later validation inspect?

### Operations, C API, and ownership

- Which indexes are valid after `graph_init` with `vertex_count == V`?
- Why do undirected add and remove operations need to update two matrix cells as one logical change?
- When must `graph_has_edge`, degree queries, and neighbor queries leave caller output unchanged?
- Why can an edge operation check only one selected pair while `graph_validate` checks the whole active graph?

### Tracing

- How do I translate the same graph among a drawing, an edge set, and an adjacency matrix?
- What matrix cells change when adding or removing one directed edge versus one undirected edge?
- How do I trace out-degree and in-degree without swapping rows and columns?
- In what order should `graph_out_neighbors` report neighbors, and how is that order visible in the matrix?

### Tests and debugging

- Which tests distinguish duplicate-edge, absent-edge, self-loop, and out-of-range failures?
- How can a test detect that an undirected add changed `[a][b]` but forgot `[b][a]`?
- What malformed graph should make a whole-graph validator fail even though an unrelated local query looks valid?
- In the Matrix Symmetry Autopsy, what two regression tests would prove both mutation and query behavior are repaired?

### Complexity

- Why is one adjacency-matrix edge lookup `O(1)`?
- Why does listing all outgoing neighbors from one vertex take `O(V)` with a matrix?
- Why does full matrix validation take `O(V^2)` even when the graph has few edges?
- For which dense or sparse workloads would a matrix, edge list, or adjacency list be the more plausible choice?

### Cybersecurity and interpretation

- Would a directed edge between two hosts mean communication, trust, authorization, or merely an observed record?
- How could silently treating a directed relation as undirected create a false security conclusion?
- Why must vertex identifiers be range-checked before any matrix access?
- Why are the course’s synthetic relationships unsuitable as evidence for scanning or exploiting live systems?

### Assignment and evidence

- Which graph operations and reports are required in the Week 3 core lab?
- Is DFS, BFS, weighted search, or dynamic adjacency-list construction required this week?
- What must the embedded Spiral 1 comparison say about choosing an ArrayList, tree, or graph?
- What evidence belongs in the Week 3 artifact and capstone skeleton without becoming a second submission?

### Transfer and prerequisites

- Which tree invariants become unnecessary, and which graph invariants must replace them?
- How will the neighbor order supplied by this representation affect later DFS and BFS traces?
- Why will graph traversal need separate visited state when tree traversal did not?
- What capstone decisions should remain representation-independent so the backend can change later?

### Extension and deferred questions — optional or later

- How would supporting self-loops change validation, degree definitions, and tests?
- How would weights change the matrix representation and the meaning of “no edge”?
- Could an adjacency list reduce work on a sparse graph, and what ownership problems would it introduce?
- Are graph searches and dynamically allocated adjacency lists part of Week 3 grading or later work?
