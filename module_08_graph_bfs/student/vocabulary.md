# Module 8 Vocabulary — Processing data in stored order

The first table follows the fifteen terms in the frozen [Korean textbook](textbook_korean.md), **저장된 순서대로 데이터 처리하기**, in the same order. Use the [workbook](class_material.md) for concrete queue, tree, and maze examples.

## Textbook terms / 교재 용어

| Name | Meaning in this chapter |
| --- | --- |
| queue / 큐 | Add data at the back and remove the earliest added data from the front. |
| first-in first-out / 선입선출 | Remove data in the order in which it was added; abbreviated FIFO. |
| enqueue / 추가 | Add data at the back of the queue. The lab stores a whole point at `queue[++rear]`. |
| dequeue / 꺼내기 | Remove and return the first queued data. The lab returns `queue[front++]`. |
| front / 맨 앞 | Index of the first data in a nonempty queue. An empty queue has no first data. |
| rear / 맨 뒤 | Index of the last data in a nonempty queue. An empty queue has no last data. |
| linear queue / 선형 큐 | An array queue whose active range advances without reusing removed positions until reset. |
| circular queue / 원형 큐 | An array queue whose indices wrap around to reuse removed positions. |
| level order / 층별 순서 | Process all nodes at one tree depth before the next depth. |
| breadth-first search / 너비 우선 탐색 | Use a queue to process nodes in nondecreasing minimum edge count from the start. Equal-cost moves make these paths shortest by cost as well. |
| discovered / 발견 | A node whose distance from the start has been established. Includes waiting and processed nodes. |
| processed / 처리 | A node removed from the queue whose neighbors have been inspected. |
| iterator / 반복자 | A mechanism that provides the next item in a defined order, such as a cell's next neighbor candidate. |
| sentinel / 특별한 표시값 | A value with a special meaning. `INF` marks a distance not yet established. |
| parent cell (predecessor) / 부모 칸 | The current cell from which another cell was first discovered. Save it to recover a shortest path. |

## Terms used in the activities / 활동에서 사용하는 용어

| Name | Meaning in the activities |
| --- | --- |
| capacity / 용량 | Reserved array positions. The linear queue needs room for all additions between resets. |
| active range / 대기 구간 | Positions `front` through `rear` containing data still waiting. Empty when `front > rear`. |
| reserved slot / 비워 두는 자리 | One position left unused to distinguish empty and full in the circular comparison. |
| depth / 깊이 | Number of edges from the tree root; a child's depth is its parent's depth plus one. |
| passage / 통로 | A cell whose maze value is 1. |
| wall / 벽 | A cell whose maze value is 0; BFS skips it. |
| coordinate / 좌표 | `{y,x}` gives row then column, matching `[y][x]` array access. |
| vertex / 노드 | One passage in the maze's graph model. |
| edge / 간선 | One horizontal or vertical move between adjacent passages. |
| implicit graph / 암시적 그래프 | Connections are computed from neighboring cells instead of stored as edge records. |
| start / 시작점 | The point passed to `bfs`; it must be inside the array. |
| unweighted graph / 비가중 그래프 | Each edge counts as one move when measuring path length. |
| pending / 대기 중 | Discovered points still in the queue. |
| peak pending / 최대 대기 수 | Largest number of points waiting together during a run. |
| distance / 거리 | Minimum move count from the start, stored in `distance[y][x]`. |
| path reconstruction / 경로 복원 | Follow saved parent cells backward from the target to the start, then reverse the collected sequence. |
| unreachable / 도달 불가 | An open passage left at `INF` after BFS; walls also retain `INF`. |
| invariant / 규칙 | A property preserved during the algorithm. Pending BFS distances never decrease from front to back. |
| caller precondition / 호출 전제 | Keep the zero border, use an in-bounds start, and respect unchecked queue and iterator conditions. |

`front` and `rear` are indices, not stored coordinate values. In a nonempty queue, `queue[front]` is its first data and `queue[rear]` its last data. In an empty queue, neither identifies data belonging to the queue, even if old values remain in the array. `front`와 `rear`는 데이터 자체가 아닌 인덱스다. 빈 큐에는 첫 데이터와 마지막 데이터가 없다.

The lab stores point values directly. It has no cell-ID mapping, linked-node pool, predecessor array, or separate visit-order array. Every `bfs` resets queue positions and distances. An in-bounds wall start leaves the queue empty and all distances at `INF`. Circular queues, tree traversal, the graph-stack comparison, and parent-cell recovery are conceptual activities; they do not add functions to the supplied source.

The new C explanations cover row-by-row brace initialization, whole-structure copying/passing/returning, and short-circuit logical OR. Named constants, increment operators, `switch`/`break`, and `continue` are earlier material used again in this chapter.
