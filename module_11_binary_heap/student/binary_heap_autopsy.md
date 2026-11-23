# Module 11 Autopsy — Find the First Wrong Step

Use the following hypothetical changes as paper traces. For each one,
compare the first wrong step with [lab.c](lab.c) and propose an assertion
for a test driver.

## What if sift-down always picks the left child?

Load `[9, 6, 5]` and set `size = 3`. In the real `heapify()`, record the
index chosen by `priority_child(0)` and the resulting array. Repeat on
paper with a helper that always returns the left child index. Identify
the parent and child that break heap order.

First difference ____________________    Assertion ____________________

## What if the caller forgets the final store?

Start with the valid heap `[5, 6, 9]`. In `enqueue(3)`, trace the parent
copies made by `sift_up`. Imagine the caller increments `size` but skips
`pq[pos] = data`. List the four live values. Which input disappeared, and
why would a check of parent–child order alone miss the loss?

First difference ____________________    Assertion ____________________

## What if the sort loop uses the shrinking size?

Start with `[1, 3, 9, 6, 5]`, size 5. On paper, change the loop condition
in `heap_sort` to `i < size`. Record `i` and the live `size` before each
condition check. List the output prefix when the loop stops and the values
still in the heap. Which assertions distinguish this from a complete sort?

First difference ____________________    Assertion ____________________
