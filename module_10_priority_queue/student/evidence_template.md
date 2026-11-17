# Chapter 10 — One Lab Evidence Record

Name / date: _______________________  Driver path: _______________________

Use one submission for inquiry, pause, investigation and testing. Standard, linear, spoken, dictated and typed responses use the same rubric. Keep the supplied lab and presentation sources unchanged.

## 1. Preserve prediction and correction

Initial model: ___________________________________________________

Observed operation or state: _____________________________________

Revised explanation: _____________________________________________

## 2. Distinguish the representation

Explain user ID versus queue position versus time. Record the initial sorted IDs, logout keys, front, rear, out_id and candidate. State the live count formula and equal-priority rule.

Evidence: ________________________________________________________

## 3. Record the canonical trace

Attach the six-row investigation trace with current user epochs/endpoints, candidate, removed ID, live IDs and indices after each round. Confirm time 12 with the three containing intervals, nine insertions, seven removals and six advances. State that counts came from your trace rather than source counters.

Evidence: ________________________________________________________

## 4. Explain why the algorithm works

Explain the greatest-login candidate, strict overlap test, blocked-interval advancement, removed-before-update rule, and exhausted result -1. Explain why updating a login to 11 does not reduce candidate 12.

Evidence: ________________________________________________________

## 5. Run the actual source

Compiler / commands: _____________________________________________

Core / student / comparison output: ______________________________

Original fixture and prediction: _________________________________

Original assertions and detected defect: _________________________

Confirm source inclusion exactly once and restoration of sample logs: ______

## 6. Record boundaries and repeatability

Record initial overlap, endpoint-only contact, no overlap, equal priorities and repeated calls. State exhaustion's epoch mutation and retained endpoints. Do not execute invalid queue operations as if they returned errors.

Evidence: ________________________________________________________

## 7. Compare work and storage

Compare actual survey, linear earliest-logout scan and interval-combination oracle on identical input. State per-operation costs, O(U² + AU) versus O(U + AU), and cumulative storage U * E rather than peak live U. Identify the actual nine-write/ten-slot bound.

Evidence: ________________________________________________________

## 8. Locate the bounded defect analysis

Chosen defect, first wrong state, and regression that exposes it: __________

## Submission check

One original regression is required; a copied smoke test does not satisfy it. Include predictions, corrections, driver, output, trace, boundary checks, comparison and costs in this one artifact. No heap implementation or Dijkstra result is required.
