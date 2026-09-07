# Chapter 1 Supplement. Reading CPython's list

Python provides a list without asking the programmer to manage an array.
CPython still has to manage that array internally. This supplement follows
the path from a small C implementation to a teaching extraction of CPython's
implementation.

The example source files are available here:

- [`simplified_array_list.c`](../code/lecture/simplified_array_list.c)
- [`cpython_list_standalone.c`](../code/lecture/cpython_list_standalone.c)

The second program is based on CPython 3.12.11
[`Include/cpython/listobject.h`](https://github.com/python/cpython/blob/v3.12.11/Include/cpython/listobject.h)
and
[`Objects/listobject.c`](https://github.com/python/cpython/blob/v3.12.11/Objects/listobject.c).
It is an adaptation for teaching. It is not a byte-for-byte copy. Code for
the interpreter, error objects, garbage collection, and thread control has
been replaced with small stand-alone definitions.

## Thinking Logically

### What stops a fixed array list?

Suppose an array has four spaces. All four spaces contain active elements.

```text
size = 4
capacity = 4

index       0     1     2     3
          +----+----+----+----+
value     | 10 | 15 | 20 | 30 |
          +----+----+----+----+
```

There is no space for another element. The earlier fixed-capacity list must
reject an append.

A Python list behaves differently. It obtains a larger block of memory. It
copies or moves the existing elements into that block. It can then store the
new element.

An array list that can obtain a larger array while the program runs is a
**dynamic array list**.

### What information must the list remember?

The list needs three pieces of information:

- the address of its array;
- the number of active elements; and
- the number of available array positions.

The simplified program keeps them together in one C structure.

```c
struct ArrayList {
    int *data;
    size_t size;
    size_t capacity;
};
```

A `struct` groups related variables into one value. This chapter does not use
`typedef`, so each use includes the keyword `struct`. `data` is a pointer. A
pointer stores a memory address. Here, `data` stores the address of the first
integer in the allocated array.

`size` and `capacity` do not mean the same thing. `size` counts active
elements. `capacity` counts all available positions.

```text
size = 3
capacity = 4

index       0     1     2     3
          +----+----+----+----+
value     | 10 | 15 | 30 |  ? |
          +----+----+----+----+
             active       unused
```

The value in an unused position does not belong to the list.

### Which conditions must always remain true?

Every operation relies on the metadata and the array agreeing. The required
conditions are:

```text
0 <= size <= capacity
```

```text
data points to capacity integer positions,
or data is NULL when capacity is 0
```

```text
data[0] through data[size - 1] are active elements
```

A condition that must be true before and after every completed operation is
an **invariant**. An operation may temporarily change the state while it
works. It must restore the invariant before it returns.

### How does the simplified list grow?

An append first checks whether `size` equals `capacity`. Equal values mean
that every position is active.

The simplified list starts with capacity four. A later growth doubles the
capacity.

```text
0 -> 4 -> 8 -> 16 -> 32
```

The function `realloc` requests a different amount of memory for an existing
allocation. It may extend the same block. It may move the data to another
block. It returns the address of the resulting block.

The program must not discard the old address before checking whether the
request succeeded.

```c
new_data = realloc(list->data, new_capacity * sizeof(*new_data));
if (new_data == NULL) {
    return 0;
}
list->data = new_data;
list->capacity = new_capacity;
```

If allocation fails, `size`, `capacity`, and the active elements remain
unchanged.

### Why does CPython leave unused positions?

Growing the array for every append would repeatedly move the existing
elements. CPython therefore asks for more positions than the next append
immediately needs. The unused positions prepare for later appends.

The teaching extraction keeps CPython 3.12's growth calculation:

```c
new_allocated = (newsize + (newsize >> 3U) + 6U) & ~(size_t)3U;
```

The expression adds roughly one eighth of the requested size and rounds the
result to a multiple of four. Students do not need to memorize the bit
operations. The important decision is to reserve some unused positions.

CPython uses `allocated` where the simplified version uses `capacity`.

```c
struct PyListObject {
    struct PyObject **ob_item;
    size_t size;
    size_t allocated;
};
```

`struct PyObject **ob_item` is a pointer to an array of pointers. A Python list does
not store every Python object inside the array. It stores one pointer to each
object.

```text
PyListObject                      Python objects

ob_item ----> +---------+       +------+
              | pointer | ----> | "10" |
              +---------+       +------+
              | pointer | ----> | "15" |
              +---------+       +------+
              | pointer | ----> | "30" |
              +---------+       +------+
```

The list owns a reference to each active object. The teaching extraction uses
`Py_INCREF` when it stores another reference and `Py_DECREF` when it releases
one. These functions model CPython's reference-counting ownership rule.

### How does insertion preserve order?

Start with the values `10`, `20`, and `30`. Insert `15` at index one.

The elements at indexes one and two must move right. The movement begins at
the right side. Otherwise, moving `20` first would overwrite `30`.

```text
before: [10, 20, 30, ?]
move 30: [10, 20, 30, 30]
move 20: [10, 20, 20, 30]
insert:  [10, 15, 20, 30]
```

The active prefix remains contiguous. `size` increases from three to four.

### How does deletion preserve order?

Delete the value at index two from `[10, 15, 20, 30]`.

The later elements move left. Movement begins immediately after the deleted
position.

```text
before: [10, 15, 20, 30]
move 30: [10, 15, 30, 30]
size--:  [10, 15, 30, ?]
```

The old value in the unused position does not belong to the list. `size`
determines the active range.

### How do we obtain part of a list?

We want indexes one and two from `[10, 15, 30]`. We describe the range as
`[1, 3)`. The left boundary is included. The right boundary is excluded.

```text
source:       [10, 15, 30]
indexes:        0   1   2

range [1, 3):      15, 30
result:           [15, 30]
```

This result is a **sublist**. Python expresses the same operation with a
slice:

```python
result = source[1:3]
```

The result needs its own array. Changing the result's list positions must not
change the source list's positions.

The simplified list copies integers into the new array. The CPython-derived
list copies object pointers and increases their reference counts. Both lists
can refer to the same Python objects, but each list owns its own pointer
array.

## Calculating Efficiency

### How much work does indexed access perform?

The program calculates one position and reads one array element. Increasing
the list size does not add more steps to this access.

Indexed access has constant growth. Its time complexity is `O(1)`.

### How much work does insertion perform?

Inserting at index one in a three-element list moves two elements. Inserting
at index zero moves all three elements. Inserting at the end moves none.

For a list of `n` elements, the largest shift moves `n` elements. Insertion
therefore has `O(n)` time complexity.

### How much work does deletion perform?

Deleting index two from four elements moves one element. Deleting index zero
moves three elements.

For a list of `n` elements, the largest shift moves `n - 1` elements. Big O
ignores the fixed difference of one. Deletion has `O(n)` time complexity.

### Is append always one step?

An append with unused capacity performs one array write. That append is
`O(1)`.

An append to a full list must enlarge the allocation. Moving `n` existing
element pointers takes work proportional to `n`. That individual append is
`O(n)`.

Growth reserves room for several later appends. Those later appends do not
move the earlier elements. When the expensive growth costs are divided over
a long sequence of appends, the average cost per append stays constant. This
method of analyzing a sequence is **amortized analysis**. Append has `O(1)`
amortized time.

The statement does not mean every append takes the same time. It describes
the cost per append across a long sequence.

### How much work does a sublist perform?

The range `[1, 3)` contains two elements. The program allocates two positions
and copies two elements.

If the selected range contains `k` elements, the loop performs `k` copies.
Sublist creation takes `O(k)` time. The result also occupies `O(k)` additional
space.

The source list may contain `n` elements while the selected range contains
only `k`. `O(k)` states the tighter relationship because elements outside the
range are not visited.

### Summary of costs

| Operation | Time | Additional space | Cause |
| --- | ---: | ---: | --- |
| Indexed access | `O(1)` | `O(1)` | Calculate one position |
| Append without growth | `O(1)` | `O(1)` | Write one element |
| One append with growth | `O(n)` | implementation-dependent | Move or copy existing elements |
| Append across a sequence | `O(1)` amortized | spare capacity | Growth pays for later appends |
| Insert | `O(n)` | `O(1)` | Shift a suffix right |
| Delete | `O(n)` | `O(1)` | Shift a suffix left |
| Sublist of length `k` | `O(k)` | `O(k)` | Allocate and copy `k` elements |

## Glossary

### Dynamic array list

An array-backed list that can replace its storage with a larger allocation
while the program runs.

### Invariant

A condition that must hold before and after every completed operation. The
main array-list invariant is `0 <= size <= capacity`.

### Allocation

A block of memory obtained while the program runs.

### Pointer

A value that stores a memory address.

### Structure

A C value declared with `struct` that groups related fields.

### Reference count

The number of owned references to a Python object in the teaching model. A
new list reference increases the count. Releasing a list reference decreases
the count.

### Half-open range

A range that includes its left boundary and excludes its right boundary.
`[1, 3)` contains indexes one and two.

### Sublist

A new list containing the elements selected from a range of another list.

### Amortized cost

The cost per operation after distributing occasional expensive work across a
long sequence of operations.

## Coding Plan

### Initialize an empty list

- Set the array pointer to `NULL`.
- Set `size` to zero.
- Set `capacity` or `allocated` to zero.
- Check the invariant.

### Grow the allocation

- Check whether growth is needed.
- Calculate a larger capacity.
- Check that the byte calculation cannot overflow.
- Request the new allocation with `realloc`.
- Keep the old state if the request fails.
- Store the new pointer and capacity if the request succeeds.

### Append an element

- Compare `size` with the capacity.
- Grow when no unused position remains.
- Store the element at index `size`.
- Increase `size`.

### Insert an element

- Check that the index is between zero and `size`.
- Grow when no unused position remains.
- Shift the suffix right, starting at the end.
- Store the new element.
- Increase `size`.

### Delete an element

- Check that the index is less than `size`.
- Save or release the removed object reference when required.
- Shift the suffix left.
- Decrease `size`.

### Create a sublist

- Clip `low` and `high` to the source size.
- Make an empty range when `high` is less than `low`.
- Calculate `count` as `high - low`.
- Allocate exactly `count` result positions.
- Copy the selected elements in order.
- Set the result size and capacity to `count`.

### Destroy a list

- Release every owned object reference when required.
- Release the array allocation with `free`.
- Restore the empty-list state.

## C Code

### The simplified representation

```c
struct ArrayList {
    int *data;
    size_t size;
    size_t capacity;
};
```

The invariant check states the relationship between these three fields.

```c
static int array_list_invariant(const struct ArrayList *list)
{
    return list != NULL && list->size <= list->capacity &&
        ((list->capacity == 0U) == (list->data == NULL));
}
```

### Growing the simplified list

```c
static int array_list_grow(struct ArrayList *list)
{
    size_t new_capacity;
    int *new_data;

    assert(array_list_invariant(list));
    new_capacity = list->capacity == 0U ? 4U : list->capacity * 2U;
    if (new_capacity < list->capacity ||
        new_capacity > SIZE_MAX / sizeof(*new_data)) {
        return 0;
    }

    new_data = realloc(list->data, new_capacity * sizeof(*new_data));
    if (new_data == NULL) {
        return 0;
    }
    list->data = new_data;
    list->capacity = new_capacity;
    assert(array_list_invariant(list));
    return 1;
}
```

The first condition detects arithmetic overflow while doubling. The second
condition checks whether the number of bytes can be represented.

### Appending to the simplified list

```c
static int array_list_append(struct ArrayList *list, int value)
{
    assert(array_list_invariant(list));
    if (list->size == list->capacity && !array_list_grow(list)) {
        return 0;
    }
    list->data[list->size] = value;
    list->size += 1U;
    return 1;
}
```

The write uses the old value of `size` as the first unused index. Increasing
`size` makes the stored value active.

### Inserting into the simplified list

```c
for (size_t i = list->size; i > index; i -= 1U) {
    list->data[i] = list->data[i - 1U];
}
list->data[index] = value;
list->size += 1U;
```

The loop moves from right to left. Each source is read before that source can
be overwritten.

### Deleting from the simplified list

```c
for (size_t i = index; i + 1U < list->size; i += 1U) {
    list->data[i] = list->data[i + 1U];
}
list->size -= 1U;
```

The loop moves from left to right. Each later element closes one position of
the gap.

### Creating a simplified sublist

```c
count = high - low;
result->data = malloc(count * sizeof(*result->data));
if (result->data == NULL) {
    return 0;
}
result->size = count;
result->capacity = count;

for (size_t source = low, destination = 0U;
     source < high;
     source += 1U, destination += 1U) {
    result->data[destination] = list->data[source];
}
```

`source` walks through the selected range. `destination` begins at zero in
the new list.

### The CPython-derived representation

```c
struct PyListObject {
    struct PyObject **ob_item;
    size_t size;
    size_t allocated;
};
```

The array stores `struct PyObject *` pointers instead of integers. The same
size-versus-capacity model remains.

### Resizing with CPython's policy

```c
if (self->allocated >= newsize &&
    newsize >= (self->allocated >> 1U)) {
    self->size = newsize;
    return 0;
}

new_allocated =
    (newsize + (newsize >> 3U) + 6U) & ~(size_t)3U;
```

The first condition reuses the current allocation. A smaller allocation is
requested only after the list falls below half of the allocated size.

### Creating the CPython-derived sublist

```c
result->ob_item = malloc(count * sizeof(*result->ob_item));
if (result->ob_item == NULL) {
    return -1;
}
result->size = count;
result->allocated = count;

for (size_t source = low, destination = 0U;
     source < high;
     source += 1U, destination += 1U) {
    struct PyObject *item = self->ob_item[source];
    Py_INCREF(item);
    result->ob_item[destination] = item;
}
```

The loop copies pointers. It does not copy the objects. `Py_INCREF` records
that the result now owns another reference to each selected object.

### Following the complete trace

The CPython-derived stand-alone program performs these operations:

```text
append 10       [10]
append 20       [10, 20]
append 30       [10, 20, 30]
insert 15 at 1  [10, 15, 20, 30]
delete index 2  [10, 15, 30]
sublist [1, 3)  [15, 30]
```

From the `module_01_arraylist/student` directory, compile the simplified
implementation to an object file. It supplies helper functions and has no
`main()`, so it is not a stand-alone executable:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic \
  -c ../code/lecture/simplified_array_list.c \
  -o simplified_array_list.o
```

Then compile and run the CPython-derived program:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic \
  ../code/lecture/cpython_list_standalone.c \
  -o cpython_list_standalone
./cpython_list_standalone
```

Compare the two files in this order:

1. Find the three representation fields.
2. Find the invariant check.
3. Find the growth decision.
4. Find the right-shift loop for insertion.
5. Find the left shift for deletion.
6. Find the sublist copy loop.
7. State the cost of each loop using the number of visited elements.

The names and object-ownership rules differ. The underlying array-list
decisions remain the same.
