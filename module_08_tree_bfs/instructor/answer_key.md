# Instructor Answer Key — Module 8

Keep this file private until the instructor-selected comparison or review
point. During the Cognitive Pause, do not release definitions, hints,
partial confirmations, or any answer from this file.

The standard and linear learner files have the same target IDs and facts.
Use this one key for either format. Accept speech, typed text, a numbered
list, tactile-card evidence recorded by a scribe, or a diagram with an exact
verbal explanation. Grade the scheduling decision and supporting evidence,
not drawing quality or memorized wording.

## Frozen notation

- A frontier is written from Queue front to back.
- `C4@2` means fixture node `C4` at depth 2.
- Fixture labels identify distinct node objects; they are not stored fields.
- `T` means `flagged == true`; `F` means `flagged == false`.
- The course visits on dequeue and enqueues a non-`NULL` left child before a
  non-`NULL` right child.
- Edge height uses `height(NULL) = -1` and `height(leaf) = 0`.
- Balance factor means left-subtree height minus right-subtree height.

---

# Stage A — Initial Inquiry

The inquiry deliberately asks for an informal model before naming BFS,
level order, frontier, Queue, FIFO, enqueue, or dequeue. During initial work,
accept any unambiguous ordinary-language version of the expert model below.
Do not require formal vocabulary retroactively.

## A. Read the arrangement

### A1. Starting item

`Control`.

It is the root: the one starting node.

### A2. End items

```text
Guest, Admin, VPN, Rules
```

Each has no child. `Firewall` is not an end item because it has left child
`Rules`.

### A3. One route

Any one of these complete root-to-leaf routes is correct:

```text
Control, Accounts, Guest
Control, Accounts, Admin
Control, Network, VPN
Control, Network, Firewall, Rules
```

A route must begin at `Control`, follow direct child links, and end at a node
with no child.

## B. Invent a fair inspection rule

### B1. Repeatable rule

One complete ordinary-language response:

> Keep an ordered waiting list. Begin with `Control`. Repeatedly take the
> item that has waited longest, inspect it, then add its left child followed
> by its right child when those children exist. Stop when nothing remains
> waiting.

This meets both promises because older, nearer work stays ahead of children
just discovered, while adding left before right fixes equal-distance order.

During Stage A, also accept a correct level-by-level description that does
not yet name the storage rule, provided the learner explains how unfinished
nodes are retained and eventually processed.

### B2. Complete inspection order

```text
Control, Accounts, Network, Guest, Admin, VPN, Firewall, Rules
```

Distances from `Control` are:

```text
0: Control
1: Accounts, Network
2: Guest, Admin, VPN, Firewall
3: Rules
```

The answer must preserve the displayed left-before-right order within each
distance.

### B3. No missed work

Keep every discovered but uninspected node in an ordered waiting
collection. Remove only the next item to inspect; add each newly discovered
child after all items already waiting. The procedure stops only when the
collection is empty.

“Remember the parents” alone is incomplete unless the response explains how
every postponed child is represented and later selected.

## C. Record unfinished work

### C1. After Control

```text
Accounts, Network
```

`Accounts` must be handled first because it is the left child and was added
first under the course tie rule.

### C2. After Accounts

```text
Network, Guest, Admin
```

`Network` was already waiting. Newly discovered `Guest` and `Admin` join
after it, left before right.

### C3. One waiting record

One record needs:

1. the identity or address of the node; and
2. the number of links used to reach it.

After formal vocabulary is released, these are the node pointer and depth.
An answer giving only the stored name or integer is insufficient when
distinct nodes may store equal values.

## D. Find the closest marked item

### D1. First acceptable result

```text
Network, 1 link from Control
```

`Admin` is two links from `Control`.

### D2. Risk of following one branch

A method that completes the left branch can reach and report `Admin` at
distance 2 before returning to `Network` at distance 1. It therefore reports
a valid marked node but not the closest marked node.

## E. Retrieve an earlier access rule

