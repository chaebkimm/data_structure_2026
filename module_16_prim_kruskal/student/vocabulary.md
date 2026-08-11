# Module 16 Vocabulary Reference

Open this reference only after preserving all three Cognitive Pause targets.

- **Adjacency list:** storage that groups the edges touching each vertex.
- **Algorithm:** a finite step-by-step procedure.
- **Bridge:** an edge whose removal increases the number of components.
- **Comparator:** a function that decides which of two records comes first.
- **Component:** a largest connected part of a graph.
- **Connected:** joined by a path.
- **Crossing edge:** an edge with endpoints on opposite sides of a cut.
- **Cut:** a separation of all vertices into two groups.
- **Cycle:** a nonempty route returning to its start without reusing an edge.
- **Density:** how many possible edges a graph contains.
- **Disjoint-set union (DSU):** a structure maintaining nonoverlapping
  groups; it is also called Union-Find.
- **Edge:** a relationship between two vertices.
- **Edge list:** storage with one record per logical edge.
- **Forest:** a collection of trees.
- **Frontier:** pending Prim work.
- **Graph:** vertices together with their edges.
- **Heap:** a tree-shaped Priority Queue.
- **Incident record:** one stored view of an edge from one endpoint.
- **Invariant:** a rule true for every valid state.
- **`int64_t`:** C's signed 64-bit whole-number type.
- **Key:** in Prim, the cheapest known single edge entering a vertex outside
  the current tree.
- **Kruskal's algorithm:** a procedure that scans edges from smallest weight
  upward and joins different DSU groups.
- **Lazy duplicate:** a new improved snapshot stored without removing the
  older one.
- **Logical edge:** one undirected relationship identified by one edge ID.
- **Minimum spanning forest (MSF):** one minimum spanning tree for each
  component.
- **Minimum spanning tree (MST):** a spanning tree with smallest possible
  selected-edge total.
- **Matrix:** storage with one position for every vertex pair.
- **Normalized endpoints:** an edge record with the smaller endpoint ID
  first.
- **Overflow:** an arithmetic result exceeding the numeric type's range.
- **Parallel edges:** distinct edge IDs with the same endpoints.
- **Parent:** in Prim, the other endpoint of a vertex's selected key edge.
- **Path:** a sequence of adjoining edges.
- **Prim's algorithm:** a procedure that grows a tree through cheapest
  crossing edges.
- **Priority Queue:** a collection that removes its first-ranked record.
- **Representative root:** the ID naming one DSU group.
- **Resilience:** the ability to continue required service after a failure.
- **Safe edge:** an edge that can be added while leaving some minimum result
  possible.
- **Self-loop:** an edge whose two endpoints are the same vertex.
- **Signed weight:** an edge value that may be negative, zero, or positive.
- **Shortest-path tree:** recorded least-cost source paths; it need not have
  minimum selected-edge total.
- **Spanning tree:** a connected, cycle-free selection containing every
  vertex of a connected graph.
- **Stale snapshot:** saved Prim work whose key is no longer current.
- **Tree:** a connected graph with no cycle.
- **Undirected edge:** an edge that works in both directions.
- **Validator:** a diagnostic operation that checks stated rules.
- **Vertex:** one item represented in a graph.
- **Weight:** the numeric cost stored on an edge.
