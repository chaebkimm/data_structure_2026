# Chapter 8. Queues, Tree BFS, and Graph BFS

Current source boundary / 현재 소스 경계: Module 7 supplies node-index operations; Module 8's `queue.c` defines the value adapters. `init_lnodes_pool()` initializes once and later calls do nothing. Between independent runs, drain/recycle every pool owner and require `qhead == qtail == -1`; reset maze metadata separately. 초기화 함수를 다시 불러도 풀은 재설정되지 않는다. 8장의 값 어댑터가 할당·값 대입·반환을 맡으며, 노드 연산 자체는 값을 반환하거나 자동 재활용하지 않는다.


Chapter 7 used a linked FIFO queue as a linked-list example. This chapter compares array queue representations, then reuses that same linked queue for tree BFS and graph BFS. The maze `lab.c` records shortest distances and all shortest predecessors.

[한글 교재](textbook_korean.md) · [Class workbook](class_material.md) · [Concept slides](ppt_material.md) · [Lab slides](ppt_lab_material.md)

## Thinking Logically

### How can we process requests in arrival order?

Recall Chapter 7's linked queue. Requests 17, 23, and 31 must be processed in the order they arrive. A Stack removes 31 first. We need to add at the back and remove at the front. This rule is first in, first out, or **FIFO**. A **queue** provides those two actions. Adding is **enqueue**; removing is **dequeue**.

Reuse the local value adapters in `queue.c`, built on Chapter 7's node queue. `enqueue(value)` allocates a node, appends it, and returns `true`; an exhausted pool returns `false` without changing the queue. `dequeue()` returns the oldest stored value and recycles its node. Enqueue 17, 23, and 31, then receive those values in the same order. The first enqueue sets both endpoints, and the final dequeue restores `qhead = qtail = -1`.

The lower-level `enqueue_lnode(node)` and `dequeue_lnode()` still exchange pool-slot indices. The raw dequeue returns `-1` when empty and does not recycle its detached node. The public `dequeue()` reads and recycles that node for the caller. Check `is_empty_queue()` before a public dequeue: its assertion expresses a nonempty precondition. The payload `-1` is a valid queued integer, so it is not an empty-result sentinel. The pool initializer runs only once; later calls preserve live/free state. Start a new process or finish/recycle all owners before an independent run.

### Can an array hold the same waiting order?

We can store integer values directly, without allocating a linked node for each value. In `queue[25]`, `front` names the next read position and `rear` names the most recent write position. Start every independent variant with `front = 0; rear = -1;`.

For the linear version, `enqueue_linear(17); enqueue_linear(23); enqueue_linear(31);` leaves positions 0, 1, 2 active. `dequeue_linear()` reads 17, then advances `front` to 1. The remaining active values are 23 and 31. Removed positions are not reused. After 25 writes, `rear == 24`, even if some values were removed. The queue is full when `rear + 1 == 25` and empty when `front == rear + 1`. It can be both full and empty after all 25 values are removed: there are no pending values and no unused write positions.

The circular version reuses positions by wrapping indexes modulo 25. Its empty condition is `front == (rear + 1) % 25`; its full condition is `front == (rear + 2) % 25`. One position is reserved to distinguish those states, so 25 slots hold at most 24 waiting values. Fill with 0 through 23, remove 0 and 1, then append 24 and 25. The new `rear` is 0. Removal still gives 2 through 25 in order.

The linked, linear, and circular queues implement the same arrival rule with different storage. The array variants share `queue`, `front`, and `rear`; do not mix them in one run. Their functions remain unchecked. Their distinct names are `enqueue_linear`, `dequeue_linear`, `is_empty_linear`, and `is_full_linear`, plus the circular variants. The public linked `enqueue` checks pool exhaustion and returns a Boolean status. The pool has ten slots; other live lists reduce those available to the queue.

### How can we process a tree one level at a time?

A tree gives a clear first use for the waiting order. We want to process the root, then its children, then their children. Following one child recursively goes deep before processing the other child. Instead, enqueue the root index. Repeatedly dequeue one index, process its data, and enqueue its existing left child followed by its right child. This level order is **breadth-first search**, or **BFS**.

