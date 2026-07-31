# Module 8 Lab Rubric — 100 Points

A **rubric** is a scoring guide. **Functional correctness** means required
code produces the required results. **Reproducible evidence** gives enough
detail for another person to repeat a check.

This rubric accompanies the Stage E lab and uses the beginner definitions
provided there and in the Stage D textbook.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| BFS model, frontier, and trace | 20 | Nondecreasing depth, FIFO work, left-first ties, canonical visit/depth/flag records, and frontier states are exact |
| Functional correctness | 25 | Level order, shallowest search, and BFS height satisfy every success, empty, repeated, missing, and limit contract |
| Contracts, limits, and ownership | 20 | Output preservation, 64-node and Queue limits, borrowed match pointer, inline Queue storage, tree nonmutation, and node cleanup are correct |
| Tests and reproducible evidence | 15 | Exact-order/depth, shallowest/missing-preservation, and height/Queue-boundary tests state distinct claims; warning-enabled build or approved equivalent evidence can be repeated |
| Shape measurement and cost | 10 | Width, edge height, balance preview, `O(n)`, BFS `O(w)`, DFS `O(h)`, and output-space separation are accurate |
| Autopsy and transfer | 10 | The first ordering defect, observation, smallest repair, regression test, and tree-to-graph visited-state boundary are explained |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The implementation and evidence satisfy every contract, deliberately test a
difficult limit or repeated-value case, and explain a new frontier state
from Queue rules rather than memorized order.

### Meets expectations

All three operations work, canonical states are exact, failures preserve
outputs, owned nodes are released, and supplied plus student-authored tests
support the claims.

### Developing

Common traversal works, but left/right tie order, depth records, not-found
behavior, Queue limits, height convention, cleanup, or testing still needs
guidance.

### Beginning

The code follows one branch, repeats or skips nodes, returns the wrong equal
match, changes output after failure, confuses Queue width with height, leaks
owned nodes, or lacks repeatable evidence.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, screen-reader, or
  instructor-run equivalent earns the same credit.
- An incorrect Cognitive Pause response is not penalized when preserved and
  meaningfully corrected.
- Extension work never replaces core correctness, output preservation,
  cleanup, or evidence.
- Rotation implementation is outside scope and receives no core points.
- Compiler or sanitizer access is not assumed; an approved equivalent run
  record receives the same tool-evidence credit.
