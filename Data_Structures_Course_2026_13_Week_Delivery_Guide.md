# Data Structures Course 2026 — 13-Week Delivery Guide

## Purpose and authority

This is the operational delivery path for a course with **13 instructional
weeks**. The repository's 15 numbered teaching packages form an instructor resource
library; Priority Queue is integrated into Module 11, and Hash Table is
Module 10. Package numbers are stable resource identifiers, not teaching weeks. Module 14
contributes linked-node material in Week 7 and DSU in Week 13. A package README describes the complete deep-dive
version of that topic. When this guide narrows or combines a package, this
guide controls what is required in the 13-week offering.

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).

Each teaching week has a hard cap of **180 contact minutes**. The cap includes
retrieval, explanation, tracing, guided implementation, testing, and evidence
work. Material displaced by a combined or bounded week becomes extension
material; it is not reassigned as required asynchronous work.

The institution's scheduled final-assessment period is separate from the 13
teaching weeks and is used for the capstone defense or its approved equivalent.

## Assessment load at a glance

- **Eleven weekly lab artifacts:** Weeks 1–5, 7–10, and 12–13, including the combined Week 8 artifact and the folded Week 13 checkpoint.
- **Practical 1:** Week 6; it replaces the ordinary Graph DFS lab.
- **Practical 2:** Week 11; it replaces the ordinary Dijkstra lab.
- **Five spiral synthesis checks:** embedded in the Week 3 lab, Practical 1,
  Week 8 combined lab, Practical 2, and folded Week 13 artifact; they are not
  separate submissions.
- **Capstone:** built incrementally, integrated in Week 13, and defended in
  the scheduled final-assessment period.

There is at most one required programming submission in any teaching week.
The Week 8 submission combines evidence from two packages. Week 10 combines
the Priority Queue contract and Heap implementation inside Module 11. Each
has one submission, one due date, and one rubric. Week 13's
capstone integration checkpoint is folded into that week's work rather than
issued as a second weekly programming submission.

## Thirteen-week calendar

| Week | Required focus and package use | Required graded work | Extension only | Weekly vocabulary and questions |
|---:|---|---|---|---|
| 1 | Fixed-capacity ArrayList — [Module 1](module_01_arraylist/README.md) core | Ordinary lab 1: access, search, append, insert, and remove | Additional boundary and operation-sequence tests | [Week 1 page](student_question_bank/week_01_arraylist.md) |
| 2 | Array-indexed expression trees and recursive evaluation — [Module 2](module_02_binary_tree/README.md), with English and Korean textbooks | Ordinary lab 2: `new_node`, `term`, `terms`, and `eval_tree` | Additional valid expressions and construction/evaluation traces | [Week 2 page](student_question_bank/week_02_binary_tree.md) |
| 3 | Directed integer adjacency matrices — [Module 3](module_03_graph/README.md) core | Ordinary lab 3: initialize, add, remove, and count outgoing edges | Additional valid directed fixtures and traces | [Week 3 page](student_question_bank/week_03_graph_representations.md) |
| 4 | Integer Stack and postfix — [Module 4](module_04_stack/README.md) core | Ordinary lab 4: top-index integer Stack, `1-2*3+4 -> 123*-4+ -> -1`, and `1+(2+3) -> 123++ -> 6` using `student/lab.c` | Checked parsing/arithmetic and legacy integer API comparisons | [Week 4 page](student_question_bank/week_04_stack.md) |
| 5 | Preorder, inorder, and postorder using explicit stacks without recursion — [Module 5 textbook](module_05_tree_dfs/student/textbook.md) | Ordinary lab 5; existing package exercise remains separate from the textbook examples | Additional tree shapes and stack traces | [Week 5 page](student_question_bank/week_05_tree_dfs.md) |
| 6 | Graph DFS — [Module 6](module_06_graph_dfs/README.md), with iterative DFS using Stack as the implementation core | **Practical 1 only**; no ordinary Module 6 lab | Recursive graph DFS | [Week 6 page](student_question_bank/week_06_graph_dfs.md) |
| 7 | Linked lists and Queue — [Week 7 materials](module_07_queue/week_07/README.md); supplied circular-array comparison | Ordinary lab 6: one linked-Queue artifact | General list insertion/deletion, doubly linked lists, circular-Queue implementation | [Week 7 page](student_question_bank/week_07_queue.md) |
| 8 | BFS from trees to graphs — [Module 8](module_08_tree_bfs/README.md) is the short tree bridge; [Module 9](module_09_graph_bfs/README.md) supplies the main graph lab | **Combined lab 7: one submission** based on Graph BFS | Tree BFS implementation, shallowest search, and other Module 8 deep-dive work | [Week 8 page](student_question_bank/week_08_bfs.md) |
| 9 | Hash Table — [Module 10](module_10_hash_table/README.md): probing/mutations core plus supplied transactional-rebuild scaffold | Ordinary lab 8 | Additional capacity-policy and adversarial work | [Week 9 page](student_question_bank/week_09_hash_table.md) |
| 10 | Priority Queue contract to Binary Heap backend — [Module 11](module_11_binary_heap/README.md) contains the contract, supplied unsorted baseline, and Heap lab | **Lab 9: one submission** based on the Heap implementation and backend comparison | Student implementation of the supplied unsorted backend and other package extensions | [Week 10 page](student_question_bank/week_10_priority_queue_heap.md) |
| 11 | Dijkstra — [Module 12](module_12_graph_dijkstra/README.md): bounded relaxation/frontier core inside the supplied Practical scaffold | **Practical 2 only**; no ordinary Module 12 lab | Full standalone Stage E lab | [Week 11 page](student_question_bank/week_11_dijkstra.md) |
| 12 | BST-to-AVL — [Module 15](module_15_bst_avl/README.md): height/balance, rotations, AVL insertion, and validation | Ordinary lab 10 | AVL deletion and package extensions | [Week 12 page](student_question_bank/week_12_avl.md) |
| 13 | Union-Find and Kruskal — [Week 13 materials](module_16_prim_kruskal/week_13/README.md); Prim demonstration only | Lab artifact 11: DSU, Kruskal, embedded synthesis, and capstone integration | Prim implementation, list repair, extended comparisons | [Week 13 page](student_question_bank/week_13_dsu_mst_capstone.md) |

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

### Week 7 — Linked lists through a Queue

Use the [Week 7 student lesson and lab](module_07_queue/week_07/README.md)
and its [instructor plan](module_07_queue/week_07/instructor.md). Introduce
singly linked nodes, traversal, allocation, ownership, and cleanup through a
FIFO Queue. Students implement enqueue-at-tail and dequeue-at-head in a
supplied lifecycle scaffold. Removing the final node restores both pointers
to NULL. Supplied destruction is traced, run, and explained.

The circular-array implementation is supplied for wraparound tracing and
comparison; it is not a second implementation assignment. General list
insertion/deletion and doubly linked lists remain optional. One artifact
contains code, tests, a link/ownership trace, and the representation comparison.

| Required contact activity | Minutes |
|---|---:|
| FIFO and Stack contrast | 20 |
| Singly linked nodes, traversal, allocation, and ownership | 40 |
| Linked-Queue implementation | 55 |
| Supplied circular-array trace and representation comparison | 35 |
| Tests, correction, and BFS transfer | 30 |
| **Total** | **180** |

### Week 8 — One BFS arc, one submission

[Module 8](module_08_tree_bfs/README.md) is a bridge, not a standalone unit in
this delivery path. Its required contribution is limited to:

- tracing a Queue of tree nodes through a left-first level-order visit;
- explaining why Queue order produces nondecreasing depth; and
- reading and running a supplied short level-order scaffold.

Do not require the Module 8 tree-BFS implementation, its separate lab, or a
separate evidence packet. Shallowest-value search and its autopsy are
optional. Height, balance-factor, and rotation work is deferred to
[Module 15](module_15_bst_avl/README.md), where it supports AVL directly.

[Module 9](module_09_graph_bfs/README.md) is the main lab. Required work is
Graph BFS discovery, distance, predecessor, and path reconstruction, with
cycle, unreachable, and representation tests. The Week 8 submission contains
the brief tree trace and the Graph BFS code/evidence in **one combined
artifact**. It has one rubric and one due date.

A workable 180-minute contact budget is:

| Activity | Minutes |
|---|---:|
| Queue retrieval and tree level-order trace | 35 |
| Transfer from tree frontier to graph discovery state | 35 |
| Graph BFS implementation and tests | 90 |
| Evidence, correction, and exit synthesis | 20 |
| **Total** | **180** |

### Week 9 — Hash Table within 180 minutes

Required work from [Module 10](module_10_hash_table/README.md) is bounded
probing, exact lookup, insert/update, deletion, tombstone reuse, and the
associated collision/wraparound traces. Students complete and test selected
decision/commit points in a supplied transactional grow/compact scaffold;
they do not build every rebuild mechanism from scratch. Follow the package’s
[Week 9 delivery override](module_10_hash_table/instructor/lesson_plan.md).

Students author the three categories already named in the package test
template: collision/wraparound with exact probes; tombstone-safe update,
reuse, and duplicate prevention; and scaffolded growth/compaction with one
forced maintenance-allocation failure and state preservation. They run an
instructor-supplied suite for missing/key-zero behavior, additional allocation
failures, maximum capacity, invalid state, validation, destruction, and long
churn. Additional adversarial and capacity-policy work is extension.

