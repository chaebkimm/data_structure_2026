# Chapter 13. Searching, Sorting, and Consolidation

We have stored values in arrays, linked nodes, hash buckets, trees, and heaps. Now choose how to find a value and whether arranging the values first is worth the work. This chapter follows the complete [lab.c](lab.c). It prepares the ordered-edge comparison in Module 14 without assuming DSU.

[한국어 교재](textbook_korean.md) · [Class workbook](class_material.md) · [Concept slides](ppt_material.md) · [Lab slides](ppt_lab_material.md)

## Thinking Logically

### How do we find one value without changing the data?

Suppose the values arrived in this order. We want the first position containing 17. The positions matter because two records have the same value.

```text
index:   0   1   2  3   4   5
value:  31  23  17  8  17  42
```

Read each position from the beginning and stop at the first match. This is the linear search already used in Chapter 1. Comparing 31, 23, and 17 returns index 2. A search for 99 checks all six values and returns `-1`. Searching does not reorder the input. An empty input also returns `-1` without reading a position.

### When can one comparison discard several positions?

A comparison with 23 in the original array cannot tell us which side contains 17. The values have no ordering rule. If values increase from left to right, a value smaller than 17 cannot be a match, and neither can any earlier value. We can use the middle value to discard a whole interval. This method is binary search.

Arrange the same six values into nondecreasing order: a value may equal its neighbor.

```text
index:   0   1   2   3   4   5
value:   8  17  17  23  31  42
```

Keep a half-open interval `[lo, hi)`: `lo` belongs to the interval and `hi` does not. Positions before `lo` are smaller than the key. Positions at or after `hi` are at least the key. Initially `lo=0`, `hi=6`, so neither excluded region contains a position.

To find the first 17, compare the middle value with the key. On equality, keep searching to its left. Do not return immediately because another 17 may occur earlier.

| `lo`, `hi` before comparison | `mid` | Value | Change |
| --- | ---: | ---: | --- |
| 0, 6 | 3 | 23 | `hi=3` |
| 0, 3 | 1 | 17 | `hi=1` |
| 0, 1 | 0 | 8 | `lo=1` |

At `lo==hi==1`, check that index 1 exists and contains 17. Return 1. This position belongs to the sorted array. The original first-match position was 2. Sorting changes positions; a position is not a permanent record identity. For 99 the interval closes at 6, so the final bound check returns `-1` without reading `sorted[6]`.

The function requires already-sorted input. It neither checks nor creates that condition. Use `lo + (hi-lo)/2` to form the midpoint without adding two possibly large bounds. The current lab bounds the array at 64 values.

### How can we grow an already-ordered beginning?

Binary search needs ordered data. Copying a value into its final location without preserving the displaced values would lose data. Instead, keep the beginning ordered and insert the next value into that beginning. Save the next value, move larger earlier values one place right, then write the saved value into the gap. This is insertion sort.

| Saved next value | Array after insertion | Right shifts in this pass |
| ---: | --- | ---: |
| 23 | 23, 31, 17, 8, 17, 42 | 1 |
| 17 | 17, 23, 31, 8, 17, 42 | 2 |
| 8 | 8, 17, 23, 31, 17, 42 | 3 |
| 17 | 8, 17, 17, 23, 31, 42 | 2 |
| 42 | 8, 17, 17, 23, 31, 42 | 0 |

The original two 17 records can be labeled 17A at index 2 and 17B at index 4 on paper. The loop moves a value only when it is strictly larger than the saved value. It leaves 17A before 17B. Preserving equal records' original relative order is stability. Plain integer output hides their identities, so seeing two equal integers in the result does not prove stability.

### How can we order larger inputs without repeatedly shifting long prefixes?

When each new value belongs near the beginning, insertion sort moves many earlier values again. We can divide the input into two smaller ranges, order each, then combine their already-ordered beginnings. This is merge sort. A range of zero or one value already satisfies the order rule.

Split the same six records into `[31,23,17A]` and `[8,17B,42]`. After recursively ordering them, the halves are `[17A,23,31]` and `[8,17B,42]`. Compare their first unused values. Copy 8 from the right half. When both next values equal 17, copy 17A from the left half first. Continue to produce `[8,17A,17B,23,31,42]`.

