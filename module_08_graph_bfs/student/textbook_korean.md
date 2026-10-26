# Chapter 8. 큐, 트리 BFS, 그래프 BFS

7장은 연결 리스트의 예로 연결 큐를 만들었다. 이번 장은 배열 큐와 저장 방식을 비교한다. 트리 BFS와 그래프 BFS에는 7장의 같은 연결 큐를 재사용한다. 미로의 `lab.c`는 각 통로까지의 최단 거리와 모든 최단 선행 칸을 기록한다.

[English textbook](textbook.md) · [수업 활동](class_material.md) · [개념 슬라이드](ppt_material.md) · [실습 슬라이드](ppt_lab_material.md)

## Thinking Logically

### 들어온 순서대로 처리하려면 어떻게 할까?

7장의 연결 큐를 떠올리자. 요청 17, 23, 31을 들어온 순서대로 처리한다. Stack에서는 31을 먼저 꺼낸다. 뒤에 넣고 앞에서 꺼내야 한다. 먼저 넣은 값을 먼저 꺼내는 규칙을 FIFO(first in, first out)라고 한다. 이 두 동작을 제공하는 구조가 큐(queue)다. 넣기는 enqueue, 꺼내기는 dequeue다.

7장의 값 중심 큐 인터페이스를 그대로 쓴다. `enqueue(value)`는 노드를 할당해 뒤에 붙이고 `true`를 반환한다. 빈 칸이 없으면 큐를 바꾸지 않고 `false`를 반환한다. `dequeue()`는 가장 오래된 값을 반환하고 그 노드를 풀에 돌려준다. 17, 23, 31을 넣으면 같은 순서로 값을 받는다. 첫 삽입은 두 끝을 함께 정하고 마지막 꺼내기는 `head = tail = -1`로 만든다.

하위 함수 `enqueue_lnode(node)`와 `dequeue_lnode()`는 풀 인덱스를 주고받는다. 하위 꺼내기는 빈 큐에서 `-1`을 반환하며 분리한 노드를 재활용하지 않는다. 공개 함수 `dequeue()`가 값을 읽고 노드를 반환한다. 공개 꺼내기 전에는 `is_empty_queue()`를 확인한다. assertion은 비어 있지 않아야 한다는 전제다. 데이터 `-1`도 큐에 넣을 수 있으므로 빈 결과 표시로 쓰지 않는다. 살아 있는 연결이 노드를 소유할 때 풀을 초기화하지 않는다.

### 배열에도 같은 대기 순서를 저장할 수 있을까?

정수를 배열에 직접 저장하면 값마다 연결 노드를 할당할 필요가 없다. `queue[25]`에서 `front`는 다음에 읽을 위치다. `rear`는 마지막으로 쓴 위치다. 독립적인 실행마다 `front = 0; rear = -1;`로 시작한다.

선형 큐에서 `enqueue_linear(17); enqueue_linear(23); enqueue_linear(31);`을 실행하면 위치 0, 1, 2가 유효하다. `dequeue_linear()`는 17을 읽고 front를 1로 옮긴다. 대기 값은 23, 31이다. 이미 읽은 위치를 다시 쓰지는 않는다. 25번 쓰면 `rear == 24`다. 일부 값을 꺼냈어도 같다. 가득 찬 조건은 `rear + 1 == 25`다. 빈 조건은 `front == rear + 1`이다. 25개를 모두 꺼낸 뒤에는 두 조건이 함께 참이다. 대기 값도 없고 새로 쓸 위치도 없기 때문이다.

원형 큐는 인덱스를 25로 나눈 나머지로 바꾸어 앞쪽 위치를 재사용한다. 빈 조건은 `front == (rear + 1) % 25`다. 가득 찬 조건은 `front == (rear + 2) % 25`다. 두 상태를 구분하려고 한 칸을 비워 두므로 25칸에 최대 24개를 넣는다. 0부터 23까지 넣고 0과 1을 꺼낸 뒤 24와 25를 넣자. 새 rear는 0이다. 꺼내는 순서는 여전히 2부터 25까지다.

세 구현은 같은 도착 순서를 다른 저장 방식으로 지킨다. 배열 큐는 `queue`, `front`, `rear`를 공유하므로 한 실행에서 섞지 않는다. 배열 변경 함수는 조건을 검사하지 않는다. 선형 배열 함수 이름은 `enqueue_linear`, `dequeue_linear`, `is_empty_linear`, `is_full_linear`이고 원형 함수는 `_circular`를 쓴다. 연결 큐의 공개 `enqueue`는 풀 소진을 확인하고 Boolean 결과를 준다. 풀은 열 칸이며 다른 활성 리스트가 소유한 칸은 큐가 쓸 수 없다.

### 트리를 한 층씩 처리하려면 어떻게 할까?

