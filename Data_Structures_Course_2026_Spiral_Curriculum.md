# Data Structures Course 2026

## Interleaved Spiral Curriculum for Cybersecurity Freshmen

### Curriculum status and assumptions

This document converts the course concept into an operational 15-module curriculum. It assumes:

- second-semester cybersecurity students;
- prior experience with C variables, functions, arrays, loops, and conditionals;
- limited fluency with pointers, dynamic allocation, and `struct`;
- approximately 3 contact hours per module, delivered as two class meetings or an equivalent lecture/lab format; final capstone integration and defense use the institution’s scheduled final-assessment period;
- synthetic, instructor-controlled cybersecurity datasets rather than live-system scanning or exploitation;
- a C11-compatible compiler, strong compiler warnings, a debugger, automated tests, and memory/error sanitizers when the platform supports them.

The course is not organized as five consecutive linear modules, followed by five tree modules, followed by five graph modules. It makes five increasingly sophisticated passes through:

> **Linear/supporting ADT → Tree application → Graph generalization**

Students therefore encounter the same ideas—representation, invariants, traversal, frontier management, complexity, ownership, and failure—several times in different forms.

---

## 1. Course learning outcomes

By the end of the course, students will be able to:

1. Draw and explain the memory representation of array-backed, pointer-linked, tree, heap, and graph structures.
2. Specify an abstract data type independently of its underlying representation.
3. Implement, test, and safely destroy core data structures in C.
4. State and check the representation invariant that makes each structure correct.
5. Implement and trace DFS and BFS on trees and graphs.
6. Implement and analyze BST, AVL-tree, binary-heap, and disjoint-set operations.
7. Implement Dijkstra and one complete minimum-spanning-tree algorithm, complete and test a scaffolded implementation of the other, and trace and compare both Prim and Kruskal under their required input assumptions.
8. Analyze worst-case, average-case where appropriate, amortized, and representation-sensitive costs.
9. Select a structure or algorithm from workload and correctness requirements rather than familiarity.
10. Diagnose pointer, bounds, ownership, overflow, and invariant failures using diagrams, tests, warnings, sanitizers, and a debugger.
11. Explain how representation choices can create reliability, performance, and security consequences.
12. Communicate a technical design through pseudocode, memory diagrams, tested code, complexity arguments, and plain-language synthesis.

---

## 2. The five spirals

| Spiral | Linear/supporting module | Tree module | Graph module | Recurring idea |
|---|---|---|---|---|
| 1 | 1. ArrayList and linked-node preview | 2. Binary-tree foundations and BST seed | 3. Graph models and representations | Representing relationships in memory |
| 2 | 4. Stack | 5. Tree DFS | 6. Graph DFS | LIFO-controlled exploration |
| 3 | 7. Queue | 8. Tree BFS | 9. Graph BFS | FIFO-controlled exploration |
| 4 | 10. Priority Queue ADT | 11. Binary Heap | 12. Dijkstra | Priority-controlled exploration |
| 5 | 13. Linked-list retrieval and Union-Find | 14. BST-to-AVL synthesis | 15. Prim and Kruskal | Maintaining global invariants while optimizing |

This map contains deliberate previews and returns:

- Linked nodes are previewed in Module 1, used in early tree work, and retrieved through bounded implementation and repair in Module 13.
- BST ordering is seeded in Module 2, used during tree traversals, and formally strengthened into AVL balance in Module 14.
- The adjacency matrix appears first because it has low pointer complexity. Adjacency-list reasoning is introduced later as pointer and dynamic-array fluency grows.
- Stack precedes DFS; Queue precedes BFS; Heap precedes Dijkstra and Prim; Union-Find precedes Kruskal.

---

## 3. Recurring questions and learning routine

Every module returns to seven anchor questions:

1. What problem does the ADT solve?
2. How is it represented in memory?
3. What invariant must remain true?
4. What operations change the state?
5. How is work scheduled or traversal controlled?
6. What are the time and space costs?
7. How can the implementation fail, and how will we detect the failure?

### Standard meeting sequence

**Meeting A: model and reason**

1. Retrieval prompt from the preceding modules
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

## Module 1 — Linear: ArrayList and linked-node preview

Production materials: [Module 1 teaching package](module_01_arraylist/README.md)

### Learning objectives

Students will:

