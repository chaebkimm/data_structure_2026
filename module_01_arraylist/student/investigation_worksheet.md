# Stage C — Investigation: Fixed-Capacity List Operations

Name: ____________________________
Date: ____________________________

Open this file after completing and preserving the Cognitive Pause.

## D. Trace one list through its operations

The array has ten slots. Initially, `size` is 3 and the list is
`[100, 200, 300]`. Only indexes below `size` contain current list items.

Complete the steps in order. Show the logical list, not the unused tail.

| Step | Request | Value read, if any | List afterward | Size afterward |
|---:|---|---|---|---:|
| 1 | Read index 1 | | | |
| 2 | Change index 1 to 500 | | | |
| 3 | Delete index 1 | | | |
| 4 | Insert 600 at index 1 | | | |
| 5 | Append 200 | | | |

1. Which steps change the count? ___________________________________
2. Which step moves a later item toward index 0? ___________________
3. Which step moves an item toward a higher index? __________________
4. Why must insertion shift from the final item toward the target?

   _________________________________________________________________

5. Why does deletion not need to erase the unused tail afterward?

   _________________________________________________________________

## E. Separate valid indexes from available storage

Start each case below with a new ten-slot array containing
`[100, 200, 300]`, with `size == 3`.

| Request | Accepted? | Reason |
|---|---|---|
| Read index 2 | | |
| Read index 3 | | |
| Update index -1 | | |
| Insert at index 3 | | |
| Insert at index 4 | | |
| Delete index 3 | | |

An **invariant** is a rule every valid state follows. Complete these rules:

- `size` is at least ______ and at most ______.
- Current items occupy indexes ______ through ______.
- The count, not a special integer value, decides ____________________.

Now consider a full list. What must append and insertion return, and which
array values may they change?

____________________________________________________________________

## F. Search for a value

A **linear search** checks current items from index 0 upward. It returns the
index of the first match. If no current item matches, it returns `-1`.
The result is an index, not an item value.

For this section, the current list is `[100, 600, 300, 600]` in ten slots.

1. Which indexes are examined when searching for 600? _______________
2. Which matching index is returned? _______________________________
3. How many items are examined when searching for 999? ______________
4. Suppose an unused slot contains 999 from an earlier operation.
   May the search count that value as a match? Explain.

   _________________________________________________________________

5. If a current item stores `-1`, is it valid data? How is that different
   from a search result of `-1`?

   _________________________________________________________________

## G. Count the work

Let `size` be the number of current items. Count item reads, writes, or moves;
do not use elapsed clock time. Assume successful operations use valid input
and that a removal starts with a nonempty list.

| Operation | Item reads, writes, or moves | Why? |
|---|---|---|
| Read or update a valid index | | |
| Search for a missing value | | |
| Append when space remains | | |
| Insert at index 0 | | |
| Delete the final item | | |
| Delete index 0 | | |
| Reject an addition when full | | |

Why does a ten-slot array still use ten slots when `size` is only 3?

____________________________________________________________________

## H. Connect the model to C

The lab uses ordinary arrays, integers, conditions, loops, and functions.

| C expression | Meaning |
|---|---|
| `int array[10];` | |
| `array[1]` | |
| `size` | |
| `capacity` | |
| `index >= 0 && index < size` | |

The mutating functions return the resulting count. A rejected request returns
the original count and leaves the array unchanged.

```c
size = int_list_append(array, size, capacity, 600);
```

Why must the caller save the returned count?

____________________________________________________________________

Why must the supplied capacity never exceed the array’s declared length?

____________________________________________________________________

## I. Exit ticket

1. What is the difference between size and capacity? ________________
2. Why is index `size` invalid for reading but valid for insertion when
   space remains? __________________________________________________
3. What stays unchanged after a full-list rejection? ________________
4. What does a search return when two current items match? __________
5. Why do unused tail values not belong to the list? ________________
