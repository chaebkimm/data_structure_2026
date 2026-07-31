# Module 9 Lab Rubric — 100 Points

A **rubric** is a scoring guide. **Functional correctness** means required
code produces the required results. **Reproducible evidence** gives enough
detail for another person to repeat a check.

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| BFS model and exact trace | 20 | Queue, discovery, processing, distance, predecessor, skipped edges, and canonical visit order are exact |
| Matrix/list functional correctness | 25 | Both traversals follow ascending neighbors, discover after successful enqueue, produce equal named results, and handle cycle, merge, unreachable, empty, singleton, and limit cases |
| Path and result contracts | 15 | Source, reachable, unreachable, inactive, and malformed-result cases satisfy status and complete output-preservation rules |
| Limits, representation, and ownership | 15 | Limit 3/2 boundary, sentinel 16, matrix/list invariants, dynamic-row ownership, Queue storage, and cleanup are correct |
| Tests and reproducible evidence | 15 | Exactly three distinct student tests cover cycle/merge state, path behavior, and representation/boundary behavior; commands and results can be repeated |
| Cost, autopsy, transfer, and safe meaning | 10 | `O(V²)`, `O(V+E)`, and `O(V)` are separated from construction; the first autopsy defect, repair, regression, Spiral 3 transfer, and modeling limit are accurate |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

All contracts and evidence are complete. A difficult limit, malformed
result, or equal-hop tie is tested independently, and the explanation
derives state from the invariant.

### Meets expectations

Both traversals and path reconstruction pass required checks, failures
preserve output, owned storage is released, and evidence supports every
core claim.

### Developing

Common traversal works, but discovery timing, predecessor permanence,
sentinels, path order, Queue limits, list cleanup, or complexity boundaries
still need guidance.

### Beginning

The code duplicates or skips work, marks at the wrong time, overwrites
predecessors, changes output after failure, leaks list storage, or lacks
repeatable evidence.

## Scoring notes

- Students may explain every professional term in ordinary language;
  memorized wording is not required.
- Drawing quality, handwriting, typing speed, and spoken fluency are not
  grading criteria.
- A verbal, tactile, numbered-text, screen-reader, or instructor-run
  equivalent earns the same credit.
- An incorrect Cognitive Pause response is not penalized when preserved and
  meaningfully corrected.
- Extension work never replaces core correctness, cleanup, preservation, or
  evidence.
- Paper forest work is required reasoning; forest code is not required.
- Compiler or sanitizer access is not assumed. Approved equivalent run
  evidence receives the same tool-evidence credit.
