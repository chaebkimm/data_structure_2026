# Stage C — Investigation: Linear Accessible Format

This version has the same targets as the standard worksheet without response
tables. It is suitable for screen readers, keyboard navigation, speech input,
or a plain-text response.

Open it after completing and preserving the Cognitive Pause.

## D. Trace one list through its operations

The array has ten slots. Initially, `size` is 3 and the current list is
100, 200, 300. Only indexes below `size` contain current items.

### D1. Operation sequence

For each step, state any value read, the logical list afterward, and the new
size. Apply the steps in order:

1. Read index 1.
2. Change index 1 to 500.
3. Delete index 1.
4. Insert 600 at index 1.
5. Append 200.

Response:

### D2. Count changes

Which steps change the count?

Response:

### D3. Movement direction

Which step moves a later item toward index 0? Which step moves an item toward
a higher index?

Response:

### D4. Insertion order

Why must insertion shift from the final item toward the target?

Response:

### D5. Unused tail

Why does deletion not need to erase the unused tail afterward?

Response:

## E. Separate valid indexes from available storage

### E1. Independent requests

Start each case with a ten-slot array containing 100, 200, 300 and `size == 3`.
Classify each request and explain:

1. Read index 2.
2. Read index 3.
3. Update index -1.
4. Insert at index 3.
5. Insert at index 4.
6. Delete index 3.

Response:

### E2. Invariant

An invariant is a rule every valid state follows. State the smallest and
largest valid size. State which indexes contain current items. Explain why
the count, not a special integer value, decides list membership.

Response:

### E3. Full-list rejection

What must append and insertion return for a full list? Which array values
may they change?

Response:

## F. Search for a value

A linear search checks current items from index 0 upward and returns the
index of the first match. It returns `-1` if no current item matches. The
result is an index, not an item value.

Use the current list 100, 600, 300, 600 in ten slots.

### F1. First match

Which indexes are examined when searching for 600, and which is returned?

Response:

### F2. Missing value

How many current items are examined when searching for 999?

Response:

### F3. Unused matching value

Suppose an unused slot contains 999 from an earlier operation. May the search
count that value as a match? Explain.

Response:

### F4. Negative data

If a current item stores `-1`, is it valid data? How is that different from a
search result of `-1`?

Response:

## G. Count the work

For each operation, count item reads, writes, or moves and explain. Do not
use elapsed clock time. Assume successful operations use valid input and that
a removal starts with a nonempty list.

1. Read or update a valid index.
2. Search for a missing value.
3. Append when space remains.
4. Insert at index 0.
5. Delete the final item.
6. Delete index 0.
7. Reject an addition when full.

Response:

Why does a ten-slot array still use ten slots when `size` is only 3?

Response:

## H. Connect the model to C

### H1. Expressions

Explain each expression:

1. `int array[10];`
2. `array[1]`
3. `size`
4. `capacity`
5. `index >= 0 && index < size`

Response:

### H2. Returned count

Mutating functions return the resulting count. Rejection returns the original
count and leaves the array unchanged. Why must the caller save the result in
`size = int_list_append(array, size, capacity, 600);`?

Response:

### H3. Declared array length

Why must the supplied capacity never exceed the array’s declared length?

Response:

## I. Exit ticket

1. What is the difference between size and capacity?
2. Why is index `size` invalid for reading but valid for insertion when space
   remains?
3. What stays unchanged after a full-list rejection?
4. What does search return when two current items match?
5. Why do unused tail values not belong to the list?

Response:
