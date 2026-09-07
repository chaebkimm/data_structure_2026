# 1장 보충. CPython 리스트 읽기

Python에서는 배열을 직접 관리하지 않고 리스트를 사용한다. 그러나 CPython은
내부에서 배열을 관리해야 한다. 이 보충 교재에서는 간단한 C 구현을 먼저 읽고,
같은 원리를 사용하는 CPython 교육용 구현을 읽는다.

예제 소스는 다음 두 파일에 있다.

- [`simplified_array_list.c`](../code/lecture/simplified_array_list.c)
- [`cpython_list_standalone.c`](../code/lecture/cpython_list_standalone.c)

두 번째 파일은 CPython 3.12.11의
[`Include/cpython/listobject.h`](https://github.com/python/cpython/blob/v3.12.11/Include/cpython/listobject.h)와
[`Objects/listobject.c`](https://github.com/python/cpython/blob/v3.12.11/Objects/listobject.c)를
바탕으로 만들었다. 원본을 그대로 복사한 파일은 아니다. 인터프리터, 오류 객체,
가비지 컬렉션, 스레드 제어 코드는 독립 실행에 필요한 간단한 코드로 바꾸었다.

## 논리적으로 생각해 보기

### 고정 배열 리스트는 어디에서 막힐까?

크기가 4인 배열의 모든 공간에 데이터가 들어 있다고 하자.

```text
size = 4
capacity = 4

인덱스       0     1     2     3
           +----+----+----+----+
값         | 10 | 15 | 20 | 30 |
           +----+----+----+----+
```

새 항목을 저장할 공간이 없다. 앞에서 만든 고정 용량 리스트는 추가 요청을
거절해야 한다.

Python 리스트는 다르게 동작한다. 더 큰 메모리 블록을 얻는다. 기존 항목을 새
블록으로 옮긴다. 그런 다음 새 항목을 저장한다.

프로그램 실행 중에 더 큰 배열을 얻을 수 있는 배열 리스트를 동적 배열 리스트
(dynamic array list)라고 한다.

### 리스트는 어떤 정보를 기억해야 할까?

리스트에는 세 가지 정보가 필요하다.

- 배열의 주소
- 사용 중인 항목 수
- 배열에 마련된 전체 자리 수

간단한 구현은 세 정보를 하나의 C 구조체에 넣는다.

```c
struct ArrayList {
    int *data;
    size_t size;
    size_t capacity;
};
```

구조체(struct)는 관련된 변수를 하나의 값으로 묶는다. 이 교재에서는 `typedef`를
사용하지 않는다. 구조체를 사용할 때마다 `struct`를 쓴다. `data`는 포인터(pointer)다.
포인터는 메모리 주소를 저장한다. 여기서 `data`는 할당된 정수 배열의 첫 주소를
저장한다.

`size`와 `capacity`의 뜻은 다르다. `size`는 사용 중인 항목 수다. `capacity`는
사용할 수 있는 전체 자리 수다.

```text
size = 3
capacity = 4

인덱스       0     1     2     3
           +----+----+----+----+
값         | 10 | 15 | 30 |  ? |
           +----+----+----+----+
              사용 중      미사용
```

미사용 자리에 어떤 값이 남아 있어도 리스트의 항목이 아니다.

### 어떤 조건이 항상 참이어야 할까?

모든 연산은 메타데이터와 배열이 서로 맞는다고 가정한다. 필요한 조건은 다음과
같다.

```text
0 <= size <= capacity
```

```text
data는 capacity개의 정수 자리를 가리킨다.
capacity가 0이면 data는 NULL이다.
```

```text
data[0]부터 data[size - 1]까지가 사용 중인 항목이다.
```

모든 연산을 시작하기 전과 끝낸 후에 참이어야 하는 조건을 불변식(invariant)이라고
한다. 연산 도중에는 상태가 잠시 달라질 수 있다. 함수는 반환하기 전에 불변식을
다시 만족시켜야 한다.

### 간단한 리스트는 어떻게 커질까?

추가 함수는 먼저 `size`와 `capacity`가 같은지 검사한다. 두 값이 같으면 빈자리가
없다.

간단한 리스트는 처음에 자리 네 개를 확보한다. 다음부터는 전체 자리 수를 두 배로
늘린다.

```text
0 -> 4 -> 8 -> 16 -> 32
```

`realloc`은 기존 메모리 블록의 크기를 바꿔 달라고 요청한다. 같은 블록을 늘릴 수도
있다. 데이터를 다른 블록으로 옮길 수도 있다. 결과 블록의 주소를 반환한다.

요청 성공을 확인하기 전에 기존 주소를 버리면 안 된다.

```c
new_data = realloc(list->data, new_capacity * sizeof(*new_data));
if (new_data == NULL) {
    return 0;
}
list->data = new_data;
list->capacity = new_capacity;
```

할당에 실패하면 `size`, `capacity`, 사용 중인 항목은 바뀌지 않는다.

### CPython은 왜 빈자리를 남겨 둘까?

항목을 추가할 때마다 배열을 키우면 기존 항목을 계속 옮겨야 한다. CPython은 다음
추가 한 번에 필요한 크기보다 더 많은 자리를 요청한다. 남겨 둔 자리는 이후 추가에
사용한다.

교육용 구현은 CPython 3.12의 크기 계산을 유지한다.

```c
new_allocated = (newsize + (newsize >> 3U) + 6U) & ~(size_t)3U;
```

이 식은 요청한 크기의 약 8분의 1을 더하고 4의 배수로 맞춘다. 비트 연산식을
외울 필요는 없다. 당장 필요한 크기보다 조금 더 확보한다는 결정이 중요하다.

CPython은 간단한 구현의 `capacity`에 해당하는 필드를 `allocated`라고 부른다.

```c
struct PyListObject {
    struct PyObject **ob_item;
    size_t size;
    size_t allocated;
};
```

`struct PyObject **ob_item`은 포인터 배열을 가리키는 포인터다. Python 리스트는 Python
객체 자체를 배열 안에 넣지 않는다. 각 객체를 가리키는 포인터를 저장한다.

```text
PyListObject                     Python 객체

ob_item ----> +--------+       +------+
              | 포인터 | ----> | "10" |
              +--------+       +------+
              | 포인터 | ----> | "15" |
              +--------+       +------+
              | 포인터 | ----> | "30" |
              +--------+       +------+
```

리스트는 사용 중인 각 객체에 대한 참조를 소유한다. 교육용 구현은 참조를 새로
저장할 때 `Py_INCREF`를 호출한다. 참조를 놓을 때 `Py_DECREF`를 호출한다. 두
함수는 CPython의 참조 횟수 소유 규칙을 간단하게 나타낸다.

### 삽입할 때 순서를 어떻게 지킬까?

`10`, `20`, `30`이 들어 있다. 인덱스 1에 `15`를 삽입한다.

인덱스 1과 2의 항목을 오른쪽으로 옮겨야 한다. 오른쪽 항목부터 움직인다. `20`을
먼저 옮기면 `30`을 덮어쓰기 때문이다.

```text
이전:    [10, 20, 30, ?]
30 이동: [10, 20, 30, 30]
20 이동: [10, 20, 20, 30]
삽입:    [10, 15, 20, 30]
```

사용 중인 구간에는 빈틈이 없다. `size`는 3에서 4가 된다.

### 삭제할 때 순서를 어떻게 지킬까?

`[10, 15, 20, 30]`의 인덱스 2를 삭제한다.

뒤에 있는 항목을 왼쪽으로 옮긴다. 삭제한 자리 바로 다음부터 움직인다.

```text
이전:       [10, 15, 20, 30]
30 이동:    [10, 15, 30, 30]
size 감소:  [10, 15, 30, ?]
```

미사용 자리에 남은 값은 리스트에 속하지 않는다. `size`가 사용 중인 범위를
결정한다.

### 리스트의 일부를 어떻게 얻을까?

`[10, 15, 30]`에서 인덱스 1과 2를 얻으려 한다. 범위는 `[1, 3)`으로 나타낸다.
왼쪽 경계는 포함한다. 오른쪽 경계는 포함하지 않는다.

```text
원본:          [10, 15, 30]
인덱스:           0   1   2

범위 [1, 3):         15, 30
결과:              [15, 30]
```

결과는 부분 리스트(sublist)다. Python에서는 같은 연산을 슬라이스로 표현한다.

```python
result = source[1:3]
```

결과 리스트에는 별도의 배열이 필요하다. 결과의 위치를 바꾸어도 원본 리스트의
위치가 바뀌면 안 된다.

간단한 리스트는 정숫값을 새 배열에 복사한다. CPython 교육용 리스트는 객체
포인터를 복사하고 참조 횟수를 늘린다. 두 리스트는 같은 Python 객체를 가리킬 수
있다. 그러나 포인터 배열은 각 리스트가 따로 소유한다.

## 효율 계산해 보기

### 인덱스로 읽을 때 몇 번 일할까?

프로그램은 위치 하나를 계산하고 배열 항목 하나를 읽는다. 리스트가 커져도 읽기
단계는 늘어나지 않는다. 인덱스 읽기의 시간 복잡도는 `O(1)`이다.

### 삽입할 때 몇 번 일할까?

항목 세 개 중 인덱스 1에 삽입하면 두 항목을 옮긴다. 인덱스 0에 삽입하면 세
항목을 모두 옮긴다. 끝에 삽입하면 옮기는 항목이 없다.

항목이 `n`개일 때 가장 큰 이동은 `n`개를 옮긴다. 삽입의 시간 복잡도는
`O(n)`이다.

### 삭제할 때 몇 번 일할까?

항목 네 개 중 인덱스 2를 삭제하면 한 항목을 옮긴다. 인덱스 0을 삭제하면 세
항목을 옮긴다.

항목이 `n`개일 때 가장 큰 이동은 `n - 1`개를 옮긴다. Big O는 고정된 차이 1을
제외한다. 삭제의 시간 복잡도는 `O(n)`이다.

### 끝에 추가하는 일은 항상 한 단계일까?

빈자리가 있으면 배열 쓰기 한 번으로 끝난다. 이 추가는 `O(1)`이다.

빈자리가 없으면 할당을 키워야 한다. 기존 항목 포인터 `n`개를 옮기는 작업은
`n`에 비례한다. 그 추가 한 번은 `O(n)`이다.

한 번 크기를 늘리면 이후 여러 번의 추가에 쓸 빈자리가 생긴다. 비싼 확장 비용을
긴 추가 연산 묶음 전체에 나누면 추가 한 번당 평균 작업량은 일정하게 유지된다.
연산 묶음 전체의 비용을 나누어 분석하는 방법을 분할 상환 분석(amortized
analysis)이라고 한다. 추가의 분할 상환 시간은 `O(1)`이다.

모든 추가가 같은 시간이 걸린다는 뜻은 아니다. 긴 연산 묶음에서 추가 한 번이
부담하는 비용을 뜻한다.

### 부분 리스트를 만들 때 몇 번 일할까?

범위 `[1, 3)`에는 항목이 두 개 있다. 프로그램은 자리 두 개를 할당하고 항목 두
개를 복사한다.

선택한 범위의 항목 수가 `k`개라면 반복문은 `k`번 복사한다. 부분 리스트 생성의
시간 복잡도는 `O(k)`다. 결과를 저장하는 추가 공간도 `O(k)`다.

원본 항목 수 `n`과 선택한 항목 수 `k`는 다를 수 있다. 범위 밖의 항목은 확인하지
않으므로 `O(k)`가 작업량을 더 정확히 나타낸다.

### 연산별 비용

| 연산 | 시간 | 추가 공간 | 원인 |
| --- | ---: | ---: | --- |
| 인덱스 읽기 | `O(1)` | `O(1)` | 위치 하나 계산 |
| 확장 없는 끝 추가 | `O(1)` | `O(1)` | 항목 하나 쓰기 |
| 확장이 발생한 추가 한 번 | `O(n)` | 구현에 따라 다름 | 기존 항목 이동 |
| 긴 연산 묶음에서의 추가 | 분할 상환 `O(1)` | 여유 용량 | 한 번의 확장이 이후 추가를 준비 |
| 삽입 | `O(n)` | `O(1)` | 뒤 구간을 오른쪽으로 이동 |
| 삭제 | `O(n)` | `O(1)` | 뒤 구간을 왼쪽으로 이동 |
| 길이 `k`의 부분 리스트 | `O(k)` | `O(k)` | `k`개 항목 할당과 복사 |

## 용어 정리

### 동적 배열 리스트(Dynamic array list)

실행 중에 기존 저장 공간을 더 큰 할당으로 바꿀 수 있는 배열 기반 리스트다.

### 불변식(Invariant)

모든 연산을 시작하기 전과 끝낸 후에 참이어야 하는 조건이다. 배열 리스트의 핵심
불변식은 `0 <= size <= capacity`다.

### 할당(Allocation)

프로그램 실행 중에 얻은 메모리 블록이다.

### 포인터(Pointer)

메모리 주소를 저장하는 값이다.

### 구조체(Structure)

`struct`로 선언하며 관련된 필드를 하나로 묶는 C 값이다.

### 참조 횟수(Reference count)

교육용 모델에서 Python 객체를 소유한 참조의 수다. 리스트 참조를 만들면 늘리고,
리스트 참조를 놓으면 줄인다.

### 반열린 범위(Half-open range)

왼쪽 경계를 포함하고 오른쪽 경계를 포함하지 않는 범위다. `[1, 3)`에는 인덱스
1과 2가 들어간다.

### 부분 리스트(Sublist)

다른 리스트의 일정 범위에서 선택한 항목으로 만든 새 리스트다.

### 분할 상환 비용(Amortized cost)

가끔 발생하는 비싼 작업을 긴 연산 묶음 전체에 나누었을 때 연산 하나가 부담하는
비용이다.

## 코딩 계획

### 빈 리스트 초기화

- 배열 포인터를 `NULL`로 정한다.
- `size`를 0으로 정한다.
- `capacity` 또는 `allocated`를 0으로 정한다.
- 불변식을 확인한다.

### 할당 확장

- 확장이 필요한지 확인한다.
- 더 큰 용량을 계산한다.
- 바이트 수 계산에서 넘침이 발생하지 않는지 확인한다.
- `realloc`으로 새 크기를 요청한다.
- 요청에 실패하면 이전 상태를 유지한다.
- 성공하면 새 포인터와 용량을 저장한다.

### 항목 추가

- `size`와 용량을 비교한다.
- 빈자리가 없으면 확장한다.
- 인덱스 `size`에 항목을 저장한다.
- `size`를 늘린다.

### 항목 삽입

- 인덱스가 0부터 `size`까지인지 확인한다.
- 빈자리가 없으면 확장한다.
- 뒤에서 시작하여 뒤 구간을 오른쪽으로 옮긴다.
- 새 항목을 저장한다.
- `size`를 늘린다.

### 항목 삭제

- 인덱스가 `size`보다 작은지 확인한다.
- 필요하면 삭제할 객체 참조를 저장하거나 놓는다.
- 뒤 구간을 왼쪽으로 옮긴다.
- `size`를 줄인다.

### 부분 리스트 생성

- `low`와 `high`를 원본 크기 안으로 줄인다.
- `high`가 `low`보다 작으면 빈 범위로 만든다.
- `high - low`로 `count`를 계산한다.
- 결과에 `count`개의 자리를 정확히 할당한다.
- 선택한 항목을 순서대로 복사한다.
- 결과의 크기와 용량을 `count`로 정한다.

### 리스트 해제

- 필요한 경우 소유한 객체 참조를 모두 놓는다.
- `free`로 배열 할당을 해제한다.
- 빈 리스트 상태로 되돌린다.

## C 코드

### 간단한 리스트의 표현

```c
struct ArrayList {
    int *data;
    size_t size;
    size_t capacity;
};
```

불변식 검사 함수는 세 필드의 관계를 나타낸다.

```c
static int array_list_invariant(const struct ArrayList *list)
{
    return list != NULL && list->size <= list->capacity &&
        ((list->capacity == 0U) == (list->data == NULL));
}
```

### 간단한 리스트 확장

```c
static int array_list_grow(struct ArrayList *list)
{
    size_t new_capacity;
    int *new_data;

    assert(array_list_invariant(list));
    new_capacity = list->capacity == 0U ? 4U : list->capacity * 2U;
    if (new_capacity < list->capacity ||
        new_capacity > SIZE_MAX / sizeof(*new_data)) {
        return 0;
    }

    new_data = realloc(list->data, new_capacity * sizeof(*new_data));
    if (new_data == NULL) {
        return 0;
    }
    list->data = new_data;
    list->capacity = new_capacity;
    assert(array_list_invariant(list));
    return 1;
}
```

첫 조건은 두 배 계산에서 정수 넘침을 찾는다. 다음 조건은 필요한 바이트 수를
표현할 수 있는지 확인한다.

### 간단한 리스트에 추가

```c
static int array_list_append(struct ArrayList *list, int value)
{
    assert(array_list_invariant(list));
    if (list->size == list->capacity && !array_list_grow(list)) {
        return 0;
    }
    list->data[list->size] = value;
    list->size += 1U;
    return 1;
}
```

쓰기에는 이전 `size`를 첫 미사용 인덱스로 사용한다. `size`를 늘리면 저장한 값이
사용 중인 항목이 된다.

### 간단한 리스트에 삽입

```c
for (size_t i = list->size; i > index; i -= 1U) {
    list->data[i] = list->data[i - 1U];
}
list->data[index] = value;
list->size += 1U;
```

반복문은 오른쪽에서 왼쪽으로 움직인다. 원본을 덮어쓰기 전에 각 원본 값을 읽는다.

### 간단한 리스트에서 삭제

```c
for (size_t i = index; i + 1U < list->size; i += 1U) {
    list->data[i] = list->data[i + 1U];
}
list->size -= 1U;
```

반복문은 왼쪽에서 오른쪽으로 움직인다. 뒤의 각 항목이 빈자리를 한 칸씩 닫는다.

### 간단한 부분 리스트 생성

```c
count = high - low;
result->data = malloc(count * sizeof(*result->data));
if (result->data == NULL) {
    return 0;
}
result->size = count;
result->capacity = count;

for (size_t source = low, destination = 0U;
     source < high;
     source += 1U, destination += 1U) {
    result->data[destination] = list->data[source];
}
```

`source`는 선택한 범위를 지난다. `destination`은 새 리스트의 인덱스 0에서
시작한다.

### CPython 교육용 리스트의 표현

```c
struct PyListObject {
    struct PyObject **ob_item;
    size_t size;
    size_t allocated;
};
```

배열은 정수 대신 `struct PyObject *` 포인터를 저장한다. 크기와 용량을 구분하는 원리는
같다.

### CPython 방식으로 크기 변경

```c
if (self->allocated >= newsize &&
    newsize >= (self->allocated >> 1U)) {
    self->size = newsize;
    return 0;
}

new_allocated =
    (newsize + (newsize >> 3U) + 6U) & ~(size_t)3U;
```

첫 조건을 만족하면 현재 할당을 그대로 쓴다. 사용량이 할당된 크기의 절반보다
작아진 뒤에야 더 작은 할당을 요청한다.

### CPython 방식의 부분 리스트 생성

```c
result->ob_item = malloc(count * sizeof(*result->ob_item));
if (result->ob_item == NULL) {
    return -1;
}
result->size = count;
result->allocated = count;

for (size_t source = low, destination = 0U;
     source < high;
     source += 1U, destination += 1U) {
    struct PyObject *item = self->ob_item[source];
    Py_INCREF(item);
    result->ob_item[destination] = item;
}
```

반복문은 객체가 아니라 포인터를 복사한다. `Py_INCREF`는 결과 리스트가 선택된
각 객체의 참조를 하나 더 소유한다고 기록한다.

### 전체 실행 과정 확인

CPython 교육용 독립 실행 프로그램은 다음 연산을 수행한다.

```text
10 추가             [10]
20 추가             [10, 20]
30 추가             [10, 20, 30]
인덱스 1에 15 삽입  [10, 15, 20, 30]
인덱스 2 삭제       [10, 15, 30]
부분 리스트 [1, 3)  [15, 30]
```

`module_01_arraylist/student` 디렉터리에서 간단한 구현을 목적 파일로
컴파일한다. 이 파일은 보조 함수를 제공하며 `main()`이 없으므로 단독으로
실행할 수 없다.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic \
  -c ../code/lecture/simplified_array_list.c \
  -o simplified_array_list.o
```

그다음 CPython 교육용 프로그램을 컴파일하고 실행한다.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic \
  ../code/lecture/cpython_list_standalone.c \
  -o cpython_list_standalone
./cpython_list_standalone
```

두 파일을 다음 순서로 비교한다.

1. 표현을 이루는 세 필드를 찾는다.
2. 불변식 검사 함수를 찾는다.
3. 확장이 필요한 조건을 찾는다.
4. 삽입에서 오른쪽으로 옮기는 반복문을 찾는다.
5. 삭제에서 왼쪽으로 옮기는 코드를 찾는다.
6. 부분 리스트를 복사하는 반복문을 찾는다.
7. 각 반복문의 작업량을 방문한 항목 수로 설명한다.

이름과 객체 소유 규칙은 다르다. 배열 리스트가 내리는 핵심 결정은 같다.