Reuse Chapter 2's exact tree after `alphabet_init(); root = tree_connect();`. Its root is F at index 5. F has children A and G; A has B and C; B has D and E. Indices 7, 8, and 9 are allocated array positions but are not reachable from F.

| Just processed | Pending indices | Pending labels |
| --- | --- | --- |
| Before processing | `[5]` | F |
| F | `[0,6]` | A, G |
| A | `[6,1,2]` | G, B, C |
| G | `[1,2]` | B, C |
| B | `[2,3,4]` | C, D, E |
| C | `[3,4]` | D, E |
| D | `[4]` | E |
| E | `[]` | empty |

The processing order is **F, A, G, B, C, D, E**, with depths 0, 1, 1, 2, 2, 3, 3. `tree_bfs(root, order)` stores these node indices and returns 7. The caller supplies room for ten indices, initializes the otherwise unowned linked-node pool, and sets `qhead = qtail = -1` before the call. Root `-1` represents an empty tree and returns 0. A valid tree has no cycles and no shared child, so each reachable node has one route from the root and enters once. A general graph can have several routes to the same vertex. The next example adds a discovery record to prevent duplicate scheduling.

The linked implementation keeps pool-slot indices in `qhead`, `qtail`, and `next`. The table shows the stored tree IDs. BFS calls `enqueue(tree_id)` and receives `tree_id` from `dequeue()`; it does not allocate, inspect, or free queue nodes itself. The public dequeue recycles before BFS adds children.

### How can we find a route with the fewest steps?

We start at one passage and want to reach another. Moving one cell right, left, down, or up takes one step. We cannot enter a wall. Following one route deeply can reach the goal after a long detour. To find the fewest steps, check all places one step away before places two steps away.

The maze is a graph. A passage is a vertex. Two passages share an edge when they touch horizontally or vertically. Every edge takes one step. A route with the fewest edges is a **shortest path**. This equal-step condition matters. The algorithm in this chapter does not compare different edge costs.

We use the same maze throughout the chapter. A `0` is a wall. A `1` is a passage. The start is `{1,1}` and the goal is `{5,5}`.

```text
            x
       0 1 2 3 4 5 6
   y 0 0 0 0 0 0 0 0
     1 0 1 0 1 1 1 0
     2 0 1 1 1 0 1 0
     3 0 1 0 1 1 1 0
     4 0 1 0 1 0 1 0
     5 0 1 1 1 1 1 0
     6 0 0 0 0 0 0 0
```

A `struct point` stores `x` first and `y` second. An array row comes first, so the cell at `{x, y}` is `maze[y][x]`. For example, `{3,2}` means `maze[2][3]`.

### What should enter the queue?

Each linked queue node has an integer `data` payload. A cell has two coordinates. Give each cell one integer, then keep the coordinates in a separate array. Initialization visits each row from left to right. The cell number is `7 * y + x`.

| Cell | Cell number | Where its search record lives | Where its coordinates live |
| --- | ---: | --- | --- |
| `{1,1}` | 8 | `info[1][1]` | `points[8]` |
| `{3,2}` | 17 | `info[2][3]` | `points[17]` |
| `{5,5}` | 40 | `info[5][5]` | `points[40]` |

`info[7][7]` holds one search record for every cell, including walls. `points[50]` maps a cell number back to coordinates. Initialization fills numbers 0 through 48. Slot 49 is unused. These cell numbers describe positions. They are not discovery times or distances.

### How can the queue keep closer cells first?

Put the start in the queue with distance 0. Remove its number from the front. Find its passage neighbors and put them at the back with distance 1. Repeat for each removed cell. Neighbors reached from a distance-1 cell receive distance 2.

The queue removes all distance-1 cells before any distance-2 cell. The same rule holds for later distances. Searching in this order is **breadth-first search**, or **BFS**. Finding a cell for the first time is discovery. Removing it and checking its neighbors is processing. A discovered cell can still be waiting in the queue.

If a shorter route to a cell existed, the cell immediately before it on that route would be processed earlier. That earlier cell would already have discovered it. Therefore the first distance assigned by BFS is the shortest distance.

