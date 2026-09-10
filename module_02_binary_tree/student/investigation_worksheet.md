# Stage C — Investigation: Build and Evaluate an Expression Tree

Name: ____________________________
Date: ____________________________

Open this file after preserving the Cognitive Pause and completing calibration.
Use a diagram or a written explanation. Preserve predictions before checking.

## Quick reference

Each array node has `char data`, `int left`, and `int right`. Child indices
use `-1` for absence; `0` is valid. `size` is the number of used nodes, and
`pos` is the next unread position in `eq`. An expression has single digits
alternating with `+` or `*`, no spaces or parentheses, and at most 19
characters. Assume every intermediate and final answer fits in `int`.

A new independent build starts with `size = 0`, `pos = 0`, and a valid string
in `eq`. These activities require no malformed-input or whole-tree validator.

## D. Translate among representations

The independent transfer tree represents `2*3+4*5`, with `size == 7`,
`pos == 7`, and `root == 3`.

| Index | `data` | `left` | `right` |
|---|---|---:|---:|
| 0 | `'2'` | -1 | -1 |
| 1 | `'*'` | 0 | 2 |
| 2 | `'3'` | -1 | -1 |
| 3 | `'+'` | 1 | 5 |
| 4 | `'4'` | -1 | -1 |
| 5 | `'*'` | 4 | 6 |
| 6 | `'5'` | -1 | -1 |

1. Draw the tree or describe every connection, including its side.
2. Complete `nodes[3].left = ...`, `nodes[3].right = ...`,
   `nodes[1].right = ...`, and `nodes[5].left = ...`.
3. Explain the meaning and value of `root`, `nodes[root].data`,
   `nodes[root].left`, `nodes[nodes[root].left].data`, and `-1` as a child link.

Response:

## E. Name positions

Depth counts links from the root. Height is the greatest number of downward
links to a leaf. A subtree contains a node and all its descendants.
Use the section D tree.

1. Write the data path from the root to index 4.
2. Give the depth of index 4.
3. List the leaf indices.
4. Give the height of index 1, then of the root.
5. List the indices in the subtree rooted at index 1.

Response:

## F. State and preserve invariants

1. How many incoming child links does the root have? How many does each
   other node have?
2. What range contains every present child index? How are absent children
   represented?
3. Explain why adding the link `nodes[0].left = 3` creates a cycle.
4. Explain why assigning `nodes[5].left = 2` would share a child and leave
   index 4 unreachable from the root.
5. Why does joining disjoint subtrees under a fresh operator preserve the
   one-parent and no-cycle rules? Does an empty child position alone prove
   that any proposed link is valid?
6. Can a general binary-tree node have only a right child? Why does a
   completed `'+'` or `'*'` node in this module require both children?

The changed states in questions 3 and 4 are paper reasoning cases. The
provided functions assume valid trees and do not validate these defects.

Response:

## G. Reserve a node and follow the shared state

Start an independent build with `size == 0`.

1. After `int a = new_node('0');`, what are `a`, `size`, and all three
   fields of `nodes[a]`? Distinguish character `'0'`, integer 0, and index 0.
2. Next, call `int b = new_node('7');`. What are `b` and `size`? Does this
   make either node a child of the other?
3. Why must both child fields be initialized even though the array exists
   for the entire program?
4. Before building an unrelated expression, why reset both `size` and `pos`?
   What happens to the meaning of an old root index as array slots are reused?
5. A valid input has at most 19 characters. Why do `eq[20]` and `nodes[20]`
   suffice under this contract?

Response:

## H. Trace the two parsing levels

Start fresh with `eq` equal to `"2*3+4*5"`, `size == 0`, and `pos == 0`.

1. Call only `term()`. Record the returned root, `size`, `pos`, and next
   unread character. List the links created.
2. Start fresh again and trace `terms()`. Record the current root, `size`,
   and `pos` after its first term, after reserving `'+'`, after its next term,
   and when the function returns.
3. Why must the right operand of `'+'` be built by `term()` instead of
   consuming just one digit?
4. Explain how `eq[pos]` and `eq[pos++]` differ. Why is the next `'+'` left
   unread by `term()`? What character remains after `terms()` finishes?

Response:

## I. Trace recursive evaluation

Start with the completed section D tree.

1. List the node indices in call-entry order when the left child is evaluated
   first. Then list the index and value for each return in completion order.
2. What does a digit leaf return, and why is subtracting `'0'` correct?
3. Why must the two child results be available before applying an operator?
4. What is the final answer? What characters remain in the operator nodes?
5. Which fields and shared variables should a second evaluation leave
   unchanged? How could a test check this?

Response:

## J. Explain association and count work

1. Build `2*3*4` from fresh state on paper. Give the final root index and its
   left and right child indices. Which `'*'` is above the other, and why?
2. Repeat for `1+2+3`. Addition and multiplication give the same arithmetic
   answer under either association for these inputs. Why must a test inspect
   links to prove that construction groups equal operators left to right?
3. Let `n` be the number of expression characters/nodes, and `h` the longest
   root-to-leaf path in links. Count work for reserving one node, assigning
   one child link, parsing the whole expression, and evaluating it.
4. Explain the storage used by the fixed array, its `n` occupied slots, the
   two parser levels, and the evaluator's longest active call chain.

Response:

## K. Transfer the model

1. Use `8+2*0` to explain why the character `'0'` is an ordinary operand and
   cannot serve as an absent-child marker.
2. A later relationship model may allow two parents to share one item.
   Give a useful example and state which tree rule would change.

Response:

## L. Exit ticket

1. What does a child link store, and which value means no child?
2. What do `size` and `pos` count?
3. Where does `term()` stop, and how does `terms()` preserve precedence?
4. What is the evaluator's base case? Does evaluation replace operator data?
5. Which four functions will you implement in the lab?

Response:
