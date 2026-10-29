# Data Structures Course 2026

## Interleaved Spiral Curriculum for Cybersecurity Freshmen

### Curriculum status and assumptions

This document defines an operational **14-week curriculum supported by 14 teaching packages**. Priority Queue is part of Module 10, and Hash Table is Module 9. Module 7 covers linked lists with linked stack and queue examples. Module 8 compares queue representations and reuses that linked queue for tree BFS and graph BFS. Teaching packages are numbered consecutively from 1 to 14, matching their teaching weeks. The exact required/extension split is collected in the [14-week delivery guide](Data_Structures_Course_2026_14_Week_Delivery_Guide.md). It assumes:

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).

- second-semester cybersecurity students;
- prior experience with C variables, functions, arrays, loops, and conditionals;
- limited fluency with pointers, dynamic allocation, and `struct`;
- approximately 3 contact hours per teaching week, delivered as two class meetings or an equivalent lecture/lab format; combined weeks selectively use two packages but still have one contact-time budget and one submission; capstone integration occurs in Week 14, while the defense or approved equivalent uses the institution’s scheduled final-assessment period;
- synthetic, instructor-controlled cybersecurity datasets rather than live-system scanning or exploitation;
- a C11-compatible compiler, strong compiler warnings, a debugger, automated tests, and memory/error sanitizers when the platform supports them.

The resource library is not organized as five consecutive linear modules, followed by five tree modules, followed by five graph modules. It makes five increasingly sophisticated passes, with the associative-index bridge in Module 9 and a searching/sorting/consolidation unit in Module 13:

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
6. Trace, test, and analyze hash-table operations, linear/binary search, and insertion/merge sorting; implement and analyze BST, AVL-tree, binary-heap, and disjoint-set operations.
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
| 3 | 7. Index-linked lists, shared-pool reuse, linked stack/queue examples; 8. Queue comparisons | 8. Tree BFS using the same linked queue | 8. Graph BFS using the same linked queue | Explicit links, storage reuse, and FIFO-controlled exploration |
| 4 | 10. Numeric priority and optional scan reference | 10. Integer min/max and dual ID Heaps | 11. Dijkstra | Priority-controlled exploration |
| 5 | Union-Find (introduced within Module 14 in Week 14) | 12. BST-to-AVL synthesis | 14. Prim and Kruskal | Maintaining global invariants while optimizing |

This map contains deliberate previews and returns:

- The table maps concepts and packages, not one package to one lecture week. In the required 14-week path, Module 7 applies linked lists to a stack and a queue; Module 8 compares queue representations and reuses that linked queue for trees and graphs. Module 10 contains integer min/max Heaps and a dual-Heap interval application in one week.
- Module 9 bridges Spirals 3 and 4 through a supplied two-sum application. It revisits Module 1's array bounds and Module 7's node-pool lifecycle and remainder calculation; adds signed hash normalization, collisions, and separate chaining; and stores earlier array positions for complement lookup.
- Array-indexed nodes appear in Module 2. Week 7 adds a free chain and separate detachment/recycling in a fixed ten-node pool. Module 9 reuses that pool for bucket chains. Dynamic allocation and owned-storage release remain optional container-reference topics; the allocated-list library in Module 7 and open-addressed map in Module 9 remain optional. DSU is introduced with Kruskal in Week 14.
- Module 2 uses expression trees to introduce indexed binary links, loop-based construction, and recursive evaluation. The Module 5 textbook develops preorder, inorder, and postorder using explicit stacks without recursion.
- Hash-table exact lookup is compared with AVL ordered lookup before the final graph synthesis; neither backend is presented as universally superior.
- The adjacency matrix appears first because it has low pointer complexity. Adjacency-list reasoning is introduced later as pointer and dynamic-array fluency grows.
- Stack precedes explicit-stack DFS; Module 2 first introduces the depth-first idea through recursion. Week 7 applies linked lists to a LIFO stack and a FIFO queue. Week 8 compares array queue variants, then uses that linked queue for tree BFS and graph BFS; Heap precedes Dijkstra and Prim; Hash Table precedes the final index-selection comparison; Union-Find is introduced immediately before Kruskal within Week 14.

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
Modules 4–6; BFS in Module 8; BST/AVL synthesis in Module 12.

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

