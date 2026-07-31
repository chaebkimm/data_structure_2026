# Instructor Lesson Plan - Module 5: Tree Depth-First Traversal

## Purpose and limits

This module returns to the binary-tree representation from Module 2 and the
Stack contract from Module 4. Students learn **depth-first traversal**, a
procedure that follows one branch before returning to a postponed branch.
They compare two ways to remember unfinished work:

- recursive functions, whose active calls are remembered by the C runtime;
  and
- an explicit Stack whose items are `const TreeNode *` pointers.

The module uses this canonical strict binary search tree (BST):

```text
                 50
               /    \
             30      70*
            /  \
          20   40*
```

An asterisk marks a flagged node. Key `30` is also flagged, so the flagged
keys in preorder are `30, 40, 70`. In text form: root `50`; its left child is
`30`, whose children are `20` and `40`; its right child is `70`. Nodes `30`,
`40`, and `70` are flagged.

By the end of the module, students should be able to:

1. identify `NULL` as the recursive base case;
2. trace recursive preorder, inorder, and postorder;
3. explain what active recursive calls remember;
4. reproduce left-first preorder with a typed explicit Stack;
5. trace and complete strict-BST search;
6. explain why postorder is appropriate for releasing an owned tree;
7. implement recursive and iterative preorder within a 64-node boundary;
8. analyze traversal as `O(n)` time and `O(h)` auxiliary space; and
9. state why aliases, shared children, cycles, or symbolic links require a
   graph model with visited tracking.

The lab uses only synthetic, in-memory trees. It does not inspect a real
filesystem, follow real symbolic links, or decide a real security policy.
Insertion is an instructor-supplied baseline. Students inspect and test it
now; full insertion and balancing return in Module 14.

## Beginner language sequence

Introduce a term immediately before students need it. Repeat its short
definition when the term returns in Meeting B.

| Term | First-use explanation |
|---|---|
| node | One stored tree item |
| key | The integer used here to identify and order a node |
| root | The starting node of a tree |
| child | A node directly below another node |
| left subtree | The tree beginning at a node's left child |
| right subtree | The tree beginning at a node's right child |
| pointer | A value that stores a memory address |
| `NULL` | A pointer value meaning "no node here" |
| flag | A Boolean marker that is either true or false |
| visit | Process one node; here, record its key and flag |
| traversal | A procedure that visits every reachable tree node once |
| depth first | Follow a branch before returning to a postponed branch |
| recursive function | A function that calls itself directly or indirectly |
| base case | An input that ends a recursive branch without another call |
| recursive case | An input that is handled partly through more recursive calls |
| active call | A function call that has started but has not returned |
| runtime call stack | Bookkeeping commonly used by C for active calls |
| call frame | Saved information for one active function call |
| preorder | Visit node, then left subtree, then right subtree |
| inorder | Visit left subtree, then node, then right subtree |
| postorder | Visit left subtree, then right subtree, then node |
| explicit Stack | A Stack object operated by program code |
| bottom and top | Oldest and newest available ends of the explicit Stack |
| push | Add one item at the explicit Stack's top |
| pop | Remove and report the explicit Stack's top item |
| binary search tree (BST) | A tree with smaller keys throughout each left subtree and larger keys throughout each right subtree |
| strict BST | A BST that rejects duplicate keys |
| search path | The nodes examined while looking for one key |
| dynamic allocation | Requesting storage while a program runs |
| ownership | Responsibility for eventually releasing requested storage |
| destroy | Release every owned node and reset the root |
| auxiliary space | Extra storage used while an algorithm runs |
| height `h` | The greatest number of downward child links on a root-to-leaf path |
| node count `n` | The number of nodes in the tree |
| acyclic | Containing no path that leads back to an earlier node |
| sharing | Two child fields identifying the same node |
| alias | Another name or path that identifies an already reachable object |
| symbolic link | A filesystem entry that redirects to another path |
| visited tracking | A record of which graph vertices have already been processed |
| application programming interface (API) | Public types and function names other code may use |
| status code | A named result reporting success or one kind of failure |
| output | A result written into caller-provided storage |
| failure atomicity | A failed operation leaves caller-visible state unchanged |
| public test | A check visible to students |
| extension test | A private instructor check used to verify the same published contract |
| test hook | A controlled testing-only way to simulate a difficult condition |
| synthetic | Invented for safe practice rather than read from a live system |

