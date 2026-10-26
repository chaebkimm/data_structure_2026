# Module 09 — Hash Table Evidence Record

Name: ____________________  Date: ____________________

Preserve predictions and add corrections after observing the supplied source.
One Week 9 submission includes the driver, output, this record, investigation,
and corrected Cognitive Pause.

## 1. Build the actual source

Record compiler, version, working directory, exact command, warnings, and
exit result. The driver includes `lab.c`; do not also compile `lab.c` as a
separate source. Preserve the repository-root include path for Module 07.

Command and result: _________________________________________________

## 2. Explain signed bucket selection

| Value | C remainder | `hash_func` return |
| ---: | ---: | ---: |
| -16 | | |
| -8 | | |
| -1 | | |
| 0 | | |
| 12 | | |
| 22 | | |

Why is the returned bucket safe to use as an array index?

____________________________________________________________________

## 3. Record chains and payloads

Save 12, 22, and -8 in that order. List bucket heads, allocated node fields,
and the free chain. Record present 22 and missing 32 searches. Then save
another 22 and identify the first returned matching node.

Prediction: ________________________________________________________

Observed nodes and returns: _________________________________________

Correction: ________________________________________________________

Explain why `save_data` permits duplicate payloads and why `find_data`
compares payloads rather than interpreting them as `nums` positions:

____________________________________________________________________

## 4. Record ownership, clearing, and exhaustion

Show bucket/free-chain state before and after `init_hashtable()`. Explain
how `free_lnode_chunk` joins a returned chunk to the free chain. Show that
each pool index belongs to exactly one live bucket chain or the free chain.
Do not reset `lnodes` while any active chain owns a record.

Record ten allocations, the eleventh failed save, and the unchanged bucket
heads, node fields, and `free_head`. Show a successful allocation after
clearing. State the assumptions about valid acyclic chains and exclusive
pool ownership.

Evidence: __________________________________________________________

## 5. Record two-sum state

| Target / fixture | `two_sum_bf` positions | `two_sum_ht` positions | Validity / miss check |
| --- | --- | --- | --- |
| 0, original array | | | |
| 2, original array | | | |
| 3, original array | | | |
| 100, original array | | | |
| 100 then 0, no manual reset between | | | |
| 6, `{1,1,5,0,0,0,0,0,0,0}` | | | |

Record the first successful target-0 iteration: current position, number,
complement, bucket, node, stored earlier position, and earlier number.
Explain search-before-save and `nums[j] == j_num`.

____________________________________________________________________

Describe what remains in the table after success and what the next call
recycles. Restore the original `nums` after custom fixtures. State that all
sums and complements in the driver are representable as C `int`.

____________________________________________________________________

## 6. State three original test claims

1. Signed hashing and collision chains, including duplicate payloads:
   _________________________________________________________________
2. Pool recycling, exhaustion, failure preservation, and reuse:
   _________________________________________________________________
3. Two-sum validity, no-self behavior, duplicates, misses, and repeat calls:
   _________________________________________________________________

For each claim, preserve assertions, output, and one explanation of an
incorrect implementation the assertions would detect.

## 7. Diagnose the source-based autopsy

Prediction: ________________________________________________________

First divergence between node index, stored position, and number:

____________________________________________________________________

Smallest corrected assertion and result: ______________________________

Why the demonstrated failure is a wrong-answer defect:

____________________________________________________________________

## 8. Explain costs and revise the model

Give separate concrete counts and costs for hashing, saving one record,
searching a chain of length `k`, clearing `n` live records across ten
buckets, and both complete pair searches. Include the maximum 45
brute-force comparisons. Distinguish expected short chains from a worst-case
long chain. The supplied table reserves ten buckets and ten pool records.

____________________________________________________________________

Which prediction changed, and which observation changed it?

____________________________________________________________________
