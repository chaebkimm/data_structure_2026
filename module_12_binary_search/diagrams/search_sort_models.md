# Module 13 Equivalent Models

Use the same records in text, tables, or diagrams. These are alternate representations of the common trace, not extra exercises.

## First-match boundary

Original indices: `0:31, 1:23, 2:17A, 3:8, 4:17B, 5:42`. Linear first index for 17 is 2.

Sorted values: `8,17A,17B,23,31,42`. Candidate intervals for 17 are `[0,6)`, `[0,3)`, `[0,1)`, `[1,1)`. The final position 1 exists and matches. An interval endpoint at 6 is not a readable element.

## Ordered prefix

Before pass i, positions `[0,i)` are ordered and keep their original multiset. Save position i before shifting. Only larger values move right, so an equal earlier record stays earlier.

## Merge boundary

```text
[31,23,17A]                    [8,17B,42]
      ↓ recursively order             ↓ recursively order
[17A,23,31]                    [8,17B,42]
                    ↓ next unused values
scratch: [8,17A,17B,23,31,42]
                    ↓ copy only [lo,hi)
values:  [8,17A,17B,23,31,42]
```

The A/B labels exist on paper to expose identities. The integer lab stores two equal 17 values. During equality the left source record is copied first. Scratch cannot alias the original values: writing it must not overwrite an unread source.

## Workload comparison

Draw separate columns for preparation, query, update, order, and reserved/used storage. Place each proposed structure in those columns before selecting it. The smallest query bound alone does not determine the whole workload cost.
