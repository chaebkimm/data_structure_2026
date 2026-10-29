# 7장. 연결 리스트

1장은 배열의 연속된 활성 칸에 값을 저장했다. 이번 장에서는 값을 옮기지 않고 연결을 바꿔 순서를 바꾼다. 현재 `lab.c`는 열 칸 배열과 정수로 기록한 연결을 사용한다. 같은 연결을 스택과 큐에 적용한다.

[English textbook](textbook.md) · [수업 활동](class_material.md) · [개념 슬라이드](ppt_material.md) · [실습 슬라이드](ppt_lab_material.md) · [질문 슬라이드](ppt.md) · [실습](lab.md)

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

17과 31 사이에 23을 넣으려 한다. 0번의 기존 다음 위치는 2번이다. 먼저 새 노드가 2번을 가리키게 한다. 그 뒤 0번이 새 노드를 가리키게 한다. `simple_link_lnode_to_prev(0,1)`은 다음 두 대입을 한다.

```text
lnodes[1].next = lnodes[0].next   // 2
lnodes[0].next = 1
결과: first=0; 0(17) → 1(23) → 2(31) → -1
```

두 대입을 뒤집으면 먼저 0번에서 2번으로 가던 연결을 덮어쓴다. 다음 대입은 `lnodes[1].next`에 1을 복사한다. 새 노드가 자기 자신을 가리키게 된다. 선행 노드의 연결을 바꾸기 전에 기존 다음 위치를 보관해야 한다.

`simple_link_lnode_to_prev(prev,node)`는 칸을 가져오지 않는다. 값을 검색하지도 않는다. 호출자는 사용을 맡은 유효하고 서로 다른 두 인덱스를 제공한다. 선행 노드는 큐가 아닌 일반 리스트에 속해야 한다. 넣을 노드는 다른 활성 연결과 사용하지 않는 노드들의 연결에 속하지 않아야 한다. 그 노드의 `next`는 `-1`이어야 한다. 이미 연결된 노드를 넣으면 순환이 생기거나 두 리스트가 섞일 수 있다.

### 중간 노드를 어떻게 뺄까?

앞 노드가 뺄 노드의 다음을 가리키게 한다. `simple_delink_next_lnode_from_prev(0)`은 1을 보관한다. `lnodes[0].next`를 2로 바꾼다. `lnodes[1].next`를 `-1`로 만든 뒤 1을 반환한다.

```text
전: first=0; 0(17) → 1(23) → 2(31) → -1
후: first=0; 0(17) → 2(31) → -1
반환: 1; lnodes[1].next = -1
```

활성 연결에서 노드를 빼는 일을 분리(detach)라고 한다. 분리된 노드의 `next`는 `-1`이다. 남은 노드와 연결되지 않은 상태다. 호출자는 다른 곳에 쓰거나 재사용할 수 있도록 반환할 때까지 그 인덱스를 보관한다. 연결에서 뺐다는 이유만으로 다른 요청이 그 칸을 받을 수 있는 것은 아니다.

유효한 선행 노드 뒤에 노드가 없으면 `simple_delink_next_lnode_from_prev(prev)`는 `-1`을 반환하고 아무것도 바꾸지 않는다. 이 함수는 일치하는 값을 검색하지 않는다. 호출자의 `first`도 바꾸지 못한다. 선행 노드는 큐가 아닌 일반 리스트에 속해야 한다. 첫 노드를 빼려면 호출자가 기존 첫 인덱스를 보관하고 `first`를 그 노드의 다음으로 옮겨야 한다. 기존 첫 노드의 `next`를 `-1`로 만든 뒤 반환하거나 다른 곳에 넣는다.

### 배열 하나를 여러 리스트가 쓸 수 있을까?

