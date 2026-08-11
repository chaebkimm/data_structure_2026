# Week 10 — Dijkstra and Practical 2: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Module 12 supplies the Dijkstra model, but **Practical 2 is the sole Week 10
submission**. Students complete the bounded relaxation/frontier core and path-
reconstruction decisions inside a supplied weighted-graph, parser, Heap, setup,
cleanup, validation, and integration scaffold. The linear-Priority-Queue
comparison uses an instructor-supplied reference. The full standalone Stage E
lab and a separate Spiral 4 comparison are not added as extra work.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| graph | A set of vertices connected by stored edges. |
| vertex | One item in a graph. |
| directed edge (arc) | A connection usable only from its stated start to its stated destination. |
| source | The vertex where a shortest-path run begins. |
| destination | A requested goal vertex. |
| path | A sequence of vertices that follows stored directed edges. |
| weight | The numeric cost assigned to an edge. |
| weighted directed graph | A directed graph in which every edge carries a cost. |
| path cost | The sum of all edge weights along a path. |
| breadth-first search (BFS) | A Queue-based algorithm that minimizes hop count in an unweighted graph. |
| Dijkstra's algorithm | An algorithm that finds least-total-cost paths when every edge weight is nonnegative. |
| nonnegative weight | An edge cost that is zero or greater. |
| distance | Modeled total path cost from the source in this week. |
| tentative distance | The best cost known so far for a vertex, still allowed to improve. |
| finalized distance | A current cost accepted as unable to improve later under Dijkstra's assumptions. |
| predecessor | The previous vertex on the recorded source-to-vertex path. |
| finalized array | One Boolean per vertex recording whether its distance has been finalized. |
| finalized order | The order in which nonstale vertices become finalized. |
| adjacency list | Outgoing weighted edges stored together for every vertex. |
| frontier | Pending vertex/cost work not yet finalized. |
| Priority Queue | An ADT that removes the waiting record ranked first. |
| minimum Heap | The Week 9 Priority Queue backend that exposes the smallest-ranked frontier record. |
| snapshot | One saved vertex-and-cost pair in the frontier. |
| lazy duplicate | A new improved snapshot inserted without editing an older queued snapshot. |
| stale snapshot | A popped snapshot whose saved cost differs from the vertex's current distance. |
| stale-pop skipping | Discarding a stale snapshot before finalizing it or inspecting its outgoing edges. |
| relaxation | Testing whether one outgoing edge creates a better distance to its destination. |
| candidate distance | The current vertex's distance plus one outgoing edge weight. |
| strict relaxation | Updating distance and predecessor only when the candidate is smaller. |
| equal-cost alternative | A second route with the same total cost, which strict relaxation does not use to replace the predecessor. |
| sentinel | A reserved value representing a special case rather than an ordinary cost. |
| `DIJKSTRA_INF` | The course sentinel meaning no finite representable path is currently known. |
| `SIZE_MAX` | The largest `size_t` value, reserved here as `DIJKSTRA_INF`. |
| `size_t` | C's nonnegative whole-number type for counts, indexes, weights, and distances. |
| parser | Code that converts textual input into checked stored values. |
| unsigned conversion | Conversion to a type that cannot represent negative values. |
| overflow | An arithmetic result beyond the range of its type. |
| subtraction guard | The pre-addition check that proves a candidate cost will not overflow or equal the infinity sentinel. |
| cost-range failure | Explicit failure when a path cost cannot be represented safely. |
| unreachable | Having no stored directed path from the source. |
| path reconstruction | Following predecessors backward and reversing them to produce a forward path. |
| source-only path | The one-vertex path returned when source and destination are the same reachable vertex. |
| path certificate | A returned path whose edges and summed cost can be checked independently. |
| failure preservation | A failed operation leaves the caller's prior protected result or path unchanged. |
| capacity | The maximum number of entries a storage object can hold. |
| frontier limit `arc_count + 1` | Space for the source snapshot plus at most one successful relaxation per arc. |
| simple graph | A graph without parallel edges or self-loops. |
| parallel edge | A second edge repeating an existing start and destination. |
| self-loop | An edge whose start and destination are the same vertex. |
| model assumption | A condition required for an algorithmic or real-world interpretation to be valid. |
| lazy-strategy time bound | `O(V + E log(E + 1))` for the implemented Heap frontier with lazy duplicates. |
| `O(E)` frontier space | The possible pending-snapshot storage used by the implemented lazy strategy. |
| Practical 2 | The cumulative Week 10 assessment that replaces the ordinary Dijkstra lab. |

### Optional vocabulary for extension questions

| Term | Working meaning |
|---|---|
| decrease-key | Lowering the priority of an entry already stored in a Priority Queue. |
| eager decrease-key frontier | A frontier that edits an existing queued entry instead of inserting a lazy duplicate. |
| negative-weight shortest-path algorithm | An algorithm designed for graphs that may contain negative edge weights; Dijkstra is not one. |
| parser fuzz/boundary testing | Trying signs, whitespace, malformed text, and range endpoints beyond the supplied core suite. |
| dynamically sized graph | A graph whose limits and allocations are determined at runtime instead of the course bound of 16 vertices. |

## Anticipated student questions

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

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Original Weeks 8–14 question bank](02_weeks_08_14_questions.md)
- [Module 12 Practical 2 role](../module_12_graph_dijkstra/README.md)
- [Module 12 vocabulary reference](../module_12_graph_dijkstra/student/vocabulary.md)