트리에서 대기 순서가 어떻게 쓰이는지 보자. root를 처리한 뒤 자식들, 그다음 자식들의 자식을 처리하려 한다. 한 자식을 재귀로 따라가면 다른 자식을 처리하기 전에 깊게 내려간다. 대신 root 인덱스를 큐에 넣는다. 인덱스 하나를 꺼내 데이터를 처리한다. 존재하는 왼쪽 자식과 오른쪽 자식을 그 순서대로 큐에 넣는다. 이 층별 탐색을 너비 우선 탐색(breadth-first search), 줄여서 BFS라고 한다.

2장의 `alphabet_init(); root = tree_connect();`가 만든 트리를 그대로 쓴다. root는 인덱스 5의 F다. F의 자식은 A와 G다. A의 자식은 B와 C다. B의 자식은 D와 E다. 인덱스 7, 8, 9는 배열에 있지만 F에서 연결을 따라 도달하지 않는다.

| 방금 처리한 데이터 | 대기 인덱스 | 대기 데이터 |
| --- | --- | --- |
| 처리 전 | `[5]` | F |
| F | `[0,6]` | A, G |
| A | `[6,1,2]` | G, B, C |
| G | `[1,2]` | B, C |
| B | `[2,3,4]` | C, D, E |
| C | `[3,4]` | D, E |
| D | `[4]` | E |
| E | `[]` | 비었음 |

처리 순서는 **F, A, G, B, C, D, E**다. 깊이는 0, 1, 1, 2, 2, 3, 3이다. `tree_bfs(root, order)`는 이 노드 인덱스를 저장하고 7을 반환한다. 호출자는 인덱스 열 개를 담을 배열을 제공한다. 다른 구조가 노드를 소유하지 않을 때 풀을 초기화하고 `head = tail = -1`로 둔다. root가 `-1`이면 빈 트리이므로 0을 반환한다. 올바른 트리는 순환도 공유 자식도 없다. 각 노드로 가는 경로가 하나이므로 한 번만 큐에 들어간다. 일반 그래프에는 같은 정점으로 가는 경로가 여러 개일 수 있다. 다음 예에서는 중복 예약을 막으려고 발견 기록을 추가한다.

연결 구현의 `head`, `tail`, `next`는 풀 인덱스다. 위 표는 저장한 트리 번호를 보인다. BFS는 `enqueue(tree_id)`와 `dequeue()`로 값을 주고받는다. 노드를 직접 할당하거나 반환하지 않는다. 공개 꺼내기가 칸을 자동 반환한 뒤 자식을 넣는다.

### 가장 적게 움직이는 경로는 어떻게 찾을까?

한 통로에서 출발해 다른 통로에 도착하려 한다. 오른쪽, 왼쪽, 아래, 위로 한 칸 이동할 때마다 한 걸음으로 센다. 벽에는 들어갈 수 없다. 한 경로를 깊이 따라가면 멀리 돌아서 목적지에 도착할 수 있다. 가장 적게 움직이려면 한 걸음 거리의 칸을 모두 확인한 뒤 두 걸음 거리의 칸을 확인해야 한다.

미로를 그래프로 볼 수 있다. 통로 한 칸이 정점이다. 가로나 세로로 맞닿은 두 통로 사이에 간선이 있다. 간선 하나를 지날 때마다 한 걸음이다. 간선을 가장 적게 지나는 경로를 최단 경로(shortest path)라고 한다. 모든 이동을 같은 한 걸음으로 세는 조건이 필요하다. 이번 알고리즘은 서로 다른 간선 비용을 비교하지 않는다.

이번 장은 같은 미로를 계속 사용한다. `0`은 벽이다. `1`은 통로다. 출발점은 `{1,1}`이다. 목적지는 `{5,5}`다.

```text
            x
       0 1 2 3 4 5 6
   y 0 0 0 0 0 0 0 0
     1 0 1 0 1 1 1 0
     2 0 1 1 1 0 1 0
     3 0 1 0 1 1 1 0
     4 0 1 0 1 0 1 0
     5 0 1 1 1 1 1 0
     6 0 0 0 0 0 0 0
```

`struct point`는 `x`, `y` 순서로 좌표를 저장한다. 배열은 행을 먼저 지정한다. 따라서 `{x, y}`의 칸은 `maze[y][x]`다. 예를 들어 `{3,2}`는 `maze[2][3]`을 뜻한다.

### 큐에는 무엇을 넣을까?

연결 큐 노드의 `data`는 정수 하나를 저장한다. 미로의 칸에는 좌표가 둘 있다. 각 칸에 정수 번호 하나를 붙이고 좌표는 별도 배열에 보관하자. 초기화는 각 행을 왼쪽부터 차례로 지난다. 칸 번호는 `7 * y + x`다.

| 칸 | 칸 번호 | 탐색 기록의 위치 | 좌표의 위치 |
| --- | ---: | --- | --- |
| `{1,1}` | 8 | `info[1][1]` | `points[8]` |
| `{3,2}` | 17 | `info[2][3]` | `points[17]` |
| `{5,5}` | 40 | `info[5][5]` | `points[40]` |

`info[7][7]`은 벽을 포함한 모든 칸의 탐색 기록을 보관한다. `points[50]`은 칸 번호로 좌표를 찾게 한다. 초기화는 0번부터 48번까지 채운다. 49번 칸은 쓰지 않는다. 칸 번호는 위치를 나타낸다. 발견 시각이나 거리가 아니다.

### 가까운 칸을 어떻게 먼저 꺼낼까?

출발점의 거리를 0으로 정하고 큐에 넣는다. 앞에서 출발점의 번호를 꺼낸다. 이웃 통로의 거리를 1로 기록하고 번호를 뒤에 넣는다. 이후에도 꺼낸 칸마다 같은 일을 한다. 거리 1인 칸에서 새로 찾은 이웃의 거리는 2가 된다.

큐는 거리 1인 칸을 모두 꺼낸 뒤 거리 2인 칸을 꺼낸다. 이후 거리에서도 같은 규칙이 성립한다. 이 순서로 탐색하는 방법이 breadth-first search다. 줄여서 BFS라고 한다. 칸을 처음 찾는 일을 발견(discovery)이라고 한다. 큐에서 꺼내 이웃을 확인하는 일을 처리(processing)라고 한다. 이미 발견한 칸도 아직 큐에서 기다릴 수 있다.

어떤 칸까지 더 짧은 경로가 있다고 가정하자. 그 경로에서 바로 앞에 있는 칸은 더 일찍 처리된다. 그러면 그 앞 칸이 목적 칸도 더 일찍 발견했어야 한다. 따라서 BFS가 처음 기록한 거리가 최단 거리다.

### 처음 찾은 통로인지 어떻게 알까?

미로에는 순환 경로가 있을 수 있다. 모든 이웃을 그대로 큐에 넣으면 같은 통로를 반복해서 넣게 된다. 각 칸에 거리를 이미 구했는지 남겨야 한다.

`init_info()`는 모든 `distance`를 25로 만든다. 모든 `prev_size`는 0으로 만든다. 거리 25는 아직 거리를 모른다는 표시다. 내부 위치는 최대 25칸이다. 최단 경로는 같은 칸을 반복하지 않는다. 따라서 최단 거리는 최대 24다. 주어진 미로에는 통로가 20칸이므로 실제 상한은 더 작다. 거리 25를 유한한 최단 거리와 구별할 수 있다.

25는 거리의 표시일 뿐이다. 칸 번호 25는 실제로 존재한다. `{4,3}`의 번호가 25다. 25를 없는 칸 번호로 해석하면 안 된다. BFS가 끝난 뒤에도 거리 25인 통로는 출발점에서 도달할 수 없는 통로다. 벽의 거리도 초기값 25로 남는다.

새 통로를 발견하면 큐에 넣기 **전에** 거리와 바로 앞 칸을 기록한다. 다른 경로가 같은 통로에 도착하면 큐에서 기다리는 중이어도 기록한 거리를 볼 수 있다. 같은 번호를 다시 넣지 않는다. 별도의 `discovered` 배열은 필요하지 않다.

### 바로 앞 칸을 왜 여러 개 저장할까?

서로 다른 경로가 같은 걸음 수로 한 통로에 도착할 수 있다. 두 경로를 모두 기억하려면 거리가 하나 작은 이웃을 모두 저장해야 한다. 최단 경로에서 바로 앞에 올 수 있는 칸을 선행 칸(predecessor)이라고 한다.

각 기록에는 `prev[4]`와 `prev_size`가 있다. 유효한 항목은 `prev[0]`부터 `prev[prev_size - 1]`까지다. 각 항목에는 좌표를 저장한다. 한 칸의 이웃은 최대 네 개이므로 네 항목이면 충분하다. 초기화는 개수를 0으로 만든다. 유효 범위 밖에 남아 있는 이전 좌표는 읽지 않는다.

벽을 건너뛴 뒤 이웃 거리와 현재 거리를 비교한다.

| 이웃의 조건 | 동작 |
| --- | --- |
| `neighbor_distance <= cur_distance` | 건너뛴다. 현재 칸에서 이웃으로 이동해도 최단 경로를 연장할 수 없다. |
| `neighbor_distance == cur_distance + 1` | 이웃의 선행 칸에 현재 칸을 추가한다. 이웃을 큐에 다시 넣지 않는다. |
| 새로 초기화한 BFS에서 나머지 경우 | 처음 발견한 통로다. 거리와 첫 선행 칸을 기록하고 번호를 큐에 넣는다. |

