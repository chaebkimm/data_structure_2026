# Data Structures Course 2026 — 14-Week Delivery Guide

## Purpose and authority

This is the operational delivery path for a course with **14 instructional
weeks**. The repository's 14 numbered teaching packages form an instructor resource
library; Priority Queue is integrated into Module 10, and Hash Table is
Module 9. Package numbers follow teaching Weeks 1–14. Module 7
teaches index-linked lists with a linked queue as an application in Week 7
and retains DSU references used by Week 14. Module 8 compares queue
representations and reuses that linked queue for tree BFS and graph BFS.
A package README describes the complete deep-dive
version of that topic. When this guide narrows or combines a package, this
guide controls what is required in the 14-week offering.

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).

Each teaching week has a hard cap of **180 contact minutes**. The cap includes
retrieval, explanation, tracing, guided implementation, testing, and evidence
work. Material displaced by a combined or bounded week becomes extension
material; it is not reassigned as required asynchronous work.

The institution's scheduled final-assessment period is separate from the 14
teaching weeks and is used for the capstone defense or its approved equivalent.

## Assessment load at a glance

- **Twelve weekly lab artifacts:** Weeks 1–5, 7–10, and 12–14, including the Week 8 queue/tree/graph-BFS artifact and the folded Week 14 checkpoint.
- **Practical 1:** Week 6; it replaces the ordinary Graph DFS lab.
- **Practical 2:** Week 11; it replaces the ordinary Dijkstra lab.
- **Five spiral synthesis checks:** embedded in the Week 3 lab, Practical 1,
  Week 8 queue/tree/graph-BFS lab, Practical 2, and folded Week 14 artifact; they are not
  separate submissions.
- **Capstone:** built incrementally, integrated in Week 14, and defended in
  the scheduled final-assessment period.

There is at most one required programming submission in any teaching week.
The Week 8 submission contains queue evidence, a tree-BFS trace, and graph-BFS code and synthesis from Module 8. Week 10 combines
the fixed integer Heap and dual-Heap interval search inside Module 10. Each
has one submission, one due date, and one rubric. Week 14's
capstone integration checkpoint is folded into that week's work rather than
issued as a second weekly programming submission.

## Fourteen-week calendar

