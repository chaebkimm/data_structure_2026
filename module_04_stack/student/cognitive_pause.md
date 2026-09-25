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

The lab uses global `char stack[10]` and `top`. Empty means `top == 10`;
full means `top == 0`. Active indexes run from `top` through 9, and the
nonempty top is `stack[top]`. A successful push decreases `top` before
writing; a successful pop increases `top` after reading. A full push changes
nothing. Empty peek and pop return `'\0'` without changing state.

Infix places operators between operands. Postfix places each operator after
its operands. Multiplication has greater precedence than addition and
subtraction. The lab uses a character Stack during conversion and a separate
integer value Stack during evaluation.

## Complete exactly three targets

### Target 1 — Trace the function labels

Start empty and trace:

```text
push('A'), push('B'), push('C'), peek(), pop(), pop(), pop()
```

Record each return, the new `top`, and the bottom-to-top logical state.
Which physical index contains `'C'` after the third push?

Response:

____________________________________________________________________

### Target 2 — Preserve state at both boundaries

Consider each case independently.

1. All ten positions are active and `top == 0`. State what `push('K')`
   returns and what happens to the array and `top`.
2. The Stack is empty with `top == 10`. State the result and final `top`
   after `peek()`.
3. Begin empty again. State the result and final `top` after `pop()`.

Response:

____________________________________________________________________

### Target 3 — Transfer LIFO to an expression

For `1-2*3+4`, write the postfix order and final integer result. Explain why
multiplication happens before the waiting subtraction. Which Stack stores
characters, and which stores integer operands and intermediate results?

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
