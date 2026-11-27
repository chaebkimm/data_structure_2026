# 자료구조 - 요약

14주차 – 이진 탐색 트리 코드

## 목차

- 배열에서 데이터 찾기
- 범위를 반씩 나눠가며 찾기
- 복습 - 트리 노드 만들기
- 이진 탐색 트리 만들기
- 이진 탐색 트리에서 데이터 찾기
- 이진 탐색 트리에 데이터 추가하기

## 배열에서 데이터 찾기

- 처음 데이터부터 마지막 데이터까지 확인한다. 
- 데이터를 찾으면 인덱스를 반환한다.
- 데이터를 못 찾으면 `-1`을 반환한다.

## 배열에서 데이터 찾는 C 코드

```c
enum { CAP = 12 };
int arr[CAP] = {1, 3, 5, 7, 9, 11};
int front = 0, rear = 5;

int linear_search(int target) {
    for (int i = front; i <= rear; i++) {
        if (arr[i] == target) { return i; }
    }
    return -1;
}
```

## 범위를 반씩 나눠가며 찾기

- 오름차순으로 정렬되어 있다고 가정한다.
- 범위에 데이터가 없으면 `-1`을 반환한다. 
- 가운데 있는 데이터를 찾는 데이터와 비교한다. 
- 찾는 데이터와 같으면 인덱스를 반환한다.
- 찾는 데이터가 더 작으면 범위를 작은 쪽 반으로 좁힌다.
- 찾는 데이터가 더 크면 범위를 큰 쪽 반으로 좁힌다. 

## 범위를 반씩 나눠가며 찾는 C 코드

```c
int binary_search(int target) {
    int low = front;
    int high = rear;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (target == arr[mid]) {
            return mid;
        } else if (target < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
```

## 트리 노드 만들기

- 노드에는 데이터와 왼쪽 자식과 오른쪽 자식을 저장한다. 
- 자식이 없으면 `-1`을 저장한다. 
- 노드들은 배열 리스트에 저장한다. 
- 새로운 노드를 만들면 배열 리스트에 추가하고 인덱스를 반환한다. 

## 트리 노드를 만드는 C 코드

```c
struct Tree_Node {
    int data;
    int left;
    int right;
};

struct Tree_Node nodes[CAP];
int nodes_size = 0;

int new_node(int val, int l, int r) {
    if (nodes_size == CAP) { return -1; }
    int i = nodes_size++;
    nodes[i].data = val;
    nodes[i].left = l;
    nodes[i].right = r;
    return i;
}
```

## 이진 탐색 트리 만들기

- 오름차순으로 정렬되어 있다고 가정한다.
- 범위 안에 데이터가 없으면 `-1`을 반환한다.
- 왼쪽 범위와 오른쪽 범위의 서브 트리를 만든다.
- 가운데 데이터로 노드를 만들고, 왼쪽 서브 트리의 루트를 왼쪽 자식으로, 오른쪽 서브 트리의 루트를 오른쪽 자식으로 둔다.
- 만든 노드의 인덱스를 반환한다.

## 이진 탐색 트리 만들기 C 코드

```c
int convert_bst(int low, int high) {
    if (low > high) { return -1; }
    int mid = (low + high) / 2;
    int l = convert_bst(low, mid - 1);
    int r = convert_bst(mid + 1, high);
    return new_node(arr[mid], l, r);
}
```

## 이진 탐색 트리에서 데이터 찾기

- 현재 노드의 데이터가 찾는 값이면 반환한다. 
- 찾는 값이 더 작으면 왼쪽 자식에서 반복한다. 
- 찾는 값이 더 크면 오른쪽 자식에서 반복한다.
- 해당 위치의 자식이 없으면 트리에 없다고 판정한다.

## 이진 탐색 트리에서 데이터 찾는 C 코드

```c
int bst_search(int i, int val) {
    while (i != -1) {
        if (val == nodes[i].data) { 
            return i; 
        } else if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    return -1;
}
```

## 이진 탐색 트리에 데이터 추가하기

- 트리에서 데이터를 찾는 과정에서 부모를 기록한다.
- 데이터가 이미 있으면 추가하지 않는다.
- 트리에 데이터가 없으면 부모의 해당 자식 자리가 비어있다. 자식으로 저장할 새 노드를 데이터로 만든다. 
- 새 노드가 부모보다 작으면 부모의 왼쪽 자식으로 저장한다.
- 새 노드가 부모보다 크면 부모의 오른쪽 자식으로 저장한다.

## 이진 탐색 트리에 데이터 추가하는 C 코드

```c
int bst_add(int i, int val) {
    int p = -1;
    while (i != -1) {
        if (val == nodes[i].data) {
            return i;
        }
        p = i;
        if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    int node = new_node(val, -1, -1);
    if (p != -1) {
        if (val < nodes[p].data) {
            nodes[p].left = node;
        } else {
            nodes[p].right = node;
        }
    }
    return node;
}
```
