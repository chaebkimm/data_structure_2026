# Module 7 — Linked Lists

Read the [English textbook](student/textbook.md) or [Korean textbook](student/textbook_korean.md), then use the [workbook](student/class_material.md) and [lab](student/lab.md). Exact executable contracts come from [student/lab.c](student/lab.c).

## Slide sources and sequence

The [question outline](student/ppt.md), [concept notes](student/ppt_material.md), and [lab slides](student/ppt_lab_material.md) move from acyclic chains and a saved first index through safe insertion/deletion, shared storage and free-node lifecycle, linked Stack, and linked Queue. All three slide outlines are delivered in Module/Week 7. Lab-slide short names (`arr`, `CAP`, `link_node`, `del_next_node`, `new_node`, `free_node`) map to `lnodes`, `CAPACITY`, `simple_link_lnode_to_prev`, `simple_delink_next_lnode_from_prev`, `new_lnode`, and `free_lnode`. The executable source defines exact preconditions; slide snippets are teaching aliases.

## Required model

Ten records of `struct Linked_Node` hold integer data and next links. Indices 0–9 identify slots; `-1` ends a chain. Logical order follows links rather than neighboring array positions. Several lists share one pool, each with its own saved first index and disjoint ownership. No `malloc` or C `free` is used.

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

`new_lnode(void)` removes a free slot and sets its next to `-1`, leaving data unchanged. Check its returned index, then assign data. Exhaustion returns `-1` unchanged. `simple_link_lnode_to_prev(prev,node)` inserts an isolated allocation after a valid distinct allocated non-queue predecessor. `simple_delink_next_lnode_from_prev(prev)` bypasses and isolates the successor, returning its index (or `-1` after a tail); it does not recycle.

`free_lnode(-1)` does nothing. Every other input must be in range, allocated, unreferenced, and isolated. There is no general range or membership check. Double return, recycling live nodes, and stale accesses are invalid. A missing return consumes shared capacity.

## Invariants

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

## Linked applications and evidence

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

Submit one [lab artifact](student/lab.md) with exact-state traces, three original test groups, compiler output, cost reasoning, and a corrected prediction. Follow the [100-point rubric](student/rubric.md) and [180-minute plan](instructor/lesson_plan.md). From the module root run `make -C code core student-tests`; see the [release manifest](release/release_manifest.md).

Known-predecessor relinking and queue/Stack endpoint work are O(1). Finding a predecessor or the i-th node can visit O(n) nodes. The first pool initialization is O(C); later calls are O(1). Each pool slot reserves one extra integer next link.

Module 8 reuses the node queue for tree/graph BFS; callers copy the payload and recycle the detached node. Array queue comparisons belong there. The separate pointer-list/DSU library is optional; DSU is taught in [Week 14](../module_14_prim_kruskal/week_14/README.md).
