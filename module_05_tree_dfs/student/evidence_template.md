# Module 5 Evidence Record

Complete this record after the Stage D notes and Stage E lab. You may replace
any table with a numbered list using the same headings.

Name: ____________________________  
Compiler used—the program that translates C into a runnable program:
____________________________

## 1. Core language

Depth-first exploration:

____________________________________________________________________

Traversal:

____________________________________________________________________

Recursive call and base case:

____________________________________________________________________

Call frame:

____________________________________________________________________

Preorder, inorder, and postorder:

____________________________________________________________________

## 2. Canonical orders

Use the tree whose root is 50; whose left subtree contains 30, 20, and 40;
and whose right child is 70.

| Order | Complete key sequence |
|---|---|
| Preorder | |
| Inorder | |
| Postorder | |
| Flagged nodes during preorder | |

## 3. Saved-work traces

When recursive preorder reaches key 20, list the active non-`NULL` calls and
state what unfinished work is remembered:

____________________________________________________________________

For iterative preorder, record the explicit Stack from bottom to top:

| Moment | Stack bottom to top |
|---|---|
| After visiting 50 and saving its children | |
| After visiting 30 and saving its children | |

Why is the right child pushed before the left child?

____________________________________________________________________

## 4. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Empty tree | | | |
| Single node | | | |
| Canonical recursive preorder | | | |
| Canonical iterative preorder | | | |
| Inorder | | | |
| Postorder | | | |
| Explicit Stack limit | | | |
| Successful BST search | | | |
| Missing BST key | | | |
| Duplicate insertion | | | |
| Postorder destruction | | | |

### Student-authored tests

For each test, state the new claim it checks.

1. Traversal or flag test and rationale:

   ____________________________________________________________________

2. Boundary or failure-preservation test and rationale:

   ____________________________________________________________________

3. BST search or cleanup test and rationale:

   ____________________________________________________________________

## 5. BST reasoning

Trace a search for key 40:

____________________________________________________________________

Why does a search for 35 report `TREE_DFS_NOT_FOUND`?

____________________________________________________________________

What does the supplied insertion baseline do when it sees an equal key?

____________________________________________________________________

## 6. Ownership and destruction

**Ownership** means responsibility for eventually releasing requested
storage. Explain why children must be destroyed before their parent:

____________________________________________________________________

What must `tree_destroy_postorder(&root)` leave in `root`?

____________________________________________________________________

## 7. Costs

Let `n` be the number of nodes. Let `h` be tree height: the greatest number
of downward links from the root to a leaf. **Auxiliary space** is temporary
working storage separate from the tree and traversal output. A **balanced**
tree keeps its left and right sides at roughly similar heights. A **skewed**
tree is strongly one-sided.

| Task | Time | Auxiliary space | Reason |
|---|---|---|---|
| Recursive preorder | | | |
| Iterative preorder | | | |
| Balanced BST search | | | |
| Skewed BST search | | | |
| Postorder destruction | | | |

## 8. Tree DFS Autopsy

- predicted faulty order:
- observed faulty order:
- first incorrect decision:
- corrected push order:
- regression test:

## 9. Forward connection

An **alias** is another name or route to the same object. A **symbolic link**
is a stored route to another location. Either can lead to an object already
reached by another path. Explain why that changes the tree task into a
graph-style task that needs a visited record:

____________________________________________________________________

## 10. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
