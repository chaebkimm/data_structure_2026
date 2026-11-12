# Module 13 — AVL Rotations and Review

**Course-plan update — 2026-11-10.** Week 13 now continues
[Module 12's Binary Search and BSTs](../module_12_binary_search_bst/README.md) with AVL
repair and course review. Follow the
[14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
and [Chapter 13 planning summary](../instructor_guide/chapter_13.md).

Teaching-content alignment remains pending. Existing textbooks,
worksheets, lab guides, detailed lesson plans, tests, and releases await
alignment. The directory is now named `module_13_avl_review`, while the
search/sort source remains grouped in Module 13;
search references support Week 12, and full sorting instruction is optional.
The supplied indexed AVL source remains in Module 12. No revised student
release is supplied here.
Existing ZIP filenames and release-script defaults retain their original
names; archives have not been regenerated.

## Required learning and assessment outline

Retrieve Week 12's skewed BST, compute height and balance, and study LL/RR
before LR/RL repair. Keep every middle subtree reachable and preserve inorder.
Trace supplied AVL insertion, retain returned subtree roots, and refresh
stored heights from the lower nodes upward. AVL deletion is outside required
scope; no from-scratch AVL implementation is required.

Protect the final 60 minutes for course review, workload selection,
corrections, and submission. Compare arrays/lists, hash versus BST/AVL
lookup, Heap priority, DFS/BFS frontier control, and minimum-hop versus
weighted routes. Briefly discuss the cost of preparing and updating an
ordered snapshot. Insertion-sort and merge-sort instruction and implementation
are optional; Module 14 supplies and explains edge ordering and its comparator
without assuming those lessons.

One submission contains four rotation traces, insertion/link/height/balance
checks, comparison evidence, a workload-selection review memo, and a corrected
prediction. Reuse earlier evidence rather than implement earlier structures again.

| Required contact activity | Minutes |
|---|---:|
| Retrieve the skewed-tree problem; establish height and balance | 20 |
| LL/RR followed by LR/RL rotations, preserving ordering and middle subtrees | 55 |
| Guided AVL insertion: returned roots and bottom-up height updates | 30 |
| Rotation and insertion checks | 15 |
| Course review, workload selection, corrections, and submission | 60 |
| **Total** | **180** |

## Existing teaching resources — pending alignment

The search/sort materials below retain the previous lesson. Their weekly
labels and complete assignments await alignment; they are not the revised
Week 13 lab. The AVL materials also await alignment to their new weekly role.

| Existing material | Reference use |
| --- | --- |
| [Module 12 AVL textbook](../module_12_binary_search_bst/student/textbook.md) · [AVL lab](../module_12_binary_search_bst/student/lab.md) | Supplied AVL explanation and checks, still stored in Module 12 |
| [Module 12 AVL source](../module_12_binary_search_bst/student/lab.c) · [Code guide](../module_12_binary_search_bst/code/README.md) | Read-only source and unchanged builds for rotation/insertion evidence |
| [English search/sort textbook](student/textbook.md) · [Korean](student/textbook_korean.md) | Search reference for Week 12; sorting instruction optional |
| [Class workbook](student/class_material.md) | Previous search/sort traces and workload prompts |
| [Concept slides](student/ppt_material.md) · [Lab slides](student/ppt_lab_material.md) | User-owned references for the previous lesson |
| [Search/sort source](student/lab.c) · [Driver](student/lab_driver.c) | Unchanged complete search/sort example |
| [Lab](student/lab.md) · [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | Previous submission outline, not the revised Week 13 assignment |
| [Vocabulary](student/vocabulary.md) · [Models](diagrams/search_sort_models.md) | Previous search/sort reference materials |
| [Detailed lesson plan](instructor/lesson_plan.md) | Previous lesson; use the revised budget above |
| [Week 13 questions](../student_question_bank/week_13_search_sort_consolidation.md) | Existing question bank, pending alignment |

## Existing search/sort source contract — reference only

Use `0<=n<=SEARCH_SORT_CAPACITY` (64). Positive-size arrays contain at least `n` accessible integers. `linear_search(values,n,key)` accepts any order; `binary_search_first(sorted,n,key)` requires nondecreasing order. Both return the smallest matching index in the array being searched, or `-1`, without modifying it. Sorting can change that index.

`insertion_sort(values,n)` and `merge_sort(values,scratch,n)` sort the first `n` values in place. The merge scratch buffer has at least `n` writable integers and must not overlap the values array. It is reused across recursive calls; there is no dynamic allocation. For zero size no array access occurs and null pointers are permitted. Invalid sizes, insufficient buffers, unsorted binary-search input, and overlapping scratch are outside the caller contract, not checked rejection cases.

The common input is `[31,23,17,8,17,42]`. Original linear search for 17 returns 2. Both sorts produce `[8,17,17,23,31,42]`; first-match binary search returns 1. Missing keys return `-1`. Insertion shifts only strictly greater keys; merge takes the left key on equality. Explain stability using the original 17A/17B identities on paper. Integer output alone cannot show their order.

## Existing search/sort build and release — pending alignment

From this module root, `make -C code` still runs the original search/sort
core checks, student checks, and demo. These targets do not implement the
revised Week 13 assessment. Existing tests cover sorting against `qsort`,
first-match scans, signed extremes, sizes 0..64, duplicates, canaries, and
repeated calls. Compile only the driver/test file when it includes `lab.c`.

The [existing release manifest](release/release_manifest.md) describes the
previous search/sort archive and awaits alignment. Its release script still
packages that lesson; this planning pass does not regenerate or relabel it.
