# Chapter 6 Class Workbook / 제6장 수업 활동 — 그래프의 연결 묶기

이름 / Name: ____________________  날짜 / Date: ____________________

[영문 교재 / English textbook](textbook.md)와 [한글 교재 / Korean textbook](textbook_korean.md)의 일곱 절 순서로 진행한다. 먼저 예상하고, 확인한 뒤 수정과 근거를 덧붙인다. 표는 같은 항목을 가진 번호 목록으로 답해도 된다.
Follow the textbooks' seven sections. Preserve predictions, then add corrections with evidence. A numbered list with the same fields may replace any table.

[개념 슬라이드 / Concept slides](ppt_material.md)와 [실습 슬라이드 / Lab slides](ppt_lab_material.md)는 해당 질문을 설명할 때 함께 참고한다. 이 활동의 개념 예제는 방문 번호 1–7의 그래프다. C 활동의 A–J 그래프는 별도 예제다.
Use the slides alongside the matching questions. Keep the numbered conceptual graph separate from the alphabet graph used by the C lab.

## 1. 논리적으로 생각해 보기 / Thinking logically

### 연결을 어떻게 저장하고 탐색할까? / How do we store and explore connections?

개념 그림의 1–7은 정해진 DFS가 끝난 뒤의 방문 번호다. 방문 1에서 시작하여 아래 이웃 순서로 탐색을 되짚는다. 탐색 중에는 처음 도달할 때에만 번호를 붙인다.
The numbers identify vertices by the completed DFS visit order. Replay from visit 1 in the neighbor order below; assign each number only on first entry.

```text
Edges / 간선:
1–2, 1–3, 2–3, 2–7, 3–4, 3–6, 3–7, 4–5, 4–6, 5–6

1:[2,3]       2:[1,3,7]     3:[1,2,4,6,7]
4:[3,5,6]     5:[4,6]       6:[3,4,5]     7:[2,3]
```

3장의 이웃 목록을 복습한 뒤, 간선 목록과 인접 행렬을 비교한다. 3–6은 이미 있으므로, 추가 실험에서는 아직 없는 1–7을 사용한다.
Review Chapter 3's adjacency lists, then compare edge lists and adjacency matrices. Edge 3–6 already exists; use the absent edge 1–7 for the insertion question.

각 편집 질문은 별도로 생각하고, 이후 DFS 추적에는 원래 그래프를 사용한다.
Treat each editing question independently; use the original graph for the DFS trace below.

| Representation / 표현 | Store 3–6 / 3–6 저장 | Add 1–7 / 1–7 추가 | Delete 3–6 / 3–6 삭제 |
| --- | --- | --- | --- |
| Neighbor lists / 이웃 목록 | | | |
| Edge list / 간선 목록 | | | |
| Adjacency matrix / 인접 행렬 | | | |

노드 7을 삭제하면 어떤 간선과 참조를 없애야 할까? 간선 기록이 이동하면 조회표는 어떻게 바꿀까?
Which edges and references disappear when vertex 7 is removed? What lookup entries must change if edge records move?

예상과 수정 / Prediction and correction: ___________________________

### 방문 3의 이웃을 어떻게 구별할까? / How do we classify vertex 3's neighbors?

각 이웃을 실제로 확인하는 시점에 분류한다. 방문 번호는 배열 인덱스와 다르다.
Classify each neighbor at the time it is examined. A visit number differs from a storage index.

| Encounter / 확인 | Kind / 종류 | Explore again? / 다시 탐색? | Evidence / 근거 |
| --- | --- | --- | --- |
| 3 → 1 | | | |
| 3 → 2 | | | |
| 3 → 4 | | | |
| 3 → 6, after 4 returns / 4 복귀 후 | | | |
| 3 → 7 | | | |

부모를 조상 빽 간선보다 먼저 구별하는 이유를 설명한다. preorder, 자식 복귀 직후, postorder에 각각 어떤 작업을 하는가?
Explain why the parent case comes before the ancestor-back-edge case. Identify work at preorder, immediately after a child returns, and at postorder.

____________________________________________________________________

### 간선을 한 번씩 기록하려면? / How do we record each edge once?

트리 간선은 자식에 들어가기 전에, 빽 간선은 후손에서 조상으로 읽을 때 기록한다. 기록 순서를 방향을 포함해 적는다. 입력의 연결 자체는 무방향이다.
Write the recording order with directions: tree edges before child entry, back edges toward ancestors. The input connections remain undirected.

