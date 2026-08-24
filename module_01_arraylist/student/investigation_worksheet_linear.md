# Investigation Worksheet — Linear Accessible Format

This version has the same targets as the standard worksheet without a response
table. It is suitable for screen readers, keyboard navigation, speech input,
or a plain-text response.

## D. Keep the invariant

Starting state: indexes 0 through 3 contain 10, 50, 20, and 30. Indexes 4 and
5 are empty.

### D1. Golden rule

State the golden rule for where stored items belong.

Response:

### D2. Delete

Delete the item at index 1. Describe the final packed state.

Response:

### D3. Deletion direction

Why must deletion move later items to the left?

Response:

### D4. Insert

Insert 99 at index 2. In what direction must existing items move?

Response:

### D5. Safe insertion order

Why must insertion move items from the back toward the target position?

Response:

## E. Compare operations

For each operation, describe how its work changes as the amount of stored data
grows and explain why.

### E1. Find by index

Response:

### E2. Find by value

Response:

### E3. Add at the end when space remains

Response:

### E4. Insert at the front

Response:

### E5. Delete at the end

Response:

### E6. Delete at the front

Response:

### E7. Expand the memory space

Response:

## F. Explain doubling

### F1. One-slot growth

Why would adding only one new slot cause repeated copying?

Response:

### F2. Doubling

Why does doubling make expansion happen less often?

Response:

### F3. Average work

Across many additions, what happens to the average work for one addition?

Response:

## G. Connect the idea to C

### G1. sizeof

What job does `sizeof` perform?

Response:

### G2. Pointer

What does a pointer store?

Response:

### G3. malloc

What job does `malloc` perform?

Response:

### G4. NULL

What does `NULL` tell the program after a memory request?

Response:

### G5. free

What job does `free` perform?

Response:

### G6. Expansion order

Place these actions in order: copy every stored item; obtain a larger memory
space; release the old memory space; start using the new memory space; add the
new item.

Response:

## H. Exit ticket

### H1. Direct indexing

Why can an index locate an item directly?

Response:

### H2. Value search

Why does searching by value require checking items one by one?

Response:

### H3. Expansion condition

What condition means expansion is required?

Response:

### H4. Safe release

What must happen before the old memory space is freed?

Response:
