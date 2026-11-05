# Chapter 8 Models — Processing Data in Stored Order

These models match the current [lab.c](../student/lab.c) and [workbook](../student/class_material.md). Queue states read front to back. Maze coordinates are always `{y,x}`. Every drawing has a text equivalent.

Use them as worked activities alongside the frozen [Korean textbook](../student/textbook_korean.md), **저장된 순서대로 데이터 처리하기**, and its English edition. The concept text states the rules; these models supply concrete queue, level, discovery, and route evidence. The actual source remains a distance-only maze BFS.

## Current model 1 — Linear positions and circular reuse

In a nonempty queue, front identifies the position of its first stored data and rear identifies the position of its last stored data. The indices are not the values at those positions. A point written first must be read first. Three writes occupy positions 0, 1, and 2. One removal advances front and leaves the other values in place.

```text
index:       0        1        2
stored:    {1,1}    {2,1}    {2,2}
                     ^        ^
                   front     rear
pending: [{2,1}, {2,2}]
```

Exact linear equivalent: front is 1 and rear is 2. They identify the positions of the first and last queued data. The next removal returns `{2,1}`. Position 0 still contains old data but is outside the pending interval. The source does not reuse removed positions until reset. Once no data waits, the queue has no first or last data; old array values do not change its empty state.

The first write increments rear from -1 to 0 while front stays 0. That singleton has front==rear. Once its only value is removed, front is one greater than rear and the active interval is empty. No data shifts in either operation.

For a paper circular comparison, front and rear remain the indices of the first and last queued data when nonempty. With 25 positions and one reserved slot, empty is `front==(rear+1)%25` and full is `front==(rear+2)%25`. Starting at 0/-1, fill labels 0–23, remove 0/1, append 24/25: front 2/rear 0 and pending labels 2–25. The actual maze queue is linear.

## Current model 2 — A tree processed by level

A queue makes already waiting siblings leave before newly added grandchildren. Use this illustrative tree; no tree implementation is part of the maze source.

```text
        A
       / \
      B   C
     / \ /
    D  E F
```

Exact linear edges: A has left B/right C; B has left D/right E; C has left F/no right child; D/E/F have no children. Queues after processing A/B/C/D/E/F are `[B,C]`, `[C,D,E]`, `[D,E,F]`, `[E,F]`, `[F]`, `[]`. Order A/B/C/D/E/F has depths 0/1/1/2/2/2. A child's depth is its parent's depth plus one.

### Why can a graph stack contain a duplicate?

Use directed edges A→B, A→C, A→D, and B→D. BFS enqueues A's neighbors as B/C/D. D already has a known distance when B checks it, so B does not enqueue it again. BFS processes A/B/C/D.

For the textbook's pending-node stack comparison, push A's neighbors in reverse order to process B first. Write the stack from bottom to top. After A it is `[D,C,B]`; popping B leaves `[D,C]`. D is unprocessed, so B pushes another D and the stack becomes `[D,C,D]`. The new D is processed before C. When the old D is eventually popped, its processed mark causes it to be skipped. The processing order is A/B/D/C. Mark a node processed before expanding its neighbors. This illustrates one iterative DFS policy; Chapter 6's actual DFS uses recursion.

## Current model 3 — The supplied maze

A passage cell connects to its orthogonally adjacent passage cells. The grid stores cell states, not pairs of graph vertices.

```text
        x=0 1 2 3 4
y=0       0 0 0 0 0
y=1       0 1 0 1 0
y=2       0 1 1 1 0
y=3       0 1 1 1 0
y=4       0 0 0 0 0
```

Exact passage list: `{1,1}`, `{1,3}`, `{2,1}`, `{2,2}`, `{2,3}`, `{3,1}`, `{3,2}`, `{3,3}`. Every other cell is a wall. Undirected passage connections are `{1,1}–{2,1}`, `{1,3}–{2,3}`, `{2,1}–{2,2}`, `{2,1}–{3,1}`, `{2,2}–{2,3}`, `{2,2}–{3,2}`, `{2,3}–{3,3}`, `{3,1}–{3,2}`, `{3,2}–{3,3}`.

