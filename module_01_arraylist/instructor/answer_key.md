# Instructor Answer Key — Module 1

The revised Chapter 1 model uses ten fixed array positions. The active list
occupies a gapless prefix, and capacity never changes.

## Stage A — Initial inquiry

### A. Distinguish the list from its storage

For `[100, 200, 300]` in a ten-position array:

1. index one stores `200`;
2. active indexes are `0`, `1`, and `2`;
3. size is `3`;
4. capacity is `10`; and
5. index two can be accessed directly after checking its range; earlier
   values do not need to be inspected first.

### B. Keep the data packed together

1. Removing `200` requires moving `300` from index two to index one.
2. The remaining list is `[100, 300]`, size two.
3. Before inserting `600` at index one, move `300` right to index two.
4. The resulting list `[100, 600, 300]` preserves requested list order; it
   does not sort the values.

### C. Full-list behavior

1. Index ten is beyond the last usable position, index nine.
2. Reject the request. In the lab API, return the original size.
3. All ten array values, size ten, and capacity ten remain unchanged.

Accept plain-language descriptions before students see the code. The key
claim is that an unsuccessful addition performs no write and no shift.

## Stage B — Representation reveal

```c
int array[10];
int size = 3;
int capacity = 10;
```

- Capacity counts all available positions.
- Size counts current list items.
- Current items occupy `[0, size)` with no gaps.
- A position at or beyond size is not a current item, even when it contains
  an old integer.
- A full list satisfies `size == capacity`.

## Cognitive Pause

### Target 1 — Interpret the count

The valid read indexes are zero, one, and two. Index three is inside the
physical array but outside the active list, so it cannot be read as a current
list item.

### Target 2 — Preserve list order

Removing index one moves `300` from index two to index one. The logical list
becomes `[100, 300]`, and size becomes two. The old value at index two need
not be erased because the new size excludes it from the list.

### Target 3 — Handle a full list

The append is rejected. The returned size is still ten, and all ten stored
values remain unchanged. Capacity is still ten.

## Stage C — Investigation

### D. Trace one list through its operations

| Step | Request | Value read | Logical list afterward | Size |
|---:|---|---|---|---:|
| 1 | read index 1 | `200` | `[100, 200, 300]` | 3 |
| 2 | change index 1 to 500 | none | `[100, 500, 300]` | 3 |
| 3 | delete index 1 | none | `[100, 300]` | 2 |
| 4 | insert 600 at index 1 | none | `[100, 600, 300]` | 3 |
| 5 | append 200 | none | `[100, 600, 300, 200]` | 4 |

1. Steps three, four, and five change the count.
2. Step three moves a later item toward index zero.
3. Step four moves an item toward a higher index.
4. Insertion moves back-to-front so an uncopied value is not overwritten.
5. Deletion need not erase the inactive tail because size determines which
   positions belong to the list.

### E. Valid indexes and available storage

Each case begins with size three and capacity ten.

| Request | Accepted? | Reason |
|---|---|---|
| read index 2 | yes | `0 <= 2 < 3` |
| read index 3 | no | index three is not active |
| update index -1 | no | negative indexes are invalid |
| insert at index 3 | yes | insertion may use the end position when room remains |
| insert at index 4 | no | it would leave a gap after the active prefix |
| delete index 3 | no | there is no active item there |

Invariant blanks:

- size is at least `0` and at most `capacity` (ten in this example);
- current items occupy indexes `0` through `size - 1`; and
- the count decides which positions are current list items.

Full append and insertion return the original size and change no array
value. An insertion does not shift anything before discovering that the list
is full.

### F. Linear first-match search

For `[100, 600, 300, 600]`:

1. searching for `600` examines indexes zero and one;
2. it returns index one;
3. searching for `999` examines all four active items;
4. an inactive `999` is ignored because its index is not below size; and
5. `-1` is valid stored data, but a returned search index of `-1` means no
   active match (or invalid metadata). These are different roles.

### G. Count the work

