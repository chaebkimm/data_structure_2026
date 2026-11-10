# Module 09 — Hash Table Evidence Record

Name: ____________________  Date: ____________________

Preserve predictions and add corrections after observing the supplied source.
One Chapter 9 submission includes driver, output, this record, investigation,
and corrected Cognitive Pause.

## 1. Build the actual source

Record compiler/version, working directory, exact command, warnings, and
exit result. Include `lab.c` once in a separate driver and compile that
driver alone. There is no Module 07 include dependency.

Command and result: _________________________________________________

## 2. Explain signed bucket selection

| Key | C remainder `% 15` | `hash_func` bucket |
| ---: | ---: | ---: |
| -16 | | |
| -8 | | |
| -1 | | |
| 0 | | |
| 12 | | |
| 27 | | |
| -3 | | |

Explain the bucket range and the distinct node-index range:

____________________________________________________________________

## 3. Record chains, keys, and payloads

Call `initialize()` and insert `(12,120)`, `(27,270)`, and `(-3,-30)`.
List status returns, allocated node indices, key/data/next fields, heads,
and `hnodes_unused`. Trace present `find(27)` and missing `find(42)`.
Insert `(27,271)` and identify the first matching node and its payload.

Prediction: ________________________________________________________

Observed nodes and returns: _________________________________________

Correction: ________________________________________________________

Explain why duplicate keys allocate new records, why `find` compares keys,
and why its return value differs from an insertion status and a payload:

____________________________________________________________________

## 4. Record reset, exhaustion, and reuse

Show heads, counter, old node fields, and `answer` before/after
`initialize()`. Explain how resetting heads and counter makes slots
reusable without clearing node fields or traversing chains.

Record ten successful insertions with colliding keys `0,15,...,135`, then
failed `insert(150,1500)`. Verify unchanged heads, node fields, and counter
on failure. Reset and show a new insertion reuses node 0. Check repeated
reset and valid, disjoint, terminating bucket chains.

Evidence: __________________________________________________________

## 5. Record two-sum state

| Target / fixture | `two_sum_bf` positions | `two_sum_ht` positions | Validity / miss check |
| --- | --- | --- | --- |
| 0, original array | | | |
| 2, original array | | | |
| 3, original array | | | |
| 100, original array | | | |
| Hash 100 then 0, no manual reset | | | |
| 6, `{1,1,5,0,0,0,0,0,0,0}` | | | |
| 10, a lone 5 then two 5s | | | |

For the first target-0 match, record `i`, current value, complement, bucket,
node index, key, and stored earlier position. Explain lookup-before-insert
and answer order `{j,i}`. Why do both methods choose the same earlier
duplicate for the target-6 fixture?

____________________________________________________________________

Describe state after success and the reset at the next call. Restore `nums`
after custom fixtures. Confirm `0 <= answer[0] < answer[1] < NUMS_SIZE`
for every hit, a correct sum, and representable `int` sums/complements.

____________________________________________________________________

## 6. State three original test claims

1. Signed hashing, chains, key/payload distinction, and duplicate keys:
   _________________________________________________________________
2. Reset, capacity exhaustion, unchanged failure state, and slot reuse:
   _________________________________________________________________
3. Two-sum validity, no self-pair, duplicates, misses, and repeated calls:
   _________________________________________________________________

Preserve assertions, output, and one incorrect implementation each claim
would detect. Use the actual supplied source without editing it.

## 7. Diagnose the source-based autopsy

Prediction: ________________________________________________________

First divergence between key comparison and payload comparison:

____________________________________________________________________

Distinguishing assertion or complete hand trace: ______________________

Why the demonstrated failure is a wrong-answer defect:

____________________________________________________________________

## 8. Explain costs and revise the model

Give separate counts/costs for hashing, allocation, head insertion,
searching `k` nodes, resetting 15 heads, and both pair searches. Include
45 comparisons for a complete brute-force miss and the actual comparisons
for a target-0 hit. State distribution/load assumptions behind expected
short chains and the worst-case collision cost. This source fixes 10 node
slots, 15 buckets, and 10 input values without automatic growth.

____________________________________________________________________

Which prediction changed, and which observation changed it?

____________________________________________________________________
