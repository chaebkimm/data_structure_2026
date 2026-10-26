# Module 09 Assessment Rubric

The one Week 9 submission is worth 100 points. The supplied
`student/lab.c` is the assessed source. Students write a driver and evidence;
there are no required hash-table implementation TODOs. Visual, linear,
typed, dictated, or verbal explanations may show equivalent reasoning.

## 1. Signed hashing and collision chains — 20 points

- 5: calculates C remainders and the normalized bucket indices correctly.
- 5: distinguishes bucket index, node index, node payload, and next index.
- 5: traces head insertion for 12, 22, and -8 with exact pool and chain state.
- 5: traces present/missing lookup and explains duplicate payload insertion
  and newest matching payload lookup.

## 2. Pool lifecycle and failure preservation — 20 points

- 5: initializes the free pool before first use with empty buckets.
- 5: traces chunk-tail joining and the bucket-clearing order correctly.
- 5: verifies ten allocations, unchanged state after a failed eleventh save,
  and allocation after clearing.
- 5: explains disjoint ownership, valid acyclic links, empty clear, and why
  the pool must not be reset while live chains own nodes.

## 3. Two-sum reasoning and exact traces — 20 points

- 5: traces brute-force `i`/`j` order and returns positions rather than values.
- 5: distinguishes the complement, node index, stored earlier position,
  and `nums[j]` during table lookup.
- 5: explains search-before-save, no self-pair, early-return state, and the
  clearing performed at the next call.
- 5: verifies fixed target answers, misses, repeated calls, and different
  valid earlier positions when duplicate numbers are present.

## 4. Three original assertion groups — 15 points

- 5: signed hashing/chains, exact states and returns, and duplicate payloads.
- 5: recycling/exhaustion, unchanged failure state, and safe reuse.
- 5: two-sum validity/existence, no-self behavior, duplicates, and repeated calls.

The driver must include the actual supplied source. Repeating one test with
new labels does not replace a missing category. Custom fixtures restore the
original `nums` and use representable `int` sums and complements.

## 5. Work counts and cost conditions — 10 points

- 4: counts at most 45 brute-force pair comparisons and separates hashing,
  insertion, chain search, and table clearing work.
- 4: distinguishes expected short chains from worst-case collision chains
  and qualifies a generalized expected linear two-sum claim.
- 2: states the fixed ten-bucket, ten-node, ten-number bounds and the absence
  of automatic table or pool growth.

## 6. Source-based autopsy — 5 points

- 3: locates the first wrong comparison between a stored position and the
  complement; restores the comparison through `nums[j]`.
- 2: explains a self-pair from saving before searching and supplies a
  distinguishing assertion or complete hand trace.

## 7. Reproducible evidence and corrections — 10 points

- 4: records an executable driver, exact include/build command, compiler
  warnings, assertion output, and result.
- 3: preserves predictions and labels evidence-based corrections.
- 3: submits the evidence record, investigation, Cognitive Pause, and
  concise synthesis tied to observed states.

## Preconditions required for executable evidence

Executable evidence must use bucket indices 0–9, valid pool indices or `-1`,
acyclic disjoint chains, and a pool initialized before allocation. It must
avoid resetting or recycling nodes still owned by active chains. All custom
arithmetic must fit in C `int`. Correct broken driver preconditions before
using its output as evidence.

Do not deduct for using the linear worksheet, drawing no diagram, choosing
different local variable names, or receiving compiler execution evidence
from the instructor. The optional open-addressed library's tombstones,
growth, and dynamic-allocation tests are outside the required assessment.
