# Module 13 Class Workbook

Keep the first prediction before opening the supplied implementation. Add corrections beside it. Use the same six values throughout: `[31,23,17,8,17,42]`, with the two 17 records labeled A then B only for the paper stability trace.

## Find before and after ordering

| Request | Prediction | Observed result | Reason/correction |
| --- | --- | --- | --- |
| Original linear search for 17 | | | |
| Original linear search for 99 | | | |
| Sorted binary first-match search for 17 | | | |
| Sorted search for a key below/between/above records | | | |

Record each binary `(lo,hi,mid,value)` row and the final bound/equality check. State what positions before `lo` and at/after `hi` mean. Explain why a sorted index is not the original record position.

## Insert and merge the same records

| Insertion pass | Saved key | Predicted ordered prefix | Observed prefix | Right shifts |
| ---: | --- | --- | --- | ---: |
| 1 | 23 | | | |
| 2 | 17A | | | |
| 3 | 8 | | | |
| 4 | 17B | | | |
| 5 | 42 | | | |

Draw the two recursively ordered halves and the final merge. Mark the exact equality decision that preserves A before B. Distinguish source values, scratch output, and copy-back. State why identical integer output alone cannot verify stability.

## Select by workload

Use the six scenarios in the [lab](lab.md). For each, write preparation cost, expected/worst query cost with assumptions, update cost, storage/ordering requirement, chosen method, and one rejected alternative. An O(1) known-predecessor relink is not an O(1) search for that predecessor. A heap is not a sorted snapshot.

## Preserve evidence

Record your three original test groups, commands and compiler output. Count canonical linear comparisons, binary interval decisions/final equality, insertion shifts, and merge workspace. Save one initial error and a justified correction. Everything belongs to the same Week 13 artifact.
