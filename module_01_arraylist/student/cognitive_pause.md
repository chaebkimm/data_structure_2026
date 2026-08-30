# Stage B — Five-Minute Cognitive Pause: Indexes and Boundaries

Use no notes, slides, neighbors, or coding tools for five minutes. You may
draw, type, dictate, or use a structured list. Preserve your initial response
when correction begins. Approved extended-time versions use the same targets.

## Starting state

The array has ten slots. The current list is `[100, 200, 300]`, so `size` is
3 and capacity is 10. Values occupy indexes 0 through 2.

## Complete exactly three targets

### Target 1 — Interpret the count

State the valid indexes for reading list items. Explain why index 3 is not a
valid list item even though it is inside the ten-slot array.

Response:

____________________________________________________________________

### Target 2 — Preserve list order

Delete the item at index 1. State which value moves, the final logical list,
and the new `size`. Must the program erase the old value beyond the new
`size` for the list to be correct? Explain.

Response:

____________________________________________________________________

### Target 3 — Handle a full list

Start a separate case with `size == 10`. The program receives an append
request. State its result and what must happen to all ten stored values and
the count.

Response:

____________________________________________________________________

## Calibration follow-up

After the expert model is revealed:

- preserve your first answers;
- label each correction `index`, `order`, or `capacity`; and
- finish the sentence below.

The evidence that changed or confirmed my model was:

____________________________________________________________________
