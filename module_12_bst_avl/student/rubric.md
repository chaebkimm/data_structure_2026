# Module 12 Assessment Rubric

Total: 100 points. This is one Week 12 submission. Credit rewards correct
reasoning and reproducible evidence. Standard, linear, typed, dictated,
tactile, and verbal formats are equivalent. The supplied source is
complete; no implementation TODO cluster is required.

## 1. Representation and caller contract — 15 points

- 5: distinguishes node ID, `char` key, integer child link, and stored height;
- 5: uses ten slots, link sentinel -1, fresh IDs with both children -1,
  and keeps `root = _add(root,id)`; and
- 5: explains left-on-equality insertion and nondecreasing inorder after
  rotations, without claiming duplicate rejection.

## 2. Height, balance, and recursive return — 15 points

- 5: uses missing height -1, leaf height 0, and left-minus-right balance;
- 5: traces the returned child root into both the link and local `l`/`r`;
- 5: explains normal height refresh, imbalance selection, and returned root.

## 3. Four rotation traces — 20 points

- 8: traces LL CBA, RR ABC, LR CAB, and RL ACB using the actual helpers;
- 6: obtains B above A/C, heights 1/0/0, and inorder ABC in every case; and
- 6: preserves captured middle-subtree IDs and updates lower heights before
  the new root. Direct LR/RL helpers need not call two other helpers.

## 4. Plain BST versus AVL measurements — 15 points

- 5: measures plain ascending/descending height 6 and seven comparisons;
- 5: measures mixed DBFACEG root D, height 2, and three comparisons; and
- 5: measures root key D, height 2, and three-comparison probes for all
  three AVL builds, with the same keys and probe definitions.

## 5. Original assertion tests — 20 points

- 8: checks all four cases and a nonempty middle subtree with exact links;
- 6: checks ordering, every expected ID exactly once, independently measured
  heights, and every balance factor after insertion; and
- 6: checks empty/singleton states, all ten valid IDs, equal keys in distinct
  nodes, and one regression that would fail if a repaired bug returned.

Renamed copies of one supplied setup earn credit once. Tests must include
the actual `student/lab.c`, rather than a copied alternative algorithm.
Out-of-range IDs, reinserting a live ID, and an eleventh node are caller
violations, not required rejection tests.

## 6. Cost, Heap contrast, and security scope — 10 points

- 4: separates one-path search/insertion, constant local rotation, recursive
  active calls, fixed reserved arrays, and diagnostic full-tree scans;
- 3: contrasts Heap parent priority with BST whole-subtree order and AVL's
  additional height bound; and
- 3: distinguishes degraded complexity, invalid memory access, and broad
  resource exhaustion, and limits the security claim.

## 7. Evidence and defect investigation — 5 points

- 3: preserves predictions, labels corrections, and provides build/test
  commands with output; and
- 2: explains a bounded lost-link or stale-height defect and an assertion
  that detects it. The optional pointer autopsy is not an extra assignment.

Noncompiling work may earn reasoning credit from preserved traces and
tests. Revision remains available under course policy. Deletion, dynamic
allocation, status-code handling, and the optional pointer library receive
no core penalty when omitted.
