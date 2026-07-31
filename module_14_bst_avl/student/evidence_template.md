# Module 14 Evidence Record

Name: ____________________________
Date: ____________________________
Revision label: __________________

Preserve initial work. Add labeled corrections rather than replacing the
evidence that shows how your reasoning changed.

## 1. Preserved inquiry and Cognitive Pause

- Stage A file preserved: yes / no
- Stage B three-target response preserved: yes / no
- correction labels used: ___________________________________________

Most important correction:

____________________________________________________________________

## 2. BST invariant and first trace

State the strict unique-key BST invariant:

____________________________________________________________________

For insertion order `20,10,30,5,15`:

- exact links: _____________________________________________________
- inorder traversal: _______________________________________________
- search 15 path/comparisons: ______________________________________
- search 17 path/comparisons: ______________________________________
- duplicate 10 preservation evidence: ______________________________

## 3. Plain-BST measurements

| Order | Root | Edge height | Deepest found comparisons | Longest missing comparisons |
|---|---:|---:|---:|---:|
| ascending 1 through 15 | | | | |
| descending 15 through 1 | | | | |
| fixed mixed | | | | |

Fixed mixed order:

```text
8,4,12,2,6,10,14,1,3,5,7,9,11,13,15
```

Explain why order, not the set of keys, changes these results:

____________________________________________________________________

## 4. Height and balance evidence

Course definitions:

```text
height(NULL) = ______
height(leaf) = ______
balance factor = __________________________________
allowed AVL factors = _____________________________
```

Attach or reproduce bottom-up heights and balance factors for the fixed
mixed structure.

How actual height differs from a stored height field:

____________________________________________________________________

## 5. Four canonical rotation traces

| Case | Input | First imbalance | Repair | Final root/children | Heights | Inorder |
|---|---|---|---|---|---|---|
| LL | `30,20,10` | | | | | |
| RR | `10,20,30` | | | | | |
| LR | `30,10,20` | | | | | |
| RL | `10,30,20` | | | | | |

All four exact final states:

```text
root = ______
left child = ______
right child = ______
root height = ______
leaf heights = ______
```

## 6. Middle-subtree ownership

For a left rotation at X with right child Y and Y's left subtree M:

1. saved pointer: ___________________________________________________
2. first relink: ____________________________________________________
3. second relink: ___________________________________________________
4. lower height refresh: ____________________________________________
5. upper height refresh: ____________________________________________

Why every key in M belongs between X and Y:

____________________________________________________________________

Evidence M remained reachable and owned:

____________________________________________________________________

## 7. Three implementation TODO clusters

### TODO 1 - rotations

- changed functions: ________________________________________________
- missing-child behavior: ___________________________________________
- middle-subtree evidence: __________________________________________
- height-update order: ______________________________________________

### TODO 2 - rebalance

- current factor: ___________________________________________________
- child-factor case selection: ______________________________________
- single/double repair evidence: ____________________________________

### TODO 3 - AVL insertion

- leaf-allocation point: ____________________________________________
- reconnect only after success: ____________________________________
- unwind and rebalance: _____________________________________________
- public root/size commit: __________________________________________

## 8. AVL measurements

| Order | Root | Edge height | Deepest found comparisons | Longest missing comparisons |
|---|---:|---:|---:|---:|
| ascending AVL | | | | |
| descending AVL | | | | |
| fixed mixed AVL | | | | |

Evidence every final AVL result has root 8 and height 3:

____________________________________________________________________

## 9. Validator evidence

BST validator checks:

____________________________________________________________________

AVL validator additionally checks:

____________________________________________________________________

| Deliberate defect | Expected validator result | Observed result |
|---|---|---|
| ordering violation | false | |
| wrong stored height | false for AVL | |
| factor outside allowed range | false for AVL | |
| shared pointer or cycle | false | |
| wrong size | false | |

Why validator work is diagnostic and may be `O(n^2)` in this supplied
implementation:

____________________________________________________________________

## 10. Exactly three original tests

### Test 1 - four rotations and middle-subtree ownership

Name and distinct check that must be true:

____________________________________________________________________

### Test 2 - hostile, reverse, and mixed measurements

Name and distinct check that must be true:

____________________________________________________________________

### Test 3 - preservation, boundary, and cleanup

Name and distinct check that must be true:

____________________________________________________________________

Test output location or attachment:

____________________________________________________________________

## 11. Failure preservation and boundary

| Case | Before-state evidence | Status (result label) | After-state evidence |
|---|---|---|---|
| duplicate key | | | |
| full at 64 | | | |
| forced allocation failure | | | |
| invalid argument | | | |
| invalid state | | | |

State why full AVL deletion is outside the core assignment:

____________________________________________________________________

## 12. Build, sanitizer, and cleanup

- compiler/version: _________________________________________________
- warning-enabled command/result: ___________________________________
- student-test command/result: ______________________________________
- sanitizer command/result or approved alternative: _________________
- normal build excludes faulty autopsy behavior: yes / no
- live-node baseline before tests: __________________________________
- live-node count after iterative destroy: ___________________________
- exact final tree state: root __________ size __________

## 13. Bounded rotation autopsy

The earliest lost-link operation:

____________________________________________________________________

Why the defect leaks the middle subtree:

____________________________________________________________________

Correct save-and-relink order:

____________________________________________________________________

Regression-test setup and result:

____________________________________________________________________

## 14. Cost evidence

- one rotation `O(1)`: ______________________________________________
- plain BST search/insertion `O(h)`: ________________________________
- skewed plain BST worst case `O(n)`: _______________________________
- AVL search/insertion `O(log n)`: _________________________________
- actual-height measurement/destroy `O(n)`: _________________________
- supplied complete validator up to `O(n^2)`: _______________________

Define each symbol and growth phrase in plain language:

____________________________________________________________________

## 15. Heap contrast

Heap parent-before-children rule:

____________________________________________________________________

BST whole-subtree search order:

____________________________________________________________________

What AVL adds:

____________________________________________________________________

## 16. Threat and scope

Attacker control:

____________________________________________________________________

Forced work in the plain BST:

____________________________________________________________________

AVL mitigation:

____________________________________________________________________

Why degraded complexity is not memory corruption:

____________________________________________________________________

Why it is not by itself proof of broad resource exhaustion:

____________________________________________________________________

One security property AVL and its validator do not prove:

____________________________________________________________________

## 17. Final synthesis

> How can local rotations preserve whole-subtree search order while
> preventing an attacker-controlled arrival order from creating a long
> search chain?

Final response:

____________________________________________________________________

One limitation that now matters to my design:

____________________________________________________________________
