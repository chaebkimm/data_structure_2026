# 목차

1. 트리를 재귀함수로 탐색하기
2. 트리를 스택으로 탐색하기
3. postfix에서 수식 트리 만들기
4. 수식 트리에서 inorder 순서로 데이터를 처리해서 infix 형식으로 쓰기

# 트리를 재귀함수로 탐색하기

1. 입력된 노드가 없으면 조기 종료
2. preorder 데이터 처리
3. 왼쪽 자식 노드에 재귀 호출
4. inorder 데이터 처리
5. 오른쪽 자식 노드에 재귀 호출
6. postorder 데이터 처리

# 복습 - 트리 노드 만들기

```c
struct TreeNode {
  char data;
  int left;
  int right;
};
struct TreeNode nodes[10];
int cap = 10, size = 0;
```

# 트리를 재귀 함수로 탐색하기

```c
void traversal(int i) {
  if (i < 0) { return; }
  /* preorder */
  traversal(nodes[i].left);
  /* inorder */
  traversal(nodes[i].right);
  /* postorder */
}
```

# 스택으로 탐색하기

1. 스택이 비어있지 않은 동안 반복한다.
2. 없는 노드는 스택에서 뺀다.
3. 진행 상태를 업데이트하고, 해당 작업을 한다.
4. 상태에 따라 자식 노드를 스택에 추가 하거나 현재 노드를 스택에서 제거한다.

# 복습 - 스택 만들기

```c
int stack[10];
int capacity = 10;
int top = -1;

void push(int data) {
  stack[++top] = data;
}

int peek() { return stack[top]; }
int pop() { return stack[top--]; }
int is_empty() {
  return top == -1;
}
```

# 스택으로 탐색하기

```c
int progress[10] = {0};

void traversal_proceed(int i) {
  if (i < 0) {
    pop();
    return;
  }
  int step = progress[i]++;
  switch (step) {
  case 0: /* preorder */
    push(nodes[i].left);
    return;
  case 1: /* inorder */
    push(nodes[i].right);
    return;
  case 2: /* postorder */
    pop();
    return;
  }
}
```

```c
void traversal_stack(int root) {
  top = -1;
  push(root);
  while (!is_empty()) {
    traversal_proceed(peek());
  }
}
```

# postfix에서 트리 만들기

- 피연산자 스택을 쓴다.
- 수식 문장을 읽다가 숫자가 보이면 자식을 -1로 하고 스택에 저장한다.
- 연산자가 보이면 스택에서 피연산자 두개를 빼서 각각 오른쪽, 왼쪽 자식으로 두고, 스택에 저장한다.

# 복습 - postfix로 변환하기

```c
char eq[8] = "1-2*3+4";
char postfix[8] = "";
```

# postfix에서 트리 만들기

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

# 복습 - 연산자 우선순위 구하기

```c
int prec(char op) {
  switch (op) {
  case '*': case '/': case '%':
    return 2;
  case '+': case '-':
    return 1;
  default:
    return 0;
  }
}
```

# 수식 트리를 inorder로 읽기

```c
char infix[20] = "";
int infix_pos = 0;

int prec2(char c) {
  if (c >= '0' && c <= '9') {
    return 3;
  } else {
    return prec(c);
  }
}
```

```c
void write_char(char c) {
  infix[infix_pos++] = c;
}

void _write_infix(int i) {
  if (i < 0) {
    return;
  }
  char c = nodes[i].data;
  if (c >= '0' && c <= '9') {
    write_char(c);
    return;
  }
  char l = nodes[nodes[i].left].data;
  char r = nodes[nodes[i].right].data;

  /* preorder */
  if (prec2(l) < prec2(c)) {
    write_char('(');
  }
  _write_infix(nodes[i].left);

  /* inorder */
  if (prec2(l) < prec2(c)) {
    write_char(')');
  }
  write_char(c);
  if (prec2(r) <= prec2(c)) {
    write_char('(');
  }
  _write_infix(nodes[i].right);

  /* postorder */
  if (prec2(r) <= prec2(c)) {
    write_char(')');
  }
}
```

```c
void write_infix(int root) {
  infix_pos = 0;
  _write_infix(root);
  write_char('\0');
}
```
