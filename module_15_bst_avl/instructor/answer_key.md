# Module 15 Instructor Answer Key

Accept equivalent linear, visual, tactile, typed, dictated, or verbal
evidence. Require exact values where the prompt locks them.

## Stage A key

### A. Place unique records

For `30,20,10`:

1. 30 reaches END and becomes first.
2. 20 compares with 30, is smaller, and uses 30's left marker.
3. 10 compares with 30 and 20, is smaller both times, and uses 20's left
   marker.

The preserved rule is whole-region ordering: every record reached through
a left marker is smaller than the current record, and every record reached
through a right marker is larger. Equal labels are rejected.

### B. Compare arrival orders

| Order | First record | Shape | Deepest found | Longest missing example/count |
|---|---:|---|---:|---|
| ascending | 1 | one right route | 15 | request 16, 15 |
| descending | 15 | one left route | 15 | request 0, 15 |
| mixed | 8 | four levels | 4 | request 0 or 16, 4 |

The fixed mixed order creates first 8, then 4/12, then 2/6/10/14, then the
odd leaves.

### C. Repair four cases

All four shortest valid results put 20 first, reach 10 through the left
marker, and reach 30 through the right marker. Smaller-to-larger order is
`10,20,30`. No record is added, discarded, or duplicated.

### D. Threat and scope

Ascending or descending order makes a 15-record route, so later deepest or
selected missing lookups compare all 15 records. This is a valid but slow
state. It does not by itself show an invalid memory access, and it does not
prove memory, time, threads, storage, or any other resource is completely
used up.

Strong synthesis: local reconnection can promote the middle label, retain
all three records, preserve smaller/larger placement, and shorten the
longest route.

## Cognitive Pause key

### Target 1

- ascending plain BST: root 1, height 14, 15 deepest comparisons, 15 for
  missing 16;
- fixed mixed plain BST: root 8, height 3, four deepest comparisons, four
  for missing 0 or 16;
- attacker-chosen ascending order turns expected short searches into
  linear work using valid unique keys.

### Target 2

| Case | Repair | Final state |
|---|---|---|
| LL | right rotation at 30 | root 20, left 10, right 30 |
| RR | left rotation at 10 | root 20, left 10, right 30 |
| LR | left at 10, then right at 30 | root 20, left 10, right 30 |
| RL | right at 30, then left at 10 | root 20, left 10, right 30 |

Every root height is 1; both leaf heights are 0; inorder is `10,20,30`.
For a left rotation at X with right child Y, Y's former left subtree M
moves to `X->right`. The mirror statement applies to a right rotation.

### Target 3

Ascending AVL 1 through 15 finishes at root 8 and height 3. Factors are
only `-1,0,1`. The BST validator checks root/size agreement, no repeated
pointer, exact size, and whole-subtree strict ordering. The AVL validator
also checks exact stored heights and factor bounds. Heap order is only
parent-before-child priority; AVL retains whole-subtree search direction.
Degraded work is not an invalid memory action and is not proof of general
resource depletion.

## Investigation worksheet key

### A. Rebuild BST ordering

`20,10,30,5,15` produces:

```text
20: left 10, right 30
10: left 5, right 15
5,15,30: no children
```

Search 15 visits 20, 10, 15: found with three comparisons. Search 17 visits
20, 10, 15, then `NULL`: absent with three comparisons. Inorder is
`5,10,15,20,30`.

Inserting duplicate 10 returns `TREE_DUPLICATE`. Root, size 5, all keys,
links, stored fields, and live-allocation count remain unchanged.

### B. Plain-BST measurements

| Order | Root | Height | Deepest found | Longest missing |
|---|---:|---:|---:|---:|
| ascending | 1 | 14 | 15 | 15 |
| descending | 15 | 14 | 15 | 15 |
| fixed mixed | 8 | 3 | 4 | 4 |

All use the same 15 unique keys, capacity, insertion rule, and search
operation. Arrival order alone changes shape. Sorted attacker-controlled
input can therefore force linear plain-BST work.

### C. AVL metadata

For the fixed mixed shape, keys 1,3,5,7,9,11,13,15 have height 0. Keys
2,6,10,14 have height 1. Keys 4 and 12 have height 2. Root 8 has height 3.
Every balance factor is 0.

If node 4 incorrectly stores height 1, its key placement remains valid.
`tree_validate_bst` may still be true because the baseline ignores cached
heights. `tree_validate_avl` is false because actual height is 2.

Separate violations:

