# Module 11 Evidence Record

Name ____________________    Date ____________________

Use this sheet or an equivalent written or dictated record for the
[lab handout](lab.md). If your [investigation worksheet](investigation_worksheet.md)
already contains a trace, attach it once and refer to it here.

## Build and test output

Record the command and actual output for each target. Include the
[student driver](../code/tests/test_lab_student.c) with your original cases.

| Target | Command | Result or attached output |
| --- | --- | --- |
| `lab-compile` | | |
| `core` | | |
| `student-tests` after adding your cases | | |

## Build and insertion traces

Start with `pq = [9, 6, 5]`, `size = 3`. Record which parent or child
values the sift copies, the index it returns, and the final live prefix.

| Operation | Prediction | Parent or child values copied | Returned index | Checked live array and size |
| --- | --- | --- | --- | --- |
| `heapify()` (one sift) | | | | |
| `enqueue(3)` | | | | |
| `enqueue(1)` | | | | |

## Removal and sorting traces

Use the full heap from the last row. On the first removal record the
replacement, which child moved up, and the comparison that ended repair.

Replacement __________    Child __________    Stop comparison __________

| Removal inside `heap_sort` | Predicted root | Returned root | Remaining live array | Written output prefix |
| ---: | --- | --- | --- | --- |
| 1 | | | | |
| 2 | | | | |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |

Why does the loop use the original size? _____________________________

Final heap size __________    Final output ___________________________

## Three original cases

Write the expected values before running your assertions. For case 3,
record a separate outcome for each starting size.

| Case | Inputs and calls | Expected result | Observed result |
| --- | --- | --- | --- |
| 1. Duplicate and negative values, remove once, insert again, then drain | | | |
| 2. Four-value build where the last parent promotes its only child | | | |
| 3a. Empty sort with a known value already in the output array | | | |
| 3b. Singleton sort | | | |
| 3c. Full five-value sort | | | |

Include final sizes, the remaining removal order for case 1, the heap
order and size for case 2, and the output contents for case 3. Identify
one observation that confirmed or changed a prediction.

Observation ________________________________________________________
