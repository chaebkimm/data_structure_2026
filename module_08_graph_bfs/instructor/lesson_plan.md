# Instructor Plan — Chapter 8: Processing data in stored order

Teach one 180-minute lesson following the current PPT order: queue representations, tree levels, graph shortest distances, then the maze code. Students submit one combined artifact through the [lab](../student/lab.md), [evidence](../student/evidence_template.md), and [rubric](../student/rubric.md). The PPTs call this “10주차”; module numbering remains Chapter 8.

Read the [concept questions](../student/ppt.md), [concept summary](../student/ppt_material.md), [code questions](../student/ppt_lab.md), and [code summary](../student/ppt_lab_material.md). Use the [English textbook](../student/textbook.md), [Korean textbook](../student/textbook_korean.md), and [workbook](../student/class_material.md) for explanations and traces.

The frozen Korean textbook, **저장된 순서대로 데이터 처리하기**, sets the content and order for the English edition and this lesson. It uses `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`, with 14, 2, 15, 4, 5, 3, and 7 topics respectively. Keep its concise question-led explanations and one-term glossary. Put worked examples in the lesson activities and interactive visuals. Code excerpts use eight-space indentation and explanatory comments; the Korean manuscript, PPT sources, and supplied `lab.c` remain unchanged.

The four invariant questions cover the queue's nondecreasing distance order, why first discovery fixes a shortest distance, what is lost with a stack or unequal move costs, and how recording distance before enqueue preserves the rule. The two efficiency topics concern queue capacity and constant-time enqueue/dequeue; full traversal counts below are supporting classroom evidence. The three new C topics are nested row initializers, copying/passing/returning whole structures, and short-circuit logical OR. Review `enum`, prefix/postfix increments, `switch`/`break`, and `continue` only when reading their uses; they have already been explained in earlier chapters.

## Before class

Run `make -C module_08_graph_bfs/code lecture` from the repository root. The separate [driver](../code/tests/test_lecture.c) uses the unchanged [lab.c](../student/lab.c). The source is self-contained and has no `main`; it imports neither the Chapter 7 linked pool nor a tree implementation.

Prepare a linear array with front/rear, a paper circular version, an illustrative tree A→B/C, B→D/E, C→F, and the current 5×5 maze. All maze coordinates are `{y,x}`. Use start `{1,1}` and target `{3,3}`. Keep first predictions and label corrections. Accept drawings, numbered text, oral explanations, dictation, or instructor-run checks.

## 180-minute sequence

Each stage supplies the state needed by the next stage.

| Minutes | Live work |
| --- | --- |
| 0–15 | Recall Chapter 7 FIFO and contrast stored order with LIFO. Store three point values directly in an array. |
| 15–35 | Derive front/rear initialization, prefix/postfix changes, empty condition, and the limit on total linear writes. |
| 35–50 | Compare modulo wraparound with a reserved slot. Trace fill 24/remove two/append two in 25 slots. |
| 50–70 | Trace the illustrative tree with a queue, then compare a stack. Record each child's depth before enqueue. |
| 70–90 | Move from a tree's unique parent to graph cycles and shared destinations. Compare duplicate pending stack entries with BFS discovery-before-enqueue, then derive shortest-distance order. |
| 90–110 | Read the 5×5 maze, y/x structure, zero border, and right/left/down/up iterator. Explain nested row initializers and whole-structure copies, parameters, and returns. |
| 110–130 | Read the array queue, distance accessors, `INF`, and `init_bfs`. Explain short-circuit OR and the four invariant questions while tracing the eight-point BFS. |
| 130–140 | Five-minute three-target pause, then five minutes of preserved corrections. |
| 140–160 | Run the lecture driver. Inspect repeated starts, a wall start, isolation/restoration, and one original valid check. |
| 160–180 | Count reset/traversal/storage costs; explain conceptual previous-point reconstruction; submit one artifact. |
| **Total** | **180 minutes** |

## How do the array positions express FIFO?

Start from the question of processing data in stored order. In the actual source, `front` is the index of the first queued data and `rear` is the index of the last queued data when nonempty. They identify data positions, not the data values themselves. An empty queue has no first or last data. Derive the initial values from the first write: incrementing `rear` must reach index 0, so it starts at -1; `front` stays at 0. Enqueue increments rear before writing; dequeue reads before incrementing front. An empty queue has `front == rear + 1`, which the code checks with `front > rear`. Mutations are unchecked: require a nonempty queue before dequeue and `rear + 1 < N * N` before enqueue.

