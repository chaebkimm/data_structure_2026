# Lab — Traverse, Build, and Write an Array-Based Expression Tree

## Purpose

Trace and verify [`lab.c`](lab.c) in the order of
[the lab slides](ppt_lab_material.md): recursive DFS, progress-state stack
DFS, postfix tree construction, and precedence-aware infix reconstruction.
The source reuses Chapter 2's array of tree nodes and Chapter 4's shared
integer stack and postfix buffer.

```text
1-2*3+4 → 123*-4+ → an expression tree → 1-2*3+4
```

Construction records a tree's shape. Writing reconstructs its expression;
these functions do not calculate an arithmetic value.

## 1. Follow array indices and locate the visit hooks

A node stores `char data` and integer `left` and `right` indices. `-1`
means an absent child. After `alphabet_init()` and `tree_connect()`, the
root is `F [5]`, and the reachable nodes are `F, A, B, C, D, E, G`.
`nodes_size == 10` also counts initialized but unconnected `H, I, J`.

`tree_traversal(i)` returns immediately for a negative index. Its three
comments mark where preorder, inorder, and postorder actions belong:
before the left call, between the child calls, and after the right call.
The current source does not print symbols or save visit values.

Record these orders on paper, in a debugger, or using assigned hook actions:

| Hook | Complete symbol order |
| --- | --- |
| Preorder | `F A B D E C G` |
| Inorder | `D B E A C F G` |
| Postorder | `D E B C A G F` |

At `D`, explain the unfinished work of `F`, `A`, and `B`. Count four
real-node calls plus the temporary empty-child call. A complete trace
needs successive records; overwriting one variable loses earlier symbols.

## 2. Resume DFS with a stack and progress

`tree_traversal_with_stack(root_index)` sets `top = -1`, pushes the root,
and repeatedly calls `tree_traversal_proceed(peek())` while nonempty.
The helper receives the top node index. A negative entry is popped before
reading node data or `progress`.

For a real node, `int step = progress[i]++;` copies the old step and
advances progress. Step 0 marks preorder and pushes the left child; step 1
marks inorder and pushes the right child; step 2 marks postorder and pops
the node. The parent remains below its child with its next step recorded.
Each leaf pushes and removes two `-1` entries before its own removal.

Trace the array indices, old step, new progress, and stack contents through
`D` and the first preorder hook at `E`. A completed run leaves `top == -1`
and progress 3 at reached nodes. The wrapper resets `top`, but does not
reset progress. Before another traversal, set every progress entry to 0,
including when construction has replaced the nodes. Diagnose stale progress
on paper: steps 3 and above have no `switch` case that removes the node.

## 3. Create the tree from postfix

`postfix` initially contains an empty string. Populate it using
`convert_to_postfix()` or a valid string of at most seven tokens before
calling `build_tree_from_postfix()`.

The builder resets `top` and `nodes_size`. Each token at position `i`
becomes node `i`. A digit gets two `-1` children. An operator pops the right
root first, then the left root, attaches them, and pushes its own index.
After valid input, the final `return pop()` returns the sole root and
leaves the stack empty.

For `123*+`, record the stack states `[0]`, `[0,1]`, `[0,1,2]`, `[0,3]`,
and `[4]`, followed by the final pop returning 4. `nodes_size == 5`,
`top == -1`, and peak stack usage is three. Use `12-` to demonstrate why
reversing the pops changes the expression. Building replaces the previous
contents of the shared node array.

## 4. Write inorder with precedence and grouping

`prec2()` returns 3 for digits and uses Chapter 4's `prec()` for other
characters: 2 for `* / %`, 1 for `+ -`. A digit writes one character.
An operator writes its left expression, its symbol, and its right expression.

Put parentheses around a child when:

- the left child's precedence is lower than the parent's; or
- the right child's precedence is lower than or equal to the parent's.

The equality on the right preserves grouping under left associativity.
Digits' higher precedence prevents unnecessary parentheses around leaves.
The aim is to retain the tree's grouping, rather than simplify by arithmetic
identities.