Write the merged range into a separate temporary array, then copy that range back. The temporary space is called a scratch buffer. Reuse the same buffer across all recursive calls. The caller supplies at least `n` writable integers that do not overlap the values array. No function calls `malloc` or `free`. Choosing the left half on equality, combined with the stable smaller sorts, preserves equal records' order.

### Which earlier structure fits the workload?

A faster search in an ordered array has a preparation cost. Sorting before one small lookup can cost more work than scanning once. Many lookups on one unchanged snapshot can share that preparation. Changing the snapshot may require maintaining its order or sorting again.

For each request, state what must be found, how often values change, what order is needed, and what storage is available. Then choose a method.

| Request | Candidate | Reason to check |
| --- | --- | --- |
| One lookup in a short unsorted snapshot | Linear scan | No sorting or index preparation |
| Many lookups in one unchanged ordered snapshot | Binary search | Middle positions are directly accessible |
| Insert/remove after a known list predecessor | Linked nodes | Local links change without shifting values |
| Repeated exact-key lookup with suitable hash distribution | Hash buckets | Search only the selected chain; inspect collisions and capacity |
| Maintain ordered keys while updating | AVL tree | Balance keeps search/update paths short |
| Repeatedly select the smallest pending item | Min-heap | The root answers the minimum request, not arbitrary-key lookup |
| Process graph work by arrival order or minimum cost | BFS queue or Dijkstra heap | Scheduling rule follows the graph question |

A linked list does not gain array-style binary-search cost merely because its values are ordered: finding the middle by following links costs work. A heap is not a sorted array and does not put every smaller key to the left of every larger key. A traversal processes relationships; an exact-key search asks a different question.

Module 14 will consider graph edges in increasing weight order. This chapter explains what that ordering costs and why equal weights need a clear tie rule. The supplied Module 14 edge sorter remains supplied; its connectivity decision is taught there.

## Calculating Efficiency

### What do the six values actually cost?

Linear search for 17 reads three keys in the original array. The binary trace makes three interval decisions and one final equality check after sorting. It does not beat that particular three-comparison linear search. A miss in the original array checks all six keys. Keep preparation and query work separate.

Insertion sort makes eight right shifts for the canonical input. Its five passes also write each saved key into the final gap. The loop makes ten value comparisons, counting a failed value comparison when one is reached; bounds checks are separate. Already-ordered data needs no shifts. Reverse order can require `1+2+...+(n-1)` shifts, so worst-case work grows as `O(n^2)`. Best-case work is `O(n)`; additional local storage is `O(1)`.

### Why does halving change growth?

A binary-search decision leaves at most about half the candidate positions. Repeated halving takes `O(log(n+1))` decisions. The extra final bound/equality check takes fixed work. Search reserves only a few indices, so its extra space is `O(1)`. Linear search can inspect all `n` positions: `O(n)` work and `O(1)` extra space.

Merge sort divides until ranges contain at most one item. Each merge level copies a total proportional to `n` values, and the number of division levels grows logarithmically. For `n>=2`, sorting takes `O(n log n)` work. The reusable scratch holds `n` integers and recursion uses `O(log n)` active calls, so additional space is `O(n)`. Empty/singleton inputs take fixed work and need no element reads or scratch writes.

### How do preparation and updates change the choice?

For `q` queries on an unchanged snapshot, linear scans can require `O(q*n)` work. Merge sorting once and then using binary search requires `O(n log n + q log(n+1))` for `n>=2`. Constants, early matches, and update work still matter. An array insertion may shift `O(n)` values. Do not state that sorting is always worthwhile.

A balanced AVL tree supports generalized search/update in `O(log(n+1))`. A hash table with `b` buckets has expected chain-search work `O(1+n/b)` under suitable distribution and worst-case `O(n)`. A min-heap exposes its minimum in `O(1)` and removes it in `O(log n)`; arbitrary-key search can take `O(n)`. These are generalized workload comparisons. Earlier fixed-capacity labs still have their own capacities and input contracts.

## Glossary

The names below describe the operations and conditions already traced.

| Term | Meaning here |
| --- | --- |
| linear search | Inspect positions in order until the first match or the end |
| first match | The smallest matching index in the array being searched |
| nondecreasing order | Each value is no smaller than its predecessor; duplicates are allowed |
| binary search | Repeatedly narrow an ordered candidate interval |
| half-open range | `[lo,hi)` includes `lo` and excludes `hi` |
| insertion sort | Insert each next value into an ordered prefix |
| merge sort | Order smaller ranges, then combine them |
| stable sort | Preserve the original relative order of equal-key records |
| scratch buffer | Separate caller-owned workspace reused during merges |
| invariant | A fact retained as each loop or recursive step progresses |
| preparation cost | Work performed before later queries can use a method |
| workload | The mix of lookups, updates, ordering, and selection requests |

