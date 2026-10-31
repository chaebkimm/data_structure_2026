# 참여자용 바꾼 예

현재 장의 확인 문제 첫 답을 모두 잠근 뒤 진행자가 지정한 장의 예 하나를 풀어요. 결과와 이유를 함께 설명해요. 각 예는 별도의 새 실행을 기준으로 하며 앞 예의 상태를 이어받지 않아요. 정답 기준은 이 파일에 없어요.

## 1장. 고정 배열에 데이터를 모아요

기준 교재: [본문](../module_01_arraylist/student/textbook.md) · [한국어판](../module_01_arraylist/student/textbook_korean.md)

고정 int array[10]의 활성 값이 [1,2,3,4,5,6,7,8,9,10]이고 size=10이에요. 교재의 조건을 지키며 끝에 11을 넣으려 해요. 이어 마지막 항목을 삭제하고 11을 끝에 다시 넣어요. 각 시도의 값·size·용량과 이동한 기존 항목 수는 무엇인가요?

## 2장. 배열 인덱스로 계층을 만들어요

기준 교재: [본문](../module_02_binary_tree/student/textbook.md) · [한국어판](../module_02_binary_tree/student/textbook_korean.md)

별도의 새 실행에서 eq_plus_init() 안의 지역 문자열 eq를 "4+5+6"으로 바꿨다고 생각해요. eq_size=5는 유지해요. eq_plus_init()과 eq_plus_connect() 뒤 root, root의 left/right, nodes_size, eval(root)의 결과는 무엇인가요? 알파벳 예를 먼저 실행했다면 그 트리도 보존되는지 설명해요.

## 3장. 여러 방향의 관계를 저장해요

기준 교재: [본문](../module_03_graph/student/textbook.md) · [한국어판](../module_03_graph/student/textbook_korean.md)

활성 정점이 0–4인 새 무방향 그래프에 간선 {1,4} 하나만 넣어요. adjacency list와 adj_size에서 바뀌는 부분, 이웃 항목 총수, 연결 요소 수는 무엇인가요? 간선에 없는 정점도 남겨야 하는 이유를 설명해요.

## 4장. 마지막에 넣은 값을 먼저 꺼내요

기준 교재: [본문](../module_04_stack/student/textbook.md) · [한국어판](../module_04_stack/student/textbook_korean.md)

4*2+3을 숫자 스택과 연산자 스택으로 직접 계산해요. +를 읽을 때 먼저 할 일과 최종 상태는 무엇인가요? 이어 실제 lab.c처럼 postfix 변환과 계산을 나눌 때 postfix와 eval_postfix() 반환 뒤 top을 말해요.

## 5장. depth-first traversal와 수식 트리

기준 교재: [본문](../module_05_tree_dfs/student/textbook.md) · [한국어판](../module_05_tree_dfs/student/textbook_korean.md)

새 프로그램에서 현재 `lab.c`를 포함하고 다음을 실행해요. 입력은 유효하며 배열 용량 안에 들어가요. `root`와 두 자식 인덱스, `infix`, `nodes_size`, 마지막 `top`, `progress[0..4]`는 무엇인가요? 같은 root를 다시 반복 순회하기 전에 무엇을 해야 하나요?

```c
strcpy(postfix, "94-2*");
int root = build_tree_from_postfix();
write_infix(root);
memset(progress, 0, sizeof progress);
tree_traversal_with_stack(root);
```

`strcpy`와 `memset`은 `<string.h>`에서 가져와요.

## 6장. undirected graph DFS와 BCC 간선 스택

기준 교재: [본문](../module_06_graph_dfs/student/textbook.md) · [한국어판](../module_06_graph_dfs/student/textbook_korean.md)

새 프로그램의 현재 `lab.c`에서 정점 0..3만 사용하도록 `nodes_size=4`로 두고, 이웃 목록을 아래 순서로 직접 설정해요. 원래 알파벳 예제 초기화 함수는 부르지 않아요. 간선은 단순 undirected graph예요.

```text
0: 1, 2
1: 0, 2, 3
2: 1, 0
3: 1
```

`init_edges_list(0); find_bcc(0);` 뒤 discovery 번호, low-link 값, `edges`의 기록 방향, 완성된 BCC 행의 간선 인덱스, 마지막 `top`은 무엇인가요? 각 블록이 닫힐 때 경계 간선을 왜 포함해 꺼내는지도 설명해요.

## 7장. 연결 리스트와 공유 노드 풀

기준 교재: [본문](../module_07_linked_list/student/textbook.md) · [한국어판](../module_07_linked_list/student/textbook_korean.md)

새 프로그램에서 아래 `lab.c`는 7장의 현재 소스예요. 모든 할당은 성공해요. 삭제 직후 `a`의 연결, `removed`, `lnodes[removed].next`, `free_head`는 무엇인가요? 이어 재할당한 `r`, raw dequeue의 `out`과 `value`, 마지막 `a`의 연결, `qhead`, `qtail`, `free_head`를 적어요. 어느 줄이 노드를 실제로 재사용 가능하게 만드는지도 설명해요.

```c
#include "lab.c"

int main(void) {
    int a = new_lnode();
    int b = new_lnode();
    int c = new_lnode();
    if (a == -1 || b == -1 || c == -1) return 1;
    lnodes[a].data = 40;
    lnodes[b].data = 60;
    lnodes[c].data = 50;
    simple_link_lnode_to_prev(a, b);
    simple_link_lnode_to_prev(a, c);
    int removed = simple_delink_next_lnode_from_prev(a);
    /* 이 지점의 상태도 답해요. */
    free_lnode(removed);
    int r = new_lnode();
    if (r == -1) return 1;
    lnodes[r].data = 90;
    enqueue_lnode(r);
    int out = dequeue_lnode();
    if (out == -1) return 1;
    int value = lnodes[out].data;
    free_lnode(out);
    return value != 90;
}
```

