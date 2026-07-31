# Module 10 Assessment Rubric

Total: 100 points. Assessment rewards accurate reasoning and reproducible
evidence, not memorized wording, drawing quality, handwriting, typing speed,
or spoken fluency. Approved standard, linear, typed, dictated, tactile, and
verbal formats are equivalent.

## 1. Model and comparator — 15 points

- 5: distinguishes alert ID, priority, and arrival sequence;
- 5: states smaller-priority then earlier-sequence comparator exactly; and
- 5: corrects the three Cognitive Pause targets using evidence.

## 2. TODO 1: stable minimum scan — 15 points

- 5: uses both comparator fields and never alert ID;
- 5: returns the correct minimum index for nonempty singleton, mixed,
  and tied live states; and
- 5: records exactly one saturating comparison per later candidate.

## 3. TODO 2: checked insertion and growth — 15 points

- 5: validates full and sequence-exhaustion cases before mutation;
- 5: grows only through 0, 4, 8, 16, 32, and 64 with allocation-failure
  preservation; and
- 5: appends the record and commits size and sequence in the required order.

## 4. TODO 3: extraction and preservation — 15 points

- 5: applies stable minimum selection;
- 5: performs correct swap-with-last removal and resets sequence on drain;
  and
- 5: preserves Queue and output on failure and publishes output last.

## 5. Exactly three student-authored tests — 15 points

- 5: mixed priorities and stable ties with non-ordering IDs;
- 5: growth plus swap-scrambled physical storage; and
- 5: protected output when empty and complete state preservation at the
  64-record full limit.

Tests must make independently meaningful claims. Three copies of one fixture
earn credit only once.

## 6. Trace, costs, and backend choice — 10 points

- 4: exact canonical service order, physical states, drained state, and 21
  extraction comparisons;
- 3: correct operation table, including 496 sorted-insert comparisons and
  496 unsorted-extract comparisons; and
- 3: backend memo justified from the requested workload.

## 7. Autopsy, policy, and safe meaning — 10 points

- 4: identifies the first faulty equal-priority decision, repairs it, and
  supplies a regression test;
- 3: explains starvation and mutable-priority risk, including decrease-key
  versus duplicate/stale strategy; and
- 3: limits claims about synthetic SOC data accurately.

## 8. Build and evidence quality — 5 points

- 2: warning-clean build or approved instructor-CI evidence;
- 2: supplied and student-test output is reproducible; and
- 1: evidence record is complete and identifies any remaining limitation.

## Required safety floor

Work that intentionally accesses outside owned storage, frees storage
incorrectly, hides a failing test, or connects to live operational data
cannot receive implementation-safety credit until repaired.

A submission that does not compile may still earn reasoning credit from
preserved traces, tests, and explanations. Revision remains available under
the course policy.
