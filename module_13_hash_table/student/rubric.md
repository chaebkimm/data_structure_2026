# Module 13 Assessment Rubric

Total: 100 points

Equivalent visual, linear, typed, dictated, or verbal evidence is accepted.
Exact values are required where the module locks a fixture.

## 1. Map model and exact traces - 15 points

- 4: distinguishes key/value map behavior from direct indexing
- 4: exact `10,18,26` collision locations and probe counts
- 3: exact `7,15,23` wraparound locations and bounded routes
- 4: correct present/missing stop conditions and complete result values

## 2. TODO 1: bounded probing - 15 points

- 4: begins at `key % capacity` and wraps correctly
- 4: matches occupied keys and stops at empty
- 4: remembers the first deleted slot while continuing the search
- 3: examines at most capacity slots and reports exact probe counts

## 3. TODO 2: insertion, update, and removal mutation - 15 points

- 4: inserts a missing key or updates one existing key without duplication
- 3: reuses deleted state with exact size/tombstone changes
- 3: removal writes canonical deleted state and preserves later reachability
- 3: maintenance is requested at the locked three-quarter boundary
- 2: caller results are committed last and preserved on non-`OK`

## 4. TODO 3: transactional maintenance - 10 points

- 3: selects same-capacity compaction, doubling, or full correctly
- 3: reinserts only occupied entries using replacement capacity
- 2: includes the requested new entry before commit
- 2: allocation/internal failure preserves old storage, records, counts, and
  output

## 5. Exactly three student-authored tests - 15 points

- 5: collision, wraparound, exact indexes/results/probes, validation, cleanup
- 5: tombstone lookup, beyond-tombstone update, absent-key reuse, exact counts
- 5: growth, same-capacity compaction, forced maintenance allocation failure,
  exact table/result/ownership preservation, and cleanup

Three renamed copies of supplied fixtures receive credit once. Extra test
functions do not replace a missing required category.

## 6. Validation, ownership, and failure evidence - 10 points

- 3: distinguishes constant-time shallow checks from full diagnosis
- 2: records exact inactive-field, count, uniqueness, and reachability rules
- 3: supplies reproducible allocation/full/output preservation evidence
- 2: destroys to all zero and returns live allocation count to baseline

## 7. Cost and representation selection - 10 points

- 4: defines live `n` and capacity `m`; states expected `O(1)` and worst
  `O(m)` requested-key probing; gives rebuild expected `O(m)`, worst
  `O(m + n^2)`, bounded `O(m^2)`; and limits expected amortized `O(1)` to
  suitable insertion-only growth rather than arbitrary deletion churn
- 3: compares direct indexing, AVL, and separate chaining accurately
- 3: selects a representation from exact lookup, ordering/range, memory, and
  worst-case requirements

## 8. Autopsy, security scope, and evidence quality - 10 points

- 3: predicts and locates delete-to-empty's first wrong state
- 2: repairs with deleted state and supplies the exact regression
- 3: explains bounded hash-flooding without calling the teaching hash
  cryptographic or claiming authentication
- 2: submits warning/test output, corrected artifacts, and a concise
  synthesis tied to evidence

## Required safety floor

Implementation credit remains incomplete until all of these are repaired:

- every probe loop is bounded by capacity;
- no operation reads or writes outside the allocated slot array;
- deletion preserves the probe route with a canonical deleted slot;
- one live key is never duplicated after a tombstone;
- failed allocation/full/invalid calls preserve table and result state;
- replacement storage is committed only after complete bounded construction;
- owned storage is released exactly once; and
- ordinary test targets do not hide failures or run intentionally unsafe
  behavior.

Do not deduct for choosing the linear worksheet, using correct numbered
prose instead of a drawing, using instructor-CI sanitizer evidence, or naming
local variables differently from the solution.
