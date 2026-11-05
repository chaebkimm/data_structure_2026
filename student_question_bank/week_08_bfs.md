# Week 8 — Processing data in stored order: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Retrieve the FIFO rule from Chapter 7, implement a linear array queue, and
compare circular wraparound conceptually. Use a hand-worked tree to explain
level order before tracing the current 5×5 maze. Queue traces, tree levels,
maze distances, checks, and explanations form **one Week 8 artifact**.

The current `lab.c` is self-contained. It stores `struct point` values in
`queue[N * N]`, with `front=0` and `rear=-1`. Coordinates are **`{y,x}`**,
and array accesses are `[y][x]`. The source has no linked-pool dependency,
integer-ID mapping, circular-queue functions, or predecessor array.

The maze has eight passages. Starting at `{1,1}` reaches all eight and gives
distance 4 at `{3,3}`. Neighbors are checked right, left, down, up. First
discovery writes the distance before enqueue; every later encounter is
skipped. `bfs()` resets the queue and all 25 distances on each call. An
in-bounds wall start leaves the queue empty and all distances `INF=25`.
The zero border must remain intact, and the start must be within the array.

Linear capacity counts total writes per reset, not just peak pending work.
The baseline writes eight coordinates, peaks at three waiting entries, and
ends with `front=8, rear=7`. Circular predicates in the workbook are a
separate PPT-based comparison with one reserved slot and 24 usable positions in 25.
Path reconstruction is a conceptual extension that would need extra storage.
The separate checked matrix/list reference under `code/` does not define
this lab's API or required scope.

The frozen Korean textbook, **저장된 순서대로 데이터 처리하기**, and its English edition follow `Thinking logically` → `Calculating efficiency` → `Glossary` → `Invariant` → `Coding plan` → `New C syntax explained` → `C code`. The three new C topics are row-by-row brace initialization, whole-structure copying/passing/returning, and short-circuit logical OR. Named constants, increment operators, `switch`/`break`, and `continue` are review. The textbook's fifteen glossary terms are supplemented below with activity vocabulary; the 33 core terms, two optional terms, 48 questions, and single-artifact scope are unchanged.

The graph-stack comparison permits repeated entries for a still-unprocessed neighbor and skips already processed nodes when popped. BFS instead records a node's distance before enqueue and skips every later discovery. This is a comparison of pending-work policies; it does not change the earlier recursive DFS code or the maze lab.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| queue | A structure that appends at the back and removes at the front. |
| first-in first-out (FIFO) | The first added data is the first removed data. |
| enqueue | Append one coordinate to the current array queue. |
| dequeue | Return the earliest waiting coordinate and advance the read position. |
| front | The array index of the first data in a nonempty queue. |
| rear | The array index of the last data in a nonempty queue; initially -1. |
| linear array queue | A queue whose write index only advances until an independent reset. |
| circular queue | A comparison representation that wraps its indices to reuse positions. |
| wraparound | Returning from the final array index to index 0 using a remainder. |
| reserved slot | The unused position separating empty and full in the stated circular convention. |
| capacity | Reserved positions; the lab has room for N*N coordinate writes per reset. |
| active range | Queue positions front through rear that still contain waiting work. |
| level order | Processing tree nodes at one depth before the next depth. |
| depth | The number of edges from the tree root to a node. |
| breadth-first search (BFS) | FIFO traversal in nondecreasing minimum edge count; equal-cost moves also give minimum-cost paths. |
| discovered | A passage whose distance has been established, whether waiting or processed. |
| processed | A passage removed from the queue whose four neighbors have been inspected. |
| implicit graph | A graph whose neighbors are computed from coordinates when needed. |
| passage vertex | One maze cell with value 1, treated as a graph vertex. |
| four-direction edge | A move between horizontally or vertically adjacent passages. |
| shortest distance | The smallest number of equal-cost moves from the start. |
| equal movement cost | Each permitted move contributes the same one step. |
| struct point | A coordinate stored in row y, column x order. |
| sentinel (INF) | A special value; N*N=25 marks a distance that has not yet been established. |
| unreachable | A passage that retains INF because no route from the selected start exists. |
| iterator | Helpers for initialization, a continuation condition, and the next neighbor. |
| iterator state | The current coordinate and direction number shared by the neighbor helpers. |
| wall-border condition | A zero border that keeps neighbors of queued interior passages in bounds. |
| first discovery | Writing the new distance before enqueueing an unrecorded passage. |
| parent cell (predecessor) | The current cell that first discovered a passage; conceptual extra storage. |
| path reconstruction | Following previous-cell records backward and reversing the result; not implemented in the current lab. |
| O(RC) | Initialization work and reserved grid storage proportional to rows times columns. |
| O(P) | Traversal work proportional to reached passages with four candidates per passage. |

### Optional vocabulary for extension questions

| Term | Working meaning |
|---|---|
| multi-source BFS | A search starting from several cells to find distance to the nearest start. |
| BFS forest | Repeated searches covering separate connected components. |

## Anticipated student questions

### FIFO and the linear array queue

1. Requests 17, 23, and 31 arrive in order. How do a Stack and a queue differ in which request leaves first?
2. What do `front = 0` and `rear = -1` mean before the first insertion?
3. Why does `queue[++rear] = data` increase the write index first while `queue[front++]` reads before increasing the index?
4. How does `0 <= front <= rear + 1 <= N*N` describe valid queue positions, which positions are active, and why does `front > rear` mean empty?
5. After 25 insertions and 25 removals, what are `front` and `rear`, and why is another insertion invalid despite the empty queue?
6. What does `dequeue()` return in the current lab, and why does it need neither a node index nor a call to `free_lnode()`?

