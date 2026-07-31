# Module 6 Lab Rubric — 100 Points

A **rubric** is a scoring guide. **Functional correctness** means required
code produces the required results. A **compiler** translates C code into a
runnable program. A **compiler warning** identifies code that may be
mistaken. **Reproducible evidence** gives enough detail for another person
to repeat a check. **Instructor-CI** means an instructor-run computer
automatically builds and tests submitted code.

An **allocation** is storage requested while a program runs. **Big-O
notation** writes a growth pattern as `O(...)`.
A **cycle** is a route back to an earlier vertex. The **frontier** contains
marked vertices waiting to be processed. **Validation** checks stored graph
rules. **Cleanup** releases temporary storage.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| DFS reasoning and traces | 20 | Visited state, cycle handling, recursive order, frontier states, and marked-versus-recorded reasoning are accurate |
| Three-TODO correctness | 25 | The recursive helper, iterative DFS, and undirected component count satisfy their contracts |
| Failure safety and cleanup | 20 | Validation order, output preservation, successful-push marking, Stack limits, allocation failure, and Stack cleanup are correct |
| Three tests and tool evidence | 15 | The exact three student-test categories plus warning-enabled compiler or instructor-CI evidence are reproducible |
| Components and costs | 10 | Undirected-only component reasoning and `O(V²)`, `O(V+E)`, and `O(V)` analysis are accurate |
| Autopsy, transfer, and safe scope | 10 | The cycle defect is diagnosed, tree-to-graph transfer is explained, and invented-graph reachability is not overstated |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains an unfamiliar frontier state, deliberately tests a
failure boundary, and distinguishes traversal order from reachable
membership on a new graph.

### Meets expectations

The three functions work, cycles terminate, caller outputs are preserved,
temporary storage is cleaned up, and required tests support the claims.

### Developing

The common traversal case works, but mark timing, destination order,
component counting, failure preservation, or testing still needs guidance.

### Beginning

The code repeats vertices, misses reachable vertices, changes caller output
after failure, leaks Stack storage, or counts components in a directed
graph.

## Scoring notes

- Every professional term may be explained in ordinary language; memorized
  notes wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- An approved verbal, tactile, linear-text, or instructor-CI equivalent
  earns the same credit.
- Optional extension work never replaces core correctness, cleanup, or
  evidence.
- An incorrect initial Cognitive Pause is not penalized when it is preserved
  and meaningfully corrected.
