# Module 11 Investigation Worksheet — Trace a Min-Heap

Name ____________________    Date ____________________

Use [lab.c](lab.c) and the [lab handout](lab.md). Predict each state before
checking the source or your driver. Keep the first prediction and record a
correction beside it. The [linear worksheet](investigation_worksheet_linear.md)
covers the same questions in numbered prose.

## A. Build the heap

Load `[9, 6, 5]` into `pq` as in `main` and set `size = 3`. For each
live index, list its existing relatives. Use a dash on paper for an absent
relative. Which two reserved indices lie outside the live prefix?

| Index | Input value | Parent index | Live child indices |
| ---: | ---: | --- | --- |
| 0 | 9 | | |
| 1 | 6 | | |
| 2 | 5 | | |

Trace `heapify()`. Where does the backward loop start? Why are its child
subtrees already heaps? Give the index and value selected by
`priority_child(0)`, the index returned by `sift_down(0, 9)`, and the
live array after the caller stores 9.

Prediction ____________________    Checked trace ____________________

## B. Follow the two insertions

Continue from A. Record each parent's value in the order it is copied down.
Give the index where the caller finally stores the new value.

| Call | Starting index | Values copied down | Final index | Live array and size |
| --- | --- | --- | --- | --- |
| `enqueue(3)` | | | | |
| `enqueue(1)` | | | | |

Which pair of siblings in the full heap could exchange places and preserve
heap order? Explain how the tree shape bounds the number of parents visited.
State the caller's size condition for another insertion.

Response ___________________________________________________________

## C. Follow the first removal

Start with B's full heap. Trace the first call to `dequeue()` inside
`heap_sort`. The saved replacement stays in the local variable `data`
while children move up.

| Saved root | Replacement | Reduced size | Child copied to the root | Final index of replacement | Live array after repair |
| --- | --- | --- | --- | --- | --- |
| | | | | | |

Which child does the sift consider next, and what comparison stops it?
How would the choice work for two equal children? State the caller's size
condition for removal.

Response ___________________________________________________________

## D. Finish the sort

Continue the same sort. Use the first removal from C for row 1.
Record only live heap entries and output slots written so far.

| Removal | Returned root | Live array after removal | Output prefix |
| ---: | --- | --- | --- |
| 1 | | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |
| 5 | | | |

Explain the child-index check on the singleton removal. Why does
`heap_sort` save `old_size` before the loop? Give the final `size`.

Response ___________________________________________________________

## E. Test your predictions

Use the [student driver](../code/tests/test_lab_student.c) for the three
original cases in the handout. Record the input, expected result, and
observed result for each in the [evidence record](evidence_template.md).

1. Interleave insertions and a removal using duplicate and negative values.
2. Heapify four values so the last parent promotes its only child.
3. Sort empty, singleton, and full heaps into a separate array. Check the
   output, final size, and preservation of a known output value in the empty case.

Attach the build and test output. Identify one comparison or array write
that confirmed or changed your initial prediction.

Evidence ___________________________________________________________
