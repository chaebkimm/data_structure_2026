# Week 8 — Queues, Tree BFS, and Graph BFS: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Module 8 retrieves Module 7's linked queue, compares linear and circular
array queues, then uses that same linked FIFO for a binary tree and the maze
as an implicit graph. Use
`module_08_graph_bfs/student/queue.c`, `tree_bfs.c`, and `lab.c`.
Queue boundary traces, tree level order, maze distances and shortest
predecessors, tests, and explanations form **one Week 8 artifact**, with
one rubric and one due date.

The array queue has 25 slots. Its linear variant permits 25 total writes
per reset; its circular variant keeps one slot unused and holds 24 values.
The BFS worklist is Module 7's linked queue, imported through `queue.c`.
Its ten pool slots store pending IDs, not all IDs ever discovered. Public
`enqueue(id)` allocates internally and reports success as `bool`. Public
`dequeue()` returns the ID and recycles its slot before BFS adds children or
neighbors. BFS does not allocate or recycle queue nodes itself. Check
`is_empty_queue()` before dequeue and call enqueue outside any `assert`
expression; assert its saved result if checking the fixed-capacity precondition.

The tree bridge uses Module 2's `alphabet_init()` and `tree_connect()`.
Its root is F (index 5); left-before-right BFS processes F, A, G, B, C, D, E.
`tree_bfs(root, order)` returns the number of processed nodes. The input is
a valid acyclic tree with unique node ownership and at most ten nodes;
root `-1` represents an empty tree.

The graph example is the supplied 7-by-7 maze with 20 connected passages
and a zero wall border. Points use column `x` and row `y`; arrays use
`[y][x]`. Record discovery by writing the distance before enqueueing. The
maze BFS does not use a separate discovered array, sorted neighbor IDs,
checked status returns, or matrix/list backends.

Reset `front = 0; rear = -1;` before independent array-queue comparisons.
Before each independent tree or maze search, prepare the otherwise-unused
pool with `init_lnodes_pool()` and set `head = tail = -1`. Run `init_info()`
before each maze search. A tree has one parent path;
a graph can reach the same passage again, so maze discovery prevents a
second enqueue while equal-distance arrivals record additional predecessors.
The F-root tree needs at most three pending slots. The baseline maze needs
four; across all its valid starts the peak is six. Even the fully open
5-by-5 interior needs at most ten pending slots across all starts. These
are bounds for these fixtures, not a claim that every graph fits ten slots.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| traversal | A procedure that processes reached nodes or cells in a defined order. |
| breadth-first search (BFS) | A method that processes smaller distances before larger distances from one start. |
| frontier | Scheduled tree nodes or discovered graph passages still waiting in the queue. |
| implicit graph | A graph whose neighbors are generated from maze coordinates rather than stored in separate edge collections. |
| passage vertex | One maze cell with value 1, treated as a graph vertex. |
| four-direction edge | One allowed move between horizontally or vertically adjacent passage cells. |
| start | The selected interior passage where the search begins. |
| hop | Following one edge, or moving one passage cell, in this maze. |
| unweighted graph | A graph in which each move contributes the same one-step cost. |
| minimum-hop path | A start-to-target route using the fewest moves. |
| discovered | Having a recorded distance instead of the unseen marker, whether waiting or already processed. |
| enqueue-time distance write | Recording the first distance before enqueueing so another encounter cannot schedule the passage twice. |
| processed | Removed from the queue and scanned in all four directions. |
| grid coordinates | Column `x` and row `y`, used to access arrays as `[y][x]`. |
| cell ID | The integer `7*y+x`, assigned to every cell, including walls. |
| coordinate lookup | The reverse mapping `points[id]` from a cell ID to its `{x,y}` point. |
| distance | The minimum number of moves from the start to a discovered passage. |
| unseen sentinel 25 | The distance marker for no recorded route; it is larger than every reachable shortest distance in the supplied maze. |
| unreachable | Having no passage route from the selected start; its distance remains 25 after the search. |
| shortest predecessor | An adjacent passage one distance closer to the start on a shortest route. |
| predecessor list | The active entries of `prev[4]`, containing every shortest predecessor recorded for a cell. |
| active prefix | Entries `prev[0]` through `prev[prev_size-1]`; unused entries need not be cleared. |
| first discovery | The encounter that changes an unseen distance to `cur_distance+1`, adds the first predecessor, and enqueues the ID. |
| equal-distance encounter | Reaching a neighbor already at `cur_distance+1`; append the predecessor without enqueueing again. |
| iterator state | Global `cur_point` and `state`, used to return the four neighbors of one current cell. |
| deterministic neighbor order | The supplied right, left, down, up inspection order, which fixes dequeue and predecessor-list order. |
| linear array queue | A comparison implementation in `queue.c`, whose `front` and `rear` advance without reusing removed slots. |
| linked-worklist reset | Preparing an otherwise-unused pool with `init_lnodes_pool()` and setting `head=tail=-1` before a search. |
| wall-border condition | A zero outer border that keeps neighbors of queued interior passages inside the grid. |
| path reconstruction | Following stored predecessors backward, then reversing the collected points to present a forward route. |
| route count | The number of complete shortest routes, which can exceed the target's immediate predecessor count. |
| `O(R*C)` | Grid initialization work and reserved grid metadata proportional to rows times columns. |
| `O(V_reached)` | Traversal work proportional to reached passages because each has only four directions to inspect. |
| weekly artifact | The single Week 8 submission containing queue, tree BFS, and maze graph BFS code, tests, traces, and explanations. |
| `enqueue_linear` | Append an integer to the comparison linear array queue. |
| `dequeue_linear` | Remove the earliest integer from the comparison linear array queue. |
| `front` | The array position read by the next dequeue. |
| `rear` | The array position used by the most recent enqueue; initially `-1`. |
| full predicate | An array report such as `is_full_linear()` or `is_full_circular()` that another insertion is not permitted. |
| empty predicate | A report such as array `is_empty_linear()` or linked `is_empty_queue()` that no item is available. |
| circular queue | A FIFO array whose index updates wrap modulo 25. |
| wraparound | Updating index 24 to index 0 with `(index + 1) % 25`. |
| reserved slot | The one unused circular-array position distinguishing empty from full. |
| capacity | Reserved storage: ten linked pool slots, or 25 integer-array slots with 24 usable circular positions. |
| unchecked operation | An array comparison operation relying on caller full/empty checks; public linked enqueue instead reports exhaustion. |
| level order | Processing all nodes at one tree depth before those at the next depth. |
| tree depth | The number of edges from the tree root to a node. |
| pending node index | The tree-node ID stored as payload inside a linked queue node; it differs from the queue pool slot. |
| left-before-right order | Scheduling the left child before the right child of a processed tree node. |
| empty tree | The tree represented by root index `-1`, producing zero processed nodes. |
| tree input condition | A valid acyclic tree of at most ten nodes, with no child shared by two parents. |
| queue pool slot | A position 0–9 in `lnodes`, used to hold one pending work item. |
| queued payload | The tree-node or maze-cell ID stored in `lnodes[slot].data`. |
| queue slot reuse | Public dequeue internally copies the queued value and recycles the slot for later work. |
| live frontier bound | The maximum number of simultaneous pending items that must fit the linked pool. |