### How do we recognize a new passage?

A maze can contain cycles. Enqueuing every neighbor would repeatedly add the same passages. Each cell needs a record showing whether its distance is already known.

`init_info()` sets every `distance` to 25 and every `prev_size` to 0. The value 25 means the distance is not known. There are only 25 interior positions. A shortest route does not repeat a position, so its distance is at most 24. This maze has 20 passages, which gives an even smaller bound. Therefore 25 cannot equal a finite shortest distance in this maze.

The value 25 is only a distance marker. It is a valid cell number: `{4,3}` has number 25. Do not treat 25 as a missing cell number. After BFS finishes, a passage with distance 25 is unreachable from the chosen start. Walls also keep their initialized distance 25.

When a new passage is found, the code writes its distance and previous cell **before** putting its number in the queue. A second route then sees the saved distance even while the passage is still waiting. The second route does not enqueue it again. No separate `discovered` array is needed.

### Why keep more than one previous cell?

Two routes can reach the same passage in the same number of steps. To remember both routes, save every neighboring cell whose distance is one less. Such a cell is a **predecessor** on a shortest path.

Each record has `prev[4]` and `prev_size`. The active entries are `prev[0]` through `prev[prev_size - 1]`. Each entry stores coordinates. Four slots suffice because a cell has at most four neighbors. Initialization resets the count; old values outside the active entries are ignored.

After skipping a wall, the code compares the neighbor's distance with the current distance.

| Neighbor condition | Action |
| --- | --- |
| `neighbor_distance <= cur_distance` | Skip the neighbor. Moving there would not extend a shortest path from the current cell. |
| `neighbor_distance == cur_distance + 1` | Append the current cell to the neighbor's predecessors. Do not enqueue the neighbor again. |
| Remaining case in a fresh BFS | Discover the neighbor. Set its distance, append its first predecessor, and enqueue its number. |

In a fresh FIFO search, the remaining case is an unseen passage with distance 25. A later cell cannot offer a shorter distance to an already discovered passage. Existing distances stay fixed, but the predecessor list can grow.

### Which neighbor is checked first?

Shortest distances do not depend on how the four directions are ordered. The queue order and predecessor order can change. This lab always checks **right, left, down, up**.

`init_iter(cur)` saves the current point in the global `cur_point` and sets the global `state` to 0. `next_iter()` copies the point, moves the copy in one direction, and increases `state`. Each `break` ends one `switch` case. Without the breaks, several coordinate changes would run in a single call.

This mechanism is a neighbor iterator: it produces one neighboring point at a time. The iterator uses shared state. Finish the four directions for one cell before initializing another cell's iteration. The current BFS does so inside its inner loop.

### What does the waiting line contain?

We can now follow the actual queue. Start `{1,1}` has number 8. The queue initially contains `[8]`. The table shows active values from front to back after processing each cell. Removed values can remain physically in the array, but they are outside the active queue.

| Removed number and cell | Distance | Queue after checking right, left, down, up |
| --- | ---: | --- |
| 8 `{1,1}` | 0 | `[15]` |
| 15 `{1,2}` | 1 | `[16,22]` |
| 16 `{2,2}` | 2 | `[22,17]` |
| 22 `{1,3}` | 2 | `[17,29]` |
| 17 `{3,2}` | 3 | `[29,24,10]` |
| 29 `{1,4}` | 3 | `[24,10,36]` |
| 24 `{3,3}` | 4 | `[10,36,25,31]` |
| 10 `{3,1}` | 4 | `[36,25,31,11]` |
| 36 `{1,5}` | 4 | `[25,31,11,37]` |
| 25 `{4,3}` | 5 | `[31,11,37,26]` |
| 31 `{3,4}` | 5 | `[11,37,26,38]` |
| 11 `{4,1}` | 5 | `[37,26,38,12]` |
| 37 `{2,5}` | 5 | `[26,38,12]` |
| 26 `{5,3}` | 6 | `[38,12,33,19]` |
| 38 `{3,5}` | 6 | `[12,33,19,39]` |
| 12 `{5,1}` | 6 | `[33,19,39]` |
| 33 `{5,4}` | 7 | `[19,39,40]` |
| 19 `{5,2}` | 7 | `[39,40]` |
| 39 `{4,5}` | 7 | `[40]` |
| 40 `{5,5}` | 8 | `[]` |

