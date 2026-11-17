# Chapter 10 Answer Key — Instructor Only

Use these answers after preserving initial predictions. Student release packaging excludes this directory. All answers refer to the unchanged three-user source and half-open intervals.

## Inquiry answers

FIFO selects by arrival, not departure. A meeting needs the latest current login before the earliest current logout. First candidate 5 fails against user 2's logout 3. Equality also fails. Advance the user whose interval has ended; if that user has no later interval, no meeting is possible. Only a new login can raise the previous maximum. The priority queue finds who leaves next without prescribing a storage method at the abstract level.

## Pause answers

1. User 2 leaves first at 3. FIFO cannot derive this from arrival order. Strict comparison leaves equal-priority older entries ahead of new ones.
2. out_id=2, front=1, rear=2, live positions 1 and 2, live count 2. The consumed index 0 is not reused by enqueue.
3. Candidate remains 12 when the new login is 11. A logout of 12 excludes meeting at 12. Exhaustion returns -1; epoch has incremented to 3 while endpoint fields retain the final interval.

## Investigation: queue operations

Initialize: front=0/rear=-1. Insert 7: [7] at 0..0. Insert 2: [2,7] at 0..1. Insert 5: [2,5,7] at 0..2. Remove 2: [5,7] at 1..2. Insert 1: [1,5,7] at 1..3. Removals return 1,5,7, leaving front=4/rear=3. pos>front prevents comparing or shifting consumed positions.

Last-digit priorities remove 21,11,1,32,22. Ties are stable because compare returns false for equal keys. After ten insertions and ten removals, front=10/rear=9. An enqueue would address index 10, outside capacity. Do not execute it. Reset then insert safely.

## Investigation: survey state

init_users chooses epoch 0 and the first pair for every user. latest_login_time returns 5. Initial sorted IDs are [2,1,0], with logout keys [3,5,6]. first_logout_id removes 2; live IDs are [1,0].

| Step | Advanced ID / epoch | Candidate | Next selected ID / logout | front / rear | Live IDs |
| --- | --- | ---: | --- | --- | --- |
| Initial | — | 5 | 2 / 3 | 1 / 2 | [1,0] |
| 1 | 2 / 1 | 5 | 1 / 5 | 2 / 3 | [0,2] |
| 2 | 1 / 1 | 7 | 0 / 6 | 3 / 4 | [2,1] |
| 3 | 0 / 1 | 8 | 2 / 7 | 4 / 5 | [1,0] |
| 4 | 2 / 2 | 9 | 1 / 8 | 5 / 6 | [0,2] |
| 5 | 1 / 2 | 12 | 0 / 9 | 6 / 7 | [2,1] |
| 6 | 0 / 2 | 12 | 0 / 13 | 7 / 8 | [2,1] |

Final current intervals are user0 [11,13), user1 [12,15), user2 [9,14). Time 12 satisfies every interval. User0's last login 11 does not lower the maximum 12. Six advances mean 3+6=9 insertions and 1+6=7 removals. These are manual trace counts; independently call survey to verify the source result.

## Correctness and test calibration

An interval ending at or before the greatest login cannot contain a common meeting for these or later intervals. Advancing it is necessary and does not lose an earlier solution. Updating only the removed ID preserves all live priorities. The loop terminates by advancing finite epochs. A successful result leaves U-1 queued IDs; it does not require an empty queue.

Initial overlap can return 0. A three-user endpoint-only fixture is user0 [0,2),[4,6),[8,10); user1 [2,4),[6,8),[10,12); user2 [0,20),[21,22),[23,24). It returns -1. A faulty strict-greater loop would return 2 immediately, when user0 has already logged out.

The unconditional candidate-update defect returns 11 for the sample even though user1 arrives at 12. The actual source returns 12. Tests should call the actual source, save/restore input, and avoid invalid operations. One original regression must identify its prediction and plausible detected defect; do not award original-test credit for the supplied smoke check.

## Costs and comparison

Insertion is O(k) for k live items, removal O(1), reset O(1). For U users and A advances, initial sorted population is O(U²), subsequent work O(AU), total O(U²+AU). A local logout scan takes O(U+AU); neither needs a heap for this chapter. Queue slots cover cumulative U+A<=UE insertions, not live membership U. With U=3/E=3, the maximum is nine slots and CAPACITY=10 suffices.

The combination oracle independently enumerates E^U selections and checks max(login)<min(logout), choosing the earliest feasible maximum. It is a test oracle, not a claimed efficient production replacement. Grade the [rubric](../student/rubric.md) as 10+20+20+15+20+15=100 within one ordinary lab artifact.
