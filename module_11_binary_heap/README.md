# Module 11 — Binary Heaps

How can a priority queue keep the smallest integer ready while moving only
a few values on each insertion or removal? Trace the five-slot min-heap in
[student/lab.c](student/lab.c) using the [lab handout](student/lab.md).

## Follow the example

Only the first `size` slots in `pq[CAPACITY]` are live. A smaller value
has higher priority. Every parent is less than or equal to its children,
so the minimum is at index 0 whenever the heap contains a value.

| Step in `main` | Live values in `pq` after the step | What moved? |
| --- | --- | --- |
| Load the input and set `size = 3` | `[9, 6, 5]` | The input is in level order and still needs repair. |
| `heapify()` | `[5, 6, 9]` | Child 5 moves up. The saved 9 goes into its slot. |
| `enqueue(3)` | `[3, 5, 9, 6]` | Parents 6 and 5 each move down one level. |
| `enqueue(1)` | `[1, 3, 9, 6, 5]` | Parents 5 and 3 each move down one level. |
| `heap_sort(sorted)` | `[]` | Five removals write `[1, 3, 5, 6, 9]` into `sorted`. |

`enqueue` requires `size < CAPACITY`. `dequeue` requires `size > 0`.
Each sift returns the index where its caller writes the saved value.
`heap_sort` takes a valid heap and a separate output array with room for the
initial live count. For a heap of size *n*, a single sift takes at most
O(log n) work, bottom-up construction takes O(n), and draining the heap
into the output array takes O(n log n) in the worst case.

## Build and submit

From the repository root, run

```sh
make -C module_11_binary_heap/code lab-compile core student-tests
```

The example in `main` returns silently. The [core driver](code/tests/test_lab.c)
checks the worked example and heap operations. Extend the
[student driver](code/tests/test_lab_student.c) with the three cases in
the handout. Submit the build and test output, your insertion and removal
traces, and the cases with their predicted results.

## Student materials

| Activity | Materials |
| --- | --- |
| Predict which value should leave first | [Inquiry](student/inquiry_prompt.md) or [linear inquiry](student/inquiry_prompt_linear.md) |
| Discuss the array and tree together | [Class workbook](student/class_material.md), [concept slides](student/ppt_material.md), [lab slides](student/ppt_lab_material.md) |
| Trace the worked example | [Investigation worksheet](student/investigation_worksheet.md) or [linear worksheet](student/investigation_worksheet_linear.md) |
| Look up a position, operation, or term | [Representation guide](student/representation_reveal.md), [English–Korean vocabulary](student/vocabulary.md) |
| Check a prediction or diagnose a wrong result | [Five-minute pause](student/cognitive_pause.md), [heap autopsy](student/binary_heap_autopsy.md) |
| Assemble the submission | [Evidence record](student/evidence_template.md), [rubric](student/rubric.md) |

The [English chapter](student/textbook.md) and [Korean chapter](student/textbook_korean.md)
trace the five-slot heap from construction through sorting and explain the cost of each operation.
