# Instructor Plan — Module 8: Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Teach queue → tree BFS → graph BFS in one 180-minute Week 8 lesson. Module 7 supplies the linked queue taught as a linked-list example. Retrieve its FIFO rule here, compare array representations, and use that original linked implementation for both BFS functions. Students submit one combined artifact using the [lab](../student/lab.md), [evidence](../student/evidence_template.md), and [rubric](../student/rubric.md).

Read the [English textbook](../student/textbook.md) or [Korean textbook](../student/textbook_korean.md), [workbook](../student/class_material.md), [concept slides](../student/ppt_material.md), and [lab slides](../student/ppt_lab_material.md). The source order is [queue.c](../student/queue.c), [tree_bfs.c](../student/tree_bfs.c), then maze [lab.c](../student/lab.c). The checked matrix/list library remains optional.

## Before class

Compile [lab_driver.c](../student/lab_driver.c) directly. It checks all required parts. No edited teaching copy is needed: the maze includes its local guarded queue and no unused DFS code. Supply the Module 2 tree and Module 7 pool at their repository-relative paths, or use the current combined student release. Keep instructor answers separate.

Prepare three board states: a linked FIFO with values 17, 23, 31; array queue[25] with front/rear; and Module 2's exact F-root tree. Prepare the current 7-by-7 maze with start (1,1) and goal (5,5). Preserve first predictions and add labeled corrections. Accept numbered text, diagrams, oral explanation, dictation, or instructor-run checks.

## 180-minute sequence

| Minutes | Required live work |
| --- | --- |
| 0–20 | Retrieve Module 7's linked-list queue using requests 17, 23, 31. Trace existing endpoints, Boolean enqueue success, and automatic public recycling; distinguish internal pool indices from returned payload IDs. |
| 20–40 | Build linear queue[25]. Trace front/rear, empty/full predicates, and 25 writes followed by draining. Explain exhausted write positions. |
| 40–60 | Trace circular modulo 25 positions, 24 usable values, and wraparound. Compare storage while preserving FIFO; check caller predicates and resets. |
| 60–90 | Reuse Module 2's F-root tree. Derive the FIFO level rule; trace pending indices, left-before-right children, F, A, G, B, C, D, E, empty/single-node cases, and valid-tree assumptions. |
| 90–110 | Treat the maze as a graph. Contrast one-parent trees with cycles/merges. Introduce discovery distance before enqueue; trace first cells from(1,1). |
| 110–130 | Trace skip/equal-distance/first-discovery branches, goal distance 8, two immediate predecessors, and three complete shortest routes. |
| 130–140 | Five-minute three-target pause below, then five minutes of labeled correction. |
| 140–150 | Map the graph trace to metadata, coordinate IDs, right/left/down/up iterator, border rules, and independent-run resets. |
| 150–165 | Run the combined driver, add one original queue/tree/maze assertion, and preserve compiler/test output. |
| 165–180 | Count queue changes, tree child checks, maze checks and initialization. Recover one route, explain output cost, and submit one artifact. |
| **Total** | **180 minutes** |

## How do we retrieve the linked-list queue?

Ask: “Requests 17, 23, 31 arrived in that order. Which request must leave first if we must preserve arrival order?” Retrieve the FIFO rule and the linked queue code already taught in Module 7. Reuse that exact implementation; array versions are storage comparisons.

`enqueue(value)` allocates and appends a node, returning `false` without queue changes when the pool is exhausted. `dequeue()` returns the oldest value and automatically recycles its node. Check `is_empty_queue()` before dequeue; `-1` is a valid payload, not an empty-result sentinel. Raw helpers still operate on indices, but BFS uses the public wrappers. Save the enqueue result before asserting it; never put the operation inside assert. Empty linked head/tail are both -1. Array mutations remain unchecked; reset front=0,rear=-1 between array comparisons.

For the circular example, fill 0..23, remove 0/1, append 24/25. front=2, rear=0 and full is true. Draining returns 2..25. The linear example can be both full and empty after 25 writes and 25 removals, because it does not reuse positions.

