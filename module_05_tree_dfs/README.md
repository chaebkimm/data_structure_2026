# Module 5 — Tree Depth-First Traversal

This Week 5 package applies depth-first traversal to the expression tree
`(3+5)*2`.

Students learn three roles for the same left-first recursive shape:

- preorder creates a structurally independent copy;
- inorder prints the expression with required parentheses; and
- postorder evaluates children before their operator.

The implementation uses a caller-owned pool of 100 nodes. It accepts
single-digit operands and the operators `+` and `*`. Failed copies restore the
pool position and preserve the caller's output pointer. Failed evaluations
preserve the caller's previous result.

Students edit `code/starter/tree_dfs.c` and `code/tests/test_student.c`.
Instructors validate with `make solution-core solution-extension` from `code/`.
