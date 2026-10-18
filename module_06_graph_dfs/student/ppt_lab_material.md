# 목차

1. 그래프를 재귀함수로 탐색하기
2. 리스트에 간선 저장하기
3. 끈끈한 그룹의 간선들을 따로 모으기

# 복습 - 그래프 반복에 필요한 것

- 방문 시간
- 방문 번호를 저장할 배열
- 방문 트리에서의 부모 노드 인덱스

```c
int visit_num[10] = {0};
int visit_time = 0;
int parent[10] = {0};
```

# 복습 - 그래프 노드

```c
struct GraphNode {
  char data;
  int adj_list[10];
  int adj_size;
};
struct GraphNode nodes[10];
int nodes_size = 0;
```

# 그래프에서 반복하기

1. preorder 시점에 방문 번호를 저장하고, 필요한 작업을 한다.
2. 노드의 이웃들에 대해서 반복하고, 이웃의 종류에 따라 재귀 호출을 하기도 하고, 적절하게 처리한다.
3. postorder 시점에 필요한 작업을 한다.

# 이웃의 종류

- 트리 간선의 자식 노드: 아직 탐색되지 않은 노드다. 부모 노드를 설정하고, 재귀호출한다.
- 트리 간선의 부모 노드: 반대 방향에서 처리됐기 때문에 작업을 안한다.
- 빽 간선의 조상 노드: 필요한 작업을 한다. 탐색된 노드이기 때문에 재귀 호출은 안한다.
- 빽 간선의 후손 노드: 반대 방향에서 처리됐기 때문에 작업을 안한다.

# 간선을 재귀 함수로 탐색하기

```c
void _edge_iteration_(int u){
  /* preorder 타이밍 */
  visit_num[u] = ++visit_time;
  for (int i = 0; i < nodes[u]
       .adj_size; i++) {
    int v =nodes[u].adj_list[i];
    if (visit_num[v] == 0) {
      /* 트리간선 자식 노드 */
      parent[v] = u;
      _edge_iteration_(v);
    } else if (v == parent[u]) {
      /* 트리간선 부모 노드 */
    } else if (visit_num[v]
               < visit_num[u]) {

      /* 빽간선 조상 노드 */
    } else if (visit_num[v]
               > visit_num[u]) {
      /* 빽간선 후손 노드 */
    }
  } /* postorder 타이밍 */
}
```

# 간선 탐색 준비하기

1. 방문 시간 초기화
2. 방문 번호 초기화
3. 부모 노드 초기화

```c
void init_visit() {
  visit_time = 0;
  for (int i = 0;
       i < nodes_size; i++) {
    visit_num[i] = 0;
    parent[i] = -1;
  }
}
```

# 간선 리스트와 이웃 행렬

- 리스트를 만들어서 전체 간선을 저장한다.
- 간선 개수 ≤ (노드 개수(노드 개수 − 1)) / 2
- 이차원 배열을 만들어서, 노드 인덱스 두개를 가지고 간선 인덱스를 저장한다.

```c
struct GraphEdge {
  int from, to;
};
struct GraphEdge edges[45];
int edges_size = 0;
int edge_index[10][10] = {0};
```

# 간선 하나 저장하기

- 무방향 그래프 간선은 리스트에 저장할 때 한쪽 방향만 저장한다.
- 이웃 배열에 간선을 저장할 때는 찾기 쉽게 양쪽 방향을 모두 저장한다.

```c
void add_edge(int u, int v) {
  int index = edges_size++;
  edges[index].from = u;
  edges[index].to = v;
  edge_index[u][v] = index;
  edge_index[v][u] = index;
}
```

# 전체 간선 저장하기

- 트리 간선은 자식 노드를 방문할 때 저장한다.
- 빽 간선은 조상 노드를 방문할 때 저장한다.

```c
/* 트리간선 자식 노드 */
add_edge(u, v);

/* 빽간선 조상 노드 */
add_edge(u, v);
```

# 전체 간선 저장 준비하고 실행하기

1. 간선 탐색 준비하기
2. 간선 리스트 크기 0으로 초기화
3. 이웃 행렬 -1로 초기화.
4. 간선 정보 저장 함수 실행

