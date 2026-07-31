# Module 15 Assessment Rubric

Total: 100 points

Equivalent typed, dictated, tactile, verbal, tabular, or drawn evidence is
accepted. Drawing quality, handwriting speed, and memorized wording are not
graded. Exact relationships, decisions, and reproducible evidence are.

## 1. Representation and objective - 10 points

- 4: represents the same logical graph correctly as edge and adjacency
  views;
- 4: distinguishes shortest source paths from minimum selected-edge total;
- 2: explains signed, undirected, self-loop, parallel-edge, and ID rules.

## 2. Prim reasoning and trace - 15 points

- 6: exact canonical key, parent, selected-edge, and frontier trace;
- 5: exact counters and strict equal-key behavior;
- 4: correct ascending restart, isolated vertex, and forest count.

## 3. Kruskal reasoning and trace - 15 points

- 5: exact relational sort order and complete canonical ledger;
- 6: correct representative-root decisions and DSU group changes;
- 4: correct negative, self-loop, parallel, and equal-weight handling.

## 4. MST/MSF correctness - 15 points

- 5: checks selected membership, uniqueness, cycle freedom, component
  partition, and `V-c`;
- 5: distinguishes structural validation from minimum exchange checking;
- 3: explains equal-total alternative edge sets;
- 2: distinguishes MST from MSF.

## 5. Three implementation clusters - 15 points

- 5: Prim restart, pop, stale/already-selected filtering, and selection;
- 5: Prim indexed incident scan, strict improvement, and
  push-before-commit;
- 5: Kruskal full sorted scan, root check, selection, and union.

## 6. Exactly three original tests - 10 points

- 4: Prim lazy trace and restart category;
- 3: Kruskal filtering and ties category;
- 3: boundaries, preservation, and cross-validation category.

Three renamed copies of one fixture earn credit once. Each category must add
at least one meaningful assertion beyond visible tests.

## 7. Numeric safety and autopsy - 8 points

- 3: relational comparator and signed extreme evidence;
- 3: order-independent mathematical total, fitting cancellation, and
  out-of-range preservation;
- 2: exact endpoint-versus-root autopsy repair and regression.

## 8. Selection, resilience, and synthesis - 12 points

- 4: selects an algorithm using representation, density, conversion work,
  and actual complexity;
- 4: identifies bridges, bounded backup benefit, and remaining failure;
- 4: states honest limits about stored weights, authorization, capacity,
  changing conditions, and system security.

## Required correctness floor

A submission cannot earn a passing score while any of these remains:

- an invalid endpoint is used as an array position;
- Prim silently drops frontier work or commits a key before a failed push;
- Kruskal accepts an edge whose representative roots match;
- a selected self-loop or cycle is reported as valid;
- a disconnected result is mislabeled as one spanning tree;
- a final mathematical total is silently overflowed or made order-dependent;
- failure changes protected caller output;
- supplied ownership is violated; or
- fabricated test output is presented as observed evidence.

After documented correction, the affected section may be reassessed.

## Revision policy

One feedback-driven revision is allowed. Preserve the original response,
label each correction, rerun the smallest relevant test, and attach the new
evidence. A revision may recover all section points when the correctness
floor is satisfied.
