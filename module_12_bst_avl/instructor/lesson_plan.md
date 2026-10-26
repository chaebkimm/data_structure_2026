# Module 12 Instructor Lesson Plan — Trace the Supplied AVL Lab

## Week 12 delivery contract

Use this [180-minute path](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
for one Week 12 submission. Meeting A takes 70 minutes and Meeting B 110.
There is no additional Stage E assignment. Full AVL deletion is outside
the required lesson.

The source authority is [`student/lab.c`](../student/lab.c), which includes
Module 2's ten character records and integer child IDs. Students trace
complete code and write assertion tests. Do not assign the older pointer
starter's implementation TODOs as the required lab.

## Learning targets

Students should be able to distinguish record IDs, keys, and heights;
explain whole-subtree search order; calculate edge height and balance;
trace LL/RR/LR/RL repairs; preserve an inner subtree; reconnect the returned
root during recursive unwind; and independently check links, inorder,
heights, and balance. They should compare plain BST and AVL search work
and keep the security conclusion limited to insertion-order slowdown.

Edge height, cached height, and balance factor receive their first formal
instruction here. Retrieve the binary-tree and DFS ideas from Modules 2
and 5 without assuming students already know AVL terminology.

## Preparation and staged release

Prepare letter cards with left/right connectors and stable IDs A=0 through
G=6. Provide linear versions for each visual task. Preserve initial models
before revealing the names and source.

1. Stage A: initial inquiry, standard or linear.
2. Stage B: representation reveal, vocabulary, and Cognitive Pause.
3. Stage C: investigation worksheet, standard or linear.
4. Stage D: textbook and diagrams with linear equivalents.
5. Stage E: complete lab, driver tests, evidence record, and rubric.

Build the required targets before class:

```sh
make -C module_12_bst_avl/code lab-compile core student-tests comparison
```

Use the [code guide](../code/README.md) for compiler and PowerShell options.
The driver includes the lab once and resolves its Module 2 dependency from
the repository root. Keep the optional pointer autopsy out of normal tests.

## Meeting A — Model and reason (70 minutes)

### 1. Retrieve without names — 8 minutes

Release Stage A only. Use distinct labels C, B, A and ask students to place
them with smaller/larger markers. Require a rule for every record in a
region, not just its immediate child. Do not reveal the professional
structure name or the completed reconnection yet.

### 2. Compare arrival orders — 10 minutes

Predict `A B C D E F G`, `G F E D C B A`, and `D B F A C E G`.
Count one comparison per visited label. END adds none. Hold these results
until students have preserved their predictions:

- ascending: root A, seven-record route;
- descending: root G, seven-record route;
- mixed: root D, three-record route.

### 3. Conjecture a local repair — 8 minutes

Use CBA, ABC, CAB, and ACB. Ask students to retain all labels and the same
smaller-to-larger sequence while shortening the longest route. In each
case, B becomes the first record with A left and C right.

### 4. Reveal representation and teach height — 15 minutes

Release Stage B. Introduce node, ID, key, root, child, subtree, inorder,
BST, edge height, balance factor, AVL, and rotation through one example
each. Read Module 2's record declaration before `_add`.

Make the lab's distinctions explicit:

- a link contains an integer ID; `-1` means missing and is never indexed;
- height lives in a separate array;
- missing height is -1 and leaf height is 0;
- equality descends left, but rotations preserve nondecreasing inorder and
  can place equals on either side;
- source routines assume valid, initialized IDs; they do not allocate.

### 5. Individual Cognitive Pause — 7 minutes

Retrieve three targets: arrival-order cost, four repairs with middle
subtrees, and independent validation plus Heap/security contrast. Accept
typed, written, dictated, tactile, or structured spoken responses.

### 6. Compare and calibrate — 17 minutes

Pairs preserve originals and annotate corrections. Calibrate to heights
6 versus 2, comparison counts 7 versus 3, final B(A,C), heights 1/0/0,
and unchanged inorder. Show why IDs remain fixed while links change.

### 7. Exit ticket — 5 minutes

Ask: which ordering rule survives the repair, and which shape rule is
restored? Expected answer: nondecreasing inorder survives; the local
left/right height difference returns to the allowed range.

## Meeting B — Read, trace, and test (110 minutes)

### 1. Rebuild ordering and metadata — 20 minutes

Use worksheet sections for plain-BST shape, independent actual height,
and stored `height[]`. Deliberately change a stored height on paper while
keeping links: order can remain correct while AVL metadata becomes false.
The driver must check these claims independently.

### 2. Trace the middle subtree — 15 minutes

Use symbolic `i`, `r`, `rl`, then the concrete sequence `F D G B E A`.
Require E to remain reachable after LL repair, now below F. A missing
middle subtree in a three-record fixture hides the lost-link error.

### 3. Read the actual interfaces — 10 minutes

Read the include, `get_height`, `set_height`, rotation signatures, and
`_add(i,new_node)`. Identify that rotation arguments are IDs and already
captured grandchildren. The helpers only rewire; `_add` refreshes heights.
Contrast this with the optional pointer reference only if students ask.

### 4. Trace LL and RR — 15 minutes

Use stable IDs and track every link assignment. After LL update `i` then
`l`; after RR update `i` then `r`. Run tests that assert exact links,
heights, and nonempty-middle retention.

### 5. Trace LR and RL — 15 minutes

Capture `lrl/lrr` or `rll/rlr` before assignments. These helpers perform
the double-rotation effect directly. Refresh both lower nodes before the
promoted grandchild. Ask which stored values the final height reads.

### 6. Trace recursive return and duplicates — 15 minutes

Follow `l = nodes[i].left = _add(...)` or its right mirror. A recursive
return may replace a child root. At each frame default `root=i`, select
one balance branch, and return the resulting ID. Save the outer result.
Trace three distinct IDs holding B to show why equal-only-on-left is not
a post-rotation invariant.

### 7. Measure and validate — 10 minutes

Run the three seven-label orders. All AVL builds finish at D, height 2;
the specified present/missing lookups take three comparisons. Plain BSTs
have heights 6/6/2 and counts 7/7/3. Baseline, lookup, measurement, and
complete validation are driver support, not source exports.

### 8. Source-based failure investigation — 5 minutes

On paper, replace a saved middle ID with `-1` and identify the first lost
route. This loses reachability in an array; it does not allocate or leak
heap storage. Require a nonempty-middle regression. Optional legacy unsafe
autopsy execution is not required.

### 9. Threat statement — 5 minutes

Require valid attacker-controlled order, forced linear plain-BST work,
AVL height repair, and one remaining limitation. Distinguish too much valid
work from invalid memory access and from complete resource exhaustion.

## Common misconceptions

- **ID equals key:** use the same alphabet IDs with several insertion
  orders and show that the root ID changes without moving records.
- **Seven nodes means height seven:** count six edges in a chain, then
  separately count seven visited records.
- **Each local child comparison proves order:** place G under B in D's
  left region and show the inherited upper bound D is violated.
- **Equal keys stay left forever:** rotate three equal-key records and
  inspect the promoted node's right child.
- **Rotation helpers update height:** locate the actual `set_height`
  calls in `_add`; direct helper tests must account for this split.
- **Updating root first is harmless:** expand `get_height` calls to show
  the promoted node would read an old lower-node height.
- **Capacity is checked:** point to the absence of a guard and make the
  driver choose ten fresh initialized IDs, never an eleventh.

## Assessment and scope

Assess three original test groups: rotation/metadata, order/measurement,
and duplicates/valid boundaries. Require commands and output, four traces,
an independent height check, and a narrow threat statement in one artifact.
Do not grade drawing quality, speed, memorized wording, allocation status,
destruction, or an optional pointer-library implementation as required work.
