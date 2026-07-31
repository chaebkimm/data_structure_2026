# Module 6 Teaching Package

## Graph Depth-First Search

This package is the Graph stage of the second
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know graph depth-first search, visited state,
recursion on a graph, or connected-component counting before this module.
Every student-facing technical term is explained in ordinary language when
first needed. Assessment rewards accurate reasoning, not memorized wording.

## Module question

> A tree branch does not reconnect to an earlier branch. What must change
> when a graph route can lead back to a vertex already reached?

## Core learning targets

Students will be able to:

1. explain why graph search needs one yes-or-no visited record per vertex;
2. distinguish a discovered vertex from a vertex already processed;
3. trace recursive depth-first search through outgoing directed edges;
4. trace iterative depth-first search with a Stack of vertex identifiers;
5. determine which vertices are reachable from one source;
6. explain why one search may not cover a disconnected graph;
7. count connected components in an undirected graph;
8. implement recursive and iterative graph DFS in C;
9. preserve caller outputs when an operation fails; and
10. compare adjacency-matrix and adjacency-list search costs.

A **vertex** is one item in a graph. An **edge** is a stored connection.
**Depth-first search (DFS)** follows one route deeply before returning to
another waiting choice. A vertex is **visited** here as soon as it has been
discovered and scheduled, so it is not scheduled twice. A **connected
component** is one largest group in an undirected graph whose vertices can
reach one another.

## Package map

```text
module_06_graph_dfs/
├── README.md
├── diagrams/
│   └── dfs_models.md
├── instructor/
│   ├── answer_key.md
│   ├── lesson_plan.md
│   └── technical_notes.md
├── student/
│   ├── cognitive_pause.md
│   ├── evidence_template.md
│   ├── graph_dfs_autopsy.md
│   ├── inquiry_prompt.md
│   ├── inquiry_prompt_linear.md
│   ├── investigation_worksheet.md
│   ├── investigation_worksheet_linear.md
│   ├── lab.md
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── textbook.md
│   └── vocabulary.md
├── release/
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_06_stage_a_*.zip … module_06_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/
    │   ├── graph_dfs.h
    │   ├── graph_matrix.h
    │   └── vertex_stack.h
    ├── starter/graph_dfs.c
    ├── solution/graph_dfs.c
    ├── support/
    │   ├── graph_matrix.c
    │   └── vertex_stack.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   ├── test_self_loop.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_cycle_dfs.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A. It withholds DFS terminology, visited
   state, formal procedures, code, and exact answers.
3. Release Stage B after each student preserves the initial route model.
4. Release Stage C after the three-target Cognitive Pause and comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/graph_dfs.c`;
- completed `code/tests/test_student.c`;
- saved output from supplied and student-authored tests;
- three original tests, one in each required category;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record and Graph DFS Autopsy;
- corrected Cognitive Pause; and
- a short tree-to-graph transfer explanation.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Relationship to the course spiral

- **Revisits:** the Module 3 adjacency matrix, Module 4 LIFO Stack, Module 5
  recursive and iterative depth-first models, checked errors, and cleanup.
- **Introduces:** visited-aware graph DFS, source reachability, and
  undirected connected-component counting.
- **Forwards:** Queue-based breadth-first search in Modules 7–9 and graph
  path algorithms later in the course.
