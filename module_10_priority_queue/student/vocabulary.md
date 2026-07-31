# Module 10 Vocabulary Reference

Keep this file closed until the Cognitive Pause response is preserved.
Terms appear in their teaching order.

1. **synthetic alert:** an invented alert used for safe study.
2. **data structure:** a planned way to organize information.
3. **abstract data type (ADT):** public operations and behavior independent
   of one storage method.
4. **priority:** a number used by this course to rank service; smaller
   numbers leave first.
5. **Priority Queue:** an ADT that reports or removes the item ranked first.
6. **minimum-priority rule:** smaller numeric priority is selected first.
7. **insert:** add one item.
8. **peek-min:** report the selected minimum without removing it.
9. **extract-min:** remove and report the selected minimum.
10. **tie:** two records having equal priority.
11. **deterministic:** the same completed state and rule give the same
    result.
12. **stable tie behavior:** equal-priority items leave in arrival order.
13. **arrival sequence:** an increasing number assigned at successful
    insertion.
14. **record:** one value grouping related fields.
15. **field:** one named part of a record.
16. **comparator:** the exact rule deciding which of two records comes
    first.
17. **dynamic array:** adjacent storage whose allocation may be replaced by
    a larger allocation.
18. **backend:** a storage method used to provide an ADT.
19. **unsorted:** not maintained in service order.
20. **physical position:** one actual array index.
21. **logical service order:** the order promised by the ADT, independent
    of physical positions.
22. **candidate minimum:** the best record found so far during a scan.
23. **scan:** inspect live positions one by one.
24. **size:** the number of live records.
25. **capacity:** the number of allocated record positions.
26. **invariant:** a rule true in every valid completed state.
27. **allocation:** storage obtained while a program runs.
28. **ownership:** responsibility for releasing an allocation exactly once.
29. **failure preservation:** a failed operation leaves protected prior
    state and output unchanged.
30. **comparison count:** the number of times the record-order rule is
    applied.
31. **saturating count:** a count that stays at its largest value instead
    of wrapping.
32. **workload:** a chosen mixture and order of operations.
33. **time complexity:** a description of how work grows with input size.
34. **`O(1)`:** work bounded by a fixed amount independent of `n`.
35. **`O(n)`:** work that may grow in proportion to `n` live items.
36. **amortized `O(1)`:** average constant work across a sequence that
    includes occasional growth.
37. **sorted array:** an array maintained in comparator order.
38. **starvation:** an item waits indefinitely because other items keep
    ranking ahead of it.
39. **mutable priority:** a priority that may change while its record waits.
40. **decrease-key:** an operation that replaces one stored priority with a
    smaller one and repairs the backend.
41. **duplicate entry:** a new record inserted instead of changing an older
    record in place.
42. **stale entry:** an older duplicate that no longer represents the
    current best information.
