# Safe Autopsy - Lost Middle Subtree in a Left Rotation

## Safety boundary

This is a bounded synthetic program. It demonstrates a memory leak: owned
allocated nodes become unreachable. It does not intentionally read or
write outside an allocation and does not intentionally use released
storage.

Use only:

```text
code/autopsy/faulty_left_rotation.c
```

The normal student build does not run faulty behavior automatically.
Follow `code/README.md`. A **sanitizer** is a runtime checker for defects
such as leaks and invalid memory access. If a sanitizer is unavailable,
use the supplied live-allocation counter or an instructor trace.

## Locked starting shape

The faulty operation rotates left at X. X's right child is Y. Y has a
nonempty left subtree M.

```text
        X
       / \
      L   Y
         / \
        M   R
```

Ownership means the `Tree` must keep every allocated node reachable from
its root until iterative destruction releases it.

### Linear equivalent

- local root: X
- X's left subtree: L
- X's right child: Y
- Y's left subtree: M
- Y's right subtree: R
- all five labeled parts are owned and reachable

## Predict before inspection

1. Which pointer is the only route from X or Y to M?
2. Which pointer value must be saved before any overwrite?
3. After a correct rotation, which field must point to M?
4. What evidence would show that M was lost?

Prediction:

____________________________________________________________________

## Inspect the faulty order

Do not merely say “the rotation is wrong.” The first replacement of
`root->right` is already incorrect, but local `upper->left` still reaches M
at that instant. Record the next assignment that removes this last route
and the earlier save that is missing.

Earliest lost-link assignment:

____________________________________________________________________

Missing saved value:

____________________________________________________________________

Why later assignments cannot recover M:

____________________________________________________________________

## Trace reachability

| Step | Local root | Reachable through X | Reachable through Y | Is M reachable? |
|---:|---|---|---|---|
| before | | | | |
| after first overwrite | | | | |
| after faulty return | | | | |
| after destroy | | | | |

If using the allocation counter:

- live count before test setup: _____________________________________
- live count after test setup: ______________________________________
- live count after faulty destroy: __________________________________
- leaked allocation difference: ____________________________________

## Repair the order

Number the correct left-rotation steps:

1. __________________________________________________________________
2. __________________________________________________________________
3. __________________________________________________________________
4. __________________________________________________________________
5. __________________________________________________________________
6. __________________________________________________________________

The required conceptual order is save Y, save M, attach M to X's right,
attach X to Y's left, refresh X, refresh Y, and return Y.

## Prove ordering and ownership

Explain why every key in M is greater than X and less than Y:

____________________________________________________________________

Exact correct after-state:

```text
        Y
       / \
      X   R
     / \
    L   M
```

### Linear equivalent

- new local root: Y
- Y's left child: X
- Y's right subtree: R
- X's left subtree: L
- X's right subtree: M
- all five labeled parts remain owned and reachable

Inorder before: _____________________________________________________

Inorder after: ______________________________________________________

## Regression test

A **regression test** checks that a repaired defect does not return.
Describe one nonempty M test setup. State exact keys, before links, after
links, stored heights, validator results, and live-count restoration.

____________________________________________________________________

## Distinguish the defect

This defect is a memory leak because:

____________________________________________________________________

It is not, in this bounded run, a use-after-free because:

____________________________________________________________________

It is separate from algorithmic-complexity denial of service because:

____________________________________________________________________

## After-action correction

Preserve the prediction. Label changes `lost link`, `middle ownership`,
`height order`, `validation`, or `scope`.

The earliest evidence that changed my reasoning was:

____________________________________________________________________