- draw the relationship among `data`, `size`, `capacity`, and allocated storage;
- verify initialization/cleanup, complete and explain the checked reserve/growth
  scaffold, and implement checked access and append;
- trace scaffolded insertion and removal, with independent implementation as an extension;
- explain constant-time indexing, linear shifting, and amortized constant-time append;
- identify bounds errors, failed allocation, stale interior pointers, and ownership mistakes;
- distinguish contiguous ArrayList storage from a previewed chain of linked nodes.

### Macro-Question

> How can a fixed block of C memory behave like a collection that grows, and what trade-offs change when elements are stored in separately allocated nodes?

### Micro-Questions

- What state must be stored in addition to the elements?
- What must be true about `size`, `capacity`, storage ownership, and allocation extent before and after every operation?
- Why should a `realloc` result be checked through a temporary pointer?
- Which operations shift elements?
- Which pointers may become invalid after a resize?
- What does a node store when it refers to another node?

### Learning sequence

Meeting A begins with array indexing and a full four-slot event buffer. Students derive the invariant `size <= capacity`; when `capacity > 0`, `data` owns storage for at least `capacity` elements. They draw pre-resize and post-resize states and compare contiguous storage with a two-node pointer chain. The linked chain is a brief diagrammatic preview, not yet a linked-list implementation.

Meeting B uses a syntax sandbox covering `struct`, `size_t`, pointers,
`sizeof *ptr`, `malloc`, `realloc`, and `free`. Students complete and explain
the reserve scaffold, implement checked access and append, run boundary tests,
and repair an unsafe resize. The core traces insert/remove contracts;
independent implementation remains an extension.

### C lab and cybersecurity context

Implement an ArrayList that stores synthetic authentication-event codes.
Required core tests include empty access, first growth, repeated growth,
invalid indexes, and cleanup. Insertion/removal tests accompany a scaffolded
or extension implementation. An instructor-only deterministic allocator hook
forces the real reserve path to fail and verifies complete state preservation.

The security emphasis is safe ingestion of an unpredictable event volume: bounds checks, capacity arithmetic, resource limits, and explicit failures. “Dynamic” does not mean unlimited.

### Evidence of learning

- before/after memory diagram;
- tested C implementation plus three nonduplicate student-authored
  contract/property tests;
- operation-cost table;
- annotated memory defect and repair;
- short comparison of contiguous storage and linked-node storage;
- bounded-ingestion or backpressure policy distinct from representation safety.

### Spiral links

**Revisits:** arrays, indexing, loops, ownership.  
**Forward:** fixed node arenas in Module 2, graph matrices in Module 3, Stack backing storage in Module 4, and linked-list implementation/repair in Module 13.

---

## Module 2 — Tree: Binary-tree foundations and BST seed

Production materials: [Module 2 teaching package](module_02_binary_tree/README.md)

### Learning objectives

Students will:

- use root, parent, child, leaf, path, depth, height, and subtree terminology;
- translate among a tree diagram, a child-index table, and a pointer-linked C representation;
- state the defining invariants of a rooted binary tree;
- safely construct and inspect fixed trees with `NULL` children;
- recognize the global ordering invariant that turns a binary tree into a BST and state an explicit duplicate-key policy.

### Macro-Question

> How can separate memory objects represent a hierarchy, and what rules prevent those links from becoming an arbitrary graph?

### Micro-Questions

- Does `left` contain a child object or the address of one?
- How is “no child” represented?
- What prevents cycles or multiple parents?
- Does a child need to be adjacent to its parent in memory?
- What must be true of every key in the left and right subtrees—not merely the immediate children?

### Learning sequence

Meeting A generalizes the linked-node preview into a binary tree. Students reconstruct trees from child-index tables, identify cycle and duplicate-parent violations, and compare logical position with physical address. BST order is introduced globally: every left-subtree key is lower and every right-subtree key is higher under the course’s stated “reject duplicate keys” policy. Rotations and balancing are deferred.

Meeting B provides a syntax sandbox for self-referential `struct`, `TreeNode *`, `->`, `&nodes[i]`, and `NULL`. Students build a tree in a fixed, non-resizing node arena and query only immediate relationships. Formal traversal waits until Stack and DFS.

### C lab and cybersecurity context

Build a simplified process or directory hierarchy and implement:

- `is_leaf`;
- `child_count`;
- immediate-family reporting;
- child assignments followed by an instructor-supplied whole-tree validator;
- a range-propagating BST validator on a supplied small example.

