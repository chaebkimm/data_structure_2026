# Instructor Answer Key — Chapter 7: Organizing data with links

Use the [rubric](../student/rubric.md), [investigation](../student/investigation_worksheet.md), and revised [workbook](../student/class_material.md). The investigation formats keep identical questions/scoring. The workbook follows the textbook’s seven sections; its discussion and syntax answers below support the same single submission.

## Workbook discussion and syntax answers

The opening workbook fixture follows indices 0, 2 and reads values 17, 31. Slot 1 is allocated but separate. After insertion, the indices are 0, 1, 2 and values 17, 23, 31. The link table is `(2, -1, -1)` before, `(2, 2, -1)` after the first assignment, and `(1, 2, -1)` after the second. Follow two links to reach the third logical node; physical slot 2 need not occupy that position.

The lifecycle table records: detachment returns 1 with active `0 → 2 → -1`, `free_head = 3`, data 23, next -1; recycling changes free head to 1 and next to 3; allocation returns 1, restores free head 3, and clears next to -1; only the caller assignment changes data to 8. Active links remain unchanged after detachment throughout these later steps.

The four efficiency categories are reserved pool/endpoint storage, constant iterative traversal state, constant known-node updates after the first O(C) initialization, and O(n) traversal/search. Ten slots bound simultaneous allocations; recycling permits more than ten values over time.

For the invariant discussion, require valid indices, acyclic chains, exclusive ownership, isolated detached nodes, and matching queue endpoints. Their benefit is terminating traversal, safe sharing, and FIFO. A valid numeric index alone does not prove the caller owns a node. Preserve successors, check returned indices, and detach/read/recycle in the required order.

Syntax answers: `CAPACITY` names 10 and is used in the array and initialization limits; local `static initialized` retains 1 after the first call; `(void)` means no arguments and a `void` result means no value; assigning `node = 4` through `qhead = qtail = node` leaves both endpoints 4; `return qhead == -1` returns 1 for -1 and 0 for 4.

## Inquiry and pause

Indices 0,1,2 read values 17,23,31. A back link 2→0 prevents termination. Save each acyclic list's first index. For insertion copy old successor into the new node before publishing the predecessor link; reversing makes a self-link. For first removal save data/next, advance first, isolate old next=-1, then return.

## A. Pool representation and lifecycle — 30 points

A1 (10): Initial free chain 0→1→2→3→4→5→6→7→8→9→-1, free_head=0. Global data begins zero by C static-storage initialization; pool init does not assign it. Reuse retains payload until explicit caller assignment. Never subscript -1.

A2 (10): Three new_lnode() calls return 0,1,2 and advance free head 1,2,3; each next=-1. Caller assigns 17,23,31. Ten allocations exhaust; eleventh returns -1 unchanged. Later init calls are no-ops because the static guard survives; they cannot recover capacity. Return every owned allocation or start a new process.

A3 (10): Canonical active 0,1,2, free 3–9, no detached allocations. After deletion, isolated 1 is caller-owned outside both chains. Several lists draw any available slot but keep disjoint membership and separate first indices. Missing return remains unavailable. For A/B fixture, returning A's 0 yields free 0→2→…→9; B then reallocates 0, writes 8, sets next=1, first_b=0. A is empty; B 0(8)→1(23)→-1; free head=2. A's old index is stale.

## B. Insertion and traversal — 25 points

B1 (10): From 0→2→-1 and isolated 1, write 1.next=2, then 0.next=1; final 0→1→2→-1. Require valid distinct allocated indices, non-queue predecessor, isolated unreferenced new node.

B2 (10): Traverse indices 0,1,2 and data 17,23,31; test -1 before indexing. Caller owns first. Stack prepends yield 2,1,0 and outputs 31,23,17. Guard/save/advance/isolate/recycle. Node Queue append yields qhead=0 and qtail=0,1,2; first append sets both. No helper allocates/recycles automatically.

B3 (5): Reversed writes set 0.next=1 then 1.next=1, losing 2. Bounds alone do not establish ownership or isolation.

## C. Detachment and recycling — 25 points

C1 (10): simple_delink_next_lnode_from_prev(0) returns 1, sets 0.next=2 and 1.next=-1, keeps free_head=3. Active 0→2→-1; free 3→…→9→-1; caller owns isolated 1.

C2 (10): Return writes 1.next=3 and free_head=1. Allocation returns 1, clears next=-1, restores free_head=3, and retains data=23. Caller assignment changes data to 8. Tail deletion returns -1 unchanged. Queue dequeue returns index, clears next=-1, and leaves recycling to caller. Final removal clears both endpoints. Empty returns -1 unchanged; payload -1 remains valid. Failed allocation returns -1; void append has no success result; enqueue(-1)/free(-1) are no-ops.

C3 (5): Autopsy first returns a still-referenced non-isolated node, overwriting its old successor 2 with free head 3. Later detachment makes 0.next=3 and 1.next=-1; the invalid active traversal reaches free records. Duplicate return can cycle the chain. Stale reads/writes select B's reused slot. There is no general bounds/membership validator; invalid non-sentinel indices are outside contract.

## D. Tests, costs, and revision — 20 points

D1 (12): Three original groups: allocation/exhaustion/shared pool; insertion/traversal; detach/recycle/reuse including Stack/Queue. Require exact state, retained data, repeat-init preservation, isolation, LIFO/FIFO/endpoints, empty sentinel, payload -1, and explicit recycling. Restore all ownership between tests; execute mutations outside assert. Invalid calls stay on paper.

D2 (4): Local work O(1), search/traversal O(n), the third logical node follows two links from the first, first init O(C), subsequent init O(1), reserved memory O(C) with extra next integer per slot and saved endpoints.

D3 (4): Preserve predictions, label corrections, and cite exact trace/test plus reproducible commands/output. A clean sanitizer run alone does not prove chain ownership.

## Linked applications

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

| Action in a pristine process | Result | `qhead` | `qtail` | Queue | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| allocate 0, write 17, append 0 | void | 0 | 0 | 0→-1 | 1 |
| allocate 1, write 23, append 1 | void | 0 | 1 | 0→1→-1 | 2 |
| allocate 2, write 31, append 2 | void | 0 | 2 | 0→1→2→-1 | 3 |
| `node=dequeue_lnode()` | index 0; next=-1 | 1 | 2 | 1→2→-1 | 3 |
| copy data 17; `free_lnode(0)` | caller recycles | 1 | 2 | 1→2→-1 | 0 |
| allocate 0, write 8, append 0 | void | 1 | 0 | 1→2→0→-1 | 3 |
| dequeue/copy/recycle remaining | values 23,31,8 | -1 | -1 | empty | 0 |

The final free chain is 0→2→1→3→4→5→6→7→8→9→-1. All ten slots are free; their order need not match initialization.

The Stack drain restores free 0→1→2→3→…→9→-1 in its pristine fixture. The Queue reuse fixture ends with a different all-free order. Treat exact numeric indices as fixture-dependent; repeated initialization does not restore ascending order.

Module 8 transfers the FIFO rule to an array queue of coordinates for maze BFS. It does not import Module 7's node operations; Module 7 callers still copy data and recycle removed nodes explicitly. All evidence remains one artifact within 180 minutes and A30/B25/C25/D20.
