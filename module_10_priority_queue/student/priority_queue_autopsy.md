# Chapter 10 — Find the First Wrong State

These are deliberately faulty documentation fragments, not edits to lab.c. Choose one case, predict its first wrong state, and add a regression to the same evidence artifact.

## Case A. Accepting a logout endpoint

Imagine the survey loop used candidate > earliest_logout instead of >=. Use user 0 intervals [0,2), [4,6), [8,10); user 1 [2,4), [6,8), [10,12); user 2 [0,20), [21,22), [23,24).

What would the faulty loop return initially? Which user is already offline then? Does any valid overlap exist? Predict the correct return before running the unchanged source. Explain which strict inequality should define success.

## Case B. Lowering the candidate

Imagine replacing the guarded candidate update with an unconditional assignment of the returning user's login. In the supplied trace, candidate 12 is followed by user 0's new login 11. Which other user has not arrived at 11? Give the first incorrect candidate and assert the actual result.

## Case C. Reusing space that enqueue cannot reuse

Imagine a caller assumes that ten removals from a ten-slot queue permit another enqueue without initialization. State front and rear after ten total insertions and removals. Which index would enqueue write next? Explain the precondition violation without executing it. Demonstrate safe reuse only after init_queue.

## Regression record

Original claim: __________________________________________________

First wrong state and source reason: ______________________________

Fixture / predicted result / assertion: ___________________________

A test passing under the actual source and failing under the described defect is useful evidence. Never patch lab.c to demonstrate a mutation.