## 8장. 큐 비교와 트리·미로 BFS

기준 교재: [본문](../module_08_graph_bfs/student/textbook.md) · [한국어판](../module_08_graph_bfs/student/textbook_korean.md)

새 프로그램에서 8장의 현재 미로 `lab.c`를 포함해요. 아래 7×7 배열로 `maze`를 바꾼 뒤 `init_lnodes_pool(); qhead=qtail=-1; init_info();`를 실행하고 `bfs((struct point){1,1})`를 불러요. 다른 구조는 풀을 사용하지 않아요. 이웃 순서는 오른쪽, 왼쪽, 아래, 위예요. 목표 `{2,2}`의 거리, `prev`의 활성 내용과 순서, 최단 경로 수, 큐의 최대 대기 수와 마지막 두 끝을 적어요. 모든 큐 칸이 재사용 가능해지는 이유도 설명해요. 다른 fixture는 새 프로그램에서 시작하거나 모든 소유 노드를 먼저 반환해야 하며 초기화 함수 재호출만으로 풀을 재설정할 수 없어요.

```text
0 0 0 0 0 0 0
0 1 1 0 0 0 0
0 1 1 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
0 0 0 0 0 0 0
```

위 표는 행 y, 열 x 순서예요. 큐에는 `7*y+x`인 data ID를 넣어요.

## 9장. 서로 다른 두 위치의 합을 찾는 Hash Table

기준 교재: [본문](../module_09_hash_table/student/textbook.md)

독립 실행마다 table이 비어 있고 열 노드가 모두 사용 가능하다고 하자. nums={2,2,7,0,0,0,0,0,0,0}, target=9다. two_sum_bf는 앞선 j를 작은 순서로 검사하고, two_sum_ht는 현재 위치를 저장하기 전에 찾으며 새 후보를 chain 앞에 붙인다. 각 함수가 처음 반환하는 두 위치를 쓰고 결과가 달라도 옳은 이유를 설명하라.

## 10장. 정수 Heap과 장치들의 공통 켜짐 시각

기준 교재: [본문](../module_10_binary_heap/student/textbook.md) · [한국어판](../module_10_binary_heap/student/textbook_korean.md)

열 장치의 닫힌 구간을 사용한다. 장치 0은 [1,4],[9,12], 장치 1은 [5,8],[10,13], 장치 2~9는 각각 [3,11]이다. 각 단계의 L,R과 진행 ID를 추적해 최초 공통 시각을 구하라. 장치 2~9의 구간만 각각 [10,10]으로 바꿔 새 all_on_time() 호출을 시작하면 결과는 무엇인가?

## 11장. Indexed Heap으로 찾는 최소 비용 경로

기준 교재: [본문](../module_11_graph_dijkstra/student/textbook.md)

A=0,B=1,C=2,D=3인 directed graph를 새로 준비했다. 간선은 A→B8,C2; C→B3,D7; B→D1이며 D에는 outgoing edge가 없다. A에서 현재 lab의 min_dist를 실행한다. 정점 제거 순서, 최종 A~D 비용, update_value 호출 대상을 쓰라. 비용 6의 경로를 사람이 설명하는 것과 프로그램이 경로를 반환하는 것도 구별하라.

## 12장. 문자 키의 BST 순서를 보존하는 AVL 회전

기준 교재: [본문](../module_12_bst_avl/student/textbook.md)

문자 A~G의 배열 ID는 0~6이다. 회전 직전 링크는 F의 왼쪽 D·오른쪽 G, D의 왼쪽 B·오른쪽 E, B의 왼쪽 A·오른쪽 C이며 A,C,E,G는 leaf다. 저장 높이는 실제 높이와 같다. F와 D의 균형 인수를 구하라. 이어서 링크 변경 연습으로 rotate_ll(5,3,4)를 호출한다. 바뀌는 두 링크와 새 root를 쓰라. 회전 함수가 높이를 바꾸지 않으므로 호출자가 갱신할 높이의 순서·값도 쓰고 E가 계속 도달 가능한지 설명하라.

## 13장. 탐색 위치와 정렬의 준비 비용

기준 교재: [본문](../module_13_search_sort_consolidation/student/textbook.md) · [한국어판](../module_13_search_sort_consolidation/student/textbook_korean.md)

입력 레코드는 (2,A),(1,B),(2,C),(1,D) 순서로 도착했다. 괄호의 첫 값은 비교 키이고 문자는 원래 레코드를 구별하는 종이 표시다. 안정 정렬 뒤 레코드 순서를 쓰라. 키만 든 정수 배열을 현재 lab으로 정렬하고 2를 검색하면 원래 linear_search 위치와 정렬 뒤 binary_search_first 위치는 각각 얼마인가? scratch 크기도 말하라.

## 14장. DSU로 연결을 판단하는 Kruskal

기준 교재: [본문](../module_14_prim_kruskal/week_14/textbook.md)

정점은 A,B,C,D,E,F이며 F는 isolated다. self-loop와 동점 처리까지 포함해 이미 정해진 검사 순서는 E–E(-5),D–E(-1),B–C(1),A–B(2),A–C(2),C–D(3),B–D(4)다. 각 간선의 채택/거절을 DSU 연결 여부로 판단하라. 마지막 component 수, 채택 간선 수, 총 비용을 쓰고 동점 간선이 반드시 모든 최소 forest에 들어가야 하는지도 설명하라.
