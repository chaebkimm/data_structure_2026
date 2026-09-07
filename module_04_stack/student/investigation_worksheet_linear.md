# Stage C — Investigation: Linear Accessible Format

## How to use this version

This version has the same questions and learning targets as the standard
investigation. It contains no response table or drawing requirement. It works
with a screen reader, keyboard navigation, speech input, or text-only output.

Open it after completing and preserving the Cognitive Pause.

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

A trace is a step-by-step record of changing state. State Stack items from
bottom to top. Start with `int stack[10]`, `size = 0`, and `capacity = 10`.

### A1. State sequence

For each request, state its return, any output value, the new size, and the
bottom-to-top Stack:

1. `push(100)`.
2. `push(200)`.
3. `push(300)`.
4. `peek`.
5. `pop`.
6. `pop`.
7. `pop`.

Response:

### A2. Greatest size

What is the greatest size reached?

Response:

### A3. Physical index

Which index stores 300 immediately after the third push?

Response:

### A4. Inspect and remove

Why does `peek` leave 300 present? In what order do the three successful pops
report the IDs?

Response:

## B. Apply the operation contracts

A contract states what a function accepts, changes, returns, and preserves.
An output parameter is caller-provided storage where a function writes an
additional result.

The public functions are:

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

### B1. Push contract

On success, `push` writes at `stack[size]` and returns `size + 1`. On
rejection, it returns the original size. State what it preserves.

Response:

### B2. Peek contract

On success, `peek` writes the top to the output and returns 1. On rejection,
it returns 0. State what it preserves.

Response:

### B3. Pop contract

On success, `pop` writes the top to the output and returns `size - 1`. On
rejection, it returns the original size. State what it preserves.

Response:

### B4. Inactive value

Why does `pop` receive a `const int stack[]`? What does that say about the
inactive array position after a pop?

Response:

### B5. Saved size

Why must the caller save the returned size after a successful `push` or
`pop`?

Response:

## C. Check empty, full, and invalid metadata

Use output value 999 where an output is needed. For every independent case,
state whether the request is accepted, its return, the final output, and the
preserved state.

### C1. Empty peek

Start empty with capacity 10. Request `peek`.

Response:

### C2. Empty pop

Start empty with capacity 10. Request `pop`.

Response:

### C3. Full push

Start with 100, 200, 300, size 3, and capacity 3. Request `push(400)`.

Response:

### C4. Invalid size

Use size 4 and capacity 3. Request `push(400)`.

Response:

### C5. Invalid peek metadata

Use size 2 and capacity 1. Request `peek`.

Response:

### C6. Successful pop

Start with 100, 200, size 2, and capacity 10. Request `pop`.

Response:

### C7. Explain the checks

Why must full be checked before writing `stack[size]`? Why does an empty Stack
have no valid `stack[size - 1]` position? If the physical array has ten
positions but the caller passes capacity 3, which boundary must the functions
honor?

Response:

## D. Transfer the rule to `1+2*3`

The evaluator accepts a nonempty alternating sequence of single digits and
operators. The only operators are `+` and `*`. It accepts no spaces,
parentheses, unary operators, or multi-digit numbers. Greater precedence is
applied first. Equal precedence is applied from left to right.

It uses two checked, ten-position Stacks: one for numbers and one for operator
character values. Input length is not otherwise capped. Every internal push
must still confirm that its Stack has room.

### D1. Successful trace

Starting with two empty Stacks, state both bottom-to-top states and any
calculation after each event: read `1`, read `+`, read `2`, read `*`, read `3`,
and end of input.

Response:

### D2. Public contract

```c
int expression_evaluate(const char expression[], int *out_result);
```

It returns 1 only after producing exactly one checked result. On rejection it
returns 0 and leaves `*out_result` unchanged.

### D3. Accepted and rejected inputs

For each input, state accept or reject, the result if accepted, and the reason:

1. `"7"`.
2. `"1+2*3"`.
3. `""`.
4. `"1++2"`.
5. `"12+3"`.
6. `"1 +2"`.
7. `"(1+2)"`.
8. An expression whose checked arithmetic would exceed the C `int` range.

Response:

### D4. Commit checked arithmetic

Why must an overflow check happen before making the calculated value official?

Response:

## E. Distinguish a physical slot from a logical item

Use this deliberately prepared state:

```text
stack:   [ 10 ][ 20 ][ 777 ][ 888 ]
index:      0      1      2       3
size: 2
capacity: 4
```

### E1. Classify positions

Which indexes are logical items? Which indexes are allocated but inactive?

Response:

### E2. Compare peek expressions

State the correct top, the value read by `stack[size]`, and the expression
that reads the correct top.

Response:

### E3. Explain the defect

Why is `stack[size]` inside the physical array but outside the logical Stack?
How could that faulty peek make a caller resume the wrong function ID?

Response:

## F. Connect cost to fixed storage

Let `n` be expression length. `O(1)` means fixed work. `O(n)` means work grows
in proportion to `n`.

### F1. Classify costs

Give the cost and one reason for each:

1. Successful or rejected `push`.
2. Successful or rejected `peek`.
3. Successful or rejected `pop`.
4. Scan and evaluate an expression of length `n`.
5. Extra storage used by two ten-position internal arrays.

Response:

### F2. No shifting

Why does no Stack operation shift existing logical items?

Response:

## G. Separate three uses of “stack”

The Stack ADT is a behavior rule. The runtime call stack is implementation
bookkeeping commonly used for active function calls. A local array such as
`int stack[10]` is one fixed buffer that may represent a Stack ADT. These are
related ideas, not interchangeable objects.

### G1. Function ID versus call frame

Does storing ID 100 in the course Stack create a real C call frame? Explain.

Response:

### G2. Name versus behavior

Does the name `stack` make an array obey LIFO automatically? Explain.

Response:

### G3. Enforced operations

Which functions enforce LIFO for the caller-owned array?

Response:

## H. Exit ticket

1. Where is the top of a nonempty Stack?
2. State LIFO in your own words.
3. Distinguish `peek` from `pop`.
4. What is preserved after a rejected `peek`?
5. What is preserved after a rejected `push`?
6. State the accepted expression grammar.
7. State one question you still have.

Response:
