# Chapter 10. 이진 힙과 공통 켜짐 시각

이 장은 제공된 [lab.c](lab.c)를 따른다.
[영문 교재](textbook.md)도 같은 예제와 소스를 사용한다.
기존 알림 우선순위 큐 라이브러리는 선택 참고 자료다.
그 라이브러리의 동적 확장, 도착 순서, 상태 반환값은 현재 실습의 규칙이 아니다.

## Thinking Logically

### 다음 최솟값을 어떻게 준비할까?

7, 3, 5, 1, 9, 4가 차례로 들어온다. 매번 가장 작은 수를 꺼내야 한다.
FIFO Queue는 먼저 들어온 7을 꺼낸다. Stack은 마지막에 들어온 4를 꺼낸다.
두 규칙 모두 1을 선택하지 못한다.

정렬하지 않은 배열은 나머지 다섯 위치를 비교해서 최솟값을 찾을 수 있다.
다음 수를 꺼낼 때도 다시 탐색한다.
배열 전체를 정렬하면 최솟값을 바로 읽을 수 있지만 새 수를 넣을 때 많은 값을 옮길 수 있다.
최솟값을 바로 읽으면서 변경 뒤에는 일부 위치만 복구할 규칙이 필요하다.

정해진 순위에 따라 다음 항목을 선택하는 자료 구조를 우선순위 큐(priority queue)라고 한다.
이 동작은 여러 표현으로 구현할 수 있다.
실습은 배열 위치를 트리로 배치한 이진 힙(binary heap)을 사용한다.
먼저 배치와 부모·자식 사이의 규칙을 살펴본다.

### 배열 위치를 어떻게 트리로 볼까?

위치 0 아래에 1과 2를 둔다. 위치 1 아래에 3과 4를 둔다.
위치 2 아래에 5와 6을 둔다.
각 층을 왼쪽부터 채운 뒤 다음 층으로 내려간다.
이 모양이 완전 이진 트리(complete binary tree)다.
사용 중인 배열 위치 하나가 노드다. 바로 위의 위치가 부모다.
맨 위의 위치가 root다.

실습은 `int heap[10]`을 예약한다. `size`는 사용 중인 값의 개수다.
현재 트리는 위치 0부터 `size - 1`까지만 사용한다.
열 칸을 예약했다고 열 칸 모두 트리에 속하는 것은 아니다.
위치 사이의 관계는 다음과 같다.

```text
부모:         (i - 1) / 2, 단 i > 0
왼쪽 자식:    2 * i + 1, 단 결과 < size
오른쪽 자식:  2 * i + 2, 단 결과 < size
```

정수 나눗셈은 나머지를 버린다.
`parent`, `left`, `right`는 해당 위치가 없으면 -1을 반환한다.
이 -1은 위치가 없다는 표시다. 저장된 값과 구별해야 한다.
힙 안에는 -1을 포함한 음수도 저장할 수 있다.
없는 위치를 배열 첨자로 사용해서는 안 된다.

여섯 위치를 사용하면 위치 2에는 왼쪽 자식 5만 있다.
새 값을 위치 `size`에 붙이면 완전 이진 트리 모양을 유지한다.

### 어떤 규칙이면 root가 최솟값일까?

모든 부모의 값을 자식 값 이하로 둔다.
어느 위치에서 부모를 따라 올라가도 값은 커지지 않는다.
따라서 root에는 최솟값이 있다.
이 조건이 최소 힙의 순서 불변식(invariant)이다.
불변식은 연산이 끝날 때마다 유지해야 하는 관계다.

형제끼리 정렬할 필요는 없다.
왼쪽 부분 트리의 모든 값이 오른쪽보다 작을 필요도 없다.
`[1,3,4,7,9,5]`는 최소 힙이지만 배열 전체가 정렬된 상태는 아니다.
임의의 값을 찾기 위한 이진 탐색 트리의 순서와도 다르다.

