# Chapter 8 Class Workbook — Processing data in stored order

Use the [concept questions](ppt.md), [code questions](ppt_lab.md), and current [lab.c](lab.c). Write predictions first. Preserve the original answer when adding a correction. Coordinates below are always `{y, x}`; queue entries are shown front to back.

Follow the frozen [Korean textbook](textbook_korean.md), **저장된 순서대로 데이터 처리하기**, and its [English edition](textbook.md). Use the textbook’s [Invariant](textbook.md#invariant) section to explain why pending distances never decrease from front to back. The [New C syntax explained](textbook.md#new-c-syntax-explained) section covers row-by-row array initialization, whole-structure copying/passing/returning, and short-circuit logical OR. `enum`, increment operators, `switch`/`break`, and `continue` are review. 교재의 규칙과 새 C 문법 설명을 상태 추적과 연결한다. 구체적인 숫자와 노드 예제는 이 활동에서 다룬다.

## 1. How do front and rear change? / 앞과 뒤는 어떻게 변하는가?

We want to remove the earliest waiting coordinate. In a nonempty queue, `front` is the index of its first stored data and `rear` is the index of its last stored data. Trace the array queue without moving remaining data. 비어 있지 않은 큐에서 `front`는 첫 데이터의 인덱스이고, `rear`는 마지막 데이터의 인덱스다. 먼저 기다린 좌표부터 꺼낸다. 남은 data는 옮기지 않는다.

| Operation / 동작 | `front` | `rear` | Returned / 반환 | Pending / 대기 순서 |
| --- | --- | --- | --- | --- |
| `init_queue()` | | | | |
| `enqueue({1,1})` | | | | |
| `enqueue({2,1})` | | | | |
| `enqueue({2,2})` | | | | |
| `dequeue()` | | | | |
| `dequeue()` | | | | |
| `dequeue()` | | | | |

An empty queue has no first or last data. Its index values describe the empty state; old values outside the pending range are not queue data. 빈 큐에는 첫 데이터와 마지막 데이터가 없다. 대기 범위 밖에 남은 옛 값은 큐에 속하지 않는다.

The enqueue notation abbreviates a `struct point` value. Explain prefix `++rear` and postfix `front++`. Why is `front > rear` empty? Why does an empty queue still lack space for another write after 25 writes? 위 표의 enqueue 표기는 구조체 값을 줄여 쓴 것이다. 증가 연산 시점과 빈 큐 조건을 설명한다.

Which part of `0 <= front <= rear + 1 <= N * N` describes these valid states? Which condition must the caller check before a direct enqueue or dequeue? 유효한 상태를 나타내는 범위와 호출 전에 확인할 조건을 구분한다.

Prediction and correction / 예상과 수정: ______________________________

For a circular comparison, keep front/rear as the indices of the first/last queued data when nonempty, reserve one of 25 slots, and wrap both positions. Use empty `front == (rear + 1) % 25` and full `front == (rear + 2) % 25`. Fill labels 0–23, remove two, append 24/25. Predict endpoints and the next value. 원형 큐는 종이에서 비교한다. 실제 미로 코드는 선형 큐다.

Circular result and reason / 순환 결과와 이유: ________________________

## 2. What waits at each tree level? / 트리의 층마다 무엇이 기다리는가?

Process root A, then its children B/C. B has D/E and C has left child F. Enqueue left before right. A의 자식은 B/C, B의 자식은 D/E, C의 왼쪽 자식은 F다. 이 트리는 설명용 예다.

| Processed / 처리 | Pending / 대기 | Depth of processed node / 깊이 |
| --- | --- | --- |
| Before / 시작 전 | A | — |
| A | | |
| B | | |
| C | | |
| D | | |
| E | | |
| F | | |

Explain why a stack changes the processing order. Record the root's distance as zero and each child's distance as its parent's distance plus one before enqueueing the child. Why does child-only traversal of a valid tree not need a discovery flag, while a graph can need one? 스택과 큐의 선택, 층 기록, 중복 발견의 차이를 설명한다.

For the graph comparison, use a stack of pending nodes and mark a node processed when it is popped for the first time. An unprocessed neighbor may be pushed again even if an older copy is still waiting; skip an already processed node when it is popped. Explain how a later copy can be selected before the older one, while a duplicate added to the back of a queue cannot advance its first processing. This is the pending-node stack method in the concept PPT, not a change to the maze BFS. 그래프의 스택 비교에서는 아직 처리하지 않은 이웃을 중복 추가할 수 있지만, 꺼낼 때 이미 처리한 노드이면 건너뛴다.

Reason / 이유: ______________________________________________________

## 3. Which array cell does a point mean? / 좌표는 어느 칸을 뜻하는가?

A row is y and a column is x. The type stores y before x. `struct point p = {2,3}` therefore means `maze[2][3]`. 행은 y, 열은 x다. 큐에는 이 구조체 값을 그대로 넣는다.

| Point / 좌표 | Array access / 배열 접근 | Wall or passage / 벽 또는 통로 |
| --- | --- | --- |
| `{1,1}` | | |
| `{1,2}` | | |
| `{2,3}` | | |
| `{3,3}` | | |

From `{2,2}`, list the four results of `next_iter()` and the value of `state` after each call. Explain why `p` is copied from `cur_point` every time. `{2,2}`의 네 이웃과 호출 뒤의 state를 순서대로 쓴다.

Explain how one inner brace pair initializes a maze row and how copying `struct point` copies both coordinates. Why can `enqueue` receive a whole point and `dequeue` return one? In the BFS condition, when does `||` omit the distance read? Then review how `break` stops one direction case and `continue` skips one neighbor. 행별 초기화, 구조체 복사·전달·반환, 논리 OR의 단축 평가를 설명한다. 두 제어문의 범위는 복습한다.

Neighbor trace / 이웃 추적: __________________________________________

## 4. What waits after each passage? / 각 통로를 처리한 뒤 무엇이 기다리는가?

Start at `{1,1}`. `bfs` initializes all 25 distances and the queue. Fill the rows using right, left, down, up. 출발지에서 새로 발견한 통로는 거리를 먼저 기록하고 큐에 넣는다.

| Processed point / 처리한 좌표 | Its distance / 거리 | Queue afterward / 처리 뒤 큐 | Newly discovered / 새 발견 |
| --- | --- | --- | --- |
| Initial / 초기 | — | | |
| `{1,1}` | | | |
| `{2,1}` | | | |
| `{2,2}` | | | |
| `{3,1}` | | | |
| `{2,3}` | | | |
| `{3,2}` | | | |
| `{3,3}` | | | |
| `{1,3}` | | | |

When `{3,1}` checks `{3,2}`, the neighbor is still waiting. What prevents another enqueue? Would marking only on dequeue give the same waiting list? `{3,2}`를 아직 꺼내지 않았는데도 다시 넣지 않는 이유를 쓴다.

Reason / 이유: ______________________________________________________

## 5. What does the final distance mean? / 마지막 거리 기록은 무엇을 뜻하는가?

Fill the distance grid. Write `INF` for walls and unreachable passages; use the maze value to distinguish them. 벽과 도달하지 못한 통로는 거리 값만으로 구분할 수 없다.

```text
      x=0  1  2  3  4
y=0    __ __ __ __ __
y=1    __ __ __ __ __
y=2    __ __ __ __ __
y=3    __ __ __ __ __
y=4    __ __ __ __ __
```

Explain why the first distance of `{3,3}` is minimum when each move costs one step. Write one shortest route, count its edges, and explain how saving the discovering current point as the parent cell on first discovery could recover it. Follow those parent cells backward from the target, then reverse the collected route. The current lab stores no predecessor array. 처음 기록한 거리가 최단 거리인 이유를 설명한다. 부모 칸 저장과 경로 복원은 개념 확장이다.

Distance, route, and reason / 거리, 경로, 이유: ________________________

## 6. Which fresh runs do we expect? / 다시 탐색하면 무엇이 바뀌는가?

Each call resets the queue and distances. Predict before running a separate driver. 모든 bfs 호출은 초기화부터 시작한다.

| Experiment / 실험 | Expected result / 예상 | Observed result and correction / 관찰과 수정 |
| --- | --- | --- |
| Baseline start `{1,1}`, target `{3,3}` | | |
| Reverse start `{3,3}`, target `{1,1}` | | |
| In-bounds wall start `{0,0}` | | |
| Temporarily block `{2,1}`, start `{1,1}` | | |
| Restore `{2,1}`, repeat baseline | | |

Keep the zero border. Do not call an out-of-range start or dequeue an empty queue. Make temporary maze changes only in the driver. 테두리를 유지한다. 실험은 lab.c 수정 없이 드라이버에서 한다.

## 7. How much work did we do? / 얼마만큼의 일을 했는가?

Apply the textbook's queue-capacity and constant-time-operation explanations to a complete run. Count the actual operations before naming their growth. 큐 용량과 추가·꺼내기의 비용 설명을 전체 탐색에 적용한다. 실제 횟수를 센 뒤 크기가 늘 때의 비용을 쓴다.

| Work / 작업 | Baseline count / 현재 횟수 | General grid / 일반 격자 |
| --- | --- | --- |
| Initialize distances / 거리 초기화 | | |
| Enqueue / 추가 | | |
| Dequeue / 꺼내기 | | |
| Check neighbor candidates / 이웃 후보 확인 | | |
| Peak pending / 최대 대기 | | |
| Reserved queue positions / 큐 예약 공간 | | |

Explain why three waiting points at peak do not make three slots sufficient for this linear queue. Distinguish reset work, traversal work, reserved storage, and a hypothetical path-output cost. 최대 대기 수와 초기화 사이의 전체 추가 수를 구분한다.

Reason / 이유: ______________________________________________________

## Expected checkpoints / 예상 확인

Read after preserving your predictions. 예상 기록을 보존한 뒤 비교한다.

1. Linear endpoints after three enqueues are 0/2. Removals return `{1,1}`, `{2,1}`, `{2,2}`, ending at 3/2. After 25 writes/removals, 25/24 is empty but has no next write position. Circular comparison ends at front 2/rear 0 with 24 values; next is label 2.
2. Tree queues after A/B/C/D/E/F are `[B,C]`, `[C,D,E]`, `[D,E,F]`, `[E,F]`, `[F]`, `[]`. Order A/B/C/D/E/F has depths 0/1/1/2/2/2. A valid tree gives each nonroot node one parent and has no cycle. In the graph stack comparison, a later copy waits above the older copy; already processed copies are discarded before inspecting neighbors. BFS instead records discovery before enqueue and never adds another copy.
3. `{1,2}` is a wall; the other listed points are passages. From `{2,2}`, the iterator returns `{2,3}`, `{2,1}`, `{3,2}`, `{1,2}`, ending at states 1/2/3/4. An inner initializer brace pair gives one row. A copied point has independent `y` and `x` members; whole-point arguments and return values are permitted. If `is_wall(p)` is true, `||` skips `get_distance(p)`.
4. Maze queues after the listed eight points are `[{2,1}]`, `[{2,2},{3,1}]`, `[{3,1},{2,3},{3,2}]`, `[{2,3},{3,2}]`, `[{3,2},{3,3},{1,3}]`, `[{3,3},{1,3}]`, `[{1,3}]`, `[]`. Processing distances are 0/1/2/2/3/3/4/4. The pending `{3,2}` already has distance 3, so it is skipped. Pending distances stay nondecreasing from front to back; each point enters once.
5. Non-wall distance rows are row 1: `0, wall, 4`; row 2: `1,2,3`; row 3: `2,3,4`. One shortest route is `{1,1}→{2,1}→{2,2}→{2,3}→{3,3}`, four moves. Earlier levels are processed first, so any shorter route would have discovered the target earlier.
6. Reverse distance is 4. A wall start leaves every distance `INF` and front 0/rear -1. Blocking `{2,1}` isolates the start; only it has distance 0, and the open target remains `INF`. Restoring that passage restores the baseline.
7. Counts: 25 reset writes, eight enqueues, eight dequeues, 32 neighbor candidates, three peak pending points, 25 reserved queue positions. Final endpoints are front 8/rear 7. For R×C cells and P reached passages, reset/storage are O(RC) and traversal is O(P). The queue uses eight write positions even though only three points wait at once.
