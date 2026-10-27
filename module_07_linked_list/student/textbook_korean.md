# 7장. 연결 리스트

1장은 배열의 연속된 활성 칸에 값을 저장했다. 이번 장에서는 값을 옮기지 않고 연결을 바꿔 순서를 바꾼다. 현재 `lab.c`는 열 칸 배열과 정수로 기록한 연결을 사용한다. 같은 연결을 스택과 큐에 적용한다.

[English textbook](textbook.md) · [수업 활동](class_material.md) · [개념 슬라이드](ppt_material.md) · [실습](lab.md)

## Thinking Logically

### 값을 밀지 않고 순서를 바꾸려면?

17, 23, 31을 저장하려 한다. 두 값 사이에 새 값을 넣거나 중간 값을 빼려 한다. 배열 리스트의 중간에 삽입하면 뒤의 값들을 밀어야 한다. 각 기록에 다음 기록의 위치를 적어 두면 어떨까? 값의 위치를 바꾸지 않고 다음 위치만 바꾸면 순서가 달라진다.

값과 다음 위치를 함께 저장한 기록을 노드(node)라고 한다. 각 노드가 다음 노드 하나를 가리키는 구조를 단일 연결 리스트(singly linked list)라고 한다. 연결에는 주소를 쓸 수도 있다. 이 실습은 배열 인덱스를 쓴다. 실제 저장 공간은 배열이다. 읽는 순서는 이웃 칸이 아니라 연결을 따른다.

각 노드에는 정수 필드가 둘 있다. `data`는 값이다. `next`는 다음 노드의 인덱스다. 유효한 인덱스는 0부터 9까지다. `-1`은 다음 노드가 없다는 표시다. `-1`로 배열에 접근하면 안 된다. 시작 인덱스는 호출자의 `first` 같은 변수에 따로 보관한다. 빈 리스트는 `first=-1`이다.

우선 0, 1, 2번 칸을 우리가 사용할 수 있다고 하자. 1번은 따로 두고 0번과 2번을 연결한다.

```text
실제 칸:       lnodes[0]       lnodes[1]       lnodes[2]
저장 내용:     data=17,next=2  data=23,next=-1 data=31,next=-1
first = 0
연결 순서:     0 → 2 → -1
읽는 값:       17 → 31
별도 노드:     1(23) → -1
```

연결을 계속 따라가면 결국 `-1`에 도달해야 한다. 앞에서 지난 노드로 돌아가는 연결이 있으면 순환이 생긴다. 그러면 따라가기를 끝낼 수 없다. 이번 장의 단순한 리스트에는 순환이 없다. 비어 있지 않은 리스트의 어느 노드에서 출발해도 마지막 노드에 도달한다.

값 23은 인덱스 1에 있다. 인덱스와 값은 다르다. 1번 칸을 재사용하면 인덱스는 같아도 값은 달라질 수 있다.

### 이미 아는 노드 뒤에 어떻게 넣을까?

17과 31 사이에 23을 넣으려 한다. 0번의 기존 다음 위치는 2번이다. 먼저 새 노드가 2번을 가리키게 한다. 그 뒤 0번이 새 노드를 가리키게 한다. `link_lnode(0,1)`은 다음 두 대입을 한다.

```text
lnodes[1].next = lnodes[0].next   // 2
lnodes[0].next = 1
결과: first=0; 0(17) → 1(23) → 2(31) → -1
```

두 대입을 뒤집으면 먼저 0번에서 2번으로 가던 연결을 덮어쓴다. 다음 대입은 `lnodes[1].next`에 1을 복사한다. 새 노드가 자기 자신을 가리키게 된다. 선행 노드의 연결을 바꾸기 전에 기존 다음 위치를 보관해야 한다.

`link_lnode(prev,node)`는 칸을 가져오지 않는다. 값을 검색하지도 않는다. 호출자는 사용을 맡은 유효하고 서로 다른 두 인덱스를 제공한다. 넣을 노드는 다른 활성 연결과 사용하지 않는 노드들의 연결에 속하지 않아야 한다. 이미 연결된 노드를 넣으면 순환이 생기거나 두 리스트가 섞일 수 있다.

### 중간 노드를 어떻게 뺄까?

앞 노드가 뺄 노드의 다음을 가리키게 한다. `delete_next_lnode(0)`은 1을 보관한다. `lnodes[0].next`를 2로 바꾸고 1을 반환한다.

```text
전: first=0; 0(17) → 1(23) → 2(31) → -1
후: first=0; 0(17) → 2(31) → -1
반환: 1; lnodes[1].next는 여전히 2
```

활성 연결에서 노드를 빼는 일을 분리(detach)라고 한다. 분리된 노드의 `next`는 그대로다. 호출자는 다른 곳에 쓰거나 재사용할 수 있도록 반환할 때까지 그 인덱스를 보관한다. 연결에서 뺐다는 이유만으로 다른 요청이 그 칸을 받을 수 있는 것은 아니다.

유효한 선행 노드 뒤에 노드가 없으면 `delete_next_lnode(prev)`는 `-1`을 반환하고 아무것도 바꾸지 않는다. 이 함수는 일치하는 값을 검색하지 않는다. 호출자의 `first`도 바꾸지 못한다. 첫 노드를 빼려면 호출자가 기존 첫 인덱스를 보관하고 `first`를 그 노드의 다음으로 옮겨야 한다.

### 배열 하나를 여러 리스트가 쓸 수 있을까?

뒤의 값을 옮기지 않고 리스트 중간의 연결을 바꿀 수 있다. 먼저 선행 노드를 알아야 한다. 세 번째 노드를 찾으려면 `first`에서 시작해 연결을 두 번 따라간다. `lnodes[2]`는 실제 배열의 2번 칸이다. 연결 순서의 세 번째 노드라는 뜻이 아니다. 각 노드는 다음 위치를 기록할 정수 하나도 더 쓴다.

두 리스트가 필요한 공간은 때마다 달라질 수 있다. 열 칸을 다섯 칸씩 나눠 주면 둘째 리스트가 한 칸만 써도 첫째 리스트는 여섯 번째 칸을 못 쓴다. 대신 비어 있는 칸이면 어느 리스트나 가져가게 한다. 리스트마다 시작 인덱스를 따로 둔다. 활성 노드는 서로 겹치지 않는다. 배열 전체에는 여전히 노드 열 개만 들어간다. 비어 있는 공간을 함께 쓴다고 용량이 늘지는 않는다.

### 비어 있는 노드는 어디서 가져올까?

새 기록을 넣으려면 사용하지 않는 칸이 필요하다. 매번 배열 전체를 찾는 대신 사용 가능한 칸끼리 연결한다. 이 연결을 가용 리스트(free list)라고 한다. 재사용할 노드를 모아 둔 고정 배열을 노드 풀(node pool)이라고 한다.

`free_head`는 첫 가용 칸의 인덱스다. `init_lnodes_pool()`는 모든 값을 0으로 만들고 다음 연결을 만든다.

