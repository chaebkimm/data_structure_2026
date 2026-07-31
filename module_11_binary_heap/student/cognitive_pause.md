# Stage B - Five-Minute Cognitive Pause

Read the starting definitions and state with the instructor before timing
begins. Then use no notes, slides, classmates, vocabulary file, or coding
tools. Preserve the first response when correction begins.

A min-Heap is a complete binary tree stored in an array. For index `i`, the
left child is `2*i+1`, the right child is `2*i+2`, and a nonroot record's
parent is `(i-1)/2`. A child exists only when its index is smaller than
`size`.

A child must not come before its parent. A smaller priority comes first;
equal priorities use smaller arrival sequence. Sift-up repairs toward index
0. Sift-down chooses the better existing child before comparing it with the
moved record.

The checker compares every nonroot record with its parent. At size `n`, it
adds zero comparisons when `n` is 0; otherwise, it adds exactly `n-1`.
Normal-operation comparisons and later checker comparisons must be reported
separately.

For every target, return to this exact starting state with
`comparison_count == 0`:

```text
capacity 8
size 5
next_sequence 5

index 0: 81/p1/s1
index 1: 27/p1/s3
index 2: 12/p2/s2
index 3: 54/p3/s0
index 4: 68/p4/s4
indexes 5 through 7: inactive
```

## Target 1 - Map and check

State:

1. the children of indexes 0 and 1;
2. the parent of index 4;
3. whether the starting state satisfies min-Heap order and why; and
4. the checker result and final comparison count.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Insert and repair upward

Return to the starting state. Insert `35/p1/s5`.

State:

1. its first index and every parent index tested;
2. every normal-operation comparison and swap;
3. the final active array; and
4. final size, next sequence, and normal-operation comparison count.

Do not call the checker in this target.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Extract and repair downward

Return to the starting state. Extract the minimum.

State:

1. the reported record and the final record moved into consideration;
2. which child is chosen at every step and why;
3. the final active array; and
4. the normal-operation comparison count, including the step with no right
   child.

Do not call the checker in this target.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `mapping`, `order`,
`upward`, `child choice`, `missing right`, or `measurement`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
