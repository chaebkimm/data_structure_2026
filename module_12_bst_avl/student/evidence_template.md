# Module 12 Evidence Record

Name: ____________________________
Date: ____________________________
Revision label: __________________

Submit one Week 12 artifact. Preserve original predictions and add labeled
corrections. The complete [lab.c](lab.c) is the implementation being tested.

## 1. Preserve the inquiry

- Stage A prediction preserved: yes / no
- Cognitive Pause preserved: yes / no
- Investigation prediction preserved before worked results: yes / no
- Most important correction and evidence: ____________________________

## 2. State the actual representation

Explain these separately:

- node ID and valid range: ___________________________________________
- key field and type: ________________________________________________
- missing child and missing-subtree height: __________________________
- fresh-node child initialization: __________________________________
- reachable node count versus `nodes_size`: _________________________
- caller's root update: ______________________________________________

What `_add` returns, and what it does not allocate or validate:

____________________________________________________________________

## 3. Show recursive return and equality

Trace the changed child through both the assignment to `nodes[i].left`
or `nodes[i].right` and the local variable `l` or `r`.

____________________________________________________________________

Use distinct IDs carrying equal keys. Show the insertion direction and
nondecreasing inorder after repair. Explain why an equal key may end up on
the right, and why a live ID must never be inserted again.

____________________________________________________________________

## 4. Record the four exact repairs

| Case | Input | Helper arguments | Returned root | Links/heights | Inorder |
| --- | --- | --- | --- | --- | --- |
| LL | C,B,A | | | | |
| RR | A,B,C | | | | |
| LR | C,A,B | | | | |
| RL | A,C,B | | | | |

State which fields move and which node identities/keys remain unchanged:

____________________________________________________________________

List the bottom-up height-update order for all four cases:

____________________________________________________________________

## 5. Preserve a nonempty middle subtree

- initial links and exact middle-subtree ID: __________________________
- saved argument before overwriting a link: __________________________
- exact final links: _________________________________________________
- independent height result and stored heights: ______________________
- expected reachable-ID set and observed set: _________________________
- assertion that would fail if the subtree were lost: _________________

Explain why an array record can become unreachable without a heap-memory
leak:

____________________________________________________________________

## 6. Compare the same seven keys

Use ascending ABCDEFG, descending GFEDCBA, and mixed DBFACEG.
The present/missing probes are G/H, A/@, and G/H respectively. For this
fixture @ is before A. Count one comparison per visited node.

| Build | Root key | Edge height | Present path/count | Missing path/count |
| --- | --- | --- | --- | --- |
| plain ascending | | | | |
| plain descending | | | | |
| plain mixed | | | | |
| AVL ascending | | | | |
| AVL descending | | | | |
| AVL mixed | | | | |

What stays fixed across the experiment, and what accounts for the change:

____________________________________________________________________

Plain BST/search support file used: _________________________________

Distinguish that driver support from the functions exported by `lab.c`:

____________________________________________________________________

## 7. Supply independent invariant evidence

After each insertion, identify how the checker verifies:

- all expected IDs are reachable exactly once: _______________________
- indices stay in range and links do not cycle/share a node: __________
- inorder is nondecreasing: __________________________________________
- actual height measured from links matches every `height[i]`: ______
- every left-minus-right factor is -1, 0, or 1: ________________________

One deliberate defect tested only in a bounded copy, and its detection:

____________________________________________________________________

## 8. Record original test claims

1. Four repairs and a nonempty middle subtree: ________________________
2. Seven-key BST/AVL measurements: ___________________________________
3. Valid boundaries, equal keys, and one regression: __________________

Include an empty state, singleton, and a tree containing all ten fresh IDs.
Do not execute an eleventh insertion, out-of-range ID, or reinsertion of a
live ID as an expected rejection: the lab supplies no such checks.

Actual test source path: ____________________________________________

## 9. Reproduce the build

From the repository root, preserve commands and their complete results:

```sh
make -C module_12_bst_avl/code lab-compile core student-tests comparison
```

Compiler and version: _______________________________________________

Warning output and its source: ______________________________________

Assertion results: __________________________________________________

Sanitizer command/result, or instructor alternative: _________________

## 10. Separate costs and security claims

Explain local rotation, one-path search/insertion, diagnostic scans,
active recursive calls, and fixed reserved array storage before giving
growth bounds.

____________________________________________________________________

Explain Heap priority order versus BST subtree order versus AVL balance:

____________________________________________________________________

State how chosen order can degrade plain-BST work, and why that observation
alone proves neither invalid memory access nor broad resource exhaustion:

____________________________________________________________________

One guarantee AVL balance does not provide:

____________________________________________________________________

## 11. Finish the correction trail

Defect investigation used: lost link / stale height / stale child ID /
missing root update / other: _________________________________________

Earliest decisive observation: _______________________________________

Original expectation: _______________________________________________

Revised claim and test that supports it: _____________________________

No required allocation, failure-status, deletion, or pointer-library
extension is part of this submission.
