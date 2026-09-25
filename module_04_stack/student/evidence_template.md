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

Start empty. Record the return, `size`, item count, and bottom-to-top logical
state. A `void` push has no return value.

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

| Step | Return | `size` | Item count | Logical Stack |
|---:|---|---:|---:|---|
| Start | none | 0 | 0 | empty |
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

State the valid range of `size`, the active index range, and the expressions
for the nonempty top, the next push position, and current item count.

____________________________________________________________________

What can remain in a popped cell? Why is it no longer a logical item?

____________________________________________________________________

Which full check uses global `capacity`, and why does changing that variable
not resize the ten-cell array?

____________________________________________________________________

Distinguish global `size`, global `postfix_size`, and local `value_size`. Which two structures
use the same next-insertion convention with separate variables?

____________________________________________________________________

## 4. Boundary behavior

For each case, record the return, final `size`, and whether any array cell
changes. Include evidence for preserved state.

1. `push('K')` when all ten character positions are active.
2. `peek()` when empty.
3. `pop()` when empty.
4. Successful pop followed by peek of the newly exposed character.

____________________________________________________________________

Why is returning `'\0'` not a separate success flag? What assumption about
ordinary test characters avoids ambiguity?

____________________________________________________________________

## 5. Expression transfer

Trace conversion of `1-2*3+4`. At each token, record the character operator
Stack, `size`, postfix prefix, and `postfix_size`. Explain the final terminator and
why the operator Stack is empty afterward.

____________________________________________________________________

Trace evaluation of the completed postfix. At each token, record the integer
`values` Stack, `size`, and any calculation. Explain `c - '0'` and why `num2`
is popped before `num1`.

____________________________________________________________________

State the permitted operators, seven-character bound, operand format,
initial-Stack requirement, and arithmetic assumptions.

____________________________________________________________________

Name three unsupported inputs and the missing checks they expose. Describe
them as limitations; do not claim they are safely rejected.

____________________________________________________________________

## 6. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Canonical A, B, C LIFO trace | | | |
| Peek preserves `size` and array | | | |
| Pop exposes previous character without erasing the old cell | | | |
| Full push preserves all ten cells and `size` | | | |
| Empty peek/pop return `'\0'` and preserve state | | | |
| `1-2*3+4` converts to `123*-4+`, length 7 | | | |
| Canonical postfix evaluates to `-1` | | | |
| Equal-precedence operators remain left associative | | | |
| Noncommutative operands have the correct order | | | |
| A second, shorter valid conversion resets `postfix_size` and terminates output | | | |
| Character digits become numeric values | | | |

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
| Character push | | |
| Character peek | | |
| Character pop | | |
| Convert `n` valid infix tokens | | |
| Evaluate `n` valid postfix tokens | | |
| Storage with the present fixed arrays | | |

Explain the current seven-token limit and how storage would change if the
arrays grew with input length.

____________________________________________________________________

## 8. Three uses of “stack”

Distinguish the Stack ADT, the runtime call stack, and this lab's global
character array. Explain why the local integer `values` array is also a
Stack representation even though its variable is not named `stack`.

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