`init_heap()`은 `size = 0`, `is_min_heap = 1`로 설정한다.
예약된 배열의 기존 값은 지우지 않는다.
모드가 1이면 `comp(i,j)`는 `heap[i] <= heap[j]`를 검사한다.
모드를 0으로 바꾸면 `heap[i] >= heap[j]`를 검사한다.
부모를 자식 이상으로 두는 규칙은 최대 힙 순서다. root에 최댓값이 온다.
`is_min_heap`은 모드 변수다. 힙 전체를 검사하는 함수가 아니다.

### 없는 위치나 같은 값을 어떻게 비교할까?

아래로 복구하려면 먼저 실제로 존재하는 자식을 골라야 한다.
`proper_parent(i,j)`는 두 위치 중 위에 있어야 하는 위치를 반환한다.
둘 다 -1이면 -1을 반환한다. 하나만 -1이면 존재하는 위치를 반환한다.
둘 다 존재할 때만 `comp(i,j)`로 값을 비교한다.

값이 같으면 첫 번째 인자를 고른다.
부모를 첫 인자로 주면 같은 값에서 교환하지 않는다.
왼쪽 자식을 첫 인자로 주면 자식 값이 같을 때 왼쪽을 고른다.
이 선택은 도착 순서를 보존한다는 보장이 아니다.
실습에는 도착 순서를 저장하는 필드가 없다.

### 새 값은 어디서 순서를 깨뜨릴까?

기존 힙은 이미 순서를 지킨다.
끝에 새 값을 붙이면 새 값과 부모 사이에서만 문제가 시작할 수 있다.
새 값이 부모보다 위에 있어야 하면 두 값을 교환한다.
이제 부모의 이전 위치에서 같은 검사를 반복한다.
부모가 선택되거나 root에 도착하면 멈춘다.
이 과정이 위로 복구하는 sift-up이다. 실습의 함수 이름은 `heapify_up`이다.

실행 전에 각 `add` 뒤의 사용 구간을 예측한다.

| 추가한 값 | 복구 뒤 사용 구간 |
| --- | --- |
| 7 | `[7]` |
| 3 | `[3,7]` |
| 5 | `[3,7,5]` |
| 1 | `[1,3,5,7]` |
| 9 | `[1,3,5,7,9]` |
| 4 | `[1,3,4,7,9,5]` |

`add(data)`는 `int i = size++;`로 이전 크기를 `i`에 저장하고 크기를 늘린다.
`heap[i]`에 값을 쓴 다음 `heapify_up(i)`를 호출한다.
호출자는 추가 전에 `size < 10`인지 확인해야 한다.
`add` 안에는 용량 검사, 동적 확장, 실패 상태 반환이 없다.

### root를 꺼낸 뒤 모양을 어떻게 유지할까?

위치 0을 그대로 제거하면 맨 위에 구멍이 남는다.
반환할 값을 저장하고 마지막 사용 값을 위치 0으로 옮긴다.
그다음 사용 개수를 하나 줄인다. 사용 구간은 완전 이진 트리 모양을 유지한다.
새 root에서만 순서 위반이 시작할 수 있다.

존재하는 자식 중 위에 있어야 하는 자식을 고른다.
그 자식이 현재 값보다 위에 있어야 하면 교환한다.
자식의 이전 위치에서 계속한다. 현재 값이 선택되면 멈춘다.
이 과정이 아래로 복구하는 sift-down이다. 함수 이름은 `heapify_down`이다.

`[1,3,4,7,9,5]`에서 `remove_root()`를 호출한다.
1을 저장하고 마지막 값 5를 위치 0으로 옮긴다.
사용 개수를 줄인 직후 배열은 `[5,3,4,7,9]`다.
자식 3을 골라 교환한다. 이제 5는 자식 7과 9 이하이므로 멈춘다.

```text
[5,3,4,7,9] -> [3,5,4,7,9]
반환값: 1
```

소스의 `heap[--size]`는 먼저 크기를 줄이고 마지막 값을 읽는다.
값이 하나뿐이면 크기가 0이 되고 `heap[0]`을 같은 위치에 복사한다.
소스는 이때도 `heapify_down(0)`을 호출한다.
양쪽 자식이 -1이므로 `proper_parent(0,-1)`은 값 비교 없이 0을 반환한다.
반복은 즉시 멈춘다.
이미 빈 힙에서 제거하는 호출은 유효하지 않다. 호출 전에 `size > 0`을 확인한다.
사용하지 않는 칸에 이전 값이 남아 있어도 그 칸은 현재 힙에 속하지 않는다.

