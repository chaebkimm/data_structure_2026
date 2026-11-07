# Module 6 Vocabulary — Grouping connections in a graph

## Current textbook terms

Use these terms with the [textbook](textbook.md) and the glossary activity
in the [bilingual workbook](class_material.md).

| Term / 용어 | Meaning / 뜻 |
| --- | --- |
| Depth-first search (DFS) / 깊이 우선 탐색 | Explore an unreached neighbor completely before resuming the current vertex's list. / 미방문 이웃의 탐색을 끝낸 뒤 현재 노드의 이웃 목록을 계속한다. |
| Visit number / 방문 번호 | Positive discovery order; zero means unvisited. / 처음 도달한 순서의 양수이며, 0은 미방문이다. |
| DFS parent / DFS 부모 | The vertex that first discovers a child; a root has none. / 자식을 처음 발견한 노드이며 root에는 없다. |
| Tree edge / 트리 간선 | An edge that first discovers an unreached vertex. / 미방문 노드를 처음 발견하는 간선. |
| Back edge / 빽 간선 | A non-parent edge from descendant to ancestor in simple undirected DFS. / 단순 무방향 DFS에서 후손에서 부모 이외의 조상으로 가는 간선. |
| Preorder / 전위 처리 | Work on first entry. / 노드에 처음 들어갈 때 하는 작업. |
| Postorder / 후위 처리 | Work after all neighbors finish. / 모든 이웃 처리가 끝난 뒤 하는 작업. |
| Low-link / 빽 번호 | Earliest visit reachable by tree descent and at most one back edge, including self. / 트리 간선으로 내려가 빽 간선을 최대 한 번 사용해 도달하는 가장 이른 방문 번호이며 자신도 후보에 포함한다. |
| Connected component / 연결 요소 | A maximal group of vertices joined by undirected paths. / 무방향 경로로 연결된 최대 노드 그룹. |
| Adjacency list / 이웃 목록 | One vertex's neighbors. / 한 노드의 이웃 모음. |
| Edge list / 간선 목록 | One endpoint-pair record per undirected edge. / 무방향 간선마다 하나씩 저장한 끝점 쌍. |
| Adjacency matrix / 인접 행렬 | Whether each vertex pair is directly connected. / 두 노드의 직접 연결 여부를 저장한 표. |
| Edge lookup / 간선 조회표 | Both endpoint orders find the same edge index; -1 means no record in this pass. / 두 끝점 순서가 같은 간선 인덱스를 찾으며, -1은 이번 탐색의 기록 없음을 뜻한다. |
| Internally vertex-disjoint paths / 내부 노드를 공유하지 않는 경로 | Paths sharing only their endpoints. / 양 끝점만 공유하는 경로. |
| Biconnected component (block) / 이중 연결 요소(블록) | A maximal connected group with no separating vertex inside; a bridge also forms a single-edge block. / 내부 절단점이 없는 최대 연결 그룹이며 다리 간선도 단일 간선 블록을 만든다. |
| Cut vertex / 절단점 | A vertex whose removal increases the component count. / 제거하면 연결 요소 수가 증가하는 노드. |
| Bridge / 다리 간선 | An edge whose removal increases the component count. / 제거하면 연결 요소 수가 증가하는 간선. |
| Pending-edge stack / 대기 간선 스택 | Handled edges awaiting assignment to a block. / 처리했지만 아직 블록에 배정하지 않은 간선의 스택. |
| Invariant / 규칙 | A statement that stays true at specified checkpoints. / 정해진 확인 시점마다 계속 참인 설명. |

A visit number, a vertex array index, and an edge record index identify
different things. The recursive call stack keeps active scans; the explicit
edge stack keeps pending edge indices.

## Legacy checked matrix-DFS vocabulary

The terms below belong to the separate [checked matrix exercise](lab.md).
Its Boolean visited array, vertex stack, status codes, and failure guarantees
do not describe the unchecked array/BCC lecture lab.

