# Instructor Plan — Chapter 7: Organizing data with links

One 180-minute lesson, one [lab artifact](../student/lab.md), three original test groups, and the existing [100-point rubric](../student/rubric.md). Use the [English textbook](../student/textbook.md), [Korean textbook](../student/textbook_korean.md), and [workbook](../student/class_material.md). Preserve predictions before revealing vocabulary or answers.

## Before class

Run `make -C code core student-tests` from the module root. Prepare ten numbered slots, separate `data` and `next` columns, and cards for `first`, `free_head`, `qhead`, and `qtail`. Keep [lab.c](../student/lab.c) and presentation sources as read-only references; callers/tests belong in separate files.

The textbook's nine implementation blocks have the same operations as `lab.c`, with teaching comments and indentation. The [question outline](../student/ppt.md), [concept notes](../student/ppt_material.md), and [lab slides](../student/ppt_lab_material.md) retain their existing aliases. Use the exact source names in executable callers.

## 180-minute sequence

| Textbook section | Classroom work | Minutes |
| --- | --- | ---: |
| Thinking logically | Trace logical order, insertion, detachment, shared-pool reuse, stack LIFO, and queue FIFO | 75 |
| Calculating efficiency | Explain reserved storage, traversal state, first allocation, and searching versus relinking | 15 |
| Glossary | Name the mechanisms students have already traced | 10 |
| Invariant | State the rules, their benefit, failure cases, and preservation | 20 |
| Coding plan | Arrange caller steps before writing code | 15 |
| New C syntax explained | Trace `enum`, `static`, `void`, chained assignment, and comparison results | 10 |
| C code | Read nine blocks, execute safe tests, record evidence and a corrected prediction | 35 |
| **Total** | | **180** |

## Thinking logically

### Start from physical slots and logical order

Put 17, 23, and 31 in allocated slots 0, 1, and 2. Begin with `first = 0`, `0.next = 2`, `1.next = -1`, and `2.next = -1`. Students read indices 0, 2 and values 17, 31. Slot 1 is separate despite its physical position. Ask how many links reach the third logical node once the list has three nodes.

The fixture assumes allocated nodes so students can first focus on links. When the pool is introduced, reproduce it in a fresh process by allocating/checking three nodes, assigning their data, and connecting 2 after 0.

### Connect and detach

Insert slot 1 after 0: first copy 2 into `1.next`, then write `0.next = 1`. Reverse the writes only on paper; the result is `1.next = 1` and the original successor is lost.

Detach after 0. The result is index 1, `0.next = 2`, and `1.next = -1`. The free head remains 3. Students explain why detachment keeps the slot allocated to the caller.

### Obtain and reuse nodes

Connect all free slots once. Explain that `new_lnode()` removes the first free node, isolates it, and leaves its data unchanged. Read 23 before returning node 1; its free link becomes 3. Reallocation returns 1 with data still 23 until the caller writes 8.

Use the workbook's A/B fixture to show shared storage: A returns singleton 0, then B receives 0 and places value 8 before its existing value 23. A's old index is stale. A second initializer call preserves B's list and the free chain. Use a fresh process for independent pristine indices; an all-free chain need not be sorted.

### Use the nodes as a stack and a queue

A stack changes the caller's `first` directly. Adding 17, 23, 31 gives `2(31) → 1(23) → 0(17) → -1`. For removal, guard against empty, save data/successor, advance `first`, isolate the old node, then recycle it. Output is 31, 23, 17. There is no separate stack API.

A queue appends an allocated, isolated node at `qtail` and removes `qhead`. The first append sets both endpoints; the last removal clears both. `dequeue_lnode()` returns an index, leaves the node allocated, and clears its link. The caller reads data and recycles exactly once. A data value of `-1` remains valid.

In the workbook's queue trace, remove/read/recycle 17, then append reused slot 0 containing 8. Remaining values are 23, 31, 8. The final free chain is `0 → 2 → 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1`.

## Calculating efficiency and naming terms

Use the four textbook headings. Storage reserves ten two-integer nodes plus endpoint indices and the initialization flag. Iterative traversal uses constant extra state. Known-predecessor and endpoint updates take constant time after initialization, while finding a predecessor or traversing n nodes takes O(n). The first initialization, including a first allocation that triggers it, takes O(C); later initializer calls take O(1).

The third logical node takes two links from the first. Accessing physical slot 2 directly is different. Ten slots limit simultaneous allocations across all lists, not the total values processed through reuse.

After students preserve predictions, use the glossary to distinguish predecessor/successor, allocation/recycling, active/detached/free, and index/data. Tie LIFO and FIFO to the observed value order.

## Invariant discussion

Use the textbook's four questions:

1. State the golden rules: valid indices or `-1`, acyclic terminating chains, exactly one ownership state per slot, isolated detached nodes, and consistent queue endpoints.
2. Explain the benefit: traversal ends, lists share space safely, and endpoint updates preserve FIFO.
3. Diagnose failures: cycles, returning active or already-free nodes, losing a detached index, stale access, and an incorrect tail.
4. Explain preservation: check returned indices, save successors before overwriting links, detach before recycling, read needed data first, and use queue helpers for queued nodes.

Check invariants after complete operations. During insertion, the new node receives the old successor before the predecessor links to it. Precondition checks happen before the helper call; the source does not validate all bounds or ownership conditions.

## Coding plan and new C syntax

Ask students to plan node storage, connection/detachment, one-time pool setup, allocation/recycling, stack updates, and queue updates. Each plan must identify who sets data, who updates the first index, and who recycles a removed node.

Use the workbook syntax questions. `CAPACITY` is the integer constant 10. The local `static initialized` retains 1 after the first call. `(void)` means no arguments; a `void` result means no returned value. `qhead = qtail = node` assigns the same index to both ends. `qhead == -1` evaluates to 1 or 0.

## Code, evidence, and transfer

Read the nine textbook blocks in order, then run callers using the supplied source. Cover allocation exhaustion, repeated initialization, deletion after a tail, shared ownership, retained data, stack/queue order, empty endpoints, and explicit recycling. Test the defined `-1` no-ops and empty returns; diagnose invalid non-sentinel indices, double returns, live-node returns, and stale accesses on paper. Execute mutations outside `assert`.

Grade A30/B25/C25/D20 within one artifact. Require exact expected/observed state, three original test groups, restored ownership, compiler output, costs, and a corrected prediction. The [answer key](answer_key.md) includes workbook and syntax responses.

Module 8 transfers FIFO to array queues and tree levels, then uses a coordinate array queue for maze BFS. Optional pointer-list/DSU material remains separate; DSU is taught in [Week 14](../../module_14_prim_kruskal/week_14/instructor.md).

For release QA use the [packager](../release/prepare_student_release.py), extract separately, verify source bytes/local links, and build there. Keep faculty answers outside the student archive.