열 개 기록 / Ten records: __________________________________________

3–6과 6–3의 조회 결과가 같아야 하는 이유와 기록 없음 표시가 `-1`인 이유는?
Why must 3–6 and 6–3 find the same record, and why is the missing-record marker `-1`?

____________________________________________________________________

### 빽 번호는 어디까지 되돌아갈 수 있음을 나타낼까? / How far back can a branch reconnect?

자신의 방문 번호로 시작한다. 조상 빽 간선에서는 조상의 방문 번호를, 자식 복귀 후에는 자식의 빽 번호를 비교하여 더 작은 값을 남긴다.
Start with the vertex's own visit number. Compare ancestor visit numbers along back edges and completed child low-link values after return; keep the smaller value.

| Visit / 방문 | Parent visit / 부모 방문 | Low-link / 빽 번호 |
| --- | --- | --- |
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |
| 7 | | |

방문 6에서 이웃 3과 4를 처리하면 값이 어떻게 바뀌는가? 그 값이 5와 4로 돌아가는 과정을 설명한다.
How do neighbors 3 and 4 affect vertex 6's value? Explain how the result returns through 5 and 4.

____________________________________________________________________

### 어느 간선을 한 블록으로 묶을까? / Which edges form a block?

세 노드 이상인 블록에서는 어느 두 노드 사이에도 내부 노드를 공유하지 않는 두 경로가 있다. 이런 성질을 가진 최대 그룹을 찾는다. 다리 간선은 하나의 간선 블록이 될 수 있다.
A block with at least three vertices has two internally vertex-disjoint paths between every pair. Find maximal groups with that property. A bridge can form a single-edge block.

두 블록의 간선과 공유하는 노드를 예상한다. 3–6의 두 경로를 예로 들고, 노드 3을 제거하면 무엇이 분리되는지 설명한다.
Predict both blocks and their shared vertex. Give two paths between 3 and 6, then explain what separates when vertex 3 is removed.

____________________________________________________________________

아래의 복귀 행은 부모가 자식의 빽 번호를 비교한 뒤의 상태다. 스택은 바닥부터 맨 위까지, 완성된 블록은 꺼낸 순서대로 적는다.
Return rows show the state after the parent's comparison. List the stack bottom to top and completed blocks in pop order.

| Event / 시점 | Pending edges / 대기 간선 | New block / 새 블록 |
| --- | --- | --- |
| Scan 6 → 4, after 6 → 3 / 6 → 3 다음 | | |
| Return 6 → 5 / 복귀 | | |
| Return 5 → 4 / 복귀 | | |
| Return 4 → 3 / 복귀 | | |
| Scan 7 → 2 / 확인 | | |
| Return 7 → 3, then 3 → 2 / 복귀 | | |
| Return 2 → 1 / 복귀 | | |

`low[child] >= visit[parent]`에서 같은 경우도 닫는 이유는? 경계 트리 간선을 포함해야 하는 이유는?
Why does equality close a block, and why must the pop include the boundary tree edge?

____________________________________________________________________

## 2. 효율 계산해보기 / Calculating efficiency

### 저장 공간 / Storage

이웃 목록, 간선 목록, 인접 행렬의 저장 공간을 비교한다. 실습이 예약한 `edges[45]`, `edge_index[10][10]`, `bcc[9][45]`, `bcc_size[9]`를 실제 사용한 칸 수와 구별한다.
Compare neighbor-list, edge-list, and matrix storage. Distinguish the lab's reserved arrays from the entries used in this run.

____________________________________________________________________

### 탐색 중 저장 공간 / Traversal memory

개념 예제에서 가장 깊은 호출 경로와 가장 많은 대기 간선을 적는다. 재귀 호출의 저장 공간과 간선 스택의 목적을 구별한다. `edges[45]`가 있어도 `stack[10]`에 한계가 있는 이유는?
Give the deepest call path and peak pending stack. Distinguish saved call work from pending edges. Why does `edges[45]` not enlarge `stack[10]`?

____________________________________________________________________

### 항목 추가 / Adding an item

여유 공간이 있을 때 한 간선 기록과 두 조회 셀을 쓰는 비용은? 새 노드의 행렬 행과 열을 초기화하는 비용은?
With available capacity, what is the cost of writing one record and its two lookup cells? What is the cost of initializing a new vertex's matrix row and column?

____________________________________________________________________

### 탐색 작업 / Traversal work

