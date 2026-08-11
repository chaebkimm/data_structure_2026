# Module 15 Teaching Package

## BST-to-AVL Synthesis

## 14-week delivery role - Week 13

This is the required Week 13 tree unit and produces **one submission**; see
the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
The complete inquiry, rotation, insertion, measurement, and validation path
fits one 180-minute contact block. Edge-height, stored height, and balance
factor receive their first required formal introduction here; Week 8 uses
level-order traversal without assigning height/balance work.

AVL insertion remains the implementation core. Full AVL deletion stays out
of scope, and optional Stage E extensions or the unsafe autopsy do not create
another submission.

This package is the Tree stage of the fifth
Linear -> Tree -> Graph spiral in **Data Structures Course 2026**. It returns
to the ordered-tree ideas from Modules 2, 5, and 8, then makes them resistant
to a deliberately harmful insertion order.

## Beginner-first rule

Students are not expected to know binary-search-tree vocabulary, stored
heights, balance factors, rotations, AVL insertion, validation, or
the deliberately slow-input security problem before this module. Every
student-facing technical term and symbol is explained in ordinary language
when first needed. Assessment rewards careful traces, safe implementation,
and reproducible evidence, not memorized wording, drawing quality, or speed.

## Module question

> If someone controls insertion order, can an apparently efficient search
> tree be forced into slow, line-by-line behavior?

A **binary search tree**, abbreviated **BST**, stores a smaller key in each
left subtree and a larger key in each right subtree. A **key** is the integer
used for ordering and searching. A **node** is one stored record with links
to as many as two next records. A **subtree** is one node and everything
reachable below it. The policy is strict: duplicate keys are rejected.

An **AVL tree** is a BST that repairs its local shape after insertion. A
**rotation** is a small reassignment of links that preserves sorted key order.
**Edge-height** counts links on the longest downward route. A **balance
factor** compares the left and right subtree heights. **Validation** means
checking that every required representation rule still holds. An
**allocation** is one reserved block of memory; **ownership** means
responsibility for eventually releasing that block.

## Core learning targets

Students will be able to:

1. state the strict ordering rule of a binary search tree;
2. use and test the supplied baseline insertion, search, measurement, and
   cleanup operations;
3. show why ascending or descending insertion can produce edge-height 14
   from only 15 keys;
4. calculate stored edge-height and left-minus-right balance factor;
5. trace the four canonical LL, RR, LR, and RL repair cases;
6. implement left and right rotations without losing a subtree;
7. implement AVL insertion with duplicate rejection and failure preservation;
8. validate ordering, stored heights, balance, size, and allocation state;
9. compare measured search work for ordinary BST and AVL variants; and
10. distinguish degraded operation cost from unsafe memory access and from
    simply using up a finite resource.

## Fixed tree contract

- `BST_AVL_MAX_NODES` is 64.
- Keys are `int`; sizes and comparison counts use `size_t`.
- A null link has edge-height `-1`; a leaf has edge-height `0`.
- Each live AVL node stores its exact current edge-height. The plain BST
  baseline does not use cached heights as an invariant; measurements follow
  the actual links.
- A node's balance factor is:

  ```text
  left-subtree height - right-subtree height
  ```

- Every AVL balance factor must be `-1`, `0`, or `1`.
- Strict ordering means every key in a left subtree is smaller than the
  node's key and every key in a right subtree is larger.
- A duplicate insertion reports that no insertion occurred and preserves the
  complete tree.
- A full tree or allocation failure also preserves the complete tree.
- Each successful insertion increases size exactly once and owns exactly one
  new allocation.
- Destruction releases every owned node and restores the canonical empty
  state.
- Public output values remain unchanged when an operation rejects its input.
- Ordinary search and insertion require a valid input tree and perform only
  shallow or search-route checks. Use the explicit full validators when a
  complete diagnosis is required.
- The full validators are explicit diagnostics. Their work is excluded from
  ordinary insertion and search measurements.

The instructor-provided BST baseline is complete and tested. Students do not
rewrite it. The starter work is limited to AVL rotations and AVL insertion.
Full AVL deletion is outside the core module.

## Canonical rotation traces

The case letters describe where the new key appears relative to the first
unbalanced node:

```text
LL insertion: 30, 20, 10
RR insertion: 10, 20, 30
LR insertion: 30, 10, 20
RL insertion: 10, 30, 20
```

Every case must finish with key 20 above keys 10 and 30:

```text
      20
     /  \
   10    30
```

The final stored heights are 1 at key 20 and 0 at both leaves. LL and RR use
one rotation. LR and RL use two rotations. Every trace must show that the
sorted inorder sequence remains `10, 20, 30`.

## Canonical 15-key experiment

Measure these exact insertion orders:

```text
ascending:  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
descending: 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
mixed:      8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
```

The unbalanced BST results are fixed:

| Order | Edge-height | Present search | Missing search |
|---|---:|---:|---:|
| ascending | 14 | key 15: 15 comparisons | key 16: 15 comparisons |
| descending | 14 | key 1: 15 comparisons | key 0: 15 comparisons |
| mixed | 3 | key 15: 4 comparisons | key 16: 4 comparisons |