When number 31 is processed, it discovers number 38 with distance 6 and predecessor `{3,4}`. Later, number 37 has distance 5 and reaches the same number 38. The equality branch adds `{2,5}` as another predecessor. Number 38 does not enter the queue again.

Number 33 first discovers the goal, number 40, at distance 8. Number 39 later adds another predecessor. At completion, `info[5][5].prev_size` is 2. The entries are `{5,4}` and `{4,5}`, in that order. There are three shortest routes in total because `{3,5}` also has two predecessors.

All 20 passages are reachable from `{1,1}`. Each enters and leaves the queue once. The final linked endpoints are `qhead = qtail = -1`. All ten queue-pool slots are free after 20 removals; peak pending is four. The maze itself is unchanged. The program does not save a separate processing-order array; the table is a hand trace.

### How do previous cells give a route?

The recorded distances let us stop following predecessors at the start. Each backward move lowers the distance by exactly one. Following only `prev[0]` from `{5,5}` produces one route:

```text
Backward: {5,5} <- {5,4} <- {5,3} <- {4,3} <- {3,3}
          <- {3,2} <- {2,2} <- {1,2} <- {1,1}
Forward:  {1,1} -> {1,2} -> {2,2} -> {3,2} -> {3,3}
          -> {4,3} -> {5,3} -> {5,4} -> {5,5}
```

The route contains nine cells and eight moves. Choosing only `prev[0]` gives one shortest route. Following every active predecessor, with a separate branch for each choice, gives all three shortest routes. Two predecessors at the goal do not necessarily mean only two complete routes.

The start has distance 0 and no predecessor. Its route contains only itself. A passage whose distance remains 25 has no route from the start. `lab.c` records the information but provides no path-reconstruction function.

### What must be ready before a search?

A new run must begin without distances or queued numbers from an earlier run. The caller runs `init_info()` and `init_lnodes_pool()` while no live structure owns the pool, sets `qhead = qtail = -1`, and supplies a passage strictly inside the outer wall. `bfs()` sets the start distance to 0 but does not perform those resets or validate the start. The array comparison counters `front` and `rear` do not control BFS.

Every border cell in the supplied maze is a wall. Every dequeued passage is therefore interior. Its four neighbors have coordinates from 0 through 6. The wall check rejects border cells before they could be enqueued. This explains why neighbor accesses are valid under the stated conditions. `is_wall()` itself performs no bounds check. An invalid start or an open border removes that guarantee.

Both searches use the **local value adapters in Module 8 over Chapter 7's node queue**. Its internal pool slot lies in 0..9, while the stored ID can be larger than 9. The wrappers hide that distinction from BFS: `enqueue(id)` allocates and checks the pool; `dequeue()` returns the ID and recycles the slot before expansion. This permits 20 total discoveries with ten slots. Canonical peak pending is four, and all supplied-maze starts peak at six. A different graph needs its own bound. BFS stores each enqueue result outside `assert`, then asserts success; compiling with `NDEBUG` must not remove an enqueue call.

## Calculating Efficiency

### How much work do queues and tree BFS need?

Each enqueue or dequeue changes a fixed number of indices, links, or array entries: O(1). Initializing the ten-node pool visits ten records. If the pool grows to `P` slots, that initialization is O(P). Finding a predecessor by traversal remains separate work.

The tree example processes seven nodes and checks two child positions per node: fourteen checks. Every reachable node enters and leaves once. For `N` reached tree nodes, the work is O(N). The pending queue can grow with the largest level width. The linked implementation recycles the removed queue node before expanding it. The seven-node fixture peaks at three pending entries, not seven permanently consumed slots. It reserves ten two-integer pool records and ten output indices. A growing implementation needs storage for the peak frontier and output; their worst case is O(N).

### How much work explores this maze?

