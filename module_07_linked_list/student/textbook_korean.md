# 7장. 연결 리스트

1장은 배열의 연속된 활성 칸에 값을 저장했다. 이번 장에서는 값을 옮기지 않고 연결을 바꿔 순서를 바꾼다. 현재 `lab.c`는 열 칸 배열과 정수로 기록한 연결을 사용한다.

[English textbook](textbook.md) · [수업 활동](class_material.md) · [개념 슬라이드](ppt_material.md) · [실습 슬라이드](ppt_lab_material.md)

## Thinking Logically

### 값을 밀지 않고 순서를 바꾸려면?

17, 23, 31을 차례로 읽으려 한다. 나중에는 두 값 사이에 새 값을 넣으려 한다. 배열 리스트의 중간에 삽입하면 뒤의 값들을 밀어야 한다. 각 기록에 다음 기록의 위치를 적어 두면 어떨까? 값의 위치를 바꾸지 않고 다음 위치만 바꾸면 순서가 달라진다.

값과 다음 위치를 함께 저장한 기록을 노드(node)라고 한다. 각 노드가 다음 노드 하나를 가리키는 구조를 단일 연결 리스트(singly linked list)라고 한다. 연결에는 주소를 쓸 수도 있다. 이 실습은 배열 인덱스를 쓴다. 실제 저장 공간은 배열이다. 읽는 순서는 이웃 칸이 아니라 연결을 따른다.

각 노드에는 정수 필드가 둘 있다. `data`는 값이다. `next`는 다음 노드의 인덱스다. 유효한 인덱스는 0부터 9까지다. `-1`은 다음 노드가 없다는 표시다. `-1`로 배열에 접근하면 안 된다.

```text
실제 칸:       lnodes[0]       lnodes[1]       lnodes[2]
저장 내용:     data=17,next=1  data=23,next=2  data=31,next=-1
연결 순서:     0 → 1 → 2 → -1
읽는 값:       17 → 23 → 31
```

값 23은 인덱스 1에 있다. 인덱스와 값은 다르다. 1번 칸을 재사용하면 인덱스는 같아도 값은 달라질 수 있다.

### 비어 있는 노드는 어디서 가져올까?

새 기록을 넣으려면 사용하지 않는 칸이 필요하다. 매번 배열 전체를 찾는 대신 사용 가능한 칸끼리 연결한다. 이 연결을 가용 리스트(free list)라고 한다. 재사용할 노드를 모아 둔 고정 배열을 노드 풀(node pool)이라고 한다.

`free_head`는 첫 가용 칸의 인덱스다. `init_lnodes_pool()`는 모든 값을 0으로 만들고 다음 연결을 만든다.

