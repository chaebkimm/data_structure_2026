# Module 07 Models — Index Links

The historical filename is retained for links. These models follow [lab.c](../student/lab.c); pointer-list/DSU references are optional.

## 1. Complete slot accounting

```text
first=0; active: 0(17) → 1(23) → 2(31) → -1
free_head=3; free: 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

All ten slots are free, active in exactly one list, or allocated/isolated with a caller. Each disjoint acyclic list saves first separately.

## 2. Share the free chain

```text
pristine allocations: A first=0: 0(17)→-1; B first=1: 1(23)→-1; free_head=2
A removes 0, sets first_a=-1, then free_lnode(0): free 0→2→3→…→9→-1
B calls new_lnode(): gets 0 with retained data 17, next=-1
B writes data=8, next=first_b, then first_b=0: B 0(8)→1(23)→-1; free_head=2
```

A's old index is stale; it does not convey ownership. Diagnose old reads/writes/double return on paper.

## 3. Preserve successor before publishing

```text
before: 0→2→-1; isolated allocation: 1
lnodes[1].next=lnodes[0].next;  // save 2
lnodes[0].next=1;              // publish
completed: 0→1→2→-1
```

## 4. Detach, recycle, allocate, assign data

```text
simple_delink_next_lnode_from_prev(0): returns 1; active 0→2→-1; 1.next=-1; free_head=3
free_lnode(1): free 1→3→4→…→9→-1; 1.data remains 23
new_lnode(): returns 1; next=-1; data still 23; free_head=3
lnodes[1].data=8: explicit caller assignment; node stays isolated
```

## 5. Caller-linked Stack

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

In that pristine fixture, free head after successive removals is 2,1,0, restoring all ten slots. Clear each old next before returning it.

## 6. Node Queue

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

## 7. Persistent initialization and invariants

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.
