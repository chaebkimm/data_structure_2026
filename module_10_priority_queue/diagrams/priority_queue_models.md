# Chapter 10 Models — Live Queue and Current Intervals

These states follow the unchanged three-user lab. Queue cells before front are consumed storage and are not part of the live range. All intervals include login and exclude logout.

## Initial priorities

```text
user ID                 0       1       2
current interval      [5,6)   [2,5)   [1,3)
initial candidate = max(5,2,1) = 5

sorted queue positions  0  1  2
stored user IDs         2  1  0
logout keys             3  5  6
```

first_logout_id removes 2. Now out_id=2, front=1, rear=2, live IDs=[1,0]. The user ID in a queue cell is not the cell's index.

## Complete canonical timeline

Each numbered row is after updating the previous out_id, reinserting it, and removing the next earliest ID.

| State | Advanced ID / new epoch | Current intervals: user 0; user 1; user 2 | Candidate | out_id / logout | front / rear | Live IDs |
| --- | --- | --- | ---: | --- | --- | --- |
| Initial | — | [5,6); [2,5); [1,3) | 5 | 2 / 3 | 1 / 2 | [1,0] |
| 1 | 2 / 1 | [5,6); [2,5); [5,7) | 5 | 1 / 5 | 2 / 3 | [0,2] |
| 2 | 1 / 1 | [5,6); [7,8); [5,7) | 7 | 0 / 6 | 3 / 4 | [2,1] |
| 3 | 0 / 1 | [8,9); [7,8); [5,7) | 8 | 2 / 7 | 4 / 5 | [1,0] |
| 4 | 2 / 2 | [8,9); [7,8); [9,14) | 9 | 1 / 8 | 5 / 6 | [0,2] |
| 5 | 1 / 2 | [8,9); [12,15); [9,14) | 12 | 0 / 9 | 6 / 7 | [2,1] |
| 6 | 0 / 2 | [11,13); [12,15); [9,14) | 12 | 0 / 13 | 7 / 8 | [2,1] |

At success, 12 < 13. All three current intervals contain 12. There were three initial insertions plus six reinsertions, and one initial removal plus six later removals. Peak live membership is three; cumulative insertions are nine.

## Stable insertion with a live suffix

Insert 7,2,5 with smaller values first: live values become [2,5,7] at indices 0..2. Remove 2: front=1 and the live values are [5,7]. Insert 1: shift positions 2 to 3 and 1 to 2, then write 1 at position 1. The consumed position 0 is untouched. The live range is now 1..3 with values [1,5,7].

Using last-digit priority, arrivals 21,11,32,1,22 leave in order 21,11,1,32,22. A strict comparator does not move equal-priority earlier arrivals behind newer arrivals.

## Why advance the earliest logout?

```text
candidate = greatest current login
success   = candidate < smallest current logout
failure of this round: smallest logout <= candidate
```

The earliest interval has ended before every user could arrive. Discarding it cannot discard a feasible meeting. Its next interval may raise the greatest login. Other queued intervals are unchanged. Exhaustion proves no meeting; it is not another valid interval.

## Storage boundary

```text
consumed slots | current live range | unused suffix
0 .. front-1   | front .. rear      | rear+1 .. CAPACITY-1
```

Insertion needs a slot in the unused suffix. Removal grows the consumed region without growing that suffix. Initialization resets front and rear but does not clear queue values. At most U + A <= U * E insertions must fit; the actual bound is 9 <= 10.
