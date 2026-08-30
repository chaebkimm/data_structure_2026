# Module 2 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Representation and invariants | 20 | The expression fixture, pointer expressions, and portable character literals agree; general-tree arity, expression arity, one incoming link, no cycles, and caller preconditions are explained |
| Direct node operations | 15 | The five local nodes are fully initialized; chosen-side attachment checks for an empty link; a right-only generic-tree case is handled correctly |
| Recursive search | 20 | Current-node, left-subtree, right-subtree order returns the first matching address without mutation; missing and `NULL` cases work |
| Clearing, removal, and lifetime | 20 | Every selected node is reset; caller detachment is explicit; the opposite side is unchanged; cleared nodes remain live objects |
| Operation efficiency | 10 | Work is counted for initialization, linking, search, clearing, and detachment; depth is related to temporary recursive-call storage |
| Tests and tool evidence | 10 | Three distinct student tests have rationales and use valid, live-node fixtures; build and approved diagnostic evidence is reproducible |
| Autopsy and forward transfer | 5 | The shared-operand setup defect is diagnosed without blaming correct clearing or claiming destroyed storage; a repair is justified |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains unfamiliar valid arrangements, tests side preservation
and repeated data deliberately, and separates a caller precondition from an
operation's local checks.

### Meets expectations

Both recursive functions work. Direct initialization, guarded attachment,
and caller detachment are demonstrated. Tests and explanations respect node
lifetime and the unshared-tree contract.

### Developing

Common cases work, but initialization, search order, recursive clearing,
side preservation, or the distinction between clearing and detaching needs
guidance.

### Beginning

The code follows uninitialized links, loses an uncleared subtree, changes
the opposite child position, or treats a cleared live node as nonexistent.
The explanation relies on automatic checks that these functions do not make.

## Scoring notes

- Only `tree_find` and `tree_clear` are implementation TODOs. Direct node
  operations remain core and are assessed through examples and student tests.
- No traversal-label memorization or whole-tree validation is required.
- Do not create a real cycle or expired-node access to earn testing credit.
- Optional extensions add valid fixtures and traces. They may earn a separate
  distinction or up to five bonus points when course policy permits, without
  replacing core points.
- Everyday explanations are acceptable. Drawing quality, handwriting, typing
  speed, and spoken fluency are not grading criteria.
- Approved linear-text, verbal, debugger, or instructor-CI equivalents earn
  the same credit. CI means another computer runs the submitted tests.
- An incorrect initial Cognitive Pause is not penalized when preserved and
  meaningfully corrected.