### E1. Choose the useful rule

Handle the earliest-added waiting item first.

From C2, `Network` was waiting before `Guest` and `Admin`, so it must leave
next. A most-recently-added rule would choose `Admin` and violate the
nearer-first promise.

### E2. Compare two shapes

Many nodes spread across the same distance can require more unfinished
records at once. A one-child chain usually has only one next node waiting.
After formal calibration, this is the difference between large width and
large height.

## F. Initial synthesis

### F1. Macro-question

Sample two-sentence answer:

> Keep discovered nodes in earliest-added-first waiting order and add each
> node’s children only after that node is inspected. All already waiting
> nearer nodes then leave before newly added deeper nodes, while adding left
> before right fixes equal-distance order.

Do not require the words Queue, FIFO, or BFS in the preserved initial
response.

### F2. Open question

This is an authentic inquiry item. Accept a relevant unresolved question,
such as:

- How much waiting storage can a very wide tree require?
- What should happen if the waiting storage limit is reached?
- How are two nodes with the same value distinguished?
- What changes if two routes reach the same object?
- How is an empty tree handled?

Do not award full credit for an unrelated question or “nothing.”

---

# Stage B — Representation Reveal

The reveal tree is:

```text
R0(26)
├─ left: R1(4)
│  └─ right: R3(58)
└─ right: R2(73)
   └─ left: R4(11)
```

Correct visit/depth order:

```text
R0@0, R1@1, R2@1, R3@2, R4@2
```

Correct frontiers:

```text
start:     [R0@0]
after R0:  [R1@1, R2@1]
after R1:  [R2@1, R3@2]
after R2:  [R3@2, R4@2]
after R3:  [R4@2]
after R4:  []
```

The state after `R1` demonstrates that a frontier can contain adjacent
depths 1 and 2 simultaneously.

---

# Stage B — Cognitive Pause

The pause must contain exactly the following three scored targets.

## Target 1 — Trace waiting work

```text
initial:
[P0@0]

after visiting P0:
[P1@1, P2@1]

after visiting P1:
[P2@1, P3@2, P4@2]

complete order:
P0@0, P1@1, P2@1, P3@2, P4@2, P5@2, P6@3
```

Common correction: `P5` is discovered when `P2` is visited and remains
behind the already waiting depth-2 records `P3` and `P4`.

## Target 2 — Choose the shallowest match

Return:

```text
P1, depth 1
```

The other node storing 14 is `P5` at depth 2. FIFO causes the depth-1 record
for `P1` to be dequeued before the later depth-2 record for `P5`.

## Target 3 — Measure shape and working space

```text
depth 0 width: 1
depth 1 width: 2
depth 2 width: 3
depth 3 width: 1

maximum width w = 3
edge height h = 3
BFS auxiliary space = O(w)
DFS auxiliary space = O(h)
```

For this fixture, `w` and `h` happen to have the same numeric value. That
does not make the two quantities or bounds interchangeable.

---

# Stage C — Investigation Worksheet

## A. Apply the Queue-controlled rule

### A1. Complete the procedure

```text
if the root exists:
    enqueue (root, depth 0)

while the Queue is not empty:
    dequeue one work record
    visit its node
    enqueue its non-NULL left child at parent depth + 1
    enqueue its non-NULL right child at parent depth + 1
```

The blanks, in order, are:

```text
root
0
dequeue
left
right
```

### A2. Explain nondecreasing depth

FIFO removes older waiting records before newer ones. A child enters only
after its parent is dequeued, so it joins behind all smaller-depth records
already waiting and cannot pass them.

An invariant-based answer may add that the Queue contains only one depth or
two adjacent depths, in nondecreasing front-to-back order.

### A3. Explain the equal-depth tie

The left-child record enters the FIFO Queue before the right-child record.
Because earlier-added records leave first, left leaves before right when
their depths are equal.

### A4. Explain the valid-tree boundary

In a valid course tree, every nonroot node has exactly one parent and no link
path returns to an earlier node. Each node therefore has exactly one route
from the root and is enqueued once.

