# Chapter 4. Taking Out the Last Value First

## Starting Question

> When several function calls are paused, which saved call must finish first?

**Expected answer:** The newest unfinished call finishes before its older
callers can resume. Preserve the initial reasoning before naming LIFO.

## Why We Need This

The Stack rule restricts access to the newest remaining item. The motivating
function IDs are abstract labels. The current `module_04_stack/student/lab.c`
stores characters in global `char stack[10]` and uses `top = 10` for empty.
Its runtime call-stack bookkeeping is a separate object.

## Board Walkthrough

Use characters A, B, C. Write logical states from bottom to top.

| Request | Return | Logical state | `top` | Count |
|---|---|---|---:|---:|
| start | none | empty | 10 | 0 |
| `push('A')` | none | A | 9 | 1 |
| `push('B')` | none | A, B | 8 | 2 |
| `push('C')` | none | A, B, C | 7 | 3 |
| `peek()` | C | A, B, C | 7 | 3 |
| `pop()` | C | A, B | 8 | 2 |
| `pop()` | B | A | 9 | 1 |

The active suffix is `top` through index 9. Push decrements before writing;
peek reads `stack[top]`; pop reads then increments. A full push (`top == 0`)
is a silent no-op. Empty peek/pop return `'\0'` without changing state.
The count is `10 - top`. The declared `capacity` does not reconfigure the
array or the literal 10 used by the empty check.

Then trace two separate phases:

```text
1-2*3+4 -> 123*-4+ -> -1
```

Conversion uses the character Stack for operators; global `size` is postfix
length seven. Evaluation uses local `int values[10]` with upward count `pos`.
Pop the right operand into `num2` before the left into `num1`. The intermediate
results are 6, -5, and -1. The terminating `'\0'` is outside the token count.

## Common First Thoughts

- “`top` is the number of stored characters.”
- “The newest item is at `stack[top - 1]`.”
- “Empty means `top == 0`.”
- “Pop must erase the old cell.”
- “Global `size` counts the operator Stack.”
- “Character `'3'` and integer 3 are interchangeable.”
- “A valid example proves that malformed input is safely rejected.”

## Neutral Questions

- What are `top` and the count before and after this request?
- Which physical indexes currently belong to the Stack?
- Which index was written by the most recent push?
- Which array and variable belong to the current expression phase?
- Which waiting operator has equal or greater precedence?
- Which popped value is the right operand?

## Vocabulary Rules

**Words we can use:** Fixed arrays, characters, integers, indexes, counts,
active suffix, invariant, sentinel, and simple function calls.

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
