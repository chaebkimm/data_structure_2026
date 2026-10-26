# Hash Table Autopsy — A Position Is Not a Number

A bucket selects candidates. The stored payload determines how to check each
candidate. Investigate a wrong-answer change to the supplied two-sum search.
Use a hand trace or a separate driver copy; keep [lab.c](lab.c) unchanged.
The old `code/autopsy/faulty_delete_empty.c` is an optional demonstration for
the separate open-addressed library. It is outside this lab's assessment.

## 1. Predict the meaning of each integer

The current search contains these steps:

```c
int j = lnodes[j_node].data;
if (nums[j] == j_num) {
    answer[0] = i;
    answer[1] = j;
    return;
}
```

Begin with empty buckets and a freshly initialized pool. For target 0 at
current position 5, fill in `i`, `nums[i]`, `j_num`,
searched bucket, `j_node`, `lnodes[j_node].data`, and `nums[j]`.
Which values are positions? Which values are numbers?

Prediction: ________________________________________________________

## 2. Locate the first wrong comparison

Suppose a copied search changes only the condition to:

```c
if (j == j_num) {
```

Trace the same iteration with the original array. Which valid pair does the
changed condition reject? State the expected comparison and the changed
comparison using exact integers. Complete the copied search by hand or run
only the separate copy with a bounded fixture.

Observation: _______________________________________________________

First divergence: __________________________________________________

Explain why choosing the same bucket does not mean that either a node index
or its stored position equals the requested number.

____________________________________________________________________

## 3. Test the order of search and insertion

Use target 2. At current position 5, the number is 1. The supplied source
searches before saving position 5. Predict why position 5 cannot match itself.
Now imagine saving position 5 first. Which invalid pair could appear?

Prediction: ________________________________________________________

A regression should assert the supplied answer's bounds, different positions,
and target sum. For this fixed array and target, also assert the actual first
answer returned by the supplied source. Record that answer and explain it.

Regression and result: ______________________________________________

## 4. Repair and classify

Restore the comparison through `nums[j]`. Keep the search before the save.
Write a short explanation connecting each repair to the fact that the table
contains only earlier positions.

____________________________________________________________________

The fixtures demonstrate a wrong-answer defect. They do not establish an
out-of-bounds access or memory corruption. State the valid-index and
representable-arithmetic assumptions under which the comparison is evaluated.

____________________________________________________________________
