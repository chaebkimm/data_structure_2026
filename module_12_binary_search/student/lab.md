# Module 13 Lab — Searching, Sorting, and Consolidation

Use the complete [lab.c](lab.c), [English textbook](textbook.md) or [Korean textbook](textbook_korean.md), and [workbook](class_material.md). Write predictions before running the code. Trace the supplied algorithms and add original tests; do not replace the lesson with four from-scratch implementations. Submit one artifact.

## 1. Which array does the returned index describe?

Keep the original values `[31,23,17,8,17,42]`. Predict `linear_search(values,6,17)` and a search for 99. Expected results are 2 and `-1`; input is unchanged. Copy the array independently for the two sorts.

After sorting, trace `binary_search_first` for 17 using half-open `[lo,hi)`. Record `(0,6,3)`, `(0,3,1)`, `(0,1,0)`, then the final boundary 1. Explain why equality changes `hi` rather than immediately returning. The sorted first position is 1. Distinguish original and sorted positions. Test a missing key below, between, and above stored keys.

## 2. Which values move, and which equal record stays first?

Predict all five insertion passes. The right-shift counts are 1, 2, 3, 2, 0: eight total. State that writes of the saved keys and bounds checks are separate work. Tag the original equal records as 17A at index 2 and 17B at index 4. Explain why strict `>` keeps A before B.

Trace merge division into `[31,23,17A]` and `[8,17B,42]`. After the halves are ordered, trace merging `[17A,23,31]` with `[8,17B,42]`. State when `<=` chooses the left equal record. Show the temporary output before it is copied back. Use a writable six-integer scratch buffer distinct from both value copies.

The code sorts integers. Matching sorted integers or a clean sanitizer run does not prove stability. Submit the tagged trace and cite the exact strict/equal comparison that preserves order. A record-valued stability experiment is optional, not another required implementation.

## 3. Which caller conditions are required?

Use only `0<=n<=64`, valid active storage, and nondecreasing input for binary search. Merge scratch is a separate writable array of at least `n` integers with no overlap. Functions do not validate these conditions. Empty inputs access nothing and may use null pointers. A singleton needs no movement. Negative values, duplicates, `INT_MIN`, and `INT_MAX` are valid keys. Avoid comparing keys by subtraction in an independent comparator because signed subtraction can overflow.

Do not run invalid-size, short-buffer, unsorted-binary-search, or overlapping-scratch calls as rejection tests. Describe their violated assumptions on paper. Preserve sentinel positions around active ranges to check that valid calls stay within their contract.

## 4. How do we build and add useful checks?

From the module root run:

```sh
make -C code core student-tests demo
```

Or compile the demonstration alone:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic student/lab_driver.c -o /tmp/module13_demo
/tmp/module13_demo
```

The demo prints:

```text
Original first index of 17: 2
Sorted: 8 17 17 23 31 42
Sorted first index of 17: 1
PASS: canonical searches and both sorts
```

Add three original groups in `code/tests/test_lab_student.c`: search results/input preservation; both sorts/order and multiplicity; empty/singleton/boundary/repeated-call behavior. Each group must state a prediction and the claim it checks. Use an independent result, not a second copy of the implementation. The supplied core checks use `qsort` only as a value-order/multiplicity oracle, not as a stable-sort reference. Where supported, add `-fsanitize=address,undefined -fno-omit-frame-pointer` to the normal compiler flags.

## 5. Which earlier method fits each workload?

For each scenario, choose one method, give a competing method, and explain preparation, query, update, ordering, and storage costs. Do not implement another old structure.

| Scenario | Required reasoning |
| --- | --- |
| One lookup in six unsorted records | Compare scanning with sorting first |
| Many exact lookups on a fixed snapshot | Compare sorted array/binary search with hash buckets and preparation |
| Frequent updates while retaining key order | Compare AVL maintenance with array shifts; state valid balance/distribution assumptions |
| Change a sequence after a known predecessor | Distinguish local links from value search or random indexed access |
| Repeated minimum selection | Explain why a heap root is useful and why arbitrary-key lookup differs |
| Explore graph relationships | Compare FIFO BFS, Stack DFS, and cost-ordered Dijkstra; distinguish traversal from exact-key search |

Connect ordered candidates to Module 14's supplied edge sorting. Do not assume DSU yet. Sorting keys or weights does not by itself establish graph connectivity.

Include the [evidence record](evidence_template.md), tests/output, tagged tie trace, operation counts, selection explanations, and one corrected prediction. Follow the [rubric](rubric.md). One Week 13 submission contains all parts.

PowerShell users can run `powershell -File code/build.ps1`; choose `-Target core`, `-Target student`, or `-Target demo`, and add `-Sanitize` where supported.
