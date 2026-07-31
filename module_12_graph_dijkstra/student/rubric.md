# Module 12 Assessment Rubric

Total: 100 points. Assessment rewards correct reasoning and reproducible
evidence, not memorized wording, drawing quality, arithmetic speed, typing
speed, or spoken fluency. Standard, linear, typed, dictated, tactile, and
verbal formats are equivalent.

A **caller** is code requesting work; **output** is where its answer is
written. A **TODO** is a marked unfinished task. A **backend** is the
storage method behind a collection. **Capacity** is its maximum entry count.
**Owned storage** is storage the function must release. A **simple graph**
has no repeated start/end edge and no edge returning to its starting vertex.
**Auxiliary state** is extra storage beyond the input. **Integrity** means
stored state obeys its required rules. **Decrease-key** means lowering a
priority already stored. An **implementation** is the code and storage
choice used to perform an operation. An **abstract data type (ADT)** states
behavior independent of storage. An **application programming interface
(API)** is the set of named operations code calls.

## 1. BFS contrast and weighted model - 12 points

- 4: distinguishes fewest edges from least additive cost;
- 4: states the canonical 14-versus-6 contradiction; and
- 4: defines the synthetic weight model without overstating it.

## 2. State and canonical trace - 18 points

- 6: distinguishes tentative and finalized distances and tracks frontier;
- 6: produces exact distance, predecessor, and finalization states; and
- 6: reports attempts 8, successes 7, pushes 8, pops 8, stale skips 3,
  peak 4, and Heap comparisons 17.

## 3. Strict relaxation and lazy snapshots - 12 points

- 4: updates only for a smaller candidate;
- 4: preserves D's predecessor on the equal zero-edge proposal; and
- 4: inserts improvements and skips all stale snapshots before edge scans.

## 4. Preconditions and numeric safety - 14 points

- 4: explains the nonnegative requirement and accepts zero;
- 4: rejects negative text before unsigned conversion;
- 4: guards addition and returns `DIJKSTRA_COST_RANGE` for overflow or a
  candidate equal to `INF`; and
- 2: preserves caller output on every status failure.

## 5. Reconstruction and unreachable result - 10 points

- 4: reconstructs `A,C,D,E` and independently verifies cost 6;
- 3: bounds predecessor traversal and checks its certificate; and
- 3: handles source-to-source and F without overstating `INF`.

## 6. Exactly three implementation TODOs - 12 points

- 4: weight-text parser satisfies syntax, negative, range, and output
  contracts;
- 4: Dijkstra loop satisfies initialization, finalization, strict
  relaxation, stale, Queue, and cleanup contracts; and
- 4: reconstruction handles valid, malformed, and unreachable results.

## 7. Exactly three student-authored tests - 8 points

- 3: parser and range-preservation category;
- 3: lazy stale trace and equal-predecessor category; and
- 2: paths, source, unreachable, and preservation category.

Three renamed copies of one **fixture**, or fixed test input, earn credit
once.

## 8. Spiral 4, complexity, and capacity - 6 points

- 2: completes the same-graph table with BFS path `A,E`, Dijkstra path
  `A,C,D,E`, calls 5/5 and 8/8, and comparison counts 14 and 17;
- 2: maps the three APIs and distinguishes stable-min ADT behavior from
  linear-scan and Heap implementations; and
- 2: states the actual linear/Heap growth and auxiliary-state bounds, avoids
  a decrease-key claim, and explains 241 insertions versus capacity 64.

## 9. Autopsy, integrity, and scope - 8 points

- 3: predicts wrap to 1 and repairs the range check;
- 2: separates arithmetic, stale, and **memory-safety** controls, meaning
  controls that keep storage access valid; and
- 3: bounds claims about authenticity, changing conditions, additive cost,
  fairness, and system security.

## Required safety floor

Work that silently accepts negative text, forms an unchecked overflowing
sum, reads an invalid vertex, drops a snapshot on `FULL`, leaks owned
storage, changes failure output, hides a failed test, or uses live
operational data cannot receive implementation-safety credit until repaired.

Noncompiling work may still earn reasoning credit from preserved models,
tests, and explanations. Revision remains available under course policy.
