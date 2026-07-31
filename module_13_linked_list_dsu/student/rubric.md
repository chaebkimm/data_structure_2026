# Module 13 Assessment Rubric

Total: 100 points

This rubric evaluates understandable reasoning, exact state, tested code,
and honest limits. Memorized wording, drawing quality, and completion speed
are not assessed.

## 1. Beginner-first models and vocabulary - 8 points

- 4: translates among symbolic nodes, fields, and traversal order;
- 2: interprets the DSU arrays as a parent forest;
- 2: explains new terms and symbols accurately in plain language.

## 2. Linked-list operations and invariant - 18 points

- 5: exact canonical push trace;
- 6: correct predecessor/victim/successor deletion trace;
- 3: exact all-zero destruction state;
- 4: complete reachable-count, limit, cycle, and one-owner invariant.

## 3. Ownership, failure, and autopsy - 12 points

- 4: every allocation has exactly one release responsibility;
- 3: allocation/full failures and absent-removal success preserve complete
  list topology and state as contracted;
- 3: identifies the first use-after-free and repairs the order;
- 2: supplies sanitizer, debugger, or approved equivalent evidence.

## 4. DSU make-set and iterative find - 15 points

- 4: exact singleton arrays, counts, and inactive sentinel;
- 5: bounded first pass validates before indexing;
- 4: exact H path and compression array;
- 2: explains why compression preserves membership and root size.

## 5. Union by size and cycle decision - 17 points

- 6: exact seven-union parent/size/component trace;
- 4: deterministic smaller-root equal-size policy;
- 4: exact D-H compression and `merged=false` result;
- 3: correct undirected cycle-producing interpretation.

## 6. Three implementation TODO clusters - 14 points

- 5: linked push, first-match removal, and destruction;
- 4: dense make-set and iterative two-pass find;
- 5: union by component size, same-set result, and failure preservation.

Partial credit requires a clear explanation of unfinished behavior. Supplied
ownership, edge-builder, and validator code must not be replaced.

## 7. Exactly three original tests - 8 points

- 3: list lifecycle and one preserved failure;
- 2: creation/compression, equal-size tie, and invalid-ID preservation;
- 3: repeated relationship, self-loop, component counts, connected query,
  and trust scope.

Tests must add nonduplicate assertions and report expected state, not only
“did not crash.”

## 8. Cost, edge pre-lab, spiral, and scope - 8 points

- 2: list costs match the implementation;
- 2: amortized `O(alpha(n))` is interpreted without calling it literally
  constant or hiding validator cost;
- 2: edge builder preserves parallel IDs and comparator never subtracts;
- 2: local/global invariant bridge and DSU trust limitation are explicit.

## Required safety floor

A submission cannot earn a passing module score until revision corrects
all applicable items:

- external IDs are rejected before array indexing;
- no normal operation reads a released node;
- every successful list allocation has one cleanup path;
- destroy restores `head=NULL`, `size=0`, and `limit=0`;
- failure does not publish partial list, DSU, or output state;
- normal builds do not link the intentionally faulty autopsy;
- shared membership is not presented as authorization or trust; and
- submitted evidence comes only from synthetic, authorized data.

## Revision policy

One feedback-driven revision is permitted under the course policy. Preserve
the first attempt, label corrections, and explain which evidence changed
the implementation or mental model.
