# Module 11 Assessment Rubric

Total: 100 points. Assessment rewards correct reasoning and reproducible
evidence, not memorized wording, drawing quality, handwriting, typing speed,
or spoken fluency. Standard, linear, typed, dictated, tactile, and verbal
formats are equivalent.

## 1. Model, formulas, and contrasts - 15 points

- 5: maps complete tree positions and applies all three index formulas;
- 5: states stable min-Heap order without claiming global sorting; and
- 5: distinguishes Heap, BST, sorted sequence, Module 10 backend, and C
  dynamic-memory heap.

## 2. TODO 1: full checker - 15 points

- 5: checks every child-parent pair and uses the complete comparator;
- 5: continues after a violation and adds zero comparisons when `n` is 0,
  otherwise exactly `n-1` saturating comparisons; and
- 5: preserves output and count on status failure and publishes output last.

## 3. TODO 2: insert and sift-up - 15 points

- 5: preserves validation, full, sequence, growth, and failure contracts;
- 5: appends at the complete-tree end and follows correct parent indexes;
  and
- 5: moves complete records, counts every parent test, and commits size and
  sequence after repair.

## 4. TODO 3: extract and sift-down - 15 points

- 5: saves the root and final candidate and preserves output on failure;
- 5: chooses the better existing child, including the lone-left case; and
- 5: produces exact stable output, counts comparisons, and resets sequence
  only after drain.

## 5. Exactly three student-authored tests - 15 points

- 5: multi-step sift-up, stable ties, exact physical state, and separate
  operation/checker deltas;
- 5: exact `5,41,17,55,70` better-child trace plus a lone-left boundary; and
- 5: two growth boundaries, post-mutation checker evidence, and full-64
  state preservation.

Three copies of one supplied fixture earn credit once.

## 6. Trace, cost, and instrumentation - 10 points

- 4: exact canonical build, extraction arrays, stable output, and normal
  totals 8 and 12;
- 3: exact checker totals 21 and 15 and combined totals 29 and 27; and
- 3: correct `O(1)`, `O(log n)`, and `O(n)` claims, including one `O(n)`
  growth insertion and amortized (spread-across-many-insertions)
  `O(log n)`, with checker work separated.

## 7. Autopsy, integrity, and scope - 10 points

- 4: identifies wrong-child divergence, repairs it, and designs a
  regression test;
- 3: frames the checker as a bounded integrity control without overstating
  it; and
- 3: states security limitations and the 64-record Dijkstra caveat.

## 8. Build and evidence quality - 5 points

- 2: warning-clean build or approved instructor-CI evidence;
- 2: supplied and student-test output is reproducible; and
- 1: evidence record is complete and names remaining limits.

## Required safety floor

Work that intentionally reads outside live storage, loses the owned pointer,
releases storage incorrectly, hides a failing test, or connects to live
operational data cannot receive implementation-safety credit until repaired.

Noncompiling work may still earn reasoning credit from preserved models,
tests, and explanations. Revision remains available under course policy.
