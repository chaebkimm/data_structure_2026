# Instructor Technical Notes — Module 07

## Source and slide alignment

[student/lab.c](../student/lab.c) is executable truth. The [question outline](../student/ppt.md), [concept slides](../student/ppt_material.md), and [lab slides](../student/ppt_lab_material.md) teach acyclic chains, predecessor mutation, shared storage/lifecycle, Stack, then Queue. Current delivery is Week 7. Short slide aliases do not replace exact executable names.

## Initialization and allocation

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

`new_lnode(void)` calls the guarded initializer, returns -1 unchanged if exhausted, otherwise removes free_head and sets the selected node's next=-1. It does not write data. Callers must check the index before assigning payload. No successor argument remains.

`free_lnode(-1)` is a no-op. Every other argument must be a valid allocated, unreferenced, isolated node. There is no general range or membership check. Return prepends the slot to free_head and preserves data. Missing return consumes capacity; active/double return violates ownership; after return the old owner must stop accessing the slot.

## List operations

`simple_link_lnode_to_prev(prev,node)` is unchecked: valid distinct allocated indices, non-queue predecessor, unreferenced isolated inserted node. It copies the old successor into the inserted node before publishing predecessor.next. Reversing writes makes a self-link and loses the old successor.

`simple_delink_next_lnode_from_prev(prev)` requires a valid allocated non-queue predecessor. It bypasses the successor, clears its next=-1, and returns its index without recycling. After a tail it returns -1 unchanged. Neither primitive updates a caller's first index or queue endpoints.

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

## Representation invariants and API preconditions

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

Invariants describe valid completed representations. During safe insertion the old successor is temporarily referenced by the new node before it is published; the caller-held node ceases to be isolated within that operation. Teach checks at operation boundaries. Detached allocations presented to another primitive must be isolated. The two simple list operations must not mutate queued nodes because they cannot repair qhead/qtail.

## Node Queue and consumer boundary

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

Module 8's queue.c imports these primitives and defines its own checked-allocation value adapters `enqueue(value)`/`dequeue()`. Those wrappers copy payload and recycle before BFS expansion. Module 7 itself supplies neither wrapper. Module 9 allocates first, then explicitly writes data/next before publishing a bucket head.

## Validation and costs

Tests include actual source. Cover one-time initialization, retained data before caller assignment, allocation/exhaustion unchanged, two-write insertion order, isolated detachment, tail deletion, explicit recycling/reuse, caller first changes, shared-pool ownership, Queue endpoints/FIFO/empty sentinel, and repeated safe reuse. Student tests add three original groups. Keep invalid calls and [autopsy](../student/linked_list_autopsy.md) defects on paper. Sanitizers cannot establish logical ownership when wrong indices remain in bounds. Legacy solution-* tests assess a different optional library.

First initialization visits C nodes (O(C)); repeated calls return immediately (O(1)). Local allocation/recycling/relinking/endpoint work is O(1). Traversal and unknown predecessor search O(n); position i follows i links. Pool memory is O(C), with one extra integer next field per slot plus first/end indices. Recycling never ends the array's C lifetime.
