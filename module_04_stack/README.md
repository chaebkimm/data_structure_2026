# Module 4 Teaching Package

## Stack ADT and Nested Delimiters

This package is the Linear/supporting stage of the second
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know Stack vocabulary, abstract data types, or
nested-delimiter algorithms before this module. Every student-facing
technical term is explained in ordinary language when it is first needed.
Assessment rewards accurate reasoning, not memorized wording.

## Module question

> If the most recently opened task must be completed first, what access rule
> should the structure enforce?

## Core learning targets

Students will be able to:

1. explain the Stack abstract data type independently of its storage;
2. use LIFO, top, push, pop, peek, and underflow accurately;
3. trace mixed Stack operations from bottom to top;
4. state the invariant for an ArrayList-backed character Stack;
5. implement checked geometric growth, push, pop, peek, and cleanup;
6. validate `()`, `[]`, and `{}` nesting with an explicit depth limit;
7. preserve prior state and caller outputs after failed operations;
8. analyze operation and full-expression costs;
9. distinguish the Stack ADT from the runtime call stack and a
   stack-allocated buffer; and
10. explain why a Stack can later control depth-first exploration without
    implementing DFS yet.

An **abstract data type (ADT)** is a behavior contract that does not require
one particular storage method. **LIFO** means “last in, first out.” **DFS**,
or depth-first search, is a later method for exploring one route deeply
before returning to another choice.

## Package map

```text
module_04_stack/
├── README.md
├── diagrams/
│   └── stack_models.md
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
│   ├── stack_autopsy.md
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
│   └── module_04_stage_a_*.zip … module_04_stage_e_*.zip
└── code/
    ├── README.md
    ├── build.ps1
    ├── Makefile
    ├── include/char_stack.h
    ├── include/delimiter_validator.h
    ├── starter/char_stack.c
    ├── starter/delimiter_validator.c
    ├── solution/char_stack.c
    ├── solution/delimiter_validator.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/
        ├── README.md
        └── faulty_delimiters.c
```

## Recommended release order

1. Run `release/prepare_student_release.ps1`.
2. Release Stage A before Meeting A; it does not reveal formal Stack/LIFO
   names, the representation, or code.
3. Release Stage B after each student preserves the initial ordering model.
4. Release Stage C after the timed Cognitive Pause and instructor
   explanation.
5. Release Stage D only after the student preserves the Stage C core.
6. Release Stage E for Meeting B.
7. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` instructor-only until revisions close.

## Core submission

Students submit:

- completed `code/starter/char_stack.c`;
- completed `code/starter/delimiter_validator.c`;
- saved text printed by the supplied tests;
- three original tests with a short explanation of each test's purpose;
- warning-enabled compiler or instructor-CI evidence;
- completed evidence record;
- Stack Autopsy;
- corrected Cognitive Pause; and
- short Stack-to-depth-first-exploration explanation.

**CI**, or continuous integration, means another computer automatically
builds and tests submitted code.

## Relationship to the course spiral

- **Revisits:** ArrayList size/capacity invariants, geometric growth,
  ownership, checked errors, and failure atomicity.
- **Introduces:** Stack ADT, LIFO access, underflow, encapsulation, and
  nesting validation.
- **Forwards:** a typed Stack for tree DFS in Module 5 and visited-aware
  graph DFS in Module 6.
