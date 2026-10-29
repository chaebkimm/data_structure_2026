# Stage C — Linked-List Investigation

Name: ____________________________ Date: ____________________________

Total: 100 points. Use [lab.c](lab.c), preserve predictions, then run safe traces/tests. Standard and linear formats have identical questions/scoring. Supplied operations are complete; add safe callers and original tests.

Canonical fixture in a pristine process: call `new_lnode()` three times, check indices, explicitly write 17,23,31, then `simple_link_lnode_to_prev(0,1); simple_link_lnode_to_prev(1,2);`. The caller keeps first=0. Active 0(17)→1(23)→2(31)→-1; free 3→4→5→6→7→8→9→-1. Repeated initialization is a no-op, not a reset. Use a new process or return all owned nodes between independent experiments.

## A. Pool representation and lifecycle — 30 points

### A1. Interpret the representation — 10 points

Distinguish node index, data, and -1 sentinel. Give the first free chain after initialization. Which statement initializes data: global static-storage initialization, pool initialization, allocation, or the caller's assignment? Explain retained data after reuse and safe traversal termination.

Response: ___________________________________________________________

### A2. Allocate and exhaust — 10 points

Record returned indices and free_head while creating the fixture. Explain why `new_lnode()` sets next=-1 but leaves data unchanged. In another pristine process allocate ten, then one more. Give the return and unchanged state. What does another `init_lnodes_pool()` call do while exhausted, and why does `static initialized` retain its value?

Response: ___________________________________________________________

### A3. Account for all slots — 10 points

Classify all ten slots as active, isolated allocated, or free. Explain disjoint acyclic chains and caller ownership of a detached allocation. In a pristine pool A owns 0(17), B owns 1(23), free head 2. Detach/recycle A's node, allocate it for B, write data 8, set its next to B's first, then update first_b. Give both first indices and all chains. Explain missing returns and stale ownership.

Response: ___________________________________________________________

## B. Insertion and traversal — 25 points

### B1. Insert without losing a successor — 10 points

Explain both assignments of `simple_link_lnode_to_prev(prev,node)`. For 0→2→-1 with isolated allocated 1, trace insertion after 0 and resulting values 17,23,31. State valid/distinct indices, non-queue predecessor, allocation, isolation, and absence of other incoming links as caller preconditions.

Response: ___________________________________________________________

### B2. Traverse and keep the first index — 10 points

Give canonical visited indices/data and the check before indexing. In a pristine linked Stack, allocate/check/write/set-next/update-first for 17,23,31. Give chain and LIFO output. On removal, save data/next, advance first, isolate old next=-1, then recycle. Explain that order. In a separate node-queue example allocate/write/append 17,23,31 and trace qhead/qtail, including the first append.

Response: ___________________________________________________________

### B3. Diagnose reversed writes — 5 points

Reverse insertion writes on paper. Identify the lost successor and self-link. Which caller preconditions keep an otherwise correct insertion safe?

Response: ___________________________________________________________

## C. Detachment and recycling — 25 points

### C1. Detach without recycling — 10 points

Trace `removed=simple_delink_next_lnode_from_prev(0)`. Give return, active chain, unchanged free chain, and isolated removed next. Who owns the returned node?

Response: ___________________________________________________________

### C2. Recycle, reuse, and test the tail — 10 points

Continue with `free_lnode(removed)`, then `reused=new_lnode()`, then explicit data=8. Give exact links, retained data before assignment, and membership after each step. What does deletion after tail 2 return/change? For a queue, show node-index dequeue, separate copy-data/recycle, and singleton endpoint cleanup. Explain exhausted allocation, void enqueue, defined -1 no-ops, empty dequeue, and payload -1.

Response: ___________________________________________________________

### C3. Diagnose membership violations — 5 points

Identify the earliest violated precondition in the [autopsy](linked_list_autopsy.md). Why do valid numeric indices fail to prove ownership? Explain double recycling, stale access after B reuses A's slot, and why free_lnode requires isolation. Keep invalid calls on paper, including invalid non-sentinel indices.

Response: ___________________________________________________________

## D. Tests, costs, and revision — 20 points

### D1. Three original test groups — 12 points

Add allocation/exhaustion/shared-pool, insertion/traversal, and detachment/recycling/reuse groups. Include retained data, repeated initialization unchanged, isolated removal, Stack LIFO/guards, Queue FIFO/endpoints, empty -1, caller-managed recycling, and exhaustion. Execute mutations outside assert. Return all owned nodes between experiments; compare exact state.

Response: ___________________________________________________________

### D2. Count actual work — 4 points

Count fixed local field work versus predecessor/i-th-node search and traversal. Distinguish O(C) first initialization from O(1) later calls, and count an extra next integer per slot. Reaching zero-based position i follows i links.

Response: ___________________________________________________________

### D3. Revise from evidence — 4 points

Preserve the first prediction and a labeled correction supported by an exact trace or test, with reproducible commands/output.

Response: ___________________________________________________________