## Current model 4 — Queue and distance trace

Start at `{1,1}`. Check right, left, down, up. Record distance before enqueue so an already waiting point is not added again.

A first discovery changes a cell from `INF` to a known distance before it enters the queue. The cell stays discovered while waiting, while its neighbors are checked, and afterward. It becomes processed once those neighbor checks finish. Distances read from the queue's front to back never decrease.

| Processed point | Distance | Queue after processing |
| --- | ---: | --- |
| Initial | — | `[{1,1}]` |
| `{1,1}` | 0 | `[{2,1}]` |
| `{2,1}` | 1 | `[{2,2},{3,1}]` |
| `{2,2}` | 2 | `[{3,1},{2,3},{3,2}]` |
| `{3,1}` | 2 | `[{2,3},{3,2}]` |
| `{2,3}` | 3 | `[{3,2},{3,3},{1,3}]` |
| `{3,2}` | 3 | `[{3,3},{1,3}]` |
| `{3,3}` | 4 | `[{1,3}]` |
| `{1,3}` | 4 | `[]` |

Exact linear explanation: `{2,2}` discovers `{3,2}` at distance 3. When `{3,1}` later checks that point, the distance is finite even though it still waits. It is skipped. The target `{3,3}` receives distance 4 from `{2,3}` and is skipped when encountered again from `{3,2}`. The lab saves no predecessors.

Final distance rows, with `INF=25`:

```text
INF INF INF INF INF
INF   0 INF   4 INF
INF   1   2   3 INF
INF   2   3   4 INF
INF INF INF INF INF
```

Eight entries are written and removed; 32 candidates are checked after 25 distance initializations. Peak pending is three, but the linear queue consumes eight write positions. Final front/rear are 8/7. One conceptual predecessor route is `{1,1}→{2,1}→{2,2}→{2,3}→{3,3}`, four moves; storing and printing it would require an extension.

## Optional checked-graph models

The remaining Stage D models describe the separate matrix/list API. Their IDs, sentinel 16, circular queue, and single-predecessor result are not the current maze lab's representation. Use them only with that optional library.

These models accompany Stage D. Every visual is followed by a linear text
equivalent. No meaning depends on color or spatial position.

An **ID** is an identifying number. The letters `u`, `v`, and `w` stand for
vertex IDs. The notation `u -> v` means a directed edge from vertex `u` to
vertex `v`. The notation `u:[v,w]` lists `u`'s outgoing neighbors in
ascending order.
Queue states are listed front to back. `T` means true, `F` means false, and
sentinel 16 means no distance or no predecessor.

## Model 1 — Canonical directed graph

```text
              0 Gateway
             /           \
         1 Web           2 Admin
        /     \          /      \
3 Database  4 LogCollector     5 VPN
       \        |  ^             |
        \       |  +-------------+
         \      v
           6 Monitor
              |
              +---- back to 1

7 Archive is isolated.
```

**Isolated** means having no entering or leaving edge.

Exact linear vertex table:

```text
0 Gateway
1 Web
2 Admin
3 Database
4 LogCollector
5 VPN
6 Monitor
7 Archive
```

Exact linear edge list:

```text
1. 0 -> 1
2. 0 -> 2
3. 1 -> 3
4. 1 -> 4
5. 2 -> 4
6. 2 -> 5
7. 3 -> 6
8. 4 -> 6
9. 5 -> 4
10. 6 -> 1
```

Exact outgoing-neighbor lists:

```text
0:[1,2]
1:[3,4]
2:[4,5]
3:[6]
4:[6]
5:[4]
6:[1]
7:[]
```

## Model 2 — Canonical Queue trace

```text
start   front [0]       back
after 0 front [1,2]     back
after 1 front [2,3,4]   back
after 2 front [3,4,5]   back
after 3 front [4,5,6]   back
after 4 front [5,6]     back
after 5 front [6]       back
after 6 front []        back
```

Exact linear sequence:

1. Initially, only source 0 waits.
2. Processing 0 discovers 1 and then 2.
3. Processing 1 discovers 3 and then 4.
4. Processing 2 skips pending 4 and discovers 5.
5. Processing 3 discovers 6.
6. Processing 4 skips pending 6.
7. Processing 5 skips processed 4.
8. Processing 6 skips processed 1.
9. The Queue is empty.

