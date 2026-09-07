# Module 4 Lab Rubric — 100 Points

A rubric is a scoring guide. Functional correctness means required code
produces required results. Reproducible evidence gives enough detail for
another person to repeat a check.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Stack model and canonical trace | 20 | LIFO, top, push, peek, pop, and underflow are explained; 100, 200, and 300 are traced exactly |
| Stack operation correctness | 25 | The three fixed-array functions satisfy their success and rejection contracts for generic integers |
| Invariant and preservation | 20 | `0 <= size <= capacity`, logical indexes, caller capacity, inactive slots, unchanged arrays, and unchanged outputs are handled accurately |
| Checked expression evaluator | 15 | The exact single-digit `+`/`*` grammar, precedence, left associativity, ten-slot checks, and integer-overflow rejection are correct |
| Tests and tool evidence | 10 | Three nonduplicate student-authored tests have reasons and reproducible warning-enabled compiler or CI results |
| Autopsy and cost reasoning | 10 | The inactive-slot peek defect and fixed-Stack/expression costs are explained without confusing physical safety with logical correctness |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains an unfamiliar valid or rejected state from the contract,
tests a preservation boundary deliberately, and transfers LIFO reasoning to a
new checked expression.

### Meets expectations

The required functions work, Stack and expression traces are accurate, and
supplied plus student-authored tests support the claims.

### Developing

The common successful case works, but underflow, a full Stack, invalid
metadata, output preservation, expression rejection, or testing still needs
guidance.

### Beginning

The code reads the wrong top, writes outside the stated capacity, changes
observable state after rejection, or cannot explain the fixed-array Stack
contract.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent earns
  the same credit. CI means another computer runs the submitted tests.
- Optional work never replaces core safety, correctness, or evidence.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