새로 시작한 FIFO 탐색에서 나머지 경우는 거리가 25인 미발견 통로다. 이미 발견한 통로에 나중에 더 짧은 경로가 나타나지 않는다. 기록한 거리는 유지된다. 선행 칸의 목록은 늘어날 수 있다.

### 어느 이웃부터 확인할까?

네 방향의 순서를 바꿔도 최단 거리는 같다. 큐에 넣는 순서와 선행 칸의 저장 순서는 달라질 수 있다. 이 실습은 **오른쪽, 왼쪽, 아래, 위** 순서로 확인한다.

`init_iter(cur)`는 현재 좌표를 전역 변수 `cur_point`에 저장한다. 전역 변수 `state`는 0으로 만든다. `next_iter()`는 현재 좌표를 복사하고 한 방향으로 옮긴다. 이어서 `state`를 증가시킨다. 각 `break`는 해당 `switch` 분기를 끝낸다. `break`가 없으면 한 번의 호출에서 여러 좌표 변경을 연달아 실행한다.

현재 칸과 다음 방향을 보관하며 이웃을 하나씩 내주는 장치를 이웃 반복자(neighbor iterator)라고 한다. 이 반복자는 전역 상태를 공유한다. 한 칸의 네 방향을 끝내기 전에 다른 칸으로 초기화하면 안 된다. 현재 BFS는 안쪽 반복문에서 네 방향을 모두 확인한다.

### 대기 중인 번호는 어떻게 바뀔까?

이제 실제 큐를 따라가자. 출발점 `{1,1}`의 번호는 8이다. 처음 큐는 `[8]`이다. 표는 각 칸을 처리한 직후의 유효한 값을 앞에서 뒤 순서로 보여 준다. 꺼낸 값이 배열에 남아 있어도 유효 구간 밖이면 큐의 값이 아니다.

| 꺼낸 번호와 칸 | 거리 | 오른쪽, 왼쪽, 아래, 위를 확인한 뒤 큐 |
| --- | ---: | --- |
| 8 `{1,1}` | 0 | `[15]` |
| 15 `{1,2}` | 1 | `[16,22]` |
| 16 `{2,2}` | 2 | `[22,17]` |
| 22 `{1,3}` | 2 | `[17,29]` |
| 17 `{3,2}` | 3 | `[29,24,10]` |
| 29 `{1,4}` | 3 | `[24,10,36]` |
| 24 `{3,3}` | 4 | `[10,36,25,31]` |
| 10 `{3,1}` | 4 | `[36,25,31,11]` |
| 36 `{1,5}` | 4 | `[25,31,11,37]` |
| 25 `{4,3}` | 5 | `[31,11,37,26]` |
| 31 `{3,4}` | 5 | `[11,37,26,38]` |
| 11 `{4,1}` | 5 | `[37,26,38,12]` |
| 37 `{2,5}` | 5 | `[26,38,12]` |
| 26 `{5,3}` | 6 | `[38,12,33,19]` |
| 38 `{3,5}` | 6 | `[12,33,19,39]` |
| 12 `{5,1}` | 6 | `[33,19,39]` |
| 33 `{5,4}` | 7 | `[19,39,40]` |
| 19 `{5,2}` | 7 | `[39,40]` |
| 39 `{4,5}` | 7 | `[40]` |
| 40 `{5,5}` | 8 | `[]` |

31번을 처리할 때 38번을 처음 발견한다. 거리는 6이다. 첫 선행 칸은 `{3,4}`다. 이후 거리 5인 37번에서도 같은 38번에 도착한다. 같은 거리 분기가 `{2,5}`를 선행 칸에 추가한다. 38번은 큐에 다시 들어가지 않는다.

33번은 목적지 40번을 처음 발견한다. 거리는 8이다. 이후 39번이 다른 선행 칸을 추가한다. 탐색이 끝나면 `info[5][5].prev_size`는 2다. 저장 순서는 `{5,4}`, `{4,5}`다. 완성된 최단 경로는 총 세 개다. `{3,5}`에도 선행 칸이 두 개 있기 때문이다.

출발점 `{1,1}`에서 통로 20칸에 모두 도달한다. 각 통로는 큐에 한 번 들어가고 한 번 나온다. 마지막에는 `head = tail = -1`이다. 20번 꺼낸 뒤 풀 열 칸이 모두 가용 상태다. 동시 대기는 최대 네 개다. 미로 자체는 바뀌지 않는다. 프로그램은 별도의 처리 순서 배열을 저장하지 않는다. 표는 실행 과정을 손으로 추적한 것이다.

### 선행 칸으로 경로를 어떻게 얻을까?