The lab distinguishes a local empty-slot check from global validation: preserving “one parent” and “no cycles” requires arena-wide bookkeeping or validation. Fixed-arena nodes are never passed to `free`; Module 5 explicitly introduces separately heap-owned nodes. Students explain why symbolic links or shared children would violate the pure-tree model and motivate graphs.

### Evidence of learning

- diagram ↔ index-table ↔ pointer translation;
- fixed-arena C construction;
- identification of a structural violation;
- pointer-state diagram;
- initial explanation of the BST-ordering benefit.

### Spiral links

**Revisits:** addresses, `NULL`, ownership, representation invariants.  
**Forward:** graph generalization in Module 3, DFS in Module 5, BFS in Module 8, and BST/AVL mastery in Module 14.

---

## Module 3 — Graph: Models and representations

Production materials: [Module 3 teaching package](module_03_graph/README.md)

### Learning objectives

Students will:

- distinguish directed/undirected and weighted/unweighted graphs;
- use vertex, edge, neighbor, degree, path, cycle, and undirected-component vocabulary;
- translate among a diagram, edge set, and adjacency matrix;
- implement bounded matrix-based graph operations;
- compare adjacency-matrix, edge-list, and adjacency-list trade-offs.

### Macro-Question

> What representation is needed when relationships may cross branches, point backward, or form cycles?

### Micro-Questions

- What becomes a vertex, and what becomes an edge?
- How does direction change the meaning of an edge?
- Why is an undirected adjacency matrix symmetric?
- Which tree invariants no longer apply?
- When is a matrix wasteful, and what would an adjacency list store instead?

### Learning sequence

Meeting A adds cross-links and back-links to the Module 2 hierarchy. Students encode the result as an edge set and adjacency matrix, manually identify paths and undirected components, and compare representations without yet performing graph search.

Meeting B implements a bounded adjacency-matrix `Graph`. Modules 3–12 use a simple-graph contract: parallel edges and self-loops are rejected. The low-pointer representation deliberately reduces extraneous load. Adjacency lists are explained and will return after students have stronger dynamic-storage skills. Directed-graph work uses reachability or traversal-forest language rather than the ambiguous word “component.”

### C lab and cybersecurity context

Implement:

- `graph_init`;
- directed and undirected edge insertion;
- edge removal and query;
- degree or in/out-degree;
- neighbor printing;
- vertex-range validation.

The lab models permitted communication in a synthetic network. An edge represents a modeled connection or policy permission, not proof of exploitability.

Module 15 deliberately broadens the input contract to an edge-list representation that may contain parallel edges and self-loops; its algorithms handle or ignore those cases explicitly.

### Evidence of learning

- equivalent diagram, edge set, and matrix;
- tested graph API;
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
- trace mixed `push`, `pop`, and `peek` operations;
- use a Stack to validate nested delimiters;
- distinguish a Stack ADT from the C runtime call stack.

### Macro-Question

> If the most recently opened task must be completed first, what access rule should the structure enforce?

### Micro-Questions

- Which item may be removed next?
- How should underflow be reported?
- Why must clients not bypass the Stack API and index the backing ArrayList?
- Why does nested structure require LIFO matching?
- How does recursion also depend on stack-like saved state?

### C lab and cybersecurity context

Implement a character Stack and validate delimiters in simplified security-policy expressions. Test empty input, deep nesting, an unmatched closing delimiter, a mismatched delimiter, leftover openings, and an explicit resource limit.

Malformed input must fail safely. The module explicitly distinguishes stack-buffer vulnerabilities, runtime call frames, and the Stack ADT.

Because C has no automatic generic container, later modules receive separately typed `const TreeNode *` and vertex-ID Stack scaffolds with the same contract. Pointer-weak students are not required to design a `void *` generic Stack. A linked-node backend is an extension and an early retrieval opportunity for Module 13.

### Evidence of learning

- stack-state trace;
- API and implementation;
- parser boundary tests;
- push/pop and full-parser complexity;
- ADT-versus-runtime-stack explanation.

### Spiral links

**Revisits:** ArrayList invariants, encapsulation, checked errors.  
**Forward:** tree DFS and graph DFS.

---

## Module 5 — Tree: Depth-first traversal

Production materials: [Module 5 teaching package](module_05_tree_dfs/README.md)

