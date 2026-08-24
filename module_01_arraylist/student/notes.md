# Student Notes — Keeping Data Together in One Place

These notes summarize the frozen Chapter 1 textbook. The lab adds a structured
C interface afterward, but it does not change the model explained here.

## 1. Why keep data together?

An ordered collection lets a program repeat the same action for every item.
An array stores items in neighboring memory positions. If the index is known,
the program calculates the item's position directly.

Searching by value is different. The program may need to inspect every stored
item until it finds a match.

## 2. Keep stored items packed at the front

The chapter's golden rule is:

> Stored items begin at index 0 and follow one another without empty gaps.

This rule determines how insertion and deletion work.

### Delete an item

Deleting an item creates a hole. Every later item moves one position to the
left. The number of stored items decreases by one.

```text
[10] [50] [20] [30] [ ]
[10] [ ]  [20] [30] [ ]
[10] [20] [30] [ ]  [ ]
```

### Insert an item

Insertion first moves the target item and every later item one position to the
right. Items move from back to front so that an unmoved value is not
overwritten. The new value enters the open position.

```text
[10] [20] [30] [ ]  [ ]
[10] [20] [ ]  [30] [ ]
[10] [20] [99] [30] [ ]
```

## 3. Grow when the space is full

Before adding an item, check whether every allocated slot is occupied. If the
space is full:

1. obtain a larger contiguous memory space;
2. copy all stored items in the same order;
3. add the new item;
4. release the old memory space;
5. continue using the new starting address.

The course example doubles the allocated space. Doubling leaves room for many
later additions, so copying happens less often than it would with one-slot
growth.

Across many additions, the total copying work grows in proportion to the
number of items added. The average work for one addition therefore remains
small.

## 4. Compare the work

| Operation | Work |
|---|---|
| Find by index | The position is calculated directly |
| Find by value | Items may be checked one by one |
| Add at the end with space available | One new item is written |
| Insert near the front | Later items move right |
| Delete near the front | Later items move left |
| Expand | Every stored item is copied |

## 5. C features used in the chapter

- `sizeof` reports how many bytes a value or type needs.
- A pointer stores a memory address.
- `malloc` requests one contiguous memory block.
- `NULL` reports that a usable address was not returned.
- `free` releases an allocated memory block.
- After `free(arrayList)`, reset the pointer to `NULL` and reset the tracking
  variables before reusing them.

## 6. Bridge to the lab

The lab groups the dynamic-array pointer and its two tracking numbers into an
`IntList`. Its functions perform the same operations described above:
initialize, obtain space, read by index, append, insert, remove, and release.

The lab also checks invalid requests and memory-allocation errors. These are
implementation requirements for robust C code. They extend the textbook
without changing its core explanation.