뒤의 값을 옮기지 않고 리스트 중간의 연결을 바꿀 수 있다. 먼저 선행 노드를 알아야 한다. 세 번째 노드를 찾으려면 `first`에서 시작해 연결을 두 번 따라간다. `lnodes[2]`는 실제 배열의 2번 칸이다. 연결 순서의 세 번째 노드라는 뜻이 아니다. 각 노드는 다음 위치를 기록할 정수 하나도 더 쓴다.

두 리스트가 필요한 공간은 때마다 달라질 수 있다. 열 칸을 다섯 칸씩 나눠 주면 둘째 리스트가 한 칸만 써도 첫째 리스트는 여섯 번째 칸을 못 쓴다. 대신 비어 있는 칸이면 어느 리스트나 가져가게 한다. 리스트마다 시작 인덱스를 따로 둔다. 활성 노드는 서로 겹치지 않는다. 배열 전체에는 여전히 노드 열 개만 들어간다. 비어 있는 공간을 함께 쓴다고 용량이 늘지는 않는다.

### 비어 있는 노드는 어디서 가져올까?

새 기록을 넣으려면 사용하지 않는 칸이 필요하다. 매번 배열 전체를 찾는 대신 사용 가능한 칸끼리 연결한다. 이 연결을 가용 리스트(free list)라고 한다. 재사용할 노드를 모아 둔 고정 배열을 노드 풀(node pool)이라고 한다. 선언과 반복문이 같은 크기를 쓰도록 이름을 붙인다. `enum { CAPACITY = 10 };`은 정수 상수 10에 `CAPACITY`라는 이름을 붙인다.

`free_head`는 첫 가용 칸의 인덱스다. `init_lnodes_pool()`의 첫 호출은 다음 연결을 만든다.

```text
free_head = 0
가용 연결: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
```

호출할 때마다 이 연결을 다시 만들면 사용 중인 노드의 연결까지 덮어쓸 수 있다. 지역 변수 앞에 `static`을 붙이면 함수가 끝나도 값이 유지된다. `static int initialized`는 처음 한 번 0으로 시작한다. 첫 호출에서 1이 된 뒤에는 함수를 다시 호출해도 아무것도 바꾸지 않고 돌아간다. 이 초기화 함수는 사용한 풀을 리셋하지 않는다. 연결만 쓰고 데이터는 쓰지 않는다. 전역 배열의 값은 프로그램 시작 때 0이지만 이후 초기화 호출로 데이터가 지워지지는 않는다.

`new_lnode()`는 초기화 함수를 호출한 뒤 가용 연결의 첫 칸을 가져온다. `free_head`를 다음 칸으로 옮긴다. 가져온 칸의 `next`를 `-1`로 만든다. 인수를 받지 않고 `data`도 쓰지 않는다. 반환한 인덱스를 검사한 뒤 호출자가 원하는 값을 저장한다. 가용 칸이 없으면 `-1`을 반환하고 아무것도 바꾸지 않는다.

| 새 프로그램에서의 호출과 호출자 대입 | 반환 인덱스 | `free_head` | 가져온 칸 |
| --- | ---: | ---: | --- |
| 할당; 인덱스 검사; 17 저장 | 0 | 1 | `data=17, next=-1` |
| 할당; 인덱스 검사; 23 저장 | 1 | 2 | `data=23, next=-1` |
| 할당; 인덱스 검사; 31 저장 | 2 | 3 | `data=31, next=-1` |

표의 각 데이터 대입 전에는 반환한 인덱스가 `-1`인지 먼저 검사해야 한다. 가용 연결에서 칸을 빼서 호출자에게 맡기는 일을 할당(allocation)이라고 한다. 이 함수들은 C의 `malloc`이나 `free`를 호출하지 않는다. 앞의 삽입을 재현하려면 `simple_link_lnode_to_prev(0,2)`, `simple_link_lnode_to_prev(0,1)`을 차례로 호출한다.