Open this reference after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| graph | Items plus the direct relationships between them |
| vertex | One item in a graph |
| edge | One direct relationship between two vertices |
| directed edge | An edge that works in one stated direction |
| undirected edge | An edge that connects both ways |
| out-neighbor | The destination of an edge leaving the current vertex |
| route | A sequence that follows stated edges |
| cycle | A route that returns to an earlier vertex |
| source | The vertex where a search starts |
| reachable | Having a route from the stated source |
| algorithm | A precise, repeatable set of steps |
| depth-first search (DFS) | A method that follows one available route deeply before returning to an unfinished choice |
| Boolean | A value that is either `true` or `false` |
| visited array | One Boolean per vertex recording whether that vertex has been discovered and scheduled |
| discover | Reach a vertex for the first time |
| schedule | Arrange for a vertex's work to occur |
| mark | Change one vertex's visited value from `false` to `true` |
| record | Append a processed vertex number to the output |
| function | A named group of instructions that performs one task |
| recursion | A function calling itself directly or through other functions |
| recursive call | A function call made as part of recursion |
| call frame | Saved information for one active function call |
| runtime call stack | Bookkeeping commonly used by a C implementation for active function calls |
| iterative algorithm | An algorithm that repeats with a loop instead of recursive calls |
| loop | Instructions repeated while a stated condition holds |
| Stack | A last-in, first-out collection |
| last in, first out (LIFO) | The newest stored item is the first removed |
| `push` | Add one item at the top of a Stack |
| `pop` | Remove and report the top Stack item |
| explicit vertex-ID Stack | A Stack directly operated by the program that stores vertex numbers |
| frontier | Discovered vertices still waiting to be processed |
| bottom-to-top order | A Stack listing from its oldest item to its removable newest item |
| pointer | A C value that identifies an object's memory location |
| `NULL` | The C pointer value meaning “points to no object” |
| caller | The function or program part that requests another function |
| isolated vertex | A vertex with no edge entering or leaving it |
| connected component | One separate group in an undirected graph whose vertices have routes to one another |
| adjacency matrix | A row-and-column grid that records possible edges |
| adjacency list | One stored list of outgoing neighbors for every vertex |
| `GraphDfsOrder` | Up to 16 recorded vertex numbers plus their count |
| API | Public types and operations available to other code |
| contract | Rules stating what an operation accepts, changes, reports, and preserves |
| output parameter | Caller-provided storage in which a function writes an answer |
| status code | A named result reporting success or one kind of failure |
| validation | Checking whether all required representation rules hold |
| failure preservation | A failed operation leaves the caller's complete old output unchanged |
| limit | A stated maximum |
| allocation | Storage obtained while a program runs |
| allocation failure | Requested storage could not be obtained |
| cleanup | Releasing temporary storage after its use |
| time complexity | A description of how work grows with input size |
| Big-O notation | A compact way to write a pattern of growth as `O(...)` |
| auxiliary space | Temporary working storage separate from input and output |
| `V` | The number of active vertices |
| `E` | The number of stored edges |
| `O(V²)` | Work or storage that can grow like vertex count times vertex count |
| `O(V+E)` | Work or storage that can grow with vertices plus edges |
| `O(V)` | Work or storage that can grow in proportion to vertex count |
| synthetic | Invented for safe practice rather than taken from a real system |

## Exact result names

| Status | Meaning |
|---|---|
| `GRAPH_DFS_OK` | The requested operation succeeded |
| `GRAPH_DFS_INVALID_ARGUMENT` | A required pointer was `NULL` |
| `GRAPH_DFS_OUT_OF_RANGE` | The requested source is not an active vertex |
| `GRAPH_DFS_INVALID_GRAPH` | The entire active stored graph breaks its Module 3 rules |
| `GRAPH_DFS_REQUIRES_UNDIRECTED` | Component counting received a directed graph |
| `GRAPH_DFS_LIMIT` | The requested or needed Stack limit, or maximum, cannot be met |
| `GRAPH_DFS_ALLOCATION` | Temporary Stack storage could not be obtained |

## Three related forms of saved work

- The Stack rule is the general last-in, first-out behavior.
- The explicit vertex-ID Stack is a program-created frontier.
- The runtime call stack commonly stores active recursive call frames.

They follow a similar newest-work-first pattern, but they are not the same
stored object.
