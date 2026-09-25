# Chapter 4. Taking Out the Last Value First

## Starting Question

> When several function calls are paused, which saved call must finish first?

**Expected answer:** The newest unfinished call finishes before its older
callers can resume. Preserve the initial reasoning before naming LIFO.

## Why We Need This

The Stack rule restricts access to the newest remaining item. The motivating
function IDs are abstract labels. The current `module_04_stack/student/lab.c`
stores characters in global `char stack[10]` and uses `pos = 0` for empty.
Its runtime call-stack bookkeeping is a separate object.

## Board Walkthrough

Use characters A, B, C. Write logical states from bottom to top.

| Request | Return | Logical state | `pos` | Count |
|---|---|---|---:|---:|
| start | none | empty | 0 | 0 |
| `push('A')` | none | A | 1 | 1 |
| `push('B')` | none | A, B | 2 | 2 |
| `push('C')` | none | A, B, C | 3 | 3 |
| `peek()` | C | A, B, C | 3 | 3 |
| `pop()` | C | A, B | 2 | 2 |
| `pop()` | B | A | 1 | 1 |

The active prefix is 0 through `pos - 1`. Push writes `stack[pos]` and
then increments `pos`; peek reads `stack[pos - 1]`; pop decrements `pos`
and then reads `stack[pos]`. A full push (`pos == 10`)
is a silent no-op. Empty peek/pop return `'\0'` without changing state.
The count is `pos`. The declared `capacity` controls the full
check but does not resize the ten-cell array.

Then trace two separate phases:

```text
1-2*3+4 -> 123*-4+ -> -1
```

Conversion uses the character Stack for operators; global `size` is postfix
length seven. Evaluation uses local `int values[10]` and its own `pos`, with the same
next-insertion/count convention as the global character Stack.
Pop the right operand into `num2` before the left into `num1`. The intermediate
results are 6, -5, and -1. The terminating `'\0'` is outside the token count.

## Common First Thoughts

- “`pos` is the index of the current top character.”
- “The newest item is at `stack[pos]`.”
- “Empty means `pos == 10`.”
- “Pop must erase the old cell.”
- “Global `size` counts the operator Stack.”
- “Character `'3'` and integer 3 are interchangeable.”
- “A valid example proves that malformed input is safely rejected.”

## Neutral Questions

- What are `pos` and the count before and after this request?
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

Core input is nonempty, at most seven characters, with single digits
alternating with `+ - * / %`; no spaces, parentheses, unary operators, or
multi-digit numbers. Divisors must be nonzero and integer intermediates
representable. The source assumes these conditions; missing checks are
extension discussion, not behavior to claim in evidence.

Run the current lab demo/tests, trace full/empty behavior and both expression
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
