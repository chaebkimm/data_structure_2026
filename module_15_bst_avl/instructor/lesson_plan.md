# Module 15 Instructor Lesson Plan - BST-to-AVL Synthesis

## 14-week delivery role - Week 13 (180 minutes)

This lesson is the authoritative Week 13 path; see the
[14-week delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
Meeting A uses 70 minutes and Meeting B uses 110 minutes, for exactly 180
contact minutes. All assessed work is assembled into one Week 13 artifact.
Do not schedule an additional Stage E lab.

Introduce edge-height (`NULL=-1`, leaf `0`), stored height, and balance factor
here as new required ideas. Week 8 contributes level-order experience only;
do not assume that students completed a tree-height or balance prelab there.

## Purpose

Students retrieve BST ordering, measure insertion-order sensitivity, and
implement AVL repair. The central claim is narrow: local rotations preserve
whole-subtree search order while keeping height logarithmic. The security
context is attacker-controlled valid input, not an invented memory exploit.

This remains a first course. Introduce each professional term only after
students have handled its ordinary-language example.

## Locked outcomes

By the end, students can:

- state strict unique-key BST ordering;
- use edge height with `NULL=-1` and leaf `0`;
- calculate left-height-minus-right-height balance factors;
- trace LL, RR, LR, and RL cases;
- preserve a nonempty middle subtree through a rotation;
- implement rotations, child-factor rebalancing, and AVL insertion;
- validate ordering, stored heights, balance, size, and pointer shape;
- report the exact 15-key BST/AVL measurements; and
- distinguish degraded complexity, memory corruption, and broad resource
  exhaustion.

## Materials and release order

Use the five staged releases in order.

1. Stage A: standard or linear initial inquiry
2. Stage B: representation reveal, vocabulary, and three-target pause
3. Stage C: standard or linear investigation worksheet
4. Stage D: textbook and diagram/linear-text models
5. Stage E: lab, code, evidence record, rubric, and bounded autopsy

Do not display professional structure names or completed three-key repairs
during Stage A. Preserve initial responses. Corrections are evidence of
learning.

## Preparation

- Confirm the standard and linear Stage A forms contain identical facts,
  questions, headings, and scores.
- Confirm neither Stage A form contains a fenced source block or embargoed
  vocabulary.
- Build the supplied core tests with warnings.
- Verify the faulty autopsy is isolated from the normal run.
- Prepare a physical alternative: numbered cards with left/right strings.
- Prepare large-print or screen-reader versions using the linear files.
- Use only synthetic keys and synthetic threat framing.

## Meeting A - Model and reason

Required time: 70 minutes.

### 1. Retrieval without names - 8 minutes

Release Stage A only. Students place `30,20,10` using smaller/larger
markers. Ask them to state the placement rule rather than guess a familiar
structure name.

Evidence to watch:

- equal labels are rejected;
- every earlier record remains reachable;
- “smaller on the left, larger on the right” applies to the whole region,
  not only an immediate neighbor.

Do not correct yet.

### 2. Arrival-order experiment - 10 minutes

Students predict ascending, descending, and fixed mixed placements. Require
one comparison count per visited record. A missing lookup counts stored
records compared; reaching END adds no comparison.

Locked results, held until comparison:

- ascending: first 1, longest route 15 records;
- descending: first 15, longest route 15 records;
- fixed mixed: first 8, longest route 4 records.

### 3. Local-reconnection conjecture - 8 minutes

Students handle all four triples. They must keep all records and preserve
smaller/larger placement. Do not reveal 20 as the new first record before
they determine it.

### 4. Height/balance foundation and representation reveal - 15 minutes

Release Stage B. Treat height and balance as first instruction, not
retrieval. Introduce in this order:

1. binary tree, node, root, child, subtree;
2. Binary Search Tree and invariant;
3. inorder traversal;
4. edge height and balance factor;
5. AVL tree; and
6. rotation and middle-subtree ownership.

Use one spoken sentence and one example per term. Avoid assuming `NULL`,
pointer, recursion, or allocation is already fluent; define each.

### 5. Three-target Cognitive Pause - 7 minutes

Time only the individual response period. The three required targets are:

1. hostile versus fixed-mixed measurements;
2. four canonical repairs and middle-subtree movement; and
3. validation, Heap contrast, and security scope.

Allow typing, handwriting, dictation, tactile cards, or structured verbal
response. Do not turn the pause into a speed score.

### 6. Peer comparison and calibration - 17 minutes

Pairs preserve originals and label corrections. Calibrate to:

- edge height 14 versus 3;
- comparisons 15 versus 4;
- all four repairs ending at `20(10,30)`;
- root/leaf heights `1,0,0`;
- inorder `10,20,30`; and
- middle subtree saved before link overwrite.

### 7. Exit ticket - 5 minutes

Prompt:

> Which whole-structure rule survives a rotation, and which shape rule does
> the rotation restore?

Expected distinction: BST ordering survives; AVL height balance is restored.

## Meeting B - Investigate, implement, and verify

Required time: 110 minutes, completing the same Week 13 contact block.

### 1. Worksheet Sections A-C - 20 minutes

Students rebuild ordering, measure the three plain BSTs, and compute
metadata bottom-up. Require them to distinguish actual height calculated
from links from a stored height field.

Checkpoint:

- a wrong stored height may leave ordering valid;
- the AVL validator must still reject it.

### 2. Worksheet Section D - 15 minutes

Use symbolic `L, X, M, Y, R` before concrete C. For a left rotation:

```text
save Y = X->right
save M = Y->left
X->right = M
Y->left = X
refresh X
refresh Y
return Y
```

Explain `->` as C field access through a pointer. Ownership evidence must
include M remaining reachable.

### 3. Read supplied interfaces - 10 minutes

Students annotate:

- `tree_model.h`;
- `bst_baseline.h`; and
- `avl_tree.h`.

Clarify the separation:

- BST baseline is supplied and intentionally does not rebalance;
- validators and iterative destruction are supplied;
- students change two starter implementation files and tests only; and
- full AVL deletion is extension work.

### 4. TODO 1 rotations - 15 minutes

Implement and immediately run LL/RR plus nonempty-middle tests. Do not move
to rebalance until validators and live-node count agree.

Likely error: update the new root's height before the lower node. Ask which
height the upper calculation reads.

### 5. TODO 2 rebalance - 15 minutes

The public helper receives a node, not the inserted key. Select cases from
child factors:

- left-heavy plus nonnegative left factor: LL;
- left-heavy plus negative left factor: LR;
- right-heavy plus nonpositive right factor: RR;
- right-heavy plus positive right factor: RL.

### 6. TODO 3 insertion - 15 minutes

Students allocate only at `NULL`, reconnect returned children only after
success, and rebalance while returning. Require failure-preservation tests
before the 15-key comparison.

### 7. Measure and validate - 10 minutes

Run ascending, descending, and fixed mixed orders through both backends.
Record the exact table. Call validators after completed mutations in
debug/test work.

Keep diagnostic cost honest: the supplied validator may take `O(n^2)` due
to its prior-pointer scan. It is not part of the AVL operation bound.

### 8. Bounded autopsy - 5 minutes

Predict first. Then inspect or run only according to `code/README.md`.
Require the earliest lost-link assignment, correct save order, and a
nonempty-middle regression.

### 9. Threat statement - 5 minutes

A complete statement names:

- attacker control of valid arrival order;
- forced linear plain-BST work;
- AVL's logarithmic-height mitigation; and
- a remaining limitation.

Reject claims that degraded performance is itself memory corruption or
proof that every resource is exhausted.

## Common misconceptions and responses

### “Each immediate left child is smaller, so the BST is valid.”

Counterexample: place 25 in the left subtree of 20 below key 10. The local
10-to-25 link looks increasing, but 25 violates the upper bound 20. Carry
whole-subtree lower and upper bounds.

### “A chain with 15 nodes has height 15.”

Ask students to count links, not nodes. It has 14 links. Search comparisons
count visited nodes, so the related result is 15.

### “Every imbalance uses one rotation.”

Have students trace `30,10,20`. One right rotation at 30 would put the keys
incorrectly. LR and RL first straighten the inner turn.

### “The middle subtree can be ignored.”

Use a nonempty M. Ask who owns it after the overwrite. A three-key-only
fixture can hide the leak because its M is `NULL`.

### “AVL means the two subtree sizes are equal.”

AVL constrains heights, not exact node counts.

### “The Heap is another search tree.”

Heap order compares a parent with children only. It does not tell an
arbitrary search whether to go left or right.

### “A validator makes mutation safe.”

A validator detects selected rule violations at a checkpoint. It cannot
repair a lost pointer, authenticate input, or prove the whole system secure.

## Accessibility and equivalent evidence

- Standard diagrams always have exact linear-text equivalents.
- Use ordered lists instead of requiring spatial drawing.
- Let students label records physically or dictate link triples.
- Accept a spoken trace that names old root, upper node, middle subtree,
  relinks, and height order.
- Do not grade visual polish.
- Provide additional non-timed practice before assessing C syntax.

## Safety controls

- Maximum size is 64.
- The intentionally skewed recursive baseline is bounded.
- Larger cleanup uses the supplied iterative destroy.
- Faulty autopsy behavior is isolated.
- No live operational data is used.
- Sanitizer evidence may be replaced with approved instructor-CI or the
  supplied allocation counter when local tooling is unavailable.

## Assessment checkpoints

- Stage A: reasoning is preserved, not correctness-graded.
- Stage B: exactly three retrieval targets.
- Stage C: 100-point reasoning path including exactly three later test
  designs.
- Stage E: rubric weights implementation, traces, safety, cost, and scope.
- Stage A through Stage E evidence is submitted once as the Week 13 artifact;
  no separate lab submission is added.
- Full AVL deletion is not required.

## Forward bridge

Module 16 compares local ordering/balance invariants with graph-wide
spanning-tree invariants. Revisit that “tree” names a shape in both
contexts, while the stored meaning and correctness rules differ.
