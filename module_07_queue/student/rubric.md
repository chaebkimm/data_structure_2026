# Module 7 Lab Rubric — 100 Points

A **rubric** is a scoring guide. **Functional correctness** means required
code produces the required results. **Reproducible evidence** gives enough
detail for another person to repeat a check.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Queue model and traces | 20 | FIFO, front/back, operations, physical/logical order, wrapped indexes, full/empty distinction, and the capacity-four trace are exact |
| Functional correctness | 25 | `validate`, `enqueue`, and `dequeue` satisfy every success, status, required empty form, and no-shifting rule |
| Invariant, failure safety, and ownership | 20 | Capacity 0–64, one fixed allocation, derived tail, output separation, unchanged failures, destruction, and no shallow copying are handled |
| Tests and tool evidence | 15 | Three nonduplicate student tests appear in order; Test 3 proves both full and post-drain empty failure preservation; claims and warning-enabled build or approved equivalent evidence are reproducible |
| Policy, cost, and storage comparison | 10 | Reject-newest, discard-oldest, backpressure, silent-loss risk, and shifting/circular/linked trade-offs are accurately explained |
| Autopsy and transfer | 10 | The earliest faulty decision, observation, repair idea, precondition, and regression test are recorded; Queue/Stack and the limited BFS connection are distinguished |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The implementation and evidence satisfy all core contracts, deliberately
test difficult boundaries, and explain a new wrapped state using the
invariant rather than memorized positions.

### Meets expectations

Required functions work, Queue states are accurately traced, failure
promises hold, and supplied plus student-authored tests support the claims.

### Developing

The common FIFO case works, but capacity 0 or 1, wrap-around, the required
empty form, failure preservation, ownership, or testing still needs guidance.

### Beginning

The code removes the wrong item, sorts codes, shifts or overwrites live
items, evaluates remainder with zero capacity, corrupts state after failure,
or lacks repeatable evidence.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, screen-reader, or
  instructor-run equivalent earns the same credit.
- The Cognitive Pause measures a model in progress. An incorrect first
  response is not penalized when preserved and meaningfully corrected.
- Extension work is optional. It may earn a separate distinction or up to
  five bonus points, but it never replaces core correctness, safety, or
  evidence.
- Compiler or sanitizer access is not assumed. An instructor-approved,
  equivalent run record receives the same tool-evidence credit.
