# Module 8 Lab — Processing data in stored order

Follow the frozen [Korean textbook](textbook_korean.md), **저장된 순서대로 데이터 처리하기**, its [English edition](textbook.md), and the [concept](ppt_material.md) and [code](ppt_lab_material.md) slides. Recall the stored order of Chapter 7's linked queue, then implement the same FIFO rule with an array. Trace tree levels before studying graph discovery. Submit one artifact using the [evidence template](evidence_template.md) and [rubric](rubric.md).

Read the textbook’s [Invariant](textbook.md#invariant) and [New C syntax explained](textbook.md#new-c-syntax-explained) sections alongside these traces. Explain why pending distances never decrease from front to back and why equal-cost moves make first discovery final. Relate these rules to the caller’s start, border, capacity, and nonempty conditions. Concrete examples belong to the workbook and lab; the textbook supplies the concepts.

## 1. How do the two queue positions move?

The first waiting value must leave first. In the supplied [lab.c](lab.c), when the queue is nonempty, `front` is the index of its first stored data and `rear` is the index of its last stored data. `init_queue()` sets them to 0 and -1. `enqueue(p)` writes a whole coordinate to `queue[++rear]`; `dequeue()` returns `queue[front++]`. Neither operation validates its precondition. The indices identify occupied positions, not the coordinate values themselves. An empty queue has no first or last data; any old values left in the array are outside the active queue.

Trace three coordinates `{1,1}`, `{2,1}`, `{2,2}` through enqueue and dequeue. Write every `front`, `rear`, returned point, and pending sequence. Check empty before dequeue. An enqueue requires `rear + 1 < N * N`. Do not deliberately call an operation outside those conditions.

Explain why draining does not move `rear` backward or reclaim earlier positions. After 25 writes and 25 removals, the queue is empty at `front = 25`, `rear = 24`, but another write needs a reset. This is a limit on total writes between resets, not on simultaneous waiting points alone.

For a paper circular comparison, keep the same endpoint meanings and wrap positions modulo 25. Empty is `front == (rear + 1) % 25`; full is `front == (rear + 2) % 25`. Reserve one slot so 24 values fit. Starting from `front = 0`, `rear = -1`, fill with labels 0–23, remove 0 and 1, then append 24 and 25. Predict endpoints and removal order. These circular operations are a concept exercise; the supplied maze uses the linear queue.

## 2. Why does a tree emerge one level at a time?

Use an illustrative tree with root A, A's children B/C, B's children D/E, and C's left child F. Enqueue existing children left before right after processing each node. Record the pending queue after every removal and the depth of every processed node. This is a paper trace, not a supplied tree function.

Compare a FIFO queue with a stack of pending nodes. Explain how to retain a node's depth by storing it with the queued node, or by assigning each child its parent's depth plus one. A valid tree has no cycles or shared children. Explain why its unique parent prevents repeated scheduling, and why a general graph needs a discovery record.

For the graph comparison in the concept PPT, a stack may receive another copy of an unprocessed neighbor even if that neighbor already waits below. Mark the node processed on its first pop and skip later popped copies before expanding neighbors. Explain why this differs from BFS, which marks discovery before enqueue and excludes all later copies. This describes one iterative stack method; the earlier recursive DFS implementation does not need duplicate pending entries.

## 3. How do coordinates and neighbors become C values?

The supplied maze has five rows and five columns. `struct point` stores `y` first and `x` second. Thus `{2,3}` means row 2, column 3, and accesses `maze[2][3]`. The queue stores that point directly; there is no cell-ID conversion.

Trace `init_iter((struct point){2,2})`, then four calls to `next_iter()` guarded by `has_next_iter()`. Record the returned coordinates and `state`. Each call copies `cur_point`, changes one coordinate, and increments `state`. Finish one iterator before initializing another because both iterator variables are global.

The three new syntax topics are nested braces initializing one array row at a time, copying/passing/returning a whole `struct point`, and short-circuit `||`. Explain why changing a copied point does not change `cur_point`, and why a true wall test prevents a distance read. Review `enum { N = 5 }`, `enum { INF = N * N }`, increment operators, `switch`/`break`, and `continue` from earlier chapters. Explain why an unseen marker larger than any finite shortest distance is needed. A shortest route need not repeat a cell, so at most 25 cells require at most 24 moves; 25 is a valid marker.

## 4. Why does each passage enter once?

Start at `{.y = 1, .x = 1}` and use target `{.y = 3, .x = 3}`. A call to `bfs` resets the queue and all distances itself. It then stores distance 0 at a passage start and enqueues it. No separate pool or metadata initialization is required.

For every removed point, inspect right, left, down, up. A wall is skipped. Any neighbor whose distance is already different from `INF` is also skipped, including one still waiting in the queue. A new passage receives `current distance + 1` before enqueue.

Complete the eight-point queue trace in the [workbook](class_material.md). Explain why `{3,2}` is skipped when processing `{3,1}`: it was already discovered from `{2,2}`. No second enqueue or extra predecessor record is made. Explain why FIFO ensures all distance-2 points are processed before any distance-3 point.

Record all final distances, target distance, number of reached passages, total writes/removals, peak pending count, and final endpoints. The code stores distances; it does not store a visit-order array or predecessors. A hand trace may record processing order for evidence.

## 5. How do we check the actual source?

Use the separate driver to call the unchanged lab:

```sh
make -C module_08_graph_bfs/code lecture
```

Record the command and actual output. The lab alone has no `main`; an object-only compile is also valid:

```sh
cc -std=c11 -Wall -Wextra -pedantic -c \
  module_08_graph_bfs/student/lab.c -o /tmp/module08_lab.o
```

Check repeated calls from different valid starts. `bfs` reinitializes queue positions and distances every time. A wall start such as `{0,0}` is within bounds and leaves all distances `INF`. An out-of-range start is outside the contract because `is_wall` directly indexes the array. Keep the all-zero border intact.

To inspect unreachable passages in a separate experiment, temporarily set `maze[2][1] = 0`. Start `{1,1}` is isolated, while target `{3,3}` remains an open passage with distance `INF`. Restore the cell to 1 before repeating the baseline. Make experimental changes in a driver at runtime, not in the user-owned `lab.c`.

Add one original, valid assertion or equivalent observation in a separate driver. State the expected result first. Do not modify the supplied source or PPTs.

## 6. What does the result cost and what does it omit?

Count 25 distance initializations, eight enqueues, eight dequeues, and 32 neighbor checks for the baseline. Queue operations take constant work. For a generalized grid of R rows and C columns with P reached passages, initialization takes O(RC), traversal takes O(P), and the reserved distance/queue arrays use O(RC) storage. The linear queue must cover total discoveries between resets; its three-point peak does not justify a three-slot array.

The concept slides and frozen textbook describe saving the discovering current point as the parent cell at first discovery. Follow the parent cells backward from the target to the start, then reverse the collected sequence. Explain this extension using one four-move route on paper. The supplied code does not implement it. No code extension or enumeration of every shortest route is required.

The checked matrix/list library and its staged worksheets are optional reference exercises. Its statuses, sentinel 16, and predecessor fields do not describe this lab.
