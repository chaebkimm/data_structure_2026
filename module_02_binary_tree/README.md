# Module 2 Teaching Package

## Expression Trees with Array Indices in C

This module follows [Chapter 2](student/textbook.md) and its
[Korean edition](student/textbook_korean.md). Students build the hierarchy
of `1+2*3` and evaluate it to obtain `7`. The chapter extends Chapter 1's
fixed arrays with structures, child indices, and recursive evaluation.

## Module question

> How can array elements record an expression's hierarchy, and how can we
> build and evaluate that hierarchy while preserving operator precedence?

## Canonical representation

```c
struct TreeNode {
    char data;
    int left;
    int right;
};

extern struct TreeNode nodes[20];
extern int size;
extern char eq[20];
extern int pos;

int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

`data` stores a digit character or operator. Child fields and the returned
root are indices into `nodes`; `-1` means no child and `0` is a valid index.
`size` counts used nodes and identifies the next unused position. `pos`
identifies the next unread character of `eq`.

Starting from `size = 0`, `pos = 0`, and `eq` containing `"1+2*3"`, construction gives:

| Index | Data | Left index | Right index |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

The root index is `1`, `size` is `5`, and `pos` is `5`, pointing at the
ending `'\0'`. `term()` completes multiplication groups before `terms()`
attaches them beneath addition. Evaluation returns `6` from the `*` subtree
and then `7` from the root, without changing any node.

## Input contract and tree rules

Use one nonempty expression that starts with a single digit and continues
with zero or more operator-and-digit pairs. Only `+` and `*` are supported.
Use no whitespace, parentheses, unary operators, or multi-digit numbers,
and at most 19 characters plus the string terminator. Every intermediate
and final value must fit in `int`. These are caller preconditions, not
validation tasks. One character needs one node, so a valid input fits in
`nodes[20]` when construction begins with `size = 0`.

For independent examples, reset `size` and `pos` to zero and copy the next
valid string into `eq` before calling `terms()`. Old root indices no longer
identify preserved trees after the storage is reused. `eval_tree` receives
a valid completed tree with one root, no shared children, and no cycles.
Every operator has two operands and every digit is a leaf. The underlying
binary-tree structure can represent a single child, but that is not a
completed operator for this evaluator.

## Core learning targets

Students will:

1. Explain nodes, roots, parent/child relationships, leaves, and subtrees.
2. Translate among expression text, a hierarchy, an index table, and C fields.
3. Reserve initialized nodes and distinguish a character, index, and result.
4. Trace `size`, `pos`, and changing subtree roots during construction.
5. Explain multiplication precedence and left grouping within operator chains.
6. Implement all four chapter functions and trace the evaluator's base case
   and separate local results.
7. Explain why fresh nodes preserve the root, single-parent, and no-cycle rules.
8. Support correctness and operation costs with tests and diagnostic evidence.

Node reservation and assignment to a known child field take constant work.
Construction and complete evaluation take work proportional to the number
of input characters/nodes. The parser uses loops with bounded function-call
depth; recursive evaluation uses temporary call space proportional to the
longest root-to-leaf path, including the root call. Capacity is fixed in
this example; distinguish reserved array space from its used positions.

## Teaching and release sequence

Use two 90-minute meetings and a 100-point rubric. Standard and linear
inquiry/worksheet versions have the same learning targets.

| Stage | Release point | Materials |
|---|---|---|
| A | Before Meeting A | Initial hierarchy inquiry; preserve the first model |
| B | After inquiry | Index representation, vocabulary, three-target Cognitive Pause |
| C | After pause and calibration | Construction/evaluation investigation with `2*3+4*5` |
| D | After the Stage C attempt | English and Korean textbooks plus diagram/text models |
| E | Meeting B | Four-function lab, tests, evidence, and precedence autopsy |

The pause checks indices, parser position/root changes, and evaluation.
The autopsy uses a finite valid tree with a deliberately wrong precedence
rule. Students preserve predictions before running it. Keep worked autopsy
answers, instructor files, the reference solution, and extension tests out
of the staged student archives.

## Package map

- `student/`: bilingual textbooks, both inquiry/worksheet formats, reveal,
  vocabulary, Cognitive Pause, lab, rubric, evidence, and autopsy worksheet.
- `diagrams/tree_models.md`: correct hierarchy, index, construction, and
  evaluation models with text equivalents.
- `instructor/`: lesson plan, answer key, and implementation notes.
- `code/`: public header, four-function starter and solution, core/student/
  extension tests, lecture driver, standalone autopsy, and build files.
- `release/`: stage READMEs, student-only build files, source manifest,
  and ZIP preparation script.

See [code/README.md](code/README.md) for reference checks and
[release/release_manifest.md](release/release_manifest.md) for packaging.

## Core submission

Submit the completed `code/starter/binary_tree.c`, three distinct tests in
`code/tests/test_student.c`, passing core/student transcripts, compiler and
supported diagnostic evidence, corrected Cognitive Pause, evidence record,
and precedence autopsy. The three tests cover node creation, construction,
and evaluation. Extensions test the same four functions; they add no APIs.

## Relationship to the course spiral

- Revisits fixed arrays, indexing, conditions, loops, and invariants.
- Introduces structures, indexed binary links, parsing, and recursive evaluation.
- Prepares for graph relationships in Module 3, explicit traversal state in
  Modules 4–6, breadth-first traversal, and later ordered trees.