Do not describe recursion as "magic" or say that the function "just goes
back." Name the saved active call and the next instruction it must perform.
Do not call the explicit `const TreeNode *` Stack "the call stack." The mechanisms
remember related information, but they are distinct.

## Five release gates

A **release gate** is a planned point when students receive the next
materials. Preserve an initial model before opening formal explanations.

| Gate | Release point | Give students | Keep back |
|---|---|---|---|
| A - Inquiry | Start of Meeting A | Standard or linear inquiry prompt | DFS, recursion, traversal-order vocabulary, code, answers |
| B - Representation | After each student preserves an initial model | Representation reveal and exactly-three-target Cognitive Pause | Vocabulary file during the pause; investigation answers, textbook, code |
| C - Investigation | After the five-minute pause and comparison | Standard or linear investigation worksheet | Textbook, completed models, code |
| D - Calibrated explanation | After the student preserves Stage C core Sections A-F | Beginner-first notes and equivalent tree/trace models | Lab package and instructor materials |
| E - Lab and evidence | After retrieval and Gate D calibration in Meeting B | Lab, evidence form, rubric, autopsy, public header, starters, public tests and hooks, student-test template, and build files | Reference solution, extension tests, answer key |

The vocabulary file remains closed for the entire Cognitive Pause. During
that timer, instructors may repeat directions and provide approved access
support, but may not provide definitions, hints, answer checks, or a fourth
target. The answer key, reference solution, and extension tests remain
private until the instructor-selected review point. Stage E includes the
public core allocation-failure hooks under `TREE_DFS_TESTING`.

An accommodation may change time, response method, lighting, room, or
assistive technology. It does not reverse the sequence of attempt, preserve,
and compare. Stage C core is Sections A through F. Sections G through I may
continue in the announced independent completion window.

---

# Meeting A - Discover How Depth-First Work Is Remembered (90 minutes)

## Macro-Question

> If we follow one branch as far as possible, how do we remember every branch
> to which we must return?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0-6 | Welcome and boundary | Reconstruct only the Module 2 five-node tree. Do not retrieve the Module 4 LIFO rule yet because it would give away the remembered-work model. State that all examples are synthetic. | Correct tree description |
| 6-19 | Gate A inquiry | Release one inquiry format. Require an individual, preserved first response before discussion. | Initial route and memory model |
| 19-29 | Compare branch routes | After initial answers are preserved, retrieve the Module 4 LIFO rule. Ask students to point, speak, type, or move cards through the tree and identify what must be remembered at each fork. Keep formal traversal-order names closed. | One justified complete route |
| 29-39 | Gate B representation reveal | Reveal the node-first/left-first/right-later procedure and the equivalence of saved active calls and postponed nodes. Do not release the vocabulary file. | Labeled representation |
| 39-44 | Five-minute Cognitive Pause | Release exactly the three targets below. Repeat directions only; preserve independent responses. | Three-target response |
| 44-53 | Compare and correct | Open vocabulary only after every response is preserved. Students annotate rather than erase initial work. Read every diagram as a parent/child list. | Corrected evidence |
| 53-64 | Three visit placements | Define visit, preorder, inorder, and postorder. Move the visit action before, between, and after the two recursive calls. | Three exact key orders |
| 64-73 | Recursive call trace | Treat `NULL` as a real input to the helper and the base case. At key `20`, count only active calls whose node is non-`NULL`: `50`, `30`, `20`. | Active-call trace |
| 73-82 | Explicit Stack trace | State Stack contents bottom to top. Push right before left so left is popped next. Trace the two required snapshots. | Correct Stack snapshots |
| 82-87 | BST search retrieval | Reapply strict BST order: smaller goes left, larger goes right. Contrast search with visiting every node. | Search paths |
| 87-90 | Exit and Gate C | Release the investigation. Ask which visit placement is safe for destroying owned nodes and why. | Postorder claim |

