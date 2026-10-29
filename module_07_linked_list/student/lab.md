# Module 07 Lab — Linked Lists

Use [lab.c](lab.c), the [textbook](textbook.md), [workbook](class_material.md), and all three slide Markdown sources: [questions](ppt.md), [concepts](ppt_material.md), and [lab slides](ppt_lab_material.md). Trace supplied operations and add safe caller/tests. Submit one Week 7 artifact.

## Build and test

From the module root:

```sh
make -C code lab-compile
make -C code core student-tests
```

PowerShell: `./code/build.ps1` and `./code/build.ps1 -StudentTests`, with `-Sanitize` where supported. Drivers include the actual lab source; compile each driver alone. Execute mutations outside `assert` so they still run when `NDEBUG` is defined.

## State, initialization, and invariants

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

`free_lnode(-1)` and `enqueue_lnode(-1)` are no-ops. Other invalid indices are outside contract; do not execute them. In-range active-node recycling, double return, and stale writes are paper diagnoses.

## 1. Allocate and link

In a pristine process, initialize and call `new_lnode()` three times, checking each returned index before writing data 17,23,31. Expect indices 0,1,2, each with next=-1, and free head 3. `new_lnode()` does not assign data. Call `simple_link_lnode_to_prev(0,2)`, then `simple_link_lnode_to_prev(0,1)`. Trace both writes and traverse values 17→23→31 from caller-owned `first=0`.

## 2. Detach, recycle, and reuse

Call `removed=simple_delink_next_lnode_from_prev(0)`. Expect index 1, active 0→2→-1, removed next=-1, and unchanged free head 3. Copy its data 23, then `free_lnode(removed)`; free chain becomes 1→3→4→5→6→7→8→9→-1. `reused=new_lnode()` returns 1, isolates it, leaves old data 23, and restores free head 3. Write data 8 explicitly. It remains detached until linked or recycled.

## 3. Boundaries and caller ownership

In another process, allocate all ten and request an eleventh. Expect `-1` with unchanged state. Calling `init_lnodes_pool()` again changes nothing, including when exhausted. Return each allocation exactly once to recover capacity. Deleting after a valid tail returns `-1` unchanged. Check only the defined sentinel no-ops; invalid non-sentinel indices are outside contract.

For first removal, guard `first != -1`, save index/data/next, advance first, isolate the old node with next=-1, then recycle. Keep each detached allocation owned until attached or returned.

## 4. Shared pool and linked Stack

In a pristine run A owns singleton 0(17), B singleton 1(23), and free head is 2. Remove A's sole node, set its first to -1, and recycle 0. `new_lnode()` returns 0 with old data 17 and next=-1. Write 8, set its next to B's first 1, then set B's first to 0. B reads 8,23. A's old index is stale; diagnose old reads/writes on paper. Repeated initialization cannot reset this live pool.

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

## 5. Linked Queue

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

In another pristine run allocate/append all ten. An eleventh `new_lnode()` returns -1; `enqueue_lnode(-1)` changes nothing. Drain, read, and recycle all ten. Also enqueue a node whose payload is -1 and distinguish that data from the empty returned index. An empty dequeue is defined and unchanged.

## Tests and evidence

Add three original groups in `code/tests/test_lab_student.c`: allocation/exhaustion with shared-pool accounting; insertion/traversal with first insertion; detachment/recycling/reuse with linked Stack and Queue. Return every owned node between experiments or use separate processes. Compare exact links, endpoints, values, ownership, and retained data.

Submit tests, compiler commands/output, [evidence](evidence_template.md), one corrected prediction, and costs. The [rubric](rubric.md) totals 100 points. Count fixed local work, O(n) search/traversal, O(C) first initialization versus O(1) later calls, and one extra integer link per slot. Pointer-list/DSU references remain optional; array queues/BFS belong to Module 8.
