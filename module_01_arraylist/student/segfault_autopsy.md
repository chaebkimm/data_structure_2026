# Bounds and Invariant Autopsy — One Slot Too Far

## Case

An **autopsy** is an investigation of the first incorrect step, not just the
final symptom. The supplied `code/autopsy/faulty_append.c` demonstration uses
this faulty condition:

```c
if (size <= capacity) {
    array[size] = value;
    return size + 1;
}
return size;
```

The usable capacity is 10 and all ten list positions are occupied:
`[100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]`.
The attempted append value is `1100`.

For safe observation, the demonstration declares one extra physical slot.
Index 10 starts with a **guard value** of `-999`. That guard is not usable
list capacity. It lets the demonstration show an incorrect write without
accessing memory outside its actual eleven-slot test array.

## Before running

Predict the returned count and the guard value after the faulty call.
Preserve your prediction.

____________________________________________________________________

## Incident report

### 1. Starting state

- usable capacity:
- current size:
- valid current-item indexes:
- guard index and initial value:

### 2. First incorrect condition

Why does `size <= capacity` accept a request that should be rejected?

____________________________________________________________________

### 3. Exact write

Which array index receives `1100`? What value occupied that position before
the write?

____________________________________________________________________

### 4. Broken invariant

State the returned size and explain which count rule it breaks.

____________________________________________________________________

### 5. Why the guard is not a fix

Would changing the real application from ten slots to eleven solve the
boundary-check defect? Explain what would happen when that new capacity
became full.

____________________________________________________________________

Why might this deliberately guarded demonstration finish normally even
though the list contract was broken?

____________________________________________________________________

### 6. Repair

State the corrected acceptance condition. Explain what the function must
return and preserve when the list is full.

____________________________________________________________________

### 7. Regression tests

A **regression test** checks that a repaired error does not return. Write one
test for the last available slot and one for a full-list rejection.

1. _________________________________________________________________
2. _________________________________________________________________

## After observation

Label each correction `bounds`, `count`, or `unchanged state`.

The evidence that changed or confirmed my model was:

____________________________________________________________________
