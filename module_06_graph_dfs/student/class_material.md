# Chapter 6 Class Workbook / 6장 수업 활동 — Graph DFS

이름 / Name: ____________________  날짜 / Date: ____________________

[개념 슬라이드 / Concept slides](ppt_material.md)의 질문 순서로 진행한다.
[영문 교재 / English textbook](textbook.md), [한글 교재 / Korean textbook](textbook_korean.md),
[실습 슬라이드 / Lab slides](ppt_lab_material.md)를 함께 사용한다.
Use the concept slides' question order. Preserve initial predictions and
write corrections beside them. Every table may instead be answered as a
numbered list with the same fields.

개념 그림의 1–7은 정해진 DFS의 방문 번호다. 아래에서는 노드를 방문 번호로
가리킨다. 마지막 코딩 활동은 최신 [lab.c](lab.c)와 원래 A–J 그래프를 사용한다.
The concept diagram's numbers 1–7 are visit numbers from the fixed DFS.
Refer to vertices by these visit numbers. The final coding activity uses
the current lab with the original A–J graph; keep its trace separate.

## 1. 이웃 간선의 종류는? / What kind of neighbor connection is this?

그림은 DFS의 방문 번호가 모두 정해진 상태다. 방문 1에서 시작하고, 그림의
이웃 번호를 오름차순으로 확인했던 과정을 되짚는다. 방문 번호는 1부터 시작한다.
The diagram shows the completed numbering of a fixed DFS. Retrace that
exploration from visit 1, checking diagram neighbors in ascending order.
Visit numbers begin at 1.

```text
Endpoint visit pairs / 끝점 방문 번호 쌍:
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6

1:[2,3]       2:[1,3,7]     3:[1,2,4,6,7]
4:[3,5,6]     5:[4,6]       6:[3,4,5]     7:[2,3]
```

방문 3에서 각 이웃을 확인했던 시점마다 네 종류 중 하나를 고른다: 아직
탐색하지 않은 트리 자식, 트리 부모, 부모가 아닌 빽 간선 조상, 이미 처리한 빽 간선 후손.
At each actual encounter from visit 3, choose: unexplored tree child,
tree parent, non-parent back-edge ancestor, or processed back-edge descendant.

| Encounter / 확인 | Kind / 종류 | Explore again? / 다시 탐색? | Evidence / 근거 |
| --- | --- | --- | --- |
| 3 → 1 | | | |
| 3 → 2 | | | |
| 3 → 4 | | | |
| 3 → 6, after 4 returns / 4의 탐색 후 | | | |
| 3 → 7 | | | |

부모를 먼저 구별해야 하는 이유는? / Why distinguish the parent before
comparing visit numbers?

Initial prediction / 첫 예상: ______________________________________

Correction and evidence / 수정과 근거: ______________________________

## 2. 작업은 언제 하는가? / When does each action happen?

preorder에서 방문 번호를 붙인다. 새 자식에게 부모를 정해 준 뒤 내려간다.
자식의 탐색이 끝나면 부모의 멈춰 있던 이웃 확인을 이어간다.
postorder는 현재 노드의 모든 이웃을 확인한 뒤다.
Assign the visit number at entry. Set a new child's parent before
exploring it. After return, resume the parent's paused neighbor scan.
Postorder occurs after scanning all of the current vertex's neighbors.

| Visit number / 방문 번호 | Parent visit number / 부모 방문 번호 |
| --- | --- |
| 1 | |
| 2 | |
| 3 | |
| 4 | |
| 5 | |
| 6 | |
| 7 | |

방문 3에서 4로 내려가기 직전과 돌아온 직후, 기다리는 작업은 무엇인가?
What work waits at visit 3 immediately before and after exploring visit 4?

____________________________________________________________________

빈 원에 해당 시점의 방문 번호를 적고, 확인한 간선을 강조한다. 그림의 숫자는
방문 번호이며, 빈 원과 부분 강조는 작업을 진행하는 판서 활동이다.
Annotate blank circles with the visit numbers reached at that stage and
highlight handled connections. The diagram's numbers are visit numbers;
blank circles and partial highlights are a board activity showing progress.

## 3. 간선을 저장하는 세 방법은? / Three ways to store connections

3장에서는 이웃 목록만 배웠다. 여기서는 이웃 목록을 복습하고, 간선 목록과
인접 행렬을 6장의 새 표현으로 배운다.
Chapter 3 taught adjacency lists only. Review those lists, then learn
edge lists and adjacency matrices as new representations in Chapter 6.

