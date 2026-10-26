# Chapter 8 Concept Slides — Queues, Tree BFS, and Graph BFS

Use one numbered topic per slide or board scene. Ask for a prediction before revealing the next state. The [English textbook](textbook.md), [Korean textbook](textbook_korean.md), [lab](lab.md), and [class workbook](class_material.md) follow the current `lab.c`.
각 번호를 슬라이드나 판서 한 장면으로 사용한다. 다음 상태를 보여 주기 전에 먼저 예상하게 한다.

## 1. Which request should leave first? / 어떤 요청부터 꺼낼까?

Requests 17, 23, 31 arrive in that order. Predict removals under the Stack rule, then state the needed arrival rule. Name FIFO and queue after the prediction. / 먼저 들어온 요청부터 처리해야 한다. 뒤에 넣고 앞에서 꺼낸다.

## 2. Which links preserve arrival order? / 어떤 연결이 도착 순서를 지킬까?

Use Module 7's value queue through `queue.c`. `enqueue(value)` allocates and returns Boolean success; `dequeue()` returns the oldest value and recycles its node. Check `is_empty_queue()` before dequeue. Raw helpers exchange node indices, but BFS does not call them. / 공개 enqueue는 값을 넣고 성공 여부를 준다. 공개 dequeue는 값을 반환하며 칸을 자동으로 돌려준다. 빈 큐에서 공개 꺼내기를 호출하지 않는다.

## 3. Why can an empty linear queue be full? / 빈 선형 큐가 왜 가득 찼다고 할까?

Start front=0, rear=-1 in queue[25]. Fill 0..24 then drain. front=25, rear=24 satisfies both predicates: no pending item and no unused write slot. / 이미 읽은 자리는 재사용하지 않는다. 독립 실행 전에 두 위치를 초기화한다.

## 4. How do positions wrap? / 위치는 어떻게 순환할까?

Circular predicates use modulo 25. One reserved position leaves 24 usable values. Fill 0..23, remove 0/1, append 24/25. rear becomes 0; removal gives 2..25. Check full/empty before mutation. / 배열 두 구현은 저장 공간을 공유한다. 한 실행에서 섞지 않는다.

## 5. How does FIFO process tree levels? / FIFO로 트리의 층을 어떻게 처리할까?

Reuse Module 2's F-root tree: F→A/G, A→B/C, B→D/E. Enqueue root; dequeue/process one index; enqueue its existing left then right child. Pending after F, A, G, B: [0,6], [6,1,2], [1,2], [2,3,4]. / 다음 층의 자식은 기존 대기 노드 뒤로 간다.

## 6. Why does a graph need a discovery record? / 그래프에는 왜 발견 기록이 필요할까?

Tree order is F, A, G, B, C, D, E with depths 0, 1, 1, 2, 2, 3, 3. tree_bfs returns 7; root -1 returns 0. A valid tree has one parent per nonroot node and no cycles. Graph merges/cycles can offer a vertex again while it is waiting. Record discovery before enqueue. / 트리와 같은 FIFO를 쓰되 그래프에서는 중복 예약을 막는다.

## 7. Which route uses the fewest moves? / 어느 길이 가장 적게 움직이는가?

We want to move from `{1,1}` to `{5,5}` through passages. Every move goes one cell right, left, down, or up. Every move has the same cost.
통로에서 상하좌우로 한 칸씩 움직인다. 도착할 수 있는 길 중 이동 횟수가 가장 적은 길을 찾는다.

```text
       x: 0 1 2 3 4 5 6
y = 0     # # # # # # #
y = 1     # S # . . . #
y = 2     # . . . # . #
y = 3     # . # . . . #
y = 4     # . # . # . #
y = 5     # . . . . G #
y = 6     # # # # # # #
```

`#` is `0`, a wall. A passage is `1`. `S` and `G` are passage cells. A point is `{x, y}`; `x` is the column and `y` is the row. C accesses the cell as `maze[y][x]`.
`x`는 열이고 `y`는 행이다. `{1,2}`를 읽을 때는 `maze[2][1]`에 접근한다.

## 8. Does finding a route prove it is shortest? / 길을 찾으면 최단 경로인가?

A search that follows one branch deeply may reach the goal before checking a shorter branch. Reaching the goal proves reachability. It does not by itself prove the fewest moves.
depth-first search는 한 갈래를 먼저 깊게 따라간다. 처음 찾은 길의 이동 횟수가 가장 작다고 보장하지 않는다.

