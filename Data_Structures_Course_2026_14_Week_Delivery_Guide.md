# Data Structures Course 2026 — 14-Week Delivery Guide

## Purpose and authority

This is the operational delivery path for a course with **14 instructional
weeks**. The repository's 14 numbered teaching packages form an instructor resource
library; Priority Queue is integrated into Module 10, and Hash Table is
Module 9. Package numbers follow teaching Weeks 1–14. Module 7
teaches index-linked lists with linked stack and queue applications in Week 7
and retains DSU references used by Week 14. Module 8 compares queue
representations, traces tree level order, and uses a coordinate array queue for maze BFS.
A package README describes the complete deep-dive
version of that topic. When this guide narrows or combines a package, this
guide controls what is required in the 14-week offering.

**Modules 12–13 planning update — 2026-11-10:** Week 12 is Binary Search
and BSTs; Week 13 is AVL Rotations and Review. The sequence, goals, and
assessment outlines below are approved planning guidance. Existing textbooks,
worksheets, lab guides, detailed lesson plans, tests, releases, and question
banks for these two weeks await alignment. Their old week labels do not
override this guide. No revised student release is supplied by this update.

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).
Its Week 12–13 pages await alignment; select questions by the revised scope.

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
| 7 | Linked lists with linked stack and queue examples — [textbook](module_07_linked_list/student/textbook.md) and [Module 7 materials](module_07_linked_list/README.md) | Ordinary lab 6: shared-pool reuse, predecessor insertion/detachment, LIFO first-node operations, FIFO endpoints, and traces/tests in one artifact | Allocated-list API, doubly linked lists, and DSU before Week 14 | [Week 7 page](student_question_bank/week_07_linked_list.md) |
| 8 | Processing data in stored order: queues → tree BFS → graph BFS — [Module 8](module_08_graph_bfs/README.md): array queue comparisons, tree level order, maze discovery/distances, and conceptual path recovery | **Lab 7: one submission** with queue checks, tree and maze traces, driver, and explanation | Checked matrix/list API, predecessor implementation, and larger-maze generalization | [Week 8 page](student_question_bank/week_08_bfs.md) |
| 9 | Hash Table — [Module 9](module_09_hash_table/README.md): fifteen buckets, ten key/data nodes, whole-table reset, and two sum in the supplied lab.c | Ordinary lab 8: one driver and evidence submission | Older open-addressed map, resizing, and adversarial extensions | [Week 9 page](student_question_bank/week_09_hash_table.md) |
| 10 | Integer min/max Heaps and shared on-time — [Module 10](module_10_binary_heap/README.md) follows current lab.c | **Lab 9: one submission** of driver, tests, traces, maps, and interval reasoning | Alert-record Heap, dynamic allocation, and unsorted-baseline implementation | [Week 10 page](student_question_bank/week_10_priority_queue_heap.md) |
| 11 | Dijkstra — [Module 11](module_11_graph_dijkstra/README.md): trace and test the supplied indexed-Heap `student/lab.c` | **Practical 2 only**, including same-graph comparison | Lazy-duplicate parser/path API | [Week 11 page](student_question_bank/week_11_dijkstra.md) |
| 12 | Binary Search and BSTs — [Module 12](module_12_bst_avl/README.md): first-match binary search, BST search/insertion, inorder, height, and skew | Ordinary lab 10: one search/BST evidence artifact | BST deletion, sorting implementations, and package extensions | [Existing Week 12 page — pending alignment](student_question_bank/week_12_avl.md) |
| 13 | AVL Rotations and Review — [Module 13](module_13_search_sort_consolidation/README.md): balance, four rotation cases, guided insertion, and course review | Lab artifact 11: AVL evidence and a review memo in one submission | AVL deletion, insertion/merge-sort instruction, and package extensions | [Existing Week 13 page — pending alignment](student_question_bank/week_13_search_sort_consolidation.md) |
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

### Week 7 — Linked lists with linked stack and queue examples

Use the [current textbook](module_07_linked_list/student/textbook.md),
[class workbook](module_07_linked_list/student/class_material.md),
[concept slides](module_07_linked_list/student/ppt_material.md),
[Module 7 lab](module_07_linked_list/student/lab.md), and
[instructor plan](module_07_linked_list/instructor/lesson_plan.md).
The source of truth is [`student/lab.c`](module_07_linked_list/student/lab.c):
ten fixed nodes, integer `next` links, and `-1` for no node. Students trace
`init_lnodes_pool` (first call only), `new_lnode()`, and `free_lnode`; callers assign payload explicitly, insert
with `simple_link_lnode_to_prev`, detach/isolate with `simple_delink_next_lnode_from_prev`, and recycle as a separate action. Later initializer calls are no-ops; independent runs need all owned nodes recycled or a new process.
This pool reserves storage in advance. It does not use `malloc` or C `free`.

