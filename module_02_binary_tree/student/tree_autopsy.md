# Precedence Autopsy — A Valid Tree for the Wrong Grouping

## Case

An autopsy identifies the first mistaken decision behind an unexpected result.
The standalone program `code/autopsy/faulty_precedence.c` builds a tree from
`1+2*3`. Its observed answer differs from the expression's intended answer.
Inspect its construction steps and predict the result before running it.

The demonstration uses initialized array nodes and valid child indices. It
contains no cycle or out-of-bounds access, so it can finish normally under
sanitizers even when its construction rule gives an incorrect grouping.

## Before running

Preserve these predictions before opening the output:

1. After consuming `1+2`, which operator is the partial tree's root?
2. If the next `'*'` takes that entire partial tree as its left operand,
   what will the final root and both child indices be?
3. What arithmetic grouping does that tree describe? What result will it return?
4. What root and links would correctly represent the original expression?

## Incident report

### 1. First incorrect construction decision

Inspect the source. Identify the point at which `'*'` becomes a parent of
the already-built addition. Explain how this gives addition higher priority
in this expression's evaluation.

Response:

### 2. Structure versus expression meaning

Does the faulty result still have one root, one parent per other node, and
no cycles? Why do these general tree rules fail to guarantee that operator
precedence was preserved?

Response:

### 3. Observation

Run `make autopsy` or the corresponding PowerShell target. Record the printed
root character and result. Trace the root index and child links from the
source, or inspect them with a debugger. Compare the faulty links with the textbook's
`root == 1`, `nodes[1].left == 0`, `nodes[1].right == 3`,
`nodes[3].left == 2`, and `nodes[3].right == 4`.

Response:

### 4. Assign the defect to the correct function

Trace evaluation of the faulty tree. Does the evaluator apply its stored
operators correctly? Why would changing evaluation to ignore the tree's
links undermine the representation instead of repairing construction?

Response:

### 5. Repair

Describe how separating `term()` from `terms()` changes the right operand
of addition. Explain which function consumes each operator and why `term()`
leaves the following `'+'` unread. Keep the same four-function interface.

Response:

### 6. Regression-test idea

Choose another valid expression for which treating all operators alike gives
a different answer. Record both expected groupings, the correct answer, and
at least one link assertion that would catch the defect.

This can supply the rationale for your construction test. No fourth coded
student test is required.

Response:

## After observation

Label corrections `index`, `precedence`, `parsing`, or `evaluation`.

The evidence that changed or confirmed my model was:

____________________________________________________________________
