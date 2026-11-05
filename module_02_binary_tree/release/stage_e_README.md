# Module 2 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- `code/starter/binary_tree.c`; and
- `code/tests/test_student.c`.

This application lab extends the textbook's `1+2+3` example to `+`/`*`
precedence. Complete `new_node`, `term`, `terms`, and `eval_tree`. Reuse
character data, child indices, `-1` empty links, and recursive child results.
The lab adds its own 20-slot arrays, `size`, and shared reading position
`pos`; the textbook uses 10 slots, `nodes_size`, and different functions.
Write three distinct tests for node creation, construction, and evaluation.
Do not modify supplied tests to hide failures.

Keep your Stage D textbook available. Use its **New C Syntax Explained**
and **C Code** sections for reading support. On the Chapter 2 webpage, use
**Ask GPT** at the end of a subsection for questions about its content or
code. The lab explains this release's header, starter, and tests. This
support adds no submission requirements.

Use valid single-digit expressions with `+` and `*`, no spaces or
parentheses, at most 19 characters, and all intermediate/results within
`int`. Reset `size` and `pos` before each independent build. Input validation
and additional APIs are not required.

Before running the standalone autopsy, preserve the prediction requested in
`student/tree_autopsy.md`. Submit the lab artifacts and evidence template.
The reference solution and instructor extension tests are not in this release.