### 배열 전체를 한 번에 힙으로 만들 수 있을까?

모든 값이 이미 배열에 있다면 하나씩 추가할 필요가 없다.
마지막 층의 잎은 자식이 없으므로 복구할 관계도 없다.
부모 위치를 뒤에서부터 처리한다.
각 부모를 처리할 때 자식 부분 트리는 이미 복구되어 있다.
따라서 그 부모에서 아래로 복구하면 된다.
이 방식이 아래에서 위로 만드는 bottom-up heap construction이다.

`[7,3,5,1,9,4]`를 사용 구간에 쓰고 `size = 6`으로 둔다.
최소 모드에서 `heapify()`는 위치 2, 1, 0을 처리한다.

```text
시작:       [7,3,5,1,9,4]
위치 2 복구: [7,3,4,1,9,5]
위치 1 복구: [7,1,4,3,9,5]
위치 0 복구: [1,3,4,7,9,5]
```

`is_min_heap`만 바꾸면 비교 규칙만 바뀐다. 배열은 움직이지 않는다.
새 순서를 사용하기 전에 다시 구성해야 한다.
마지막 배열에서 모드를 0으로 바꾸고 `heapify()`를 호출하면
`[9,7,5,1,3,4]`가 된다. 다음 제거는 9를 반환한다.
빈 힙과 값 하나인 힙은 아래에서 위로 복구할 부모가 없다.

### 열 장치가 모두 켜진 최초 시각은 언제일까?

이번에는 장치마다 켜져 있는 시간 구간이 있다.
모든 장치의 켜짐 구간에 속하는 최초 시각을 찾아야 한다.
장치마다 구간 하나를 골랐다고 하자.
모두 켜지려면 가장 늦게 켜지는 장치도 시작해야 한다.
동시에 가장 먼저 꺼지는 장치가 아직 켜져 있어야 한다.

가장 늦은 시작을 `L`, 가장 이른 종료를 `R`이라고 하자.
선택한 구간들은 정확히 `L <= R`일 때 겹친다.
실습의 닫힌 구간(closed interval)은 양 끝 시각을 포함한다.
따라서 두 시각이 같아도 겹친다. 겹치는 구간의 최초 시각은 `L`이다.

다음 입력을 계속 사용한다.

| 장치 ID | 켜져 있는 구간 |
| --- | --- |
| 0 | `[1,3]`, `[7,10]` |
| 1 | `[2,5]`, `[8,12]` |
| 2–9 각각 | `[4,9]` |

처음에는 가장 늦은 시작이 4, 가장 이른 종료가 3이다.
선택한 구간에 공통 시각이 없다.
3에 끝나는 장치 0의 구간으로는 4에 도달할 수 없다.
장치 0을 다음 구간 `[7,10]`으로 옮긴다.
이제 경계는 7과 5다. 장치 1을 `[8,12]`로 옮긴다.
경계는 8과 9가 된다. 최초 공통 켜짐 시각은 8이다.

### 구간과 현재 선택을 어떻게 저장할까?

구간 전체를 힙에 복사하지 않고 각 장치의 현재 구간만 지정하면 된다.
`toggle_info[10][10]`의 행 하나가 ID 하나의 시간표다.
각 행은 시작·종료 쌍을 최대 다섯 개 저장한다.
장치 0의 앞 네 값은 `1,3,7,10`이다.
`interval_size[0]`은 정수 개수 4가 아니라 구간 개수 2다.

`epoch[id]`는 현재 구간 번호다. 0부터 시작하며 실제 시각이 아니다.
`get_on_time(id)`는 `2 * epoch[id]` 위치를 읽는다.
`get_off_time(id)`는 그다음 위치를 읽는다.
행의 사용하지 않는 칸은 추가 구간이 아니다.

