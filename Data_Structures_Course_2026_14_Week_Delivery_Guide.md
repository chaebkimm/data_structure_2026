# Data Structures Course 2026 — 14-Week Delivery Guide

## Purpose and authority

This is the operational delivery path for a course with **14 instructional
weeks**. The repository's 16 numbered teaching packages remain intact as an
instructor resource library; package number and teaching week are no longer
the same after Week 7. A package README describes the complete deep-dive
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

- **Twelve weekly lab artifacts:** Weeks 1–5, 7–9, and 11–14, including the combined Weeks 8–9 artifacts and the folded Week 14 checkpoint.
- **Practical 1:** Week 6; it replaces the ordinary Graph DFS lab.
- **Practical 2:** Week 10; it replaces the ordinary Dijkstra lab.
- **Five spiral synthesis checks:** embedded in the Week 3 lab, Practical 1,
  Week 8 combined lab, Practical 2, and folded Week 14 artifact; they are not
  separate submissions.
- **Capstone:** built incrementally, integrated in Week 14, and defended in
  the scheduled final-assessment period.

There is at most one required programming submission in any teaching week.
The Week 8 and Week 9 submissions each use evidence from two packages but are
graded as one combined lab, with one due date and one rubric. Week 14's
capstone integration checkpoint is folded into that week's work rather than
issued as a second weekly programming submission.

## Fourteen-week calendar

| Week | Required focus and package use | Required graded work | Extension only | Weekly vocabulary and questions |
|---:|---|---|---|---|
| 1 | Fixed-capacity ArrayList — [Module 1](module_01_arraylist/README.md) core | Ordinary lab 1: access, search, append, insert, and remove | Additional boundary and operation-sequence tests | [Week 1 page](student_question_bank/week_01_arraylist.md) |
| 2 | Array-indexed expression trees and recursive evaluation — [Module 2](module_02_binary_tree/README.md), with English and Korean textbooks | Ordinary lab 2: `new_node`, `term`, `terms`, and `eval_tree` | Additional valid expressions and construction/evaluation traces | [Week 2 page](student_question_bank/week_02_binary_tree.md) |
| 3 | Directed integer adjacency matrices — [Module 3](module_03_graph/README.md) core | Ordinary lab 3: initialize, add, remove, and count outgoing edges | Additional valid directed fixtures and traces | [Week 3 page](student_question_bank/week_03_graph_representations.md) |
| 4 | Character Stack and postfix — [Module 4](module_04_stack/README.md) core | Ordinary lab 4: forward-growing character Stack and `1-2*3+4 -> 123*-4+ -> -1` using `student/lab.c` | Checked parsing/arithmetic and legacy integer API comparisons | [Week 4 page](student_question_bank/week_04_stack.md) |
| 5 | Preorder, inorder, and postorder using explicit stacks without recursion — [Module 5 textbook](module_05_tree_dfs/student/textbook.md) | Ordinary lab 5; existing package exercise remains separate from the textbook examples | Additional tree shapes and stack traces | [Week 5 page](student_question_bank/week_05_tree_dfs.md) |
| 6 | Graph DFS — [Module 6](module_06_graph_dfs/README.md), with iterative DFS using Stack as the implementation core | **Practical 1 only**; no ordinary Module 6 lab | Recursive graph DFS | [Week 6 page](student_question_bank/week_06_graph_dfs.md) |
| 7 | Queue and circular buffer — [Module 7](module_07_queue/README.md) core | Ordinary lab 6 | Package extensions | [Week 7 page](student_question_bank/week_07_queue.md) |
| 8 | BFS from trees to graphs — [Module 8](module_08_tree_bfs/README.md) is the short tree bridge; [Module 9](module_09_graph_bfs/README.md) supplies the main graph lab | **Combined lab 7: one submission** based on Graph BFS | Tree BFS implementation, shallowest search, and other Module 8 deep-dive work | [Week 8 page](student_question_bank/week_08_bfs.md) |
| 9 | Priority Queue contract to Binary Heap backend — [Module 10](module_10_priority_queue/README.md) supplies the contract and instructor-provided unsorted baseline; [Module 11](module_11_binary_heap/README.md) supplies the main Heap lab | **Combined lab 8: one submission** based on the Heap implementation and backend comparison | Student implementation of the Module 10 unsorted backend and other package extensions | [Week 9 page](student_question_bank/week_09_priority_queue_heap.md) |
| 10 | Dijkstra — [Module 12](module_12_graph_dijkstra/README.md): bounded relaxation/frontier core inside the supplied Practical scaffold | **Practical 2 only**; no ordinary Module 12 lab | Full standalone Stage E lab | [Week 10 page](student_question_bank/week_10_dijkstra.md) |
| 11 | Hash Table — [Module 13](module_13_hash_table/README.md): probing/mutations core plus supplied transactional-rebuild scaffold | Ordinary lab 9 | Additional capacity-policy and adversarial work | [Week 11 page](student_question_bank/week_11_hash_table.md) |
| 12 | Linked-list clinic and Union-Find — [Module 14](module_14_linked_list_dsu/README.md): one ownership repair plus DSU | Ordinary lab 10 | Remaining list operations and linked-backend work | [Week 12 page](student_question_bank/week_12_linked_list_dsu.md) |
| 13 | BST-to-AVL — [Module 15](module_15_bst_avl/README.md): height/balance, rotations, AVL insertion, and validation | Ordinary lab 11 | AVL deletion and package extensions | [Week 13 page](student_question_bank/week_13_avl.md) |
| 14 | Prim, Kruskal, and capstone integration — [Module 16](module_16_prim_kruskal/README.md): complete Kruskal core plus bounded decision checkpoints in supplied Prim | Lab artifact 12 folds in the individual synthesis and capstone-integration checkpoint | Full Prim implementation and package extensions | [Week 14 page](student_question_bank/week_14_mst_capstone.md) |

