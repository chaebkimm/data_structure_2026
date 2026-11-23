# Module 13 Vocabulary

Attach these names to the examples after students explain the needed actions. The [textbook](textbook.md) introduces each idea in context.

| Term | Working meaning |
| --- | --- |
| Search key | The value requested by a lookup |
| First match | Smallest matching index in the array currently searched |
| Linear search | Inspect successive positions until a match or the end |
| Nondecreasing | Neighboring values never get smaller from left to right |
| Binary search | Narrow a sorted interval by comparing its middle |
| Half-open interval | A range that includes its start and excludes its end |
| Lower boundary | The first position whose value is at least the requested key |
| Ordered prefix | The beginning already satisfying the sort order |
| Insertion sort | Extend that prefix by shifting strictly larger values |
| Merge sort | Recursively order smaller ranges and combine them |
| Merge | Combine two ordered ranges by their next unused values |
| Stable sort | Preserve the relative order of equal-key records |
| Scratch buffer | Nonoverlapping caller-owned temporary merge space |
| Copy-back | Write the merged temporary range into the original range |
| Precondition | A condition the caller must establish before a function |
| Invariant | A fact retained as the algorithm progresses |
| Oracle | An independent basis for an expected test result |
| Multiplicity | How many occurrences of each value must be retained |
| Canary | A surrounding marker used to detect unintended writes |
| Preparation cost | Work needed before later queries can use a method |
| Query | One request to find or select information |
| Update cost | Work needed when records are inserted, removed, or changed |
| Workload | The mix and frequency of queries and updates |
| Consolidation | Use earlier invariants and costs to justify a method choice |

AVL, hash buckets, linked lists, heaps, BFS, DFS, and Dijkstra are prior concepts retrieved here. DSU and spanning-tree selection are introduced in Module 14, not prerequisites for this lesson.