### Optional vocabulary for extension questions

These terms support optional generalizations and do not enlarge the required
maze implementation. The separate checked matrix/list reference has its own
API: IDs 0–15, sentinel 16, one chosen predecessor, and checked failure rules.
Those contracts do not describe the current maze `lab.c`.

| Term | Working meaning |
|---|---|
| multi-source BFS | A search initialized with several starts to find the nearest start by move count. |
| BFS forest | Repeated searches used to cover every component of a disconnected graph. |
| checked BFS API | The optional reference interface that validates calls and protects caller outputs on reported failure. |
| representation equivalence | Optional matrix and list backends producing the same public results under their own shared ordering rule. |

## Anticipated student questions

### Reuse the linked queue from Module 7

- How does Module 8 import the same linked-queue implementation taught as a list example in Module 7?
- Why does BFS pass a tree-node or maze-cell ID directly to public `enqueue(id)` rather than pass a pool-slot index?
- How does public `dequeue()` return the queued ID and recycle its slot without exposing the slot to BFS?
- Why must BFS avoid a separate `free_lnode` after public dequeue, and how does internal recycling make room before children or neighbors are enqueued?
- Which pool and endpoint state proves that a completed search returned all worklist nodes for reuse?
- Why can a search process 20 or 25 different passage IDs with only ten reusable queue slots?

### Linear array queue

- What do `front = 0` and `rear = -1` mean before the first array enqueue?
- Why does `enqueue_linear` increment `rear` before writing while `dequeue_linear` increments `front` after reading?
- Why is the linear empty condition `front == rear + 1`?
- Why can a linear queue remain full at `rear == 24` after some earlier items have been removed?
- Which full/empty checks must callers perform because the array queue operations are unchecked?
- Why must `front` and `rear` be reset before switching between the linear and circular variants that share `queue[25]`?

### Circular array queue

- How does `(index + 1) % 25` move from index 24 back to index 0?
- Why is this circular queue empty when `front == (rear + 1) % 25`?
- Why is this circular queue full when `front == (rear + 2) % 25`?
- Why do 25 reserved array positions hold only 24 queued values under these predicates?
- How does removing two values from a full circular queue permit two more enqueues across wraparound while preserving FIFO order?
- Which boundary traces distinguish array capacity, current queued count, and the 24-value circular limit?


### Tree BFS bridge

- Starting with Module 2's root F (index 5), which pending node indices remain after processing F, A, and G in turn?
- Why does left-before-right scheduling produce F, A, G, B, C, D, E rather than the DFS order?
- How does `tree_bfs(root, order)` use the queue's integer payloads to find each tree node's data and children?
- What count and output prefix should an empty-root test and the seven-node tree test verify?
- Why does the tree's unique-parent condition avoid repeated scheduling, while a graph needs discovery recorded before enqueue?
- Why must a fresh tree run initialize the otherwise-unused linked pool and reset `head` and `tail`, and why do three pending slots suffice for the F-root fixture?