A cycle, a shared child, an alias, or another graph-like reconnecting
relationship would permit repeated arrival at the same object and require a
visited record.

## B. Trace and search the canonical tree

Complete frontier table:

| Completed visit | Complete frontier after adding children |
|---|---|
| none | `C0@0` |
| `C0` | `C1@1, C2@1` |
| `C1` | `C2@1, C3@2, C4@2` |
| `C2` | `C3@2, C4@2, C5@2, C6@2` |
| `C3` | `C4@2, C5@2, C6@2` |
| `C4` | `C5@2, C6@2, C7@3` |
| `C5` | `C6@2, C7@3` |
| `C6` | `C7@3, C8@3` |
| `C7` | `C8@3` |
| `C8` | empty |

### B1. Complete visit records

```text
C0, value 42, F, depth 0
C1, value 17, T, depth 1
C2, value 68, F, depth 1
C3, value 23, F, depth 2
C4, value 91, T, depth 2
C5, value 17, T, depth 2
C6, value 5,  F, depth 2
C7, value 44, T, depth 3
C8, value 44, F, depth 3
```

Exact copied `TreeBfsVisit` values:

```text
(42,false,0)
(17,true,1)
(68,false,1)
(23,false,2)
(91,true,2)
(17,true,2)
(5,false,2)
(44,true,3)
(44,false,3)
```

Flagged keys in BFS order are `17, 91, 17, 44`.

### B2. Find the peak Queue count

The largest count is 4, after visiting `C2`:

```text
[C3@2, C4@2, C5@2, C6@2]
```

This example’s peak happens to equal its maximum level width. That is not a
general identity. During a transition, a frontier can contain remaining
nodes from depth `d` and children already discovered at depth `d + 1`.

### B3. Search for repeated value 17

Return:

```text
C1, depth 1
```

Nodes inspected through the successful match:

```text
C0, C1
```

Search stops immediately when `C1` is dequeued and found; it does not need
to inspect the deeper `C5`.

### B4. Search for repeated value 44

Return `C7` at depth 3.

`C4` is processed before `C6` in left-first level order. Therefore `C4`
enqueues `C7` before `C6` enqueues `C8`. FIFO removes `C7` first.

### B5. Search for missing value 99

Status:

```text
TREE_BFS_NOT_FOUND
```

The caller’s previous `TreeBfsMatch.node` and `TreeBfsMatch.depth` both
remain unchanged.

## C. Measure depth, width, height, and balance

### C1. Record every depth

| Node | `C0` | `C1` | `C2` | `C3` | `C4` | `C5` | `C6` | `C7` | `C8` |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Depth | 0 | 1 | 1 | 2 | 2 | 2 | 2 | 3 | 3 |

### C2. Record every level width

```text
depth 0: 1
depth 1: 2
depth 2: 4
depth 3: 2
maximum width w = 4
```

### C3. Calculate heights from the leaves upward

```text
C3 = 0
C5 = 0
C7 = 0
C8 = 0
C4 = 1
C6 = 1
C1 = 2
C2 = 2
C0 = 3
```

The complete tree’s height is 3.

### C4. Apply the edge-height convention

```text
empty tree: -1
one leaf: 0
n-node one-child chain: n - 1
```

### C5. Calculate balance factors

For every nonleaf:

```text
C0 =  2 - 2  =  0
C1 =  0 - 1  = -1
C2 =  0 - 1  = -1
C4 =  0 - (-1) = +1
C6 = -1 - 0  = -1
```

Every leaf has factor 0, although the question asks only for nonleaves.

Do not call the canonical tree an AVL tree. It is not a strict BST and it
contains duplicate keys.

## D. Compare BFS and DFS

### D1. Compare visit orders

Left-first preorder:

```text
42, 17, 23, 91, 44, 68, 17, 5, 44
```

