# Stage A — Initial Inquiry: Linear Format

Use [`lab.c`](lab.c) and [the lab slides](ppt_lab_material.md). The root is
`F [5]`, with children `A [0]` and `G [6]`. `A` has children `B [1]` and
`C [2]`; `B` has children `D [3]` and `E [4]`. All other child links are
`-1`. `H`, `I`, and `J` are initialized but unconnected. Preserve first
predictions in a numbered record. These tasks match the standard inquiry.

1. **Follow links and change the recording moment.** Which nodes can be reached? Why is the initialized count different? Always finish the left branch first; record the current symbol before, between, and after the branches. Where could that action go in the source? Does a comment itself record data? What remains if each recording overwrites one variable?

2. **Remember unfinished work.** While working on `D`, what must `F`, `A`, and `B` still do? Imagine storing these nodes in a last-in, first-out container. What extra information tells each node where to resume? What should happen when a missing child is represented by `-1`? Which state does the wrapper reset, and which state must be fresh before another run?

3. **Build instead of calculate.** Read `123*+` left to right, creating one node per character. Store completed subtree roots in a stack. How should an operator join the two most recent roots? Use `12-` to decide which pop goes on which side. What does the stack hold, and how does this differ from Chapter 4's evaluation?

4. **Write symbols and retain meaning.** Draw the trees for `123*+`, `12+3*`, and `123--`. First record left expression, operator, and right expression without parentheses. Which meanings change? Predict what the source's precedence comparisons write. Why might equal-priority children on the left and right use different rules? What does giving digits precedence 3 accomplish?

5. **Start a complete write and consider limits.** A wrapper resets its next-write position, calls a recursive helper, and appends a null terminator. What happens when another complete write follows? Why must child calls share the advancing position? Seven tokens fit the input array; how much room might grouping parentheses add? Compare the required space for `1+(2+(3+4))` with the current output array.

6. **Optional transfer: recover a tree from two sequences.** Given `ABDECFG` for parent-before-children recording and `DBEAFCG` for left-parent-right recording, identify the root and its two groups. Repeat inside each group. Why does knowing group sizes help? Could repeated labels make the choice ambiguous? This exercise uses the separate tree in [ppt_material.md](ppt_material.md); reconstruction is not implemented in the core lab.
