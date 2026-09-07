# Stage B — Five-Minute Cognitive Pause

Read the starting state and definitions with the instructor before timing
begins. When the instructor starts the five-minute timer, use no notes,
slides, classmates, vocabulary file, or coding tools. You may draw, type,
dictate, or respond in numbered sentences.

An approved extended-time or asynchronous version uses the same starting
state and the same three targets. Speed, handwriting, and drawing quality are
not assessed. Preserve the initial response when correction begins.

## Starting state and needed words

A Stack allows access at one end, called the top. Last in, first out means the
most recently added item is the first item removed. `push` adds at the top,
`peek` reports the top without removing it, and `pop` removes and reports it.

This activity uses `int stack[10]`, `size`, and `capacity`. Logical items
occupy indexes 0 through `size - 1`. If `size > 0`, the top is
`stack[size - 1]`. A rejected operation leaves the entire prior array, size,
and any required output unchanged.

## Complete exactly three targets

### Target 1 — Trace the function IDs

Start empty with capacity 10. Trace:

```text
push(100), push(200), push(300), peek, pop, pop, pop
```

Record every reported value, every new size, and every bottom-to-top state.

Response:

____________________________________________________________________

### Target 2 — Preserve state at both boundaries

Consider each case independently.

1. A capacity-3 Stack contains 100, 200, 300. State the result of
   `push(400)` and everything that remains unchanged.
2. An empty Stack is asked to `peek` into an output currently holding 999.
   State the result and the final output value.
3. An empty Stack is asked to `pop` into the same output. State the returned
   size and the final output value.

Response:

____________________________________________________________________

### Target 3 — Transfer LIFO to an expression

For `1+2*3`, explain why multiplication is completed before addition. State
the final value. Then decide whether `1++2` is accepted and what must happen
to a preexisting output value when it is rejected.

Response:

____________________________________________________________________

## Calibration

When the instructor releases the accurate model:

1. preserve your initial response;
2. mark reasoning that remains correct;
3. label each correction `trace`, `boundary`, or `expression`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed my model was:

____________________________________________________________________

You may open `vocabulary.md` only after this response has been preserved.