실행 전에 열 ID 모두에 구간을 하나 이상, 다섯 개 이하로 넣는다.
시각은 0 이상의 정수로 두고 각 구간에서 `on <= off`를 지킨다.
다음 구간의 시작은 이전 구간의 종료보다 커야 한다.
이 조건에서 구간은 시간순으로 분리되고 -1은 실패를 뜻할 수 있다.
소스는 구간 개수, 끝점 순서, 입력 누락을 검사하지 않는다.
닫힌 구간이므로 한 시각만 포함하는 `[t,t]`도 허용된다.

### 같은 ID를 왜 두 힙에 넣을까?

가장 늦은 시작과 가장 이른 종료를 각각 바로 읽어야 한다.
한 가지 순서로는 두 경계를 모두 root에 둘 수 없다.
따라서 열 ID를 모두 담은 힙 두 개를 유지한다.

`max_on_heap.array`는 현재 시작 시각이 큰 ID를 위에 둔다.
`min_off_heap.array`는 현재 종료 시각이 작은 ID를 위에 둔다.
root에 저장된 값은 시각이 아니라 ID다.
그 ID로 시간 읽기 함수를 호출해야 끝점을 얻는다.
검색 중에는 ID를 추가하거나 제거하지 않는다.
이 두 힙은 일반 정수 힙의 `size`나 `is_min_heap`을 사용하지 않는다.

두 객체의 자료형은 `struct Heap_Full`이다.
객체에는 배열과 호출할 함수를 고르는 함수 포인터(function pointer) 두 개가 있다.
`int (*comp)(int x, int y)`는 ID 두 개를 비교하는 함수를 가리킨다.
`void (*swap)(int i, int j)`는 위치 두 개를 교환하는 함수를 가리킨다.
`_heap->comp(...)`는 `_heap`이 가리키는 객체에 연결된 비교 함수를 호출한다.
각 비교 함수는 `epoch`를 통해 현재 시각을 읽는다.

`_proper_parent`의 인자는 위치다.
함수는 배열에서 ID를 읽은 뒤 그 ID를 비교 함수에 넘긴다.
추적할 때 위치, ID, 구간 번호, 시각을 구별한다.
시각이 같은 ID가 여러 개라면 여러 root 후보가 가능하다.
숫자가 작은 ID나 먼저 들어온 ID를 우선한다는 보장은 없다.

### 이동한 ID의 위치를 어떻게 찾을까?

한 장치의 구간 번호를 바꾸면 두 힙에서 그 ID의 비교 기준이 바뀐다.
같은 ID가 두 배열에서 차지하는 위치는 서로 다를 수 있다.
매번 두 배열을 검색하면 전체 탐색을 반복한다.
대신 ID를 첨자로 받아 현재 힙 위치를 저장하는 역위치 배열(inverse position map)을 둔다.

```text
max_on_heap.array[_max_heap_pos[id]] == id
min_off_heap.array[_min_heap_pos[id]] == id
```

`__swap__`은 힙의 ID 두 개를 교환하면서 두 ID의 역위치도 고친다.
위치 `i`, `j`에 ID `x`, `y`가 있었다면
교환 뒤 `pos[x] = j`, `pos[y] = i`여야 한다.
`_swap_max`, `_swap_min`은 각각 맞는 힙 배열과 역위치 배열을 선택한다.
힙 순서만 맞아서는 충분하지 않다.
역위치가 오래된 상태면 다음 복구가 다른 장치에서 시작한다.

`_reheapify`는 변경 위치와 부모를 비교한다.
root이거나 부모가 여전히 위에 있어야 하면 아래로 복구한다.
변경 위치가 부모보다 위에 있어야 하면 위로 복구한다.
변경 전의 나머지 힙은 순서를 지키므로 한 위치에서 시작하는 복구면 된다.
현재 응용에서는 다음 구간으로 갈수록 시작·종료 시각이 커진다.
시작 시각은 최대 힙에서 올라갈 수 있고 종료 시각은 최소 힙에서 내려갈 수 있다.
공유 복구 함수는 양쪽 방향을 모두 처리한다.

고정 힙은 항상 열 위치를 쓴다.
`_left(4)`는 9, `_right(4)`는 -1이다. 위치 5–9는 잎이다.
`_heapify`는 5부터 시작한다. 위치 5 호출은 아무 교환도 하지 않는다.
이후 4부터 0까지 복구한다.
이 고정 크기 계산을 일반 정수 힙의 가변 크기 계산과 혼동하지 않는다.

### 가장 먼저 끝나는 구간을 버려도 될까?

`L > R`이면 어떤 장치의 현재 구간은 다른 장치의 시작보다 먼저 끝난다.
그 끝나는 구간으로는 이후의 공통 시각을 만들 수 없다.
앞서 버린 구간도 같은 이유로 제외되었다.
따라서 가장 먼저 끝나는 현재 구간을 버려도 해답을 건너뛰지 않는다.
종료 시각이 같은 장치가 여럿이면 그중 하나를 진행해도 된다.

`all_on_time()`은 먼저 `_init_heaps()`를 호출한다.
모든 구간 번호를 0으로 돌리고, ID 배열과 역위치를 초기화하고,
함수 포인터를 설정한 뒤 두 힙을 구성한다.
입력 구간을 채우거나 일반 정수 힙을 초기화하지는 않는다.

현재 구간들이 겹치지 않으면 최소 종료 힙의 root ID를 고른다.
그 ID의 `epoch`를 하나 늘린다.
번호가 `interval_size[id]`와 같아지면 구간이 소진되었으므로 -1을 반환한다.
존재하지 않는 구간을 읽기 전에 반환한다.
아직 구간이 있으면 `_min_heap_pos[id]`에서 최소 종료 힙을 복구하고
`_max_heap_pos[id]`에서 최대 시작 힙을 복구한다. 그다음 다시 확인한다.

| 상태 | `epoch[0]` | `epoch[1]` | 가장 늦은 시작 `L` | 가장 이른 종료 `R` | 동작 |
| --- | --- | --- | --- | --- | --- |
| 초기 | 0 | 0 | 4 | 3 | ID 0 진행 |
| 첫 복구 뒤 | 1 | 0 | 7 | 5 | ID 1 진행 |
| 둘째 복구 뒤 | 1 | 1 | 8 | 9 | 8 반환 |

호출할 때마다 첫 구간부터 다시 시작한다.
실패한 호출은 어떤 구간 번호를 구간 개수와 같은 값으로 남긴다.
그때 두 힙도 마지막 변경을 복구하지 않았을 수 있다.
-1을 받은 직후 현재 구간을 읽어서는 안 된다.
`all_on_time()`을 다시 호출하거나 유효한 입력을 넣고 `_init_heaps()`로 초기화한다.

## Calculating Efficiency

### 한 번의 복구는 얼마나 움직일까?

여섯 값에서 첫 최솟값을 전체 탐색하면 다른 다섯 위치와 비교한다.
힙은 root를 바로 읽는다. 위·아래 복구는 경로 하나만 따른다.
각 층에 1, 2, 4, 8개를 넣으면 네 층에 15개를 담는다.
값의 수가 두 배쯤 늘어날 때 층은 하나쯤 늘어난다.
이 증가가 로그 증가다. 사용 값의 수를 `n`이라 할 때 `O(log n)`으로 쓴다.

root 읽기는 `O(1)`이다.
일반화한 `add`와 `remove_root`의 최악 비용은 각각 `O(log n)`이다.
실습에는 메모리 할당이나 배열 확장 비용이 없다.
부모와의 비교, 두 자식 중 선택은 각각 일정한 작업이다.

### 아래에서 만들면 왜 선형 비용일까?

대부분의 위치는 트리 아래쪽에 있다.
약 절반은 잎이어서 복구하지 않는다.
약 4분의 1은 한 층, 약 8분의 1은 두 층까지만 내려갈 수 있다.
이 작업을 합하면 전체 값의 수에 일정한 수를 곱한 범위에 머문다.
모든 위치에 root의 전체 높이를 적용할 필요가 없다.
따라서 bottom-up `heapify`의 비용은 `O(n)`이다.
`add`를 `n`번 호출해서 만드는 방식의 최악 비용은 `O(n log n)`이다.
모든 값을 하나씩 제거하는 비용도 최악 `O(n log n)`이다.