After 25 writes and removals, front 25/rear 24 is empty but no write slot remains. Explain the difference between zero pending values and unused array positions. In the paper circular version, wrapping and one reserved slot give empty `front == (rear + 1) % 25` and full `front == (rear + 2) % 25`. Fill labels 0–23, remove 0/1, append 24/25: front 2/rear 0, 24 pending, next label 2. Keep the circle comparison separate from the source's linear implementation.

## How does the tree establish levels?

Use A with B/C, B with D/E, and C with left child F. Pending queues after A/B/C are `[B,C]`, `[C,D,E]`, `[D,E,F]`. Complete order is A/B/C/D/E/F, depths 0/1/1/2/2/2. Enqueue existing left children before right children. A node's depth can accompany its queue entry; a child receives parent depth plus one. Alternatively, record the current level's pending count before adding the next level.

A valid tree has one parent per nonroot node and no cycle, so every reachable node is offered once. A graph can offer the same destination from two parents while that destination still waits. In the textbook's pending-node DFS comparison, push every neighbor that has not yet been processed, even if another entry for it already waits in the stack. The new entry is above its old copy and can move its processing earlier. On pop, skip an already processed node; otherwise mark it processed before adding its neighbors. This is a particular iterative DFS policy. Chapter 6's actual DFS is recursive and is not an implementation of this stack policy. BFS instead records first discovery before enqueue and never adds that node again.

## How does the graph record a shortest distance?

A passage is a vertex and an allowed horizontal/vertical move is an edge. Every move costs one. A point is stored directly in the queue. `bfs` begins by resetting queue positions and all 25 distances to `INF`. For a passage start, it records 0 before enqueue.

Every processed point completes all four iterator states before another `init_iter` call. The iterator variables are global. The source calls `has_next_iter` and `next_iter`; the summary slides shorten these to `has_next` and `next`. The source calls its grid `distance` and uses `N`/`INF`; the summary uses `dist` and literal 5/25. Explain the correspondence without renaming the user's files.

A wall or any finite-distance neighbor is skipped. For a first discovery, write current distance plus one and then enqueue. When `{3,1}` encounters `{3,2}`, the latter already waits at distance 3 and receives no new entry. FIFO processes each earlier layer first, so a shorter route would already have discovered any later cell.

Keep discovered and processed distinct. A discovered node already has a known distance; it can be waiting, currently under examination, or finished. A processed node has been removed and its neighbors checked. `INF` is an initial marker, not a known distance. The queue's distances stay equal or increase from front to back. With equal unit moves, first discovery therefore fixes a shortest distance. A stack or unequal move costs removes that guarantee; a later improvement would need to be propagated to neighbors rather than skipped as an old discovery.

The baseline order is `{1,1}`, `{2,1}`, `{2,2}`, `{3,1}`, `{2,3}`, `{3,2}`, `{3,3}`, `{1,3}`. Distances in that order are 0/1/2/2/3/3/4/4. The goal distance is 4. The code stores no predecessor array. Saving one previous point at first discovery and following it backward is the concept slides' extension; it is explained on paper, not required as code.

## Which assumptions make the code valid?

The start must be within indices 0–4. An in-bounds wall start is supported and leaves every distance `INF`; out-of-range coordinates are not checked. Preserve the zero border so every enqueued passage is interior and its four neighbors remain inside the array. The iterator must be initialized and queried only while `has_next_iter` is true.

The maintained queue bound is `0 <= front <= rear + 1 <= N*N`. BFS keeps recorded distances nondecreasing from front to back and queues each passage at most once. These invariants follow from the operations under the caller conditions above. Every passage enters once, so at most N×N points can be written between resets. This proves the linear queue's capacity without wraparound. Do not replace this argument with peak pending size: the baseline peaks at three but writes eight slots. Every `bfs` starts a fresh run automatically; direct queue experiments call `init_queue` themselves.

## Pause, costs, and final evidence

Use the [three-target pause](../student/cognitive_pause.md): array endpoints/wraparound, tree levels, and duplicate suppression/shortest distance. Preserve the initial answers before correction.

The baseline initializes 25 distances, inserts/removes eight points, and checks 32 candidates. Final front/rear are 8/7. The illustrative tree processes six nodes and checks twelve binary child positions. For a generalized grid, reset and reserved storage grow with all RC cells; traversal grows with reached passages P because four neighbors are checked per passage. Use O(RC) and O(P) only after these counts.

The final artifact includes a queue trace, a tree trace, the complete maze trace, actual driver output, and an explained correction. The optional checked matrix/list library and historic staged exercises remain separate reference work.
