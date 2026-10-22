# Week 13 — Union-Find, Kruskal, and Capstone Integration: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 13-week course

Introduce DSU here, then implement find, union by size, and Kruskal selection in one supplied scaffold. Make-set, loading, sorting, totals, validation, and Prim are supplied. Prim implementation and the original List/DSU and two-MST labs are optional. Brief synthesis and the integration checkpoint belong to the same artifact; defense is in the separate final period.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| DSU / Union-Find | A structure maintaining nonoverlapping groups. |
| disjoint | Sharing no member. |
| dense ID | An integer from zero through the active count minus one. |
| parent array | An array encoding a forest of representative paths. |
| root / representative | An ID whose parent is itself. |
| make-set | Create a singleton component; supplied this week. |
| find | Return the representative of an element. |
| path compression | Redirect a searched path to its representative. |
| iterative two-pass find | Locate the root first, then compress the path. |
| union | Merge two different components. |
| union by size | Attach the smaller component below the larger root. |
| component size | Number of members, stored only at roots here. |
| component count | Number of distinct roots. |
| same-set result | Successful union with no merge because roots already match. |
| amortized cost | Total work averaged across an operation sequence. |
| alpha(V) | The very slow-growing function in the optimized DSU bound. |
| weighted undirected graph | Bidirectional relationships with numeric edge costs. |
| logical edge | One relationship distinct from its two incident records. |
| edge list | One record per logical edge. |
| parallel edges | Different edges joining the same endpoints. |
| self-loop | An edge whose endpoints are the same vertex. |
| cycle | A closed route formed when accepted-edge connectivity already joins the endpoints. |
| forest | A collection of trees with no cycle. |
| MST | A minimum-total-cost tree spanning a connected graph. |
| MSF | A minimum spanning tree for each connected component. |
| Kruskal | Scan edges in weight order and accept those joining different components. |
| cut property | A lightest crossing edge is safe for a cut respecting the accepted forest. |
| Prim | Grow a tree across its boundary; supplied demonstration this week. |
| comparator | A supplied relational ordering function that avoids subtracting weights. |
| int64_t | A signed 64-bit integer type used for weights and totals. |
| checked total | A sum published only if its mathematical result fits the type. |
| failure preservation | Invalid input does not partially publish a result or caller output. |
| invariant | A rule linking valid representation state and algorithm progress. |
| V−c | Selected edge count for a spanning forest with V vertices and c components. |
| shortest-path objective | Minimize route distance from a source; differs from total MST cost. |
| resilience | Ability to remain useful after failure; minimum cost does not ensure it. |
| capstone integration | Connect tested module interfaces in the existing cumulative project. |

## Anticipated student questions

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

## Sources

- [Combined Week 13 lesson, lab, and release](../module_16_prim_kruskal/week_13/README.md)
- [13-week delivery guide](../Data_Structures_Course_2026_13_Week_Delivery_Guide.md)
