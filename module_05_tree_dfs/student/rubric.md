# Module 5 Lab Rubric — 100 Points

A rubric is a scoring guide. Functional correctness means required code
produces the required results. A compiler translates C code into a runnable
program. A compiler warning points out code that may be mistaken.
Reproducible evidence gives enough detail for another person to repeat a
check. **Instructor-CI** means an instructor-run computer automatically
builds and tests submitted code.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Traversal model and traces | 20 | Depth-first behavior, the base case, active calls, three visit orders, and explicit Stack states are accurate |
| Functional correctness | 25 | Recursive preorder, iterative preorder, BST search, and destruction satisfy their contracts |
| Ownership and failure safety | 20 | Allocation ownership, output preservation, Stack cleanup, explicit limits, and child-before-parent release are correct |
| Tests and tool evidence | 15 | Three required student-test categories plus reproducible warning-enabled compiler or instructor-CI results |
| BST and cost reasoning | 10 | Strict search/insertion decisions and `O(n)`/`O(h)` analysis are accurate |
| Autopsy and transfer | 10 | The push-order defect is diagnosed and the tree-to-graph visited-state need is explained |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains an unfamiliar traversal state, deliberately tests a
failure boundary, and transfers the saved-work model to a new tree shape.

### Meets expectations

Required functions work, traversal orders are exact, owned nodes are
released, and supplied plus student-authored tests support the claims.

### Developing

The common recursive case works, but visit placement, explicit Stack order,
missing-key behavior, cleanup, or testing still needs guidance.

### Beginning

The code skips or repeats nodes, visits the right subtree unintentionally,
uses a freed parent, loses output after failure, or confuses the explicit
Stack with active function calls.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  notes wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent
  earns the same credit.
- Optional extension work never replaces core correctness, cleanup, or
  evidence.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