같은 세 칸으로 두 리스트를 만들 수도 있다. `first_a=0`에서 `0(17)→2(31)→-1`로 연결하고, `first_b=1`에서 `1(23)→-1`로 연결한다. 두 리스트가 함께 쓰는 가용 연결은 3번부터 시작한다. 어느 리스트가 요청해도 첫 가용 칸을 받는다. `init_lnodes_pool()`를 다시 호출해도 두 리스트와 가용 연결은 유지된다. 칸을 다시 쓰려면 연결에서 빼서 반환해야 한다. 초기화 함수를 다시 호출해도 그 칸을 되찾지 않는다.

### 뺀 칸은 언제 다시 쓸 수 있을까?

`0(17)→1(23)→2(31)→-1`, `free_head=3`인 하나의 리스트로 돌아가자. `simple_delink_next_lnode_from_prev(0)` 뒤에는 1번이 분리되고 `free_head`는 여전히 3이다. 필요한 값은 `free_lnode(1)` 전에 읽는다. 이 호출은 칸을 가용 연결의 맨 앞에 붙인다.

```text
free_head = 1
가용 연결: 1 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → -1
lnodes[1].data = 23; lnodes[1].next = 3
```

`free_lnode`는 `next`를 덮어쓴다. `data`는 지우지 않는다. 이어서 `new_lnode()`를 호출하면 1을 반환한다. 그 칸은 `next=-1`이고 기존 값 23이 남아 있다. 새 호출자가 기록을 쓰기 전에 `lnodes[1].data=8`을 대입한다. 다른 리스트가 그 칸을 받을 수도 있다.

칸을 올바른 상태 하나에 두는 책임을 소유 책임(ownership)이라고 한다. 칸은 가용 연결, 활성 연결 하나, 호출자가 보관한 분리 상태 가운데 하나에만 속해야 한다. 분리한 뒤 반환하지 않은 칸은 계속 사용할 수 없다. 그 인덱스까지 잃으면 활성 리스트의 노드가 열 개보다 적어도 풀이 소진될 수 있다.

활성 노드를 반환하면 리스트가 쓰는 연결을 덮어쓴다. 1번을 연속 두 번 반환하면 `lnodes[1].next=1`이 되어 가용 연결에 순환이 생긴다. `free_lnode(-1)`는 아무것도 하지 않는다. 다른 인수는 범위 안에 있고 할당되었으며 어디에서도 참조하지 않는 노드여야 한다. 그 노드의 `next`는 `-1`이어야 한다. 함수는 이런 인수의 범위나 소유 상태를 검사하지 않는다. 잘못된 연결은 실행하지 않고 종이에 추적한다.

1번을 반환한 뒤에는 이전 호출자가 자기 기록처럼 그 칸을 쓰면 안 된다. 재사용 전의 `next`는 가용 연결의 일부다. `data`에는 23이 남아 있을 수 있다. 재사용 뒤에 읽으면 다른 리스트의 값 8을 볼 수 있다. `next`에 쓰면 다른 리스트나 가용 연결이 망가질 수 있다. `data`에 쓰면 다른 호출자의 값이 바뀔 수 있다. 필요한 값과 다음 위치는 반환 전에 보관한다.

### 마지막에 넣은 값을 먼저 꺼내려면?

4장은 마지막에 넣은 값을 먼저 꺼냈다. 같은 LIFO 규칙을 연결로 지켜 보자. 새 기록을 시작 노드로 넣고 같은 끝에서 뺀다. 연결 노드로 만든 스택을 연결 스택(linked Stack)이라고 한다. 호출자의 `first`가 맨 위를 가리킨다.

새 프로그램에서 `first=-1`로 시작한다. 값을 넣을 때는 분리된 칸을 할당하고 성공 여부를 검사한다. 새 노드의 `data`에 값을 쓴다. `next`를 기존 `first`로 만든다. 그 뒤 `first`를 새 인덱스로 바꾼다. 할당이 `-1`을 반환하면 기존 `first`와 연결을 그대로 둔다.