One exact difference: BFS visits `C2`/68 at depth 1 before `C3`/23 at depth
2, while preorder follows the left branch and visits `C3`/23 before
returning to `C2`/68.

Equivalent label orders:

```text
BFS:      C0,C1,C2,C3,C4,C5,C6,C7,C8
preorder: C0,C1,C3,C4,C7,C2,C5,C6,C8
```

### D2. Compare search guarantees

BFS dequeues records in nondecreasing depth, so no undiscovered or waiting
node at a smaller depth can remain when the first match is dequeued. Its
first match therefore has minimum depth.

Ordinary DFS can follow one branch to a deeper match while a shallower match
waits on another branch. Its first match does not generally guarantee
minimum depth.

### D3. State full-traversal costs

```text
BFS: O(n) time, O(w) auxiliary space
DFS: O(n) time, O(h) auxiliary space
```

Each complete traversal processes every node once. BFS pending work follows
tree width; recursive or suitable explicit-Stack DFS work follows height.

### D4. Compare wide and skewed shapes

On a very wide shallow tree, BFS may retain many same-level or adjacent-level
records, so large `w` can make BFS use more working storage.

On a long one-child chain, `w == 1` while `h == n - 1`; DFS’s active path can
grow with `h`, while BFS needs only a small frontier.

Neither method always uses less storage.

### D5. Separate output from working storage

`TreeBfsOrder` is the required published result. Auxiliary space counts
temporary algorithmic work separate from both input and required output.
The typed frontier Queue is included in `O(w)`; the `O(n)` copied result is
not.

## E. Apply the public contracts

Assume every required output pointer not explicitly described as `NULL` is
valid.

| Request | Status | Required output effect |
|---|---|---|
| level order of `NULL`, Queue limit 0 | `TREE_BFS_OK` | publish `count == 0` |
| level order of a nonempty tree, Queue limit 0 | `TREE_BFS_LIMIT` | previous order unchanged |
| canonical level order, Queue limit 4 | `TREE_BFS_OK` | publish all nine exact records |
| canonical level order, Queue limit 3 | `TREE_BFS_LIMIT` | previous order unchanged |
| any operation with Queue limit 65 | `TREE_BFS_LIMIT` | previous output unchanged |
| shallowest search of `NULL` for 17 | `TREE_BFS_NOT_FOUND` | previous match unchanged |
| shallowest search of the canonical tree for 99 | `TREE_BFS_NOT_FOUND` | previous match unchanged |
| height of `NULL`, Queue limit 0 | `TREE_BFS_OK` | publish `-1` |
| a required output pointer is `NULL` | `TREE_BFS_INVALID_ARGUMENT` | no output can be written |
| supplied node creation cannot allocate a node | `TREE_BFS_ALLOCATION` | caller’s previous node pointer unchanged |

For canonical limit 3, failure occurs when enqueueing `C6` would require a
fourth pending record.

### E1. Name the three TODO operations

1. `tree_level_order` — copy every visited key, flag, and depth in
   left-first BFS order.
2. `tree_find_shallowest` — return the first dequeued node whose key equals
   the target, together with its depth.
3. `tree_height_bfs` — compute edge height as the greatest reached depth,
   with `-1` for an empty tree.

### E2. Explain failure preservation

A later enqueue or 65th-node check can fail after partial work has already
been performed. Building into local temporary storage prevents that partial
candidate from replacing a valid caller result. Publish only after success;
otherwise the failed call appears not to have changed the caller’s output.

Search also delays publication until a match exists, so not found preserves
the prior match.

### E3. State Queue storage and ownership

The supplied typed Queue’s fixed 64-record array is stored inline inside a
local Queue object. It performs no dynamic allocation and requires no
destruction.

The Queue owns only its local work-record fields. It does not own, allocate,
release, or modify any tree node. Its copied pointers are borrowed.

### E4. State tree nonmutation

The functions may read each reached node’s `key`, `flagged`, `left`, and
`right` fields. They may change none of those fields and may not allocate,
release, relink, or replace a node.

### E5. State the input precondition

