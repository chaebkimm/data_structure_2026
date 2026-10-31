# Module 10 Investigation — Linear Response Format

Use this alternative to [investigation_worksheet.md](investigation_worksheet.md).
The targets and evidence requirements are identical. Keep initial predictions
and add labeled corrections. Follow [lab.c](lab.c), not the optional alert API.

## A. Map the live prefix

Start with `[7,3,5,1,9,4]` and size 6 in ten reserved slots. For each position
0 through 5, list its parent, left child, and right child using `-1` where
missing. Explain the root, the lone-left parent, capacity versus size, and
inactive values remaining after `init_heap()`.

Response: ________________________________________________________

## B. Follow upward repair

Start independently with `init_heap()` and add `7,3,5,1,9,4`. For each call,
record the appended position, each tested parent, every swap, and final live
array. Explain `proper_parent(-1,-1)`, `proper_parent(2,-1)`, and
`proper_parent(-1,2)`. State which argument wins a value tie and why no
first-arrival guarantee follows.

Response: ________________________________________________________

## C. Follow downward repair

Remove the root from B's final state. Record the saved value, replacement,
new size, each better-child choice, and final array. Verify all parent/child
relationships without requiring sibling sorting. Explain how a wrong child
would break the rule. In a separate singleton run, remove once and explain
why the size-zero repair reads no missing child. Explain why removing again
is invalid.

Response: ________________________________________________________

## D. Build from the bottom and switch modes

Load `[7,3,5,1,9,4]`, size 6, minimum mode. Record arrays after repairs from
2, 1, and 0. Explain why each child's subtree is ready before its parent.
Set maximum mode and rebuild; record the array and guarded drain order.
Explain why the flag alone does not move values. Compare separate insertion,
bottom-up construction, root inspection, and a full diagnostic scan. The lab
has no supplied comparison counter or full-order checker.

Response: ________________________________________________________

## E. Compare two endpoint bounds

Load all ten IDs: ID 0 `[1,3],[7,10]`; ID 1 `[2,5],[8,12]`; IDs 2–9 `[4,9]`.
State nonnegative endpoint, one-to-five-pair, within-pair, and strictly
separated chronological input conditions. After initialization and after
each advance, list epochs 0 and 1, latest start, earliest end, and next
action. Explain the closed-interval test and why earliest-end advancement
preserves the first possible shared time.

Response: ________________________________________________________

## F. Distinguish IDs and positions

After initialization and each successful advance, list each complete ID
array and each map indexed by ID. Verify both `array[pos[id]]==id` relations
for every ID. Explain the arguments to `_proper_parent`, the arguments its
comparator receives, both map writes in a swap, and the map-based position
passed to `_reheapify`. Explain why repairing only one Heap is insufficient.
Explain the fixed-ten lone-left child and harmless `_heapify` visit at 5.

Response: ________________________________________________________

## G. Check valid boundaries

Test integer ties in both modes, empty/singleton builds, and ten guarded
integer insertions. Stop before an eleventh insertion. Test immediate
interval success with all IDs `[4,9]`; equality by changing ID 1's second
interval to `[9,12]`; and exhaustion with only `[1,3]` for ID 0 and `[4,9]`
for all others. State the terminal out-of-range epoch after exhaustion and
why time readers or repairs must wait until valid reinitialization. Explain
how another `all_on_time()` call starts epochs and maps again.

Response: ________________________________________________________

## H. Connect evidence and cost

Complete three original test groups from [lab.md](lab.md). Use independent
endpoint scans to check interval answers. State generalized costs for `n`
IDs and `r` interval advances, then distinguish those bounds from the actual
ten-ID/five-interval storage. Attach commands, output, original explanation,
first mismatch, and corrected explanation to the [evidence record](evidence_template.md).

Response: ________________________________________________________