세 표현은 같은 그래프를 저장한다. 이웃 목록은 한 노드의 이웃을 모으고,
간선 목록은 끝점 쌍을 모으며, 인접 행렬은 두 끝점으로 연결을 조회한다.
The three representations store the same graph: neighbor lists collect
a vertex's neighbors, an edge list collects endpoint pairs, and an
adjacency matrix supports lookup by two endpoints.

| Representation / 표현 | Store 3–6 / 3–6 저장 | Add 3–6 / 추가 | Delete 3–6 / 삭제 |
| --- | --- | --- | --- |
| Neighbor lists / 이웃 목록 | | | |
| Edge list / 간선 목록 | | | |
| Adjacency matrix / 인접 행렬 | | | |

간선 목록의 장점과 행렬의 장점은? 노드를 삭제하면 연결된 간선은 어떻게 처리하는가?
What is useful about an edge list and a matrix? What happens to incident
connections when deleting a vertex?

____________________________________________________________________

## 4. 같은 간선을 두 번 모으지 않으려면? / Collect each connection once

자식으로 내려갈 때 트리 간선을 모은다. 부모가 아닌 조상을 볼 때 빽 간선을
모은다. 부모와 후손 방향은 반대쪽에서 이미 처리했으므로 건너뛴다.
Collect tree connections before entering a child and back connections
when encountering a non-parent ancestor. Skip parent and descendant
directions already processed from the other endpoint.

모은 순서대로 끝점 방문 번호 쌍을 적는다. 작은 번호를 먼저 쓴다. 예: 3 → 1은 1–3.
List endpoint visit-number pairs in collection order, smaller number first:
3 → 1 becomes 1–3.

| Collection order / 모은 순서 | Endpoint visit pair / 끝점 방문 번호 쌍 | Tree or back? / 트리 또는 빽? |
| --- | --- | --- |
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |
| 7 | | |
| 8 | | |
| 9 | | |
| 10 | | |

1 → 3을 나중에 확인할 때 왜 다시 모으지 않는가?
Why is 1 → 3 not collected again when visit 1 eventually scans it?

____________________________________________________________________

## 5. 방문 6의 빽번호는? / What is visit 6's earliest reconnection number?

자신의 방문 번호로 시작한다. 조상으로 가는 빽 간선에서는 조상의 방문 번호를,
자식이 돌아왔을 때는 자식의 빽번호를 비교해서 더 작은 값을 남긴다.
빽번호는 트리 간선을 따라 내려가고 빽 간선을 최대 한 번 사용해 도달할 수 있는
가장 이른 방문 번호이며, 자신의 방문 번호도 후보에 포함한다.
Begin with the vertex's own visit number. Compare an ancestor's visit
number along a back connection and a child's earliest number after its
return. Keep the smaller value: the earliest visit reachable by tree
descent and at most one back connection, including self.

| Visit number / 방문 번호 | Earliest reconnection / 빽번호 |
| --- | --- |
| 1 | |
| 2 | |
| 3 | |
| 4 | |
| 5 | |
| 6 | |
| 7 | |

방문 6에서 이웃 3과 4를 확인할 때의 비교를 설명한다. 빽번호 3으로 돌아갈 수
있는 조상은 어느 방문인가? / Explain visit 6's comparisons at neighbors
3 and 4. Which earlier visit can it reconnect to with an earliest number of 3?

____________________________________________________________________

## 6. 끈끈한 간선을 찾으면? / Which connections belong together?

세 노드 이상인 끈끈한 그룹에서는 어느 두 노드 사이에도 내부 노드를 공유하지
않는 두 경로가 있다. 끝점은 공유해도 된다. 최대 그룹을 찾으며, 서로 다른 그룹은
경계 노드를 공유할 수 있지만 간선은 공유하지 않는다.
In a block of at least three vertices, every pair has two paths with no
shared internal vertex; endpoints may be shared. Find maximal blocks.
Different blocks may share a boundary vertex but do not share connections.

