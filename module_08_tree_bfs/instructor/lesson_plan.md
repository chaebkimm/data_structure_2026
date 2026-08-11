# Instructor Lesson Plan — Module 8: Tree Breadth-First Traversal

## 14-week delivery override - Week 8 bridge (35 of 180 minutes)

Use only this short bridge before the 145-minute Module 9 graph-BFS block.
There is no standalone Module 8 lab or submission in the 14-week path. The
full plan below remains an optional instructor resource. See the
[14-week delivery guide](../../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).

| Minutes | Required live work |
|---:|---|
| 0-5 | Retrieve FIFO Queue behavior from Module 7. |
| 5-12 | Display the canonical tree and read the supplied node-and-depth Queue scaffold. |
| 12-25 | Trace left-first level order, recording Queue contents and nondecreasing depths. |
| 25-32 | Contrast a tree's unique parent route with a graph's need for discovered state. |
| 32-35 | Preserve the trace as formative evidence and hand off directly to Module 9. |

Do not release the full Stage E starter as required work. Shallowest-match
search and the Tree BFS Autopsy are optional; width analysis is optional;
height and balance-factor work moves to Module 15. The Week 8 submission is
the single combined Module 9 submission, which includes the in-class tree
trace but no Module 8 code TODO.

## Purpose and limits

This module is the Tree stage of the third
Linear → Tree → Graph spiral. It retrieves:

- the valid binary-tree representation from Module 2;
- traversal, depth, height, and depth-first search (DFS) from Module 5; and
- first-in, first-out (FIFO) Queue behavior from Module 7.

Students learn **breadth-first search (BFS)**, a procedure that processes
nodes nearer the root before nodes farther from the root. When BFS visits an
entire tree, its order is called **level order**. A **level** contains all
nodes at one depth. **Depth** is the number of child links from the root to a
node.

The public algorithms assume a valid tree: it is acyclic, no node is shared
by two parents, and every child pointer is either `NULL` or identifies one
node in the same tree. The algorithms do not validate those properties and
do not use a visited record. Cycles, sharing, graph discovery state,
distances, predecessors, and disconnected components wait until Module 9.

All examples are synthetic, meaning invented for safe study. The lab does
not inspect a live process tree, filesystem, access-control system, or
network. Passing the lab does not establish the safety of a real policy.

## Canonical course tree

Manual materials use labels `C0` through `C8` to distinguish node objects.
The labels are fixture names, not stored `TreeNode` fields.

```text
C0(42, not flagged)
├─ left: C1(17, flagged)
│  ├─ left:  C3(23, not flagged)
│  └─ right: C4(91, flagged)
│     └─ left: C7(44, flagged)
└─ right: C2(68, not flagged)
   ├─ left:  C5(17, flagged)
   └─ right: C6(5, not flagged)
      └─ right: C8(44, not flagged)
```

Exact linear equivalent:

1. `C0`, key 42 and not flagged, is the root.
2. `C0` has left child `C1`, key 17 and flagged, and right child `C2`,
   key 68 and not flagged.
3. `C1` has left child `C3`, key 23 and not flagged, and right child `C4`,
   key 91 and flagged.
4. `C2` has left child `C5`, key 17 and flagged, and right child `C6`,
   key 5 and not flagged.
5. `C4` has left child `C7`, key 44 and flagged.
6. `C6` has right child `C8`, key 44 and not flagged.
7. `C3`, `C5`, `C7`, and `C8` have no children. Every child not named
   above is `NULL`.

This is a general binary tree, not a binary search tree (BST). Its repeated
keys 17 and 44 are deliberate. A general binary tree may contain repeated
keys; the distinct node pointers identify distinct objects. Do not build
this fixture with the supplied strict-BST insertion operation, which rejects
duplicates.

By the end of the module, students should be able to:

1. explain BFS as processing nodes in nondecreasing depth;
2. explain level order and the left-before-right course tie rule;
3. trace a Queue of node-and-depth work records from front to back;
4. implement checked level-order traversal;
5. implement a checked shallowest-key search;
6. handle repeated keys, a missing key, and a `NULL` root;
7. compute tree height with BFS under the course edge-height convention;
8. calculate level widths and maximum width;
9. analyze BFS as `O(n)` time and `O(w)` auxiliary space;
10. compare BFS `O(w)` space with DFS `O(h)` space;
11. explain why a valid tree does not require visited tracking; and
12. calculate balance factors and trace one instructor-provided rotation
    without implementing tree balancing.

## Beginner language sequence

Introduce or retrieve a term immediately before students need it. A
professional term must never appear in a student-facing direction before its
plain-language explanation.

| Term | First-use explanation |
|---|---|
| node | One stored item in a tree |
| root | The starting node of a tree |
| child | A node directly below another node |
| pointer | A value that stores a memory address |
| `NULL` | A pointer value meaning “no node here” |
| valid tree | One root, no cycles, no shared child, and exactly one parent for every nonroot node |
| visit | Process one node; here, copy its key, flag, and depth |
| traversal | A planned procedure that visits every tree node |
| depth | The number of child links from the root to a node |
| level | All nodes at one depth |
| breadth-first search (BFS) | Process nearer nodes before farther nodes |
| level order | The complete-tree order produced by BFS |
| nondecreasing | Staying equal or increasing, never decreasing |
| Queue | A collection in which the oldest waiting item leaves first |
| first in, first out (FIFO) | The first item added is the first item removed |
| enqueue | Add one item at the Queue’s back |
| dequeue | Remove and report the Queue’s front item |
| frontier | Nodes scheduled for processing but not yet visited |
| work record | One node pointer paired with that node’s depth |
| shallowest | Having the smallest depth |
| tie rule | A published rule choosing between equally deep matches; here, left before right |
| width of a level | The number of nodes at one depth |
| maximum width `w` | The largest level width in the tree |
| height `h` | The greatest number of downward child links from root to leaf |
| edge height | The course convention `height(NULL) = -1` and `height(leaf) = 0` |
| node count `n` | The number of nodes in the tree |
| auxiliary space | Temporary working storage, excluding the input tree and required output |
| `O(n)` | Work that can grow in proportion to node count `n` |
| `O(w)` | Working storage that can grow in proportion to maximum width `w` |
| `O(h)` | Working storage that can grow in proportion to height `h` |
| balance factor | Left-subtree height minus right-subtree height |
| rotation | A small local link rearrangement that can change height while preserving BST order |
| application programming interface (API) | Public types and function names other code may use |
| status code | A named result reporting success or one kind of failure |
| caller | Code requesting a function to run |
| output | A result written into caller-provided storage |
| precondition | A rule the caller must make true before requesting an operation |
| local candidate | A possible result kept private until the operation succeeds |
| commit or publish | Copy a completed local candidate into caller-visible output |
| failure preservation | A failed operation leaves published outputs and the input tree unchanged |
| queue limit | The greatest number of pending work records this call permits |
| allocation | Requesting storage while a program runs |
| ownership | Responsibility for eventually releasing requested storage |
| borrowed pointer | A pointer that may be inspected but does not transfer ownership |
| regression test | A retained test that detects whether a repaired defect returns |
| synthetic | Invented for safe practice rather than read from a live system |

Do not define breadth first as merely “using a Queue.” State the ordering
promise first: nearer depths are processed before farther depths. Then show
how FIFO preserves that promise.

Do not say that the frontier always equals one complete level. During a
transition it may contain unprocessed nodes at depth `d` and children at
depth `d + 1`.

## Frozen BFS behavior

The course procedure is:

```text
if root is not NULL:
    enqueue (root, depth 0)

while the Queue is not empty:
    dequeue one work record
    visit its node
    if its left child is not NULL:
        enqueue (left child, parent depth + 1)
    if its right child is not NULL:
        enqueue (right child, parent depth + 1)
```

The Queue is always written from front to back in traces. The course visits a
node when its work record is dequeued. Left is enqueued before right. BFS
does not sort keys and flag values do not affect scheduling.

For shallowest search, compare the target with the key immediately after
dequeue. Return the first match without enqueuing that matched node’s
children. This produces:

- minimum depth because all earlier dequeued records have depth no greater
  than the current record; and
- the left-before-right result among equally deep matches because child
  records enter the FIFO Queue left before right.

## Five release gates

A **release gate** is a planned point when students receive the next
materials. The sequence is:

```text
attempt → preserve → compare → correct
```

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A — Nearer-first inquiry | Start of Meeting A | Standard or linear inquiry prompt | BFS, level order, frontier, Queue solution, code, and answers |
| B — Representation reveal | After each Stage A response is preserved | Representation reveal, vocabulary reference, and exactly-three-target Cognitive Pause | Vocabulary during the timer; pause answers, Stage C, textbook, and code |
| C — Investigation | After the pause and instructor comparison | Standard or linear investigation worksheet | Textbook, completed models, lab, and code |
| D — Calibrated explanation | After preserved Stage C core Sections A–F | Beginner-first textbook and diagram/text models | Lab package and instructor materials |
| E — Lab and evidence | After Meeting B retrieval and Gate D calibration | Lab, evidence form, rubric, safe autopsy, public header, supplied support, starter, core tests, student-test template, and build files | Reference solution, extension tests, answer key, and technical notes |

The vocabulary file remains closed during the complete Cognitive Pause.
Instructors may repeat directions and provide approved access support but
may not define a term, confirm correctness, give a hint, or add a fourth
target.

An accommodation may change time, response method, room, lighting, or
assistive technology. It does not change the fixture, targets, order,
independence, or closed resources.

Stage C core is Sections A through F. Sections G through I are later
testing, autopsy, and reflection work.

---

# Meeting A — Discover Nearer-First Tree Exploration (90 minutes)

## Macro-question

> How can we guarantee that every node close to the root is inspected before
> any deeper node?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–7 | Retrieve the tree | Reconstruct root, left/right child, `NULL`, and depth in ordinary language. State the valid-tree precondition and synthetic scope. Do not retrieve Queue terminology yet. | Accurate parent/child description |
| 7–21 | Gate A inquiry | Release one accessible format. Require an individual preserved first response. | Nearer-first rule and remembered-work model |
| 21–30 | Compare without erasing | Ask which waiting item must leave next and what must be remembered. Add labeled corrections rather than replacing first work. | Annotated initial model |
| 30–42 | Gate B reveal | Define BFS, level order, frontier, node-depth work record, and left-first FIFO scheduling. Work the `R0` fixture below. | Reveal trace |
| 42–47 | Five-minute Cognitive Pause | Release exactly the three `P0` targets. Repeat directions only. | Preserved three-target response |
| 47–57 | Calibrate | Open vocabulary after all responses are preserved. Read each diagram as a parent/child list and each frontier as a front-to-back row. | Labeled corrections |
| 57–72 | Canonical trace | Work `C0` through `C8`, including repeated keys, flags, depths, and every frontier state. | Exact Queue/depth trace |
| 72–79 | Shallowest search | Search 17, 44, and 99. Make the equal-depth tie rule and unchanged not-found output explicit. | Three search results |
| 79–86 | Height, width, and costs | Calculate level widths, maximum width, edge height, and `O(n)`/`O(w)`. Contrast with DFS `O(h)`. | Cost explanation |
| 86–90 | Exit and Gate C | Ask why FIFO preserves depth order, why no visited record is used, and what Queue limit 4 means on the canonical tree. Release Stage C. | Three-part exit response |

## Stage A inquiry fixture and calibration

Stage A uses this synthetic hierarchy:

```text
Control
├─ left: Accounts
│  ├─ left:  Guest
│  └─ right: Admin [check]
└─ right: Network [check]
   ├─ left:  VPN
   └─ right: Firewall
      └─ left: Rules
```

The prompt asks students to invent a repeatable method that starts at
`Control`, inspects items requiring fewer links before items requiring more
links, and keeps left before right. It does not name BFS, Queue, FIFO,
frontier, enqueue, dequeue, level order, width, or balance.

After first responses are preserved, calibration may establish:

```text
inspection order:
Control, Accounts, Network, Guest, Admin, VPN, Firewall, Rules

closest [check] item:
Network, depth 1

waiting after Control:
Accounts, Network

waiting after Accounts:
Network, Guest, Admin

waiting after Network:
Guest, Admin, VPN, Firewall
```

A newest-first rule can inspect `Admin` before the shallower `Network`; it
therefore does not guarantee the requested nearest-first order.

## Stage B representation reveal

The reveal fixture is different from the pause and canonical fixtures:

```text
R0(26)
├─ left: R1(4)
│  └─ right: R3(58)
└─ right: R2(73)
   └─ left: R4(11)
```

Exact linear form: `R0` is the root; its children are `R1` and `R2`.
`R1` has right child `R3`; `R2` has left child `R4`; all other child
positions are `NULL`.

The correct visit/depth order is:

```text
R0@0, R1@1, R2@1, R3@2, R4@2
```

Required frontier states, front first:

```text
start:     [R0@0]
after R0:  [R1@1, R2@1]
after R1:  [R2@1, R3@2]
after R2:  [R3@2, R4@2]
after R3:  [R4@2]
after R4:  []
```

The state after `R1` contains depths 1 and 2 at once. This is intentional.

## Stage B Cognitive Pause — exactly three targets

Use this fixture:

```text
P0(60)
├─ left: P1(14)
│  ├─ left:  P3(7)
│  └─ right: P4(35)
│     └─ left: P6(92)
└─ right: P2(83)
   └─ right: P5(14)
```

Exact linear form: `P0` is root with children `P1` and `P2`. `P1` has
children `P3` and `P4`. `P2` has right child `P5`. `P4` has left child
`P6`. Every other child is `NULL`.

Students receive exactly these targets:

1. Give the frontier initially, after visiting `P0`, and after visiting
   `P1`; then give the complete visit/depth order.
2. Search for key 14. Identify the returned node and depth and explain why
   the deeper duplicate is not returned.
3. Give every level width, maximum width `w`, edge height `h`, and the BFS
   and DFS auxiliary-space expressions.

Private responses:

```text
Target 1:
[P0@0]
[P1@1, P2@1]
[P2@1, P3@2, P4@2]

P0@0, P1@1, P2@1, P3@2, P4@2, P5@2, P6@3

Target 2:
P1 at depth 1. P1 is dequeued before depth-2 P5.

Target 3:
level widths 1, 2, 3, 1
w = 3
h = 3
BFS auxiliary space O(w)
DFS auxiliary space O(h)
```

Keep these answers private during the pause. Do not add a balance-factor,
code, policy, or graph question.

## Canonical Queue and depth trace

The exact copied visit records are:

| Visit | Fixture node | Key | Flagged | Depth |
|---:|---|---:|---|---:|
| 1 | `C0` | 42 | false | 0 |
| 2 | `C1` | 17 | true | 1 |
| 3 | `C2` | 68 | false | 1 |
| 4 | `C3` | 23 | false | 2 |
| 5 | `C4` | 91 | true | 2 |
| 6 | `C5` | 17 | true | 2 |
| 7 | `C6` | 5 | false | 2 |
| 8 | `C7` | 44 | true | 3 |
| 9 | `C8` | 44 | false | 3 |

Required frontier states after each visit, front first:

```text
after C0: [C1@1, C2@1]
after C1: [C2@1, C3@2, C4@2]
after C2: [C3@2, C4@2, C5@2, C6@2]
after C3: [C4@2, C5@2, C6@2]
after C4: [C5@2, C6@2, C7@3]
after C5: [C6@2, C7@3]
after C6: [C7@3, C8@3]
after C7: [C8@3]
after C8: []
```

Thus:

```text
keys:   42, 17, 68, 23, 91, 17, 5, 44, 44
depths:  0,  1,  1,  2,  2,  2, 2,  3,  3
flagged keys in BFS order: 17, 91, 17, 44
```

