# Module 7 Teaching Package

## Queue and Circular Buffer

This package is the Linear stage of the third
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know Queue vocabulary, circular indexing, or
overflow policies before this module. Every student-facing technical term is
explained in ordinary language when first needed. Assessment rewards
accurate reasoning, not memorized wording or arithmetic speed.

## Module question

> How can a security-event collector process events in arrival order without
> shifting all remaining events after every removal?

## Core learning targets

Students will be able to:

1. explain first-in, first-out behavior independently of storage;
2. contrast Queue FIFO behavior with Stack LIFO behavior;
3. use enqueue, peek, dequeue, empty, full, head, size, and derived tail;
4. distinguish logical Queue order from physical array positions;
5. trace wrap-around in a fixed-capacity circular array;
6. state and validate the Queue representation invariant;
7. implement constant-time enqueue and dequeue without shifting;
8. preserve Queue state and outputs after checked failures;
9. compare reject-newest, discard-oldest, and backpressure policies; and
10. compare circular-array and linked-Queue representations.

A **Queue** removes the item that has waited longest. **FIFO** means “first
in, first out.” A **circular buffer** reuses earlier array positions after
reaching the physical end. The course implementation reports a full Queue
instead of silently discarding an event.

## Package map

```text
module_07_queue/
├── README.md
├── diagrams/
│   └── queue_models.md
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
│   ├── queue_autopsy.md
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
│   └── module_07_stage_a_*.zip … module_07_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/event_queue.h
    ├── starter/event_queue.c
    ├── solution/event_queue.c
    ├── tests/
    │   ├── test_core.c
    │   ├── test_extension.c
    │   └── test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_wrap.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A. It withholds Queue terminology,
   circular-buffer fields, formulas, code, and exact answers.
3. Release Stage B after each student preserves the initial arrival-order
   model.
4. Release Stage C after the exactly-three-target Cognitive Pause and
   comparison.
5. Release Stage D only after the student preserves Sections A through F of
   Stage C.
6. Release Stage E after retrieval and Stage D calibration in Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/event_queue.c`;
- completed `code/tests/test_student.c`;
- saved output from supplied and student-authored tests;
- exactly three original tests in the required categories;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record and Queue Autopsy;
- corrected Cognitive Pause; and
- a short Queue-to-later-exploration transfer explanation.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Relationship to the course spiral

- **Revisits:** indexed arrays, capacity, allocation, ownership, invariants,
  checked errors, and failure preservation.
- **Contrasts:** Queue FIFO removes the oldest waiting item; Stack LIFO
  removes the newest.
- **Introduces:** circular indexing, derived tail, wrap-around, and explicit
  overflow policy.
- **Forwards:** Queue-controlled tree and graph breadth-first exploration in
  Modules 8 and 9.
