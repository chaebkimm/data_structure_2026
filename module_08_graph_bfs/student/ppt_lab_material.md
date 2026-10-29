# Chapter 8 Lab Slides — Trace Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Use the current `lab.c` with the [lab](lab.md), [English textbook](textbook.md), [Korean textbook](textbook_korean.md), and [class workbook](class_material.md). Each scene starts with a prediction and ends with state evidence.
실행 전에 상태를 예상한다. 실행 후에는 거리와 이전 칸, 큐 위치를 함께 확인한다.

## 1. Which request should leave first? / 어떤 요청부터 꺼낼까?

Requests 17, 23, 31 arrive in that order. Predict removals under the Stack rule, then state the needed arrival rule. Name FIFO and queue after the prediction. / 먼저 들어온 요청부터 처리해야 한다. 뒤에 넣고 앞에서 꺼낸다.

## 2. Which links preserve arrival order? / 어떤 연결이 도착 순서를 지킬까?

Use Module 8's local value adapters in `queue.c` over Module 7's node queue. `enqueue(value)` allocates and returns Boolean success; `dequeue()` returns the oldest value and recycles its node. Check `is_empty_queue()` before dequeue. Raw helpers exchange node indices, but BFS does not call them. / 공개 enqueue는 값을 넣고 성공 여부를 준다. 공개 dequeue는 값을 반환하며 칸을 자동으로 돌려준다. 빈 큐에서 공개 꺼내기를 호출하지 않는다.

## 3. Why can an empty linear queue be full? / 빈 선형 큐가 왜 가득 찼다고 할까?

Start front=0, rear=-1 in queue[25]. Fill 0..24 then drain. front=25, rear=24 satisfies both predicates: no pending item and no unused write slot. / 이미 읽은 자리는 재사용하지 않는다. 독립 실행 전에 두 위치를 초기화한다.

## 4. How do positions wrap? / 위치는 어떻게 순환할까?

Circular predicates use modulo 25. One reserved position leaves 24 usable values. Fill 0..23, remove 0/1, append 24/25. rear becomes 0; removal gives 2..25. Check full/empty before mutation. / 배열 두 구현은 저장 공간을 공유한다. 한 실행에서 섞지 않는다.

## 5. How does FIFO process tree levels? / FIFO로 트리의 층을 어떻게 처리할까?

Reuse Module 2's F-root tree: F→A/G, A→B/C, B→D/E. Enqueue root; dequeue/process one index; enqueue its existing left then right child. Pending after F, A, G, B: [0,6], [6,1,2], [1,2], [2,3,4]. / 다음 층의 자식은 기존 대기 노드 뒤로 간다.

## 6. Why does a graph need a discovery record? / 그래프에는 왜 발견 기록이 필요할까?

Tree order is F, A, G, B, C, D, E with depths 0, 1, 1, 2, 2, 3, 3. tree_bfs returns 7; root -1 returns 0. A valid tree has one parent per nonroot node and no cycles. Graph merges/cycles can offer a vertex again while it is waiting. Record discovery before enqueue. / 트리와 같은 FIFO를 쓰되 그래프에서는 중복 예약을 막는다.

## 7. What compiles together? / 어떤 소스를 함께 빌드할까?

`lab_driver.c` includes maze `lab.c` and `tree_bfs.c`. Both share guarded `queue.c`; it imports Module 7's linked queue and pool behind a shared consumer guard. The tree includes Module 2's tree. Compile only the driver with repository root on the include path. / 준비 사본 없이 실제 소스를 직접 빌드한다.

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

Expected: `PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches`.

## 8. What state must each run reset? / 탐색마다 어떤 상태를 초기화할까?

The BFS function only records the start distance and enqueues its ID. The caller must prepare all other state.
`bfs()`는 전체 정보를 초기화하지 않는다. 독립 실행의 초기 상태는 호출자가 만든다.

```c
init_info();
init_lnodes_pool();
qhead = qtail = -1;
bfs((struct point){1, 1});
```

Before calling `bfs`, verify that the start is an interior passage. `is_wall()` directly indexes the array, so it cannot validate an arbitrary coordinate.
시작점은 1 이상 5 이하의 좌표를 가진 통로여야 한다. 좌표가 유효한지 먼저 확인한 뒤 배열을 읽는다.

Predict a second independent run without resetting: previous distances may suppress discoveries or live links may retain pending work. Initialize metadata and verify all pool slots are recycled with empty endpoints before each independent run; the pool initializer only acts once. The initializer runs only once; it cannot reset live, exhausted, or damaged pool state. Finish/recycle every owner between independent runs.

## 9. Which grid entries does initialization assign? / 초기화가 어떤 칸에 기록하는가?

Inspect the nested loops in `init_info()`. The loops include walls and assign an ID to every grid position.
행과 열을 모두 순회한다. 통로만 따로 번호를 매기지 않는다.

```text
info[0][0]: index 0, distance 25, prev_size0
info[1][1]: index 8, distance 25, prev_size0
info[5][5]: index 40, distance 25, prev_size0
info[6][6]: index 48, distance 25, prev_size0
points[8]={1,1}; points[40]={5,5}; points[48]={6,6}
```

Assert coordinate round trips for all 49 cells. `points[49]` is unused. Read a predecessor only when its slot number is less than `prev_size`.

## 10. Does the iterator preserve the coordinate convention? / 반복자가 좌표 규칙을 지키는가?

Start the iterator at `{3,2}`. Predict all four results before stepping through `next_iter()`.
`x`가 열이라는 규칙을 유지한다. `state`가 증가해도 기준점 `cur_point`는 바뀌지 않는다.