값을 뺄 때는 `first!=-1`인지 검사한다. 기존 첫 인덱스와 그 값, 다음 위치를 보관한다. `first`를 다음 위치로 옮긴다. 기존 칸의 `next`를 `-1`로 만든 뒤 `free_lnode`로 반환한다. 이 끝에는 `simple_delink_next_lnode_from_prev`에 줄 선행 노드가 없다. 호출자가 시작 인덱스를 직접 바꾼다.

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

소스의 전역 변수 `qhead`, `qtail`은 처음에 모두 `-1`이다. 값을 넣으려면 `new_lnode()`를 호출하고 인덱스를 검사한다. 그 칸의 `data`를 쓴 뒤 인덱스를 `enqueue_lnode(node)`에 전달한다. 노드는 할당되었고 어디에서도 참조하지 않으며 `next=-1`인 분리 상태여야 한다. 비어 있지 않으면 기존 끝 노드가 새 노드를 가리키고 `qtail`이 새 노드로 옮겨간다. 빈 큐라면 양 끝 모두 새 노드가 된다. 이 함수는 칸을 할당하지 않고 성공 여부도 반환하지 않는다. `enqueue_lnode(-1)`는 아무것도 하지 않는다.

`dequeue_lnode()`는 가장 오래된 **노드의 인덱스**를 반환한다. 데이터 값을 반환하는 것이 아니다. `qhead`를 옮기고 뺀 노드의 `next`를 `-1`로 만든다. 노드는 호출자에게 할당된 상태로 남는다. 유일한 노드를 빼면 `qtail`도 `-1`이 된다. 빈 큐에서는 상태를 바꾸지 않고 `-1`을 반환한다. 반환 인덱스를 검사한 뒤 `lnodes[node].data`를 읽는다. 사용이 끝나면 `free_lnode(node)`로 분리된 칸을 반환한다.

데이터 값 `-1`도 유효하다. 빈 상태 표시는 저장한 값이 아니라 노드 인덱스에 적용된다. 이 소스에는 값 기반 `enqueue`, `dequeue` 함수가 없다. 할당, 데이터 대입, 삽입, 제거, 데이터 읽기, 반환은 호출자가 각각 수행한다.