### 구간을 진행할 때 무엇을 줄일까?

전체 탐색 방식은 구간을 진행할 때마다 `n`개 장치에서 두 경계를 다시 찾는다.
두 힙은 처음 구성할 때 `O(n)` 작업을 한다.
root 두 개를 읽는 작업은 일정하다.
구간 하나를 진행하면 `O(log n)` 복구를 두 번 한다.
역위치 배열은 변경 ID의 위치를 일정한 작업으로 찾는다.

실제로 다음 구간으로 이동한 횟수를 `a`라고 하면
일반화한 전체 비용은 `O(n + a log n)`이다.
마지막 소진 시도는 일정한 작업만 더한다.
모든 장치의 구간 수 합계를 `m`이라고 하면 성공적인 이동은 최대 `m - n`번이다.
마지막 소진 시도는 최대 한 번이다.
따라서 조금 넓은 상한으로 `O(n + m log n)`을 쓸 수 있다.
입력 구간을 적재하는 `O(m)` 작업은 별도다.
전체 탐색 방식은 `O(n(a + 1))` 작업을 한다.

실제 소스는 장치 열 개와 장치당 최대 다섯 구간으로 고정되어 있다.
성공적인 이동은 최대 마흔 번이다.
열 위치의 힙에서는 한 복구가 최대 세 간선을 지난다.
실제 실행 크기는 고정되어 있다.
위 수식은 배열과 크기 계산을 함께 확장했을 때의 증가를 설명한다.
배열 선언만 크게 바꿔서는 고정 크기 보조 함수가 일반화되지 않는다.

### 어떤 저장 공간을 예약할까?

일반 힙은 정수 열 개와 크기·모드 변수를 예약한다.
구간 응용은 입력 정수 100개, 구간 개수 열 개, 현재 번호 열 개,
ID 힙 배열 두 개, 역위치 배열 두 개, 함수 포인터 네 개를 예약한다.
복구는 반복문과 일정한 수의 지역 변수를 사용한다.
동적 할당이나 재귀 호출은 없다.

장치 `n`개와 전체 구간 `m`개로 일반화하면 입력은 `O(m)`,
힙·역위치·현재 번호는 `O(n)` 공간을 쓴다.
연산별 추가 지역 공간은 `O(1)`이다.
테스트에서 힙 전체나 역위치 전체를 검사하면 `O(n)` 위치를 방문한다.
이 검사는 경로 하나를 복구하는 연산과 구별해야 한다.
현재 소스에는 비교 횟수 계수기나 전체 검사 API가 없다.

## Glossary

앞서 추적한 표현과 동작에 이름을 붙인다.

| 이름 | 이 실습에서의 뜻 |
| --- | --- |
| 우선순위 큐 | 정해진 순위로 다음 항목을 선택하는 자료 구조 |
| 완전 이진 트리 | 층을 위에서 아래로, 각 층을 왼쪽에서 오른쪽으로 채운 트리 |
| 이진 힙 | 완전 이진 트리 모양과 부모·자식 순서를 유지하는 표현 |
| root | 위치 0. 극값 또는 극값을 가진 ID가 있는 위치 |
| 최소·최대 힙 | 각각 작은 값·큰 값을 부모 쪽에 두는 힙 |
| 불변식 | 완료된 연산이 유지해야 하는 관계 |
| sift-up, sift-down | 각각 위·아래 경로 하나를 따라 순서를 복구하는 동작 |
| bottom-up heapify | 자식 부분 트리부터 복구해서 전체 힙을 구성하는 방식 |
| 비교 함수 | 두 값 또는 ID 중 위에 있어야 하는 쪽을 정하는 함수 |
| 닫힌 구간 | 시작과 종료 시각을 모두 포함하는 구간 |
| epoch | 장치별 현재 구간 번호 |
| 함수 포인터 | 호출할 함수를 보관하는 필드 |
| 역위치 배열 | ID로 해당 힙에서의 현재 위치를 찾는 배열 |
| reheapify | 키 변경 뒤 방향을 골라 순서를 복구하는 동작 |
| 구간 소진 | 어떤 장치의 마지막 구간을 넘어가는 상태 |

