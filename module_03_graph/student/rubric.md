# Module 3 Lab Rubric — 100 Points

A **rubric** is a scoring guide. **Functional correctness** means that the
required code produces the required results. A **compiler** translates C
code into a runnable program. A compiler **warning** points out code that
may be mistaken. **CI**, or continuous integration, means another computer
automatically builds and tests submitted code. **Reproducible** evidence
includes enough detail for another person to repeat the check. **Transfer**
means using an idea in a new setting.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Vocabulary and representation | 20 | New terms are explained; diagram, edge set, and matrix describe the same graph |
| Functional correctness | 25 | Initialization, edge operations, degrees, and neighbor reporting satisfy their contracts—the stated rules for inputs, changes, and results |
| Matrix and boundary safety | 20 | Vertex indexes, self-loops, duplicates, symmetry, and unchanged outputs are handled correctly |
| Tests and tool evidence | 15 | Three nonduplicate student-authored tests with rationale plus reproducible warning-enabled compiler or CI results |
| Representation reasoning | 10 | Matrix, edge-list, and adjacency-list trade-offs and operation costs are accurately compared |
| Autopsy and spiral transfer | 10 | The one-sided defect is diagnosed and ArrayList/tree/graph choices are justified |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains unfamiliar graph states with the invariant, deliberately
tests a direction or symmetry risk, and transfers the representation choice
accurately.

### Meets expectations

The required functions work, matrix relationships are accurately described,
and supplied plus student-authored tests support the claims.

### Developing

The common successful case works, but terminology, symmetry, output
preservation, or testing still needs guidance.

### Beginning

The code or diagram reverses row and column meaning, accepts unsafe indexes,
or cannot distinguish directed from undirected storage.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  notes wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent earns
  the same credit.
- **Extension work**, meaning optional work beyond the required core, may
  earn a separate distinction or up to five bonus points. It never replaces
  core representation, safety, or evidence points.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
