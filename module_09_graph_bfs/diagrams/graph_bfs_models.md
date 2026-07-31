# Graph BFS Models and Exact Linear Equivalents

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
