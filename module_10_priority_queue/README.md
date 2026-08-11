# Module 10 Teaching Package

## Stable Minimum Priority Queue

This package is the Linear stage of the fourth
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## 14-week delivery role

This package supplies the contract and reference baseline for the combined
**Week 9 Priority Queue → Binary Heap** unit. The instructor supplies the
completed unsorted-array implementation; students trace it and compare its
costs, but do not implement it as a separate project and do not submit a
Module 10 assignment. The full package remains available as an instructor
resource.

See the
[14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
for the 40-minute baseline block and handoff to Module 11. Where the targets,
release order, or submission list below are broader, the guide and this
delivery-role note control the required path.

## Beginner-first rule

Students are not expected to know Priority Queue vocabulary, comparison
rules, stable tie behavior, dynamic-array growth, or operation costs before
this module. Every student-facing technical term and symbol is explained in
ordinary language when first needed. Assessment rewards correct reasoning
and reproducible evidence, not memorized wording, arithmetic speed, or
drawing quality.

## Module question

> If urgent alerts should be processed before routine alerts, what replaces
> arrival order, and what does that choice cost?

## Core learning targets

Students will be able to:

1. contrast first-in, first-out Queue order with priority-controlled order;
2. specify a stable minimum Priority Queue independently of its storage;
3. apply one deterministic comparison rule to alert records;
4. explain why a smaller number means greater urgency in this package;
5. preserve arrival order when two alerts have equal priorities;
6. trace insertion, minimum inspection, and minimum removal in an unsorted
   array;
7. implement geometric array growth with a hard capacity limit of 64;
8. validate representation rules and preserve state and outputs on failure;
9. count comparisons for insert-heavy and removal-heavy workloads;
10. compare unsorted-array and sorted-array costs; and
11. explain fairness, starvation, and poorly calibrated severity risks.

A **Priority Queue** chooses the waiting record with the highest defined
priority instead of always choosing the oldest record. This package uses a
**minimum Priority Queue**, so the smaller `size_t` priority value is chosen
first. If priorities tie, the earlier `size_t` arrival sequence is chosen.
`size_t` is a C whole-number type used for sizes and array positions; it
cannot represent a negative number. Choosing earlier equal-priority records
first makes the behavior **stable**.

The student implementation stores records in an unsorted, geometrically
growing array. **Geometric growth** increases capacity by a multiplying
factor rather than one slot at a time. The implementation never owns more
than 64 records.

## Package map

```text
module_10_priority_queue/
├── README.md
├── diagrams/
│   └── priority_queue_models.md
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
│   ├── priority_queue_autopsy.md
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
│   └── module_10_stage_a_*.zip … module_10_stage_e_*.zip
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
        └── faulty_tie.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1` after all materials and tests
   pass.
2. Release Stage A before Meeting A. It withholds formal names, operation
   names, storage choices, formulas, code, and exact answers.
3. Release Stage B after each student preserves the initial urgency-order
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
- comparison counts for insert-heavy and removal-heavy workloads;
- an unsorted-versus-sorted backend-selection memo;
- completed evidence record and Priority Queue Autopsy;
- corrected Cognitive Pause; and
- a short fairness and starvation explanation.

## Fixed course conventions

- A smaller `size_t` priority value is selected before a larger value.
- Equal priorities are selected by earlier `size_t` arrival sequence.
- The queue assigns arrival sequences in insertion order and does not change
  them while records wait.
- The backend is one owned, unsorted, geometrically growing dynamic array.
- Capacity never exceeds 64 records.
- Insertion appends without scanning for the minimum.
- Minimum inspection scans with the complete comparison rule.
- Minimum removal replaces the removed slot with the last live record, then
  reduces the size; the physical array order may therefore change.
- Every failed operation preserves the complete queue; output arguments
  change only on success.
- The sorted-array design is analyzed on paper, not implemented.
- Heap and mutable-priority operations are reserved for later modules.

## Relationship to the course spiral

- **Revisits:** Queue semantics, ArrayList growth, allocation, ownership,
  invariants, checked failures, and abstraction boundaries.
- **Contrasts:** FIFO chooses the oldest waiting record; this Priority Queue
  chooses by priority and then arrival sequence.
- **Introduces:** a stable comparator, unsorted-array backend costs,
  comparison counting, starvation, and backend selection.
- **Forwards:** the same public behavior with a binary Heap backend, then
  Dijkstra and Prim as Priority Queue clients.
