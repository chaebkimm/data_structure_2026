# Module 11 Lab — Binary Heaps

Trace the five-slot integer min-heap in [lab.c](lab.c). By the end of the
lab, you should be able to predict which values move during insertion and
removal, build a heap from an unordered array, and use it to sort integers.

## Build and run

From the `module_11_binary_heap` directory, run the following commands.

```sh
make -C code lab-compile
make -C code core
make -C code student-tests
```

The supplied program has its own `main`. It runs the worked example and
returns silently. The test drivers rename that `main` when including the
source so they can call the heap functions and check their results. Add
your own cases to the [student test driver](../code/tests/test_lab_student.c).

## 1. Build a heap from three values

The program stores the live values in `pq[0]` through `pq[size - 1]`.
The root is at index 0. Each parent's value must be less than or equal to
each child's value. `compare(x, y)` returns true when `x < y`.

Start as `main` does. Load `[9, 6, 5]` into the first three slots and set
`size = 3`. Predict the root after `heapify()`. For any heap with at least
two values, the loop starts at `parent(size - 1)`, the last parent. It works
back toward the root so that each child subtree is already a heap when its
parent is repaired.

For this input there is one parent to repair. Record which child
`priority_child(0)` selects and which index `sift_down(0, 9)` returns.
Compare your prediction with the first row below.

## 2. Trace two insertions

Call `enqueue` only when `size < CAPACITY`. Each insertion starts at index
`size`. For a non-root index `i`, the parent is at `(i - 1) / 2`.
`sift_up` copies each larger parent down and returns the index where
`enqueue` writes the new value. Predict each row before checking it.

| Operation | Live array after the call | Size |
| --- | --- | ---: |
| `heapify()` on `[9, 6, 5]` | `[5, 6, 9]` | 3 |
| `enqueue(3)` | `[3, 5, 9, 6]` | 4 |
| `enqueue(1)` | `[1, 3, 9, 6, 5]` | 5 |

For each insertion, list the two parents copied down and the index where
the new value lands. Identify a pair of siblings whose values could be
exchanged while preserving heap order.

## 3. Trace removal and sorting

Call `dequeue()` only when `size > 0`. It saves the root, reduces `size`,
and takes the former last value as the replacement. At index `i`, the
candidate child indices are `2*i + 1` and `2*i + 2`. A child exists
when its index is below the new size. With two children, `priority_child`
selects the smaller one, choosing the left child on a tie. With no children,
it returns `-1`, so the `c != -1` check stops the sift before it reads `pq[c]`.

Trace the first removal from the five-element heap above. Record the
returned value, the replacement, the child copied to the root, and the live
array after repair. Repeat on paper until the heap is empty.

In `main`, `heap_sort(sorted)` performs those removals and writes their
results into a separate array from left to right. It starts with a valid
heap and an output array large enough for the initial size. Check that the
result is `[1, 3, 5, 6, 9]` and the final size is zero. Explain why the
loop uses `old_size` as its bound.

## Evidence to submit

Submit the build and test output, your insertion and removal traces, and
three original cases in the student driver. For each case, record the input
and expected result before running it.

1. Insert duplicate and negative values, remove the minimum, then insert
   another value. Check the remaining removal order and final size.
2. Heapify an array with four values. Choose values that make the last
   parent promote its only child. Check the heap order and live size.
3. Sort an empty heap, a singleton, and a full heap into a separate output
   array. Check the written values and final size. For the empty case, give
   the output array a known value and check that it is preserved.