### Circular queue comparison

7. How does `(index + 1) % 25` move from index 24 to index 0?
8. When `front` identifies the first queued data’s index and `rear` the last queued data’s index in a nonempty queue, why are empty and full respectively `front == (rear + 1) % 25` and `front == (rear + 2) % 25`?
9. Why do these predicates reserve one position and allow only 24 waiting values in 25 slots?
10. Start at `front=0, rear=-1`, insert 0 through 23, remove two values, and insert 24 and 25. What are the new indices and removal order? Does the supplied maze lab use this circular implementation?

### Tree levels before graph search

11. In the workbook tree A(B(D,E),C(F)), what queue remains after processing A, then B, then C with left-before-right insertion?
12. What are the complete BFS order, corresponding depths, and maximum number of waiting nodes in this tree?
13. Why does a stack with right-before-left child insertion give A, B, D, E, C, F instead? In the graph-stack comparison, why may an unprocessed neighbor be pushed again, and why must an already processed node be skipped when popped?
14. How do setting the root's distance to zero and recording each child's distance as its parent's distance plus one before enqueue show which level is being processed?
15. Why does child-only traversal of a valid tree schedule each node once, while graph cycles and merging routes require a discovery record?

### Maze representation

16. How do passage cells and orthogonal moves define a graph without storing an adjacency list or matrix?
17. For `(struct point){2,3}`, what are `y`, `x`, and the array access used by `is_wall()`?
18. How can `enqueue` receive a whole `struct point`, `queue[N * N]` store it, and `dequeue` return it without converting the coordinate into an integer ID?
19. How does each inner brace pair initialize one row of `maze[N][N]`, and how do the two indices select a row and column? Review how `enum { N = 5 };` names the dimension.
20. How do the zero border and an in-bounds start keep neighbor accesses within the array, and which condition does `is_wall()` itself fail to check?

### Neighbor iteration

21. Starting from `{2,2}`, which four coordinates do `init_iter()`, `has_next_iter()`, and `next_iter()` produce, and in what order?
22. Why does every `next_iter()` call begin with a fresh copy of `cur_point`, and why does changing `p.x` leave `cur_point.x` unchanged?
23. What point would the first call return if only the first switch `break` were missing?
24. Why must one cell's four neighbors be finished before `init_iter()` starts another cell's iteration?

### Distance and initialization

25. Why is `INF = N * N` distinct from every possible shortest distance in this grid?
26. Which queue and distance state does `init_bfs()` reset before each independent search?
27. What happens when an in-bounds wall is supplied as the start, and why is an out-of-bounds start a different case?
28. Which state is changed by `set_distance()` and returned by `get_distance()`?
29. Why can the distance array replace a separate discovered array for both waiting and processed passages?

### Trace the supplied maze

30. Starting from `{1,1}`, what remains in the queue after `{1,1}`, `{2,1}`, and `{2,2}` are processed?
31. Why does the encounter from `{3,1}` to `{3,2}` leave both the stored distance and queue unchanged?
32. What are the complete removal order and final distance grid for the supplied maze?
33. What are the distance to `{3,3}`, the number of reached passages, and the final `front` and `rear`?
34. How do `||` and `continue` skip a wall or recorded neighbor without ending BFS? When does short-circuit OR omit `get_distance(p)`, and which operand rejects the encounter from `{3,2}` to `{3,3}`?

### Shortest-distance reasoning and paths

35. Why must a newly found distance be recorded before the coordinate enters the queue?
36. Why do pending distances never decrease from front to back, and how do FIFO processing and equal movement costs make first discovery shortest? What can no longer be guaranteed if a stack is used or movement costs differ?
37. If the first-discovering parent were stored as a conceptual extension, which five coordinates would reconstruct a four-move route to `{3,3}` in this neighbor order?
38. Which path records and printing operations would need to be added, given that the supplied lab records distances only?

### Work and storage

39. How many cells are initialized, how many coordinates are inserted and removed, and how many direction candidates are checked in the baseline run?
40. Why does a peak of three waiting coordinates still require eight total writes in the linear array queue?
41. For an `R` by `C` grid with `P` reached passages, why are initialization, traversal, and reserved search storage respectively `O(RC)`, `O(P)`, and `O(RC)`?
42. Why is a queue with room for all cells sufficient for one search, even though `enqueue()` does not check for overflow?

### Checks and evidence

43. Why can `lab.c` be compiled to an object with `-c` but need a separate `main()` driver for execution?
44. Which observations distinguish a successful fresh reverse-start run from one that accidentally retains the previous distances?
45. In a separate driver, temporarily block `maze[2][1]` and start at `{1,1}`. Which distance and queue states show that the target is unreachable, and what must be restored afterward?
46. Which traces, corrected predictions, and checks should appear together in the single queue, tree, and maze submission?

### Optional extension questions

47. How would initializing several passages at distance 0 change the meaning of each final distance?
48. How could repeated BFS searches cover every component when interior walls disconnect the passages?

## Sources

- [Current textbook](../module_08_graph_bfs/student/textbook.md)
- [Korean textbook](../module_08_graph_bfs/student/textbook_korean.md)
- [Concept slides](../module_08_graph_bfs/student/ppt_material.md)
- [Lab slides](../module_08_graph_bfs/student/ppt_lab_material.md)
- [Current lab source](../module_08_graph_bfs/student/lab.c)
- [Lab instructions](../module_08_graph_bfs/student/lab.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md)
