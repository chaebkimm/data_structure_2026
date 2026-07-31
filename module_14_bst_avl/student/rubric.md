# Module 14 Assessment Rubric

Total: 100 points. Assessment rewards correct reasoning and reproducible
evidence, not memorized wording, drawing quality, handwriting, typing speed,
or spoken fluency. Standard, linear, typed, dictated, tactile, and verbal
formats are equivalent.

## 1. BST ordering and measurements - 15 points

- 5: states strict unique-key ordering and explains sorted inorder;
- 5: obtains exact ascending/descending height 14 and 15-comparison
  deepest/missing results; and
- 5: obtains fixed mixed root 8, height 3, and four-comparison results.

## 2. Height, balance, and four traces - 15 points

- 5: uses `height(NULL)=-1`, leaf height 0, and left-minus-right factor;
- 5: identifies LL, RR, LR, and RL repairs; and
- 5: produces root 20, children 10/30, heights `1,0,0`, and inorder
  `10,20,30` for every case.

## 3. TODO 1: rotations and ownership - 15 points

- 5: saves and reconnects the middle subtree in both mirror operations;
- 5: refreshes the lower node before the new local root; and
- 5: handles missing required children safely and preserves all nodes,
  ordering, and ownership.

## 4. TODO 2: rebalance - 10 points

- 4: refreshes height and detects imbalance;
- 4: uses child balance factors to distinguish LL/LR and RR/RL; and
- 2: returns the correct new local root after single or double repair.

## 5. TODO 3: AVL insertion - 15 points

- 5: allocates only at a `NULL` link and reconnects only after success;
- 5: rebalances while recursive calls return and commits public root/size
  only after full success; and
- 5: preserves state for duplicate, full, allocation, argument, and
  invalid-state failures.

## 6. Exactly three student-authored tests - 10 points

- 4: all four canonical cases plus a nonempty middle subtree;
- 3: exact hostile, reverse, and mixed BST/AVL measurements; and
- 3: duplicate, 64-node boundary, allocation failure, malformed state,
  and iterative-cleanup preservation.

Three renamed copies of one supplied test setup earn credit once.

## 7. Validators, cost, and Heap contrast - 10 points

- 4: checks ordering, exact size, pointer shape, stored heights, and AVL
  factors after mutation;
- 3: states rotation `O(1)`, plain BST `O(h)`/worst `O(n)`, AVL
  `O(log n)`, actual-height/destroy `O(n)`, and supplied validator up to
  `O(n^2)`; and
- 3: distinguishes Heap parent priority from BST whole-subtree search order
  and the AVL height bound.

## 8. Autopsy, security scope, and evidence - 10 points

- 4: identifies the lost middle-subtree link, repairs the order, and adds a
  test proving the fixed defect does not return;
- 3: distinguishes algorithmic-complexity denial of service from memory
  corruption and broad resource exhaustion; and
- 3: supplies reproducible warning/sanitizer or approved alternative
  output, allocation cleanup, and one remaining security limitation.

## Required safety floor

Work that intentionally loses an owned subtree, reads or writes invalid
storage, releases storage incorrectly, hides a failing test, or connects
to live operational data cannot receive implementation-safety credit until
repaired.

Full AVL deletion is extension work and receives no core penalty when
omitted. Noncompiling work may still earn reasoning credit from preserved
models, tests, and explanations. Revision remains available under course
policy.
