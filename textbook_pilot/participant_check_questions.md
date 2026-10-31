# 참여자용 확인 문제

현재 장을 혼자 읽은 뒤 교재를 닫고 답해요. 진행자가 지정한 장만 봐요. 각 장의 네 문제는 모두 필수예요. 결과와 그렇게 판단한 이유를 함께 설명해요. 정답 기준은 이 파일에 없어요.

## 1장. 고정 배열에 데이터를 모아요

기준 교재: [본문](../module_01_arraylist/student/textbook.md) · [한국어판](../module_01_arraylist/student/textbook_korean.md)

### 확인 1

용량 8, size=3인 배열 리스트에서 현재 값으로 읽을 수 있는 인덱스는 어디까지인가요? 사용하지 않는 칸에 0이 있으면 현재 값인가요?

### 확인 2

고정 배열이 가득 찼을 때 삽입 조건은 어떻게 되고, 기존 값·size·용량은 어떻게 되나요?

### 확인 3

[100,200,300]의 위치 1에 600을 넣을 공간이 있어요. 기존 값은 어느 순서로 옮기고 최종 활성 배열은 무엇인가요?

### 확인 4

교재의 for(index=0; index<size; ...) 검색에서 값이 여러 번 나오면 어느 위치에서 멈추나요? 아무 값도 맞지 않으면 index는 무엇이며 바로 array[index]를 읽어도 되나요?

## 2장. 배열 인덱스로 계층을 만들어요

기준 교재: [본문](../module_02_binary_tree/student/textbook.md) · [한국어판](../module_02_binary_tree/student/textbook_korean.md)

### 확인 1

nodes 배열의 인접한 두 칸이 자동으로 부모와 자식이 되나요? nodes[0].left=1은 무엇을 연결하나요?

### 확인 2

원래 알파벳 트리에서 tree_connect()가 돌려준 root는 무엇인가요? nodes_size가 10이어도 root에서 몇 노드에 도달하며, 나머지 칸은 어떻게 되나요?

### 확인 3

1+2+3의 다섯 문자를 배열에 넣고 연결하면 최종 root와 두 자식은 무엇인가요? 어떤 괄호 묶음이며 eval의 결과는 무엇인가요?

### 확인 4

트리 높이는 무엇을 세나요? F→A→B→D 경로에서 높이와 동시에 남는 호출을 구분하고, 자식 -1에서 재귀가 멈추는 이유를 설명해요.

## 3장. 여러 방향의 관계를 저장해요

기준 교재: [본문](../module_03_graph/student/textbook.md) · [한국어판](../module_03_graph/student/textbook_korean.md)

### 확인 1

방향 간선 A→B가 있으면 B→A도 있나요? 나가는 간선이 없으면 고립 정점인가요?

### 확인 2

원래 무방향 그래프의 아홉 간선은 adjacency list에서 모두 몇 개의 이웃 항목이 되나요? adj_size와 nodes_size는 무엇이 다른가요?

### 확인 3

원래 A–J 그래프에서 연결 요소는 몇 개인가요? I와 J가 각각 요소가 되는 이유와 mark_all_groups 전에 필요한 준비를 말해요.

### 확인 4

save_back_num에서 parent로 되돌아가는 간선과 이미 발견한 조상으로 가는 간선은 어떻게 다루나요? visit_num과 back_num은 왜 같은 DFS 순서에서 계산하나요?

## 4장. 마지막에 넣은 값을 먼저 꺼내요

기준 교재: [본문](../module_04_stack/student/textbook.md) · [한국어판](../module_04_stack/student/textbook_korean.md)

### 확인 1

top=-1인 스택에 100,200,300을 넣으면 top과 데이터 수는 얼마인가요? peek와 pop 뒤 상태는 무엇이 다른가요?

### 확인 2

is_full과 is_empty를 호출하면 잘못된 push나 pop도 자동으로 거부되나요? 유효한 호출을 위해 누가 무엇을 확인하나요?

### 확인 3

1-2*3+4를 postfix로 바꾼 결과와 계산 값은 무엇인가요? 변환 뒤 계산을 시작하기 전에 같은 스택을 어떻게 준비하나요?

### 확인 4

1+(2+3)을 바꿀 때 여는 괄호는 어떤 경계인가요? 변환 결과와 계산 결과, 입력 버퍼 조건을 말해요.