### Learning objectives

Students will:

- identify recursive base cases and saved state;
- trace preorder, inorder, and postorder;
- implement recursive and explicit-stack preorder traversal;
- trace and complete scaffolded BST search using the Module 2 ordering seed;
- inspect and test an instructor-provided BST insertion baseline that returns in Module 14;
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
- reproduce the traversal with an instructor-provided typed
  `const TreeNode *` Stack;
- perform an inorder trace and complete scaffolded BST search;
- destroy a heap-allocated test tree in postorder.

The instructor supplies the heap-building fixture and constructor so students do not confuse Module 2’s non-owning arena nodes with individually allocated nodes. Real filesystem traversal is not required. Students document that aliases or symbolic links would require graph-style visited tracking.

### Evidence of learning

- call-stack and explicit-stack traces;
- recursive and iterative C implementations;
- empty, single-node, balanced, and skewed tests;
- cleanup evidence;
- time/space analysis using `n` and `h`.

### Spiral links

**Revisits:** Stack, tree representation, `NULL`, ownership.  
**Forward:** graph DFS, BST inorder reasoning, and AVL height.

---

## Module 6 — Graph: Depth-first search

Production materials: [Module 6 teaching package](module_06_graph_dfs/README.md)

### Learning objectives

Students will:

- explain why graph DFS requires visited state;
- implement recursive and iterative DFS;
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

Using the Module 3 graph, implement recursive and iterative DFS, report all vertices reachable from a selected source, and count connected components only for an undirected graph. The iterative version uses an instructor-provided vertex-ID Stack with the Module 4 contract. Test a cycle, an isolated vertex, a disconnected graph, and a single vertex. A separate faulty-input test verifies that the simple-graph API rejects a self-loop.

The synthetic policy graph asks whether a modeled route reaches a protected zone. Reachability is not treated as exploitability.

### Evidence of learning

- frontier/visited trace;
- tested DFS implementations;
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

### Learning objectives

Students will:

- explain how a Queue produces level-order traversal;
- trace frontier contents and node depths;
- implement level-order traversal and shallowest-match search;
- analyze `O(n)` time and `O(w)` auxiliary space, where `w` is maximum width;
- compare DFS height cost with BFS width cost;
- compute height and preview balance factors for later AVL work.

### Macro-Question

> How can we guarantee that every node close to the root is inspected before any deeper node?

### Micro-Questions

- What does the Queue contain at any moment?
- Why are nodes processed in nondecreasing depth?
- When is BFS preferable to DFS?
- Why does BFS space depend on width?
- Why is visited state unnecessary for a valid tree?
- How do height and left/right subtree heights expose imbalance?

### C lab and cybersecurity context

Implement level-order traversal and a shallowest-match query over a hierarchical policy or process tree. Test an empty tree, one node, balanced/skewed shapes, repeated target values, and a missing target.

Students also compute height and diagnose one skewed BST. They manually trace one instructor-provided rotation as an advance organizer; implementation waits until Module 14.

The course uses edge height consistently: `height(NULL) = -1` and `height(leaf) = 0`. Therefore an `n`-node chain has height `n - 1`.

### Evidence of learning

- Queue/depth trace;
- tested tree BFS;
- width-versus-height space comparison;
- height and balance-factor worksheet.

### Spiral links

**Revisits:** Queue, tree nodes, DFS, height.  
**Forward:** graph BFS and AVL balance.

---

## Module 9 — Graph: Breadth-first search

Production materials: [Module 9 teaching package](module_09_graph_bfs/README.md)

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

Students first run BFS on the known matrix representation. They then receive a scaffolded adjacency list implemented as an array of dynamic neighbor arrays. This revisits ArrayList without requiring full linked-list implementation yet. They compare both traversals and account for the different runtime bounds.

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
- matrix-versus-adjacency-list complexity analysis.

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

### Learning objectives

Students will:

- specify a minimum-priority Queue independently of its backend;
- distinguish FIFO order from priority order;
- define deterministic tie behavior;
- implement an unsorted dynamic-array backend;
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

Implement a stable, unsorted-array Priority Queue of alert records. Use an arrival-sequence field as the tie-breaker. Count comparisons for insert-heavy and removal-heavy workloads, and compare with a sorted-array design on paper.

SOC alert triage motivates the ADT while also exposing fairness, starvation, and poorly calibrated severity scores.