| Seven-vertex example / 7노드 예제 | Count / 횟수 |
| --- | --- |
| Vertex entries per pass / 한 번의 탐색에서 노드 진입 | |
| Neighbor inspections per pass / 한 번의 이웃 확인 | |
| Vertex entries across three passes / 세 번의 노드 진입 | |
| Neighbor inspections across three passes / 세 번의 이웃 확인 | |
| Lookup cells initialized / 조회표 초기화 칸 | |

탐색은 `O(R + E_R)`인데 전체 과정은 왜 `O(V² + E_R)`인가?
Why is one traversal `O(R + E_R)` while the full process is `O(V² + E_R)`?

____________________________________________________________________

## 3. 용어 정리 / Glossary

교재의 용어 정의를 자신의 말로 설명한다. 각 쌍이 같은 뜻이 아닌 이유를 예로 든다.
Explain these terms in your own words, using one example to distinguish each pair.

1. 방문 번호와 배열 인덱스 / Visit number and array index
2. 트리 간선과 빽 간선 / Tree edge and back edge
3. 인접 행렬과 간선 조회표 / Adjacency matrix and edge lookup
4. 연결 요소와 블록 / Connected component and block
5. 절단점과 다리 간선 / Cut vertex and bridge
6. 호출 스택과 대기 간선 스택 / Call stack and pending-edge stack

설명 / Explanations: _______________________________________________

## 4. 규칙 / Invariant

### 어떤 규칙이 유지되어야 할까? / What must remain true?

새 간선을 넣은 직후 또는 한 간선을 꺼내 결과에 기록한 직후, 처리한 각 간선은 스택 또는 결과 중 정확히 한 곳에 한 번만 있어야 한다. 작성 중인 결과 행도 포함한다.
After each push or completed pop-and-store step, every handled edge appears once, either pending or assigned. Assigned includes the row being filled.

| Checkpoint / 확인 시점 | Handled / 처리 | Pending / 대기 | Assigned / 결과 |
| --- | --- | --- | --- |
| Start / 시작 | 0 | 0 | 0 |
| First pop stored / 첫 pop을 기록한 후 | 8 | | |
| First block completed / 첫 블록 완성 | 8 | | |
| After 3 returns to 2 / 3에서 2로 복귀 후 | 10 | | |
| Finished / 종료 | 10 | | |

### 규칙을 지키면 무엇이 좋을까? / What does the rule guarantee?

방문 4의 postorder에서, 부모 3이 비교하기 전의 스택을 경계 3–4 아래와 위로 나눈다. 어느 구간이 들어온 부모 간선과 같은 최종 블록에 속하는가? 방문 3의 구간은 왜 그 블록 전체가 아닌가?
At vertex 4's postorder, before parent 3 compares, split the stack at 3–4. Which suffix belongs with the incoming edge? Why is vertex 3's suffix only part of its eventual block?

____________________________________________________________________

### 규칙이 깨지면 어떻게 될까? / What if a rule breaks?

반대 방향을 다시 넣기, 경계 간선을 빼고 꺼내기, 빽 번호 저장 뒤 이웃 순서 바꾸기 중 하나를 선택해 잘못된 결과를 설명한다. 마지막 스택이 비어 있다는 사실만으로 충분한가?
Choose duplicate pushing, excluding the boundary edge, or changing neighbor order after saving low-links. Explain the failure. Is an empty final stack sufficient evidence?

____________________________________________________________________

### 규칙을 어떻게 지킬까? / How do we preserve the rules?

초기화, 한 번씩 넣기, 꺼낸 즉시 결과에 기록하기, 경계 포함하기, 같은 root와 이웃 순서 사용하기가 각각 어떤 규칙을 지키는지 연결한다.
Match initialization, once-only pushes, pop-and-store, inclusive boundaries, and unchanged root/order to the rules they preserve.

____________________________________________________________________

## 5. 코딩 계획 / Coding plan

이제 [C 실습](lab.c)의 별도 A–J 예제로 전환한다. 간선은 A–B, B–C, B–D, B–E, B–F, D–E, D–F, E–F, G–H이며 I/J는 고립되어 있다. A에서 시작하면 A–F만 도달한다.
Switch to the lab's separate A–J graph with these nine edges and isolated I/J. Starting at A reaches only A–F.

