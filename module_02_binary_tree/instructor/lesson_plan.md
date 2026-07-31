# Instructor Lesson Plan — Module 2: Binary-Tree Foundations

## Purpose and limits

This module introduces a **hierarchy**, an arrangement in which objects are
placed above or below other objects. Students represent the hierarchy with a
**binary tree**, a structure in which each object has at most two direct
**children**, objects directly below it.

The module deliberately uses a fixed, non-resizing **arena**: one already
created array that holds every node used in the exercise. A **node** is one
object in the tree. Students do not request memory, resize memory, or call
`free`, the C function that releases previously requested memory, in this
module. An **address** is a memory location. A **pointer** is a C variable
that stores an address.
An **invariant** is a rule that must hold whenever a completed structure is
used. A **validator** is a function that checks stated rules. A **graph** is a
collection of objects and less-restricted relationships. A **traversal** is a
planned process for visiting nodes, and an **algorithm** is a precise sequence
of problem-solving steps. Formal traversal algorithms wait until later
modules.

By the end of the module, students should be able to:

1. name and locate a root, parent, child, leaf, path, depth, height, and
   subtree;
2. translate one small tree among a diagram, an array-index table, and C
   pointers;
3. state and test the rooted-binary-tree invariant;
4. implement checked questions about one node and make a checked local child
   assignment;
5. use supplied whole-tree validators without implementing traversal;
6. explain the ordering rule that changes a binary tree into a **binary search
   tree**, a binary tree arranged by lower and higher keys;
7. explain which relaxed tree rules lead toward a graph.

## Beginner language sequence

Introduce each word immediately before students need it.

| Word | First-use explanation |
|---|---|
| object | One stored item with its own fields |
| relationship | A connection between two objects |
| address | A number-like location identifying where an object is stored |
| pointer | A C variable that stores an address |
| index | An array position; C begins numbering positions at zero |
| `NULL` | A special pointer value meaning “no object” |
| node | One object in a tree |
| root | The one starting node; it has no parent |
| parent | A node directly above another node |
| child | A node directly below another node |
| binary tree | A tree in which every node has at most two children |
| leaf | A node with no children |
| path | A sequence of connected nodes |
| depth | The number of links from the root to a node |
| height | The greatest number of downward links from a node to a leaf |
| subtree | A node together with every node below it |
| invariant | A rule that must be true whenever a completed structure is used |
| reachable | Able to be reached by starting at the root and following child pointers |
| cycle | A path that returns to a node already on that same path |
| validator | A function that checks whether stated rules hold |
| traversal | A planned process for visiting the nodes of a structure |
| local check | A check of only the requested node or link |
| whole-tree check | A check involving every node and relationship |
| output | A result a function writes into a variable supplied by its caller |
| caller | The code that asks a function to run |
| `TreeSide` | A named choice between the left and right child fields |
| `TreeStatus` | A named result describing success or the kind of failure |
| key | The integer value used to compare nodes |
| binary search tree (BST) | A binary tree with a global lower-key/higher-key ordering rule |
| graph | A collection of objects and relationships without the parent/child restrictions of a tree |

Do not use “obvious,” “simply,” “just recurse,” or unexplained family
metaphors. Ask students to point to exact nodes and pointers.

## Five release gates

A **release gate** is a planned point when the instructor makes another set of
materials available. The gates prevent later explanations from replacing the
student’s first attempt.

| Gate | Release time | Give students | Hold back |
|---|---|---|---|
| A — Initial inquiry | Before Meeting A | Standard or linear initial prompt | Node representation, vocabulary reference, invariant answer, code |
| B — Representation | After students preserve their first relationship model | Representation reveal, three-target Cognitive Pause, and post-pause vocabulary reference | Instructor explanation and structural worksheet |
| C — Investigation | After the pause and instructor relationship explanation | Standard or linear structural investigation worksheet | Beginner notes, completed models, code |
| D — Notes and models | After Meeting A and completion of the Stage C core | Example-first beginner notes and diagrams with text equivalents | Lab package and all instructor materials |
| E — Lab and evidence | At the start of Meeting B | Lab, rubric, evidence form, autopsy, public header, starter, public tests, student-test template, and build files | Reference solution, instructor tests, answer key |

Reference answers and the solution remain instructor-only until the
instructor’s chosen post-submission review. They are not a sixth student
release gate.

Students needing an accommodation may receive material earlier without
penalty. Preserve the order of “attempt, compare, calibrate” even when the
timing changes.

---

# Meeting A — Model and Reason (90 minutes)

## Macro-Question

> How can memory addresses represent a hierarchy, and what rules keep those
> connections from becoming an unrestricted graph?

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Welcome and retrieval | Revisit Module 1: an address can identify an object even when objects are not conceptually adjacent. Define “object,” “address,” and “pointer.” | One-sentence retrieval |
| 8–18 | Human hierarchy model | Use labeled cards. Define root, parent, child, and binary tree. Limit every card to a left and right child position. | Spoken or written labels |
| 18–29 | Missing children | Introduce `NULL` as “no child.” Define leaf. Ask whether a one-child node is a leaf. | Two classifications with reasons |
| 29–42 | Three representations | Translate the five-node example among a tree diagram, child-index table, and `&nodes[i]` pointer expression. Stress that logical position means role in the tree, not neighboring memory. | Completed translation |
| 42–47 | Gate B Cognitive Pause | Release the three-target prompt. Students work alone for five minutes on representation, structural change, and BST order. | Initial individual model |
| 47–59 | Peer comparison and expert calibration | Partners compare exact links. Release the expert model only after both have committed an answer. | Corrected model in a second color, annotation style, or revision block |
| 59–72 | What makes it a tree? | Define invariant, reachable, and cycle. Test cards showing a second parent, a cycle, and an unreachable node. | Violation name plus offending link |
| 72–82 | Gate C and BST preview | Release the investigation. Work through its structural-rule and global-order cases. Define key, subtree, binary search tree, and range. State that duplicate keys are rejected. | Deep-violation explanation |
| 82–88 | Tree → Graph transfer | Add a shared child and then a back-link. Define graph. Ask which tree rule each added link breaks and why the relation may still be useful. | Two-rule comparison |
| 88–90 | Exit ticket | “What must be true of every completed course tree?” Explain the between-meetings task and preserve every first response. | Invariant statement |

## Between meetings — Complete, then read

Allow about 60–75 minutes for students to finish the Stage C worksheet in
the standard or linear format. Sections D–J are the core; Section K is the
short exit check. Release Gate D—the notes and models—only after the
student has submitted or preserved that core attempt. Students then use the
notes to label corrections before Meeting B. An approved extended-time or
asynchronous schedule preserves the same attempt-before-explanation order.

## Cognitive Pause prompt

Use the released five-node table:

| Node index | Key | Left-child index | Right-child index |
|---:|---:|---:|---:|
| 0 | 50 | 1 | 2 |
| 1 | 30 | 3 | 4 |
| 2 | 70 | none | none |
| 3 | 20 | none | none |
| 4 | 40 | none | none |

Students complete exactly three targets:

1. report the root key, the two addresses in its child fields, and all leaf
   indexes;
2. decide whether `nodes[3].left = &nodes[0]` leaves a valid tree and name
   the relevant whole-tree rule;
3. decide whether changing the key at index `4` to `60`, or to a duplicate
   `50`, satisfies the course BST rule.

Accept a structured list, tactile model, or spoken response instead of a
drawing.

## Meeting A checks

Before moving on, verify that students can say:

- `left` and `right` store addresses, not whole child objects;
- `NULL` means that the corresponding child is absent;
- array index and tree depth are different ideas;
- checking only an immediate child cannot prove the whole BST rule;
- a shared child or cycle is rejected by the course tree model.

---

# Meeting B — Build and Verify (90 minutes)

## Scope reminder

An **application programming interface (API)** is the set of named functions
other code is allowed to call. Students complete only the small local API.
The whole-tree structural validator and range-based BST validator are
supplied. Students call and interpret them and trace key limits on small
examples. They do not implement either validator or classify its
link-following order.

| Minutes | Activity | Instructor move | Evidence |
|---:|---|---|---|
| 0–8 | Gate E and invariant retrieval | Release the lab package. Keep editors closed while students state the root, parent, reachability, cycle, and child-count rules. | Retrieval response |
| 8–21 | C syntax sandbox | Define a sandbox as a short, isolated practice. Build `TreeNode` and `TreeArena` one field at a time. Define `struct`, `->`, `&nodes[i]`, pointer, and `NULL` as they appear. | Four expression translations |
| 21–31 | Fixed arena and lifetime | Define lifetime as the period when an object exists. Explain that the arena points to, but does not own, its array. `malloc` requests memory, `realloc` resizes a request, and `free` releases one; none is used here. | Ownership sentence |
| 31–43 | Checked local questions | Students predict and then implement checked leaf and child-count functions. Failed requests do not change output values. | Focused public tests |
| 43–54 | Immediate family | Students report a node’s parent, left child, and right child. The parent is found by checking the arena because nodes store no parent pointer. | Family record for three nodes |
| 54–64 | Local child assignment | Students implement the checked local assignment. It verifies arguments, index bounds, selected side, empty destination, and direct self-link. Explain what it cannot prove. | Local tests and limitation statement |
| 64–72 | Construct candidate tree | Students initialize all links to `NULL`, assign the supplied child table, and set the root. A **candidate** is a not-yet-approved structure. | Fixed-arena construction |
| 72–79 | Supplied structural validator | Validate the completed candidate. Deliberately create one shared child, one cycle, and one unreachable node, restoring the valid tree each time. | Three detected failures |
| 79–84 | Supplied BST validator | Run the range-based validator on the valid example, a deep ordering violation, and a duplicate key. | Results with reasons |
| 84–88 | Tree → Graph transfer | State which rejected relationship becomes normal in a graph. Define bookkeeping as extra recorded facts, then identify what later graph work must record. | Transfer statement |
| 88–90 | Exit and submission check | Collect the representation translation, C results, violation analysis, and BST preview. | Complete evidence list |

