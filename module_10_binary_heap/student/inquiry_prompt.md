# Module 10 Inquiry — Keep an Extreme Value Ready

Name: ____________________ Date: ____________________

Keep each first prediction. Add a labeled correction after running the
[current lab](lab.c). Initially reason about the problem before reading
implementation details. Use this prompt or its [linear version](inquiry_prompt_linear.md).

## Which request should leave first?

Six requests have urgency numbers `7,3,5,1,9,4`. Smaller numbers should be
handled sooner. Write their required removal order. If larger numbers
instead mean more urgent, how does the order change?

Prediction: ______________________________________________________

## How can the next request stay in one place?

An unsorted array can scan every live request to choose the smallest.
Describe what work repeats after each removal. Could nearby relationships
keep the smallest at position 0 without sorting every position?

Prediction: ______________________________________________________

Place the six values into positions with these relationships:

| Upper position | Immediately lower positions |
| ---: | --- |
| 0 | 1, 2 |
| 1 | 3, 4 |
| 2 | 5 |

State a rule between each upper position and its children. Explain why
that rule makes position 0 an answer. Does the rule determine sibling order?

Prediction: ______________________________________________________

## Which path needs repair after a change?

A new value first occupies the next free position. Describe which nearby
comparisons could move it toward position 0. After removing position 0,
move the final value into the opening. Which child should it compare with?
What happens when only one child exists?

Prediction: ______________________________________________________

## Can one ordering answer two questions?

Ten devices each have a list of on-intervals. We need the first time all ten
are on. For a selected interval from each device, which two endpoint values
are enough to decide whether all ten overlap? Include the case where an
on-time equals an off-time.

Prediction: ______________________________________________________

Use ID 0 with `[1,3],[7,10]`, ID 1 with `[2,5],[8,12]`, and IDs 2 through 9
with `[4,9]`. Predict which interval must advance first, then next. Explain
why a device's identity and its location in a rearranged array are different.

Prediction: ______________________________________________________

## What must the caller check?

The source reserves ten integer slots. Predict the conditions needed before
insertion and removal. These operations have no full/empty rejection path.
Write the invalid calls as explanations; do not execute them.

Prediction: ______________________________________________________

One unanswered question: __________________________________________

Correction and evidence: __________________________________________
