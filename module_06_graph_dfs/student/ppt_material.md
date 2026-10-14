# 오늘의 목차

# 복습 - 간선의 구성 요소

# 복습 - 노드의 이웃 리스트

# 복습 - 그래프에서 반복하는 방법

# 복습 - DFS 트리 간선과 빽간선

# 복습 - 트리 방문 번호와 빽번호

# 이웃 간선의 종류는?

# 다음 그래프에서 간선의 종류는?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 이웃 노드의 종류는?

# 2번 노드 이웃의 종류는?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 트리 간선 자식 노드의 특징은?

# 빽 간선 후손 노드의 특징은?

# 빽 간선 조상 노드의 특징은?

# 트리 간선 부모 노드의 특징은?

# 이웃 노드를 구별하는 방법은?

# 2번 노드 이웃을 구별하면?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 그래프 탐색의 작업 타이밍은?

# preorder에서 항상 하는 일은?

# 트리 간선 자식에 항상 하는 일은?

# 2번 노드에서 진행되는 작업은?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("#160;"))
    n3(("#160;"))
    n4(("#160;"))
    n5(("#160;"))
    n6(("#160;"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#bfbfbf,stroke-width:2px
    linkStyle 0,2 stroke:#156082,stroke-width:2px
```

# 간선을 저장하는 세가지 방법은?

# 간선 리스트를 만들면 좋은점은?

# 이웃 행렬을 만들면 좋은 점은?

# 리스트, 행렬에 간선을 추가하려면?

# 간선 추가 작업을 할 대상 이웃은?

# 그래프의 간선 리스트를 만들면?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 복습 - 빽번호란?

# 복습 - 5번 노드의 빽번호는 ?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 복습 - 끈끈한 그래프란?

# 복습 - 여기서 끈끈한 그래프는?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 복습 - 빽번호로 끈끈한 간선 찾기

# 복습 - 끈끈한 간선을 찾으면?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 끈끈한 간선 찾을 때 스택의 용도?

# 끈끈한 간선 찾을 때 스택의 변화?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 트리 간선 자식에서 할 일은?

# 빽 간선 조상에서 할 일은?

# postorder에서 할 일은?

# 끈끈한 간선을 찾는 과정?

```mermaid
flowchart TB
    n0(("0"))
    n1(("1"))
    n2(("2"))
    n3(("3"))
    n4(("4"))
    n5(("5"))
    n6(("6"))

    n0 --- n1
    n0 --- n2
    n1 --- n2
    n1 --- n6
    n2 --- n3
    n2 --- n5
    n2 --- n6
    n3 --- n4
    n3 --- n5
    n4 --- n5

    classDef vertex fill:#ffffff,stroke:#4eaa23,stroke-width:2px,color:#000000
    class n0,n1,n2,n3,n4,n5,n6 vertex
    linkStyle default stroke:#156082,stroke-width:2px
```

# 2025 중간고사 기출문제

- 그래프에 노드나 간선을 저장하고, 추가하고, 삭제하는 방법 설명하기

- 끈끈한 그래프의 정의와 찾는 방법 설명하기

# 2025 중간고사 기출문제

- 그래프에 노드나 간선을 저장하고, 추가하고, 삭제하는 방법 설명하기

- 끈끈한 그래프의 정의와 찾는 방법 설명하기

- preorder, inorder로 트리 복원하기
