# Module 8 Lab — Queues, Tree BFS, and Graph BFS

Retrieve the linked queue built as Module 7's linked-list example. Keep values in arrival order with the same implementation. Then process a tree by increasing depth. Finally process graph passages by increasing distance while remembering repeated arrivals. Use [queue.c](queue.c), [tree_bfs.c](tree_bfs.c), and the maze [lab.c](lab.c). Submit one artifact containing all three parts.

Read the [English textbook](textbook.md) or [Korean textbook](textbook_korean.md). Preserve predictions in the [class workbook](class_material.md) before running [lab_driver.c](lab_driver.c). Keep the original prediction and add a labeled correction.

## 1. Which queue state changes?

Reuse Module 7's value-based linked queue. Initialize the otherwise unowned pool with `init_lnodes_pool()` and set `head=tail=-1`. Call `enqueue(17)`, `enqueue(23)`, and `enqueue(31)` outside assertions, save each Boolean result, and check success. Trace endpoints, active links, and the free chain. `dequeue()` returns 17,23,31 and automatically recycles each removed node.

`enqueue(value)` allocates and appends a node, returning `false` without queue changes when the pool is exhausted. `dequeue()` returns the oldest value and automatically recycles its node. Check `is_empty_queue()` before dequeue; `-1` is a valid payload, not an empty-result sentinel. The lower-level `dequeue_lnode()` returns a slot or -1 and leaves recycling to its caller. Distinguish this raw helper from public dequeue. Never recycle a public-dequeue result: it is a payload value and its node is already free.

For each independent array queue run, reset `front=0; rear=-1`. The two variants share `queue[25]`; do not mix their operations.

| Variant | Empty predicate | Full predicate | Required boundary evidence |
| --- | --- | --- | --- |
| Linear | `front == rear+1` | `rear+1 == 25` | Fill 0..24, drain in order, explain why full and empty are then both true |
| Circular | `front == (rear+1)%25` | `front == (rear+2)%25` | Fill 0..23, remove 0/1, append 24/25, then drain 2..25 |

The array circular queue holds 24 values in 25 slots because one position distinguishes full from empty. In the wraparound example `rear` becomes 0. Check the predicate before every tested enqueue/dequeue. The array functions do not reject invalid operations for you. Do not execute unchecked overflow or underflow as a test.

## 2. Which tree data is processed next?

Prepare Module 2's original tree:

```c
int order[10];
alphabet_init();
int root = tree_connect();
init_lnodes_pool();
head = tail = -1;
int count = tree_bfs(root, order);
```

The root is F (index 5). Its children are A/G; A has B/C; B has D/E. Follow existing left before right children. Predict the pending indices after processing F, A, G, and B. Expected queues are `[0,6]`, `[6,1,2]`, `[1,2]`, and `[2,3,4]`. The final order is `5,0,6,1,2,3,4`, or F, A, G, B, C, D, E; count is 7. Array slots 7..9 are not reachable from the root.

Test an empty tree using root `-1` and a one-node tree using root index 3. Before each independent traversal initialize the otherwise unowned pool and set `head=tail=-1`. `order` has ten positions. Inputs must be valid acyclic trees without shared children. The function does not validate them. Explain why one parent per node makes a discovery array unnecessary here, and why that assumption fails for a general graph with cycles and merging routes.

## 3. How does a graph avoid scheduling a passage twice?

The 7-by-7 maze is a graph whose vertices are passages and whose edges join horizontally or vertically adjacent passages. Every edge is one move. Start `{1,1}` and target `{5,5}` are used throughout the lesson. Coordinates are `{x, y}` while array access is `[y][x]`.

Before each independent maze run, with no live pool owner:

```c
init_info();
init_lnodes_pool();
head = tail = -1;
bfs((struct point){1, 1});
```

The start must be an interior passage and the border must remain walls. `is_wall()` performs no bounds check. Initialization assigns `index=7*y+x` to all 49 cells and inverse coordinates to `points[0..48]`; `points[49]` is unused. Distance 25 means unseen/unreachable. ID 25 validly names `{4,3}`. Walls also retain distance 25.

After skipping walls, the iterator checks right, left, down, up. It has shared `cur_point` and `state`, so finish one cell's four directions before starting another.

| Neighbor distance, with current distance d | Record change | Queue change |
| --- | --- | --- |
| `<= d` | None | None |
| `== d+1` | Append current point to `prev` | None |
| Unseen 25 in a fresh run | Set distance d+1, append first predecessor | Enqueue once |

Setting distance before enqueue prevents a second route from scheduling a waiting passage again. Only `prev[0..prev_size)` is active. The start has distance 0 and no predecessor.