## 5장. depth-first traversal와 수식 트리

기준 교재: [본문](../module_05_tree_dfs/student/textbook.md) · [한국어판](../module_05_tree_dfs/student/textbook_korean.md)

### 확인 1

`tree_traversal(i)`에서 preorder, inorder, postorder 작업은 두 자식 호출의 어디에 놓이나요? 현재 주석만 있는 함수를 실행하면 방문 순서가 저장되나요?

### 확인 2

`tree_traversal_proceed()`는 왜 자식을 넣기 전에 `progress[i]++`를 하나요? 같은 트리를 다시 순회할 때 `tree_traversal_with_stack()`가 초기화하는 상태와 호출자가 초기화할 상태는 무엇인가요?

### 확인 3

postfix `123*-4+`로 트리를 만들 때 연산자는 어느 자식부터 꺼내나요? 마지막 root 인덱스, 그 root의 두 자식 인덱스, `nodes_size`, `top`은 무엇인가요?

### 확인 4

왼쪽 연산자 자식과 오른쪽 연산자 자식을 괄호로 묶는 우선순위 조건은 각각 무엇인가요? `write_infix()`가 출력 위치를 재설정하는 시점과 문자열을 끝내는 방법도 설명해요.

## 6장. undirected graph DFS와 BCC 간선 스택

기준 교재: [본문](../module_06_graph_dfs/student/textbook.md) · [한국어판](../module_06_graph_dfs/student/textbook_korean.md)

### 확인 1

단순 undirected graph에서 간선 하나는 이웃 목록에 두 번 나타나요. `init_edges_list()`는 tree edge와 back edge를 각각 언제 기록하고, 어느 두 경우를 건너뛰어 중복을 막나요?

### 확인 2

`edge_index[u][v]`는 무엇을 저장하나요? `edge_index[v][u]`와 같은 값을 갖는 이유와, 일반 adjacency matrix가 답하는 질문과의 차이를 설명해요.

### 확인 3

BCC 추출 중 자식 `adj`에서 돌아왔을 때 `back_num[adj] < visit_num[node]`이면 왜 스택을 남기나요? 반대 경우에는 어느 간선까지 꺼내며, 처리한 간선의 불변식은 무엇인가요?

### 확인 4

새 프로그램에서 같은 시작 정점과 같은 이웃 순서로 `init_edges_list(start)` 다음 `find_bcc(start)`를 불러요. 여러 DFS pass의 순서를 맞춰야 하는 이유는 무엇인가요? 이 호출이 다른 연결 요소와 이전 BCC 결과까지 자동 처리하나요?

## 7장. 연결 리스트와 공유 노드 풀

기준 교재: [본문](../module_07_linked_list/student/textbook.md) · [한국어판](../module_07_linked_list/student/textbook_korean.md)

### 확인 1

`new_lnode()`는 인수와 반환값을 어떻게 사용하나요? 성공 직후 `data`, `next`, `free_head`는 어떻게 되며, 빈 칸이 없으면 무엇이 바뀌나요?

### 확인 2

`simple_link_lnode_to_prev(prev,node)`는 왜 새 노드에 옛 후속 인덱스를 먼저 저장하나요? `simple_delink_next_lnode_from_prev(prev)` 성공 뒤 반환 노드의 `next`와 소유 상태는 무엇인가요?

### 확인 3

노드가 사용 중일 때 `init_lnodes_pool()`를 다시 부르면 무엇이 되나요? 분리한 노드를 돌려주지 않거나 두 번 돌려주거나, 반환한 옛 인덱스로 계속 쓰면 각각 어떤 문제가 생기나요?

### 확인 4

연결 Stack과 연결 Queue는 어느 끝에서 넣고 빼나요? 이 장의 `dequeue_lnode()`가 반환하는 수, 호출자의 후속 작업, 마지막 삭제 뒤 `qhead`와 `qtail`을 설명해요. payload `-1`도 저장할 수 있나요?

## 8장. 큐 비교와 트리·미로 BFS

기준 교재: [본문](../module_08_graph_bfs/student/textbook.md) · [한국어판](../module_08_graph_bfs/student/textbook_korean.md)

### 확인 1