Follow the slide sequence: an acyclic chain with a separately stored first
index; predecessor insertion/deletion and safe write order; shared-pool
benefits and link/traversal costs; free-chain allocation/recycling; then the
linked stack and queue. Multiple lists can use the same pool while keeping
their live slots disjoint. Omitted recycling makes a detached slot unavailable;
double recycling corrupts the free chain. After a slot is recycled, its former
owner must stop reading or writing it because it may serve the free chain or
another list.

For the linked stack, keep a caller-owned `first`. Allocate/check, assign data, set next to its old first, and update `first` only after allocation succeeds. For removal,
check nonempty, save the old first and its value, advance `first` to its successor,
isolate old.next=-1, and recycle the old slot. Inputs 17,23,31 leave as 31,23,17. This is a caller-side
application of the supplied primitives; the lab does not supply a separate
linked-stack API.

Use a linked FIFO queue as the application of those links. First trace the
node-level helpers: `enqueue_lnode(node)` appends a detached allocation whose `next` is `-1`;
`dequeue_lnode()` returns a slot without recycling it, or `-1` when empty.
Trace `qhead`/`qtail` across empty, singleton, and multiple-node states. Allocation/check/data assignment precedes the void append; successful removal returns an isolated node index. The caller copies data and explicitly recycles once. Empty removal returns -1 unchanged; data -1 is valid. The supplied Module 7 has no value wrappers. Module 8 instead stores coordinates directly in an array queue. Execute mutations outside assertions. Keep invalid non-sentinel indices and ownership violations on paper.

One artifact contains pool/link callers and linked stack/queue evidence, boundary tests, state traces,
an ArrayList/list comparison, and a corrected explanation. Trace a live
chain separately from the free chain and preserve a removed node's successor
before recycling changes its `next` field. Compare constant local work after
a known predecessor with linear traversal to find that predecessor. The older
allocated-list API, allocation-failure hooks, destruction exercise, and
doubly linked lists remain optional reference work. DSU is first taught and
assessed with Kruskal in Week 14. Array queue comparisons and both BFS
applications are taught in Week 8. The FIFO rule is the bridge between weeks.

| Required contact activity | Minutes |
|---|---:|
| ArrayList comparison and acyclic index-linked node model | 20 |
| Predecessor insertion/detachment and safe write order | 30 |
| Shared pool, allocation/recycling, exhaustion, and stale access | 35 |
| Linked stack with caller-owned first index | 25 |
| Linked queue as a list application | 35 |
| Caller tests, costs, corrections, and Module 8 transfer | 35 |
| **Total** | **180** |

### Week 8 — Processing data in stored order, one submission

[Module 8](module_08_graph_bfs/README.md) recalls Week 7's FIFO rule and
implements waiting order with array positions. The current PPTs label the
lesson 10주차; the repository keeps Chapter/Module 8 as its resource number. The bilingual textbook is **Processing data in stored order** / **저장된 순서대로 데이터 처리하기**. The English edition follows the Korean manuscript frozen on 2026-11-03. Its `Invariant` section explains nondecreasing pending distances and first-discovery shortest paths under equal move costs. The three new C topics are nested two-dimensional initializer braces, whole-structure copying/passing/returning, and short-circuit OR. Other syntax is review; these explanations add no separate artifact.

Compare linear and circular queues with `front` as the first queued data’s index
and `rear` as the last queued data’s index when nonempty. An empty queue has
neither first nor last data. Linear storage permits 25 total writes
per reset. Under the illustrated circular convention, empty is
`front == (rear + 1) % 25` and full is `front == (rear + 2) % 25`;
one reserved slot leaves room for 24 pending values. The actual maze lab
uses the linear version, with unchecked enqueue/dequeue operations.

Trace the illustrative tree A(B(D,E),C(F)) on paper. Appending children
left before right produces A, B, C, D, E, F with depths 0, 1, 1, 2, 2, 2.
Track a level with stored depths or the number waiting when that level
begins. Compare the order with stack-based DFS. A valid tree has no shared
child or cycle; graph search needs a discovery record. In the conceptual
pending-node DFS stack, an unprocessed neighbor may be pushed again and
already-processed popped copies are skipped. BFS records discovery before
enqueue and skips all later encounters, including nodes still waiting.
This comparison does not replace Chapter 6's recursive DFS implementation.

