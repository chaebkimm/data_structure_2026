# Module 2 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- `code/starter/binary_tree.c`; and
- `code/tests/test_student.c`.

Complete the two functions `tree_find` and `tree_clear`. Practice direct
initialization, guarded left/right attachment, and clear-then-detach removal
in the three required student tests. Do not invent additional helper APIs or
modify supplied tests to hide failures.

The supplied core fixture uses `(3 + 5) * 2`, but your functions remain
generic binary-tree operations. They must also handle valid one-child trees,
duplicate integer data, zero data, and values unrelated to expressions.

Before running the isolated autopsy, preserve the prediction requested in
`student/tree_autopsy.md`. Submit the artifacts listed in the lab and
complete the evidence template. Instructor extension tests are not an extra
required implementation.
