# Chapter 8. Processing data in stored order

Follow the [180-minute lesson plan](../module_08_graph_bfs/instructor/lesson_plan.md) and current PPTs. The lesson recalls FIFO from Chapter 7, builds an array queue, traces tree levels, then computes shortest distances in a maze. The slides' “10주차” heading does not change the repository's Chapter 8 numbering.

The [English textbook](../module_08_graph_bfs/student/textbook.md), [Korean textbook](../module_08_graph_bfs/student/textbook_korean.md), and [workbook](../module_08_graph_bfs/student/class_material.md) follow the [concept questions](../module_08_graph_bfs/student/ppt.md) and [code questions](../module_08_graph_bfs/student/ppt_lab.md). Submit one artifact using the [lab](../module_08_graph_bfs/student/lab.md), [evidence](../module_08_graph_bfs/student/evidence_template.md), and [rubric](../module_08_graph_bfs/student/rubric.md).

The frozen Korean textbook, **저장된 순서대로 데이터 처리하기**, governs the English edition and teaching material. Read its seven sections in order: `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`. They contain 14, 2, 15, 4, 5, 3, and 7 topics respectively. Keep the Korean manuscript and the user's PPT and lab sources unchanged. Worked examples below support the concise concept text; they are part of the same lesson and submission.

The three new C explanations are nested row initialization, whole-structure copying/parameters/returns, and short-circuit logical OR. `enum`, increments, `switch`/`break`, and `continue` are review. The four invariant questions explain nondecreasing queue distances, the benefit of first-discovery finality, the loss of that guarantee, and preservation by recording distance before enqueue.

## Which queue positions preserve stored order?

Use the actual [lab.c](../module_08_graph_bfs/student/lab.c): `queue[N*N]` stores whole points. In a nonempty queue, `front` identifies its first data’s index and `rear` identifies its last data’s index. Empty queues have neither first nor last data, even if old values remain in the array. Reset to 0/-1. Enqueue increments rear before writing; dequeue reads before incrementing front. Empty is front>rear. The maintained position bound is `0 <= front <= rear + 1 <= N*N`; a nonempty queue and an available write position are caller preconditions for the unchecked operations. After 25 writes and removals, 25/24 is empty but has no unused write position. Queue operations are unchecked.

Compare a paper circular queue with the same endpoint meanings. Modulo 25 and one reserved slot give empty `front==(rear+1)%25` and full `front==(rear+2)%25`. Fill 0–23, remove 0/1, append 24/25: front 2/rear 0, next value 2. The supplied maze remains a linear queue.

## Why does a tree emerge by level?

Use an illustrative tree A→B/C, B→D/E, C→F. Enqueue existing left children before right children. Queues after A/B/C are `[B,C]`, `[C,D,E]`, `[D,E,F]`. Output A/B/C/D/E/F has depths 0/1/1/2/2/2. Store a depth with each queued node or process a saved number of current-level entries. The valid tree has no cycle or shared child. A graph may offer the same destination while it still waits.

Tree traversal is a conceptual bridge; no supplied tree function or imported linked-node pool is required for this lesson.

For the graph comparison, distinguish BFS discovery from DFS processing. BFS skips every previously discovered neighbor, including a node still waiting. In the described pending-node stack DFS, an unprocessed neighbor may be pushed again and its newer entry can be handled before the old copy. Mark it processed on its first pop and skip later copies before expanding neighbors. This explains the concept slides' duplicate-stack question; Chapter 6's actual DFS uses recursion.

## How does the maze establish shortest distances?

The current maze is 5×5. Coordinate pairs mean `{y,x}` and index `maze[y][x]`. Start `{1,1}` and target `{3,3}`. The iterator produces right, left, down, up with `init_iter`, `has_next_iter`, and `next_iter`. Complete one point's iterator before initializing the next.

`bfs` resets the queue and fills all 25 distances with `INF=25` on each call. A passage start gets distance 0 before enqueue. Skip a wall or any finite-distance neighbor. First discovery writes current distance+1 before enqueue. When `{3,1}` checks waiting `{3,2}`, its distance is already 3, so it is skipped. FIFO processes closer layers first and makes the first assigned distance shortest.

Here every move costs one. Distances in the pending queue are nondecreasing, so a first-discovered neighbor cannot have a shorter undiscovered route. A stack or unequal move costs removes this guarantee. A later shorter distance would have to be recorded and propagated through the neighbors. A discovered node has a known distance; a processed node has also had its neighbors checked.

Processing order is `{1,1}`, `{2,1}`, `{2,2}`, `{3,1}`, `{2,3}`, `{3,2}`, `{3,3}`, `{1,3}`. Goal distance is 4. There are eight insertions/removals, 32 neighbor checks, and a peak of three pending points. Final front/rear are 8/7. The linear array uses eight write slots even with a peak of three.

The start must be inside the array and the border must remain walls. An in-bounds wall start leaves every distance `INF`. Every independent `bfs` resets itself. The concept slides' previous-point recording explains path reconstruction, but the actual lab stores distances only. One paper route is `{1,1}→{2,1}→{2,2}→{2,3}→{3,3}`.

## Which evidence closes the lesson?

Run `make -C module_08_graph_bfs/code lecture`. The [separate driver](../module_08_graph_bfs/code/tests/test_lecture.c) calls the unchanged lab, which has no main. Use the [three-target pause](../module_08_graph_bfs/student/cognitive_pause.md) for queue positions, tree levels, and graph discovery. Check baseline, reverse start, wall start, temporary isolation/restoration, and one original valid assertion outside `lab.c`.

Count six illustrative tree nodes/twelve binary child checks, then 25 maze initializations/eight processed passages/32 neighbor checks. General grid reset/storage is O(RC); traversal is O(P) for P reached passages. Keep total linear writes distinct from peak pending. The optional checked matrix/list library and historical staged worksheets remain separate references.
