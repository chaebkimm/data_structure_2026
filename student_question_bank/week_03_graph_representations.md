# Week 3 — Directed Adjacency Matrices: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Required scope: represent a fixed directed, unweighted graph with `vertex_count` and an integer adjacency matrix; implement initialization, directed addition, directed removal, and out-degree; and use guarded direct lookup. Undirected graphs, weights, edge lists, adjacency lists, and connected components are conceptual comparisons. Graph search is deferred.

Sources: [Module 3 teaching-package overview](../module_03_graph/README.md), [Module 3 full vocabulary reference](../module_03_graph/student/vocabulary.md), and [Weeks 1–7 anticipated-question source](01_weeks_01_07_questions.md).

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| graph | A model of vertices and the relationships among them. |
| vertex | One item in a graph. |
| edge | One direct relationship between two vertices. |
| directed graph | A graph whose edges have a start and an end. |
| undirected graph | A graph whose edges do not distinguish a start and an end. |
| source | The vertex where a directed edge starts. |
| destination | The vertex where a directed edge ends. |
| degree | The number of edges touching one vertex; directed graphs separate incoming and outgoing counts. |
| out-degree | The number of directed edges leaving one vertex. |
| in-degree | The number of directed edges entering one vertex. |
| path | A sequence that follows edges without repeating a vertex. |
| cycle | A route that returns to its starting vertex without repeating another vertex. |
| self-loop | An edge whose source and destination are the same vertex. |
| weight | A number such as cost or delay attached to an edge. |
| unweighted graph | A graph that records edge existence without an edge value. |
| edge list | A sequence that stores the graph's edges one by one. |
| adjacency list | A representation that stores a neighbor collection for each vertex. |
| adjacency matrix | A square table in which row and column indexes identify a possible edge. |
| connected component | An undirected connected group that cannot be extended by adding another vertex. |
| isolated vertex | An active vertex with no incoming or outgoing edges. |
| symmetric matrix | A matrix whose value at `[u][v]` equals its value at `[v][u]`. |
| row | A horizontal line of matrix cells; this module uses it for an edge source. |
| column | A vertical line of matrix cells; this module uses it for an edge destination. |
| grid cell | One position in a row and column. |
| diagonal | Cells whose row and column indexes are equal. |
| two-dimensional array | An array made of indexed rows and columns. |
| active vertex | A vertex whose index is lower than `vertex_count`. |
| inactive row or column | A reserved row or column whose index is not currently active. |
| `size_t` | A nonnegative C integer type used for sizes and indexes. |
| `GRAPH_MAX_VERTICES` | The fixed capacity of the graph's rows and columns. |

## Anticipated student questions

### Meaning and mental model

- What can a graph represent that Chapter 2's tree cannot represent as a valid tree?
- What is the difference among a vertex, an edge, a path, and a cycle?
- Why are `u -> v` and `v -> u` separate facts in a directed graph?
- What information does this unweighted graph omit from an edge?

### Representation and invariants

- What does `grid[from][to] == 1` mean?
- How does `vertex_count` distinguish an isolated active vertex from an inactive index?
- Why must every inactive row and column remain zero?
- Why is a self-loop forbidden here even though a cycle through two or more vertices is valid?

### Operations and C

- Why does `graph_init` clear all 16 by 16 cells even when only seven accounts are active?
- Which checks must occur before a direct grid lookup or update?
- Why may a repeated valid add or removal succeed without changing the final cell value?
- What do `size_t` and `GRAPH_MAX_VERTICES` contribute to the fixed representation?

### Tracing

- Which cells record the follows `0 -> 1`, `1 -> 2`, `2 -> 0`, `2 -> 3`, `4 -> 5`, and `5 -> 4` for Mina, Joon, Sora, Dae, Hana, Leo, and Nuri?
- Why is Sora's initial row `[1, 0, 0, 1, 0, 0, 0]`, and what is her out-degree?
- After removing `2 -> 3`, what is row 2 and what out-degree should be reported?
- How can `0 -> 1 -> 2 -> 0` form a valid cycle while every diagonal cell remains zero?
- Why is Nuri initially isolated while Dae, who also follows nobody, is not?

### Components and feeds — after the Stage C attempt

- What does maximal mean when identifying a connected component?
- Why do weak components ignore arrow directions while strong components require directed paths in both directions?
- Why do Mina, Joon, and Sora form a strong component without every pair following each other directly?
- Why does Dae share their weak component but form a separate strong component?
- Which components change when Sora unfollows Dae?
- How could component membership help select candidate posts without determining their ranking?
- Why can restricting Sora's feed to her strong component exclude a directly followed account?
- How could an isolated account such as Nuri receive recommendations, and why does connectivity not grant permission to view a post?

### Tests and debugging

- How can a test prove that initialization clears cells outside the active square?
- Which test distinguishes a directed edge from its reverse edge?
- How can a test prove that a rejected bound or self-loop addition changes no matrix cell?
- How can a test prove that a failed out-degree request leaves its output unchanged?

### Complexity

- Why does reading, adding, or removing one checked edge take constant work?
- Why does out-degree counting inspect every active cell in one row?
- Why does inspecting an active matrix take work proportional to the vertex count squared?
- Why can a fixed adjacency matrix waste storage when few edges exist?

### Safety and interpretation

- What can happen if a vertex index is used before it is checked against `vertex_count`?
- Why do the four functions assume the rest of the supplied matrix already satisfies its invariant?
- How can a stale 1 in an inactive row reappear as a ghost connection later?
- Why does an all-zero row mean no outgoing edges rather than no vertex?

### Assignment and evidence

- Which four functions are implementation tasks, and which guarded lookup remains a direct operation?
- What three distinct student-designed tests are required?
- What build, diagnostic, and explanation evidence belongs in the submission?
- Why are Boolean graph kinds, validators, DFS, BFS, and dynamic adjacency lists outside this lab?

### Representation comparison

- How would an undirected connection differ from the directed matrix operation implemented here?
- How would an edge list and an adjacency list store the same relationships differently?
- When might a matrix be preferable to a list representation, and when might it be wasteful?
- Why are weights and connected-component algorithms discussed without being implemented here?

### Transfer to later modules

- Why will a later traversal need visited state when this graph contains a cycle?
- How will scanning matrix columns in increasing order influence later traversal traces?
- What new support must Module 6 add before it can operate on undirected graphs?
- How do the ArrayList, tree, and graph representations differ in their central invariant?