## Required scope decisions

### Week 4 — Current character-Stack lab

The required source is [Module 4 `student/lab.c`](module_04_stack/student/lab.c).
Trace A, B, C with empty `pos == 0`, full `pos == capacity`, active indexes
`0..pos - 1`, and next insertion index and item count `pos`. Full push is a silent no-op; empty
peek/pop return the null character and preserve state. Separate conversion
from evaluation: global `pos` counts character-Stack items, global `size`
counts postfix characters, and a separate local `pos` counts integer values.
The canonical expression converts to `123*-4+` with
size 7 and evaluates to -1.

Core examples assume valid nonempty expressions of at most seven characters,
with alternating single digits and `+ - * / %`, no spaces, parentheses,
unary operators, or multi-digit operands, nonzero divisors, and representable
integer intermediates. Those assumptions are not a promise of safe rejection.
Use the current lab demo/tests and three justified added LIFO, boundary, and
valid-expression cases. The checked caller-owned integer library remains an
optional extension, not a second required assignment. Preserve the five
release gates, three-target pause, and standard/linear response alternatives.

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

### Week 9 — Priority Queue contract to Heap backend

[Module 10](module_10_priority_queue/README.md) contributes the stable-minimum
Priority Queue contract, comparator/tie rule, an unsorted-array trace, and the
cost baseline. The instructor supplies a verified unsorted-array
implementation as readable baseline code; students do not complete the
Module 10 starter or submit a separate Module 10 project.

[Module 11](module_11_binary_heap/README.md) is the main lab. Students
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

### Week 10 — Dijkstra and Practical 2

[Module 12](module_12_graph_dijkstra/README.md) supplies the Dijkstra model,
but Practical 2 is the week’s only submission. Students complete the bounded
relaxation/frontier core and required tests inside a supplied weighted-graph,
Heap, and path-reconstruction scaffold. The linear-Priority-Queue comparison
uses an instructor-supplied reference. Do not assign the full Stage E lab or
the Spiral 4 comparison as additional work; both are represented inside the
practical. Follow the package’s [Week 10 delivery override](module_12_graph_dijkstra/instructor/lesson_plan.md).

