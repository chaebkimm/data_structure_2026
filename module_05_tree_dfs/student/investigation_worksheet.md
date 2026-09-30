# Stage C — Investigation Worksheet

Use [`lab.c`](lab.c) and the [textbook](textbook.md). Record predictions
before running the [lecture demo](../code/lecture/lab_demo.c). From
`module_05_tree_dfs/code`, use `make lecture` (or `./build.ps1 -Target lecture`
in PowerShell). The input contract is a well-formed, nonempty postfix
string of at most five tokens: single digits and binary `+`, `-`, `*`, `/`,
or `%`, with no spaces.

## A. Follow and visit the alphabet tree

Run `alphabet_init()` and `tree_connect()` on paper.

- Root index and character: ______________________________________
- `size`, reachable node count, and unreachable characters: _______
- Meaning of a child index of `-1`: _______________________________
- Why changing a child link does not move a node: __________________

Trace the three assignments in `tree_traversal(root)` separately.

| Assignment | Complete assignment sequence | Final stored character |
| --- | --- | --- |
| `pre_data` | ____________________________ | ______________________ |
| `in_data` | ____________________________ | ______________________ |
| `post_data` | ____________________________ | ______________________ |

Does the function save these sequences? Explain the difference between
an assignment trace and its final three global values.

________________________________________________________________

## B. Explain saved work

While processing `D`, list the active node calls and the work each older
call must resume. What happens at a leaf? Why is passing `-1` directly to
`tree_traversal()` different from encountering it as a child link?

________________________________________________________________

State the alphabet tree's height in edges and maximum active node calls.

________________________________________________________________

## C. Build from postfix

Complete the trace for `123*+`. Stack entries are array indices; show the
top on the right. For a digit, record `-1` in both child columns.

| Input index/token | Left child | Right child | Stack after token | `size` |
| --- | --- | --- | --- | --- |
| 0 / `'1'` | ______ | ______ | ______________ | ______ |
| 1 / `'2'` | ______ | ______ | ______________ | ______ |
| 2 / `'3'` | ______ | ______ | ______________ | ______ |
| 3 / `'*'` | ______ | ______ | ______________ | ______ |
| 4 / `'+'` | ______ | ______ | ______________ | ______ |

State the returned root, final `top`, and peak number of used stack slots.
Explain the difference between `size` and `top + 1`. Use `12-` to explain
why the first popped root must become the right child. Does construction
calculate a numeric result? What happens to the earlier alphabet tree?

________________________________________________________________

## D. Write infix with parentheses

Complete each output, then explain the needed or omitted parentheses.

| Postfix input | Written infix |
| --- | --- |
| `123*+` | ________________________ |
| `12+3*` | ________________________ |
| `123--` | ________________________ |
| `12-3-` | ________________________ |
| `123++` | ________________________ |
| `123/%` | ________________________ |

Why does the left-child comparison use `>` while the right uses `>=`?
What precedence value keeps digits from acquiring parentheses? Does a
fallback result of 0 from `prec()` make unsupported input valid?

________________________________________________________________

## E. Start, finish, and repeat

Trace `start_write_infix()` for `123++`, then rebuild and format `12+`.
For each call record the characters including `'\0'`, its index, and final
`pos`. Explain the separate roles of resetting `pos` and terminating the
string. Why must recursive child calls not reset `pos`?

________________________________________________________________

Predict the complete lecture demo output before running it. Explain what
its first line reports. Choose another valid expression within the input
limit and record its expected output before trying it in a scratch driver.

________________________________________________________________

## F. State assumptions and capacity

State the required tree shape and valid-root assumptions. Explain why the
alphabet tree cannot be passed to `write_infix()`. Does `eq_tree()` validate
postfix input, and does the writer check output capacity?

________________________________________________________________

Derive the maximum tokens, operators, parentheses, and total characters
including `'\0'` for the current `post_eq[6]`. Does the same reasoning cover
every larger tree that might fit in `nodes[10]`?

________________________________________________________________

## G. Count work and storage

Let `n` be reachable nodes, `t` postfix tokens, and `h` height in edges.
Explain traversal and formatting time, construction time, and maximum
active node calls in terms of these quantities. Distinguish the ten slots
reserved by `stack[10]` from the slots used by `123*+`, and from the space
needed by a general builder whose capacity can grow with input.

________________________________________________________________
