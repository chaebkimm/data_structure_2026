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

Distinguish global `size`, local conversion cursor `pos`, and postfix token
length. How do the two phases reuse the same array and count?

____________________________________________________________________

## 4. Boundary behavior

For valid operations, record the return, final `size`, and array contents.
For invalid calls, identify the out-of-bounds index on paper; do not execute
them or promise a deterministic return or preserved final state.

1. Observe `is_full()` after ten valid pushes; explain why an eleventh push is invalid.
2. Observe `is_empty()` when `size == 0`; explain why peek is invalid.
3. Explain the decrement and invalid index of empty pop.
4. Execute a valid pop followed by peek of the newly exposed item.

____________________________________________________________________

Why is the conversion sentinel a stored item rather than an empty-read result?
Which caller checks prevent invalid primitive calls?

____________________________________________________________________

## 5. Expression transfer

Trace conversion of `1-2*3+4`. At each token, record the character operator
Stack (including the sentinel), `size`, postfix prefix, and local `pos`.
Explain why draining the sentinel writes the final terminator, advances `pos`
to 8, and leaves the operator Stack empty afterward.

____________________________________________________________________

Trace evaluation of the completed postfix. At each token, record the integer
`stack` values, global `size`, and any calculation. Explain `c - '0'` and why `num2`
is popped before `num1`.

____________________________________________________________________

State the permitted operators, exactly-seven-character requirement, operand
format, phase-entry resets, and arithmetic assumptions.

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
| Full predicate reports true after ten valid pushes; no eleventh push is called | | | |
| Empty predicate reports true after draining; no empty read is called | | | |
| `1-2*3+4` converts to `123*-4+`, length 7 | | | |
| Canonical postfix evaluates to `-1` | | | |
| Equal-precedence operators remain left associative | | | |
| Noncommutative operands have the correct order | | | |
| Repeated seven-character conversion resets `size` and local `pos`; sentinel terminates output | | | |
| Evaluation discards prior active items by resetting shared `size` | | | |
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
| Valid integer push | | |
| Valid integer peek | | |
| Valid integer pop | | |
| Convert `n` valid infix tokens | | |
| Evaluate `n` valid postfix tokens | | |
| Storage with the present fixed arrays | | |

Explain the current exactly-seven-token requirement and how storage would change if the
arrays grew with input length.

____________________________________________________________________

## 8. Three uses of “stack”

Distinguish the Stack ADT, the runtime call stack, and this lab's global
integer array. Explain how its active values change from operator codes
and a sentinel to numeric operands and results across the two phases.

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
