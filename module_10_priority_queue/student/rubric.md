# Module 11 — Practical 2 Rubric

Total: 100 points for one integrated Week 11 artifact. Assessment rewards
reasoning and reproducible evidence, not memorized wording, drawing skill,
arithmetic speed, or typing speed. Standard, linear, spoken, dictated,
tactile, and typed responses receive the same assessment. Existing
worksheet answers may be referenced in the evidence record.

The required source is [lab.c](lab.c): a fixed ten-node indexed minimum
heap and distance-only Dijkstra loop. The supplied functions are complete.
There are no required parser, path-reconstruction, allocation, or lazy-
snapshot implementation tasks.

## 1. Distinguish the objectives — 10 points

- 4: states that BFS minimizes edge count and Dijkstra minimizes total cost;
- 4: checks one-edge A,E at cost 14 against three-edge A,C,D,E at cost 6;
- 2: states the additive synthetic model without claims about external
  authorization, trust, or real-world availability.

## 2. Trace the canonical source — 20 points

- 8: records final distances `[0,5,2,4,6,-1]`, final `found`
  `[1,1,1,1,1,0]`, and an empty heap;
- 7: traces the live heaps and finalization order A,C,D,B,E, including both
  in-place improvements; and
- 5: reports five insertions including source, five removals, two updates,
  eight edge inspections, six successful edge changes, and peak size three,
  with a stated method for counts the lab does not return.

## 3. Explain and check the indexed heap — 20 points

- 8: distinguishes node IDs from heap positions and follows
  `node_dist[heap[i]]` comparisons;
- 8: checks parent/child order and the inverse map for every live slot,
  including both map changes during a swap; and
- 4: explains singleton removal, stale removed positions, and the absence
  of stable arrival-order or ID-order ties.

A correct invariant is `node_heap_pos[heap[i]] == i` for live positions.
Do not require `-1` for a removed ID: the supplied source leaves that entry
stale. Do not treat the entire heap array as globally sorted.

## 4. Explain relaxation and finalization — 10 points

- 4: separates first discovery, strict improvement, and equal/larger cases;
- 3: explains why B and E improve through existing heap entries; and
- 3: justifies finalization with positive weights and accurately states
  that `found` is written but not checked by the loop.

## 5. Test the actual supplied lab — 20 points

- 8: records reproducible compile/core/student commands and output from
  drivers that include the actual `student/lab.c`;
- 8: adds one original focused regression with predicted results,
  assertions, and a clearly identified defect it detects; and
- 4: uses the supplied broader suite and independent reference honestly,
  including repeated initialization or a different-source check.

A copied canonical printout alone is not an original regression. Invalid
operations are not rejection tests for a source with no rejection API.
A trace driver must be checked against an independent call to `min_dist`.

## 6. State contracts, comparisons, and costs — 15 points

- 5: states valid IDs and adjacency bounds, positive listed weights,
  nonempty removal and bounded insertion, and representable `int` sums;
- 5: compares BFS, the supplied linear Priority Queue reference, and the
  indexed heap on the same graph, separating ADT behavior from storage; and
- 5: gives generalized `O((V+E) log V)` time and `O(V)` auxiliary state,
  accounts separately for the `O(V^2)` input cost matrix, and distinguishes
  full invariant scans from one-path repairs and fixed ten-node bounds.

The source has no validator or overflow guard and stores no predecessors.
A manually verified route is useful evidence but is not a program-returned
path. No additional path feature is required for full credit.

## 7. Preserve and revise reasoning — 5 points

- 3: preserves the initial inquiry and three-target pause, with a labeled
  observation and correction; and
- 2: identifies the first divergence in one bounded position/ID autopsy and
  links the corrected explanation to a concrete check.

## Scope and feedback

The activities and short autopsy fit inside the same 180-minute Practical
2 sequence. There is no second Week 11 programming assignment. Optional
`code/starter` lazy-duplicate work and its unsigned parser, path API,
allocation, range-preservation, and stable-frontier tests earn no required
points and do not replace evidence about the actual lab.