기록한 거리를 보면 출발점에서 멈출 수 있다. 선행 칸으로 한 번 갈 때마다 거리가 정확히 1씩 줄어든다. 선행 칸을 거슬러 간 뒤 순서를 뒤집는 일을 경로 복원(path reconstruction)이라고 한다. `{5,5}`에서 `prev[0]`만 따라가면 다음 경로를 얻는다.

```text
거꾸로: {5,5} <- {5,4} <- {5,3} <- {4,3} <- {3,3}
        <- {3,2} <- {2,2} <- {1,2} <- {1,1}
앞으로: {1,1} -> {1,2} -> {2,2} -> {3,2} -> {3,3}
        -> {4,3} -> {5,3} -> {5,4} -> {5,5}
```

경로에는 아홉 칸이 있다. 이동은 여덟 번이다. `prev[0]`만 선택하면 최단 경로 하나를 얻는다. 유효한 모든 선행 칸을 선택지마다 따로 따라가면 최단 경로 세 개를 모두 얻는다. 목적지의 선행 칸이 두 개라고 해서 전체 경로도 반드시 두 개인 것은 아니다.

출발점의 거리는 0이다. 선행 칸은 없다. 출발점까지의 경로에는 출발점만 있다. 거리가 25인 통로에는 출발점에서 가는 경로가 없다. `lab.c`는 복원에 필요한 기록을 저장한다. 경로를 복원하는 함수는 제공하지 않는다.

### 탐색 전에 무엇을 준비해야 할까?

새 실행에는 이전 거리나 대기 번호가 남아 있으면 안 된다. 호출자가 `init_info()`를 호출한다. 다른 구조가 풀을 소유하지 않을 때 `init_lnodes_pool()`를 호출하고 `head = tail = -1`로 둔다. 바깥 벽 안쪽의 통로를 출발점으로 제공한다. `bfs()`는 출발점의 거리를 0으로 정한다. 앞의 초기화와 출발점 검사는 수행하지 않는다. 배열 비교용 `front`, `rear`는 BFS를 제어하지 않는다.

주어진 미로의 테두리는 모두 벽이다. 따라서 큐에서 꺼내는 통로는 모두 내부에 있다. 내부 통로의 네 이웃 좌표는 0부터 6 사이에 있다. 테두리 칸은 벽 검사에서 걸러지므로 큐에 들어가지 않는다. 이 조건 때문에 이웃을 배열에서 읽을 수 있다. `is_wall()` 자체에는 범위 검사가 없다. 잘못된 출발점을 주거나 테두리를 통로로 열면 같은 보장이 성립하지 않는다.

두 탐색은 **7장의 값 중심 연결 큐**를 쓴다. 내부 풀 위치는 0..9지만 저장한 번호는 9보다 클 수 있다. BFS는 `enqueue(id)`와 `dequeue()`를 호출한다. 앞 함수가 할당과 풀 소진 검사를 맡고, 뒤 함수가 번호를 반환하며 이웃을 넣기 전에 칸을 재활용한다. 열 칸으로 발견 20번을 처리할 수 있다. 기본 출발점의 최대 대기는 4개이고 현재 미로의 모든 출발점에서는 최대 6개다. 다른 그래프는 별도 용량 근거가 필요하다. `enqueue`는 `assert` 밖에서 실행하고 Boolean 결과를 검사한다. `NDEBUG`에서도 삽입 자체가 사라지면 안 된다.

## Calculating Efficiency

### 큐와 트리 BFS는 얼마나 일할까?

넣기와 꺼내기는 정해진 수의 인덱스, 연결, 배열 항목만 바꾼다. 각각 O(1)이다. 열 노드 풀 초기화는 기록 열 개를 방문한다. 풀이 P칸으로 커지면 초기화는 O(P)다. 순회로 앞 노드를 찾는 작업은 별도로 센다.

트리 예는 노드 일곱 개를 처리한다. 노드마다 자식 위치 둘을 확인하므로 열네 번 확인한다. 도달한 노드는 한 번씩 들어가고 나온다. N개를 처리하는 일은 O(N)이다. 순간 대기 수는 가장 넓은 층의 크기와 함께 커질 수 있다. 연결 큐는 꺼낸 큐 노드를 자식을 넣기 전에 반환한다. 일곱 노드 예의 최대 동시 대기는 세 개다. 노드 일곱 칸을 계속 소모하지 않는다. 두 정수 필드를 가진 큐 풀 열 칸과 출력 인덱스 열 개를 예약한다. 크기가 커지는 구현은 최대 대기 수와 출력에 비례한 공간이 필요하다. 최악에는 O(N)이다.

### 미로를 탐색할 때 얼마나 일할까?

예제는 통로 번호 20개를 꺼낸다. 각 통로에서 이웃 네 개를 확인한다. 이웃 검사는 총 80번이다. 거리 기록, 선행 칸 하나 추가, 정수 하나의 삽입과 삭제는 각각 일정한 수의 연산을 쓴다. 이웃을 찾으려고 배열의 행 전체를 훑지 않는다.

