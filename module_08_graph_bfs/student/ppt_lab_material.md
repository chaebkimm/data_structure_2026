# 자료구조 - 요약

10주차 – 큐와 BFS 코드

## 목차

1. 미로를 코드로 표현하기
2. 반복하는 방법이 복잡할 때
3. 큐를 배열로 쉽게 쓰는 방법
4. 미로에서 출발지로부터의 거리 찾기

## 미로를 코드로 표현하기

- 미로의 좌표를 이차원 배열로 나타낸다.
- 좌표축으로 행과 열 인덱스를 쓴다.
- 갈 수 없는 좌표는 0으로 표시하고, 갈 수 있는 좌표는 1로 표시한다.
- 테두리는 갈 수 없게 만들어서 이웃을 찾을 때 인덱스 범위 초과를 방지한다.

## 미로를 표현하는 C 코드

```c
int maze[5][5] = {
  {0, 0, 0, 0, 0},
  {0, 1, 0, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0}
};
```

## 좌표를 코드로 표현하기

- 행에 해당하는 y좌표와 열에 해당하는 x좌표를 구조체로 만든다.
- 초기값을 정하는 코드에서 원점은 왼쪽 위가 된다.

## 좌표를 표현하는 C 코드

```c
struct point {
  int y, x;
};
```

## 특정 좌표가 막혀있는지 확인

- 이차원 배열에서 y 좌표와 x 좌표의 인덱스에 저장된 값을 확인한다.
- 저장된 값이 0이면 갈 수 없는 벽이고 1이면 갈 수 있는 통로다.

## 좌표가 벽인지 확인하는 C 코드

```c
int is_wall(struct point p) {
  return maze[p.y][p.x] == 0;
}
```

## 어떤 좌표의 이웃들에 반복하는 법

- 반복할 순서를 정해놓는다.
- 현재 좌표와 몇 번째 반복 중인지를 기억해둔다.
- 현재 반복 중인 이웃의 좌표는 현재 좌표, 현재 몇 번째 반복 중인지를 가지고 계산한다 (동서남북 순서).

## 어떤 좌표의 이웃들에 반복하는 법

- 초기 상태: 현재 좌표를 저장한다. 반복 상태를 0으로 한다.
- 반복 조건: 현재 상태가 0부터 3까지.
- 반복 진행: 이웃 좌표를 계산해서 알려준다. 상태를 1 증가시킨다.

## 좌표의 이웃들에 반복하는 C 코드

```c
struct point cur_point;
int state;

void init_iter(struct point p) {
  cur_point = p;
  state = 0;
}
```

## 좌표의 이웃들에 반복하는 C 코드

```c
int has_next(void) {
  return state < 4;
}
struct point next(void) {
  struct point p = cur_point;
  switch (state) {
    case 0: p.x += 1; break;
```

## 좌표의 이웃들에 반복하는 C 코드

```c
    case 1: p.x -= 1; break;
    case 2: p.y += 1; break;
    case 3: p.y -= 1; break;
  }
  ++state;
  return p;
}
```

## 큐와 그래프의 BFS 탐색

- 각 좌표를 노드로 보면 이웃한 통로 노드 간에는 간선이 있다고 볼 수 있다.
- 그래프 노드를 방문할 때 마다 새로운 이웃들을 큐에 추가하면 출발지에서 가까운 노드들 순서대로 방문할 수 있다.
- 용량은 노드 전체 저장 가능하면 된다.

## 큐를 배열로 구현하는 방법

- 제일 앞과 제일 뒤 인덱스를 기억해둔다.
- 데이터 추가는 제일 뒤 다음에 한다.
- 데이터 삭제는 제일 앞에서 한다.
- 마지막 데이터를 삭제해서 제일 앞이 한 칸 다음으로 가면, 제일 앞이 제일 뒤보다 1 더 크게 된다.

## 큐에 데이터를 추가하는 C 코드

```c
struct point queue[25];
int front, rear;

void enqueue(struct point data){
  queue[++rear] = data;
}
```

## 큐에서 데이터를 삭제하는 C 코드

```c
struct point dequeue(void) {
  return queue[front++];
}
int is_empty_queue(void) {
  return front > rear;
}
```

## 큐를 초기화 하는 C 코드

```c
void init_queue(void) {
  front = 0; rear = -1;
}
```

## 미로에서 출발지와 거리 측정하기

- 처음에는 테두리 안에 있는 출발지 좌표에서 시작한다.
- 반복할 때마다 새로운 이웃의 거리를 업데이트하고 큐에 추가한다.
- 모든 이웃을 확인했으면 큐에서 좌표를 꺼내서 다시 반복한다.

## 미로 거리 측정 초기화 작업

- 출발지를 제외한 모든 좌표의 거리를 무한대에 해당하는 값으로 저장한다. 전체 좌표 개수면 충분하다.
- 출발지의 거리는 0으로 한다.
- 큐를 초기화하고, 큐에 출발지를 추가한다.

## 미로 거리 측정 초기화 C 코드

```c
int dist[5][5];

void init_bfs(struct point s) {
  init_queue();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++){
      dist[i][j] = 25;
```

## 미로 거리 측정 초기화 C 코드

```c
    }
  }
  if (is_wall(s)) { return; }
  dist[s.y][s.x] = 0;
  enqueue(s);
}
```

## 미로 거리 측정에서 반복할 일

- 현재 좌표는 큐에서 하나 가져오면 된다.
- 현재 좌표 이웃들에 반복할 준비를 한다.
- 만약 이웃이 벽이거나 이미 발견됐으면 건너뛴다.
- 처음 이웃을 발견했을 때 거리를 업데이트 하고 큐에 추가한다.

## 미로 거리 측정 C 코드

```c
void bfs(struct point start) {
  init_bfs(start);

  while (!is_empty_queue()) {
    struct point c = dequeue();
    init_iter(c);
```

## 미로 거리 측정 C 코드

```c
    while (has_next()) {
      struct point p = next();
      if (is_wall(p) ||
          dist[p.y][p.x] != 25){
        continue;
      }
```

## 미로 거리 측정 C 코드

```c
      dist[p.y][p.x]
        = dist[c.y][c.x] + 1;
      enqueue(p);
    }
  }
}
```
