# Module 14 Instructor Technical Notes

## 1. Contract summary

The package separates the shared model, supplied plain-BST baseline, and
student AVL work.

```text
code/include/tree_model.h
code/include/bst_baseline.h
code/include/avl_tree.h
code/support/tree_support.c
code/starter/avl_rotations.c
code/starter/avl_tree.c
code/tests/test_core.c
code/tests/test_student.c
code/autopsy/faulty_left_rotation.c
```

`BST_AVL_MAX_NODES` is 64. `Tree` owns every `TreeNode` reachable from
`root`; `size` is the exact reachable count. A node stores one integer key,
cached edge height, and left/right pointers.

The empty/destroyed state is exactly `{root=NULL,size=0}`. Do not
reinitialize a live object. Strict unique keys mean equality returns
`TREE_DUPLICATE`.

Status values are:

```text
TREE_OK
TREE_INVALID_ARGUMENT
TREE_FULL
TREE_DUPLICATE
TREE_ALLOCATION_FAILED
TREE_INVALID_STATE
```

Reported failures preserve the public structure and output objects.

## 2. Height convention

The course uses edge height:

```text
actual_height(NULL) = -1
actual_height(leaf) = 0
actual_height(node) =
    1 + max(actual_height(node->left), actual_height(node->right))
```

The balance factor is left height minus right height. AVL permits only
`-1,0,1`.

This convention is consistent with Module 8. A chain of `n` nodes has
height `n-1`. Search comparisons count visited nodes, so the corresponding
deepest successful search has `n` comparisons.

The plain BST baseline intentionally does not refresh cached heights.
`tree_validate_bst` therefore ignores `node->height`. Use
`tree_actual_height` for baseline measurements. AVL insertion must keep
cached heights exact, and `tree_validate_avl` checks them.

## 3. Whole-subtree ordering

Immediate-child comparison is insufficient. Validation carries optional
strict lower and upper bounds:

- a left recursive call inherits the lower bound and sets the current key
  as upper bound;
- a right recursive call sets the current key as lower bound and inherits
  the upper bound.

Strict comparisons reject duplicates anywhere. Integer bounds use Boolean
presence flags rather than invented `INT_MIN-1` or `INT_MAX+1`, so all
integer keys remain representable.

## 4. Supplied BST baseline

`bst_insert_baseline` is recursive and bounded by 64. It first rejects:

- `NULL` tree;
- contradictory root/size or size over 64;
- a duplicate found within the bounded lookup; and
- full capacity.

It allocates only at the selected `NULL` link. The baseline deliberately
does not rebalance and deliberately leaves old cached heights alone.

`bst_search` reports:

- `out_found`;
- `out_comparisons`, one per visited node; and
- status.

Output pointers must be non-`NULL`, distinct, and not overlap the tree or
its nodes as documented by the interface. Failure preserves both outputs.
A `NULL` terminator adds no comparison.

## 5. Rotation proof

For a left rotation, use ordered regions:

```text
L < X < M < Y < R
```

Before:

```text
        X
       / \
      L   Y
         / \
        M   R
```

After:

```text
        Y
       / \
      X   R
     / \
    L   M
```

The inorder region sequence is unchanged. The exact safe implementation is:

```c
upper = root->right;
middle = upper->left;
root->right = middle;
upper->left = root;
refresh_height(root);
refresh_height(upper);
return upper;
```

The right rotation is the mirror. Required-child absence returns the input
root unchanged.

The old root becomes lower, so refresh it first. The new root's correct
height depends on that refreshed value.

No allocation or release occurs during a rotation. Ownership is preserved
only if the middle subtree is reconnected. A fixture with `middle=NULL`
cannot detect the canonical lost-middle leak.

## 6. Rebalance classification

`avl_rebalance(TreeNode *node)` has no inserted-key parameter. It refreshes
the node and classifies by child balance factors:

```text
node factor > 1:
    left factor >= 0 -> LL -> rotate right(node)
    left factor < 0  -> LR -> rotate left(node->left),
                              rotate right(node)

node factor < -1:
    right factor <= 0 -> RR -> rotate left(node)
    right factor > 0  -> RL -> rotate right(node->right),
                               rotate left(node)
```

The nonnegative/nonpositive cases also support rebalance reuse in a future
deletion implementation. An inserted-key shortcut is acceptable for paper
traces but is not the public helper's contract.

## 7. AVL insertion and failure preservation

The public operation performs shallow validation, bounded duplicate search,
and the capacity check before recursion. The recursive helper:

1. calls `tree_node_create` only at `NULL`;
2. returns the old path unchanged on allocation failure;
3. stores a returned child only after `TREE_OK`;
4. rebalances the current node on successful unwind; and
5. returns the possibly new subtree root.

The public operation commits root and increments size only after success.
There is at most one new allocation. No old node is released or newly
allocated during rotations.

If the code implementation changes to perform complete prevalidation,
account for the validator's separate cost. Do not silently advertise the
diagnostic scan as part of `O(log n)` AVL insertion.

Full AVL deletion is deliberately excluded. Deletion can change balance at
multiple ancestors and has additional successor/predecessor and ownership
cases.

## 8. Validators

Both validators first check:

- non-`NULL` tree;
- size at most 64; and
- exact root/empty agreement.

They then check:

- no pointer appears twice, detecting sharing or a cycle;
- strict whole-subtree lower/upper bounds; and
- visited count equals `size`.

The AVL validator additionally computes actual heights bottom-up, checks
every cached height, and requires factor in `[-1,1]`.

The current seen-pointer implementation linearly scans up to the already
visited count for each node. Its worst-case cost is `O(n^2)`, with `O(n)`
fixed auxiliary pointer capacity. The recursive traversal depth is at most
64 under the bounded valid contract. Do not label this implementation
`O(n)`.