| Week | Required focus and package use | Required graded work | Extension only | Weekly vocabulary and questions |
|---:|---|---|---|---|
| 1 | Fixed-capacity ArrayList — [Module 1](module_01_arraylist/README.md) core | Ordinary lab 1: access, search, append, insert, and remove | Additional boundary and operation-sequence tests | [Week 1 page](student_question_bank/week_01_arraylist.md) |
| 2 | Array-indexed expression trees and recursive evaluation — [Module 2](module_02_binary_tree/README.md), with English and Korean textbooks | Ordinary lab 2: `new_node`, `term`, `terms`, and `eval_tree` | Additional valid expressions and construction/evaluation traces | [Week 2 page](student_question_bank/week_02_binary_tree.md) |
| 3 | Directed integer adjacency matrices — [Module 3](module_03_graph/README.md) core | Ordinary lab 3: initialize, add, remove, and count outgoing edges | Additional valid directed fixtures and traces | [Week 3 page](student_question_bank/week_03_graph_representations.md) |
| 4 | Integer Stack and postfix — [Module 4](module_04_stack/README.md) core | Ordinary lab 4: top-index integer Stack, `1-2*3+4 -> 123*-4+ -> -1`, and `1+(2+3) -> 123++ -> 6` using `student/lab.c` | Checked parsing/arithmetic and legacy integer API comparisons | [Week 4 page](student_question_bank/week_04_stack.md) |
| 5 | Preorder, inorder, and postorder using explicit stacks without recursion — [Module 5 textbook](module_05_tree_dfs/student/textbook.md) | Ordinary lab 5; existing package exercise remains separate from the textbook examples | Additional tree shapes and stack traces | [Week 5 page](student_question_bank/week_05_tree_dfs.md) |
| 6 | Graph DFS — [Module 6](module_06_graph_dfs/README.md), with iterative DFS using Stack as the implementation core | **Practical 1 only**; no ordinary Module 6 lab | Recursive graph DFS | [Week 6 page](student_question_bank/week_06_graph_dfs.md) |
| 7 | Linked lists with a linked queue example — [textbook](module_07_linked_list/student/textbook.md) and [Module 7 materials](module_07_linked_list/README.md) | Ordinary lab 6: node-pool reuse, predecessor insertion/detachment, linked FIFO endpoints, and list/queue traces and tests | Allocated-list API, doubly linked lists, and DSU before Week 14 | [Week 7 page](student_question_bank/week_07_linked_list.md) |
| 8 | Queues → tree BFS → graph BFS — [Module 8](module_08_graph_bfs/README.md): queue comparisons, linked-queue reuse for tree levels and maze discovery, shortest predecessors, and path recovery | **Lab 7: one submission** with queue checks, tree and maze traces, driver, and explanation | Checked matrix/list API, all-path printing, and larger-maze generalization | [Week 8 page](student_question_bank/week_08_bfs.md) |
| 9 | Hash Table — [Module 9](module_09_hash_table/README.md): ten buckets, separate chaining, pool reuse, and two-sum in the supplied lab.c | Ordinary lab 8: one driver and evidence submission | Older open-addressed map, resizing, and adversarial extensions | [Week 9 page](student_question_bank/week_09_hash_table.md) |
| 10 | Integer min/max Heaps and shared on-time — [Module 10](module_10_binary_heap/README.md) follows current lab.c | **Lab 9: one submission** of driver, tests, traces, maps, and interval reasoning | Alert-record Heap, dynamic allocation, and unsorted-baseline implementation | [Week 10 page](student_question_bank/week_10_priority_queue_heap.md) |
| 11 | Dijkstra — [Module 11](module_11_graph_dijkstra/README.md): trace and test the supplied indexed-Heap `student/lab.c` | **Practical 2 only**, including same-graph comparison | Lazy-duplicate parser/path API | [Week 11 page](student_question_bank/week_11_dijkstra.md) |
| 12 | BST-to-AVL — [Module 12](module_12_bst_avl/README.md): height/balance, rotations, AVL insertion, and validation | Ordinary lab 10 | AVL deletion and package extensions | [Week 12 page](student_question_bank/week_12_avl.md) |
| 13 | Searching, sorting, and consolidation — [Module 13](module_13_search_sort_consolidation/README.md): first-match linear/binary search, stable insertion/merge sorting, and structure selection | Lab artifact 11: one driver, traces, tests, and consolidation memo | Additional sorting algorithms, generic records, and benchmarking | [Week 13 page](student_question_bank/week_13_search_sort_consolidation.md) |
| 14 | Union-Find and Kruskal — [Week 14 materials](module_14_prim_kruskal/week_14/README.md); Prim demonstration only | Lab artifact 12: DSU, Kruskal, embedded synthesis, and capstone integration | Prim implementation, list repair, extended comparisons | [Week 14 page](student_question_bank/week_14_dsu_mst_capstone.md) |

## Required scope decisions

### Week 4 — Current integer-Stack lab

The required source is [Module 4 `student/lab.c`](module_04_stack/student/lab.c).
Trace A, B, C as character codes in `int stack[10]`, with empty `top == -1`,
full `top + 1 == capacity`, active indexes `0..top`, and item count and next
insertion index `top + 1`. Push increments before writing `stack[++top]`;
peek reads `stack[top]`; pop reads before decrementing with `stack[top--]`.
The full/empty predicates only report state. Callers must avoid a full push
or an empty peek/pop; those operations are unchecked.

First use the PPT’s direct two-Stack calculation of `1-2*3+4` to explain
waiting operators and values. The lab then separates conversion and evaluation
while reusing the same global integer Stack. `convert_to_postfix()` resets
`top = -1` and writes to `postfix` using local output position `pos`. It
scans `eq` until its terminator. `while (!is_empty())` guards each operator
read; `break` stops when the waiting operator has lower precedence. No
sentinel is stored. After draining operators, the explicit statement
`postfix[pos++] = '\0'` writes index 7 for the canonical expression, leaving
`pos == 8` and `top == -1`. Evaluation resets `top = -1`, scans postfix to
its terminator, and returns the final pop. The expression becomes `123*-4+`
and evaluates to -1.

Then trace `infix_to_postfix_parentheses()` with `eq_paren = "1+(2+3)"`.
An opening parenthesis is a barrier. On a closing parenthesis, pop while
nonempty; if the popped item is `(`, break without writing it. Otherwise,
write that operator and continue. The output is `123++`, explicitly terminated at
index 5, and evaluates to 6. Both converters leave `top == -1` after draining.

