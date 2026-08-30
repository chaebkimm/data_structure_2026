# Module 2 Teaching Package

## Expression Trees with Child-Only Binary Links in C

This package is the Tree stage of the first Linear -> Tree -> Graph spiral
in **Data Structures Course 2026**. It follows Chapter 2's locally declared
nodes and two named child positions.

## Beginner-first rule

Chapter 1 supplies fixed arrays, conditions, loops, and invariants. This
module introduces explicit structure tags, object addresses, child pointers,
`NULL`, and recursion. Explain each new term in ordinary language before
students use it.

## Module question

> How can local node variables form a hierarchy using left and right links,
> and how can we find data or clear a branch without disturbing another side?

## Canonical model

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

The canonical fixture represents `(3 + 5) * 2` with five live local nodes:

```text
          root:'*'
          /      \
     plus:'+'    two:2
       /   \
  three:3 five:5
```

Its current-node/left/right sequence is `'*', '+', 3, 5, 2`. The operator
and number values all fit in the `int data` field because C character
constants such as `'*'` and `'+'` have type `int`. Left and right preserve
operand order; they are not interchangeable expression positions.

Create nodes as ordinary variables and connect their addresses. A node has
no stored upward link. Left and right are independent: a right-only child is
valid, and removing the left branch never shifts the right branch.

For the canonical fixture, clearing and detaching `plus` leaves `two` on the
right. That is a valid generic binary tree, but it is no longer a completed
binary expression because `root` has only one operand.

The expression fixture uses zero children for number nodes and two children
for its binary operators. The underlying `TreeNode` representation remains a
general binary tree, so valid test fixtures may also contain exactly one
child, repeated values in distinct nodes, or values with no arithmetic
meaning.

The caller must keep every referenced node initialized and alive and ensure
the structure is finite, acyclic, and unshared. An empty-side check does not
establish those whole-tree properties.

The two required library functions are:

```c
struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

Search checks the current node, then the complete left subtree, then the
right subtree, returning the first match or `NULL`. Clearance resets every
reachable node's data to zero and its links to `NULL`. It does not end the
local objects' lifetimes or detach an outside incoming link. To remove a
left branch, the caller clears it and then sets that left link to `NULL`.
Zero remains a valid data value; only `NULL` marks an empty child link.

## Core learning targets

Students will be able to:

1. explain root, parent, child, sibling, leaf, path, depth, height, and subtree;
2. translate a binary hierarchy among a diagram, a left/right table, and C;
3. initialize local nodes and distinguish `node`, `&node`, `node.data`,
   and `p->data`;
4. attach a fresh, unlinked node to a chosen empty side without replacing an
   occupied link;
5. distinguish a local side check from the caller's no-cycle/no-sharing rule;
6. implement and trace current-left-right recursive search;
7. implement cascading clearance and explicitly detach a selected branch;
8. show that the opposite side stays unchanged and cleared local objects
   remain alive while their scope is active; and
9. explain operation costs and support claims with tests and tool evidence.

Direct initialization, guarded attachment, and clear-then-detach removal
are core examples and student-test work, not additional library APIs.
Only `tree_find` and `tree_clear` are starter implementation tasks.
Search-tree ordering and balancing are outside this module.

## Package map

```text
module_02_binary_tree/
|-- README.md
|-- diagrams/tree_models.md
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
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- textbook.md
|   |-- tree_autopsy.md
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
    |-- include/binary_tree.h
    |-- starter/binary_tree.c
    |-- solution/binary_tree.c
    |-- tests/test_core.c
    |-- tests/test_extension.c
    |-- tests/test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_cascade.c
```

## Recommended release order

1. Validate the reference implementation before preparing archives.
2. Release Stage A's standard or linear inquiry before Meeting A; withhold
   the representation and vocabulary.
3. Preserve the first model, then release Stage B's left/right reveal,
   vocabulary, and three-target Cognitive Pause.
4. Release Stage C after the pause and instructor calibration.
5. Release Stage D's textbook and diagram/text models only after the Stage C
   attempt is saved. Do not include worked Stage E autopsy answers.
6. Release Stage E for Meeting B.
7. Keep `instructor/`, `code/solution/`, and instructor extension tests
   private until the chosen review point.

The standard and linear materials have the same targets. The plan provides
two 90-minute meetings and a 100-point core rubric.

## Core submission

Students submit:

- completed `code/starter/binary_tree.c`;
- three nonduplicate tests in `code/tests/test_student.c`, with rationales;
- supplied and student-test transcripts;
- warning-enabled and supported runtime-check, debugger, or instructor-CI
  evidence;
- the evidence record and corrected Cognitive Pause; and
- the Tree Structure Autopsy.

Extensions provide additional tests of the same model, not extra required
APIs or graph-validation algorithms.

## Relationship to the course spiral

- **Revisits:** conditions, loops, fixed representations, and invariants.
- **Introduces:** local node objects, addresses, child-only binary links,
  current-node/left/right recursive search, and cascading clearance.
- **Previews:** shared relationships in Module 3, deeper traversal analysis
  in Module 5, breadth-first traversal in Module 8, and later ordered trees.