## Stage B Cognitive Pause - exactly three targets

Students receive the exact three targets in `student/cognitive_pause.md`:

1. For the tree whose root is `12`, whose children are `5` and `17`, and
   whose node `5` has children `2` and `9`, state preorder, inorder, and
   postorder.
2. For the course tree when recursive preorder has reached key `20`, explain
   the `NULL` left-child call, list active non-`NULL` calls oldest to newest,
   and name the work remembered by calls `30` and `50`.
3. For iterative left-first preorder of the course tree, state the explicit
   Stack bottom to top after visiting `50`, state it after visiting `30`,
   and explain why right is pushed before left.

The exact responses are:

1. preorder `12, 5, 2, 9, 17`; inorder `2, 5, 9, 12, 17`; postorder
   `2, 9, 5, 17, 12`;
2. the `NULL` call returns immediately; active non-`NULL` calls are
   `50, 30, 20`; call `30` must finish its right subtree at `40`, and call
   `50` must finish its right subtree at `70`; and
3. after `50`: `70, 30`; after `30`: `70, 40, 20`; right is pushed first so
   LIFO removal selects left next.

Keep these responses private during the pause. Do not add another target.

## Meeting A checks

Before moving on, verify that students can state:

- `NULL` is the smallest valid subtree and ends one recursive branch;
- recursive preorder is node, left subtree, right subtree;
- inorder is left subtree, node, right subtree;
- postorder is left subtree, right subtree, node;
- the canonical orders are preorder `50, 30, 20, 40, 70`, inorder
  `20, 30, 40, 50, 70`, and postorder `20, 40, 30, 70, 50`;
- at key `20`, the active non-`NULL` calls are `50`, `30`, and `20`;
- the runtime remembers active recursive calls;
- an explicit Stack remembers postponed node pointers;
- right must be pushed before left for left-first iterative preorder;
- strict-BST search goes left for smaller and right for larger; and
- postorder handles children before their parent.

---

# Meeting B - Implement Checked Recursive and Iterative Traversal (90 minutes)

## Coding question

> How can recursive calls and an explicit Stack produce the same preorder
> while preserving every API contract?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0-8 | Retrieval | Without notes, give the three canonical orders and the two explicit-Stack snapshots. Preserve before comparison. | Retrieval trace |
| 8-14 | Gate D calibration | Reopen the textbook and models. Correct visit placement, base case, Stack direction, and ownership language. | Annotated correction |
| 14-20 | Gate E orientation | Release the lab. Define header, starter, public test, private extension test, and public test hook before naming package files. | Package map |
| 20-30 | Public model and contracts | Read `TreeNode`, `TreeVisit`, `TreeOrder`, and `TreeDfsStatus`. Establish the 64-visit boundary and unchanged-output rule. | Contract table |
| 30-42 | Recursive preorder | Write the `NULL` base case first. Check the output boundary before recording a visit; recurse left, then right. | Passing recursive core tests |
| 42-55 | Iterative preorder | Initialize the typed pointer Stack, push root, then repeat pop/visit/push right/push left. Trace every return path and destroy the Stack. | Matching preorder and limit tests |
| 55-63 | Flag report and other orders | Filter recorded visits by `flagged`. Inspect the supplied inorder and postorder implementations and connect order to visit placement. | Flagged sequence and three-order table |
| 63-71 | Strict-BST search | Complete the scaffold: equality succeeds, smaller chooses left, larger chooses right, `NULL` means not found. Delay output writes until success. | Found/missing traces |
| 71-79 | Ownership and cleanup | Contrast Module 2's caller-owned arena with individually allocated nodes. Complete `tree_destroy_postorder` using supplied `tree_node_release`. Require children to be released before parent. | Ownership and release order |
| 79-84 | Cost analysis | Define `n`, `h`, time, and auxiliary space. Compare balanced and skewed height. | `O(n)`/`O(h)` explanation |
| 84-88 | Safe autopsy | Predict the faulty iterative order before running. Identify the first bad decision, then write a regression test. | Prediction, observation, fix |
| 88-90 | Boundary and submission | State acyclic/no-sharing precondition, graph visited requirement, synthetic scope, required evidence, and completion window. | Complete checklist |

