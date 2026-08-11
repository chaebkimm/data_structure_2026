# Student Question Bank: Weeks 8-14

> This is the consolidated question-only view. The canonical weekly pages,
> including vocabulary and required-scope notes, are linked from the
> [all-week bank index](../Data_Structures_Course_2026_Student_Question_Bank.md).

## Week 8: BFS from Trees to Graphs (Modules 8-9)

### Meaning and mental model

- What does breadth-first search mean in ordinary language?
- What is a frontier, and why does BFS manage it with a Queue?
- Why does a FIFO Queue visit a tree in nondecreasing depth?
- What changes when the tree-level-order idea is transferred to a graph?
- What does a minimum-hop path minimize, and what does it ignore?

### Representation and invariants

- What information belongs in each supplied tree-BFS work record?
- Which tree properties let level-order traversal omit a discovered array?
- Why does graph BFS need discovered state even when tree BFS does not?
- What do the `distance` and `predecessor` arrays mean for a discovered vertex?
- When must a graph vertex become discovered, and what invariant does that timing preserve?
- Which result fields use the sentinel value 16, and why is 16 unambiguous in this course graph?

### Operations, C API, and ownership

- Which parts of the supplied Module 8 level-order scaffold are students expected to read and run rather than implement?
- Does `tree_level_order` own or modify the caller's tree nodes?
- What must `graph_bfs_matrix` and `graph_bfs_list` preserve when they return an error?
- What must `graph_bfs_reconstruct_path` include in a successful path, including the source-only case?
- Who owns the graph, Queue storage, BFS result, and reconstructed path at each API boundary?

### Tracing

- Given a binary tree, what are the Queue contents before and after each left-first level-order step?
- How can a tree trace demonstrate that depths never decrease in dequeue order?
- On a graph with two routes to the same vertex, which route fixes its predecessor?
- How do Queue, discovery, distance, predecessor, and visit order change during one complete graph-BFS trace?
- What happens in the trace when an outgoing edge points to an already discovered vertex?
- How does ascending neighbor-ID order determine one reproducible minimum-hop path when several exist?

### Testing and debugging

- Which test shows that enqueue-time marking prevents duplicate pending work on converging routes?
- Which tests distinguish an empty graph, a singleton source path, a cycle, and a disconnected destination?
- How would a matrix/list equivalence test reveal a representation-specific BFS defect?
- What symptom would appear if a vertex were marked discovered only when dequeued?
- How can a test verify that an unreachable or malformed path request leaves the caller's prior output unchanged?

### Complexity

- Why is the supplied tree-level-order trace `O(n)` time and `O(w)` auxiliary space?
- Why does matrix-based graph BFS take `O(V^2)` time even on a sparse graph?
- Why does adjacency-list graph BFS take `O(V + E)` time when each vertex and edge is processed in bounded ways?
- How can the Queue's peak size differ between a narrow tree and a wide graph without changing BFS correctness?

### Security and interpretation

- Why does graph reachability not prove that access is authorized?
- Why does a small hop count not establish likelihood, exploitability, trust, or real-world risk?
- How could invalid vertex IDs or unchecked Queue limits become reliability or security problems in C?

### Assignment and evidence

- What belongs in the single combined Week 8 submission?
- Why is there no separate Module 8 programming submission in the 14-week course?
- Which evidence demonstrates correct distance, predecessor, path reconstruction, cycles, unreachable vertices, and representation equivalence?
- How should the brief tree trace and the main graph-BFS code be connected in the synthesis explanation?

### Transfer

- How does Queue-controlled tree level order prepare you to reason about graph BFS?
- When would DFS answer a reachability question without providing the minimum-hop certificate that BFS provides?
- How will graph-BFS predecessor paths prepare you for Dijkstra's weighted paths?
- Why is a dense Boolean discovered array preferable to a hash table when vertex IDs already occupy `0` through `V - 1`?

### Extension questions

- How would you implement `tree_level_order` from the supplied scaffold while preserving output on every failure?
- How would a shallowest-value tree search resolve equal-depth ties?
- How could a full BFS forest cover all disconnected graph components after the source component finishes?
- What additional proof obligations arise if outgoing neighbors are not stored in deterministic order?

