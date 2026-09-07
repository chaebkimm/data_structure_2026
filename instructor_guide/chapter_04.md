# Chapter 4. Taking Out the Last Value First

## Starting Question

> When several function calls are paused, which saved call must finish first?

**Expected answer:** The newest unfinished call must finish before the older
calls below it can resume.

## Why We Need This

A fixed array can store saved function IDs, but an access rule is still
needed. New IDs enter at one end. Only the newest ID may be inspected or
removed. This is the Stack rule: last in, first out.

The runtime call stack is a motivating model, not the `int` Stack object that
students implement. The course Stack is an ordinary caller-owned array with a
separate `size` and `capacity`.

## Board Walkthrough

Use capacity 10. Write states from bottom to top.

| Request | Report | State | Size |
|---|---|---|---:|
| start | none | empty | 0 |
| push 100 | none | 100 | 1 |
| push 200 | none | 100, 200 | 2 |
| push 300 | none | 100, 200, 300 | 3 |
| peek | 300 | 100, 200, 300 | 3 |
| pop | 300 | 100, 200 | 2 |
| pop | 200 | 100 | 1 |

When `size` is 3, the top is `stack[size - 1]`, or `stack[2]`.
`stack[size]` is the next inactive slot.

Then trace the textbook expression `1+2*3` with a number Stack and an
operator Stack. Multiplication waits above addition. At the end, apply `*`
before `+`; the sole result is 7.

## Common First Thoughts

- “The top is at `stack[size]`.”
- “Pop must erase the old array cell.”
- “Peek and pop perform the same mutation.”
- “A full push can write first and report failure afterward.”
- “The expression evaluator accepts spaces, parentheses, or multi-digit
  operands.”
- “The program-controlled Stack and runtime call bookkeeping are the same
  object.”

## Neutral Questions

- What is `size` before and after this request?
- Which indexes belong to the active Stack?
- Which value is at `size - 1`?
- What must remain unchanged when the request is rejected?
- Which waiting operator has equal or greater precedence?

## Vocabulary Rules

**Words we can use:** Fixed arrays, indexes, size, capacity, active prefix,
pointers, character constants, invariants, rejection preservation, and simple
recursive calls.

**Names introduced here:** Stack, last in first out (LIFO), top, push, peek,
pop, underflow, call frame, operator, operand, precedence, and expression
evaluation.

**Words deferred:** Allocation, release, ownership, geometric growth,
amortized cost, tree traversal orders, and graph depth-first search.

## Final Check

> Why does the evaluator for `1+2*3` leave `+` waiting when `*` arrives?

**Minimum answer:** The incoming `*` has greater precedence than the `+` at
the operator Stack's top, so `*` is pushed. At the end, `*` is popped and
applied before `+`, producing 7.
