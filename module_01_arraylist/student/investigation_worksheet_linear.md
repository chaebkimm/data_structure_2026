# Investigation Worksheet — Linear Accessible Format

## How to use this version

This version has the same targets as the standard investigation without
response tables or long blank lines. Open it after completing and preserving
the Cognitive Pause.

## D. Valid and invalid states

For address `A` below, assume `A` is live, uniquely owned, and points to an
allocation large enough for the stated capacity.

### D1. Canonical empty state

`data` is `NULL`; `size` is 0; `capacity` is 0.

Classification and reason:

### D2. Missing storage

`data` is `NULL`; `size` is 1; `capacity` is 1.

Classification and reason:

### D3. Partially occupied allocation

`data` is address `A`; `size` is 3; `capacity` is 4.

Classification and reason:

### D4. Too many logical elements

`data` is address `A`; `size` is 5; `capacity` is 4.

Classification and reason:

### D5. Reserved empty list

`data` is address `A`; `size` is 0; `capacity` is 4.

Classification and reason:

### D6. Limits of field inspection

Without the assumption above, what facts about address `A` cannot be proven
from the three field values alone?

Response:

### D7. Full invariant

State the full representation invariant.

Response:

## E. Operation contracts

For each operation, give the valid request, state change, cost as the list
grows, and failure behavior.

### E1. Get

Response:

### E2. Append with spare capacity

Response:

### E3. Append requiring growth

Response:

### E4. Insert

Response:

### E5. Remove

Response:

## F. Growth ordering

### F1. Safe append order

Put these actions in a safe order: increment size; ensure capacity; write at
the old size; validate the list and request.

Response:

### F2. Failed growth

What must stay unchanged when growth fails?

Response:

### F3. Temporary allocator pointer

Why is a temporary pointer used with `realloc`?

Response:

## G. Complexity

Give the cost and a brief reason for each operation.

### G1. Get

Response:

### G2. Append with spare capacity

Response:

### G3. One append that grows

Response:

### G4. Geometric-growth append, amortized

Response:

### G5. Insert at the front

Response:

### G6. Remove at the front

Response:

### G7. Meaning of amortized

In one sentence, explain why amortized `O(1)` does not mean every append is
`O(1)`.

Response:

## H. Linked-node preview

### H1. Missing field name

Complete the field name:

```c
typedef struct Node {
    int value;
    struct Node *____________;
} Node;
```

Response:

### H2. Physical layout

Compare ArrayList and linked-node physical layout.

Response:

### H3. Indexed access

Compare indexed-access cost.

Response:

### H4. Local insertion

Compare local insertion after a known position.

Response:

### H5. Pointer risks

Give a major pointer risk for each representation.

Response:

## I. Exit ticket

### I1. Valid access

What condition must a valid element index satisfy?

Response:

### I2. Alias after moving growth

After successful moving growth, what is the status of a saved pointer into the
old allocation?

Response:

### I3. Failure preservation

What must a failed reserve operation preserve?

Response:

### I4. Append costs

Give the worst-case cost of one append and the amortized cost under geometric
growth.

Response:

### I5. Forward transfer

An ArrayList uses one contiguous block. Explain how separately linked objects
can represent a hierarchy now and arbitrary graph relationships later.

Response:

### I6. Open question

What question do you still have?

Response:
