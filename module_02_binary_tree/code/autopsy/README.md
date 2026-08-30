# Cascading-Clearance Autopsy

`faulty_cascade.c` deliberately reuses one local operand node in two parts of
an expression. The supplied `tree_clear` function is correct; the shared
child makes the overall structure invalid.

The six objects resemble `(3 + 5) * (5 - 2)`, but both appearances of `5`
are the same `shared_five` object. The `plus` node points right to it, and the
`minus` node points left to it. A valid expression tree would use two distinct
leaf objects even though both stored values were `5`.

Before running it:

1. Draw all six objects and every child address.
2. Identify the initializer that gives one node two incoming child links.
3. Predict which operands and links change when the `plus` branch is cleared.
4. Predict what `minus.left` will contain afterward.

From the parent `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Or run `make autopsy`.

After running it, record which addresses remain reachable through `root` and
what data those addresses reveal. Compare the observation with your saved
prediction before deciding whether the result concerns a changed field, an
ended object lifetime, or both.

The fixture contains no cycle and makes no invalid memory access. It is
separate from normal tests, whose inputs must be valid unshared trees.
Neither `tree_find` nor `tree_clear` detects or prevents malformed links;
building fresh, disjoint child subtrees is the caller's responsibility.