The caller must provide a finite acyclic tree with no shared child. Under
that rule, every node has one route from the root and is enqueued once.

If links reconnect without visited tracking, the same object could be
enqueued and processed repeatedly. A cycle could repeat until a course limit
stops the call; that is unsupported graph-like input, not valid tree BFS.

## F. Preview imbalance and one rotation

### F1. Measure the skewed BST

| Node | Left height | Right height | Height | Balance factor |
|---:|---:|---:|---:|---:|
| 10 | -1 | -1 | 0 | 0 |
| 20 | 0 | -1 | 1 | 1 |
| 30 | 1 | -1 | 2 | 2 |

### F2. Identify the imbalance

Node 30 is outside the later AVL range because its balance factor is `+2`.

### F3. Trace one right rotation

```text
root: 20
20.left: 10
20.right: 30
10.left and 10.right: NULL
30.left and 30.right: NULL
```

Diagram:

```text
   20
  /  \
10   30
```

### F4. Check what remains true

```text
inorder: 10,20,30
new root height: 1
balance factor of 10: 0
balance factor of 20: 0
balance factor of 30: 0
```

The rotation changed shape and height but preserved strict BST inorder.

### F5. Respect the preview boundary

Any two of these are valid:

- choosing which rotation applies;
- LL, RR, LR, and RL case names;
- double rotations;
- implementing rotation code;
- maintaining stored heights;
- AVL insertion;
- AVL deletion; or
- proving all AVL invariants after mutation.

## G. Design three tests — extension

Equivalent precise tests are acceptable. Require expected statuses, exact
outputs, and a clear preservation check.

### G1. Level order and depths

One complete new fixture:

```text
A(9,F)
├─ left: B(4,T)
│  └─ right: D(7,T)
└─ right: C(12,F)
```

With Queue limit 2, require:

```text
(9,F,0), (4,T,1), (12,F,1), (7,T,2)
```

Check count 4 and every key, flag, and depth. The comment should explain
what this fixture adds beyond a supplied test—for example, a missing left
child followed by a right child that must remain behind `C`.

### G2. Shallowest duplicate and missing preservation

One complete new fixture:

```text
A(9)
├─ left: B(5)
└─ right: C(8)
   └─ left: D(5)
```

Require target 5 to return exact pointer `B` at depth 1 rather than `D` at
depth 2. Then set the match to recognizable pointer/depth sentinels, search
for missing key 77, require `TREE_BFS_NOT_FOUND`, and verify both fields are
unchanged.

### G3. Height and Queue boundary

One complete new fixture:

```text
A(10)
├─ left: B(20)
│  └─ left: D(40)
└─ right: C(30)
```

With Queue limit 2, require `TREE_BFS_OK` and edge height 2. Reset height to
the recognizable sentinel 77, call with Queue limit 1, require
`TREE_BFS_LIMIT`, and verify height remains 77.

Equivalent fixtures earn credit when they establish the same distinct
claims and do not merely rename a supplied test.

## H. Conduct an autopsy and transfer to graphs — extension

### H1. Predict the isolated program

Faulty complete visit order:

```text
A, C, B, E, D
```

Faulty shallowest search for key 44 returns:

```text
E, depth 2
```

### H2. Locate the first broken decision

- First broken decision: immediately after visiting `A`, the faulty code
  enqueues right child `C` before left child `B`.
- Smallest repair: enqueue each non-`NULL` left child before its non-`NULL`
  right child.
- Regression test: build the exact autopsy tree, search for 44, and assert
  that the returned pointer is exactly `D` at depth 2, not merely any node
  with key 44.

The correct complete order is `A,B,C,D,E`. Both `D` and `E` are shallowest
matches at depth 2; the defect violates the published left-first tie, not
the minimum-depth property.

### H3. Transfer to graph BFS

A graph may contain cycles or several routes to one vertex. Without a
visited/discovered record, the same vertex could enter the Queue repeatedly
and a cycle could keep generating work. A valid tree has exactly one route
to each node, so that record is unnecessary here.