| Operation | Maximum active items checked or moved | Explanation |
|---|---:|---|
| read/update a valid index | 1 | directly access the selected position |
| search for a missing value | `size` | check every active item |
| append with room | 0 moved; 1 written | use the first inactive position |
| insert at index 0 | `size` moved | every existing item moves right |
| delete the final item | 0 moved | no later item exists |
| delete index 0 | `size - 1` moved | every later item moves left |
| reject a full addition | 0 checked/moved/written array items | compare counts and reject |

A ten-position array still occupies ten positions when size is three because
the declared capacity is fixed; size changes membership, not the storage
layout.

### H. Connect the model to C

| Expression | Meaning |
|---|---|
| `int array[10];` | declare ten adjacent integer positions |
| `array[1]` | the integer in position one |
| `size` | number of active list items |
| `capacity` | fixed number of usable array positions |
| `index >= 0 && index < size` | the index names an active item |

The caller must retain a mutator's returned count so later operations see the
correct active prefix. The supplied capacity must not exceed the actual
array length because the helpers cannot discover that length from the
argument.

### I. Exit ticket

1. Size counts current items; capacity counts all available positions.
2. Index size is the next empty list position, so it is not readable but is
   a valid insertion position when space remains.
3. A full-list rejection preserves every array value and the count.
4. Search returns the first matching active index.
5. Tail values are outside the active prefix determined by size.

## Lab contracts

The public API is:

```c
int int_list_valid_index(int size, int capacity, int index);
int int_list_append(int array[], int size, int capacity, int value);
int int_list_insert(
    int array[], int size, int capacity, int index, int value
);
int int_list_remove(int array[], int size, int capacity, int index);
int int_list_find(const int array[], int size, int capacity, int value);
```

Required metadata is `0 <= size <= capacity`, with an actual array at least
as long as capacity. The normal example uses capacity ten.

- `int_list_valid_index` returns one for valid metadata and an active index;
  otherwise zero. Use it before direct indexed reads or updates.
- `int_list_find` scans the active prefix and returns the first match, or
  `-1` for no match or invalid metadata.
- Append and insertion return size plus one on success.
- Removal returns size minus one on success.
- Every rejected mutation returns the original size and leaves the entire
  array unchanged.
- Insertion allows index size; read/update/removal do not.
- Removal need not clear the former last active position.

Students must assign each returned size back to their count variable. For
example:

```c
size = int_list_insert(array, size, capacity, 1, 600);
```

## Bounds and Invariant Autopsy

The guarded demonstration starts with ten active values, usable capacity ten,
and a guard value of `-999` in extra physical slot ten. Valid list indexes
are zero through nine. The wrong condition
`size <= capacity` accepts an append when size is ten.

Expected observations:

1. the test incorrectly accepts equality;
2. the appended `1100` overwrites `-999` in guard slot ten;
3. the returned size becomes eleven;
4. `size <= capacity` is now false; and
5. the real ten-position list contract has been violated even though the
   demonstration's eleven-position backing array avoids an actual invalid
   memory access.

The repair is to check `size < capacity` before writing. On rejection,
return the original size and preserve every value, including the guard used
by the test. The guard is not usable capacity and is not itself a repair.

Changing the real array to eleven usable positions would not repair the
comparison: once size reaches eleven, the wrong condition would accept an
attempted write at index eleven. The demonstration finishes normally because
its observed index-ten write is within the actual eleven-position fixture.

Required regression cases:

1. With size nine and capacity ten, append succeeds at index nine and returns
   ten without changing earlier values.
2. With size ten and capacity ten, append returns ten and preserves every
   value, including a test guard if present.

Further useful cases include a full insertion and a remove-then-append
sequence that reuses the reopened position without changing capacity.

## Efficiency answers

Let `n` be the number of active items.

| Operation | Cost |
|---|---:|
| checked indexed read/update | `O(1)` |
| first-match value search | `O(n)` worst case |
| append with room | `O(1)` |
| insert/remove near the front | `O(n)` |
| insert/remove at the end | `O(1)` |
| reject a full append/insert | `O(1)` |

## Assessment anchors

Use the 100-point student rubric. All six operations are core. Strong work
includes exact shift traces, valid-index reasoning, first-match behavior,
unchanged-state evidence for rejection, passing supplied tests, three useful
student tests, and a clear autopsy diagnosis. Extensions add only more edge
and sequence tests for the same operations.
