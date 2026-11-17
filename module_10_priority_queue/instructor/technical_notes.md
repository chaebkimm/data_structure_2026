# Chapter 10 Technical Notes — Actual Source Contract

The authoritative implementation is [lab.c](../student/lab.c); the [concept](../student/ppt_material.md) and [code](../student/ppt_lab_material.md) presentations set the teaching progression. Preserve their bytes. This lab is self-contained; a driver includes it once and is the only translation unit compiled for that executable.

## Representation and preconditions

CAPACITY=10, N_USERS=3 and N_EPOCHS=3 are compile-time constants. queue stores ints; survey uses valid user IDs. front is the first live index and rear the last, with empty front==rear+1. Initialization sets 0/-1 and installs a valid strict, consistent priority comparator. It does not clear unused slots.

Before enqueue require rear+1<CAPACITY. Before dequeue require front<=rear. The functions do not validate or return error statuses. Stable ties follow from shifting only when compare(new,old) is true. Initialization resets indices, not queue contents.

Each log row holds three nonnegative, nonempty, chronological, nonoverlapping [login,logout) intervals. Require login<logout and previous logout<=next login. No validator enforces these conditions. IDs remain 0..2; standalone next_epoch calls use a currently valid epoch and stop on -1.

## Survey invariants and proof

After initialization and every successful advance, the candidate is the greatest current login. At each loop test, out_id is a user with minimum current logout; every other user appears exactly once in the live queue. Only out_id changes its endpoints while outside the queue, so the remaining priorities stay sorted.

A candidate below the minimum logout lies in every current interval. Otherwise that earliest interval ends no later than the greatest login. It cannot participate in a common meeting with the current or any later intervals of the other users. Advancing it loses no solution. Its next login cannot decrease, so max(existing candidate,new login) remains the greatest login. Exhaustion means no solution. At most U(E-1) successful advances occur; a failed next_epoch can follow and ends the run immediately.

The comparator looks through IDs to mutable users fields. Changing any still-queued user's key without reinsertion is outside this algorithm's valid procedure. Global state means experiments are sequential, not concurrent.

## Endings and repeatability

survey initializes users and queue every time but retains timelogs. It returns time 0 legitimately for an initial common interval starting at 0. Logout equality fails. On exhaustion next_epoch has incremented epoch to N_EPOCHS, leaves old endpoints, and returns -1 before accessing a new log pair. Do not call it repeatedly from that exhausted state or use epoch to index another pair. A fresh survey resets the state.

A successful return does not drain the queue: it leaves one selected ID outside and two IDs inside. Sample state is time 12, selected ID 0, front 7, rear 8, live IDs [2,1]. The three intervals are [11,13), [12,15), [9,14). Six advances account for nine enqueues and seven dequeues. The [models](../diagrams/priority_queue_models.md) give every state.

## Costs and validation

Inserting among k live items costs O(k); removal and queue reset cost O(1). Initial population can cost O(U²). With A advances, survey costs O(U²+AU), bounded by O(U²E) for E>=1. The scan implementation costs O(U+AU); this application demonstrates the priority interface rather than an asymptotic speedup.

The queue requires U+A positions since slots are not reused. At most UE positions suffice. Auxiliary storage is O(UE) for that queue and O(U) for users, excluding O(UE) input. Do not describe it as O(U) merely because at most U entries are live. Actual storage is fixed at 10 queue slots, 3 user records and 18 endpoint integers.

Core tests independently enumerate all interval combinations, taking the earliest max(login) satisfying max(login)<min(logout). This does not reuse the advancement rule. Ten thousand generated valid schedules include meetings and misses; repeated calls and explicit boundaries are checked under sanitizers. The separate comparison uses local epochs and a fresh logout scan. It tests the actual survey on identical inputs.

## Source-reference and archive boundaries

Slides use two users and arr/logs/on/off/IDS/EPOCHS/max_login_time; this package uses the lab's three users and original names. The slides' Week 12 label is recorded without rescheduling the course. The required lesson has no heap, map, graph dependency, paths or dynamic allocation. [Legacy material](../legacy/README.md) is historical and excluded from the student release.