도달하는 통로가 `R`개라면 삭제는 `R`번이다. 이웃 검사는 `4R`번이다. 탐색 시간은 O(R)이다. 정점이 `V`개이고 간선이 `E`개인 일반 그래프에서는 도달한 정점과 연결을 확인하므로 BFS의 시간 상한을 O(V + E)로 나타낸다. 이 미로는 통로마다 이웃이 최대 네 개다. 확인할 연결 수도 도달한 통로 수에 비례한다.

초기화는 별도로 칸 기록과 좌표 49개를 모두 쓴다. 높이 `H`, 너비 `W`인 미로의 초기화는 O(HW)다. 도달하는 통로도 전체 칸의 일부다. 따라서 초기화와 탐색을 합친 시간은 O(HW)다. 고정된 7행 7열 프로그램에는 고정된 상한이 있다. 위 표기는 미로 크기를 늘릴 때의 증가를 설명한다.

### 기록에는 얼마나 많은 공간이 필요할까?

프로그램은 미로 정수 49개, 탐색 기록 49개, 좌표 50개, 두 정수 필드의 연결 큐 풀 열 칸을 예약한다. 별도의 배열 비교도 정수 25개를 예약하지만 두 BFS는 그 배열을 쓰지 않는다. 벽의 기록에도 선행 칸 네 항목을 둔다. 예약 공간은 실제로 도달한 통로 수가 아니라 미로 크기에 따라 정해진다. 미로가 커지면 미로와 탐색 기록의 공간은 O(HW)다. 반복문이 추가로 사용하는 지역 공간은 O(1)이다.

예제의 삽입과 꺼내기는 각각 20번이다. 꺼낸 칸은 이웃을 넣기 전에 풀로 돌려준다. `{1,1}`에서 동시에 기다리는 항목은 최대 네 개다. 필요한 풀 용량은 전체 발견 수가 아니라 최대 동시 대기 수로 정한다. 탐색이 끝나면 `head == tail == -1`이고 열 칸이 모두 가용 상태다. 내부 5 × 5칸을 모두 열고 이 방향 순서로 탐색해도 모든 출발점에서 동시 대기는 최대 열 개다. 더 크거나 다른 그래프에 이 상한을 그대로 적용하지 않는다.

### 경로를 복원할 때 얼마나 일할까?

예제 목적지에서 선행 칸 하나씩 선택하면 아홉 칸을 지난다. 이동이 `L`번인 경로에는 `L + 1`칸이 있다. 그 칸을 따라가고 순서를 뒤집는 시간은 O(L + 1)이다. 결과를 담는 공간도 O(L + 1)이다. 저장한 거리가 25인지 확인하는 일은 O(1)이다.

모든 최단 경로를 나열하려면 각 결과 경로를 실제로 써야 한다. 선행 칸의 선택이 여러 곳에서 갈리면 완성되는 경로도 많아질 수 있다. BFS가 선행 칸을 저장했다고 해서 전체 경로를 나열하는 비용이 경로 하나를 따라가는 비용과 같아지지는 않는다.

## Glossary

앞에서 설명한 동작과 기록에 다음 이름을 붙인다.

| 이름 | 이 실습에서의 뜻 |
| --- | --- |
| FIFO / 선입선출 | Remove values in arrival order / 먼저 들어온 값부터 꺼내는 규칙 |
| enqueue, dequeue / 넣기, 꺼내기 | Append at the back, remove from the front / 뒤에 넣고 앞에서 꺼내기 |
| linked queue / 연결 큐 | Pool-node indices connected between head and tail / head와 tail 사이의 풀 노드 연결 |
| linear queue / 선형 큐 | Increasing positions without slot reuse / 위치를 증가시키며 사용한 칸은 재사용하지 않음 |
| circular queue / 원형 큐 | Positions wrap modulo 25; 24 usable slots / 25로 나눈 나머지로 순환하며 24개 저장 |
| level order / 층별 순서 | Process tree nodes by increasing depth / 깊이가 작은 층부터 처리 |
| shortest path / 최단 경로 | 한 칸 이동을 가장 적게 하는 통로 경로 |
| breadth-first search / 너비 우선 탐색 | FIFO로 거리가 작은 칸부터 처리하는 탐색 |
| discovery / 발견 | 통로의 거리를 처음 기록하고 큐에 넣는 일 |
| processing / 처리 | 칸 번호를 꺼내 네 이웃을 확인하는 일 |
| distance / 거리 | 출발점부터의 최소 이동 횟수. 25는 미확정 또는 도달 불가 표시 |
| predecessor / 선행 칸 | 최단 경로에서 출발점 쪽으로 한 걸음 앞선 이웃 통로 |
| cell number / 칸 번호 | 큐에 저장하는 정수 `7 * y + x` |
| active predecessor entries / 유효한 선행 칸 항목 | `prev[0]`부터 `prev[prev_size - 1]`까지 |
| neighbor iterator / 이웃 반복자 | `cur_point`와 `state`로 네 방향을 차례로 내주는 장치 |
| path reconstruction / 경로 복원 | 선행 칸을 거슬러 간 뒤 칸의 순서를 뒤집는 일 |

