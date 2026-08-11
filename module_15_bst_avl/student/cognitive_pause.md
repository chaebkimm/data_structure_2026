# Stage B - Five-Minute Cognitive Pause

Read the locked definitions and states before timing begins. Then use no
notes, slides, vocabulary file, classmates, or coding tools. Preserve the
first response when correction begins.

BST means Binary Search Tree. Every left-subtree key is smaller and every
right-subtree key is larger. Keys are unique. Edge height uses
`height(NULL)=-1` and `height(leaf)=0`. Balance factor is left height minus
right height. AVL balance permits only `-1`, `0`, or `1`.

## Target 1 - Measure hostile and mixed orders

Use:

```text
ascending: 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
mixed:     8,4,12,2,6,10,14,1,3,5,7,9,11,13,15
```

For the plain BST produced by each order, state:

1. the root;
2. the edge height;
3. the comparisons for a deepest successful search;
4. the comparisons for a missing search along a longest route; and
5. why attacker-controlled ascending order can cause
   algorithmic-complexity denial of service.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 2 - Repair all four imbalances

Use:

```text
LL: 30,20,10
RR: 10,20,30
LR: 30,10,20
RL: 10,30,20
```

For each case:

1. name the single rotation or ordered pair of rotations;
2. give the exact final root and children;
3. give all three stored heights;
4. show that inorder remains `10,20,30`; and
5. state where a middle subtree moves during one chosen rotation.

Response:

____________________________________________________________________

____________________________________________________________________

## Target 3 - Validate, contrast, and limit the claim

An AVL build receives ascending keys 1 through 15.

State:

1. the final root and edge height;
2. the allowed balance factors;
3. what ordering, stored-height, balance, and count validators must check;
4. how AVL search order differs from binary Heap order; and
5. why degraded complexity is neither memory corruption nor proof of
   broad resource exhaustion.

Response:

____________________________________________________________________

____________________________________________________________________

## Compare after time is called

Preserve the original response. Label corrections `edge height`,
`comparison count`, `rotation case`, `middle subtree`, `invariant`, or
`security scope`.

The evidence that changed or strengthened my thinking was:

____________________________________________________________________