## After Meeting B — Finish and document

The 90-minute meeting establishes the model and starts each core function;
it is not expected to absorb every student's debugging and documentation
time. Allow about 45–75 additional minutes for students to finish the starter
TODOs, run the supplied tests, write three original tests, complete the
autopsy, and finish the evidence record. Provide an instructor-supported lab
period or equivalent asynchronous help for students who need it.

## Core API teaching contracts

A **contract** states what a function accepts, returns, changes, and preserves.
Use the actual package names if they differ, but preserve these concepts:

```c
typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *nodes;
    size_t count;
    TreeNode *root;
} TreeArena;
```

- `tree_arena_init`: copies supplied keys into the fixed node array, clears
  every child link, and selects the root by array index;
- `tree_node_is_leaf`: reports whether both child pointers are `NULL`;
- `tree_node_child_count`: reports zero, one, or two non-`NULL` children;
- `tree_assign_child`: accepts parent and child indexes plus a `TreeSide`,
  then changes one empty child pointer only after local checks pass;
- `tree_immediate_family`: reports parent, left-child, and right-child
  indexes; `TREE_NO_INDEX` means that a relative is absent;
- supplied `tree_validate_structure`: checks the completed whole-tree
  invariant;
- supplied `tree_validate_bst`: passes allowable lower and upper key limits
  through the whole tree and rejects duplicate keys;
- `tree_status_name`: turns a numeric `TreeStatus` result into a short
  explanation suitable for messages. `TREE_ERR_INVALID_STRUCTURE` means the
  links do not form a valid tree. `TREE_ERR_NOT_BST` means the links do form a
  valid tree, but at least one key breaks strict BST ordering.

## Hint ladder

Reveal one prompt at a time:

1. Which object does this pointer identify?
2. Is the pointer allowed to be `NULL` here?
3. Is the pointed-to node one of the arena’s nodes?
4. Does this question concern only one node or the whole tree?
5. Can another parent already point to this child?
6. Could following this link eventually return to an earlier node?
7. Have all nodes in the arena been reached from the root?
8. What lower and upper key limits apply at this node?

## Common misconceptions

| Misconception | Diagnostic question | Correction |
|---|---|---|
| A child is stored inside its parent | “What is the declared type of `left`?” | It is a pointer storing a child’s address. |
| Array neighbors must be tree relatives | “Must `nodes[2]` be a child of `nodes[1]`?” | No. Pointers, not array adjacency, define the tree. |
| `NULL` is a node with key zero | “Can `NULL->key` be read?” | No. `NULL` means no object is present. |
| A node with one child is a leaf | “How many non-`NULL` child pointers does it have?” | A leaf has zero children. |
| Two local comparisons prove BST order | “Could a larger value hide deeper in the left subtree?” | Every descendant must remain inside its inherited range. |
| A successful local assignment proves a valid tree | “Could the child already have a different parent?” | Whole-tree facts require the supplied validator. |
| Arena nodes should be freed one by one | “Which call allocated each node?” | None. The fixed array owns their storage; do not call `free`. |
| Duplicate keys can go on either side | “What is this course’s duplicate policy?” | The course BST rejects duplicate keys. |
| Trees and graphs are unrelated | “What happens if one child is shared?” | Relaxing tree restrictions produces graph-like relationships. |

## Accessibility and pacing

- Pair every diagram with a numbered text description or table.
- Do not rely on color, line direction alone, or spatial layout alone.
- Permit drawing, typing, dictation, tactile cards, or oral explanation.
- Read pointer expressions aloud: `&nodes[3]` means “the address of node
  three.”
- Read the starting state before timing, then give five uninterrupted minutes
  for the Cognitive Pause.
- Allow an extended or asynchronous pause when an accommodation calls for it.
- Grade relationship reasoning, not drawing quality or typing speed.
- Keep formal traversal names and recursive code out of student requirements.

## Evidence collected

1. initial and corrected diagram/index/pointer translation;
2. complete invariant statement;
3. checked local API implementation and test results;
4. fixed-arena ownership explanation;
5. three structural-validator failure explanations;
6. valid, deep-invalid, and duplicate-key BST results;
7. Tree → Graph transfer statement.
