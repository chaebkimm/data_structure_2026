# Chapter 7 Class Workbook / 7장 수업 활동 — Linked Lists

Name / 이름: ____________________ Date / 날짜: ____________________

Use the [textbook](textbook.md), [Korean textbook](textbook_korean.md), [question outline](ppt.md), [concept slides](ppt_material.md), [lab slides](ppt_lab_material.md), and exact [lab.c](lab.c). Preserve first predictions and add corrections. 첫 예상은 지우지 않고 옆에 수정한다. 표 대신 번호 목록으로 답해도 된다.

## 1. Which number is the value? / 값과 인덱스는 어떻게 다른가?

```text
first=0
lnodes[0]={17,1}; lnodes[1]={23,2}; lnodes[2]={31,-1}
```

1. List visited indices and read values. / 방문 인덱스와 값을 각각 쓴다.
2. Explain -1 and who keeps first. / -1의 뜻과 first를 보관하는 주체를 쓴다.
3. If 2.next becomes 0, will traversal end? / 2.next가 0이면 끝나는가?

Prediction / 예상: ____________________ Correction / 수정: ____________________

## 2. Which link must be saved first? / 어느 연결을 먼저 보관하는가?

For 0→2→-1 and allocated isolated 1, trace `simple_link_lnode_to_prev(0,1)`. 기록 1은 할당되어 있고 next=-1이며 다른 연결에 없다.

| Moment / 시점 | 0.next | 1.next | 2.next |
| --- | --- | --- | --- |
| before / 전 | | | |
| first assignment / 첫 대입 | | | |
| second assignment / 둘째 대입 | | | |

Reverse the writes on paper and explain the lost successor/self-link. 대입 순서를 뒤집은 결과는 종이에만 추적한다.

## 3. Is detaching recycling? / 분리와 반환은 같은가?

Start with 0(17)→1(23)→2(31)→-1 and free chain 3→4→5→6→7→8→9→-1.

| Call / 호출 | Returned index / 반환 인덱스 | Active chain / 활성 연결 | free_head | 1.data | 1.next |
| --- | --- | --- | --- | --- | --- |
| `simple_delink_next_lnode_from_prev(0)` | | | | | |
| `free_lnode(1)` | void | | | | |
| `node=new_lnode()` | | | | | |
| caller writes `lnodes[node].data=8` | none | | | | |

Which call isolates, which makes the slot free, and which assigns new data? 분리, 반환, 값 대입을 하는 동작을 나눈다. Why can a caller not return the same slot twice?

## 4. How can lists share slots? / 여러 리스트가 칸을 나누려면?

In a pristine process, allocate singleton A=0(17), B=1(23), free_head=2. Detach A's sole node and set first_a=-1; recycle 0. Allocate 0 for B, write data 8, set next=first_b, then first_b=0. 두 리스트의 시작 위치는 따로 보관한다.

Record both first indices and free/active chains after each step. Explain why A's old index becomes stale, why unused detached allocations consume capacity, and why a double return can create a cycle. 종이에만 잘못된 접근을 진단한다.

`init_lnodes_pool()` has a persistent static guard. Predict a second call while B is live, and a call while the pool is exhausted. It is not a reset. 반복 호출은 초기 상태로 돌려놓지 않는다. For independent pristine indices run a new process; otherwise return all owned allocations and follow the actual free-chain order.

## 5. Which first-node changes give LIFO? / 시작 노드로 LIFO를 만들려면?

There is no supplied Stack API. To prepend, call `node=new_lnode()` and check success, then write its data, set `lnodes[node].next=first`, and finally set `first=node`. Prepending 17,23,31 in a pristine process gives 2(31)→1(23)→0(17)→-1. Before removal check `first != -1`; save the old index, data, and next, advance `first`, set `lnodes[old].next=-1`, then recycle. The outputs are 31,23,17. Clearing next is required because `free_lnode` accepts only isolated allocations. Never recover data or next through a recycled old index.