### Meaning and mental model

- What does breadth-first search mean when moving through this maze?
- What is the frontier, and why does BFS keep it in a FIFO queue?
- Why do queued passages leave in nondecreasing distance from the start?
- How do the maze's passages and four-direction moves form a graph without a separate edge table?
- Why does a shortest route with eight moves contain nine points?

### Representation and invariants

- Why does point `{3,2}` access `maze[2][3]` rather than `maze[3][2]`?
- How does `7*y+x` map `{4,3}` to cell ID 25, and why is that ID different from distance sentinel 25?
- Why does `points[50]` contain only 49 initialized mappings when the maze has 20 passages?
- What do `prev[4]` and `prev_size` record, and which entries may be read?
- How does `distance` record discovery for waiting and processed passages without a separate discovered array?
- Why is 25 a valid unseen-distance marker for this maze, and what would need reconsideration for a larger maze?

### Operations, C API, and ownership

- Which functions are already complete in `lab.c`, and which caller setup, tests, and route reconstruction must students add?
- How do `set_distance` and `add_prev` change the shared `info` array instead of a local copy?
- Why must the caller call `init_info()`, prepare an otherwise-unused linked pool with empty endpoints, and select an interior passage before each independent search?
- How do `cur_point`, `state`, and the switch `break` statements generate right, left, down, then up?
- Why does the maze include its local `queue.c`, which imports Module 7's linked queue, and why must a build avoid duplicate definitions?

### Tracing

- What are the start's distance, predecessor count, and queued cell-ID payload when a fresh search begins at `{1,1}`?
- Which distances and remaining queue IDs follow processing `{1,1}` and then `{1,2}`?
- How do encounters from `{3,4}` and `{2,5}` create two predecessors for `{3,5}` while enqueueing it only once?
- What changes in each branch when the neighbor distance is at most the current distance, exactly one greater, or still 25?
- Why does ID 24 leave the queue before ID 10 even though the traversal distances never decrease?
- Why does goal `{5,5}` have distance 8 and two immediate predecessors but three complete shortest routes?

### Testing and debugging

- Which payload trace and final free-chain/endpoint state verify 20 baseline work items and complete recycling after the queue drains?
- How can a start-as-target test verify distance 0, no predecessor, and a one-point reconstructed route?
- How does a fully reset run from `{5,5}` check reachability and the reverse distance to `{1,1}`?
- How can a temporary isolated-passage test preserve the zero border and verify distance 25 with `prev_size==0`?
- How can a test check that every stored predecessor is an adjacent passage with distance exactly one less?

### Complexity

- Why does `init_info()` initialize 49 records here and require `O(R*C)` work for an R-by-C grid?
- Why do 20 dequeues lead to 80 direction checks here and `O(V_reached)` traversal work in general?
- Why does the linked worklist need capacity for four pending baseline items rather than all 20 discovered passages, while the comparison linear queue needs space for total writes?
- Why can enumerating all shortest routes require more work than computing distances and predecessor lists?

### Security and interpretation

- How does the valid-start and zero-border condition protect neighbor accesses even though `is_wall()` has no bounds check?
- Why does a larger maze require a new live-frontier bound even though public enqueue reports pool exhaustion and the current BFS asserts that its enqueue succeeded?
- Why do maze reachability and a small move count establish neither access authorization nor real-world risk?

### Assignment and evidence

- What caller code, tests, predictions, corrections, and traces belong in the single Week 8 queue, tree BFS, and graph BFS submission?
- Why are the optional checked matrix/list API and its sentinel 16 outside the required maze implementation?
- Which evidence establishes queue order, all shortest predecessors, an unreachable target, and three shortest goal routes?
- How do Module 7's linked-queue endpoint and recycling rules explain safe reuse between tree BFS and maze BFS?

### Transfer

- When can DFS establish reachability without guaranteeing that its first route uses the fewest moves?
- Why does following shortest predecessors always decrease distance and avoid a cycle during reconstruction?
- How does shortest-route reconstruction prepare you for later paths with unequal movement costs?
- Why can direct grid indexing and recorded distances replace a separate hash lookup for discovered state here?

### Extension questions

- How would multi-source BFS find each passage's distance from the nearest chosen start?
- How could repeated BFS searches cover all components after interior walls disconnect the maze?
- How do the optional checked API's single predecessor, sentinel 16, and failure-preservation rules differ from the maze records?
- How could optional matrix/list equivalence tests compare two backends under their own shared neighbor-order rule?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md)
- [Module 8 teaching-package overview](../module_08_graph_bfs/README.md)
- [Current combined textbook](../module_08_graph_bfs/student/textbook.md)
- [Current combined lab](../module_08_graph_bfs/student/lab.md)
- [Queue source](../module_08_graph_bfs/student/queue.c)
- [Tree BFS bridge](../module_08_graph_bfs/student/tree_bfs.c)
