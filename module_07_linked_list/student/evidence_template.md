# Module 07 Evidence Record

Name: ____________________ Date: ____________________ Revision: ____________________

Use [lab.c](lab.c). Preserve predictions and labeled corrections. Keep slot indices separate from payloads. State whether each independent fixture uses a new process or recycles all prior ownership.

## 1. Pool and list trace

Initialize once, allocate/check three nodes, explicitly write 17,23,31, and link 0→1→2→-1.

| Checkpoint | First | Active chain | Free head/chain | Isolated allocations | Removed/reused data/next |
| --- | --- | --- | --- | --- | --- |
| first initialization | | | | | |
| repeated initialization | | | | | |
| three allocations and links | | | | | |
| `simple_delink_next_lnode_from_prev(0)` | | | | | |
| `free_lnode(removed)` | | | | | |
| `reused=new_lnode()` | | | | | |
| explicit reused data=8 | | | | | |

Account for all ten indices with no overlap or cycles: ____________________

## 2. Insertion and traversal

Record both writes of `simple_link_lnode_to_prev(0,1)` for 0→2→-1 and isolated 1. Preserve a paper prediction for reversed writes. Identify who retains first.

Prediction / observed links / correction: ____________________

## 3. Boundaries and ownership

- Ten allocations, exhaustion, and repeated init unchanged: ____________________
- Tail deletion and empty dequeue return -1 unchanged: ____________________
- Defined `free_lnode(-1)` and `enqueue_lnode(-1)` no-ops: ____________________
- Other invalid indices are unchecked precondition violations, kept on paper: ____________________
- Missing return, double return, and active-node recycling: ____________________
- Two disjoint lists and stale A index after B reuses a slot: ____________________
- First removal saves data/next, advances first, isolates, then recycles: ____________________

## 4. Original tests and build evidence

| Group | Assertion | Expected | Observed |
| --- | --- | --- | --- |
| allocation/exhaustion/shared pool | | | |
| insertion/traversal/first insertion | | | |
| detachment/recycling/reuse with Stack and Queue | | | |

Commands/compiler: ____________________ Output: ____________________

## 5. Diagnosis, costs, and revision

Record the autopsy's first broken precondition, repaired chains, fixed local work versus O(n) search, O(C) first initialization versus O(1) later calls, extra next storage, preserved prediction, and correction supported by evidence.

Evidence: ____________________

## 6. Linked Stack

Allocate/check/write/set-next/update-first for 17,23,31. Record 2→1→0→-1 in a pristine fixture, guarded removal with explicit isolation, outputs 31,23,17, and all-free completion. There is no supplied push/pop API.

Prediction / trace / test / correction: ____________________

## 7. Linked Queue

Record checked allocation, explicit payload write, void append, node-index removal, data copy, and separate recycling. Include qhead/qtail singleton transitions, reuse behind waiting nodes, full-pool allocation -1, empty dequeue -1, a valid payload -1, and isolation after removal. Queue operations themselves never allocate or recycle. Module 8 adds its own value adapters around these node primitives.

Prediction / trace / test / correction: ____________________
