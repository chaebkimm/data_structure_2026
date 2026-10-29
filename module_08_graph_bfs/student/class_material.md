# Chapter 8 Class Workbook / 8장 수업 활동 — Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Name / 이름: ____________________ Date / 날짜: ____________________

Use the [English textbook](textbook.md), [Korean textbook](textbook_korean.md), [concept slides](ppt_material.md), [lab slides](ppt_lab_material.md), and [lab](lab.md). The current `lab.c` defines the maze and operations. Keep your first prediction, then record corrections beside it.
첫 예상을 남긴다. 예상과 실행 결과가 다르면 원인을 함께 적는다. 아래 예상 확인 부분은 활동을 마친 뒤 읽는다.


## First hour: build arrival order / 먼저 큐를 만든다

Module 7 taught linked lists and used a linked FIFO queue as their example. Predict before running `queue.c`.
7장은 연결 리스트의 예로 연결 큐를 만들었다. 큐 코드를 실행하기 전에 예상한다.

1. Enqueue values 17, 23, 31 through the public wrapper and check Boolean success. Record free chain, head, tail, and next links after every change. / 각 변경 뒤 빈 연결과 두 끝을 기록한다.
2. Dequeue the values. Explain why public returns are payloads while raw helper returns are pool indices. When does the wrapper recycle? / 공개 반환값은 데이터다. 하위 함수의 풀 인덱스와 구분하고 자동 반환 시점을 설명한다.
3. Fill the linear queue with 0..24, then drain it. Explain why `is_empty_linear()` and `is_full_linear()` are both true. / 다 꺼내도 rear가 24인 이유를 설명한다.
4. Reset. Fill the circular queue with 0..23, remove 0/1, append 24/25. Predict front, rear, full, and the remaining order. / 한 칸을 비워 24개를 담는 이유와 순환 뒤 순서를 설명한다.

| Representation / 구현 | First prediction / 첫 예상 | Observed state / 관찰 | Correction / 수정 |
| --- | --- | --- | --- |
| Linked endpoints and recycle / 연결 끝과 재활용 | | | |
| Linear exhausted writes / 선형 쓰기 위치 소진 | | | |
| Circular wraparound / 원형 순환 | | | |

## Next thirty minutes: process tree levels / 트리를 층별로 처리한다

Run `alphabet_init(); root=tree_connect();` from Module 2. Root F has A/G; A has B/C; B has D/E. Use `tree_bfs(root, order)` after ensuring all prior allocations are recycled and calling the guarded initializer and setting head/tail to -1.
2장의 같은 트리를 쓴다. root F부터 왼쪽 자식을 먼저 큐에 넣는다.

| Just processed / 처리 | Your pending indices / 대기 인덱스 | Correction / 수정 |
| --- | --- | --- |
| F | | |
| A | | |
| G | | |
| B | | |

Predict all seven output labels and depths. Explain why C is processed before D. Explain why empty root -1 produces no output and why nodes 7..9 are not reached. Compare the one-parent tree rule with graph cycles and merges.
처리 순서와 깊이를 예상한다. C를 D보다 먼저 처리하는 이유를 설명한다. 순환과 합류가 있는 그래프에서 발견 기록이 필요한 이유를 설명한다.

Checkpoint after preserving predictions: pending queues are `[0,6]`, `[6,1,2]`, `[1,2]`, `[2,3,4]`. Order is F, A, G, B, C, D, E. Depths are 0, 1, 1, 2, 2, 3, 3.


## 1. How does a point identify a cell? / 점은 어느 칸을 가리키는가?

We need to connect coordinates, array access, and the integer stored in the queue. In this maze, `x` is the column and `y` is the row.
좌표, 배열 위치, 큐에 넣는 번호를 연결한다. `init_info()`는 벽을 포함한 모든 칸에 번호를 붙인다.

| Point / 점 | Array access / 배열 접근 | Cell ID / 번호 | Wall or passage? / 벽 또는 통로 |
| --- | --- | --- | --- |
| `{1,1}` | | | |
| `{3,2}` | | | |
| `{4,2}` | | | |
| `{5,5}` | | | |

Why does `points[50]` not mean that the maze has 50 passages? What is the last ID assigned by `init_info()`?
`points[50]`이 통로 50개를 뜻하지 않는 이유와 마지막으로 부여한 번호를 쓴다.

Prediction / 예상: __________________________________________________

## 2. Which operation makes a passage discovered? / 어느 동작이 발견을 기록하는가?

The start is `{1,1}`. Prepare an independent run, then predict the state after the first two removals.
독립 실행을 준비한다. 첫 두 칸을 꺼내 처리한 뒤의 상태를 예상한다.

```c
init_info();
init_lnodes_pool();
qhead = qtail = -1;
bfs((struct point){1, 1});
```

