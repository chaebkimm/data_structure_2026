# Module 4 Teaching Package

## Integer Stack, Infix-to-Postfix Conversion, and Evaluation

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
these labels nor the integer array is a real runtime call frame.

## Module question

> If the most recently started unfinished task must finish first, what
> access rule should the program enforce?

## Authoritative model

```c
int stack[10];
int capacity = 10;
int size = 0;
```

The global integer Stack grows toward larger indexes. With `capacity == 10`,
callers maintain `0 <= size <= capacity`; active items occupy 0 through
`size - 1`. The count and next insertion index are `size`, and the nonempty
top is `stack[size - 1]`. Push writes `stack[size++]`; pop reads
`stack[--size]`. Neither erases or shifts earlier cells.

`is_full()` and `is_empty()` report boundaries but do not guard push, peek,
or pop. A full push or an empty read has undefined behavior. `capacity`
controls the full predicate only, and changing it does not resize the array.

Expression processing has two phases:

```text
infix_to_postfix():  1-2*3+4 → 123*-4+
eval_postfix():      123*-4+ → -1
```

The PPT first calculates directly with conceptual operator and value Stacks:
an incoming `+` causes `2*3` to become 6, then `1-6` to become -5. Writing
operators at their calculation times produces `123*-4+`. The C lab separates
this ordering work from arithmetic and reuses the same global integer array.

Conversion initializes local `pos = 0`, resets `size = 0`, and pushes a
`'\0'` sentinel. It scans exactly seven `eq` characters and writes postfix
tokens to `eq_re`. The final drain writes the sentinel to `eq_re[7]`: `pos`
ends at 8, visible token length is 7, and `size` is 0. Evaluation resets
`size` again, scans exactly seven tokens, and reuses `stack` for integer
operands/results. It pops the right operand first; the final pop returns
-1 and leaves `size == 0`.

Supported input is exactly seven characters: four single digits alternating
with three binary operators from `+ - * / %`, then a terminator in `eq[7]`.
Multiplication, division, and remainder have higher precedence; equal
precedence is left associative. Exclude spaces, parentheses, unary operators,
and multi-digit operands. Divisors must be nonzero and intermediates must fit
C `int`. Shorter strings are unsupported because both loops run seven times.

The functions assume this grammar and arithmetic domain. Invalid characters,
early terminators, and missing operands can lead to out-of-bounds accesses;
zero divisors and overflow are unchecked. Safe rejection is an extension,
not a guarantee of the current source.

## Core learning targets

Students will be able to:

1. explain LIFO and distinguish push, peek, and pop;
2. trace `'A'`, `'B'`, `'C'` through indexes 0, 1, and 2;
3. distinguish the top index, active item count, and inactive slots;
4. state the actual full/empty preconditions of the integer Stack functions;
5. convert infix to postfix using precedence and left associativity;
6. evaluate postfix with correct left/right operand order;
7. distinguish character digits from integer intermediate results;
8. explain shared `size`, local `pos`, the stored sentinel, and the null terminator;
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
Existing `()` declarations can produce prototype warnings; integer-to-character
assignments can produce narrowing warnings. Use `(void)` when revising
parameterless definitions, and record diagnostics honestly.

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