All three AVL results are the same perfect 15-node shape: root key 8,
edge-height 3, and four comparisons for the listed present and missing
searches.

## Exactly three implementation TODO clusters

1. Complete the left and right rotation helpers while preserving every
   subtree and repairing heights in bottom-up order.
2. Complete the local rebalance decision, including LL, RR, LR, and RL.
3. Complete recursive AVL insertion with strict duplicate rejection, bounded
   allocation, exact size change, and failure preservation.

Students also complete exactly three original test categories in
`code/tests/test_student.c`.

## Isolated rotation autopsy

An **autopsy** is a careful investigation after a failure. The isolated
program contains an actual faulty left rotation that can lose an owned
subtree.

- Ordinary autopsy commands define `AUTOPSY_INSPECT_ONLY`, explain the
  defect, run a corrected bounded example, and exit safely.
- The explicit unsafe target requires sanitizers, compiles the actual faulty
  branch, prints its path, and never runs it automatically.
- Neither autopsy mode is linked into ordinary tests.

## Package map

```text
module_15_bst_avl/
|-- README.md
|-- diagrams/
|   `-- bst_avl_models.md
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
|   |-- tree_rotation_autopsy.md
|   `-- vocabulary.md
|-- release/
|   |-- prepare_student_release.ps1
|   |-- release_manifest.md
|   |-- stage_a_README.md ... stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
|-- dist/
|   `-- module_15_stage_a_*.zip ... module_15_stage_e_*.zip
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/
    |   |-- tree_model.h
    |   |-- bst_baseline.h
    |   `-- avl_tree.h
    |-- starter/
    |   |-- avl_rotations.c
    |   `-- avl_tree.c
    |-- solution/
    |   |-- avl_rotations.c
    |   `-- avl_tree.c
    |-- support/
    |   `-- tree_support.c
    |-- tests/
    |   |-- test_core.c
    |   |-- test_extension.c
    |   `-- test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_left_rotation.c
```

The source package contains exactly 43 files before the five generated
archives: 26 Markdown files, 3 PowerShell files, 2 Makefiles, 9 C files, and
3 headers.

## Recommended release order

1. Run `release/prepare_student_release.ps1` only after all materials and
   tests pass.
2. Release Stage A before Meeting A. It withholds formal names,
   representations, formulas, code, and completed reasoning.
3. Release Stage B after each student preserves the initial record model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves the Stage C core.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Week 13 submission

Students submit:

- completed `code/starter/avl_rotations.c`;
- completed `code/starter/avl_tree.c`;
- completed `code/tests/test_student.c`;
- reproducible core and student-test output;
- exactly three original tests in the required categories;
- four canonical before/after rotation traces;
- the exact BST-versus-AVL 15-key measurement table;
- ordering, height, balance, size, and ownership validation evidence;
- sanitizer-clean insertion and destruction evidence where supported;
- a completed evidence record and Tree-Rotation Autopsy; and
- a concise explanation of the operation-cost threat and its limits.

These items form one Week 13 artifact. Optional extension tests and unsafe
autopsy execution are not additional submissions.

## Cost and security boundary

Let `n` be the number of live nodes and `h` the tree's edge-height.

- BST and AVL search follow one route and take `O(h)` time.
- A plain BST may have `h = n - 1`, making search and insertion `O(n)`.
- An AVL tree maintains `h = O(log n)`, so search and insertion are
  `O(log n)`.
- One rotation is `O(1)`.
- Actual-height measurement, inorder traversal, and destruction are `O(n)`.
- The bounded full validators use a simple seen-pointer scan at each visit
  and are `O(n^2)` for this teaching implementation.
- Both representations use `O(n)` owned storage.

An adversarial insertion order can cause **algorithmic-complexity denial of
service**: chosen input makes an operation much slower than intended. This is
degraded operation cost. **Memory corruption** means an invalid access to or
change in storage. **Resource exhaustion** means using up a finite resource,
such as memory or processing time. Slow operation cost is not by itself
either condition, a proof of unauthorized access, or every possible form of
resource exhaustion. Bounds checking, allocation-failure handling,
validation, and cleanup remain necessary even when AVL height is correct.

## Relationship to the course spiral

- **Revisits:** Module 2 strict BST ordering, Module 5 inorder DFS, Module 8
  level-order traversal, Module 11 Heap-order contrast, and Module 13
  hash-table exact lookup. Edge-height, stored height, and balance factor are
  introduced formally in this module rather than Module 8.
- **Contrasts:** a Heap has only parent-child priority order; a BST has a
  global left-smaller/right-larger rule. A plain BST does not control shape;
  an AVL tree does. A hash table supports exact-key lookup without sorted
  traversal; an AVL tree preserves order for ordered iteration and range
  questions.
- **Introduces:** stored-height repair, four-case rotation selection, tested
  AVL insertion, and adversarial-order cost analysis.
- **Forwards:** Module 16 compares these local tree repairs with global
  minimum-spanning-tree decisions.
