# Instructor Technical Notes — Module 8

## Source of truth

The public header is authoritative for spelling, field order, status order,
parameters, and limits. These notes explain the required behavior; they do
not expand the public API.

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

`TreeNode` stores one integer key, one Boolean flag, and two child pointers.
A **pointer** stores a memory address. `NULL` means no node. A **Boolean**
value is either `true` or `false`.

`TreeBfsVisit` is a copied result record. Changing or destroying the tree
after a successful traversal does not change the copied key, flag, or depth
already stored in `TreeBfsOrder`.

`TreeBfsMatch` is different: its `node` is a borrowed pointer into the input
tree. **Borrowed** means ownership does not transfer. The caller must not
release the matched node separately and must stop using the pointer before
the tree is destroyed.

The status enumeration has this exact order:

```text
TREE_BFS_OK
TREE_BFS_INVALID_ARGUMENT
TREE_BFS_LIMIT
TREE_BFS_ALLOCATION
TREE_BFS_DUPLICATE
TREE_BFS_NOT_FOUND
```

The exact readable names are:

| Status | `tree_bfs_status_name` result |
|---|---|
| `TREE_BFS_OK` | `"ok"` |
| `TREE_BFS_INVALID_ARGUMENT` | `"invalid argument"` |
| `TREE_BFS_LIMIT` | `"tree or Queue limit reached"` |
| `TREE_BFS_ALLOCATION` | `"allocation failed"` |
| `TREE_BFS_DUPLICATE` | `"duplicate key"` |
| `TREE_BFS_NOT_FOUND` | `"key not found"` |
| any unknown value | `"unknown TreeBfsStatus"` |

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

Students implement only `tree_level_order`, `tree_find_shallowest`, and
`tree_height_bfs`. Node construction, one-node release, strict-BST
insertion, postorder destruction, status naming, and the typed work Queue
are supplied.

## Tree precondition

All three BFS functions assume that `root` is either `NULL` or identifies a
valid finite binary tree:

1. every non-`NULL` child pointer identifies a live `TreeNode`;
2. the root has no parent;
3. every other node has exactly one parent;
4. no child-link path returns to an earlier node;
5. no two child fields share the same node; and
6. the caller keeps every node alive for the complete call.

The functions do not validate these properties. They do not maintain a
visited set. A **visited set** is storage recording which objects were
reached before.

This precondition is what makes “enqueue each child” equivalent to “enqueue
each node once.” If links reconnect, the same pointer could be enqueued
again. The 64-node guard may eventually stop some malformed inputs, but it
does not turn a graph-like input into a supported tree and must not be
described as structural validation.

Module 9 introduces graph discovery state and defines exactly when a graph
vertex is marked.

## General tree versus strict BST

The BFS functions operate on any valid binary tree. They do not require BST
ordering and do not interpret numeric magnitude as scheduling priority.
Repeated keys are valid.

The supplied `tree_bst_insert` has a narrower contract: it builds a strict
BST, in which every left-subtree key is lower, every right-subtree key is
higher, and duplicate keys are rejected with `TREE_BFS_DUPLICATE`.

Consequently, the canonical Module 8 tree cannot be created by repeatedly
calling `tree_bst_insert`; it deliberately contains two nodes with key 17
and two with key 44. Build that teaching fixture by creating distinct nodes
and assigning the published child relationships. The labels `C0` through
`C8` name fixture variables, not `TreeNode` fields.

## Ownership and lifetime

Each successful `tree_node_create` obtains one separately allocated node.
Before a node is linked into a tree, its caller owns it. After a successful
link or insertion transfers it into the tree, the tree owns it.

`tree_destroy_postorder` releases both child subtrees before releasing their
parent and resets the caller’s root pointer to `NULL`. It requires the same
acyclic, unshared ownership tree as traversal. Releasing a borrowed search
result separately would create a dangling child pointer and later
double-release risk.

The three BFS functions accept `const TreeNode *`. `const` means they may
inspect nodes but must not change keys, flags, child pointers, or allocation
ownership.