## Coding Plan

테스트를 쓰기 전에 각 함수와 상태 변경을 연결한다.

1. 일반 힙의 사용 구간과 최소 모드 초기화를 확인한다.
2. 부모·자식 위치, 없는 위치 처리, 값 비교와 교환을 추적한다.
3. 아래 복구와 bottom-up 구성을 추적한다.
4. root 대체와 새 값 추가 뒤의 위 복구를 추적한다.
5. 열 시간표를 넣고 `epoch`를 두 시간 읽기 함수와 연결한다.
6. 고정 힙의 위치 인자와 비교 함수의 ID 인자를 구별한다.
7. 함수 포인터 호출과 교환 뒤의 역위치 갱신을 추적한다.
8. 고정 힙 구성, root 읽기, 복구 방향 선택을 추적한다.
9. 겹침 검사, 구간 진행, 소진, 두 힙 복구를 추적한다.
10. 독립적인 순서·역위치 검사와 작은 전체 탐색 기준 구현을 가진 테스트를 쓴다.

실습 함수는 모두 제공된다.
별도 실행 드라이버와 세 가지 원본 테스트 그룹을 작성한다.
구체적인 제출물은 [lab.md](lab.md)를 따른다.
빈 힙 제거와 열한 번째 추가는 거부 동작을 검사하는 실행 테스트가 아니다.
유효하지 않은 호출은 사전 조건 설명으로만 남긴다.

## C Code

다음은 원래 순서와 내용을 보존한 `lab.c` 전체다.
앞부분은 크기가 바뀌는 정수 힙이다.
뒷부분은 장치 ID 열 개를 모두 유지하는 두 힙이다.
소스에는 `main`이 없다. 별도 테스트 드라이버에서 한 번 포함하고 드라이버만 컴파일한다.
빌드 명령은 [실습 안내](lab.md)를 따른다.

