# Data Structures Course 2026

## Interleaved Spiral Curriculum for Cybersecurity Freshmen

### Curriculum status and assumptions

This document defines an operational **14-week curriculum supported by 16 teaching packages**. The package numbers preserve the full resource sequence; they are not a promise of sixteen lecture weeks or sixteen assignments. The exact required/extension split is collected in the [14-week delivery guide](Data_Structures_Course_2026_14_Week_Delivery_Guide.md). It assumes:

Companion resource: [weekly vocabulary and anticipated student question bank](Data_Structures_Course_2026_Student_Question_Bank.md).

- second-semester cybersecurity students;
- prior experience with C variables, functions, arrays, loops, and conditionals;
- limited fluency with pointers, dynamic allocation, and `struct`;
- approximately 3 contact hours per teaching week, delivered as two class meetings or an equivalent lecture/lab format; combined weeks selectively use two packages but still have one contact-time budget and one submission; capstone integration occurs in Week 14, while the defense or approved equivalent uses the institution’s scheduled final-assessment period;
- synthetic, instructor-controlled cybersecurity datasets rather than live-system scanning or exploitation;
- a C11-compatible compiler, strong compiler warnings, a debugger, automated tests, and memory/error sanitizers when the platform supports them.

The resource library is not organized as five consecutive linear modules, followed by five tree modules, followed by five graph modules. It makes five increasingly sophisticated passes through, with one associative-index bridge between the fourth and fifth passes:

> **Linear/supporting ADT → Tree application → Graph generalization**

Students therefore encounter the same ideas—representation, invariants, traversal, frontier management, complexity, ownership, and failure—several times in different forms.

---

## 1. Course learning outcomes

By the end of the course, students will be able to:

1. Draw and explain the memory representation of array-backed, hash-table, pointer-linked, tree, heap, and graph structures.
2. Specify an abstract data type independently of its underlying representation.
3. Implement, test, and safely destroy core data structures in C.
4. State and check the representation invariant that makes each structure correct.
5. Implement recursive tree DFS, iterative graph DFS, and graph BFS; trace tree BFS and the alternate graph-DFS form to explain how frontier control transfers between trees and graphs.
6. Implement and analyze hash-table, BST, AVL-tree, binary-heap, and disjoint-set operations.
7. Implement Dijkstra and one complete minimum-spanning-tree algorithm, finish and test bounded decision checkpoints in an instructor-supplied implementation of the other, and trace and compare both Prim and Kruskal under their required input assumptions.
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
| 3 | 7. Queue | 8. Tree BFS | 9. Graph BFS | FIFO-controlled exploration |
| 4 | 10. Priority Queue ADT | 11. Binary Heap | 12. Dijkstra | Priority-controlled exploration |
| 5 | 14. Linked-list retrieval and Union-Find | 15. BST-to-AVL synthesis | 16. Prim and Kruskal | Maintaining global invariants while optimizing |

This map contains deliberate previews and returns:

- The table maps concepts and packages, not one package to one lecture week. In the required 14-week path, Modules 8 and 9 form one breadth-first week, and Modules 10 and 11 form one priority/Heap week.
- Module 13 is an associative-index bridge between Spirals 4 and 5. It revisits Module 1's array bounds and Module 4's growable-array storage, adds collision resolution and deletion markers, and maps sparse external identifiers to the dense internal IDs used by graph algorithms.
- Linked local node variables appear in Module 2. Allocation is introduced with the Stack in Module 4 and with individual tree nodes in Module 5, then retrieved through bounded implementation and repair in Module 14.
- Module 2 uses an expression tree to introduce binary-tree links, node lifetime, and simple recursive processing. Module 5 formalizes traversal orders and introduces binary-search ordering before Module 15 strengthens that ordering with AVL balance.
- Hash-table exact lookup is compared with AVL ordered lookup before the final graph synthesis; neither backend is presented as universally superior.
- The adjacency matrix appears first because it has low pointer complexity. Adjacency-list reasoning is introduced later as pointer and dynamic-array fluency grows.
- Stack precedes DFS; Queue precedes BFS; Heap precedes Dijkstra and Prim; Hash Table precedes the final index-selection comparison; Union-Find precedes Kruskal.

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

**Forward:** linked node variables in Module 2, graph matrices in Module 3,
growable Stack backing storage introduced in Module 4, and checked Hash Table
storage in Module 13. Allocation and release belong to the later Stack and
owned-node labs, not this chapter.

---

## Module 2 — Tree: Expression-tree model, binary-tree links, and recursive clearance

Production materials: [Module 2 teaching package](module_02_binary_tree/README.md)

### Learning objectives

Students will:

- identify root, parent, child, sibling, ancestor, descendant, leaf, path, depth, height, and subtree;
- map the expression `(3 + 5) * 2` to a five-node binary tree while distinguishing expression rules from generic binary-tree rules;
- translate between a binary-tree diagram and local node variables with distinct left/right links;
- explain the one-incoming-link and no-cycle invariants, including the caller's responsibility for them;
- initialize nodes and attach a fresh child only to an empty chosen side;
- implement current-node, left-subtree, right-subtree search and return the first matching node;
- clear a selected subtree, detach its parent-side link explicitly, and preserve the other branch;
- distinguish resetting fields from ending a node variable's lifetime.

### Macro-Question

> How can separate node variables represent a hierarchy, and how can we search and clear its branches without losing track of the links?

### Micro-Questions

- Does a child field contain another node or its address?
- Why are `'*'` and `'+'` valid values for an `int` field in this simplified C model?
- Why does operand position matter even though a generic tree allows either side to be empty?
- Why is a right-only child valid, and why must it stay on the right?
- Why can two parents not share a child even without a cycle?
- What stops the recursive search or clearance?
- Why can an unsorted-tree search need to inspect every node?
- Why does clearing a child not automatically detach the parent's link?

### Learning sequence

Use two 90-minute meetings and the five A–E release gates. Meeting A
contrasts Chapter 1's contiguous row with distinct local node variables.
Students first model the hierarchy, then learn addresses, `struct`,
`&`, `.`, `->`, and `NULL`. The canonical tree represents `(3 + 5) * 2`:
root `'*'` has left child `'+'` with children `3` and `5`, and right child
`2`. The current-left-right search sequence is `'*', '+', 3, 5, 2`.
Stage C transfers the same reasoning to `(8 - 3) * (4 + 2)`. Vocabulary
belongs to Stage B; Stage D notes do not reveal the later autopsy's result.

Meeting B implements exactly the two functions shown in the textbook:

```c
struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

The node has `int data`, `struct TreeNode *left`, and
`struct TreeNode *right`. Initialization and guarded attachment remain
direct field operations. C character constants such as `'*'` and `'+'`
have type `int`; using them here is a simplified label encoding, not a
type-safe evaluator. To remove the left branch, the caller uses
`tree_clear(parent.left);` followed by `parent.left = NULL;`.
No child positions are shifted. Students construct local fixtures in three
authored tests and explain the return path and clearance sequence.

A generic binary-tree node may have zero, one, or two children. A completed
binary expression using binary operators requires two operands per operator
and no children below a numeric operand. The two child-pointer fields enforce
the generic two-position limit, but the library does not validate the
expression-specific arity rule. After removing one operand, the links may
still form a valid tree even though they no longer encode a complete expression.

Formal DFS and named traversal-order comparisons belong to Module 5.
Allocation, parent pointers, shared-root queries, status-code interfaces,
binary-search ordering, and balancing are not Module 2 work.

### C lab and cybersecurity context

The caller supplies initialized node objects that remain live while their
addresses are used. Child links must form a finite, acyclic, unshared tree.
The functions assume those conditions; they do not validate an arbitrary
graph. A guarded direct attachment preserves an occupied side.

`tree_find` returns the first matching address or `NULL`, without changing
the tree. `tree_clear(NULL)` does nothing. Clearing resets all reachable
data to zero and child links to `NULL`, but does not release storage or
remove an outside parent's link. Zero remains an ordinary data value.

The bounded autopsy intentionally gives two parents the same live child.
Clearing one branch unexpectedly changes the child observed from the other.
All objects remain live, so the lesson concerns logical aliasing, not a
dangling pointer or a double free. Do not run recursive functions on an
actual cycle or deliberately exhaust call-stack space.

### Evidence of learning

- expression-diagram-to-left/right-field translation and a separate generic right-only-child case;
- direct local initialization and occupied-side preservation;
- correct recursive search, including duplicate values and absence;
- branch clearance with explicit detachment and unchanged opposite branch;
- three nonduplicate student-authored tests and warning/diagnostic evidence;
- an explanation that cleared objects remain live;
- corrected Cognitive Pause and bounded autopsy reasoning.

### Spiral links

**Revisits:** variables, conditions, loops, fixed storage, and invariants.

**Introduces:** an expression-tree application, self-referential structs,
node addresses and lifetimes, distinct left/right links, recursive search,
and recursive field clearance.

**Forward:** graph relationships in Module 3; allocation and growable storage
in Module 4; formal DFS and allocated-node destruction in Module 5; BFS in
Module 8; BST/AVL synthesis in Module 15.

---

## Module 3 — Graph: Models and representations

Production materials: [Module 3 teaching package](module_03_graph/README.md)

### Learning objectives

Students will:

- distinguish directed from undirected and weighted from unweighted graphs;
- use vertex, edge, degree, path, cycle, self-loop, and isolated-vertex vocabulary;
- translate the textbook's three-server graph among connections and a matrix;
- implement four bounded directed-matrix operations; and
- compare matrix, edge-list, and adjacency-list representations conceptually.

### Macro-Question

> What representation is needed when relationships may cross branches, point backward, or form cycles?

### Micro-Questions

- What becomes a vertex, and what becomes an edge?
- How does direction change the meaning of an edge?
- How would two-way communication appear as two directed cells?
- Which tree invariants no longer apply?
- When is a matrix wasteful, and what would an adjacency list store instead?

### Learning sequence

Meeting A contrasts Chapter 2's tree rules with relationships that share a
destination or form a cycle. Students use the three textbook vertices—Web,
App, and Database—and translate `0 -> 1`, `1 -> 2`, and `1 -> 0` into a
directed integer adjacency matrix. Undirected graphs, weights, edge lists,
adjacency lists, symmetric matrices, and connected components remain
conceptual comparisons. No formal graph search is performed.

Meeting B implements a bounded `struct DirectedGraph` with `vertex_count`
and a fixed 16 by 16 `int grid`. Active vertex IDs are the dense range from
zero through one less than the count. Entries are 0 or 1, inactive rows and
columns stay zero, and the diagonal stays zero. Cycles longer than a
self-loop and multiple incoming edges are valid. Adjacency lists return after
students have stronger dynamic-storage skills.

### C lab and cybersecurity context

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

The lab models permitted communication in a synthetic network. An edge is a
stored relationship, not proof that communication occurred.

Module 16 deliberately broadens the input contract to an edge-list representation that may contain parallel edges and self-loops; its algorithms handle or ignore those cases explicitly.

### Evidence of learning

- equivalent connection description and directed matrix;
- tested four-function API and direct guarded lookup;
- representation comparison;
- explanation of why the model is no longer a tree.

### Spiral 1 synthesis

Students choose among ArrayList, tree, and graph for three short scenarios. For each choice they state:

1. the representation;
2. its central invariant;
3. one operation cost;
4. one safety or correctness risk.

---

# Spiral 2 — LIFO and Depth-First Exploration

## Module 4 — Linear: Stack ADT

Production materials: [Module 4 teaching package](module_04_stack/README.md)

### Learning objectives

Students will:

- specify the LIFO contract independently of its backend;
- implement a checked ArrayList-backed Stack;
- trace growable-array storage and checked geometric growth introduced in this module;
- trace mixed `push`, `pop`, and `peek` operations;
- use a Stack to validate nested delimiters;
- distinguish a Stack ADT from the C runtime call stack.

### Macro-Question

> If the most recently opened task must be completed first, what access rule should the structure enforce?

### Micro-Questions

- Which item may be removed next?
- How should underflow be reported?
- Why must clients not bypass the Stack API and index the backing ArrayList?
- How can a replaceable backing array preserve prior state when a growth request fails?
- Why does doubling reduce the frequency of complete copies during repeated pushes?
- Why does nested structure require LIFO matching?
- How does recursion also depend on stack-like saved state?

### C lab and cybersecurity context

Implement a character Stack and validate delimiters in simplified security-policy expressions. Test empty input, deep nesting, an unmatched closing delimiter, a mismatched delimiter, leftover openings, and an explicit resource limit.

Growable-array storage, replacement-buffer ownership, and checked geometric
growth are introduced here. Students carry forward Module 1's active-prefix
and bounds rules while learning how a successful growth changes capacity and
how a failed growth preserves prior state. They distinguish an individual
copying push from the amortized cost of repeated pushes under a doubling
policy. These are new Stack-backend requirements, not Chapter 1 tasks.

Malformed input must fail safely. The module explicitly distinguishes stack-buffer vulnerabilities, runtime call frames, and the Stack ADT.

Because C has no automatic generic container, later modules receive separately typed `const TreeNode *` and vertex-ID Stack scaffolds with the same contract. Pointer-weak students are not required to design a `void *` generic Stack. A linked-node backend is an extension and an early retrieval opportunity for Module 14.

### Evidence of learning

- stack-state trace;
- API and implementation;
- parser boundary tests;
- push/pop and full-parser complexity;
- ADT-versus-runtime-stack explanation.

### Spiral links

**Revisits:** Module 1's contiguous storage, size/capacity distinction, and
bounds checks; node addresses, fields, and local-variable lifetime from Module 2.

**Introduces:** allocation and release, growable-array storage, checked
doubling, owned storage, Stack encapsulation, and its error contract.

**Forward:** tree DFS and graph DFS.

---

## Module 5 — Tree: Depth-first traversal

Production materials: [Module 5 teaching package](module_05_tree_dfs/README.md)

**14-week role:** required Week 5 tree-DFS unit. Recursive traversal, BST-search tracing, and postorder cleanup are core. Explicit-stack tree traversal remains available in the package as an extension, not a second required implementation.

### Learning objectives

Students will:

- identify recursive base cases and saved state;
- trace preorder, inorder, and postorder;
- implement recursive preorder, inorder, and postorder traversal;
- trace an explicit-stack preorder traversal and explain its correspondence to call frames;
- distinguish the binary-tree representation and trace scaffolded BST search before completing it;
- inspect and test an instructor-provided BST insertion baseline that returns in Module 15;
- use postorder to destroy a dynamically allocated tree safely;
- analyze traversal as `O(n)` time and `O(h)` auxiliary space.

### Macro-Question

> If we follow one branch as far as possible, how do we remember every branch to which we must return?

### Micro-Questions

- What is the smallest valid subtree?
- What must a recursive call remember?
- How does visit placement create preorder, inorder, or postorder?
- Why is the right child pushed first for left-first iterative preorder?
- Why is postorder suitable for freeing nodes?

### C lab and cybersecurity context

Traverse a synthetic in-memory directory or policy tree:

- report flagged nodes using recursive preorder;
- trace the frontier of an instructor-provided typed `const TreeNode *` Stack; implementing the explicit-stack traversal is an extension;
- perform an inorder trace and complete scaffolded BST search;
- destroy a heap-allocated test tree in postorder.

The instructor supplies the allocated-node fixture and constructor. Students reuse Module 2's binary `left`/`right` links while learning that these nodes now require matching release calls. Module 2 only reset local node fields; Module 5 destroys individually allocated nodes. Real filesystem traversal is not required. Students document that aliases or symbolic links would require graph-style visited tracking.

### Evidence of learning

- call-stack and explicit-stack traces;
- recursive C traversal and cleanup implementation;
- empty, single-node, balanced, and skewed tests;
- cleanup evidence;
- time/space analysis using `n` and `h`.

### Spiral links

**Revisits:** Stack, tree representation, `NULL`, ownership.  
**Forward:** graph DFS, BST inorder reasoning, and AVL height.

---

## Module 6 — Graph: Depth-first search

Production materials: [Module 6 teaching package](module_06_graph_dfs/README.md)

**14-week role:** required Week 6 graph-DFS unit and Practical 1. Iterative graph DFS is the required implementation; recursive graph DFS is traced and remains an extension. The practical replaces the ordinary Module 6 lab submission.

### Learning objectives

Students will:

- explain why graph DFS requires visited state;
- implement iterative DFS with the Module 4 Stack and trace its recursive equivalent;
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
an instructor-provided vertex-ID Stack with the Module 4 contract. Students
trace the equivalent recursive control flow; implementing that second form
is an extension. Test a cycle, an isolated vertex, a disconnected graph, and
a single vertex. A separate faulty-input test verifies that the Module 6
support API rejects a self-loop.

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

# Spiral 3 — FIFO and Breadth-First Exploration

## Module 7 — Linear: Queue and circular buffer

Production materials: [Module 7 teaching package](module_07_queue/README.md)

### Learning objectives

Students will:

- specify the FIFO contract and checked Queue operations;
- trace a circular array using `head`, `size`, and derived `tail`;
- implement constant-time enqueue and dequeue without shifting;
- compare circular-array and linked-queue representations;
- explain how overflow policy affects data retention.

### Macro-Question

> How can a security-event collector process events in arrival order without shifting all remaining events after every removal?

### Micro-Questions

- What guarantee distinguishes FIFO from LIFO?
- What state distinguishes empty, full, and partially occupied buffers?
- What happens when the physical end of the array is reached?
- When is `tail = (head + size) % capacity` valid?
- Should a full buffer reject newest data, discard oldest data, or apply backpressure?

### C lab and cybersecurity context

Implement a fixed-capacity circular Queue of synthetic security events. Test empty dequeue, capacity one, fill-to-capacity, wrap-around, repeated fill/drain cycles, and FIFO preservation.

Students compare overflow policies for a log-ingestion or packet-buffering system. Silent event loss is treated as a security-relevant design decision.

### Evidence of learning

- wrap-around state trace;
- tested C Queue;
- representation and cost comparison;
- justified overflow/error policy.

### Spiral links

**Revisits:** ArrayList indexes, modular arithmetic, ownership, API contracts.  
**Forward:** tree BFS and graph BFS.

---

## Module 8 — Tree: Breadth-first traversal

Production materials: [Module 8 teaching package](module_08_tree_bfs/README.md)

**14-week role:** bridge portion of combined Week 8. Students complete a short tree level-order trace and inspect/run a supplied bounded scaffold before transferring the Queue model to graph BFS. Module 8 has no standalone submission; implementing tree BFS, its shallowest-match lab, autopsy, and extended width work are optional. Height and balance-factor work moves to Module 15.

### Learning objectives

Students will:

- explain how a Queue produces level-order traversal;
- trace frontier contents and node depths;
- inspect and run a supplied level-order traversal scaffold;
- analyze `O(n)` time and `O(w)` auxiliary space, where `w` is maximum width;
- compare DFS height cost with BFS width cost;
- explain why tree traversal needs no discovered array while graph traversal does.

### Macro-Question

> How can we guarantee that every node close to the root is inspected before any deeper node?

### Micro-Questions

- What does the Queue contain at any moment?
- Why are nodes processed in nondecreasing depth?
- When is BFS preferable to DFS?
- Why does BFS space depend on width?
- Why is visited state unnecessary for a valid tree?
- What additional state will be required when branches can reconnect?

### C lab and cybersecurity context

Trace level-order traversal over a small hierarchical policy or process tree, then inspect and run a supplied bounded traversal scaffold. Use the same Queue-state vocabulary immediately in Module 9. Implementing tree BFS, the complete shallowest-match implementation, and its autopsy remain in the package for extension or a longer calendar.

Height, balance factors, and the rotation advance organizer are taught with AVL work in Module 15 rather than added to this combined week.

### Evidence of learning

- Queue/depth trace included in the single Week 8 BFS submission;
- annotated tree-to-graph transfer explanation;
- width-versus-height space comparison.

### Spiral links

**Revisits:** Queue, tree nodes, and DFS.  
**Forward:** graph BFS.

---

## Module 9 — Graph: Breadth-first search

Production materials: [Module 9 teaching package](module_09_graph_bfs/README.md)

**14-week role:** main implementation portion of combined Week 8. Graph BFS, distance, predecessor state, and path reconstruction form the single required BFS lab; students do not also submit the complete Module 8 lab.

### Learning objectives

Students will:

- implement BFS with discovered, distance, and predecessor state;
- explain why marking on enqueue prevents duplicate frontier entries;
- reconstruct shortest unweighted paths;
- handle cycles, unreachable vertices, and disconnected graphs;
- compare adjacency-matrix `O(V^2)` and adjacency-list `O(V+E)` BFS.

### Macro-Question

> Which system is reachable in the fewest communication hops when relationships may branch, merge, and cycle?

### Micro-Questions

- What breaks if tree BFS is copied unchanged?
- When should a vertex be marked discovered?
- Why does first discovery establish minimum hop distance?
- What additional information does `predecessor[]` preserve?
- How can a complete BFS forest cover disconnected components?

### Learning sequence and representation spiral

Students implement BFS on the known matrix representation. They then inspect and run an instructor-supplied sorted adjacency-list implementation built as an array of dynamic neighbor arrays. This revisits ArrayList without requiring a second BFS implementation or full linked-list work. They compare both traversals and account for the different runtime bounds.

The week opens with the short Module 8 tree trace, making the discovered array and cycle-safe enqueue rule explicit additions rather than introducing a second standalone traversal project.

### C lab and cybersecurity context

Given a synthetic authorized-communication graph, report:

- visit order;
- distance from a source;
- predecessor for each reachable vertex;
- a reconstructed path to a destination;
- an explicit unreachable result;
- an optional full traversal forest. For an undirected graph, its trees identify connected components; no weak/strong-component claim is made for directed graphs.

The context is hop-based blast-radius analysis. Students state that hop count alone does not model likelihood, exploitability, or real risk.

### Evidence of learning

- Queue/distance/predecessor trace;
- cycle-safe BFS;
- reconstructed path as an output certificate;
- matrix-versus-adjacency-list complexity analysis;
- the Module 8 tree-to-graph transfer trace, all in one combined submission.

### Spiral 3 synthesis

Students compare what a Queue item and “discovered but unprocessed” mean in:

1. an event Queue;
2. tree level-order traversal;
3. graph BFS.

They explain why FIFO order, unit/unweighted edges, and marking vertices when enqueued together produce minimum-hop distance. FIFO alone is not a shortest-path guarantee.

---

# Spiral 4 — Priority and Weighted Exploration

## Module 10 — Linear: Priority Queue ADT

Production materials: [Module 10 teaching package](module_10_priority_queue/README.md)

**14-week role:** contract-and-baseline portion of combined Week 9. The instructor supplies the completed, tested unsorted-array Priority Queue. Students inspect its contract, measure its comparison cost, and then replace its backend in Module 11. Module 10 has no separate programming project or submission.

### Learning objectives

Students will:

- specify a minimum-priority Queue independently of its backend;
- distinguish FIFO order from priority order;
- define deterministic tie behavior;
- inspect and test a supplied unsorted dynamic-array reference backend;
- compare sorted-array and unsorted-array costs;
- identify starvation and mutable-priority hazards.

### Macro-Question

> If urgent alerts should be processed before routine alerts, what replaces arrival order, and what does that choice cost?

### Micro-Questions

- Does a smaller or larger number mean higher priority?
- What should happen when priorities tie?
- Which workload favors an unsorted array?
- Which workload favors a sorted array?
- Can a low-priority item wait forever?
- Will later algorithms require decrease-key, or can they tolerate duplicate entries?

### C lab and cybersecurity context

Run and inspect a supplied stable, unsorted-array Priority Queue of alert records. Use its arrival-sequence tie-breaker, count comparisons for insert-heavy and removal-heavy workloads, and compare with a sorted-array design on paper. Students preserve this reference implementation as the differential-test oracle for Module 11.

SOC alert triage motivates the ADT while also exposing fairness, starvation, and poorly calibrated severity scores.

The canonical backend table is explicit: an unsorted dynamic array has amortized `O(1)` insertion and `O(n)` peek/extract-min. A sorted array has `O(n)` insertion and only achieves `O(1)` peek/extract-min when the minimum is maintained at the removable end; otherwise extraction requires shifting and is `O(n)`.

### Evidence of learning

- formal ADT contract and comparator;
- operation-count experiment against the supplied linear backend;
- backend-selection and fairness-risk explanation included in the single Week 9 Heap submission.

### Spiral links

**Revisits:** Queue semantics, ArrayList growth, abstraction boundaries.  
**Forward:** Heap as a faster backend and Dijkstra as a client.

---

## Module 11 — Tree: Binary Heap

Production materials: [Module 11 teaching package](module_11_binary_heap/README.md)

**14-week role:** main implementation portion of combined Week 9. Students implement the Heap backend, preserve the Module 10 contract, and compare it with the supplied linear reference. This is the week’s single required submission.

### Learning objectives

Students will:

- map a complete binary tree onto an array;
- derive parent and child index formulas;
- distinguish heap order, BST order, and sorted order;
- implement sift-up, sift-down, insertion, peek, and root `extract_min`;
- use an invariant checker after every mutation;
- verify `O(1)` peek and `O(log n)` insert/`extract_min`.

### Macro-Question

> Can a compact array avoid scanning every alert while still returning the highest-priority item quickly?

### Micro-Questions

- Why must the tree be complete?
- Where is the next inserted item placed?
- Why is repairing one root-to-leaf path sufficient?
- Is a Heap globally sorted?
- How does Heap order differ from BST order?
- How is a binary Heap different from C’s dynamically allocated heap memory?

### C lab and cybersecurity context

Replace the Module 10 backend with a minimum binary Heap while preserving the Priority Queue API. Implement `is_min_heap` before benchmarking. Test empty and singleton heaps, ascending/descending input, duplicate priorities, a missing right child, capacity growth, and randomized operations against a simple reference implementation.

The reference implementation is supplied rather than assigned as an additional project. Contract inspection, linear-versus-Heap measurements, and the Heap lab form one combined submission.

The stated `O(log n)` removal bound applies to `extract_min`, not to locating and deleting an arbitrary value. The `O(n)` invariant checker is debug/test instrumentation: students report instrumented and uninstrumented measurements separately and do not include full validation in the claimed per-operation bound.

The invariant checker is treated as an integrity control: corrupt indexes or size fields can cause memory errors, while silent Heap-order corruption can misprioritize events.

### Evidence of learning

- array ↔ complete-tree translation;
- insertion/`extract_min` traces;
- Heap-backed implementation and invariant checker;
- randomized differential tests;
- comparison counts against Module 10.

### Spiral links

**Revisits:** ArrayList, complete trees, height, invariants, Priority Queue contract.  
**Forward:** Dijkstra and Prim. Module 13 will add collision-aware exact lookup, and Module 15 will contrast Heap partial order with AVL total search order.

---

## Module 12 — Graph: Dijkstra’s shortest-path algorithm

Production materials: [Module 12 teaching package](module_12_graph_dijkstra/README.md)

**14-week role:** required Week 10 Dijkstra unit and Practical 2. Students complete and test the bounded relaxation/frontier core inside a supplied weighted-graph, Heap, and path-reconstruction scaffold. Practical 2 is the week’s only submission; the full standalone Stage E lab remains a longer-calendar resource.

### Learning objectives

Students will:

- explain why BFS is insufficient for unequal edge costs;
- maintain tentative distance, predecessor, and frontier state;
- apply relaxation correctly;
- explain the nonnegative-weight precondition;
- implement Dijkstra with a weighted adjacency list and minimum Heap;
- reconstruct a minimum-cost path and report unreachable destinations.

### Macro-Question

> BFS minimizes the number of edges. How can we minimize total cost when different edges have different weights?

### Micro-Questions

- Can a path with more edges have a lower total cost?
- What does `dist[v]` mean before and after selection?
- What condition causes relaxation?
- Why is selecting the smallest tentative distance safe only with nonnegative weights?
- How are stale Heap entries detected if decrease-key is not implemented?
- How are overflow and infinity handled safely?

### C lab and cybersecurity context

Within Practical 2, complete the bounded Dijkstra core in a supplied weighted adjacency-list integration scaffold using lazy duplicate Heap entries. Required trace, repair, and tests include:

- unreachable destinations;
- zero-weight and equal-cost alternatives;
- rejection of negative weights;
- stale entries;
- invalid vertices;
- overflow-safe candidate-distance calculation;
- predecessor-based path reconstruction.

The supplied code handles already-mastered parsing and Heap plumbing so the practical can assess relaxation, stale-entry handling, overflow safety, unreachable state, and path evidence within the Week 10 contact budget. There is no second Module 12 lab submission.

Weights represent a clearly defined synthetic quantity such as latency or inspection cost. Students explain that the result is only as meaningful as the additive weight model.

The core loop uses strict relaxation, `candidate < dist[v]`, and skips stale snapshots with `if (popped_distance != dist[u]) continue`. It computes a candidate only when `dist[u] != INF` and `weight <= INF - dist[u]`. Negative textual weights are rejected before any conversion to an unsigned storage type.

With lazy duplicate entries, the Heap can hold `O(E)` snapshots. The full bound is `O(V + E log(E + 1))` time and `O(V + E)` auxiliary state; for a simple graph this becomes `O(V + E log V)`. Students analyze the implementation they actually wrote rather than claiming a decrease-key bound automatically.

### Evidence of learning

- complete `distance/predecessor/frontier` trace;
- integrated implementation;
- reconstructed path and independently verified cost;
- BFS-versus-Dijkstra comparison;
- complexity matching the actual Heap strategy.

### Spiral 4 synthesis within Practical 2

As the practical’s comparison component, students use the same graph to:

1. run BFS while ignoring weights;
2. run the instructor-supplied Dijkstra/linear-Priority-Queue reference;
3. run Dijkstra with the Heap backend;
4. compare paths, operation counts, and API calls;
5. identify which behavior belongs to the ADT and which belongs to its implementation.

---

# Associative-Index Bridge — Sparse Keys and Collisions

## Module 13 — Supporting ADT: Hash Table

Production materials: [Module 13 teaching package](module_13_hash_table/README.md)

**14-week role:** required Week 11 Hash Table core. Students implement bounded probing, lookup, insert/update, deletion, and tombstone reuse, then complete and test an instructor-scaffolded transactional rebuild. Additional adversarial and capacity-policy work in the complete package is extension material.

### Learning objectives

Students will:

- distinguish a map's key-to-value contract from a particular table representation;
- compute home slots and trace linear probing with wraparound;
- explain why collisions are normal and how `EMPTY`, `OCCUPIED`, and `DELETED` states preserve probe-chain reachability;
- implement exact lookup, insert-or-update, and deletion without duplicating a key;
- maintain `size`, tombstone count, capacity, uniqueness, and reachability invariants;
- complete and test a bounded transactional grow/compact scaffold that rehashes entries when capacity changes;
- compare hash-table, direct-index-array, linked-chain, and AVL lookup trade-offs; and
- qualify expected constant-time claims and explain collision-flooding risk precisely.

### Macro-Question

> When external indicator IDs are sparse and provide no search direction, how can we find a stored record without scanning every record—and what can collisions make that promise cost?

### Micro-Questions

- What is the difference between a key, a value, a hash value, and a home slot?
- What happens when two keys have the same home slot?
- Why must a probe wrap from the last slot to slot zero?
- Why does lookup stop at `EMPTY` but continue through `DELETED`?
- How can an insertion reuse a tombstone without creating a duplicate key later in the same cluster?
- Why must every probe loop have a capacity-sized bound?
- Why are all occupied entries rehashed rather than copied to the same indexes after growth?
- Under what distribution and load assumptions is expected `O(1)` defensible?

### Learning sequence

Meeting A begins with sparse synthetic indicator IDs. Students compare an impractically large direct-index array with an eight-slot table, then place keys 10, 18, and 26. All three have home slot 2, so they occupy slots 2, 3, and 4. They delete 18 and discover that marking slot 3 `EMPTY` would make 26 falsely unreachable. A separate 7, 15, 23 trace forces wraparound through slots 7, 0, and 1.

Meeting B makes the table dynamic while keeping the implementation bounded. Capacities follow `8 -> 16 -> 32 -> 64`. Before a new key would make live entries plus tombstones exceed three quarters of capacity, the table either compacts at the same capacity or grows. Rebuilding allocates fresh storage, rehashes only occupied entries, and commits only after the complete rebuild succeeds. Students complete the bounded decision/commit points in a supplied rebuild scaffold and run the instructor’s allocation-failure and maximum-capacity state-preservation tests.

### C lab and cybersecurity context

Implement a bounded `uint32_t`-to-`int` sparse-indicator map using open addressing and linear probing. Key zero is legal because occupancy is represented by a separate state field. The three implementation clusters cover:

1. a capacity-bounded probe helper and exact lookup;
2. insert-or-update, deletion, tombstone reuse, and exact probe evidence; and
3. completion and testing of a supplied transactional compaction/growth and rehash scaffold.

Students author three bounded test categories: collision/wraparound with exact probes; tombstone reachability, update, reuse, and duplicate prevention; and scaffolded growth/compaction with one forced maintenance-allocation failure and state preservation. They also run an instructor-supplied suite covering missing keys, key zero, additional allocation failures, maximum load, invalid arguments, validation, destruction, and long churn.

The teaching hash is deliberately transparent: `home = key % capacity`. It is suitable for tracing this bounded mechanism, not a production security recommendation. Students describe a hash-flood algorithmic-complexity denial of service only when chosen colliding keys cause excessive work. They also state that a non-cryptographic table hash does not authenticate data, establish authorization, or provide cryptographic collision resistance.

Let `n` be live entries and `m` be capacity. Expected lookup, insertion, and deletion are `O(1)` only when hashes are adequately distributed and load is controlled; each inspects at most `m` slots and is `O(m)` in the worst case (often written `O(n)` only when `m = Theta(n)`). Rebuilding scans `m` old slots and reinserts `n` entries, so it is expected `O(m)` under the same assumptions and worst-case `O(m + n^2)`, bounded by `O(m^2)`, when repeated placements collide. Insertion is amortized expected `O(1)` only under the stated assumptions.

### Evidence of learning

- collision, wraparound, and tombstone traces with exact inspected-slot counts;
- tested `hash_table.h`/`hash_table.c` implementation;
- scaffolded transactional-rehash and allocation-failure evidence;
- three student-authored test categories covering the listed core cases;
- Hash-Table Autopsy correction; and
- a workload-based comparison with direct indexing, separate chaining, and AVL.

### Bridge links

**Revisits:** Module 1's contiguous storage, bounds, and unchanged state after
rejection; Module 4's growable-array storage, doubling, and failed-growth
preservation; modular indexing; and Module 12's dense internal vertex IDs.

**Forward:** Module 14 contrasts open-addressed slots with separately allocated nodes; Module 15 contrasts expected exact lookup with ordered `O(log n)` lookup; the capstone can map sparse external labels to validated dense graph IDs.

---

# Spiral 5 — Invariants and Minimum-Cost Connectivity

## Module 14 — Linear: Linked-list retrieval clinic and Union-Find bridge

Production materials: [Module 14 teaching package](module_14_linked_list_dsu/README.md)

**14-week role:** required Week 12 bounded ownership clinic plus DSU. Students trace supplied list operations, repair one ownership-sensitive operation, and implement/test DSU. Remaining list operations and linked Stack/Queue work are extensions; the edge-list builder and comparator are supplied for a brief instructor-led trace.

### Learning objectives

Students will:

- trace safe singly linked-list insertion, deletion, traversal, and destruction;
- state ownership and link invariants;
- complete or repair one bounded ownership-sensitive operation in a supplied list scaffold, diagnosing its leak, dangling-pointer, or use-after-free failure;
- implement `make_set`, `find`, and `union` over `parent[]` and `rank[]` or `size[]`;
- apply path compression and union by rank/size;
- use Union-Find for incremental connectivity and cycle detection.

### Macro-Question

> As relationships arrive one at a time, how can we determine whether two vertices are already connected without searching the entire graph after every update?

### Micro-Questions

- Which pointer must be saved before deleting a node?
- When is it safe to call `free`?
- How can a flat parent array encode a forest?
- What identifies a representative root?
- Why do naïve unions form long chains?
- Why do path compression and union by rank preserve membership?
- What questions can Union-Find not answer?

### Learning sequence

Meeting A contrasts linked nodes with Module 1's contiguous storage. Students trace the supplied insertion, deletion, traversal, and destruction operations, then repair one selected list or linked-adjacency ownership defect. They do not complete three operations plus a second repair, and they are not required to design a complete list library from scratch.

Meeting B treats Union-Find as a bridge: two linear arrays encode a forest. Students trace a deliberately tall parent forest, apply compression, and implement a bounds-checked interface. A two-pass iterative `find` avoids relying on deep recursion.

At the close, the instructor demonstrates and runs an instructor-supplied undirected edge-list builder and safe `qsort` comparator interface. Students briefly trace why the builder emits one record per logical undirected edge, does not double-count mirrored adjacency entries, and preserves genuine parallel edges. This is a short Kruskal pre-lab, not another implementation or evidence assignment.

### C lab and cybersecurity context

The lab has two linked parts:

1. repair one broken incident-record or standalone linked-adjacency chain containing a leak, dangling pointer, or use-after-free;
2. implement a DSU that clusters synthetic hosts as relationships arrive.

Reject out-of-range identifiers before indexing `parent[]`. Students state that shared DSU membership does not imply trust or authorization.

The capstone continues using the array-of-dynamic-neighbor-arrays representation introduced in Module 9. The linked-adjacency repair is a standalone ownership exercise, so no unexplained capstone representation migration occurs.

### Evidence of learning

- before/after linked-list ownership diagram;
- one sanitizer-clean repaired list operation;
- parent-array trace before/after compression;
- tested `dsu.h`/`dsu.c`;
- amortized `O(alpha(n))` interpretation and one DSU limitation.

### Spiral links

**Revisits:** ArrayList versus links, components, implicit trees, ownership.  
**Forward:** Kruskal cycle checks in Module 16.

---

## Module 15 — Tree: BST-to-AVL synthesis

Production materials: [Module 15 teaching package](module_15_bst_avl/README.md)

**14-week role:** required Week 13 AVL unit and the formal home for height, balance factors, and rotations deferred from the BFS bridge. AVL insertion and validation are core, AVL deletion is extension, and the week produces one submission within the 180-minute budget.

### Learning objectives

Students will:

- state BST ordering and AVL balance invariants;
- trace and test the instructor-provided BST search/insertion baseline seeded in Module 5;
- show how hostile insertion order creates height `n - 1`;
- compute heights and balance factors;
- recognize LL, RR, LR, and RL cases;
- implement rotations and AVL insertion;
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

The course uses edge height consistently: `height(NULL) = -1` and `height(leaf) = 0`. Therefore an `n`-node chain has height `n - 1`.

Build an adversarial asset or indicator index:

1. use the tested baseline to insert ascending, descending, and deterministically shuffled keys into a BST;
2. measure height and comparison counts;
3. run the supplied `validate_bst`;
4. implement left/right rotations and the AVL rebalancing path;
5. test all four canonical rotation cases;
6. run and extend `validate_avl` tests;
7. destroy the structure and verify a sanitizer-clean result.

Duplicate-key policy must be explicit. Test sizes are bounded so a deliberately skewed recursive baseline cannot exhaust the runtime call stack; an iterative cleanup is supplied when larger experiments are used. Full AVL deletion is an extension, not a core requirement.

The security connection is algorithmic-complexity denial of service. Students distinguish degraded complexity from memory corruption and from general resource exhaustion.

### Evidence of learning

- four rotation traces;
- BST-versus-AVL measurement table;
- invariant-checking tests;
- safe implementation;
- concise threat analysis.

### Spiral links

**Revisits:** Module 5 BST seed and inorder DFS, tree-height reasoning, Heap-order contrast, and Module 13's sparse exact-match index.
**Forward:** compare AVL's ordered worst-case guarantee with hash lookup's expected exact-match cost, then compare local and global invariants.

---

## Module 16 — Graph: Prim and Kruskal

Production materials: [Module 16 teaching package](module_16_prim_kruskal/README.md)

**14-week role:** required Week 14 MST and capstone-integration unit. One folded artifact combines the selected complete MST core, the scaffolded comparison, the embedded Spiral 5 individual check, and the capstone integration checkpoint. These are not separate programming submissions or additional contact blocks; the defense remains in the final-assessment period.

### Learning objectives

Students will:

- distinguish a shortest-path tree from a minimum spanning tree;
- state the weighted, undirected input contract;
- trace Prim’s frontier growth and Kruskal’s component merging;
- explain the roles of Heap and Union-Find;
- implement one complete MST core loop and finish/test bounded decision checkpoints in a supplied implementation of the other;
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

Students reuse the tested graph parser, Module 11 Heap, and Module 14 DSU. They complete:

- one selected algorithm—key-based Prim or Kruskal—from a bounded skeleton;
- bounded decision checkpoints in the supplied implementation of the other algorithm;
- result validation;
- total-weight comparison.

Prim uses lazy duplicate Heap entries with stale-key and `in_tree` checks; it restarts from each unvisited vertex for a disconnected input. Kruskal uses the supplied edge-list builder, `qsort`, a relational comparator, and DSU. A short comparator retrieval explains why returning `left_weight - right_weight` can overflow.

Students do not rewrite the parser, Heap, and DSU in this module. Tests include a singleton graph, normal connected graph, disconnected graph, equal-weight alternatives, parallel edges, self-loops, negative weights, invalid endpoints, and a total weight requiring `int64_t`.

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
- one tested complete implementation plus completed checkpoints and output from the supplied comparison implementation;
- invariant-based result validation;
- algorithm-selection memo;
- cost-versus-resilience analysis.

### Spiral 5 synthesis and individual check

Given an adversarial insertion stream and a weighted graph, students:

1. trace a collision cluster and preserve lookup through a deletion marker;
2. trace DSU unions and identify the first cycle-producing edge;
3. draw the skewed BST created by hostile order;
4. perform the required AVL repair;
5. select a hash table or AVL index from exact-match, ordering, and worst-case requirements;
6. choose Prim or Kruskal for the supplied graph representation; and
7. distinguish exact lookup, MST, shortest-path, connectivity, and resilience objectives.

These prompts are embedded in the existing MST trace and the single folded Week 14 artifact; they are not a separate check, capstone program, or contact block. The capstone report absorbs the longer synthesis, and the defense occurs in the scheduled final-assessment period rather than inside Week 14’s three contact hours.

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
| Twelve weekly lab artifacts, including combined Weeks 8–9 and the folded Week 14 checkpoint | 26% | C code, tests, tool output, and memory models; one artifact in each lab week |
| Five embedded spiral synthesis checks | 15% | Transfer scored within the Week 3 lab, Practical 1, Week 8 combined lab, Practical 2, and Week 14 artifact; no separate submissions |
| Segfault Autopsies and Micro-CTFs | 10% | One embedded debugging artifact per spiral |
| Two cumulative practical assessments | 14% | Weeks 6 and 10 implementation, trace, debug, repair, select, and justify |
| Individual synthesis portfolio | 10% | Revised artifacts, connection maps, test evidence, reflection |
| Capstone | 15% | Integrated tool, report, individual evidence, and defense/equivalent |
| **Total** | **100%** | |

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

### Practical 2 — Week 10, with Module 12

Students:

- interpret a short tree-level-order-to-graph-BFS transfer trace and complete graph distance/predecessor state;
- repair a circular-buffer or visited-state defect;
- trace Heap operations;
- execute one Dijkstra relaxation round;
- complete or repair a bounded Dijkstra core and its stale-entry, unreachable, and negative-input tests;
- state the nonnegative-weight contract;
- compare the supplied linear Priority Queue baseline with the Heap backend.

Both practicals include an expert-model correction opportunity followed by a short transfer question. Corrections recover evidence of learning, not all points automatically.

Each practical replaces that teaching week’s ordinary lab rather than adding another assignment. Combined Weeks 8 and 9 likewise produce one submission each: the graph-BFS lab absorbs the tree-BFS bridge evidence, and the Heap lab absorbs the supplied Priority Queue baseline comparison.

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
| Week 8 / Modules 8–9 | Queue-backed BFS and unweighted paths |
| Week 10 / Module 12 | Heap-backed Dijkstra |
| Week 11 / Module 13 | Hash-backed sparse external-label-to-dense-ID index |
| Week 12 / Module 14 | Reusable DSU; linked-adjacency repair remains a standalone clinic |
| Week 13 / Module 15 | AVL-backed ordered asset/indicator index and backend-selection comparison |
| Week 14 / Module 16 | Prim, Kruskal, cross-validation, and comparative report |

Each milestone contributes evidence inside that week’s lab or practical; it is not a second weekly submission. The Week 14 lab grade covers the bounded MST implementation and comparison, while the capstone grade covers cross-module integration, the cumulative report, and the defense. The same code is not scored twice for the same criterion.

The final toolkit must:

- validate all vertex identifiers and input sizes;
- document ownership for each allocated object;
- traverse the model with DFS and BFS;
- reconstruct unweighted and weighted paths;
- reject negative edge weights for Dijkstra;
- map sparse external labels to validated dense internal IDs without confusing a hash with authentication;
- select hash-backed exact lookup or AVL-backed ordered lookup from the stated workload and worst-case requirements;
- compute an MST or minimum spanning forest with one complete and one scaffolded algorithm;
- cross-check Prim and Kruskal totals when both are enabled;
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
uses fixed-array bounds and plain integer counts. Module 2 introduces local
node variables, pointer links, and recursive field clearance. Module 4 adds
allocation and replaceable array storage; Module 5 adds allocated tree nodes.
Module 2's recursive functions assume valid trees: inspect malformed cycles
with diagrams, not by running recursive operations on them.

- compile with the strongest practical warnings for the course toolchain;
- never ignore an allocation result;
- validate external indexes before array access;
- define empty/error behavior in the API;
- use `size_t` for sizes and indexes where appropriate;
- define hash-key ownership and update policy explicitly;
- bound every probe loop, check load-factor arithmetic, and rehash transactionally;
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
| Addresses and pointers | Module 2 | Later node and container implementations |
| `struct` and local-node lifetime | Module 2 | Later node and container implementations |
| Allocation, release, and owned storage | Module 4 array storage; Module 5 individual nodes | Later containers and linked-node implementations |
| Linked-node mental model | Module 2 tree representation; Module 14 retrieval clinic | Trees, linked adjacency, DSU bridge |
| Binary-tree representation and recursive field clearance | Module 2 | Graph contrast, DFS, BFS |
| BST-ordering preview | Module 5 | AVL |
| Graph representation | Module 3 | All graph algorithms |
| Stack | Module 4 | Tree and graph DFS |
| Growable-array storage and checked doubling | Module 4 | Priority Queue, Heap, Hash Table |
| Recursive base cases and bottom-up field clearance | Module 2 | Formal traversal and later tree algorithms |
| Traversal orders and explicit call frames | Module 5 recursive core; explicit-stack tree traversal as extension | Tree and graph algorithms |
| Queue | Module 7 | Tree and graph BFS |
| Tree level-order transfer | Module 8 bridge in combined Week 8 | Graph BFS |
| Height and balance | Module 15 | AVL validation and rotation |
| Adjacency list and predecessors | Module 9 main lab in combined Week 8 | Dijkstra and Prim |
| Priority Queue ADT and linear reference | Module 10 baseline in combined Week 9 | Heap comparison, Dijkstra, and Prim |
| Binary Heap | Module 11 main lab in combined Week 9 | Dijkstra and Prim |
| Weighted relaxation | Module 12 | Dijkstra; comparison with Prim |
| Hash Table, linear probing, and tombstones | Module 13 | Sparse external-label index; comparison with AVL |
| Union-Find with compression/rank | Module 14 | Kruskal |
| BST operations and AVL rotations | BST operations seeded in Module 5; height, balance, and rotations mastered in Module 15 | Ordered-index capstone; comparison with hashing |
| Edge-list construction and safe sorting/comparator | Module 14 Kruskal pre-lab | Kruskal |

Scope controls:

- Every teaching week has a hard 180-minute contact budget. A complete package may contain extension, make-up, or longer-calendar materials beyond that budget.
- Module 1 requires checked indexed read/update, first-match search, append,
  insertion, and removal in a fixed array. Its extensions add tests only;
  growable-array storage is introduced in Module 4.
- Module 5 requires recursive tree DFS; explicit-stack tree traversal is an extension. Module 6 requires iterative graph DFS; recursive graph DFS is an extension.
- Modules 8 and 9 share one Week 8 submission. The Module 8 core is a short level-order trace and supplied-code inspection; graph BFS, predecessor state, and path reconstruction are the main implementation.
- Modules 10 and 11 share one Week 9 submission. The Module 10 unsorted-array implementation is supplied; the Heap backend and comparison are the main implementation.
- Module 13 uses a scaffolded transactional rebuild, and Module 14 requires one bounded list repair plus DSU; their complete package menus are not assigned as hidden homework.
- AVL insertion is core; AVL deletion is an extension.
- Module 16 reuses tested graph, Heap, and DSU libraries.
- Prim and Kruskal are both traced and compared; the default 14-week path implements Kruskal fully and finishes/tests bounded decision checkpoints in a supplied Prim implementation.
- Hash tables provide the sparse external-key index. Boolean/indexed visited arrays remain the simpler representation when vertex IDs are already dense.
- The required hash-table backend uses open addressing with linear probing; separate chaining and cryptographic hash design are extensions. Advanced general-purpose sorting remains outside the required topic list.
- Algorithms operate only on synthetic, authorized datasets.

---

# Required 14-Week Calendar

| Week | Primary topic | Package use and major artifact |
|---:|---|---|
| 1 | Keeping data together with a fixed-capacity ArrayList | Module 1; checked operations and bounds/invariant autopsy |
| 2 | Expression-tree model and binary-tree links | Module 2; local-node construction, search, and clearance evidence |
| 3 | Graph fundamentals | Module 3; Spiral 1 synthesis and capstone skeleton |
| 4 | Stack | Module 4; growable backend and nested-input Micro-CTF |
| 5 | Tree DFS | Module 5 recursive core; explicit-stack implementation is extension |
| 6 | Graph DFS | Module 6 iterative core; Spiral 2 synthesis and Practical 1 replace the ordinary lab |
| 7 | Queue | Module 7; circular-buffer incident analysis |
| 8 | BFS from trees to graphs | Module 8 trace and supplied-code inspection + Module 9 graph-BFS lab; one combined submission |
| 9 | Priority Queue contract to Binary Heap | Supplied Module 10 baseline + Module 11 Heap lab; one combined submission |
| 10 | Dijkstra | Module 12; Spiral 4 synthesis and Practical 2 replace the ordinary lab |
| 11 | Hash Table | Module 13; linear probing, tombstones, and scaffolded transactional-rehash experiment |
| 12 | Linked-list retrieval and Union-Find | Module 14; one bounded ownership repair and DSU |
| 13 | BST-to-AVL | Module 15; height/balance, adversarial-input, and index-selection experiment |
| 14 | Prim and Kruskal | Module 16; one folded MST, embedded Spiral 5 check, and capstone-integration artifact |

The capstone begins with the Week 3 skeleton and receives the milestones listed above; it is not introduced in Week 14. The Module 16 individual check and integration checkpoint are embedded in the week’s single artifact, while the capstone defense uses the scheduled final-assessment period. If that period is unavailable, move the defense to an institutionally approved assessment slot rather than adding it to Week 14’s 180-minute plan.

The 16 full packages remain useful for extensions, make-up work, or a longer calendar. In the 14-week path, do not release both complete Stage E labs in a combined week as required work. Week 11 Hash Table and Week 12 List/DSU must likewise use their bounded 180-minute cores rather than their complete package menus. Use the exact selections in the [14-week delivery guide](Data_Structures_Course_2026_14_Week_Delivery_Guide.md), and do not turn omitted implementations into uncounted homework.

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
