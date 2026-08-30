# Module 2 Evidence Record

Name: ____________________________
Compiler or approved test environment: _____________________________

## 1. Representation in your own words

Explain the node's three fields:

- `data`: _________________________________________________________
- `left`: _________________________________________________________
- `right`: ________________________________________________________

Distinguish `root`, `&root`, and `root.left`.

____________________________________________________________________

Show the canonical five-node tree for `(3 + 5) * 2` as a drawing or
side-labeled description. `root` stores `'*'` and links to `plus` and `two`;
`plus` stores `'+'` and links to `three` and `five`.

____________________________________________________________________

Why may a general binary-tree node have a right child and no left child? Why
would that shape not be a completed binary operator in this expression model?

____________________________________________________________________

## 2. Invariants and caller preconditions

State the one-root, one-incoming-link, and no-cycle rules.

____________________________________________________________________

What must the caller ensure about initialization and node lifetime?

____________________________________________________________________

What does an empty-side guard check? Which whole-tree conditions does it
not establish?

____________________________________________________________________

## 3. Direct node operations

Show the direct C statements for:

1. initializing one local node's data and both links;
2. attaching a fresh child to a chosen empty side; and
3. clearing and detaching a selected left child.

____________________________________________________________________

When the chosen side is occupied, what must a guarded attachment leave
unchanged?

____________________________________________________________________

After removing the left branch, why must the right child keep its side?

____________________________________________________________________

## 4. Test evidence

Use the supplied tests and your own cases. Do not run cyclic or shared
structures as ordinary recursive-function tests.

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Data and both links initialized before use | | | |
| Right-only child | | | |
| Occupied-side guard keeps the existing child | | | |
| Search finds the current node | | | |
| Search returns the first matching address | | | |
| Search handles data on either side without a sorting rule | | | |
| Missing or `NULL` search | | | |
| Zero is ordinary searchable data | | | |
| Clearing resets all selected nodes | | | |
| Clearing alone leaves the outside parent's link intact | | | |
| Caller detachment leaves the opposite side unchanged | | | |
| Cleared local variables remain usable within their lifetime | | | |

### Three student-authored tests

State the new claim each test checks. Explain why its local node variables
remain alive through all checks.

1. Search boundary, duplicate, or ordering case:

   __________________________________________________________________

2. Direct initialization, guarded linking, or detachment case:

   __________________________________________________________________

3. Recursive clearing and still-live node reuse case:

   __________________________________________________________________

## 5. Search and removal traces

Start with the canonical tree. Trace these searches without changing it.

| Target | Data checked in order | Returned address or `NULL` |
|---:|---|---|
| `2` | | |
| 404 | | |

Now remove the left branch:

```c
tree_clear(root.left);
root.left = NULL;
```

- node variables whose fields are reset:
- their final data and links:
- `root.left` after clearing but before detachment:
- `root.left` after detachment:
- `root.right` after both actions:
- why the cleared node objects still exist:

If the caller retained the address of a cleared node, could a search for
zero find that node while it remains alive? Explain.

____________________________________________________________________

## 6. Operation costs

Count the fields or nodes processed.

- initialize one node:
- attach a fresh node to a known empty side:
- search for an absent value in a tree of `n` nodes:
- clear a subtree of `k` nodes:
- detach an already cleared child:
- why deeper recursion needs more temporary call storage:

## 7. Tree Structure Autopsy

- first initializer that creates the shared-operand relationship:
- tree precondition it violates:
- prediction before running:
- observed `root.left`, `minus.left`, and shared-operand data changes:
- why the result does not mean a node's lifetime ended:
- why the correct clearing function is not a whole-tree validator:
- repair and a regression-test idea:

## 8. Tool evidence

Warning-enabled build command and core-test result:

```text
paste output here
```

Student-test command and result:

```text
paste output here
```

Sanitizer, debugger, or approved instructor-test evidence:

```text
paste output here
```

## 9. Correction note

My initial misconception:

____________________________________________________________________

The evidence that changed or confirmed my reasoning:

____________________________________________________________________
