# 자료구조 - 요약

11주차 – 해시테이블 코드

## 목차

1. 키와 데이터를 갖는 노드
2. 해시함수와 해시테이블
3. 해시테이블에 데이터를 저장하고 찾기
4. 배열에서 합이 목표치인 두 숫자 찾기
5. 해시테이블로 두 숫자 찾기

## 키와 데이터를 갖는 노드

- 해시테이블에서는 해시값을 계산할 키가 데이터와 더불어 필요하다.
- 해시값이 같은 데이터들을 리스트에 모아 놓는다. 개수를 알기 어려우므로 링크드 리스트가 적절하다.
- 전체 노드들은 배열 리스트로 관리한다.

## 키와 데이터를 갖는 노드 C 코드

```c
struct hnode {
  int key;
  int data;
  int next;
};
struct hnode hnodes[5];
int size = 0;
```

## 키와 데이터를 갖는 노드 만들기

- 노드가 필요할 때는 배열 리스트의 제일 끝에 추가해서 쓴다.

## 노드를 만드는 C 코드

```c
int new_hnode(int _key, int _data, int _next) {
  if (size >= 5) { return -1; }
  int i = size++;
  hnodes[i].key = _key;
  hnodes[i].data = _data;
  hnodes[i].next = _next;
```

## 노드를 만드는 C 코드

```c
  return i;
}
```

## 해시테이블을 위한 해시함수

- 해시값을 인덱스로 쓴다. 해시함수의 결괏값은 0부터 해시테이블 용량 - 1까지의 범위 안에서 나오게 한다.
- 나머지 연산이 흔히 쓰이는데, 음수를 나눈 나머지는 음수가 될 수 있음을 주의한다.

## 인덱스 반환 해시함수 C 코드

```c
int hash_func(int key) {
  int hash = key % 7;
  if (hash < 0) { hash += 7; }
  return hash;
}
```

## 해시값이 같은 리스트들의 배열

- 해시값이 같은 노드들을 하나의 링크드 리스트로 관리한다.
- 배열에 해시값이 같은 링크드 리스트들 각각의 처음 노드 인덱스를 저장한다.
- 인덱스는 해시값을 그대로 쓴다.

## 해시테이블 C 코드

```c
int htable[7];
void initialize(void) {
  size = 0;
  for (int i = 0; i < 7; i++) {
    htable[i] = -1;
  }
}
```

## 해시테이블에 데이터 저장하기

- 데이터가 저장된 노드를 만든다.
- 노드를 해시값이 같은 리스트의 제일 앞에 추가한다.
- 해시테이블에서 시작 노드 인덱스를 바꿔 준다.

## 해시테이블에 저장하는 C 코드

```c
int insert(int k, int d) {
  int hash = hash_func(k);
  int old_head = htable[hash];
  int node
    = new_hnode(k, d, old_head);
```

## 해시테이블에 저장하는 C 코드

```c
  if (node == -1) {
    return -1;
  }
  htable[hash] = node;
  return 0;
}
```

## 해시테이블에서 데이터 찾기

- 키의 해시값을 가지고 해시테이블에서 리스트의 시작 노드를 가져온다.
- 리스트의 모든 노드에서 반복하며 키를 가지고 있는 노드를 찾는다.

## 해시테이블에서 찾는 C 코드

```c
int find(int k) {
  int hash = hash_func(k);
  int node = htable[hash];
  while (node != -1) {
    if (hnodes[node].key == k) {
      return node;
    }
```

## 해시테이블에서 찾는 C 코드

```c
    node = hnodes[node].next;
  }
  return -1;
}
```

## 합이 목표치인 두 숫자 찾기

- brute force 솔루션: 모든 숫자 쌍에 대해서 반복하며 더해 본다.
- hash table 솔루션: 모든 숫자에 대해서 보수가 해시테이블에 있는지 확인한다. 없으면 숫자를 해시테이블에 추가한다.

## 합이 t인 두 숫자를 찾는 C 코드

```c
int arr[5] = {1, 2, 4, 8, 16};
int ans[2] = {-1, -1};
void two_sum_bf(int t) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < i; j++){
      if (arr[i] + arr[j] == t){
        ans[0] = j;
```

## 합이 t인 두 숫자를 찾는 C 코드

```c
        ans[1] = i;
        return;
      }
    }
  }
  ans[0] = ans[1] = -1;
}
```

## 합이 t인 두 숫자 찾기

- 모든 숫자 n에 대해 반복하며 t - n이 해시테이블에 있는지 확인한다.
- 없으면 n을 해시테이블에 추가한다.
- 먼저 찾아본 다음에 저장하기 때문에 앞에 나온 숫자와만 짝을 이룬다.

## 합이 t인 두 숫자 찾기

- 노드에서 숫자를 key에, 숫자의 배열에서의 인덱스를 data에 저장한다.
- 숫자가 해시테이블에 저장되어 있는지 확인할 수 있고, 저장되어 있으면 배열에서의 인덱스를 알 수 있다.

## 합이 t인 두 숫자를 찾는 C 코드

```c
void two_sum_ht(int t) {
  initialize();
  for (int i = 0; i < 5; i++) {
    int complement = t - arr[i];
    int node = find(complement);
    if (node != -1) {
      ans[0] = hnodes[node].data;
```

## 합이 t인 두 숫자를 찾는 C 코드

```c
      ans[1] = i;
      return;
    }
    insert(arr[i], i);
  }
  ans[0] = ans[1] = -1;
}
```
