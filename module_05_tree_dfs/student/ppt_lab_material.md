# 목차

1. 트리를 재귀함수로 탐색하기
2. 트리를 스택으로 탐색하기
3. postfix에서 수식 트리 만들기
4. 수식 트리에서 inorder 순서로 데이터를 처리해서 infix 수식

# 트리를 재귀함수로 탐색하기

1. 입력된 노드가 없는 노드면 조기 종료
2. preorder 데이터 처리
3. 왼쪽 자식 노드에 재귀 호출
4. inorder 데이터 처리
5. 오른쪽 자식 노드에 재귀 호출
6. postorder 데이터 처리

# C 문법 - 변수 선언

```c
타입 변수이름, 다른변수이름, 또다른변수이름;
```

같은 타입의 여러 변수를 쉼표 , 로 구분해서 한 줄에 만들 수 있다.

# 트리를 재귀 함수로 탐색하기

```c
int predata, indata, postdata;

void traversal(int i) {
  if (i < 0) {
    return;
  }
  predata = nodes[i].data;
  traversal(nodes[i].left);
  indata = nodes[i].data;
  traversal(nodes[i].right);
  postdata = nodes[i].data;
}
```

# 스택으로 탐색하기

1. 스택이 비어있지 않은 동안 반복한다.
2. 노드가 없는 노드면 스택에서 뺀다.
3. 진행 상태를 업데이트하고, 해당 작업을 한다.
4. 상태에 따라 자식 노드를 스택에 추가 하거나 현재 노드를 스택에서 제거한다.

# C 문법 - continue

반복의 다음 회차로 이동한다.

```c
continue;
```

# 스택으로 탐색하기

```c
int progress[10] = {0};

void traversal_proceed(int i) {
  int step = progress[i]++;
  switch (step) {
  case 0:
    pre_data = nodes[i].data;
    push(nodes[i].left);
    return;
  case 1:
    in_data = nodes[i].data;
    push(nodes[i].right);
    return;
  case 2:
    post_data = nodes[i].data;
    pop();
    return;
  }
}
```

```c
void traversal_with_stack(int root_index) {
  top = -1;
  push(root_index);
  while (!is_empty()) {
    if (peek() < 0) {
      pop();
      continue;
    }
    traversal_proceed(peek());
  }
}
```

# postfix에서 트리 만들기

- 피연산자 스택을 쓴다.
- 수식 문장을 읽다가 숫자가 보이면 자식을 -1로 하고 스택에 저장한다.
- 연산자가 보이면 스택에서 피연산자 두개를 빼서 각각 오른쪽, 왼쪽 자식으로 두고, 스택에 저장한다.

```c
int build_tree_from_postfix() {
  top = -1;
  nodes_size = 0;
  for (int i = 0;
       postfix[i] != '\0'; i++){
    char c = postfix[i];
    nodes[i].data = c;
    if (c >= '0' && c <= '9') {
      nodes[i].left = -1;
      nodes[i].right = -1;
    } else {
      nodes[i].right = pop();
      nodes[i].left = pop();
    }
    push(i);
    ++nodes_size;
  }
  return pop();
}
```

# 수식 트리를 inorder로 읽기

- 숫자 노드는 재귀호출을 하지 않고 infix 문자 배열에 숫자를 적는다.
- 연산자 노드는 왼쪽 자식에 재귀호출을 하고, infix 문자 배열에 연산자를 적고, 오른쪽 자식에 재귀호출을 한다.

```c
char infix[10] = "";
int infix_pos = 0;

void _write_infix(int i) {
  char c = nodes[i].data;
  if (c >= '0' && c <= '9') {
    infix[infix_pos++] = c;
    return;
  }
  _write_infix(nodes[i].left);
  infix[infix_pos++] = c;
  _write_infix(nodes[i].right);
}
```

```c
void write_infix(int root) {
  _write_infix(root);
  infix[infix_pos++] = '\0';
}
```