As a linked-list application, students maintain FIFO `qhead` and `qtail` with `enqueue_lnode`, `dequeue_lnode`, and `is_empty_queue`. Allocate/check/assign data before appending an isolated node. Dequeue returns an isolated node index without recycling; caller copies payload and recycles once. Both endpoints become -1 after the last removal. Module 7 supplies no value wrappers; Module 8 adds local adapters for BFS. Pool initialization is first-only through a static guard; later calls do not reset active, free, or exhausted state.

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
**Forward:** reuse the linked queue for tree BFS and graph BFS in Week 8; separate-chained hashing and pool reuse in Module 9; DSU arrays in Week 14.

---

## Module 8 — Queues, tree BFS, and graph BFS

Production materials: [Module 8 teaching package](module_08_graph_bfs/README.md)

**14-week role:** compare queue representations, then reuse Module 7's linked
queue for tree BFS and graph BFS within one 180-minute lesson and one
submission. Week 7 supplies both linked storage and the FIFO example.
The current graph example is the maze in
[`student/lab.c`](module_08_graph_bfs/student/lab.c).

### Learning objectives

Students will:

- preserve FIFO with linked endpoints and compare linear/circular queue storage;
- explain full/empty predicates, caller checks, reset, and wraparound;
- distinguish internal pool slots from queued tree/cell IDs and explain automatic recycling in the public value API;
- trace level-order tree BFS using integer node IDs and left-before-right enqueueing;
- explain why a graph needs discovery state when branches merge or cycle;
- trace first-discovery distance and all equal-distance shortest predecessors;
- recover one shortest unweighted route and report an unreachable target;
- count tree work, four-neighbor maze work, and reserved versus active storage.

### Macro-Question

> How can arrival order help us process one tree level at a time and find a
> route with the fewest moves when paths merge or cycle?

### Micro-Questions

- Which end of a waiting line must supply the next item?
- Why can a linear queue exhaust its writes after earlier items leave?
- Why does the circular convention leave one array slot unused?
- How does adding children behind waiting nodes preserve tree levels?
- Why must graph discovery be recorded before enqueueing?
- Why can an equal-distance arrival add a predecessor without another enqueue?

### Learning sequence and representation spiral

Begin with [`student/queue.c`](module_08_graph_bfs/student/queue.c), which
imports Module 7's node queue and defines local value adapters. Retrieve its `qhead`/`qtail`
transitions and the public value wrappers. Compare
linear and circular `queue[25]`: 25 writes before a linear reset versus
24 usable circular positions under the reserved-slot convention. Predicates
report state; callers guard unchecked operations and reset between variants.
The linear comparison uses `enqueue_linear`, `dequeue_linear`,
`is_empty_linear`, and `is_full_linear` so it does not redefine the linked API.
The tree and maze BFS use the linked queue rather than the array variants.
Before each independent traversal require every prior pool owner already recycled and empty endpoints `qhead = qtail = -1`. The pool initializer is one-time and cannot reset ownership. Module 8 defines the value adapters locally. Call `enqueue(id)` and check its Boolean result. Guard
with `is_empty_queue()`, then call public `dequeue()` to obtain a payload ID.
That function reads and recycles the internal slot before BFS adds children
or neighbors; callers do not recycle its returned value. Keep enqueue calls
outside assertions so `NDEBUG` cannot remove their side effects. The pool limits
pending work rather than the total number of discoveries.

Next use [`student/tree_bfs.c`](module_08_graph_bfs/student/tree_bfs.c) with
Module 2's indexed F-root tree. Processing order is `F,A,G,B,C,D,E`. Trace
left-before-right child insertion behind waiting nodes. A valid tree has no
shared child or cycle, so each reachable node enters once without graph
discovery state. Compare the result with the Stack-based DFS choice.

Then trace the 7 × 7 maze as an implicit graph. Reset `info` and verify all pool slots recycled with empty linked endpoints before each independent run; the pool initializer is one-time. Process neighbors right, left, down, up.
First discovery sets distance before enqueueing; an equal shortest arrival
adds a predecessor without enqueueing again. Start `{1,1}` reaches all 20
passages. Target `{5,5}` has distance 8 and three shortest routes.
The supplied ten-slot pool fits the tree's peak of three pending nodes,
the canonical maze's peak of four, and the peak of six over all starts in
that maze. The queue drains and all slots return to the free chain.

Allocate 60 minutes to queues, 30 to tree BFS, 60 to graph/maze BFS, and 30
to tests, costs, corrections, and synthesis. The older checked matrix/list
API and representation-cost comparison remain optional reference work.

### C lab and cybersecurity context

