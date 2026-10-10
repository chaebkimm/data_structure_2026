# 목차

1. 그래프를 재귀함수로 탐색하기
2. 리스트에 간선 저장하기
3. 끈끈한 그룹의 간선들을 따로 모으기

# 그래프 간선을 저장할 구조체

- 간선에는 양쪽 노드 정보가 들어간다.
- 무방향 그래프이므로, 멤버를 어떻게 저장하던 상관 없지만, 탐색할 때 부모 노드와 자식 노드를 저장한다.

# 그래프 간선 만들기

```c
struct GraphEdge {
 int from, to;
};
struct GraphEdge edges[10];
int edges_size = 0;
```

# 간선을 쉽게 찾게 저장하기

- 이차원 배열을 만들어서, 노드 인덱스 두개를 가지고 간선 리스트에서 어디 저장되어있는지를 찾을 수 있게 만든다.
- 무방향그래프이므로, 노드 인덱스 순서는 두가지 조합이 가능하다.

# 간선 저장하기

```c
int edge_index[10][10] = {0};

void add_edge(int u, int v) {
 int index = edges_size++;
 edges[index].from = u;
 edges[index].to = v;

 edge_index[u][v] = index;
 edge_index[v][u] = index;
}
```

# 그래프에서 반복할 준비하기

- 방문 시간
- 방문 번호를 저장할 배열
- 방문 트리에서의 부모 노드 인덱스

# 복습 - 발견 순서를 번호로 저장

```c
int visit_num[10] = {0};
int visit_time = 0;
int parent[10] = {0};
```

# 그래프에서 반복할 준비하기

```c
void init_visit() {
 visit_time = 0;
 for (int i = 0; i < nodes_size;
      i++) {
  visit_num[i] = 0;
  parent[i] = -1;
 }
}
```

# 그래프에서 반복하기

1. 한 노드의 이웃들에 대해서 반복한다.
2. preorder 시점에 방문 번호를 저장한다.
3. 이웃의 종류에 따라 적절하게 처리한다.
4. postorder 시점에 필요한 작업을 한다.

# 이웃의 종류

- 트리 간선의 자식 노드: 아직 탐색되지 않은 노드다. 부모 노드를 설정하고, 재귀호출한다.
- 트리 간선의 부모 노드: 반대 방향에서 처리됐기 때문에 작업을 안한다.
- 빽 간선의 조상 노드: 필요한 작업을 한다. 탐색된 노드이기 때문에 재귀 호출은 안한다.
- 빽 간선의 후손 노드: 반대 방향에서 처리됐기 때문에 작업을 안한다.

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

# 간선을 재귀 함수로 탐색하기

```c
void _edge_iteration_(int n){
 visit_num[n] = ++visit_time;
 for (int i = 0; i < nodes[n]
      .adj_size; i++) {
  int adj =nodes[n].adj_list[i];
  if (visit_num[adj] == 0) {
   /* tree edge to child */
   parent[adj] = n;
   _edge_iteration_(adj);
  } else if (adj == parent[n]) {
   /* tree edge to parent */
  } else if (visit_num[adj]
             < visit_num[n]){
   /* back edge to ancester */
  } else if (visit_num[adj]
             > visit_num[n]) {
   /*back edge to descendant*/
  }
 }
 /* postorder processing */
}
```

# 이웃 리스트의 간선 정보 저장

- 트리 간선은 자식 노드를 방문할 때 저장한다.
- 빽 간선은 조상 노드를 방문할 때 저장한다.

```c
/* tree edge */
add_edge(n, adj);
parent[adj] = n;
_init_edges_list(adj);

/* back edge to ancester */
add_edge(n, adj);
```

# 간선 정보 저장 준비하고 실행하기

1. 방문 번호와 시간 초기화
2. 리스트 크기 0으로 설정
3. 간선 인덱스 이차원 배열 -1로 설정.
4. 간선 정보 저장하기

```c
void init_edges_list(int root) {
 init_visit();
 edges_size = 0;
 for (int i = 0; i < nodes_size;
      i++) {
  for (int j = 0;
       j < nodes_size; j++) {
   edge_index[i][j] = -1;
  }
 }
 _init_edges_list(root);
}
```

# 끈끈하게 연결된 그래프

- 끈끈하게 연결된 그래프는 모든 노드가 두 개 이상의 서로 노드가 겹치지 않는 경로로 이어져 있다.
- 어떤 노드는 여러 끈끈하게 연결된 그래프에 속할 수 있다.
- 간선 하나와 노드 두개도 최소한의 끈끈한 그래프라고 친다.
- 모든 간선은 하나의 끈끈한 그래프에만 속한다.
- 끈끈한 그래프를 거기에 속한 간선들로 표현할 수 있다.

```c
int bcc[10][45];
int bcc_size[10] = {0};
int current_bcc = 0;
```

# 끈끈한 그래프와 빽번호

- 빽 간선이 노드들을 끈끈하게 이어준다.
- 빽 간선이 없으면 조상과 끈끈하지 않다.
- 빽 번호가 자신의 방문 번호면 부모 노드와 간선 하나만으로 끈끈하다.
- 빽 번호가 부모의 방문 번호면 부모 노드와 후손들이 끈끈하다.

# 끈끈한 간선들 찾기

- 재귀 함수로 반복하는데, postorder로 가장 후대에서부터 확인한다. 빽번호가 자기 자신이거나 부모인 경우 간선들을 끈끈한 간선들로 분리한다.
- preorder에서는 간선을 스택에 추가한다.

# C 문법 - do while

한 번 먼저 실행하고 조건을 봐서 반복

```c
do { 반복할내용 } while (조건);
```

조건에서 쓸 변수는 do 전에 만들어 놓아야 한다.

# 복습 - 빽 번호 저장

```c
/* preorder processing */
visit_num[n] = ++visit_time;
back[n] = visit_num[n];

/* tree edge */
parent[adj] = n;
save_back (adj);
if (back[n] > back[adj]) {
 back[n] = back[adj];
}
/* back edge to ancester */
if (back[n] > visit_num[adj]) {
 back[n] = visit_num[adj];
}
```

# 끈끈한 간선들 찾기

```c
/* tree edge */
push(edge_index[n][adj]);
parent[adj] = n;
_find_bcc(adj);

/* back edge to ancester */
push(edge_index[n][adj]);
```

```c
/* postorder processing */
if (parent[n] == -1
    || back_num[n]
     < visit_num[parent[n]]) {
 return;
}
int parent_edge
 = edge_index[parent[n]][n];

int cur = current_bcc++;
int pos = 0;

int edge;
do {
 edge = pop();
 bcc[cur][pos++] = edge;
} while (edge != parent_edge);

bcc_size[cur] = pos;
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
