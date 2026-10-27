# Instructor Technical Notes — Module 07

## Scope and source of truth

[student/lab.c](../student/lab.c) supplies the fixed-pool linked-list lesson and its linked queue example. The updated [concept slides](../student/ppt_material.md) add explicit shared-pool lifecycle and linked Stack reasoning. Its exact names are `lnodes`, `init_lnodes_pool`, `new_lnode`, `free_lnode`, `link_lnode`, and `delete_next_lnode`. Linked Stack operations compose these functions in the caller; there is no supplied linked `push`/`pop` API. `head`, `tail`, `enqueue_lnode`, `dequeue_lnode`, and `is_empty_queue` apply the same links to FIFO. Module 8 imports this implementation for tree/graph BFS and teaches array queue alternatives. The pointer-list and DSU library under `code/` is a separate optional API.

## Pool representation and lifecycle

The ten `Linked_Node` records hold integer data and next. `init_lnodes_pool()` zeros data, links 0 through 9 ending at `-1`, and sets `free_head=0`. Before initialization `free_head=-1`; static zero fields alone do not form a valid free chain. Reinitializing over live users corrupts their membership.

`new_lnode(data_value,next_value)` removes `free_head`, advances to its old next, then stores both supplied arguments. It does not validate the supplied successor. Use next `-1` to obtain a detached record. Exhaustion checks the sentinel before indexing and preserves every field.

`free_lnode` checks only 0–9 bounds, writes the old free head into next, and installs the returned index as free head. Data remains unchanged. In-range active-node or duplicate recycling is invalid and unchecked.

Each slot is free or allocated. An allocated slot is in one live chain or held detached by the caller. Active/free chains must have no cycles or overlap. Stale links in a detached node do not establish membership. Each active list keeps a separate first index and ends at `-1`. Any list can use any free slot; no fixed partition is required. All live users share the ten-slot limit.

A detached slot that is never returned remains allocated and reduces available capacity. A returned slot's data is not erased, but its next now serves the free chain. After another allocation, both fields may serve another list. A stale index can therefore remain in bounds while reading a replacement value or corrupting another user's links. These are ownership defects without C deallocation, so sanitizers need not diagnose them. Reinitialization is allowed only when no live or detached allocation remains owned.

## List primitives and their preconditions

`link_lnode(prev,node)` requires valid distinct allocated indices and a detached inserted node. It preserves the predecessor's old successor before publishing the new link. Reversing the writes loses that successor and can create a self-link.

`delete_next_lnode(prev)` requires a valid predecessor. It bypasses and returns the successor, or returns `-1` without mutation for a tail. It leaves the detached next unchanged and does not recycle. Neither primitive finds a value or updates a caller's first-node variable.

To remove the first node, first check that the list is nonempty. Save the old index, data, and successor, advance the caller's first index, then recycle the detached old first. Never fetch the result or successor through the returned index after recycling. To prepend, `new_lnode(value,first)` can initialize the successor; install the returned index as first only after checking success. Prepending 17,23,31 and removing from the first position yields 31,23,17, implementing Stack LIFO without a tail or a search. Empty removal is skipped by a caller guard. A stored value `-1` is valid and cannot replace that guard.

## Autopsy, validation, and costs

The [student autopsy](../student/linked_list_autopsy.md) diagnoses recycling before detachment. Recycling rewrites the victim's successor to the free chain; subsequent deletion can make active nodes reach free records and lose the old active successor. These accesses may remain in bounds and evade sanitizers. Use a bounded paper trace for defective operations.

Core tests use actual lab source. Verify all ten slots, second-argument storage, exhaustion preservation, insertion order, tail deletion, detachment, exact recycling/reuse, caller-managed first removal, linked FIFO endpoints, stale-link detachment, full-pool reuse, and repeated dequeue/recycle cycles. Student tests add three original groups with shared-list pool reuse and linked Stack/Queue evidence. Use safe calls to check membership; use bounded paper traces for stale access or other invalid ownership actions. Legacy `solution-*` tests verify the optional API separately.

Initialization visits C slots, so work/storage are O(C). Allocation, recycling, known-predecessor mutations, and linked Stack first operations take O(1) additional work/storage. Searching or traversing n nodes takes O(n); reaching zero-based position i follows i next links. The representation adds one next integer per reserved node and a first index per list; the queue also stores a tail index. Sharing the pool avoids unused per-list partitions but does not increase its capacity. The fixed pool is allocated for the program's lifetime; recycling does not call C `free`.

## Linked queue application and Module 8 reuse

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot whose `next` must be `-1`; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

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