A false validator result is diagnostic evidence. It does not identify
every cause, restore an overwritten pointer, authenticate keys, or prove
security.

## 9. Iterative destruction

`tree_destroy_iterative` uses a fixed stack of 64 pointers. It pushes live
children before releasing the current node, so it never follows a link
through released storage. It then restores `{NULL,0}`.

Precondition for a nonempty input: acyclic, uniquely owned shape with at
most 64 nodes. The operation accepts `NULL` and repeated destruction.
Destroy is `O(n)` time with bounded `O(n)` auxiliary pointer storage
(`O(1)` relative to this fixed course maximum).

Testing hooks under `TREE_TESTING` provide:

- `tree_test_fail_next_allocation`; and
- `tree_test_live_node_count`.

Compare the live count to a baseline, because other tests may legitimately
own nodes at a checkpoint.

## 10. Canonical measurements

Plain BST:

| Order | Root | Height | Deepest found | Longest missing |
|---|---:|---:|---:|---:|
| 1 through 15 | 1 | 14 | 15 | 15 using 16 |
| 15 through 1 | 15 | 14 | 15 | 15 using 0 |
| fixed mixed | 8 | 3 | 4 | 4 using 0 or 16 |

Fixed mixed:

```text
8,4,12,2,6,10,14,1,3,5,7,9,11,13,15
```

For this perfect shape, every leaf factor and every internal factor is 0.

AVL for all three orders:

| Root | Height | Deepest found | Longest missing |
|---:|---:|---:|---:|
| 8 | 3 | 4 | 4 |

Do not generalize that every permutation of 1 through 15 produces the same
physical AVL tree. The claim is limited to these three locked orders.

## 11. Canonical rotation results

| Case | Input | Repair |
|---|---|---|
| LL | `30,20,10` | right at 30 |
| RR | `10,20,30` | left at 10 |
| LR | `30,10,20` | left at 10, right at 30 |
| RL | `10,30,20` | right at 30, left at 10 |

All finish:

```text
root 20, height 1
left 10, height 0
right 30, height 0
inorder 10,20,30
```

## 12. Complexity

Let `n` be reachable node count and `h` be edge height.

- node-height lookup from a cached field: `O(1)`;
- balance-factor calculation from cached child heights: `O(1)`;
- one rotation: `O(1)`;
- plain BST search/insertion: `O(h)`;
- skewed plain BST search/insertion: `O(n)` because `h=n-1`;
- AVL search/insertion core: `O(log n)` because AVL height is logarithmic;
- actual-height measurement: `O(n)`;
- iterative destroy: `O(n)`;
- current full validator: `O(n^2)`.

These are operation-specific claims. Adding a full validator before every
mutation changes observed debug cost. The fixed maximum of 64 bounds the
teaching program but does not change the conceptual growth comparison.

## 13. Security framing

The threat model is:

- the attacker can choose valid unique-key arrival order;
- the defender uses a plain BST believing searches will usually be short;
- sorted input creates height `n-1`;
- repeated lookups or inserts consume linear work; and
- AVL balance limits this particular shape-based amplification.

Call it algorithmic-complexity denial of service only when the forced work
can delay or deny intended service. In the classroom fixture, it is a
bounded demonstration of the mechanism.

Distinguish:

- **degraded complexity:** valid operations require more work due to shape;
- **memory corruption:** an invalid memory read, write, or release; and
- **broad resource exhaustion:** memory, threads, storage, processing time,
  descriptors, or another resource is used up.

These can coexist in real software but are not synonyms. A skewed valid BST
is not itself evidence of memory corruption. One slow operation is not
proof that a resource is exhausted.

AVL does not prove authorization, key authenticity, input completeness,
availability under other load, thread safety, durable recovery, or overall
security.

## 14. Heap contrast

A binary Heap's invariant compares each parent against its children under a
priority relation. Siblings and whole subtrees are not fully ordered.
Therefore a Heap supports efficient extreme selection but not directed
arbitrary-key lookup.

A BST requires every left-subtree key smaller and every right-subtree key
larger. AVL preserves that whole-subtree search order and adds a height
bound. “Heap” in binary Heap is unrelated to C's colloquial use of “heap”
for dynamically allocated storage; define the intended meaning.

## 15. Autopsy boundary

The autopsy first assigns `root->right = NULL`. That replacement is wrong,
but local `upper->left` still reaches the middle node. The next assignment,
`upper->left = root`, overwrites the final route and is the earliest point
at which the middle node becomes unreachable. The fixture must make M
nonempty. Expected evidence:

- inorder loses M after faulty relinking;
- live-allocation count fails to return to baseline after destroying only
  reachable nodes; or
- a leak sanitizer reports the bounded lost allocation.

The canonical run should not intentionally dereference the leaked node
through a stale pointer. The lesson is ownership loss, not use-after-free.
Default build behavior must follow `code/README.md`; never auto-run unsafe
or intentionally faulty behavior outside the documented boundary.

## 16. Private-test priorities

Prioritize:

1. left/right rotations with nonempty middle subtrees;
2. missing-required-child no-change behavior;
3. lower-before-upper height refresh;
4. all four canonical cases;
5. child-factor zero boundary for LL/RR;
6. three exact 15-key measurement families;
7. duplicate/full/allocation preservation;
8. malformed size/root, cycle, sharing, ordering, and cached-height cases;
9. `INT_MIN` and `INT_MAX` keys without bound arithmetic; and
10. iterative destruction and live-count restoration.

Keep malformed pointer fixtures bounded and release them only after
restoring an acyclic unique-owner shape.
