# Week 1 — Keeping Data Together in One Place

The revised Chapter 1 textbook defines the core scope: a fixed array, a
separate item count, checked access, search, append, insertion, and deletion.
The lab packages the same actions into functions with plain array parameters.

## Textbook vocabulary

| Term | Question |
|---|---|
| data | What values does this collection store? |
| data structure | How does a storage rule help us use and change data? |
| contiguous memory | What does it mean for memory positions to be next to one another? |
| array | What stays fixed after `int array[10]` is declared? |
| list | What does it mean for stored data to have an order? |
| ArrayList | How can a fixed array and an item count represent a list? |
| index | How does an index locate an item? |
| element | What is one stored item called? |
| capacity | How many slots are available to this list? |
| size | How many items currently belong to this list? |
| invariant | Which placement rule must insertion and deletion preserve? |
| indexed access | How can an index locate an item without searching by value? |
| linear search | Why might finding a value require checking each item in order? |

## Core questions

### Memory and access

- Why can an item be found directly when its index is known?
- Why can searching for a value require checking every stored item?
- Which positions belong to the list when size is 3 and capacity is 10?
- Why do stored items begin at index 0 in this design?

### Insertion and deletion

- After deleting index 1 from `[100, 500, 300]`, which items must move?
- Why does insertion shift items from back to front?
- How much work can insertion at the front require?
- How much work can deletion at the end require?

### Fixed capacity and invariants

- How do size and capacity differ?
- What must remain unchanged when an addition is attempted on a full list?
- Why is index 10 not a slot in `int array[10]`?
- How does deleting an item make room without changing capacity?
- Why can zero be a stored value rather than an empty-slot marker?
- What goes wrong if size includes a slot that has not been initialized as a list item?

### C connection

- Which conditions must be checked before reading or updating `array[index]`?
- Why can insertion accept index equal to size while removal cannot?
- Why must the caller assign the size returned by a mutating function?
- What does `int_list_find` return for a missing value or duplicate matches?
- What does `const` promise about the array passed to `int_list_find`?

## Lab and testing questions

These questions connect the textbook actions to the required lab. Extra
boundary and operation-sequence tests are the optional extension.

- How do the textbook's array, size, and capacity map to the function arguments?
- Which test distinguishes an unused array slot from a valid list index?
- How can a snapshot prove that a rejected operation changed no array slot?
- What happens when size is negative or greater than capacity?
- Why must the caller ensure capacity does not exceed the actual array length?
- Which operation sequence demonstrates that deletion makes room for another addition?
- How does the guard-slot autopsy expose a bad full check without accessing outside its physical array?
