# Safe Autopsy — A Lost Link or a Stale Height

## Investigate the supplied indexed representation

A defect investigation starts with a prediction and an exact changed
field. The required [lab.c](lab.c) stores nodes in a fixed array; it does
not dynamically allocate or free them. A lost link can make a record
unreachable while the record still exists in `nodes[]`.

Work on a bounded copied fixture or a paper trace. Keep the supplied lab
as the implementation tested by the normal drivers. The separate
`code/autopsy/faulty_left_rotation.c` is an optional pointer-library
example with a different memory contract.

## Predict a right-heavy repair

The starting local shape has root X, right child Y, and Y's nonempty left
subtree M. L and R are the other subtrees.

```text
        X
       / \
      L   Y
         / \
        M   R
```

The captured IDs are `i=X`, `r=Y`, and `rl=M`.
All keys in M lie between X and Y. The correct helper must place M at
`nodes[i].right`, then place X at `nodes[r].left`.

Before reading further, predict:

1. Which ID must be captured before a child field is overwritten?
2. Which two fields change?
3. What are the new local root and the old root's right child?
4. Which node's height must be recomputed first?

Prediction: ________________________________________________________

____________________________________________________________________

## Inspect a bounded faulty variant

Suppose a copied helper accidentally uses this assignment sequence:

```c
nodes[i].right = -1;   /* Wrong: drops the captured middle subtree. */
nodes[r].left = i;
return r;
```

After the first assignment, Y is still held by local `r`, and M remains
reachable through `nodes[r].left`. The second assignment overwrites that
last tree link to M. Returning Y cannot restore the missing link.

Record the earliest assignment that removes the last route to M:

____________________________________________________________________

Explain why this is a reachability defect in the fixed array, rather
than evidence of a dynamically allocated heap-memory leak:

____________________________________________________________________

Do not replace `nodes[i].right` with `r` instead. That would keep a
link back to Y while Y points to X, creating a cycle. A correct
reachability checker must detect repeated IDs before recurring again.

## Restore the actual helper

A saved middle-subtree ID has exactly one destination after this repair.
The supplied `rotate_rr` performs these assignments:

```c
nodes[i].right = rl;
nodes[r].left = i;
return r;
```

The correct after-state is:

```text
        Y
       / \
      X   R
     / \
    L   M
```

In `_add`, height repair follows the link changes:

```c
set_height(i, l, rl);
set_height(r, i, rr);
```

Both calls use the new children. X's new height must be available before
Y's new height is calculated. The caller must also save the returned
local root into its child field, or into the whole tree's root variable.

## Investigate stale saved heights

Use A=0, B=1, C=2 after `alphabet_init()`. Insert C, B, A.
Before the final insertion, C's saved height is 1. After the LL repair,
C becomes a leaf and its exact height is 0.

If the height calls were omitted, which saved value would remain wrong?

____________________________________________________________________

Which independent link-based height check would catch it?

____________________________________________________________________

Why can correct inorder order alone fail to expose this defect?

____________________________________________________________________

## Write a regression test

A regression test checks that a repaired defect does not return.
Use a valid fixture within ten distinct IDs and a nonempty M. You may
trace one supplied test setup, then construct a different original case.

Record:

- every initial key and child ID: ____________________________________
- middle-subtree root ID and members: _______________________________
- returned local root and exact final links: _________________________
- all expected IDs reachable exactly once: ___________________________
- independent actual heights and matching `height[]`: ______________
- each balance factor after complete insertion repair: _______________
- nondecreasing inorder before and after: ____________________________

A direct helper only changes links. It does not promise fresh heights or
a fully balanced arbitrary input shape by itself. To test the complete
insertion contract, use `_add` on an initially valid AVL tree.

## Limit the claim and preserve the evidence

Lost reachability, stale metadata, a cycle, and a long valid search route
are different defects. Name the field and observation supporting each
claim. A sanitizer may detect an invalid memory access; it cannot replace
assertions about expected records or sorted order.

Chosen defect: _____________________________________________________

Preserved prediction: _______________________________________________

Earliest decisive observation: ______________________________________

Corrected claim and detecting assertion: ____________________________

Attach this investigation to the single Week 12 evidence record. The
optional pointer autopsy and deletion extensions add no submission.
