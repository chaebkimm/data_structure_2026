# Module 1 Teaching Package

## Keeping Data Together in One Place

This package is the first Linear -> Tree -> Graph spiral's linear stage in
**Data Structures Course 2026**.

## Module question

> How can a fixed array keep ordered data together, and how do reads,
> updates, searches, additions, and removals preserve that order?

## Canonical model

```c
int array[10];
int size = 0;
int array_capacity = 10;
```

Capacity is the ten available positions. Size is the number of active items.
The active list occupies indexes `0` through `size - 1` with no gaps. An
unused position may still contain an old value; `size` determines whether
that position belongs to the list.

The capacity stays ten. An append or insertion into a full array is rejected
without changing the size or any active value.

## Core learning targets

Students will be able to:

1. distinguish fixed capacity from the number of stored items;
2. explain contiguous storage and the active-prefix invariant;
3. read and update a checked index directly;
4. find the first matching value with a left-to-right linear search;
5. append at the first unused position when space remains;
6. insert by shifting right from back to front;
7. remove by shifting later items left from front to back; and
8. reject invalid indexes and full-array additions without changing the
   existing list.

Read, update, find, append, insert, and remove are all core operations. The
extension suite adds only extra edge cases and longer operation sequences.

## Reading support

Both `student/textbook.md` and `student/textbook_korean.md` retain the main
chapter and include **Full C Code Explanation** as an optional reference.
Students can look up a symbol or one operation when needed; reading the
whole appendix and completing its practice questions are not requirements.
`student/notes.md` maps common questions to its eleven topics, and the lab
explains the additional syntax used by the supplied function scaffold.

The textbook's complete program starts with five active values. The shorter
three-item inquiry examples practice the same fixed-capacity rules.

## Package map

```text
module_01_arraylist/
|-- README.md
|-- diagrams/memory_models.md
|-- instructor/
|   |-- answer_key.md
|   |-- lesson_plan.md
|   `-- technical_notes.md
|-- student/
|   |-- cognitive_pause.md
|   |-- day2_plan.md
|   |-- evidence_template.md
|   |-- inquiry_prompt.md
|   |-- inquiry_prompt_linear.md
|   |-- investigation_worksheet.md
|   |-- investigation_worksheet_linear.md
|   |-- lab.md
|   |-- notes.md
|   |-- representation_reveal.md
|   |-- rubric.md
|   |-- segfault_autopsy.md
|   |-- textbook.md
|   |-- textbook_korean.md
|   `-- vocabulary.md
|-- release/
|   |-- release_manifest.md
|   |-- prepare_student_release.ps1
|   |-- stage_a_README.md ... stage_e_README.md
|   |-- student_build.ps1
|   |-- student_code_README.md
|   `-- student_Makefile
|-- dist/
|   `-- module_01_stage_a_*.zip ... module_01_stage_e_*.zip
`-- code/
    |-- README.md
    |-- build.ps1
    |-- Makefile
    |-- include/int_list.h
    |-- lecture/simplified_array_list.c
    |-- starter/int_list.c
    |-- solution/int_list.c
    |-- tests/test_core.c
    |-- tests/test_extension.c
    |-- tests/test_student.c
    `-- autopsy/
        |-- README.md
        `-- faulty_append.c
```

## Recommended release order

1. Prepare the five archives described in `release/release_manifest.md` only
   after the reference checks pass.
2. Before Meeting A, release Stage A only. Offer the standard or linear
   accessible inquiry; withhold the model and vocabulary.
3. Preserve the first model, then release Stage B for the fixed-array reveal,
   vocabulary reference, and timed Cognitive Pause.
4. After the pause and expert calibration, release Stage C for invariant,
   operation, and efficiency reasoning.
5. Release Stage D's English/Korean textbooks, notes, and diagram/text models
   after the Meeting A investigation and exit ticket.
6. Release Stage E for Meeting B with the starter, supplied tests,
   student-test template, and isolated autopsy.
7. Assess the submission with the 100-point `student/rubric.md`.
8. Keep `code/solution/` and all `instructor/` materials private until
   revisions close.

## Core submission

Students submit:

- completed `code/starter/int_list.c`;
- passing core-test transcript;
- three passing student-authored tests with rationales;
- warning-enabled compiler and approved memory-check/debugger evidence;
- completed `student/evidence_template.md`;
- autopsy response; and
- corrected Cognitive Pause.

Extensions provide further boundary and sequence tests for the same core
operations; they do not introduce another representation or additional
required operations.

## Relationship to the course spiral

- **Supports:** C variables, arrays, indexing, loops, functions, and conditions,
  including students encountering all of this syntax for the first time.
- **Introduces:** fixed-capacity ArrayLists, size versus capacity, linear
  first-match search, shift direction, checked boundaries, and invariants.
- **Previews:** an array-backed Stack and later comparisons with linked
  structures.
