# Module 8 Teaching Package

## Tree Breadth-First Traversal: Nearer Nodes First

This package is the Tree stage of the third
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know breadth-first search vocabulary, tree
frontiers, width analysis, or balance factors before this module. Every
student-facing technical term is explained in ordinary language when first
needed. Assessment rewards a correct visiting rule and tested evidence, not
memorized wording, drawing quality, or speed.

## Module question

> How can we guarantee that every node close to the root is inspected before
> any deeper node?

## Core learning targets

Students will be able to:

1. explain breadth-first search and level order;
2. trace a Queue of node-and-depth work records;
3. explain why Queue order produces nondecreasing depth;
4. implement left-first level-order traversal;
5. find the first shallowest repeated value;
6. handle empty, missing, limit, and invalid-argument cases without changing
   caller outputs on failure;
7. compute edge height, level width, and maximum width;
8. explain `O(n)` time and `O(w)` auxiliary space;
9. compare BFS width cost with DFS height cost; and
10. calculate a balance factor and trace one supplied rotation without
    implementing AVL balancing.

A **traversal** is a planned procedure for visiting nodes. **Breadth-first
search (BFS)** visits nodes in nondecreasing depth, meaning nearer nodes
before deeper nodes. A **frontier** is the discovered work still waiting.
The supplied Queue stores one node pointer and its depth in each work record.

## Package map

```text
module_08_tree_bfs/
├── README.md
├── diagrams/
│   └── bfs_models.md
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
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── textbook.md
│   ├── tree_bfs_autopsy.md
│   └── vocabulary.md
├── release/
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_08_stage_a_*.zip … module_08_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/
    │   ├── tree_bfs.h
    │   └── tree_work_queue.h
    ├── starter/tree_bfs.c
    ├── solution/tree_bfs.c
    ├── support/
    │   ├── tree_support.c
    │   └── tree_work_queue.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_shallowest.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A. It withholds BFS, Queue, frontier,
   depth, width, formulas, code, and exact answers.
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

- completed `code/starter/tree_bfs.c`;
- completed `code/tests/test_student.c`;
- saved output from supplied and student-authored tests;
- exactly three original tests in the required categories;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record and Tree BFS Autopsy;
- corrected Cognitive Pause; and
- a short tree-to-graph transfer explanation.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Fixed course conventions

- A valid tree has no cycle and no shared node.
- The root has depth 0.
- Edge height uses `height(NULL) = -1` and `height(leaf) = 0`.
- Left children enter the Queue before right children.
- A `NULL` root is a valid empty tree.
- Every traversal and height failure leaves its caller output unchanged.
- A missing shallowest match leaves the caller's prior match unchanged.
- The teaching limit is 64 reached nodes and 64 pending work records.

The canonical repeated-value tree is a general binary tree, not a binary
search tree. A separate strict binary search tree is used only for the
balance-and-rotation preview.

## Relationship to the course spiral

- **Revisits:** tree nodes, pointers, `NULL`, Queue FIFO behavior, DFS,
  checked failures, ownership, and height.
- **Contrasts:** BFS remembers work across width; DFS remembers work along
  height.
- **Introduces:** frontier records, level order, shallowest-match search,
  maximum width, and balance-factor preview.
- **Forwards:** graph BFS with visited state in Module 9 and AVL balancing in
  Module 14.
