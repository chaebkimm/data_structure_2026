# Module 15 - Prim and Kruskal

This final graph module asks one question in two ways: how can every site in
each connected part of a weighted, undirected graph be joined at minimum
total weight?

The package is beginner-first. A **graph** stores items called **vertices**
and relationships called **edges**. An **undirected edge** works both ways.
Its **weight** is the signed whole-number cost attached to it. A **minimum
spanning tree (MST)** connects every vertex of one connected graph, contains
no **cycle** (a route that returns to its start), and has the least possible
total weight. A disconnected graph has a **minimum spanning forest (MSF)**:
one minimum tree for each connected component. **Connected** means a route
exists between every pair of vertices in the group; a **component** is one
largest such group.

An **algorithm** is a defined sequence of problem-solving steps. Students
trace both algorithms, complete the bounded C starters, validate
their results, and compare minimum cost with resilience. The supplied graph,
minimum-Heap, sorting, and Disjoint-Set Union support keep attention on the
two core decisions:

A **binary minimum Heap** is a tree-shaped array that removes the smallest
pending key first. **Disjoint-Set Union (DSU)** stores which vertices are
currently in the same group.

- Prim repeatedly accepts the cheapest current connection from a reached
  vertex to an unreached vertex.
- Kruskal considers all logical edges from least weight upward and accepts
  an edge only when Disjoint-Set Union says its endpoints were in different
  components.

## Learning outcomes

By the end, students can:

1. distinguish a shortest-path tree from an MST;
2. state the signed, weighted, undirected input contract;
3. trace Prim's frontier and Kruskal's component merges;
4. explain the roles of a binary minimum Heap and Disjoint-Set Union;
5. complete and test both bounded core loops;
6. validate a spanning tree or forest;
7. explain why valid MSTs can select different edges but have equal weight;
8. choose an algorithm for a supplied representation; and
9. explain why minimum cost alone does not provide resilience.

## Input and result contract

- Vertex IDs are **dense**, meaning they have no gaps, from 0 through
  `vertex_count - 1`.
- At most 16 vertices, 120 logical edges, and 240 incident records are used.
- A **logical edge** is one connection. It has exactly two **incident
  records**, one stored view from each endpoint (each vertex it connects).
- A **self-loop** connects a vertex to itself. It has two identical incident
  records and is never selected.
- **Parallel edges** connect the same endpoint pair but have different edge
  IDs, so they remain distinct candidates.
- Weights use `int64_t`, C's signed 64-bit whole-number type; negative and
  zero weights are valid.
- Supplied support computes the mathematical total independently of selected
  edge order. Cancellation is allowed, and the total is published only when
  the final value fits `int64_t`.
- Prim's **frontier**, its pending choices, is lazy: an improved choice is
  added while its older record remains until removal. It permits at most
  `E + V`, or 136, total pushes.
- A result for `V` vertices and `c` components contains exactly `V - c`
  selected edges.
- Prim and Kruskal must agree on total weight, but equal-weight alternatives
  can make their selected edge IDs differ.

The algorithms receive an undirected representation. They do not silently
reinterpret a directed graph.

## Canonical connected fixture

Letters are display labels for dense IDs `A=0` through `E=4`.

| Edge ID | Endpoints | Weight |
|---:|---|---:|
| 0 | A-B | 4 |
| 1 | A-C | 4 |
| 2 | B-C | 1 |
| 3 | B-D | 5 |
| 4 | C-D | 2 |
| 5 | C-E | 3 |
| 6 | D-E | 3 |
| 7 | A-E | 10 |

Starting Prim at A selects IDs `0, 2, 4, 5`. Kruskal selects IDs
`2, 4, 5, 0`. Each result has four edges, one component, and total weight
10.

Exact equality of edge order is not a correctness requirement. The tests
instead verify membership, acyclicity, component coverage, edge count, and
total.

The initial inquiry may stop choosing offers once every site is reached.
That is an inquiry shortcut, not the implementation contract. Full Kruskal
examines every logical edge so its decision ledger also records later cycle
and self-loop rejections.

## Five-stage release

The staged materials preserve prediction before explanation:

1. **Stage A:** ordinary-language site-planning inquiry;
2. **Stage B:** representation reveal and exactly-three-target pause;
3. **Stage C:** paired standard and linear investigation worksheets;
4. **Stage D:** ultra-concise textbook and equivalent models; and
5. **Stage E:** lab, evidence files, starter code, visible tests, and the
   bounded cycle autopsy.

See [the release manifest](release/release_manifest.md) for timing,
exclusions, exact archive contents, and instructor checks. Generate the
archives only after source review:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File `
  .\release\prepare_student_release.ps1
```

The script checks the exact 47-file source inventory and refuses to
overwrite an existing archive.

## Package map

```text
module_15_prim_kruskal/
|-- README.md
|-- diagrams/
|   `-- mst_models.md
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
|   |-- mst_cycle_autopsy.md
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- textbook.md
|   `-- vocabulary.md
|-- release/
|   |-- prepare_student_release.ps1
|   |-- release_manifest.md
|   |-- stage_a_README.md
|   |-- stage_b_README.md
|   |-- stage_c_README.md
|   |-- stage_d_README.md
|   |-- stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/
    |   |-- dsu.h
    |   |-- minimum_spanning_forest.h
    |   |-- prim_frontier.h
    |   `-- undirected_edge_list.h
    |-- starter/
    |   |-- kruskal.c
    |   `-- prim.c
    |-- solution/
    |   |-- kruskal.c
    |   `-- prim.c
    |-- support/
    |   |-- dsu.c
    |   |-- mst_support.c
    |   |-- prim_frontier.c
    |   `-- undirected_edge_list.c
    |-- tests/
    |   |-- test_core.c
    |   |-- test_extension.c
    |   `-- test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_endpoint_cycle.c
```

## Teaching sequence

- Begin with [the standard inquiry](student/inquiry_prompt.md) or
  [linear inquiry](student/inquiry_prompt_linear.md), not both.
- Reveal [the representation](student/representation_reveal.md), collect
  [the Cognitive Pause](student/cognitive_pause.md), and only then open
  [the vocabulary](student/vocabulary.md).
- Use the
  [standard investigation](student/investigation_worksheet.md) or its
  [linear equivalent](student/investigation_worksheet_linear.md).
- Calibrate with [the textbook](student/textbook.md) and
  [the model set](diagrams/mst_models.md).
- Complete [the lab](student/lab.md), preserve
  [evidence](student/evidence_template.md), apply
  [the rubric](student/rubric.md), and investigate
  [the cycle autopsy](student/mst_cycle_autopsy.md).

Instructor-only support consists of the
[lesson plan](instructor/lesson_plan.md),
[answer key](instructor/answer_key.md), and
[technical notes](instructor/technical_notes.md).

## Build boundary

The full instructor build commands are documented in
[the code guide](code/README.md). Stage E receives a smaller build surface
that exposes only starter core tests, student tests, and the safe isolated
autopsy. It contains no solution or extension target.

All Module 13 and Module 12 ideas needed by the lab are copied or adapted
inside this module. Builds do not include files from sibling module
directories and require no earlier compiled binary.

## Security and interpretation boundary

The examples use synthetic, authorized data. A selected edge means only
that the stored model chose a low-cost connection. It does not prove that a
real connection is trusted, available, correctly priced, or secure.

Every edge in a tree is a single point of failure: removing it separates
that tree. A minimum-cost design therefore needs a separate resilience
analysis. **Resilience** is the ability to keep working after a failure; it
can require additional approved connections.
