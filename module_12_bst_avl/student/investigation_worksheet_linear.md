# Stage C — Source-Based BST and AVL Investigation

Name: ____________________________
Date: ____________________________

Use this linear-format worksheet after the Cognitive Pause. Preserve Sections A–F
before opening worked Stage D materials. Complete later test evidence in
Sections G–I. The required source is the complete [lab.c](lab.c).

## A. Separate identities, keys, and links — 10 points

The lab includes Module 2's ten-record array. The key is a `char` in
`nodes[i].data`; children are integer IDs and -1 means no child.
A new ID must be unused, with both children initialized to -1.

1. If node ID 4 holds key B, which value does a search compare? Which
   value is stored in another node's child field? (4 points)
2. With `alphabet_init()`, insert IDs for D,B,F,A,C. Draw or list the
   resulting plain BST and its inorder sequence. (3 points)
3. A fresh ID holds another B. Trace its insertion direction. Explain why
   inserting this fresh ID differs from inserting the same live ID twice.
   Do not predict a duplicate-rejection status. (3 points)

Response: __________________________________________________________

____________________________________________________________________

## B. Measure order effects — 15 points

A search driver compares once per visited node. Use the same seven
distinct keys in each build, with these exact probes:

Fields: Order; Arrival order; Present probe; Missing probe.
- Order: ascending; Arrival order: A,B,C,D,E,F,G; Present probe: G; Missing probe: H.
- Order: descending; Arrival order: G,F,E,D,C,B,A; Present probe: A; Missing probe: @.
- Order: mixed; Arrival order: D,B,F,A,C,E,G; Present probe: G; Missing probe: H.

For this course fixture, @ precedes A. Missing links add no comparisons.

1. Before AVL repair, record each root, edge height, present path/count,
   and missing path/count. (8 points)
2. Identify what stays fixed and what changes across the builds. (3 points)
3. Explain how chosen arrival order can increase valid lookup work.
   State why this does not by itself demonstrate invalid memory access.
   (4 points)

Fields: Plain BST; Root key; Height; Present path/count; Missing path/count.
- Plain BST: ascending; Root key: ________; Height: ________; Present path/count: ________; Missing path/count: ________.
- Plain BST: descending; Root key: ________; Height: ________; Present path/count: ________; Missing path/count: ________.
- Plain BST: mixed; Root key: ________; Height: ________; Present path/count: ________; Missing path/count: ________.

## C. Measure height independently — 15 points

A missing subtree has edge height -1; a leaf has height 0. A node's height
is one more than its larger child height. Balance is left height minus
right height. AVL permits only -1, 0, and 1.

1. Compute all heights and factors of the mixed tree, starting at its
   leaves. (6 points)
2. Change only the saved height of key D to 1 in a copied test fixture.
   Which ordering rules still hold? What must an independent checker
   detect? Restore the fixture before continuing. (5 points)
3. Explain why an actual-height checker must follow links instead of
   trusting `height[]`. Distinguish saved height from node ID. (4 points)

Response: __________________________________________________________

____________________________________________________________________

## D. Trace the four repairs — 20 points

The case letters describe the two directions below the first unbalanced
node. Use a separate empty tree for each order.

Fields: Case; Arrival order; First unbalanced key; Helper; Final links/heights.
- Case: LL; Arrival order: C,B,A; First unbalanced key: ________; Helper: ________; Final links/heights: ________.
- Case: RR; Arrival order: A,B,C; First unbalanced key: ________; Helper: ________; Final links/heights: ________.
- Case: LR; Arrival order: C,A,B; First unbalanced key: ________; Helper: ________; Final links/heights: ________.
- Case: RL; Arrival order: A,C,B; First unbalanced key: ________; Helper: ________; Final links/heights: ________.

1. Give each final root, children, inorder sequence, and stored heights.
   (8 points)
2. Copy the actual link assignments from each helper. Mark which captured
   argument preserves a middle subtree. Explain why LR/RL can be direct
   helpers even though they represent two geometric rotations. (6 points)
3. Trace each `set_height` call in `_add`. Which nodes are below the new
   root and why must their heights be ready first? (6 points)

Response: __________________________________________________________

____________________________________________________________________

## E. Follow recursive returns — 15 points

The parent must reconnect the child's new root after a deeper insertion.

1. Explain both assignments in
   `l = nodes[i].left = _add(l,new_node)`, and its right-side mirror.
   What would be stale if only the field changed? (5 points)
2. Trace `int root = i`, normal height refresh, a rotation branch, and
   the final return. Explain the outer
   `root = _add(root,new_node)`. (5 points)
3. Build all three seven-key orders using the actual AVL source. Predict
   roots, heights, and probe counts before comparing test output.
   (5 points)

Fields: AVL; Root key; Height; Present comparisons; Missing comparisons.
- AVL: ascending; Root key: ________; Height: ________; Present comparisons: ________; Missing comparisons: ________.
- AVL: descending; Root key: ________; Height: ________; Present comparisons: ________; Missing comparisons: ________.
- AVL: mixed; Root key: ________; Height: ________; Present comparisons: ________; Missing comparisons: ________.

## F. Distinguish work and guarantees — 10 points

1. Count local link changes in LL/RR and LR/RL. Separate local repair,
   one-path recursion, fixed ten-slot storage, and full-tree diagnostic
   work. Then state scalable search/insertion and rotation bounds.
   (4 points)
2. Contrast Heap parent priority, BST whole-subtree order, and AVL's
   additional height rule. (3 points)
3. Distinguish shape-based slowdown, invalid memory access, and broad
   resource exhaustion. Name one claim that AVL balance cannot establish.
   (3 points)

Response: __________________________________________________________

____________________________________________________________________

## G. Keep a nonempty middle subtree — later evidence

Use distinct keys and a valid fixture within ten IDs. Trace a repair
where a middle subtree is nonempty. Record its exact ID before and after,
every resulting link, actual heights, and the expected reachable-ID set.
Explain why a three-node test alone cannot detect every lost-middle bug.

Chosen fixture and assertions:

____________________________________________________________________

## H. Write original assertions — later evidence

Add original cases to `code/tests/test_lab_student.c`. Include the actual
lab once. Use the build commands in [the lab](lab.md).

Cover four repairs and a middle subtree; the seven-key measurements; and
valid boundaries/equal keys/regressions. Check all expected IDs exactly
once, nondecreasing inorder, exact stored heights, and all balance factors.
Test all ten valid IDs without attempting an eleventh insertion or a
repeated live ID. The lab promises no rejection for invalid calls.

Test claims and observed results:

____________________________________________________________________

## I. Preserve the correction trail — later evidence

Keep the original prediction and label each correction. State the earliest
observation that changed the model. Attach commands/output and one
independent manual or measured check. Complete one Week 12
[evidence record](evidence_template.md); there is no second submission.

____________________________________________________________________