| Postfix | `write_infix()` output |
| --- | --- |
| `123*+` | `1+2*3` |
| `12+3*` | `(1+2)*3` |
| `123--` | `1-(2-3)` |
| `12-3-` | `1-2-3` |
| `123++` | `1+(2+3)` |
| `1234+++` | `1+(2+(3+4))` |

`write_char()` advances the shared `infix_pos`. `write_infix(root)` resets
that position to 0, calls `_write_infix(root)`, and writes `'\0'`. For
`1+2*3`, the terminator is at index 5 and final `infix_pos == 6`. A second
complete write starts at zero; do not reset the cursor inside child calls.
A negative root writes the empty string, but this guard does not validate
missing children of an operator.

## 5. State assumptions and costs

Provide a valid tree with initialized indices, no cycles, and no shared
children. For construction, use a nonempty valid postfix expression of
single-digit operands and binary `+ - * / %` with no whitespace, unary
signs, or multi-digit operands. Every operator needs two waiting roots and
exactly one root must remain at the end. The builder treats every nondigit
as an operator and does not validate these conditions.

`nodes[10]`, `stack[10]`, and `progress[10]` reserve ten entries each.
`postfix[8]` holds seven tokens and a terminator. `infix[20]` accommodates
the grouping parentheses for this range: `1+(2+(3+4))` needs twelve cells
including `'\0'`. Neither the builder nor writer checks bounds. A manually
constructed ten-node chain needs eleven traversal stack entries including
its absent child and exceeds the current stack capacity.

Construction takes `O(n)` time in tokens. Traversal and writing take `O(r)`
time in reachable nodes. Recursive frames and the used iterative path take
`O(h + 1)` space for height `h` in edges; stack traversal also reserves
per-node progress. Generalized postfix construction can require `O(n)`
stack entries. Distinguish these used-space costs from fixed array storage.

## 6. Run and add three justified cases

`lab.c` has no `main`. The supplied [lecture driver](../code/lecture/lab_demo.c)
uses it directly. From `module_05_tree_dfs/code`, run:

```sh
make lecture
make lab-tests
```

For PowerShell, run the matching targets with `./build.ps1 -Target lecture`
and `./build.ps1 -Target lab-tests`. Use `code/README.md` for compiler setup
and include-path details. Preserve complete commands, compiler diagnostics,
and output. The demo's traversal report reflects comments and progress;
a symbol trace needs an actual recording action at the visit hooks.

Keep supplied tests intact and add exactly three focused cases to
`code/tests/test_lab.c`, following its harness and calling each new case:

1. A valid traversal shape that tests progress and an absent-child entry;
   reset progress deliberately before every independent traversal.
2. A valid postfix construction that checks data, child indices, returned
   root, node count, and final empty stack; choose a case where side matters.
3. Grouping or repeated writing that checks exact text, actual terminator,
   final cursor, and the wrapper's reset.

State the additional claim each case tests. Use valid input and respect
unchecked stack preconditions. Run the lab tests again and complete the
[investigation worksheet](investigation_worksheet.md) and
[evidence record](evidence_template.md). Preserve and correct the
[Cognitive Pause](cognitive_pause.md).

## Optional scaffold and extensions

The pointer-based starter/solution in `code/starter`, `code/solution`, and
`code/include` has a separate interface for preorder copy, inorder printing,
and postorder evaluation, with checked failures and caller-owned state.
Its `(3+5)*2` example, value 16, and rollback behavior are optional
comparison exercises. The [Tree Copy Autopsy](tree_dfs_autopsy.md) belongs
to that scaffold. Those guarantees are not implemented by the core lab.

Reconstruction from distinct preorder/inorder labels is a separate concept
exercise in [the general slides](ppt_material.md). Optional core extensions
include progress reset in the traversal wrapper, input and shape validation,
capacity guards, or generalized token storage. State each new contract
before claiming a feature the current source does not provide.
