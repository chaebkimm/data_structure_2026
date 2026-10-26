# Week 13 — Searching, Sorting, and Consolidation: Vocabulary and Questions

[All-week bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

Use [Module 13](../module_13_search_sort_consolidation/README.md) to compare
linear search with first-match binary search, then trace stable insertion
sort and stable merge sort. Consolidate the structure and algorithm choices
from Modules 1–12. Sorting prepares the ordered-edge idea used by
[Kruskal in Week 14](week_14_dsu_mst_capstone.md); DSU remains new learning there.

The supplied C lab uses `linear_search`, `binary_search_first`,
`insertion_sort`, and `merge_sort` with at most 64 integers. Searches return
the first matching array index or `-1`; binary search requires nondecreasing input.
Merge sort uses a separate caller-owned scratch buffer of at least `n`
integers. Valid zero-length calls access no element and may use null pointers.
The functions do not check every caller precondition. Do not test invalid
sizes, unsorted binary-search input, or overlapping merge buffers as requests
that should be rejected.

Keep the example `[31,23,17,8,17,42]`: linear search for 17 returns index 2.
Both sorts produce `[8,17,17,23,31,42]`; first-match binary search returns
index 1 in that sorted array. Sorting changes positions, so the result is
not an original-position lookup. One 180-minute artifact contains traces,
focused original assertions, compiler output, workload comparisons, and a
justified structure/algorithm choice.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| search key | The value requested by a search. |
| first match | The smallest active index whose value equals the requested key. |
| linear search | Check active positions from the beginning until a match or the end. |
| sorted / nondecreasing | Each value is no smaller than the value immediately before it. |
| binary search | Narrow an ordered candidate interval using its middle value. |
| half-open interval | The positions from `lo` through `hi-1`, written `[lo,hi)`. |
| lower-bound position | The first position whose value is not less than the key, or `n` if none exists. |
| safe midpoint | `lo + (hi-lo)/2`, which avoids adding two potentially large indices. |
| insertion sort | Extend an ordered prefix by shifting larger values and inserting one saved value. |
| sorted prefix | The already-ordered beginning of the active array. |
| shift | Move an existing value one position to make room. |
| merge | Combine two ordered ranges into one ordered range. |
| merge sort | Divide a range, order both parts, and merge them. |
| base case | A range of zero or one value, which needs no sorting work. |
| scratch buffer | Caller-owned temporary storage used by merge sort. |
| nonoverlapping buffers | The array and scratch buffer occupy separate storage. |
| stable sort | Equal-key records keep their original relative order. |
| comparison | A test deciding how values or a value and key relate. |
| preprocessing cost | Work performed before later queries can use a prepared representation. |
| permutation preservation | The result contains exactly the original values with their multiplicities. |
| workload | The mix of queries, updates, ordering needs, and data sizes. |
| consolidation | Explain earlier structures together and choose from their contracts and costs. |
| oracle | An independent expected result used to check a program's output. |
| reserved versus additional storage | Separate the input array from extra scratch space and active recursive calls. |

## Anticipated student questions

### Search contracts and candidate intervals

- What index does linear search return for 17 in `[31,23,17,8,17,42]`, and why does it stop before the second 17?
- Why does first-match binary search return index 1 after the same values are sorted?
- Why is a sorted-array result not necessarily the original record's index?
- Why must the binary-search array be nondecreasing before the first comparison?
- Which positions remain possible in the half-open interval `[lo,hi)`?
- Why does a middle value below the key permit `lo = mid + 1`?
- Why does a middle value equal to the key move the upper boundary instead of returning immediately?
- Why must the final lower-bound position be checked for equality before reporting a match?
- How do missing keys below all values, between values, and above all values end in `-1`?
- Why do empty and singleton inputs need explicit expected results even though the search code is short?

### Sorting actions and invariants

- What ordered prefix remains after inserting 23 into the canonical array's first two positions?
- Why must insertion sort save the current value before shifting larger values?
- Why does shifting only strictly larger values preserve the order of equal keys?
- Which eight shifts occur across the canonical insertion-sort run?
- Why does a zero- or one-element merge-sort range require no further split?
- How do two already-ordered halves make the next smallest merged value available at one of their fronts?
- Why does choosing the left value on an equal-key merge preserve stability?
- Why must merge sort's scratch buffer have at least `n` writable integer slots and not overlap the input?
- Why must the sorted merged range be copied back before its caller merges a larger range?
- Why can identical integer output fail to reveal whether the two original 17 records exchanged places?

### Tests, costs, and evidence

- Which assertions distinguish sorted order from preservation of every original value and duplicate count?
- Which independent oracle can check a search result without repeating the binary-search implementation?
- Which empty, singleton, duplicate-heavy, sorted, reverse, and signed-extreme fixtures exercise different behavior?
- Why are invalid sizes or overlapping merge buffers outside this lab's unchecked caller contract?
- How can paper labels `17A` and `17B` establish the equal-key order that integer-only output hides?
- Why does the canonical binary search use three interval comparisons and one final equality test rather than automatically beating every short linear query?
- When do repeated queries justify paying a sorting cost once?
- Why can insertion sort need quadratic shifts in reverse order while an already-ordered input needs no shifts?
- Why does merge sort combine logarithmically many levels of linear merging work?
- Why are merge scratch `O(n)` and active recursive calls `O(log n)` separate additional-storage terms?

### Consolidation and transfer

- When is a sorted array with binary search suitable for many queries over rarely changed data?
- When do frequent exact-key updates favor a hash index, and which distribution assumptions affect its expected cost?
- When do ordered range queries justify an AVL index rather than a hash table?
- Why does a Heap support repeated minimum selection without keeping its whole array sorted?
- Why do linked-list insertion after a known predecessor and searching for that predecessor have different costs?
- Which public linked-queue API did Module 8 use for BFS, and where does dequeue recycle its pool slot before expansion?
- Why does FIFO unweighted BFS answer a different path question from indexed-Heap Dijkstra?
- How can sorting prepare Kruskal's edge scan without deciding which edges form cycles?
- Which trace, original assertions, costs, and corrected explanation belong in the single Week 13 artifact?
- How does a structure-choice claim change when query frequency, mutation frequency, memory, or ordering requirements change?

## Sources

- [Module 13 lesson and lab](../module_13_search_sort_consolidation/README.md)
- [Lab source](../module_13_search_sort_consolidation/student/lab.c)
- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
