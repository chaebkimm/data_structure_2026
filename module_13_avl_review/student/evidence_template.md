# Module 13 Evidence Record

Name: ____________________  Date: ____________________

Keep initial predictions and add labeled corrections. Use the [lab](lab.md), [workbook](class_material.md), and [rubric](rubric.md) for one submission.

## Search results and positions

Record original array, independent sorted copies, key, original first index, sorted first index, and miss result. Add the binary `(lo,hi,mid,value)` table, final check, invariants, and evidence that searches do not mutate input.

## Sorting and equal records

Record all five insertion prefixes and shift counts. Mark original 17A and 17B, show the final merge, and cite strict `>` and left-on-`<=` decisions. Explain what integer-only output cannot establish. Name the scratch buffer, its size, and why it cannot overlap values.

## Original checks

| Group | Predicted result | Actual result | Claim and independent basis |
| --- | --- | --- | --- |
| Search/first duplicates/misses/input preservation | | | |
| Both sorts/order and multiplicity | | | |
| Empty/singleton/boundary/extreme/repeated calls | | | |

Record compiler, command, diagnostics, and output. State `0<=n<=64` and the sorted-input/storage preconditions. Do not present invalid unchecked calls as checked rejections.

## Workload selection

For every lab scenario record preparation cost, query/update costs with assumptions, required ordering/storage, chosen method, and one competing method. Distinguish exact lookup, minimum selection, known-predecessor mutation, and graph traversal. Connect ordered candidates to Module 14 without assuming DSU.

## Count and correct

Record three original linear comparisons for key 17; three binary interval decisions plus the final equality after sorting; eight insertion shifts; merge workspace and recursion. Choose one incorrect initial claim, preserve it, and explain the correction. Confirm one complete artifact, not separate search/sort/consolidation submissions.