트리 자식 간선과 조상 빽 간선을 스택에 넣는다. 자식의 탐색이 끝나 돌아오면 부모가
즉시 자식의 빽번호와 자신의 방문 번호를 비교한다. 자식의 빽번호가 부모의 방문 번호
이상이면, 부모–자식 간선까지 포함해 꺼내서 한 그룹으로 모은다.
Push child tree pairs and ancestor back pairs. Immediately after a child
returns, the parent compares the child's earliest number with its own
visit number. If the child's value is at least the parent's number, remove
through the parent–child pair, including it, to make one block.

스택은 바닥부터 맨 위까지, 새 그룹은 꺼낸 순서대로 끝점 방문 번호 쌍을 적는다.
List complete pending pairs bottom to top and each block in removal order.

| Event / 시점 | Complete pending pairs / 전체 대기 쌍 | New block / 새 그룹 |
| --- | --- | --- |
| Enter visit 3 / 방문 3 진입 | | |
| Scan 3 → 1 / 3 → 1 확인 | | |
| Scan 6 → 4, after 6 → 3 / 6 → 3 다음 | | |
| Finish visit 6 / 방문 6 종료 | | |
| Finish visit 5 / 방문 5 종료 | | |
| Finish visit 4 / 방문 4 종료 | | |
| Scan 7 → 2 / 7 → 2 확인 | | |
| Finish visit 7 / 방문 7 종료 | | |
| Finish visit 3 / 방문 3 종료 | | |
| Finish visit 2 / 방문 2 종료 | | |
| Finish visit 1 / 방문 1 종료 | | |

방문 4의 빽번호와 부모 방문 3의 번호가 같을 때도 그룹을 꺼내는 이유는?
Why does equality between visit 4's earliest number and parent visit 3 close a block?

____________________________________________________________________

두 그룹의 끝점 방문 번호 쌍과 공유하는 방문을 적는다.
List both blocks' endpoint visit pairs and identify their shared visit.

____________________________________________________________________

### 6.1. 간선 스택의 불변식 / Edge-stack invariant

**불변식**은 정해진 확인 시점마다 계속 참인 설명이다. 새 트리 간선이나 조상
빽 간선을 처리해 넣은 직후, 또는 한 간선을 꺼내 결과 행에 기록한 직후를 확인한다.
An **invariant** stays true at each checkpoint: just after pushing a newly
handled tree/ancestor pair, or after popping and storing one result pair.

**한 번 처리한 각 undirected 간선은 대기 스택 또는 결과 그룹 중 정확히 한 곳에
한 번만 있다.** 아직 꺼내는 중인 결과 행에 기록한 간선도 결과에 포함한다.
두 곳은 겹치지 않는다. 스택의 바닥부터 위까지는 아직 배정하지 않은 간선의
처리 순서이고, 꺼낼 때는 그 역순이다. 부모·후손 방향의 반대 항목은 다시 넣지 않는다.
**Every handled undirected edge occurs exactly once, either pending on the
stack or assigned to a block.** Assigned includes pairs already stored in
the row being formed. These sets are disjoint. Bottom to top preserves the
recording order of unassigned pairs; removal reverses it. Reverse parent
and descendant entries never push another copy.

자식이 돌아왔어도 그 아래의 모든 간선이 대기하지는 않는다. 안쪽 그룹은 이미
꺼냈을 수 있다. 부모가 자식의 빽번호를 비교할 때 값이 더 작으면 남겨 두고,
같거나 크면 **아직 배정하지 않은** 맨 위 구간을 부모–자식 경계 간선까지 포함해
꺼낸다. 그 구간이 다음 그룹이다.
A returned subtree may already have emitted inner blocks. After return,
the parent leaves the remaining pairs pending if the child's earliest
number is smaller than the parent's visit number. Otherwise, the next
block is the **unassigned** suffix through and including that child's
boundary pair.

| Checkpoint / 확인 시점 | Handled pairs / 처리한 수 | Pending / 대기 수 | Assigned, including forming row / 결과 수 |
| --- | --- | --- | --- |
| Start extraction / 추출 시작 | 0 | 0 | 0 |
| After 4 returns and its block closes / 4 복귀 후 그룹 완성 | 8 | | |
| After 3 returns to 2 / 3에서 2로 복귀 후 | 10 | | |
| After 2 returns and its block closes / 2 복귀 후 그룹 완성 | 10 | | |

처음에는 왜 참인가? 새 간선 넣기와 꺼내 결과에 기록하기는 왜 이를 유지하는가?
도달한 그룹의 탐색이 끝나 스택이 비면 무엇을 결론낼 수 있는가?
Explain initialization, preservation by push and pop-and-store, and what
an empty stack proves after the reached connected group is fully scanned.