Core examples are nonempty valid expressions of at most seven characters
plus a terminator in an eight-character buffer. Operands are single digits
and binary operators are `+ - * / %`; only the dedicated converter accepts
balanced parentheses. Shorter valid strings work. Spaces, unary signs, and
multi-digit operands are unsupported. Divisors must be nonzero and integer
intermediates representable. These assumptions are not checked rejections.
Use the current lab demo, eight baseline test groups, and three justified
added LIFO, boundary-predicate, and valid-expression cases. The checked
caller-owned integer library remains an optional extension. Preserve the
five release gates, three-target pause, and standard/linear alternatives.

### Week 5 — Tree DFS

The [Module 5 textbook](module_05_tree_dfs/student/textbook.md) focuses on
preorder, inorder, and postorder using explicit stacks without recursion.
Students trace the saved branches, ancestors, and completed subtrees, then
connect these states to the recursion introduced in Module 2. Count `O(n)`
work and distinguish `O(h + 1)` used stack entries from the example's fixed
reserved capacity. The existing package lab remains a separate exercise;
this textbook revision does not change its submission requirements.

### Week 6 — Graph DFS and Practical 1

Required work from [Module 6](module_06_graph_dfs/README.md) is one complete
graph DFS implementation: the iterative version using a supplied vertex-ID
Stack that preserves Week 4's LIFO behavior under a Module 6 storage policy.
Students must still trace discovery, handle cycles and disconnected input,
and justify traversal cost. Recursive graph DFS is extension work.

Practical 1 is the only required graded submission for Week 6. Its bounded
Graph DFS task is the implementation evidence for the week; do not also
assign the standalone Module 6 lab.

### Week 7 — Linked lists with a linked queue example

Use the [current textbook](module_07_linked_list/student/textbook.md),
[class workbook](module_07_linked_list/student/class_material.md),
[Module 7 lab](module_07_linked_list/student/lab.md), and
[instructor plan](module_07_linked_list/instructor/lesson_plan.md).
The source of truth is [`student/lab.c`](module_07_linked_list/student/lab.c):
ten fixed nodes, integer `next` links, and `-1` for no node. Students trace
`init_lnodes_pool`, `new_lnode(data_value, next_value)`, and `free_lnode`; insert
with `link_lnode`; detach with `delete_next_lnode`; and recycle a detached
slot as a separate action.
This pool reserves storage in advance. It does not use `malloc` or C `free`.

Use a linked FIFO queue as the application of those links. First trace the
node-level helpers: `enqueue_lnode(node)` appends a detached allocation;
`dequeue_lnode()` returns a slot without recycling it, or `-1` when empty.
Then expose the value interface: `enqueue(value)` allocates internally and
returns `false` without changes if no slot is available. `dequeue()` returns
the payload and recycles the slot internally. Trace `head`/`tail` across empty,
singleton, and multiple-node states. Check `is_empty_queue()` before public
dequeue; its assertion diagnoses an empty call but is disabled by `NDEBUG`.
Payload `-1` is valid and must not be interpreted as the public queue's empty
result. Perform enqueue calls outside assertions so release builds retain them.

One artifact contains pool/link and linked-queue code, boundary tests, state traces,
an ArrayList/list comparison, and a corrected explanation. Trace a live
chain separately from the free chain and preserve a removed node's successor
before recycling changes its `next` field. Compare constant local work after
a known predecessor with linear traversal to find that predecessor. The older
allocated-list API, allocation-failure hooks, destruction exercise, and
doubly linked lists remain optional reference work. DSU is first taught and
assessed with Kruskal in Week 14. Array queue comparisons and both BFS
applications are taught in Week 8. The linked queue is the bridge between weeks.

| Required contact activity | Minutes |
|---|---:|
| ArrayList comparison and index-linked node model | 20 |
| Free-chain initialization and allocation | 35 |
| Predecessor insertion and detachment | 35 |
| Recycling, exhaustion, and reuse | 30 |
| Linked queue as a list application | 35 |
| Caller tests, costs, corrections, and Module 8 transfer | 25 |
| **Total** | **180** |

### Week 8 — Queues, tree BFS, and graph BFS, one submission

