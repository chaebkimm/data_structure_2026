# Stage A — Initial Inquiry: Linear Format

Use [`lab.c`](lab.c). The root is `F [5]`, with children `A [0]` and
`G [6]`. `A` has children `B [1]` and `C [2]`; `B` has children
`D [3]` and `E [4]`. All other child links are `-1`. `H`, `I`, and `J`
are initialized but unconnected. Preserve first predictions in a numbered
record. These tasks match the standard inquiry.

1. **Follow links and change the recording moment.** Use the supplied tree below. Which nodes can be reached? Why is the
   initialized count different? Always finish the left branch first; record
   the current symbol before, between, and after the branches. What remains
   if each recording overwrites one variable?

2. **Remember unfinished work.** While working on `D`, what must `F`, `A`, and `B` still do? Imagine storing
   these nodes in a last-in, first-out container. What extra information tells
   each node where to resume? What should happen when a missing child is
   represented by `-1`? What state must be fresh before another run?

3. **Recover a tree from two sequences.** Given `ABDECFG` for parent-before-children recording and `DBEAFCG` for
   left-parent-right recording, identify the root and its two groups. Repeat
   inside each group. Why does knowing group sizes help? Could repeated
   labels make the choice ambiguous?

4. **Build instead of calculate.** Read `123*+` left to right, creating one node per character. Store completed
   subtree roots in a stack. How should an operator join the two most recent
   roots? Use `12-` to decide which pop goes on which side. What does the
   stack hold, and how does this differ from Chapter 4's evaluation?

5. **Write symbols and retain meaning.** Draw the trees for `123*+`, `12+3*`, and `123--`. Record left expression,
   operator, and right expression without parentheses. Which meanings change?
   How could parentheses around a child preserve the original grouping?
   Should equal-priority children on the left and right use the same rule?

6. **Write once, then consider limits.** A next-write position starts at zero and a wrapper appends a null
   terminator but does not reset that position. What happens on another run?
   What reset is needed? Seven tokens fit the input array; would adding
   parentheses still fit a ten-character output array for every such input?