- ordering-only: key 25 anywhere in root 20's left subtree;
- metadata/balance-only: correct links with a false stored height, or an
  ordered chain whose factor is 2.

### D. Rotations and ownership

The four repairs and final states match the pause table. Inorder before and
after is `10,20,30`; therefore each smaller key remains before the larger
keys.

Left rotation at X:

1. `Y = X->right`;
2. `M = Y->left`;
3. `X->right = M`;
4. `Y->left = X`;
5. refresh X;
6. refresh Y;
7. return Y.

M keys are greater than X because M was inside X's right subtree. They are
smaller than Y because M was Y's left subtree. Overwriting the only M link
without saving/reconnecting it makes the allocation unreachable and leaks
it.

### E. AVL insertion and validation

Insertion descends by BST order. While recursive calls return, the child
result is reconnected, the current height is refreshed, and imbalance is
repaired.

- factor `>1`, left-child factor `>=0`: LL;
- factor `>1`, left-child factor `<0`: LR;
- factor `<-1`, right-child factor `<=0`: RR;
- factor `<-1`, right-child factor `>0`: RL.

All three AVL builds finish:

| Order | Root | Height | Deepest found | Longest missing |
|---|---:|---:|---:|---:|
| ascending AVL | 8 | 3 | 4 | 4 |
| descending AVL | 8 | 3 | 4 | 4 |
| fixed mixed AVL | 8 | 3 | 4 | 4 |

Validation is checkpoint evidence. It does not substitute for saving an
owned pointer before overwrite or preserving a failed operation.

### F. Cost, contrast, and security

- rotation: `O(1)`, fixed link/field changes;
- plain BST search/insertion: `O(h)`;
- skewed plain BST: `h=n-1`, hence `O(n)`;
- AVL search/insertion: `O(log n)`;
- actual-height measurement and iterative destruction: `O(n)`;
- supplied complete validator: up to `O(n^2)` because each visited pointer
  may scan the earlier seen-pointer list.

`O(1)` is fixed-bounded work. `O(h)` grows with edge height. `O(log n)`
grows with repeated halvings of node count. `O(n)` grows in proportion to
node count.

A Heap orders parents against children by priority, not entire left and
right regions. It supports extreme selection but not directed arbitrary-key
search. BST supplies whole-subtree search order; AVL also limits height.

Degraded complexity is excess valid work. Memory corruption is an invalid
read, write, or release. Broad resource exhaustion means some resource is
used up. Validators do not prove authorization, authenticity, availability,
thread safety, or complete system security.

### G. Exactly three tests

Credit distinct categories, not function naming alone.

1. All four exact repairs plus a nonempty middle subtree retained,
   validators true, live count unchanged by rotation.
2. All three exact 15-key BST and AVL measurement sets.
3. Duplicate, full 64, allocation failure, argument/state errors, unchanged
   evidence, then iterative destroy returning live count to baseline.

### H. Autopsy

`root->right = NULL` is already the wrong replacement, but M remains
reachable through local `upper->left`. The following
`upper->left = root` overwrites that final route and is the earliest point
where M becomes unreachable. Correct order saves Y and M, connects M to X,
connects X below Y, refreshes lower X then upper Y, and returns Y. A
regression must make M non-`NULL`; a three-key fixture can hide the bug.

### I. Synthesis

Strong response: AVL uses constant-size local rotations. The middle subtree
moves within the only ordering interval it satisfies, so inorder and
ownership remain valid. Repeated repair bounds height despite hostile
arrival order, changing the plain BST's possible linear search into
logarithmic search. This does not prove broader security.

## Evidence-template exact values

- empty/destroyed state: `root=NULL`, `size=0`;
- maximum: 64 nodes;
- all canonical three-node after-states: root 20, left 10, right 30;
- heights: root 1, leaves 0;
- canonical inorder: `10,20,30`;
- plain ascending/descending: height 14, comparisons 15;
- plain mixed: root 8, height 3, comparisons 4;
- every canonical 15-key AVL: root 8, height 3, comparisons 4.

Allocation failure must not change root, size, links, keys, or stored
heights. Successful iterative destruction restores the prior live-node
baseline.

## Rubric interpretation

Do not deduct for:

- choosing the linear format;
- using a correct mirror drawing;
- naming variables differently;
- using instructor-CI evidence when a local sanitizer is unavailable; or
- omitting full AVL deletion.

Do deduct implementation-safety credit until repaired when a submission
loses the middle subtree, mutates on reported failure, hides test failures,
or intentionally performs invalid memory access.
