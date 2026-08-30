# Instructor Answer Key — Module 2

Keep this file instructor-only. Students preserve an initial attempt before
calibration and an autopsy prediction before observation.

## Macro-question synthesis

Separate local objects form a hierarchy when their child fields store
addresses of other live objects. Every node has two named child positions,
left and right. Either position may be empty independently.

The caller constructs a finite, acyclic, unshared tree. The two recursive
functions assume those rules; they do not certify arbitrary link patterns.
Operators and numbers are data, not directions for choosing a search branch.

## Stage A — Initial inquiry

### A. Reconstruct the hierarchy

```text
                 '*'
                /   \
              '+'    2
             /   \
            3     5
```

- Starting item: `'*'`.
- Items with nothing below them: `3`, `5`, and `2`.
- Route to `5`: `'*' -> '+' -> 5`.
- Maximum number immediately below an item: two, one at each named side.

The tree represents `(3 + 5) * 2`. Left and right preserve operand order;
they are not interchangeable expression positions.

Accept a side-labeled table or linear description instead of a drawing.

### B. Preserve the hierarchy

1. Giving the existing `five` object another incoming link from `two.left`
   shares one node between two routes. That is no longer this module's
   unshared tree.
2. Linking `three` back to `root` creates the cycle
   `root -> plus -> three -> root`. Repeated downward processing cannot rely
   on reaching an empty link along that route.
3. Removing the left `plus` branch below `root` leaves `two` on the right.
   Side identity does not depend on a neighboring side being occupied. The
   result is a valid general binary tree with one child, but it is no longer
   a completed binary expression because `'*'` lacks its left operand.

Suitable rules include no sharing, no cycles, at most one item on each
named side, and one starting root.

### C–D. Model and storage brainstorm

Each object needs its data and a way to identify each child. A special empty
marker represents an unused position. Related objects need not be physically
adjacent. Two objects storing the same integer remain different objects.

Do not require pointer vocabulary before the Stage B reveal. A response
such as “remember where the left and right items are” is a sound initial
model.

## Stage B — Representation and pause

### Canonical local-node table

| Variable | Data | Left address | Right address |
|---|---|---|---|
| `root` | `'*'` | `&plus` | `&two` |
| `plus` | `'+'` | `&three` | `&five` |
| `three` | `3` | `NULL` | `NULL` |
| `five` | `5` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

### Target 1 — Preserve the sides

After complete removal of the root's left branch:

```c
root.left == NULL
root.right == &two
```

A right child without a left child is valid. The removed local objects have
been cleared but remain alive while their scope is active. The remaining
shape is not a completed binary expression because the root operator has only
one operand.

### Target 2 — Whole-tree rule

`three.left = &root` would create a cycle. An empty `three.left` proves only
that this one field is unused; it does not make the whole relationship safe.
The caller must prevent the change. Neither search nor clearance is a
cycle-rejection routine. Do not run the invalid example recursively.

### Target 3 — Search order

`tree_find(&root, 2)` checks:

```text
'*', '+', 3, 5, 2
```

It returns `&two`. There is no value-order guarantee: the complete left
subtree must be searched before the right operand, because the expression
shape encodes operations and operands rather than binary search ordering.

## Stage C — Investigation

Each independent operation starts again from the supplied Stage C state.

### D. Translate among representations

```text
                  root:'*'
                  /       \
             minus:'-'    plus:'+'
               /   \       /   \
          eight:8 three:3 four:4 two:2
```

| Variable | Data | `left` | `right` |
|---|---|---|---|
| `root` | `'*'` | `&minus` | `&plus` |
| `minus` | `'-'` | `&eight` | `&three` |
| `plus` | `'+'` | `&four` | `&two` |
| `eight` | `8` | `NULL` | `NULL` |
| `three` | `3` | `NULL` | `NULL` |
| `four` | `4` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

Direct relationships include:

```c
root.left = &minus;
root.right = &plus;
minus.left = &eight;
minus.right = &three;
plus.left = &four;
plus.right = &two;
```

| Expression | Meaning |
|---|---|
| `root` | the node object |
| `&root` | that object's address |
| `root.data` | `'*'` |
| `root.left` | `&minus` |
| `root.left->data` | `'-'`, reached through the stored left address |
| `NULL` | no child at the selected position |

### E. Paths and positions

- Path to `four`: `'*' -> '+' -> 4`.
- Depth of `four`: 2.
- Leaves: `eight`, `three`, `four`, and `two`.
- Height of `minus`: 1.
- Height of `root`: 2.
- Subtree rooted at `minus`: `minus`, `eight`, and `three`.

Count links, not nodes. A leaf has height zero. Parent and ancestor remain
relationship words, but the node stores no upward link. The diagram or a
route from a known root supplies that context.

### F. Invariants versus local checks

The representation has at most two children, distinguished as left and
right. Every reachable non-root node has one incoming tree link; no node is
shared, and no downward route repeats a node. All referenced objects must
be initialized and alive.

The four rule blanks are zero incoming links at the root, one incoming link
at each other node, a cycle, and alive.

| Proposed change | Judgment |
|---|---|
| attach a fresh initialized `n7` to empty `two.left` under the general tree contract | valid if its lifetime is sufficient, though it no longer represents the supplied binary expression |
| put `&n7` in occupied `root.left` without replacement | not permitted; the empty-side guard prevents the write |
| also put existing `&three` in `four.left` | invalid sharing, even if the selected side is empty |
| connect `eight.left` to `&root` | invalid cycle |
| put `&n7` in both sides of `two` | invalid repeated incoming link, even though both fields can hold an address |

The `if` check establishes only whether that side is empty. There is no
status value or automatic whole-tree rejection. The caller must not perform
a link assignment that would violate the global rules.

### G. Local-node lifetime and clearance

| Action | Judgment and explanation |
|---|---|
| initialize data and both links before use | safe and required before linking the node |
| follow a node whose child links were never initialized | unsafe; those fields do not yet identify valid children or empty sides |
| inspect `minus.data` after `tree_clear(&minus)` while still in scope | valid; the data is zero |
| keep using the address of a local node after its scope ends | invalid lifetime use |

Clearance resets contents. It does not destroy the local variable.
Reinitialization and reuse are possible while that object remains alive and
unlinked. Zero is an ordinary value, not a “no node” marker; `NULL` marks an
empty link.

Passing an address to another function does not extend the local object's
lifetime. The declaring block still controls when it ends.

### H. Selected-side attachment and removal

In the separate worksheet example, `parent.left == NULL` and
`parent.right == &n8`. The parent is not a leaf because its right child is
present. Attaching fresh `n4` to the selected left side gives:

```c
if (parent.left == NULL) {
    parent.left = &n4;
}
```

The two links are then `&n4` and `&n8`. If the selected left field were
occupied, the guard would leave it unchanged; it would not silently use the
right side instead.

For removal:

```c
tree_clear(parent.left);
parent.left = NULL;
```

The links become `NULL` and `&n8`. The right field keeps its identity and
original address. Clearing an empty selected side and assigning `NULL` again
is harmless.

### I. Recursive search

Complete current-left-right sequence:

```text
'*', '-', 8, 3, '+', 4, 2
```

Searching for `4` checks `'*', '-', 8, 3, '+', 4` and returns `&four`.
Searching for 404 checks all seven nodes and returns `NULL`.
If `two.data` is separately changed to `4`, a search for `4` still returns
`&four`: it checks `'*', '-', 8, 3, '+', 4` and stops before `two`. The return
value identifies that object rather than merely reporting the integer.

Changing `eight.data` to 900 does not break a tree rule. A search for 900
checks `'*', '-', 900` and finds `&eight`. The lack of a value-order invariant
means the left subtree cannot be skipped based on a comparison with root data.

A correct function handles `NULL`, checks the current node, searches left,
returns a left match immediately, then searches right. Search does not
change any field. Worst-case work is `O(n)`.

### J. Cascading clearance and removal

For the Stage C left branch:

1. clear `eight`;
2. clear `three`;
3. clear `minus`; and
4. set `root.left` to `NULL`.

The three cleared objects each end with data zero and both links empty.
The surviving root still stores `'*'`, and `root.right == &plus`. The plus
node and its children `four` and `two` are unchanged. No child changes sides.
The remaining links form a valid generic binary tree but not a completed
binary expression, because the root operator now has only its right operand.

If the caller only runs `tree_clear(&minus)`, `root.left` still contains
`&minus`. The additional assignment is what detaches that cleared branch.

Calling `tree_clear(&root)` resets all seven node objects but does not end
any of their lifetimes. Calling it again is safe. A later
`tree_find(&root, 0)` returns `&root`, because that live node now stores
zero. The detached descendants are no longer reachable from it.

| Operation | Work | Reason |
|---|---:|---|
| initialize one existing node | `O(1)` | set three fixed fields |
| attach to a known empty selected side | `O(1)` | one check and one link write |
| search data | `O(n)` worst case | a missing value can require every node |
| clear a selected subtree | `O(k)` | reset each of its `k` nodes |
| detach a known side alone | `O(1)` | write one `NULL` |
| clear and detach | `O(k)` | recursive clearance dominates |

