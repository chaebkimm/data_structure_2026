# Technical Notes — Module 4 Integer Stack and Postfix Evaluation

## Source and teaching boundary

The current teaching source is `student/lab.c`. One global `int stack[10]`
holds operator character codes during conversion, then numeric values during
evaluation. Each phase resets global `size` and reuses that same storage.
The older caller-owned `int_stack_*` and checked `expression_evaluate` library
under `code/include`, `code/starter`, and `code/solution` is an optional legacy
comparison with different contracts and tests.

```c
int stack[10];
int capacity = 10;
int size = 0;
char eq[8] = "1-2*3+4";
char eq_re[8] = "";
```

## The forward representation and exact operations

With `capacity == 10`, valid caller-maintained state satisfies
`0 <= size <= capacity`. The active prefix is indexes 0 through `size - 1`;
the nonempty top is `stack[size - 1]`. `size` is both the active count and
next insertion index. Logical bottom-to-top order follows increasing indexes.
Popping leaves old bits in an inactive cell.

| Operation | Source behavior | Caller precondition |
|---|---|---|
| `is_full()` | returns `size == capacity` | state is valid |
| `push(int data)` | `stack[size++] = data` | room remains in the array |
| `is_empty()` | returns `size == 0` | state is valid |
| `peek()` | returns integer `stack[size - 1]` | `size > 0` |
| `pop()` | returns integer `stack[--size]` | `size > 0` |

The predicates do not guard the operations. A full push writes outside the
ten-cell array; empty peek/pop read index -1. These calls have undefined
behavior, not a promised no-op or sentinel result. Keep them as paper
diagnoses and exercise predicates/valid transitions in tests. `capacity`
changes the full predicate only; it does not resize storage or stop push.

## One Stack, two expression phases, and a local cursor

The PPT first motivates the algorithm through a direct calculation with
conceptual operator and value Stacks. For incoming `+` in `1-2*3+4`, calculate
`2*3 = 6`, then `1-6 = -5`, before saving `+`. Reading 4 and performing the
last addition gives -1. Recording this calculation order gives `123*-4+`.
The lab separates conversion and evaluation so it can reuse one array.

| State | Meaning |
|---|---|
| `stack[10]`, global `size` | operators plus sentinel in conversion; numeric operands/results in evaluation |
| `eq[8]` | seven infix token characters and a terminator |
| `eq_re[8]`, local conversion cursor `pos` | postfix output; `pos` advances for every write, including the terminator |

## Phase 1: infix to postfix

Conversion initializes local `pos = 0`, resets `size = 0`, and pushes `'\0'`.
It scans exactly seven `eq` positions. Digits go straight to `eq_re`; waiting
operators of greater or equal precedence are popped before an incoming
operator is pushed. Equal precedence uses `>=`, preserving left associativity.

`prec` returns 1 for `+ -`, 2 for `* / %`, and 0 otherwise. The actual stored
sentinel has precedence 0 and remains below every valid operator, keeping
peek inside the active prefix during the operator loop.

| Read/work | Visible postfix | Stack, bottom to top | `size` | `pos` |
|---|---|---|---:|---:|
| reset and push sentinel | empty | `'\0'` | 1 | 0 |
| `1` | `1` | `'\0'` | 1 | 1 |
| `-` | `1` | `'\0'`, `-` | 2 | 1 |
| `2` | `12` | `'\0'`, `-` | 2 | 2 |
| `*` | `12` | `'\0'`, `-`, `*` | 3 | 2 |
| `3` | `123` | `'\0'`, `-`, `*` | 3 | 3 |
| `+`: pop `*`, pop `-`, push `+` | `123*-` | `'\0'`, `+` | 2 | 5 |
| `4` | `123*-4` | `'\0'`, `+` | 2 | 6 |
| drain `+` | `123*-4+` | `'\0'` | 1 | 7 |
| drain sentinel | `123*-4+` terminated | empty | 0 | 8 |

The final drain includes the sentinel: `eq_re[7] = '\0'`. Thus `pos` ends
at 8, token length is 7, and `size` is 0. `pos` is local and cannot be read by
the driver after return. Repeated supported conversions reset `size` and
`pos`; shorter strings are not supported by the fixed loop.

## Phase 2: postfix evaluation

Evaluation resets `size = 0` and processes exactly `eq_re[0..6]`, without a
sentinel. Digits become numbers through `push(c - '0')`. Each operator pops
right operand `num2` first, then left operand `num1`, and pushes
`calc(num1, num2, c)`. All pops decrement `size` before reading `stack[size]`.

| Token | Active `stack`, bottom to top | `size` | Calculation |
|---|---|---:|---|
| `1` | 1 | 1 | digit |
| `2` | 1, 2 | 2 | digit |
| `3` | 1, 2, 3 | 3 | digit |
| `*` | 1, 6 | 2 | `2 * 3 = 6` |
| `-` | -5 | 1 | `1 - 6 = -5` |
| `4` | -5, 4 | 2 | digit |
| `+` | -1 | 1 | `-5 + 4 = -1` |
| final `pop()` | empty | 0 | return -1 |

The terminator at index 7 is excluded. Integer storage preserves negative
or multidigit intermediate values; no separate local value array exists.

## Input assumptions and unchecked cases

Core runs require exactly seven characters: four single digits alternating
with three `+ - * / %` operators, followed by `'\0'` in `eq[7]`. There are no
spaces, parentheses, unary operators, or multi-digit operands. Divisors must
be nonzero and intermediate results representable as C `int`. Integer `/`
truncates toward zero; `%` is the corresponding remainder operation.

These are caller assumptions. An unsupported character, including an early
terminator in a short input, has precedence 0: conversion can pop the sentinel
and then peek an empty Stack. Missing operands can underflow evaluation;
extra operands have no final-count check. Output bounds, zero divisors,
signed overflow, and Stack preconditions are not validated. Discuss proposed
validation as extensions and keep unsupported runs out of normal tests.

## Costs and storage

Valid push, peek, and pop do constant work, `O(1)`, without shifting. Each
input token is scanned once and each waiting operator is pushed/popped at
most once, giving `O(n)` conversion and evaluation for the generalized
algorithm. This source fixes `n = 7` and reserves fixed storage, `O(1)`.
A generalized postfix buffer would need space proportional to input length.

## Stack-Top Autopsy — instructor only

The isolated fixture has ten characters:

```text
index:   0  1  2  3  4  5  6  7  8  9
stack:   +  *  ?  ?  ?  ?  ?  ?  ?  ?
size: 2
```

The active prefix is indexes 0 and 1. Correct `stack[size - 1]` reads `'*'`;
faulty `stack[size]` reads `'?'` at inactive index 2. Both accesses are
inside the array in this fixture. At full capacity, the faulty expression
would read out-of-bounds `stack[10]`. Here the first broken rule is logical membership,
so a clean memory-sanitizer result cannot establish correctness. Preserve the
student's prediction before revealing this comparison. Keep these specific
answers out of the Stage D diagram release.

## Build and evidence

From `code`, run `make lab-demo` and `make lab-tests`, or use
`powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target lab`
and `-Target lab-tests`. The demonstration links the current student source;
the tests exercise that same source. Record actual output rather than reusing
the legacy eight-core/five-extension totals.

Use warning-enabled C11 builds and supported sanitizers. The source's empty
parameter lists can trigger strict-prototype warnings; explain the diagnostic
and the C11 spelling `(void)` without silently changing the canonical source.
Integer-to-character assignments can also trigger narrowing warnings.
A clean valid-input run establishes evidence within the stated assumptions,
not a checked parser contract.