## Coding Plan

Implement the already-traced actions in this order. The complete functions are supplied so class time can focus on prediction, tests, and selecting a method.

1. Scan from index 0 and return the first match, otherwise `-1`.
2. Narrow `[lo,hi)` using the safe midpoint. Keep equality on the left side. Check the closed boundary before reading.
3. Save each insertion key, shift only strictly larger values, and fill the gap.
4. Recursively divide half-open ranges. Merge into the nonoverlapping scratch array, taking the left value on equality, then copy back.
5. Keep an original copy for unsorted search and use independent copies for both sorts.
6. Check first duplicates, misses, empty/singleton inputs, signed extremes, boundaries, and repeated calls. Compare sorting output with an independent oracle and preserve the tagged tie explanation.

## C Code

The complete current `lab.c` follows. Each public function requires `0<=n<=SEARCH_SORT_CAPACITY` (64) and access to `n` valid integers when `n>0`. Search does not mutate input. `binary_search_first` requires nondecreasing input. Sorts change only the first `n` values. `merge_sort` requires a separate writable scratch buffer of at least `n` integers with no overlap. The functions assume those conditions; they do not return invalid-input statuses. For `n==0`, pointers may be null because no array position is read or written.

```c
#ifndef MODULE_13_SEARCH_SORT_LAB_C
#define MODULE_13_SEARCH_SORT_LAB_C

#define SEARCH_SORT_CAPACITY 64

int linear_search(const int values[], int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (values[i] == key) return i;
    }
    return -1;
}

int binary_search_first(const int sorted[], int n, int key) {
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (sorted[mid] < key) lo = mid + 1;
        else hi = mid;
    }
    if (lo < n && sorted[lo] == key) return lo;
    return -1;
}

void insertion_sort(int values[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = values[i];
        int pos = i;
        while (pos > 0 && values[pos - 1] > key) {
            values[pos] = values[pos - 1];
            --pos;
        }
        values[pos] = key;
    }
}

static void merge_range(int values[], int scratch[], int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    merge_range(values, scratch, lo, mid);
    merge_range(values, scratch, mid, hi);
    int left = lo;
    int right = mid;
    int out = lo;
    while (left < mid && right < hi) {
        if (values[left] <= values[right]) scratch[out++] = values[left++];
        else scratch[out++] = values[right++];
    }
    while (left < mid) scratch[out++] = values[left++];
    while (right < hi) scratch[out++] = values[right++];
    for (int i = lo; i < hi; ++i) values[i] = scratch[i];
}

void merge_sort(int values[], int scratch[], int n) {
    merge_range(values, scratch, 0, n);
}

#endif
```

The following complete caller uses the common six-value example. Compile this driver alone; it includes `lab.c`.

```c
#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void) {
    int values[] = {31, 23, 17, 8, 17, 42};
    int insertion[] = {31, 23, 17, 8, 17, 42};
    int scratch[6];
    assert(linear_search(values, 6, 17) == 2);
    printf("Original first index of 17: %d\n", linear_search(values, 6, 17));
    insertion_sort(insertion, 6);
    merge_sort(values, scratch, 6);
    const int expected[] = {8, 17, 17, 23, 31, 42};
    printf("Sorted:");
    for (int i = 0; i < 6; ++i) {
        assert(values[i] == expected[i] && insertion[i] == expected[i]);
        printf(" %d", values[i]);
    }
    printf("\nSorted first index of 17: %d\n", binary_search_first(values, 6, 17));
    assert(binary_search_first(values, 6, 17) == 1);
    assert(binary_search_first(values, 6, 99) == -1);
    puts("PASS: canonical searches and both sorts");
    return 0;
}
```

Run `make -C code` from the module root. The demonstration prints:

```text
Original first index of 17: 2
Sorted: 8 17 17 23 31 42
Sorted first index of 17: 1
PASS: canonical searches and both sorts
```

The [lab](lab.md), [evidence record](evidence_template.md), and [rubric](rubric.md) define one submission. Carry the ordering idea into Module 14; no DSU or MST implementation is required here.
