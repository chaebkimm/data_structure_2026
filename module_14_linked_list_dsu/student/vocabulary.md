# Module 14 Vocabulary Reference

Keep this file closed until the Cognitive Pause is preserved.

1. **memory address:** a value identifying a storage location.
2. **pointer:** a C value that stores an address.
3. **node:** one separately allocated object containing data and a link.
4. **singly linked list:** nodes connected only toward the next node.
5. **head:** the pointer to the first list node.
6. **`next`:** the node field holding the following node's address.
7. **`NULL`:** C's marker meaning no object.
8. **`*` in a declaration:** marks a pointer type.
9. **`->`:** accesses a field through a pointer.
10. **traversal:** visiting nodes by following links.
11. **allocation:** storage reserved while a program runs.
12. **ownership:** responsibility for releasing storage.
13. **invariant:** a rule true in every valid observable state.
14. **shallow copy:** copying addresses without copying owned objects.
15. **push-front:** insertion before the current first node.
16. **destroy:** release all owned storage and restore an empty state.
17. **memory leak:** owned storage that should be released but is lost.
18. **dangling pointer:** an address whose intended object is no longer
    alive.
19. **use-after-free:** reading or writing an object after its release.
20. **failure preservation:** a failed operation leaves prior state intact.
21. **set:** a collection of distinct items.
22. **disjoint:** sharing no item.
23. **connected component:** items joined through processed undirected
    relationships.
24. **Disjoint-Set Union (DSU):** a structure maintaining separate groups.
25. **Union-Find:** another name for DSU.
26. **dense IDs:** consecutive IDs beginning at zero.
27. **array:** a numbered row of same-typed values.
28. **sentinel:** a reserved value carrying a special meaning.
29. **parent:** the next ID followed toward a representative.
30. **forest:** several tree-shaped parent groups.
31. **root or representative:** an ID whose parent is itself.
32. **make-set:** create a new one-item group.
33. **find and connected query:** find follows parents to return a root; a
    connected query reports whether two IDs have the same root.
34. **iterative:** performed with loops rather than recursive self-calls.
35. **path compression:** redirect a find path to its root.
36. **union:** merge two represented groups.
37. **union by component size:** attach the smaller root under the larger.
38. **cycle and self-loop:** a cycle is a route that returns to an earlier
    item; a self-loop is one relationship from an item back to itself.
39. **cycle-producing relationship:** a new undirected relationship whose
    endpoints were already in one component.
40. **amortized analysis:** average cost across a sequence, including
    occasional expensive operations.
41. **`alpha(n)`:** an extraordinarily slow-growing function used in the
    DSU amortized bound.
42. **edge:** a graph connection between vertices.
43. **edge list:** one record per logical graph edge.
44. **reciprocal records:** two stored directions representing one
    undirected edge.
45. **parallel edges:** distinct edges with the same endpoints.
46. **`qsort` and relational comparator:** `qsort` is C's library function
    for arranging array records; its comparator tells which record comes
    first using less-than and greater-than tests instead of subtraction.
47. **`int64_t`:** a signed whole-number C type with exactly 64 bits.
48. **Kruskal's algorithm:** a later minimum-connection procedure that
    considers edges in increasing weight order and rejects cycles.
49. **authorization:** permission to perform an action.
50. **resilience:** ability to continue operating after a failure.
