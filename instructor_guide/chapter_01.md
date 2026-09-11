# Chapter 1. Keeping Data Together in One Place

## Questions to Start the Class

> Why does keeping ordered data in neighboring memory positions help us?

**What to expect:** Students should connect neighboring positions with
repeating a task in order and locating an item directly from its index.

## Why Do We Need It?

A fixed array provides a known number of slots. An ordered collection must
also track how many slots belong to the list and explain how to insert and
delete without leaving gaps. When the array is full, an addition is rejected
without changing the values or the count.

Keep the lesson in everyday language before attaching formal names. The
textbook is the source of truth for the conceptual scope.

## Supporting a First Reading of C

The [English textbook](../module_01_arraylist/student/textbook.md#full-c-code-explanation)
and [Korean textbook](../module_01_arraylist/student/textbook_korean.md)
include an optional **Full C Code Explanation** after the original chapter.
Release both editions at Stage D, after the investigation and exit ticket.
The appendix is a reference students can consult one topic at a time; its
length and practice questions do not add required reading or assessment.

When a student cannot read a line, explain its names and symbols before
asking them to trace it. Topics 1–4 explain program structure, punctuation,
storage, and conditions. Topics 5–8 follow the four operation examples;
topic 9 joins the trace, and topic 10 provides the complete runnable program.
Students can return to their current lab checkpoint after one relevant
example. On the website, the section opens with **Expand full explanation**.

The lab packages the same array operations into functions. Use the
[lab's textbook-to-lab guidance](../module_01_arraylist/student/lab.md)
to explain that extra step: integer parameters are local copies, mutations
return a size the caller must save, and the search function returns `-1`
for absence while the textbook loop finishes with `index == size`.

## Blackboard Tracking

Reveal one line at a time.

| Action | Memory state |
|---|---|
| Store 100, 200, 300, 400, 500 | Active prefix `[100] [200] [300] [400] [500]`; size 5, capacity 10 |
| Read index 1 | Value 200; state unchanged |
| Update index 1 to 500 | Active prefix `[100] [500] [300] [400] [500]`; size 5 |
| Find 300 | The first match is index 2; state unchanged |
| Remove index 1 | Shift the later items left; active prefix `[100] [300] [400] [500]`; size 4 |
| Insert 600 at index 1 | Shift the suffix right from the back; active prefix `[100] [600] [300] [400] [500]`; size 5 |
| Separate full fixture | `[100] [200] [300] [400] [500] [600] [700] [800] [900] [1000]`; size 10 |
| Attempt to append 1100 | Reject; every array slot and size remain unchanged |

Ask students to name the action before revealing the next line. Slots after
the active prefix are not list items; they need not contain zero or be cleared.
The shorter three-item inquiry fixtures are separate practice examples.

## Common Initial Thoughts

- “Deleting a value is enough.”
  Ask what happens to the gap and to the meaning of later indexes.
- “Move items from left to right during insertion.”
  Trace the first overwritten value.
- “An index below capacity is always a valid list position.”
  Contrast an existing item with an unused slot after the active prefix.
- “Write the new value first, then check whether the array is full.”
  Ask whether index 10 is a valid slot of `int array[10]`.
- “Zero means an empty slot.”
  Store zero as an ordinary list item and identify the list using size.
- “Changing size inside a function updates the caller's variable.”
  Trace the returned count and the assignment in the caller.

## Neutral Questions

- Which positions currently contain stored items?
- Which item moves first, and why?
- How do size and capacity differ?
- What condition means the fixed array is full?
- What must remain unchanged when an addition is rejected?
- How does deletion make room without changing capacity?
- How does finding by index differ from finding by value?

## Vocabulary Boundaries

**Revisit with support:** C variables, functions, arrays, loops, and conditional
statements. Do not assume that previous exposure means students can read
their syntax; use the optional appendix for the line they are working on.

**Introduce here:** data structure, contiguous memory, array, list, ArrayList,
index, element, size, capacity, invariant, indexed access, and linear search.

**Lab connection:** Use plain array parameters and integer counts. Mutating
functions return the new size, or the original size after rejection. Reads
and updates use a checked index. Search returns the first matching index or
`-1`. The supplied `const` qualifier marks the search array as read-only.

There is no allocation, release, or resizing task in Module 1. Later labs
introduce node storage and growable arrays; do not make them prerequisites here.

## Final Check

> A ten-slot array contains ten items. What happens when we try to append
> 1100? After removing the last item, what changes if we try again?

**Minimum correct answer:** The first addition is rejected before any write;
all values and size remain unchanged. Removing the last item changes size
from 10 to 9, not capacity. The second addition writes 1100 at index 9 and
returns size 10. The caller stores the returned size.
