# Stage B — Five-Minute Cognitive Pause

Read the starting state and definitions with the instructor before timing
begins. When the instructor starts the five-minute timer, use no notes,
slides, classmates, vocabulary file, or coding tools. You may draw, type,
dictate, or respond in numbered sentences.

An approved extended-time or asynchronous version uses the same starting
state and the same three targets. Speed, handwriting, and drawing quality are
not assessed. Preserve the initial response when correction begins.

## Starting state and needed words

A **Stack** is a collection with access at one end, called the **top**.
**Last in, first out (LIFO)** means the item added most recently is the first
item that may be removed.

- `push` adds one item at the top.
- `peek` reports the top item without removing it.
- `pop` removes and reports the top item.
- **empty** means the Stack has no item and therefore no top.
- **underflow** is an attempt to `peek` or `pop` an empty Stack.

This character Stack uses an ArrayList as its **backend**, meaning its
lower-level storage. `size` counts current items. If `size > 0`, the top is
stored at `data[size - 1]`. In every response, list Stack items from bottom
to top.

A **delimiter** is a mark that begins or ends a group. The matching pairs are
`()`, `[]`, and `{}`. Ordinary letters do not change the Stack. Push an
opening delimiter. For a closing delimiter, check the top opening and pop it
only when the pair matches.

The **nesting limit** is the maximum number of openings the Stack may hold.
For this activity, the limit is 2.

## Complete exactly three targets

### Target 1 — Trace a complete expression

For `A(B[C]{D})`, record the Stack state after each delimiter. State the
greatest value reached by `size` and the final state.

Response:

____________________________________________________________________

### Target 2 — Distinguish two closing failures

Consider `A(B]` and `A)B` independently.

For each input, state:

- the symbol at which failure is known;
- the Stack state just before that symbol is handled; and
- whether the failure is a mismatched pair or a closing delimiter with no
  opening available.

Response:

____________________________________________________________________

### Target 3 — Enforce the boundary and check the end

Consider each input independently with nesting limit 2.

1. For `A([B{C}])`, identify the symbol at which the limit prevents an
   operation and state the unchanged Stack state.
2. For `A(B`, state the final Stack state and explain why reaching the end
   does not mean the input is complete.

Response:

____________________________________________________________________

## Calibration

**Calibration** means comparing an initial response with an accurate model.
When the instructor releases that model:

1. preserve your initial response;
2. place a check beside reasoning that remains correct;
3. label each correction `trace`, `closing failure`, `limit`, or `final
   state`; and
4. finish the sentence below.

Correction:

____________________________________________________________________

The evidence that changed my model was:

____________________________________________________________________

You may open `vocabulary.md` only after this response has been preserved.