8장의 `queue.c`가 정의한 `enqueue(value)`와 `dequeue()`는 7장의 raw 노드 연산에 어떤 작업을 더하나요? payload `-1`과 빈 큐는 어떻게 구분하나요?

### 확인 2

`queue[25]`의 선형 큐와 원형 큐는 읽은 칸을 어떻게 다르게 사용하나요? 원형 큐가 24개만 저장하는 이유와 empty/full 조건을 적어요.

### 확인 3

F가 root인 교재 트리에서 왼쪽 자식부터 넣는 BFS의 처리 순서와 최대 대기 수는 무엇인가요? 같은 코드를 일반 그래프에 쓰면 발견 기록이 추가로 필요한 이유는 무엇인가요?

### 확인 4

원래 미로의 `{1,1}` BFS에서 목적지 `{5,5}`의 거리와 저장된 두 선행 칸은 무엇인가요? 선행 칸 두 개가 전체 경로 두 개를 뜻하나요? 발견 기록은 enqueue 전후 언제 쓰나요?

## 9장. 서로 다른 두 위치의 합을 찾는 Hash Table

기준 교재: [본문](../module_09_hash_table/student/textbook.md)

### 확인 1

hash_func(-16), hash_func(-8), hash_func(4)는 각각 어느 bucket을 고르는가? -16과 4가 같은 bucket을 골라도 같은 값이라고 할 수 없는 이유는 무엇인가?

### 확인 2

새 실행에서 별도 초기화 없이 save_data(2,12), save_data(2,22), save_data(2,-8)을 순서대로 호출했다. bucket 2의 노드 순서와 free_head는 무엇인가? 이어서 init_lnodes_pool()을 호출하면 무엇이 바뀌는가?

### 확인 3

nums={-16,-8,-4,-2,-1,1,2,4,8,16}, target=0일 때 two_sum_ht는 어떤 answer를 남기는가? 현재 위치를 저장하기 전에 complement를 찾는 이유와 성공 후 table에 남는 노드 수도 설명하라.

### 확인 4

init_hashtable()은 사용한 노드를 어떻게 재사용 가능하게 만드는가? pool이 소진된 save_data와 그 실패를 만난 two_sum_ht는 어떤 결과를 남기는가?

## 10장. 정수 Heap과 장치들의 공통 켜짐 시각

기준 교재: [본문](../module_10_binary_heap/student/textbook.md) · [한국어판](../module_10_binary_heap/student/textbook_korean.md)

### 확인 1

최소 모드에서 7,3,5,1,9,4를 차례로 add한 live 배열은 무엇인가? 여기서 remove_root가 돌려주는 값과 제거 뒤 배열을 쓰고, 배열 전체가 정렬될 필요가 없는 이유를 설명하라.

### 확인 2

최소 Heap [1,3,4,7,9,5]에서 update_value(4,0), update_value(0,8)을 차례로 호출하면 각 배열은 무엇인가? i의 의미와 복구 방향 선택도 설명하라.

### 확인 3

장치 0의 구간은 [1,3],[7,10], 장치 1은 [2,5],[8,12], 장치 2~9는 각각 [4,9]다. 최초의 L과 R, 진행시키는 ID 순서, all_on_time()의 반환값을 쓰라. L==R이면 성공하는가?

### 확인 4

시간표 검색은 왜 ID Heap 두 개와 역위치 배열 두 개를 쓰는가? 한 장치의 epoch를 바꾼 뒤 무엇을 복구하며, 교환 때 역위치를 갱신하지 않으면 다음 변경에서 어떤 문제가 생기는가?

## 11장. Indexed Heap으로 찾는 최소 비용 경로

기준 교재: [본문](../module_11_graph_dijkstra/student/textbook.md)

### 확인 1

A→E의 비용이 14이고 A→C→D→E의 비용이 2+2+2일 때, BFS의 최소 연결 수와 최소 비용 답이 다른 이유는 무엇인가? node_dist의 -1과 source의 0은 각각 무엇을 뜻하는가?

### 확인 2

heap=[3,4,1], 해당 ID들의 node_dist가 각각 4,14,5인 live 상태에서 root가 가리키는 정점과 node_heap_pos[1]은 무엇인가? heap의 위치와 정점 ID를 구별하고 swap이 유지해야 하는 식을 쓰라.

### 확인 3

