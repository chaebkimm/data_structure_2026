# Instructor Plan — Module 7: Linked Lists

This plan organizes one 180-minute lesson. The source of truth is [student/lab.c](../student/lab.c). Use the [English textbook](../student/textbook.md), [Korean textbook](../student/textbook_korean.md), [class workbook](../student/class_material.md), [concept slides](../student/ppt_material.md), and [lab slides](../student/ppt_lab_material.md).

## Required scope

Students trace ten array records with integer next links. Teach the free chain, two-argument allocation, exhaustion, insertion after a known predecessor, traversal, detachment, recycling, and reuse. Apply those operations to a linked queue with saved head and tail. Require the caller to retain the first-node index and establish index/membership preconditions.

Submit one [lab artifact](../student/lab.md) with traces, three original tests, build output, cost reasoning, and a corrected prediction. Use the [100-point rubric](../student/rubric.md). The linked queue is a linked-list example here; Module 8 imports it for BFS. Array queue comparisons and the BFS algorithms belong to Module 8.

## Before class

Run `make -C code core student-tests` from the module root. Prepare a ten-slot table with separate data and next fields. Preserve first predictions. Allow structured text instead of drawings.

## 180-minute sequence

| Activity | Minutes |
|---|---:|
| ArrayList comparison and index-linked order | 20 |
| Free-chain allocation and next argument | 35 |
| Predecessor insertion and detachment | 35 |
| Recycling, exhaustion, and reuse | 30 |
| Linked queue as a linked-list example | 35 |
| Tests, costs, corrections, and Module 8 transfer | 25 |
| **Total** | **180** |

Begin with changing record order without moving values. Introduce formal names after students describe the necessary links.

Allocate 17,23,31 with `new_lnode(value,-1)` and expect indices 0,1,2. `link_lnode(0,2)` then `link_lnode(0,1)` forms 0→1→2→-1. `delete_next_lnode(0)` returns 1 without changing `free_head=3` or clearing `lnodes[1].next=2`. Only `free_lnode(1)` makes that slot available. `new_lnode(8,-1)` reuses it with a new value and requested next.

Give a separate example of `new_lnode(value,first)` to prepend: check success before replacing `first`. The function stores the next argument without validating membership.

## Misconceptions to diagnose

- Physical array position determines traversal order.
- The returned allocation index is the stored data.
- Allocation always writes next `-1`, regardless of its second argument.
- Detachment returns a slot to the free chain or clears its old next.
- An in-range slot is always safe to recycle.
- The primitives update the caller's first-node variable.

Ask which exact write contradicts each claim. Test invalid indices only on `free_lnode`, whose contract defines the boundary. Keep active-node recycling, duplicate recycling, and other unchecked invalid calls as paper traces.

## Cost and transfer

Count fixed field work before naming O(1). Finding an unknown predecessor or traversing `n` nodes takes O(n). Initializing capacity `C` takes O(C); reserved pool storage is O(C).

Use an independent fresh pool and reset `head = tail = -1`. Allocate/enqueue 17, 23, and 31. Trace head/tail and the tail link. Trace raw dequeue returning an index without recycling. Then use public enqueue(value)/dequeue(): check insertion status and nonempty state; public removal returns data and recycles internally. The final removal restores both endpoints. Reuse the first returned slot behind waiting nodes to distinguish slot order from FIFO order.

Module 8 reuses this exact linked queue for tree and graph BFS. Students bring the functions and their ownership/lifecycle rules, then change the payload to a vertex ID. Ten slots bound simultaneous allocated records, while recycling permits more than ten total queue operations.

## Optional faculty references

The older pointer-list, heap-allocation hooks, unsafe lifetime autopsy, DSU, and edge-list sources remain optional. They define different APIs. DSU teaching and assessment belong to the [Week 14 plan](../../module_14_prim_kruskal/week_14/instructor.md).

## Release check

Run the [packager](../release/prepare_student_release.py), extract to a temporary directory, and run core/student tests there. Verify canonical source bytes and local Markdown links. Keep faculty answers and optional implementations outside the student archive.
