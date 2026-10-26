# Module 07 Lab — Linked Lists

Use the supplied [lab.c](lab.c), [textbook](textbook.md), and [class workbook](class_material.md). Trace the complete operations and add safe callers and original tests. Submit one Week 7 artifact.

## Build and test

From the module root:

```sh
make -C code lab-compile
make -C code core student-tests
```

PowerShell: `./code/build.ps1` and `./code/build.ps1 -StudentTests`. Add `-Sanitize` where supported. The tests include the actual `student/lab.c`; compile the test driver alone.

## State and caller responsibilities

The ten records are `lnodes[10]`. Each contains integer `data` and `next`. Valid indices are 0–9; `-1` means no node. Initialize with `init_lnodes_pool()` only when no live list uses the pool. Keep the first-node index in the caller.

`new_lnode(data_value,next_value)` stores both arguments and returns the first free index, or returns `-1` without changes when exhausted. Pass `-1` to create a detached node. Check the result before indexing. A supplied successor must be a valid node in the intended list or `-1`.

`link_lnode(prev,node)` requires valid, distinct allocated indices. The inserted node must be outside every active chain. `delete_next_lnode(prev)` requires a valid predecessor and returns the detached successor or `-1`. It neither recycles nor clears the returned link.

`free_lnode(node)` rejects out-of-range indices. For an in-range index the caller must establish that it is allocated and detached. Recycling an active or already-free slot corrupts the chains.

## 1. Allocate and link

Initialize. Allocate 17, 23, and 31 with second argument `-1`. Expect indices 0, 1, and 2, and `free_head=3`. Call `link_lnode(0,2)`, then `link_lnode(0,1)`. Trace both writes and traverse 17→23→31.

## 2. Detach, recycle, and reuse

Call `removed=delete_next_lnode(0)`. Expect 1, active chain 0→2→-1, and unchanged `free_head=3`. The removed node still stores `next=2`. Call `free_lnode(removed)`; expect free chain 1→3→4→5→6→7→8→9→-1. Allocate 8 with next `-1`; expect index 1 and `next=-1`. It remains detached until explicitly linked.

## 3. Check boundaries and caller ownership

In an independent experiment, allocate all ten slots and request an eleventh. Assert `-1` and unchanged fields. Deleting after a valid tail also returns `-1` without mutation. Check that `free_lnode(-1)` and `free_lnode(10)` preserve state. Diagnose double recycling and reversed insertion writes on paper.

For removing the first node, save `lnodes[first].next`, update the caller's `first`, then recycle the old first node. The provided primitives do not maintain that variable.

## 4. Apply the list to a linked queue

Use `init_lnodes_pool(); head = tail = -1;` only when no live user owns a pool slot. `enqueue(value)` allocates a detached node, appends it, and returns `true`. Pool exhaustion returns `false` without changing the pool or queue. `dequeue()` returns the oldest **value** and recycles its node internally. The caller must check `is_empty_queue()` before calling it and must not recycle the returned value as if it were a slot index.

The node helpers expose the implementation: `enqueue_lnode(index)` appends an allocated detached slot; `dequeue_lnode()` detaches and returns an index without recycling it, or returns `-1` without changes when empty. Raw callers read `lnodes[index].data` before `free_lnode(index)`. Public `dequeue()` performs those steps itself. It asserts nonempty rather than returning an empty status. With `NDEBUG`, the assertion is removed, so the caller's nonempty precondition still applies.

A queued value of `-1` is valid. It is not an empty marker in the value interface. Check the queue state, not the returned payload. Store the result of `enqueue(value)` before checking it; `assert(enqueue(value))` would remove the insertion when assertions are disabled.

In a fresh independent run, enqueue 17, 23, and 31 as values and check each boolean result. Trace endpoint transitions and the free chain inside each wrapper. `dequeue()` returns 17 and makes its old slot reusable. Enqueue 8 behind the waiting 23 and 31; the remaining output is 23,31,8. Verify ten queued values followed by a failed insertion with unchanged fields, then drain and reuse the slots.

Use a separate raw-helper experiment to show that `dequeue_lnode()` returns an index without recycling; its empty return is `-1`. Distinguish that helper from public `dequeue()`. Include a valid queued payload `-1` and check emptiness through the predicate, not through that value.

## Tests and evidence

Add three original groups in `code/tests/test_lab_student.c`: allocation/exhaustion, insertion/traversal, and detachment/recycling/reuse including the linked queue example. Use valid independent starting states. Compare exact links and values, not only program exit status.

Submit code/tests, compiler commands and output, the [evidence record](evidence_template.md), a corrected prediction, and operation counts. Follow the [rubric](rubric.md). Local relinking takes fixed work; finding a predecessor can inspect every active node.

The linked queue is a linked-list example in Module 7 and is reused for tree and graph BFS in Module 8. Array queue comparisons are Module 8 work. The allocated pointer-list and DSU reference library is optional; DSU teaching belongs to Week 14.