The example removes 20 passage numbers and checks four neighbors for each. That is 80 neighbor checks. Assigning a distance, appending one predecessor, and inserting or removing one integer each take a fixed amount of work. No array row is scanned to find neighbors.

If `R` passages are reachable, the search makes `R` removals and `4R` neighbor checks. Its time is O(R). For a general graph with `V` vertices and `E` edges, checking reached vertices and their incident edges gives the usual BFS bound O(V + E). Here each passage has at most four neighbors, so the number of checked connections grows with the number of reached passages.

Initialization separately writes all 49 cell records and coordinate entries. On an `H` by `W` maze, initialization takes O(HW). Initialization and search together take O(HW), since the reachable passages are part of those cells. The fixed 7 by 7 program has fixed bounds; these symbols describe growth when the maze size grows.

### How much storage records the search?

The program reserves 49 maze integers, 49 search records, 50 points, and ten two-integer linked queue-pool records. The separate array comparison also reserves 25 integers, but neither BFS uses that array. Each search record has four predecessor slots even if the cell is a wall. Reserving storage depends on the grid size, not on how many passages are reached. For a growing grid, the maze and search storage are O(HW). The loop's additional local storage is O(1).

The example makes 20 total insertions and 20 removals. Each removed slot returns to the pool before expansion. At most four entries wait simultaneously from `{1,1}`. The required pool capacity follows peak live queue occupancy, not total discoveries. Every completed run leaves `qhead == qtail == -1` and all ten slots free. Even a fully open 5 × 5 interior peaks at ten pending entries over all 25 possible starts with this direction order. Arbitrary larger or altered graphs are outside that measured bound.

### How much work rebuilds routes?

Choosing one predecessor per backward move visits nine cells for the example goal. For a route of `L` moves, following and reversing its `L + 1` cells takes O(L + 1) time and O(L + 1) output storage. Checking whether the stored distance is 25 takes O(1).

Listing all shortest routes costs more because every output route must be written. Branches in the predecessor records can create many complete routes. BFS storing the predecessors does not make enumerating all routes cost the same as following one route.

## Glossary

The following names refer to the actions and records already used above.

| Name | Meaning in this lab |
| --- | --- |
| FIFO / 선입선출 | Remove values in arrival order / 먼저 들어온 값부터 꺼내는 규칙 |
| enqueue, dequeue / 넣기, 꺼내기 | Append at the back, remove from the front / 뒤에 넣고 앞에서 꺼내기 |
| linked queue / 연결 큐 | Pool-node indices connected between head and tail / head와 tail 사이의 풀 노드 연결 |
| linear queue / 선형 큐 | Increasing positions without slot reuse / 위치를 증가시키며 사용한 칸은 재사용하지 않음 |
| circular queue / 원형 큐 | Positions wrap modulo 25; 24 usable slots / 25로 나눈 나머지로 순환하며 24개 저장 |
| level order / 층별 순서 | Process tree nodes by increasing depth / 깊이가 작은 층부터 처리 |
| shortest path / 최단 경로 | A passage route using the fewest one-cell moves |
| breadth-first search / 너비 우선 탐색 | A FIFO search that processes cells in nondecreasing distance order |
| discovery / 발견 | First assigning a passage's distance and scheduling it in the queue |
| processing / 처리 | Removing a cell number and checking its four neighbors |
| distance / 거리 | The minimum move count from the start; 25 means unknown or unreachable |
| predecessor / 선행 칸 | A neighboring passage one step closer to the start on a shortest path |
| cell number / 칸 번호 | The integer `7 * y + x`, used in the queue |
| active predecessor entries / 유효한 선행 칸 항목 | `prev[0]` through `prev[prev_size - 1]` |
| neighbor iterator / 이웃 반복자 | The shared `cur_point` and `state` mechanism producing four directions |
| path reconstruction / 경로 복원 | Following predecessors backward and reversing the cell sequence |

## Coding Plan

The data prepared in each step supports the next action.

