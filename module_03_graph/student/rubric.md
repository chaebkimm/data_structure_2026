# Module 3 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Directed representation and vocabulary | 15 | Seven-account SNS diagram or description, six-edge set, and `int` matrix agree; row is follower and column is followed account |
| Initialization | 20 | Valid count is stored and the complete 16-by-16 grid, including inactive cells, is cleared; failure preserves state |
| Directed edge operations | 20 | Add and remove check active indexes, update one directed cell, preserve unrelated cells, and behave idempotently |
| Out-degree and direct lookup | 15 | Sora's row count changes from 2 to 1 after removing `2 → 3`; general valid rows are counted correctly, invalid requests preserve output, and a guarded direct lookup is demonstrated |
| Invariants and boundary safety | 10 | Capacity, active-index, binary-cell, inactive-cell, and diagonal rules are applied accurately |
| Tests and tool evidence | 15 | Exactly three distinct student-authored tests have rationales and pass with reproducible warning-enabled compiler or approved CI evidence |
| Ghost autopsy and reflection | 5 | The separate 4→3→4 autopsy's defect, delayed symptom, repair, and regression claim are distinguished; Stage D reflection explains component membership and the limits of hypothetical feed rules |
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
  adjacency-list graphs, connected-component reasoning, and feed reflection
  do not add C functions or tests. Component and feed explanations follow the
  Stage C attempt and Stage D reading.
- Optional extension work may earn separate recognition, but it never replaces
  required core evidence.
