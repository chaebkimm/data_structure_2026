# Week 6 — Graph DFS and Practical 1: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Required work is one complete graph DFS implementation: the iterative version
using the Week 4 Stack. Students trace discovery, handle cycles and disconnected
input, and justify traversal cost. Recursive graph DFS is extension work.
**Practical 1 is the only required graded submission for Week 6**; its bounded
Graph DFS task supplies the week's implementation evidence, so the standalone
Module 6 lab is not assigned in addition to it.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| graph | A set of items and the direct relationships stored between them. |
| vertex | One item in a graph. |
| edge | One direct relationship between two vertices. |
| directed edge | An edge that can be followed only in its stated direction. |
| undirected edge | A relationship that can be followed in both directions. |
| out-neighbor | A vertex reached by an edge leaving the current vertex. |
| route | A sequence of vertices connected by edges in the allowed direction. |
| cycle | A route that returns to a vertex reached earlier. |
| source | The vertex where a search begins. |
| reachable | Having at least one route from the stated source. |
| isolated vertex | A vertex with no incident edges. |
| connected component | One separate group in an undirected graph whose vertices can reach one another. |
| depth-first search (DFS) | A search that follows one available route deeply before returning to another waiting choice. |
| iterative algorithm | An algorithm that repeats with a loop rather than recursive calls. |
| Stack | A collection that removes the newest stored item first. |
| last in, first out (LIFO) | The Stack rule: the most recently added item is removed first. |
| `push` | Add one vertex ID to the top of the Stack. |
| `pop` | Remove and report the vertex ID at the top of the Stack. |
| frontier | Discovered vertices that are waiting to be processed. |
| discover | Reach a vertex for the first time. |
| schedule | Place a discovered vertex on the frontier so its work will occur. |
| process | Remove a vertex from the frontier and perform its traversal work. |
| visited array | One Boolean per vertex recording whether it has already been discovered and scheduled. |
| push-time marking | Marking a vertex immediately after it is successfully pushed onto the DFS frontier. |
| traversal order | The sequence in which processed vertices are recorded. |
| deterministic order | A reproducible order produced by a stated neighbor-inspection rule. |
| adjacency matrix | A row-and-column table that records whether each possible edge exists. |
| adjacency list | One stored collection of outgoing neighbors for every vertex. |
| `GraphDfsOrder` | The course result object containing recorded vertex IDs and their count. |
| invariant | A rule that must remain true after every completed traversal step. |
| validation | Checking that arguments and stored graph state obey their required rules. |
| output parameter | Caller-provided storage in which a function writes a result. |
| failure preservation | A failed operation leaves the caller's previous protected output unchanged. |
| time complexity | A description of how running work grows as the graph grows. |
| auxiliary space | Temporary working storage separate from the input graph and returned result. |
| `V` | The number of active vertices. |
| `E` | The number of stored edges. |
| `O(V²)` | Matrix-traversal work that can grow like the vertex count multiplied by itself. |
| `O(V + E)` | Adjacency-list traversal work that grows with vertices plus stored edges. |
| Practical 1 | The cumulative Week 6 assessment that replaces the ordinary Graph DFS lab. |
| synthetic reachability model | An invented graph used to practice reachability without claiming real authorization or exploitability. |

### Optional vocabulary for extension questions

These terms support the optional questions below; recursive graph DFS is not
part of the required Week 6 implementation.

| Term | Working meaning |
|---|---|
| recursive graph DFS | A DFS form in which a function calls itself to explore an out-neighbor. |
| recursion | A function calling itself directly or through other functions. |
| call frame | Saved local state for one active function call. |
| runtime call stack | The implementation-managed storage commonly used for active call frames. |
| recursion-depth risk | The possibility that a very deep search exhausts available call-stack space. |

## Anticipated student questions

### Meaning and mental model

- What changes when depth-first exploration moves from a tree to a graph?
- What is the difference between discovering, scheduling, popping, and processing a vertex?
- Why does a route back to an earlier vertex require persistent visited state?
- Why can DFS from one source leave valid vertices completely unvisited?

### Representation and invariants

- What must be true of `GraphDfsOrder` after a successful traversal?
- When should a vertex be marked visited so that it is never pushed twice?
- Why must the stored graph be validated before DFS begins?
- What invariant connects the Stack, visited array, and output order during iterative DFS?

### Operations, C API, and ownership

- Which DFS form is the required Week 6 implementation in the 14-week path?
- Why does iterative DFS inspect outgoing neighbors in descending index order?
- Why must `out_order` or `out_component_count` remain unchanged on every failure?
- Why does connected-component counting reject directed graphs under this API?

### Tracing

- What Stack, visited-array, and output states result at each step of a cyclic graph trace?
- How do ascending versus descending neighbor scans change the deterministic visit order?
- What happens when two pending routes lead to the same vertex before either route is processed?
- How does an outer scan over all vertices turn source DFS into connected-component counting?

### Tests and debugging

- Which tests separately exercise a self-loop rejection, a longer cycle, a disconnected graph, and an isolated vertex?
- How can a regression test prove that no vertex is scheduled or recorded twice?
- What test reveals a visited mark placed after `pop` instead of after a successful `push`?
- In the Graph DFS Autopsy, why does omitting or delaying the visited check cause repeated calls around a cycle?

### Complexity

- Why does full DFS over an adjacency matrix take `O(V^2)` time?
- Why can the same conceptual traversal take `O(V + E)` with adjacency lists?
- What is the maximum amount of Stack and visited storage needed by this bounded implementation?
- Why is a different visit order not automatically a complexity or correctness defect?

### Cybersecurity and interpretation

- What can reachability from a synthetic source tell us, and what can it not prove about authorization or exploitability?
- How could failing to validate a start vertex lead to unsafe array access?
- How might a deliberately dense graph amplify the cost difference between representations?
- Why should a disconnected vertex not be silently treated as absent from the dataset?

### Assignment and evidence

- Is Practical 1 the only required graded submission in Week 6?
- Do I also need to submit the standalone Module 6 Stage E lab?
- Which bounded iterative-DFS behavior, cycle test, and disconnection test can appear in Practical 1?
- What prior ArrayList, tree, graph, Stack, pointer, and bounds evidence may Practical 1 ask me to reconstruct or repair?

### Transfer and prerequisites

- How does the Week 4 Stack control the frontier in iterative graph DFS?
- Which Week 5 recursive-tree trace helps explain unfinished graph choices?
- What new visited invariant is added when a tree becomes a general graph?
- How will replacing the Stack with a Queue change exploration in the BFS arc?

### Extension questions — optional

- How does recursive graph DFS represent its frontier without an explicit vertex Stack?
- Can recursive and iterative DFS produce different valid orders on the same graph?
- What additional failure risk does recursion introduce on a very deep graph?
- Is recursive graph DFS required in Practical 1 or explicitly extension work?

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Original Weeks 1–7 question bank](01_weeks_01_07_questions.md)
- [Module 6 delivery role](../module_06_graph_dfs/README.md)
- [Module 6 vocabulary reference](../module_06_graph_dfs/student/vocabulary.md)