We need to finish all cells at distance 1 before cells at distance 2, then finish distance 2 before distance 3. Put newly found cells at the back of a FIFO queue. Remove the oldest cell from the front.
한 번에 닿는 칸부터 처리한다. 새로 찾은 칸은 큐의 뒤에 넣는다. 먼저 들어온 칸부터 꺼낸다. 이 탐색을 breadth-first search라고 한다.

Predict the first distances: `{1,1}` has 0, `{1,2}` has 1, and `{2,2}` and `{1,3}` have 2. Distance counts edges, so a route with 8 moves contains 9 cells.

## 9. How does a cell become an integer in the queue? / 칸을 큐의 정수로 어떻게 바꾸는가?

The queue stores integers, but the maze uses two coordinates. Number every grid position by row, including walls.
큐에는 정수를 저장한다. 행을 먼저 따라가며 모든 칸에 번호를 붙인다.

```text
index = 7*y + x
{1,1} → 8       {1,2} → 15       {5,5} → 40
get_index(p) → info[p.y][p.x].index
points[8] → {1,1}
```

`init_info()` assigns IDs 0 through 48. `points[50]` has one unused slot at index 49. These are grid IDs, not compact passage numbers. The maze has 20 passages.
벽도 번호를 가진다. 큐에 넣는 것은 실제로 도달한 통로의 번호다. 통로는 모두 20칸이다.

## 10. Which information must each cell remember? / 각 칸에 무엇을 기록할까?

We need to know whether a passage was found and how many moves reached it. We also need the earlier cells that can lead into it on a shortest route.
발견 여부와 이동 횟수를 기록한다. 최단 경로에서 바로 앞에 올 수 있는 칸도 기록한다.

```c
struct maze_node {
    int index;
    int distance;
    struct point prev[4];
    int prev_size;
};
```

`init_info()` sets every distance to 25 and every `prev_size` to 0. The value 25 means no route has been recorded. The supplied maze has 20 passages, so any reachable shortest route uses at most 19 edges. The marker is larger than every valid distance here.
`distance`가 발견 표시도 겸한다. 별도 방문 배열은 없다. 25는 이 미로에서 아직 경로를 기록하지 않았다는 표시다. 탐색 종료 후에도 통로의 값이 25라면 시작점에서 도달하지 못했다.

Only `prev[0]` through `prev[prev_size-1]` are meaningful. Unused predecessor slots need not be cleared.

## 11. What happens when a passage is first found? / 통로를 처음 찾으면 무엇을 할까?

Suppose the current distance is `d`. An adjacent passage can be reached in `d+1` moves. Because the queue processes shorter distances first, its first recorded distance is already shortest.
현재 칸까지 `d`번 움직였다면 이웃까지는 `d+1`번이다. 큐가 짧은 거리부터 처리하므로 첫 발견 거리를 나중에 줄일 필요가 없다.

```c
set_distance(neighbor, cur_distance + 1);
add_prev(neighbor, cur);
added = enqueue(get_index(neighbor));
assert(added);
```

The Boolean variable `added` is declared before the search loop. Call enqueue outside assert, then check the saved result; NDEBUG must not remove the insertion. Record the distance before enqueueing. Another cell may encounter the same neighbor while the neighbor is still waiting. The recorded distance prevents a second enqueue.
큐에서 꺼낼 때까지 기다리지 않는다. 큐에 넣기 전에 거리를 기록해야 중복 삽입을 막는다.

Predict the queue after processing `{1,2}`: `{2,2}`, `{1,3}`. The iterator checks right, left, down, then up. Walls and already closer cells are skipped.

## 12. Can two routes arrive with the same shortest distance? / 같은 최단 거리로 두 길이 합쳐질까?

A passage may already have the proposed distance. That encounter gives another shortest-route predecessor. Keep the predecessor without inserting the passage again.
이미 같은 거리로 발견한 통로라면 최단 경로가 하나 더 합쳐진다. 이전 칸만 추가한다.

```text
{3,4}, distance 5 → first discovers {3,5}, distance 6
    prev[0] = {3,4}; prev_size = 1; enqueue ID 38
{2,5}, distance 5 → later reaches {3,5} at distance 6
    prev[1] = {2,5}; prev_size = 2; no enqueue
```

The supplied comparison has three outcomes:

| Neighbor state / 이웃 상태 | Action / 동작 |
| --- | --- |
| `neighbor_distance <= cur_distance` | Skip / 건너뛴다 |
| `neighbor_distance == cur_distance + 1` | Append `cur` to `prev` / 이전 칸만 추가한다 |
| Otherwise, first discovery in this run | Set distance, append `cur`, enqueue / 거리 기록, 이전 칸 추가, 큐 삽입 |

Each passage has at most four adjacent cells. Each reached cell is processed once. Therefore `prev[4]` can hold every shortest-route predecessor for this maze representation.