1. Import Chapter 7's linked queue through `queue.c`. Compare its storage with the linear and circular array queues defined here.
2. Use the imported linked queue in `tree_bfs.c`. Store tree indices in queue-node `data`, enqueue left before right, and store processed indices in `order`.
3. Store the maze and coordinate type. Keep `0` for walls and `1` for passages. Read a coordinate using `[y][x]`.
4. Give every cell a number. Fill `info` and `points`, set distances to 25, and clear predecessor counts.
5. Read and write distances in the global records. Append predecessor coordinates using the active count.
6. Generate right, left, down, and up with the shared iterator. End every `switch` case with `break`.
7. Call `enqueue(start_id)`, store its Boolean result, and assert success. The wrapper owns allocation and insertion. Keep the enqueue operation outside `assert`.
8. Get the cell ID from `dequeue()`. Its queue node has already been recycled. Recover coordinates, skip wall/earlier-distance neighbors, retain equal-distance predecessors, and enqueue only first discoveries.
9. In a separate driver, initialize records and the otherwise unowned pool, and reset linked endpoints before each run. Check distances and active predecessor entries. Follow one or all predecessors when a route is needed.

## C Code

The queue code is in [queue.c](queue.c). It imports Chapter 7's complete linked queue and pool without redefining them. [tree_bfs.c](tree_bfs.c) imports Chapter 2's tree and the same queue. The maze [lab.c](lab.c) includes `queue.c` directly. The queue include guard shares one queue definition when the driver includes both searches. Compile only the driver; included C files are not separate compiler inputs.

### Import the linked queue and compare array representations

The include reuses Chapter 7's raw node queue; `queue.c` adds local `enqueue(value)` and `dequeue()` value adapters as the BFS interface. The array comparison functions below use `_linear` or `_circular` suffixes, so their names do not collide.

```c
/* Module 8: compare array queues and reuse Module 7's linked node queue.
 * Value adapters below allocate/write/enqueue, then dequeue/read/recycle.
 * The imported pool initializes once; drain every owner between independent runs.
 */
#ifndef MODULE_08_QUEUE_C
#define MODULE_08_QUEUE_C
#include <assert.h>
#include <stdbool.h>
#ifndef MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#define MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#include "module_07_linked_list/student/lab.c"
#endif

/* Module 8 convenience interface, built on Module 7's index operations. */
bool enqueue(int value) {
    int node = new_lnode();
    if (node == -1) { return false; }
    lnodes[node].data = value;
    enqueue_lnode(node);
    return true;
}

/* Caller guarantees nonempty; a payload of -1 is valid. */
int dequeue(void) {
    assert(!is_empty_queue());
    int node = dequeue_lnode();
    int value = lnodes[node].data;
    free_lnode(node);
    return value;
}

int queue[25];
int front = 0;
int rear = -1;

void enqueue_linear(int data) {
    queue[++rear] = data;
}

int dequeue_linear() {
    return queue[front++];
}

int is_full_linear() {
    return rear + 1 == 25;
}

int is_empty_linear() {
    return front == rear + 1;
}

void enqueue_circular(int data) {
    rear = (rear + 1) % 25;
    queue[rear] = data;
}

int dequeue_circular() {
    int data = queue[front];
    front = (front + 1) % 25;
    return data;
}

int is_full_circular() {
    return front == (rear + 2) % 25;
}

int is_empty_circular() {
    return front == (rear + 1) % 25;
}

#endif
```

### Process the tree with Chapter 7's linked queue

The tree stores child indices in `nodes[cur].left` and `.right`. A `-1` child never enters the queue.

```c
/* Use Module 8 value adapters over Module 7's node queue for tree-node IDs.
 * Before an independent run, initialize once and drain every pool owner.
 * A valid nonempty tree has no cycles/shared child and at most ten nodes.
 * order has ten slots; root -1 denotes an empty tree.
 */
#include <assert.h>
#include "module_02_binary_tree/student/lab.c"
#include "queue.c"

int tree_bfs(int root, int order[10]) {
    int count = 0;
    if (root == -1) return 0;
    bool added = enqueue(root);
    assert(added);
    (void)added;
    while (!is_empty_queue()) {
        int cur = dequeue(); /* Returns the ID and recycles its queue node. */
        order[count++] = cur;
        if (nodes[cur].left != -1) {
            added = enqueue(nodes[cur].left);
            assert(added);
        }
        if (nodes[cur].right != -1) {
            added = enqueue(nodes[cur].right);
            assert(added);
        }
    }
    return count;
}
```