```text
free_head = 0
가용 연결: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

`new_lnode(value, -1)`는 가용 연결의 첫 칸을 가져온다. `free_head`를 다음 칸으로 옮긴다. 가져온 칸에 값을 쓴다. 두 번째 인수로 `next`를 정한다. `-1`을 전달하면 다른 노드와 연결되지 않은 칸이 된다. 반환값은 저장한 값이 아니라 인덱스다. 가용 칸이 없으면 `-1`을 반환하고 아무것도 바꾸지 않는다.

| 초기화 후 호출 | 반환 인덱스 | `free_head` | 가져온 칸 |
| --- | ---: | ---: | --- |
| `new_lnode(17, -1)` | 0 | 1 | `data=17, next=-1` |
| `new_lnode(23, -1)` | 1 | 2 | `data=23, next=-1` |
| `new_lnode(31, -1)` | 2 | 3 | `data=31, next=-1` |

세 노드는 아직 서로 연결되지 않았다. 여기서 할당(allocation)은 가용 연결에서 칸을 빼서 호출자에게 맡기는 일이다. 운영체제에 새 저장 공간을 요청하지 않는다. 이 함수들은 C의 `malloc`이나 `free`를 호출하지 않는다.

### 이미 아는 노드 뒤에 어떻게 넣을까?

분리된 세 노드에 `link_lnode(0, 1)`, `link_lnode(1, 2)`를 차례로 적용한다. 그러면 앞에서 본 17, 23, 31의 연결이 된다. 시작 인덱스는 호출자의 `first` 같은 변수에 따로 보관한다.

`prev` 뒤에 `node`를 넣으려면 먼저 기존 다음 위치를 새 노드에 저장한다. 그 뒤 `prev`가 새 노드를 가리키게 한다.

```text
lnodes[node].next = lnodes[prev].next
lnodes[prev].next = node
```

두 대입의 순서를 뒤집으면 기존 다음 위치를 잃는다. 새 노드가 자기 자신을 가리킬 수도 있다. `link_lnode`는 칸을 할당하지 않는다. 값을 검색하지도 않는다. 호출자가 유효하고 서로 다른 두 할당 인덱스를 제공해야 한다. 넣을 노드는 다른 활성 연결과 가용 연결에 속하지 않아야 한다.

### 연결에서 빼면 바로 재사용할 수 있을까?

0번 뒤의 노드를 빼 보자. `delete_next_lnode(0)`은 1을 보관한다. `lnodes[0].next`를 2로 바꾸고 1을 반환한다.

```text
전: first=0; 0(17) → 1(23) → 2(31) → -1
후: first=0; 0(17) → 2(31) → -1
반환: 1; lnodes[1].next는 여전히 2; free_head는 여전히 3
```

활성 연결에서 노드를 빼는 일을 분리(detach)라고 한다. 분리한 칸은 아직 가용 연결에 없다. 호출자는 `lnodes[1].data`를 읽은 뒤 `free_lnode(1)`로 칸을 반환할 수 있다.

```text
free_head = 1
가용 연결: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode`는 `next`를 덮어쓴다. `data`는 지우지 않는다. 이어서 `new_lnode(8, -1)`을 호출하면 1을 반환한다. 그 칸은 `data=8, next=-1`이 된다. 이전 값 23은 이제 활성 기록의 값이 아니다.

칸을 올바른 상태 하나에 두는 책임을 소유 책임(ownership)이라고 한다. 칸은 가용 연결, 활성 연결 하나, 호출자가 보관한 분리 상태 가운데 하나에만 속해야 한다. 활성 노드를 반환하면 그 노드의 연결이 바뀐다. 같은 칸을 두 번 반환하면 가용 연결에 순환이 생길 수 있다. `free_lnode`의 범위 검사는 이런 중복을 알아내지 못한다.

유효한 `prev` 뒤에 노드가 없으면 `delete_next_lnode(prev)`는 `-1`을 반환하고 연결을 바꾸지 않는다. 이 함수는 첫 일치 값을 검색해서 지우는 함수가 아니다. 선행 노드가 없는 첫 노드도 직접 지우지 못한다. 별도로 둔 시작 인덱스의 변경은 호출자가 맡는다.


### 들어온 순서를 연결 리스트로 어떻게 지킬까?

17, 23, 31을 도착한 순서로 처리하려고 한다. 새 기록은 꼬리 뒤에 붙이고 처리할 기록은 머리에서 뺀다. 양 끝을 기억하므로 검색하지 않는다. 먼저 들어온 값을 먼저 꺼내는 규칙을 **FIFO**라고 한다. 이 규칙을 따르는 구조가 **큐**다. 여기서는 앞에서 만든 연결 노드를 큐에 적용한다.

사용 중인 노드가 없는 독립 실험에서 `init_lnodes_pool(); head = tail = -1;`로 준비한다. `enqueue(value)`는 노드를 할당해 꼬리에 붙이고 성공하면 `true`를 반환한다. 가용 칸이 없으면 풀과 큐를 바꾸지 않고 `false`를 반환한다. `dequeue()`는 가장 오래된 **값**을 반환하고 그 노드를 내부에서 반환한다. 호출자는 `is_empty_queue()`로 비어 있지 않은지 확인한다. 반환된 값에 `free_lnode`를 적용하면 안 된다.

내부 노드 함수는 인덱스를 다룬다. `enqueue_lnode(index)`는 이미 할당해 분리한 칸을 붙인다. `dequeue_lnode()`는 칸을 분리하고 인덱스를 반환하지만 재활용하지 않는다. 빈 큐에서는 상태를 바꾸지 않고 `-1`을 반환한다. 내부 함수를 직접 쓸 때는 데이터를 읽은 뒤 `free_lnode`를 호출한다. 공개 함수 `dequeue()`는 이 과정을 직접 수행한다.

`dequeue()`의 빈 큐 검사는 `assert`다. `NDEBUG`로 빌드하면 검사가 사라지므로 호출자의 비어 있지 않다는 조건은 계속 필요하다. 데이터 값 `-1`도 큐에 넣을 수 있다. 값을 빈 큐 표시로 쓰지 않는다. `assert(enqueue(value))`처럼 상태를 바꾸는 호출을 검사 안에 넣으면 안 된다. 먼저 결과를 변수에 저장한 뒤 검사해야 삽입이 생략되지 않는다.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

첫 삽입은 양 끝을 같은 칸으로 만든다. 마지막 제거는 둘 다 `-1`로 만든다. 가용 칸 0을 재사용해 기다리던 23과 31 뒤에 8을 붙일 수 있다. 작은 인덱스라고 먼저 나오지 않는다. 8장은 같은 공개 함수에 트리나 그래프의 ID를 값으로 넣는다. BFS 호출자가 큐 노드의 할당과 반환을 직접 관리하지 않는다.

## Calculating Efficiency


### 연결 하나를 바꾸는 일은 얼마나 걸릴까?

할당은 가용 연결의 첫 인덱스를 가져온다. 반환은 인덱스 하나를 앞에 붙인다. 선행 노드를 이미 알 때 삽입은 연결 둘을 바꾼다. 삭제는 다음 노드 하나를 읽고 연결 하나까지 바꾼다. 모두 연결 전체를 돌지 않으므로 O(1)이다. 선행 노드를 값으로 찾아야 한다면 그 검색은 별도다. 활성 노드 `n`개를 모두 볼 수 있으므로 O(n)이다.

용량 `C`칸 초기화는 각 칸에 한 번씩 기록하므로 O(C)다. 실습의 `C`는 10이다. 활성 노드 수와 관계없이 정수 필드 둘을 가진 노드 열 개의 공간을 예약한다. 저장 공간은 O(C)다. 각 연산의 추가 지역 저장 공간은 O(1)이다. 이 실습의 할당 실패는 가용 연결의 소진이다. 운영체제의 메모리 요청 실패가 아니다.

### 도착 순서를 지키는 일은 얼마나 걸릴까?

공개 enqueue는 가용 칸 하나를 가져와 기억한 tail 뒤에 붙인다. 공개 dequeue는 head를 옮기고 값 하나를 읽은 뒤 칸을 반환한다. 각 단계의 필드 작업 수가 일정하므로 두 함수 모두 O(1)이다. 열 칸 풀은 동시에 할당된 기록 수를 제한한다. 공개 함수가 칸을 재사용하므로 처리하는 전체 값 수를 열 개로 제한하지 않는다. 8장의 BFS도 이 차이를 사용한다.

## Glossary


앞에서 사용한 동작과 상태에 다음 이름을 붙인다.

| 이름 | 이 실습에서의 뜻 |
| --- | --- |
| node / 노드 | `data`와 `next`를 가진 기록 |
| singly linked list / 단일 연결 리스트 | 노드마다 다음 인덱스를 하나씩 기록한 순서 |
| node pool / 노드 풀 | 고정 저장 공간 `lnodes[10]` |
| free list / 가용 리스트 | `free_head`부터 연결한 사용 가능 인덱스 |
| allocation / 할당 | 사용하려고 가용 연결에서 칸을 꺼내는 일 |
| detach / 분리 | 활성 연결에서 빼되 가용 연결에 반환하지 않는 일 |
| recycle / 반환 | 분리된 할당 칸을 가용 연결에 넣는 일 |
| ownership / 소유 책임 | 한 칸을 올바른 상태 하나에만 두는 책임 |
| traversal / 순회 | `-1`을 만날 때까지 `next`를 따라가는 일 |
| linked queue / 연결 큐 | `tail` 뒤에 붙이고 `head`에서 빼는 연결 리스트 예 |
| FIFO | 도착한 순서대로 기록을 처리하는 규칙 |
| public enqueue / dequeue | 값을 받아 성공 여부 반환 / 값을 반환하고 노드 재활용 |
| node helpers | 칸 인덱스를 다루는 `enqueue_lnode`, `dequeue_lnode` |


## Coding Plan

앞의 동작이 다음 동작을 준비하도록 순서를 정한다.

1. `Linked_Node`, `lnodes[10]`, `free_head`를 둔다. 열 칸을 `-1`로 끝나는 가용 연결로 만든다.
2. `new_lnode(data_value, next_value)`로 첫 가용 칸을 가져온다. 분리된 칸을 만들 때는 두 번째 인수에 `-1`을 준다.
3. 유효한 선행 노드의 기존 다음 위치를 새 노드에 보관한 뒤 선행 노드의 연결을 바꾼다.
4. 다음 노드를 분리하고 인덱스를 반환한다. 사용을 끝낸 뒤 `free_lnode`로 반환한다.
5. 첫 노드의 인덱스는 호출자가 보관한다. 반환 인덱스를 검사하고 `-1`에 도달하기 전에만 배열에 접근한다.
6. 가용 연결 소진, 꼬리 뒤 삭제, 분리 후 재사용을 독립된 유효 상태에서 검사한다.
7. 내부 노드 함수를 추적한 뒤 값 기반 `enqueue`, `dequeue`로 할당과 반환을 감싼다. 호출자는 삽입 성공과 빈 큐를 확인한다.

## C Code

다음 코드는 연결 큐 예를 포함한 현재 `lab.c` 전체다. 이 소스는 한 드라이버에서 한 번만 포함한다. 이후 모듈은 공유 소스를 가져오는 경계에서 중복 포함을 막는다. 소스에는 `main`이 없다. 테스트 드라이버가 이 파일을 포함한다. 두 번째 할당 인수는 `next`에 그대로 저장된다. 유효한 다음 인덱스 또는 `-1`을 제공하는 책임은 호출자에게 있다.

```c
#include <stdbool.h>
#include <assert.h>