The canonical backend table is explicit: an unsorted dynamic array has amortized `O(1)` insertion and `O(n)` peek/extract-min. A sorted array has `O(n)` insertion and only achieves `O(1)` peek/extract-min when the minimum is maintained at the removable end; otherwise extraction requires shifting and is `O(n)`.

### Evidence of learning

- formal ADT contract and comparator;
- tested linear backend;
- operation-count experiment;
- backend-selection memo;
- fairness-risk explanation.

### Spiral links

**Revisits:** Queue semantics, ArrayList growth, abstraction boundaries.  
**Forward:** Heap as a faster backend and Dijkstra as a client.

---

## Module 11 — Tree: Binary Heap

Production materials: [Module 11 teaching package](module_11_binary_heap/README.md)

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
**Forward:** Dijkstra and Prim. Module 14 will contrast Heap partial order with AVL total search order.

---

## Module 12 — Graph: Dijkstra’s shortest-path algorithm

Production materials: [Module 12 teaching package](module_12_graph_dijkstra/README.md)

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

Extend the adjacency-list graph with nonnegative weights and implement Dijkstra using lazy duplicate Heap entries. Required tests include:

- unreachable destinations;
- zero-weight and equal-cost alternatives;
- rejection of negative weights;
- stale entries;
- invalid vertices;
- overflow-safe candidate-distance calculation;
- predecessor-based path reconstruction.

Weights represent a clearly defined synthetic quantity such as latency or inspection cost. Students explain that the result is only as meaningful as the additive weight model.

The core loop uses strict relaxation, `candidate < dist[v]`, and skips stale snapshots with `if (popped_distance != dist[u]) continue`. It computes a candidate only when `dist[u] != INF` and `weight <= INF - dist[u]`. Negative textual weights are rejected before any conversion to an unsigned storage type.

With lazy duplicate entries, the Heap can hold `O(E)` snapshots. The full bound is `O(V + E log(E + 1))` time and `O(V + E)` auxiliary state; for a simple graph this becomes `O(V + E log V)`. Students analyze the implementation they actually wrote rather than claiming a decrease-key bound automatically.

### Evidence of learning

- complete `distance/predecessor/frontier` trace;
- integrated implementation;
- reconstructed path and independently verified cost;
- BFS-versus-Dijkstra comparison;
- complexity matching the actual Heap strategy.

### Spiral 4 synthesis

On the same graph, students:

1. run BFS while ignoring weights;
2. run Dijkstra with the linear Priority Queue;
3. run Dijkstra with the Heap backend;
4. compare paths, operation counts, and API calls;
5. identify which behavior belongs to the ADT and which belongs to its implementation.

---

# Spiral 5 — Invariants and Minimum-Cost Connectivity

## Module 13 — Linear: Linked-list retrieval clinic and Union-Find bridge

Production materials: [Module 13 teaching package](module_13_linked_list_dsu/README.md)

### Learning objectives

Students will:

- trace safe singly linked-list insertion, deletion, traversal, and destruction;
- state ownership and link invariants;
- repair a bounded leak, dangling-pointer, or use-after-free defect in supplied code;
- complete `push_front`, a bounded deletion operation, and `list_destroy` in a supplied list scaffold;
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

Meeting A returns to the linked-node preview from Module 1 and, where assigned, linked Stack/Queue extensions. Students complete three bounded operations in a supplied list scaffold, then repair a linked-adjacency deletion defect. They are not required to design a complete list library from scratch in this module.

Meeting B treats Union-Find as a bridge: two linear arrays encode a forest. Students trace a deliberately tall parent forest, apply compression, and implement a bounds-checked interface. A two-pass iterative `find` avoids relying on deep recursion.

At the close, students read and test an instructor-supplied undirected edge-list builder and safe `qsort` comparator interface. The builder emits one record per logical undirected edge, does not double-count mirrored adjacency entries, and preserves genuine parallel edges. This is a short Kruskal pre-lab, not another implementation assignment.

### C lab and cybersecurity context

The lab has two linked parts:

1. repair one broken incident-record or standalone linked-adjacency chain containing a leak, dangling pointer, or use-after-free;
2. implement a DSU that clusters synthetic hosts as relationships arrive.

Reject out-of-range identifiers before indexing `parent[]`. Students state that shared DSU membership does not imply trust or authorization.

