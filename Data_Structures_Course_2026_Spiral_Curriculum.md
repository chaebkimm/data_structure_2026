# Data Structures Course 2026

## Interleaved Spiral Curriculum for Cybersecurity Freshmen

### Curriculum status and assumptions

This document defines an operational **14-week curriculum supported by 14 teaching packages**. Priority Queue is part of Module 10, and Hash Table is Module 9. Module 7 covers linked lists with linked stack and queue examples. Module 8 compares array queues, traces tree level order, and uses a coordinate array queue for maze BFS. Teaching packages are numbered consecutively from 1 to 14, matching their teaching weeks. The exact required/extension split is collected in the [14-week delivery guide](Data_Structures_Course_2026_14_Week_Delivery_Guide.md). It assumes:

**Modules 12–13 planning update — 2026-11-10:** Module 12 covers Binary
Search and BSTs; Module 13 covers AVL Rotations and Review. Student lessons,
worksheets, lab guides, detailed lesson plans, tests, releases, and question
banks for these weeks await alignment. The module directories are now
`module_12_binary_search_bst` and `module_13_avl_review`; source files keep
their existing module grouping. This rename does not rewrite the lessons.

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).
Its Week 12–13 resources await alignment with the revised sequence.

- second-semester cybersecurity students;
- prior experience with C variables, functions, arrays, loops, and conditionals;
- limited fluency with pointers, dynamic allocation, and `struct`;
- approximately 3 contact hours per teaching week, delivered as two class meetings or an equivalent lecture/lab format; combined weeks selectively use two packages but still have one contact-time budget and one submission; capstone integration occurs in Week 14, while the defense or approved equivalent uses the institution’s scheduled final-assessment period;
- synthetic, instructor-controlled cybersecurity datasets rather than live-system scanning or exploitation;
- a C11-compatible compiler, strong compiler warnings, a debugger, automated tests, and memory/error sanitizers when the platform supports them.

The resource library is not organized as five consecutive linear modules, followed by five tree modules, followed by five graph modules. It makes five increasingly sophisticated passes, with the associative-index bridge in Module 9, binary search and BSTs in Module 12, and AVL rotations and course review in Module 13:

> **Linear/supporting ADT → Tree application → Graph generalization**

Students therefore encounter the same ideas—representation, invariants, traversal, frontier management, complexity, ownership, and failure—several times in different forms.

---

## 1. Course learning outcomes

By the end of the course, students will be able to:

1. Draw and explain the memory representation of array-backed, hash-table, pointer-linked, tree, heap, and graph structures.
2. Specify an abstract data type independently of its underlying representation.
3. Implement, test, and safely destroy core data structures in C.
4. State and check the representation invariant that makes each structure correct.
5. Build and evaluate expression trees recursively, use explicit stacks for tree DFS, and implement iterative graph DFS and graph BFS; trace the alternate graph-DFS form and explain how Stack and Queue frontier control changes graph exploration.
6. Trace, test, and analyze hash-table operations, linear/first-match binary search, and BST search/insertion; trace and test supplied AVL rotations and insertion; implement and analyze the required binary-heap and disjoint-set operations. Explain preparation costs without requiring insertion-sort or merge-sort instruction.
7. Trace and test supplied Dijkstra; implement DSU find/union and Kruskal; explain a supplied Prim demonstration and compare shortest-path and minimum-spanning objectives.
8. Analyze worst-case, expected/average-case where assumptions justify it, amortized, and representation-sensitive costs.
9. Select a structure or algorithm from workload and correctness requirements rather than familiarity.
10. Diagnose pointer, bounds, ownership, overflow, and invariant failures using diagrams, tests, warnings, sanitizers, and a debugger.
11. Explain how representation choices can create reliability, performance, and security consequences.
12. Communicate a technical design through pseudocode, memory diagrams, tested code, complexity arguments, and plain-language synthesis.

---

## 2. The five spirals and resource-package map

| Spiral | Linear/supporting module | Tree module | Graph module | Recurring idea |
|---|---|---|---|---|
| 1 | 1. Keeping ordered data together with an ArrayList | 2. Expression-tree model and binary-tree links | 3. Graph models and representations | Representing relationships in memory |
| 2 | 4. Stack | 5. Tree DFS | 6. Graph DFS | LIFO-controlled exploration |
| 3 | 7. Index-linked lists, shared-pool reuse, linked stack/queue examples; 8. Queue comparisons | 8. Tree level order using FIFO | 8. Maze BFS using a coordinate array queue | Explicit links, storage reuse, and FIFO-controlled exploration |
| 4 | 10. Numeric priority and optional scan reference | 10. Integer min/max and dual ID Heaps | 11. Dijkstra | Priority-controlled exploration |
| 5 | 12. Binary search; Union-Find introduced within Module 14 | 12. BSTs → 13. AVL rotations and review | 14. Prim and Kruskal | Maintaining global invariants while optimizing |

This map contains deliberate previews and returns:

- The table maps concepts and packages, not one package to one lecture week. In the required 14-week path, Module 7 applies linked lists to a stack and a queue; Module 8 compares array queues, traces tree levels, and applies FIFO to maze distances. Module 10 contains integer min/max Heaps and a dual-Heap interval application in one week.
- Module 9 bridges Spirals 3 and 4 through a supplied two-sum application. It revisits Module 1's array bounds and Module 7's node-pool lifecycle and remainder calculation; adds signed hash normalization, collisions, and separate chaining; and stores earlier array positions for complement lookup.
- Array-indexed nodes appear in Module 2. Week 7 adds a free chain and separate detachment/recycling in a fixed ten-node pool. Module 9 reuses that pool for bucket chains. Dynamic allocation and owned-storage release remain optional container-reference topics; the allocated-list library in Module 7 and open-addressed map in Module 9 remain optional. DSU is introduced with Kruskal in Week 14.
- Module 2 uses expression trees to introduce indexed binary links, loop-based construction, and recursive evaluation. The Module 5 textbook develops preorder, inorder, and postorder using explicit stacks without recursion.
- Hash-table exact lookup is compared with AVL ordered lookup before the final graph synthesis; neither backend is presented as universally superior.
- The adjacency matrix appears first because it has low pointer complexity. Adjacency-list reasoning is introduced later as pointer and dynamic-array fluency grows.
- Stack precedes explicit-stack DFS; Module 2 first introduces the depth-first idea through recursion. Week 7 applies linked lists to a LIFO stack and a FIFO queue. Week 8 compares array queue variants, traces tree BFS, then uses an array queue for maze BFS; Heap precedes Dijkstra and Prim; Hash Table precedes the final index-selection comparison; Union-Find is introduced immediately before Kruskal within Week 14.

---

## 3. Recurring questions and learning routine

Every teaching unit returns to seven anchor questions; each complete package also supports the same routine when used for extension or a longer calendar:

1. What problem does the ADT solve?
2. How is it represented in memory?
3. What invariant must remain true?
4. What operations change the state?
5. How is work scheduled or traversal controlled?
6. What are the time and space costs?
7. How can the implementation fail, and how will we detect the failure?

### Standard meeting sequence

**Meeting A: model and reason**

1. Retrieval prompt from preceding teaching weeks or resource packages
2. Syntax sandbox or prerequisite check
3. Macro-Question
4. Micro-Question deconstruction
5. Diagram, trace, or pseudocode construction
6. Three-to-five-minute individual Cognitive Pause
7. Peer comparison and expert-model calibration
8. Exit ticket connecting Linear → Tree → Graph

**Meeting B: implement and verify**

1. Retrieve the invariant before opening the IDE
2. Translate the diagram or pseudocode into sanitized C
3. Implement one operation at a time
4. Test ordinary, empty, boundary, and malformed cases
5. Use warnings, a debugger, and sanitizers where available
6. Conduct a short “segfault autopsy” or invariant-failure analysis
7. Compare with a selected, version-pinned production-code excerpt when appropriate
8. Submit a corrected synthesis artifact

The Cognitive Pause is retrieval and construction time, not a compliance exercise. Students may handwrite, type, use an accessible diagramming method, or dictate a structured response.

---

# Spiral 1 — Representation and Relationships

## Module 1 — Linear: Keeping data together with an ArrayList

Production materials: [Module 1 teaching package](module_01_arraylist/README.md)

### Learning objectives

Students will:

- explain why neighboring memory positions support direct indexed access;
- perform checked indexed reads and updates, and compare them with first-match value search;
- preserve the no-gap, index-0 rule during insertion and deletion;
- distinguish the fixed capacity from the number of stored items;
- reject a full-array addition before changing any slot or the item count;
- translate the textbook loops into functions using plain array parameters and returned counts.

### Macro-Question

> How can we keep ordered data in ten positions, preserve its order when items are added or deleted, and reject an addition when no position remains?

### Micro-Questions

- Why can an index locate an item directly?
- Why can finding an item by value require checking every item?
- How do the stored-item count and the fixed capacity differ?
- Which direction must items move during insertion and deletion?
- Why is index `size` a possible insertion position but not a stored item?
- What must remain unchanged when an index is invalid or the array is full?

### Learning sequence

The module uses two 90-minute meetings and five gated releases. Stage A
preserves each student's initial model without a vocabulary reference.
Stage B reveals the representation and vocabulary and ends with an individual
Cognitive Pause; Stage C follows the instructor explanation. Stage D releases
the textbook after the Stage C core is saved, and Stage E supplies the
Meeting B lab. Standard and linear materials have the same questions and
evidence requirements.

Meeting A follows the revised textbook's fixed-capacity model:

```c
int array[10] = {100, 200, 300};
int size = 3;
int capacity = 10;
```

Students distinguish the active prefix `array[0]` through `array[size - 1]`
from inactive positions. They read index 1, update it to 500, remove index 1
to obtain `[100, 300]`, and insert 600 at index 1 to obtain
`[100, 600, 300]`. Appending 200 then gives `[100, 600, 300, 200]`.
A separate duplicate example establishes that value search returns the first
matching index. A full ten-item example rejects append and insertion without
changing the count or any array element. Capacity remains 10 throughout.

Meeting B translates these traces into plain array-parameter functions.
Students check indexes before direct reads or updates, search the active
prefix, append only when there is room, shift right from back to front for
insertion, and shift left for removal. All operations are core; extensions
add edge-case and operation-sequence tests, not additional required APIs.

### C lab and cybersecurity context

Implement the following fixed-array operations for synthetic event codes:

```c
int int_list_valid_index(int size, int capacity, int index);
int int_list_append(int array[], int size, int capacity, int value);
int int_list_insert(int array[], int size, int capacity, int index, int value);
int int_list_remove(int array[], int size, int capacity, int index);
int int_list_find(const int array[], int size, int capacity, int value);
```