## Canonical public model

The public header is the source of truth. It defines:

```c
#define TREE_DFS_MAX_NODES 64U

typedef struct TreeNode {
    int key;
    bool flagged;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;
```

`TreeVisit` is one copied visit record. `TreeOrder` stores up to 64 records
and their count. The function chosen determines preorder, inorder, or
postorder. The status enumeration appears in this exact order:

```text
TREE_DFS_OK
TREE_DFS_INVALID_ARGUMENT
TREE_DFS_LIMIT
TREE_DFS_ALLOCATION
TREE_DFS_DUPLICATE
TREE_DFS_NOT_FOUND
```

The exact public functions are:

```c
TreeDfsStatus tree_node_create(
    int key, bool flagged, TreeNode **out_node);
void tree_node_release(TreeNode *node);
TreeDfsStatus tree_bst_insert(
    TreeNode **root, int key, bool flagged);
TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_inorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_postorder_recursive(
    const TreeNode *root, TreeOrder *out_order);
TreeDfsStatus tree_preorder_iterative(
    const TreeNode *root, size_t stack_limit, TreeOrder *out_order);
TreeDfsStatus tree_bst_search(
    const TreeNode *root, int target, const TreeNode **out_node);
TreeDfsStatus tree_destroy_postorder(TreeNode **root);
const char *tree_dfs_status_name(TreeDfsStatus status);
```

All traversal outputs remain unchanged on failure. A `NULL` root is a valid
empty tree and produces a successful empty traversal. Public traversal is
bounded to at most 64 visits. Iterative `stack_limit` is valid from zero
through 64 inclusive.

The explicit Stack stores `const TreeNode *` values and uses its own
`NodeStackStatus`. Do not substitute `TreeDfsStatus` for the Stack's internal
contract. Its dynamic-array rules repeat Module 4: checked arguments and
state, geometric growth, an explicit limit, no output mutation on failure,
failure atomicity, and one matching destroy.

## Canonical recursive model

Teach preorder as this language-independent pattern:

```text
preorder(node):
    if node is NULL:
        return
    record node
    preorder(node.left)
    preorder(node.right)
```

Moving "record node" between the child calls creates inorder. Moving it after
both child calls creates postorder. Do not teach three unrelated algorithms;
teach one recursive shape with three visit positions.

At the moment key `20` is being processed, the active calls whose node
arguments are not `NULL` are, oldest to newest:

```text
50, 30, 20
```

After the call for `20` asks to process its missing left child, a short-lived
call receives `NULL` and immediately returns. If that `NULL` call is shown in
a full event trace, label it separately; do not include it in the requested
count of active non-`NULL` calls.

## Canonical iterative model

For left-first preorder:

```text
push root
while Stack is not empty:
    node = pop
    record node
    push node.right when non-NULL
    push node.left when non-NULL
```

Because a Stack is last in, first out, pushing right before left makes left
the next item removed. Required snapshots, written bottom to top:

```text
after visiting 50: 70, 30
after visiting 30: 70, 40, 20
```

The autopsy intentionally pushes left before right. It therefore records:

```text
50, 70, 30, 40, 20
```

The first bad decision is the push order immediately after visiting `50`.
The repair is to push the right child before the left child. Merely reversing
the final output hides rather than repairs the contract violation.

## Canonical search and ownership rules

