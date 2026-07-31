# Module 9 Teaching Package

## Graph Breadth-First Search: Minimum-Hop Reachability

This package is the Graph stage of the third
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know graph breadth-first search, discovery
timing, distance arrays, predecessor arrays, path reconstruction, or
adjacency-list ownership before this module. Every student-facing technical
term and symbol is explained in ordinary language when first needed.
Assessment rewards correct reasoning and reproducible evidence, not
memorized wording, drawing quality, or speed.

## Module question

> Which system is reachable in the fewest communication hops when
> relationships may branch, merge, and cycle?

## Core learning targets

Students will be able to:

1. transfer Queue-controlled breadth-first order from trees to graphs;
2. mark a vertex discovered immediately after its first successful enqueue;
3. trace Queue, visit, discovery, distance, and predecessor state;
4. explain why enqueue-time marking prevents duplicate pending work;
5. calculate minimum-hop distances in an unweighted graph;
6. reconstruct one deterministic minimum-hop path;
7. report an unreachable destination explicitly;
8. handle cycles, converging routes, and disconnected graphs;
9. produce equivalent results from an adjacency matrix and sorted adjacency
   lists;
10. compare matrix `O(V²)` and adjacency-list `O(V+E)` traversal; and
11. explain why hop count alone is not likelihood, exploitability,
    authorization, or real risk.

A **graph** stores items called vertices and connections called edges.
**Breadth-first search (BFS)** processes vertices in nondecreasing hop
distance from one source. A **hop** follows one edge. The supplied Queue,
matrix, and dynamic-neighbor-array support let students focus on when state
changes and what that state proves.

## Package map

```text
module_09_graph_bfs/
├── README.md
├── diagrams/
│   └── graph_bfs_models.md
├── instructor/
│   ├── answer_key.md
│   ├── lesson_plan.md
│   └── technical_notes.md
├── student/
│   ├── cognitive_pause.md
│   ├── evidence_template.md
│   ├── graph_bfs_autopsy.md
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
│   └── module_09_stage_a_*.zip … module_09_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/
    │   ├── graph_adj_list.h
    │   ├── graph_bfs.h
    │   ├── graph_matrix.h
    │   └── vertex_queue.h
    ├── starter/graph_bfs.c
    ├── solution/graph_bfs.c
    ├── support/
    │   ├── graph_adj_list.c
    │   ├── graph_bfs_support.c
    │   ├── graph_matrix.c
    │   └── vertex_queue.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_frontier.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A. It withholds formal BFS state, Queue
   terminology, representations, formulas, code, and exact answers.
3. Release Stage B after each student preserves the initial model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/graph_bfs.c`;
- completed `code/tests/test_student.c`;
- saved output from supplied and student-authored tests;
- exactly three original tests in the required categories;
- matrix/list comparison and cleanup evidence;
- completed evidence record and Graph BFS Autopsy;
- corrected Cognitive Pause; and
- a short Queue → tree BFS → graph BFS synthesis.

## Fixed course conventions

- Active vertex IDs are `0` through `vertex_count - 1`, with a maximum of
  16 vertices.
- Named sentinel value 16 means no distance or no predecessor.
- Directed BFS follows outgoing edges only.
- Outgoing neighbors are inspected in ascending vertex-ID order.
- A vertex is marked discovered only after its first enqueue succeeds.
- First discovery fixes its distance and predecessor permanently.
- Visit order records successful dequeue order.
- Every failed traversal or path operation preserves caller output.
- Matrix and sorted-list results are field-for-field identical.
- The optional full forest is traced on paper; code implementation is not
  required.

## Relationship to the course spiral

- **Revisits:** graphs, matrices, cycles, discovery state, Queue FIFO,
  breadth-first depth, checked limits, and output preservation.
- **Contrasts:** tree BFS has one route to each node; graph BFS must prevent
  repeated scheduling through merging routes and cycles.
- **Introduces:** minimum-hop distance, predecessor, path certificate,
  unreachable state, and dynamic neighbor arrays.
- **Forwards:** adjacency lists, Priority Queues, Heaps, Dijkstra, and Prim.
