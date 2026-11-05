# Module 8 — Processing data in stored order

Chapter 8 follows the current concept and code PPTs: recall FIFO, build an array queue, compare stack and queue traversal on a tree, then compute maze distances with breadth-first search. The required lesson lasts 180 minutes and produces one submission. The supplied PPTs label the lesson “10주차”; the repository keeps its Chapter 8/module 8 numbering.

| Material | Purpose |
| --- | --- |
| [English textbook](student/textbook.md) · [Korean textbook](student/textbook_korean.md) | Explain the queue → tree → graph progression |
| [Concept questions](student/ppt.md) · [Concept summary](student/ppt_material.md) | Predict queue states, level order, and shortest distances |
| [Code questions](student/ppt_lab.md) · [Code summary](student/ppt_lab_material.md) | Follow the maze, iterator, array queue, and BFS implementation |
| [Class workbook](student/class_material.md) · [Pause](student/cognitive_pause.md) | Preserve predictions and explain corrections |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | One combined artifact |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_08.md) | Teach the 180-minute lesson |
| [lab.c](student/lab.c) | Self-contained 5×5 maze and linear array queue |
| [Lecture checks](code/tests/test_lecture.c) | Run the current lab without modifying it |

The current textbook, **Processing data in stored order** / **저장된 순서대로 데이터 처리하기**, follows seven sections: `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`. The Korean manuscript was frozen by the user on 2026-11-03; see the [chapter instructions](AGENTS.md). It determines the English edition's structure and wording. The four PPT sources supply the lesson's questions and demonstrations without changing the approved Korean text.

The `Invariant` section explains nondecreasing distances in the queue, why first discovery fixes a shortest distance when every move has the same cost, what breaks that guarantee, and how recording before enqueue preserves it. New C explanations cover nested braces for two-dimensional array initialization, whole-structure copying/passing/returning, and short-circuit logical OR. Named `enum` constants, prefix/postfix increments, `switch`/`break`, and `continue` are review from earlier chapters. The textbook's efficiency section covers queue capacity and constant-time insertion/removal; concrete traversal counts remain workbook exercises.

For the graph comparison, a pending-node DFS stack may contain another copy of an unprocessed node; skip a popped copy if that node has already been processed. BFS instead records discovery before enqueue and never schedules that node again. This stack comparison is conceptual and does not describe Chapter 6's recursive implementation.

The maze stores walls as 0 and passages as 1. `struct point` stores `y` before `x`; access is `maze[p.y][p.x]`. The queue stores whole points in `queue[N * N]`, with `front = 0`, `rear = -1`, and empty condition `front > rear`. The code does not import a linked queue or tree implementation. Circular queues and tree BFS are concept exercises.

Every `bfs(start)` calls `init_bfs(start)`, resets the queue, and fills all distances with `INF = N * N = 25`. A passage start receives distance 0 and enters the queue. A wall start within the array leaves the queue empty and every distance at `INF`. Starts must be within bounds, and the zero border must remain intact. The shared iterator checks right, left, down, up. A new passage receives its distance before enqueue; every already discovered passage is skipped.

From `{.y = 1, .x = 1}`, all eight passages are reached. Target `{.y = 3, .x = 3}` has distance 4. The run initializes 25 distances, enqueues/dequeues eight points, and checks 32 neighbor candidates. Peak pending count is three; the linear queue still uses eight write positions. It ends at `front = 8`, `rear = 7`. The lab records distances only. Saving one predecessor and tracing a route backward is a conceptual extension from the slides.

Run from the repository root:

```sh
make -C module_08_graph_bfs/code lecture
```

The supplied `lab.c` has no `main`. To compile it alone, use an object build:

```sh
cc -std=c11 -Wall -Wextra -pedantic -c \
  module_08_graph_bfs/student/lab.c -o /tmp/module08_lab.o
```

The separate checked matrix/list API under `code/include`, `starter`, `solution`, and `support` remains optional. Its sentinel 16, typed circular queue, statuses, predecessor results, and staged worksheets are separate contracts. Use `lecture` to check the current slide-based lab.