## Supplied typed Queue

The support Queue stores this conceptual record:

```text
node   const pointer to one scheduled TreeNode
depth  that node's root-to-node child-link count
```

It is a **typed Queue** because it accepts only this record type. Its backing
array is inline: the 64 record slots are fields of a local Queue object.
There is no Queue allocation, allocation-failure hook, initialization
allocation, or destruction operation. The local Queue stops existing when
the BFS call returns.

The Queue owns only its inline work-record slots. It never owns a tree node.
Copying a node pointer into a work record does not copy or transfer the node.

`TREE_BFS_ALLOCATION` remains part of the shared status enumeration because
the supplied node constructor and strict-BST insertion may need allocation.
The three BFS functions perform no allocation and do not return
`TREE_BFS_ALLOCATION`.

The Queue’s physical implementation is support code rather than a student
TODO. Students retrieve Module 7’s FIFO contract but do not reimplement
circular wrap-around here.

The supplied private representation is:

```c
typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeWorkItem;

typedef struct {
    TreeWorkItem data[TREE_BFS_MAX_NODES];
    size_t limit;
    size_t head;
    size_t size;
} TreeWorkQueue;
```

Its internal statuses are, in order:

```text
WORK_QUEUE_OK
WORK_QUEUE_INVALID_ARGUMENT
WORK_QUEUE_LIMIT
WORK_QUEUE_UNDERFLOW
WORK_QUEUE_INVALID_STATE
```

Its representation rules are:

```text
limit <= 64
size <= limit
size == 0 requires head == 0
size > 0 requires limit > 0 and head < limit
tail = (head + size) % limit only when another item can be enqueued
```

Initialization accepts limits 0 through 64, sets `head` and `size` to zero,
and does not need to clear the inactive array slots. A full enqueue reports
`WORK_QUEUE_LIMIT` and preserves all fields and established slots. Empty
dequeue reports `WORK_QUEUE_UNDERFLOW` and preserves its output. Removing
the final item normalizes `head` to zero.

Readable internal names are:

| Internal status | Result |
|---|---|
| `WORK_QUEUE_OK` | `"ok"` |
| `WORK_QUEUE_INVALID_ARGUMENT` | `"invalid argument"` |
| `WORK_QUEUE_LIMIT` | `"Queue limit reached"` |
| `WORK_QUEUE_UNDERFLOW` | `"Queue is empty"` |
| `WORK_QUEUE_INVALID_STATE` | `"Queue representation is invalid"` |
| any unknown value | `"unknown TreeWorkQueueStatus"` |

Public BFS code maps `WORK_QUEUE_LIMIT` to `TREE_BFS_LIMIT`. Other unexpected
internal Queue failures map to `TREE_BFS_INVALID_ARGUMENT`; they indicate a
support-code or internal-state defect rather than a published new status.

## Meaning of `queue_limit`

`queue_limit` is the greatest number of pending work records permitted at
one time during this call. It is not:

- the tree’s total node count;
- the number of completed visits;
- the output capacity; or
- a promise that the input contains no more nodes.

The accepted parameter range is 0 through 64 inclusive. A value greater
than 64 reports `TREE_BFS_LIMIT`.

A `NULL` root needs no work record:

- empty level order succeeds at queue limit 0;
- empty height succeeds at queue limit 0 and writes `-1`; and
- empty search reports `TREE_BFS_NOT_FOUND` at queue limit 0.

A nonempty tree must first enqueue its root, so queue limit 0 reports
`TREE_BFS_LIMIT`.

Before each enqueue, support code must ensure that adding one record would
not exceed `queue_limit` or the physical 64-record bound. On failure, the
public operation returns `TREE_BFS_LIMIT` and leaves caller output unchanged.

## Independent 64-node processing bound

`TreeBfsOrder` holds at most 64 copied visits. All three BFS algorithms use
the same `TREE_BFS_MAX_NODES` processing boundary, including search and
height, so their behavior does not depend on whether an output happens to
store every visit.

