# Module 1 Fixed-Array Models

These models use ten fixed positions. Every diagram includes a text
equivalent. The active list is the prefix of positions before `size`.

## 1. Size and capacity

```text
index:       0     1     2     3    4    5    6    7    8    9
array:     [100] [200] [300] [ ]  [ ]  [ ]  [ ]  [ ]  [ ]  [ ]
active:    <------------- >
size: 3                                           capacity: 10
```

Text equivalent: indexes zero, one, and two contain the three active values
`100`, `200`, and `300`. Indexes three through nine are available but do not
belong to the list yet. Capacity is ten; size is three.

An empty drawing position means “outside the active list,” not necessarily
that its stored bits are zero. Reading a list item requires `index < size`,
not merely `index < capacity`.

## 2. Checked indexed read and update

```text
before: [100] [200] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
                ^
           index 1 is active

read array[1]: 200
write array[1] = 500

after:  [100] [500] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
size remains 3; capacity remains 10
```

Text equivalent: check `0 <= index && index < size` before using brackets.
Reading returns the selected value. Updating replaces that one active value;
it does not change the number of items.

## 3. Linear first-match search

```text
active values: [100] [600] [300] [600]
index:            0     1     2     3
target: 600

check index 0: no match
check index 1: match; return 1 and stop
```

Text equivalent: examine active items from index zero upward. Return the
first matching index. The second `600` is not visited after the first match
is found. If no active item matches, `int_list_find` returns `-1`.

## 4. Append into the first unused position

```text
before: [100] [200] [300] [ ]  [ ] [ ] [ ] [ ] [ ] [ ]
size: 3                    ^ next write at index size

append 400:
after:  [100] [200] [300] [400] [ ] [ ] [ ] [ ] [ ] [ ]
size: 4
```

Text equivalent: when `size < capacity`, place the new value at `array[size]`
and increase size by one. No existing active item moves.

## 5. Remove and close the gap

Starting from the updated textbook state:

```text
before: [100] [500] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
remove index 1
move:   [100] [300] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
size becomes 2
active: [100] [300]
```

Text equivalent: copy index two into index one, then reduce size from three
to two. The old value at index two may remain in the array, but it is outside
the active prefix and is not a third list item.

For a longer list, move later values left from front to back:

```text
array[index]     = array[index + 1]
array[index + 1] = array[index + 2]
... continue through the former last active item
```

## 6. Insert without overwriting

Insert `600` at index one into `[100, 300]`:

```text
before: [100] [300] [ ]   [ ] [ ] [ ] [ ] [ ] [ ] [ ]
shift:  [100] [300] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
write:  [100] [600] [300] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
size changes from 2 to 3
```

Text equivalent: first move the last active value from index one to index
two. Then write `600` at index one. Existing values must move right from back
to front so each source is copied before its position is overwritten.

For insertion at index one into `[10, 20, 30, 40]`:

```text
1. move 40: index 3 -> index 4
2. move 30: index 2 -> index 3
3. move 20: index 1 -> index 2
4. write the new value at index 1
5. increase size
```

## 7. Full means reject without mutation

```text
before:
[100] [200] [300] [400] [500] [600] [700] [800] [900] [1000]
size: 10; capacity: 10

request: append 1100
result: rejected; returned size is still 10

after:
[100] [200] [300] [400] [500] [600] [700] [800] [900] [1000]
```

Text equivalent: there is no usable index ten in the ten-position model.
Append and insertion must check fullness before any write or shift. The
capacity and all array contents remain unchanged after rejection.

## 8. Valid positions differ by operation

| Operation | Accepted position |
|---|---|
| read or update | `0 <= index < size` |
| remove | `0 <= index < size` |
| insert | `0 <= index <= size`, with `size < capacity` |
| append | exactly index `size`, with `size < capacity` |

Text equivalent: insertion may use the position immediately after the current
last item. A read, update, or removal cannot use that position because it does
not contain an active item yet.

## 9. Counting the work

Let `n` be the number of active items.

| Operation | Work |
|---|---|
| checked read or update | `O(1)` |
| first-match value search | `O(n)` worst case |
| append with room | `O(1)` |
| insert at the end | `O(1)` |
| insert near the front | `O(n)` shifts |
| remove the last item | `O(1)` |
| remove near the front | `O(n)` shifts |
| reject a full append/insert | `O(1)` |

The teaching array has capacity ten. Counting work in terms of `n` explains
which operations depend on the number of stored items, even within that
small fixed limit.
