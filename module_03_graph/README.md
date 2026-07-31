# Module 3 Teaching Package

## Graph Models and Representations

This package is the Graph stage of the first Linear → Tree → Graph spiral in
**Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know graph vocabulary, two-dimensional arrays,
or graph algorithms before this module. Every student-facing technical term
is defined in ordinary language before it is used. Assessment rewards
accurate reasoning, not memorized wording.

## Module question

> What representation is needed when relationships may cross branches, point
> backward, or form cycles?

## Core learning targets

Students will be able to:

1. explain graph, vertex, edge, neighbor, degree, path, cycle, and connected
   component;
2. distinguish directed from undirected and weighted from unweighted graphs;
3. translate one graph among a diagram, edge set, and adjacency matrix;
4. explain why an undirected adjacency matrix is symmetric;
5. build and test a bounded, unweighted graph in a fixed Boolean matrix;
6. add, remove, query, count, and report relationships safely;
7. distinguish local edge checks from full graph validation;
8. compare an adjacency matrix, edge list, and adjacency list; and
9. choose among an ArrayList, tree, and graph for a small scenario.

A **Boolean value** is either true or false. A **graph search** is a planned
procedure for finding or visiting vertices. Depth-first search (DFS),
breadth-first search (BFS), weighted-path algorithms, and dynamically
allocated adjacency lists are deferred to later modules.

## Package map

```text
module_03_graph/
├── README.md
├── diagrams/
│   └── graph_models.md
├── instructor/
│   ├── answer_key.md
│   ├── lesson_plan.md
│   └── technical_notes.md
├── student/
│   ├── cognitive_pause.md
│   ├── evidence_template.md
│   ├── inquiry_prompt.md
│   ├── inquiry_prompt_linear.md
│   ├── investigation_worksheet.md
│   ├── investigation_worksheet_linear.md
│   ├── lab.md
│   ├── matrix_autopsy.md
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── textbook.md
│   └── vocabulary.md
├── release/
│   ├── release_manifest.md
│   ├── prepare_student_release.ps1
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_03_stage_a_*.zip … module_03_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/graph_matrix.h
    ├── starter/graph_matrix.c
    ├── solution/graph_matrix.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_undirected.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A; it does not reveal formal graph names or
   representations.
3. Release Stage B after each student preserves the initial relationship
   model.
4. Release Stage C after the timed Cognitive Pause and instructor
   explanation.
5. Release Stage D only after the student preserves the Stage C core attempt.
6. Release Stage E for Meeting B.
7. Keep `instructor/`, `code/solution/`, and `code/tests/test_extension.c`
   instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/graph_matrix.c`;
- saved text printed by the supplied tests;
- three original tests with a short explanation of each test's purpose;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record;
- Matrix Symmetry Autopsy;
- corrected Cognitive Pause; and
- Spiral 1 structure-choice comparison.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Relationship to the course spiral

- **Revisits:** arrays, indexes, fixed storage, tree paths, cycles, and
  whole-structure rules.
- **Introduces:** general graph relationships, matrix symmetry, direction,
  weights, and representation trade-offs.
- **Previews:** Stack and depth-first exploration, Queue and breadth-first
  exploration, weighted shortest paths, and spanning trees.
