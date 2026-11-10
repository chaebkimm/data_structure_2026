# Hash Table Autopsy — A Key Is Not Its Payload

A bucket selects candidates; key equality decides a match. Use a hand trace
or separate driver copy for these wrong-answer changes. Keep [lab.c](lab.c)
unchanged. The older `code/autopsy/faulty_delete_empty.c` demonstrates a
separate open-addressing problem and is outside the required assessment.

## 1. Predict the meaning of each integer

The current table search compares keys:

```c
if (hnodes[node].key == k) {
    return node;
}
```

The two-sum caller then recovers the earlier input position:

```c
int complement = target - nums[i];
int node = find(complement);
if (node != -1) {
    int j = hnodes[node].data;
    answer[0] = j;
    answer[1] = i;
    return;
}
```

Use original `nums` and target 0. At current position 5, list `i`,
`nums[i]`, complement, search bucket, returned node, node key, node data,
and `nums[j]`. Which are positions, which are values, and which select
node or bucket arrays?

Prediction: ________________________________________________________

## 2. Locate the first wrong comparison

Suppose a separate copied `find` changes only its equality check to:

```c
if (hnodes[node].data == k) {
```

At target 0 and `i = 5`, the requested key is -1, bucket is 14, and its
head is node 4 with key -1 and data 4. State the correct comparison and
changed comparison using exact integers. Which valid answer is rejected
at this iteration? Trace any remaining nodes reached by the changed search.

Also distinguish the lookup contract using initialized calls
`insert(12,120)`, `insert(27,270)`, and `insert(-3,-30)`. What should
`find(27)` return, and why would comparing payloads fail?

Observation: _______________________________________________________

First divergence: __________________________________________________

The same bucket proves neither matching keys nor equality between an input
position and its value. Explain this in your own words.

____________________________________________________________________

## 3. Test the order of lookup and insertion

For target 2 and `i = 5`, the current value is 1 and the complement is 1.
The supplied code searches before inserting. Explain why no stored entry
can represent position 5 then. Imagine inserting `(1,5)` first; which
invalid answer could `find(1)` now allow?

For the supplied source assert bounds, distinct positions, target sum, and
its actual first target-2 answer `{3,7}`. A separate fixture with a lone 5
and target 10 should miss; adding a second 5 should permit a valid pair.
Keep all arithmetic representable as `int` and restore custom input changes.

Regression or complete hand trace: __________________________________

## 4. Repair and classify

Restore key comparison in the copied `find`, read its returned node's data
for the answer position, and keep lookup before insertion. Explain each
step using the invariant that all table entries represent earlier positions.

____________________________________________________________________

These fixtures demonstrate wrong answers. They do not establish an
out-of-bounds access or memory corruption. State the initialized-table,
valid-chain, valid-position, and representable-arithmetic assumptions used
by the trace. Never copy the experimental defect into `lab.c`.

____________________________________________________________________