____________________________________________________________________

이 불변식과 저장 용량은 별개다. 실습의 `stack[10]`에는 동시에 대기하는 간선이
10개 이하여야 한다. 간선 기록용 `edges[45]`가 이 조건을 대신하지 않는다.
Capacity is a separate precondition: the lab's `stack[10]` must fit the peak
pending count, even though `edges[45]` can record more connections.

## 7. 5분 회상 / Five-minute retrieval pause

자료를 덮고 세 질문에 답한다. 첫 답을 남기고, 비교 후 수정과 근거를 덧붙인다.
Close the sources. Answer exactly these three targets, retain the first
response, then add corrections and evidence after comparison.

1. 방문 3의 이웃 네 종류를 예로 설명한다. / Give all four neighbor kinds at visit 3.
2. 방문 6의 빽번호와 방문 4의 그룹 경계를 설명한다. / Explain visit 6's earliest number and the boundary at visit 4.
3. 호출이 기억하는 작업과 스택의 대기 간선을 구별한다. / Distinguish call work from pending edge pairs.

First response / 첫 답: ____________________________________________

Correction and evidence / 수정과 근거: ______________________________

## 8. 중간고사 복습 / Midterm review

1. 세 표현에서 노드·간선을 저장하고 추가하고 삭제하는 방법을 설명한다.
   Explain vertex/edge storage, insertion, and deletion in all three representations.
2. 끈끈한 그룹의 정의와 방문 번호·빽번호·스택을 이용해 찾는 방법을 설명한다.
   Define a block and explain how visit numbers, earliest reconnection, and a stack collect it.
3. [5장 트리 복원 / Chapter 5 reconstruction](../../module_05_tree_dfs/student/textbook.md)의
   preorder `ABDECFG`, inorder `DBEAFCG`로 트리를 복원한다. 첫 분할과 postorder를 적는다.
   Reconstruct the tree from those orders; give the first split and resulting postorder.

____________________________________________________________________

## 9. 코딩 활동: 원래 A–J 그래프 / Coding: original A–J graph

여기부터는 [lab.c](lab.c)와 [실습 슬라이드](ppt_lab_material.md)의 C 구현을 읽는다.
강의 실행 파일은 Chapter 3의 초기화 함수로 A–J를 만든다.
From here, read the C implementation in the lab and lab slides. This
lecture driver initializes the original Chapter 3 A–J graph.

```text
A–B, B–C, B–D, B–E, B–F, D–E, D–F, E–F, G–H
I and J are isolated / I와 J는 고립된 노드
A:[B] B:[A,C,D,E,F] C:[B] D:[B,E,F] E:[B,D,F] F:[B,D,E]
G:[H] H:[G] I:[] J:[]
```

`_edge_iteration_()`는 방문·부모를 기록하는 틀이다. `_init_edges_list()`의 자식
분기는 `add_edge(node, adj)`, 부모 설정, 재귀 호출 순서다. `add_edge()`는 이미
존재하는 연결의 기록과 대칭 조회 셀을 만들며, 이웃 목록을 바꾸지 않는다.
The traversal template records discovery/parents. The indexing child
branch records the edge, sets its parent, then recurses. It does not construct adjacency.

`init_edges_list(start_node)`는 방문 시간·번호·부모를 초기화하고, `edges_size`를
0으로 만든다. 활성 `edge_index` 칸을 -1로 채운 뒤 `_init_edges_list()`를 실행한다.
간선 인덱스 0도 유효하므로, 기록하지 않은 연결을 0으로 표시할 수 없다.
The indexing wrapper resets discovery and parents, clears the record count,
fills the active lookup region with -1, then records reached edges. Edge
index 0 is valid, so -1 distinguishes an unrecorded connection.

`find_bcc(start_node)`는 방문 초기화, 빽번호 저장, 스택 초기화, 방문 재초기화,
추출의 다섯 작업을 한다. 저장한 `back_num`은 보존한다. 같은 시작점과 같은
이웃 순서를 사용해야 발견 번호를 재현한다.
Match these five wrapper actions to the final lab slide. Saved low-link
values survive the second discovery reset; extraction must reproduce their numbering.

