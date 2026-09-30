# Module 4 Evidence Record

Complete this record after the Stage D notes and Stage E lab. Any table may
be replaced with numbered responses using the same headings.

Name: ____________________________

Compiler and version: ____________________________

Build command(s): ____________________________

## 1. Stack language

Explain Stack, LIFO, top, push, peek, pop, underflow, and a full Stack in your
own words. Distinguish a physical array cell from a logical Stack item.

Response:

____________________________________________________________________

## 2. Canonical character trace

Start empty. Record the return, `top`, item count, and bottom-to-top logical
state. A `void` push has no return value.

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

| Step | Return | `top` | Item count | Logical Stack |
|---:|---|---:|---:|---|
| Start | none | -1 | 0 | empty |
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |
| 6 | | | | |
| 7 | | | | |

Where are `'A'`, `'B'`, and `'C'` physically after all three pushes?

____________________________________________________________________

## 3. Representation invariant

State the valid range of `top`, the active index range, and the expressions
for the nonempty top, the next push position, and current item count.

____________________________________________________________________

What can remain in a popped cell? Why is it no longer a logical item?

____________________________________________________________________

Which full check uses global `capacity`, and why does changing that variable
not resize the ten-cell array?

____________________________________________________________________

Distinguish global `top`, local conversion cursor `pos`, and postfix token
length. How do the two phases reuse the same array and top index?

____________________________________________________________________

## 4. Boundary behavior

For valid operations, record the return, final `top`, and array contents.
For invalid calls, identify the out-of-bounds index on paper; do not execute
them or promise a deterministic return or preserved final state.

1. Observe `is_full()` after ten valid pushes; explain why an eleventh push is invalid.
2. Observe `is_empty()` when `top == -1`; explain why peek is invalid.
3. Explain which invalid index empty pop reads before decrementing `top`.
4. Execute a valid pop followed by peek of the newly exposed item.

____________________________________________________________________

Why does conversion check `!is_empty()` before inspecting or popping?
Which caller checks prevent invalid primitive calls elsewhere?

____________________________________________________________________

## 5. Expression transfer

Trace conversion of `1-2*3+4`. At each token, record the character operator
Stack, `top`, postfix prefix, and local `pos`. Explain how the operator
loop uses `break`. Separate draining the last operator (`pos == 7`) from
writing the terminator (`pos == 8`). Why is `top == -1` at both points?

____________________________________________________________________

Trace evaluation of the completed postfix. At each token, record the integer
`stack` values, global `top`, and any calculation. Explain `c - '0'` and why `num2`
is popped before `num1`.

____________________________________________________________________

Trace `eq_paren = "1+(2+3)"` through `infix_to_postfix_parentheses()`.
Explain which `+` is emitted at `)`, why parentheses are absent from `123++`,
where the output terminator is written, and why evaluation returns 6.

State the permitted operators, eight-cell buffer limit, operand format,
balanced-parentheses rule, phase-entry resets, and arithmetic assumptions.
Explain why shorter valid expressions stop at their terminators.

____________________________________________________________________

Name three unsupported inputs and the missing checks they expose. Describe
them as limitations; do not claim they are safely rejected.

____________________________________________________________________

## 6. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Canonical A, B, C LIFO trace | | | |
| Peek preserves `top` and array | | | |
| Pop exposes previous character without erasing the old cell | | | |
| Full predicate reports true after ten valid pushes; no eleventh push is called | | | |
| Empty predicate reports true after draining; no empty read is called | | | |
| `1-2*3+4` converts to `123*-4+`, length 7 | | | |
| Canonical postfix evaluates to `-1` | | | |
| Equal-precedence operators remain left associative | | | |
| Noncommutative operands have the correct order | | | |
| Repeated conversion, including a shorter result, resets `top` and local `pos`; explicit final write terminates output | | | |
| Evaluation discards prior active items by resetting shared `top` | | | |
| Character digits become numeric values | | | |
| `1+(2+3)` converts to `123++`, terminates at index 5, and evaluates to 6 | | | |
| Shorter valid expressions stop at the null terminator | | | |

### Three student-authored cases

Add exactly three justified new cases to `code/tests/test_lab.c` and retain
the supplied cases. Record each case's new claim and expected state/result.

1. A new LIFO sequence:

   __________________________________________________________________

2. A boundary or inactive-cell case:

   __________________________________________________________________

3. A valid expression or repeated-conversion case:

   __________________________________________________________________

Paste or attach the demo and complete passing lab-test transcripts:

____________________________________________________________________

Record compiler warnings or diagnostic results and what they mean. What do
passing valid-input tests leave unproven?

____________________________________________________________________

## 7. Costs

| Work | Cost | Reason |
|---|---|---|
| Valid integer push | | |
| Valid integer peek | | |
| Valid integer pop | | |
| Convert `n` valid infix characters, including parentheses | | |
| Evaluate `n` valid postfix tokens | | |
| Storage with the present fixed arrays | | |

Explain the current limit of seven input characters and how storage would
change if the arrays grew with input length.

____________________________________________________________________

## 8. Three uses of “stack”

Distinguish the Stack ADT, the runtime call stack, and this lab's global
integer array. Explain how its active values change from operator codes
to numeric operands and results across the two phases.

____________________________________________________________________

## 9. Stack-Top Autopsy

- Prediction preserved before running:
- First incorrect read:
- Logical rule broken:
- Why the read is still inside physical storage in the fixture:
- Observed character and consequence:
- Repair:
- Regression case:

## 10. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
