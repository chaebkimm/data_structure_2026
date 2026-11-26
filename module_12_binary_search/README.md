# Module 12 — Binary Search and BSTs

Use the [Chapter 12 guide](../instructor_guide/chapter_12.md) for the weekly scope. Trace binary search on sorted arrays, explain BST ordering, and compare search paths in skewed and balanced examples. Week 13 follows with [LLRB search and insertion](../module_13_llrb/README.md).

[Search textbook](student/textbook.md) · [한국어](student/textbook_korean.md) · [Current C source](student/lab.c)

The [search/sort workbook](student/class_material.md), [lab guide](student/lab.md), [driver](student/lab_driver.c), build, and archive are earlier resources. The following notes describe that earlier search/sort package.

## Existing search/sort source contract — reference only

Use `0<=n<=SEARCH_SORT_CAPACITY` (64). Positive-size arrays contain at least `n` accessible integers. `linear_search(values,n,key)` accepts any order; `binary_search_first(sorted,n,key)` requires nondecreasing order. Both return the smallest matching index in the array being searched, or `-1`, without modifying it. Sorting can change that index.

`insertion_sort(values,n)` and `merge_sort(values,scratch,n)` sort the first `n` values in place. The merge scratch buffer has at least `n` writable integers and must not overlap the values array. It is reused across recursive calls; there is no dynamic allocation. For zero size no array access occurs and null pointers are permitted. Invalid sizes, insufficient buffers, unsorted binary-search input, and overlapping scratch are outside the caller contract, not checked rejection cases.

The common input is `[31,23,17,8,17,42]`. Original linear search for 17 returns 2. Both sorts produce `[8,17,17,23,31,42]`; first-match binary search returns 1. Missing keys return `-1`. Insertion shifts only strictly greater keys; merge takes the left key on equality. Explain stability using the original 17A/17B identities on paper. Integer output alone cannot show their order.

## Existing search/sort build and release — pending alignment

From this module root, `make -C code` still runs the original search/sort
core checks, student checks, and demo. These targets do not implement the
Week 12 or Week 13 assessment. Existing tests cover sorting against `qsort`,
first-match scans, signed extremes, sizes 0..64, duplicates, canaries, and
repeated calls. Compile only the driver/test file when it includes `lab.c`.

The [existing release manifest](release/release_manifest.md) describes the
previous search/sort archive and awaits alignment. Its release script still
packages that lesson; this planning pass does not regenerate or relabel it.
