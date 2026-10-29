# Chapter 8. Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Follow the [Module 8 plan](../module_08_graph_bfs/instructor/lesson_plan.md) for one 180-minute lesson: queues 60 minutes, tree BFS 30, maze graph BFS 60, testing/cost/synthesis 30. Module 7 introduces FIFO through a linked-list example. Module 8 reuses that implementation for both BFS traversals.

The [English textbook](../module_08_graph_bfs/student/textbook.md), [Korean textbook](../module_08_graph_bfs/student/textbook_korean.md), [workbook](../module_08_graph_bfs/student/class_material.md), [concept slides](../module_08_graph_bfs/student/ppt_material.md), and [lab slides](../module_08_graph_bfs/student/ppt_lab_material.md) use the same three-part sequence. Submit once through the [lab](../module_08_graph_bfs/student/lab.md) and [rubric](../module_08_graph_bfs/student/rubric.md).

## Starting question

Requests 17, 23, 31 arrived in that order. How can we process them in arrival order? Retrieve Module 7's FIFO linked-list example and contrast its known rule with the Stack. Read [queue.c](../module_08_graph_bfs/student/queue.c) after the link/array traces.

Trace linked head/tail through empty, first insertion, and final removal. `enqueue(value)` allocates and appends a node, returning `false` without queue changes when the pool is exhausted. `dequeue()` returns the oldest value and automatically recycles its node. Check `is_empty_queue()` before dequeue; `-1` is a valid payload, not an empty-result sentinel. BFS uses those wrappers and never frees a queue node itself. The raw helper returns indices and leaves recycling to the wrapper. Array functions have distinct `_linear`/`_circular` names and remain unchecked. Initialize the otherwise unowned pool with `init_lnodes_pool()` and reset head/tail before independent BFS runs.

For the linear 25-slot queue, fill 0..24 and drain: front 25, rear 24 is both empty and full. For circular modulo 25, one reserved position leaves 24 values. Fill 0..23, remove 0/1, append 24/25: front 2, rear 0; draining gives 2..25.

## Tree board walkthrough

Reuse [Module 2's tree](../module_02_binary_tree/student/lab.c), with root F(index 5), children A/G, A→B/C, B→D/E. Enqueue the root and then enqueue existing left children before right children after processing each index. Pending after F, A, G, B is [0,6], [6,1,2], [1,2], [2,3,4]. The output F, A, G, B, C, D, E has depths 0, 1, 1, 2, 2, 3, 3.

[tree_bfs(root, order)](../module_08_graph_bfs/student/tree_bfs.c) returns 7 here and 0 for root -1. The output has room for ten indices. A valid tree has no cycles or shared children; each reached node enters once without a discovery array. Ask what changes when two graph routes reach the same waiting vertex.

## Graph board walkthrough

The maze [lab.c](../module_08_graph_bfs/student/lab.c) is graph BFS. Passages are vertices; orthogonal moves are equal-cost edges. Start (1,1), target (5,5). Trace right, left, down, up. Coordinates are{x, y}; access is [y][x]; ID is 7*y+x. ID 25 is valid, while distance 25 means unseen.

First discovery sets distance before enqueue. An equal-distance arrival appends a predecessor without another enqueue. An earlier distance is skipped. The goal distance is 8, with predecessors (5,4),(4,5). The two choices at (3,5), namely(3,4),(2,5), give three complete shortest routes. One recovered route contains nine cells/eight moves. The source records predecessors without printing routes.

Before each maze run call init_info, ensure every prior allocation is recycled, call the guarded initializer with init_lnodes_pool, and set qhead = qtail = -1. The start must be an interior passage and the zero wall border remains intact. The shared neighbor iterator completes each cell before starting another. Twenty passages enter once; the linked frontier peaks at four entries, and every supplied start peaks at most six. Public dequeue returns the cell ID and recycles its node before neighbors are added. Final head/tail are -1 and all ten pool slots return. Tree and maze include the same guarded local queue; the combined driver compiles directly without a prepared copy.

## Pause and final evidence

Use the lesson plan's three-target pause: queue boundaries/wraparound, tree order/valid-tree assumptions, and graph merge/distance/routes. Preserve original predictions and add labeled corrections. Run the [combined driver](../module_08_graph_bfs/student/lab_driver.c) and add original queue/tree/maze assertions. The separate checked matrix/list API and older staged worksheets remain optional references.

Count seven processed tree nodes/fourteen child checks and twenty maze passages/eighty neighbor checks. Separate 49-cell initialization, fixed reserved arrays, peak linked pending count versus total discoveries, array-comparison writes, and route-output work. The final explanation connects one FIFO rule to arrival order, tree levels, and shortest graph distances with a discovery record.