The capstone continues using the array-of-dynamic-neighbor-arrays representation introduced in Module 9. The linked-adjacency repair is a standalone ownership exercise, so no unexplained capstone representation migration occurs.

### Evidence of learning

- before/after linked-list ownership diagram;
- sanitizer-clean list operations;
- parent-array trace before/after compression;
- tested `dsu.h`/`dsu.c`;
- amortized `O(alpha(n))` interpretation and one DSU limitation.

### Spiral links

**Revisits:** ArrayList versus links, components, implicit trees, ownership.  
**Forward:** Kruskal cycle checks in Module 15.

---

## Module 14 — Tree: BST-to-AVL synthesis

Production materials: [Module 14 teaching package](module_14_bst_avl/README.md)

### Learning objectives

Students will:

- state BST ordering and AVL balance invariants;
- trace and test the instructor-provided BST search/insertion baseline seeded in Modules 2 and 5;
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

**Revisits:** Module 2 BST seed, inorder DFS, height from BFS, Heap-order contrast.  
**Forward:** final comparison of local and global invariants.

---

## Module 15 — Graph: Prim and Kruskal

Production materials: [Module 15 teaching package](module_15_prim_kruskal/README.md)

### Learning objectives

Students will:

- distinguish a shortest-path tree from a minimum spanning tree;
- state the weighted, undirected input contract;
- trace Prim’s frontier growth and Kruskal’s component merging;
- explain the roles of Heap and Union-Find;
- implement one complete MST core loop and complete/test a scaffolded implementation of the other;
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

Students reuse the tested graph parser, Module 11 Heap, and Module 13 DSU. They complete:

- one selected algorithm—key-based Prim or Kruskal—from a bounded skeleton;
- the other algorithm from a more complete scaffold;
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
- one tested complete implementation and one tested scaffolded implementation;
- invariant-based result validation;
- algorithm-selection memo;
- cost-versus-resilience analysis.

### Spiral 5 synthesis and individual check

Given an adversarial insertion stream and a weighted graph, students:

1. trace DSU unions and identify the first cycle-producing edge;
2. draw the skewed BST created by hostile order;
3. perform the required AVL repair;
4. choose Prim or Kruskal for the supplied representation;
5. distinguish MST, shortest-path, connectivity, and resilience objectives.

This individual trace/coding check is submitted before the pair capstone defense. The capstone report absorbs the longer synthesis; the defense occurs in the scheduled final-assessment period rather than inside Module 15’s three contact hours.

---

# Assessment Architecture

## 1. Assessment principles

Assessment mirrors the learning routine. Students are not asked only to reproduce code from memory. Every important assessment collects three kinds of evidence:

1. **Explain and trace:** representation, memory state, invariant, and operation.
2. **Build and test:** bounded C implementation, repair, or integration.
3. **Audit and transfer:** complexity, failure mode, security consequence, and structure choice.

Initial Cognitive Pause responses are evaluated for serious participation and subsequent correction rather than immediate perfection. Module labs permit one feedback-driven revision. Summative tasks use the same Macro/Micro architecture practiced in class, with less scaffolding.

## 2. Recommended grading plan

| Component | Weight | Primary evidence |
|---|---:|---|
| Retrieval practice and corrected Cognitive Pauses | 10% | Short traces, diagrams, invariant questions, annotated corrections |
| Thirteen ordinary module labs | 26% | C code, tests, tool output, memory models |
| Five Linear→Tree→Graph synthesis checks | 15% | Transfer across each three-module spiral |
| Segfault Autopsies and Micro-CTFs | 10% | One embedded debugging artifact per spiral |
| Two cumulative practical assessments | 14% | Modules 6 and 12 implementation, trace, debug, repair, select, and justify |
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

### Practical 1 — After Module 6

Students:

- reconstruct an ArrayList, tree, and graph from memory representations;
- repair one pointer or bounds defect;
- trace Stack, tree DFS, and graph DFS;
- complete or repair a bounded graph-DFS function and its cycle/disconnection tests;
- identify the invariant added at each generalization;
- select a representation for a short scenario.

### Practical 2 — After Module 12

Students:

- trace Queue/tree BFS/graph BFS;
- repair a circular-buffer or visited-state defect;
- trace Heap operations;
- execute one Dijkstra relaxation round;
- complete or repair a bounded Dijkstra core and its stale-entry, unreachable, and negative-input tests;
- state the nonnegative-weight contract;
- compare a linear and Heap-backed Priority Queue.