## 13. Which layers does the queue process? / 큐는 어떤 거리 순서로 처리하는가?

Follow the current iterator order from `{1,1}`. Cells in one distance layer leave the queue before cells in the next layer.
같은 거리의 칸을 모두 처리한 뒤 다음 거리로 넘어간다. 같은 거리 안의 순서는 이웃 검사 순서에 따라 달라진다.

| Distance / 거리 | Dequeue order within the layer / 해당 거리의 처리 순서 |
| ---: | --- |
| 0 | `{1,1}` |
| 1 | `{1,2}` |
| 2 | `{2,2}`, `{1,3}` |
| 3 | `{3,2}`, `{1,4}` |
| 4 | `{3,3}`, `{3,1}`, `{1,5}` |
| 5 | `{4,3}`, `{3,4}`, `{4,1}`, `{2,5}` |
| 6 | `{5,3}`, `{3,5}`, `{5,1}` |
| 7 | `{5,4}`, `{5,2}`, `{4,5}` |
| 8 | `{5,5}` |

At the end, 20 passages have been reached. `{5,5}` has distance 8 and ordered predecessors `{5,4}`, `{4,5}`. Its two immediate predecessors represent three complete shortest routes because `{3,5}` itself has two predecessors.
목표의 바로 앞 칸은 둘이지만 전체 최단 경로는 셋이다. 이전 칸 개수와 전체 경로 개수는 다르다.

## 14. How do earlier cells recover a route? / 이전 칸으로 경로를 어떻게 복원할까?

The stored predecessors point toward the start. Choose one predecessor at each step, then reverse the collected sequence to print a route from start to goal.
목표에서 이전 칸을 따라가면 시작점으로 돌아간다. 모은 순서를 뒤집어 출력한다.

```text
one backward chain:
{5,5}←{5,4}←{5,3}←{4,3}←{3,3}←{3,2}←{2,2}←{1,2}←{1,1}
```

Every predecessor has distance one less, so following these links terminates at distance 0. To enumerate all shortest routes, explore every stored predecessor choice. `lab.c` records the links; it does not contain a route-printing function.
한 경로를 고를 때는 이전 칸을 하나씩 선택한다. 모든 최단 경로를 출력하려면 각 선택지를 모두 따라가야 한다. 제공 코드는 이전 칸의 기록까지만 수행한다.

## 15. What conditions keep this implementation valid? / 어떤 조건에서 안전하게 동작하는가?

The functions rely on the caller and the supplied maze. Establish these conditions before running.
함수 내부에서 모든 조건을 검사하지 않는다. 실행 전에 호출자가 조건을 맞춘다.

- Start at an interior passage. A wall start is invalid. / 내부 통로에서 시작한다.
- Call `init_info()` and initialize the otherwise unowned pool with `init_lnodes_pool(); head=tail=-1;` before each independent search. / 독립 탐색마다 정보와 큐를 초기화한다.
- Preserve the zero wall border. A queued passage is interior; its four neighbors have valid indices. `is_wall()` itself does no bounds check. / 바깥 테두리의 0을 유지한다.
- Reuse Module 7's linked queue. Twenty discoveries reuse ten pool slots because every removed slot returns before expansion. Peak pending is four from the canonical start and at most six over all supplied starts. / 꺼낸 큐 노드의 데이터를 먼저 읽고 반환한다. 동시에 기다리는 항목만 풀 칸을 쓴다.

The maze includes local `queue.c` and compiles directly with the combined driver. The queue guard avoids duplicate definitions when the tree search is included too. See [lab setup](lab.md).
미로와 트리는 같은 큐를 포함한다. 포함 가드로 정의 중복을 막는다. 실제 소스를 직접 컴파일한다.

## 16. How much work does the search perform? / 탐색은 얼마나 일하는가?

Initialization writes metadata for all 49 cells. Traversal removes each reached passage once and checks four directions for each removal.
초기화는 전체 격자에 기록한다. 탐색은 도달한 통로마다 네 방향을 한 번씩 확인한다.

- Supplied run: 49 metadata initializations, 20 enqueues, 20 dequeues, and 80 neighbor checks.
- For an `R` by `C` maze: initialization O(R·C); traversal O(V_reached) because each reached passage has at most four neighbors.
- Grid metadata and coordinate lookup reserve O(R·C) space. A suitably sized queue also needs at most O(R·C) space.
- Following one returned route takes work proportional to its length. Printing every shortest route additionally depends on the number and lengths of routes printed.

No adjacency matrix is scanned here. Adjacent cells are generated directly from coordinates. The [lab slides](ppt_lab_material.md) turn these predictions into code checks.