struct Linked_Node {
    int data;
    int next;
};

struct Linked_Node lnodes[10];

void link_lnode(int prev, int node) {
    lnodes[node].next = lnodes[prev].next;
    lnodes[prev].next = node;
}

int delete_next_lnode(int prev) {
    int node = lnodes[prev].next;
    if (node != -1) {
        lnodes[prev].next = lnodes[node].next;
    }
    return node;
}

int free_head = -1;

void init_lnodes_pool(void) {
    for (int i = 0; i < 9; i++) {
        lnodes[i].data = 0;
        lnodes[i].next = i + 1;
    }
    lnodes[9].data = 0;
    lnodes[9].next = -1;
    free_head = 0;
}

int new_lnode(int data_value, int next_value) {
    if (free_head == -1) {
        return -1;
    }
    int node = free_head;
    free_head = lnodes[free_head].next;
    lnodes[node].data = data_value;
    lnodes[node].next = next_value;
    return node;
}

void free_lnode(int node) {
    if (node < 0 || node >= 10) {
        return;
    }
    lnodes[node].next = free_head;
    free_head = node;
}

int head = -1;
int tail = -1;

bool is_empty_queue(void) {
    return head == -1;
}

void enqueue_lnode(int node) {
    if (is_empty_queue()) {
        head = tail = node;
    } else {
        lnodes[tail].next = node;
        tail = node;
    }
}