## Week 9: Priority Queue Contract to Binary Heap Backend (Modules 10-11)

### Meaning and mental model

- How is a Priority Queue different from the FIFO Queue used for BFS?
- What does "minimum" mean under the course's alert-priority convention?
- What makes the Priority Queue stable when two priorities are equal?
- Why can two storage backends implement the same Priority Queue ADT?
- What does a binary Heap promise that a globally sorted array does not?

### Representation and invariants

- Which public record fields and service rules must remain identical across the supplied unsorted backend and the Heap backend?
- What makes the array representation a complete binary tree?
- How are a nonroot node's parent and its possible child indexes calculated?
- What exact parent-child relationship defines the stable minimum-Heap invariant?
- Why can a valid minimum Heap contain an array that is not globally sorted?
- Which Queue fields describe owned storage, logical size, capacity, arrival sequence, and diagnostic comparison work?

### Operations, C API, and ownership

- Why is the Module 10 unsorted-array implementation supplied rather than student-written in Week 9?
- What happens to a complete Heap and caller output if growth allocation fails during insertion?
- Why can Heap `peek_min` return the root without performing record comparisons?
- What steps must extraction perform before and during sift-down?
- Why must output storage for a returned record not point inside the Queue's allocation?
- What does `alert_priority_queue_destroy` own, release, and reset?

### Tracing

- How does the supplied unsorted baseline insert, inspect the minimum, and remove the minimum?
- Given an insertion sequence, where is each new Heap record appended and which comparisons cause it to sift upward?
- Given a root extraction, which record moves to index 0 and how is the smaller child chosen during sift-down?
- How should sift-down behave when a node has a left child but no right child?
- How do equal priorities and arrival sequences determine swaps during a Heap trace?
- Which fields may change during extraction even though the public service behavior remains unchanged?

### Testing and debugging

- Which focused tests isolate sift-up, sift-down, stable ties, and the one-child case?
- How can `alert_priority_queue_is_min_heap` expose a local order violation after a mutation?
- Why must checker comparisons be measured separately from normal-operation comparisons?
- How can randomized differential testing compare the Heap against the supplied unsorted reference without assuming identical internal arrays?
- What bug would occur if sift-down compared only priorities and ignored arrival sequence?

### Complexity

- What are the insertion, minimum-inspection, and minimum-removal costs of the supplied unsorted-array baseline?
- Why are Heap insertion and extraction `O(log n)` while Heap minimum inspection is `O(1)`?
- Why is a Heap's height logarithmic in its number of records?
- Which workload would make the unsorted baseline competitive, and which workload would favor the Heap?

### Security and interpretation

- How can an incorrect priority calibration cause unfairness or starvation even when the data structure is correct?
- Why is stable tie handling a policy guarantee rather than a security authorization decision?
- How could unchecked index arithmetic or a missing-child read corrupt Heap behavior or memory?

### Assignment and evidence

- What belongs in the single combined Week 9 submission?
- Why is there no separate student implementation or submission for Module 10 in the 14-week path?
- Which traces and tests demonstrate the complete-tree indexes, stable comparator, sift behavior, and Heap invariant?
- What comparison evidence fairly distinguishes the supplied baseline's costs from the Heap backend's costs?

### Transfer

- Why can Dijkstra use the Priority Queue contract without depending on whether its backend is an unsorted array or Heap?
- How does Heap order differ from the strict ordering rule of a BST or AVL tree?
- How do comparison counts provide evidence about backend choice without proving wall-clock performance on every machine?
- What failure-preservation ideas transfer from dynamic arrays to both Priority Queue backends?

### Extension questions

- How would you implement the unsorted-array Priority Queue while preserving the same public contract?
- How could bottom-up heap construction differ from repeated insertion?
- What interface changes would a decrease-key Heap require?
- How would a maximum-oriented Heap change the comparator and invariant while retaining the same array geometry?

## Week 10: Dijkstra and Practical 2 (Module 12)

### Meaning and mental model

