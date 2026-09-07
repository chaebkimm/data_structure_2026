# Module 4 Teaching Package

## Fixed-Capacity Stack and Expression Precedence

This package is the Linear/supporting stage of the second
Linear → Tree → Graph spiral in **Data Structures Course 2026**.

## Beginner-first rule

Students are not expected to know Stack vocabulary, abstract data types, or
operator precedence before this module. Student materials begin with three
unfinished function IDs, preserve initial reasoning, name the LIFO rule, and
then reveal a caller-owned fixed-array representation. Assessment rewards
accurate reasoning rather than memorized wording.

## Module question

> If the most recently started unfinished task must finish first, what access
> rule should the program enforce?

## Authoritative model

The module represents a Stack with a caller-owned integer array plus separate
`size` and `capacity` values. Valid metadata satisfies:

```text
0 <= size <= capacity
```

Logical items occupy indexes `0` through `size - 1`. When `size > 0`, the top
is `stack[size - 1]`; when `size < capacity`, `stack[size]` is the next
inactive position. The Stack functions borrow the caller's fixed storage;
they do not change its extent or erase it.

The canonical trace pushes function IDs 100, 200, and 300. The transfer task
uses two internal ten-position Stacks to evaluate `1+2*3`. The evaluator
accepts only alternating single digits and `+` or `*`, applies normal
precedence and left associativity, checks every internal push and every `int`
calculation, and preserves its output after rejection.

The public surface is:

```c
int int_stack_push(int stack[], int size, int capacity, int value);
int int_stack_peek(
    const int stack[], int size, int capacity, int *out_value
);
int int_stack_pop(
    const int stack[], int size, int capacity, int *out_value
);
int expression_evaluate(const char expression[], int *out_result);
```

## Core learning targets

Students will be able to:

1. explain the Stack ADT and last-in, first-out access rule;
2. trace `push`, `peek`, and `pop` from bottom to top;
3. locate the top at `stack[size - 1]` only when the Stack is nonempty;
4. state and apply `0 <= size <= capacity`;
5. implement checked fixed-array operations for generic integers;
6. preserve array state and caller outputs after rejected operations;
7. distinguish logical removal from erasing an inactive array cell;
8. evaluate the stated single-digit `+`/`*` grammar with two fixed Stacks;
9. explain precedence, left associativity, capacity rejection, and checked
   integer overflow; and
10. distinguish a Stack ADT, a local Stack-representation array, and the
    runtime call stack.

## Package map

```text
module_04_stack/
├── README.md
├── diagrams/stack_models.md
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
│   ├── prepare_student_release.ps1
│   ├── release_manifest.md
│   ├── stage_a_README.md … stage_e_README.md
│   ├── student_build.ps1
│   ├── student_code_README.md
│   └── student_Makefile
└── code/
    ├── include/int_stack.h
    ├── include/expression_evaluator.h
    ├── starter/int_stack.c
    ├── starter/expression_evaluator.c
    ├── solution/int_stack.c
    ├── solution/expression_evaluator.c
    ├── tests/test_core.c
    ├── tests/test_extension.c
    ├── tests/test_student.c
    └── autopsy/faulty_top.c
```

## Recommended release order

1. Release Stage A before Meeting A. It contains no formal Stack vocabulary,
   representation, code, or answer.
2. Release Stage B after each student preserves the initial function-return
   model. Open the vocabulary only after the three-target pause is preserved.
3. Release Stage C after the pause and brief instructor calibration.
4. Release Stage D after the student preserves the Stage C core. It contains
   the textbook and equivalent Stack models, but no autopsy answer.
5. Release Stage E for Meeting B. Keep `instructor/`, `code/solution/`, and
   `code/tests/test_extension.c` private through the assessed revision.

`release/prepare_student_release.ps1` creates five archives only after it
confirms that every source exists and that every destination path is unique
within its stage. It refuses to overwrite an existing archive.

## Core submission

Students submit:

- completed `code/starter/int_stack.c`;
- completed `code/starter/expression_evaluator.c`;
- three justified tests in `code/tests/test_student.c`;
- passing public-test and warning-enabled build evidence;
- the completed evidence record and Stack-Top Autopsy; and
- the preserved and corrected Cognitive Pause.

## Relationship to the course spiral

- **Revisits:** caller-owned fixed arrays, separate logical size and physical
  capacity, bounds checks, invariants, and failure preservation.
- **Introduces:** Stack ADT, LIFO, top, push, peek, pop, underflow, operator
  precedence, and a checked two-Stack evaluator.
- **Forwards:** the LIFO behavior contract. Later tree and graph modules
  choose their own element types and storage policies.
- **Defers:** storage-growth and ownership policies. Those are not part of
  this module's Stack implementation.
