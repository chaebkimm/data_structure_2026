# 자료구조 - 요약

15주차 – 왼쪽으로 기울어진 레드 블랙 트리 코드

## 목차

- 복습 - 왼쪽으로 기울어진 레드 블랙 트리
- 레드 블랙 트리 노드 만들기
- 노드 색깔이 빨간색인지 확인하기
- 데이터를 추가하는 방법
- 데이터 추가할 자리 찾기
- 왼쪽으로 돌리기
- 오른쪽으로 돌리기
- 색깔 바꾸기
- 데이터 추가하기

## 복습 - 왼쪽으로 기울어진 레드 블랙 트리

- 레드 블랙 트리의 규칙은 루트는 검은색이고, 다른 노드들 중 빨간색은 부모와 한 묶음으로 취급한다는 것이다. 
- 빨간 자식은 연달아 올 수 없게 하여 묶음에 들어 있는 노드 숫자를 제한한다.
- 묶음 기준으로 모든 리프가 같은 층이 있다.
- 왼쪽으로 기울어진 레드 블랙 트리의 규칙은 빨간 자식이 왼쪽에만 있다는 것이다. 

## 레드 블랙 트리 노드 만들기

- 노드에는 데이터와 왼쪽 자식과 오른쪽 자식을 저장한다. 
- 자식이 없으면 `-1`을 저장한다. 
- 노드가 빨간색인지 여부를 저장한다.
- 노드들은 배열 리스트에 저장한다. 
- 새로운 노드를 만들면 배열 리스트에 추가하고 인덱스를 반환한다.
- 새로운 노드는 부모에 붙일 것이므로 빨간색으로 만든다.


## 트리 노드를 만드는 C 코드

```c
enum { CAP = 12 };

struct Rbtree_Node {
    int data;
    int left;
    int right;
    int is_red;
};

struct Rbtree_Node nodes[CAP];
int nodes_size = 0;

int new_node(int d) {
    if (nodes_size == CAP) { return -1; }
    int i = nodes_size++;
    nodes[i].data = d;
    nodes[i].is_red = 1;
    nodes[i].left = -1;
    nodes[i].right = -1;
    return i;
}
```

## 노드의 색깔이 빨간색인지 확인하기

- 빨간색은 부모 노드에 붙어 있음을 의미한다.
- 노드가 없으면 거짓임을 반환한다.
- 노드가 있으면 색깔이 빨간색인지를 반환한다.

## 노드의 색깔이 빨간색인지 확인하는 C 코드

```c
int check_red(int i) {
    return i != -1 && nodes[i].is_red;
}
```

## 데이터 추가하는 방법

- 트리가 비어 있으면 노드를 만들어서 반환한다.
- 트리에 데이터가 있으면 데이터를 추가하지 않는다. 
- 데이터가 없으면 노드를 만들어서 이진 탐색 트리를 따라 적절한 자리에 저장한다. 
- 후손부터 조상 방향으로 트리를 고친다.
- 빨간 자식이 오른쪽에만 있으면 왼쪽으로 돌린다.
- 빨간 자식이 왼쪽에 있고 빨간 자식의 왼쪽에 빨간 자식이 또 있으면 오른쪽으로 돌린다.
- 왼쪽과 오른쪽이 모두 빨간 자식이면 자식은 검은색으로 색깔을 바꾸고, 노드를 빨간색으로 만든다.
- 트리의 루트를 반환한다.

## 데이터를 저장하는 C 코드

```c
int add_at(int i, int val) {
    if (i == -1) { 
        return new_node(val); 
    }
```

아래 네 코드가 `add_at`의 나머지다. 

## 데이터 추가할 자리 찾기

- 추가할 데이터를 현재 노드와 비교한다.
- 추가할 데이터가 현재 노드와 같으면 추가를 하지 않고 종료한다.
- 추가할 데이터가 현재 노드보다 작으면 왼쪽 자식 트리에서 추가한다.
- 추가할 데이터가 현재 노드보다 크면 오른쪽 자식 트리에서 추가한다.

## 데이터 추가할 자리를 찾는 C 코드

```c
    int l = nodes[i].left;
    int r = nodes[i].right;

    if (val == nodes[i].data) { 
        return i; 
    } else if (val < nodes[i].data) {
        nodes[i].left = add_at(l, val);
        l = nodes[i].left;
    } else {
        nodes[i].right = add_at(r, val);
        r = nodes[i].right;
    }
```

## 왼쪽으로 돌리기

- 노드의 오른쪽에만 빨간 자식이 있는 경우 규칙을 지키기 위해서 노드와 오른쪽 자식을 왼쪽으로 돌린다.
- 노드와 기존 오른쪽 자식의 색깔을 서로 맞바꾸고, 노드를 기존 오른쪽 자식의 왼쪽 자식으로 삼는다.
- 기존 오른쪽 자식의 원래 왼쪽 자식은 노드의 오른쪽 자식으로 삼는다. 

## 왼쪽으로 돌리는 C 코드

```c
    if (check_red(r) && !check_red(l)) {
        int rl = nodes[r].left;
        nodes[r].left = i;
        nodes[i].right = rl;
        nodes[r].is_red = nodes[i].is_red;
        nodes[i].is_red = 1;

        /* int ll = l; */
        l = i;
        i = r;
        r = nodes[i].right;
    }
```

## 오른쪽으로 돌리기

- 노드의 왼쪽에 빨간 자식이 있고, 빨간 자식의 왼쪽에 또 빨간 손자가 있을 때, 오른쪽으로 돌려서 색깔을 바꿀 준비를 한다.
- 노드와 왼쪽 자식의 색깔을 서로 맞바꾸고, 노드를 기존 왼쪽 자식의 오른쪽 자식으로 삼는다. 
- 기존 왼쪽 자식의 원래 오른쪽 자식은 노드의 왼쪽 자식으로 삼는다. 

## 오른쪽으로 돌리는 C 코드

```c
    if (check_red(l)) {
        int ll = nodes[l].left;
        if (check_red(ll)) {
            int lr = nodes[l].right;
            nodes[l].right = i;
            nodes[l].is_red 
                = nodes[i].is_red;
            nodes[i].left = lr;
            nodes[i].is_red = 1;

            /* int rr = r; */
            r = i;
            i = l;
            l = ll;
            /* ll = nodes[i].left; */
        }
    }
```

## 색깔 바꾸기

- 노드의 자식들이 모두 빨간색일 경우, 자식들의 색깔을 검은색으로 바꾸고, 노드의 색깔은 빨간색으로 바꾼다.
- 결과적으로 붙어 있던 세 노드가 분리되고, 가운데 노드는 부모에 붙게 된다. 
- 돌리기와 색깔 바꾸기를 통해 트리를 수리했으면, 현재 트리의 루트를 반환한다.

## 색깔을 바꾸는 C 코드

```c
    if (check_red(l) && check_red(r)) {
        nodes[l].is_red = 0;
        nodes[r].is_red = 0;
        nodes[i].is_red = 1;
    }

    return i;
}
```

## 데이터 추가하기

- 트리의 루트와 추가할 데이터를 입력받는다.
- 앞에서 만든 함수로 트리에 데이터를 저장한다.
- 루트에는 부모가 없어서 위에 붙일 수 없으므로 색깔을 검은색으로 만든다.

## 데이터 추가하는 C 코드

```c
int add(int root, int val) {
    root = add_at(root, val);
    if (root != -1) { 
        nodes[root].is_red = 0; 
    }
    return root;
}
```