| 새 프로그램에서의 동작 | 반환 노드 | `qhead` | `qtail` | 큐의 칸 | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| 0 할당, 17 저장, 0 삽입 | 할당: 0 | 0 | 0 | 0 → -1 | 1 |
| 1 할당, 23 저장, 1 삽입 | 할당: 1 | 0 | 1 | 0 → 1 → -1 | 2 |
| 2 할당, 31 저장, 2 삽입 | 할당: 2 | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue_lnode()` | 0; 값 17 읽기 | 1 | 2 | 1 → 2 → -1 | 3 |
| `free_lnode(0)` | 없음 | 1 | 2 | 1 → 2 → -1 | 0 |
| 0 할당, 8 저장, 0 삽입 | 할당: 0 | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| 23, 31, 8 제거, 읽기, 반환 | 인덱스 1, 2, 0 | -1 | -1 | 비어 있음 | 0 (열 칸 모두 가용) |

가용 칸 0을 재사용해 기다리던 값 뒤에 8을 붙여도 도착 순서를 지킨다. 배열 인덱스의 크기가 꺼내는 순서를 정하지 않는다. 이후 BFS 호출자는 트리나 그래프의 ID를 `data`에 저장할 수 있다. 그 ID와 `dequeue_lnode()`가 반환하는 풀의 칸 인덱스는 서로 다르다.

### 계속 지켜야 할 규칙은 무엇일까?

풀을 초기화한 뒤에는 각 연산을 마칠 때 모든 칸과 양 끝의 상태가 맞아야 한다. 이렇게 계속 유지할 규칙을 불변식(invariant)이라고 한다.

- 각 활성 연결과 가용 연결은 0–9 인덱스를 쓰고 같은 노드를 반복하지 않으며 `-1`로 끝난다.
- 열 칸 각각은 활성 연결 하나, 가용 연결, 호출자가 보관한 분리 상태 가운데 정확히 하나에 속한다. 서로 다른 소유자가 겹치면 안 된다. 분리된 노드의 `next`는 `-1`이다.
- 일반 리스트는 시작 인덱스를 따로 보관한다. 큐는 `qhead == -1 && qtail == -1`일 때만 비어 있다.
- 비어 있지 않은 큐의 `qtail`은 `qhead`에서 도달하는 마지막 노드다. `lnodes[qtail].next == -1`이다.
- 끝에 넣고 처음에서 빼면 FIFO 순서를 지킨다. 뺀 노드는 호출자가 정확히 한 번 반환할 때까지 할당 상태다.

이 규칙은 함수나 호출자 쪽의 전체 갱신을 마친 뒤 적용한다. 함수가 모든 규칙을 검사하지는 않는다. 호출 전에 명시된 조건을 확인한다. 큐에 속한 노드는 큐 함수로 다룬다. 일반 선행 노드 함수로 바꾸면 큐 양 끝의 정보가 맞지 않을 수 있다.

## Calculating Efficiency

### 연결 하나를 바꾸는 일은 얼마나 걸릴까?

초기화 뒤의 할당은 가용 연결의 첫 인덱스를 가져온다. 반환은 인덱스 하나를 앞에 붙인다. 선행 노드를 이미 알 때 삽입은 연결 둘을 바꾼다. 삭제는 다음 노드 하나를 읽고 건너뛴 뒤 뺀 노드의 연결을 `-1`로 만든다. 모두 연결 전체를 돌지 않으므로 O(1)이다. 선행 노드를 값으로 찾아야 한다면 그 검색은 별도다. 활성 노드 `n`개를 모두 볼 수 있으므로 O(n)이다.

첫 노드는 연결을 따라가지 않고 찾는다. 세 번째 노드는 `next`를 두 번 따라간다. `n`개 중 마지막 노드는 처음부터 `n-1`번 따라간다. 연결 순서로 위치를 찾는 일은 O(n)이 될 수 있다. 이미 아는 실제 배열 인덱스로 접근하는 일은 O(1)이다.

### 연결을 기록하는 데 공간은 얼마나 들까?

노드마다 정수 값 하나와 정수 연결 하나를 저장한다. 활성 기록 수와 관계없이 정수 둘을 가진 노드 열 개와 `free_head`, `qhead`, `qtail`, 초기화 여부를 유지하는 정수 하나를 예약한다. 여러 리스트가 비어 있는 칸을 함께 쓸 수 있다. 리스트를 더 만들 때마다 시작 인덱스도 따로 필요하다. 한 칸이 두 활성 리스트에 동시에 속하면 안 된다.

용량 `C`칸의 첫 초기화는 각 연결에 한 번씩 기록하므로 O(C)다. 실습의 `C`는 10이다. `new_lnode()`가 첫 초기화까지 수행하면 그 첫 할당은 O(C)다. 이후 초기화 호출과 할당은 O(1)이다. 풀의 저장 공간은 O(C)다. 각 연산의 추가 지역 저장 공간은 O(1)이다. 할당 실패는 가용 연결의 소진이다. 운영체제에 새 메모리를 요청하지 않는다.

### 스택이나 큐의 순서를 지키는 일은 얼마나 걸릴까?

연결 스택은 `first`와 일정한 수의 노드 필드만 바꾼다. 첫 기록을 넣고 빼는 일은 O(1)이다. 큐 함수는 기억한 끝에 붙이거나 기억한 처음을 분리한다. 필드 작업 수가 일정하므로 두 함수 모두 O(1)이다. 초기화 뒤에는 호출자의 할당, 데이터 대입, 값 읽기, 반환도 각각 O(1)이다.

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
| detach / 분리 | 활성 연결에서 빼서 `next=-1`로 만들되 가용 연결에 반환하지 않는 일 |
| recycle / 반환 | 분리된 할당 칸을 가용 연결에 넣는 일 |
| ownership / 소유 책임 | 한 칸을 올바른 상태 하나에만 두는 책임 |
| stale index / 이전 소유자의 인덱스 | 반환 뒤에도 보관했지만 더는 그 호출자의 기록을 뜻하지 않는 인덱스 |
| linked Stack / 연결 스택 | 시작 노드에 넣고 시작 노드에서 빼는 연결 리스트 |
| LIFO | 마지막에 넣은 값을 먼저 꺼내는 규칙 |
| linked queue / 연결 큐 | `qtail` 뒤에 붙이고 `qhead`에서 빼는 연결 리스트 |
| FIFO | 도착한 순서대로 기록을 처리하는 규칙 |
| enqueue / 삽입 | 할당해 분리한 인덱스를 `enqueue_lnode`로 큐에 붙이기 |
| dequeue / 제거 | `dequeue_lnode`로 분리된 인덱스 받기; 호출자가 읽고 반환 |
| invariant / 불변식 | 전체 연산을 마친 뒤 유지하는 규칙 |
| `enum` / 열거 상수 | `CAPACITY`처럼 정수 상수에 이름을 붙이는 문법 |
| `static` local / 정적 지역 변수 | 호출 사이에 값을 유지하며 처음 한 번 초기화하는 지역 변수 |

## Coding Plan

앞의 동작이 다음 동작을 준비하도록 순서를 정한다.

1. `Linked_Node`와 `lnodes[CAPACITY]`를 둔다. `enum { CAPACITY = 10 };`은 정수 상수 10에 `CAPACITY`라는 이름을 붙인다. 각 리스트의 시작 인덱스를 따로 보관한다. 활성 연결은 `-1`로 끝내고 순환을 막는다.
2. 선행 노드의 기존 다음 위치를 새 노드에 보관한 뒤 선행 노드의 연결을 바꾼다. 다음 노드를 뺄 때는 그 노드의 다음을 연결한다. 뺀 노드의 `next`를 `-1`로 만들고 인덱스를 보관한다.
3. 첫 초기화 호출에서 사용하지 않는 열 칸을 `free_head`부터 연결한다. 지역 `static` 표시로 이후 호출이 풀을 보존하게 한다. `new_lnode()`로 할당하고 인덱스를 검사한 뒤 호출자가 `data`를 쓴다.
4. 필요한 데이터는 `free_lnode` 전에 읽는다. 할당되었고 어디에서도 참조하지 않으며 `next=-1`인 칸을 정확히 한 번 반환한다. 반환 뒤에는 이전 소유자로서 그 칸에 접근하지 않는다.
5. 호출자 코드에서 연결 스택을 만든다. `first`에 넣고 빈 상태를 검사한 뒤 뺀다. 기존 첫 노드의 값과 다음 위치를 보관한다. `first`를 옮기고 뺀 노드를 분리한 뒤 반환한다.
6. 큐 양 끝은 `qhead`, `qtail`에 둔다. 할당하고 데이터를 쓴 뒤 `enqueue_lnode`로 붙인다. `dequeue_lnode`로 분리하고 인덱스를 검사한다. 값을 읽은 뒤 반환한다. 마지막 제거 후에는 양 끝 모두 빈 상태여야 한다.
7. 가용 연결 소진, 꼬리 뒤 삭제, 반복 초기화, 공유 풀의 분리, 스택 순서, 빈 큐 전환, 재사용을 유효 상태에서 검사한다. 새 풀의 예는 별도 프로그램으로 실행한다. 미반환, 중복 반환, 반환 후 접근은 종이에 추적한다.

## C Code

다음 코드는 연결 큐 예를 포함한 현재 `lab.c` 전체다. 드라이버에서 한 번만 포함한다. 소스에는 `main`이 없다. `enum`은 정수 상수 10에 `CAPACITY`라는 이름을 붙인다. 실습 슬라이드는 같은 동작에 짧은 이름을 쓴다.

| 실습 슬라이드 이름 | 현재 `lab.c` 이름 |
| --- | --- |
| `arr`, `CAP`, `fhead` | `lnodes`, `CAPACITY`, `free_head` |
| `link_node`, `del_next_node` | `simple_link_lnode_to_prev`, `simple_delink_next_lnode_from_prev` |
| `init_nodes_pool`, `new_node`, `free_node` | `init_lnodes_pool`, `new_lnode`, `free_lnode` |
| `enqueue_node`, `dequeue_node`, `is_empty` | `enqueue_lnode`, `dequeue_lnode`, `is_empty_queue` |

슬라이드의 `enqueue_node`는 새 끝 노드의 `next`를 직접 지운다. 소스는 호출자가 이미 `next=-1`인 분리된 노드를 제공하도록 요구한다. 실행할 드라이버에서는 이 소스의 호출 조건을 지킨다.

```c
enum { CAPACITY = 10 };

