# Module 5 Teaching Package

## Tree Depth-First Traversal

This package is the Tree stage of the second
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know traversal orders, recursion, call frames,
or depth-first search before this module. Each student-facing technical term
is explained in ordinary language when first needed. Assessment rewards
accurate reasoning, not memorized wording.

## Module question

> If we follow one branch as far as possible, how do we remember every branch
> to which we must return?

## Core learning targets

Students will be able to:

1. explain depth-first exploration as following one branch before returning;
2. identify `NULL` as the stopping case for an absent subtree;
3. trace preorder, inorder, and postorder visits;
4. explain what an active recursive call must remember;
5. implement recursive preorder traversal;
6. reproduce left-first preorder with a typed `const TreeNode *` Stack;
7. complete strict binary-search-tree search from the Module 2 ordering rule;
8. explain and test the supplied insertion baseline;
9. destroy individually allocated nodes in postorder; and
10. analyze traversal as `O(n)` time and `O(h)` extra space.

A **traversal** is a planned procedure for visiting every tree node.
**Recursion** occurs when a function calls itself directly or through other
functions. **Depth-first search (DFS)** follows one branch deeply before
returning to another saved choice. A **typed Stack** is a Stack designed for
one kind of item; this module's explicit Stack stores tree-node pointers.
In the cost notation, `n` is the node count and `h` is tree height.

## Package map

```text
module_05_tree_dfs/
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
│   ├── inquiry_prompt.md
│   ├── inquiry_prompt_linear.md
│   ├── investigation_worksheet.md
│   ├── investigation_worksheet_linear.md
│   ├── lab.md
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── textbook.md
│   ├── tree_dfs_autopsy.md
│   └── vocabulary.md
├── release/
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_05_stage_a_*.zip … module_05_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/tree_dfs.h
    ├── include/tree_node_stack.h
    ├── starter/tree_dfs.c
    ├── solution/tree_dfs.c
    ├── support/tree_support.c
    ├── support/tree_node_stack.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_preorder.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A; it withholds the formal exploration
   names, recursion model, traversal names, and code.
3. Release Stage B after each student preserves the initial branch-return
   model.
4. Release Stage C after the timed Cognitive Pause and instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/tree_dfs.c`;
- completed `code/tests/test_student.c`;
- saved output from the supplied and student-authored tests;
- three original tests with a short explanation of each purpose;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record;
- Tree DFS Autopsy;
- corrected Cognitive Pause; and
- a short tree-to-graph transfer explanation.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Relationship to the course spiral

- **Revisits:** binary-tree links, `NULL`, BST ordering, Stack behavior,
  ownership, checked errors, and failure preservation.
- **Introduces:** recursive and explicit-stack DFS, three traversal orders,
  active call frames, and postorder destruction.
- **Forwards:** visited-aware graph DFS in Module 6, BST operations in
  Module 14, and AVL height reasoning.
