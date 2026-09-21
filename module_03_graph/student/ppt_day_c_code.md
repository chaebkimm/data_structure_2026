# 복습 - 무방향 그래프 노드

노드에는 데이터와 연결된 노드에 대한 정보가 들어 있다. 
연결된 노드 정보는 리스트로 관리한다.

# 노드를 저장할 배열 리스트 생성

배열 리스트의 용량을 정한다.
노드를 저장할 수 있는 배열을 만든다.
저장된 데이터의 개수를 기록한다. 

# 그래프 노드 만들기

```c
struct GraphNode {
  char data;
  int adj_list[10];
  int adj_size;
};
struct GraphNode nodes[10];
int nodes_size = 0;
```

# 복습 - 배열 리스트에 노드 저장

배열의 각 노드에 데이터를 저장한다. 
연결된 노드 리스트에는 저장된 노드 개수를 0개로 초기화한다. 

# 그래프 노드 초기화

```c
void alphabet_nodes_init() {
  nodes_size = 10;
  for (int i = 0; i < 10; i++) {
    nodes[i].data = 'A' + i;
    nodes[i].adj_size = 0;
  }
}
```

# 복습 - 간선 정보로 노드 연결하기

간선은 노드 두 개로 구성된다.
각 노드에서 상대 노드를 이웃 리스트에 추가한다.

# C 문법 - 이차원 배열

배열을 묶어 놓은 배열 (배열의 배열)
타입 배열이름[묶음 개수][내부 개수];

쓸 때는, 배열이름[묶음 번호][내부 번호]

# C 문법 - 이차원 배열 초기값

타입 배열이름[묶음 개수][내부 개수] = { 
    {0번째 묶음의 초기값들}, 
    {1번째 묶음의 초기값들}, 
    ... 
};

# 간선 정보 저장하기

```c
void edges_init() {
  int edges[9][2] = {
    {0, 1}, {1, 2}, {1, 3}, 
    {1, 4}, {1, 5},  {3, 4}, 
    {3, 5}, {4, 5}, {6, 7}
  };
  for (int i = 0; i < 9; i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    int u_adj_end 
      = nodes[u].adj_size++;
    int v_adj_end 
      = nodes[v].adj_size++;
    nodes[u].adj_list[u_adj_end] 
      = v;
    nodes[v].adj_list[v_adj_end] 
      = u;
  }
}
```

# 그래프 노드들에서 반복하려면

노드를 입력받는다.
노드의 이웃들에 대해서,
확인하지 않았으면 재귀호출한다. 

// 확인했는지 저장할 배열 필요. 

# 발견 순서를 번호로 저장하기

발견할 때마다 새로운 번호를 저장한다.
발견 번호를 보면 노드를 확인했는지 
알 수 있다.

# 발견 순서를 번호로 저장하기

```c
int visit_num[10] = {0};
int visit_time = 0;
 
void save_visit_num(int i) {
  visit_num[i] = ++visit_time;
  for (int j = 0; 
    j < nodes[i].adj_size; j++){
    int adj 
      = nodes[i].adj_list[j];
    if (visit_num[adj] == 0) {
      save_visit_num(adj);
    }
  }
}
```

# 연결된 노드들을 그룹 짓기

새로운 그룹 번호를 정한다.
연결된 노드들에 대해 반복하며 그룹 번호를 저장한다.

# 연결된 노드들을 그룹 짓기

```c
int group[10] = {0};
int current_group = 0; 

void mark_group(int i) {
  visit_num[i] = ++visit_time;
  group[i] = current_group;
  for (int j = 0; 
    j < nodes[i].adj_size; j++){
    int adj 
      = nodes[i].adj_list[j];
    if (visit_num[adj] == 0) {
      mark_group(adj);
    }
  }
}

void mark_all_groups() {
  for (int i = 0; 
       i < nodes_size; i++) {
    if (visit_num[i] == 0) {
      current_group++;
      mark_group(i);
    }
  }
}
```

# 복습 - 빽 간선과 그래프의 구조

트리 간선과 빽 간선이 나뉜 기준은 탐색 시작점과 간선 탐색 순서
빽 간선 하나로 부모 간선을 대체한다면, 어느 조상이 가장 최근의 필수 노드일까

# 빽 간선 정보를 번호로 저장하기

자신이나 후손의 빽 간선 하나를 통해 도달할 수 있는 최소 발견 번호를 저장한다. 
부모나 조상에 도달할 수 없으면 자신의 발견 번호를 저장한다.
이웃 노드가 후손인지, 조상인지, 부모인지를 구분해서 처리한다. 

# 빽 간선 정보를 번호로 저장하기

트리 간선을 처음 확인하면, 자식이다.
반대로 다시 확인하면, 부모다. 
빽 간선을 처음 확인하면, 조상이다.
반대로 다시 확인하면, 후손이다.

# 빽 번호 저장하기

자식의 빽 번호가 작으면 쓴다.
부모의 빽 번호는 안 쓴다.
조상의 발견 번호가 작으면 쓴다.
후손의 발견 번호는 안 쓴다.

# 빽 번호 저장하기

```c
int back[10] = {0};
int parent[10] = {0};
 
void save_back(int i) {
 visit_num[i] = ++visit_time; 
 back[i] = visit_num[i];
 for (int j = 0; 
      j < nodes[i].adj_size; 
      j++){

  int adj 
      = nodes[i].adj_list[j];
  if (visit_num[adj] == 0) {
   parent[adj] = i;
   save_back(adj);
   if (back[i] > back[adj]) {
    back[i] = back[adj];
   }
  }
  else if (adj != parent[i]
   && back[i] > visit_num[adj]){
     back[i] = visit_num[adj];
  }
 }
}
```