A strict BST has no duplicate keys. Search compares once per examined node:

- equal means found;
- smaller goes left;
- larger goes right; and
- reaching `NULL` means `TREE_DFS_NOT_FOUND`.

On `TREE_DFS_NOT_FOUND` or another failure, the caller's output pointer remains
unchanged. The supplied insertion baseline applies the same left/right rule,
rejects duplicates with `TREE_DFS_DUPLICATE`, and preserves the tree on failure.
Students inspect and test it; implementation returns in Module 14.

Each successful constructor creates one individually allocated node. The
receiving tree owns that node after successful insertion. A node not
transferred into a tree remains the caller's responsibility.
`tree_destroy_postorder` releases the left subtree, then the right subtree,
then the parent, and resets the caller's root. It must not read a child field
after the parent has been released.

This model requires a valid tree: child links are acyclic, no node is shared
by two parents, and no child points to an object outside the owned tree.
Those are preconditions, not properties proven by traversal. If aliases,
symbolic links, sharing, or cycles are possible, the structure is graph-like
and later DFS must record which vertices were already visited.

## Hint ladder

Reveal only one hint at a time:

1. Which node is current, and what work remains at that node?
2. Is the node pointer `NULL`?
3. Where does the visit occur relative to the two child calls?
4. Which non-`NULL` calls are active right now?
5. For the explicit version, what is the Stack from bottom to top?
6. Which child must be removed next?
7. Because removal is LIFO, which child must be pushed first?
8. Has the output reached the fixed 64-visit limit, or has the iterative
   method reached its caller-selected Stack limit?
9. Can success be known before changing an output?
10. In BST search, is the wanted key smaller, equal, or larger?
11. Who owns this node, and what must remain usable before the parent is
    released?
12. Has every temporary Stack allocation been destroyed on this return path?

Stop after the first hint that restores productive work. Record hint level
for instructional planning, not as a grade penalty.

## Common misconceptions

| Misconception | Diagnostic question | Correction |
|---|---|---|
| `NULL` is an error | "What tree has no nodes?" | A `NULL` root is the valid empty tree and the recursive base case. |
| A leaf needs a special traversal rule | "What do its two child calls receive?" | The same rule works; both child pointers are `NULL`. |
| Preorder means sorted order | "Where is the visit placed?" | Preorder is node-left-right; inorder is sorted only for a valid BST. |
| Inorder always sorts any binary tree | "Does the tree satisfy strict BST order?" | Sorted inorder follows from BST ordering, not tree shape alone. |
| Postorder visits the parent first | "Can a released parent still safely provide child addresses?" | Postorder handles both children before the parent. |
| Recursion stores no state | "How does execution know what follows the child call?" | Each active call commonly has a call frame with saved continuation state. |
| The explicit Stack is the runtime call stack | "Which one does student code call `push` on?" | Program code controls the explicit Stack; C manages active calls. |
| Push left first for left-first preorder | "Which pushed item will be popped first?" | Push right, then left, because the Stack is LIFO. |
| Stack contents equal visit output | "Has every stored node been processed yet?" | Stack items are postponed work; output items are completed visits. |
| BST search must visit every node | "Which subtree can the key comparison rule eliminate?" | Strict ordering selects at most one child at each step. |
| Missing search may replace the output with `NULL` | "What does the failure contract preserve?" | `TREE_DFS_NOT_FOUND` leaves the output unchanged. |
| Every traversal uses `O(n)` extra space | "How many nodes are simultaneously active or postponed?" | Auxiliary space is `O(h)` for recursive DFS and a suitable explicit implementation. |
| Freeing parent before children is harmless | "Where will the child pointers be read afterward?" | Read and destroy both child subtrees before releasing the parent. |
| A tree traversal is safe on cycles | "What base case stops a link back to an ancestor?" | `NULL` alone cannot stop a cycle; graph DFS needs visited tracking. |
| A valid flag report proves security | "What did the synthetic example actually check?" | It demonstrates traversal only, not real authorization correctness. |

