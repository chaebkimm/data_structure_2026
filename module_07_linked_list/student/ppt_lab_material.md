# 목차

1. 링크드 리스트 노드 만들기
2. 노드 연결하고 삭제하기
3. 가용 노드 리스트
4. 노드 꺼내고 반납하기
5. 링크드 리스트로 큐 구현하기

# 복습 - 링크드 리스트 노드

- 노드에는 데이터와 다른 노드에 대한 정보가 들어있다.
- 링크드 리스트를 위한 노드는 다음 노드 정보를 저장한다.
- 노드들을 배열에 저장한다.

# C 문법 - enum

- 정수 상수에 이름을 붙일 수 있다.

```c
enum { 상수이름1 = 정수값1, 상수이름2 = 정수값2 };
```

- 코드에서 상수이름을 쓰면 정수 상수값을 쓰는 것과 같다.

# 링크드 리스트 노드 만들기

```c
struct Linked_Node {
  int data;
  int next;
};
enum { CAP = 10 };
struct Linked_Node arr[CAP];
```

# 복습 - 링크드 리스트에 노드 추가

- 기존 연결: 앞 --- 뒤
- 추가 후: 앞 --- 노드 --- 뒤
- 해야 할 작업: 노드의 다음을 뒤로 만들기, 앞의 다음을 노드로 만들기

# 링크드 리스트에 노드 추가

```c
void link_node(int p, int n) {
  arr[n].next = arr[p].next;
  arr[p].next = n;
}
```

# 복습 - 링크드 리스트의 노드 삭제

- 기존 연결: 앞 --- 노드 --- 뒤
- 삭제 후: 앞 --- 뒤
- 해야 할 작업: 앞의 다음을 노드의 다음으로 만들기. 노드가 없을 경우 작업하지 않기.

# 링크드 리스트의 노드 삭제

```c
int del_next_node(int p) {
  int n = arr[p].next;
  if (n != -1) {
    arr[p].next = arr[n].next;
    arr[n].next = -1;
  }
  return n;
}
```

# 복습 - 링크드 리스트로 배열 관리

- 안 쓰는 노드들을 모두 연결해서 링크드 리스트로 만든다.
- 처음에는 배열의 모든 노드들이 연결되어 있다.
- 시작 노드로 링크드 리스트를 표현한다.

# C 문법 - static

- 로컬 변수의 타입 앞에 static 키워드를 붙이면, 프로그램이 실행되는 동안 변수가 없어지지 않고 유지된다. 초기값은 처음 한 번만 저장된다. 함수가 다시 실행되면 이전 값이 그대로 저장되어 있다.

# 링크드 리스트로 배열 관리

```c
int fhead = -1;

void init_nodes_pool(void) {
  static int initialized = 0;
  if (initialized) {return;}
  initialized = 1;
  for (int i = 0; i < CAP - 1;
       i++) {
    arr[i].next = i + 1;
  }
  arr[CAP - 1].next = -1;
  fhead = 0;
}
```

# 복습 - 링크드 리스트의 시작 노드

- 노드가 필요하면 시작 노드를 쓰고, 시작 노드는 기존의 다음 노드로 바꾼다.
- 노드를 다 써서 시작 노드에 추가할 때는 노드의 다음 노드에 기존 시작 노드를 저장한다. 추가된 노드로 시작 노드를 바꾼다.

# 시작 노드를 꺼내서 쓰기

- 시작 노드가 없으면 못 꺼낸다.
- 기존 시작 노드를 저장해 놓고, 그 다음 노드로 시작 노드를 바꾼다.
- 저장해 놓았던 노드를 쓰면 된다.

```c
int new_node(void) {
  init_nodes_pool();
  if (fhead == -1) {
    return -1;
  }
  int node = fhead;
  fhead = arr[fhead].next;
  arr[node].next = -1;
  return node;
}
```

# 시작 노드로 추가해서 반납하기

- 반납할 노드의 다음 노드를 기존 시작 노드로 바꾼다.
- 반납할 노드로 시작 노드를 바꾼다.
- 없는 노드 -1에는 작업하지 않는다.

```c
void free_node(int node) {
  if (node == -1) {
    return;
  }
  arr[node].next = fhead;
  fhead = node;
}
```

# 복습 - 링크드 리스트로 큐 구현

- 시작 노드와 끝 노드 정보가 필요하다.
- 큐에 노드를 추가할 때는 끝에 추가한다.
- 큐에서 노드를 삭제할 때는 시작 노드를 삭제한다.
- 시작 노드를 보면 큐가 비었는지 안다.

# 링크드 리스트로 큐 구현

```c
int qhead = -1;
int qtail = -1;

int is_empty(void) {
  return qhead == -1;
}
```

# 복습 - 큐에 노드 추가하기

- 마지막 노드의 다음 노드에 추가할 노드를 저장한다. 추가할 노드가 새로운 마지막 노드가 된다.
- 큐가 비어있었을 때는 노드를 추가하면 시작 노드와 끝 노드가 모두 그 노드가 된다.

# 큐에 노드 추가하기

```c
void enqueue_node(int node) {
  if (node == -1) {
    return;
  }
  if (is_empty()) {
    qhead = qtail = node;
  }
  else {
    arr[qtail].next = node;
    qtail = node;
  }
  arr[qtail].next = -1;
}
```

# 복습 - 큐에서 노드 삭제하기

- 시작 노드를 기존 시작 노드의 다음 노드로 바꾼다.
- 노드가 하나인 큐에서 삭제해서 큐가 비어있게 되면 시작 노드와 끝 노드가 모두 없다고 저장한다.
- 비어 있는 큐에서는 삭제를 못 한다.

# 큐에서 노드 삭제하기

```c
int dequeue_node(void) {
  if (is_empty()) {
    return -1;
  }
  int oldest = qhead;
  qhead = arr[qhead].next;
  if (qhead == -1) {
    qtail = -1;
  }
  arr[oldest].next = -1;
  return oldest;
}
```
