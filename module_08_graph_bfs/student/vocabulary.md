# Module 8 Vocabulary — Queues, Tree BFS, and Graph BFS

Use these names after working through queues, the tree, and the maze in the [textbook](textbook.md) or [class workbook](class_material.md).

| Name | Meaning in the current queue/tree/maze sources |
| --- | --- |
| FIFO | Remove in arrival order / 먼저 들어온 값부터 꺼냄 |
| Queue | Add at the back and remove at the front / 뒤에 넣고 앞에서 꺼내는 구조 |
| Linked queue | Module 7 node primitives plus Module 8 local value adapters; qhead/qtail identify pool slots / 7장의 노드 연산을 8장의 값 어댑터로 감싼 큐 |
| Queue-node payload | Tree index or maze cell ID in lnodes[slot].data, separate from the pool-slot index / 풀 위치와 저장한 탐색 번호를 구분 |
| Peak pending | Largest simultaneous linked frontier; four canonical, at most six over this maze's starts / 동시 대기 최대 개수 |
| Recycling | Public dequeue reads the payload and returns its node to the pool before returning / 공개 꺼내기가 값을 읽고 칸을 자동 반환 |
| Linear queue | Increasing front/rear; no slot reuse before reset / 위치를 증가시키며 초기화 전 칸 재사용 없음 |
| Circular queue | Modulo25 positions; one reserved slot gives 24 usable values / 위치 순환과 한 칸 비우기 |
| Enqueue / dequeue | Add / remove; linked public API accepts/returns values and owns node recycling / 넣기와 꺼내기 |
| Level order | Process by increasing tree depth / 깊이가 작은 층부터 처리 |
| Tree BFS | FIFO pending indices; left child before right / 인덱스를 FIFO에 두고 왼쪽 자식을 먼저 넣음 |
| passage / 통로 | A cell whose maze value is 1; movement may enter it |
| wall / 벽 | A cell whose maze value is 0; BFS skips it |
| coordinate / 좌표 | `{x, y}` means column and row; arrays use `[y][x]` |
| vertex / 정점 | One passage in the maze's graph model |
| edge / 간선 | One allowed orthogonal move between passages |
| implicit graph / 암시적 그래프 | Connections generated from the grid rather than stored as edge records |
| source / 출발점 | The interior passage supplied as `start` |
| hop / 이동 한 번 | Following one edge; every move costs one hop |
| unweighted graph / 비가중 그래프 | A graph whose edges all count equally |
| breadth-first search | FIFO search that processes smaller distances before larger distances |
| frontier / 대기 중인 정점 | Discovered passage IDs stored as payloads along the linked queue from head to tail |
| discovered / 발견됨 | Given a distance below 25 before entering the queue; no separate flag exists |
| processed / 처리됨 | Dequeued and examined through all four neighbor candidates |
| cell index / 칸 인덱스 | `7*y+x`, stored in a linked queue node's data field |
| inverse mapping / 역방향 대응 | `points[index]` recovers the coordinate |
| distance / 거리 | Minimum move count from the start; the start has distance 0 |
| sentinel / 특별값 | Distance 25 represents unseen cells and, after completion, unreachable cells |
| predecessor / 이전 칸 | A neighbor one distance smaller on a shortest path |
| predecessor list / 이전 칸 목록 | The active `prev[0..prev_size)` entries; several shortest predecessors may exist |
| equal-distance arrival / 같은 거리의 도착 | Another route of length `current_distance+1` equals the stored distance; append a predecessor without reenqueueing |
| neighbor iterator / 이웃 반복자 | `init_iter`, `has_next`, and `next_iter` generate right, left, down, and up |
| path reconstruction / 경로 복원 | Follow predecessors backward, then reverse the selected sequence |
| unreachable / 도달 불가 | A passage left at distance 25 after BFS; check `maze` to distinguish a wall |
| caller precondition / 호출 전제 | Reset metadata, require all pool slots recycled and the queue empty, choose a valid passage, and preserve the zero border |

Cell index 25 is valid. The sentinel belongs to the distance field only. `prev_size == 0` means there are no active predecessors; unused `prev` slots have no meaning. The lab supplies no stored visit-order array, heap allocation, or path-reconstruction function. Linked enqueue returns Boolean success; dequeue requires a nonempty queue.
