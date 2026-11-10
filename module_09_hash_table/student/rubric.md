# Module 09 Assessment Rubric

One Chapter 9 submission is worth 100 points. The assessed source is
`student/lab.c`; students write a driver and evidence, with no required
hash-table implementation TODOs. Visual, linear, typed, dictated, or verbal
explanations may demonstrate equivalent reasoning.

## 1. Signed hashing, keys, and collision chains — 20 points

- 5: correct C remainders and normalized bucket indices for `% 15`.
- 5: distinct bucket/node/input indices, node key, payload, and next link.
- 5: exact insertion traces for `(12,120)`, `(27,270)`, and `(-3,-30)`.
- 5: present/missing key lookup and duplicate insertion with newest match;
  distinguishes insertion status, returned node index, and payload.

## 2. Reset and failure preservation — 20 points

- 5: calls `initialize()` before first table operations.
- 5: traces reset of counter and all 15 heads, with old node fields and
  `answer` retained; explains no chain traversal or free list.
- 5: verifies ten insertions, unchanged state on an eleventh failure, and
  reuse of node 0 after reset.
- 5: explains valid, disjoint, terminating chains and repeated reset;
  distinguishes total node capacity from the number of bucket positions.

## 3. Two-sum reasoning and exact traces — 20 points

- 5: traces ascending `i`, descending earlier `j`, and answer order `{j,i}`.
- 5: distinguishes complement key, returned node, and stored earlier index;
  explains `find(complement)` and `hnodes[node].data`.
- 5: explains lookup-before-insert, no self-pair, early-return state, and
  reset at the next hash-based call.
- 5: verifies fixed answers, misses, repeated calls, and the same newest
  earlier duplicate selected by both supplied implementations.

## 4. Three original assertion groups — 15 points

- 5: hashing/chains, exact state/returns, key versus data, and duplicate keys.
- 5: reset/exhaustion, unchanged failure state, and reuse.
- 5: two-sum validity/existence, no self-pair, duplicates, and repeated calls.

Include the actual source in the driver. Repeating one test with new labels
does not replace a category. Restore `nums` after custom fixtures and use
representable `int` sums and complements.

## 5. Work counts and cost conditions — 10 points

- 4: counts a maximum of 45 brute-force comparisons and separates hashing,
  allocation/insertion, chain search, and reset of bucket heads.
- 4: distinguishes expected short chains from worst-case collisions and
  qualifies a generalized expected linear two-sum claim.
- 2: states fixed bounds of 10 nodes, 15 buckets, and 10 numbers, with no growth.

## 6. Source-based autopsy — 5 points

- 3: locates the wrong comparison of payload instead of key in a copied
  `find`; explains why the target-0 complement must match key -1, not data 4.
- 2: explains a self-pair caused by inserting before lookup and provides a
  distinguishing assertion or complete trace.

## 7. Reproducible evidence and corrections — 10 points

- 4: executable driver, exact build command, warnings, output, and result.
- 3: initial predictions retained with labeled evidence-based corrections.
- 3: evidence record, investigation, Cognitive Pause, and concise synthesis
  tied to observed state.

## Preconditions for executable evidence

Initialize before table use. Reachable node indices must be in the allocated
prefix of `hnodes` or -1, with valid, disjoint, acyclic bucket chains and
keys hashing to their bucket. Custom calls to `new_hnode` must use valid
next links; normally use `insert` so it maintains links for you. All custom
sums and complement subtractions must fit in C `int`. Correct broken driver
preconditions before treating its output as evidence.

Do not deduct for linear worksheets, no diagram, different driver-local
names, or instructor-provided compiler evidence. Open addressing, Robin Hood
hashing, tombstones, dynamic allocation, deletion, and growth are context or
optional comparisons, not required implementation tasks.
