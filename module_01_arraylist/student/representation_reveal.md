# Stage B — Representation Reveal: Ten Slots and One Count

Open this file only when the instructor releases it.

## 1. Separate capacity from size

The list needs storage and a count of how much storage it currently uses.

```c
int array[10];
int capacity = 10;
int size = 3;

array[0] = 100;
array[1] = 200;
array[2] = 300;
```

**Capacity** is the maximum item count: 10. **Size** is the current item
count: 3. The list occupies indexes 0 through 2. The remaining slots exist,
but the program must not read them as list items.

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---|---:|---:|---:|---|---|---|---|---|---|---|
| List value | 100 | 200 | 300 | unused | unused | unused | unused | unused | unused | unused |

An unused slot may contain an old value. Neither zero nor any other integer
marks an unused slot. The count determines which positions belong to the
list.

## 2. State the invariant

An **invariant** is a rule that every valid list state follows:

- `size` is between 0 and 10, including both limits.
- The current items occupy indexes 0 through `size - 1` in list order.
- There are no unused positions between those current items.
- Capacity stays 10 throughout this example.

When `size` is 0, the list has no valid item index. When `size` is 10, the
list is full.

Complete the sentence:

> A slot can be inside the array but outside the current list when
> ________________________________________________________________.

## 3. Distinguish the operations

Reading or updating an item requires `0 <= index < size`. Inserting allows
`index == size` because that position is immediately after the last item.
Insertion also requires `size < capacity`.

Searching for a value checks current items from index 0 upward and stops at
the first match. It must not examine unused slots.

## 4. Reject an addition when full

If `size == capacity`, append and insertion report that the list is full.
They do not write a value or change the count. A **rejected operation** leaves
the previous list unchanged.

Do not solve the Cognitive Pause until the instructor releases it.