Submit queue checks, a tree trace, and a maze driver with distance and
predecessor assertions, one recovered route, and an unreachable case.
The maze's zero border, interior start, distance-25 sentinel, and queue
capacity are explicit preconditions. Generalizing the maze or printing all
routes is extension work. As a transfer question, interpret unit graph
edges as communication hops; hop count alone does not model real risk.

### Evidence of learning

- linked/linear/circular queue states and boundary checks;
- tree level-order and maze distance/predecessor traces;
- discovery-before-enqueue and equal-arrival evidence;
- one recovered shortest route and an unreachable result;
- tree/maze costs and a Stack-versus-Queue explanation, all in one submission.

### Spiral 3 synthesis

Students compare what a frontier item and “discovered but unprocessed” mean in:

1. a FIFO queue;
2. tree BFS;
3. graph BFS, compared with Stack-backed graph DFS.

They explain why FIFO order, unit/unweighted edges, and marking vertices when enqueued together produce minimum-hop distance. FIFO alone is not a shortest-path guarantee.

---

# Associative-Index Bridge — Buckets, Collisions, and Two-Sum

## Module 9 — Supporting ADT: Hash Table

Production materials: [Module 9 teaching package](module_09_hash_table/README.md),
[source of truth](module_09_hash_table/student/lab.c).

**14-week role:** required Week 9 trace-and-test lab. The supplied source
uses ten bucket heads, Module 7's linked-node pool, and separate chaining to
compare brute-force and hash-assisted two-sum. Students submit one driver
and evidence record. The older open-addressed map is an optional reference.

### Learning objectives

Students will:

- normalize signed remainders into bucket positions 0–9;
- distinguish bucket positions, node positions, payloads, and `nums` positions;
- trace collisions as newest-first linked chains;
- explain why `save_data` prepends and permits duplicate payloads, while `find_data` compares raw payloads;
- initialize the unused pool once and recycle disjoint active chains between runs;
- trace `two_sum_bf` with `j < i` and `two_sum_ht` with complement lookup before current-index insertion;
- explain why two-sum compares `nums[j]`, rather than using `find_data` to compare a needed number with a stored position;
- test successes, misses, exhausted allocation, repeated calls, and differing valid pair order; and
- state chain-search costs with the bucket-count and distribution assumptions visible.

### Macro-Question

> How can we find the earlier number needed by the current number without checking every earlier position, and what happens when several numbers select the same group?

### Micro-Questions

- Why does `hash_func` add 10 only to a negative remainder?
- How do 12, 22, and -8 all select bucket 2?
- Why does `hashtable[2]` contain a node position rather than the number 2?
- Which record becomes the head when `save_data` succeeds?
- What does `find_data` compare, and what does it return?
- Why does `init_hashtable` not replace the first `init_lnodes_pool` call?
- How does `free_lnode_chunk` join an active chain to the free chain?
- Why must two-sum look up its complement before storing `i`?
- When can both functions return valid but different position pairs?

### Learning sequence

Meeting A begins with the pair-sum problem and the supplied
`nums = {-16,-8,-4,-2,-1,1,2,4,8,16}`. Students enumerate earlier pairs,
then calculate the one complement needed by each current number. They
normalize negative remainders, initialize the free pool, and trace saves
of 12, 22, and -8 into bucket 2. Those saves allocate nodes 0, 1, and 2,
leaving the active route `2 → 1 → 0 → -1`. A repeated payload is another
node rather than an update. Students distinguish payload equality from
bucket equality and predict successful and unsuccessful chain searches.

Meeting B follows the two-sum source. The hash version stores earlier array
positions as payloads and compares `nums[j]` with `target - nums[i]`.
Target 0 yields `{5,4}` in both versions. Students inspect the five nodes
left active by the successful early return, recycle the chains, and run
again. A complete target-100 miss stores ten positions and leaves no free
node until reset. A duplicate-input fixture exposes the different
oldest-first and newest-first candidate order without changing correctness.

### C lab and cybersecurity context

The operations in `student/lab.c` are supplied. Students write and run a
driver with three original test groups:

1. signed hashes, collisions, prepend order, payload lookup, and duplicates;
2. pool initialization, allocation exhaustion, unchanged failed insertion,
   whole-chain recycling, and safe reuse; and
3. successful and unsuccessful two-sum results, distinct positions,
   repeated calls, and multiple-solution behavior.

The driver includes the actual lab once and compiles with the repository
root on the include path. It does not link the lab or the imported Module 7
source a second time. Calls supply bucket positions 0–9 and valid, acyclic,
disjoint active/free chains. All evaluated additions and subtractions must
fit in `int`. The functions do not validate those caller preconditions.

The shared ten-node pool must be initialized before the first run and
available exclusively to the table for a complete ten-number scan.
`init_hashtable` returns existing chains to that pool. `two_sum_ht` stops
if allocation fails and writes `{-1,-1}`, the same result as a completed
unsuccessful search. The result does not distinguish those cases.

With `n` stored candidates and `b` buckets, adequately distributed inputs
give expected lookup work `O(1+n/b)`. A chain with `k` candidates can require
`O(k)` comparisons. A generalized two-sum design has expected `O(n)` work
only when bucket count and distribution keep chain lengths bounded;
colliding candidates can require `O(n^2)` total work. The supplied source
fixes both arrays at ten and performs no dynamic growth. Brute force checks
45 pairs in a complete miss. Clearing costs `O(b+s)` for `s` active nodes.

Collision-heavy input demonstrates how a representation can increase
work. The remainder hash is transparent and supplies no cryptographic or
authenticity guarantee. Individual deletion, tombstones, resizing,
transactional rebuilding, and the older deletion autopsy are optional
open-addressed-reference topics.

### Evidence of learning

- normalized signed-hash and bucket/node traces;
- raw-payload versus stored-position explanations;
- active/free-chain lifecycle and failed-insertion preservation evidence;
- a driver containing three original test groups and warning-enabled output;
- brute-force and hash-assisted pair traces, including repeat-call reuse;
- corrected Cognitive Pause, investigation, and evidence records; and
- comparison counts and qualified generalized expected/worst-case claims.

### Bridge links

**Revisits:** Module 1's array bounds and state preservation, Module 7's
indexed linked records, free-chain lifecycle and remainder calculation,
and Module 8's distinction between stored numbers and array positions.

**Forward:** Module 10 develops integer Heap ordering and dual indexed Heaps. Module 12 compares ordered lookup with bucket-based exact lookup.
A capstone may adapt a supplied hash index for external labels; that adapter
is not an additional Week 9 implementation requirement.

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
Heap partial order with BST/AVL search order. Their supplied support defines
its own record, storage, and tie policies.

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

## Module 12 — Tree: BST-to-AVL synthesis

Production materials: [Module 12 teaching package](module_12_bst_avl/README.md)

**14-week role:** required Week 12 AVL unit and the formal home for height, balance factors, and rotations deferred from the BFS bridge. AVL insertion and validation are core, AVL deletion is extension, and the week produces one submission within the 180-minute budget.

### Learning objectives

Students will:

- state BST ordering and AVL balance invariants;
- trace and test the instructor-provided BST search/insertion baseline introduced in this unit;
- show how hostile insertion order creates height `n - 1`;
- compute heights and balance factors;
- recognize LL, RR, LR, and RL cases;
- trace the supplied indexed rotations and AVL insertion, and write original assertion tests;
- validate ordering, stored heights, and balance after every mutation.

### Macro-Question

> If an attacker controls insertion order, can an apparently efficient search tree be forced into linear-time behavior?

### Micro-Questions

- Why does inorder traversal produce sorted keys?
- Which inputs create a skewed BST?
- How does height control search cost?
- How can a rotation change shape without changing key order?
- Which single or double rotation repairs each imbalance?
- Which pointer reassignment errors can lose an entire subtree?

### C lab and cybersecurity context

The indexed lab uses edge height consistently: `get_height(-1) = -1` and
`height[leaf_id] = 0`. Therefore an `n`-node chain has height `n - 1`.

Build an adversarial asset or indicator index:

1. use the driver baseline to insert `ABCDEFG`, `GFEDCBA`, and `DBFACEG` into a BST;
2. measure height and comparison counts;
3. check ordering and exact reachable IDs with the independent driver validator;
4. trace the supplied `student/lab.c` rotations and recursive AVL insertion;
5. test all four canonical rotation cases;
6. check exact stored heights, balance, duplicate labels, and transferred subtrees;
7. reset and rebuild the fixed arrays, then preserve assertion and sanitizer output.

The required lab reuses Module 2's `nodes[10]`, with `char data` and integer
child links, and adds `height[10]`. Equal labels in fresh IDs descend left
on insertion; rotations preserve nondecreasing inorder and may place
equals on either side. Callers retain the returned root and supply valid
detached IDs. There is no allocation or cleanup operation in this source.
The retained 64-node pointer API and full AVL deletion are optional references.

