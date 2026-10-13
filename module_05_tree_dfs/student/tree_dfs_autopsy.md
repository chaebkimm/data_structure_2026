# Tree DFS Autopsy — Optional Pointer Scaffold

This exercise belongs to the separate pointer-based code in `code/autopsy`
and `code/starter`, rather than the array-based [`lab.c`](lab.c). Run the
isolated `make autopsy` target with a sanitizer. Predict the failure first,
then identify the first invalid memory access.

1. Which function result was ignored?
2. Why was `copy` still `NULL`?
3. Which caller-owned values should a correct failed copy preserve?
4. Where must the error travel through the recursive calls?

Transfer to the core lab on paper: which unchecked calls would fail for
an empty postfix expression or an operator without two waiting roots?
Which capacity would a ten-node traversal path plus `-1` exceed?
