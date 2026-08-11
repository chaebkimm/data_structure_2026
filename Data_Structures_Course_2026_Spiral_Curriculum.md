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
| 1 | 1. ArrayList and linked-node preview | 2. Binary-tree foundations and BST seed | 3. Graph models and representations | Representing relationships in memory |
| 2 | 4. Stack | 5. Tree DFS | 6. Graph DFS | LIFO-controlled exploration |
| 3 | 7. Queue | 8. Tree BFS | 9. Graph BFS | FIFO-controlled exploration |
| 4 | 10. Priority Queue ADT | 11. Binary Heap | 12. Dijkstra | Priority-controlled exploration |
| 5 | 14. Linked-list retrieval and Union-Find | 15. BST-to-AVL synthesis | 16. Prim and Kruskal | Maintaining global invariants while optimizing |

This map contains deliberate previews and returns:

- The table maps concepts and packages, not one package to one lecture week. In the required 14-week path, Modules 8 and 9 form one breadth-first week, and Modules 10 and 11 form one priority/Heap week.
- Module 13 is an associative-index bridge between Spirals 4 and 5. It returns to array growth, adds collision resolution and deletion markers, and maps sparse external identifiers to the dense internal IDs used by graph algorithms.
- Linked nodes are previewed in Module 1, used in early tree work, and retrieved through bounded implementation and repair in Module 14.
- BST ordering is seeded in Module 2, used during tree traversals, and formally strengthened into AVL balance in Module 15.
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
**Forward:** fixed node arenas in Module 2, graph matrices in Module 3, Stack backing storage in Module 4, Hash Table storage in Module 13, and linked-list implementation/repair in Module 14.

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
**Forward:** graph generalization in Module 3, DFS in Module 5, BFS in Module 8, and BST/AVL mastery in Module 15.

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

Module 16 deliberately broadens the input contract to an edge-list representation that may contain parallel edges and self-loops; its algorithms handle or ignore those cases explicitly.

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

Because C has no automatic generic container, later modules receive separately typed `const TreeNode *` and vertex-ID Stack scaffolds with the same contract. Pointer-weak students are not required to design a `void *` generic Stack. A linked-node backend is an extension and an early retrieval opportunity for Module 14.

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

**14-week role:** required Week 5 tree-DFS unit. Recursive traversal, BST-search tracing, and postorder cleanup are core. Explicit-stack tree traversal remains available in the package as an extension, not a second required implementation.

### Learning objectives

Students will:

- identify recursive base cases and saved state;
- trace preorder, inorder, and postorder;
- implement recursive preorder, inorder, and postorder traversal;
- trace an explicit-stack preorder traversal and explain its correspondence to call frames;
- trace and complete scaffolded BST search using the Module 2 ordering seed;
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

The instructor supplies the heap-building fixture and constructor so students do not confuse Module 2’s non-owning arena nodes with individually allocated nodes. Real filesystem traversal is not required. Students document that aliases or symbolic links would require graph-style visited tracking.

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

Using the Module 3 graph, implement iterative DFS, report all vertices reachable from a selected source, and count connected components only for an undirected graph. The implementation uses an instructor-provided vertex-ID Stack with the Module 4 contract. Students trace the equivalent recursive control flow; implementing that second form is an extension. Test a cycle, an isolated vertex, a disconnected graph, and a single vertex. A separate faulty-input test verifies that the simple-graph API rejects a self-loop.

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

**Revisits:** Module 1 contiguous storage and growth, modular indexing, failure preservation, and Module 12's dense internal vertex IDs.  
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

Meeting A returns to the linked-node preview from Module 1. Students trace the supplied insertion, deletion, traversal, and destruction operations, then repair one selected list or linked-adjacency ownership defect. They do not complete three operations plus a second repair, and they are not required to design a complete list library from scratch.

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

**Revisits:** Module 2 BST seed, inorder DFS, tree-height reasoning, Heap-order contrast, and Module 13's sparse exact-match index.  
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
| Week 3 / Module 3 | Validated records, graph representation, and capstone skeleton |
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

All submitted implementations use a consistent engineering contract:

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
| Pointers, `struct`, allocation, ownership | Module 1 syntax sandbox | Entire course |
| Linked-node mental model | Module 1 preview; Module 14 retrieval clinic | Trees, linked adjacency, DSU bridge |
| Tree representation and BST-order preview | Module 2 | DFS, BFS, AVL |
| Graph representation | Module 3 | All graph algorithms |
| Stack | Module 4 | Tree and graph DFS |
| Recursion and explicit call frames | Module 5 recursive core; explicit-stack tree traversal as extension | Tree algorithms and cleanup |
| Queue | Module 7 | Tree and graph BFS |
| Tree level-order transfer | Module 8 bridge in combined Week 8 | Graph BFS |
| Height and balance | Module 15 | AVL validation and rotation |
| Adjacency list and predecessors | Module 9 main lab in combined Week 8 | Dijkstra and Prim |
| Priority Queue ADT and linear reference | Module 10 baseline in combined Week 9 | Heap comparison, Dijkstra, and Prim |
| Binary Heap | Module 11 main lab in combined Week 9 | Dijkstra and Prim |
| Weighted relaxation | Module 12 | Dijkstra; comparison with Prim |
| Hash Table, linear probing, and tombstones | Module 13 | Sparse external-label index; comparison with AVL |
| Union-Find with compression/rank | Module 14 | Kruskal |
| BST operations and AVL rotations | BST operations seeded in Modules 2/5; height, balance, and rotations mastered in Module 15 | Ordered-index capstone; comparison with hashing |
| Edge-list construction and safe sorting/comparator | Module 14 Kruskal pre-lab | Kruskal |

Scope controls:

- Every teaching week has a hard 180-minute contact budget. A complete package may contain extension, make-up, or longer-calendar materials beyond that budget.
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
| 1 | ArrayList and linked-node preview | Module 1; safe growth lab |
| 2 | Binary-tree foundations and BST seed | Module 2; representation translation |
| 3 | Graph fundamentals | Module 3; Spiral 1 synthesis and capstone skeleton |
| 4 | Stack | Module 4; nested-input Micro-CTF |
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