The maximum pending count is 4, immediately after visiting `C2`. Therefore
all three BFS functions can complete this full traversal with
`queue_limit == 4`. A full traversal with `queue_limit == 3` reports
`TREE_BFS_LIMIT` when enqueueing `C6` would require a fourth pending record.
Its caller output remains unchanged.

An early shallowest search can succeed with a smaller limit if it finds its
target before a later wide frontier is needed. For example, target 17 is
found at `C1` before the canonical frontier reaches four items.

## Meeting A checks

Before releasing Stage C, verify that each learner can state:

- BFS processes nearer depths before farther depths;
- the Queue stores work records, not copied subtrees;
- the frontier contains scheduled but unvisited nodes;
- frontier rows are written front to back;
- the course enqueues left before right;
- visit depths never decrease;
- keys are not sorted;
- target 17 returns `C1` at depth 1;
- target 44 returns `C7` before equal-depth `C8`;
- a valid tree has no repeated route to a node and therefore needs no visited
  record;
- the canonical widths are `1, 2, 4, 2`, so `w == 4`;
- canonical height is 3; and
- queue limit 4 succeeds while queue limit 3 cannot finish the canonical
  traversal.

---

# Meeting B — Implement Checked Tree BFS (90 minutes)

## Coding question

> How can a typed FIFO Queue produce level order, a shallowest match, and
> edge height while preserving every public contract?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Retrieval | Without notes, reproduce the canonical key/depth order, the frontier after `C2`, and the search result for 44. Preserve before comparison. | Retrieval trace |
| 8–14 | Gate D calibration | Reopen the textbook and models. Correct Queue direction, depth, tie, height, width, and no-visited language. | Annotated correction |
| 14–20 | Gate E orientation | Release the lab. Define header, starter, supplied support, public test, extension test, and student-test template. | Package map |
| 20–31 | Public model and contracts | Read every public type, status, function, limit, empty-tree result, and unchanged-output rule. | Contract table |
| 31–45 | Level order | Stage output locally, enqueue root at depth 0, then dequeue/record/enqueue left/enqueue right. Check the 64-record boundary. | Passing traversal tests |
| 45–57 | Shallowest match | Compare immediately after dequeue and publish only the first match. Test repeated 17, tied 44, and missing 99. | Search evidence |
| 57–67 | Height by BFS | Return `-1` for empty. For nonempty input, track the greatest dequeued depth and publish only after completion. | Height tests |
| 67–74 | Limits and preservation | Contrast limits 4 and 3 for canonical full traversal/height, early search 17 with limit 2, and the 65th-reached-node limit. | Failure snapshots |
| 74–80 | Costs and shapes | Compare a seven-node chain (`h=6,w=1`) with levels of widths `1,2,4` (`h=2,w=4`). | `O(w)` versus `O(h)` |
| 80–85 | Balance preview | Compute the separate skewed BST’s heights and balance factors. Trace one right rotation manually. | Before/after table |
| 85–88 | Safe autopsy | Predict the right-before-left output and match before running. Identify the first bad scheduling decision. | Four-part autopsy |
| 88–90 | Boundary and submission | State valid-tree precondition, borrowed search pointer, synthetic scope, required evidence, and completion window. | Complete checklist |

## Canonical public model

The public header is the source of truth:

```c
#define TREE_BFS_MAX_NODES 64U

typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
    size_t depth;
} TreeBfsVisit;

typedef struct {
    TreeBfsVisit items[TREE_BFS_MAX_NODES];
    size_t count;
} TreeBfsOrder;

typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeBfsMatch;
```

The status enumeration appears in this exact order:

```text
TREE_BFS_OK
TREE_BFS_INVALID_ARGUMENT
TREE_BFS_LIMIT
TREE_BFS_ALLOCATION
TREE_BFS_DUPLICATE
TREE_BFS_NOT_FOUND
```

The public operations are:

```c
TreeBfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
);

void tree_node_release(TreeNode *node);

TreeBfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
);

TreeBfsStatus tree_level_order(
    const TreeNode *root,
    size_t queue_limit,
    TreeBfsOrder *out_order
);

TreeBfsStatus tree_find_shallowest(
    const TreeNode *root,
    int target,
    size_t queue_limit,
    TreeBfsMatch *out_match
);

TreeBfsStatus tree_height_bfs(
    const TreeNode *root,
    size_t queue_limit,
    int *out_height
);

TreeBfsStatus tree_destroy_postorder(TreeNode **root);

const char *tree_bfs_status_name(TreeBfsStatus status);
```

`tree_node_create`, `tree_node_release`, `tree_bst_insert`, and
`tree_destroy_postorder` are supplied. Students implement only:

1. `tree_level_order`;
2. `tree_find_shallowest`; and
3. `tree_height_bfs`.

The supplied internal Queue stores `(const TreeNode *, size_t depth)` work
records in an inline array. **Inline** means the Queue’s 64 records are part
of the local Queue object; traversal does not request memory. Students use
the supplied Queue rather than reimplementing Module 7.

## Public contract summary

- `queue_limit` may be 0 through 64 inclusive. A value greater than 64
  reports `TREE_BFS_LIMIT`.
- A `NULL` required output pointer reports `TREE_BFS_INVALID_ARGUMENT`.
- A `NULL` root is a valid empty tree.
- Empty level order succeeds with `count == 0`, even when queue limit is 0.
- Empty height succeeds and writes `-1`, even when queue limit is 0.
- Empty search reports `TREE_BFS_NOT_FOUND` and leaves its output unchanged.
- A nonempty tree with queue limit 0 reports `TREE_BFS_LIMIT`.
- A call reports `TREE_BFS_LIMIT` before accepting a 65th reached node.
- Every BFS function leaves its output unchanged on failure.
- `tree_find_shallowest` also leaves its output unchanged on
  `TREE_BFS_NOT_FOUND`.
- BFS functions never mutate the tree.
- The search result’s node pointer is borrowed. The caller must not release
  it separately and must stop using it before the tree is destroyed.
- The BFS functions use no allocation and therefore do not themselves
  produce `TREE_BFS_ALLOCATION`. That status is used by supplied node
  creation and BST insertion.

## Height, width, and space

Use edge height consistently:

```text
height(NULL) = -1
height(leaf) = 0
height(nonempty tree) = greatest visited depth
```

For the canonical tree:

```text
level widths: 1, 2, 4, 2
maximum width w: 4
height h: 3
```

Every valid-tree node is enqueued once and dequeued once, so complete BFS
takes `O(n)` time. At a level transition, the Queue may hold remaining nodes
at one depth and already-enqueued children at the next depth. Each group has
at most `w` nodes, so the pending count is at most `2w`. A constant factor of
2 is omitted in growth notation; auxiliary space is therefore `O(w)`.
Never claim that the peak Queue count must equal one complete level’s width.

DFS auxiliary space is conventionally `O(h)`. Shape determines which is
smaller:

| Shape | `h` | `w` | DFS working space | BFS working space |
|---|---:|---:|---:|---:|
| Seven-node one-child chain | 6 | 1 | `O(h)` | `O(w)` |
| Seven nodes in levels of 1, 2, and 4 | 2 | 4 | `O(h)` | `O(w)` |

## Height and balance preview boundary

Use a separate strict BST:

```text
    30
   /
  20
 /
10
```

The **balance factor** of a node is:

```text
height(left subtree) - height(right subtree)
```

Before rotation:

| Node | Left height | Right height | Node height | Balance factor |
|---:|---:|---:|---:|---:|
| 10 | -1 | -1 | 0 | 0 |
| 20 | 0 | -1 | 1 | 1 |
| 30 | 1 | -1 | 2 | 2 |

Later AVL trees require each balance factor to be `-1`, `0`, or `1` in
addition to satisfying BST order.

The instructor demonstrates one right rotation at 30:

```text
   20
  /  \
10   30
```

Afterward, both children have height 0, the root has height 1, all three
balance factors are 0, and inorder remains `10, 20, 30`.

Do not assign rotation code. Do not introduce LL, RR, LR, or RL labels,
double rotations, stored-height maintenance, rotation-selection rules, AVL
insertion, or deletion. Those belong to Module 15. Do not imply that every
imbalance is repaired by this one rotation.

