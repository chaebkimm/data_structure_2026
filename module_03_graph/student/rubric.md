# Module 3 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Directed representation and vocabulary | 15 | Diagram or description, edge set, and `int` matrix agree; row is source and column is destination |
| Initialization | 20 | Valid count is stored and the complete 16-by-16 grid, including inactive cells, is cleared; failure preserves state |
| Directed edge operations | 20 | Add and remove check active indexes, update one directed cell, preserve unrelated cells, and behave idempotently |
| Out-degree and direct lookup | 15 | A valid row is counted correctly, invalid requests preserve output, and a guarded direct lookup is demonstrated |
| Invariants and boundary safety | 10 | Capacity, active-index, binary-cell, inactive-cell, and diagonal rules are applied accurately |
| Tests and tool evidence | 15 | Exactly three distinct student-authored tests have rationales and pass with reproducible warning-enabled compiler or approved CI evidence |
| Ghost autopsy and reflection | 5 | The first inactive-cell defect, delayed symptom, repair, and regression claim are distinguished |
| **Total** | **100** | |

## Performance guidance

- Full credit does not require memorized wording. Accurate ordinary-language
  explanations earn the same credit.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria. An approved linear-text, verbal, tactile, or instructor-CI
  equivalent earns the same credit.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
- Conceptual comparisons with undirected, weighted, edge-list, or
  adjacency-list graphs do not add implementation requirements.
- Optional extension work may earn separate recognition, but it never replaces
  required core evidence.
