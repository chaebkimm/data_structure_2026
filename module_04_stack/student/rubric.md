# Module 4 Lab Rubric — 100 Points

A rubric is a scoring guide. Reproducible evidence gives enough detail for
another person to repeat a check against `student/lab.c`.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Stack model and canonical trace | 20 | LIFO and `'A'`, `'B'`, `'C'` trace are correct; returns, physical indexes, and bottom-to-top logical states agree |
| Character Stack operations | 25 | `top` decreases on push and increases on pop; full push is a no-op; empty peek/pop return `'\0'`; unchanged state is demonstrated |
| Representation and limits | 20 | `0 <= top <= 10`, active suffix, inactive cells, literal boundaries, and the distinct meanings of `top`, `size`, and `pos` are explained |
| Two expression phases | 15 | `1-2*3+4` becomes `123*-4+` with `size == 7`, then evaluates to `-1`; precedence, left associativity, operand order, termination, and input assumptions are accurate |
| Tests and tool evidence | 10 | Three justified new cases extend `test_lab.c`; demo, passing lab tests, commands, and actual compiler diagnostics are recorded |
| Autopsy and cost reasoning | 10 | The inactive-cell read is distinguished from the correct top; physical bounds and logical correctness are separated; operation and expression costs are explained |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student predicts unfamiliar valid states, tests preservation deliberately,
and explains how character conversion and integer evaluation use different
representations of the same LIFO rule.

### Meets expectations

The required traces are accurate, supplied and student-authored tests support
the claims, and unchecked input assumptions are identified honestly.

### Developing

Common cases work, but boundary preservation, index direction, `size` versus
`pos`, operand order, or reproducible evidence still needs guidance.

### Beginning

The student reads an inactive cell as the top, confuses Stack item count with
postfix length, reverses operands, or attributes validation to code that does
not implement it.

## Scoring notes

- Ordinary-language explanations earn full credit; memorized wording is not
  required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- Approved verbal, tactile, linear-text, or instructor-CI equivalents earn
  the same credit. CI means another computer runs the submitted tests.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
- Optional defensive checks or legacy checked-API work do not replace core
  evidence. Malformed-input rejection and overflow handling are not required
  guarantees of the current lab implementation.