The maximum pending count is 3. Queue limit 3 succeeds. With limit 2,
processing 1 can enqueue 3 but cannot then enqueue 4.

## Model 3 — Final result

| Vertex | Discovered? | Distance | Predecessor | Visit position |
|---:|---|---:|---:|---:|
| 0 | true | 0 | 16, meaning none | 0 |
| 1 | true | 1 | 0 | 1 |
| 2 | true | 1 | 0 | 2 |
| 3 | true | 2 | 1 | 3 |
| 4 | true | 2 | 1 | 4 |
| 5 | true | 2 | 2 | 5 |
| 6 | true | 3 | 3 | 6 |
| 7 | false | 16, meaning unreachable | 16, meaning none | absent |

Exact linear arrays:

```text
visit order: 0,1,2,3,4,5,6
discovered:  T,T,T,T,T,T,T,F
distance:    0,1,1,2,2,2,3,16
predecessor: 16,0,0,1,1,2,3,16
```

## Model 4 — Predecessor path

Backward predecessor view:

```text
destination 6 <- 3 <- 1 <- 0 source
```

Forward path:

```text
0 -> 1 -> 3 -> 6
```

Exact linear checks:

1. The first path vertex is source 0.
2. The last path vertex is destination 6.
3. Edges `0 -> 1`, `1 -> 3`, and `3 -> 6` exist.
4. The path uses three edges.
5. Three equals `distance[6]`.
6. Other equal-hop paths may exist; this is the route selected by the
   ascending-neighbor rule.

## Model 5 — Matrix row versus dynamic neighbor array

For source vertex 2:

```text
matrix row destinations: 0 1 2 3 4 5 6 7
matrix row values:       F F F F T T F F

neighbor-row metadata:
data ------> [4][5][unused][unused]
size = 2
capacity = 4
```

Exact linear equivalent:

1. The matrix scans eight cells in row 2.
2. True cells occur at destinations 4 and 5.
3. **Metadata** is information describing a stored row.
4. The list row's `data` field identifies its owned allocation.
5. The list row's `size` is 2, so only positions 0 and 1 are **live**,
   meaning currently used.
6. The live values are 4 and 5 in ascending order.
7. `capacity` is 4, but positions 2 and 3 are not graph edges.
8. BFS reads live list positions only; supplied support owns growth and
   cleanup.

## Model 6 — Paper-only undirected forest

```text
tree 1: 0 -- 1 -- 2

tree 2: 3 -- 4 -- 5

tree 3: 6
```

Exact linear graph:

```text
vertices: 0,1,2,3,4,5,6
undirected edges: {0,1}, {1,2}, {3,4}, {4,5}
vertex 6 is isolated
```

The notation `0 -- 1` and the braces in `{0,1}` both mean one undirected
edge, which connects both ways.

Exact ascending forest:

```text
0,1,2 | 3,4,5 | 6
roots: 0,3,6
connected components: 3
```

The vertical bars mark tree boundaries and are not stored values. The
component conclusion is valid because this fixture is undirected. A
directed outer-scan forest does not automatically identify weak or strong
components.

## Model 7 — Cost comparison

Let `V` mean active vertex count and `E` mean edge count. `O(x)`, read
“order x,” describes how a bound grows with `x`. `V²` means `V` multiplied
by `V`.

| Work or storage | Matrix | Adjacency list |
|---|---:|---:|
| Representation storage | `O(V²)` | `O(V+E)` |
| Complete public BFS | `O(V²)` | `O(V+E)` |
| Temporary BFS state | `O(V)` | `O(V)` |

Exact linear explanation:

1. A matrix reserves one cell for every possible from/to vertex pair.
2. Matrix processing scans possible destinations, including missing edges.
3. A list stores existing neighbors and per-vertex row metadata.
4. List processing reads stored neighbors.
5. Both searches store discovery, distance, predecessor, and Queue state.
6. Construction and conversion costs are separate from traversal costs.
