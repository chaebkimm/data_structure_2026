# Week 1 — Keeping Data Together in One Place

The frozen Chapter 1 textbook defines the core scope. Questions about the
repository's `IntList` interface are grouped separately as lab extensions.

## Textbook vocabulary

| Term | Question |
|---|---|
| contiguous memory | What does it mean for memory positions to be next to one another? |
| array | What stays fixed after an array's memory has been set aside? |
| list | What does it mean for stored data to have an order? |
| ArrayList | How can an array represent a list? |
| dynamic array | What happens when its current memory space is full? |
| index | How does an index locate an item? |
| element | What is one stored item called? |
| invariant | Which placement rule must insertion and deletion preserve? |

## Core questions

### Memory and access

- Why can an item be found directly when its index is known?
- Why can searching for a value require checking every stored item?
- Which positions are part of the collection when the allocated space also
  contains unused slots?
- Why do stored items begin at index 0 in this design?

### Insertion and deletion

- After deleting the item at index 1, which items must move?
- Why does insertion shift items from back to front?
- How much work can insertion at the front require?
- How much work can deletion at the end require?

### Expansion

- What condition means that a new memory space is required?
- In what order should the old items be copied?
- When may the old memory space be released?
- Why would growing by only one slot cause repeated copying?
- Why does doubling make copying happen less often?
- Across many additions, why does the average work per addition remain small?

### C connection

- What does `sizeof(int)` report?
- What information does a pointer store?
- What does `malloc` return when it cannot provide the requested space?
- Why must allocated memory eventually be passed to `free`?
- Why is the pointer reset to `NULL` after the final `free` in the chapter?

## Lab-extension questions

These questions assess the supplied implementation task, not prerequisite
textbook understanding.

- How do the textbook's starting address and two tracking numbers map to
  `IntList`?
- Why does checked access compare an index with the number of stored items?
- How does `int_list_reserve` implement the textbook's expansion step?
- What must the lab implementation preserve if allocation fails?
- Why does the lab reject an allocation size that cannot be represented?
- Which tests demonstrate append, access, expansion, and cleanup?
- How do insertion and removal preserve the textbook's no-gap invariant?
