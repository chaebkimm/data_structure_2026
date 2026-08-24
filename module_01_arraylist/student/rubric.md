# Module 1 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Textbook model and invariant | 20 | Accurate mapping from the textbook's contiguous, no-gap model to the implementation fields and valid ranges |
| Functional correctness and edge cases | 25 | Correct core API behavior for initialization, reserve, access, append, and destruction |
| Ownership and memory safety | 20 | Correct completion and explanation of the checked allocation scaffold, failure atomicity, and no leaks, invalid access, or stale-pointer use |
| Tests and tool evidence | 15 | Three nonduplicate student-authored contract/property tests with rationale, reproducible output, warnings, and sanitizer/debugger/CI evidence |
| Operation efficiency | 10 | Correct operation costs and an accurate explanation of why doubling reduces repeated copying |
| Explanation and security transfer | 10 | Accurate autopsy plus a concrete retention/backpressure policy explaining why safe growth is not unlimited growth |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The implementation preserves invariants on unfamiliar cases, tests failure behavior deliberately, and supports design choices with clear evidence.

### Meets expectations

The required core works on specified cases, tests are appropriate, and the
student accurately connects the implementation to the textbook model.

### Developing

The happy path mostly works, but boundary behavior, failure atomicity, testing, or invariant reasoning still needs guidance.

### Beginning

The implementation is unsafe or incomplete on the happy path, or the student cannot explain which storage is owned and which indexes are logical.

## Scoring notes

- Extension work may earn a separate distinction or up to five bonus points
  when course policy permits. It does not replace core points and cannot
  compensate for missing invariant reasoning, ownership safety, or evidence.
- Drawing quality, handwriting, typing speed, and spoken fluency are not grading criteria.
- Toolchain limitations are not penalized when the student supplies an approved equivalent such as instructor CI or debugger evidence.
- An initially incorrect Cognitive Pause is not penalized when it is preserved and meaningfully corrected.