### Week 10 — Priority Queue contract to Heap backend

[Module 11](module_11_binary_heap/README.md) contains the stable-minimum
Priority Queue contract, comparator/tie rule, an unsorted-array trace, and the
cost baseline alongside the Heap implementation. Its
[supplied baseline](module_11_binary_heap/priority_queue_baseline/README.md)
provides verified unsorted-array code for inspection and comparison. Students
use it as a reference, with no separate baseline implementation or submission.

In the same Module 11 lab, students
implement the Heap-backed version, test sift-up/sift-down and stable ties,
check the Heap invariant, and compare measured or counted work with the
supplied unsorted baseline. The implementation and comparison form **one
combined artifact**, with one rubric and one due date.

A workable 180-minute contact budget is:

| Activity | Minutes |
|---|---:|
| Priority Queue contract, comparator, and unsorted-baseline trace | 40 |
| Heap shape, order, and index relationships | 35 |
| Heap implementation, tests, and backend comparison | 85 |
| Evidence, correction, and exit synthesis | 20 |
| **Total** | **180** |

### Week 11 — Dijkstra and Practical 2

[Module 12](module_12_graph_dijkstra/README.md) supplies the Dijkstra model,
but Practical 2 is the week’s only submission. Students complete the bounded
relaxation/frontier core and required tests inside a supplied weighted-graph,
Heap, and path-reconstruction scaffold. The linear-Priority-Queue comparison
uses an instructor-supplied reference. Do not assign the full Stage E lab or
the Spiral 4 comparison as additional work; both are represented inside the
practical. Follow the package’s [Week 11 delivery override](module_12_graph_dijkstra/instructor/lesson_plan.md).

### Week 12 — BST to AVL within 180 minutes

[Module 15](module_15_bst_avl/README.md) supplies the combined tree unit.
Start with the supplied BST search/insertion baseline and demonstrate how
ordered input creates a chain. Introduce edge height, balance factors,
rotations, AVL insertion, and validation. Students complete one AVL lab;
BST deletion and AVL deletion are optional. Follow the existing
[70 + 110 minute plan](module_15_bst_avl/instructor/lesson_plan.md).

### Week 13 — Union-Find and Kruskal within 180 minutes

Use the [combined Week 13 materials](module_16_prim_kruskal/week_13/README.md).
DSU is introduced here, not assumed from an earlier week. Students complete
iterative two-pass find with path compression, union by component size, and
the Kruskal selection loop. Make-set, graph construction/loading, edge-list
building, sorting with a safe comparator, and checked totals are supplied.

Prim is a short instructor demonstration connecting heaps and Dijkstra to MST;
there are no student Prim TODOs. DSU tests, Kruskal tests, an individual
synthesis, and the capstone integration checkpoint form one artifact.
The capstone starts in Week 3 and is assembled incrementally through Week 12;
Week 13 adds DSU/Kruskal to that existing project. The capstone grade covers
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

1. Keep all 15 complete packages, staged archives, solutions, tests, and
   instructor notes available to faculty. Compression changes assignment
   scope, not the resource library.
2. For an ordinary week, use the week-specific bounded scope in this guide
   and the linked package lesson-plan override. Do not infer that every file
   in a complete staged release is required merely because the week draws
   from one package.
3. In Week 6, release only the Module 6 preparation and support needed for
   Practical 1. Do not release its complete Stage E as an additional required
   lab.
4. In Week 8, use a faculty-curated Module 8 trace/scaffold (for example, the
   level-order portions of its investigation and diagram) and use Module 9
   Stage E for the programming lab. Do **not** assign both Module 8 Stage E and
   Module 9 Stage E. The omitted Module 8 lab remains optional enrichment.
5. In Week 9, use a faculty-curated Module 10 Hash Table starter that supplies
   the non-core rebuild mechanics and exposes only the bounded decision/commit
   work described above.
6. In Week 10, use Module 11 inquiry/contract/cost materials and its verified
   unsorted-array baseline, then use Module 11 Stage E for the Heap lab. The
   baseline is supplied; its optional implementation is not a second project.
7. In Week 11, release only the preparation and support for Practical 2.
   Week 12 uses the bounded BST-to-AVL package, with deletion optional.
8. In Week 13, release the combined DSU/Kruskal scaffold, not the complete
   Module 14 and Module 16 labs. Supply make-set, graph-loading, sorting,
   totals, validation, and Prim. Use one checklist for DSU, Kruskal,
   synthesis, and integration. Week 7 likewise uses its linked-Queue scaffold
   instead of requiring the original circular-Queue implementation lab.
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

The final-assessment capstone defense is not counted inside Week 13's 180
minutes. If no separate final-assessment period exists, the course calendar
must be renegotiated rather than silently adding an additional lecture-equivalent
workload to Week 13.