```c
int heap[10];
int size;
int is_min_heap;

void init_heap() {
    size = 0;
    is_min_heap = 1;
}
int parent(int i) {return i <= 0 ? -1 : (i - 1) / 2;}
int left(int i) {return 2 * i + 1 >= size ? -1 : 2 * i + 1;}
int right(int i) {return 2 * i + 2 >= size ? -1 : 2 * i + 2;}
int comp(int i, int j) {
    return is_min_heap ? heap[i] <= heap[j] : heap[i] >= heap[j];
}
int proper_parent(int i, int j) {
    if (i == -1 && j == -1) {
        return -1;
    } else if (i == -1 || j == -1) {
        return i == -1 ? j : i;
    }
    return comp(i, j) ? i : j;
}
void swap_data(int i, int j) {
    int old_i_val = heap[i];
    int old_j_val = heap[j];
    heap[i] = old_j_val;
    heap[j] = old_i_val;
}
void heapify_down(int i) {
    while (i != -1) {
        int child = proper_parent(left(i), right(i));
        if (proper_parent(i, child) == i) {break;}
        swap_data(i, child);
        i = child;
    }
}
void heapify() {
    for (int i = parent(size - 1); i >= 0; i--) {
        heapify_down(i);
    }
}
int remove_root() {
    int root = 0;
    int data = heap[root];
    heap[root] = heap[--size];
    heapify_down(root);
    return data;
}
void heapify_up(int i) {
    while (i > 0) {
        int p = parent(i);
        if (proper_parent(p, i) == p) {break;}
        swap_data(i, p);
        i = p;
    }
}
void add(int data) {
    int i = size++;
    heap[i] = data;
    heapify_up(i);
}

int toggle_info[10][10];
int interval_size[10];
int epoch[10];

int get_on_time(int id) {
    return toggle_info[id][epoch[id] * 2];
}

int get_off_time(int id) {
    return toggle_info[id][epoch[id] * 2 + 1];
}

int _comp_on_max(int id_x, int id_y) {
    int on_time_x = get_on_time(id_x);
    int on_time_y = get_on_time(id_y);
    return on_time_x >= on_time_y;
}

int _comp_off_min(int id_x, int id_y) {
    int off_time_x = get_off_time(id_x);
    int off_time_y = get_off_time(id_y);
    return off_time_x <= off_time_y;
}

struct Heap_Full {
    int array[10];
    int (*comp)(int x, int y); 
    void (*swap)(int i, int j);
} max_on_heap, min_off_heap;

int _proper_parent(struct Heap_Full *_heap, int i, int j) {
    if (i == -1 && j == -1) {return -1;}
    else if (i == -1) {return j;}
    else if (j == -1) {return i;}
    else {
        int *arr = _heap->array;
        return _heap->comp(arr[i], arr[j]) ? i : j;
    }
}

int _parent(int i) {return i == 0 ? -1 : (i - 1) / 2;}
int _left(int i) {return i >= 5 ? -1 : 2 * i + 1;}
int _right(int i) {return i >= 4 ? -1 : 2 * i + 2;}

int _max_heap_pos[10];
int _min_heap_pos[10];

void __swap__(int i, int j, int *_arr, int *_heap_pos) {
    int x = _arr[i]; /* _heap_pos[x] == i */
    int y = _arr[j]; /* _heap_pos[y] == j */
    _arr[i] = y;
    _arr[j] = x;
    _heap_pos[x] = j;
    _heap_pos[y] = i;
}
void _swap_max(int i, int j) {__swap__(i, j, max_on_heap.array, _max_heap_pos);}
void _swap_min(int i, int j) {__swap__(i, j, min_off_heap.array, _min_heap_pos);}

void _heapify_down(struct Heap_Full *_heap, int i) {
    int leaf_start = 5;
    while (i < leaf_start) {
        int child = _proper_parent(_heap, _left(i), _right(i));
        int pp = _proper_parent(_heap, i, child);
        if (pp == i) {break;}
        _heap->swap(i, child);
        i = child;        
    }
}

void _heapify(struct Heap_Full *_heap) {
    for (int i = 5; i >= 0; i--) {
        _heapify_down(_heap, i);
    }
}

void _init_heaps() {
    for (int i = 0; i < 10; i++) {
        epoch[i] = 0;
        max_on_heap.array[i] = i;
        _max_heap_pos[i] = i;
        min_off_heap.array[i] = i;
        _min_heap_pos[i] = i;
    }
    max_on_heap.comp = _comp_on_max;
    max_on_heap.swap = _swap_max;
    min_off_heap.comp = _comp_off_min;
    min_off_heap.swap = _swap_min;
    _heapify(&max_on_heap);
    _heapify(&min_off_heap);
}

int _get_root(struct Heap_Full *_heap) {
    return _heap->array[0];
}

void _heapify_up(struct Heap_Full *_heap, int i) {
    while (i > 0) {
        int pp = _proper_parent(_heap, _parent(i), i);
        if (pp == _parent(i)) {break;}
        _heap->swap(i, _parent(i));
        i = _parent(i);
    }
}

void _reheapify(struct Heap_Full *_heap, int i) {
    int pp = _proper_parent(_heap, _parent(i), i);
    if (i == 0 || pp == _parent(i)) {_heapify_down(_heap, i);}
    else {_heapify_up(_heap, i);}
}

int check_all_on() {
    int last_on_id = _get_root(&max_on_heap);
    int first_off_id = _get_root(&min_off_heap);
    return get_on_time(last_on_id) <= get_off_time(first_off_id);
}

int all_on_time() {
    _init_heaps();
    while (!check_all_on()) {
        int id = _get_root(&min_off_heap);
        if (++epoch[id] == interval_size[id]) {return -1;}
        _reheapify(&min_off_heap, _min_heap_pos[id]);
        _reheapify(&max_on_heap, _max_heap_pos[id]);
    }
    int last_on_id = _get_root(&max_on_heap);
    return get_on_time(last_on_id);
}
```