두 함수를 차례로 부르면 간선 기록, 빽번호 계산, 그룹 추출의 세 탐색을 한다.
추출은 자식 호출 직후 `back_num[adj] < visit_num[node]`이면 대기 간선을 남긴다.
그렇지 않으면 `close_bcc(tree_edge)`가 경계 간선까지 포함해 꺼낸다.
Calling the two wrappers in order gives three passes: indexing, low-link
calculation, and extraction. After a child returns, a strict `<` keeps its
edges pending; otherwise the pop loop includes the boundary tree edge.

[강의 실행 파일 / Lecture driver](../code/lecture/lab_demo.c)는 새 프로세스에서 실행한다.
From `module_06_graph_dfs/code`, predict before running:

```sh
make lecture
```

| Coding evidence / 코딩 근거 | Prediction / 예상 | Output or source check / 출력 또는 소스 확인 | Correction / 수정 |
| --- | --- | --- | --- |
| Reached vertices and discovery / 도달 노드와 발견 번호 | | | |
| Indexed edge records / 기록된 간선 수 | | | |
| Symmetric B–E lookup / B–E 대칭 조회 | | | |
| Low-link values A–F / A–F 빽번호 | | | |
| Result rows and sizes / 결과 행과 크기 | | | |
| Final stack / 최종 스택 | | | |

조회 셀과 중간 스택은 출력하지 않으므로 소스·손 추적 또는 디버거로 확인한다.
The driver does not print lookup cells or intermediate stacks; label those
checks as source, hand trace, or debugger evidence. Resolve result edge indices into endpoint pairs.

Compiler, command, diagnostics / 컴파일러, 명령, 진단: ________________

16개 이웃 항목을 세 번 확인하고, 조회표 100칸을 준비하는 비용을 설명한다.
최대 호출 5개와 대기 간선 7개를 실제 예약 용량과 구별한다. 결과 재호출 시
`current_bcc`가 초기화되지 않는 점을 확인한다.
Explain three passes over 16 neighbor entries and 100 lookup writes.
Distinguish peak calls 5/pending connections 7 from reserved capacities.

현재 배열은 `edges[45]`, `bcc[9][45]`, `bcc_size[9]`이고,
가져온 스택은 `stack[10]`이다. 노드 10개의 단순 undirected graph에는 최대
45개 간선이 있지만, 추출 중 동시에 대기할 간선은 스택의 10칸 안에 들어야 한다.
The current lab reserves 45 edge records and nine result rows of 45 entries,
while the imported stack still holds ten pending indices. Forty-five is
the maximum edge count for ten vertices in a simple undirected graph;
it does not increase the stack's capacity.

Check the missing result reset before reuse. Valid input and fitting
capacities are assumed; globals and stack operations are unchecked.

선택 실험: [슬라이드 실행 파일 / Slide driver](../code/lecture/ppt_demo.c)는
현재 실습 코드에 슬라이드 그래프의 이웃 목록을 따로 제공한다. 저장된 발견·빽번호와
두 개의 다섯 간선 그룹을 위 개념 표와 비교한다. A–J 실행과는 새 프로세스로 구별한다.
내부 배열 칸 0–6에는 A–G를 저장하고, 출력되는 간선 끝점은 실제 방문 번호 1–7이다.
Optional experiment: the slide driver supplies the slide graph to the same
current lab. Compare its numbers and two five-edge groups with the
concept tables. Its internal indices 0–6 contain A–G, but printed endpoint
numbers come from actual visit numbers 1–7. Run it independently from the
original A–J driver.
저장소 루트에서 실행한다. / From the repository root:

```sh
cc -std=c11 -I. module_06_graph_dfs/code/lecture/ppt_demo.c -o /tmp/ppt_demo
/tmp/ppt_demo
```

[검사형 행렬 실습 / Checked matrix exercise](lab.md)은 별도의 과제와 계약을 유지한다.
That exercise retains separate tasks and contracts.

## 10. 미니퀴즈 제출 / Mini-quiz submission

교사가 제공한 미니퀴즈에 답하고 안내된 수업 절차로 제출한다. 제출 전에 방문 3의
이웃 분류, 방문 6의 빽번호, 두 그룹의 끝점 쌍을 자신의 근거와 대조한다.
Complete the instructor's mini-quiz and submit using the classroom
instructions. Before submitting, check your reasoning for visit 3's
neighbor kinds, visit 6's earliest number, and both blocks' endpoint pairs.

문항과 확인 내용 / Questions and checks: ___________________________
