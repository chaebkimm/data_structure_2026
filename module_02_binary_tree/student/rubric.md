# Module 2 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Vocabulary and representation | 20 | New terms are correctly explained; diagram, index table, and pointers describe the same tree |
| Functional correctness | 25 | Leaf, child-count, child-assignment, and immediate-family functions satisfy their contracts—the stated rules for inputs, changes, and results |
| Structural and pointer safety | 20 | Bounds and slots are checked; local and whole-tree validation are distinguished; outputs remain unchanged on error |
| Tests and tool evidence | 15 | Three nonduplicate student-authored tests with rationale plus reproducible warning-enabled compiler or CI results |
| Binary search tree reasoning | 10 | The binary search tree (BST) ordering rule and reject-duplicates policy are explained with a correct allowed-range trace |
| Autopsy and forward transfer | 10 | Structural defect is diagnosed and the move from one-parent trees to general graph relationships is justified |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains unfamiliar structures using the invariant, tests a
whole-structure risk deliberately, and transfers the model accurately to
graphs.

### Meets expectations

The required functions work, pointer relationships are accurately described,
and supplied plus student-authored tests support the claims.

### Developing

The common successful case works, but terminology, whole-tree reasoning, output
preservation, or testing still needs guidance.

### Beginning

The code or diagram confuses an address with an object, accepts unsafe
indexes, or cannot distinguish a tree from arbitrary links.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  textbook wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent earns
  the same credit.
- **CI**, or continuous integration, means another computer automatically
  builds and tests submitted code.
- Extension work may earn a separate distinction or up to five bonus points.
  It never replaces core representation, safety, or evidence points.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
