# Chapter 7 Class Workbook / 7장 수업 활동 — Linked Lists

Name / 이름: ____________________ Date / 날짜: ____________________

Use the [English textbook](textbook.md), [Korean textbook](textbook_korean.md),
[concept slides](ppt_material.md), and [lab slides](ppt_lab_material.md).
The source of truth is `lab.c`. Keep each first prediction and add corrections beside it.
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
3. Explain the ending `-1` / 끝 표시의 뜻: ____________________
4. What would change if slot 1 were reused for value 8? / 1번을 값 8로 재사용하면 무엇이 바뀌는가?

Initial prediction / 첫 예상: ______________________________________
Correction and reason / 수정과 이유: _______________________________

## 2. How does a slot leave the free chain? / 가용 칸은 어떻게 빠지는가?

Start an independent pool with `init_lnodes_pool()`. Allocate three nodes without linking them.
새 풀에서 세 칸을 할당한다. 아직 서로 연결하지 않는다.

| Call / 호출 | Return index / 반환 인덱스 | `free_head` | Allocated node's `next` / 할당 노드의 다음 위치 |
| --- | --- | --- | --- |
| `new_lnode(17, -1)` | | | |
| `new_lnode(23, -1)` | | | |
| `new_lnode(31, -1)` | | | |

After all ten slots are allocated, predict one more allocation's return and every changed field.
열 칸이 모두 할당된 뒤 한 번 더 요청하면 무엇을 반환하고 어떤 필드가 바뀌는가?

__________________________________________________________________

## 3. Which link must be saved first? / 어느 연결을 먼저 보관하는가?

Continue with indices 0, 1, and 2 holding 17, 23, and 31. Call `link_lnode(0, 2)` to make `0→2→-1`. Now insert node 1 after node 0 with `link_lnode(0, 1)`.
0번 뒤에 2번을 연결한 뒤 그 사이에 1번을 넣는다.

| Moment / 시점 | `lnodes[0].next` | `lnodes[1].next` | `lnodes[2].next` |
| --- | --- | --- | --- |
| before insertion / 삽입 전 | | | |
| after the first assignment / 첫 대입 후 | | | |
| after the second assignment / 두 번째 대입 후 | | | |

Predict the result if the two assignments are reversed. Trace the writes on paper only.
두 대입을 뒤집었을 때의 결과는 종이에만 추적한다.

__________________________________________________________________

## 4. Is detaching the same as recycling? / 분리와 반환은 같은가?

Use `0(17)→1(23)→2(31)→-1`, with `free_head=3`. The following calls happen in order.
다음 세 호출을 순서대로 적용한다.

| Call / 호출 | Return / 반환 | Active chain / 활성 연결 | `free_head` | `lnodes[1].data` | `lnodes[1].next` |
| --- | --- | --- | --- | --- | --- |
| `delete_next_lnode(0)` | | | | | |
| `free_lnode(1)` | no return / 없음 | | | | |
| `new_lnode(8, -1)` | | | | | |

Why must the caller retain the returned index? Why is calling `free_lnode(1)` twice invalid even though 1 is in range?
반환 인덱스를 보관해야 하는 이유와 범위 안의 칸도 중복 반환하면 안 되는 이유를 쓴다.

__________________________________________________________________

## 5. What does the evidence establish? / 실행 근거는 무엇을 보여 주는가?

Run the Week 7 tests and add three original safe groups: allocation/exhaustion, insertion/traversal, and detachment/recycling/reuse.
Week 7 테스트를 실행하고 할당과 소진, 삽입과 순회, 분리와 반환 및 재사용을 검사하는 세 그룹을 추가한다.

Command / 명령: ____________________
Expected and observed state / 예상과 관찰 상태: ____________________
Correction and reason / 수정과 이유: ____________________

Count the writes for a known-predecessor insertion. Compare them with searching for that predecessor.
이미 아는 선행 노드 뒤의 삽입과 그 노드를 찾는 검색의 작업 수를 구분한다.

## 6. Which end preserves arrival order? / 어느 끝이 도착 순서를 지키는가?

Prepare an independent unowned pool with `init_lnodes_pool(); head = tail = -1;`. Call `enqueue(17)`, `enqueue(23)`, and `enqueue(31)`. Save and check each boolean result. Predict the value and free-chain change after `dequeue()`; the wrapper recycles its slot. Enqueue 8 behind the remaining values. Record 23,31,8 as the final output.
새 풀과 양 끝을 준비한다. 공개 함수는 값을 넣고 성공 여부를 반환한다. 값을 꺼낼 때 칸도 내부에서 반환한다. 기다리는 값 뒤에 재사용한 칸을 붙여도 도착 순서를 유지해야 한다.

| Action after a fresh reset | Return | `head` | `tail` | Live slots | `free_head` |
| --- | --- | ---: | ---: | --- | ---: |
| `enqueue(17)` | `true` | 0 | 0 | 0 → -1 | 1 |
| `enqueue(23)` | `true` | 0 | 1 | 0 → 1 → -1 | 2 |
| `enqueue(31)` | `true` | 0 | 2 | 0 → 1 → 2 → -1 | 3 |
| `dequeue()` | 17 | 1 | 2 | 1 → 2 → -1 | 0 |
| `enqueue(8)` | `true` | 1 | 0 | 1 → 2 → 0 → -1 | 3 |
| drain 23, 31, 8 | values | -1 | -1 | empty | 0 (all ten free) |

Compare `int slot=dequeue_lnode()` with `int value=dequeue()`. Which call leaves a detached allocated slot? Which already recycles it? What does each return for a queue containing the payload `-1`? What must be checked before public dequeue?
내부 함수의 인덱스 반환과 공개 함수의 값 반환을 구분한다. `assert(enqueue(17))`를 `NDEBUG`로 빌드하면 왜 삽입이 사라지는지 설명한다.

Prediction / 예상: ____________________ Correction and reason / 수정과 이유: ____________________
