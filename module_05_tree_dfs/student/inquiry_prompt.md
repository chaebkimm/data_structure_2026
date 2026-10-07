# Stage A — Initial Inquiry: Follow, Resume, Build, and Write

Use [`lab.c`](lab.c) without naming traversal methods yet. Child links are
indices; `-1` marks absence. `H`, `I`, and `J` are initialized but unconnected.

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

## A. Follow links and change the recording moment

Use the supplied tree below. Which nodes can be reached? Why is the
initialized count different? Always finish the left branch first; record
the current symbol before, between, and after the branches. What remains
if each recording overwrites one variable?

## B. Remember unfinished work

While working on `D`, what must `F`, `A`, and `B` still do? Imagine storing
these nodes in a last-in, first-out container. What extra information tells
each node where to resume? What should happen when a missing child is
represented by `-1`? What state must be fresh before another run?

## C. Recover a tree from two sequences

Given `ABDECFG` for parent-before-children recording and `DBEAFCG` for
left-parent-right recording, identify the root and its two groups. Repeat
inside each group. Why does knowing group sizes help? Could repeated
labels make the choice ambiguous?

## D. Build instead of calculate

Read `123*+` left to right, creating one node per character. Store completed
subtree roots in a stack. How should an operator join the two most recent
roots? Use `12-` to decide which pop goes on which side. What does the
stack hold, and how does this differ from Chapter 4's evaluation?

## E. Write symbols and retain meaning

Draw the trees for `123*+`, `12+3*`, and `123--`. Record left expression,
operator, and right expression without parentheses. Which meanings change?
How could parentheses around a child preserve the original grouping?
Should equal-priority children on the left and right use the same rule?

## F. Write once, then consider limits

A next-write position starts at zero and a wrapper appends a null
terminator but does not reset that position. What happens on another run?
What reset is needed? Seven tokens fit the input array; would adding
parentheses still fit a ten-character output array for every such input?
