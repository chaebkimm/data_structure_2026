# Stage B — Five-Minute Cognitive Pause

Read the starting state with the instructor before timing begins. Then use
no notes, slides, neighbors, or coding tools for five minutes. You may draw,
type, dictate, or respond in numbered sentences.

Approved extended-time versions use the same targets. Speed and drawing
quality are not assessed. Preserve your first response when correction begins.

## Starting state

Five initialized local node variables represent `(3 + 5) * 2`:

| Variable | Data | Left address | Right address |
|---|---:|---|---|
| `root` | `'*'` | `&plus` | `&two` |
| `plus` | `'+'` | `&three` | `&five` |
| `three` | `3` | `NULL` | `NULL` |
| `five` | `5` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

All objects remain alive during this activity. Consider each target
independently, starting from this state.

## Complete exactly three targets

### Target 1 — Preserve the side positions

The caller removes the whole left branch below `root`. What should
`root.left` and `root.right` contain afterward? Is a right child without a
left child valid as a general binary tree? Does the result still represent a
completed binary expression? Explain the distinction.

Response:

____________________________________________________________________

### Target 2 — Check the whole-tree rule

Suppose someone connects `three.left` back to `&root`. That side is currently
empty. Is an empty-side check enough to make the new link valid?

Name the broken rule. State whether the caller must prevent this change or
may expect the search function to reject it safely.

Response:

____________________________________________________________________

### Target 3 — Trace the search

A recursive search checks the current node, then the left subtree, then the
right subtree. It stops at its first match.

List the data values checked by `tree_find(&root, 2)`, ending at the match.
Why does the binary shape not provide a value-order rule for skipping a
subtree?

Response:

____________________________________________________________________

## Calibration

After the instructor reveals the expert model:

1. preserve your initial response;
2. mark reasoning that remains correct;
3. label each correction `position`, `invariant`, or `search`; and
4. finish the sentence below.

The evidence that changed or confirmed my model was:

____________________________________________________________________
