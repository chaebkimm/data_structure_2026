# Chapter 1. Keeping Data Together in One Place

## Questions to Start the Class

> Why does keeping ordered data in neighboring memory positions help us?

**What to expect:** Students should connect neighboring positions with
repeating a task in order and locating an item directly from its index.

## Why Do We Need It?

A fixed array works when the required number of slots is known. An ordered
collection must also explain how to insert and delete without leaving gaps.
If the allocated space becomes full, the program needs a larger space.

Keep the lesson in everyday language before attaching formal names. The
textbook is the source of truth for the conceptual scope.

## Blackboard Tracking

Reveal one line at a time.

| Action | Memory state |
|---|---|
| Start | `[10] [50] [20] [30] [ ]` |
| Remove 50 | `[10] [ ] [20] [30] [ ]` |
| Close the gap | `[10] [20] [30] [ ] [ ]` |
| Insert 99 | `[10] [20] [99] [30] [ ]` |
| Full four-slot space | `[10] [50] [20] [30]` |
| Move and add 99 | `[10] [50] [20] [30] [99] [ ] [ ] [ ]` |

Ask students to name the action before revealing the next line.

## Common Initial Thoughts

- “Deleting a value is enough.”
  Ask what happens to the gap and to the meaning of later indexes.
- “Move items from left to right during insertion.”
  Trace the first overwritten value.
- “Write the new value first, then get more memory.”
  Ask which allocated slot receives the value when the space is full.
- “Grow by one slot every time.”
  Count how often all old items would be copied.
- “Doubling makes every addition equally cheap.”
  Separate ordinary additions from additions that trigger copying.

## Neutral Questions

- Which positions currently contain stored items?
- Which item moves first, and why?
- What condition means the allocated space is full?
- What must be preserved when the data moves?
- Why does doubling place more additions between copying steps?
- How does finding by index differ from finding by value?

## Vocabulary Boundaries

**Already available:** C variables, functions, arrays, loops, and conditional
statements.

**Introduce here:** data structure, contiguous memory, array, list, ArrayList,
dynamic array, index, element, invariant, pointer, `malloc`, `NULL`, and
`free`.

**Reserve for the lab:** the `IntList` API, status codes, detailed allocation
failure contracts, arithmetic-limit checks, and implementation testing.

## Final Check

> A four-slot memory space contains 10, 50, 20, and 30. Explain how to add 99
> while preserving the old order.

**Minimum correct answer:** Obtain a larger contiguous memory space, copy the
four old values in order, add 99 after them, release the old space, and
continue using the new space.
