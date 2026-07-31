# Module 11 Vocabulary Reference

Keep this file closed until the Cognitive Pause is preserved. Terms appear
in their teaching order.

1. **synthetic alert:** an invented notice used for safe study.
2. **abstract data type (ADT):** public behavior independent of one storage
   method.
3. **Priority Queue:** an ADT that reports or removes the record ranked
   first.
4. **record:** one value grouping related named fields.
5. **field:** one named part of a record.
6. **priority:** the course number used first for service order; smaller
   leaves first.
7. **arrival sequence:** an increasing number assigned at successful
   insertion.
8. **comparator:** the exact rule deciding which of two records comes first.
9. **stable:** equal-priority records leave in arrival order.
10. **backend:** one storage method used to provide an ADT.
11. **binary tree:** a hierarchy with at most two child positions per node.
12. **node:** one stored item in a tree.
13. **root:** the one top node of a nonempty tree.
14. **parent:** the node directly above a child.
15. **child:** a node directly below a parent.
16. **level:** nodes the same link count below the root.
17. **complete binary tree:** every level is full except possibly the last,
    which fills left to right without a gap.
18. **array:** a numbered row of same-type values.
19. **index:** one array position, beginning at 0.
20. **implicit relationship:** a relationship calculated from positions
    instead of stored as a pointer.
21. **integer division:** whole-number division that discards a remainder.
22. **binary Heap:** a complete binary tree arranged for a priority rule.
23. **minimum binary Heap (min-Heap):** a Heap whose minimum record is at
    the root.
24. **Heap-order invariant:** no child comes before its parent under the
    comparator.
25. **partial order:** only required relationships are ordered; the entire
    array need not be sorted.
26. **append:** place a new record at the end.
27. **swap:** exchange two complete records.
28. **sift-up:** repair Heap order from an appended record toward the root.
29. **peek-min:** copy the root without removing it.
30. **extract-min:** remove and report the root.
31. **candidate:** the final record being placed during downward repair.
32. **better child:** the existing child that comes first under the
    comparator.
33. **sift-down:** repair Heap order from the root toward a leaf.
34. **leaf:** a node with no children.
35. **invariant checker:** a debug function that checks required rules.
36. **mutation:** an operation that changes stored structure.
37. **instrumentation:** extra measurement or checking added for study and
    debugging.
38. **instrumented run:** operation work plus enabled diagnostic checking.
39. **normal-operation count:** work measured before a separate checker is
    called.
40. **time complexity:** a description of how work grows with input size.
41. **`O(1)`:** fixed-bounded work independent of live size.
42. **`O(log n)`:** work that grows with the height of a complete binary
    tree; adding a level roughly doubles available positions.
43. **`O(n)`:** work that may grow with all `n` live records.
44. **binary search tree (BST):** a binary tree with global lower-left and
    higher-right search-key order.
45. **sorted sequence:** a sequence in which every record is kept in total
    comparator order.
46. **C dynamic-memory heap:** storage from which C allocation functions
    obtain blocks; it is not the binary Heap data structure.
47. **differential test:** a test applying the same requests to two
    implementations and comparing their public results.
48. **reference model:** a simpler implementation used as the expected
    answer in a differential test.
49. **integrity:** stored state still obeys its required rules.
50. **corruption:** an unintended state change that breaks a required rule.
