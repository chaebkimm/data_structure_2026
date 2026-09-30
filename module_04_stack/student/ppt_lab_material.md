# 목차

스택을 배열 리스트로 만들기
수식을 postfix 형식으로 바꾸기
postfix 형식의 수식을 계산하기

# 복습 - 스택을 배열리스트로 구현

접근 가능 데이터: 마지막 데이터
데이터 추가 방식: 리스트 끝에 추가
데이터 삭제 방식: 마지막 데이터 삭제

# C 문법 - ++

저장된 값을 바꾸고 결과값을 얻기
++i는 i의 값을 1 증가시키고, 증가된 i의 값이 결과값
i++는 원래 i의 값이 결과값이고, i의 값을 1 증가시키기

# 스택 만들기

int stack[10];
int capacity = 10;
int top = -1;

void push(int data) {
  stack[++top] = data;
}

int peek() {
  return stack[top];
}

int pop() {
  return stack[top--];
}
 
int is_full() {
  return top + 1 == capacity;
}

int is_empty() {
  return top == -1;
}

# 스택에서 반복하는 방법

스택이 비어있지 않은 동안 반복한다.
데이터를 읽어서 작업한다.
데이터를 꺼내서 상태를 업데이트한다.

# 수식에서 연산자 우선 순위

곱하기 관련 *, /, %는 우선순위가 높다.
더하기 관련 +, -는 우선순위가 낮다.
기타 괄호 등은 우선순위가 제일 낮다.

# C 문법 - switch

조건의 값에 따라 실행할 곳을 정한다.
switch (조건식) {
case 값:
실행할 문장
}
해당 값이 없으면 default로 간다.

# 연산자 우선순위 구하기

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

# 복습 - postfix로 변환하기

연산자 스택을 쓴다.
숫자는 그대로 변환된 수식에 적는다.
연산자는 스택에 추가하는데, 그 전에 우선순위가 높거나 같은 연산자들이 스택에 있으면 모두 빼서 변환된 수식에 적는다.
수식을 모두 읽은 후에 스택에 연산자가 남아있으면 전부 변환된 수식에 적는다.
변환된 수식의 끝에 '\0'을 적는다.

# C 문법 - while

조건이 참이면 실행하고 다시 확인
while (조건) { 실행할 문장 }

무한 반복 주의

# C 문법 - &&

두 조건이 참일 때만 결과가 참인 연산
조건 && 조건

첫번째 조건이 거짓이면 두번째 조건은 계산되지 않음

# postfix로 변환하기

char eq[8] = "1-2*3+4";
char postfix[8] = "";
 
void convert_to_postfix() {
  int pos = 0;
  top = -1;

  for (int i = 0; eq[i] != '\0'; 
       i++) {
    char c = eq[i];
    if (c >= '0' && c <= '9') {
      postfix[pos++] = c;
    } else {
      while (!is_empty()) {
        char op = peek();
        if (prec(op) < prec(c)){
          break;
        }
        postfix[pos++] = pop();
      }
      push(c);
    }
  }
  while (!is_empty()) {
    postfix[pos++] = pop();
  }
  postfix[pos++] = '\0';
}

# 복습 - postfix 계산하기

피연산자 스택을 쓴다. 
수식 문장을 읽다가 숫자가 보이면 '0'을 빼서 스택에 저장한다.
연산자가 보이면 스택에서 피연산자 두개를 빼서 계산하고, 다시 스택에 저장한다.

# postfix 계산하기

int calc(int num1, int num2, 
         int op) {
  switch (op) {
  case '+': return num1 + num2;
  case '-': return num1 - num2;
  case '*': return num1 * num2;
  case '/': return num1 / num2;
  case '%': return num1 % num2;
  }
  return 0;
}

int eval_postfix() {
    top = -1;
  for (int i = 0; 
       postfix[i] != '\0'; i++){
    char c = postfix[i];
    if (c >= '0' && c <= '9') {
      push(c - '0');
    }
    else {
      int num2 = pop();
      int num1 = pop();
      push(calc(num1, num2, c));
    }
  }
  return pop();
}