### Store walls and coordinates

The outer wall keeps the neighbors of interior passages within the array. The coordinate fields still use `x, y`; array access uses `y, x`.

```c
int maze[7][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0}
};

struct point {
    int x;
    int y;
};

int is_wall(struct point p) {
    return maze[p.y][p.x] == 0;
}
```

### Initialize the cell records

The same `pos` fills the forward number and the reverse coordinate lookup. A zero predecessor count makes old predecessor values inactive.

```c
struct maze_node {
    int index;
    int distance;
    struct point prev[4];
    int prev_size;
};

struct maze_node info[7][7];
struct point points[50];

void init_info() {
    int pos = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            info[i][j].index = pos;
            info[i][j].distance = 25;
            info[i][j].prev_size = 0;
            points[pos].y = i;
            points[pos].x = j;
            pos++;
        }
    }
}
```

### Update the global search records

The setters change `info` directly. `prev_size++` supplies the old count as the insertion position and then increases the count. The BFS rules limit the count to four distinct neighboring predecessors.

```c
int get_index(struct point p) {return info[p.y][p.x].index;}

int get_distance(struct point p) {return info[p.y][p.x].distance;}
void set_distance(struct point p, int dist) {info[p.y][p.x].distance = dist;}

void add_prev(struct point p, struct point from) {
    int pos = info[p.y][p.x].prev_size++;
    info[p.y][p.x].prev[pos] = from;
}
```

### Produce four neighbors in order

Each call starts from a copy of `cur_point`. Movement from an earlier call does not carry into the next neighbor.

```c
struct point cur_point;
int state;

void init_iter(struct point p) {
    cur_point = p;
    state = 0;
}

int has_next() {return state < 4;}

struct point next_iter() {
    struct point p = cur_point;
    switch (state) {
        case 0: p.x += 1; break;
        case 1: p.x -= 1; break;
        case 2: p.y += 1; break;
        case 3: p.y -= 1; break;
    }
    ++state;
    return p;
}
```

### Save distances and every shortest predecessor

The equality branch changes only the predecessor list. The discovery branch writes the record before insertion. These rules let several shortest routes share one queued cell.

```c
void bfs(struct point start) {
    set_distance(start, 0);
    bool added = enqueue(get_index(start));
    assert(added);
    (void)added;

    while (!is_empty_queue()) {
        int cell_id = dequeue(); /* Returns the ID and recycles its queue node. */
        struct point cur = points[cell_id];
        int cur_distance = get_distance(cur);
        init_iter(cur);
        while (has_next()) {
            struct point neighbor = next_iter();
            if (is_wall(neighbor)) {continue;}
            int neighbor_distance = get_distance(neighbor);
            if (neighbor_distance <= cur_distance) {continue;}
            else if (neighbor_distance == cur_distance + 1) {
                add_prev(neighbor, cur);
            }
            else {
                set_distance(neighbor, cur_distance + 1);
                add_prev(neighbor, cur);
                added = enqueue(get_index(neighbor));
                assert(added);
            }
        }
    }
}
```

### Verify queues, tree, and maze together

[lab_driver.c](lab_driver.c) checks queue boundaries, circular reuse, the exact tree order, maze distances, and every shortest predecessor. It initializes the unowned node pool and linked endpoints before independent runs, resets metadata before maze runs, and verifies that all ten queue slots return after traversal. Build the actual sources directly; no edited teaching copy is needed.

```sh
cc -std=c11 -Wall -Wextra -pedantic -I . \
  module_08_graph_bfs/student/lab_driver.c -o /tmp/module08_lab
/tmp/module08_lab
```

```text
PASS: linked queues, tree BFS, mapping, canonical maze, and independent searches
```

Submit once: include the three queue traces, the pending tree queue, graph discovery and equal-distance predecessors, and one shortest route. The checked matrix/list API under `code/` remains optional reference.