Maintain a reached-node count. Before accepting the 65th dequeued/reached
node as part of the algorithm:

```text
if reached count is already 64:
    report TREE_BFS_LIMIT
```

The 65th node is not compared as a successful search match and is not used
to update height. A target found among the first 64 dequeued nodes may
succeed immediately even if unexamined links would lead to additional
nodes. Search is allowed to stop once its published result is known.

For complete traversal and height, a 65-node chain reaches the 65th-node
limit even though its pending Queue count never exceeds 1. This distinguishes
the processing bound from `queue_limit`.

## Error precedence

Use one consistent public order:

1. validate the required output pointer;
2. validate `queue_limit <= TREE_BFS_MAX_NODES`;
3. handle the `NULL` root according to the requested operation;
4. initialize local candidate output and local Queue state;
5. process records while enforcing Queue and reached-node limits; and
6. publish the local candidate only on success.

Therefore:

- a `NULL` required output pointer reports `TREE_BFS_INVALID_ARGUMENT`,
  even if another parameter is also unusable;
- a non-`NULL` output with queue limit 65 reports `TREE_BFS_LIMIT`, including
  when root is `NULL`; and
- a `NULL` root with an accepted queue limit follows the empty-tree rules.

Do not add pointer-origin checks, structural validation, hidden key-order
validation, or allocation behavior to these APIs.

## Failure preservation

All three BFS functions are read-only with respect to the tree.

`tree_level_order` must stage a complete `TreeBfsOrder` locally. Only
`TREE_BFS_OK` publishes it. Invalid argument or limit leaves every byte of
the caller’s prior `TreeBfsOrder` unchanged.

`tree_find_shallowest` publishes `TreeBfsMatch` only on
`TREE_BFS_OK`. `TREE_BFS_NOT_FOUND`, invalid argument, or limit leaves both
the caller’s prior node pointer and prior depth unchanged.

`tree_height_bfs` publishes the candidate integer height only on
`TREE_BFS_OK`. Invalid argument or limit leaves the prior integer unchanged.

The internal Queue and partial local results require no caller-visible
cleanup after an error.

## Canonical BFS invariant

An **invariant** is a rule that remains true at each completed loop
boundary. For the course BFS loop:

1. every queued record identifies a discovered but not yet visited node;
2. every visited node has been dequeued exactly once;
3. queued depths are nondecreasing from front to back;
4. queued records belong to at most two adjacent depths;
5. records at one depth retain left-before-right discovery order;
6. each child record has depth exactly one greater than its parent record;
7. no node is both already visited and still queued; and
8. the local reached count does not exceed 64.

The valid-tree precondition supports “exactly once.” FIFO supports
nondecreasing depth. Enqueueing left before right supports the tie order.

## Why only two adjacent depths coexist

When processing a record at depth `d`:

- older records already waiting have depth `d` or `d + 1`;
- newly enqueued children have depth `d + 1`; and
- no depth-`d + 2` child can be generated before a depth-`d + 1` record is
  dequeued.

Once the final depth-`d` record leaves, the Queue contains only depth
`d + 1`. This establishes level-by-level progress without requiring a
separate level delimiter.

## Level-order algorithm

Language-independent model:

```text
level_order(root, queue_limit, output):
    reject a missing output
    reject queue_limit greater than 64
    if root is NULL:
        publish empty order
        succeed

    candidate.count = 0
    enqueue (root, 0), respecting queue_limit

    while Queue is not empty:
        record = dequeue
        reject a 65th reached node

        candidate.items[candidate.count] =
            (record.node.key, record.node.flagged, record.depth)
        candidate.count += 1

        enqueue left child at record.depth + 1 when non-NULL
        enqueue right child at record.depth + 1 when non-NULL

    publish candidate
    succeed
```

The key and flag are copied at visit time. The function does not filter
unflagged nodes and does not sort keys.

If enqueueing either child exceeds the Queue limit, discard the local
candidate by returning `TREE_BFS_LIMIT`. The caller’s old output remains
unchanged even if several records were already copied locally.

