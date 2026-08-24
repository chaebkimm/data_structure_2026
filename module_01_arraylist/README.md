# Module 1 Teaching Package

## Keeping Data Together in One Place

This package is the production template for the remaining modules in **Data Structures Course 2026**. It implements the first Linear → Tree → Graph spiral’s linear stage.

### Module question

> How can we keep ordered data together, preserve its order when items are added or deleted, and continue when the original memory space becomes full?

### Core learning targets

Students will be able to:

1. Explain why an ordered collection keeps its active items together.
2. Find an item directly by index and search for an item by value.
3. Trace the shifts required for insertion and deletion.
4. Explain why a full array must move to a larger memory space.
5. Compare the work required by indexing, searching, shifting, and expansion.
6. Use `sizeof`, pointers, `malloc`, `NULL`, and `free` in a small dynamic-array example.

The textbook defines the conceptual core. The lab maps the same ideas to the
repository's `IntList` API and adds implementation-level checks. Those checks
support safe C programming, but they are not prerequisites for understanding
the textbook.

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
│   ├── textbook.md
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
3. Let students predict insertion, deletion, and full-array behavior, then
   release Stage B for the memory-model reveal and timed Cognitive Pause.
4. After the growth trace, release Stage C for the invariant, operations, and
   efficiency investigation.
5. Release the Stage D textbook, notes, and diagrams only after Meeting A
   reasoning is complete.
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
- **Introduces:** contiguous storage, ArrayLists, dynamic arrays, indexes,
  elements, shifting, dynamic growth, and invariants.
- **Lab extension:** an `IntList` implementation with checked access,
  allocation errors, arithmetic limits, and cleanup contracts.
- **Previews:** array-backed Stack.