Both practicals include an expert-model correction opportunity followed by a short transfer question. Corrections recover evidence of learning, not all points automatically.

Each practical replaces that module’s ordinary lab rather than adding another assignment to the same week.

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

The capstone is built incrementally so Module 15 is integration rather than a new project.

| Milestone | Capability added |
|---|---|
| Spiral 1 | Validated records and graph representation |
| Spiral 2 | Stack-backed DFS and reachability |
| Spiral 3 | Queue-backed BFS and unweighted paths |
| Spiral 4 | Heap-backed Dijkstra |
| Module 13 | Reusable DSU; linked-adjacency repair remains a standalone clinic |
| Module 14 | AVL-backed asset/indicator index |
| Module 15 | Prim, Kruskal, cross-validation, and comparative report |

The final toolkit must:

- validate all vertex identifiers and input sizes;
- document ownership for each allocated object;
- traverse the model with DFS and BFS;
- reconstruct unweighted and weighted paths;
- reject negative edge weights for Dijkstra;
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

All submitted implementations use a consistent engineering contract:

- compile with the strongest practical warnings for the course toolchain;
- never ignore an allocation result;
- validate external indexes before array access;
- define empty/error behavior in the API;
- use `size_t` for sizes and indexes where appropriate;
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
| Pointers, `struct`, allocation, ownership | Module 1 syntax sandbox | Entire course |
| Linked-node mental model | Module 1 preview; Module 13 retrieval clinic | Trees, linked adjacency, DSU bridge |
| Tree representation and BST-order preview | Module 2 | DFS, BFS, AVL |
| Graph representation | Module 3 | All graph algorithms |
| Stack | Module 4 | Tree and graph DFS |
| Recursion and explicit call frames | Module 5 | Tree algorithms and cleanup |
| Queue | Module 7 | Tree and graph BFS |
| Height and balance preview | Module 8 | AVL |
| Adjacency list and predecessors | Module 9 | Dijkstra and Prim |
| Priority Queue ADT | Module 10 | Dijkstra and Prim |
| Binary Heap | Module 11 | Dijkstra and Prim |
| Weighted relaxation | Module 12 | Dijkstra; comparison with Prim |
| Union-Find with compression/rank | Module 13 | Kruskal |
| BST operations and AVL rotations | Seeded Modules 2/5/8; mastered Module 14 | Ordered-index capstone |
| Edge-list construction and safe sorting/comparator | Module 13 Kruskal pre-lab | Kruskal |

Scope controls:

- AVL insertion is core; AVL deletion is an extension.
- Module 15 reuses tested graph, Heap, and DSU libraries.
- Prim and Kruskal are both traced and compared; local calendar constraints may allow students to implement one fully and complete the other from a scaffold.
- Hash tables and advanced sorting are outside the required topic list. A boolean/indexed visited array is used when vertex IDs are dense.
- Algorithms operate only on synthetic, authorized datasets.

---

# Suggested 15-Module Calendar

| Module | Primary topic | Spiral checkpoint or major artifact |
|---:|---|---|
| 1 | ArrayList and linked-node preview | Safe growth lab |
| 2 | Binary-tree foundations and BST seed | Representation translation |
| 3 | Graph fundamentals | Spiral 1 representation synthesis |
| 4 | Stack | Nested-input Micro-CTF |
| 5 | Tree DFS | Recursive/iterative comparison |
| 6 | Graph DFS | Spiral 2 depth synthesis; Practical 1 |
| 7 | Queue | Circular-buffer incident analysis |
| 8 | Tree BFS | Width/height comparison |
| 9 | Graph BFS | Spiral 3 breadth synthesis |
| 10 | Priority Queue ADT | Backend-selection experiment |
| 11 | Binary Heap | Invariant-driven implementation |
| 12 | Dijkstra | Spiral 4 priority synthesis; Practical 2 |
| 13 | Linked-list retrieval and Union-Find | Ownership repair and DSU |
| 14 | BST-to-AVL | Adversarial-input experiment |
| 15 | Prim and Kruskal | Spiral 5 synthesis and capstone integration; defense in final period |

If the institution reserves the final instructional week entirely for examinations, start the capstone earlier and place Module 15 across the preceding graph-algorithm meetings. Do not compress the entire MST implementation and capstone assembly into a single final class.

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
