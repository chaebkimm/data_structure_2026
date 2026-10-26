# Chapter 7 Lab Slides — Trace and Test the Current lab.c

Use the current `lab.c` with the [lab](lab.md) and [class workbook](class_material.md). Each scene connects a code operation to a predicted state. The supplied source is complete; students add callers, tests, and explanations.
각 장면에서 실행 전에 상태를 예상한다. 무검사 함수의 잘못된 호출은 실행하지 않고 종이에 추적한다.

## 1. What state must an experiment reset? / 실험 전에 무엇을 초기화할까?

The file defines globals and functions, with no `main`. Run the supplied driver from `code`:

```sh
make core
make student-tests
```

Use a C11 compiler. A fresh pool requires `init_lnodes_pool()`. Do not reset a pool while preserving active chains from its old state.

## 2. Does initialization build the complete free chain? / 가용 연결이 끝까지 이어지는가?

Inspect `struct Linked_Node`, `lnodes[10]`, and `init_lnodes_pool()`.
모든 칸의 값은 0이다. 0–8번의 다음 위치는 인덱스보다 1 크다. 9번은 `-1`이다.

Expected evidence: `free_head=0`, exactly ten distinct reachable indices, ending at `-1`. Follow links rather than assuming physical order after later recycling.

## 3. Is allocation a value or an index? / 할당 결과는 값인가 인덱스인가?

Call `new_lnode(17, -1)`, `new_lnode(23, -1)`, `new_lnode(31, -1)`.
반환은 0,1,2다. 각 노드의 `next`는 `-1`이다. `free_head`는 3이다.

Test ten successful allocations and one extra request. On exhaustion, expect `-1` with unchanged pool fields. Check the return before passing it to `link_lnode`. Test out-of-range `free_lnode` only because that function explicitly checks its range; this is not a general guarantee for other functions.

## 4. Do insertion writes preserve the old successor? / 삽입 대입이 기존 다음 위치를 보존하는가?

Build `0→2→-1` and insert1 after0. Step through `link_lnode(0,1)` one line at a time.
첫 대입은 `lnodes[1].next=2`다. 두 번째 대입은 `lnodes[0].next=1`이다.

Expected chain: `0(17)→1(23)→2(31)→-1`.
The function assumes distinct valid allocated indices and a detached inserted node. It supplies no search or bounds check.

## 5. Which function actually returns the slot? / 어느 함수가 칸을 반환하는가?

Run `int removed=delete_next_lnode(0);` and inspect the state before recycling.
`removed=1`, 활성 연결은 `0→2→-1`, `free_head=3`, `lnodes[1].next=2`다.

Then call `free_lnode(removed)`. Expect `free_head=1` and `lnodes[1].next=3`. The old data remains 23. A following `new_lnode(8, -1)` reuses index 1 and sets `next=-1`.

Test deleting after the last valid node: return `-1`, no changed links. Do not substitute first-match deletion or automatic reclamation for this contract.

## 6. What does a useful test assert? / 유용한 테스트는 무엇을 확인할까?

Add original tests for allocation/exhaustion, insertion/traversal, and detach/recycle/reuse. Check exact links and the free chain. A run without a crash does not prove correct membership.
할당과 소진, 삽입과 순회, 분리와 반환 및 재사용을 검사한다. 연결과 가용 연결을 직접 확인한다.

## 7. Who changes the first-node index? / 첫 노드 인덱스는 누가 바꿀까?

The primitives act after a predecessor. The caller changes its own `first` when removing the first node. Save the old next index before recycling that first node.
제공 함수는 선행 노드 뒤를 바꾼다. 첫 노드를 뺄 때 호출자가 `first`를 바꾼다. 반환 전에 기존 다음 인덱스를 보관한다.

## 8. Which changes make the list a queue? / 어느 변경으로 연결 리스트가 큐가 되는가?

Prepare `init_lnodes_pool(); head = tail = -1;` with no live node users. Trace `enqueue_lnode(index)` and `dequeue_lnode()` to expose the two endpoint changes. The raw dequeue returns a detached index, or -1 if empty, without recycling.

Now call `bool added=enqueue(17);` and check `added`. For each public removal first check `!is_empty_queue()`, then use `int value=dequeue();`. The wrapper reads data and recycles before returning. Do not call free_lnode on that value.
공개 함수의 반환값은 데이터다. 내부 함수의 반환값은 칸이다. 값을 넣는 호출은 assert 밖에서 실행한다.

Test ten successful enqueues followed by false without mutation; drain/reuse, singleton endpoint reset, and a queued value -1. Keep public empty dequeue outside the caller contract, including NDEBUG builds. Module 8 uses the same value interface rather than managing pool indices.
