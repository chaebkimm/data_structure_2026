# Module 2 Teaching Package

## Binary-Tree Foundations and Binary Search Tree (BST) Preview

This package is the Tree stage of the first Linear → Tree → Graph spiral in
**Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know tree vocabulary or pointer-linked
structures before this module. Every student-facing technical term is defined
in ordinary language when it first appears. Assessment rewards accurate
reasoning, not memorized wording.

## Module question

> How can separate memory objects represent a hierarchy, and what rules prevent those links from becoming an arbitrary graph?

## Core learning targets

Students will be able to:

1. explain node, root, parent, child, leaf, path, depth, height, and subtree;
2. translate one tree among a diagram, index table, and C pointer fields;
3. state the rules for a completed rooted binary tree;
4. build nodes safely in a fixed, non-resizing array;
5. implement checked leaf, child-count, local link, and immediate-family
   operations;
6. distinguish local link safety from whole-tree validity;
7. trace a supplied binary search tree validator—a function that checks
   stated rules—that rejects duplicate keys;
8. explain why shared or many-to-many relationships lead toward graphs.

General **traversal** (systematically visiting nodes), **dynamic allocation**
(requesting storage while a program runs), student-written **recursion** (a
function calling itself), tree **rotations** (small link rearrangements), and
tree **balancing** (keeping branch heights reasonably similar) are deferred
to later modules.

## Package map

```text
module_02_binary_tree/
├── README.md
├── diagrams/
│   └── tree_models.md
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
│   ├── tree_autopsy.md
│   └── vocabulary.md
├── release/
│   ├── release_manifest.md
│   ├── prepare_student_release.ps1
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_02_stage_a_*.zip … module_02_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/tree_arena.h
    ├── starter/tree_arena.c
    ├── solution/tree_arena.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_links.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A; it does not reveal the node struct.
3. Release Stage B after initial hierarchy models are preserved.
4. Release Stage C after the timed Cognitive Pause and instructor
   explanation.
5. Release Stage D only after the student has preserved the Stage C core
   attempt between meetings.
6. Release Stage E for Meeting B.
7. Keep `instructor/` and `code/solution/` instructor-only until revisions
   close.

## Core submission

Students submit:

- completed `code/starter/tree_arena.c`;
- supplied-test transcript;
- three nonduplicate student-authored tests with rationale;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record;
- Tree Structure Autopsy;
- corrected Cognitive Pause.

## Relationship to the course spiral

- **Revisits:** addresses, pointers, `NULL`, arrays, and invariants (rules
  that must remain true in every valid state).
- **Introduces:** tree relationships, whole-structure validation, fixed node
  arenas, and global BST ordering.
- **Previews:** graph relationships in Module 3, depth-first traversal in
  Module 5, breadth-first traversal in Module 8, and BST/AVL mastery in
  Module 15.