- Why can BFS return the wrong route when edge costs are unequal?
- What does a tentative distance mean before a vertex is finalized?
- What does relaxation ask about one outgoing arc?
- Why does Dijkstra remove the smallest tentative snapshot next?
- What is a stale frontier entry in the lazy-duplicate strategy?

### Representation and invariants

- What do `distance`, `predecessor`, `finalized`, and `finalized_order` represent?
- Why is `SIZE_MAX` reserved as `DIJKSTRA_INF` rather than permitted as a reachable cost?
- What relationship must hold between a nonstale popped snapshot and the current distance array?
- Why does strict relaxation leave an existing predecessor unchanged on an equal-cost route?
- Why is the dedicated frontier limit `arc_count + 1` rather than the Module 11 teaching cap of 64?

### Operations, C API, and ownership

- Which parser, weighted-graph, Heap-frontier, setup, cleanup, and validation parts are supplied in Practical 2?
- Which bounded Dijkstra run-loop and path-reconstruction decisions must students complete?
- What must `dijkstra_shortest_paths` preserve if validation, allocation, capacity, or arithmetic fails?
- What must `dijkstra_reconstruct_path` return for a reachable source-only path and preserve for an unreachable destination?
- Which object owns the graph arcs, frontier entries, result arrays, and reconstructed path at each stage?

### Tracing

- How do distances, predecessors, frontier entries, and finalized state change during the canonical A-through-F trace?
- Which canonical frontier pops are stale, and why must their outgoing arcs be skipped?
- How does a zero-cost arc participate in strict relaxation?
- How is the path `A, C, D, E` reconstructed from predecessor state?
- What state shows that F is unreachable from A?
- How would a nonstrict relaxation change the predecessor trace when two equal-cost routes exist?

### Testing and debugging

- What single focused regression test should isolate a core error in the student's bounded implementation?
- Which supplied tests establish negative-input rejection, stale-pop skipping, unreachable handling, and cost-range protection?
- What failure would appear if a stale snapshot were finalized or expanded?
- How can the reconstructed path cost be checked independently of the algorithm's reported distance?
- How can a same-graph comparison distinguish BFS, linear-Priority-Queue Dijkstra, and Heap-Dijkstra results?

### Complexity

- Why does lazy-duplicate Dijkstra use `O(V + E log(E + 1))` time with this frontier strategy?
- Why can the lazy frontier require `O(E)` entries?
- Under what simple-graph assumption can the bound be written as `O(V + E log V)`?
- Why must the analysis describe the implemented lazy strategy rather than assume decrease-key?

### Security and interpretation

- Why must a negative textual weight be rejected before conversion to `size_t`?
- How does the subtraction guard prevent overflow or collision with the reserved infinity value?
- Why does a least-cost path not prove authorization, trust, availability, or low security risk?

### Assignment and evidence

- Why is Practical 2 the sole Week 10 programming artifact?
- What code, canonical trace, regression test, boundary evidence, and comparison belong in the integrated Practical 2 submission?
- Why must the full standalone Module 12 Stage E lab not be added as homework?
- How should the submission distinguish the Priority Queue ADT from its linear and Heap implementations?

### Transfer

- Which Week 8 predecessor-path ideas transfer directly from BFS to Dijkstra?
- Which Week 9 Heap and stable-frontier ideas does Dijkstra reuse?
- How is Dijkstra's objective different from the objective of Prim or Kruskal?
- When would BFS be simpler and sufficient despite the availability of Dijkstra?

### Extension questions

- How would an eager decrease-key frontier change the implementation and complexity argument?
- Which algorithmic family would be needed if negative edges were permitted?
- How could the full parser be tested against signs, whitespace, malformed text, and range boundaries?
- What additional evidence would be needed to run Dijkstra safely on a larger, dynamically sized graph?

## Week 11: Hash Table (Module 13)

### Meaning and mental model

- What service does a key-to-value map provide independently of its storage representation?
- Why is direct array indexing wasteful when legal external keys are sparse and very large?
- What does a hash function contribute to lookup, and what does it not guarantee?
- What is a collision, and why can a correct hash table never assume collisions will not occur?
- How does linear probing search for another usable slot after a collision?

### Representation and invariants

