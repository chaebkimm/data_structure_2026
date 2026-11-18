# 자료구조 - 요약

12주차 – 우선순위 큐 코드

## 목차

- 미팅 시간 정하기 문제
- 데이터가 우선순위를 갖는 큐
- 우선순위 큐에 데이터 추가, 삭제하기
- 접속 계획표 처리하기
- 모두 접속할 계획인 시간 찾기

## 복습 - 전체 미팅 시간 정하는 문제
- `IDS`명의 유저들이 각자 계획한 시간에 로그인과 로그아웃을 `EPOCHS`번 반복한다.
- 미팅을 언제 할지 결정하기 위해 모든 유저가 접속할 가장 이른 시간을 찾는다.

## 새로운 C 문법: 멤버 구조체

- 구조체의 멤버로 다른 구조체 타입의 변수를 쓸 수 있다.

## 로그인 정보 구조체 C 코드

```c
enum { IDS = 3, EPOCHS = 3 };

struct Session {
  int login;
  int logout;
};

struct User {
  int id;
  int epoch;
  struct Session now;
};
```

## 복습 - 우선순위를 갖는 큐

- 데이터를 꺼낼 때 우선순위 순서로 한다.
- 관리는 단순 큐처럼 `front`, `rear`로 해본다.
- 구현은 데이터를 저장할 때 우선순위 순서가 지켜지는 방식으로 해본다.
- 모든 로그인 계획이 추가 가능하게 용량은 `IDS * EPOCHS`로 한다.

## 우선순위 큐 C 코드

```c
struct User pq[IDS * EPOCHS];
int front, rear;
 
void init_pqueue(void) {
  front = 0;
  rear = -1;
}
```

## 복습 - 미팅 관련 우선순위

- 어떤 유저가 로그아웃 하면 다음에 로그아웃할 유저를 찾기 위해 우선순위 큐를 쓴다.
- 로그아웃 시간이 이른 유저에게 높은 우선순위를 부여한다.

## 새로운 C 문법: 구조체 대입

- 구조체를 매개변수에서 쓰거나 다른 변수에 대입하는 방식은 `int`에서와 같다. 값이 복사되어 저장된다.

## 우선순위를 정하는 C 코드

```c
int compare(struct User x, struct User y) {
  return x.now.logout < y.now.logout;
}
```

## 복습 - 우선순위 큐에 데이터 추가

- 가정: 배열 뒤쪽에 저장할 공간이 있다.
- 마지막 데이터부터 차례로 비교해 추가할 위치를 찾는다. 
- 동시에 기존 데이터를 이동해 자리를 마련한 뒤 데이터를 추가한다.
- 마지막 데이터 위치를 업데이트 한다.

## 복습 - 우선순위 큐 데이터 꺼내기

- 가정: 저장된 데이터가 존재한다.
- 우선순위가 가장 높은 데이터는 처음 데이터이므로, 처음 데이터를 꺼낸다.
- 처음 데이터 위치를 업데이트 한다.

## 데이터 추가 삭제 C 코드

```c
void enqueue(struct User user) {
  int i = rear + 1;
  while (i > front && compare(user, pq[i - 1])) {
    pq[i] = pq[i - 1];
    i--;
  }
  pq[i] = user;
  rear++;
}
 
struct User dequeue(void) {
  return pq[front++];
}
```

## 데이터 저장 방식 디자인

- `IDS`명의 유저마다 로그인 또는 로그아웃 할 시간들을 저장한다.
- 모든 유저가 `EPOCHS`번의 계획을 저장한다.
- 시간은 `0`부터 시작하며, 시간의 흐름에 따라 증가하는 순서로 저장한다.
- 각 유저의 현재 접속 계획 하나씩을 우선순위 큐에서 관리한다.
- 어떤 유저가 로그아웃하면 다음 계획으로 접속 계획을 업데이트한다.
- `EPOCHS`회차가 되면 더 이상 업데이트하지 않는다. 

## 전체 접속 계획 이차원 배열 C 코드

```c
struct Session plans[IDS][EPOCHS] = {
  {{5, 6}, {8, 9}, {11, 13}}, 
  {{2, 5}, {7, 8}, {12, 15}}, 
  {{1, 3}, {5, 7}, {9, 14}}
};
```

## 로그인 회차 업데이트 C 코드

```c
struct User next_epoch(struct User u) {
  int ep = ++u.epoch;
  if (ep < EPOCHS) {
    u.now = plans[u.id][ep];
  }
  return u;
}
```

## 복습 - 미팅 시간 정하는 절차

1. 우선순위 큐에 유저들 초기 정보 추가
2. 늦게 오는 유저 기준 미팅 시간 제시
3. 먼저 가는 유저 찾기
4. 미팅 때까지 안 가면 확정
5. 미팅을 못 하면 먼저 간 유저 정보 업데이트하고 확인하는 것을 반복

## 우선순위 큐에 유저들 추가하기

- 우선순위 큐를 초기화한다.
- 유저의 로그인 회차를 `0`으로 만든다. 
- 모든 유저 아이디에 대해, 유저의 아이디와 `0`회차 로그인 계획을 저장하고, 우선순위 큐에 추가한다.

## 새로운 C 문법: 멤버 초기화

- 구조체 변수를 만들 때 멤버의 초기값을 선택적으로 지정할 수 있다.
- `struct 태그 변수이름 = {.멤버이름 = 초기값, .멤버이름 = 초기값};` 형식이다.
- 정하지 않은 멤버는 `0`이 된다.

## 우선순위 큐에 유저들 추가 C 코드

```c
void init_meeting(void) {
  init_pqueue();
  struct User u = {.epoch = 0};
  for (int i = 0; i < IDS; i++) {
    u.id = i;
    u.now = plans[i][0];
    enqueue(u);
  }
}
```

## 복습 - 미팅 시간 제시

- 로그인 시간의 최대값 때까지 모두 온다.
- 처음에는 모든 유저를 비교한다. 어떤 시간보다도 작은 `-1`로 시작한다.
- 다음부터는 기존의 최대값이 그대로 있으므로 누군가 먼저 갔다가 돌아오는 시간하고만 비교해 보면 된다. 

## 미팅 시간 제시 C 코드

```c
int latest_login(void) {
  int latest = -1;
  for (int i = front; i <= rear; i++) {
    int cur = pq[i].now.login;
    if (cur > latest) {
      latest = cur;
    }
  }
  return latest;
}
```

## 복습 - 미팅 시간 확정하기

- 미팅 시간이 로그인 시간 기준으로 계산해서 제시되었으므로, 로그아웃 시간만 확인하면 된다.
- 먼저 가는 유저가 미팅 시간이 지나서 로그아웃 하면 미팅 시간을 확정한다.

## 복습 - 돌아오는 유저 업데이트

- 먼저 가는 유저가 다시 돌아올 계획이 없으면 미팅을 못 한다.
- 돌아온 유저가 미팅 시간이 지나서 오면 미팅 시간을 새 로그인 시간으로 바꾼다.
- 돌아온 유저는 큐에 다시 추가하고, 큐에서 먼저 가는 유저를 새로 꺼낸다.

## 미팅 시간 확정하기 C 코드

```c
int meeting_time(void) {
  init_meeting();
  int t = latest_login();
  struct User out = dequeue();

  while (t >= out.now.logout) {
    out = next_epoch(out);
    if (out.epoch >= EPOCHS) { 
      return -1; 
    } 
    if (out.now.login > t) {
      t = out.now.login;
    }
    enqueue(out);
    out = dequeue();
  }
  return t;
}
```
