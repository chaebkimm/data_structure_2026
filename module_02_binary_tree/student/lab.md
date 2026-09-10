# Lab — Build and Evaluate an Array-Based Expression Tree

## Purpose and scope

Implement Chapter 2's four functions: reserve a node, build a multiplication
term, build a sum of terms, and recursively evaluate the resulting tree.
The canonical input is `1+2*3`, whose answer is 7.

## Two 90-minute meetings

| Meeting | Work | Minutes |
|---|---|---:|
| A — Conceptual stages | Inquiry, representation reveal, Cognitive Pause, calibration, investigation, and exit ticket | 90 |
| B — Stage E lab | Four functions, tests, precedence autopsy, and submission evidence | 90 |
| **Total** | | **180** |

Stage D's English and Korean textbooks and models follow Meeting A's
investigation and exit ticket. Stage E's lab and code are released for
Meeting B. Both accessible pathways use the same learning targets and rubric.

## Files

You receive `code/include/binary_tree.h`, `code/starter/binary_tree.c`,
`code/tests/test_core.c`, `code/tests/test_student.c`,
`code/tests/test_helpers.h`,
`code/autopsy/faulty_precedence.c`, `code/Makefile`, and `code/build.ps1`.
Edit only the starter implementation and student tests. Keep the supplied
header, core tests, and test runner unchanged. A reference solution is kept
in the instructor package.

## Representation and function contracts

```c
struct TreeNode {
    char data; /* Store characters: '3', '+', or '*'. */
    int left;  /* Index of a child in nodes, or -1. */
    int right; /* Index of a child in nodes, or -1. */
};

/* Defined once by the implementation; declared extern in the header. */
struct TreeNode nodes[20];
int size = 0;          /* Used nodes and next free index. */
char eq[20] = "1+2*3";
int pos = 0;           /* Next unread character in eq. */

int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

Every child link and root is an integer index. `-1` means no child; `0` is a
valid node index. The structure's `data` is a character. Evaluation returns
an integer result separately, without replacing the character.

Assume valid, nonempty inputs consisting of single digits alternating with
`+` or `*`, no spaces or parentheses, and at most 19 characters. All
intermediate and final results must fit in `int`. The string's `\0` occupies
one additional slot. Each character becomes one node, so the arrays suffice
for this contract. Input validation and malformed-tree handling are outside
this lab. The completed tree has a single root, no cycles or shared children,
and two children at every operator.

## Core checkpoints and coding plan

The starter has four `TODO(core)` regions, one in each function. Implement
all four, including the evaluator's base case. Add short comments that explain
why a step is needed, especially at a term boundary or root change.

### 1. Reserve and initialize a node: `new_node`

Use the next unused index recorded by `size`. Store `data`, initialize both
children to `-1`, advance `size`, and return the reserved index. Returning
`size` after incrementing it would identify the next unused slot instead of
the new node. Node creation alone does not attach the node to a parent.

### 2. Build one multiplication term: `term`

Consume the first digit and make its new node the current root. While the
next character is `'*'`, reserve that operator and the following digit. Link
the previous root on the left and the new digit on the right, then make the
operator the root. Return when the next character is `'+'` or `'\0'`, leaving
that character unconsumed. Each new operator groups the term built so far
with the next operand, producing left association.

### 3. Build a sum of complete terms: `terms`

Call `term()` for the first subtree. While the next character is `'+'`,
reserve the operator and call `term()` for its entire right operand. Attach
the old root on the left and the returned term root on the right, then update
the root. Calling `term()` completes multiplication before addition is linked.
Both parsing functions share `pos`; do not reset it inside either function.

For `1+2*3`, the required completed state is:

| Index | `data` | `left` | `right` |
|---|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

The root is 1, `size` is 5, and `pos` is 5, selecting the final `\0`.

### 4. Evaluate recursively: `eval_tree`

At a digit leaf, subtract `'0'` and return its numeric value; this is the
base case. At an operator, evaluate its left and right subtrees into separate
local variables, then apply `+` or `*` and return the answer. Evaluate the
left subtree first so that traces are reproducible. Preserve every node field,
`size`, `pos`, and `eq` during evaluation. A leaf never requires a call on -1.

In the canonical tree, completed calls return 1, 2, 3, 6, and 7. Operators
remain the characters `'+'` and `'*'`. Explain why this differs from writing
calculated answers into the tree.

### 5. Design three student tests

Replace the three placeholder bodies in `code/tests/test_student.c`, keeping
the supplied runner. Each test returns 1 on success and 0 on failure.

1. Node creation: check returned indices, the stored character, both -1 child
   fields, and `size`. Include a claim beyond the supplied creation cases.
2. Construction: check a new valid expression's links, consumed position,
   precedence, or left association. An answer alone cannot distinguish the
   association of repeated `+` or repeated `*`; inspect the tree shape.
3. Evaluation: check a valid expression's answer and verify that evaluating
   it, including a repeated call, preserves the tree and shared state.

Start each independent build by resetting the shared counters and copying
a valid expression. For example, inside a test that includes `<string.h>`:

```c
size = 0;                  /* Reuse the array for a new expression. */
pos = 0;                   /* Start reading its first character. */
strcpy(eq, "8+2*0");        /* This known valid string fits in eq. */
int root = terms();        /* Save only this build's root index. */
int answer = eval_tree(root);
```

The supplied `begin_expression("8+2*0")` helper performs the same reset and
copy. Use `REQUIRE(condition)` to make a test fail when its claim is false.
After a full build, `REQUIRE(complete_tree(root))` checks the returned tree
before tests follow its links or evaluate it. These are provided test helpers;
you do not implement an additional validator.

Test code may use local snapshots and direct field comparisons. Do not add
new public functions. Resetting the counters starts a new logical tree; old
roots must not be used after the storage has been reused. Do not run the
parser on inputs outside its contract or the evaluator on invalid indices,
cycles, or shared structures.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

When supported, add `-Sanitize` to a test command. The execution-policy
option applies only to this child PowerShell process.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
make autopsy
```

The Makefile defaults to GCC; use `make CC=clang starter-core` for Clang.
Warnings and sanitizers help reveal implementation mistakes. A wrong
precedence rule can still compile cleanly and finish normally, so tests also
need expected answers and structure checks. If diagnostics are unavailable
locally, use approved debugger or instructor-CI evidence.

Optional additional valid fixtures may be released separately. They use the
same four functions and are not part of the core score.

## Required submission

1. The completed starter with all four functions and concise explanatory comments.
2. A passing supplied core-test transcript.
3. Three passing student tests, with a new claim and rationale for each.
4. Warning-enabled and approved diagnostic evidence.
5. The completed evidence record, precedence autopsy, and corrected Cognitive Pause.

Completion means the four contracts are satisfied, student-controlled code
has no compiler warnings, and the explanation connects indices, parser
boundaries, precedence, association, and returned evaluation values.