## Accessibility and pacing

- Pair every tree diagram with the parent/left/right text description.
- Pair every recursive-call drawing with an oldest-to-newest event list.
- Pair every vertical Stack drawing with a bottom-to-top row.
- Read `node->left` aloud as "the node pointer's left child address."
- Read `O(n)` as "order n" and explain it before using the notation.
- Never use color alone for flags, current nodes, visit placement, or
  corrected work; use labels, asterisks, borders, or text.
- Permit cards, tactile nodes, speech, typing, handwriting, or a scribe for
  traces.
- Supply the linear inquiry and investigation versions when spatial layout
  is a barrier.
- During the Cognitive Pause, read all three targets, permit an approved
  extended timer, and provide no content hint or vocabulary access.
- For extended-time equivalence, keep the same three targets, order,
  independence, and closed resources; change only the approved duration.
- Accept a numbered parent/child list instead of a drawing and a numbered
  event list instead of arrows.
- Grade traversal decisions and contract reasoning, not drawing quality,
  indentation, pointer-address handwriting, typing speed, or visual memory.
- Announce the independent completion window before coding starts.

## Evidence collected

1. preserved Gate A route and saved-work model;
2. exactly-three-target Cognitive Pause with visible later corrections;
3. exact preorder, inorder, postorder, and flagged-preorder sequences;
4. recursive active-call and `NULL` base-case trace;
5. explicit-Stack snapshots and push-order explanation;
6. recursive and iterative preorder implementations with matching results;
7. found and missing strict-BST search traces with output preservation;
8. ownership statement and postorder cleanup evidence;
9. empty, single-node, balanced, skewed, limit, and allocation-failure test
   results;
10. `O(n)` time and `O(h)` auxiliary-space explanation;
11. autopsy prediction, first bad decision, repair, and regression test; and
12. tree-precondition, graph-transfer, and synthetic-scope statements.

## After Meeting B - transparent completion window

The two meetings establish every core concept and implementation path, but
they need not contain all debugging and evidence writing. Allow about 75-105
additional minutes for students to finish starter functions, run public
tests, write original tests, complete the autopsy, and submit the evidence
form. Offer a staffed lab period or equivalent remote support. Keep the due
window visible from Gate E onward and apply documented accommodations.

Public tests reveal examples of the published contract; they are not a list
of every grading case. Stage E includes the public core test hooks guarded by
`TREE_DFS_TESTING`; normal builds do not expose them. Only the reference
solution and extension tests remain private. Instructor tests must exercise
only published behavior.

## Instructor readiness checklist

- [ ] Stage A does not reveal DFS, recursion, preorder, inorder, postorder,
      push, pop, or the formal solution.
- [ ] The Stage B vocabulary file remains closed during the pause.
- [ ] The Stage B pause contains exactly three targets.
- [ ] The canonical tree and flagged nodes match every student file.
- [ ] The three traversal orders and flagged preorder are exact.
- [ ] `NULL` is taught as the base case, not an invalid node.
- [ ] The active non-`NULL` calls at key `20` are `50, 30, 20`.
- [ ] Explicit Stack snapshots use bottom-to-top order.
- [ ] Right is pushed before left for left-first preorder.
- [ ] Gate D follows preserved Stage C core Sections A-F.
- [ ] Gate E follows retrieval and Gate D calibration in Meeting B.
- [ ] All types, statuses, parameters, and limits match the public header.
- [ ] A `NULL` root is accepted as an empty traversal.
- [ ] Failed traversal and search operations leave outputs unchanged.
- [ ] Constructor/insertion ownership and postorder destruction are explicit.
- [ ] The supplied insertion baseline is inspected, not assigned for
      implementation.
- [ ] The autopsy's first bad decision and regression test are required.
- [ ] Visual models have equivalent text or table forms.
- [ ] Graph visited tracking is motivated without teaching Module 6 early.
- [ ] Synthetic scope and the completion window are announced.
