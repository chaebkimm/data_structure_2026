# Stage C — Investigation Worksheet: Fixed Stack State

Name: ____________________________  
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

The Stage C core is Sections A through F. Complete and preserve those
sections before opening Stage D. Sections G and H may be completed during the
announced independent-work window.

## Quick reference

A Stack is an abstract data type (ADT) with one accessible end, the top. Last
in, first out (LIFO) means the most recently pushed item is the first item
popped. `peek` reports that item without removing it.

This module stores generic integers in caller-owned fixed arrays. `size`
counts logical items and `capacity` counts prepared positions. Valid metadata
satisfies `0 <= size <= capacity`. When `size > 0`, the top is
`stack[size - 1]`. A rejected operation preserves the prior array, size, and
required output.

## A. Trace the canonical function IDs

A trace is a step-by-step record of changing state. Write Stack states from
bottom to top. Start with `int stack[10]`, `size = 0`, and `capacity = 10`.

| Request | Returned value | Output value, if used | State after request | New `size` |
|---|---:|---:|---|---:|
| start | none | none | empty | 0 |
| `push(100)` | | none | | |
| `push(200)` | | none | | |
| `push(300)` | | none | | |
| `peek` | | | | |
| `pop` | | | | |
| `pop` | | | | |
| `pop` | | | | |

1. What is the greatest size reached? ______________________________
2. Which index stores 300 immediately after the third push? _________
3. Why does `peek` leave 300 present? ______________________________
4. In what order do the three successful pops report the IDs? _______

## B. Apply the operation contracts

A contract states what a function accepts, changes, returns, and preserves.
An output parameter is caller-provided storage where a function writes an
additional result.

```c
int int_stack_push(
    int stack[],
    int size,
    int capacity,
    int value
);

int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);
```

For `peek` and `pop`, the output storage must be separate from the Stack
array.

Complete the contract table.

| Operation | Success result and effect | Rejection result | What rejection preserves |
|---|---|---|---|
| `push` | writes at `stack[size]`; returns `size + 1` | original size | |
| `peek` | writes top to output; returns 1 | 0 | |
| `pop` | writes top to output; returns `size - 1` | original size | |

Why does `pop` receive a `const int stack[]`? What does that say about the
inactive array position after a pop?

____________________________________________________________________

Why must the caller save the returned size after a successful `push` or
`pop`?

____________________________________________________________________

## C. Check empty, full, and invalid metadata

Classify each case independently. Use output value 999 where an output is
needed.

| Starting state and request | Accepted? | Return | Final output | Preserved state |
|---|---|---:|---:|---|
| empty, capacity 10; `peek` | | | | |
| empty, capacity 10; `pop` | | | | |
| 100, 200, 300; size 3, capacity 3; `push(400)` | | | none | |
| size 4, capacity 3; `push(400)` | | | none | |
| size 2, capacity 1; `peek` | | | | |
| 100, 200; size 2, capacity 10; `pop` | | | | |

1. Why must `size == capacity` be checked before writing `stack[size]`?

   _________________________________________________________________

2. Why does an empty Stack have no valid `stack[size - 1]` position?

   _________________________________________________________________

3. The array has ten physical positions, but the caller passes capacity 3.
   Which boundary must the functions honor? Why?

   _________________________________________________________________

## D. Transfer the rule to `1+2*3`

The evaluator accepts a nonempty alternating sequence of single digits and
operators. The only operators are `+` and `*`. It accepts no spaces,
parentheses, unary operators, or multi-digit numbers. Operators with greater
precedence are applied first. Operators with equal precedence are applied
from left to right.

It uses two checked, ten-position Stacks: one for numbers and one for operator
character values. Input length is not otherwise capped. Every internal push
must still confirm that its own Stack has room.

Complete the successful trace.

| Input event | Number Stack | Operator Stack | Calculation, if any |
|---|---|---|---|
| start | empty | empty | none |
| read `1` | | | |
| read `+` | | | |
| read `2` | | | |
| read `*` | | | |
| read `3` | | | |
| end: apply waiting operators | | | |

The public contract is:

```c
int expression_evaluate(const char expression[], int *out_result);
```

It returns 1 only after producing exactly one checked result. On every
rejection it returns 0 and leaves `*out_result` unchanged.

| Input | Accept or reject? | Result if accepted | Reason |
|---|---|---:|---|
| `"7"` | | | |
| `"1+2*3"` | | | |
| `""` | | | |
| `"1++2"` | | | |
| `"12+3"` | | | |
| `"1 +2"` | | | |
| `"(1+2)"` | | | |
| arithmetic outside the C `int` range | | | |

Why must an overflow check happen before making the calculated value
official?

____________________________________________________________________

## E. Distinguish a physical slot from a logical item

Consider this deliberately prepared array:

```text
stack:   [ 10 ][ 20 ][ 777 ][ 888 ]
index:      0      1      2       3
size: 2
capacity: 4
```

1. Which indexes are logical Stack items? ___________________________
2. Which value is the correct top? _________________________________
3. What does the faulty expression `stack[size]` read? ______________
4. Why is that read inside the array but outside the logical Stack? __
5. Which expression reads the correct top? _________________________

A memory-safe access can still be logically wrong. Explain how the faulty
peek could make a caller resume the wrong function ID.

____________________________________________________________________

## F. Connect cost to fixed storage

Let `n` be the expression length. `O(1)` means a fixed amount of work. `O(n)`
means work grows in proportion to `n`.

| Work | Cost | Reason |
|---|---:|---|
| successful or rejected `push` | | |
| successful or rejected `peek` | | |
| successful or rejected `pop` | | |
| scan and evaluate an expression of length `n` | | |
| extra storage used by two ten-position internal arrays | | |

Why does no Stack operation shift existing logical items?

____________________________________________________________________

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack is implementation
bookkeeping commonly used for active function calls. A local array such as
`int stack[10]` is one fixed buffer that may be used to represent a Stack ADT.
These are related ideas, not interchangeable objects.

1. Does storing ID 100 in the course Stack create a real C call frame?

   _________________________________________________________________

2. Does the name `stack` make an array obey LIFO automatically?

   _________________________________________________________________

3. Which functions enforce LIFO for the caller-owned array?

   _________________________________________________________________

## H. Exit ticket

1. Where is the top of a nonempty Stack? ____________________________
2. State LIFO in your own words. ____________________________________
3. Distinguish `peek` from `pop`. ___________________________________
4. What is preserved after a rejected `peek`? ______________________
5. What is preserved after a rejected `push`? ______________________
6. State the accepted expression grammar. __________________________
7. One question you still have: ____________________________________
