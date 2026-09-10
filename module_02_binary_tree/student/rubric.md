# Module 2 Lab Rubric — 100 Points

| Criterion | Points | Full-credit evidence |
|---|---:|---|
| Representation and invariants | 20 | Character data, child indices, -1 absence, valid index 0, root, size, and pos agree across code and diagrams; single root, no sharing/cycles, expression arity, and valid-input assumptions are explained |
| Node creation | 15 | new_node reserves the correct index, stores the character, initializes both child fields to -1, increments size once, and preserves previously created nodes |
| Expression construction | 20 | term and terms consume the intended characters, preserve multiplication precedence and left association, return correct roots, and produce the required links |
| Recursive evaluation | 20 | A digit is the base case; child results are computed before their operator; correct answers are returned without changing nodes or shared parser state |
| Operation efficiency | 10 | Constant node/link work, linear parsing/evaluation, occupied array storage, and evaluation stack depth are justified; fixed capacity is distinguished from the scalable model |
| Tests and tool evidence | 10 | Three distinct valid-input tests cover creation, construction, and evaluation/nonmutation; builds and approved diagnostics are reproducible |
| Autopsy and forward transfer | 5 | The left-to-right parser's precedence defect is identified, a term-based repair is explained, and a regression claim distinguishes the wrong and correct trees |
| **Total** | **100** | |

## Performance levels

### Exceeds expectations

The student explains unfamiliar valid expressions, uses structural checks to
prove association, and distinguishes parser state, stored characters, and
returned numeric values with evidence.

### Meets expectations

All four functions work. Valid inputs produce the textbook's representation
and results. Tests reset shared state for independent builds and show that
evaluation leaves the tree unchanged.

### Developing

Common cases work, but index initialization, term boundaries, precedence,
root updates, digit conversion, or recursive return values need guidance.

### Beginning

The code confuses 0 with an absent child, returns unused indices, loses
subtrees while updating roots, consumes the wrong characters, or replaces
operators with calculated values.

## Scoring notes

- All four functions are `TODO(core)` tasks: `new_node`, `term`, `terms`, and
  `eval_tree`. The student implements the evaluator's base case as well.
- Whole-tree validation, malformed-input handling, and traversal-label
  memorization are not required. Use the stated valid-input contract.
- Optional valid fixtures may earn a separate distinction or up to five
  bonus points when course policy permits, without replacing core points.
- Everyday explanations and approved linear-text, verbal, debugger, or
  instructor-CI equivalents earn the same credit. Drawing quality, writing
  speed, and spoken fluency are not grading criteria.
- An incorrect initial Cognitive Pause is not penalized when preserved and
  meaningfully corrected.