- Why must each slot distinguish `EMPTY`, `OCCUPIED`, and `DELETED` states?
- How can key 0 remain legal when inactive slots contain zeroed key and value fields?
- What relationships must hold among `size`, `tombstones`, and `capacity`?
- Why must every occupied key be unique and reachable from its home slot without crossing an `EMPTY` slot?
- Which capacities are legal, and what does the canonical destroyed state look like?
- Why must every probe loop inspect at most `capacity` slots?

### Operations, C API, and ownership

- What is the difference between inserting a new key and updating an existing key in `hash_table_put`?
- Why must insertion remember the first tombstone but continue probing before committing there?
- How does `hash_table_remove` preserve the lookup reachability of later colliding keys?
- What table state and result output must be preserved if allocation or maintenance fails?
- Why is shallow copying a live `HashTable` prohibited, and what storage does `hash_table_destroy` release?

### Tracing

- At capacity 8, how do keys 10, 18, and 26 occupy their collision cluster?
- After removing key 18, which indexes must lookup for key 26 inspect, and which state appears at each?
- Which indexes must a missing-key lookup for 34 inspect before absence is established?
- Why must an update of key 26 continue past the tombstone instead of inserting a duplicate there?
- How can a new key 34 reuse the tombstone only after the search proves that 34 is not already present?
- How do keys with home slot 7 demonstrate wraparound from the last slot to index 0?

### Testing and debugging

- What exact-probe test covers both a collision cluster and wraparound?
- What test sequence proves tombstone-safe update, tombstone reuse, and duplicate prevention?
- How can a test force growth or same-capacity compaction and verify the selected maintenance action?
- What evidence proves that a forced maintenance-allocation failure preserves the old pointer, records, counts, and caller output?
- How would the full validator detect an unreachable occupied key, duplicate key, invalid state, or inconsistent count?

### Complexity

- Under which distribution and load assumptions do `get`, `put`, and `remove` have expected `O(1)` probe work?
- Why can one lookup require `O(m)` probes in a table of capacity `m`?
- What work and temporary space does a transactional rebuild require?
- Why does expected amortized `O(1)` growth not automatically describe arbitrary deletion/insertion churn with repeated compaction?

### Security and interpretation

- How can attacker-chosen colliding keys cause algorithmic-complexity denial of service?
- Why does increasing capacity alone not defeat deliberately chosen collisions under the teaching hash?
- Why is `key % capacity` neither a cryptographic hash nor an authentication mechanism?
- What validation must occur before an external label mapped by the table becomes a dense graph ID used for indexing?

### Assignment and evidence

- Which probing, lookup, insertion/update, removal, and scaffold checkpoints belong in the single Week 11 submission?
- What three student-authored test categories are required in the bounded Week 11 artifact?
- Which maximum-capacity, long-churn, deep-validator, and additional allocation-failure work is supplied or optional rather than a second assignment?
- What traces and tool output demonstrate collision, wraparound, tombstone, growth, compaction, and failure preservation?

### Transfer

- When is a hash table preferable to an AVL tree for exact lookup?
- When do ordered iteration, range queries, or worst-case lookup requirements favor an AVL tree instead?
- How can the hash table bridge sparse external identifiers to dense internal graph IDs?
- How do transactional rehashing and ArrayList growth share a commit-after-success principle?

### Extension questions

- How would separate chaining change collision storage, ownership, and worst-case traversal?
- What capacity policy could shrink a table without causing resize thrashing?
- How could a keyed production hash reduce predictable collision attacks?
- What proof or test strategy could strengthen confidence in long mixed-operation churn?

## Week 12: Linked-List Ownership Clinic and Union-Find (Module 14)

### Meaning and mental model

- How does a singly linked list differ physically from an ArrayList?
- What does ownership mean for separately allocated linked-list nodes?
- What problem does Disjoint-Set Union answer as relationships arrive?
- How does a `parent[]` array represent a forest without allocating tree nodes?
- What does a representative root mean, and what does it not reveal about paths in the original graph?

### Representation and invariants