For each prepend/remove, record first, active chain, detached index, and free head. 제거 전에 값과 다음을 보관하고, first를 바꾼 뒤 옛 노드의 next를 -1로 만들어 반환한다. Explain unchanged Stack state on exhausted allocation and the nonempty guard on removal.

## 6. Which end preserves arrival order? / 어느 끝이 도착 순서를 지키는가?

The supplied queue operates on **node indices**. `enqueue_lnode(node)` appends a valid allocated, unreferenced, isolated node (`next == -1`). Allocate first with `new_lnode()`, check for `-1`, write `lnodes[node].data=value`, then append. `enqueue_lnode(-1)` is a no-op; the void function does not report allocation failure.

`dequeue_lnode()` returns the oldest **index**, isolates that node with `next=-1`, and leaves it allocated to the caller. Empty removal returns `-1` without changes. On success, copy `lnodes[node].data`, then call `free_lnode(node)` exactly once. Neither queue operation allocates or recycles automatically. There are no supplied value-based `enqueue(value)` or `dequeue()` wrappers.

The endpoints are `qhead` and `qtail`. Both are `-1` when empty; otherwise `qtail` is reachable from `qhead` and `lnodes[qtail].next == -1`. The first append sets both; the final removal clears both. A payload of `-1` is valid: only the returned node index is the empty marker.

| Action in a pristine process | Result | `qhead` | `qtail` | Queue | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| allocate 0, write 17, append 0 | void | 0 | 0 | 0→-1 | 1 |
| allocate 1, write 23, append 1 | void | 0 | 1 | 0→1→-1 | 2 |
| allocate 2, write 31, append 2 | void | 0 | 2 | 0→1→2→-1 | 3 |
| `node=dequeue_lnode()` | index 0; next=-1 | 1 | 2 | 1→2→-1 | 3 |
| copy data 17; `free_lnode(0)` | caller recycles | 1 | 2 | 1→2→-1 | 0 |
| allocate 0, write 8, append 0 | void | 1 | 0 | 1→2→0→-1 | 3 |
| dequeue/copy/recycle remaining | values 23,31,8 | -1 | -1 | empty | 0 |

The final free chain is 0→2→1→3→4→5→6→7→8→9→-1. All ten slots are free; their order need not match initialization.

Allocate/append a node with data=-1; what index does removal return? What does an empty removal return? 값 -1과 빈 큐의 인덱스 -1을 구분한다. Explain why the caller copies data and explicitly recycles once, and why a void append is not an allocation-success result.

## 7. Which rules must remain true? / 계속 지켜야 할 규칙은?

- Every active list and the free chain are acyclic, end at `-1`, and contain only indices 0–9.
- Every slot belongs exactly once to the free chain, one active list, or a caller-held isolated allocation. Active lists are disjoint; every standalone list has its own saved first index.
- A caller-held node ready for insertion, enqueue, or recycling has `next == -1` and no incoming live link.
- The queue is empty exactly when both endpoints are `-1`; otherwise the tail is reachable and ends at `-1`.
- Save payload/successor before recycling, then stop using the old owner's index. Index range alone does not establish ownership.

For each operation distinguish its caller preconditions from its completed-state invariants. 사전 조건과 연산 후 불변식을 구분한다. Do not execute invalid non-sentinel indices, double return, stale writes, or recycling live nodes.

## 8. What does the evidence establish? / 실행 근거는 무엇을 보여 주는가?

Use three original test groups: allocation/exhaustion/shared pool; insertion/traversal/first insertion; detachment/recycling/reuse with Stack LIFO and Queue FIFO/endpoints. Return every owned node between tests. Execute mutations outside assert; release builds may remove assertions.

Command / 명령: ____________________ Expected/observed / 예상과 관찰: ____________________ Correction / 수정: ____________________

Count fixed field work, O(n) predecessor/i-th-node search, O(C) first initialization and O(1) later calls, and one extra next integer per slot. 같은 한 제출물에 근거를 모은다.
