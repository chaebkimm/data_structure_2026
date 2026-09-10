# Stage B — Five-Minute Cognitive Pause

Read the starting state with the instructor before timing begins. Then use
no notes, slides, neighbors, or coding tools for five minutes. You may draw,
type, dictate, or respond in numbered sentences.

Approved extended-time versions use the same three targets. Speed and drawing
quality are not assessed. Preserve your first response when correction begins.

## Starting state

After building `1+2*3`, `size == 5`, `pos == 5`, and `root == 1`:

| Index | `data` | `left` | `right` |
|---|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

Text equivalent: the plus node at 1 has children 0 and 3. The multiplication
node at 3 has children 2 and 4. Nodes 0, 2, and 4 are digit leaves.
Consider each target independently.

## Target 1 — Distinguish indices and characters

What do `root`, `nodes[root].left`, and `nodes[nodes[root].left].data`
contain? Why does child index 0 identify a real node, and what would child
index -1 mean?

Response:

____________________________________________________________________

## Target 2 — Stop at a term boundary

Start a fresh build with `eq` equal to `"1+2*3"`, `size == 0`, and `pos == 0`.
Call `terms()` and pause immediately after its first call to `term()` returns.
Which root index did `term()` return, what are `size` and `pos`, and which
character is left unread? Explain how the enclosing `terms()` call continues
building the sum without losing the multiplication's precedence.

Response:

____________________________________________________________________

## Target 3 — Return answers without changing nodes

Start again with the completed tree. Trace the values returned by
`eval_tree(root)`, evaluating the left child before the right child. What is
the final answer? What characters remain at indices 1 and 3? Explain the
base case and why the operator waits for its children's results.

Response:

____________________________________________________________________

## Calibration

After the instructor reveals the expert model:

1. Preserve your initial response.
2. Mark reasoning that remains correct.
3. Label corrections `index`, `parsing`, or `evaluation`.
4. Finish: “The evidence that changed or confirmed my model was …”
