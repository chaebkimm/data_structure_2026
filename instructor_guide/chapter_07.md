# Chapter 7. Organizing data with links

Use the [180-minute plan](../module_07_linked_list/instructor/lesson_plan.md), [English textbook](../module_07_linked_list/student/textbook.md), [Korean textbook](../module_07_linked_list/student/textbook_korean.md), and [workbook](../module_07_linked_list/student/class_material.md). Chapter 7 teaches acyclic lists, shared-pool reuse, caller-managed stacks, and queues of node indices. The [question outline](../module_07_linked_list/student/ppt.md), [concept notes](../module_07_linked_list/student/ppt_material.md), [lab slides](../module_07_linked_list/student/ppt_lab_material.md), and [lab.c](../module_07_linked_list/student/lab.c) remain read-only references.

## Reading and lecture flow

Follow the textbook's seven sections: Thinking logically → Calculating efficiency → Glossary → Invariant → Coding plan → New C syntax explained → C code. The workbook uses the same sections. Begin with concrete links and preserve predictions before naming terms; revisit the examples when explaining cost and invariants. The final C section contains nine small implementation blocks.

## Starting question

> If records stay in numbered slots, how can we change their reading order?

Compare array-list shifting with next-index links. After concrete descriptions name node/singly linked list. Save first separately; require every chain to terminate at -1 without revisiting a slot. Follow insertion/deletion, shared-storage benefits/costs, free-chain lifecycle errors, Stack, then Queue.

## Board walkthrough

In a pristine process initialize once. Allocate/check 0,1,2 with new_lnode(), write data 17,23,31. From 0→2→-1 with isolated 1, insertion first copies 2 into 1.next, then writes 0.next=1. Reversed assignments make a self-link. Detachment after 0 returns 1 with next=-1, active 0→2→-1, and free head unchanged at 3. Returning 1 links it before 3. Reallocation retains data 23; the caller writes 8 explicitly.

`init_lnodes_pool()` initializes links only on its first call. Its function-local `static initialized` flag survives later calls, including calls from `new_lnode()`. First initialization builds 0→1→2→3→4→5→6→7→8→9→-1 and sets `free_head=0`; it does not assign data fields. Global data begins at zero by C static-storage rules, while reused data remains until a caller writes it. Later initialization calls change nothing and cannot reset or recover an exhausted pool. Use a new process for an independent pristine fixture, or recycle every owned node before continuing; an all-free chain need not be in ascending order.

A/B fixture: A owns singleton 0(17), B 1(23), free head 2. Detach/recycle A's 0; B allocates 0, writes 8, sets next=1, then changes first_b. A's old index now selects B. Missing returns consume capacity; duplicate returns/stale writes are paper diagnoses.

## Neutral questions

- Which number identifies a slot, and which is its payload?
- Which call changes data, and which only changes links?
- Why does repeated initialization preserve live state instead of reset it?
- Which write preserves the old successor?
- Does isolated detachment already make a node free?
- Which ownership/isolation conditions must be true before recycling?
- Who changes a standalone first index, and why must old.next be cleared before return?
- How can several disjoint lists share one free chain?
- Why does an old in-range index fail to establish continuing ownership?

## Linked stack

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

## Linked queue

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

Trace reuse of returned 0 behind waiting 1/2: outputs 17,23,31,8 despite nonascending slot order. Require explicit dequeue/copy/recycle and singleton endpoint checks. Module 8 transfers FIFO to array queues and tree levels, then stores whole coordinates in a linear queue for maze BFS.

## New C syntax and code discussion

Have students explain `enum { CAPACITY = 10 };`, the persistent local `static initialized`, no-argument `(void)`, a `void` return type, `qhead = qtail = node`, and the 1-or-0 result of `qhead == -1`. Connect each syntax feature to its purpose: matching limits, preserving live state, expressing a function interface, or updating/querying queue endpoints.

Read the nine commented blocks in textbook order: storage; insertion; detachment; pool initialization; allocation; recycling; queue endpoints; enqueue; dequeue. Callers separately assign data, check returned indices, maintain a stack's first index, and recycle removed nodes.

## Invariants, costs, and final evidence

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

Ask the four invariant questions: what must remain true, what benefit the rules provide, what breaks when they fail, and how operations preserve them. Distinguish preconditions from complete-operation state.

Use the four efficiency categories: reserved pool storage, constant extra traversal state, constant known-position/endpoint updates after initialization, and linear search/traversal. First initialization is O(C), later calls O(1). The third logical node takes two links from the first; direct access to physical slot 2 is different. Each slot stores an extra next integer. Reuse increases the number of values processed over time without increasing simultaneous capacity. Require three original safe test groups and exact traces, compiler output, costs, and corrected prediction in one artifact under the [100-point rubric](../module_07_linked_list/student/rubric.md): A30/B25/C25/D20. Invalid non-sentinel inputs are outside contract. Keep mutations outside assert. Optional pointer libraries/DSU do not widen required work; DSU belongs to Week 14.