Trace these three decisions: `{1,2} → {1,1}`, `{2,5} → {3,5}`, and the first `{5,4} → {5,5}`. Continue the queue trace through all 20 passages. Final linked endpoints are `head=tail=-1`; all ten pool slots are free. Each queue node holds a cell ID in `data`; its pool-slot index is different. Public dequeue returns the cell ID and automatically recycles its node before BFS adds neighbors. The linked queue performs 20 insertions/removals from `{1,1}` but peaks at four pending entries. All valid starts on the supplied maze peak at six, within the unchanged ten-slot pool. Every completed run restores all ten free slots and empty endpoints. A fully open 5-by-5 interior peaks at ten pending entries over all starts with this direction order; different graphs need a new bound. Its shortest route still uses at most 24 edges, below unseen distance 25.

The goal has distance 8 and ordered predecessors `{5,4}`, `{4,5}`. `{3,5}` has predecessors `{3,4}`, `{2,5}`. Together those records encode three complete shortest routes. Follow `prev[0]` backward, then reverse it to recover one route of nine cells and eight moves. `bfs` records routes but does not print them. Printing all three routes is optional.

The supplied unreachable-passage check temporarily sets `maze[2][1]=0`, isolating the valid start `{1,1}`. The target `{5,5}` is still a passage but keeps distance 25, zero predecessors, and zero routes. Only the start is enqueued. The driver then restores `maze[2][1]=1` and checks a fresh canonical search. Include this result in the required evidence.

## 4. How do we run all parts together?

The current sources compile directly. `queue.c` imports Module 7's linked queue and pool without redefining either. `tree_bfs.c` includes Module 2's tree and the guarded queue. The maze includes the same queue. The combined driver includes both searches and verifies the original Module 7 queue; do not compile the included C files again as separate inputs. No DFS include or prepared teaching copy is needed.

From the repository root:

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

Expected output:

```text
PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches
```

Or use `make -C module_08_graph_bfs/code core`. PowerShell users run `code/build.ps1 -Target lab`. A compiler with sanitizer support can add `-g -fsanitize=address,undefined -fno-omit-frame-pointer`. Module 2's unchanged source may emit warnings about its unused demonstration variable and old-style no-argument definitions; record compiler diagnostics with the result.

The supplied checks cover linked endpoints and recycling, linear/circular boundaries, wraparound order, exact tree output, empty/single-node trees, all cell mappings, canonical maze distances, all shortest predecessor sets, three shortest routes, repeated runs from every valid starting passage, and an unreachable valid passage after isolating the start. The driver also verifies exact-once linked payload scheduling, FIFO order, live/free disjointness, insertion/removal counts, peak pending occupancy, and return of all ten pool slots. Add one original assertion each for queue, tree, and maze behavior and state the claim each assertion tests.

## 5. What evidence belongs in the one submission?

Include your driver and output, the queue representation traces, the tree pending-queue trace, the graph's three discovery cases, one recovered shortest route, original assertions, and corrected predictions. Use the [evidence template](evidence_template.md) and [rubric](rubric.md).

Count work before naming growth. Queue operations use a fixed number of changes: O(1). The linked tree frontier peaks at three entries. The tree processes seven nodes and checks fourteen child positions; N reachable nodes require O(N) work. Maze initialization touches 49 cells; search removes 20 passages and checks 80 neighbor candidates. General grid initialization is O(RC), and four-neighbor traversal is O(P) for P reached passages. General adjacency-list graph BFS is O(V+E). All arrays remain reserved after they drain. Enumerating every shortest route also costs the time needed to output every route.

- [ ] Module 7's value queue is retrieved; Module 8 compares array representations with separate names and reset evidence.
- [ ] Public linked dequeue returns values and recycles automatically; raw helpers exchange node indices.
- [ ] Circular queue has 24 usable slots and preserves FIFO across wraparound.
- [ ] Tree output is F, A, G, B, C, D, E and pending states are shown.
- [ ] Tree and graph discovery assumptions are compared.
- [ ] Maze metadata, otherwise unowned node pool, and linked endpoints are reset before each run.
- [ ] Public dequeue returns the payload ID after recycling; BFS adds children/neighbors afterward.
- [ ] Canonical peak pending is four, all supplied starts peak at six, and all ten pool slots return.
- [ ] ID 25, distance 25, coordinates, and array subscripts are distinguished.
- [ ] Equal-distance predecessors are retained without duplicate enqueue.
- [ ] Goal distance 8, two immediate predecessors, and three full routes are explained.
- [ ] Original assertions, compiler output, costs, and corrected predictions are included.

The checked matrix/list library and the older staged inquiry/worksheet/autopsy files are optional references. Their sentinel 16, checked statuses, typed circular queue, and single-predecessor policy describe that API only.

Both BFS functions use the original public `enqueue(value)`, `dequeue()`, and `is_empty_queue()` from Module 7. They do not allocate or recycle queue nodes themselves. Enqueue calls remain outside assert; a saved Boolean result is checked. Array queues are comparisons, with `_linear` and `_circular` names.

Check a valid payload of `-1` and a full ten-node queue: enqueue returns false without mutation, while draining returns each value and restores the pool. Public empty dequeue is outside the caller contract. Its assert is a diagnostic check and disappears with NDEBUG; use the emptiness predicate first.
