# Stage C — Linked-List Investigation

Name: ____________________________  Date: ____________________________

Total: 100 points. Use [lab.c](lab.c), preserve predictions, then run safe
traces/tests. All indices are 0–9; `-1` ends a chain. Standard and linear
versions have identical questions and scoring. The code supplies its
operations; this worksheet does not add missing implementation TODOs.

Canonical list fixture, starting after `init_lnodes_pool()`, three allocations
for 17,23,31 with next argument `-1`, then `link_lnode(0,1); link_lnode(1,2);`:

| Index | Data | Next |
|---:|---:|---:|
| 0 | 17 | 1 |
| 1 | 23 | 2 |
| 2 | 31 | -1 |

The standalone list's first-node index is 0. Free slots begin at 3 and
continue 3→4→5→6→7→8→9→-1. The standalone first index belongs to the caller. Reset the pool only after finishing every live list.

## A. Pool representation and lifecycle — 30 points

### A1. Interpret the representation — 10 points

Distinguish a node index, its data, and the `-1` sentinel. Give the exact
free chain and data initialization immediately after `init_lnodes_pool()`.
Explain why traversal tests for `-1` before indexing.

Response: ___________________________________________________________

### A2. Allocate and exhaust — 10 points

Record each returned index and `free_head` while creating the canonical
fixture. Explain why supplying `-1` as the second argument gives each fresh node `next=-1` before linking.
In a separate reset, allocate all ten slots, then attempt one more.
State its return value and which state must remain unchanged.

Response: ___________________________________________________________

### A3. Account for all slots — 10 points

At the canonical fixture, classify all ten indices as active, detached,
or free. State why active/free chains cannot overlap or contain cycles.
Explain who holds responsibility for a temporarily detached allocation.

Response: ___________________________________________________________

## B. Insertion and traversal — 25 points

### B1. Insert without losing a successor — 10 points

Explain the two assignments in `link_lnode(prev,node)` and their order.
For a separate valid list 0→2→-1 and detached node 1, trace
`link_lnode(0,1)` and give all resulting links and traversal values.
What must the caller establish about both indices and node membership?

Response: ___________________________________________________________

### B2. Traverse and keep the first index — 10 points

Write the visited indices and data for the canonical fixture. Explain how to stop before indexing `-1`. Who retains the first-node index? How would the caller remove that first node safely? In a fresh linked-queue example, call value-based enqueue for 17, 23, 31. Trace `head` and `tail`, including the empty-to-singleton transition.

Response: ___________________________________________________________

### B3. Diagnose reversed writes — 5 points

Reverse the two insertion assignments on paper. Identify the first lost successor or self-link. State the caller's index and membership preconditions.

Response: ___________________________________________________________

## C. Detachment and recycling — 25 points

### C1. Detach without recycling — 10 points

Trace `removed=delete_next_lnode(0)` in the canonical fixture. State the return, active chain, unchanged free chain, and removed node's stale link.

Response: ___________________________________________________________

### C2. Recycle, reuse, and test the tail — 10 points

Continue with `free_lnode(removed)`, then `reused=new_lnode(8,-1)`. Give exact links and membership after each call. In the canonical fixture, what does `delete_next_lnode(2)` return and change? For the linked queue example, compare raw `dequeue_lnode()` with public `dequeue()`. The raw helper leaves recycling to its caller; the public wrapper returns the value and recycles internally. Show the last removal resets both endpoints. Check full insertion returns false unchanged, and explain why payload -1 is valid.

Response: ___________________________________________________________

### C3. Diagnose membership violations — 5 points

Explain why range checks cannot detect recycling an active or already-free slot. Identify the first broken rule in the [autopsy](linked_list_autopsy.md). Keep defective operations on paper.

Response: ___________________________________________________________

## D. Tests, costs, and revision — 20 points

### D1. Three original test groups — 12 points

Add allocation/exhaustion, insertion/traversal, and detachment/recycling/reuse groups, including FIFO endpoints, public value returns, automatic recycling, and exhausted-enqueue status. Record exact expected/observed states and build commands.

Response: ___________________________________________________________

### D2. Count actual work — 4 points

Count field changes for known-predecessor operations. Compare them with finding a predecessor and initializing the entire pool.

Response: ___________________________________________________________

### D3. Revise from evidence — 4 points

Preserve the first prediction and a labeled correction supported by a trace or test.

Response: ___________________________________________________________
