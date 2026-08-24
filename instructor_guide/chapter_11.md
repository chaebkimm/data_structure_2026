# Chapter 11. Taking Out the First Value Without Scanning Everything

## Starting Question

> "To keep priority and arrival order, but avoid looking at the whole array every time we take a value out, what shape should we put the values in?"

**Expected Answer:** Students should say that we need to put the first (top) value in a fixed spot, and only fix the short path that got out of order after putting a value in or taking one out.

## Why We Need This

The unsorted array from Chapter 10 is easy to add values to, but we have to look at every record when taking a value out. As the number of items grows, we keep repeating the same full check. A shape where an array is filled level by level without any empty spaces is called a "complete binary tree." A complete binary tree where the parent always comes before its children is called a "min-heap." With this shape, we can always take the answer right out from position 0.

In week 9, we compare this with the provided unsorted array code. Students submit their heap code and the comparison results just once.

## Board Walkthrough

Write the records in `ID/P/S` order. `P` is priority and `S` is the arrival order. When comparing, we look at `P` first, then `S`.

```text
71/3/0, 88/1/1, 42/2/2, 17/1/3,
26/4/4, 9/2/5, 63/1/6

```

Reveal the ID array one line at a time after inserting:

```text
[71]
[88,71]
[88,71,42]
[88,17,42,71]
[88,17,42,71,26]
[88,17,42,71,26,9]
[88,17,63,71,26,9,42]

```

Empty the same array to the end:

```text
88 -> [17,42,63,71,26,9]
17 -> [63,42,9,71,26]
63 -> [42,71,9,26]
42 -> [9,71,26]
9  -> [71,26]
71 -> [26]
26 -> []

```

Ask these questions before showing the next state:

* When we add 17 to `[88,71,42]`, which path's relationship do we check?
* If we take out 88 and move 42 to position 0, which of the two children do we pick first to compare with?
* If we check the heap rule for the whole array of 7 items, how many times do we compare parents and children?

## Common First Thoughts

* "The entire heap array is perfectly sorted in processing order."
* "When a new record comes in, we have to fix all the branches in the array."
* "When moving down, we always move the left child up no matter what."
* Students might mix up the number of comparisons for checking the whole rule with the cost of just putting in or taking out one item.

## Neutral Questions

* Where is the parent-child relationship that could get messed up right now?
* Between the two children, what comparison rule do we use to pick the record that will move up to the parent's spot?
* Where did you count the comparisons for moving things, and where did you count them for checking the whole rule?

## Vocabulary Rules

**Words we can use:** Priority, arrival order, stable tie-breaking rule, array position, parent, child, root, and array expansion.

**Names we will introduce in this chapter:** Complete binary tree, min-heap, move up (bubble up), and move down (bubble down).

**Words we won't use yet:** Data structures for quickly finding random records, the path cost procedure in Chapter 12, or the names of other heap shapes.

## Final Check

> "How does a min-heap keep the top record at position 0, and why do we only need to fix one single path after adding or taking out a value?"

**Minimum Expected Answer:** Students should mention the complete shape, the parent-child rule, and that we only need to check the one specific path that could newly go out of order.