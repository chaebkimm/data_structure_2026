# Module 11 Assessment Rubric

The [lab handout](lab.md) defines the submission. Use the traces, original
test cases, and build output to assess the following areas for a total of
100 points. Typed, linear, dictated, tactile, and verbal explanations are
equivalent.

| Area | Points | Evidence in the submission |
| --- | ---: | --- |
| Heap model | 15 | Distinguishes indices from values, capacity from live size, and identifies the parent–child rule that places a minimum at the root. |
| Bottom-up build | 20 | Traces `heapify()` on `[9, 6, 5]`, identifies the chosen child and returned index, and explains why child subtrees are ready before the parent. |
| Insertion | 15 | Traces `enqueue(3)` and `enqueue(1)` in order, showing each parent copied down, the final store, and the live array. |
| Removal | 15 | Identifies the saved root, replacement, reduced size, and child choice. Records the remaining heap after each removal. |
| Sorting | 15 | Gives the ascending output and final heap size. Explains why `heap_sort` uses a separate output array and the initial size. |
| Three original cases | 10 | Exercises interleaved operations with duplicates and negatives, four-value heap construction with a lone left child, and empty, singleton, and full sorts. Compares each result with a prediction. |
| Boundary reasoning | 5 | Gives valid size conditions for `enqueue` and `dequeue`. Checks that the empty sort preserves a known output value. |
| Reproducible evidence | 5 | Includes the student driver, build commands, test output, and enough input and state information to reproduce the traces. |

Noncompiling work may still earn reasoning credit from preserved traces
and explanations. Revision remains available under course policy.
