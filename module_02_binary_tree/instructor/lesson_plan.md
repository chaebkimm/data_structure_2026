# Instructor Lesson Plan — Module 2: Child-Only Binary Trees

## Purpose and limits

This module uses ordinary local node variables. Each `struct TreeNode`
stores one integer plus independent `left` and `right` child pointers.
There is no upward pointer. Relationships form a binary tree only when the
caller preserves the no-cycle, no-sharing, and live-object preconditions.

Chapter 1 supplies fixed arrays, conditions, loops, and invariants. Introduce
addresses, pointers, explicit structure tags, `NULL`, and recursive calls
here. Do not assume Chapter 1 taught these new representation features.

The module has two 90-minute meetings. It does not teach binary-search ordering,
balancing, arbitrary-graph validation, or a resizable child collection.
Clearing resets existing objects; it does not end their lifetimes.

## Learning targets

Students will be able to:

1. identify root, parent, child, sibling, leaf, path, depth, height, and subtree;
2. translate a binary hierarchy among a diagram, a left/right table, and C;
3. initialize a local node and distinguish the object from its address;
4. explain why a right-only child is valid;
5. distinguish local attachment checks from whole-tree caller preconditions;
6. trace and implement recursive current-left-right search;
7. clear a selected subtree descendant-first and detach only its chosen link;
8. explain why the unselected side never shifts; and
9. support claims with tests, compiler evidence, and an autopsy explanation.

## Canonical representation

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

Use this tree for the Stage B reveal:

```text
             root:'*'
             /      \
        plus:'+'    two:2
          /   \
     three:3 five:5
```

It represents `(3 + 5) * 2`, and its current-left-right order is
`'*', '+', 3, 5, 2`. Left and right identify operand positions, so students
must not treat the two links as interchangeable.

Stage C uses the fresh expression `(8 - 3) * (4 + 2)`: root `'*'`, left
child `minus:'-'` with children `eight:8` and `three:3`, and right child
`plus:'+'` with children `four:4` and `two:2`. Students translate a fresh set
of labels rather than repeat the first table.

Binary operators in these expression fixtures have exactly two operands.
Keep that expression rule distinct from the general `TreeNode`
representation, which also permits valid zero-child and one-child nodes.

## Beginner language sequence

| Word or symbol | First-use explanation |
|---|---|
| node | an object storing one value and child links |
| address | a location that identifies an object |
| pointer | a C value holding an address or `NULL` |
| `&node` | the address of a node variable |
| `node.data` | a field selected directly from an object |
| `p->data` | a field selected through a pointer |
| `NULL` | no child at this position |
| binary tree | a tree with two named positions, left and right |
| expression tree | a tree whose operator nodes connect to operand subexpressions |
| operator and operand | an action and the values or subexpressions it combines |
| parent | the node immediately above another in the hierarchy |
| leaf | a node whose left and right links are both empty |
| path | a route following child links |
| depth | number of links from the root to a node |
| height | longest downward route to a leaf, counted in links |
| subtree | one node and every node below it |
| lifetime | the time during which an object remains usable |
| recursion | calling the same function on a smaller part of the problem |
| base case | an input handled without further recursive calls |
| current-first search | inspect the current node, then the left and right subtrees |
| cascading clearance | reset every node in a selected branch |
| detach | remove a link to a branch |
| precondition | a fact the caller must establish before an operation |

A parent is a relationship, not a stored field in this representation.
Require students to name the exact local variable, pointer, or child side
rather than saying only “the node.”

## Five release gates

| Gate | Release time | Give students | Hold back |
|---|---|---|---|
| A — Initial inquiry | before Meeting A | standard or linear hierarchy prompt | representation, vocabulary, code, answers |
| B — Model and pause | after the first model is saved | left/right reveal, vocabulary, three-target Cognitive Pause | expert calibration and investigation |
| C — Investigation | after the pause and calibration | standard or linear structural investigation | worked notes, code, answers |
| D — Textbook and models | after the Stage C attempt is saved | textbook and diagram/text models | lab, autopsy prediction answers, instructor materials |
| E — Lab and evidence | Meeting B | lab, 100-point rubric, evidence form, autopsy, header, starter, public tests, build files | solution, instructor extension tests, answer key |

Accommodations may change timing without changing the reasoning target.
Preserve the sequence “attempt, compare, correct.” Vocabulary begins in
Stage B, never as an early exception in Stage A. Stage D must not contain a
worked answer to the Stage E autopsy.

# Meeting A — Model and Reason (90 minutes)

## Macro-question

> How can separate node variables form a hierarchy using only left and right
> links, and what rules keep recursive operations meaningful?

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–8 | Retrieve fixed-array bounds, conditions, and invariants | Entry response |
| 8–18 | Stage A hierarchy inquiry | Preserved first model |
| 18–28 | Compare branching models without introducing code early | Annotated relationships |
| 28–38 | Stage B reveal: local nodes, addresses, and two child sides | Node/field labels |
| 38–43 | Five-minute Cognitive Pause | Three independent responses |
| 43–54 | Calibrate side identity, caller rules, and search order | Corrected pause |
| 54–70 | Stage C translation, paths, and legal local changes | Worksheet traces |
| 70–80 | Trace clearing and removal in the Stage C tree | Reset and surviving-link table |
| 80–88 | Compare a tree with a shared or cyclic relationship model | Transfer explanation |
| 88–90 | Exit ticket | One supported invariant claim |