```text
free_head = 0
가용 연결: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

`new_lnode(value,-1)`는 가용 연결의 첫 칸을 가져온다. `free_head`를 다음 칸으로 옮긴다. 가져온 칸에 값을 쓴다. 두 번째 인수로 `next`를 정한다. `-1`을 전달하면 다른 노드와 연결되지 않은 칸이 된다. 반환값은 저장한 값이 아니라 인덱스다. 가용 칸이 없으면 `-1`을 반환하고 아무것도 바꾸지 않는다. 배열에 접근하기 전에 반환값을 검사한다.

| 초기화 후 호출 | 반환 인덱스 | `free_head` | 가져온 칸 |
| --- | ---: | ---: | --- |
| `new_lnode(17,-1)` | 0 | 1 | `data=17, next=-1` |
| `new_lnode(23,-1)` | 1 | 2 | `data=23, next=-1` |
| `new_lnode(31,-1)` | 2 | 3 | `data=31, next=-1` |

가용 연결에서 칸을 빼서 호출자에게 맡기는 일을 할당(allocation)이라고 한다. 이 함수들은 C의 `malloc`이나 `free`를 호출하지 않는다. 앞의 삽입을 재현하려면 `link_lnode(0,2)`, `link_lnode(0,1)`을 차례로 호출한다.

같은 세 칸으로 두 리스트를 만들 수도 있다. `first_a=0`에서 `0(17)→2(31)→-1`로 연결하고, `first_b=1`에서 `1(23)→-1`로 연결한다. 두 리스트가 함께 쓰는 가용 연결은 3번부터 시작한다. 어느 리스트가 요청해도 첫 가용 칸을 받는다. 풀은 분리된 칸을 포함해 할당된 노드를 소유한 사용자가 없을 때만 초기화한다. 어느 리스트든 사용 중이면 초기화가 두 리스트의 기록을 덮어쓴다.

### 뺀 칸은 언제 다시 쓸 수 있을까?

`0(17)→1(23)→2(31)→-1`, `free_head=3`인 하나의 리스트로 돌아가자. `delete_next_lnode(0)` 뒤에는 1번이 분리되고 `free_head`는 여전히 3이다. 필요한 값은 `free_lnode(1)` 전에 읽는다. 이 호출은 칸을 가용 연결의 맨 앞에 붙인다.

```text
free_head = 1
가용 연결: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode`는 `next`를 덮어쓴다. `data`는 지우지 않는다. 이어서 `new_lnode(8,-1)`을 호출하면 1을 반환한다. 그 칸은 `data=8, next=-1`이 된다. 다른 리스트가 그 칸을 받을 수도 있다.

칸을 올바른 상태 하나에 두는 책임을 소유 책임(ownership)이라고 한다. 칸은 가용 연결, 활성 연결 하나, 호출자가 보관한 분리 상태 가운데 하나에만 속해야 한다. 분리한 뒤 반환하지 않은 칸은 계속 사용할 수 없다. 그 인덱스까지 잃으면 활성 리스트의 노드가 열 개보다 적어도 풀이 소진될 수 있다.

활성 노드를 반환하면 리스트가 쓰는 연결을 덮어쓴다. 1번을 연속 두 번 반환하면 `lnodes[1].next=1`이 되어 가용 연결에 순환이 생긴다. `free_lnode`는 범위 밖 인덱스를 거절하지만 범위 안의 소유 상태는 검사하지 못한다. 잘못된 연결은 실행하지 않고 종이에 추적한다.

1번을 반환한 뒤에는 이전 호출자가 자기 기록처럼 그 칸을 쓰면 안 된다. 재사용 전의 `next`는 가용 연결의 일부다. `data`에는 23이 남아 있을 수 있다. 재사용 뒤에 읽으면 다른 리스트의 값 8을 볼 수 있다. `next`에 쓰면 다른 리스트나 가용 연결이 망가질 수 있다. `data`에 쓰면 다른 호출자의 값이 바뀔 수 있다. 필요한 값과 다음 위치는 반환 전에 보관한다.

### 마지막에 넣은 값을 먼저 꺼내려면?

4장은 마지막에 넣은 값을 먼저 꺼냈다. 같은 LIFO 규칙을 연결로 지켜 보자. 새 기록을 시작 노드로 넣고 같은 끝에서 뺀다. 연결 노드로 만든 스택을 연결 스택(linked Stack)이라고 한다. 호출자의 `first`가 맨 위를 가리킨다.

독립된 새 풀에서 `first=-1`로 시작한다. 값을 넣을 때는 분리된 칸을 할당하고 성공 여부를 검사한다. 새 노드의 `next`를 기존 `first`로 만든다. 그 뒤 `first`를 새 인덱스로 바꾼다. 할당이 `-1`을 반환하면 기존 `first`와 연결을 그대로 둔다.

값을 뺄 때는 `first!=-1`인지 검사한다. 기존 첫 인덱스와 그 값, 다음 위치를 보관한다. `first`를 다음 위치로 옮긴 뒤 기존 칸을 `free_lnode`로 반환한다. 이 끝에는 `delete_next_lnode`에 줄 선행 노드가 없다. 호출자가 시작 인덱스를 직접 바꾼다.

| 새 풀에서의 동작 | `first` | 맨 위부터의 연결 | `free_head` |
| --- | ---: | --- | ---: |
| 17 넣기 | 0 | 0(17) → -1 | 1 |
| 23 넣기 | 1 | 1(23) → 0(17) → -1 | 2 |
| 31 넣기 | 2 | 2(31) → 1(23) → 0(17) → -1 | 3 |
| 31을 꺼내고 2번 반환 | 1 | 1(23) → 0(17) → -1 | 2 |
| 23을 꺼내고 1번 반환 | 0 | 0(17) → -1 | 1 |
| 17을 꺼내고 0번 반환 | -1 | 비어 있음 | 0 |

출력은 31, 23, 17이다. 마지막 제거는 `first=-1`로 만든다. 빈 리스트에서는 노드를 뺄 수 없다. 기존 노드 함수를 사용해 호출자 쪽에서 만든 스택이다. `lab.c`에 별도 스택 API가 있는 것은 아니다.

### 들어온 순서를 연결 리스트로 어떻게 지킬까?

이번에는 17, 23, 31을 도착한 순서로 처리하려 한다. 새 기록은 마지막 노드 뒤에 붙이고 첫 노드에서 뺀다. 양 끝을 기억하므로 검색하지 않는다. 먼저 들어온 값을 먼저 꺼내는 규칙을 **FIFO**라고 한다. 이 규칙을 따르는 구조가 **큐**다. 앞에서 만든 노드를 큐에 적용한다.

사용 중인 노드가 없는 독립 실험에서 `init_lnodes_pool(); head = tail = -1;`로 준비한다. `enqueue(value)`는 노드를 할당해 꼬리에 붙이고 성공하면 `true`를 반환한다. 새 끝 노드의 `next`는 `-1`이다. 비어 있지 않으면 기존 끝 노드가 새 노드를 가리키고 `tail`이 새 노드로 옮겨간다. 빈 큐라면 양 끝 모두 새 노드가 된다. 가용 칸이 없으면 풀과 큐를 바꾸지 않고 `false`를 반환한다.

`dequeue()`는 가장 오래된 **값**을 반환하고 그 노드를 내부에서 반환한다. 호출자는 `is_empty_queue()`로 비어 있지 않은지 확인한다. 반환된 값에 `free_lnode`를 적용하면 안 된다. 유일한 노드를 빼면 `head`와 `tail`이 모두 `-1`이 된다.

내부 노드 함수는 인덱스를 다룬다. `enqueue_lnode(index)`는 이미 할당해 분리한 칸을 붙인다. 그 칸의 `next`는 `-1`이어야 한다. `dequeue_lnode()`는 칸을 분리하고 인덱스를 반환하지만 재활용하지 않는다. 빈 큐에서는 상태를 바꾸지 않고 `-1`을 반환한다. 내부 함수를 직접 쓸 때는 데이터를 읽은 뒤 `free_lnode`를 호출한다. 공개 함수 `dequeue()`는 이 과정을 직접 수행한다.

`dequeue()`의 빈 큐 검사는 `assert`다. `NDEBUG`로 빌드하면 검사가 사라지므로 호출자의 비어 있지 않다는 조건은 계속 필요하다. 데이터 값 `-1`도 큐에 넣을 수 있다. 값을 빈 큐 표시로 쓰지 않는다. `enqueue(value)`의 결과는 먼저 변수에 저장하고 검사한다. `assert(enqueue(value))`처럼 상태 변경을 검사 안에 넣으면 검사가 사라질 때 삽입도 생략된다.

| 새 풀에서의 동작 | 반환 | `head` | `tail` | 활성 칸 | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| 23, 31, 8을 모두 꺼내기 | 값 | -1 | -1 | 비어 있음 | 0 (열 칸 모두 가용) |

가용 칸 0을 재사용해 기다리던 값 뒤에 8을 붙여도 도착 순서를 지킨다. 배열 인덱스의 크기가 꺼내는 순서를 정하지 않는다. 8장은 같은 공개 함수에 트리나 그래프의 ID를 값으로 넣는다. BFS 호출자가 큐 노드의 할당과 반환을 직접 관리하지 않는다.

## Calculating Efficiency

### 연결 하나를 바꾸는 일은 얼마나 걸릴까?

할당은 가용 연결의 첫 인덱스를 가져온다. 반환은 인덱스 하나를 앞에 붙인다. 선행 노드를 이미 알 때 삽입은 연결 둘을 바꾼다. 삭제는 다음 노드 하나를 읽고 연결 하나까지 바꾼다. 모두 연결 전체를 돌지 않으므로 O(1)이다. 선행 노드를 값으로 찾아야 한다면 그 검색은 별도다. 활성 노드 `n`개를 모두 볼 수 있으므로 O(n)이다.

첫 노드는 연결을 따라가지 않고 찾는다. 세 번째 노드는 `next`를 두 번 따라간다. `n`개 중 마지막 노드는 처음부터 `n-1`번 따라간다. 연결 순서로 위치를 찾는 일은 O(n)이 될 수 있다. 이미 아는 실제 배열 인덱스로 접근하는 일은 O(1)이다.

### 연결을 기록하는 데 공간은 얼마나 들까?

노드마다 정수 값 하나와 정수 연결 하나를 저장한다. 활성 기록 수와 관계없이 정수 둘을 가진 노드 열 개와 `free_head`, `head`, `tail`을 예약한다. 여러 리스트가 비어 있는 칸을 함께 쓸 수 있다. 리스트를 더 만들 때마다 시작 인덱스도 따로 필요하다. 한 칸이 두 활성 리스트에 동시에 속하면 안 된다.

용량 `C`칸 초기화는 각 칸에 한 번씩 기록하므로 O(C)다. 실습의 `C`는 10이다. 풀의 저장 공간은 O(C)다. 각 연산의 추가 지역 저장 공간은 O(1)이다. 할당 실패는 가용 연결의 소진이다. 운영체제에 새 메모리를 요청하지 않는다.

### 스택이나 큐의 순서를 지키는 일은 얼마나 걸릴까?

연결 스택은 `first`와 일정한 수의 노드 필드만 바꾼다. 첫 기록을 넣고 빼는 일은 O(1)이다. 공개 enqueue는 가용 칸 하나를 가져와 기억한 tail 뒤에 붙인다. 공개 dequeue는 head를 옮기고 값 하나를 읽은 뒤 칸을 반환한다. 각 단계의 필드 작업 수가 일정하므로 두 함수 모두 O(1)이다.

열 칸은 풀을 쓰는 모든 구조가 동시에 할당한 기록 수를 제한한다. 넣고 빼기를 반복하며 처리하는 전체 값 수를 열 개로 제한하지 않는다. 같은 풀에서 스택이 세 칸을 쓰면 큐에는 최대 일곱 칸이 남는다. 8장의 BFS도 동시에 기다리는 수와 전체 처리 수의 차이를 사용한다.

## Glossary

앞에서 사용한 동작과 상태에 다음 이름을 붙인다.

| 이름 | 이 실습에서의 뜻 |
| --- | --- |
| node / 노드 | `data`와 `next`를 가진 기록 |
| singly linked list / 단일 연결 리스트 | 노드마다 다음 인덱스를 하나씩 기록한 순서 |
| first / 시작 노드 | 따로 보관하는 첫 노드의 인덱스, 빈 리스트라면 `-1` |
| cycle / 순환 | 이미 지난 노드로 돌아가는 연결 경로 |
| traversal / 순회 | `-1`을 만날 때까지 `next`를 따라가는 일 |
| node pool / 노드 풀 | 여러 사용자가 함께 쓰는 고정 저장 공간 `lnodes[10]` |
| free list / 가용 리스트 | `free_head`부터 연결한 사용 가능 인덱스 |
| allocation / 할당 | 사용하려고 가용 연결에서 칸을 꺼내는 일 |
| detach / 분리 | 활성 연결에서 빼되 가용 연결에 반환하지 않는 일 |
| recycle / 반환 | 분리된 할당 칸을 가용 연결에 넣는 일 |
| ownership / 소유 책임 | 한 칸을 올바른 상태 하나에만 두는 책임 |
| stale index / 이전 소유자의 인덱스 | 반환 뒤에도 보관했지만 더는 그 호출자의 기록을 뜻하지 않는 인덱스 |
| linked Stack / 연결 스택 | 시작 노드에 넣고 시작 노드에서 빼는 연결 리스트 |
| LIFO | 마지막에 넣은 값을 먼저 꺼내는 규칙 |
| linked queue / 연결 큐 | `tail` 뒤에 붙이고 `head`에서 빼는 연결 리스트 |
| FIFO | 도착한 순서대로 기록을 처리하는 규칙 |
| public enqueue / dequeue | 값을 받아 성공 여부 반환 / 값을 반환하고 노드 재활용 |
| node helpers | 칸 인덱스를 다루는 `enqueue_lnode`, `dequeue_lnode` |

## Coding Plan

앞의 동작이 다음 동작을 준비하도록 순서를 정한다.

1. `Linked_Node`와 `lnodes[10]`을 둔다. 각 리스트의 시작 인덱스를 따로 보관한다. 활성 연결은 `-1`로 끝내고 순환을 막는다.
2. 선행 노드의 기존 다음 위치를 새 노드에 보관한 뒤 선행 노드의 연결을 바꾼다. 다음 노드를 뺄 때는 그 노드의 다음을 연결하고 뺀 인덱스를 보관한다.
3. 사용하지 않는 열 칸을 `free_head`부터 연결한다. `new_lnode(data_value,next_value)`로 할당한다. 분리된 칸은 두 번째 인수에 `-1`을 준다. 반환값을 검사한 뒤 배열에 접근한다.
4. 필요한 데이터는 `free_lnode` 전에 읽는다. 분리된 칸을 정확히 한 번 반환한다. 반환 뒤에는 이전 소유자로서 그 칸에 접근하지 않는다.
5. 호출자 코드에서 연결 스택을 만든다. `first`에 넣고 빈 상태를 검사한 뒤 뺀다. 기존 첫 노드의 값과 다음 위치를 보관하고 `first`를 옮긴 뒤 반환한다.
6. 내부 노드 함수로 큐 양 끝의 변화를 추적한다. 이후 값 기반 `enqueue`, `dequeue`를 쓴다. 호출자는 삽입 성공과 빈 큐를 확인한다.
7. 가용 연결 소진, 꼬리 뒤 삭제, 공유 풀의 분리, 스택 순서, 빈 큐 전환, 재사용을 독립된 유효 상태에서 검사한다. 미반환, 중복 반환, 반환 후 접근은 종이에 추적한다.

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

다음 호출자는 중간 삽입, 분리, 재사용을 재현한다. 아래 드라이버는 각각 독립된 프로그램으로 새 풀에서 실행한다. 각 코드 블록을 `lab.c` 옆에 저장하고 드라이버만 컴파일한다. 모든 검사와 상태 변경은 `NDEBUG`에서도 실행된다.

```c
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = new_lnode(17, -1);
    int middle = new_lnode(23, -1);
    int last = new_lnode(31, -1);
    if (first == -1 || middle == -1 || last == -1) return 1;
    link_lnode(first, last);
    link_lnode(first, middle);
    int removed = delete_next_lnode(first);
    if (removed != middle || lnodes[first].next != last) return 1;
    free_lnode(removed);
    int reused = new_lnode(8, -1);
    if (reused != middle || lnodes[reused].next != -1) return 1;
    return 0;
}
```

### 같은 노드를 스택에 적용한다

호출자가 자기 `first`를 보관한다. 기존 첫 칸의 값과 다음 위치를 저장한 뒤 반환한다. 17, 23, 31을 넣고 출력 31, 23, 17을 검사한다. 할당이 실패하면 기존 스택을 그대로 둔다.

```c
#include "lab.c"

int main(void) {
    init_lnodes_pool();
    int first = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode(values[i], -1);
        if (node == -1) return 1;
        lnodes[node].next = first;
        first = node;
    }
    for (int i = 2; i >= 0; --i) {
        if (first == -1) return 1;
        int old_first = first;
        int value = lnodes[old_first].data;
        int next = lnodes[old_first].next;
        first = next;
        free_lnode(old_first);
        if (value != values[i]) return 1;
    }
    if (first != -1 || free_head != 0) return 1;
    return 0;
}
```

### 같은 노드를 큐에 적용한다

호출자는 삽입 성공과 빈 큐를 확인한다. `dequeue()`가 내부에서 칸을 반환한다. 출력은 17, 23, 31이다. 데이터 값 `-1`도 유효한 값인지 검사한다.

```c
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
    if (!is_empty_queue() || head != -1 || tail != -1) return 1;
    bool added = enqueue(-1);
    if (!added || is_empty_queue()) return 1;
    int value = dequeue();
    if (value != -1 || !is_empty_queue()) return 1;
    return 0;
}
```