[Module 8](module_08_graph_bfs/README.md) retrieves Week 7's linked FIFO
queue before applying it to trees and graphs. Begin with its `head`/`tail`
transitions and node recycling. Then compare the linear and circular `queue[25]` variants
in [`student/queue.c`](module_08_graph_bfs/student/queue.c). Linear storage
allows 25 total writes before reset; circular storage wraps modulo 25 and
reserves one slot, leaving 24 usable positions. Callers check predicates
before unchecked array operations and reset `front = 0; rear = -1;` between
array experiments. Both BFS implementations use the linked queue from
Module 7 rather than these array variants. Linear comparison operations use
`enqueue_linear`, `dequeue_linear`, `is_empty_linear`, and `is_full_linear`
to distinguish them from the public linked-queue operations.

Use [`student/tree_bfs.c`](module_08_graph_bfs/student/tree_bfs.c) to trace
level-order processing of Module 2's F-root tree: `F,A,G,B,C,D,E`. Enqueue
each valid left child before the right child. A valid tree has no shared
children or cycles. Compare its frontier with Module 5/6's Stack/LIFO choice.
Tree BFS is required within this lesson and shares its single submission.

Then follow the complete maze BFS in
[`student/lab.c`](module_08_graph_bfs/student/lab.c). The 7 × 7 occupancy grid defines
an implicit graph: each passage has at most four neighbors. It is not a
`V × V` adjacency matrix.

Before each independent traversal, initialize the otherwise-unused node pool
with `init_lnodes_pool()` and set `head = tail = -1`. A worklist node's pool
index differs from the tree/cell ID stored in its `data` field. BFS calls
`enqueue(id)` and `dequeue()` through the public value interface; dequeue
copies the data and recycles the slot internally before BFS adds children
or neighbors. Do not free a public dequeue result. Execute enqueue outside
assertions, then check its saved Boolean result. The ten-slot pool limits simultaneous pending work, not total
processed items. The supplied tree peaks at three pending nodes; the maze
from `{1,1}` peaks at four and all supplied-maze starts peak at six.

Trace maze start `{1,1}` using right, left, down, up. Initialize `info`
before every independent maze run as well as resetting the linked queue. A distance
below 25 records discovery before enqueue. An equal shortest arrival adds
another predecessor without reenqueuing. The target `{5,5}` has distance 8,
two immediate predecessors, and three complete shortest routes. Students
add a driver and checks, recover one route, and explain the distinction
between one chosen predecessor and the full `prev[0..prev_size)` list.
The maze imports Module 8's queue source and needs no DFS include.

The Week 8 submission contains queue tests, the tree-BFS trace, the maze
caller and checks, path recovery, and a FIFO/DFS explanation in **one artifact**,
with one rubric and one due date. The older
checked matrix/list API, all-route printer, and generalization beyond the
fixed border/capacity contract are optional. Height, balance-factor, and
rotation work belongs to [Module 12](module_12_bst_avl/README.md).

A workable 180-minute contact budget is:

| Activity | Minutes |
|---|---:|
| Retrieve the linked queue and compare linear/circular arrays | 60 |
| Tree BFS: level-order processing and FIFO trace | 30 |
| Graph/maze BFS: discovery, distances, predecessors, and path recovery | 60 |
| Tests, costs, corrections, and single-submission synthesis | 30 |
| **Total** | **180** |

### Week 9 — Hash Table within 180 minutes

