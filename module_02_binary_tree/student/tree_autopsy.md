# Tree Structure Autopsy — One Child, Two Parents

## What an autopsy means here

An **autopsy** is a careful investigation after something goes wrong. The
goal is to find the first broken rule, not merely the final incorrect output.

The supplied program builds links that are individually inside the arena and
stored in empty child slots. It then reports more node visits than the arena
actually contains.

## Before running

Predict:

1. Which node might be reached by two different parent links?
2. Which completed-tree rule would that break?
3. Why might a simple counting function count that node twice?

Preserve your prediction.

## Incident report

### 1. Relationship table

Record every parent-to-child link created by the program.

| Parent index | Side | Child index |
|---:|---|---:|
| | | |
| | | |
| | | |
| | | |

### 2. First invalid completed state

Identify the assignment after which the links can no longer describe a pure
tree.

____________________________________________________________________

### 3. Broken rule

State the exact completed-tree rule that is broken.

____________________________________________________________________

### 4. Local versus global checking

Why can each individual assignment pass an empty-slot and in-range check?

____________________________________________________________________

Why does detecting the defect require information from more than one parent?

____________________________________________________________________

### 5. Observable consequence

A **visit** means that a function reaches a node while following links.
Explain why four stored nodes can produce five visits.

____________________________________________________________________

### 6. Repair

Choose one repair:

- remove one parent link and keep a pure tree; or
- intentionally model shared relationships as a graph in a later module.

Explain your choice:

____________________________________________________________________

### 7. Regression tests

A **regression test** is a test kept to prevent a repaired defect from
returning.

Write two tests:

1. _________________________________________________________________
2. _________________________________________________________________

## After observation

Label each correction with one of:

`address` · `parent` · `reachability` · `invariant` · `tree-to-graph`

The evidence that changed my model was:

____________________________________________________________________