Do not require Module 9’s exact “mark on enqueue” rule yet.

## Tree BFS Autopsy — complete key

### 1. Predict before running

Exact visible lines, ignoring permitted trailing-space differences:

```text
complete observation: A C B E D
search observation:   A C B E
match: E at depth 2
```

Thus:

```text
predicted complete node-label order: A,C,B,E,D
predicted returned node/depth: E at depth 2
```

The search line ends at `E` because the function returns on its first
matching dequeue; it does not continue to `D`.

### 2. Observe the bounded program

The expected observation is the same three lines:

```text
complete observation: A C B E D
search observation:   A C B E
match: E at depth 2
```

“Yes, the observation matched” is complete when the learner’s prediction
was exact. If it was not, require preservation of the original prediction
and a concrete difference rather than an erased answer.

### 3. Locate the first broken decision

```text
frontier immediately after A: [C@1,B@1]
next node removed: C
required next node: B
first decision that made them differ:
the code enqueued A's right child C before its left child B
```

The final returned `E` is a later symptom, not the earliest defect.

### 4. Separate safety from correctness

Every Queue insertion checks capacity before calculating and writing its
bounded circular-array slot. Those checks can keep memory indexes valid, but
they do not determine which valid child is enqueued first. The program can
therefore remain memory-safe while violating the semantic left-first tie
contract.

Deleting a bounds or state check does not reverse the child order. It only
removes protection against an invalid access or invalid Queue state and can
turn a bounded logic defect into a memory-safety defect.

### 5. State the smallest repair

Swap the two child-addition blocks so each non-`NULL` left child is added
before the corresponding right child. Do not reverse the final output or
rewrite the Queue.

After repair:

```text
complete node-label order: A,B,C,D,E
search observation: A,B,C,D
returned node: D
returned depth: 2
```

### 6. Design a regression test

Exact `A`–`E` course-API adaptation:

```text
A(42,F)
├─ B(17,F)
│  └─ left D(44,T)
└─ C(68,F)
   └─ right E(44,F)
```

Require copied records:

```text
(42,F,0), (17,F,1), (68,F,1), (44,T,2), (44,F,2)
```

Require shallowest search for 44 to return the exact pointer `&D` at depth
2. The distinct flags make the two equal-key visits observable in
`TreeBfsOrder`.

One different valid test:

```text
root(9)
├─ left:  L(7)
└─ right: R(7)
```

Search 7 must return exact pointer `&L` at depth 1. A deeper opposite-side
version is also acceptable if both targets have equal depth and the expected
pointer is explicit.

### 7. Autopsy conclusion

```text
prediction: A,C,B,E,D; E@2
observation: A,C,B,E,D; E@2
first broken decision: right child C enqueued before left child B after A
smallest repair: enqueue left before right
regression test: equal-depth repeated key; require exact left-node pointer
```

## I. Exit reflection — extension

### I1. Answer the macro-question

Sample answer:

> BFS keeps discovered nodes in a FIFO Queue and stores each node with its
> depth. Because children join behind work already waiting, all smaller
> depths are dequeued first; adding left before right resolves equal-depth
> ties.

### I2. Compare the spiral steps

Sample:

- Module 7 Queue idea: earliest-added waiting work leaves first.
- Module 2 or 5 tree idea: nodes have left/right child pointers and depth is
  counted from the root.
- New BFS idea: the Queue frontier produces nondecreasing depth and a
  shallowest-match guarantee.

Equivalent accurate examples earn credit.

### I3. Preserve and correct

This response is individual. A complete answer must include:

1. the original claim without erasing it;
2. a clearly labeled correction or confirmation; and
3. specific evidence, such as a named frontier state, returned fixture
   pointer and depth, width/height calculation, or passing test.

Example:

> Initial claim: the frontier always contains one level.  
> Correction — frontier: after reveal node `R1`, the frontier is
> `[R2@1,R3@2]`, so adjacent depths can coexist.

