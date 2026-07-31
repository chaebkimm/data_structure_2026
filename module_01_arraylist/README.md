# Module 1 Teaching Package

## ArrayList and Linked-Node Preview

This package is the production template for the remaining modules in **Data Structures Course 2026**. It implements the first Linear → Tree → Graph spiral’s linear stage.

### Module question

> How can a fixed block of C memory behave like a collection that grows, and what trade-offs change when elements are stored in separately allocated nodes?

### Core learning targets

Students will be able to:

1. Draw the relationship among an `IntList`, its allocation, `size`, and `capacity`.
2. State and check the representation invariant.
3. Verify initialization/cleanup, complete and explain the safe growth
   scaffold, and implement checked access and append.
4. Explain `O(1)` indexing, `O(n)` shifting, and amortized `O(1)` append.
5. Diagnose bounds, allocation, overflow, ownership, and stale-pointer defects.
6. Compare contiguous storage with a brief linked-node preview.

Insertion and removal are scaffolded extensions. They are not required for the core three-hour module.

## Package map

```text
module_01_arraylist/
├── README.md
├── diagrams/
│   └── memory_models.md
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
│   ├── notes.md
│   ├── representation_reveal.md
│   ├── rubric.md
│   ├── segfault_autopsy.md
│   └── vocabulary.md
├── release/
│   ├── release_manifest.md
│   ├── prepare_student_release.ps1
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
├── dist/
│   └── module_01_stage_a_*.zip … module_01_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/int_list.h
    ├── starter/int_list.c
    ├── solution/int_list.c
    ├── tests/test_allocation_failure.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_append.c
```

## Recommended use

1. Run `release/prepare_student_release.ps1` once and use the five archives
   described in `release/release_manifest.md`.
2. Before Meeting A, release Stage A only. Offer the standard or linear
   accessible initial prompt and optional vocabulary support.
3. Let students propose the representation, then release Stage B for the
   representation reveal and timed Cognitive Pause.
4. After expert growth calibration, release Stage C for the invariant,
   operations, complexity, and forward-transfer investigation.
5. Release Stage D notes and diagrams only after Meeting A reasoning is
   complete.
6. Before Meeting B, release Stage E with the starter, supplied tests,
   student-test template, and solution-independent autopsy.
7. Assess the submission with `student/rubric.md`.
8. Keep `code/solution`, `code/tests/test_allocation_failure.c`, and all
   `instructor/` materials instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/int_list.c`;
- passing core-test transcript;
- three passing student-authored tests with rationale;
- compiler-warning and sanitizer/debugger evidence;
- `student/evidence_template.md`, completed in an accessible format;
- Segfault Autopsy response;
- corrected Cognitive Pause.

The extension submission adds `int_list_insert` and `int_list_remove` plus the extension tests.

## Relationship to the course spiral

- **Revisits:** C arrays, indexing, loops, functions, address-of, and dereference.
- **Introduces:** ADT versus representation, ownership, dynamic growth, failure atomicity, amortized reasoning, and invariants.
- **Previews:** linked nodes, pointer stability, tree nodes, adjacency lists, and array-backed Stack.