Follow the complete [maze lab](module_08_graph_bfs/student/lab.c).
It stores `struct point {y,x}` values directly in `queue[N*N]` and
uses a 5×5 wall-bordered maze. Edges are generated right, left, down, up.
`bfs` calls `init_bfs` on every run: reset front/rear, initialize all 25
distances to `INF`, then schedule a passage start at distance zero.
Every start must be in bounds. An in-bounds wall start leaves all distances
`INF` and the queue empty. Keep the outer border closed.

From `{1,1}`, all eight passages are reached. Target `{3,3}` has distance 4.
First discovery writes distance before enqueue; every later encounter is
skipped. The run performs eight insertions/removals and 32 direction checks,
peaks at three pending points, and finishes with `front=8,rear=7`.
The linear queue needs eight write positions despite its smaller pending peak.
The supplied code records distances only. Explain the slides' path idea by
remembering one predecessor at first discovery, then following it backward;
implementing route storage is optional.

Use [the separate lecture driver](module_08_graph_bfs/code/tests/test_lecture.c)
without modifying the supplied lab. Run `make -C module_08_graph_bfs/code lecture`.
Submit queue traces, the tree-level trace, maze distance/queue evidence,
one original caller-side check, and the FIFO/DFS explanation in **one artifact**.
The checked matrix/list API and larger-maze generalization remain optional.

| Activity | Minutes |
|---|---:|
| Recall FIFO and compare linear/circular arrays | 60 |
| Tree BFS: level order, depth, and queue trace | 30 |
| Graph/maze BFS: representation, iterator, discovery, and distances | 60 |
| Tests, costs, corrections, and conceptual path recovery | 30 |
| **Total** | **180** |

### Week 9 — Hash Table within 180 minutes

Required work follows the self-contained [Module 9 lab.c](module_09_hash_table/student/lab.c),
with the PPTs as conceptual references. Students trace fifteen bucket heads
and ten `hnode` records containing `key`, `data`, and `next`. They explain
signed normalization, head insertion, full-key comparison, duplicate-key
newest matches, and resetting the counter and bucket heads. No Module 7
source is imported. The PPT's five-node/seven-bucket example illustrates
the same representation with different constants and input.

Compare `two_sum_bf` with `two_sum_ht`. Both return `{j,i}`, with `j<i`.
Brute force decrements `j`; the hash version finds the complement among
stored keys and reads the earlier position from node data before inserting
the current `(nums[i],i)`. Both choose the latest matching earlier position.
The implementation is supplied; students write a separate assertion driver.
Follow the [Week 9 lesson plan](module_09_hash_table/instructor/lesson_plan.md).

One submission has three original groups: signed hashing and collision
chains; exhaustion, unchanged failure, reset and reuse; and two-sum hits,
misses, repeated calls, distinct positions, and duplicate values. Preserve
predictions and warning-enabled output. Call `initialize()` before manual
experiments; `two_sum_ht` calls it automatically at every entry. Reset
retains node fields and `answer` while making old chains unreachable.

A complete brute-force miss makes 45 comparisons and target 0 makes 11.
The target-0 hash trace compares one key. Generalized lookup has expected
`O(1+n/b)` cost under adequate distribution. Expected linear hash two-sum
requires bounded load, `b=Θ(n)`, and sufficient nodes; collision-heavy
searches can take quadratic work. Reset costs `Θ(b)`, with no node traversal.
The actual arrays fix ten nodes and fifteen buckets. Direct addressing,
open addressing, and Robin Hood hashing supply PPT context; implementing
probing, deletion, resizing, or the older library is optional.

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

<a id="week-12--bst-to-avl-within-180-minutes"></a>

### Week 12 — Binary Search and BSTs within 180 minutes

Use the revised [Module 12 overview](module_12_bst_avl/README.md) and
[Chapter 12 planning summary](instructor_guide/chapter_12.md). Begin with
linear search, then trace first-match binary search on supplied sorted
arrays. Binary search requires nondecreasing input and returns the smallest
matching index or `-1`. Use supplied unsorted and sorted copies to distinguish
their positions; students do not implement a sorting algorithm.

Transfer the elimination rule to BST ordering, search, insertion, and inorder
reasoning. Use Module 2's indexed-node representation and the existing plain
BST baseline as references. Compare ascending, descending, and mixed arrival
orders. Count one logical key comparison per visited node, and distinguish
edge height from node count. Search follows a path in `O(h + 1)` work; an
`n`-node chain has height `n - 1` and can require `O(n)` search work.

