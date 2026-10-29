# Module 8 — Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Module 7 uses a linked FIFO queue as an example of linked-list operations. Module 8 retrieves that same implementation, compares array queue representations, and uses the linked queue for both tree BFS and graph BFS. The required order is **queue → tree BFS → graph BFS** within one 180-minute lesson and one submission.

| Material | Purpose |
| --- | --- |
| [English textbook](student/textbook.md) · [Korean textbook](student/textbook_korean.md) | One flow from queue representations to tree and graph search |
| [Concept slides](student/ppt_material.md) · [Lab slides](student/ppt_lab_material.md) | Predictions and code walkthrough |
| [Class workbook](student/class_material.md) | Preserve traces and corrected explanations |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | One combined Week 8 artifact |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_08.md) | 180-minute delivery |
| [queue.c](student/queue.c) | Imports Module 7's linked FIFO; defines linear/circular array comparisons |
| [tree_bfs.c](student/tree_bfs.c) | Tree level order using the imported linked FIFO |
| [lab.c](student/lab.c) | Maze graph BFS with distances and all shortest predecessors |
| [lab_driver.c](student/lab_driver.c) | Executable checks for all three parts |

`queue.c` imports Module 8's local value adapters over Module 7's node queue and ten-node pool without redefining them. `enqueue(value)` allocates and appends a node, returning `false` without queue changes when the pool is exhausted. `dequeue()` returns the oldest value and automatically recycles its node. Check `is_empty_queue()` before dequeue; `-1` is a valid payload, not an empty-result sentinel. Internally, `enqueue_lnode` and `dequeue_lnode` exchange slot indices; BFS does not call them. The array comparisons use `enqueue_linear`, `dequeue_linear`, `is_empty_linear`, and `is_full_linear`, plus `_circular` variants. Reset front=0,rear=-1 between array experiments. Linear storage allows 25 writes per reset; circular storage holds 24 values in 25 slots. Array mutations remain unchecked.

Tree BFS reuses Module 2's exact index-linked tree. `alphabet_init(); root=tree_connect();` produces root F and processing order **F, A, G, B, C, D, E**, indices `5,0,6,1,2,3,4`. Enqueue existing left children before right children. `tree_bfs(root, order)` returns the number processed; `-1` root returns zero. The caller provides ten output slots and a valid tree without cycles or shared children.

The maze is an implicit graph: neighboring passages define edges. Start `{1,1}` reaches all 20 passages. Goal `{5,5}` has minimum distance 8 and ordered predecessors `{5,4}`, `{4,5}`. These choices represent three shortest routes. First discovery sets distance before enqueue; an equal-distance arrival appends a predecessor without enqueueing again. Before each independent BFS run, ensure every prior allocation is recycled, call the guarded initializer with `init_lnodes_pool()` and set `qhead = qtail = -1`; maze runs also call `init_info()`. Call `dequeue()` to receive the cell ID; it automatically recycles its node before BFS expands children or neighbors. Canonical maze work has 20 insertions/removals but only four pending entries at peak; all valid starts on this maze peak at six. Every completed traversal returns all ten pool slots. Allocation assertions diagnose a violated initialization/capacity precondition. The intact zero border and an interior passage start keep all neighbor reads in range. Distance 25 means unseen; ID 25 is valid.

Build from the repository root:

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

Or run `make -C module_08_graph_bfs/code core`. The sources compile directly. The maze no longer imports unused DFS code. Queue definitions are guarded so the combined driver shares one queue. Compile the driver only; it includes the other C files.

The separate checked matrix/list API in `code/include`, `starter`, `solution`, and `support` remains an optional reference. It uses sentinel 16, one predecessor, status codes, and a typed queue. Its tests and optional worksheets do not define the required lab. The [current release manifest](release/release_manifest.md) describes the combined student archive and its Module 2/7 dependencies.
