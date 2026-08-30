# Tree Structure Autopsy — One Operand Object in Two Branches

## Case

An autopsy identifies the first broken rule behind an unexpected result.

The standalone program `code/autopsy/faulty_cascade.c` uses six initialized
local node variables. They remain alive throughout the demonstration.

| Variable | Initial data | Left address | Right address |
|---|---:|---|---|
| `root` | `'*'` | `&plus` | `&minus` |
| `plus` | `'+'` | `&three` | `&shared_five` |
| `minus` | `'-'` | `&shared_five` | `&two` |
| `three` | `3` | `NULL` | `NULL` |
| `shared_five` | `5` | `NULL` | `NULL` |
| `two` | `2` | `NULL` | `NULL` |

The malformed expression resembles `(3 + 5) * (5 - 2)`, but both written
occurrences of `5` lead to the same `shared_five` object. They are not two
separate objects that happen to store equal data. The fixture intentionally
violates the unshared-tree precondition. It contains no cycle or
ended-lifetime address, so this specific demonstration can be observed
safely.

The program supplies a correct recursive `tree_clear`. It then runs:

```c
tree_clear(root.left);
root.left = NULL;
```

## Before running

Predict all four results and preserve your first answers.

1. `root.left`: ___________________________________________________
2. `root.right`: __________________________________________________
3. `minus.left`: __________________________________________________
4. `minus.left->data`: ____________________________________________

## Incident report

### 1. First invalid state

Inspect the source. Which initializer first gives one object two incoming
child links?

____________________________________________________________________

### 2. Broken precondition

State the rule violated by the two routes to `shared_five`. Explain why an
empty-side check would not detect this relationship defect.

____________________________________________________________________

### 3. Observable consequence

Run the program. Record the pointer and data results, then compare them with
your prediction.

____________________________________________________________________

Which nodes does clearing the `plus` branch reach? How can that change a
value later reached through the `minus` branch?

____________________________________________________________________

### 4. Object lifetime

Did the `shared_five` variable stop existing, or did its fields change?
Explain using the variable's declaring scope and the actions performed by
`tree_clear`.

____________________________________________________________________

Why can the program finish normally even though its tree precondition was
broken?

____________________________________________________________________

### 5. Operation versus caller responsibility

Is the defect in the clearing algorithm or in how the caller linked the
objects? Explain why these two functions do not automatically validate the
whole structure.

____________________________________________________________________

### 6. Repair

Describe a repair that restores one incoming link per non-root node. If both
branches need an operand with data `5`, explain how two distinct local node
objects differ from two links to one object.

____________________________________________________________________

Relationships that intentionally share objects need a different model. A
later module introduces that model; do not add a whole-structure validator
here.

### 7. Regression-test idea

A regression test checks that a repaired defect does not return. Describe a
valid version of `(3 + 5) * (5 - 2)` with two distinct nodes storing `5` that
proves clearing and detaching the `plus` branch leaves the `minus` branch's
data and side unchanged.

____________________________________________________________________

This may be the rationale for one of your three student tests. No fourth
coded test is required by the autopsy.

## After observation

Label corrections `address`, `invariant`, `clearing`, or `lifetime`.

The evidence that changed or confirmed my model was:

____________________________________________________________________