The security connection is algorithmic-complexity denial of service. Students distinguish degraded complexity from memory corruption and from general resource exhaustion.

### Evidence of learning

- four rotation traces;
- BST-versus-AVL measurement table;
- invariant-checking tests;
- caller-precondition and valid-boundary evidence;
- concise threat analysis.

### Spiral links

**Revisits:** Module 5 inorder DFS, tree-height reasoning, Heap-order contrast, and Module 9's bucket-based exact-number lookup.
**Forward:** compare AVL's ordered worst-case guarantee with hash lookup's expected exact-match cost, then compare local and global invariants.

---

## Module 13 — Searching, sorting, and consolidation

Production materials: [Module 13 teaching package](module_13_search_sort_consolidation/README.md),
[English textbook](module_13_search_sort_consolidation/student/textbook.md), and
[Korean textbook](module_13_search_sort_consolidation/student/textbook_korean.md).

**14-week role:** one bounded Week 13 search/sort and consolidation artifact.
Students trace and test complete supplied functions, then select structures
for stated workloads using evidence from earlier modules. DSU and MST remain
new learning in Module 14.

### Learning objectives

- compare linear search with first-match binary search on sorted input;
- distinguish an array position before sorting from a position after sorting;
- preserve a sorted prefix during insertion sort and combine sorted runs during merge sort;
- explain stable equal-key order with tagged paper records;
- test duplicates, missing keys, empty/singleton inputs, bounds, and signed integer extremes;
- compare local shifts, merge passes, scratch storage, and preprocessing for repeated lookup;
- consolidate ArrayList/list, hash/BST/AVL, Heap, and DFS/BFS/Dijkstra choices.

### Macro-Question

> When is it worth rearranging data before searching, and which earlier
> structure best fits the workload we actually have?

### Learning sequence and evidence

Keep `[31,23,17,8,17,42]` as the common input. Linear search first finds 17
at index 2. Sorting gives `[8,17,17,23,31,42]`; first-match binary search
then returns index 1. Both searches return `-1` for a missing key. Binary
search requires sorted input and continues left after a match to find the
first duplicate. The lab contract permits up to 64 integers.

Insertion sort shifts larger prefix values and keeps equal values in order.
Merge sort combines sorted halves using a caller-owned disjoint scratch
buffer. Explain why strict insertion comparison and left-first merge ties
preserve stability. Integer-only output cannot prove original equal-record
order; use tagged records in the paper trace. Count work before naming
linear/quadratic or logarithmic growth.

One submission contains original search/sort checks, traces, saved build
output, costs, a corrected prediction, and a workload-selection memo. Reuse
earlier artifacts rather than reimplement every structure. Compare exact
lookup, ordered lookup, priority removal, complete sorted output, traversal,
minimum-hop paths, and weighted routes. The sorting ideas prepare Module 14's
supplied edge comparator; students do not add a second sorting implementation
to the MST scaffold.

Allocate 35 minutes to retrieval/search, 55 to sorting, 25 to tests, 45 to
consolidation, and 20 to correction/submission: 180 minutes total. Extra
sorting algorithms, generic-record code, and broad benchmarks are extensions.

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