int dequeue_lnode(void) {
    if (is_empty_queue()) {
        return -1;
    }
    int oldest = head;
    if (head == tail) {
        head = tail = -1;
    } else {
        head = lnodes[head].next;
    }
    return oldest;
}

bool enqueue(int value) {
    int node = new_lnode(value, -1);
    if (node == -1) {return false;}
    enqueue_lnode(node);
    return true;
}

int dequeue(void) {
    int node = dequeue_lnode();
    assert(node != -1);
    int value = lnodes[node].data;
    free_lnode(node);
    return value;
}
```

분리된 세 칸을 받아 연결할 때는 다음 순서를 쓴다. 새 프로세스 또는 활성 노드가 없는 상태에서 실행한다. 한 번 더 할당하려면 모든 반환값을 같은 방식으로 검사한다.

```c
#include <assert.h>
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = new_lnode(17, -1);
    int middle = new_lnode(23, -1);
    int last = new_lnode(31, -1);
    assert(first != -1 && middle != -1 && last != -1);
    link_lnode(first, last);
    link_lnode(first, middle);
    int removed = delete_next_lnode(first);
    assert(removed == middle && lnodes[first].next == last);
    free_lnode(removed);
    int reused = new_lnode(8, -1);
    assert(reused == middle && lnodes[reused].next == -1);
    return 0;
}
```

### 같은 노드를 큐에 적용한다

독립된 새 풀에서 시작한다. 다음 호출자는 값을 넣고 성공 여부를 확인한다. `dequeue()`가 내부에서 칸을 반환한다. 상태 변경은 `NDEBUG`에서도 실행된다.

```c
#include <assert.h>
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    head = tail = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        bool added = enqueue(values[i]);
        if (!added) return 1;
    }
    for (int i = 0; i < 3; ++i) {
        if (is_empty_queue()) return 1;
        int value = dequeue();
        if (value != values[i]) return 1;
    }
    assert(is_empty_queue() && head == -1 && tail == -1);
    bool added = enqueue(-1);
    if (!added || is_empty_queue()) return 1;
    int value = dequeue();
    if (value != -1 || !is_empty_queue()) return 1;
    return 0;
}
```
