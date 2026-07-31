# Module 11 Teaching Package

## Stable Minimum Priority Queue with a Binary Heap

This package is the Tree stage of the fourth
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know binary Heap vocabulary, complete-tree
shape, array index formulas, Heap order, sifting, or Heap operation costs
before this module. Every student-facing technical term and symbol is
explained in ordinary language when first needed. Assessment rewards correct
reasoning and reproducible evidence, not memorized wording, arithmetic speed,
or drawing quality.

## Module question

> Can a compact array avoid scanning every alert while still returning the
> highest-priority item quickly?

## Core learning targets

Students will be able to:

1. map a complete binary tree onto an array;
2. derive parent, left-child, and right-child index formulas;
3. distinguish Heap order, BST order, and globally sorted order;
4. preserve the Module 10 stable minimum Priority Queue service rule;
5. trace insertion followed by sift-up;
6. trace root extraction followed by sift-down;
7. handle a node that has a left child but no right child;
8. implement and use an `is_min_heap` invariant checker;
9. separate checker/debug comparisons from normal-operation comparisons;
10. preserve growth, ownership, failure, and output contracts;
11. verify constant-time minimum inspection and logarithmic-height insertion
    and extraction; and
12. test the Heap against a simple reference implementation.

A **binary Heap** is a complete binary tree stored compactly in an array.
**Complete** means every level is full except possibly the last, and the last
level fills from left to right. This package uses a **minimum Heap**: no child
record may come before its parent under the stable Module 10 comparator.
Therefore the minimum record is at array index 0, but the complete array is
not globally sorted.

The Module 10 public Priority Queue contract remains in force. The only
public API extension is `alert_priority_queue_is_min_heap`, which reports
whether Heap order holds. For any Queue with a valid visible shape, the
checker examines every non-root live record and adds exactly `size - 1`
record-comparator calls to `comparison_count` when records are present, and
zero calls when `size` is 0. It finishes even when it finds a violation.
Students measure checker/debug deltas separately from normal-operation deltas.

## Package map

```text
module_11_binary_heap/
├── README.md
├── diagrams/
│   └── binary_heap_models.md
├── instructor/
│   ├── answer_key.md
│   ├── lesson_plan.md
│   └── technical_notes.md
├── student/
│   ├── binary_heap_autopsy.md
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
│   └── vocabulary.md
├── release/
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_11_stage_a_*.zip … module_11_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/alert_priority_queue.h
    ├── starter/alert_priority_queue.c
    ├── solution/alert_priority_queue.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_sift_down.c
```

The source package contains 38 files before the five generated archives are
created.

## Recommended release order

1. Run `release/prepare_student_release.ps1` only after all materials and
   tests pass.
2. Release Stage A before Meeting A. It withholds formal structure names,
   storage details, index formulas, operation names, complexity, code, and
   exact answers.
3. Release Stage B after each student preserves the initial compact-order
   model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   instructor comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/alert_priority_queue.c`;
- completed `code/tests/test_student.c`;
- saved output from supplied and student-authored tests;
- exactly three original tests in the required categories;
- complete-tree/index and sift traces;
- checker results after required mutations;
- separately measured normal-operation and checker comparison deltas;
- randomized differential-test evidence;
- completed evidence record and Binary Heap Autopsy; and
- corrected Cognitive Pause.

## Fixed course conventions

- The public record, Queue fields, statuses, service operations, error
  precedence, and failure promises from Module 10 are preserved.
- `alert_priority_queue_is_min_heap` is the only public API addition.
- A smaller `size_t` priority value is selected before a larger value.
- Equal priorities are selected by earlier `size_t` arrival sequence.
- Alert IDs and physical array positions never settle ties.
- The root is index 0. For a valid non-root index `i`, its parent is
  `(i - 1) / 2`. Its possible children are `2 * i + 1` and `2 * i + 2`.
- Capacity grows only through 0, 4, 8, 16, 32, and 64 records.
- Insertion appends at the next complete-tree position and sifts the complete
  record upward.
- Minimum inspection reads the root without scanning.
- Minimum extraction saves the root, moves the final live record to index 0,
  reduces the size, and sifts that record downward when records remain.
- A missing right child is never read or compared.
- Every failed operation preserves the complete Queue; output arguments
  change only on success.
- On a valid visible shape, the Heap checker performs zero comparator calls
  when `size` is 0; otherwise it performs exactly `size - 1` and scans all
  parent relationships.
- Checker calls contribute to the shared saturating comparison counter.
  Students reset or take before/after snapshots so checker cost is not
  silently included in normal-operation measurements.
- Bottom-up heap construction, decrease-key, arbitrary deletion, and
  Dijkstra/Prim integration are deferred.

## Relationship to the course spiral

- **Revisits:** ArrayList growth, complete trees, height, invariants,
  ownership, checked failure, and the Module 10 Priority Queue contract.
- **Contrasts:** An unsorted-array backend scans for every minimum; a binary
  Heap keeps only parent-to-child order and does not globally sort records.
- **Introduces:** array/tree index translation, sift-up, sift-down, a
  Heap-order checker, and instrumented-versus-uninstrumented evidence.
- **Forwards:** Dijkstra and Prim use a minimum Heap; Module 14 contrasts Heap
  partial order with AVL search order.
