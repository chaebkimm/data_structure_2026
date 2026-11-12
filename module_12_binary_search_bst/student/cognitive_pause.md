# Stage B — Five-Minute Cognitive Pause

Read the definitions before timing begins. Then use no notes, slides,
vocabulary file, classmates, or coding tools. Preserve your first response
when correction begins. Typed, spoken, drawn, and linear records are equal.

The lab stores at most ten node records. Links are integer IDs; `-1` means
no child. A missing subtree has height -1 and a leaf has height 0. Balance
is left height minus right height. AVL permits -1, 0, or 1 at every node.
Equal keys use different IDs; inorder order is nondecreasing.

## Target 1 — How much work does order cause?

Use the same seven keys in three orders:

```text
ascending:  A,B,C,D,E,F,G
descending: G,F,E,D,C,B,A
mixed:      D,B,F,A,C,E,G
```

For each plain BST, state its root, edge height, and the comparisons for a
deepest successful search. Choose H as the missing probe for ascending and
mixed, and @ (before A in the course alphabet fixture) for descending.
Count one comparison per visited record. Explain how arrival order can
lengthen a route without changing the stored set.

Response: __________________________________________________________

____________________________________________________________________

## Target 2 — What changes in a rotation?

Trace LL `C,B,A`, RR `A,B,C`, LR `C,A,B`, and RL `A,C,B`.

For each, give the final root key, children, heights, and inorder sequence.
State which helper runs and the order in which `_add` updates heights.
For LL, name the captured middle-subtree index that becomes the old root's
left child. Explain why a local root must be returned to the parent.

Response: __________________________________________________________

____________________________________________________________________

## Target 3 — Which claims need which evidence?

An AVL build receives A through G in ascending order.

State its final root key and height. List independent checks for all
inserted IDs, no repeated ID, sorted inorder, exact saved heights, and
allowed balance factors. Explain why checking saved heights using the
same saved values would be weak evidence.

Explain the Heap/BST/AVL distinction. State why short routes neither
validate a node ID nor prove whole-system security.

Response: __________________________________________________________

____________________________________________________________________

## Correct after time is called

Preserve the first response. Label corrections `ID versus key`, `edge
height`, `comparison count`, `middle subtree`, `height order`, `root
return`, `duplicate order`, or `security scope`.

The evidence that changed or strengthened my reasoning was:

____________________________________________________________________