- What shape and count conditions define a valid bounded singly linked list?
- Why must the last reachable list node point to `NULL`, with no cycles or shared nodes?
- Which exact fields form the initialized empty state and the canonical destroyed state?
- What parent and component-size rules must hold for every active DSU element?
- Why are component sizes positive only at roots and zero at nonroots?
- How do root count, component count, and the sum of root sizes cross-check one another?

### Operations, C API, and ownership

- Which one linked-list operation must students repair in the Week 12 core?
- Why must `linked_list_remove_first` save the still-needed next link before freeing the matching node?
- What does removing a missing value return, and which topology and output promises still apply?
- How does iterative two-pass `dsu_find` locate a root and then compress the visited path?
- How does `dsu_union` choose the winning root by component size and break equal-size ties?
- Why does `Dsu` require no destructor while `LinkedList` does?

### Tracing

- For `17 -> 23 -> 31 -> NULL`, which pointers and counts change when the first 23 is removed?
- Which nodes remain owned and reachable immediately before and after the middle node is freed?
- How do `parent[]`, `component_size[]`, and component count change across unions `A-B, C-D, A-C, E-F, G-H, E-G, A-E`?
- What two passes occur when finding H along `H -> G -> E -> A`?
- Which parent entries change after compression, and which membership and size facts remain unchanged?
- Why does processing D-H after those unions report a cycle-producing relationship without performing another merge?

### Testing and debugging

- Which test proves that middle-node deletion preserves the remaining chain and releases exactly one node?
- How can before/after ownership diagrams expose a lost link, leak, double free, or use-after-free?
- Which DSU tests cover invalid IDs, same-set union, equal-size ties, path compression, and component counts?
- How can `linked_list_is_valid` and `dsu_is_valid` support debugging without being hidden inside ordinary operation costs?
- What observation from the supplied edge-builder and comparator demo verifies canonical endpoints and deterministic relational ordering?

### Complexity

- Why is first-match linked-list search and removal `O(n)` even though the pointer repair itself is constant work?
- Why are DSU operations described with amortized `O(alpha(n))` cost rather than worst-case constant time per isolated call?
- What space does the linked list own, and what fixed arrays does the bounded DSU use?
- Why are full validators excluded from ordinary linked-list and DSU complexity measurements?

### Security and interpretation

- How can reading `node->next` after `free(node)` create a use-after-free vulnerability?
- Why must every external DSU ID be checked before indexing either array?
- Why does shared DSU membership not establish trust, authorization, a route, a shortest path, or resilience?
- Why can standard DSU neither remove an old relationship nor reconstruct the relationship path?

### Assignment and evidence

- What belongs in the single Week 12 submission?
- Which list operations are supplied or demonstrated rather than student implementation requirements?
- Why are the edge-list builder, comparator, remaining list operations, and unsafe autopsy not separate Week 12 evidence packets?
- Which diagrams, parent-array traces, tests, and supplied boundary-suite output demonstrate the required ownership repair and DSU core?

### Transfer

- How will DSU decide whether a Kruskal candidate edge would create a cycle?
- How does the supplied edge-list builder turn paired incident records into one logical-edge stream for sorting?
- Why must an `int64_t` weight comparator compare relationally instead of subtracting operands?
- How do linked-list ownership rules transfer to linked adjacency structures without requiring a second repair this week?

### Extension questions

- How would you safely implement `push_front` with a forced allocation failure?
- How would you destroy an entire list without reading a node after releasing it?
- How would union by rank differ from the required union-by-component-size representation?
- What additional data structure would be needed to support dynamic connectivity after relationship deletions?

## Week 13: BST-to-AVL Synthesis (Module 15)

### Meaning and mental model

- What global ordering rule defines a strict binary search tree?
- Why can the same set of keys produce very different BST shapes?
- What does edge-height count, and why are `height(NULL) = -1` and `height(leaf) = 0` consistent?
- What does a node's left-minus-right balance factor reveal?
- How does an AVL tree repair local shape without changing sorted key order?

### Representation and invariants

- Which links, key, and cached-height fields belong to each AVL node?
- What ordering relationship must hold across every node's entire left and right subtrees?
- What exact relationship must hold between a node's cached height and its children's heights?
- Which balance-factor values are valid in an AVL tree?
- Why must the tree's `size` equal the number of uniquely owned reachable nodes?
- How does a Heap's parent-child priority invariant differ from an AVL tree's global search-order invariant?