## Stage B calibration

The three pause targets are:

1. read the named child positions and explain that a right-only node is valid;
2. explain why placing `root` below leaf `three` would create a cycle even
   though the selected side is empty; and
3. trace the search for `2` as `'*', '+', 3, 5, 2`, explaining why the whole
   left subtree is visited before the right operand.

For the proposed cycle, distinguish “invalid for a tree” from “automatically
detected by an empty-side check.” Whole-tree acyclicity is the caller's
responsibility.
Do not execute a recursive search or clear on the invalid example.

## Representation demonstration

Declare or draw five separate node objects. Initialize their data and empty
links, then connect their addresses. Show these two equivalent views:

```c
root.left = &plus;
struct TreeNode *p = &root;
/* p->left and root.left contain the same address. */
```

Physical adjacency does not determine the relationship. The link does.
No child needs to store how it was reached.

## Invariant calibration

A valid tree has one starting root and:

- no repeated node on any downward route;
- no node reached through two child links;
- only initialized, live node objects at nonempty links; and
- at most one child at each named side.

Both links may be empty. Either link may be empty independently of the
other. A direct empty-side check inspects the selected field; it is not a
whole-tree validator. The only two library functions are recursive find and
clear.

## Search trace routine

For each call, ask:

1. Is the current pointer empty?
2. Does this node's data match?
3. What returned from the complete left subtree?
4. Should the right subtree be searched?
5. Which address or empty result returns to the caller?

Use a missing target to establish worst-case `O(n)` visits. Use equal data
in separate nodes to establish that the first current-left-right match wins.

## Clear and remove trace

For the Stage C left branch, reset `eight` and `three` before `minus`, then
empty the root's left link. The `plus` node remains on the right with its
children `four` and `two` unchanged. The reset local variables still exist.
The remaining links form a valid generic tree, but not a completed binary
expression because the `'*'` node now has only its right operand.

Emphasize two separate responsibilities: recursive clearance changes the
selected objects, and removal changes the link in the node above them.
Calling a child-only clear operation cannot discover or erase that incoming
link.

## Formative checks

- Is a right-only node valid? Yes.
- Is it a leaf? No.
- Does a right child have to store a larger number? No.
- Does an empty side prove a proposed link is globally safe? No.
- Does clearing a local node make its address unusable? Not while its scope
  remains active.
- Can a returned address outlive the local variable it identifies? No.
- Should removing the left branch move the right branch? No.

# Between meetings

1. Preserve the Stage C attempt before releasing Stage D.
2. Ask students to annotate earlier answers using the textbook and models.
3. Release Stage E for Meeting B.
4. Validate reference tests and the isolated autopsy with strong warnings
   and supported runtime checks.

# Meeting B — Implement, Test, and Explain (90 minutes)

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–8 | Retrieve the model and current-left-right order | Re-entry response |
| 8–18 | Read the two-function contract and mark caller preconditions | Header annotations |
| 18–30 | Practice direct initialization and guarded selected-side attachment | Side-preservation tests |
| 30–48 | Implement recursive current-left-right search | Search trace and tests |
| 48–66 | Implement recursive clearance | Descendant-reset tests |
| 66–73 | Practice caller-side removal and unchanged opposite side | Surviving-link tests |
| 73–80 | Run public tests and finish three distinct student tests | Transcript and rationales |
| 80–87 | Preserve an autopsy prediction, then run and explain it | Incident record |
| 87–90 | Check submission against the 100-point rubric | Evidence checklist |

## Coaching boundaries

Coach the contract, not a memorized solution:

- Which object exists before this function is called?
- Which fields need initialization?
- Which single side may this successful operation change?
- What remains unchanged after a local rejection?
- Which global facts are the caller's responsibility?
- What is the recursion base case?
- Which descendants must be visited before these links are reset?
- Why is the right side still right after removing the left?

Do not accept a claim of automatic no-cycle/no-sharing validation without
code and a contract that actually provide it. Do not ask students to add
such validation as hidden core work.

## Tests, autopsy, and assessment

Require three nonduplicate student-authored tests with a rationale for each:

1. search boundaries or first-match selection with duplicate data in a valid
   tree;
2. direct initialization and selected-side behavior, such as an occupied-side
   guard or caller detachment with the opposite side unchanged; and
3. cascading clearance and reuse of a cleared, still-live local node.

Use the student rubric's 100-point core:

| Criterion | Points |
|---|---:|
| Representation and invariants | 20 |
| Direct node operations | 15 |
| Recursive search | 20 |
| Clearing, removal, and lifetime | 20 |
| Operation efficiency | 10 |
| Tests and tool evidence | 10 |
| Autopsy and forward transfer | 5 |
| Total | 100 |

Instructor extension tests add boundary and sequence evidence; they do not
add parent tracking, extra library APIs, or graph validation requirements.
The current-left-right order is called preorder in later traversal work;
name memorization and traversal-order comparisons are not Chapter 2 core.

The isolated autopsy is an invariant exercise. Its malformed expression
`(3 + 5) * (5 - 2)` uses one `shared_five` node as an operand of both `plus`
and `minus`. Students predict before running, compare observable link/data
state, explain the violated rule, and propose a regression test. A crash is
not the target. Keep worked fixture answers in the instructor answer key only.

Provide linear text, selectable commands, verbal or tactile equivalents, and
instructor CI where needed. Grade reasoning and evidence, not drawing
quality, typing speed, or exact memorized terminology.
