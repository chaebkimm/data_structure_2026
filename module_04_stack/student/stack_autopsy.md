# Stack Autopsy — The Next Unused Slot Is Not the Top

## Case

An **autopsy** is a careful study of a supplied defect. The supplied program
uses a stack while checking delimiters such as `(` and `)`.

The stack stores:

```text
data: [ '(' ][ '[' ][ '?' ][ '?' ][ '?' ]
index:    0      1      2      3      4
size: 2
```

Only indexes 0 and 1 are **logical elements**—values currently in the stack.
Index 2 is inside the physical array, but it is the next unused slot.

The faulty operation is:

```c
return stack->data[stack->size];
```

## 1. Predict before running

What character should a correct `peek` return?

____________________________________________________________________

What character will the faulty `peek` return?

____________________________________________________________________

Will the faulty validator accept the valid text `([])`? Why?

____________________________________________________________________

## 2. Record the observation

Copy the five important output lines:

```text
size:
correct top:
faulty top:
faulty validator says valid:
reported index:
```

Did the observation match your prediction?

____________________________________________________________________

## 3. Find the first broken rule

Do not begin with the final rejection. State the earliest stack rule that the
program violates.

____________________________________________________________________

Complete the two indexes:

```text
top index = size - ___
next unused index = size
```

## 4. Explain why this can hide

The faulty read stays inside the five-cell demonstration array. Why does
"inside the physical array" not mean "inside the logical stack"?

____________________________________________________________________

Why might this bug produce different-looking symptoms if an unused cell did
not contain the predictable character `?`?

____________________________________________________________________

## 5. Trace the validator

Trace `([])` one character at a time.

| Index | Character | Stack after an opening is pushed | Value read as top | Decision |
|---:|:---:|---|:---:|---|
| 0 | `(` | | | |
| 1 | `[` | | | |
| 2 | `]` | | | |
| 3 | `)` | | | |

At what index does the wrong stack operation first change the validator's
decision?

____________________________________________________________________

## 6. Repair and regression test

Write the corrected one-line `peek` expression:

```c
return ________________________________________________;
```

A **regression test** is a test kept so that a repaired bug does not return.
Write two tests: one stack-level test and one delimiter-level test.

1. Stack-level: _____________________________________________________
2. Delimiter-level: _________________________________________________

## 7. Separate the three meanings of “stack”

Which stack appears in this autopsy?

- [ ] the Stack abstract data type used to organize values;
- [ ] the runtime call stack used by function calls;
- [ ] a fixed stack buffer, meaning a local fixed-size array.

More than one box may apply. Explain each choice in one sentence.

____________________________________________________________________
