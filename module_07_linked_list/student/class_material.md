# Chapter 7 Class Workbook / 7장 수업 활동 — Organizing data with links

Name / 이름: ____________________ Date / 날짜: ____________________

Use the [English textbook](textbook.md) or [Korean textbook](textbook_korean.md), then record your predictions and observations here. Keep the first prediction and add a correction beside it. 첫 예상은 지우지 않고 옆에 수정한다. 표 대신 번호 목록으로 답해도 된다.

## 1. Thinking logically / 논리적으로 생각해 보기

### What order do the links describe? / 연결은 어떤 순서를 나타내는가?

```text
first = 0
lnodes[0] = {17, 2}
lnodes[1] = {23, -1}  // allocated and separate / 할당된 별도 노드
lnodes[2] = {31, -1}
```

1. List the visited indices and the values read from `first`. / 방문 인덱스와 읽은 값을 각각 쓴다.
2. Explain why physical slot 1 is outside this list. / 배열의 1번 칸이 리스트에 없는 이유를 쓴다.
3. Explain `-1`, who keeps `first`, and when to check the index. / `-1`의 뜻, `first`의 보관 위치, 인덱스 검사 시점을 쓴다.
4. On paper, change `2.next` to 0. Will traversal finish? / 종이에서 `2.next`를 0으로 바꾸고 순회가 끝나는지 판단한다.

Prediction / 예상: ____________________ Correction / 수정: ____________________

### Which link must be saved first? / 어느 연결을 먼저 보관하는가?

Insert the separate node 1 after node 0 using `simple_link_lnode_to_prev(0, 1)`. The indices are valid and distinct; node 1 is allocated, outside every chain, and has `next = -1`. / 별도 노드 1을 노드 0 뒤에 넣는다.

| Moment / 시점 | 0.next | 1.next | 2.next |
| --- | --- | --- | --- |
| before / 전 | | | |
| first assignment / 첫 대입 | | | |
| second assignment / 둘째 대입 | | | |

Write the resulting index order and value order. Reverse the assignments on paper and identify the lost successor and self-link. / 결과의 인덱스 순서와 값 순서를 쓴다. 대입 순서를 뒤집은 결과는 종이에만 추적한다.

### Is detaching recycling? / 분리와 반환은 같은가?

Start with `0(17) → 1(23) → 2(31) → -1` and free chain `3 → 4 → 5 → 6 → 7 → 8 → 9 → -1`.

| Call / 호출 | Returned index / 반환 인덱스 | Active chain / 활성 연결 | free_head | 1.data | 1.next |
| --- | --- | --- | --- | --- | --- |
| `simple_delink_next_lnode_from_prev(0)` | | | | | |
| `free_lnode(1)` | void | | | | |
| `node = new_lnode()` | | | | | |
| caller writes `lnodes[node].data = 8` | none | | | | |

Which operation isolates the node, which returns it to the pool, and which changes its data? When must the caller read data it wants to keep? / 분리, 풀에 반환, 값 대입을 구분한다. 보관할 값은 언제 읽어야 하는가?

### How can lists share slots? / 여러 리스트가 칸을 나누려면?

In a fresh process, A owns singleton `0(17)`, B owns singleton `1(23)`, and `free_head = 2`. Remove A's node and set `first_a = -1`, then recycle 0. Allocate a node for B, write 8, link it before B's first node, and update `first_b`. / 두 리스트의 시작 위치를 따로 보관한다.

Record both first indices and every active/free chain. Explain why A's old index is stale. Predict what `init_lnodes_pool()` does when called again, including when all slots are allocated. / 각 시작 인덱스와 활성·가용 연결을 쓴다. A의 이전 인덱스를 계속 쓰면 안 되는 이유와 초기화 함수의 반복 호출 결과를 설명한다.

### Which end gives LIFO or FIFO? / 어느 끝에서 넣고 빼는가?

Use separate fresh processes for the stack and queue traces. In each, allocate nodes, check each returned index, and write values 17, 23, and 31. / 스택과 큐를 각각 새 프로그램에서 추적한다.

- Stack: add before `first`, then remove from `first`. Record each first index and the output values. Before recycling, save the old first node's data and successor, advance `first`, and set the old node's `next = -1`. / 스택은 첫 노드에서 넣고 뺀다.
- Queue: append with `enqueue_lnode()`, then remove with `dequeue_lnode()`. Record both endpoints, each returned index, and its data. Read the data before recycling the returned node. / 큐는 꼬리에 넣고 머리에서 뺀다. 반환 인덱스로 값을 읽은 뒤 노드를 반환한다.

For the queue, remove/read/recycle 17, allocate a node containing 8, and append it behind the waiting nodes. Predict the remaining output and the final free-chain order. / 큐에서 17을 꺼내 반환한 뒤 8을 넣는다. 남은 출력과 마지막 가용 연결의 순서를 예상한다.

Also compare a node whose data is `-1` with an empty dequeue result of `-1`. / 데이터 `-1`과 빈 큐를 뜻하는 반환 인덱스 `-1`을 구분한다.

