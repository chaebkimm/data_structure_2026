# Module 2 Student Code

## Files you edit

- `starter/binary_tree.c`
- `tests/test_student.c`

Keep the public header and supplied tests unchanged. The four `TODO(core)`
functions are `new_node(char data)`, `term(void)`, `terms(void)`, and
`eval_tree(int node)`, each returning `int`.

## Help with C syntax

The Stage D textbooks include an optional **Full C Code Explanation** in
English and Korean. Use the
[lab's topic map and file-layout guide](../student/lab.md#help-with-reading-the-c-code)
to find help for your current statement, including the extra notation in
the supplied header and tests. The textbook's complete program has its own
`main`; this release already supplies `main` in the test files. Implement
the four starter bodies and use the build commands below to compile them
with the tests. No appendix exercises are added to your required work.

## Model and contract

`struct TreeNode` stores `char data`, `int left`, and `int right`.
`nodes[20]` holds the nodes; links and roots are array indices. `-1` marks
no child, while index `0` names the first node. `size` is the used-node
count/next unused position. `eq[20]` contains the expression and `pos`
marks its next unread character.

`new_node` saves a character, initializes both children to `-1`, and
returns the reserved index. `term` builds a digit and its following
multiplications; `terms` joins complete terms beneath additions. Each new
operator keeps the previously built subtree on its left. `eval_tree`
converts digit leaves with `- '0'`, obtains both child results, and returns
the operation's result without changing the tree.

The canonical input `1+2*3` creates five nodes with character data
`'1', '+', '2', '*', '3'` at indices `0` through `4`. Its root is index `1`.

Use only valid nonempty alternating single digits and `+`/`*`, with no
whitespace or parentheses, at most 19 characters, and every intermediate
and final result within `int`. These preconditions are not checked by the
textbook implementation. `eval_tree` assumes a completed finite tree with
no cycles or shared children. Missing operands are outside its contract.

Before each independent test, reset `size` and `pos` to zero and copy its
valid expression into `eq`. Rebuilding reuses the node array; evaluate or
inspect a previous tree before resetting. The initial global values already
prepare the canonical example for its first build.

## Build and test

From this `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target starter -StudentTests
```

Add `-Sanitize` when supported. The execution-policy setting applies to the
launched child process. The script searches for Clang, GCC, then Microsoft
C; Microsoft C requires a Visual Studio Developer PowerShell.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

Use `make CC=clang starter-core` for Clang. The initial starter and three
student-test placeholders deliberately fail until completed. Test node
creation, construction shape/precedence, and evaluation without mutation.

## Standalone precedence autopsy

Preserve the prediction in `../student/tree_autopsy.md` before running:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target autopsy
```

Or run `make autopsy`. The fixture is self-contained and does not require
your unfinished functions. Compare its tree and answer with the expression's
operator precedence; a successful process exit does not prove the builder
represented the intended expression.

The reference implementation, lecture linked to that implementation, and
instructor extension tests are deliberately absent from this release.
