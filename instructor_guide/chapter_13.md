# Chapter 13. Finding Values, Ordering Records, and Choosing a Method

Follow the [Module 13 180-minute plan](../module_13_search_sort_consolidation/instructor/lesson_plan.md). Use the [English textbook](../module_13_search_sort_consolidation/student/textbook.md) or [Korean textbook](../module_13_search_sort_consolidation/student/textbook_korean.md), [workbook](../module_13_search_sort_consolidation/student/class_material.md), and complete [lab.c](../module_13_search_sort_consolidation/student/lab.c). One artifact combines search/sort tests and workload consolidation. DSU/Prim/Kruskal belong to Module 14.

## Starting Question

> “Where is the first 17 in 31,23,17,8,17,42, and what rule would let one comparison exclude several positions?”

Expected response: a scan finds original position 2; eliminating an interval needs a known order. Preserve the initial answer before sorting the cards.

## Why We Need This

A middle value in unordered data cannot tell us which side contains the key. Ordering enables interval elimination but costs preparation work. Repeated queries can share that preparation; one query may not justify it. Insertions and merges also have different movement and space costs. Choose from the complete workload rather than one asymptotic query label.

## Board Walkthrough

1. Compare 31,23,17 and return original index 2. A miss examines six values.
2. Order the same records as 8,17A,17B,23,31,42. Trace `[0,6) → [0,3) → [0,1) → [1,1)`. Check index 1 before reading, then confirm equality.
3. Trace insertion shift counts 1,2,3,2,0. Strict `>` preserves 17A before 17B.
4. Merge ordered halves `[17A,23,31]` and `[8,17B,42]` through separate scratch. Left-on-equality chooses A first.
5. Compare preparation/query/update/order/space for a scan, sorted array, linked list, hash table, AVL tree, heap, and graph frontier. Do not implement those earlier structures again.

The labels expose record identity on paper. Integer-only output checks cannot establish stable tie order. Search returns a position in the current array, not the original identity after sorting.

## Common First Thoughts

- “Return immediately when binary search sees any equal key.”
- “A sorted index is the original record position.”
- “Identical sorted integer output proves stability.”
- “A sorted linked list has constant-time access to its middle.”
- “A heap is a sorted array and finds any key quickly.”
- “Sorting first is always cheaper than scanning.”

## Neutral Questions

Ask which earlier candidate could still equal the key, which source value a write would overwrite, how A/B identities remain ordered, what work happens before a query, and which update changes the chosen representation. Require assumptions with hash expected costs and AVL balance claims.

## Vocabulary Rules

Retrieve arrays, links, hash collisions, balanced-tree paths, heap priority, FIFO/LIFO, BFS, DFS, and Dijkstra. Introduce half-open intervals, first-match binary search, insertion/merge sorting, stability, scratch buffers, preparation cost, and workload selection. DSU and MST selection are not prerequisites.

## Final Check

> “For one lookup and for many lookups on an unchanged snapshot, which method do you choose, what preparation does it require, and what changes when the records are updated?”

Minimum answer separates preparation from queries, states the ordering/storage conditions, handles duplicate first-match semantics, and justifies a competing method. Carry ordered edge candidates into Module 14 without assigning a new graph algorithm here.