### Week 11 — Hash Table within 180 minutes

Required work from [Module 13](module_13_hash_table/README.md) is bounded
probing, exact lookup, insert/update, deletion, tombstone reuse, and the
associated collision/wraparound traces. Students complete and test selected
decision/commit points in a supplied transactional grow/compact scaffold;
they do not build every rebuild mechanism from scratch. Follow the package’s
[Week 11 delivery override](module_13_hash_table/instructor/lesson_plan.md).

Students author the three categories already named in the package test
template: collision/wraparound with exact probes; tombstone-safe update,
reuse, and duplicate prevention; and scaffolded growth/compaction with one
forced maintenance-allocation failure and state preservation. They run an
instructor-supplied suite for missing/key-zero behavior, additional allocation
failures, maximum capacity, invalid state, validation, destruction, and long
churn. Additional adversarial and capacity-policy work is extension.

### Week 12 — Ownership clinic and DSU within 180 minutes

Required work from [Module 14](module_14_linked_list_dsu/README.md) is one
bounded ownership-sensitive list or linked-adjacency repair plus a tested DSU
with path compression and union by rank/size. Students trace the other
supplied list operations rather than implementing a small list library and a
second repair. The instructor demonstrates and runs the supplied edge-list
builder and safe comparator as a short Kruskal preview; it is not another
implementation or evidence packet. Follow the package’s
[Week 12 delivery override](module_14_linked_list_dsu/instructor/lesson_plan.md).

### Weeks 13–14 — AVL, MST, and integration

[Module 15](module_15_bst_avl/README.md) is the formal home for edge height,
balance factors, rotations, AVL insertion, and validation. AVL deletion is
extension work. Week 13 produces one lab artifact under the
[Week 13 delivery override](module_15_bst_avl/instructor/lesson_plan.md).

In [Module 16](module_16_prim_kruskal/README.md), students implement Kruskal
fully and finish/test bounded decision checkpoints in a supplied Prim
implementation. The algorithm comparison, embedded Spiral 5 individual check, and capstone
integration checkpoint form **one folded Week 14 artifact** and one contact
block. The weekly lab grade covers bounded MST work; the capstone grade covers
cross-module integration, the report, and the later defense, so the same code
is not scored twice for the same criterion. Follow the package’s
[Week 14 delivery override](module_16_prim_kruskal/instructor/lesson_plan.md).

## Release rules for the compressed path

1. Keep all 16 complete packages, staged archives, solutions, tests, and
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
5. In Week 9, use selected Module 10 inquiry/contract/cost materials and give
   students the verified unsorted-array implementation as a supplied
   baseline. Use Module 11 Stage E for the programming lab. Do **not** assign
   both Module 10 Stage E and Module 11 Stage E.
6. In Week 10, release only the Module 12 preparation and support needed for
   Practical 2. Do not add the complete Module 12 Stage E as a second graded
   project.
7. In Week 11, use a faculty-curated Module 13 starter that supplies the
   non-core rebuild mechanics and exposes only the bounded decision/commit
   work described above. In Week 12, release one selected ownership repair
   plus the DSU work, not the complete list-operation menu.
8. In Week 14, use one checklist for the folded MST/synthesis/integration
   artifact. Do not issue a separate individual-check or capstone-programming
   submission during the same teaching week.
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
lab into mandatory homework. The combined Week 8 and Week 9 budgets above are
the default cuts unless local evidence supports a smaller core.

The final-assessment capstone defense is not counted inside Week 14's 180
minutes. If no separate final-assessment period exists, the course calendar
must be renegotiated rather than silently adding a fifteenth lecture-equivalent
workload to Week 14.