```c
void init_edges_list(int root) {
  init_visit();
  edges_size = 0;
  for (int i = 0;
       i < nodes_size; i++) {
    for (int j = 0;
         j < nodes_size; j++) {
      edge_index[i][j] = -1;
    }
  }
  _init_edges_list(root);
}
```

# 복습 - 빽 번호 저장하기

- 빽번호는 자신이나 후손의 빽간선 하나를 통해 도달할 수 있는 가장 먼 조상의 방문 번호.
- 자신의 방문 번호, 조상의 방문 번호, 후손의 빽 번호 중 최소값

```c
/* preorder 타이밍 */
back[u] = visit_num[u];
    /* 트리간선 자식 노드 */
    /* 재귀 호출 후 */
    if (back[u] > back[v]) {
      back[u] = back[v];
    }
    /* 빽간선 조상 노드 */
    if (back[u]
        > visit_num[v]) {
      back[u] = visit_num[v];
    }
```

# 끈끈하게 연결된 그래프 리스트

- 끈끈하게 연결된 그래프는 모든 노드가 두 개 이상의 서로 노드가 겹치지 않는 경로로 이어져 있다.
- 간선 하나도 끈끈한 그래프라고 친다.
- 간선 리스트의 리스트를 만든다.
- 끈끈한 그룹 개수 ≤ 노드 개수 − 1

```c
int bcc[9][45];
int bcc_size[9] = {0};
int current_bcc = 0;
```

# 끈끈한 그래프를 찾는 방법

- DFS로 뻗어나가면서 간선들을 스택에 저장한다.
- DFS로 최대한 간 다음에 돌아오면서 끈끈한 그래프들만 스택에서 뺀다.
- 스택의 탑 쪽에 현재 처리중인 끈끈한 그래프 간선들이 모여있다.

# 스택에서 끈끈한 그래프 모으기

- 현재 처리 중인 DFS로 뻗어나가면서 간선들을 스택에 저장한다.
- DFS로 최대한 간 다음에 돌아오면서 끈끈한 그래프들만 스택에서 뺀다.

# C 문법 - do while

한 번 먼저 실행하고 조건을 봐서 반복

```c
do { 반복할내용 } while (조건);
```

조건에서 쓸 변수는 do 전에 만들어 놓아야 한다.

# 끈끈한 그래프를 찾는 방법

```c
void close_bcc(int boundary) {
  int cur = current_bcc++;
  int pos = 0;
  int edge;
  do {
    edge = pop();
    bcc[cur][pos++] = edge;

  } while (edge != boundary);
  bcc_size[cur] = pos;
}
```

# 끈끈한 그래프와 빽번호

- 빽 번호가 조상의 방문 번호면 부모 노드, 후손들, 조상들이 끈끈하다.
- 빽 번호가 부모의 방문 번호면 부모 노드와 후손들이 끈끈하다.
- 빽 번호가 자신의 방문 번호면 부모 노드와 간선 하나만으로 끈끈하다.

# 끈끈한 간선들 찾기

- 트리 간선의 자식 노드에서 간선을 스택에 추가한다.
- 자식 노드의 빽번호가 조상에 닿지 않으면 스택에서 트리 간선 이후의 간선들을 꺼내서 끈끈한 그래프로 만든다.

```c
/* 트리간선의 자식 노드 */
/* 재귀 호출 전 */
int tree_edge
  = edge_index[node][adj];
push(tree_edge);

/* 재귀 호출 후 */
if (back_num[adj]
    < visit_num[node]) {
  continue;
}
close_bcc(tree_edge);
```

```c
/* 빽간선 조상 노드 */
int back_edge
  = edge_index[node][adj];
push(back_edge);
```

# 끈끈한 간선 찾기 준비 및 실행

1. 방문 번호와 시간 초기화
2. 빽 번호 계산
3. 스택 비우기
4. 방문 번호와 시간 초기화
5. 끈끈한 간선 찾기

# 간선 정보 저장 준비하고 실행하기

```c
void find_bcc(int start_node) {
  init_visit();
  save_back_num(start_node);
  top = -1;
  init_visit();
  _find_bcc(start_node);
}
```
