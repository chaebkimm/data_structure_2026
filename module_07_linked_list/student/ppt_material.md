# Chapter 7 Concept Slides — Linked Lists

Use one numbered topic per slide or board scene. Ask for a prediction before revealing the state. The [textbooks](textbook.md) and [workbook](class_material.md) use the same examples. The implementation is the current `lab.c`.
각 번호를 슬라이드나 판서 한 장면으로 사용한다. 상태를 보여 주기 전에 먼저 예상하게 한다.

## 1. Can the order change without moving values? / 값을 옮기지 않고 순서를 바꾸려면?

We want to keep 17, 23, and 31 while changing which record follows which.
배열 리스트는 중간 삽입 때 뒤의 값을 민다. 다음 위치를 따로 기록하면 연결만 바꿀 수 있다.

Reveal a node as `{data, next}` after students describe the needed information.

```text
0:{17,1}  1:{23,2}  2:{31,-1}
index order: 0 → 1 → 2 → -1
value order: 17 → 23 → 31
```

Attach the name singly linked list. Emphasize that the lab's links are integer indices; its storage is still an array. `-1` is an ending marker, never an array position.

## 2. How do we find a reusable slot? / 재사용할 칸을 어떻게 찾을까?

Scanning ten slots repeats work. Connect the available indices instead.
사용 가능한 칸을 연결하고 첫 위치 하나를 기억한다. 이를 가용 리스트라고 한다.

```text
init_lnodes_pool(): free_head=0
0→1→2→3→4→5→6→7→8→9→-1
new_lnode(17, -1): returns0, free_head1, lnodes[0]={17,-1}
new_lnode(23, -1): returns1, free_head2, lnodes[1]={23,-1}
new_lnode(31, -1): returns2, free_head3, lnodes[2]={31,-1}
```

Predict exhaustion: after ten successful allocations, the next returns `-1` and changes nothing. The pool is fixed storage; no heap allocation occurs.

## 3. Which write must happen first? / 어느 대입을 먼저 할까?

Start with `0(17)→2(31)→-1`. Node1 containing23 is allocated and detached.
1번에 기존 다음 위치를 보관한 뒤 0번의 다음 위치를 바꾼다.

```text
link_lnode(0,1):
  lnodes[1].next = lnodes[0].next   // 2
  lnodes[0].next = 1
result: 0(17)→1(23)→2(31)→-1
```

Have students trace the reversed writes on paper: node1 points to itself and the old successor becomes unreachable from node0. Never run this corrupted chain as a traversal exercise.

## 4. Does removal make a slot available? / 빼면 가용 칸이 되는가?

Remove the successor of index0, keeping the returned index.
분리와 반환을 서로 다른 상태 변경으로 표시한다.

```text
initial: 0→1→2→-1; free_head3
delete_next_lnode(0): returns1; active0→2→-1; lnodes[1].next2; free_head3
free_lnode(1): free_head1; free1→3→4→5→6→7→8→9→-1
new_lnode(8, -1): returns1; lnodes[1]={8,-1}; free_head3
```

A node belongs to one active chain, the free chain, or the caller as a detached allocation. A range check does not prevent returning an active node or returning a node twice. `delete_next_lnode` needs a valid predecessor; it does not search for a value.

## 5. How much work changes a link? / 연결을 바꾸는 일은 얼마나 걸릴까?

Count two link assignments for insertion after a known predecessor. Searching for that predecessor can inspect every active node.
선행 노드를 이미 알면 연결 둘만 바꾼다. 선행 노드를 찾아야 하면 활성 노드를 모두 볼 수 있다.

Board / 판서: relink O(1), traversal O(n), initialization O(capacity).

## 6. Which slots are reusable? / 어떤 칸을 다시 쓸 수 있을까?

Classify each of ten slots as free, active, or allocated and detached. No slot may belong to two groups. A range check does not establish membership.
열 칸을 가용, 활성, 할당 후 분리 상태로 나눈다. 한 칸이 두 상태에 겹치면 안 된다. 범위 검사만으로 소속을 확인할 수 없다.

## 7. How can a list preserve arrival order? / 연결 리스트로 도착 순서를 지키려면?

Requests 17,23,31 must leave in arrival order. Remember both ends, then name FIFO and linked queue. First trace node helpers: append an allocated detached index with `enqueue_lnode`; detach an index with `dequeue_lnode`. The raw removal leaves recycling to its caller and returns `-1` when empty.

Then hide that lifecycle behind `bool enqueue(value)` and `int dequeue()`. Enqueue allocates and reports success; dequeue returns the payload and recycles. Callers check status and `is_empty_queue()`. They do not allocate or free queue slots themselves.
공개 함수는 값으로 큐를 쓰게 한다. 노드의 할당과 반환은 함수 안에 둔다. 내부 인덱스와 반환 데이터가 다르다.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

Show a full ten-value queue: the next enqueue returns false with unchanged state. Show payload -1: it is a value, not an empty marker. Evaluate enqueue before any assertion. Module 8 reuses this value interface for BFS IDs.
