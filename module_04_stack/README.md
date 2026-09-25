# Module 4 Teaching Package

## Character Stack, Infix-to-Postfix Conversion, and Evaluation

This package is the Linear stage of the second Linear → Tree → Graph
spiral in **Data Structures Course 2026**. Its current implementation is
[student/lab.c](student/lab.c); the textbook in
[English](student/textbook.md) or [Korean](student/textbook_korean.md),
[lab guide](student/lab.md), and assessments follow that file.

## Beginner-first rule

Students begin by predicting the order of unfinished function calls before
being given Stack vocabulary. The conceptual IDs 100, 200, and 300 are
later represented by character labels `'A'`, `'B'`, and `'C'`. Keep the
initial reasoning, then revise it with a concrete array trace. Neither
these labels nor the character array is a real runtime call frame.

## Module question

> If the most recently started unfinished task must finish first, what
> access rule should the program enforce?

## Authoritative model

```c
char stack[10];
int capacity = 10;
int size = 0;
```

The global character Stack grows toward larger indexes. Its invariant is
`0 <= size <= capacity`; active items occupy indexes 0 through `size - 1`. Empty means
`size == 0`, full means `size == 10`, and the active count is `size`.
Push writes `stack[size]` and then increases `size`. Peek reads `stack[size - 1]`
when nonempty; pop decreases `size` and then reads `stack[size]`, without
erasing the array cell.
A full push does nothing. Empty peek/pop return `'\0'`. There is no
separate status output. `capacity` is initialized to 10 and controls the full
check; the array itself still has a fixed ten-cell allocation.

Expression processing has two phases:

```text
infix_to_postfix():  1-2*3+4 → 123*-4+
eval_postfix():      123*-4+ → -1
```

Conversion uses the global character Stack for operators. `postfix_size` counts
postfix characters, excluding the terminating null. It is reset before
each conversion. Evaluation uses its own `int values[10]`, with `size`
counting active integers. The first value popped is the right operand.

The input assumption is one digit followed by zero or more operator/digit
pairs. Operators are `+`, `-`, `*`, `/`, `%`; multiplication, division,
and remainder have higher precedence. Equal precedence is left associative.
Both strings have eight positions, so an input must fit in seven characters
plus `'\0'`. There are no spaces, parentheses, unary operators, or multi-digit
operands. Divisors must be nonzero and intermediate results representable as
`int`. Conversion starts with an empty operator Stack.

The expression functions do **not** enforce all these assumptions. Invalid
characters can cause an unbounded pop loop, malformed operands can underflow
the value Stack, and zero divisors/overflow are unchecked. These limitations
are discussion and extension work; safe rejection is not a core guarantee.

## Core learning targets

Students will be able to:

1. explain LIFO and distinguish push, peek, and pop;
2. trace `'A'`, `'B'`, `'C'` through indexes 0, 1, and 2;
3. distinguish the top index, active item count, and inactive slots;
4. state the actual full/empty behavior of the character functions;
5. convert infix to postfix using precedence and left associativity;
6. evaluate postfix with correct left/right operand order;
7. distinguish character digits from integer intermediate results;
8. explain global `size`, global `postfix_size`, local `value_size`, and the null terminator;
9. justify constant-time Stack operations and linear expression processing;
10. identify assumptions that would need checks in a more general evaluator.

## Teaching and build materials

| Location | Role |
|---|---|
| `student/lab.c` | Current instructional implementation, without `main` |
| `student/*.md` | Inquiry, reveal, pause, worksheets, textbook, lab, rubric, evidence |
| `diagrams/stack_models.md` | Visual models with text equivalents |
| `instructor/` | Lesson plan, answer key, and technical notes |
| `code/lab_demo.c` | Entry point for the supplied expression |
| `code/tests/test_lab.c` | Six core test groups; students add three justified cases |
| `code/autopsy/` | Isolated, intentional `stack[size]` top-read defect |
| `release/` | Five-stage manifest and student build/package templates |

From `code`, run `make lab-demo`, `make lab-tests`, or `make autopsy`.
See [code/README.md](code/README.md) for PowerShell and manual commands.

## Release order

1. Stage A: preserve initial return-order reasoning before naming LIFO.
2. Stage B: reveal the character representation, preserve the three-target
   Cognitive Pause, then open the vocabulary.
3. Stage C: complete the investigation after instructor calibration.
4. Stage D: read the textbook and diagrams after preserving the required
   investigation sections. No autopsy answer is released here.
5. Stage E: run the lab demo, tests, and isolated autopsy; submit evidence.

[The release manifest](release/release_manifest.md) defines the exact
student files. Packaging verifies source existence and unique paths and
refuses to overwrite archives. Instructor answers and optional reference
solutions are excluded.

## Core submission

Submit `student/lab.c`, `code/tests/test_lab.c` with three additional
justified cases, predictions and observed test/build output, the completed
evidence and autopsy records, and the preserved/revised Cognitive Pause.
Existing `()` declarations can produce prototype warnings; use `(void)`
when revising parameterless definitions. `-Wshadow` also reports local `value_size`
hiding global `size`; explain their separate scopes and record diagnostics
honestly.

## Optional earlier checked implementation

`code/include/`, `code/starter/`, `code/solution/`, and the older
`test_core.c`, `test_extension.c`, and `test_student.c` retain the earlier
caller-owned integer Stack and checked `+`/`*` evaluator. They use the same active-prefix idea with `size` as the count,
but their status/output contracts differ from `lab.c`. They are
an optional comparison and are not the current submission or Stage E lab.

## Spiral links

The module revisits fixed arrays, indexes, character arithmetic, and saved
work. It introduces LIFO, a forward-growing active prefix, postfix,
precedence, and operand order. Later tree and graph modules reuse LIFO
behavior with their own item types and storage policies.