## How does the tree establish breadth-first order?

Use only Module 2's existing tree: F has A/G; A has B/C; B has D/E. The root is index 5. Enqueue root, then repeatedly dequeue/process and enqueue existing left/right children in that order. After F, A, G, B the pending queues are [0,6], [6,1,2], [1,2], [2,3,4]. The output is indices 5,0,6,1,2,3,4 or F, A, G, B, C, D, E. Depths never decrease:0, 1, 1, 2, 2, 3, 3.

A valid tree is acyclic and has no shared child. Therefore a reached nonroot node is offered once by its only parent. The tree function stores output indices, returns 7 for this fixture, returns 0 for root -1, and requires ten output slots. Initialize the otherwise unowned linked pool and set qhead = qtail = -1 before independent traversals. Call public `dequeue()` to obtain the tree ID after automatic recycling; then call `enqueue(child_id)` for each existing child and check its Boolean result. Ask why adding a shared child or a cycle would require a different discovery rule before moving to the graph.

## How does the graph prevent repeated scheduling?

Maze passages are vertices and orthogonal moves are edges. Every move costs one. The graph is implicit: neighbors come from four coordinate changes, not a V-by-V adjacency matrix. IDs 7*y+x encode positions, not processing order or distance. ID 25 is valid; distance 25 means unseen. Only points 0..48 are filled.

The caller initializes metadata, verifies all prior pool allocations recycled, calls the guarded initializer, then sets qhead = qtail = -1 for each run. BFS receives a payload ID from `dequeue()`, which has already recycled its node before neighbors are added. The start is an interior passage and the border remains walls. The shared iterator completes right, left, down, up for one current cell before reinitialization. First discovery stores distance and a predecessor before enqueue. A later equal-distance arrival adds a predecessor but never another queue entry. Earlier/equal-current distances are skipped.

Start (1,1) reaches 20 passages with 20 insertions/removals. The peak pending count is four; every supplied start peaks at most six. At completion head and tail are -1 and all ten pool slots are free. Goal (5,5) distance 8 has ordered predecessors (5,4),(4,5). Passage (3,5) has predecessors (3,4),(2,5). The goal's second predecessor reaches that extra choice, producing three full routes. Recover one by following prev[0] backward and reversing. The source itself records but does not print paths.

## Three-target pause

Use five minutes without tools, notes, or classmates. Ask exactly these three targets; then preserve answers before five minutes of correction.

1. **Queue state:** explain linear full-and-empty after 25 writes/drains; predict circular front/rear after filling 24, removing 2, appending 2. Checkpoint: linear front 25/rear 24, circular front 2/rear 0, 24 values pending.
2. **Tree order:** give the pending queue after F and A, the complete output, and why no discovery flag is needed under valid-tree assumptions. Checkpoint:[0,6], [6,1,2]; F, A, G, B, C, D, E; one parent and no cycles.
3. **Graph merge:** explain why (2,5)→(3,5) appends a predecessor but does not enqueue; give goal distance and total routes. Checkpoint: current distance 5, neighbor 6; distance 8; three routes via the two choices at (3,5).

## Costs and final check

Queue changes take constant work. Tree BFS processes seven nodes and checks fourteen child positions; N reached nodes give O(N) work. The public dequeue wrapper recycles each removed slot before expansion, so its capacity follows peak pending work. The tree peaks at three, the canonical maze at four, and all supplied maze starts at most six; the full ten-slot pool covers them. The driver also verifies all fully open interior starts, whose maximum is ten. Different graphs need another bound. Maze initialization visits 49 cells. Traversal removes 20 passages and checks 80 neighbor candidates; P reached passages give O(P) traversal. Grid initialization/reserved search storage are O(RC). General adjacency-list graph BFS is O(V+E). Listing all shortest routes also costs their output size.

Final question: “How does one FIFO rule produce arrival order, tree levels, and graph shortest distances, and which extra record does the graph need?” A complete answer gives the concrete states above, caller resets, and discovery-before-enqueue with retained equal-distance predecessors.
