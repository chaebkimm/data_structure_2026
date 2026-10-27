# Module 7 — Linked Lists

The required source is [student/lab.c](student/lab.c). Read the [English textbook](student/textbook.md) or [Korean textbook](student/textbook_korean.md), then use the [class workbook](student/class_material.md), [concept slides](student/ppt_material.md), and [lab](student/lab.md).

The slides move from an acyclic chain and its first node to insertion/deletion, shared storage and its costs, free-node management, a linked stack, and a linked queue. The textbook and activities follow that progression.

## Required Week 7 model

Ten records in `struct Linked_Node lnodes[10]` hold integer `data` and integer `next`. Indices 0–9 identify nodes; `-1` ends a chain. Logical order follows links rather than adjacent array positions. Each active list is acyclic, with its first index stored separately. Several lists can share the pool, but each allocated slot belongs to one list or a caller as a detached allocation. This lab uses neither `malloc` nor C's `free`.

`init_lnodes_pool()` builds the free chain. `new_lnode(data_value,next_value)` takes its first slot, writes both supplied fields, and returns its index. Exhaustion returns `-1` without changes. Use next `-1` for a detached node and check every allocation result before indexing.

`link_lnode(prev,node)` inserts an allocated detached node after a valid distinct predecessor. `delete_next_lnode(prev)` bypasses and returns the successor, or returns `-1` when none exists. It neither recycles nor clears the removed node's next field. The caller retains and updates the first-node index.

`free_lnode(node)` prepends a detached allocated slot to the free chain. It rejects out-of-range indices but cannot detect recycling a live node or returning the same node twice. A detached slot omitted from the free chain cannot be allocated again. After recycling, its old owner must stop using the slot: its `next` now serves the free chain, and another list can receive it. Initialize the pool only when no user owns an active or detached allocation.

## Learning targets and evidence

Trace active/free chains and detached allocations. Apply the list first to a LIFO stack by inserting/removing at a caller-owned `first`, then to a FIFO queue by keeping `head` and `tail`. Stack callers use the existing node primitives; the lab supplies no separate stack API. Preserve the old first, successor, and payload before recycling. Verify exhaustion, tail deletion, shared-pool reuse, and empty/singleton transitions. Submit one [lab artifact](student/lab.md) with exact-state traces, three original test groups, compiler output, and one corrected explanation. The [rubric](student/rubric.md) and [180-minute instructor plan](instructor/lesson_plan.md) cover both applications.

From the module root, run `make -C code core student-tests`. The [release manifest](release/release_manifest.md) describes the self-contained student package.

Known-predecessor mutation takes fixed work. Finding that predecessor or traversing `n` live nodes can inspect all `n`. Initialization visits all ten records.

## Optional reference library

The separate pointer-list and DSU library remains under `code/`. Its headers and explicit reference targets define a different API with heap allocation and its own tests. Those contracts do not replace `student/lab.c`. DSU is introduced with Kruskal in [Week 14](../module_14_prim_kruskal/week_14/README.md).

## Transfer to Module 8

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot whose `next` must be `-1`; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

[Module 8](../module_08_graph_bfs/README.md) imports this source and uses public enqueue/dequeue with tree and graph IDs. Array queue comparisons and BFS are taught there. The two scalar wrappers keep node allocation/recycling out of those BFS loops.