---

# Evidence Template Reference Entries

Require actual commands and observations where the template asks for tool
evidence. The entries below provide the expected conceptual and fixture
facts; they are not a substitute for a learner’s run record.

## 1. BFS model

- **BFS and level order:** BFS processes smaller node depths before larger
  depths. Level order is the complete-tree visit order produced by that
  rule.
- **Depth and shallowest:** depth is the root-to-node child-link count;
  shallowest means minimum depth.
- **Frontier and work record:** the frontier is the FIFO Queue of reached,
  scheduled, not-yet-visited nodes; one work record pairs a node pointer with
  its depth.
- **Why FIFO works:** children are added after records already waiting, so
  newer deeper work cannot pass older nearer work.

## 2. Canonical trace

```text
complete key order:
42,17,68,23,91,17,5,44,44

complete flag order:
F,T,F,F,T,T,F,T,F

complete depth order:
0,1,1,2,2,2,2,3,3

largest Queue count:
4

one frontier state at that count:
[C3@2,C4@2,C5@2,C6@2]
```

Adjacent depths can coexist because children at depth `d + 1` join the back
while unvisited records at depth `d` can remain at the front.

## 3. Search evidence

| Target | Expected result |
|---:|---|
| 17 | `TREE_BFS_OK`, exact pointer `C1`, depth 1 |
| 44 | `TREE_BFS_OK`, exact pointer `C7`, depth 3 |
| 99 | `TREE_BFS_NOT_FOUND`, prior match unchanged |

Target 44 is an equal-depth tie because `C7` and `C8` both have depth 3.
The left-before-right discovery path places `C7` first.

For preservation evidence, initialize both match fields to recognizable
sentinels, snapshot them, search 99, and compare both fields byte-for-byte or
field-by-field after `TREE_BFS_NOT_FOUND`.

## 4. Shape measurements

```text
width at depth 0: 1
width at depth 1: 2
width at depth 2: 4
width at depth 3: 2
maximum width w: 4
edge height h: 3
root balance factor: 0

height(NULL): -1
height(leaf): 0
height(n-node one-child chain): n - 1
```

## 5. Contract and failure evidence

| Case | Expected status | Expected ending output |
|---|---|---|
| empty level order | `TREE_BFS_OK` | count 0 |
| nonempty, Queue limit 0 | `TREE_BFS_LIMIT` | starting order unchanged |
| canonical level order, Queue limit 4 | `TREE_BFS_OK` | nine canonical visits |
| canonical level order, Queue limit 3 | `TREE_BFS_LIMIT` | starting order unchanged |
| canonical search for 17, Queue limit 2 | `TREE_BFS_OK` | exact pointer `C1`, depth 1 |
| empty height | `TREE_BFS_OK` | `-1` |
| missing search | `TREE_BFS_NOT_FOUND` | starting match unchanged |

Local candidates prevent a partial traversal or partial height from becoming
visible when a later limit check fails.

## 6. Student-authored tests

Use the exact categories published in the final `test_student.c`, lab, and
worksheet. A full test states:

1. the distinct claim;
2. fixture and starting sentinels;
3. exact call sequence;
4. exact statuses and outputs;
5. preservation or nonmutation checks; and
6. observed result.

Reference designs for the exact level-order/depth, repeated/missing search,
and height/Queue-boundary categories appear in Stage C G1–G3 above.

## 7. Tool evidence

Answers are environment-specific. Require:

- actual compiler name and version or the approved alternative;
- the exact command copied rather than “ran tests”;
- the complete pass/fail summary;
- every warning, including “none”; and
- sanitizer output when that tool is available.

Do not invent a sanitizer result for a learner whose environment lacks one.

## 8. Storage and ownership

The work array is inside the local `TreeWorkQueue` object. It is not
dynamically allocated, so it requires no release or destroy call.

Separately allocated tree nodes are owned by the valid tree after they are
linked. `TreeBfsMatch.node` becomes unsafe when its node or owning tree is
destroyed or otherwise ends its lifetime.