## Safe autopsy

Use this separate fixture:

```text
A(42)
├─ left: B(17)
│  └─ left: D(44)
└─ right: C(68)
   └─ right: E(44)
```

Correct left-first BFS visits:

```text
A, B, C, D, E
```

Correct shallowest search for key 44 returns `D` at depth 2.

The bounded faulty program enqueues a right child before a left child. If
allowed to finish, it visits:

```text
A, C, B, E, D
```

Its shallowest search returns `E` at depth 2. The result is still at the
minimum depth, but it violates the published left-before-right tie rule.
The first bad decision occurs after visiting `A`, when `C` is enqueued before
`B`. The smallest repair swaps the child-enqueue order. A regression test
must contain equal-depth repeated keys on opposite sides and assert that the
left-side node pointer is returned.

The autopsy is bounded and performs no invalid memory access. Students
predict before running and identify the earliest broken rule rather than
merely reversing final output.

## Hint ladder

Outside the no-hint Cognitive Pause, stop after the least revealing prompt
that restores productive work:

1. Read the exact status or failing assertion aloud.
2. State the requested order in ordinary language.
3. Write the current Queue from front to back.
4. Name the depth stored with each pending pointer.
5. Ask which child must enter first for a left-first FIFO tie.
6. Ask which caller output must remain unchanged.
7. Point to the relevant pseudocode step without supplying C.
8. Supply one pseudocode line only after the learner records why it is
   needed and proposes a regression test.

## Common misconceptions

| Misconception | Corrective prompt |
|---|---|
| “BFS sorts keys.” | “Which contract mentions numeric order?” |
| “The Queue stores whole subtrees.” | “What are the two fields in one work record?” |
| “Every frontier is one complete level.” | “After reveal node R1, which two depths coexist?” |
| “Visit when enqueued.” | “At what published operation does this course record a visit?” |
| “Right must be enqueued first, as in DFS.” | “Which end removes next in FIFO?” |
| “The first repeated value is arbitrary.” | “What tie rule follows from left-before-right enqueue?” |
| “Search must finish the entire traversal.” | “What guarantee already holds when the first match is dequeued?” |
| “A missing search may clear its output.” | “What does the not-found contract preserve?” |
| “A `NULL` root is invalid.” | “What tree contains zero nodes?” |
| “Queue limit is total node count.” | “Does the limit count completed visits or simultaneously pending records?” |
| “Peak Queue size always equals maximum level width.” | “Can pending records from adjacent depths coexist?” |
| “BFS always uses less memory than DFS.” | “Is the tree a chain or a wide shape?” |
| “Height counts nodes.” | “How many child links occur on the longest path?” |
| “A balance factor alone makes an AVL tree.” | “Does the tree also satisfy BST ordering?” |
| “Tree BFS is safe on a cycle.” | “What prevents the same object from being enqueued repeatedly?” |
| “Passing this lab proves a policy safe.” | “Which real inputs and enforcement behaviors were not modeled?” |

## Accessibility and pacing

- Pair every diagram with an exact numbered parent/left/right description.
- Pair every vertical Queue drawing with a front-to-back text row.
- Include fixture labels and depths in frontier records; never identify
  repeated keys by key alone.
- Give standard and linear files identical target IDs, values, order, and
  scoring.
- Never use color alone for current, queued, visited, matched, flagged,
  corrected, or unbalanced state.
- Permit tactile node cards, speech, typing, handwriting, keyboard-only
  tables, or a scribe.
- Read `node->left` aloud as “the node pointer’s left child address.”
- Read `O(w)` as “order w” and define `w` before using it.
- Accept a numbered event list instead of arrows and a parent/child list
  instead of a drawing.
- During the Cognitive Pause, read all three targets and permit approved
  extended time without giving definitions, hints, or answer checks.
- Grade scheduling, depth, contracts, and evidence rather than drawing
  quality, indentation, spatial memory, handwriting, or response speed.
- Announce the independent completion window before coding begins.

