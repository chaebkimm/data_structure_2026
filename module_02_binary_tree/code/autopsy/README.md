# Operator-Precedence Autopsy

`faulty_precedence.c` is a standalone investigation of how a builder's child
links determine expression meaning. It uses fixed array nodes, integer child
indices, and a recursive evaluator. It compares a deliberately faulty build
with a directly initialized comparison fixture.

Before opening the source or running it, complete and preserve the prediction
section in `student/tree_autopsy.md`. Then use your saved prediction while
tracing the source:

1. Trace each consumed character and the current root index.
2. Draw all five array nodes with their left and right child indices.
3. Predict the final root character and the returned answer.
4. Draw the tree that preserves multiplication precedence and explain how
   you expect its root and child links to differ.

From the parent `code` directory, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

Or run `make autopsy`. The executable is standalone; it does not use the
student implementation or require the reference solution.

Record each printed root character and answer. Use the source trace to record
the root indices and child links, which the executable does not print. Compare
both structures with your saved prediction and mark any differences.

Both trees are finite and acyclic, with one root and no shared children.
Every operator has two children, every leaf has child indices `-1`, and index
`0` identifies a real node. The defect changes the meaning of the expression
without breaking those structural invariants or accessing invalid memory.
Evaluation correctly follows the tree it receives; the builder must encode
the intended precedence.

Explain which construction decision caused the observed difference, then
propose a change using the roles of `term()` and `terms()`. Distinguish the
builder's responsibility from the evaluator's responsibility.

The program returns `0` when the planned demonstration succeeds. A successful
exit confirms that the investigation reproduced its intended fault; it does
not mean the faulty builder is correct.
