# Lab — Build and Check a Small Tree

## Purpose

Build a small hierarchy in C without asking for new memory while the program
runs. Asking for memory while a program runs is called **dynamic allocation**.
A **process** is a program while it is running. This lab uses invented
numbers to stand for processes; it does not read a live computer.

A **hierarchy** arranges objects in levels. A **tree** is a hierarchy in which
each object, except the top object, has exactly one object directly above it.
A **binary tree** allows each object to have no more than two children.

## Files

You receive:

- `code/include/tree_arena.h`
- `code/starter/tree_arena.c`
- `code/tests/test_core.c`
- `code/tests/test_student.c`
- `code/build.ps1`
- `code/Makefile`

A **header** is a C file ending in `.h` that declares shared types and
functions. A **test** is code that runs a specific case and checks the result.
A **build script** or **Makefile** contains commands that translate the source
files into a runnable program.

Edit only:

- `code/starter/tree_arena.c`
- `code/tests/test_student.c`

Do not change the public header or supplied tests unless the instructor
authorizes it.

## Words used in this lab

- A **node** is one object in a tree.
- A **function** is a named block of code that performs one task.
- An **argument** is a value given to a function when asking it to run.
- The **root** is the top node.
- A **parent** is the node directly above another node.
- A **child** is a node directly below another node.
- A **leaf** is a node with no children.
- A **pointer** is a C variable that stores a memory address.
- `NULL` means that a pointer does not contain a usable object address.
- `bool` is a C type whose only values are `true` and `false`.
- An **enum** is a C type whose allowed choices have names.
- `const` states that a function promises not to change an object through
  that particular pointer.
- An **index** is an array position. C indexes begin at zero.
- `size_t` is a nonnegative whole-number type used for counts and indexes.
- An **arena** in this module is a fixed array that already contains every
  node. It does not grow.
- A **contract** states what a function accepts, changes, and returns.
- An **invariant** is a rule that must be true for every completed valid tree.
- An **output** is a result that a function writes into a caller-provided
  variable.
- A **caller** is the code that asks a function to run.
- **Nonnull** means “not `NULL`.”

## Public representation

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

`key` is the integer stored in a node. `left` and `right` hold child addresses
or `NULL`.

`TreeArena` points to a caller-provided node array. It does not own that array
and must not call `free`.

## Completed-tree rules

The course's empty tree has no node array, a count of zero, and a `NULL`
root. A completed valid nonempty binary tree satisfies all of these rules:

1. The root pointer names one node inside the fixed arena, and that root has
   no parent.
2. Every other node has exactly one parent.
3. Every node can be reached by following child pointers from the root.
4. No child path returns to a node already above it. Such a return is a
   **cycle**.
5. Every node has at most two children, represented by `left` and `right`.
6. Every nonnull child pointer names a node inside the fixed arena.
7. One node's `left` and `right` fields cannot name the same child.

During construction, some nodes may not yet be connected. Treat that state as
a candidate, not as a completed tree. Run the supplied whole-tree validator
after all links have been assigned.

## Core checkpoints

### 1. Read initialization and validation

The starter supplies:

- `tree_arena_init`, which copies keys into the fixed node array and clears
  all child links;
- `tree_validate_structure`, a **validator** (a function that checks rules)
  for the completed-tree rules;
- `tree_validate_bst`, which checks the additional binary search tree (BST)
  ordering rule defined in checkpoint 6.

Do not rewrite these supplied validators. Mark where each output value is
changed and what remains unchanged after an error.

You do not need to understand every supplied helper function yet. Use its
written contract, and edit only the marked `TODO` regions. `TODO` labels work
that remains to be completed.

### 2. Decide whether a node is a leaf

Complete `tree_node_is_leaf`.

A node is a leaf only when both child pointers are `NULL`.

- Reject a null node or null output pointer.
- Change the output only when the function succeeds.

### 3. Count immediate children

Complete `tree_node_child_count`.

- Add one when `left` is not `NULL`.
- Add one when `right` is not `NULL`.
- The result must be `0`, `1`, or `2`.
- Change the output only on success.

### 4. Assign one child link

Complete `tree_assign_child`.

The function performs **local validation**, meaning it checks only the
requested parent, child, and slot:

- both indexes must be inside the arena;
- a node cannot be its own child;
- the selected slot must be empty;
- `TREE_SIDE_LEFT` selects `left`; `TREE_SIDE_RIGHT` selects `right`.

A successful local assignment does not prove that the finished whole
structure is a tree. It could still give one child two parents or create a
longer cycle. The supplied whole-tree validator detects those problems.

### 5. Report immediate family

Complete `tree_immediate_family`.

The result contains the indexes of the node’s parent, left child, and right
child. `TREE_NO_INDEX` means that a relationship is absent.

The function must:

1. reject invalid arguments or an out-of-range node index;
2. require the completed structure to pass whole-tree validation;
3. scan the arena to find the one parent;
4. translate nonnull child pointers back to indexes;
5. change the output only after every check succeeds.

### 6. Trace the BST key limits

A **binary search tree**, shortened to **BST**, is a binary tree with an
additional ordering rule:

- every key in a node’s left subtree is lower than the node’s key;
- every key in its right subtree is higher;
- duplicate keys are rejected in this course.

A **subtree** is one node together with every node below it.

For each node below, write the lower and upper key limits carried by the
supplied validator. Do not classify the order in which nodes are visited.

```text
Valid:          Global-order violation:
     10                  10
    /  \                /  \
   5   15              5   15
      /                  \
     12                  12
```

The second example fails because `12` is inside the entire left subtree of
`10`, even though it is greater than its immediate parent `5`.

### 7. Design three tests

Inspect the supplied tests. Add three cases that are not direct copies:

- one boundary or invalid-input case;
- one local-versus-whole-structure case;
- one additional function-contract or BST rule you identify.

For each case, explain what new claim it checks. Clean up is unnecessary
because this module performs no dynamic allocation.

A **boundary case** uses a value at or near an allowed limit. **Invalid
input** breaks a function's contract. A test **rationale** is a short
explanation of why the test adds useful evidence.

## Build and test

From the `code` directory in PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target starter -StudentTests
```

The execution-policy option applies only to this child PowerShell process.

In Git Bash, MSYS2, WSL, Linux, or macOS:

```sh
make starter-core
make starter-student-tests
```

The Makefile uses commands understood by those environments and defaults to
the GCC C compiler. Use `make CC=clang starter-core` to select the Clang C
compiler instead.

If a compiler is unavailable, use the instructor’s approved CI or classroom
compiler. **CI**, or continuous integration, means another computer
automatically builds and tests the submitted code.

## Constraints

- Do not call `malloc`, `realloc`, or `free`, which are C library functions
  for requesting, resizing, or releasing memory while a program runs.
- Do not use a live process list or directory tree.
- Do not treat a locally accepted child link as proof of a valid whole tree.
- Do not change a caller’s output value after an error.
- Do not implement general **traversal**—a procedure that systematically
  visits nodes—yet; that appears in later modules.

## Required submission

1. completed `tree_arena.c`;
2. supplied-test transcript, meaning the saved text printed by the test run;
3. three passing student-authored tests with rationale;
4. compiler-warning or instructor-CI evidence;
5. completed evidence record;
6. Tree Structure Autopsy;
7. corrected Cognitive Pause.