Each node always includes space for its two pointers, including a leaf.
Recursive call-stack space is proportional to the longest pending route,
`O(h + 1)` when height counts links.

### K. Tree-to-graph transfer

A reused subexpression referenced by two operators may need a directed
acyclic graph rather than a tree. A relationship model that also permits
cycles needs a more general directed graph. A tree assumes one route to each
node from its root; shared or returning relationships require different
processing rules, commonly including remembering which objects have already
been visited.

Students explain this distinction; they do not implement a graph validator
or repair arbitrary graphs with the two tree functions.

### L. Exit anchors

A child field stores an address or `NULL`. Both child positions are
independent. The caller keeps objects alive and prevents sharing and cycles.
Search is current node, left subtree, right subtree. Clearance resets every
reachable node, and removal also needs the caller to erase the selected
incoming link. No side shifting occurs.

## Exact implementation boundary

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *tree_find(struct TreeNode *node, int target);
void tree_clear(struct TreeNode *node);
```

Only the two function bodies are starter TODOs. Direct initialization,
guarded attachment, and explicit detachment belong in examples and tests.
Do not grade an invented constructor, count query, status type, or validation
helper as required work.

In formal traversal terminology the search order is preorder. Chapter 2
requires the sequence and reasoning, not memorization of this later label.

## Tree Structure Autopsy — worked instructor answers

### Starting links

All six variables remain alive throughout the fixture. The intended reading
is `(3 + 5) * (5 - 2)`, but both written `5` operands incorrectly identify
one shared node object.

| Object and data | `left` | `right` |
|---|---|---|
| `root`, `'*'` | `&plus` | `&minus` |
| `plus`, `'+'` | `&three` | `&shared_five` |
| `minus`, `'-'` | `&shared_five` | `&two` |
| `three`, `3` | `NULL` | `NULL` |
| `shared_five`, `5` | `NULL` | `NULL` |
| `two`, `2` | `NULL` | `NULL` |

The initializer for `minus` first violates the unshared-tree rule when its
left field receives `&shared_five` while `plus.right` already holds that
address. The fact that this is a newly initialized field is not evidence that
`shared_five` is unlinked elsewhere.

### Predicted consequence

The fixture performs correct recursive clearance on the left branch, then
sets `root.left = NULL`.

```text
root.left  = NULL
root.right = &minus
minus.data = '-'
minus.left = &shared_five
minus.right = &two
shared_five.data = 0
shared_five.left = NULL
shared_five.right = NULL
plus.data = 0
plus.left = NULL
plus.right = NULL
three.data = 0
two.data = 2
```

The program's exact observations are:

```text
before: shared operand data=5
after clearing and detaching the plus branch:
root.left is NULL: yes
root.right still points to minus: yes
minus.left still points to shared_five: yes
minus.left->data=0
```

The shared operand remains alive at the same address. The surviving minus
route still reaches it, but it now contains zero rather than 5. This is
not an expired pointer, and a memory sanitizer need not complain.

The defect is the invalid shared relationship, not the supplied
`tree_clear` implementation. Changing clear to skip a descendant or
preserve its data would break the valid-tree contract.

### Repair and regression evidence

Keep one incoming link to the shared object, or use distinct `left_five` and
`right_five` objects if both expression positions need the value 5. Equal
data does not make two operands the same object. If the application truly
needs a shared reusable subexpression, choose a later graph representation
with an appropriate processing policy.

A valid regression fixture can give the left and right branches distinct
operand objects that both store 5. After removing the plus branch, assert that
the minus branch's operand remains at its original address with data 5, while
all plus-branch objects are zeroed and `root.left == NULL`.

This explanation may support one of the three required student tests; the
autopsy does not require a fourth coded test. Do not claim the regression
fixture turns the library into an automatic sharing detector.

## Assessment alignment

| Criterion | Points |
|---|---:|
| Representation and invariants | 20 |
| Direct node operations | 15 |
| Recursive search | 20 |
| Clearing, removal, and lifetime | 20 |
| Operation efficiency | 10 |
| Tests and tool evidence | 10 |
| Autopsy and forward transfer | 5 |
| Total | 100 |

The three authored-test slots cover search boundaries/duplicate order,
direct linking/occupied sides/detachment, and recursive clearance/live-node
reuse, in that order. Together they must show the opposite side is unchanged.
Require distinct claims and rationales; copying the same test with different
data is insufficient.

Accept equivalent linear descriptions, verbal explanations, and approved
tool evidence. Do not penalize an initial misconception that is preserved
and meaningfully corrected.
