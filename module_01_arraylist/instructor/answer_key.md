# Instructor Answer Key — Module 1

The frozen textbook defines the conceptual answers. The final section records
the additional contracts required by the implementation lab.

## Initial Inquiry

### A. Start with one memory space

1. Index 2 contains `20`.
2. Indexes 0 through 3 contain stored items.
3. The computer calculates the address from the starting address, the index,
   and the size of one element.

### B. Keep the data packed together

After removing `50`, index 1 is empty. Move `20` from index 2 to index 1,
then move `30` from index 3 to index 2.

To insert `99` between `20` and `30`, move `30` right first. Moving
from the back prevents an unmoved value from being overwritten.

### C. When the memory space becomes full

Writing beyond the final allocated slot accesses memory outside the array.
Obtain a larger contiguous space, copy the values in order, add the new value,
release the old space, and continue using the new address.

## Memory-Space Reveal

- The ordered collection occupies indexes 0 through 3.
- Index 4 is allocated but unused.
- The space is full when the number of stored items equals the number of
  available slots.
- Golden rule: stored items begin at index 0 and follow without gaps.
- Expansion actions: obtain a larger space, copy in order, then release the old
  space after the new state is ready.

## Cognitive Pause

Expected new state:

```text
[10] [50] [20] [30] [99] [ ] [ ] [ ]
```

The old four-slot allocation is released after the four old values and the
new value are safely stored in the new space.

Growing by one slot would make the next addition trigger another complete
copy. Doubling leaves several empty slots, so complete copies happen less
often.

## Investigation Worksheet

### D. Invariant and shifts

- Golden rule: stored items begin at index 0 and have no empty gaps.
- After deleting index 1: `[10] [20] [30] [ ] [ ] [ ]`.
- Later items move left to close the gap.
- Insertion moves existing items right.
- Items move from back to front to avoid overwriting an item before it moves.

### E. Operation work

| Operation | Expected explanation |
|---|---|
| Find by index | Calculate one position directly |
| Find by value | Check items one by one; possibly all of them |
| Add at end with space | Write one item |
| Insert at front | Move every existing item right |
| Delete at end | No later item moves |
| Delete at front | Move every later item left |
| Expand | Copy every stored item |

### F. Doubling

One-slot growth immediately becomes full again. Doubling creates several
empty slots and spreads expansions farther apart. Across many additions, the
total copying grows in proportion to the number of items added, so the
average work per addition stays small.

### G. C connection

| Feature | Job |
|---|---|
| `sizeof` | Report the byte size of a type or value |
| pointer | Store a memory address |
| `malloc` | Request a contiguous memory block |
| `NULL` | Report that no usable address was returned |
| `free` | Release an allocated memory block |

Expansion order:

1. obtain a larger memory space;
2. copy every stored item in order;
3. add the new item;
4. start using the new memory space;
5. release the old memory space.

Accept steps 4 and 5 in the opposite order only when the student's description
clearly preserves the new address before freeing the old allocation.

## Lab implementation extension

The lab uses:

```c
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;
```

This maps the textbook model into one C object:

- `data` is the starting address;
- `size` tracks stored items;
- `capacity` tracks allocated slots.

Required lab conditions:

- `size <= capacity`;
- zero capacity uses the reset state `{NULL, 0, 0}`;
- logical elements occupy `[0, size)`;
- checked access requires `index < size`;
- append obtains enough space before writing;
- failed operations preserve the previous valid list;
- destruction releases the allocation and resets the fields.

The reference implementation uses `realloc` rather than the textbook's
explicit `malloc`–copy–`free` sequence. Both express the same conceptual
move. The lab adds a temporary result, arithmetic checks, and status values
because production C code must report failure without corrupting the list.

Expected implementation costs:

| Operation | Cost |
|---|---:|
| Checked indexed access | `O(1)` |
| Append when space remains | `O(1)` |
| One append that expands | `O(n)` |
| Long sequence of doubling appends | amortized `O(1)` |
| Insert or remove near the front | `O(n)` |

These symbols are lab terminology attached to the work already counted in the
textbook; they are not required in the initial conceptual inquiry.