### Operations, C API, and ownership

- Which complete BST baseline operations are supplied rather than rewritten in Week 13?
- What link changes must a left rotation make while preserving the middle subtree?
- In what bottom-up order must cached heights be refreshed after a rotation?
- How must recursive `avl_insert` handle a duplicate, full tree, or allocation failure?
- What storage does the `Tree` own, and what must destruction restore?

### Tracing

- Why does insertion order `30, 20, 10` require an LL repair, and which rotation resolves it?
- Why does `10, 20, 30` require an RR repair?
- Which two rotations resolve `30, 10, 20`, and why is it an LR case?
- Which two rotations resolve `10, 30, 20`, and why is it an RL case?
- How do inorder sequence, subtree ownership, and final stored heights compare before and after each repair?
- Why do ascending and descending 15-key streams produce height 14 in a plain BST but height 3 in the required AVL experiment?

### Testing and debugging

- Which focused test should isolate each of LL, RR, LR, and RL rotation behavior?
- How can a test verify duplicate rejection without relying only on the returned status?
- What evidence proves allocation failure leaves root, links, size, keys, and ownership unchanged?
- How can `tree_validate_avl` distinguish an ordering defect, stale height, excessive balance factor, size mismatch, or shared node?
- What sanitizer or allocation-count evidence can reveal a lost middle subtree after a faulty rotation?

### Complexity

- Why do BST and AVL search both take `O(h)` time for tree height `h`?
- How can an unbalanced BST make search and insertion `O(n)`?
- Why does the AVL balance invariant keep search and insertion at `O(log n)`?
- Why is a single rotation `O(1)` while full traversal, measurement, and destruction remain `O(n)`?

### Security and interpretation

- How can attacker-controlled insertion order create algorithmic-complexity denial of service in a plain BST?
- Why is degraded operation cost not the same as memory corruption?
- Why does AVL balancing not eliminate allocation failure, bounds, ownership, or input-validation risks?
- Why is using all available memory a different failure category from performing too many comparisons?

### Assignment and evidence

- What code, tests, four rotation traces, measurement table, and validation output belong in the single Week 13 submission?
- Why are edge-height and balance factor formally assessed here rather than in the compressed Week 8 tree-BFS bridge?
- Which three implementation clusters form the required AVL core?
- Why are AVL deletion, optional extension tests, and unsafe autopsy execution outside the Week 13 requirement?

### Transfer

- When would an AVL index be a better capstone choice than the Week 11 hash index?
- How does inorder DFS provide sorted evidence for the BST invariant?
- How do local AVL rotations differ from the global edge-selection decisions used by MST algorithms?
- Which failure-preservation and ownership rules carry over from linked lists and hash tables to AVL insertion?

### Extension questions

- What additional cases and repair steps would AVL deletion require?
- How could parent pointers change rotation code and ownership validation?
- How might a red-black tree trade a weaker balance rule for different update behavior?
- What experiment would compare hash-table and AVL lookup under ordinary and adversarial inputs?

## Week 14: Prim, Kruskal, and Capstone Integration (Module 16)

### Meaning and mental model

- What problem does a minimum spanning tree solve on a connected weighted undirected graph?
- What does a minimum spanning forest represent when the graph is disconnected?
- How is the objective of an MST different from a source-to-destination shortest path?
- What greedy decision does Prim make at each step?
- What greedy decision does Kruskal make at each step?

### Representation and invariants

- Why must the MST core receive a validated undirected representation rather than silently reinterpret a directed graph?
- How are one logical edge and its two incident records related?
- Why do parallel edges require distinct logical edge IDs even when their endpoints match?
- Why is a self-loop never selected, even though its two incident records are valid input?
- What edge-count relationship must a forest with `V` vertices and `c` components satisfy?
- Which membership, acyclicity, component-coverage, total-weight, and minimum-cost conditions must a valid result satisfy?

### Operations, C API, and ownership

