# Week 14 — Prim, Kruskal, and Capstone Integration: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

> **Required scope (14-week path; one folded artifact):** Students trace and compare both MST strategies, implement the complete Kruskal core, and finish and test bounded decision checkpoints in an instructor-supplied Prim scaffold. The algorithm comparison, embedded Spiral 5 individual synthesis, and capstone-integration checkpoint are parts of the same Week 14 artifact, not separate submissions. Full Prim implementation is optional. The capstone report and defense are assessed later in the separate final-assessment period, outside Week 14's 180 contact minutes.

Extension questions below are enrichment only and do not enlarge the required Week 14 artifact.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| `int64_t` | C's signed integer type with exactly 64 bits. |
| Acyclic | Containing no cycle. |
| Adjacency list | Graph storage grouping the edges incident to each vertex. |
| Algorithm | A finite step-by-step procedure. |
| API boundary | The documented point where one component validates and passes data to another. |
| Bridge | An edge whose removal increases the graph's number of components. |
| Comparator | A function deciding which of two records comes first. |
| Component | A largest connected part of a graph. |
| Component coverage | The requirement that a result span every vertex in each input component. |
| Connected | Joined by a path. |
| Crossing edge | An edge whose endpoints lie on opposite sides of a cut. |
| Cross-validation | Checking independent implementations against a shared correctness property, such as minimum total weight. |
| Cut | A separation of all vertices into two groups. |
| Cycle | A nonempty route returning to its start without reusing an edge. |
| Dense internal vertex ID | A validated consecutive identifier used safely inside graph arrays. |
| Density | How many of the possible graph edges are present. |
| Directed graph | A graph whose edges have direction; the standard MST contract here is undirected. |
| Disjoint-Set Union (DSU) | A structure maintaining nonoverlapping groups for Kruskal's cycle test. |
| Edge | A relationship between two vertices. |
| Edge list | Graph storage with one record per logical edge. |
| Folded artifact | One submission combining MST work, individual synthesis, and the integration checkpoint. |
| Forest | A collection of trees. |
| Frontier | Pending Prim work representing possible next connections. |
| Graph | Vertices together with their edges. |
| Heap | A tree-shaped Priority Queue used to remove the smallest pending Prim key. |
| Incident record | One stored view of an edge from one endpoint. |
| Invariant | A rule true for every valid state. |
| Key in Prim | The cheapest known single edge entering an unreached vertex. |
| Kruskal's algorithm | Scan logical edges from smallest weight upward and join different DSU groups. |
| Lazy duplicate | A new improved frontier snapshot inserted without removing the older one. |
| Logical edge | One undirected relationship identified by one edge ID. |
| Matrix | Graph storage with one position for every vertex pair. |
| Minimum spanning forest (MSF) | One minimum spanning tree for each connected component. |
| Minimum spanning tree (MST) | A spanning tree with the smallest possible selected-edge total. |
| Normalized endpoints | An edge record storing the smaller endpoint ID first. |
| Overflow | An arithmetic result outside the numeric type's range. |
| Parallel edges | Distinct edge IDs having the same endpoints. |
| Parent in Prim | The other endpoint of a vertex's currently selected key edge. |
| Path | A sequence of adjoining edges. |
| Prim's algorithm | Grow a tree by repeatedly accepting a cheapest safe crossing edge. |
| Priority Queue | A collection that removes its first-ranked record. |
| Reached set | Vertices already incorporated into Prim's current tree. |
| Representative root | The ID naming one DSU component. |
| Resilience | Ability to continue required service after a failure. |
| Safe edge | An edge that can be added while leaving some minimum result possible. |
| Self-loop | An edge whose two endpoints are the same vertex. |
| Shortest-path tree | Recorded least-cost routes from one source; it need not minimize total selected-edge weight. |
| Signed weight | An edge cost that may be negative, zero, or positive. |
| Single point of failure | One element whose loss alone interrupts required connectivity or service. |
| Spanning tree | A connected, cycle-free edge selection containing every vertex of a connected graph. |
| Sparse external identifier | A nonconsecutive outside label translated and validated before internal indexing. |
| Stale snapshot | Saved Prim work whose key is no longer current. |
| Tree | A connected graph with no cycle. |
| Undirected edge | An edge usable in both directions. |
| Validator | A diagnostic operation checking stated structural and result rules. |
| Vertex | One item represented in a graph. |
| Weight | The numeric cost stored on an edge. |

### Optional-only vocabulary for extension questions

| Term | Working meaning |
|---|---|
| Arbitrary-precision arithmetic | Numeric representation that grows beyond fixed-width integer limits as needed. |
| Redundant link | An additional approved connection retained to reduce single-failure exposure. |
| Second-best spanning tree | A spanning tree with the smallest total strictly above, or otherwise ranked after, an optimum under a stated tie rule. |
| Unbounded graph | A graph not restricted to the course's fixed vertex and edge limits. |

## Anticipated student questions

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

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md#weeks-1314--avl-mst-and-integration)
- [Master curriculum, Module 16](../Data_Structures_Course_2026_Spiral_Curriculum.md#module-16--graph-prim-and-kruskal)
- [Module 16 package](../module_16_prim_kruskal/README.md)
- [Module 16 vocabulary reference](../module_16_prim_kruskal/student/vocabulary.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md#week-14-prim-kruskal-and-capstone-integration-module-16)
