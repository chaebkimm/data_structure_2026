# Module 1 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Textbook model and invariant | 20 | Correct distinction between ten array slots and current items; valid count range and gapless list order are explained |
| Core operations | 25 | Checked read/update, first-match search, append, insertion, and deletion work; the caller saves returned counts |
| Bounds and rejected-state safety | 20 | Invalid indexes/counts and full additions leave the entire array unchanged; unused slots are not treated as current items |
| Tests and tool evidence | 15 | Three distinct student tests have rationales and reproducible warning-enabled and approved diagnostic evidence |
| Operation efficiency | 10 | The student correctly counts comparisons and moves, including insertion direction and zero moves for a full-list rejection |
| Autopsy and explanation | 10 | The boundary defect and guard-slot result are diagnosed; the repair preserves both values and count |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The implementation preserves the invariant in unfamiliar sequences, tests
rejection deliberately, and explains the result using exact indexes and
counts.

### Meets expectations

Every core operation works on specified cases. Tests are appropriate, and
the student connects the implementation to the fixed-capacity model.

### Developing

Common cases work, but range checks, shift order, count updates, first-match
behavior, or rejection still needs guidance.

### Beginning

The implementation accesses an invalid position or loses list items, or the
student cannot distinguish size from capacity.

## Scoring notes

- All listed operations are core. Extension tests add edge and sequence cases
  for the same functions; they do not introduce extra operations.
- Extension work may earn a separate distinction or up to five bonus points
  when course policy permits. It does not replace core points.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved linear-text, verbal, debugger, or instructor-CI equivalent
  earns the same credit. CI means another computer runs the submitted tests.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