struct Linked_Node {
  int data;
  int next;
};
struct Linked_Node lnodes[CAPACITY];

/* Unchecked: caller guarantees 0 <= prev, node < CAPACITY,
 * prev != node, prev is an allocated non-queue node,
 * and node is allocated, unreferenced, and isolated (lnodes[node].next == -1). */
void simple_link_lnode_to_prev(int prev, int node) {
	lnodes[node].next = lnodes[prev].next;
	lnodes[prev].next = node;
}

/* Unchecked: caller guarantees 0 <= prev < CAPACITY and prev is an
 * allocated non-queue node.
 * Returns the detached node index (or -1 if none); caller owns the returned node. */
int simple_delink_next_lnode_from_prev(int prev) {
	int node = lnodes[prev].next;
	if (node != -1) {
		lnodes[prev].next = lnodes[node].next;
		lnodes[node].next = -1;
	}
	return node;
}

int free_head = -1;

/* Initializes the free list on first use; does not reset an active pool. */
void init_lnodes_pool(void) {
	static int initialized = 0;
	if (initialized) { return; }
	initialized = 1;

	for (int i = 0; i < CAPACITY - 1; i++) {
		lnodes[i].next = i + 1;
	}
	lnodes[CAPACITY - 1].next = -1;
	free_head = 0;
}

