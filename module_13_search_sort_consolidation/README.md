# Module 13 — Searching, Sorting, and Consolidation

After maintaining search trees in Module 12, compare the whole workload: finding a key, arranging a snapshot, maintaining order, and selecting the next item. Module 13 traces and tests a supplied implementation of linear search, first-match binary search, insertion sort, and merge sort. Consolidation connects those choices to the earlier arrays, lists, hash tables, AVL trees, heaps, and graph frontiers. Module 14 connects ordering to Kruskal’s sorted-edge scan and Prim’s minimum-Heap frontier.

## Read and teach the current lesson

| Material | Purpose |
| --- | --- |
| [English textbook](student/textbook.md) · [Korean textbook](student/textbook_korean.md) | One flow from finding a value through sorting and workload selection |
| [Class workbook](student/class_material.md) | Predictions, traces, tagged ties, and corrections |
| [Concept slides](student/ppt_material.md) · [Lab slides](student/ppt_lab_material.md) | Board scenes and source walkthrough |
| [lab.c](student/lab.c) · [lab_driver.c](student/lab_driver.c) | Complete implementation and runnable six-value example |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | One combined Week 13 artifact |
| [Vocabulary](student/vocabulary.md) · [Models](diagrams/search_sort_models.md) | Names and equivalent range/merge diagrams |
| [Instructor plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_13.md) | One 180-minute lesson |

## Source and caller contract

Use `0<=n<=SEARCH_SORT_CAPACITY` (64). Positive-size arrays contain at least `n` accessible integers. `linear_search(values,n,key)` accepts any order; `binary_search_first(sorted,n,key)` requires nondecreasing order. Both return the smallest matching index in the array being searched, or `-1`, without modifying it. Sorting can change that index.

`insertion_sort(values,n)` and `merge_sort(values,scratch,n)` sort the first `n` values in place. The merge scratch buffer has at least `n` writable integers and must not overlap the values array. It is reused across recursive calls; there is no dynamic allocation. For zero size no array access occurs and null pointers are permitted. Invalid sizes, insufficient buffers, unsorted binary-search input, and overlapping scratch are outside the caller contract, not checked rejection cases.

The common input is `[31,23,17,8,17,42]`. Original linear search for 17 returns 2. Both sorts produce `[8,17,17,23,31,42]`; first-match binary search returns 1. Missing keys return `-1`. Insertion shifts only strictly greater keys; merge takes the left key on equality. Explain stability using the original 17A/17B identities on paper. Integer output alone cannot show their order.

## Build, evidence, and delivery

From this module root run `make -C code`. Core tests compare sorting with an independent `qsort` oracle, search with a first-match scan, signed extremes, every size 0..64, duplicates, canaries, and repeated calls. Compile the driver/test file only; it includes `lab.c`.

One submission contains original search/sorting/boundary tests, preserved traces, tagged stability reasoning, a workload-selection table, compiler output, and a corrected prediction. The plan uses 35 minutes for retrieval/search, 55 for sorting, 25 for tests, 45 for consolidation, and 20 for correction/submission. There is no additional DSU, MST, or from-scratch data-structure assignment.

The [release manifest](release/release_manifest.md) describes a self-contained archive with exact student sources and tests. Generate it with `python release/prepare_student_release.py`. Instructor answers and plans are excluded.