| After processing / 처리한 칸 | Newly discovered points and distances / 새로 찾은 점과 거리 | Remaining queue IDs / 남은 큐 번호 |
| --- | --- | --- |
| `{1,1}` | | |
| `{1,2}` | | |

Explain why `set_distance()` runs before the checked public `enqueue(id)`. What could happen if discovery were recorded only when removing the cell?
큐에 넣기 전에 거리를 기록하는 이유를 쓴다. 꺼낼 때만 발견을 표시하면 어떤 일이 생길 수 있는가?

Reason / 이유: ______________________________________________________

## 3. Which directions does one iterator inspect? / 반복자는 어느 방향을 확인하는가?

Process `{3,2}` at distance 3. Its neighbors must be checked in the actual source order.
현재 칸의 거리와 이웃의 기존 거리를 비교한다. 이미 발견했지만 아직 큐에 있는 칸도 발견 상태다.

| Direction / 방향 | Neighbor point / 이웃 | Wall? / 벽인가? | Distance before / 기존 거리 | Action / 동작 |
| --- | --- | --- | --- | --- |
| first / 첫째 | | | | |
| second / 둘째 | | | | |
| third / 셋째 | | | | |
| fourth / 넷째 | | | | |

Explain what a missing `break` would do to the first returned point. Trace the switch on paper.
첫 `break`를 빼면 첫 결과가 어떻게 달라지는지 대입 순서대로 추적한다.

Reason / 이유: ______________________________________________________

## 4. How do two shortest routes merge? / 두 최단 경로는 어떻게 합쳐지는가?

The search reaches `{3,5}` first from `{3,4}`, then from `{2,5}`. Both preceding cells have distance 5.
두 현재 칸의 거리는 모두 5다. 두 번째 만남에서 바뀌는 필드를 구분한다.

| Encounter from / 현재 칸 | Distance before / 기존 거리 | Distance after / 새 거리 | `prev_size` after | Ordered `prev` after / 이전 칸 순서 | Enqueue? / 삽입 여부 |
| --- | --- | --- | --- | --- | --- |
| `{3,4}` | | | | | |
| `{2,5}` | | | | | |

Why can `prev[4]` hold all shortest-route predecessors here? Why does this argument depend on the four-direction representation?
이 표현에서 이전 칸 네 개면 충분한 이유를 쓴다.

Reason / 이유: ______________________________________________________

## 5. Does the final predecessor count equal the route count? / 이전 칸 수가 경로 수인가?

The target is `{5,5}`. Use the predecessor records rather than guessing from the drawing.
목표에서 시작점 쪽으로 기록을 따라간다. 여러 이전 칸이 있는 곳에서는 선택지를 나눈다.

1. Predict target distance and ordered predecessors. / 목표 거리와 이전 칸의 순서를 예상한다.
2. Write one complete shortest route as points. / 최단 경로 하나를 점의 순서로 쓴다.
3. Count all shortest routes. Explain any difference from the target's `prev_size`. / 전체 최단 경로 수와 목표의 이전 칸 수가 다른 이유를 쓴다.
4. Check how the distance changes on each backward step. / 이전 칸을 따라갈 때 거리가 어떻게 바뀌는지 확인한다.

Prediction / 예상: __________________________________________________
Route / 경로: _______________________________________________________
Reason / 이유: ______________________________________________________

## 6. Which assumptions protect the array accesses? / 어떤 조건이 배열 접근을 지키는가?

The supplied maze has a zero wall border. Only passage cells are enqueued after a valid passage start.
테두리와 시작점 조건을 함께 사용해 `is_wall()`의 배열 접근을 설명한다.

Explain each case without executing unchecked invalid calls:

1. Why do neighbors of any queued cell remain inside indices 0 through 6? / 큐에서 꺼낸 칸의 이웃 번호가 범위 안인 이유는?
2. Why is an arbitrary wall or out-of-range start outside the contract? / 임의의 벽이나 범위 밖 시작점이 유효하지 않은 이유는?
3. Why can ten reused linked-queue slots handle 20 discoveries? / 연결 큐 열 칸으로 발견 20번을 처리할 수 있는 이유는?
4. Why must an independent search initialize metadata and the unowned linked pool/endpoints? / 탐색 기록과 소유자가 없는 풀 및 두 끝을 초기화하는 이유는?
5. Why do both searches include one guarded queue source? / 두 탐색은 왜 포함 가드가 있는 큐 소스를 함께 사용하는가?

Reason / 이유: ______________________________________________________

## 7. Which evidence checks the result? / 어떤 근거로 결과를 확인할까?

Run [lab_driver.c](lab_driver.c) directly using the [lab setup](lab.md).
실제 소스와 드라이버를 직접 빌드한다. 준비 사본은 필요 없다.

