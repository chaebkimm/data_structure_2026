# Module 12 Instructor Technical Notes — Indexed AVL Insertion

## Source and representation

The required implementation is [`student/lab.c`](../student/lab.c). It
includes `module_02_binary_tree/student/lab.c`, whose model is:

```c
struct TreeNode {
    char data;
    int left;
    int right;
};
struct TreeNode nodes[10];
```

Module 12 adds `height[10]`. An integer link/root is either `-1` or a valid
record ID 0 through 9. Keys are character data, not IDs. Records remain in
their array slots through every repair. `nodes_size` and `capacity` are
inherited Module 2 globals; `_add` neither allocates a slot nor maintains
an inserted-node count. A driver tracks the set of inserted IDs itself.

`alphabet_init()` assigns A through J and clears both child links of every
slot. It does not reset `height[]`; each fresh leaf receives height zero
on insertion. Start a new build with root -1 and reset all child links.
Do not use Module 2's preconnected demonstration tree as an AVL input.

## Caller preconditions

- The existing root describes an acyclic AVL tree with exact stored heights.
- Every reachable link is a valid ID, and every reachable record occurs once.
- `new_node` is a fresh valid ID outside that tree, with two `-1` links.
- At most ten distinct record IDs are inserted.
- The caller reconnects the returned root, including the top-level call:
  `root = _add(root, new_node)`.

The source has no capacity check, input parser, malformed-state detector,
error status, ownership API, or deletion routine. Invalid IDs or reinserting
a live ID do not produce a specified rejection. The lab is a bounded
algorithm demonstration, not a defensive container API.

## Height and classification

```text
get_height(-1) = -1
height(leaf) = 0
height(i) = 1 + max(height(left(i)), height(right(i)))
balance(i) = height(left(i)) - height(right(i))
```

The get helper guards `-1` before reading the array. AVL permits balance
values -1, 0, and 1. A valid insertion changes one path by at most one
level, so each examined balance lies in [-2,2]. The code handles precisely
these preconditions; initializing `root=i` is not a recovery procedure for
an arbitrarily malformed tree with a larger imbalance.

The balance calculation reads child heights, so the current `height[i]`
need not be refreshed before case selection. If no rotation occurs it is
updated in the balanced branch. If a rotation occurs, the affected nodes
are refreshed using their new children.

| Current factor | Child-height test | Case |
| --- | --- | --- |
| 2 | `height(ll) >= height(lr)` | LL |
| 2 | `height(ll) < height(lr)` | LR |
| -2 | `height(rr) >= height(rl)` | RR |
| -2 | `height(rr) < height(rl)` | RL |

These tests are equivalent to inspecting the relevant child's balance.
There is no inserted-key shortcut and no separate `avl_rebalance` call.

## Ordering with equal keys

`nodes[new_node].data <= nodes[i].data` directs equal keys left during
descent. A right rotation of three equal-key records necessarily leaves
an equal key on the right of the promoted root. The durable invariant is:

```text
all left-region keys <= node key <= all right-region keys
```

Equivalently, inorder is nondecreasing. A bounds-based validator must use
inclusive bounds, or independently verify inorder while also detecting
invalid/repeated IDs. Strict unique-key validation belongs only to the
optional pointer library. Equal data with different IDs is valid;
reinsertion of the same live ID is not.

## Rotation contracts and saved regions

The four helpers only assign links. Their caller supplies valid IDs,
including the relevant promoted child/grandchild. They do not validate
arguments, allocate storage, refresh metadata, or update an ancestor link.

| Helper | New links | Return |
| --- | --- | --- |
| `rotate_ll(i,l,lr)` | `i.left=lr`, `l.right=i` | `l` |
| `rotate_rr(i,r,rl)` | `i.right=rl`, `r.left=i` | `r` |
| `rotate_lr(i,l,lr,lrl,lrr)` | `l.right=lrl`, `i.left=lrr`, `lr.left=l`, `lr.right=i` | `lr` |
| `rotate_rl(i,r,rl,rll,rlr)` | `i.right=rll`, `r.left=rlr`, `rl.left=i`, `rl.right=r` | `rl` |

An argument named `lr` is the captured ID of `nodes[l].right`, not a key
or a height. Inner grandchildren must be read before rewiring. Saving
these regions in caller locals makes every retained subtree explicit.

For RR, use inorder regions `L, i, rl, r, rr`. Before repair, i has left L
and right r; r has left rl and right rr. After repair, r is root, i has
children L/rl, and r has children i/rr. The inorder region sequence is
unchanged. The other cases obey the same interval argument; equal keys
replace strict region inequalities with inclusive ones.

LR/RL helpers directly implement the effect of two single rotations.
Do not claim that the source invokes two helper calls for them.

## Metadata refresh proof

The code supplies the new child IDs directly to `set_height`:

| Case | Refresh calls in source order |
| --- | --- |
| LL | `set_height(i,lr,r)`; `set_height(l,ll,i)` |
| RR | `set_height(i,l,rl)`; `set_height(r,i,rr)` |
| LR | `set_height(i,lrr,r)`; `set_height(l,ll,lrl)`; `set_height(lr,l,i)` |
| RL | `set_height(i,l,rll)`; `set_height(r,rlr,rr)`; `set_height(rl,i,r)` |

All unchanged regions already have exact heights. Each demoted node is
therefore computable from exact child values, and the promoted root is
then computed from those refreshed values. In a double repair the first
two lower-node updates are independent; either order is mathematically
valid, while the table records this exact source order.

Direct rotation tests should check their stated link-only contract.
Insertion tests should check both links and heights after `_add` returns.
Requiring a helper alone to refresh heights would test a different API.

## Recursive unwind

The returned ID may be a different local root. Chained assignment updates
both the actual parent link and the local cache:

```c
l = nodes[i].left = _add(l, new_node);
```

The corresponding right branch updates r. Using the old child ID after a
recursive rotation would calculate the wrong height difference. Default
`root=i`, then use the `if`/`else if` chain for balanced, left-heavy, and
right-heavy cases. Return `root` once at the end. At `i==-1`, return the
new leaf directly.

## Exact fixtures

Use alphabet IDs A=0 through G=6. All four canonical triples finish at ID1
(B), children ID0 and ID2, heights 1/0/0:

```text
LL: C B A       RR: A B C
LR: C A B       RL: A C B
```

For `F D G B E A`, LL repair at F retains middle E as F's left child.
Root becomes D, with B(A,-1) and F(E,G); heights are D2, B1, F1, A/E/G0.

| Order | Plain root/height | Present/missing target | Plain counts | AVL root/height/counts |
| --- | --- | --- | --- | --- |
| `A B C D E F G` | A / 6 | G / H | 7 / 7 | D / 2 / 3,3 |
| `G F E D C B A` | G / 6 | A / @ | 7 / 7 | D / 2 / 3,3 |
| `D B F A C E G` | D / 2 | G / H | 3 / 3 | D / 2 / 3,3 |

Every final AVL has `D(B(A,C),F(E,G))`. The baseline and lookup operations
are driver support. They are not present in the supplied lab source.

## Diagnostic and boundary strategy

Use an independent recursive traversal that rejects invalid IDs before
array access, tracks seen IDs to detect repeated records, counts reachable
IDs, checks nondecreasing inorder, calculates actual height from links,
and compares it with `height[]` plus factor bounds. Compare visited IDs
with the exact inserted-ID set so missing records cannot hide behind
sorted output. A visit-once array/bitset implementation is O(n) time and
O(n) bookkeeping; its recursion uses O(h) stack space. Keep these costs
separate from insertion.

Test empty and singleton trees, every canonical repair, nonempty inner
regions, duplicate data in distinct records, every capacity position, and
reset between experiments. Do not use invalid memory accesses as tests
for a rejection mechanism that is absent. Sanitizers can check executed
array accesses; they do not establish sorted order or exact heights.

## Complexity and security

Each helper changes a fixed number of links; each local refresh reads two
cached heights. One recursive insertion takes O(h) time and stack. For a
generalized AVL tree that is O(log n); an unbalanced plain BST can take
O(n). Directed lookup has the same O(h) shape dependence. Inorder and
independent full-height measurement take O(n). The actual arrays remain
fixed at ten records; state this cap beside generalized bounds.

Sorted valid insertion order can create algorithmic-complexity denial of
service in a scalable plain BST. This is excess valid work, distinct from
memory corruption or proof of broad resource exhaustion. AVL prevents
that shape-driven degradation but does not supply input validation,
capacity guards, authentication, concurrency control, or service-level
availability.

An overwritten middle link loses reachability, not heap allocation: all
records still occupy the fixed array. The optional pointer autopsy can
demonstrate a real allocation leak, but it is a different implementation.

## Optional reference boundary

The retained `code/include`, `starter`, `solution`, `support`, older tests,
and pointer autopsy use a 64-node allocated API with unique integer keys,
status codes, failure preservation, allocator hooks, and iterative
destruction. Keep its targets and explanation separate in the code guide.
It is optional extension material and does not define the required source
contract, student tests, or Week 12 submission.