## Shallowest-match algorithm

Language-independent model:

```text
find_shallowest(root, target, queue_limit, output):
    reject a missing output
    reject queue_limit greater than 64
    if root is NULL:
        report not found without changing output

    enqueue (root, 0), respecting queue_limit

    while Queue is not empty:
        record = dequeue
        reject a 65th reached node

        if record.node.key equals target:
            publish (record.node, record.depth)
            succeed

        enqueue non-NULL left child
        enqueue non-NULL right child

    report not found without changing output
```

Check the current node immediately after dequeue and before enqueueing its
children. The first match is shallowest because dequeued depths never
decrease. The left-before-right tie follows from the child-enqueue rule, not
from key magnitude or pointer address.

Stopping at the first dequeued match is part of the API. Continuing after a
known first match would add needless work and could incorrectly turn a valid
early success into a later limit failure.

## Height-by-BFS algorithm

The course uses edge height:

```text
height(NULL) = -1
height(leaf) = 0
height(nonempty tree) = greatest node depth
```

Language-independent model:

```text
height_bfs(root, queue_limit, output):
    reject a missing output
    reject queue_limit greater than 64
    if root is NULL:
        publish -1
        succeed

    candidate_height = 0
    enqueue (root, 0), respecting queue_limit

    while Queue is not empty:
        record = dequeue
        reject a 65th reached node
        candidate_height = record.depth
        enqueue non-NULL left child
        enqueue non-NULL right child

    publish candidate_height
    succeed
```

Because depths are nondecreasing, the most recently dequeued depth is the
greatest depth so far. Using an explicit maximum comparison is also correct
and may make the invariant clearer.

Depth uses `size_t`, but the public height output is `int` so the empty-tree
value `-1` can be represented. The 64-node boundary keeps every nonempty
height well within `int`.

## Canonical fixture

```text
C0(42,F)
├─ C1(17,T)
│  ├─ C3(23,F)
│  └─ C4(91,T)
│     └─ C7(44,T)
└─ C2(68,F)
   ├─ C5(17,T)
   └─ C6(5,F)
      └─ C8(44,F)
```

Exact level order:

```text
C0@0, C1@1, C2@1, C3@2, C4@2, C5@2, C6@2, C7@3, C8@3
```

Copied records:

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

Frontier after each completed visit:

```text
C0: [C1@1,C2@1]
C1: [C2@1,C3@2,C4@2]
C2: [C3@2,C4@2,C5@2,C6@2]
C3: [C4@2,C5@2,C6@2]
C4: [C5@2,C6@2,C7@3]
C5: [C6@2,C7@3]
C6: [C7@3,C8@3]
C7: [C8@3]
C8: []
```

Search results:

```text
target 17 -> C1, depth 1
target 44 -> C7, depth 3
target 99 -> TREE_BFS_NOT_FOUND, output unchanged
```

The second 44, `C8`, is also at depth 3. `C7` wins because `C4` occurs
before `C6` in left-first level order and therefore enqueues `C7` before
`C6` enqueues `C8`.

For a full traversal, height calculation, or search that continues through
this state, the maximum pending count is 4 after `C2`. Queue limit 4
succeeds. Queue limit 3 fails on the attempted enqueue of `C6`, after `C5`
has filled the third pending slot:

```text
before visiting C2: [C2@1,C3@2,C4@2]
after dequeue C2:   [C3@2,C4@2]
enqueue C5:         [C3@2,C4@2,C5@2]
enqueue C6:         would require count 4 -> TREE_BFS_LIMIT
```

The partially built local traversal, match state, or height is not
published.

## Complexity

Let:

- `n` be the number of reached tree nodes;
- `h` be edge height; and
- `w` be maximum level width.

Each node is enqueued once and dequeued once. Child inspection is constant
per node. A complete level order or height therefore takes `O(n)` time.
An unsuccessful search also takes `O(n)` time. A successful search takes
time proportional to the prefix through its first match, with `O(n)` as the
worst case.

At a transition between levels, the Queue may contain:

