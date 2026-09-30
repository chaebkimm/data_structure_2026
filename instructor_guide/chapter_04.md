# Chapter 4. Taking Out the Last Value First

## Starting Question

> When several function calls are paused, which saved call must finish first?

**Expected answer:** The newest unfinished call finishes before its older
callers can resume. Preserve the initial reasoning before naming LIFO.

## Why We Need This

The Stack rule restricts access to the newest remaining item. The motivating
function IDs are abstract labels. The current `module_04_stack/student/lab.c`
stores integers and character codes in global `int stack[10]` and uses `top = -1` for empty.
Its runtime call-stack bookkeeping is a separate object.

## Board Walkthrough

Use characters A, B, C. Write logical states from bottom to top.

| Request | Return | Logical state | `top` | Count |
|---|---|---|---:|---:|
| start | none | empty | -1 | 0 |
| `push('A')` | none | A | 0 | 1 |
| `push('B')` | none | A, B | 1 | 2 |
| `push('C')` | none | A, B, C | 2 | 3 |
| `peek()` | C | A, B, C | 2 | 3 |
| `pop()` | C | A, B | 1 | 2 |
| `pop()` | B | A | 0 | 1 |

The active prefix is 0 through `top`. Push increments `top` and
then writes `stack[top]`; peek reads `stack[top]`; pop returns
`stack[top--]`, reading before decrementing. These operations are unchecked.
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

Conversion resets global `top = -1` and sets local `pos = 0`.
`convert_to_postfix()` scans `eq` until its terminator. Before peeking,
its operator loop checks `!is_empty()`. It breaks if the waiting operator
has lower precedence and otherwise emits it. The final drain writes the
last `+`, leaving `pos == 7` and `top == -1`. A separate assignment writes
`postfix[7] = '\0'` and advances `pos` to 8. No sentinel is stored.

Evaluation resets `top` and reuses the same `int stack[10]` for numbers.
It scans `postfix` until its terminator, excluding that character. Pop the
right operand into `num2` before the left into `num1`. Intermediate results
are 6, -5, and -1; final `pop()` returns -1 and leaves `top == -1`. Shorter
valid expressions work because both loops stop at the null terminator.

Next trace `infix_to_postfix_parentheses()` with `eq_paren = "1+(2+3)"`.
It pushes `(` as a boundary. At `)`, its guarded loop pops and emits the
inner `+`, then pops `(` and breaks without writing it. Draining the outer
`+` produces `123++`; the explicit terminator write at index 5 leaves
`pos == 6` and `top == -1`. Evaluation
returns 6 and again leaves `top == -1`.

## Common First Thoughts

- “`top` is the item count.”
- “The newest item is at `stack[top + 1]`.”
- “Empty means `top == 9`.”
- “Pop must erase the old cell.”
- “The null terminator is popped from the Stack.”
- “Local output cursor `pos` is always equal to token length.”
- “Character `'3'` and integer 3 are interchangeable.”
- “A valid example proves that malformed input is safely rejected.”

## Neutral Questions

- How do the top index `top` and item count `top + 1` change after this request?
- Which physical indexes currently belong to the Stack?
- Which index was written by the most recent push?
- Which array and variable belong to the current expression phase?
- Which waiting operator has equal or greater precedence?
- Which popped value is the right operand?

## Vocabulary Rules

**Words we can use:** Fixed arrays, characters, integers, indexes, counts,
active prefix, invariant, and simple function calls.

**Names introduced here:** Stack, LIFO, top, push, peek, pop, underflow, infix,
postfix, operand, operator, precedence, associativity, and null terminator.
Explain `switch` in `prec` and how `break` exits the nearest loop.

**Deferred or optional:** Allocation, ownership, geometric growth, checked
parser design, arithmetic overflow guards, and the legacy caller-owned
`int_stack_*`/`expression_evaluate` API.

## Scope and Evidence

Core input is a nonempty valid expression of at most seven characters plus
its terminator in the eight-cell buffer. Use single-digit operands and binary
`+ - * / %` operators. The dedicated converter accepts balanced parentheses;
the plain converter does not. Exclude spaces, unary operators, and multi-digit
numbers. Divisors must be nonzero and integer intermediates representable. The source assumes these conditions; missing checks are
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
