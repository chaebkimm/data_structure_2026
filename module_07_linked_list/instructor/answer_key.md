# Instructor Answer Key — Module 07 Linked Lists

Use the [rubric](../student/rubric.md) and [investigation](../student/investigation_worksheet.md). Standard and linear formats have identical questions and scoring.

## Initial inquiry and Cognitive Pause

Follow places 0,1,2 to read 17,23,31. To remove 23, change place 0's continuation to 2 before returning place 1. To insert 1 between 0 and 2, copy 0's old continuation into 1, then point 0 at 1. Reversing writes makes 1 point to itself and loses 2 from the live chain.

An exhausted allocation returns `-1` and changes nothing. Recycling an already-free slot can make a cycle. A numeric range check cannot establish ownership.

## A. Pool representation and lifecycle — 30 points

A1 (10): Initialization zeros ten data fields and links 0→1→2→3→4→5→6→7→8→9→-1 with `free_head=0`. Data is separate from an index. Never subscript `-1`.

A2 (10): `new_lnode(17,-1)`, `(23,-1)`, `(31,-1)` return 0,1,2 and advance free head to 1,2,3. Every requested next is `-1`. The actual function stores any supplied next argument directly. Ten allocations exhaust the pool; an eleventh preserves all fields and returns `-1`.

A3 (10): Canonical active indices are 0,1,2; free indices 3–9; no detached allocations. After detachment, index 1 is caller-held and outside both chains. No overlap or cycles are valid.

## B. Insertion and traversal — 25 points

B1 (10): Starting 0→2→-1 and detached 1, first set `lnodes[1].next=2`, then `lnodes[0].next=1`. Final chain 0→1→2→-1.

B2 (10): Indices 0,1,2 yield 17,23,31. Stop on `-1` before array access. The caller owns `first`. To remove the first record, save its next, advance first, then recycle the old first.

B3 (5): Reversed writes set 0.next=1 and then 1.next=1, losing successor 2. Caller indices must be valid/distinct/allocated; inserted node must be detached from all live chains and absent from the free chain.

## C. Detachment and recycling — 25 points

C1 (10): `delete_next_lnode(0)` returns 1; 0.next becomes 2; 1.next remains 2; free head remains 3. Active chain is 0→2→-1 and free chain is 3→4→5→6→7→8→9→-1.

C2 (10): `free_lnode(1)` writes 1.next=3 and free head=1. `new_lnode(8,-1)` returns 1, writes data=8/next=-1, and restores free head=3. Reused index 1 remains detached. Tail deletion returns `-1` and changes nothing.

C3 (5): Recycling active 1 first rewrites its next to 3; deleting after 0 then follows 3 rather than 2. Active/free membership overlaps and old successor 2 is lost from the active chain. Recycling index 1 twice without allocation creates a self-link in the free chain. Range checks reject neither case.

## D. Tests, costs, and revision — 20 points

D1 (12): Require three original groups: allocation/exhaustion, insertion/traversal, and detach/recycle/reuse. Reward exact field and membership assertions with valid independent starting states, commands, and observed output. The third group includes the linked queue example: FIFO order, head/tail transitions, read-before-recycle, and slot reuse. No separate queue submission, pointer-library implementation, or DSU task is required.

D2 (4): Local allocation/recycle/link/detach and linked-queue enqueue/dequeue work is O(1). Traversal and predecessor search are O(n); initialization is O(C) for capacity C; reserved storage is O(C).

D3 (4): Preserve initial responses and cite an exact trace or test for a correction. A crash-free or sanitizer-clean run alone does not prove logical chain validity.

## Linked queue example — required list application

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

In the singleton example, raw `dequeue_lnode()` returns the slot and leaves it allocated; public `dequeue()` returns 31 and recycles that slot. Both reset endpoints. Do not double-recycle after public removal. Module 8 calls the value interface with tree/vertex IDs. The shared ten-slot pool limits simultaneous ownership, and pool initialization does not reset queue endpoints.