1. 그래프와 스택 저장 공간을 준비한다. / Prepare graph and stack storage.
2. 방문과 부모를 초기화하고 도달 간선을 한 번씩 기록한다. / Reset visits/parents and index reached edges once.
3. 새 탐색에서 빽 번호를 저장한다. / Save low-link values in a fresh DFS.
4. 스택과 방문 상태를 초기화하되 빽 번호는 보존한다. / Reset pending/visit state while keeping low-links.
5. 같은 순서로 탐색하고 자식 복귀 후 블록을 닫는다. / Replay the same order and close blocks after child returns.
6. 결과 행의 간선 인덱스를 끝점으로 바꾸어 읽는다. / Resolve result edge indices into endpoints.

`init_edges_list()`와 `find_bcc()`에 위 단계를 연결한다. 왜 탐색은 세 번인가? `init_visit()`가 보존하는 상태와 재호출 전에 별도로 관리할 결과 상태는?
Map these steps to the two wrappers. Why are there three passes? Which state survives `init_visit()`, and which result state needs explicit management before reuse?

____________________________________________________________________

## 6. 새로운 C 문법 설명 / New C syntax explained

| Expression / 문장 | Explain the value and effect / 값과 효과 설명 |
| --- | --- |
| `edge_index[u][v]` and `bcc[row][pos]` | |
| `visit_num[node] = ++visit_time` | |
| `int index = edges_size++` | |
| `back_num[i] = visit_num[i] = ++visit_time` | |
| `continue;` after a child's return | |
| `bcc[cur][pos++] = edge` | |
| `do { ... } while (edge != boundary_edge);` | |
| `#include "module_03_graph/student/lab.c"` | |

`edge`를 `do` 바깥에 선언하는 이유는? 교재의 `save_back_num()` 복습 코드를 다시 정의하면 안 되는 이유는?
Why is `edge` declared outside `do`? Why must the textbook's review copy of `save_back_num()` not be defined again?

____________________________________________________________________

## 7. C 코드 / C code

교재의 코드 순서대로 초기화, 이웃 분류, 간선 저장, 빽 번호, 블록 저장, 그룹 탐색을 읽는다. 각 주석을 해당 조건이나 저장 상태와 연결한다.
Read initialization, classification, edge storage, low-link review, block storage, and grouping in textbook order. Connect each comment to the condition or state it explains.

새 프로세스에서 예상한 뒤 실행한다. 저장소 루트에서:
Predict first, then run each driver in a fresh process. From the repository root:

```sh
make -C module_06_graph_dfs/code lecture lecture-ppt
```

| A–J coding evidence / A–J 코딩 근거 | Prediction / 예상 | Output or source check / 출력 또는 소스 확인 | Correction / 수정 |
| --- | --- | --- | --- |
| Reached vertices and discovery / 도달 노드와 방문 번호 | | | |
| Edge records / 간선 기록 | | | |
| Symmetric B–E lookup / B–E 대칭 조회 | | | |
| Low-link values A–F / A–F 빽 번호 | | | |
| Result rows and lengths / 결과 행과 길이 | | | |
| Final stack / 최종 스택 | | | |

드라이버가 출력하지 않는 조회 셀이나 중간 스택은 소스·손 추적·디버거 근거로 표시한다. 두 번째 드라이버는 내부 인덱스 0–6에 A–G를 저장하고, 개념 그래프의 실제 방문 번호 1–7로 끝점을 출력한다.
Label lookup or intermediate-stack checks as source, hand-trace, or debugger evidence. The second driver uses internal indices 0–6 with A–G data and prints actual visit-number endpoints for the conceptual graph.

컴파일러, 명령, 진단 / Compiler, command, diagnostics: ________________

자료를 덮고 세 가지를 설명한다: 방문 3의 이웃 분류, 방문 4에서 같은 값으로 블록을 닫는 이유, 호출과 간선 스택이 기억하는 작업. 첫 답을 보존하고 수정 근거를 적는다.
Close the sources and explain three targets: vertex 3's neighbor cases, equality closing at vertex 4, and the work saved by calls versus the edge stack. Preserve the first response and add evidence for corrections.

첫 답과 수정 / First response and correction: _______________________

[검사형 행렬 실습 / Checked matrix exercise](lab.md)은 별도의 과제와 계약을 유지한다. 추가로 지정된 5장 트리 복원이나 미니퀴즈는 교사의 수업 안내에 따라 진행한다.
The checked matrix exercise retains its separate tasks and contracts. Any assigned Chapter 5 reconstruction review or mini-quiz follows the instructor's classroom instructions.