## Coding Plan

각 단계에서 준비한 기록이 다음 동작에 쓰이도록 순서를 정한다.

1. `queue.c`를 통해 7장의 연결 큐를 가져온다. 이번 장의 선형·원형 배열 큐와 저장 방식을 비교한다.
2. `tree_bfs.c`에서 가져온 연결 큐를 쓴다. 큐 노드의 `data`에 트리 인덱스를 넣는다. 왼쪽 자식을 먼저 넣고 처리한 인덱스를 `order`에 저장한다.
3. 미로와 좌표 자료형을 둔다. 벽은 `0`, 통로는 `1`로 저장한다. 좌표로 읽을 때는 `[y][x]`를 쓴다.
4. 모든 칸에 번호를 붙인다. `info`와 `points`를 채운다. 거리는 25, 선행 칸 개수는 0으로 만든다.
5. 전역 기록의 거리를 읽고 쓴다. 현재 유효 개수 위치에 선행 좌표를 추가한다.
6. 공유 반복자로 오른쪽, 왼쪽, 아래, 위를 만든다. 각 `switch` 분기를 `break`로 끝낸다.
7. `enqueue(start_id)`를 실행하고 Boolean 결과를 저장해 성공을 확인한다. 할당과 삽입은 wrapper가 맡는다. 삽입 호출을 assert 안에 넣지 않는다.
8. `dequeue()`에서 칸 번호를 받는다. 그 큐 노드는 이미 풀로 반환되었다. 좌표를 얻고 벽과 더 이른 거리를 건너뛴다. 같은 거리의 선행 칸을 남기고 처음 발견할 때만 넣는다.
9. 별도 드라이버에서 매번 기록과 소유자가 없는 풀을 초기화하고 연결 큐의 두 끝을 초기화한다. 거리와 유효한 선행 칸을 확인한다. 경로가 필요하면 선행 칸 하나 또는 모든 선택지를 따라간다.

## C Code

큐 코드는 [queue.c](queue.c)에 있다. 7장의 연결 큐와 노드 풀 전체를 정의 중복 없이 가져온다. [tree_bfs.c](tree_bfs.c)는 2장 트리와 같은 큐를 포함한다. 미로 [lab.c](lab.c)는 `queue.c`를 직접 포함한다. 큐 포함 가드는 두 탐색을 함께 쓸 때 정의가 중복되지 않게 한다. 드라이버만 컴파일한다. 포함한 C 파일을 별도 입력으로 다시 컴파일하지 않는다.

### 연결 큐를 가져오고 배열 구현을 비교한다

앞에서 추적한 상태를 다음 함수로 바꾼다.

```c
/* Module 8: compare array queues and reuse Module 7's linked queue.
 * Callers check full/empty conditions and reset independent queue runs.
 */
#ifndef MODULE_08_QUEUE_C
#define MODULE_08_QUEUE_C
#ifndef MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#define MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#include "module_07_linked_list/student/lab.c"
#endif

int queue[25];
int front = 0;
int rear = -1;

void enqueue_linear(int data) {
    queue[++rear] = data;
}

int dequeue_linear() {
    return queue[front++];
}

int is_full_linear() {
    return rear + 1 == 25;
}

int is_empty_linear() {
    return front == rear + 1;
}

void enqueue_circular(int data) {
    rear = (rear + 1) % 25;
    queue[rear] = data;
}

int dequeue_circular() {
    int data = queue[front];
    front = (front + 1) % 25;
    return data;
}

int is_full_circular() {
    return front == (rear + 2) % 25;
}

int is_empty_circular() {
    return front == (rear + 1) % 25;
}

#endif
```

### 7장의 연결 큐로 트리를 처리한다

`nodes[cur].left`와 `.right`에 자식 인덱스가 있다. `-1`은 큐에 넣지 않는다.