| `state` before call | Direction / 방향 | Result / 결과 | Maze value / 미로 값 |
| ---: | --- | --- | ---: |
| 0 | right / 오른쪽 | `{4,2}` | 0 |
| 1 | left / 왼쪽 | `{2,2}` | 1 |
| 2 | down / 아래 | `{3,3}` | 1 |
| 3 | up / 위 | `{3,1}` | 1 |

After four calls, `has_next()` is false. Each `break` stops switch fallthrough. Do not call `next_iter()` after exhaustion as part of the traversal.

## 11. Which value records discovery? / 어느 값이 발견을 표시하는가?

Process `{1,1}` and then `{1,2}`. Observe the moment each distance changes from 25.
거리는 큐에 넣기 전에 바뀐다. 큐 안에서 기다리는 칸도 이미 발견한 칸이다.

```text
initial queue IDs: [8]
process {1,1}: discover {1,2}, distance 1, prev[{1,1}], queue[15]
process {1,2}: discover {2,2}, distance 2, prev[{1,2}]
                 discover {1,3}, distance 2, prev[{1,2}]
queue IDs after both removals: [16,22]
```

Inspect `set_distance()` and `add_prev()`. Both write the shared `info` array. No local copy of a whole `maze_node` is being changed.

## 12. Does an equal-length encounter enqueue twice? / 같은 거리로 다시 만나면 두 번 넣는가?

Trace the two arrivals at `{3,5}`. Its shortest distance is 6.
거리 5인 두 칸이 같은 통로를 만난다. 이전 칸은 둘이지만 큐 삽입은 한 번이다.

| Current cell / 현재 칸 | Neighbor distance before / 기존 거리 | Action / 동작 | Stored predecessors after / 기록 결과 |
| --- | ---: | --- | --- |
| `{3,4}` | 25 | distance 6, add previous, enqueue 38 | `{3,4}` |
| `{2,5}` | 6 | add previous only | `{3,4}`, `{2,5}` |

Count the total enqueues of ID 38: one. Check that every predecessor is adjacent and has distance exactly one less than the cell it precedes.

## 13. What complete order should the run produce? / 전체 처리 순서는 무엇인가?

Record dequeued IDs using the existing right, left, down, up iterator order. The order is deterministic for this start and this maze.
제공된 이웃 순서를 유지하면 다음 순서로 처리한다.

```text
8,15,16,22,17,29,24,10,36,25,31,11,37,26,38,12,33,19,39,40
```

After the run, `qhead==qtail==-1`, `is_empty_queue()` is true, and all ten pool slots are free. There are 20 insertions/removals and a peak of four pending entries. Public `dequeue()` returns the ID after recycling its node, then BFS expands the ID.
두 BFS는 7장의 연결 큐를 그대로 호출한다. 꺼낸 풀 칸의 데이터를 읽고 반환한 뒤 이웃을 넣는다. 선형·원형 배열은 비교 예다.

Do not replace distance checks with a requirement to sort IDs. For example, ID 24 leaves before ID 10 because the iterator finds `{3,3}` before `{3,1}`.

## 14. Which final state proves the distance result? / 어떤 최종 상태를 확인할까?

Display passage distances after running from `{1,1}`. The following table uses `#` for walls; wall metadata still holds distance 25.
거리 25인 벽과 도달한 통로를 구분해 표시한다.

```text
# # # # # # #
# 0 # 4 5 6 #
# 1 2 3 # 7 #
# 2 # 4 5 6 #
# 3 # 5 # 7 #
# 4 5 6 7 8 #
# # # # # # #
```

Check goal distance 8, `prev_size==2`, `prev[0]=={5,4}`, and `prev[1]=={4,5}`. At `{3,5}`, expect two predecessors in the order `{3,4}`, `{2,5}`. At the start, expect distance 0 and `prev_size==0`.

## 15. How do we test a route separately from the search? / 경로를 탐색과 나눠 어떻게 확인할까?

The source stores predecessor choices but prints no paths. Add route reconstruction in the driver as an exercise.
제공 코드에는 경로 출력이 없다. 드라이버에서 이전 칸을 따라가며 경로를 만든다.

For each output route, check the start, goal, passage membership, four-direction adjacency, and exactly 8 moves. Following `prev[0]` at every step gives one shortest route. Exploring all stored choices gives three routes for `{5,5}`.
목표의 `prev_size`가 2라고 경로 수가 2인 것은 아니다. 합쳐진 이전 칸에도 여러 선택지가 있을 수 있다.

First check `distance!=25` before attempting reconstruction for a target. An unreachable target has no predecessor route to follow.

## 16. Which boundary evidence is useful? / 어떤 경계 상태를 확인할까?

Use valid calls to distinguish the search contract from accidental results.
유효한 입력에서 경계 상태를 검사한다. 무검사 함수의 잘못된 호출은 실행으로 확인하지 않는다.

- Run from `{5,5}` after a complete reset. Expect distance 8 at `{1,1}` and 20 reached passages. / 초기화 후 반대쪽에서 다시 시작한다.
- Use the start itself as a target. Expect distance 0 and a route containing one point. / 시작점까지 이동 횟수는 0이다.
- In a temporary maze experiment, close interior passages as needed to isolate the chosen target, preserving the zero border. Expect the isolated target to remain at distance 25 with `prev_size==0`. Restore the maze before baseline checks. / 격리한 통로는 미발견 표시를 유지한다.
- Count discoveries, dequeues, and neighbor checks in the baseline run. Expect 20, 20, and 80. / 도달한 칸마다 네 방향을 검사한다.

Explain why the wall border is sufficient for the supplied valid starts, why it is insufficient for arbitrary invalid starts, and why a larger maze needs a larger queue and a suitable unseen-distance marker. Submit predictions, observed state, and the cause of the first mismatch.
