# Chapter 4. Taking Out the Last Value First

## Starting Question

> When several function calls are paused, which saved call must finish first?

**Expected answer:** The newest unfinished call finishes before its older
callers can resume. Preserve the initial reasoning before naming LIFO.

## Why We Need This

The Stack rule restricts access to the newest remaining item. The motivating
function IDs are abstract labels. The current `module_04_stack/student/lab.c`
stores integers and character codes in global `int stack[10]` and uses `size = 0` for empty.
Its runtime call-stack bookkeeping is a separate object.

## Board Walkthrough

Use characters A, B, C. Write logical states from bottom to top.

| Request | Return | Logical state | `size` | Count |
|---|---|---|---:|---:|
| start | none | empty | 0 | 0 |
| `push('A')` | none | A | 1 | 1 |
| `push('B')` | none | A, B | 2 | 2 |
| `push('C')` | none | A, B, C | 3 | 3 |
| `peek()` | C | A, B, C | 3 | 3 |
| `pop()` | C | A, B | 2 | 2 |
| `pop()` | B | A | 1 | 1 |

The active prefix is 0 through `size - 1`. Push writes `stack[size]` and
then increments `size`; peek reads `stack[size - 1]`; pop returns
`stack[--size]`, decrementing before reading. These operations are unchecked.
Callers must avoid full push and empty peek/pop; such calls have undefined
behavior. The predicates report state only. `capacity` controls the full
predicate but does not resize the array or stop push.

First follow the PPT’s direct calculation of `1-2*3+4`. A number Stack
remembers operands and intermediate results; an operator Stack remembers
operations waiting for their turn. At the incoming `+`, calculate `2*3`,
then `1-6`, before saving `+`. This explains why the newest waiting values
and operators must be retrieved first.

Then show how postfix notation records that calculation order and trace the
lab’s two separate phases:

```text
1-2*3+4 -> 123*-4+ -> -1
```

Conversion resets global `size`, sets local `pos = 0`, and pushes a real
`'\0'` sentinel. It scans seven `eq` characters, then drains the sentinel to
`eq_re[7]`; `pos` ends at 8 while token length is 7 and `size` is 0. The
sentinel's precedence 0 stops reductions before an empty peek.

Evaluation resets `size` and reuses the same `int stack[10]` for numbers.
It scans exactly seven postfix tokens, excluding the terminator. Pop the
right operand into `num2` before the left into `num1`. Intermediate results
are 6, -5, and -1; final `pop()` returns -1 and leaves `size == 0`. Shorter
inputs are unsupported because both loops run seven iterations.

## Common First Thoughts

- “`size` is the index of the current top character.”
- “The newest item is at `stack[size]`.”
- “Empty means `size == 10`.”
- “Pop must erase the old cell.”
- “The sentinel is returned by an empty peek.”
- “Local output cursor `pos` is always equal to token length.”
- “Character `'3'` and integer 3 are interchangeable.”
- “A valid example proves that malformed input is safely rejected.”

## Neutral Questions

- How does the item count `size` change after this request?
- Which physical indexes currently belong to the Stack?
- Which index was written by the most recent push?
- Which array and variable belong to the current expression phase?
- Which waiting operator has equal or greater precedence?
- Which popped value is the right operand?

## Vocabulary Rules

**Words we can use:** Fixed arrays, characters, integers, indexes, counts,
active prefix, invariant, sentinel, and simple function calls.

**Names introduced here:** Stack, LIFO, top, push, peek, pop, underflow, infix,
postfix, operand, operator, precedence, associativity, and null terminator.

**Deferred or optional:** Allocation, ownership, geometric growth, checked
parser design, arithmetic overflow guards, and the legacy caller-owned
`int_stack_*`/`expression_evaluate` API.

## Scope and Evidence

Core input is exactly seven characters, with four single digits
alternating with `+ - * / %`; no spaces, parentheses, unary operators, or
multi-digit numbers. Divisors must be nonzero and integer intermediates
representable. The source assumes these conditions; missing checks are
extension discussion, not behavior to claim in evidence.

Run the current lab demo/tests, trace full/empty preconditions and both expression
phases, and preserve then revise the autopsy prediction. Standard and linear
activities have the same targets; response mode and drawing quality do not
change the reasoning required.

## Final Check

> When `+` arrives in `1-2*3+4`, why are `*` and `-` written to postfix
> before the new `+` is pushed?

**Minimum answer:** Both waiting operators have precedence at least as high
as incoming `+`. Multiplication is emitted first, then the earlier equal
precedence subtraction. The final postfix text is `123*-4+`; evaluating it
with the right operand popped first produces -1.