Record at least these observations: start distance and predecessor count; goal distance and predecessors; reached-passage count; final linked `qhead`/`qtail` and the restored free-node count; and one cell with multiple predecessors.
거리 하나만 확인하지 말고 발견 수, 연결 큐의 두 끝, 반환한 풀 칸 수, 합쳐진 이전 칸도 확인한다.

Command / 명령: _____________________________________________________
Observed state / 관찰 상태: __________________________________________
First mismatch and correction / 첫 불일치와 수정: ______________________

Design one additional valid experiment: a fresh reverse-start run, start-as-target reconstruction, or a temporary isolated target with the wall border preserved. State the expected result before running. Restore the baseline maze after changes.
추가 실험 하나의 초기 상태와 예상 결과를 적는다. 미로를 바꿨다면 기본 확인 전에 원래 상태로 되돌린다.

Experiment and expectation / 실험과 예상: ______________________________

## 8. Which work grows with the maze? / 미로가 커지면 무엇이 늘어나는가?

Count operations for the baseline run before writing a cost formula.
초기화와 탐색의 일을 따로 센다. 모든 경로 출력은 별도의 작업이다.

| Work / 작업 | Baseline count / 현재 실행 횟수 | General growth / 일반 크기 |
| --- | --- | --- |
| initialize cell metadata / 칸 정보 초기화 | | |
| enqueue and dequeue / 삽입과 삭제 각각 | | |
| inspect neighbors / 이웃 검사 | | |
| reserved grid metadata / 격자 정보 공간 | | |

Why does this code not scan a row of an adjacency matrix for each cell? Why can listing every shortest route cost more than computing the distances?
이 코드가 인접 행렬의 한 행을 매번 훑지 않는 이유를 쓴다. 모든 최단 경로 출력이 거리 계산보다 오래 걸릴 수 있는 이유를 쓴다.

Reason / 이유: ______________________________________________________

---

## Expected checkpoints / 예상 확인

Read these after completing your predictions. Keep the first answer and explain each correction.
예상을 마친 뒤 비교한다. 첫 답을 지우지 않고 수정 이유를 적는다.

1. **Coordinates and IDs.** `{1,1}` → `maze[1][1]`, ID8, passage; `{3,2}` → `maze[2][3]`, ID17, passage; `{4,2}` → `maze[2][4]`, ID18, wall; `{5,5}` → `maze[5][5]`, ID40, passage. All 49 grid positions receive IDs 0–48. There are 20 passages. `points[49]` is unused.
2. **First discoveries.** After `{1,1}`, `{1,2}` has distance 1 and queue `[15]`. After `{1,2}`, `{2,2}` and `{1,3}` have distance 2 and queue `[16,22]`. Writing the distance before insertion prevents duplicate insertion while a cell waits in the queue.
3. **Iterator and branch.** From `{3,2}`, inspect `{4,2}` wall; `{2,2}` distance 2, skip; `{3,3}` distance 25, discover at 4; `{3,1}` distance 25, discover at4. Removing only the first `break` allows case1 to undo the x increment before its own `break`, returning `{3,2}` on the first call.
4. **Merge.** `{3,4}` changes `{3,5}` from 25 to 6, appends the first predecessor, and enqueues ID38. `{2,5}` keeps 6, appends the second predecessor, and does not enqueue. Each reached cell is processed once and a cell has at most four neighbors, so no more than four distinct predecessors can be appended.
5. **Routes.** The goal has distance 8 and ordered predecessors `{5,4}`, `{4,5}`. There are three complete shortest routes. One is `{1,1}→{1,2}→{2,2}→{3,2}→{3,3}→{4,3}→{5,3}→{5,4}→{5,5}`. The two choices at `{3,5}` account for the extra complete route. Each backward step decreases distance by 1.
6. **Caller conditions.** A passage lies at coordinates1–5 because the border is walls. Its immediate neighbors lie at0–6. The start must already satisfy the passage and coordinate conditions. Twenty passages are each enqueued once. Public `dequeue()` copies the payload and recycles its node before BFS expands it. The canonical peak pending count is four; every supplied start peaks at most six. An independent run needs `init_info(); init_lnodes_pool(); qhead = qtail = -1;` with no other live pool owner. The queue include guard shares one definition across tree and maze searches.
7. **Baseline evidence.** The start has distance 0 and `prev_size==0`. All 20 passages are reached. At the end `qhead==qtail==-1` and all ten pool slots are free. There are 20 insertions/removals and a peak of four pending entries. The reversed valid start reaches all 20 passages and gives distance 8 at `{1,1}`. A start-as-target route has one point and zero moves. An isolated passage target keeps distance 25 and no predecessors.
8. **Work.** There are 49 metadata initializations,20 enqueues,20 dequeues, and80 direction checks. For `R` rows and `C` columns, initialization and grid storage are O(R·C). Traversal is O(V_reached) because each reached cell has at most four neighbors. Generating neighbors directly avoids an adjacency-matrix scan. Enumerating every route depends on the number and lengths of the routes printed.