정점은 A=0부터 F=5다. 간선은 A→B9,C2,E14; B→D1,E8; C→B3,D2; D→E2이며 E,F의 outgoing edge는 없다. A에서 시작해 C의 간선을 처리한 뒤 A~F의 node_dist와 live Heap은 무엇인가? B의 개선에 새 복사본을 넣는가?

### 확인 4

이 lab은 왜 found를 읽지 않고도 제거된 정점의 비용을 확정할 수 있는가? 제거 뒤 node_heap_pos[v]!=-1을 membership 검사로 써도 되는지와 올바른 실행의 가정을 설명하라.

## 12장. 문자 키의 BST 순서를 보존하는 AVL 회전

기준 교재: [본문](../module_12_bst_avl/student/textbook.md)

### 확인 1

A~G를 ABCDEFG 순서로 만든 일반 BST와 DBFACEG 순서로 만든 일반 BST에서 G를 찾을 때 각각 몇 노드를 비교하는가? 같은 키를 저장해도 경로가 달라지는 이유는 무엇인가?

### 확인 2

빈 부분과 leaf의 높이는 각각 얼마인가? C,B,A를 새 ID로 삽입할 때 어느 회전이 일어나며, 결과 root 키·두 자식 키·높이는 무엇인가?

### 확인 3

rotate_ll(i,l,lr)에서 l의 오른쪽 부분 lr를 왜 i의 왼쪽으로 옮기는가? 회전 뒤 저장 높이를 어떤 순서로 갱신하고 _add의 반환값은 어디에 저장해야 하는가?

### 확인 4

새 키가 기존 키와 같으면 _add는 어느 쪽으로 내려가는가? 회전이 끝난 뒤 같은 키는 반드시 왼쪽에만 있는가? 새 ID의 중복 키 삽입과 이미 연결된 ID의 재삽입도 구별하라.

## 13장. 탐색 위치와 정렬의 준비 비용

기준 교재: [본문](../module_13_search_sort_consolidation/student/textbook.md) · [한국어판](../module_13_search_sort_consolidation/student/textbook_korean.md)

### 확인 1

원래 배열 [31,23,17,8,17,42]의 linear_search(17)과 정렬된 [8,17,17,23,31,42]의 binary_search_first(17)은 각각 어떤 위치를 반환하는가? 두 위치가 달라도 오류가 아닌 이유는 무엇인가?

### 확인 2

정렬된 여섯 값에서 17을 찾을 때 [lo,hi)와 mid는 어떻게 변하는가? 같은 값을 찾았을 때 바로 반환하지 않는 이유와 99 검색에서 sorted[6]을 읽지 않는 이유도 설명하라.

### 확인 3

같은 여섯 값의 insertion sort에서 오른쪽 이동은 총 몇 번인가? 원래의 두 17을 17A,17B로 표시할 때 순서가 유지되는 비교 조건은 무엇인가? merge sort는 같을 때 어느 쪽을 택하는가?

### 확인 4

merge_sort의 scratch에는 어떤 조건이 필요한가? 한 번의 작은 검색과 변경 없는 같은 자료에 대한 많은 검색에서 정렬의 준비 비용을 어떻게 따로 판단해야 하는가?

## 14장. DSU로 연결을 판단하는 Kruskal

기준 교재: [본문](../module_14_prim_kruskal/week_14/textbook.md)

### 확인 1

A=0부터 H=7로 두고 A–B,C–D,A–C,E–F,G–H,E–G,A–E를 순서대로 union했다. 교재의 parent는 A,A,A,C,A,E,E,G다. H의 find 경로와 압축 후 바뀌는 parent, root의 size와 component_count를 쓰라.

### 확인 2

union by size는 서로 다른 두 root를 어떻게 연결하는가? 같은 size일 때의 규칙, 같은 root를 다시 union한 결과, root와 nonroot의 component_size 조건을 설명하라.

### 확인 3

A–B(1),B–C(2),A–C(3),C–D(4)를 이 순서로 검사한다. Kruskal은 어떤 간선을 채택하며 A–C를 건너뛰는 근거는 무엇인가? 결과 비용과 간선 수도 쓰라.

### 확인 4

Kruskal 결과에서 accepted forest와 DSU 집합은 어떤 관계인가? V개 정점과 c개 component의 결과 간선 수, 음수 가중치 허용 여부, 이번 주 Prim의 역할을 설명하라.
