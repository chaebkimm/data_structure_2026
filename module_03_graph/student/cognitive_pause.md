# Stage B — Five-Minute Individual Construction

Complete this activity after the representation reveal and before opening
`vocabulary.md`. Use no notes, slides, classmates, or code-running tools while
the timer is active. You may draw, type, dictate, or answer in numbered
sentences. Preserve your first response; drawing quality and speed are not
graded.

## Starting state

The fixed directed graph has three active vertices:

- 0: Web
- 1: App
- 2: Database

Its directed edges are `0 → 1`, `1 → 2`, and `1 → 0`. In the adjacency
matrix, row `from`, column `to` records that one directed edge with `1`; `0`
means the edge is absent. Opposite directions are separate facts.

## Complete exactly three targets

### Target 1 — Orient the grid

Write the three active matrix rows. Then explain why the cell at row 0,
column 1 can differ from the cell at row 1, column 0 even though both happen
to be `1` in this model.

Response:

____________________________________________________________________

### Target 2 — Trace one removal

Suppose the directed edge `1 → 2` is removed. State which one cell changes,
write the new active row 1, and give the new out-degree of vertex 1.

Response:

____________________________________________________________________

### Target 3 — Protect the invariant

The graph has `vertex_count == 3` and capacity 16. For each proposed addition,
state accept or reject and name the rule that supports your choice:

1. `2 → 2`
2. `3 → 1`
3. `2 → 0`

State what must happen to the matrix when an addition is rejected.

Response:

____________________________________________________________________

## Compare after time is called

When the instructor releases the model, preserve the initial response, mark
reasoning that remains correct, and label each correction `row/column`,
`direction`, `active index`, or `self-loop`.

The evidence that changed or strengthened my model was:

____________________________________________________________________

You may now open `vocabulary.md`.
