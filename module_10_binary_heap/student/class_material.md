# Chapter 10 Class Workbook — Heaps and Common On-Time

Name: ____________________ Date: ____________________

Keep each initial prediction. Use the [textbook](textbook.md),
[concept slides](ppt_material.md), [lab slides](ppt_lab_material.md), and
[current source](lab.c). The [investigation worksheet](investigation_worksheet.md)
provides the complete response record.

## 1. How can nearby comparisons keep the answer ready?

Place `7,3,5,1,9,4` in six complete-tree positions. Explain a parent/child
rule that keeps the smallest at position 0. State which relationships
remain unordered and how the rule changes for the largest value.

Prediction: ______________________________________________________
Correction: ______________________________________________________

## 2. Which paths do the values follow?

Start with `init_heap()` and add the same six values. Record the array
after each addition. Remove once and record the saved root, replacement,
better-child choices, and final array. Trace a singleton removal separately.
State the caller's capacity and nonempty checks.

Prediction: ______________________________________________________
Observed states: __________________________________________________
Correction: ______________________________________________________

## 3. Why visit the last parent first?

Load the original six values directly, set size 6 and minimum mode, and
trace `heapify()` from positions 2, 1, and 0. Change to maximum mode and
rebuild. Explain why a changed comparison rule alone leaves stale order.

Prediction: ______________________________________________________
Observed states: __________________________________________________
Correction: ______________________________________________________

## 4. Which pair of endpoint bounds is enough?

Load ID 0 `[1,3],[7,10]`; ID 1 `[2,5],[8,12]`; IDs 2–9 `[4,9]`.
Predict the largest selected start and smallest selected end after each
advance. Explain why discarding the earliest-ending interval cannot skip
a possible shared time. Include equality at an endpoint.

Prediction: ______________________________________________________
Observed bounds and answer: _______________________________________
Correction: ______________________________________________________

## 5. Where is the changed device now?

List both complete ID arrays and both inverse maps after initialization
and each successful advance. Show one swap and both map writes. Explain
why `_reheapify` needs a current position and why both Heaps are repaired.

Prediction: ______________________________________________________
Observed invariant checks: ________________________________________
Correction: ______________________________________________________

## 6. What does the boundary test establish?

Test immediate overlap, endpoint equality, and exhaustion. After `-1`,
identify the invalid terminal epoch and explain the reset before another
run. Do not ask unchecked integer operations to reject overflow/underflow.

Command and result: _______________________________________________
Original tests: ___________________________________________________
One-path, whole-build, and diagnostic costs: ________________________
One corrected explanation: ________________________________________
