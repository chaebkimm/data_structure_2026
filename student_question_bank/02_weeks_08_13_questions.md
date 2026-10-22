# Consolidated Weeks 8–13 Questions

These questions match the current weekly pages. Optional clusters remain optional.

## Week 8 — BFS from Trees to Graphs

[Weekly vocabulary and scope](week_08_bfs.md)


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
- Why is there no separate Module 8 programming submission in the 13-week course?
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


## Week 9 — Hash Table

[Weekly vocabulary and scope](week_09_hash_table.md)


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

- Which probing, lookup, insertion/update, removal, and scaffold checkpoints belong in the single Week 9 submission?
- What three student-authored test categories are required in the bounded Week 9 artifact?
- Which maximum-capacity, long-churn, deep-validator, and additional allocation-failure work is supplied or optional rather than a second assignment?
- What traces and tool output demonstrate collision, wraparound, tombstone, growth, compaction, and failure preservation?

### Transfer

- In the supplied comparison preview, when is a hash table preferable to an AVL tree for exact lookup?
- In that preview, when do ordered iteration, range queries, or worst-case lookup requirements favor an AVL tree instead?
- How can the hash table bridge sparse external identifiers to dense internal graph IDs?
- How can transactional rehashing prepare you to preserve state when the later Heap backend grows?

### Extension questions

- How would separate chaining change collision storage, ownership, and worst-case traversal?
- What capacity policy could shrink a table without causing resize thrashing?
- How could a keyed production hash reduce predictable collision attacks?
- What proof or test strategy could strengthen confidence in long mixed-operation churn?


## Week 10 — Priority Queue Contract to Binary Heap

[Weekly vocabulary and scope](week_10_priority_queue_heap.md)


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

- Why is Module 11's unsorted-array baseline supplied rather than student-written in Week 10?
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

- What belongs in the single combined Week 10 submission?
- Why is there no separate student implementation or submission for the unsorted baseline in Module 11?
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


## Week 11 — Dijkstra and Practical 2

[Weekly vocabulary and scope](week_11_dijkstra.md)


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

- Why is Practical 2 the sole Week 11 programming artifact?
- What code, canonical trace, regression test, boundary evidence, and comparison belong in the integrated Practical 2 submission?
- Why must the full standalone Module 12 Stage E lab not be added as homework?
- How should the submission distinguish the Priority Queue ADT from its linear and Heap implementations?

### Transfer

- Which Week 8 predecessor-path ideas transfer directly from BFS to Dijkstra?
- Which Week 10 Heap and stable-frontier ideas does Dijkstra reuse?
- How is Dijkstra's objective different from the objective of Prim or Kruskal?
- When would BFS be simpler and sufficient despite the availability of Dijkstra?

### Extension questions

- How would an eager decrease-key frontier change the implementation and complexity argument?
- Which algorithmic family would be needed if negative edges were permitted?
- How could the full parser be tested against signs, whitespace, malformed text, and range boundaries?
- What additional evidence would be needed to run Dijkstra safely on a larger, dynamically sized graph?


## Week 12 — BST-to-AVL Synthesis

[Weekly vocabulary and scope](week_12_avl.md)


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

- Which complete BST baseline operations are supplied rather than rewritten in Week 12?
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

- What code, tests, four rotation traces, measurement table, and validation output belong in the single Week 12 submission?
- Why are edge-height and balance factor formally assessed here rather than in the compressed Week 8 tree-BFS bridge?
- Which three implementation clusters form the required AVL core?
- Why are AVL deletion, optional extension tests, and unsafe autopsy execution outside the Week 12 requirement?

### Transfer

- When would an AVL index be a better capstone choice than the Week 9 hash index?
- How does inorder DFS provide sorted evidence for the BST invariant?
- How do local AVL rotations differ from the global edge-selection decisions used by MST algorithms?
- Which failure-preservation and ownership rules carry over from linked lists and hash tables to AVL insertion?

### Extension questions

- What additional cases and repair steps would AVL deletion require?
- How could parent pointers change rotation code and ownership validation?
- How might a red-black tree trade a weaker balance rule for different update behavior?
- What experiment would compare hash-table and AVL lookup under ordinary and adversarial inputs?


## Week 13 — Union-Find, Kruskal, and Capstone Integration

[Weekly vocabulary and scope](week_13_dsu_mst_capstone.md)


### DSU representation and operations

- Why learn Union-Find immediately before Kruskal?
- How does parent[] encode a forest without node pointers?
- What distinguishes a representative root from another member?
- Why are component sizes positive only at roots?
- What does make-set supply before the first graph edge is processed?
- Why does find locate a valid root before compressing the path?
- Which old parent must be saved during the compression pass?
- Why must union locate both roots before mutating either path?
- How does union by size choose the winning root, including ties?
- What changes after a merge, and what stays unchanged after same-set union?
- Why does compression preserve group membership, root sizes, and component count?
- How are invalid IDs rejected while preserving state and outputs?

### Kruskal and correctness

- Why do equal roots mean that the candidate edge would create a cycle?
- Why is sorting necessary in addition to DSU connectivity checks?
- What does the cut property establish about accepting a lightest safe edge?
- How do accepted edges and DSU components describe the same forest?
- Why does the edge builder retain distinct parallel edges?
- Why are self-loops skipped even if their weights are negative?
- Why does the comparator use relational tests instead of subtracting weights?
- What belongs in the edge-examination and skip ledger?
- Why does a disconnected result have V−c edges?
- Why can equal-weight MSTs use different edges with the same total?
- Why are negative weights accepted here but rejected by Dijkstra?
- Why does the scaffold publish the result only after checked total calculation?

### Tests, complexity, and comparison

- Which test verifies path compression as well as the returned root?
- How do I test same-set unions without confusing them with invalid input?
- How can a disconnected fixture include an isolated vertex?
- How can parallel edges or self-loops expose a wrong cycle decision?
- What evidence covers invalid endpoints, empty input, and large totals?
- What does amortized O(alpha(V)) mean for DSU operations?
- Why is sorting the usual dominant term in Kruskal?
- Why is diagnostic forest validation excluded from ordinary algorithm costs?
- What distinguishes the supplied Prim boundary growth from Kruskal merging?
- Why does neither MST construction guarantee redundant routes?

### Assignment, synthesis, and integration

- Which three functions are the required DSU/Kruskal TODOs?
- Are make-set, sorting, graph loading, checked totals, and Prim supplied?
- Do I submit another list repair, Prim implementation, or full package lab?
- Which DSU trace, edge ledger, tests, and compiler output accompany the two C files?
- How does the brief individual synthesis retrieve hash/AVL selection?
- How is the capstone integration checkpoint folded into the one weekly artifact?
- Which connected and disconnected runs show integration with existing graph IDs?
- How are lab correctness criteria separated from later capstone integration and defense?
- Why does DSU membership not imply trust, authorization, or an available path?
- Why can this DSU not directly handle arbitrary graph-edge deletions?
