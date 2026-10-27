# Chapter 7 Class Workbook / 7장 수업 활동 — Linked Lists

Name / 이름: ____________________ Date / 날짜: ____________________

Use the [English textbook](textbook.md), [Korean textbook](textbook_korean.md),
[concept slides](ppt_material.md), and [lab](lab.md). Read exact behavior in [lab.c](lab.c).
Keep each first prediction and add corrections beside it.
첫 예상을 지우지 않고 옆에 수정한다. 표 대신 같은 항목의 번호 목록으로 답해도 된다.

## 1. Which number is the value? / 값은 어느 숫자인가?

We want to read 17, 23, and 31 without requiring neighboring slots.
값의 물리적 위치와 읽는 순서를 나눠 보자.

```text
lnodes[0] = {17, 1}
lnodes[1] = {23, 2}
lnodes[2] = {31, -1}
first = 0
```

1. Write the visited indices / 방문 인덱스: ____________________
2. Write the read values / 읽는 값: ____________________
3. Explain the ending `-1` and who keeps `first` / 끝 표시의 뜻과 시작 위치를 보관하는 주체: ____________________
4. If slot 2 pointed back to 0, would traversal finish? / 2번의 다음이 0이면 순회가 끝나는가?

Initial prediction / 첫 예상: ______________________________________
Correction and reason / 수정과 이유: _______________________________

## 2. Which link must be saved first? / 어느 연결을 먼저 보관하는가?

Use a valid list 0(17)→2(31)→-1 and detached allocated node 1 holding 23.
`link_lnode(0,1)` inserts node 1 between nodes 0 and 2.
0번과 2번 사이에 1번을 넣는다. 삽입할 노드는 다른 활성 연결이나 가용 연결에 없어야 한다.

| Moment / 시점 | `lnodes[0].next` | `lnodes[1].next` | `lnodes[2].next` |
| --- | --- | --- | --- |
| before insertion / 삽입 전 | | | |
| after the first assignment / 첫 대입 후 | | | |
| after the second assignment / 두 번째 대입 후 | | | |

Predict the result if the two assignments are reversed. Trace the writes on paper only.
두 대입을 뒤집었을 때의 결과는 종이에만 추적한다.

__________________________________________________________________

## 3. Is detaching the same as recycling? / 분리와 반환은 같은가?

Use 0(17)→1(23)→2(31)→-1, with `free_head=3` and the remaining slots linked in ascending order.
다음 세 호출을 순서대로 적용한다.

| Call / 호출 | Return / 반환 | Active chain / 활성 연결 | `free_head` | `lnodes[1].data` | `lnodes[1].next` |
| --- | --- | --- | --- | --- | --- |
| `delete_next_lnode(0)` | | | | | |
| `free_lnode(1)` | no return / 없음 | | | | |
| `new_lnode(8, -1)` | | | | | |

Why must the caller retain the detached index? What happens if the caller never returns it?
분리한 인덱스를 보관해야 하는 이유와 반환을 빠뜨렸을 때의 결과를 쓴다.
Why is returning it twice invalid even when the index is in range?
범위 안의 칸도 중복 반환하면 안 되는 이유를 쓴다.

__________________________________________________________________

## 4. How can lists share ten slots? / 여러 리스트가 열 칸을 어떻게 나눠 쓰는가?

Start an independent unowned pool with `init_lnodes_pool()`. Allocate 17 and 23 with next `-1`.
Keep `first_a=0` for list A and `first_b=1` for list B. The free chain starts at 2.
새 풀에서 두 리스트의 시작 위치를 따로 보관한다. 어느 활성 리스트에도 같은 칸을 중복으로 넣지 않는다.

| Action / 동작 | A's first / A 시작 | B's first / B 시작 | `free_head` | Slot 0 data/next / 0번 값과 다음 |
| --- | --- | --- | --- | --- |
| two singleton lists / 한 노드 리스트 둘 | 0 | 1 | 2 | 17 / -1 |
| detach A's first, then `free_lnode(0)` / A에서 분리 후 반환 | | | | |
| `node=new_lnode(8,first_b)`, check result, then `first_b=node` / B 맨 앞에 추가 | | | | |