- remaining nodes from depth `d`, at most `w`; and
- already generated children at depth `d + 1`, also at most `w`.

Thus the pending count is at most `2w` for a binary tree. Growth notation
omits the constant factor, giving `O(w)` auxiliary space. This is an
asymptotic bound, not a claim that peak pending count equals one level width.

The fixed inline array physically reserves 64 work records in this teaching
implementation. Conceptual analysis still reports the amount of active
working information required by an input shape as `O(w)`. Be explicit about
the distinction between a fixed course maximum and algorithmic growth.

The required `TreeBfsOrder` result is output, not auxiliary space. It stores
`O(n)` copied visits. DFS likewise produces `O(n)` output when asked to
record every visit, while its separate recursive or explicit-Stack working
state is `O(h)`.

Shape comparison:

```text
seven-node one-child chain:
h = 6, w = 1
BFS Queue need follows w; DFS active path follows h

seven nodes in levels 1, 2, 4:
h = 2, w = 4
BFS Queue need follows w; DFS active path follows h
```

Neither BFS nor DFS always uses less working storage.

## Width and balance calculations

Canonical level widths:

```text
depth 0: C0                         -> 1
depth 1: C1,C2                      -> 2
depth 2: C3,C4,C5,C6                -> 4
depth 3: C7,C8                      -> 2
maximum width w = 4
```

Canonical node heights:

```text
C3=0, C5=0, C7=0, C8=0
C4=1, C6=1
C1=2, C2=2
C0=3
```

With balance factor defined as left-subtree height minus right-subtree
height:

```text
C0=0
C1=-1
C2=-1
C4=+1
C6=-1
every leaf=0
```

The canonical tree is not a BST because it does not satisfy the strict
global key-order rule and contains duplicates. Do not call it an AVL tree,
even though these local shape factors lie in the later AVL range.

## Manual balance preview

Use a separate strict BST:

```text
    30
   /
  20
 /
10
```

Before rotation:

```text
node 10: left -1, right -1, height 0, factor 0
node 20: left  0, right -1, height 1, factor 1
node 30: left  1, right -1, height 2, factor 2
```

One instructor-led right rotation at 30 produces:

```text
   20
  /  \
10   30
```

Afterward:

```text
node 10: height 0, factor 0
node 30: height 0, factor 0
node 20: height 1, factor 0
inorder before and after: 10,20,30
```

The preview establishes only that a local link change can lower height
without changing BST inorder. It does not teach case naming, selection
rules, double rotations, stored-height repair, AVL insertion, or code.

## Safe autopsy mechanics

Fixture:

```text
A(42)
├─ left: B(17)
│  └─ left: D(44)
└─ right: C(68)
   └─ right: E(44)
```

The correct left-first trace is:

```text
start [A@0]
visit A -> [B@1,C@1]
visit B -> [C@1,D@2]
visit C -> [D@2,E@2]
visit D -> first 44 at depth 2
```

The bounded faulty code enqueues right before left:

```text
start [A@0]
visit A -> [C@1,B@1]
visit C -> [B@1,E@2]
visit B -> [E@2,D@2]
visit E -> first 44 at depth 2
```

Complete faulty visit order is `A,C,B,E,D`. The first broken decision is the
enqueue order immediately after `A`. The minimal repair is left enqueue
before right enqueue. A suitable regression test asserts that searching 44
returns the exact pointer `D`, not merely a node whose key is 44.

Do not say the fault destroys the shallowest-depth guarantee: both matches
are at depth 2. It violates the separately published left-before-right tie
rule. This distinction is the main autopsy evidence.

## Required test interpretation

Public core evidence should cover:

- public result fields and status-name fallbacks;
- supplied constructor invalid-output and forced-allocation failures;
- supplied strict-BST insertion success, duplicate rejection, allocation
  failure, and failure preservation;
- supplied postorder destruction and root reset;
- empty level order with queue limit 0;
- empty height `-1` with queue limit 0;
- empty search not found with unchanged match output;
- one-node traversal, search, and height 0;
- canonical copied key/flag/depth order;
- canonical search 17, search 44, and missing 99;
- canonical full-traversal and height limit-4 success and limit-3 failure;
- canonical early search 17 success with limit 2;
- queue limit 65 rejection;
- nonempty queue limit 0 rejection;
- output preservation for traversal, search, and height failures;
- a right-skewed height;
- a wide-tree Queue boundary; and
- direct typed-Queue FIFO, wrap, full, underflow, and status behavior.

Private extension evidence should add:

- an exact 64-node accepted boundary;
- 65th-reached-node rejection with preserved traversal, search, and height
  outputs;
- early root-target success before an oversized remainder is explored;
- a complete 63-node tree whose Queue limit 32 succeeds and 31 fails;
- tree-field snapshots proving nonmutation after success, not found, and
  limit failure;
- circular-Queue validity at every possible head position;
- invalid Queue-state rejection with unchanged state and output; and
- constructor and BST-insertion allocation-failure atomicity.

Student-authored evidence contains three independently meaningful tests in
this order:

1. exact left-first level order with every copied key, flag, and depth;
2. a repeated-key shallowest match and missing-key match preservation; and
3. exact edge height plus a too-small Queue limit that preserves the prior
   height.

## Security and systems boundary

The policy/process language is motivational only. The model omits:

- concurrent tree mutation;
- unreliable or adversarial pointers;
- cycles, aliases, and symbolic links;
- live operating-system permissions;
- authentication and authorization decisions;
- durable logging;
- process races; and
- resource limits beyond the published teaching bounds.

BFS can report the shallowest matching node in this valid in-memory tree.
It does not prove that the stored tree is accurate, that a match is
security-relevant, or that a real system is safe.

## Deferred topics

Do not add these to Module 8 core:

- graph visited/discovered arrays;
- marking on enqueue;
- graph distances or predecessors;
- path reconstruction;
- disconnected traversal forests;
- graph adjacency representations;
- shortest-path claims;
- generic `void *` Queues;
- another circular-buffer implementation;
- recursive height as a required alternative;
- BST insertion implementation;
- AVL case names or rotation code;
- stored-height fields;
- AVL insertion or deletion; or
- live system traversal.

## Instructor validation checklist

- [ ] The header and all prose use a maximum of 64.
- [ ] Statuses appear in the exact required order.
- [ ] Only the three BFS functions are student TODOs.
- [ ] The typed Queue is inline and allocation-free.
- [ ] `TREE_BFS_ALLOCATION` is not attributed to BFS traversal.
- [ ] Queue limit measures simultaneously pending work records.
- [ ] Empty input succeeds for traversal and height at limit 0.
- [ ] Empty search reports not found and preserves output.
- [ ] A nonempty input at limit 0 reports limit.
- [ ] A limit above 64 reports limit.
- [ ] The 65th reached node reports limit in every BFS operation.
- [ ] All failures preserve caller output.
- [ ] Search not found preserves both match fields.
- [ ] BFS operations never mutate or own tree nodes.
- [ ] General-tree repeated keys are distinguished from strict-BST insert.
- [ ] The canonical flag, depth, and Queue traces are exact.
- [ ] Canonical full traversal and height succeed with limit 4 and fail
      with limit 3 at `C6` enqueue; early search 17 succeeds with limit 2.
- [ ] Search stops at the first dequeued match.
- [ ] Search 44 returns pointer `C7`, not merely key 44.
- [ ] Height uses `NULL=-1` and leaf=0.
- [ ] Complexity is `O(n)` time and `O(w)` auxiliary space.
- [ ] Prose says Queue peak is bounded by `2w`, not necessarily equal to `w`.
- [ ] The canonical general tree is never called an AVL tree.
- [ ] The rotation preview remains manual and uses the separate strict BST.
- [ ] The autopsy remains bounded and memory-safe.
- [ ] The graph visited-state requirement is motivated but not implemented.
- [ ] No real security guarantee is inferred from synthetic tests.