- Which complete algorithm core must students implement in Week 14?
- Which Prim decisions are bounded checkpoints inside an instructor-supplied scaffold rather than a second full implementation?
- How does Kruskal use the supplied relational edge ordering and DSU API?
- How does lazy Prim use its minimum-Heap frontier when a vertex's best crossing edge improves?
- What graph and result outputs must remain unchanged if parsing, validation, allocation, frontier, or total-range checks fail?

### Tracing

- How does Prim starting at A select edge IDs `0, 2, 4, 5` on the canonical fixture?
- How does Kruskal select edge IDs `2, 4, 5, 0` on the same fixture?
- Why can the two selection orders differ while both totals equal 10?
- What DSU state change follows each accepted Kruskal edge, and why is each rejected cycle edge skipped?
- What reached-set, best-key, predecessor-edge, and frontier state changes occur at each bounded Prim checkpoint?
- How should each algorithm process negative edges, zero-weight edges, equal-weight alternatives, parallel edges, and self-loops?

### Testing and debugging

- Which tests cover a singleton graph, connected graph, disconnected graph, equal-weight alternatives, parallel edges, and self-loops?
- How can structural validation detect a cycle, missing component coverage, wrong edge count, or non-input edge?
- Why should Prim and Kruskal be cross-checked by total weight rather than exact edge sequence?
- What evidence proves the final signed total is checked independently of selected-edge order and fits `int64_t`?
- What defect would result if Kruskal checked whether endpoint IDs differ instead of asking DSU whether their components differ?

### Complexity

- Why does Kruskal require `O(E log E)` sorting plus near-linear amortized DSU work?
- Why does lazy-duplicate Prim use up to `O(E)` Heap entries and `O(V + E log(E + 1))` time?
- How does the graph representation influence whether Prim or Kruskal is the more natural choice?
- Why is the explicit minimum-result validator's diagnostic work excluded from each algorithm's normal complexity?

### Security and interpretation

- Why does a minimum-cost selected edge not prove that a real connection is trusted, available, correctly priced, or secure?
- Why is every edge of a spanning tree a single point of failure?
- What resilience evidence would be needed beyond a minimum-cost tree?
- Why are negative weights valid for MST even though they violate Dijkstra's input contract?

### Assignment and evidence

- What belongs in the single folded Week 14 MST, synthesis, and capstone-integration artifact?
- Which evidence demonstrates the complete Kruskal core and the bounded Prim checkpoints without requiring two full algorithms?
- How should the individual comparison distinguish shortest-path, connectivity, exact lookup, MST, and resilience objectives?
- Why are the full Prim implementation, second MST lab, separate synthesis check, and separate capstone checkpoint not required work?
- Which part is graded as the Week 14 lab evidence, and which cumulative integration evidence belongs to the capstone grade without double-scoring the same criterion?

### Transfer

- How does Week 12 DSU make Kruskal's cycle test efficient?
- How do Week 9 Heap behavior and Week 10 lazy frontier reasoning transfer to Prim?
- Why might an edge-list representation favor Kruskal while adjacency access favors Prim?
- How do AVL local balance, Dijkstra path relaxation, and MST global edge selection enforce different invariants?

### Capstone integration

- Where does the Week 11 hash table translate sparse external asset identifiers into validated dense internal vertex IDs?
- Which API boundary guarantees that Prim and Kruskal never hash or trust external names inside their core loops?
- How do graph ownership, edge-list construction, Heap frontier storage, DSU arrays, selected-edge results, and cleanup responsibilities connect?
- Which invariant checker should run at each boundary before one module's output becomes another module's input?
- How should the toolkit cross-check Prim and Kruskal totals when both are enabled while allowing different valid edge sets?
- What reproducible evidence demonstrates DFS reachability, BFS unweighted paths, Dijkstra weighted paths, index selection, DSU connectivity, and MST output in one coherent tool?
- Which design decisions and live modification questions should each student be prepared to defend in the separate final-assessment period?

### Extension questions

- How would you complete the full Prim implementation beyond the supplied checkpoints?
- How could a second-best spanning tree or added redundant links support a resilience analysis?
- How would MST behavior or meaning change for a directed graph?
- What additional tests and numeric strategy would be required if vertex and edge limits were removed?