```c
/* Reuse Module 7's value-based linked queue for tree-node IDs.
 * Before an independent run, initialize the unowned pool and set head=tail=-1.
 * A valid nonempty tree has no cycles/shared child and at most ten nodes.
 * order has ten slots; root -1 denotes an empty tree.
 */
#include <assert.h>
#include "module_02_binary_tree/student/lab.c"
#include "queue.c"

int tree_bfs(int root, int order[10]) {
    int count = 0;
    if (root == -1) return 0;
    bool added = enqueue(root);
    assert(added);
    (void)added;
    while (!is_empty_queue()) {
        int cur = dequeue(); /* Returns the ID and recycles its queue node. */
        order[count++] = cur;
        if (nodes[cur].left != -1) {
            added = enqueue(nodes[cur].left);
            assert(added);
        }
        if (nodes[cur].right != -1) {
            added = enqueue(nodes[cur].right);
            assert(added);
        }
    }
    return count;
}
```

### 벽과 좌표를 저장한다

바깥 벽 때문에 내부 통로의 이웃은 배열 안에 있다. 좌표 필드의 순서는 `x, y`다. 배열 접근 순서는 `y, x`다.

```c
int maze[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0}
};

struct point {
    int x;
    int y;
};

int is_wall(struct point p) {
    return maze[p.y][p.x] == 0;
}
```

### 칸의 기록을 초기화한다

같은 `pos`로 칸 번호와 역방향 좌표 표를 채운다. 선행 칸 개수가 0이면 예전 좌표 값은 유효하지 않다.

```c
struct maze_node {
    int index;
    int distance;
    struct point prev[4];
    int prev_size;
};

struct maze_node info[7][7];
struct point points[50];

void init_info() {
    int pos = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            info[i][j].index = pos;
            info[i][j].distance = 25;
            info[i][j].prev_size = 0;
            points[pos].y = i;
            points[pos].x = j;
            pos++;
        }
    }
}
```

### 전역 탐색 기록을 바꾼다

변경 함수는 `info`에 직접 기록한다. `prev_size++`는 증가 전 개수를 삽입 위치로 쓰고 개수를 늘린다. BFS의 규칙에 따라 서로 다른 이웃 선행 칸은 최대 네 개다.

```c
int get_index(struct point p) {return info[p.y][p.x].index;}

int get_distance(struct point p) {return info[p.y][p.x].distance;}
void set_distance(struct point p, int dist) {info[p.y][p.x].distance = dist;}

void add_prev(struct point p, struct point from) {
    int pos = info[p.y][p.x].prev_size++;
    info[p.y][p.x].prev[pos] = from;
}
```

### 이웃 네 개를 차례로 만든다

각 호출은 `cur_point`의 복사본에서 시작한다. 앞 호출에서 움직인 결과가 다음 이웃에 누적되지 않는다.

```c
struct point cur_point;
int state;

void init_iter(struct point p) {
    cur_point = p;
    state = 0;
}

int has_next() {return state < 4;}

struct point next_iter() {
    struct point p = cur_point;
    switch (state) {
        case 0: p.x += 1; break;
        case 1: p.x -= 1; break;
        case 2: p.y += 1; break;
        case 3: p.y -= 1; break;
    }
    ++state;
    return p;
}
```

### 거리와 모든 최단 선행 칸을 기록한다

같은 거리 분기는 선행 칸 목록만 바꾼다. 처음 발견한 분기는 큐에 넣기 전에 기록한다. 따라서 여러 최단 경로가 한 번만 큐에 들어간 통로를 공유할 수 있다.

```c
void bfs(struct point start) {
    set_distance(start, 0);
    bool added = enqueue(get_index(start));
    assert(added);
    (void)added;

    while (!is_empty_queue()) {
        int cell_id = dequeue(); /* Returns the ID and recycles its queue node. */
        struct point cur = points[cell_id];
        int cur_distance = get_distance(cur);
        init_iter(cur);
        while (has_next()) {
            struct point neighbor = next_iter();
            if (is_wall(neighbor)) {continue;}
            int neighbor_distance = get_distance(neighbor);
            if (neighbor_distance <= cur_distance) {continue;}
            else if (neighbor_distance == cur_distance + 1) {
                add_prev(neighbor, cur);
            }
            else {
                set_distance(neighbor, cur_distance + 1);
                add_prev(neighbor, cur);
                added = enqueue(get_index(neighbor));
                assert(added);
            }
        }
    }
}
```

### 큐, 트리, 미로를 함께 검증한다

[lab_driver.c](lab_driver.c)는 큐 경계, 원형 재사용, 트리의 정확한 처리 순서, 미로 거리와 모든 선행 칸을 검사한다. 독립 실행 전에 큐를 초기화한다. 미로에서는 기록도 초기화한다. 원래 소스를 직접 빌드한다. DFS 포함문을 지우는 준비 사본은 더 이상 필요 없다.

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

```text
PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches
```

이번 주 제출은 하나다. 큐 세 종류의 추적, 트리 BFS의 대기 순서, 미로 BFS의 발견과 동거리 선행 칸, 최단 경로 하나를 함께 설명한다. `code/`의 검사 기능이 있는 matrix/list API는 선택 참고 자료다.
