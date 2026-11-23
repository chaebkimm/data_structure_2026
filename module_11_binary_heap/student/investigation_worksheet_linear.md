# Module 11 Investigation — Linear Response Format

Use this alternative to the [table worksheet](investigation_worksheet.md).
Respond in numbered prose or by dictation. Preserve each first prediction,
then check it with [lab.c](lab.c) and the [lab handout](lab.md).

## A. Build the heap

1. Load `[9, 6, 5]` and set `size = 3`. For each live index, give its value,
   parent if present, and existing children. Name the two inactive slots.
2. Give the first index visited by `heapify()`. Explain why each child
   subtree is already a heap. Give the index and value chosen by
   `priority_child(0)`, the index returned by `sift_down(0, 9)`, and the
   live array after 9 is stored.

Prediction ____________________    Checked trace ____________________

## B. Follow the two insertions

1. Continue from A. For `enqueue(3)` and then `enqueue(1)`, record the
   starting index, parent values copied down in order, final index of the
   inserted value, resulting array, and size.
2. Name two siblings in the full heap that could trade places while
   preserving heap order. Explain how the tree shape bounds the number
   of parents visited. Give the size condition for another insertion.

Response ___________________________________________________________

## C. Follow the first removal

1. Start with B's full heap. Trace the first `dequeue()` inside
   `heap_sort`. Give the saved root, replacement value, reduced size, child
   copied to the root, final index of the replacement, and live array.
2. Which child does the sift consider next? Give the comparison that
   stops it, the tie rule for two equal children, and the caller's size
   condition for removal.

Response ___________________________________________________________

## D. Finish the sort

1. Continue the same sort. For removals 1 through 5, starting with the
   removal in C, list the returned root, remaining live heap, and written
   output prefix.
2. Explain the child-index check on the singleton removal. Explain why
   `heap_sort` records `old_size`, and give the final `size`.

Response ___________________________________________________________

## E. Test your predictions

Use the [student driver](../code/tests/test_lab_student.c) for the three
original cases in the handout. For each, give your input, prediction, and
observed result in the [evidence record](evidence_template.md) or in prose.

1. Interleave insertions and a removal with duplicate and negative values.
2. Heapify four values so the last parent promotes its only child.
3. Sort empty, singleton, and full heaps into a separate array. Check the
   output and final size. Check that sorting an empty heap preserves a
   known value in the output array.

Attach the build and test output. Identify one comparison or array write
that confirmed or changed an initial prediction.

Evidence ___________________________________________________________