## 2. Calculating efficiency / 효율 계산해보기

Answer the textbook's four cost questions. / 교재의 네 가지 효율 질문에 답한다.

| Question / 질문 | Reasoning / 근거 |
| --- | --- |
| What space is reserved even when the lists are empty? / 리스트가 비어 있어도 확보하는 공간은? | |
| What extra state does an iterative traversal keep? / 반복 순회가 추가로 보관하는 것은? | |
| Why is the first allocation different from later allocations? / 첫 할당의 작업량이 다른 이유는? | |
| How many links reach the third node? How many visit all n nodes? / 세 번째 노드와 전체 n개 노드에 접근하는 작업량은? | |

Separate changing links after a known predecessor from finding that predecessor. Explain why ten slots limit simultaneous allocations but not the total number of values processed through reuse. / 선행 노드를 찾는 작업과 연결 변경을 구분한다. 재사용으로 처리한 전체 값의 수와 동시에 할당된 노드 수를 구분한다.

## 3. Glossary / 용어 정리

After preserving your predictions, use the textbook glossary or [vocabulary reference](vocabulary.md). / 예상을 기록한 뒤 용어를 확인한다.

Explain these pairs using the traces above: index/data, predecessor/successor, allocation/recycling, active/detached node, stack/queue. Identify a cycle and a stale index. / 위 추적으로 각 용어의 차이를 설명하고 순환과 이전 소유자의 인덱스를 찾아본다.

## 4. Invariant / 불변식

### What are the golden rules? / 반드시 지켜야 할 규칙은?

State the rules for valid indices, acyclic chains, exclusive ownership, detached nodes, and queue endpoints. Account for all ten slots after each complete operation. / 유효 인덱스, 순환 없는 연결, 겹치지 않는 소유 상태, 분리 노드, 큐의 양 끝 규칙을 쓴다.

### What benefit do they provide? / 어떤 이점이 있는가?

Explain why traversal ends, why lists can safely share the pool, and why queue endpoints preserve FIFO. / 순회 종료, 풀 공유, FIFO 유지와 규칙의 관계를 설명한다.

### What happens when a rule is broken? / 규칙이 깨지면 어떻게 되는가?

Diagnose a cycle, a lost detached index, returning an active node, duplicate return, and stale access on paper. / 순환, 분리 노드의 인덱스 분실, 사용 중인 노드 반환, 중복 반환, 이전 인덱스 사용을 종이에서 진단한다.

### How do we preserve the rules? / 어떻게 규칙을 지킬까?

Distinguish caller preconditions from the state after a completed operation. Explain why the ordinary predecessor helpers must not change queued nodes. / 호출 전 조건과 연산 후 불변식을 구분한다. 큐에 일반 선행 노드 함수를 쓰면 안 되는 이유를 설명한다.

## 5. Coding plan / 코딩 계획

Write the steps before running code: design a node; connect/detach; initialize the pool once; allocate/recycle; update a stack's first index; maintain queue endpoints. / 노드 설계, 연결·분리, 풀 초기화, 할당·반환, 스택, 큐 순서로 계획을 쓴다.

Mark where each plan checks `-1`, preserves a successor, assigns data, and transfers ownership. Include allocation failure and empty removal. / 각 계획에서 `-1` 검사, 다음 위치 보관, 데이터 대입, 소유 상태 변경을 표시한다.

## 6. New C syntax explained / 새로운 C 문법 설명

1. Which declarations and loops use `CAPACITY` from `enum { CAPACITY = 10 };`? / 상수 이름을 사용하는 선언과 반복문을 찾는다.
2. What value does the local `static initialized` retain after the first call? / 첫 호출 뒤 유지되는 값은?
3. Explain the two uses of `void` in `int new_lnode(void)` and `void free_lnode(int node)`. / 두 `void`의 뜻을 구분한다.
4. If `node` is 4, what does `qhead = qtail = node;` store? / 연속 대입 뒤 두 값은?
5. What does `return qhead == -1;` return for `qhead = -1` and `qhead = 4`? / 비교 결과의 반환값은?

## 7. C code and evidence / C 코드와 실행 근거

Read the textbook's nine small C blocks alongside [lab.c](lab.c). The textbook changes display comments and indentation; the operations are the same. Create your caller and tests as described in the [lab](lab.md). / 교재의 아홉 C 코드 블록을 원본과 함께 읽고 실습 안내에 따라 호출자와 테스트를 작성한다.

Use three original test groups: allocation/exhaustion/shared pool; insertion/traversal/first insertion; detachment/recycling/reuse with stack LIFO and queue FIFO/endpoints. Return every owned node between tests or run independent examples as separate processes. Execute state changes outside `assert`. / 세 가지 독창적인 테스트 그룹의 결과를 기록한다.

Command / 명령: ____________________ Expected/observed / 예상과 관찰: ____________________ Correction / 수정: ____________________

Submit the traces, tests, cost reasoning, and corrected prediction together in the existing single lab artifact. / 추적, 테스트, 효율 근거, 수정한 예상을 하나의 실습 제출물로 모은다.