Required work follows [Module 9's supplied lab.c](module_09_hash_table/student/lab.c).
Students trace ten bucket heads and separate chains using Module 7's shared
`lnodes[10]` pool. They explain signed-remainder normalization, prepend order,
payload lookup, and whole-chain recycling. They then compare `two_sum_bf`
with `two_sum_ht`, which stores earlier `nums` positions and searches for a
complement before inserting the current position. The lab implementation is
supplied; students write a driver rather than complete map-operation TODOs.
Follow the [Week 9 lesson plan](module_09_hash_table/instructor/lesson_plan.md).

One submission contains three original test groups: hash calculation and
collision chains; pool lifecycle, exhaustion, and reuse; and two-sum results,
misses, repeated calls, distinct-position checks, and duplicate-input behavior.
Preserve predicted bucket/node/free-chain states and warning-enabled output.
Initialize the unused pool with `init_lnodes_pool()` before the first run;
`init_hashtable()` recycles active chains but does not create the free pool.

Compare the 45 candidate pairs in a complete ten-number brute-force miss
with the selected-chain work. State expected lookup `O(1+n/b)` under suitable
distribution for `n` records and `b` buckets, and quadratic generalized
two-sum worst cases when candidates collide. The actual source fixes both
buckets and nodes at ten. Linear probing, tombstones, dynamic allocation,
growth, compaction, and the older deletion autopsy are optional reference
work, not additional requirements.

### Week 10 — Integer Heaps and Shared On-Time

[Module 10](module_10_binary_heap/README.md) follows its current
[student/lab.c](module_10_binary_heap/student/lab.c). Students trace and test
the supplied fixed integer min/max Heap, including bottom-up construction.
They then trace ten-device closed intervals using a max-on ID Heap, min-off
ID Heap, current epochs, two inverse position maps, and local key repair.
The code and driver evidence form **one artifact**, with one rubric and due date.

Use all ten IDs, each with one through five nonnegative, ordered disjoint
intervals. Callers enforce capacity, nonempty removal, valid IDs, and interval
bounds. Dynamic allocation, alert arrival sequences, comparison counters,
and status-return contracts belong to the optional alert-record library and
[baseline](module_10_binary_heap/priority_queue_baseline/README.md).
They are not required implementations or a second submission.

| Activity | Minutes |
|---|---:|
| Numeric priority, complete shape, formulas, and min/max order | 35 |
| Add/remove, up/down repair, bottom-up rebuild, and pause | 65 |
| Two ID heaps, epochs, callbacks, maps, and interval search | 60 |
| Tests, costs, evidence, correction, and exit synthesis | 20 |
| **Total** | **180** |

### Week 11 — Dijkstra and Practical 2

[Module 11](module_11_graph_dijkstra/README.md) follows the complete updated
`student/lab.c`. Students trace a ten-node indexed minimum Heap, strict
relaxation, live inverse positions, and unreachable distances, then write
focused assertion tests. Practical 2 is the week's only submission. Include
the same-graph BFS/linear-minimum-selection/indexed-Heap comparison in that
artifact within 180 minutes. The raw code assumes valid node IDs, positive
`int` weights, and representable sums; it supplies no parser, predecessor
output, overflow guard, or lazy duplicate snapshots. The older C API is an
optional reference, not extra implementation work. Follow the package's
[Week 11 plan](module_11_graph_dijkstra/instructor/lesson_plan.md).

### Week 12 — BST to AVL within 180 minutes

[Module 12](module_12_bst_avl/README.md) supplies the combined tree unit.
Follow the complete indexed `student/lab.c`: ten character records,
integer links, separate edge heights, and four link-only rotation helpers.
Use the driver BST baseline to compare the seven-label ascending,
descending, and mixed orders. Students trace the supplied insertion,
validate its links/heights/balance, and extend three assertion-test groups
in one submission. Equal labels on distinct IDs are allowed; no allocation
or duplicate-rejection TODO is required. The pointer library and deletion
remain optional. Follow the
[70 + 110 minute plan](module_12_bst_avl/instructor/lesson_plan.md).

### Week 13 — Searching, sorting, and consolidation within 180 minutes

Use [Module 13](module_13_search_sort_consolidation/README.md) and its
[current lab](module_13_search_sort_consolidation/student/lab.md).
Students trace and test supplied linear search, first-match binary search,
stable insertion sort, and stable merge sort. Both searches return the first
matching index or `-1`; binary search requires sorted input. Use
`[31,23,17,8,17,42]` throughout. Linear search finds 17 at index 2 before
sorting; sorting produces `[8,17,17,23,31,42]`, where first-match binary
search returns index 1. Sorting changes positions, so an index always refers
to the current array order.

Keep the implementation bounded to 64 integers. Merge sort uses a supplied,
writable, disjoint scratch buffer with room for the active values. Compare
insertion sort's local shifts with merge sort's combining passes. Use tagged
equal-key records in the paper trace to explain stability; an integer-only
output does not establish the order of equal records.

Consolidate earlier representations through a workload-selection memo:
ArrayList and linked-list access/mutation; hash versus BST/AVL lookup;
Heap priority versus complete sorting; DFS/BFS frontier order; and the
minimum-hop versus weighted-route objectives. Reuse earlier tested code.
Do not require a new implementation of every earlier structure. Sorted
edge order prepares the supplied Kruskal comparator in Module 14; DSU is
introduced there.

One artifact contains search/sort traces, a driver with original checks,
compiler output, cost reasoning, the consolidation memo, and a corrected
prediction. It is one submission and one rubric.

| Required contact activity | Minutes |
|---|---:|
| Retrieval, linear search, and first-match binary search | 35 |
| Stable insertion sort and merge sort | 55 |
| Tests and observed results | 25 |
| Structure-selection consolidation | 45 |
| Corrections and submission | 20 |
| **Total** | **180** |

### Week 14 — Union-Find and Kruskal within 180 minutes

Use the [combined Week 14 materials](module_14_prim_kruskal/week_14/README.md).
DSU is introduced here, not assumed from an earlier week. Students complete
iterative two-pass find with path compression, union by component size, and
the Kruskal selection loop. Make-set, graph construction/loading, edge-list
building, sorting with a safe comparator, and checked totals are supplied.

Prim is a short instructor demonstration connecting heaps and Dijkstra to MST;
there are no student Prim TODOs. DSU tests, Kruskal tests, an individual
synthesis, and the capstone integration checkpoint form one artifact.
The capstone starts in Week 3 and is assembled incrementally through Week 13;
Week 14 adds DSU/Kruskal to that existing project. The capstone grade covers
integration/report/defense rather than scoring the lab's algorithm criteria twice.

| Required contact activity | Minutes |
|---|---:|
| Components, MST objective, and cycle decisions | 20 |
| Parent/size arrays, find/compression, and union trace | 30 |
| Implement and test find and union in supplied DSU scaffold | 40 |
| Sorted-edge trace, Kruskal implementation and tests | 50 |
| Supplied Prim demonstration and shortest-path comparison | 10 |
| Individual synthesis and capstone integration checkpoint | 20 |
| Correction and submission | 10 |
| **Total** | **180** |

## Release rules for the compressed path

1. Keep all 14 complete packages, staged archives, solutions, tests, and
   instructor notes available to faculty. Compression changes assignment
   scope, not the resource library.
2. For an ordinary week, use the week-specific bounded scope in this guide
   and the linked package lesson-plan override. Do not infer that every file
   in a complete staged release is required merely because the week draws
   from one package.
3. In Week 6, release only the Module 6 preparation and support needed for
   Practical 1. Do not release its complete Stage E as an additional required
   lab.
4. In Week 8, use the current Module 8 release for queues, tree BFS, and
   graph/maze BFS, with their tests, traces, and frontier-control synthesis
   in one submission. Include its queue source, tree bridge, maze source,
   and required Module 2 tree and Module 7 pool dependencies.
5. In Week 9, release the current Module 9 `student/lab.c`, its Module 7
   node-pool dependency, and the driver/evidence materials. Preserve the
   repository-relative layout required by the source include. The older
   open-addressed map is optional and supplies no required implementation TODOs.
6. In Week 10, release the current Module 10 `student/lab.c` and its driver,
   trace, and evidence materials. Teach integer min/max repair and construction,
   then the ten-ID dual-Heap interval search. The alert-record library and
   unsorted baseline are optional references with separate contracts.
7. In Week 11, release only the preparation and support for Practical 2.
   Week 12 uses the bounded BST-to-AVL package, with deletion optional.
   Week 13 uses the bounded searching/sorting source, its tests and traces,
   and a consolidation memo reusing previous artifacts.
8. In Week 14, release the combined DSU/Kruskal scaffold, not the complete
   combined List/DSU reference and complete Module 14 lab. Supply make-set, graph-loading, sorting,
   totals, validation, and Prim. Use one checklist for DSU, Kruskal,
   synthesis, and integration. Week 7 uses the current linked-list/node-pool release;
   DSU files in the full Module 7 reference are not Week 7 homework.
9. Do not relabel a hand-curated subset as an unchanged staged ZIP. Give it a
   week-specific name and a short manifest so students can distinguish the
   selected required materials from the complete optional package.
10. Extension work must be visibly labeled optional, must not gate later core
   work, and must not be required to recover points on the core submission.

## Contact-time control

Package lesson plans are resource-rich menus, not permission to exceed the
schedule. Before each week, the instructor selects activities whose displayed
times total no more than 180 minutes. If a required activity runs long, remove
an extension or shorten a second example; do not move the displaced package
lab into mandatory homework. The Week 8 and Week 10 budgets above are
the default cuts unless local evidence supports a smaller core.

The final-assessment capstone defense is not counted inside Week 14's 180
minutes. If no separate final-assessment period exists, the course calendar
must be renegotiated rather than silently adding an additional lecture-equivalent
workload to Week 14.
