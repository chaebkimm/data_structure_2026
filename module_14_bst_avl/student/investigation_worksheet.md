# Stage C - BST and AVL Investigation

Name: ____________________________
Date: ____________________________

Use this standard-format worksheet after the Cognitive Pause. Preserve
Sections A through F before opening Stage D. Sections G through I are later
work. All keys are synthetic unique integers. The capacity is 64 nodes.

## A. Rebuild BST ordering - 10 points

A Binary Search Tree (BST) stores smaller keys in each node's left subtree
and larger keys in its right subtree. A node is one record; a subtree is a
node and everything below it.

### A1. Insert and search - 4 points

Insert `20,10,30,5,15`. Show every comparison and link choice. Then trace
searches for 15 and 17, counting comparisons.

____________________________________________________________________

### A2. Traverse inorder - 3 points

Write the inorder traversal—left subtree, node, right subtree—and explain
why it is increasing.

____________________________________________________________________

### A3. Enforce unique keys - 3 points

Predict an insertion of 10. State the returned **status**, the named
outcome reported by the operation, and every field, node, link, and
allocation count that must remain unchanged.

____________________________________________________________________

## B. Measure arrival-order effects - 15 points

Use these exact orders:

| Name | Order |
|---|---|
| ascending | `1,2,3,4,5,6,7,8,9,10,11,12,13,14,15` |
| descending | `15,14,13,12,11,10,9,8,7,6,5,4,3,2,1` |
| fixed mixed | `8,4,12,2,6,10,14,1,3,5,7,9,11,13,15` |

Edge height counts links on a longest downward route:
`height(NULL)=-1` and `height(leaf)=0`.

### B1. Measure plain BSTs - 8 points

For each order, state root, edge height, deepest successful-search
comparisons, and suitable missing-search comparisons. Explain each number.

| Order | Root | Height | Deepest found | Longest missing |
|---|---:|---:|---:|---:|
| ascending | | | | |
| descending | | | | |
| fixed mixed | | | | |

### B2. Identify adversarial control - 4 points

Explain how attacker-controlled ascending or descending order can create
algorithmic-complexity denial of service, meaning valid input forces much
more work.

____________________________________________________________________

### B3. Hold other variables still - 3 points

State what is identical across the three experiments and why the arrival
order, not the set of keys, explains the different plain-BST results.

____________________________________________________________________

## C. Compute AVL metadata - 15 points

**Metadata** means values that describe other data. Here, heights and
balance factors describe nodes.

An AVL tree is a BST whose every balance factor is `-1`, `0`, or `1`.
Balance factor equals left-subtree height minus right-subtree height.

### C1. Compute bottom-up - 6 points

For the fixed mixed structure, compute every leaf height, every internal
height, and every balance factor from the bottom upward.

____________________________________________________________________

### C2. Check stored heights - 5 points

Suppose node 4 stores height 1 instead of 2 while its links are unchanged.
Explain why BST ordering can still be valid but AVL validation must fail.

____________________________________________________________________

### C3. Separate two invariants - 4 points

State the BST ordering invariant and the AVL height/balance invariant
separately. Give one malformed state that violates each one alone.

____________________________________________________________________

## D. Trace four rotations and ownership - 15 points

Use the four insertion orders:

| Case | Order |
|---|---|
| LL | `30,20,10` |
| RR | `10,20,30` |
| LR | `30,10,20` |
| RL | `10,30,20` |

A rotation is a local link rearrangement that preserves inorder key order.

### D1. Select repairs - 4 points

For each case, name the single rotation or ordered pair of rotations.

| Case | Repair |
|---|---|
| LL | |
| RR | |
| LR | |
| RL | |

### D2. Prove the exact result - 5 points

For every case, give root 20, children 10 and 30, heights `1,0,0`, and
inorder `10,20,30`. Explain why the inorder result proves ordering was
preserved.

____________________________________________________________________

### D3. Preserve the middle subtree - 6 points

For a left rotation at X with right child Y and Y's left subtree M, number
the save-and-relink steps. Explain why M belongs as X's new right subtree
and how losing M would create a memory leak.

____________________________________________________________________

## E. Trace AVL insertion and validation - 15 points

### E1. Rebalance while returning - 5 points

Explain why recursive insertion updates height and checks balance after the
deeper call returns. State how LL, RR, LR, and RL are selected.

____________________________________________________________________

### E2. Measure all three AVL builds - 5 points

Insert the ascending, descending, and fixed mixed orders from Section B
into AVL trees. Record exact final root, height, deepest successful-search
comparisons, and suitable missing-search comparisons.

| Order | Root | Height | Deepest found | Longest missing |
|---|---:|---:|---:|---:|
| ascending AVL | | | | |
| descending AVL | | | | |
| fixed mixed AVL | | | | |

### E3. Validate after mutation - 5 points

List what the supplied BST validator and AVL validator must check. Explain
why validation is diagnostic evidence, not a substitute for correct
mutation logic.

____________________________________________________________________

## F. Analyze cost, contrast, and security - 10 points

### F1. State costs - 4 points

State costs for plain-BST search/insertion in terms of height `h`, their
worst case in terms of node count `n`, AVL search/insertion, one rotation,
complete validation, and destruction. Explain `O(1)`, `O(h)`, `O(log n)`,
and `O(n)` in plain language.

____________________________________________________________________

### F2. Contrast a binary Heap - 3 points

Explain why parent-before-children Heap order supports repeated minimum or
maximum selection but does not provide arbitrary-key search order. Contrast
that with BST whole-subtree search order—every smaller key left and every
larger key right—and AVL balance.

____________________________________________________________________

### F3. Limit the security claim - 3 points

Distinguish degraded complexity from memory corruption and from broad
resource exhaustion. State one security property AVL validation cannot
prove.

____________________________________________________________________

## G. Design exactly three tests - later work - 9 points

### G1. Four rotations and middle-subtree ownership - 3 points

Design one test category covering LL, RR, LR, and RL exact roots, links,
heights, inorder order, validators, and one nonempty middle subtree.

____________________________________________________________________

### G2. Hostile, reverse, and mixed measurements - 3 points

Design one test category proving exact BST and AVL results for all three
15-key orders, including comparison counts and root 8 AVL results.

____________________________________________________________________

### G3. Preservation, boundary, and cleanup - 3 points

Design one test category covering duplicate, capacity 64, allocation
failure, invalid argument/state, unchanged failures, and iterative destroy
with the live-allocation count restored.

____________________________________________________________________

## H. Complete the bounded autopsy - later work - 6 points

### H1. Find the lost link - 2 points

Identify the overwrite in `faulty_left_rotation.c` that loses the
nonempty middle subtree.

____________________________________________________________________

### H2. Repair and verify - 2 points

Give the corrected save-and-relink order and record sanitizer, allocation
counter, or instructor-trace evidence.

____________________________________________________________________

### H3. Add a regression - 2 points

A **regression test** checks that a repaired defect does not return. State
exact before/after links, inorder sequence, heights, and live-node count
for this test with a nonempty middle subtree.

____________________________________________________________________

## I. Synthesize - later work - 5 points

### I1. Compare measurements - 2 points

Use the completed BST-versus-AVL table to explain what AVL changes and what
BST property it preserves.

____________________________________________________________________

### I2. State the threat precisely - 2 points

Write a concise threat statement naming attacker control, the forced work,
the AVL mitigation, and one remaining limitation.

____________________________________________________________________

### I3. Exit synthesis - 1 point

Answer:

> How can local rotations preserve whole-subtree search order while
> preventing an attacker-controlled arrival order from creating a long
> search chain?

____________________________________________________________________
