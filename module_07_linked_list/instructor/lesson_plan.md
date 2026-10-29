# Instructor Plan — Module 7: Linked Lists

One 180-minute lesson, one [lab artifact](../student/lab.md), three original test groups, and the [100-point rubric](../student/rubric.md). Use exact [lab.c](../student/lab.c), bilingual [textbook](../student/textbook.md)/[Korean textbook](../student/textbook_korean.md), [workbook](../student/class_material.md), and all three slide sources: [question outline](../student/ppt.md), [concepts](../student/ppt_material.md), [lab slides](../student/ppt_lab_material.md).

The slide outlines are delivered in Week 7. Lab-slide short aliases map to current source names as shown in the [module README](../README.md). Preserve predictions before revealing vocabulary/answers.

## Before class

Run `make -C code core student-tests` from the module root. Prepare ten slots with distinct data/next columns and separate caller first indices, free_head, qhead/qtail. For pristine independent examples use separate processes; otherwise recycle every owned allocation and follow the actual free-chain order.

## 180-minute sequence

| Activity | Minutes |
| --- | ---: |
| ArrayList comparison, acyclic chains, saved first index | 20 |
| Safe predecessor insertion/deletion | 30 |
| Shared pool, one-time initialization, allocation/recycling/stale access | 35 |
| Caller-linked Stack and LIFO | 25 |
| Node Queue, FIFO, empty/singleton endpoints | 35 |
| Original tests, costs, correction, Module 8 transfer | 35 |
| **Total** | **180** |

Begin with changing order without moving values. Ask why a chain needs a saved start and termination rule. Provide allocated isolated fixture nodes for first rewiring; then explain how the free chain supplies them. Name the invariant and precondition after the concrete rules emerge.

## Board fixtures and exact behavior

In a pristine process allocate/check three indices 0,1,2 and explicitly write 17,23,31. `simple_link_lnode_to_prev(0,2)` then `(0,1)` forms 0→1→2→-1. Copy the old successor before publishing the new link. Reversed writes create 1.next=1.

`simple_delink_next_lnode_from_prev(0)` returns 1, sets 0.next=2 and 1.next=-1, leaving free head 3. Copy data before `free_lnode(1)`. Allocation reuses 1 with retained data 23 and next=-1; only the caller's assignment changes data to 8.

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

For shared storage, A owns singleton 0(17), B 1(23), free head 2. Detach/recycle A's node; B allocates 0, writes 8, sets next=1, and makes 0 its first. A's former index is stale. Diagnose stale writes, live-node return, duplicate return, and missing return on paper.

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

Use the workbook's FIFO reuse trace. The final free chain is 0→2→1→3→4→5→6→7→8→9→-1; all-free does not mean sorted slots.

## Rules and misconceptions

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

Diagnose claims that allocation writes data, initialization resets, detachment recycles, dequeue returns a value, append allocates, any in-range slot is recyclable, or old indices retain ownership. Invalid non-sentinel indices are unchecked; do not run them. Test defined -1 no-ops, tail deletion, and empty dequeue instead. Execute mutations outside assert.

## Costs, evidence, and transfer

Known-position relinking and endpoint operations take O(1); predecessor search/traversal O(n); reaching position i follows i links. First initialization O(C), later calls O(1); pool storage O(C), with one extra next integer per slot and saved endpoints. Shared storage avoids fixed partitions without increasing ten-slot capacity.

Grade A30/B25/C25/D20 inside one artifact. Require exact expected/observed state, three original groups, restored ownership, compiler output, costs, and corrected prediction. Module 8 adds local value adapters around these raw node operations, then uses FIFO for tree/graph BFS and compares array queues. DSU/optional pointer libraries remain [Week 14](../../module_14_prim_kruskal/week_14/instructor.md) references.

For release QA run the [packager](../release/prepare_student_release.py), extract separately, verify source bytes/local links, and build there. Keep faculty answers outside the archive.