One artifact combines interval and BST traces, original search/insertion
checks, height/comparison evidence, and a corrected explanation. Finish with
ascending insertions producing a skewed tree: Week 13 will repair its shape.
AVL balance, rotations, and insertion are Week 13 learning. BST deletion is
outside required scope.

The existing [search/sort lab guide](module_13_search_sort_consolidation/student/lab.md),
[BST/AVL lab guide](module_12_bst_avl/student/lab.md), and
[detailed Week 12 lesson plan](module_12_bst_avl/instructor/lesson_plan.md)
await alignment. Use only relevant search/BST references; their complete
assignments are not the revised Week 12 submission.

| Required contact activity | Minutes |
|---|---:|
| Linear-search recap and first-match binary search on supplied sorted arrays | 45 |
| BST ordering, search, insertion, and inorder reasoning | 60 |
| Height, insertion-order effects, and search costs; finish with a skewed tree | 35 |
| Traces, checks, and one combined evidence artifact | 40 |
| **Total** | **180** |

<a id="week-13--searching-sorting-and-consolidation-within-180-minutes"></a>

### Week 13 — AVL Rotations and Review within 180 minutes

Use the revised [Module 13 overview](module_13_search_sort_consolidation/README.md)
and [Chapter 13 planning summary](instructor_guide/chapter_13.md). Retrieve
Week 12's skewed BST, establish edge height and balance, and introduce LL/RR
before LR/RL repairs. Preserve inorder, reachability, and transferred middle
subtrees. Trace guided AVL insertion, retain returned roots, and update
stored heights from the lower nodes upward. Full AVL deletion is outside
required scope.

The supplied indexed AVL source remains in Module 12. Its
[lab guide](module_12_bst_avl/student/lab.md) and Module 13's
[detailed lesson plan](module_13_search_sort_consolidation/instructor/lesson_plan.md)
await alignment; neither is the revised complete Week 13 assignment. Reuse
the existing source and checks selectively without requiring a new AVL
implementation or another earlier structure implementation.

Protect the final 60 minutes for review, corrections, and submission. Compare
ArrayList/list access and mutation, hash versus BST/AVL lookup, Heap priority,
DFS/BFS frontier control, and minimum-hop versus weighted-route objectives.
Keep a brief preparation-cost discussion: ordered snapshots support binary
search, but preparing and updating them costs work. Insertion-sort and
merge-sort instruction and implementation are optional. Module 14 supplies
edge sorting and its comparator; no sorting lesson is a prerequisite.

One submission combines four rotation traces, insertion/link/height/balance
checks, comparison evidence, a workload-selection review memo, and a corrected
prediction. The memo uses earlier evidence rather than new implementations.

| Required contact activity | Minutes |
|---|---:|
| Retrieve the skewed-tree problem; establish height and balance | 20 |
| LL/RR followed by LR/RL rotations, preserving ordering and middle subtrees | 55 |
| Guided AVL insertion: returned roots and bottom-up height updates | 30 |
| Rotation and insertion checks | 15 |
| Course review, workload selection, corrections, and submission | 60 |
| **Total** | **180** |

### Week 14 — Union-Find and Kruskal within 180 minutes

Use the [combined Week 14 materials](module_14_prim_kruskal/week_14/README.md).
DSU is introduced here, not assumed from an earlier week. Students complete
iterative two-pass find with path compression, union by component size, and
the Kruskal selection loop. Make-set, graph construction/loading, edge-list
building, sorting with a safe comparator, and checked totals are supplied.
Explain increasing edge-weight order and the supplied tie rule here without
assuming students completed insertion-sort or merge-sort instruction.
The existing Week 14 lab and detailed plan still refer to the former Module
13 sorting lesson; those prerequisite references await alignment and do not
add required sorting instruction to Week 13.

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
5. In Week 9, release the self-contained Module 9 `student/lab.c` and its
   driver/evidence materials. No Module 7 dependency is needed. Compile only
   the driver when it includes the lab. The older open-addressed map is
   optional and supplies no required implementation TODOs.
6. In Week 10, release the current Module 10 `student/lab.c` and its driver,
   trace, and evidence materials. Teach integer min/max repair and construction,
   then the ten-ID dual-Heap interval search. The alert-record library and
   unsorted baseline are optional references with separate contracts.
7. In Week 11, release only the preparation and support for Practical 2.
   Week 12 selects binary-search and ordinary-BST references for one evidence
   artifact. Week 13 selects indexed AVL references and earlier artifacts for
   rotation/insertion evidence and a review memo. Their existing lessons,
   question banks, and archives await alignment; this planning update does
   not issue revised releases. Do not assign either old full weekly lab.
   BST/AVL deletion and insertion/merge-sort instruction remain optional.
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