Metadata is valid when `0 <= size <= capacity`; zero capacity with zero size
is valid. The caller supplies an actual live array whose extent is at least
`capacity`. `int_list_valid_index` returns 1 only for valid metadata and
`0 <= index < size`; students use it before a direct `array[index]` read or
update. `int_list_find` returns the first matching active index, or -1 for
absence or invalid metadata.

Append, insert, and remove return the new count on success and the original
count on rejection. The caller retains that result, for example
`size = int_list_append(array, size, capacity, 400);`. Invalid metadata,
an invalid index, or a full-array addition must leave every array element
unchanged. Insertion accepts `0 <= index <= size` only when there is room;
removal accepts `0 <= index < size`. Removal need not erase the now-inactive
tail position.

Core tests cover checked read/update, first-match search, append, insertion,
removal, and rejection without mutation. Students add three nonduplicate
tests. The Bounds and Invariant Autopsy uses an eleven-element demonstration
array with a usable capacity of ten and a guard at physical index 10. A faulty
`size <= capacity` append changes the guard from -999 to 1100 and the count
from 10 to 11. This safely exposes the logical bound violation without a real
out-of-bounds access. The extra guard is a teaching fixture, not the repair;
the repair checks `size < capacity` before any mutation.

The security connection is bounded input handling: a rejected item must not
overwrite another position or make the item count untrustworthy. Any policy
for rejecting, deferring, or reporting excess input is separate from the
fixed-array representation.

### Evidence of learning

- indexed-access, first-match search, insertion, and deletion traces;
- tested C implementation plus three nonduplicate student-authored
  contract/property tests;
- full-array and invalid-index evidence showing unchanged count and contents;
- operation-cost table: indexed read/update and append are `O(1)`; search,
  insertion, and removal are `O(n)` in the worst case;
- annotated guard-autopsy explanation, repair, and regression test;
- explanation of the active prefix and the caller's returned-count assignment.

The 100-point rubric assigns 20 points to the model and invariant, 25 to core
operations, 20 to bounds and rejection, 15 to tests, 10 to efficiency, and 10
to the autopsy.

### Spiral links

**Revisits:** plain arrays, indexing, conditions, loops, and function calls.

**Forward:** array-indexed nodes in Module 2, graph matrices in Module 3,
the fixed-capacity Stack in Module 4, index-linked pool nodes in Module 7, and
Hash Table bucket/node indexes in Module 9. Allocation and release belong to later
owned-node and container labs, not this chapter.

---

## Module 2 — Tree: Indexed expression construction and recursive evaluation

Production materials: [Module 2 teaching package](module_02_binary_tree/README.md),
[English chapter](module_02_binary_tree/student/textbook.md), and
[Korean chapter](module_02_binary_tree/student/textbook_korean.md).

### Learning objectives

Students will:

- explain nodes, roots, parent/child relationships, siblings, ancestors,
  descendants, leaves, and subtrees;
- translate `1+2*3` between expression text, a hierarchy, and an index table;
- reserve a node with character data and two integer child indices;
- distinguish `-1` (no child), index `0`, and the digit character `'0'`;
- trace shared `size`/`pos` state and the current subtree root;
- build multiplication terms and join them with addition while preserving
  precedence and left grouping within equal-precedence chains;
- evaluate recursively using digit leaves as the base case and separate
  local child results, leaving stored characters and links unchanged;
- explain the one-root, single-parent, and no-cycle invariants; and
- support operation costs and correctness with tests and diagnostic evidence.

### Macro-Question

> How can array elements record an expression's hierarchy, and how can we
> construct and evaluate it while preserving operator precedence?

### Micro-Questions

- Does a child member contain a character, a node, or an array index?
- Why is `0` a usable root index while `-1` means no child?
- What do `size` and `pos` track, and why can they differ during construction?
- What does `eq[pos++]` consume, and what does `eq[pos]` leave for the caller?
- Why does `term()` finish before the surrounding addition attaches its result?
- Why does the old subtree become the new operator's left child?
- Why must an operator wait for both child results before returning its answer?
- Why does a number leaf return `data - '0'`?
- How do fresh node positions avoid sharing and cycles?

### Learning sequence

Use two 90-minute meetings and five A–E release gates. Stage A asks students
to model the work in `1+2*3` before revealing its C representation. Stage B
introduces `struct`, character members, and array indices, followed by the
three-target Cognitive Pause: indices, parser state, and evaluation.

The canonical allocation order is `'1', '+', '2', '*', '3'` at indices
`0` through `4`. The root is index `1`; its children are `0` and `3`, and
node `3` links to `2` and `4`. Evaluation returns `7`. Stage C transfers the
model to `2*3+4*5`; Stage D provides both language editions and correct
models after students preserve their investigation attempt.

Meeting B's Stage E lab implements the four textbook functions:

```c
int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

The shared representation is `struct TreeNode { char data; int left;
int right; };` with `nodes[20]`, `size`, `eq[20]`, and `pos`. Links use `-1`
for no child. Every input character creates one node. `term()` uses a loop
to build multiplication groups; `terms()` uses a loop to join complete
terms. Only `eval_tree()` calls itself recursively.

Use valid nonempty single-digit expressions with binary `+` and `*`, no
spaces or parentheses, at most 19 characters, and every intermediate and
final result within `int`. These are preconditions, not required validation
features. Start each independent build with `size = 0` and `pos = 0` and a
valid string in `eq`. Reusing the array does not preserve an earlier tree.

A generic binary-tree node can have zero, one, or two children. A completed
expression requires two operand children per operator and none per digit.
The evaluator assumes that completed expression rule, valid indices, and
finite unshared structure. Pointer-based nodes, search, clearing, dynamic
allocation, malformed-input handling, and additional operators are outside
this module's required implementation.

### C lab and correctness context

The preallocated array outlives each function call. Fresh parent nodes
join the current subtree to distinct newly built nodes, preserving the
tree rules. `new_node` and assignment to a known child member take constant
work. Construction and complete evaluation each take linear work in the
number of characters/nodes. Parsing has bounded call depth; evaluation
uses call space proportional to the longest root-to-leaf path including
the root call. Use diagrams to discuss malformed sharing or cycles.

The standalone autopsy deliberately gives every operator the same precedence
while building a finite tree. It demonstrates that valid indices and a
valid tree shape do not establish the intended arithmetic meaning. Students
preserve the predicted shape and answer before running it, then explain
how building complete terms repairs the precedence rule. A clean sanitizer
run does not establish this logical property.

### Evidence of learning

- expression, hierarchy, and index-table translations;
- traces of reservation, `size`, `pos`, and changing roots;
- precedence and left-grouping evidence from tree shape;
- recursive child-result traces and unchanged-node snapshots;
- four completed functions and three distinct student-authored tests;
- warning and supported diagnostic evidence;
- operation costs, corrected Cognitive Pause, and autopsy reasoning.

The three student tests cover node creation, construction, and evaluation.
The 100-point rubric and staged artifacts are maintained in the module.
Extensions add valid cases for the same four functions, not extra APIs.

### Spiral links

**Revisits:** fixed arrays, indexing, variables, conditions, loops, and invariants.

**Introduces:** structure members, indexed binary links, expression parsing,
precedence, and recursive evaluation with a digit base case.

**Forward:** graph relationships in Module 3; explicit traversal state in
Modules 4–6; BFS in Module 8; BSTs in Module 12 and AVL repair in Module 13.

---

## Module 3 — Graph: Models and representations

Production materials: [Module 3 teaching package](module_03_graph/README.md)

### Learning objectives

Students will:

- distinguish directed from undirected and weighted from unweighted graphs;
- use vertex, edge, degree, path, cycle, self-loop, and isolated-vertex vocabulary;
- translate the textbooks' seven-account SNS follower graph among connections and a matrix;
- implement four bounded directed-matrix operations;
- compare matrix, edge-list, and adjacency-list representations conceptually; and
- distinguish strong and weak components by hand and explain possible uses
  in feed candidate selection after the Stage C attempt.

### Macro-Question

> What representation is needed when relationships may cross branches, point backward, or form cycles?

### Micro-Questions

- What becomes a vertex, and what becomes an edge?
- How does direction change the meaning of an edge?
- How would two accounts following each other appear as two directed cells?
- Which tree invariants no longer apply?
- When is a matrix wasteful, and what would an adjacency list store instead?

### Learning sequence

Meeting A contrasts Chapter 2's tree rules with relationships that share a
destination or form a cycle. Students use accounts Mina (0), Joon (1), Sora
(2), Dae (3), Hana (4), Leo (5), and Nuri (6). An arrow points from follower
to followed account. They translate `0 -> 1`, `1 -> 2`, `2 -> 0`, `2 -> 3`,
`4 -> 5`, and `5 -> 4` into a directed integer adjacency matrix.
Undirected graphs, weights, edge lists, adjacency lists, and symmetric
matrices remain conceptual comparisons. Stage D offers equivalent English
and Korean textbook editions after the Stage C attempt is saved. Students
then trace strong and weak components and discuss feed candidates versus
ranking. No formal graph search or feed system is implemented.

Meeting B implements a bounded `struct DirectedGraph` with `vertex_count`
and a fixed 16 by 16 `int grid`. Active vertex IDs are the dense range from
zero through one less than the count. Entries are 0 or 1, inactive rows and
columns stay zero, and the diagonal stays zero. Cycles longer than a
self-loop and multiple incoming edges are valid. Adjacency lists return after
students have stronger dynamic-storage skills.

### C lab and SNS context

Implement:

- `graph_init`;
- idempotent `graph_add_edge` for one directed cell;
- idempotent `graph_remove_edge`; and
- row-based `graph_out_degree`.

Guarded direct matrix lookup is core test work rather than another public
function. The lab has no graph-kind enum, status enum, Boolean matrix,
whole-graph validator, neighbor result, in-degree helper, or undirected
mutation API. Initialization clears all 256 cells. Rejected bounds or
self-loop insertion leaves the graph unchanged.

The lab models follows in an SNS network. The canonical change removes
`2 -> 3`, reducing Sora's out-degree from 2 to 1 and isolating Dae. A follow
edge does not prove friendship or guarantee that a post appears in a feed.

Module 14 deliberately broadens the input contract to an edge-list representation that may contain parallel edges and self-loops; its algorithms handle or ignore those cases explicitly.

### Evidence of learning

- equivalent connection description and directed matrix;
- tested four-function API and direct guarded lookup;
- representation comparison;
- strong/weak component and feed-candidate reasoning after Stage C;
- explanation of why the model is no longer a tree.

### Spiral 1 synthesis

Students choose among ArrayList, tree, and graph for three short scenarios. For each choice they state:

1. the representation;
2. its central invariant;
3. one operation cost;
4. one safety or correctness risk.

---

# Spiral 2 — LIFO and Deferred Work

## Module 4 — Linear: Integer Stack and Postfix Evaluation

Production materials: [Module 4 teaching package](module_04_stack/README.md)

### Learning objectives

Students will:

- specify the LIFO access rule independently of its representation;
- trace the global fixed integer Stack in `student/lab.c` using A, B, C;
- explain forward growth, last active index `top`, active prefix
  `0..top`, item count `top + 1`, and the nonempty top item at `stack[top]`;
- state the preconditions for unchecked push/peek/pop and distinguish
  boundary predicates from guards;
- convert infix to postfix, then reuse the same global integer Stack to
  evaluate postfix with correct precedence, associativity, and operand order;
- distinguish global top index `top`, local output position `pos`, and
  the explicit output-terminator write after the operator drain; and
- separate supported-input assumptions from validation actually implemented.

### Macro-Question

> If the newest saved task must be completed first, what access rule should
> the structure enforce?

### Micro-Questions

- Which item may be removed next?
- Why is empty represented by `top == -1` and full by `top + 1 == capacity`?
- Why does push increment before writing while peek reads `stack[top]`?
- Why must the caller check state before a full push or empty peek/pop?
- Why does `stack[top--]` read before decrementing, without erasing or shifting cells?
- How does `1-2*3+4` become `123*-4+`, then -1?
- How does a parenthesis barrier make `1+(2+3)` become `123++`, then 6?
- Why must the right operand be popped before the left operand?

### C lab and cybersecurity context

Read, trace, run, and test the current `module_04_stack/student/lab.c`.
The global `int stack[10]` grows toward larger indexes and tracks the last
active index in `top`. Empty is -1; item count is `top + 1`. Push increments
first and writes `stack[++top]`; pop reads first with `stack[top--]`.
Peek reads `stack[top]`. `is_full()` and `is_empty()` report conditions but
are not called by those operations. First trace the PPT’s direct calculation
of `1-2*3+4`: a number Stack remembers values, and an operator Stack remembers
waiting operations.

The lab separates calculation order into two phases. `convert_to_postfix()`
resets `top = -1` and appends to `postfix[8]` using local `pos`. It scans
`eq` until the null terminator. `while (!is_empty())` guards every waiting
operator read. Lower precedence triggers `break`; equal or higher precedence
causes a pop and output write. No sentinel occupies the Stack. For
`1-2*3+4`, conversion writes seven tokens, drains the remaining operators,
then explicitly writes `postfix[pos++] = '\0'` at index 7. This leaves
`pos == 8` and `top == -1`. Evaluation resets
`top = -1` and reuses the same global Stack for integer operands and results.
It scans to the output terminator, pops the right operand before the left,
and returns a final pop. The canonical transfer is `1-2*3+4 -> 123*-4+ -> -1`.

`infix_to_postfix_parentheses()` scans `eq_paren`. It pushes `(` as a barrier;
when `)` arrives, it pops while nonempty and breaks when the popped item
is `(`. Other popped operators are written to the output. For `1+(2+3)`, the output is `123++`, the terminator is
explicitly written at index 5, and `pos == 6`. Evaluation gives 6. Parentheses control
order but do not appear in postfix output.

Core input is a nonempty valid expression of at most seven characters plus
a terminator in `eq[8]` or `eq_paren[8]`. Operands are single digits and
binary operators are `+ - * / %`. Only the dedicated parentheses converter
accepts balanced groups. Shorter valid expressions work. Spaces, unary
operators, and multi-digit operands are unsupported. Divisors must be nonzero
and integer intermediates representable. No full/empty operation guards,
input validation, or arithmetic checks are supplied. Checked parsing and the
older caller-owned integer API are optional extensions.

The representation revisits physical bounds and logical membership using an
active prefix. With capacity 10, valid state satisfies `-1 <= top < 10`.
The item count and next insertion index are `top + 1`. Constant-time
push/peek/pop allocate, shift, and release no storage. The isolated autopsy
contrasts a valid physical index with logical Stack membership, so a clean
memory diagnostic is not proof of a correct top read. Students preserve
their prediction before running it.

The module distinguishes the explicit Stack from runtime call bookkeeping.
Later tree and graph modules preserve LIFO while specifying their own item
types, storage policies, and error contracts.

### Evidence of learning

- integer returns (including character codes), `top`, item count, and active-index trace;
- full/empty predicate checks without executing invalid operations;
- separate infix-to-postfix and postfix-evaluation tables;
- valid precedence, operand-order, short-input, parentheses, and Stack-reset tests;
- three justified additions to the current lab tests;
- operation/phase costs, autopsy reasoning, and unsupported-input limits.

### Spiral links

**Revisits:** Module 1's fixed contiguous storage, physical bounds versus
logical membership, and the need for boundary checks; character data and
expression precedence from Module 2.

**Introduces:** Stack, LIFO, top index and item count, active prefix, push, peek,
pop, underflow, postfix notation, two separate expression phases, parenthesis barriers, and the
right-before-left operand-pop convention.

**Forward:** tree and graph DFS reuse LIFO behavior with their own storage
and reporting contracts.

---

## Module 5 — Tree: Depth-first traversal

Production materials: [Module 5 teaching package](module_05_tree_dfs/README.md)

**14-week role:** required Week 5 tree-DFS unit. The textbook focuses on preorder, inorder, and postorder using explicit stacks without recursion. The existing package lab remains separate; its submission requirements are unchanged by this textbook revision.

### Learning objectives

Students will:

- retrieve Module 2's recursive stopping cases and identify the state to save explicitly;
- trace preorder, inorder, and postorder;
- follow and run nonrecursive preorder, inorder, and postorder C examples;
- explain right-before-left pushes in preorder, saved ancestors in inorder, and completed-subtree tracking in postorder;
- connect each explicit Stack state to the work that a recursive call would remember;
- analyze traversal as `O(n)` work and at most `O(h + 1)` used stack entries, distinguishing used entries from fixed reserved storage.

### Macro-Question

> If we follow one branch as far as possible, how do we remember every branch to which we must return?

### Micro-Questions

- What is the smallest valid subtree?
- What information must the explicit stack remember between iterations?
- How does visit placement create preorder, inorder, or postorder?
- Why is the right child pushed first for left-first iterative preorder?
- Which ancestors must wait while inorder follows the left branch?
- How does postorder distinguish an unvisited right subtree from a completed one?

### C lab and cybersecurity context

The textbook traces all three traversal orders on an expression tree and
shows standalone C examples using explicit stacks of node addresses.
The examples reuse the package's existing node representation. Students
follow the stack and current-node state after each step; recursion is the
connection back to Module 2, not the implementation of these examples.

The existing package lab separately exercises expression-tree copying,
printing, and evaluation with its caller-owned node pool. This textbook
revision does not replace that lab or change its code contracts. Neither
real filesystem traversal nor a new allocation exercise is part of the
textbook change.

### Evidence of learning

- exact preorder, inorder, and postorder sequences for the same tree;
- explicit-stack traces explaining why each node is processed once;
- runnable nonrecursive C traversal examples;
- empty, single-node, balanced, and skewed-tree reasoning;
- time/space analysis using `n` and `h`, with fixed capacity accounted for separately.

### Spiral links

**Revisits:** Stack, tree representation, `NULL`, recursion, and expression evaluation.
**Forward:** graph DFS, BST inorder reasoning, and AVL height.

---

## Module 6 — Graph: Depth-first search

Production materials: [Module 6 teaching package](module_06_graph_dfs/README.md)

**14-week role:** required Week 6 graph-DFS unit and Practical 1. Iterative graph DFS is the required implementation; recursive graph DFS is traced and remains an extension. The practical replaces the ordinary Module 6 lab submission.

### Learning objectives

Students will:

- explain why graph DFS requires visited state;
- implement iterative DFS with a supplied vertex-ID Stack that preserves
  Module 4's LIFO behavior, and trace its recursive equivalent;
- determine reachability and count connected components in an undirected graph;
- trace frontier and visited state on cyclic and disconnected graphs;
- distinguish matrix-based `O(V^2)` traversal from adjacency-list `O(V+E)` traversal.

### Macro-Question

> Tree DFS terminates because branches do not reconnect. What must change when a path can lead back to a vertex already visited?

### Micro-Questions

- What plays the role of children in a graph?
- What happens on a cycle without visited state?
- When should a vertex be marked?
- Can one starting vertex reach every component?
- Why may two correct DFS implementations produce different orders?

### C lab and cybersecurity context

Using an instructor-supplied Boolean directed/undirected graph that extends
Module 3's fixed-matrix idea, implement iterative DFS, report all vertices
reachable from a selected source, and count connected components only for an
undirected graph. The broader graph kind and whole-graph validation belong to
Module 6 support, not the Module 3 implementation. The implementation uses
an instructor-provided vertex-ID Stack that preserves Module 4's LIFO
behavior while defining its own error-reporting and growable-storage policy.
Students trace the equivalent recursive control flow; implementing that
second form is an extension. Test a cycle, an isolated vertex, a disconnected
graph, and a single vertex. A separate faulty-input test verifies that the
Module 6 support API rejects a self-loop.

The Week 6 practical collects this implementation, trace, repair, and transfer evidence. There is no additional ordinary Module 6 submission in the 14-week path.

The synthetic policy graph asks whether a modeled route reaches a protected zone. Reachability is not treated as exploitability.

### Evidence of learning

- frontier/visited trace;
- tested iterative DFS implementation and recursive-form trace;
- component result;
- tree-versus-graph DFS comparison;
- representation-sensitive complexity analysis.

### Spiral 2 synthesis

Students explain the same LIFO idea in three forms:

1. Stack ADT state;
2. recursive or explicit tree worklist;
3. graph DFS frontier.

They then identify visited state as the essential graph addition.

---

# Spiral 3 — Linked Storage, FIFO, and Breadth-First Exploration

## Module 7 — Linear: Linked lists

Production materials: [Module 7 teaching package](module_07_linked_list/README.md)

**14-week role:** required Week 7 follows the current
[`student/lab.c`](module_07_linked_list/student/lab.c),
[textbook](module_07_linked_list/student/textbook.md), and
[module lab](module_07_linked_list/student/lab.md).
DSU references remain available but are taught with Kruskal in Week 14.
The older separately allocated list is an optional reference API.

### Learning objectives

Students trace integer links in `lnodes[10]` and `-1` endings; explain the
free chain initialized by `init_lnodes_pool`; use `new_lnode()` with explicit caller payload assignment,
`simple_link_lnode_to_prev`, `simple_delink_next_lnode_from_prev`, and `free_lnode`; and keep detachment separate
from recycling. They distinguish physical array positions from logical list
order and explain why exhaustion leaves the pool unchanged.

Follow the [updated concept slides](module_07_linked_list/student/ppt_material.md):
acyclic chains and separately stored first indices; safe insertion/deletion;
shared-storage benefits and costs; free-node management; linked stack; linked
queue. Separate lists share the ten-slot capacity, with disjoint live nodes.
Omitted recycling prevents reuse, double recycling corrupts the free chain,
and an old owner must stop accessing a recycled slot.

Students implement stack behavior in the caller with a separate `first`.
New nodes point to the previous first. After a successful allocation the caller
updates `first`. Removal checks nonempty, saves the old first and value, advances
to the next node, isolates old.next=-1, then recycles. The lab has no separate linked-stack API.

As a linked-list application, students maintain FIFO `qhead` and `qtail` with `enqueue_lnode`, `dequeue_lnode`, and `is_empty_queue`. Allocate/check/assign data before appending an isolated node. Dequeue returns an isolated node index without recycling; caller copies payload and recycles once. Both endpoints become -1 after the last removal. Module 7 supplies no value wrappers; Module 8 instead stores coordinates directly in an array queue. Pool initialization is first-only through a static guard; later calls do not reset active, free, or exhausted state.

### Macro-Question

> How can we change sequence links without shifting records and reuse a
> removed slot without leaving it in the live list?

### C lab and evidence

Use the current fixed-node-pool lab in one artifact. Include free-chain
initialization, exhaustion/reuse, predecessor insertion, and detachment traces.
A returned node index has not been recycled automatically.
`simple_delink_next_lnode_from_prev` clears the returned node's next=-1; `free_lnode` writes the free-chain link when the caller returns it. The caller
preserves any needed successor and updates the list head separately. Include a
linked-stack trace that inserts 17,23,31 at the first position and removes
31,23,17. Compare it with the queue trace below within the same three original
test groups and submission. Trace a recycled slot moving between two lists;
inspect invalid stale accesses on paper.

Add the linked queue example to the same artifact. Allocate 17, 23, and 31
as detached nodes, append them in arrival order, and remove them in the same
order. Preserve endpoint and free-chain traces. The first enqueue sets both
endpoints; the final dequeue restores both to `-1`. Raw `dequeue_lnode`
returns an isolated unrecycled slot. The caller reads its data and explicitly recycles it once. Empty raw removal returns -1 unchanged, while payload -1 remains valid. This example applies list operations without requiring
array queue or BFS work in Week 7.

Count fixed local work for pool, known-predecessor link, and linked-queue operations;
distinguish that from traversing a list or searching for a predecessor.
The old allocated-list insertion/deletion/destruction exercise, allocation
hooks, doubly linked lists, and DSU work are optional in Week 7. Follow the
180-minute plan.

**Revisits:** arrays, indexes, structs, explicit links, and caller preconditions.
**Forward:** apply FIFO to tree level order and array-queue maze BFS in Week 8; separate-chained hashing and pool reuse in Module 9; DSU arrays in Week 14.

---

## Module 8 — Processing data in stored order

Production materials: [Module 8 teaching package](module_08_graph_bfs/README.md)

**14-week role:** recall the linked queue's FIFO rule, compare array queue
representations, trace tree levels, and run the 5×5 maze BFS in one
180-minute lesson and one submission. The current PPTs say 10주차;
Chapter/Module 8 remains the repository resource number. The English textbook follows the Korean manuscript frozen on 2026-11-03. Its Chapter 2-style seven-section flow connects nondecreasing pending distances, equal move costs, first-discovery shortest paths, and discovery-before-enqueue. The three new C topics are nested initializer braces, whole-structure copying/passing/returning, and short-circuit OR; `enum`, increment operators, `switch`/`break`, and `continue` are review. Use these explanations with the existing code trace, without adding another assignment.

### Learning objectives

Students will:

- explain linear front/rear updates and distinguish empty from exhausted write space;
- trace circular wraparound under an explicit reserved-slot convention;
- process a tree one level at a time and track the current depth;
- explain why graphs need discovery state when routes merge or cycle;
- distinguish BFS discovery-before-enqueue from a conceptual pending-node DFS stack that permits unprocessed duplicates and skips already-processed popped copies;
- represent maze cells as row-first `struct point` values stored directly in a queue;
- use the right/left/down/up iterator and a distance array to discover each passage once;
- distinguish the implemented distance result from conceptual predecessor-based path recovery;
- explain reset, border, start, capacity, and cost conditions using concrete traces.

### Macro-Question

> How does arrival order help us process one tree level at a time and find
> the fewest moves through a maze?

### Micro-Questions

- Why does removing an array entry not restore a linear write position?
- How does circular wraparound reuse space without changing FIFO order?
- How does placing children behind waiting nodes preserve tree levels?
- Why must BFS discovery be recorded before enqueueing, while the pending-node DFS comparison may push another copy of a still-unprocessed neighbor?
- Why is the first distance minimal when every move costs one?
- What extra record would recover a route rather than only its length?

### Learning sequence and representation spiral

Recall Module 7's FIFO behavior. Use `front=0,rear=-1` to trace linear
array writes and reads. Compare a circular convention with
`front==(rear+1)%25` for empty and `front==(rear+2)%25` for full;
25 reserved slots then hold at most 24 pending values. Circular operations
are a concept comparison, not functions in the supplied maze source.

Trace the illustrative tree A(B(D,E),C(F)). Left-before-right child insertion
produces A, B, C, D, E, F. Track levels with depths or a per-level queue count.
A valid tree offers each child once; cycles and merging graph routes require
a discovery record. Compare the queue's order with Stack-based DFS.

The [current lab](module_08_graph_bfs/student/lab.c) uses a 5×5 wall-bordered
maze, `struct point {y,x}`, `queue[N*N]`, and `distance[N][N]`.
`init_bfs` resets the queue and all 25 distances before each call.
`INF=N*N=25` marks unseen or unreachable cells. An in-bounds wall start
leaves an empty queue and all distances `INF`. The border stays closed;
out-of-range starts are outside the source contract.

The iterator generates right, left, down, up. First discovery records a
distance before enqueue; every already-discovered neighbor is skipped.
From `{1,1}`, the search reaches eight passages and gives `{3,3}` distance 4.
There are eight writes, eight removals, 32 candidate checks, and at most three
pending points. Final positions are `front=8,rear=7`. Linear capacity follows
total writes, not the maximum number waiting. A cell is added once, so
`N*N` slots suffice. No linked pool or coordinate-ID map is used.

Allocate 60 minutes to queues, 30 to tree level order, 60 to maze representation
and BFS, and 30 to tests, costs, corrections, and conceptual path recovery.
The supplied source stores distances only. A first-discovery predecessor
would support one shortest path; adding that implementation is optional.

### C lab and transfer

Use [the separate lecture driver](module_08_graph_bfs/code/tests/test_lecture.c)
to exercise the unchanged lab. Run `make -C module_08_graph_bfs/code lecture`.
Submit array queue traces, the tree-level trace, full maze distances,
repeat/wall/unreachable evidence, and one original caller-side check.
The checked matrix/list library is optional and has a different contract.
As a transfer question, unit graph edges can model communication hops;
hop count alone does not describe other movement costs.

### Evidence of learning

- linear/circular queue states under explicitly stated conventions;
- tree level order and the depth of each processed node;
- discovery-before-enqueue and one queue entry per reached passage;
- distance 4 at the target, an unreachable result, and independent-run resets;
- 25 initializations, 32 direction checks, and eight linear writes in the canonical run;
- a conceptual shortest route and a Stack-versus-Queue explanation in one submission.

### Spiral 3 synthesis

Compare waiting work in a queue, tree BFS, and graph BFS. Explain why FIFO,
unit movement costs, and a discovery record together produce minimum-hop
distances. Distinguish three pending points from eight total linear writes.

---

# Associative-Index Bridge — Buckets, Collisions, and Two-Sum

## Module 9 — Supporting ADT: Hash Table

Production materials: [Module 9 teaching package](module_09_hash_table/README.md),
[source of truth](module_09_hash_table/student/lab.c),
[concept PPT](module_09_hash_table/student/ppt_material.md), and
[code PPT](module_09_hash_table/student/ppt_lab_material.md).

**14-week role:** required Week 9 trace-and-test lab. The self-contained
source uses fifteen bucket heads and ten `hnode` records with separate
`key`, `data`, and `next` fields. Students compare brute-force and chained
hash two-sum, then submit one driver and evidence record. The older
open-addressed map is optional.

### Learning objectives

Students will:

- explain direct addressing, hash bucket selection, and collisions;
- normalize signed remainders into bucket positions 0–14;
- distinguish bucket positions, node positions, keys, payloads, and input positions;
- trace head insertion, full-key lookup, and duplicate-key newest-match behavior;
- reset all bucket heads and the allocation counter, then reuse node slots;
- trace descending earlier positions in `two_sum_bf` and lookup before insertion in `two_sum_ht`;
- explain `find(complement)` followed by `hnodes[node].data` to recover the earlier input index;
- test hits, misses, exhaustion without mutation, duplicate values, and repeated calls; and
- state cost claims with bucket count, capacity, and distribution assumptions visible.

### Macro-Question

> How can the current number find the earlier number it needs without checking every earlier position, and what if different keys select the same bucket?

### Micro-Questions

- Why does `hash_func` add 15 only to a negative remainder?
- How do 12, 27, and -3 all select bucket 12?
- Why does `hashtable[12]` store a node index rather than a key or payload?
- How do `new_hnode` and `insert` differ in their successful return values?
- What does `find` compare, and what does it return?
- Why must a manual experiment call `initialize()` before searching or inserting?
- Which fields does reset change, and which fields remain?
- Why must two sum search before inserting the current position?
- Why do both supplied methods choose the newest matching earlier position?

### Learning sequence

Meeting A follows the PPTs from direct addressing to hashed groups and
separate chaining. Use the lab's signed values and capacities, rather than
the code PPT's smaller positive example. After `initialize()`, insert
`(12,120)`, `(27,270)`, and `(-3,-30)`. Bucket 12 becomes
`2 → 1 → 0 → -1`; `hnodes_unused` is 3. Full keys decide equality.
`find(27)` returns node 1, whose payload is 270. A repeated key creates a
new record rather than updating the older one. Contrast separate chains
with the PPT's open-addressing and Robin Hood concepts without assigning
a second implementation.

Meeting B follows two sum. Store `nums[i]` as key and `i` as data.
For target 0, both implementations return `{4,5}`: earlier index first.
The hash version leaves five records and bucket 14 has `4 → 0 → -1`.
A target-100 miss stores all ten inputs. The next call resets the counter
and heads, reusing slots from 0. No shared pool or free-chain recycling is
involved. For `{1,1,5,0,0,0,0,0,0,0}`, target 6 gives `{1,2}` in both
methods: brute force decrements `j`, and chains search newest matches first.

### C lab and cybersecurity context

The supplied operations remain unchanged. Students write a separate driver
with three original assertion groups:

1. signed hashing, keys versus data, collision chains, lookup, and duplicate keys;
2. all ten allocations, unchanged failed insertion, full reset, retained old
   fields, and slot reuse; and
3. two-sum results, bounds, distinct positions, duplicate values, and repeated calls.

Include `lab.c` once and compile only the driver. There is no Module 7
source dependency or repository-root include-path requirement. Use valid
node links and keep all evaluated sums and complement subtractions within
`int`; the source does not check overflow.

`insert` returns 0 on success or -1 on exhaustion. `find` returns a node
index or -1. `initialize` resets the counter and all fifteen heads without
clearing node fields, `nums`, or `answer`. A failed insertion preserves all
state. The normal ten-input hash scan resets at entry and has enough space
for all ten insertions; its failure branch is defensive and reports
`{-1,-1}`, the same answer as a miss.

A complete brute-force miss tests 45 pairs; target 0 tests 11. The target-0
hash trace compares one key. Generalized lookup costs expected `O(1+n/b)`
with adequate distribution of `n` records across `b` buckets. Expected
linear hash two-sum also needs bounded load, `b=Θ(n)`, and enough nodes;
collision-heavy searches can require quadratic total work. Reset costs
`Θ(b)`, without traversing old nodes. The actual source fixes ten nodes
and fifteen buckets and performs no dynamic growth.

Collision-heavy input can increase work. The remainder hash supplies no
cryptographic or authenticity guarantee. Individual deletion, tombstones,
resizing, and the older deletion autopsy are optional reference topics.

### Evidence of learning

- signed-hash calculations and bucket/key/node/payload traces;
- head-insertion and full-key lookup explanations;
- counter/head reset and failed-insertion preservation evidence;
- three original test groups and warning-enabled compiler output;
- exact `{j,i}` two-sum traces, duplicate values, and repeated calls;
- corrected Cognitive Pause, investigation, and evidence records; and
- concrete counts and qualified expected/worst-case claims.

### Bridge links

**Revisits:** Module 1's bounds and state preservation, Module 7's indexed
links and prepend order, and Module 8's meanings of array indices. This lab
owns its own hash-node array rather than sharing Module 7's pool.

**Forward:** Module 10 develops integer Heap ordering and dual indexed Heaps.
Module 12 compares ordered lookup with bucket-based exact lookup. A capstone
may adapt a supplied hash index for external labels; that adapter is optional.

---

# Spiral 4 — Priority and Weighted Exploration

## Module 10 — Integer Heaps and Shared On-Time

Production materials: [Module 10 teaching package](module_10_binary_heap/README.md)
and its authoritative [student/lab.c](module_10_binary_heap/student/lab.c).

**14-week role:** one 180-minute unit and one driver/evidence submission.
Use 35 minutes for numeric priority and tree shape, 65 for integer operations,
mode rebuild and pause, 60 for the dual-Heap interval search, and 20 for tests,
costs and correction. Supplied lab functions are traced and tested; there is
no required alert-library backend replacement.

### Learning objectives

Students will:

- distinguish FIFO arrival order from numeric priority selection;
- map complete-tree positions to a fixed ten-integer active prefix;
- explain the min/max flag, non-strict comparison, and missing-child sentinel;
- trace add/remove and upward/downward repair;
- rebuild bottom-up after loading values or changing comparison direction;
- distinguish Heap parent-child order from sorted and BST order;
- interpret each device's current closed interval through its epoch;
- explain stored comparator/swap function pointers in the full Heap;
- preserve both ID-Heap inverse position maps during swaps;
- repair both Heaps after changing a single ID's current interval;
- find the earliest common on-time or justify interval exhaustion;
- separate generalized costs from the literal fixed storage and input bounds.

### Macro-Question

> How can we keep the smallest or largest value ready, and use both choices
> to find when ten devices are all on?

### Micro-Questions

- Which parent-child relationship can change after one addition or removal?
- Why must a downward repair choose the better existing child?
- What does changing the min/max flag fail to repair by itself?
- Why does bottom-up construction avoid repeated full-height insertions?
- Why do the two full Heaps store IDs rather than endpoint values?
- Which map locates a changed ID in each Heap?
- When does `_reheapify` go up or down?
- Why do the latest on-time and earliest off-time determine overlap?
- Why is advancing an earliest-off interval necessary when overlap fails?
- Why must exhaustion return before reading another endpoint?

### C lab and evidence

Use integer arrivals `7,3,5,1,9,4`, producing `[1,3,4,7,9,5]` in min mode.
Removing 1 leaves `[3,5,4,7,9]`. Rebuilding the original six-value min Heap
in max mode produces `[9,7,5,1,3,4]`.

For the ten-ID trace, load ID0 `[1,3],[7,10]`, ID1 `[2,5],[8,12]`, and
IDs2–9 `[4,9]`. Bounds progress from `(4,3)` through `(7,5)` to `(8,9)`;
return 8. Include endpoint equality, immediate success, and exhaustion tests.
Check Heap order, ID permutations, and `array[pos[id]]==id` for both maps.

The integer operations do not reject invalid full/empty requests. Interval
input must supply all ten IDs, each with 1–5 nonnegative closed intervals,
valid on <= off endpoints, and chronological disjoint order. Tests enforce
these caller preconditions. There is no required input-validator task.
After an exhausted epoch, do not call a current-time accessor; restart through
`all_on_time`, which initializes all epochs and both Heaps again.

For generalized n, root selection is O(1), local repair O(log n), and
bottom-up construction O(n). With A epoch advances, the interval search is
O(n + A log n) with O(n) auxiliary ID/map/epoch storage, excluding input.
The actual source reserves fixed arrays for ten values/IDs and at most five
intervals each. It does not allocate, grow, expose status enums, count
comparisons, or store stable arrival sequences.

The [alert-record Heap](module_10_binary_heap/code/README.md) and supplied
[unsorted baseline](module_10_binary_heap/priority_queue_baseline/README.md)
remain optional reference libraries. Their stable-tie and owned-storage
contracts are separate from the required lab.

### Spiral links

**Revisits:** fixed arrays, active prefix, caller preconditions, complete
trees, height, and FIFO contrast.

**Forwards:** minimum-Heap selection in Dijkstra and Prim; Module 12 compares
Heap partial order with BST search order; Module 13 adds AVL balance. Their
supplied support defines its own record, storage, and tie policies.

---

## Module 11 — Graph: Dijkstra with an indexed minimum Heap

Production materials: [Module 11 teaching package](module_11_graph_dijkstra/README.md)

**14-week role:** required Week 11 Dijkstra unit and Practical 2. The complete
`student/lab.c` is the source of truth. Students trace the indexed Heap and
write an assertion driver; they do not complete parser, path-reconstruction,
or lazy-snapshot TODOs. Practical 2 is the week's only submission, including
the same-graph comparison within 180 minutes.

### Learning objectives

Students will:

- explain why BFS's minimum-hop route can have a larger total cost;
- interpret tentative distances and finalization marks;
- distinguish node IDs from Heap positions and verify live inverse maps;
- trace first discovery, strict relaxation, and an in-place key update;
- explain why positive weights prevent a finalized node from improving;
- test the supplied implementation against an independent distance oracle;
- identify unreachable nodes and describe actual time/storage costs.

### Macro-Question

> BFS minimizes the number of edges. How can we minimize total cost when different edges have different weights?

### Micro-Questions

- What does `node_dist[v] == -1` mean before and after a run?
- Why does `comp(i,j)` read `node_dist[heap[i]]` rather than `node_dist[i]`?
- How does `node_heap_pos` locate an existing entry after other nodes move?
- Why must a swap update both inverse positions?
- When does relaxation insert a new node, update a live node, or do nothing?
- Why is a removed node's stale position never used under the input contract?
- Which assumptions does the raw source require rather than validate?

### C lab and modeling context

The supplied code includes Module 3's ten-node adjacency lists and stores
positive `int` weights separately in `edge_length[10][10]`. A matrix entry
is not an edge unless its destination appears in the source adjacency list.
Callers provide valid indices and sums representable in `int`; the lab has
no input parser, overflow guard, status API, or dynamic allocation.

`init_dist` resets the Heap and all ten distance/found slots, then inserts
the source with cost zero. First discovery uses `add_node`; strict cost
improvement uses `update_value` on the existing live entry. The Heap holds
each pending node once. `found` records finalization but is not checked in
the loop. Minimum-first removal and positive weights prove that a removed
node cannot later improve. Position maps are guaranteed only for live
entries; `remove_root` leaves the removed entry stale. Strict comparison
allows equal keys to swap and does not promise stable ties.

The common directed fixture is
`A->B9,A->C2,A->E14,B->D1,B->E8,C->B3,C->D2,D->E2`, with F isolated.
From A, distances are `[0,5,2,4,6,-1]`, removal order is `A,C,D,B,E`,
and peak pending size is three. The run has five insertions, five removals,
two key updates, and eight adjacency inspections. These are trace counts,
not counters stored by `lab.c`. The manual route `A,C,D,E` witnesses cost
6, but the source stores no predecessor or reconstructed path.

Generalized initialization and scanning cost `O(V+E)`. At most `V`
insertions/removals and `E` updates each use `O(log V)` repair, giving
`O(V + (V+E) log V)` time for `V>=2` and `O(V)` auxiliary Heap/node state.
The separate weight matrix occupies `O(V^2)` input space. The actual fixed
ten-node arrays should be distinguished from this scalable analysis.

The old `code/include`, `starter`, `solution`, and `support` library remains
an optional comparison: its lazy duplicate snapshots, stable ties,
`size_t` parser/range checks, and predecessor paths do not describe the
required lab and add no separate submission.

### Evidence of learning and Spiral 4 synthesis

Submit one Practical 2 artifact containing predictions and corrected states,
a test driver including the exact lab, saved test output, an independent
distance check, and the same-graph comparison:

1. Run BFS while ignoring weights and identify its minimum-hop objective.
2. Run an instructor-supplied linear-minimum-selection Dijkstra reference.
3. Run the supplied indexed-Heap Dijkstra.
4. Compare distances, a manually checked route-cost witness, and operation counts.
5. Distinguish the Priority Queue ADT from its linear and Heap implementations.

Use positive small inputs, repeated runs, nonzero sources, disconnected
nodes, equal-cost alternatives, and live-map checks. Do not invoke invalid
indices, over-capacity insertion, empty removal, or signed overflow to test
rejection that this source does not implement.

---

# Spiral 5 — Invariants and Minimum-Cost Connectivity

## Union-Find bridge within Week 14

Production materials: [combined Week 14 DSU/Kruskal lab](module_14_prim_kruskal/week_14/README.md)
and [Module 7 DSU reference](module_07_linked_list/code/include/dsu.h).

**14-week role:** DSU is introduced with Kruskal in Module 14. Its reference
implementation remains in the renamed Module 7 library; it is not a Week 7
prerequisite or a standalone module assignment.

### Required DSU objectives and scope

Students interpret `parent[]` and `component_size[]`, trace representative roots,
implement iterative two-pass find with path compression and union by component
size, and use a failed merge to detect a cycle. The smaller root ID wins ties.
Initialization, make-set, bounded root-location helpers, and validation are
supplied so DSU and Kruskal fit the same 180-minute block.

DSU membership does not imply trust, authorization, or a graph path. Explain
amortized near-constant operation cost without requiring an inverse-Ackermann
proof. Root sizes and component count must stay correct after compression.

The original list repair and complete List/DSU lab are optional resource
material. They do not create another required implementation or submission.

---

<a id="module-12--tree-bst-to-avl-synthesis"></a>

## Module 12 — Binary Search and BSTs

Planning references: [Module 12 overview](module_12_binary_search_bst/README.md) and
[Chapter 12 summary](instructor_guide/chapter_12.md). Existing teaching
materials linked from the overview await alignment with this sequence.

**14-week role:** introduce ordered interval elimination and BST search and
insertion. One search/BST evidence artifact fits the 180-minute budget.
AVL balance, rotations, and insertion move to Module 13.

### Learning objectives

- explain why binary search needs a sorted array and narrow a half-open interval;
- trace first-match binary search, including duplicates, missing keys, and empty input;
- state BST ordering and trace supplied ordinary search and insertion;
- connect inorder traversal with nondecreasing key order;
- measure height and visited-node comparisons for different insertion orders;
- explain why ordering alone does not guarantee logarithmic BST search.

### Macro-Question

> What ordering rule lets us discard candidates, and why can an ordered tree
> still force us to inspect every node?

### Learning sequence and evidence

Recap linear search on `[31,23,17,8,17,42]`, which finds 17 at index 2.
Supply `[8,17,17,23,31,42]` already sorted and trace first-match binary
search returning 1. Positions belong to the array being searched. Sorting
implementation is not part of this lesson.

Transfer the smaller/larger choice to Module 2's character nodes and integer
child links. Use the existing plain-BST baseline for `ABCDEFG`, `GFEDCBA`,
and `DBFACEG`. Check ordering and reachability; count one logical comparison
per visited node. With empty height `-1` and leaf height `0`, the first two
orders give height 6, while the mixed order gives height 2. Search costs
`O(h + 1)`; an `n`-node chain can require `O(n)` work.

One submission combines binary-search intervals, BST search/insertion and
inorder traces, original checks, height/comparison evidence, and a corrected
prediction. End with the ascending-order chain as Module 13's repair problem.
BST deletion is outside required scope. Distinguish shape-based performance
degradation from invalid memory access or general resource exhaustion.

| Required contact activity | Minutes |
|---|---:|
| Linear-search recap and first-match binary search on supplied sorted arrays | 45 |
| BST ordering, search, insertion, and inorder reasoning | 60 |
| Height, insertion-order effects, and search costs; finish with a skewed tree | 35 |
| Traces, checks, and one combined evidence artifact | 40 |
| **Total** | **180** |

### Spiral links

**Revisits:** ArrayList access/search, Module 2 indexed trees, Module 5 inorder,
Heap-order contrast, and Module 9 exact lookup.
**Forward:** Module 13 repairs long BST paths while preserving key order.

---

<a id="module-13--searching-sorting-and-consolidation"></a>

## Module 13 — AVL Rotations and Review

Planning references: [Module 13 overview](module_13_avl_review/README.md)
and [Chapter 13 summary](instructor_guide/chapter_13.md). Existing AVL
references remain in Module 12; existing Module 13 search/sort materials
await alignment and are not the revised weekly assignment.

**14-week role:** establish AVL balance, trace local repair and supplied
insertion, then protect the final hour for course review. One artifact
combines AVL evidence and a review memo. DSU/MST remain new in Module 14.

### Learning objectives

- compute edge heights and left-minus-right balance factors;
- recognize LL/RR before LR/RL and preserve inorder and middle subtrees;
- retain returned subtree roots and update heights from lower nodes upward;
- check reachability, ordering, exact heights, and balance after insertion;
- compare ordinary BST and AVL paths on the same keys;
- justify structure choices using query, update, order, space, and route requirements.

### Macro-Question

> How can we shorten an ordered tree without losing its ordering rule, and
> when does that structure fit the workload?

### Learning sequence and evidence

Retrieve Module 12's chain, then introduce balance and local reconnection.
Use `C B A`, `A B C`, `C A B`, and `A C B` for LL, RR, LR, and RL. Include
a nonempty transferred middle subtree. Trace the supplied indexed AVL code
still stored in Module 12: rotations change links; `_add` refreshes heights
and returns a possibly new root. Fresh IDs may share labels; insertion uses
`<=` on the left, while rotations preserve nondecreasing inorder and can
place equal labels on either side. Respect the ten-slot caller contract.

One submission includes four rotation traces, insertion/link/height/balance
checks, a BST/AVL comparison, a workload-selection review memo, and a corrected
prediction. No from-scratch AVL implementation, deletion, or new implementation
of an earlier structure is required.

The final 60 minutes review arrays/lists, hash versus BST/AVL lookup, Heap
priority, DFS/BFS frontier control, and minimum-hop versus weighted routes.
Briefly discuss the cost of preparing and updating an ordered snapshot.
Insertion-sort and merge-sort instruction and implementation are optional;
they do not gate core work. Module 14 explains its supplied sorted edges and
comparator without assuming a sorting lesson.

| Required contact activity | Minutes |
|---|---:|
| Retrieve the skewed-tree problem; establish height and balance | 20 |
| LL/RR followed by LR/RL rotations, preserving ordering and middle subtrees | 55 |
| Guided AVL insertion: returned roots and bottom-up height updates | 30 |
| Rotation and insertion checks | 15 |
| Course review, workload selection, corrections, and submission | 60 |
| **Total** | **180** |

---

## Module 14 — Graph: Prim and Kruskal

Production materials: [Module 14 teaching package](module_14_prim_kruskal/README.md)

**14-week role:** required Week 14 combines new DSU learning with Kruskal. One artifact contains DSU/Kruskal tests, a short individual synthesis, and capstone integration. Prim is an instructor demonstration, with no student implementation checkpoints. The defense remains in the final-assessment period.

### Learning objectives

Students will:

- distinguish a shortest-path tree from a minimum spanning tree;
- state the weighted, undirected input contract;
- trace Prim’s frontier growth and Kruskal’s component merging;
- explain the roles of Heap and Union-Find;
- implement DSU find/union and Kruskal in one scaffold; inspect supplied Prim output;
- validate a spanning tree or minimum spanning forest;
- compare algorithm suitability by representation and density;
- explain why minimum cost does not imply resilience.

### Macro-Question

> How can we connect all monitoring sites at minimum total cost, and why is that different from finding the cheapest route from one source?

### Micro-Questions

- What quantity does Dijkstra minimize, and what does an MST minimize?
- What makes an edge safe to add across Prim’s frontier?
- How does Kruskal detect a cycle?
- Why can two valid MSTs use different edges but have the same total weight?
- How many edges should a connected result contain?
- What result is appropriate for a disconnected graph?
- Are negative weights valid for MST algorithms?
- Is the cheapest connected design resilient?

### C lab and cybersecurity context

Students use supplied graph construction, edge sorting, and checked totals. They learn DSU in this same week and use it immediately in Kruskal. They complete:

- DSU find/union and the complete Kruskal selection loop from the combined scaffold;
- a brief trace of the instructor-supplied Prim demonstration;
- result validation;
- total-weight comparison.

Prim uses lazy duplicate Heap entries with stale-key and `in_tree` checks; it restarts from each unvisited vertex for a disconnected input. Kruskal uses the supplied edge-list builder, `qsort`, a relational comparator, and DSU. A short comparator explanation introduces increasing weight order and ties and explains why returning `left_weight - right_weight` can overflow. No prior insertion-sort or merge-sort lesson is assumed.

Students implement the bounded DSU core here; parser, Heap, make-set, and sorting are supplied. Tests include a singleton graph, normal connected graph, disconnected graph, equal-weight alternatives, parallel edges, self-loops, negative weights, invalid endpoints, and a total weight requiring `int64_t`.

A monitoring-backbone scenario illustrates the objective. Students must recommend redundancy beyond the MST because every tree edge is a potential single point of failure.

### Correctness and complexity contracts

- A connected result contains `V - 1` selected edges.
- A graph with `c` components has `V - c` edges in a minimum spanning forest.
- Prim and Kruskal must agree on minimum total weight, not necessarily exact edges.
- Negative weights are valid for MST but not for Dijkstra.
- A standard MST is not defined for a directed graph.
- Lazy-duplicate Prim uses up to `O(E)` Heap entries and runs in `O(V + E log(E + 1))`, which becomes `O(V + E log V)` for a simple graph.
- Kruskal is `O(E log E)` for sorting plus near-linear DSU work.

### Evidence of learning

- side-by-side algorithm trace;
- tested DSU and Kruskal code plus an observation from the supplied Prim demonstration;
- invariant-based result validation;
- algorithm-selection memo;
- cost-versus-resilience analysis.

### Spiral 5 synthesis and individual check

Use the existing DSU/edge ledger for one short individual explanation:
why does DSU membership match connectivity in accepted Kruskal edges?
Then select hash or AVL lookup for one stated workload and distinguish total
MST cost from shortest-path distance. These retrieve earlier evidence rather
than require new Hash/AVL implementations or seven separate trace exercises.

The synthesis and integration record are folded into the single Week 14
artifact and its 180-minute block. Longer cross-module comparisons belong to
the cumulative capstone report; the defense uses the separate final period.

---

# Assessment Architecture

## 1. Assessment principles

Assessment mirrors the learning routine. Students are not asked only to reproduce code from memory. Every important assessment collects three kinds of evidence:

1. **Explain and trace:** representation, memory state, invariant, and operation.
2. **Build and test:** bounded C implementation, repair, or integration.
3. **Audit and transfer:** complexity, failure mode, security consequence, and structure choice.

Initial Cognitive Pause responses are evaluated for serious participation and subsequent correction rather than immediate perfection. Required teaching-week labs permit one feedback-driven revision. Summative tasks use the same Macro/Micro architecture practiced in class, with less scaffolding.

## 2. Recommended grading plan

| Component | Weight | Primary evidence |
|---|---:|---|
| Retrieval practice and corrected Cognitive Pauses | 10% | Short traces, diagrams, invariant questions, annotated corrections |
| Twelve weekly lab artifacts, including the Week 8 queue/tree/graph-BFS lab and the folded Week 14 checkpoint | 26% | C code, tests, tool output, and memory models; one artifact in each lab week |
| Five embedded spiral synthesis checks | 15% | Transfer scored within the Week 3 lab, Practical 1, Week 8 queue/tree/graph-BFS lab, Practical 2, and Week 14 artifact; no separate submissions |
| Segfault Autopsies and Micro-CTFs | 10% | One embedded debugging artifact per spiral |
| Two cumulative practical assessments | 14% | Weeks 6 and 11 implementation, trace, debug, repair, select, and justify |
| Individual synthesis portfolio | 10% | Revised artifacts, connection maps, test evidence, reflection |
| Capstone | 15% | Integrated tool, report, individual evidence, and defense/equivalent |
| **Total** | **100%** | |

The weekly-lab category is distributed across the twelve required lab artifacts;
combining weeks does not create an extra submission.

The Segfault Autopsies and Micro-CTFs are embedded in existing labs so they do not become five additional programming projects.

Students may drop their two lowest retrieval/Cognitive Pause scores. An absent student may complete an asynchronous equivalent within the course’s normal make-up window.

## 3. Common lab rubric

| Criterion | Weight |
|---|---:|
| Representation and invariant reasoning | 20% |
| Functional correctness and edge cases | 25% |
| C ownership, allocation, and memory safety | 20% |
| Tests and tool-supported evidence | 15% |
| Complexity analysis and structure selection | 10% |
| Explanation and security transfer | 10% |

Performance descriptions:

- **Exceeds expectations:** maintains invariants on unfamiliar cases and justifies design trade-offs with evidence.
- **Meets expectations:** correct on required cases, with clear ownership and appropriate tests.
- **Developing:** partially correct but needs guidance to maintain an invariant or handle boundary cases.
- **Beginning:** handles only the happy path, uses unsafe ownership, or cannot explain the represented state.

Drawing quality, prose polish, and coding speed do not substitute for conceptual correctness.

## 4. Cumulative practical assessments

### Practical 1 — Week 6, with Module 6

Students:

- reconstruct an ArrayList, tree, and graph from memory representations;
- repair one pointer or bounds defect;
- compare one recursive tree-DFS trace with one Stack-backed iterative graph-DFS trace, identifying saved frontier and visited state;
- complete or repair a bounded iterative graph-DFS function and its cycle/disconnection tests;
- identify the invariant added at each generalization;
- select a representation for a short scenario.

### Practical 2 — Week 11, with Module 11

Students:

- interpret a Queue-backed graph-BFS trace and complete graph distance/predecessor state;
- repair a circular-buffer or visited-state defect;
- trace Heap operations;
- execute one Dijkstra relaxation round;
- trace and test the supplied indexed-Heap Dijkstra, including live inverse positions, in-place improvement, unreachable nodes, and repeated runs;
- state the raw lab's positive-weight, valid-index, and representable-sum preconditions;
- compare the supplied linear Priority Queue baseline with the Heap backend.

Both practicals include an expert-model correction opportunity followed by a short transfer question. Corrections recover evidence of learning, not all points automatically.

Each practical replaces that teaching week’s ordinary lab rather than adding another assignment. Week 8 and Week 10 likewise produce one submission each: the Module 8 queue/tree/graph-BFS lab includes its frontier-control synthesis, and the Module 10 Heap lab includes integer repairs, ID/map checks, and common-interval reasoning.

---

# Cumulative Portfolio and Capstone

## 1. Synthesis portfolio

Each student maintains a “data-structure passport.” Every structure or algorithm receives one concise entry containing:

- visual or tabular memory representation;
- ADT contract;
- central invariant;
- core operation costs;
- ownership rules;
- common failure or attack surface;
- earlier structures it reuses;
- one corrected misconception.

The final portfolio contains:

- one substantially revised artifact from each spiral;
- five Linear→Tree→Graph connection maps;
- selected test and sanitizer evidence;
- at least three Segfault Autopsies;
- a final reflection identifying which mental model changed most.

The portfolio is a technical communication artifact, not a scrapbook. Students may present it as accessible HTML, Markdown, or an approved equivalent. A PDF submission must be tagged and checked for logical reading order.

### Portfolio rubric

| Criterion | Weight |
|---|---:|
| Technical accuracy and completeness | 30% |
| Meaningful revision and misconception correction | 25% |
| Linear→Tree→Graph connections | 25% |
| Clear, accessible technical communication | 20% |

## 2. Capstone — Defensive Network Analysis Toolkit in C

The capstone is built incrementally so Week 14 is integration rather than a new project.

| Delivery milestone | Capability added |
|---|---|
| Week 3 / Module 3 | Bounded directed matrix, tested operations, and capstone skeleton |
| Week 6 / Module 6 | Stack-backed DFS and reachability |
| Week 7 / Module 7 | Acyclic links, safe insertion/detachment, shared-pool reuse, stale-access rules, and linked LIFO/FIFO applications |
| Week 8 / Module 8 | Array queue comparisons; tree level order, maze BFS distances, and conceptual unweighted path recovery |
| Week 9 / Module 9 | Separate-chained key lookup, allocation-counter reset, and two-sum evidence; external-label index adaptation belongs to later integration |
| Week 11 / Module 11 | Heap-backed Dijkstra |
| Week 12 / Module 12 | Binary-search and ordinary-BST evidence, insertion-order effects, and a skewed-index example |
| Week 13 / Module 13 | AVL repair/insertion evidence, ordered-index comparison, and a workload-selection review memo |
| Week 14 / Module 14 | DSU and Kruskal integration; supplied Prim comparison and cumulative report |

Each milestone contributes evidence inside that week’s lab or practical; it is not a second weekly submission. The Week 14 lab grade covers the bounded MST implementation and comparison, while the capstone grade covers cross-module integration, the cumulative report, and the defense. The same code is not scored twice for the same criterion.

The final toolkit must:

- validate all vertex identifiers and input sizes;
- document ownership for each allocated object;
- traverse the model with DFS and BFS;
- reconstruct unweighted paths and independently check weighted route costs; Module 11 itself stores distances only;
- validate positive Dijkstra weights at the integration boundary; the raw Module 11 lab assumes valid input;
- map sparse external labels to validated dense internal IDs without confusing a hash with authentication;
- select hash-backed exact lookup or AVL-backed ordered lookup from the stated workload and worst-case requirements;
- use a sorted-array search or repeated scan where its preparation, update, and lookup costs fit the workload;
- compute an MST or minimum spanning forest using Kruskal and student-completed DSU;
- interpret the supplied Prim comparison; implementing Prim remains optional;
- validate important structure invariants;
- release all allocated memory;
- explain why minimum cost does not imply a resilient network design.

Students may work in pairs if each submits an individual design explanation and completes a short individual defense or live modification. A written, recorded, or extended-time equivalent must be available so speaking fluency and typing speed are not hidden grading criteria.

### Capstone rubric

| Criterion | Weight |
|---|---:|
| Algorithmic correctness | 20% |
| Module integration and interface design | 15% |
| Data-structure invariants | 15% |
| Memory safety and input validation | 15% |
| Tests and reproducible evidence | 15% |
| Complexity and algorithm selection | 10% |
| Security analysis and individual defense | 10% |

---

# Differentiation, Accessibility, and Psychological Safety

## Required access provisions

- Permit diagrams as drawings, structured tables, tactile models, or verbal descriptions.
- Permit Cognitive Pause work on paper, in an accessible editor, or through speech-to-text.
- Do not rely on color alone or require a literal red pen; tracked changes or labeled annotations are equivalent.
- Caption demonstrations and provide all commands, code, and diagrams in text-accessible form.
- Provide screen-reader-friendly starter code with descriptive identifiers and short functions.
- Offer a nonphysical equivalent for manipulatives or embodied activities.
- Grade conceptual targets rather than handwriting, visual aesthetics, typing speed, or public-speaking fluency.

## Differentiated scaffolding

Each module provides three response levels:

1. **Entry support:** glossary, completed first trace row, memory-shape template, sentence starter, and a tested API skeleton.
2. **Core target:** independent trace, required operations, boundary tests, complexity explanation, and one failure analysis.
3. **Extension:** alternative backend, proof sketch, performance experiment, additional operation, or production-code comparison.

Advanced students receive extension questions during Cognitive Pauses instead of additional busywork. Students who are stuck receive a hint ladder rather than the complete answer:

1. restate the invariant;
2. label the relevant state;
3. identify the next legal operation;
4. compare with the preceding linear/tree module;
5. inspect one worked substep.

Near-peer mentors or teaching assistants should normalize debugging difficulty without using labels such as “script kiddie” or presenting struggle as a fixed student identity.

---

# C Engineering Baseline

All submitted implementations use a consistent engineering contract. Apply
representation-specific requirements when they are introduced: Chapter 1
uses fixed-array bounds and plain integer counts. Module 2 introduces array-indexed
nodes, loop-based construction, and recursive expression evaluation. Its
small parser assumes valid inputs and representable integer results. Module 4 adds a
forward-growing integer-Stack representation with last active index `top`
and item count `top + 1`.
A direct two-Stack calculation motivates the separate infix-to-postfix and
postfix-evaluation phases using the same global Stack, under explicit
valid null-terminated input assumptions (at most seven characters), including
balanced parentheses through the dedicated converter. Its Stack operations are unchecked; the
full/empty predicates do not guard operations or validate expressions. Module 7 introduces
index-linked pool nodes, shared storage, separate detachment and recycling,
and linked LIFO stack/FIFO queue applications. Module 8 compares array queues and uses a direct coordinate array queue for maze BFS,
with explicit caller preconditions. Module 9
reuses that pool for separate-chained hashing and complement lookup. Module 10 uses fixed integer and ID Heaps with caller preconditions. Dynamic
allocation, owned-storage release, and checked rebuilding remain optional
container-reference topics.
Module 2's recursive functions assume valid trees: inspect malformed cycles
with diagrams, not by running recursive operations on them.

- compile with the strongest practical warnings for the course toolchain;
- never ignore an allocation result;
- validate external indexes before array access;
- define empty/error behavior in the API;
- use `size_t` for sizes and indexes where appropriate;
- define hash-key ownership and update policy explicitly;
- preserve valid, acyclic, disjoint active/free chains in the Module 9 pool; bound probe loops and rehash transactionally when using the optional open-addressed reference;
- check capacity arithmetic and weighted-path arithmetic for overflow;
- document ownership transfer;
- pair every successful allocation with a defined cleanup path;
- test empty, singleton, boundary, duplicate, malformed, and adversarial cases;
- run AddressSanitizer/UndefinedBehaviorSanitizer or the closest supported equivalent;
- keep invariant-checking functions available in debug builds;
- use version-pinned, short, annotated production-code excerpts rather than unfiltered source files.

For Kruskal, comparator code must compare relationally rather than subtracting weights, because subtraction can overflow. For accumulated graph weights, use a type large enough for the stated input contract and check addition.

---

# Dependency and Scope Audit

| Dependency | First formal placement | Used later by |
|---|---|---|
| Fixed-array bounds, active prefix, shifts, and first-match search | Module 1 | Stack, matrices, Hash Table, Heap |
| Addresses and pointers | At the first pointer-based API; not a Module 2 prerequisite | Later node and container implementations |
| `struct`, character members, and global node-array lifetime | Module 2 | Later node and container implementations |
| Fixed-pool allocation, detachment, and recycling | Module 7 indexed linked nodes | Queue lifecycle, Module 9 bucket chains, and later ownership comparisons |
| Dynamic allocation, release, and owned storage | Optional Module 10 alert library, Module 7 allocated list, and Module 9 open-addressed map | Later containers and linked-node implementations |
| Node relationships | Module 2 indexed tree representation; Module 7 linked-list lesson in Week 7 | Trees, linked adjacency, DSU bridge |
| Indexed binary-tree representation and expression evaluation | Module 2 | Graph contrast, DFS, BFS |
| BST ordering and baseline | Module 12 in Week 12 | AVL |
| Graph representation | Module 3 | All graph algorithms |
| Stack | Module 4 | Tree and graph DFS |
| Growable-array storage and checked commit | Optional Module 10 alert library | Optional container comparisons; supplied later frontier support |
| Recursive base cases and child-results-first evaluation | Module 2 | Explicit-stack traversal and later tree algorithms |
| Depth-first search idea | Module 2 recursive examples | Module 5 traversal orders and Module 6 graph DFS |
| Named traversal orders and explicit traversal stacks | Module 5 textbook core: nonrecursive preorder, inorder, and postorder | Tree and graph algorithms |
| Queue | Module 7 linked FIFO example; Module 8 compares linear/circular arrays | Apply FIFO to tree levels and direct-coordinate array-queue maze BFS in Week 8 |
| Edge height | Module 2, retrieved for BST path costs in Module 12 | AVL height updates in Module 13 |
| Balance factors and AVL rules | Module 13 | AVL validation and rotation |
| Adjacency list | Module 3 graph representation | Later graph-algorithm reference APIs |
| Shortest predecessor concept | Module 8 concept slides in Week 8; the lab records distances only | Optional path recovery and later shortest-path comparisons |
| Hash Table, signed hashing, separate chaining, and complement lookup | Module 9 supplied lab.c | Exact-lookup comparison with AVL; later external-label index adaptation |
| Priority selection and optional linear reference | Module 10 fixed integer Heap; alert-record baseline is optional | Heap comparison, Dijkstra, and Prim |
| Binary Heap | Module 10 main lab in Week 10 | Dijkstra and Prim |
| Weighted relaxation | Module 11 | Dijkstra; comparison with Prim |
| Union-Find with compression and union by size | Module 14 scaffold in Week 14 | Kruskal in the same week |
| BST operations and AVL rotations | BST search/insertion in Module 12; AVL balance, rotations, and guided insertion in Module 13 | Ordered-index capstone; comparison with hashing |
| First-match binary search | Module 12 on supplied sorted arrays | Module 13 workload review and later snapshot lookup |
| Insertion-sort and merge-sort instruction | Optional reference material; not a required prerequisite | Optional sorting comparisons |
| Edge-list construction and safe sorting/comparator | Supplied Week 14 scaffold | Kruskal |

Scope controls:

- Every teaching week has a hard 180-minute contact budget. A complete package may contain extension, make-up, or longer-calendar materials beyond that budget.
- Module 1 requires checked indexed read/update, first-match search, append,
  insertion, and removal in a fixed array. Its extensions add tests only;
  Module 4 reuses fixed storage for a Stack, while later modules introduce
  allocation and growable storage in their own contracts.
- Module 2's textbooks and lab use loop-based expression-tree construction and recursive evaluation of valid single-digit `+`/`*` input. Module 5's textbook focuses on explicit-stack preorder, inorder, and postorder without recursion; existing package labs remain separate. Module 6 requires iterative graph DFS; recursive graph DFS is an extension.
- Module 7 applies linked lists to a stack and a queue. Module 8 compares array queues, traces tree levels, and uses an array queue for maze BFS in one Week 8 submission. Queue positions, graph discovery, distances, resets, and conceptual path recovery share one lesson; Week 6 DFS provides the frontier-control comparison.
- Module 10 combines fixed integer min/max Heaps and ten-device interval search in one Week 10 driver/evidence submission. Its alert-record Heap and unsorted baseline remain optional.
- Module 9 traces and tests the supplied separate-chained two-sum program in one driver/evidence submission. It reuses Week 7's fixed pool; open-addressed rebuilding is optional. Week 14 combines bounded DSU work and Kruskal. Complete reference-package menus are optional resources.
- Module 12 requires binary search and ordinary BST search/insertion; BST deletion is outside required scope. Module 13 requires guided supplied AVL insertion and rotation evidence; AVL deletion is outside required scope. Its final 60 minutes are reserved for review, corrections, and submission.
- Week 14 supplies graph/Heap support and introduces DSU before its use in Kruskal.
- Students implement DSU and Kruskal together; Prim is a brief supplied demonstration, with no required student TODOs.
- Module 9 demonstrates bucket-based exact-number lookup through two-sum. A supplied or adapted hash index can support sparse external keys in later synthesis. Boolean/indexed visited arrays remain the simpler representation when vertex IDs are already dense.
- The required hash-table representation uses separate chaining in a fixed node pool. The older open-addressed map, linear probing, tombstones, resizing, and cryptographic hash design are extensions. Module 12 requires first-match binary search on supplied sorted arrays. Insertion-sort and merge-sort instruction and implementation are optional; Module 14 supplies and explains its edge ordering without assuming either sorting lesson.
- Algorithms operate only on synthetic, authorized datasets.

---

# Required 14-Week Calendar

| Week | Primary topic | Package use and major artifact |
|---:|---|---|
| 1 | Keeping data together with a fixed-capacity ArrayList | Module 1; checked operations and bounds/invariant autopsy |
| 2 | Recursion, binary-tree links, and expression trees | Module 2 bilingual textbooks and four-function construction/evaluation lab |
| 3 | Graph fundamentals | Module 3; Spiral 1 synthesis and capstone skeleton |
| 4 | Integer Stack and postfix | Module 4; top index and item count, LIFO boundaries, top-index autopsy, `1-2*3+4 -> 123*-4+ -> -1`, and parentheses conversion |
| 5 | Tree DFS | Module 5 textbook: explicit-stack preorder, inorder, and postorder; existing package lab remains separate |
| 6 | Graph DFS | Module 6 iterative core; Spiral 2 synthesis and Practical 1 replace the ordinary lab |
| 7 | Linked lists with linked stack and queue examples | Module 7 acyclic links, shared pool, safe insertion/detachment, recycling, LIFO first-node operations, and FIFO endpoint transitions |
| 8 | Processing data in stored order | Module 8; array queue comparison, tree levels, maze discovery/distances, conceptual path recovery, and frontier-control synthesis in one submission |
| 9 | Hash Table and two-sum | Module 9 supplied lab.c; signed hashing, separate chains, pool reuse, and one driver/evidence submission |
| 10 | Integer Heaps and shared on-time | Current Module 10 lab.c, driver, repairs, dual ID Heaps, maps, and interval reasoning; one submission |
| 11 | Dijkstra | Module 11; Spiral 4 synthesis and Practical 2 replace the ordinary lab |
| 12 | Binary Search and BSTs | Module 12; first-match binary search, BST search/insertion, inorder, height, and skew evidence in one artifact |
| 13 | AVL Rotations and Review | Module 13; balance, four rotation cases, guided supplied insertion, checks, and a review memo in one artifact; final 60 minutes for review |
| 14 | Union-Find and Kruskal | Module 14; one DSU/MST, embedded Spiral 5 check, and integration artifact; Prim demonstration |

The capstone begins with the Week 3 skeleton and receives the milestones listed above; it is not introduced in Week 14. The Module 14 individual check and integration checkpoint are embedded in the week’s single artifact, while the capstone defense uses the scheduled final-assessment period. If that period is unavailable, move the defense to an institutionally approved assessment slot rather than adding it to Week 14’s 180-minute plan.

The 14 full packages remain useful for extensions, make-up work, or a longer calendar. In the 14-week path, use Module 8's combined queue/tree-BFS/graph-BFS lesson in Week 8 and the current Module 10 integer/dual-Heap lab in Week 10. Week 9 Hash Table and Week 14 DSU/Kruskal must likewise use their bounded 180-minute cores rather than their complete package menus. Use the exact selections in the [14-week delivery guide](Data_Structures_Course_2026_14_Week_Delivery_Guide.md), and do not turn omitted implementations into uncounted homework.

---

# Course Evaluation Plan

The redesign should be evaluated rather than assumed effective. Collect:

- an ungraded beginning/end concept inventory covering memory models, invariants, traversal, and representation choice;
- a beginning/end code-reading task using the same unfamiliar C excerpt;
- lab revision data identifying recurring pointer, bounds, and invariant errors;
- performance on near-transfer and far-transfer synthesis questions;
- a mid-course workload/accessibility survey;
- anonymous feedback on cybersecurity relevance and psychological safety;
- results disaggregated by prior programming experience, without treating groups as fixed ability categories.

Review results after each offering. Revise the module in which misconceptions first appear, not only the later module where they become visible.
