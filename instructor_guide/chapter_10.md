# Chapter 10. Priority Queues and Finding a Meeting Time

## Starting question

> Everyone has several login sessions. Which user should we examine next to find the earliest time when all are online?

Expected answer: keep a candidate equal to the latest current login and examine the earliest current logout. If that user is already offline at the candidate, advance that user's interval. Stop with a meeting only when the candidate is strictly before the earliest logout.

## Source and scope

The authoritative [lab.c](../module_10_priority_queue/student/lab.c) is a sorted-array priority queue and a three-user meeting search. The [concept](../module_10_priority_queue/student/ppt_material.md) and [code](../module_10_priority_queue/student/ppt_lab_material.md) presentations guide the sequence. They remain unchanged. Their Week 12 label is recorded without rescheduling the course; the package is Chapter 10 in its existing delivery slot.

Use the matching [English](../module_10_priority_queue/student/textbook.md) and [Korean](../module_10_priority_queue/student/textbook_korean.md) textbooks. This is one ordinary lab artifact within 180 minutes, not an indexed-heap Dijkstra practical. The code is supplied complete; students predict, trace and test it.

## Board walkthrough

Recall FIFO, then derive a comparison-based next item. Insert 7,2,5 in ascending priority. Remove 2, insert 1, and show that the live range moves from indices 1..2 to 1..3 without reusing index 0. Strict comparison preserves equal-priority arrivals. Explain the callback declaration and &earlier_logout before using them.

Use the exact three-user schedule. Candidate 5 first meets user 2's logout 3. Advance IDs 2,1,0,2,1,0; candidates become 5,7,8,9,12,12. The next selected logouts become 5,6,7,8,9,13. Return 12 because 12<13. All selected intervals contain 12: [11,13),[12,15),[9,14). A new login of 11 cannot lower candidate 12.

At completion there have been nine insertions, seven removals and six successful advances. front=7, rear=8, live IDs=[2,1], selected ID=0 outside the queue. These are trace observations, not source counters. Verify them against the actual survey() call.

## Neutral questions

- What does the queue store: user IDs, positions, or times?
- What does pos > front prevent after a removal?
- Which equal-priority item moves when compare uses strict less-than?
- Does unused space before front make another insertion safe at rear+1?
- Why can a blocking interval be discarded without losing a possible meeting?
- Why must equality fail at logout?
- Why does only the removed user's state change before reinsertion?
- Which fields change when next_epoch returns -1?
- Why does success leave other IDs in the queue?
- Why does a linear logout scan have no worse asymptotic cost here?

## Contracts, costs and final check

Require valid IDs, a strict comparator, a nonempty queue before removal and space at rear+1 before insertion. Each of three users has three nonnegative nonempty chronological nonoverlapping [login,logout) intervals. Login is included; logout excluded. On exhaustion epoch increments beyond the final valid index and endpoint fields remain old. Restart through survey rather than treating exhaustion as a valid interval.

For U users and A advances, sorted insertion is O(k), removal O(1), and the complete survey O(U²+AU). The linear scan costs O(U+AU). Up to UE cumulative queue slots are needed for E intervals per user, despite at most U live entries. Actual storage is ten queue slots for at most nine writes.

Students submit one original regression with its predicted result and detected defect, the canonical trace, boundary/reset checks, actual compiler output, comparison and corrections. Use the [180-minute plan](../module_10_priority_queue/instructor/lesson_plan.md), [answer key](../module_10_priority_queue/instructor/answer_key.md), and [100-point rubric](../module_10_priority_queue/student/rubric.md). Archived Dijkstra and heap materials are not additional required work.