## Evidence collected

Collect:

1. preserved and corrected Stage A response;
2. exactly-three-target Stage B response;
3. Stage C core Sections A through F;
4. canonical visit/depth and frontier trace;
5. warning-clean starter build after the three TODOs;
6. public core-test output;
7. exactly three independently meaningful student-authored tests;
8. repeated-key, equal-depth-tie, and missing-key search evidence;
9. queue-limit and unchanged-output evidence;
10. empty, one-node, wide, skewed, and 65-node boundary evidence;
11. canonical width/height and BFS-versus-DFS cost explanation;
12. skewed-BST balance worksheet and manual rotation trace;
13. safe-autopsy prediction, earliest broken rule, repair, and regression
    test;
14. valid-tree/no-visited and tree-to-graph transfer explanation; and
15. borrowed-pointer, ownership, and synthetic-scope statements.

The three student-authored test categories are:

1. an exact left-first level order with every copied key, flag, and depth;
2. a repeated-key shallowest match followed by a missing-key
   output-preservation check; and
3. exact edge height followed by a too-small Queue limit that preserves the
   prior height output.

Do not accept three renamed copies of supplied tests.

## Scoring alignment

Use the published 100-point rubric without adding unannounced criteria:

| Criterion | Points |
|---|---:|
| BFS model, frontier, and trace | 20 |
| Functional correctness | 25 |
| Contracts, limits, and ownership | 20 |
| Tests and reproducible evidence | 15 |
| Shape measurement and cost | 10 |
| Autopsy and transfer | 10 |
| **Total** | **100** |

An incorrect Cognitive Pause response is not penalized when it is preserved
and meaningfully corrected. Approved verbal, tactile, linear-text,
screen-reader, or instructor-run evidence receives the same credit as a
visual or locally compiled form. Rotation implementation is outside scope
and receives no core points.

## After Meeting B — transparent completion window

The meetings establish the core model and implementation path. Allow about
75–105 additional minutes for students to finish starter functions, run
tests, write original tests, complete the autopsy, and assemble evidence.
Offer a staffed lab period or equivalent remote support.

Public tests demonstrate the published contract but are not a complete list
of grading cases. The reference solution, extension tests, and instructor
materials remain private until the instructor-selected review point.

## Instructor readiness checklist

- [ ] Stage A contains no BFS, Queue, FIFO, frontier, level-order, formula,
      code, or exact solution.
- [ ] Standard and linear materials have identical target IDs and facts.
- [ ] The reveal uses `R0` through `R4` and the exact mixed-depth frontier.
- [ ] The pause uses `P0` through `P6`, contains exactly three targets, and
      keeps vocabulary closed.
- [ ] The canonical fixture, duplicate keys, and flags match every file.
- [ ] Canonical BFS keys and depths are exact.
- [ ] Search 17 returns `C1`; search 44 returns `C7`; search 99 is not found.
- [ ] Keys are never interpreted as priority or BST order in the canonical
      general tree.
- [ ] Child enqueue is left then right, and visit occurs on dequeue.
- [ ] The frontier is always written front to back.
- [ ] Queue limit 4 succeeds and limit 3 fails on the canonical full
      traversal.
- [ ] `TREE_BFS_MAX_NODES` is 64 and the 65th reached node reports limit.
- [ ] All types, statuses, parameters, and empty-tree rules match the public
      header.
- [ ] Every failed BFS call preserves output and every BFS call preserves
      the tree.
- [ ] The internal Queue is typed, inline, supplied, and allocation-free.
- [ ] Height uses `NULL = -1` and leaf = 0.
- [ ] `O(w)` is taught without claiming peak Queue count always equals `w`.
- [ ] The separate strict-BST preview uses only one manual right rotation.
- [ ] Rotation implementation and four-case AVL terminology remain deferred.
- [ ] The autopsy is bounded, memory-safe, and uses the exact equal-depth
      repeated-key fixture.
- [ ] Every diagram has an exact linear equivalent.
- [ ] Every professional term is explained before or at first use.
- [ ] Synthetic scope and the completion window are announced.
