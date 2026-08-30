# Module 3 Teaching Package

## Directed Graphs in a Fixed Adjacency Matrix

This package is the Graph stage of the first Linear -> Tree -> Graph spiral
in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know graph vocabulary or two-dimensional arrays
before this module. Define each student-facing term in ordinary language
before use. Assessment rewards accurate relationship and matrix reasoning,
not memorized terminology.

## Module question

> How can a fixed grid record one-way relationships that may cross branches,
> point backward, or form cycles?

## Canonical implementation

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
    size_t vertex_count;
    int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

The lab implements one bounded, directed, unweighted graph. Vertex IDs are
`0` through `vertex_count - 1`. Cell `grid[from][to]` is 1 exactly when
that directed edge exists; otherwise it is 0.

The only public functions are:

```c
int graph_init(struct DirectedGraph *graph, size_t vertex_count);
int graph_add_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_remove_edge(struct DirectedGraph *graph, size_t from, size_t to);
int graph_out_degree(
    const struct DirectedGraph *graph,
    size_t vertex,
    size_t *out_degree
);
```

Each returns 1 on success and 0 on rejection. Initialization clears all 256
cells, not only the active square. Adding and removing are idempotent:
repeating a valid addition or removal succeeds without another state change.
Addition rejects a self-loop. Every rejected mutation leaves the complete
object unchanged. An out-degree failure leaves the caller's output unchanged.

A direct guarded read of `graph.grid[from][to]` is core. It is not a fifth
library function.

## Core learning targets

Students will be able to:

1. explain graph, vertex, directed edge, path, cycle, and out-degree;
2. distinguish direction from its reverse and trace a cycle longer than one
   edge;
3. translate a directed graph among a diagram, ordered edge set, and matrix;
4. map `grid[from][to]` to row-as-source and column-as-destination;
5. initialize a bounded graph while clearing active and inactive cells;
6. add or remove an edge with checked, failure-preserving behavior;
7. perform a guarded direct lookup and count one row's outgoing edges;
8. explain the fixed-matrix invariant and operation costs;
9. compare the implemented matrix conceptually with undirected graphs,
   weighted edges, edge lists, adjacency lists, and components; and
10. support claims with three student-authored tests and tool evidence.

Undirected mutation, weights, graph traversal, component computation, edge
lists, and adjacency lists are not implementation requirements. Formal DFS
and BFS begin in later modules.

## Canonical three-vertex trace

Use active vertices 0, 1, and 2 with edges:

```text
0 -> 1
1 -> 2
1 -> 0
```

The two opposite edges `0 -> 1` and `1 -> 0` are separate facts and form a
valid length-two directed cycle. Initially row 1 is `[1, 0, 1]`, so vertex
1 has out-degree 2. After removing `1 -> 2`, row 1 is `[1, 0, 0]` and its
out-degree is 1.

## Package map

```text
module_03_graph/
|-- README.md
|-- diagrams/graph_models.md
|-- instructor/
|   |-- answer_key.md
|   |-- lesson_plan.md
|   `-- technical_notes.md
|-- student/
|   |-- cognitive_pause.md
|   |-- evidence_template.md
|   |-- inquiry_prompt.md
|   |-- inquiry_prompt_linear.md
|   |-- investigation_worksheet.md
|   |-- investigation_worksheet_linear.md
|   |-- lab.md
|   |-- matrix_autopsy.md
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- textbook.md
|   `-- vocabulary.md
|-- release/
|   |-- release_manifest.md
|   |-- prepare_student_release.ps1
|   |-- stage_a_README.md ... stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/graph_matrix.h
    |-- starter/graph_matrix.c
    |-- solution/graph_matrix.c
    |-- tests/test_core.c
    |-- tests/test_extension.c
    |-- tests/test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_ghost_connection.c
```

## Recommended release order

1. Validate the reference implementation before preparing archives.
2. Release Stage A's standard or linear inquiry before Meeting A. Withhold
   vocabulary and the formal matrix model.
3. Preserve the first model, then release Stage B's representation,
   vocabulary, and three-target Cognitive Pause.
4. Release Stage C after the pause and instructor calibration.
5. Release Stage D's textbook and diagram/text models only after the Stage C
   attempt is saved. Do not reveal the Stage E autopsy result.
6. Release Stage E for Meeting B.
7. Keep instructor materials, the solution, and extension tests private until
   the chosen review point.

The standard and linear versions have the same targets. The plan provides
two 90-minute meetings and a 100-point rubric.

## Core submission

Students submit:

- completed `code/starter/graph_matrix.c`;
- three distinct tests in `code/tests/test_student.c`, with rationales;
- supplied and student-test transcripts;
- warning-enabled and supported diagnostic or instructor-CI evidence;
- completed evidence record;
- Matrix Autopsy;
- corrected Cognitive Pause; and
- Spiral 1 structure-choice comparison.

## Relationship to the course spiral

- **Revisits:** fixed arrays, indexes, bounds, tree paths, and invariants.
- **Introduces:** general directed relationships, matrix representation,
  out-degree, directed cycles, and graph representation trade-offs.
- **Previews:** Stack and depth-first exploration, Queue and breadth-first
  exploration, weighted paths, and spanning trees.
