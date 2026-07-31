# Module 12 Vocabulary Reference

Keep this file closed until the Cognitive Pause is preserved.

1. **graph:** vertices connected by edges.
2. **vertex:** one item stored in a graph.
3. **directed edge:** a connection usable only in its stated direction.
4. **breadth-first search (BFS):** edge-count-layer processing with a
   first-in, first-out Queue.
5. **source:** the starting vertex.
6. **destination:** a requested goal vertex.
7. **path:** a sequence that follows directed edges.
8. **weight:** the numeric cost assigned to an edge.
9. **weighted directed graph:** a directed graph whose edges have costs.
10. **path cost:** the sum of weights along a path.
11. **adjacency list:** outgoing edges stored together for each vertex.
12. **algorithm:** a precise, finite procedure.
13. **Dijkstra's algorithm:** a least-total-cost procedure requiring
    nonnegative weights.
14. **nonnegative:** zero or greater.
15. **distance:** modeled total path cost in this module.
16. **tentative distance:** best cost known so far, still replaceable.
17. **finalized distance:** a cost proved not to improve later.
18. **predecessor:** the previous vertex on the recorded path.
19. **sentinel:** a named marker with a special meaning.
20. **`INF`:** no finite representable path is currently known.
21. **`size_t`:** C's nonnegative whole-number type for sizes.
22. **`SIZE_MAX`:** the largest `size_t` value.
23. **frontier:** pending work not yet finalized.
24. **Priority Queue:** a collection that removes its first-ranked record.
25. **minimum Heap:** a tree-shaped Priority Queue with its minimum at the
    root.
26. **snapshot:** one saved vertex/cost pair.
27. **lazy duplicate:** a new snapshot added without editing an older one.
28. **decrease-key:** lowering a priority already stored in a Queue.
29. **stale snapshot:** a saved cost that differs from current `dist`.
30. **relaxation:** testing whether one edge improves a distance.
31. **candidate distance:** current distance plus one edge weight.
32. **strict relaxation:** updating only for a smaller candidate.
33. **parser:** code that converts input text into stored values.
34. **unsigned conversion:** conversion to a type with no negative values.
35. **overflow:** an arithmetic result beyond its type's range.
36. **cost-range failure:** explicit failure for an unrepresentable cost.
37. **reconstruct:** follow predecessors backward, then reverse them.
38. **unreachable:** having no stored directed path from the source.
39. **time complexity:** how running work grows with input size.
40. **auxiliary state:** extra storage beyond the input.
41. **parallel edge:** an edge repeating an existing start/end pair.
42. **self-loop:** an edge returning to its starting vertex.
43. **simple graph:** a graph without parallel edges or self-loops.
44. **model assumption:** a condition needed for a result to carry meaning.
45. **integrity:** stored state still obeys its required rules.
46. **stable:** equal-cost snapshots leave in insertion order.
47. **caller:** code that requests an operation.
48. **output:** storage where an operation writes its answer.
49. **allocation:** storage reserved while a program runs.
50. **capacity:** the maximum number of entries storage can hold.
51. **ownership:** responsibility for releasing reserved storage.
52. **backend:** the storage method behind a collection.
53. **public header:** a C file declaring names student code may use.
54. **TODO:** a marked task that is not finished yet.
55. **implementation:** the code and storage choice performing an operation.
56. **abstract data type (ADT):** behavior promised without requiring one
    storage method.
57. **application programming interface (API):** the named operations code
    can call.
58. **ID:** a number or name used to identify one item.
59. **pop:** removal of the first-ranked record.
60. **cycle:** a path that returns to an earlier vertex.
