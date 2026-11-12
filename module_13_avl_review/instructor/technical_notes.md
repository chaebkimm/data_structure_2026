# Module 13 Technical Notes

The canonical implementation is [student/lab.c](../student/lab.c). It is an include-guarded teaching source without a main function. The [driver](../student/lab_driver.c) and each test file include it; compile those files individually rather than also linking lab.c.

## Public contract

`SEARCH_SORT_CAPACITY` is 64 for this lesson. Every function receives `n` in 0..64 and sufficient active storage. Linear search accepts any key order; binary first-match search requires nondecreasing order. Both return the smallest matching index in the searched array or -1 and never mutate it. Sorting changes only active values. Empty size performs no accesses, so null pointers are allowed only under that zero-size contract. For positive n, writable merge scratch contains at least n integers and must be completely nonoverlapping with values. Insufficient/overlapping storage, invalid n, and unsorted binary input are caller violations, not checked error-status cases.

## Invariants and arithmetic

Binary search uses `[lo,hi)`, starting at `[0,n)`. The safe midpoint is `lo+(hi-lo)/2`. Lower values move lo past mid; equality and greater values set hi=mid. The final `lo<n && sorted[lo]==key` relies on short-circuiting to avoid reading the excluded endpoint. The first-match contract is equivalent to finding the lower bound then checking equality.

Insertion keeps `[0,i)` ordered with its original multiset. Saving the key before right shifts prevents loss. Strict `>` preserves equal-key order. Merge recursively orders half-open ranges, uses left-on-`<=`, drains unused tails, and copies only `[lo,hi)` back. There are no key additions/subtractions in the algorithms, so all int values including INT_MIN/MAX are valid. The test oracle comparator uses relational comparisons rather than subtraction.

## Validation meaning

Core checks compare every length 0..64 using increasing, decreasing, all-equal, and deterministic signed duplicate inputs; add a canonical fixture and signed extremes. Independent first-match scans verify search results, `qsort` verifies value order/multiplicity, canaries verify writes stay within active ranges, and repeated sorts verify reusability of input/scratch. Explicit zero-size null calls establish no-access behavior. The student file is a smoke test and three-group starting point.

The oracle is not a stability oracle. Equal integers have no observable identities. Stability evidence is the paper A/B trace plus the exact strict/equal source rules. An optional record variant can test identities but is not part of this bounded lab.

## Costs and boundaries

Linear search is O(n) worst-case; binary is O(log(n+1)); both have O(1) extra state. Insertion is O(n^2) worst-case and O(n) best-case with O(1) extra state. For n>=2, merge sort uses O(n log n) work, O(n) caller scratch, and O(log n) active call frames; total extra space is O(n). Zero/singleton ranges return with fixed work. Reserve versus active space and preprocessing versus per-query work must be distinguished.

Module 13 retrieves prior structure contracts; it does not expand their fixed capacities or validation guarantees. Module 14 introduces DSU and spanning-tree selection. Its comparator and graph-edge sorting remain supplied, although the cost/tie-order reasoning transfers from this lesson.

## Release QA

Generate a fresh archive using [prepare_student_release.py](../release/prepare_student_release.py). Verify source/doc bytes and manifest entries; extract and run core/student/demo. Instructor files and build products must be absent. The exclusive-create ZIP mode rejects an existing destination. The archive imports no sibling module and therefore needs no repository checkout.
