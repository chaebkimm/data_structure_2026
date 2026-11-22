# 자료구조 - 요약

13주차 – 힙 코드

## 목차

- 힙으로 우선순위 큐 구현하기
- 데이터 올리고 내리기, 자식 찾기
- 데이터 추가, 데이터 꺼내기
- 힙 만들기
- 힙으로 정렬하기, 예제

## 힙으로 우선순위 큐 구현하기

- 배열의 인덱스 `0`에 트리의 루트를 저장하고, 그다음은 한 층씩 왼쪽부터 `1`, `2`, ... 인덱스에 저장한다. 
- 부모가 항상 자식보다 우선순위가 높거나 같고, 루트의 우선순위가 가장 높다.
- `0`부터 `size - 1`까지 모두 데이터가 있다.
- 비교 함수는 무엇이 우선순위가 높은지 확인한다.
- 값이 작을수록 우선순위가 높으면 최소 힙이 되고 반대는 최대 힙이 된다.

## 우선순위 큐 C 코드

```c
enum { CAPACITY = 5 };
int pq[CAPACITY];
int size;

void init_pqueue(void) { size = 0; }
int comp(int x, int y) { return x < y; }
```

## 데이터 올리기

- 부모가 있고 데이터보다 우선순위가 낮으면, 부모를 한 층 내리고 이를 반복한다.
- 데이터를 저장할 비어 있는 자리를 반환한다.
- 인덱스 `i`의 부모는 `(i - 1) / 2`로 구한다.

## 데이터 올리기 C 코드

```c
int parent(int i) { return (i - 1) / 2; }

int sift_up(int i, int data) {
  int p = parent(i);
  while (i > 0 && comp(data, pq[p])) {
    pq[i] = pq[p];
    i = p;
    p = parent(i);
  }
  return i;
}
```

## 데이터 내리기

- 자식이 있고 데이터보다 우선순위가 더 높으면, 우선순위가 높은 자식을 한 층 올리고, 이를 반복한다. 
- 데이터를 저장할 비어 있는 자리를 반환한다.
- 자식은 `priority_child` 함수로 선택한다.

## 데이터 내리기 C 코드

```c
int priority_child(int i);

int sift_down(int i, int data) {
  int c = priority_child(i);
  while (c < size && comp(pq[c], data)) {
    pq[i] = pq[c];
    i = c;
    c = priority_child(i);
  }
  return i;
}
```

## 우선순위가 높은 자식 찾기

- 인덱스 `i`의 왼쪽 자식은 `i * 2 + 1`이고, 오른쪽 자식은 `i * 2 + 2`다. 
- 오른쪽 자식이 존재하면 왼쪽 자식과 비교해 우선순위가 높은 쪽을 반환한다.
- 그 외에는 왼쪽 자식을 반환하며, 자식이 없으면 반환값이 `size` 이상이다.

## 우선순위가 높은 자식 찾기 C 코드

```c
int left(int i) { return i * 2 + 1; }
int right(int i) { return i * 2 + 2; }

int priority_child(int i) {
  int l = left(i);
  int r = right(i);
  int child;
  if (r < size && comp(pq[r], pq[l])) {
    child = r;
  } else {
    child = l;
  }
  return child;
}
```

## 힙에 데이터 추가하기

- 마지막 리프 다음 자리에서 출발해서 데이터를 올릴 자리를 만들며 찾는다.
- 찾은 자리에 데이터를 저장하고 `size`를 늘린다.
- 가정: 배열에 추가할 용량이 남아있을 때만 데이터를 추가한다.

## 힙에 데이터 추가하기 C 코드

```c
void enqueue(int data) {
  int pos = sift_up(size, data);
  pq[pos] = data;
  size++;
}
```

## 힙에서 데이터 꺼내기

- 루트를 따로 복사해둔다.
- `size`를 줄여서 마지막 데이터를 빼고, 루트에서 출발해 내릴 자리를 만들며 찾는다.
- 찾은 자리에 다시 저장한다.
- 복사해둔 루트를 반환한다.
- 가정: 데이터가 있을 때만 꺼낸다.

## 힙에서 데이터 꺼내기 C 코드

```c
int dequeue(void) {
  int root = pq[0];
  int data = pq[--size];
  int pos = sift_down(0, data);
  pq[pos] = data;
  return root;
}
```

## 배열에 있는 데이터들로 힙 만들기

- 처음에는 각 리프가 별개의 힙이다.
- 자식이 있는 마지막 데이터부터 앞으로 이동하며 데이터를 내린다. 마지막 데이터의 부모로 구한다.
- 내리기 전에 양쪽 자식 트리는 힙이다. 데이터를 내리면 힙 하나로 합쳐진다.

## 힙 만들기 C 코드

```c
void heapify(void) {
  for (int i = parent(size - 1); i >= 0; i--) {
    int data = pq[i];
    int pos = sift_down(i, data);
    pq[pos] = data;
  }
}
```

## 힙으로 정렬하기

- 힙에서 하나씩 데이터를 꺼내서 다른 배열에 앞에서부터 저장하면 우선순위 순서로 데이터가 저장된다.
- 힙에서 데이터가 나가면 `size`가 변한다는 것을 주의한다.
- 가정: 힙이 만들어져 있다.

## 힙으로 정렬하기 C 코드

```c
void heap_sort(int sorted[]) {
  int n = size;
  for (int i = 0; i < n; i++) {
    sorted[i] = dequeue();
  }
}
```

## 힙 예제

- `pq` 배열에 `9`, `6`, `5`를 저장하고, `size`는 `3`으로 두고, 힙으로 만든다. 
- 힙에 `3`, `1`을 추가한다. 
- 힙으로 정렬한 결과를 `sorted` 배열에 저장한다.

## 힙 예제 C 코드

```c
int main(void) {
  pq[0] = 9;
  pq[1] = 6;
  pq[2] = 5;
  size = 3;
  heapify();

  enqueue(3); 
  enqueue(1); 

  int sorted[CAPACITY];
  heap_sort(sorted); 
  return 0;
}
```