Prim uses lazy duplicate Heap entries with stale-key and `in_tree` checks; it restarts from each unvisited vertex for a disconnected input. Kruskal uses the supplied edge-list builder, `qsort`, a relational comparator, and DSU. A short comparator retrieval explains why returning `left_weight - right_weight` can overflow.

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
| Week 8 / Module 8 | Queue representation comparisons; the same linked queue for tree BFS, graph BFS, and unweighted paths |
| Week 9 / Module 9 | Separate-chained complement lookup and pool-reuse evidence; external-label index adaptation belongs to later integration |
| Week 11 / Module 11 | Heap-backed Dijkstra |
| Week 12 / Module 12 | AVL-backed ordered asset/indicator index and backend-selection comparison |
| Week 13 / Module 13 | Searching/sorting evidence and workload-based consolidation of previous structures |
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
and linked LIFO stack/FIFO queue applications. Module 8 compares unchecked array queues and reuses
that linked queue for tree BFS and graph BFS,
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
| Queue | Module 7 linked FIFO example; Module 8 compares linear/circular arrays | Reuse the Module 7 linked queue for tree BFS, then graph BFS in Week 8 |
| Height and balance | Module 12 | AVL validation and rotation |
| Adjacency list | Module 3 graph representation | Later graph-algorithm reference APIs |
| Shortest predecessors | Module 8 maze BFS in Week 8 | Path recovery and later shortest-path comparisons |
| Hash Table, signed hashing, separate chaining, and complement lookup | Module 9 supplied lab.c | Exact-lookup comparison with AVL; later external-label index adaptation |
| Priority selection and optional linear reference | Module 10 fixed integer Heap; alert-record baseline is optional | Heap comparison, Dijkstra, and Prim |
| Binary Heap | Module 10 main lab in Week 10 | Dijkstra and Prim |
| Weighted relaxation | Module 11 | Dijkstra; comparison with Prim |
| Union-Find with compression and union by size | Module 14 scaffold in Week 14 | Kruskal in the same week |
| BST operations and AVL rotations | BST operations, height, balance, and rotations introduced together in Module 12 | Ordered-index capstone; comparison with hashing |
| First-match binary search and stable insertion/merge sorting | Module 13, using array access, shifts, and recursion from earlier modules | Workload-selection consolidation and supplied Kruskal edge ordering in Module 14 |
| Edge-list construction and safe sorting/comparator | Supplied Week 14 scaffold | Kruskal |

Scope controls:

- Every teaching week has a hard 180-minute contact budget. A complete package may contain extension, make-up, or longer-calendar materials beyond that budget.
- Module 1 requires checked indexed read/update, first-match search, append,
  insertion, and removal in a fixed array. Its extensions add tests only;
  Module 4 reuses fixed storage for a Stack, while later modules introduce
  allocation and growable storage in their own contracts.
- Module 2's textbooks and lab use loop-based expression-tree construction and recursive evaluation of valid single-digit `+`/`*` input. Module 5's textbook focuses on explicit-stack preorder, inorder, and postorder without recursion; existing package labs remain separate. Module 6 requires iterative graph DFS; recursive graph DFS is an extension.
- Module 7 applies linked lists to a stack and a queue. Module 8 compares queue representations and uses that same linked queue for required tree BFS and graph BFS in one Week 8 submission. Queue boundaries, pool-slot recycling, tree levels, graph discovery, distances, predecessors, and path recovery share one lesson; Week 6 DFS provides the frontier-control comparison.
- Module 10 combines fixed integer min/max Heaps and ten-device interval search in one Week 10 driver/evidence submission. Its alert-record Heap and unsorted baseline remain optional.
- Module 9 traces and tests the supplied separate-chained two-sum program in one driver/evidence submission. It reuses Week 7's fixed pool; open-addressed rebuilding is optional. Week 14 combines bounded DSU work and Kruskal. Complete reference-package menus are optional resources.
- AVL insertion is core; AVL deletion is an extension.
- Week 14 supplies graph/Heap support and introduces DSU before its use in Kruskal.
- Students implement DSU and Kruskal together; Prim is a brief supplied demonstration, with no required student TODOs.
- Module 9 demonstrates bucket-based exact-number lookup through two-sum. A supplied or adapted hash index can support sparse external keys in later synthesis. Boolean/indexed visited arrays remain the simpler representation when vertex IDs are already dense.
- The required hash-table representation uses separate chaining in a fixed node pool. The older open-addressed map, linear probing, tombstones, resizing, and cryptographic hash design are extensions. Module 13 requires first-match linear/binary search and stable insertion/merge sorting; additional sorting algorithms remain extensions.
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
| 8 | Queues, tree BFS, and graph BFS | Module 8; queue comparison and linked-queue reuse for tree levels, graph discovery, distances, predecessors, path reconstruction, and frontier-control synthesis in one submission |
| 9 | Hash Table and two-sum | Module 9 supplied lab.c; signed hashing, separate chains, pool reuse, and one driver/evidence submission |
| 10 | Integer Heaps and shared on-time | Current Module 10 lab.c, driver, repairs, dual ID Heaps, maps, and interval reasoning; one submission |
| 11 | Dijkstra | Module 11; Spiral 4 synthesis and Practical 2 replace the ordinary lab |
| 12 | BST-to-AVL | Module 12; height/balance, adversarial-input, and index-selection experiment |
| 13 | Searching, sorting, and consolidation | Module 13; first-match linear/binary search, stable insertion/merge sorting, original tests, and a workload-selection memo in one artifact |
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
