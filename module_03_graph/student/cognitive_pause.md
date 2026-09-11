# Stage B — Five-Minute Individual Construction

Complete this activity after the representation reveal and before opening
`vocabulary.md`. Use no notes, slides, classmates, or code-running tools while
the timer is active. You may draw, type, dictate, or answer in numbered
sentences. Preserve your first response; drawing quality and speed are not
graded.

## Starting state

The fixed directed graph has seven active accounts:

- 0: Mina
- 1: Joon
- 2: Sora
- 3: Dae
- 4: Hana
- 5: Leo
- 6: Nuri

Its directed edges are `0 → 1`, `1 → 2`, `2 → 0`, `2 → 3`, `4 → 5`, and
`5 → 4`. An arrow points from the follower to the followed account. In the
adjacency matrix, row `from`, column `to` records that one directed edge with
`1`; `0` means the edge is absent. Opposite directions are separate facts.

## Complete exactly three targets

### Target 1 — Orient the grid

Write only active rows 0, 2, and 6, with columns 0 through 6 in order. You do
not need to copy the full matrix. Then explain why row 0, column 1 is `1`
while row 1, column 0 is `0` in this model.

Response:

____________________________________________________________________

### Target 2 — Trace one removal

Suppose Sora unfollows Dae: the directed edge `2 → 3` is removed. State which
one cell changes, write the new active row 2, and give Sora's new out-degree.

Response:

____________________________________________________________________

### Target 3 — Protect the invariant

Start each proposed addition independently from the original graph above,
before the removal in Target 2. The graph has `vertex_count == 7` and
capacity 16. State accept or reject and name the rule that supports each
choice:

1. `2 → 2`
2. `7 → 1`
3. `3 → 0`

State what must happen to the matrix when an addition is rejected.

Response:

____________________________________________________________________

## Compare after time is called

When the instructor releases the model, preserve the initial response, mark
reasoning that remains correct, and label each correction `row/column`,
`direction`, `active index`, or `self-loop`.

The evidence that changed or strengthened my model was:

____________________________________________________________________

After completing this calibration, you may read the 30 numbered core entries
in `vocabulary.md`. Leave its supplemental textbook terms until Stage D,
after preserving your Stage C investigation attempt.