Cleanup evidence should show:

```text
destroy result: TREE_BFS_OK
root after destroy: NULL
live-node count: returned to its starting baseline, when the hook is used
```

The constructed-node count must match the learner’s actual fixture.

## 9. BFS and DFS costs

| Method | Full-traversal time | Auxiliary space | Shape that stresses it |
|---|---:|---:|---|
| BFS | `O(n)` | `O(w)` | wide, shallow tree |
| DFS | `O(n)` | `O(h)` | long one-child chain |

`TreeBfsOrder` is a required output, while auxiliary space means temporary
working storage separate from input and output.

## 10. Balance preview

```text
heights before:
10=0, 20=1, 30=2

balance factors before:
10=0, 20=1, 30=2

relationships after right rotation:
root 20; 20.left=10; 20.right=30; all other children NULL

inorder after:
10,20,30

height after:
1

balance factors after:
10=0, 20=0, 30=0
```

## 11. Tree BFS Autopsy

```text
predicted faulty order: A,C,B,E,D
observed faulty order: A,C,B,E,D
predicted returned node: E at depth 2
observed returned node: E at depth 2
first broken decision: enqueueing C before B after A
smallest repair: enqueue left before right
regression test: repeated key 44 at D and E; require exact pointer D@2
```

If actual observation differs, preserve it and investigate the build or
fixture rather than copying the expected line.

## 12. Transfer and correction

A valid tree has one route to each node, while a graph can contain cycles or
several routes to one vertex. Graph BFS therefore needs reached-state
tracking to avoid repeatedly adding the same vertex.

The correction is individual. Require the preserved claim, a labeled
change, and specific evidence.

---

# Canonical lab expectations

The learner lab and evidence form should be scored against these behaviors:

## `tree_level_order`

- `NULL` root with accepted limit publishes an empty order.
- Nonempty root with limit 0 reports `TREE_BFS_LIMIT`.
- Queue limit greater than 64 reports `TREE_BFS_LIMIT`.
- Visit occurs on dequeue.
- Every visit copies key, flag, and depth.
- Left child is enqueued before right child.
- A 65th reached node reports `TREE_BFS_LIMIT`.
- Caller output changes only on `TREE_BFS_OK`.
- Tree fields never change.

## `tree_find_shallowest`

- `NULL` root reports `TREE_BFS_NOT_FOUND`.
- Compare target immediately after dequeue.
- Return the first dequeued matching node and its depth.
- Repeated targets obey minimum depth and left-before-right equal-depth tie.
- Stop immediately on success.
- Not found and every failure preserve both output fields.
- The returned node pointer is borrowed.

## `tree_height_bfs`

- `NULL` root succeeds with `-1`.
- A leaf succeeds with 0.
- A nonempty result is the greatest dequeued depth.
- Queue and 64-node limits match the other BFS operations.
- Caller height changes only on success.

## Supplied operations

- `tree_node_create` may report `TREE_BFS_ALLOCATION` and preserves the
  caller’s node pointer on failure.
- `tree_bst_insert` is strict and reports `TREE_BFS_DUPLICATE` for an
  existing key.
- `tree_destroy_postorder` releases owned children before parent and resets
  the root.
- These supplied strict-BST operations do not imply that BFS input must be a
  BST.

## Cost evidence

Accept:

```text
complete BFS time: O(n)
BFS auxiliary space: O(w)
complete DFS time: O(n)
DFS auxiliary space: O(h)
```

The learner must explain that adjacent depths can coexist. A precise bound
is at most `2w` pending records in a valid binary-tree BFS, which remains
`O(w)`. Do not require the literal `2w` proof from a beginner if the
frontier explanation is otherwise correct.

## Safe-meaning statement

A complete response states that the program traverses only a valid,
synthetic, single-threaded, in-memory tree. It does not validate live
pointers, follow cycles safely, inspect a real system, or prove a real
policy secure.