int new_lnode(void) {
	init_lnodes_pool();
	if (free_head == -1) {
		return -1;
	}
	int node = free_head;
	free_head = lnodes[free_head].next;
	lnodes[node].next = -1;
	return node;
}

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void free_lnode(int node) {
	if (node == -1) {
		return;
	}
	lnodes[node].next = free_head;
	free_head = node;
}

int qhead = -1;
int qtail = -1;

int is_empty_queue(void) { return qhead == -1; }

/* Unchecked: caller guarantees node == -1, or (0 <= node < CAPACITY and
 * node is allocated, unreferenced, and isolated (lnodes[node].next == -1)). */
void enqueue_lnode(int node) {
	if (node == -1) {
		return;
	}
	if (is_empty_queue()) {
		qhead = qtail = node;
	} else {
		lnodes[qtail].next = node;
		qtail = node;
	}
}

/* Returns the detached node index (or -1 if none); caller owns the returned node. */
int dequeue_lnode(void) {
	if (is_empty_queue()) {
		return -1;
	}
	int oldest = qhead;
	qhead = lnodes[qhead].next;
	if (qhead == -1) {
		qtail = -1;
	}
	lnodes[oldest].next = -1;
	return oldest;
}
```

다음 호출자는 중간 삽입, 분리, 재사용을 재현한다. 반복 초기화가 활성 노드를 보존하는지도 검사한다. 할당한 칸에 기존 데이터가 남는지도 검사한다. 아래 드라이버는 각각 별도 프로그램으로 실행한다. 각 프로그램은 처음 상태의 전역 저장 공간에서 시작한다. 드라이버를 `lab.c` 옆에 저장하고 드라이버만 컴파일한다. 검사와 상태 변경은 `NDEBUG` 여부와 관계없이 실행된다.

```c
#include "lab.c"