A stale copy of A's former index still equals 0. What does reading its data now return?
Why can writing its `data` or `next` damage B? Diagnose on paper; do not perform stale writes.
A가 예전 인덱스 0으로 읽으면 무엇을 얻는가? 그 칸을 바꾸면 B가 왜 바뀌는가?
Explain why both lists can use any available slot and why initialization cannot run while either owns a slot.
가용 칸을 어느 리스트나 쓸 수 있는 이유와 사용 중인 풀을 초기화하면 안 되는 이유를 쓴다.

__________________________________________________________________

## 5. Which first-node changes give LIFO? / 시작 노드를 어떻게 바꾸면 LIFO가 되는가?

Use a fresh unowned pool and caller variable `first=-1`. There is no supplied Stack API.
For each of 17, 23, and 31, call `node=new_lnode(value,first)`; set `first=node` only after checking `node != -1`.
새 풀에서 시작 노드 앞에 차례로 추가한다. 할당 실패 시 시작 위치를 바꾸지 않는다.

| Action / 동작 | Return index/value / 반환 인덱스 또는 값 | `first` | Stack chain / 스택 연결 | `free_head` |
| --- | --- | --- | --- | --- |
| add 17 / 17 추가 | | | | |
| add 23 / 23 추가 | | | | |
| add 31 / 31 추가 | | | | |
| remove first / 시작 노드 제거 | | | | |
| drain remaining two / 나머지 둘 제거 | | | | |

Before removal, check `first != -1`. Save the old index, its data, and its next; update `first`, then recycle the old node. Stop using that index afterward.
제거 전 빈 스택인지 검사한다. 옛 인덱스와 값, 다음 위치를 보관하고 시작 위치를 바꾼 뒤 반환한다.
Predict output 31,23,17. Contrast it with the arrival order. What happens on an empty removal or an exhausted allocation?
출력 31,23,17을 도착 순서와 비교한다. 빈 스택의 제거와 풀 소진 시 호출자가 할 일을 쓴다.

Prediction / 예상: ____________________ Correction and reason / 수정과 이유: ____________________

## 6. Which end preserves arrival order? / 어느 끝이 도착 순서를 지키는가?

Prepare an independent unowned pool with `init_lnodes_pool(); head = tail = -1;`. Call `enqueue(17)`, `enqueue(23)`, and `enqueue(31)`. Save and check each boolean result. Predict the value and free-chain change after `dequeue()`; the wrapper recycles its slot. Enqueue 8 behind the remaining values.
새 풀과 양 끝을 준비한다. 공개 함수는 값을 넣고 성공 여부를 반환한다. 값을 꺼낼 때 칸도 내부에서 반환한다.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

Compare `int slot=dequeue_lnode()` with `int value=dequeue()`. Which leaves a detached allocated slot? Which already recycles it? What does each return for a queue containing the payload `-1`? What must be checked before public dequeue?
내부 함수의 인덱스 반환과 공개 함수의 값 반환을 구분한다. 마지막 노드를 꺼낼 때 양 끝이 모두 `-1`인지 확인한다.
Explain why `assert(enqueue(17))` loses its insertion under `NDEBUG`.
삽입 호출을 `assert` 안에 넣으면 안 되는 이유를 쓴다.

Prediction / 예상: ____________________ Correction and reason / 수정과 이유: ____________________

## 7. What does the evidence establish? / 실행 근거는 무엇을 보여 주는가?

Run the Week 7 tests and add three original safe groups: allocation/exhaustion including shared-pool accounting, insertion/traversal including first insertion, and detachment/recycling/reuse including linked Stack and Queue.
세 테스트 그룹 안에서 공유 풀, 스택의 LIFO, 큐의 FIFO와 양 끝 전환을 검사한다.

Command / 명령: ____________________
Expected and observed state / 예상과 관찰 상태: ____________________
Correction and reason / 수정과 이유: ____________________

Count the writes for a known-predecessor insertion and first-node Stack/Queue changes. Compare them with searching for the i-th node. Count one additional integer link per pool slot, without assuming an integer's byte size.
이미 아는 위치의 연결 변경과 i번째 노드를 찾는 작업을 구분한다. 다음 위치 저장에 필요한 메모리도 센다.
