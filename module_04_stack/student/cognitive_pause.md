# Stage B — Five-Minute Cognitive Pause

Read the starting state and definitions with the instructor before timing
begins. When the five-minute timer starts, use no notes, slides, classmates,
vocabulary file, or coding tools. You may draw, type, dictate, or respond in
numbered sentences.

An approved extended-time or asynchronous version uses the same starting
state and exactly the same three targets. Speed, handwriting, and drawing
quality are not assessed. Preserve the initial response before correcting it.

## Starting state and needed words

A Stack follows last in, first out. `push` adds at the top, `peek` reports the
top without removing it, and `pop` removes and reports it.

The lab uses global `int stack[10]` and `size`. Empty means `size == 0`;
full means `size == capacity` (10 in this lab). Active indexes run from 0
through `size - 1`, and the nonempty top is `stack[size - 1]`. A successful
push writes at `size`, then increases it; pop decreases `size`, then
reads `stack[size]`. These operations are unchecked: avoid full push and
empty peek/pop. The predicates report state but do not guard operations.

Infix places operators between operands. Postfix places each operator after
its operands. Multiplication has greater precedence than addition and
subtraction. The lab reuses one integer Stack: operator codes and a bottom
sentinel during conversion, then integer values during evaluation.

## Complete exactly three targets

### Target 1 — Trace the function labels

Start empty and trace:

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

Record each return, the new `size`, and the bottom-to-top logical state.
Which physical index contains `'C'` after the third push?

Response:

____________________________________________________________________

### Target 2 — Respect both boundaries

Consider each case independently.

1. All ten positions are active and `size == 10`. What does `is_full()`
   report, and which index would an invalid `push('K')` try to write?
2. The Stack is empty with `size == 0`. What does `is_empty()` report,
   and which index would an invalid `peek()` select?
3. Begin empty again. Which index would `pop()` try to read after its
   decrement, and why can no return value or preserved state be promised?

Diagnose invalid calls on paper; do not execute them.

Response:

____________________________________________________________________

### Target 3 — Transfer LIFO to an expression

For `1-2*3+4`, write the postfix order and final integer result. Explain why
multiplication happens before the waiting subtraction. Which Stack stores
operator codes and the sentinel, and how is that storage reused for integers?

Response:

____________________________________________________________________

## Calibration

When the instructor releases the accurate model:

1. preserve the initial response;
2. mark reasoning that remains correct;
3. label each correction `trace`, `boundary`, or `expression`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed my model was:

____________________________________________________________________

You may open `vocabulary.md` after preserving this response.
