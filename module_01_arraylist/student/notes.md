# Student Notes — A List in a Fixed Array

Use these notes after the initial inquiry. The chapter’s main example uses
`int array[10]`, an item count named `size`, and a fixed capacity of 10.

## 1. Distinguish storage from current items

An array provides ten neighboring integer positions. The list uses only the
first `size` positions. With `size == 3`, indexes 0, 1, and 2 are current
items; indexes 3 through 9 are unused by the list.

The array still has ten slots after a deletion. Only the item count changes.
An unused slot may retain an earlier value. The program must not read it as a
current list item.

## 2. Keep the invariant

A valid list state follows these rules:

- `0 <= size <= capacity`;
- current items occupy indexes 0 through `size - 1` with no gaps; and
- those positions preserve list order, which need not be numerical order.

The example’s capacity remains 10. Every array passed to a function must
actually have at least the claimed number of slots.

Zero, negative numbers, and repeated values are valid data. No integer marks
an unused position. The count defines the current list.

## 3. Read, update, and search

`int_list_valid_index(size, capacity, index)` returns 1 only when the counts
are valid and `0 <= index < size`. Otherwise it returns 0.

After a successful check, `array[index]` reads or changes that item directly.
Reading or updating does not change `size`.

`int_list_find(array, size, capacity, value)` checks current items in index
order. It returns the first matching index, or `-1` if no item matches or the
counts are invalid. Its result is an index. A data value of `-1` can therefore
still be found at a nonnegative index.

## 4. Append, insert, and remove

An append writes at the old `size` when space remains. Insertion also allows
that final position, but can place the new item earlier in the sequence.

To insert in the middle, move items from the final current item toward the
target index. Moving in this order prevents an unread item from being
overwritten.

To remove an item, move every later current item one position toward index 0.
The count decreases by one. The inactive tail does not need to be erased.

The chapter’s sequence is:

```text
start:             [100, 200, 300]   size 3
update index 1:    [100, 500, 300]   size 3
remove index 1:    [100, 300]        size 2
insert 600 at 1:   [100, 600, 300]   size 3
```

Each row uses the same ten-slot array; only current items are shown.

## 5. Preserve state when a request is rejected

A full list has `size == capacity`. Append and insertion must reject the
request before writing or shifting anything. Invalid counts or indexes also
leave the entire array unchanged.

Each mutating function returns the new count on success or the original
count on rejection. The caller must save that result:

```c
size = int_list_append(array, size, capacity, 600);
```

No function in this module changes the capacity.

## 6. Count the work

Except for the rejection row, assume valid requests that succeed. Removal
starts with at least one current item.

| Operation | Item work |
|---|---|
| Read or update by valid index | Access one item |
| Find a value | Check up to `size` current items |
| Append with room | Write one item |
| Insert at index 0 | Move `size` current items |
| Remove the final item | Move no other items |
| Remove index 0 | Move `size - 1` items |
| Reject a full-list addition | Change no items |

## 7. C features used in the lab

- `int array[10]` declares ten integer slots.
- `array[index]` selects one slot.
- Conditions check counts and index limits before access.
- Loops shift or search current items.
- A function return value communicates a new count or a search index.
- `const` on the search function’s array parameter means that the function
  does not change the array through that parameter.
