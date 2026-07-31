# Module 4 Lab Rubric — 100 Points

A rubric is a scoring guide. Functional correctness means that required code
produces the required results. A compiler translates C code into a runnable
program. A compiler warning points out code that may be mistaken. CI, or
continuous integration, means another computer automatically builds and
tests submitted code. Reproducible evidence includes enough detail for
another person to repeat a check.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Stack model and trace | 20 | LIFO, top, push, pop, peek, and underflow are explained; operation traces are exact |
| Functional correctness | 25 | Stack and delimiter functions satisfy their stated input, change, and result rules |
| Representation and failure safety | 20 | The invariant, limit, checked growth, ownership, and unchanged-state/output promises are preserved |
| Tests and tool evidence | 15 | Three nonduplicate student-authored tests with reasons plus reproducible warning-enabled compiler or CI results |
| Delimiter and cost reasoning | 10 | Valid and malformed nesting cases are distinguished and operation/parser costs are accurate |
| Autopsy and transfer | 10 | The defect is diagnosed and the Stack-to-depth-first-exploration connection is explained without confusing Stack meanings |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains an unfamiliar Stack state with the invariant,
deliberately tests a failure boundary, and transfers the LIFO rule to a new
setting.

### Meets expectations

The required functions work, Stack states are accurately traced, and
supplied plus student-authored tests support the claims.

### Developing

The common successful case works, but underflow, growth, output
preservation, malformed input, or testing still needs guidance.

### Beginning

The code removes the wrong item, bypasses the Stack contract, corrupts state
after failure, or cannot distinguish the Stack ADT from other uses of the
word “stack.”

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  notes wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent
  earns the same credit.
- Extension work means optional work beyond the required core. It may earn a
  separate distinction or up to five bonus points, but it never replaces
  core safety or evidence.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
