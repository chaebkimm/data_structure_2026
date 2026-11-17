# Chapter 10 — Investigate the Actual Priority Queue

Use the unchanged [lab.c](lab.c). Predict before running; record observations separately. All time ranges include login and exclude logout.

## A. Trace insertion and live positions

Initialize with a strict smaller-integer comparator. Insert 7, 2, 5; remove once; insert 1; remove the remaining values. For every operation record front, rear, live positions and values, returned value, and shifted items. What does the condition pos > front prevent after the first removal?

Prediction: _____________________________________________________

Observation and revision: ________________________________________

## B. Explain ties and capacity

Use values 21, 11, 32, 1, 22 with priority given by the last digit (smaller first). Predict removal order. Explain which strict comparison preserves equal-priority arrivals. After ten total insertions without initialization, can a new enqueue be safe merely because most items were removed? State the required index check without executing an invalid call.

Prediction: _____________________________________________________

Observation and revision: ________________________________________

## C. Trace initialization and IDs

With the supplied three-user logs, call init_users, latest_login_time, and first_logout_id. Record all users' epoch/login/logout fields, the initial candidate, the sorted IDs and corresponding logout keys, the removed ID, and the remaining live range. Explain why a queue position is not a user ID.

Prediction: _____________________________________________________

Observation and revision: ________________________________________

## D. Trace the meeting search

Fill each row after advancing the removed user, raising the candidate if needed, reinserting that user, and removing the next earliest logout. Also record front, rear, and live IDs. Continue until success or exhaustion.

| Step | Advanced ID | New epoch / login / logout | Candidate | Next out ID / logout | front / rear / live IDs |
| --- | --- | --- | --- | --- | --- |
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |
| 5 | | | | | |
| 6 | | | | | |

Compare your trace's final candidate with an independent call to survey(). Count insertions, removals and successful advances manually; these are not counters exported by the source.

## E. Justify the rule

Why is the candidate the greatest current login? Why must an interval ending at or before that time be replaced? Why can changing only the removed user's fields preserve the queued order? Explain why a new login of 11 cannot lower an existing candidate of 12.

Response: _______________________________________________________

## F. Check endings and resets

Check initial overlap, contact at an excluded logout endpoint, no overlap, tied logouts, and repeated survey calls. Trace next_epoch on the final interval: which field increments, which fields retain old values, and when must the caller stop? Restore the sample after every custom-log experiment.

Response: _______________________________________________________

## G. Compare and submit

Run core, student-tests, and comparison. Explain the independent interval-combination oracle and the separate scan implementation. State the per-operation costs, total O(U² + AU) work, and the cumulative insertion bound U * E. Add one original regression and identify the plausible defect it catches. Keep predictions and corrections in the same evidence artifact.

Response: _______________________________________________________
