# Instructor Plan — Module 7: Linked Lists

This plan organizes one 180-minute lesson. The source of truth is [student/lab.c](../student/lab.c). Use the [English textbook](../student/textbook.md), [Korean textbook](../student/textbook_korean.md), [class workbook](../student/class_material.md), and updated [concept slides](../student/ppt_material.md).

## Required scope

Students trace acyclic lists with a saved first index and ten array records with integer next links. Follow the slides through predecessor insertion/deletion, advantages and costs, shared free-chain allocation, recycling errors, linked Stack, and linked Queue. Require the caller to retain each list's first index and establish index/membership preconditions. Stack operations are caller-side compositions of the existing primitives; the source supplies no linked `push` or `pop` function.

Submit one [lab artifact](../student/lab.md) with traces, three original test groups, build output, cost reasoning, and a corrected prediction. Use the [100-point rubric](../student/rubric.md): pool 30, insertion/traversal 25, detachment/recycling 25, tests/costs/revision 20. Linked Stack and Queue are applications inside this artifact; Module 8 imports the queue for BFS. Array queue comparisons and the BFS algorithms belong to Module 8.

## Before class

Run `make -C code core student-tests` from the module root. Prepare a ten-slot table with separate data and next fields. Preserve first predictions. Allow structured text instead of drawings.

## 180-minute sequence

| Activity | Minutes |
|---|---:|
| ArrayList comparison, acyclic chains, and saved first index | 20 |
| Predecessor insertion/deletion and safe write order | 30 |
| Shared pool, allocation/exhaustion, recycling, and stale access | 35 |
| Linked Stack: prepend, guarded removal, and LIFO trace | 25 |
| Linked Queue: append, FIFO, and empty/singleton endpoints | 35 |
| Original tests, costs, corrections, and Module 8 transfer | 35 |
| **Total** | **180** |

Begin with changing record order without moving values. Introduce formal names after students describe the necessary links. Establish that each valid list ends at `-1` with no cycle and needs a separately saved first index. For the first rewiring exercise, provide allocated slots as a fixture; the free-chain activity then explains where those slots come from.

Allocate 17,23,31 with `new_lnode(value,-1)` and expect indices 0,1,2. `link_lnode(0,2)` then `link_lnode(0,1)` forms 0→1→2→-1. `delete_next_lnode(0)` returns 1 without changing `free_head=3` or clearing `lnodes[1].next=2`. Only `free_lnode(1)` makes that slot available. `new_lnode(8,-1)` reuses it with a new value and requested next.

Give a separate example of `new_lnode(value,first)` to prepend: check success before replacing `first`. The function stores the next argument without validating membership.

Use the workbook's fresh shared-pool fixture: A owns slot 0 with 17, B owns slot 1 with 23, and the free chain begins at 2. Detach A's only node, save its value and next, set A's first to `-1`, then return slot 0. B can allocate 8 into that same slot and prepend it to B. A's saved old index 0 now identifies B's node. Reading it yields 8; writing its data or next damages B. A missing return consumes a slot; a duplicate return can create a free-chain cycle. Diagnose bad calls on paper.

For an independent Stack fixture, start `first=-1`. Prepend 17, 23, and 31 with checked allocation results. The chain is `2(31)→1(23)→0(17)→-1`. A removal first checks `first != -1`, saves the old index, its value, and its next, advances `first`, and recycles the detached slot. Values leave 31,23,17. The final first is `-1`; the final free chain starts at 0. Do not read a recycled node to recover the result.

## Misconceptions to diagnose

- Physical array position determines traversal order.
- The returned allocation index is the stored data.
- Allocation always writes next `-1`, regardless of its second argument.
- Detachment returns a slot to the free chain or clears its old next.
- An in-range slot is always safe to recycle.
- The primitives update the caller's first-node variable.
- Any old in-range index still belongs to its former list after recycling.
- Each list needs a separate fixed partition of the ten-slot pool.
- A linked Stack needs a tail search or an invented supplied push/pop API.

Ask which exact write contradicts each claim. Test invalid indices only on `free_lnode`, whose contract defines the boundary. Keep active-node recycling, duplicate recycling, and other unchecked invalid calls as paper traces.

## Cost and transfer

Count fixed field work before naming O(1). Finding an unknown predecessor or traversing `n` nodes takes O(n). Reading the i-th node takes i link steps when positions start at zero. Each record stores an extra integer next link, and each live list stores a first index. Initializing capacity `C` takes O(C); reserved pool storage is O(C). Multiple disjoint lists can draw any available slot from the common free chain, but their combined live and detached allocations cannot exceed ten.

Use an independent fresh pool and reset `head = tail = -1`. Allocate/enqueue 17, 23, and 31. Trace head/tail and the tail link. Trace raw dequeue returning an index without recycling. Then use public enqueue(value)/dequeue(): check insertion status and nonempty state; public removal returns data and recycles internally. The final removal restores both endpoints. Reuse the first returned slot behind waiting nodes to distinguish slot order from FIFO order.

Module 8 reuses this exact linked queue for tree and graph BFS. Students bring the functions and their ownership/lifecycle rules, then change the payload to a vertex ID. Ten slots bound simultaneous allocated records, while recycling permits more than ten total queue operations.

## Optional faculty references

The older pointer-list, heap-allocation hooks, unsafe lifetime autopsy, DSU, and edge-list sources remain optional. They define different APIs. DSU teaching and assessment belong to the [Week 14 plan](../../module_14_prim_kruskal/week_14/instructor.md).

## Release check

Run the [packager](../release/prepare_student_release.py), extract to a temporary directory, and run core/student tests there. Verify canonical source bytes and local Markdown links. Keep faculty answers and optional implementations outside the student archive.