int main(void) {
    int first = new_lnode();
    int middle = new_lnode();
    int last = new_lnode();
    if (first == -1 || middle == -1 || last == -1) return 1;
    lnodes[first].data = 17;
    lnodes[middle].data = 23;
    lnodes[last].data = 31;
    simple_link_lnode_to_prev(first, last);
    simple_link_lnode_to_prev(first, middle);
    int saved_free_head = free_head;
    init_lnodes_pool(); /* This repeated call must preserve live links. */
    if (free_head != saved_free_head || lnodes[first].next != middle) return 1;
    int removed = simple_delink_next_lnode_from_prev(first);
    if (removed != middle || lnodes[first].next != last) return 1;
    if (lnodes[removed].next != -1 || lnodes[removed].data != 23) return 1;
    free_lnode(removed);
    int reused = new_lnode();
    if (reused != middle || lnodes[reused].next != -1) return 1;
    if (lnodes[reused].data != 23) return 1;
    lnodes[reused].data = 8;
    free_lnode(reused);
    removed = simple_delink_next_lnode_from_prev(first);
    if (removed != last || lnodes[first].next != -1) return 1;
    free_lnode(removed);
    if (simple_delink_next_lnode_from_prev(first) != -1) return 1;
    free_lnode(first);
    return 0;
}
```

### 같은 노드를 스택에 적용한다

호출자가 자기 `first`를 보관한다. 값과 다음 위치를 저장하고 `first`를 옮긴다. 기존 첫 노드를 분리한 뒤 반환한다. 17, 23, 31을 넣고 출력 31, 23, 17을 검사한다. 할당이 실패하면 기존 스택을 그대로 둔다.

```c
#include "lab.c"

int main(void) {
    int first = -1;
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode();
        if (node == -1) return 1;
        lnodes[node].data = values[i];
        lnodes[node].next = first;
        first = node;
    }
    for (int i = 2; i >= 0; --i) {
        if (first == -1) return 1;
        int old_first = first;
        int value = lnodes[old_first].data;
        int next = lnodes[old_first].next;
        first = next;
        lnodes[old_first].next = -1;
        free_lnode(old_first);
        if (value != values[i]) return 1;
    }
    if (first != -1 || free_head != 0) return 1;
    return 0;
}
```

### 같은 노드를 큐에 적용한다

호출자는 각 노드를 할당하고 데이터를 쓴 뒤 붙인다. 반환받은 인덱스를 검사하고 데이터를 읽은 뒤 분리된 칸을 반환한다. 출력은 17, 23, 31이다. 데이터 값 `-1`도 유효하다. 빈 큐의 제거 결과 `-1`은 인덱스가 없다는 표시다.

```c
#include "lab.c"

int main(void) {
    int values[3] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = new_lnode();
        if (node == -1) return 1;
        lnodes[node].data = values[i];
        enqueue_lnode(node);
    }
    for (int i = 0; i < 3; ++i) {
        int node = dequeue_lnode();
        if (node == -1) return 1;
        int value = lnodes[node].data;
        if (lnodes[node].next != -1) return 1;
        free_lnode(node);
        if (value != values[i]) return 1;
    }
    if (!is_empty_queue() || qhead != -1 || qtail != -1) return 1;
    if (dequeue_lnode() != -1) return 1;
    int node = new_lnode();
    if (node == -1) return 1;
    lnodes[node].data = -1;
    enqueue_lnode(node);
    node = dequeue_lnode();
    if (node == -1) return 1;
    int value = lnodes[node].data;
    free_lnode(node);
    if (value != -1 || !is_empty_queue() || qtail != -1) return 1;
    return 0;
}
```
