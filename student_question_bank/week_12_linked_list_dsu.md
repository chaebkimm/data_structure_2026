# Week 12 — Linked-List Ownership Clinic and Union-Find: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

> **Required scope (14-week path; one submission):** Students repair and verify one ownership-sensitive list operation: first-match deletion of the middle node in the canonical list. They implement and test DSU make-set, iterative two-pass find with path compression, and union by component size. Other list operations are supplied for tracing, while the edge-list builder and relational comparator are instructor demonstration material. Remaining list implementations, linked backends, and the unsafe autopsy are optional.

Extension questions below are enrichment only and do not enlarge the required Week 12 artifact.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| `*` in a declaration | Marks a C pointer type. |
| `->` | Accesses a structure field through a pointer. |
| `alpha(n)` | An extraordinarily slow-growing function used in the optimized DSU amortized bound. |
| `int64_t` | C's signed integer type with exactly 64 bits. |
| `next` | The list-node field holding the following node's address. |
| `NULL` | C's marker meaning that a pointer refers to no object. |
| Allocation | Storage reserved while a program runs. |
| Amortized analysis | Analysis that averages total work across an operation sequence. |
| Array | A numbered row of same-typed values. |
| Authorization | Permission to perform an action; DSU connectivity does not establish it. |
| Component count | The number of distinct DSU representative roots. |
| Component size | The number of active elements in one DSU set, stored only at its root here. |
| Connected component | Items joined through the processed undirected relationships. |
| Connected query | A test of whether two IDs have the same representative root. |
| Cycle | A route that returns to an earlier item. |
| Cycle-producing relationship | A new undirected relationship whose endpoints are already in one DSU set. |
| Dangling pointer | An address whose intended object is no longer alive. |
| Dense IDs | Consecutive identifiers beginning at zero. |
| Destroy | Release owned storage and restore the canonical empty state. |
| Disjoint | Sharing no item. |
| Disjoint-Set Union (DSU) / Union-Find | A structure that maintains nonoverlapping groups as unions occur. |
| Edge | A graph connection between vertices. |
| Edge list | Storage containing one record per logical graph edge. |
| Failure preservation | A failed operation leaves the earlier valid state and promised outputs unchanged. |
| Find | Follow parent entries to return a set's representative root. |
| First-match deletion | Remove only the first reachable node whose value matches the target. |
| Forest | Several tree-shaped parent groups encoded by the DSU arrays. |
| Head | The pointer to the first list node. |
| Incident record | One stored view of an edge from one endpoint. |
| Invariant | A rule true in every valid observable state. |
| Iterative | Performed with loops rather than recursive self-calls. |
| Kruskal's algorithm | A later MST procedure that scans edges by increasing weight and rejects cycle-producing edges. |
| Logical edge | One undirected relationship identified independently of its two incident records. |
| Make-set | Initialize one element as a one-item DSU group. |
| Memory address | A value identifying a storage location. |
| Memory leak | Owned storage that becomes unreachable without being released. |
| Node | One separately allocated object containing data and a link. |
| Ownership | Responsibility for releasing allocated storage. |
| Parallel edges | Distinct logical edges with the same endpoints. |
| Parent | The next dense ID followed toward a DSU representative. |
| Path compression | Redirect IDs visited by find directly to their representative root. |
| Pointer | A C value that stores an address. |
| Push-front | Insert a new node before the current first node. |
| `qsort` | C's library function for arranging array records according to a comparator. |
| Reciprocal records | Two stored directions representing one undirected edge. |
| Relational comparator | An ordering function using less-than and greater-than tests instead of subtraction. |
| Representative root | A DSU ID whose parent is itself and which names one group. |
| Resilience | Ability to continue required operation after a failure; connectivity alone does not prove it. |
| Self-loop | One relationship from an item back to itself. |
| Set | A collection of distinct items. |
| Shallow copy | Copying addresses without copying the objects they own. |
| Singly linked list | Separately allocated nodes connected only toward the next node. |
| Traversal | Visiting nodes by following links. |
| Union | Merge two represented DSU groups when their roots differ. |
| Union by component size | Attach the smaller component's root below the larger component's root. |
| Use-after-free | Reading or writing an object after its storage has been released. |

### Optional-only vocabulary for extension questions

| Term | Working meaning |
|---|---|
| Dynamic connectivity | Maintaining connectivity information while relationships may be both added and removed. |
| Linked backend | An ADT implementation that stores elements in separately allocated linked nodes. |
| Rank | A DSU root's approximate tree-height measure used by union by rank. |
| Union by rank | Attach the root with smaller rank below the root with larger rank. |

## Anticipated student questions

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

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md#week-12--ownership-clinic-and-dsu-within-180-minutes)
- [Master curriculum, Module 14](../Data_Structures_Course_2026_Spiral_Curriculum.md#module-14--linear-linked-list-retrieval-clinic-and-union-find-bridge)
- [Module 14 package](../module_14_linked_list_dsu/README.md)
- [Module 14 vocabulary reference](../module_14_linked_list_dsu/student/vocabulary.md)
- [Consolidated Weeks 8–14 question bank](02_weeks_08_14_questions.md#week-12-linked-list-ownership-clinic-and-union-find-module-14)
