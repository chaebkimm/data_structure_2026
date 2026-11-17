# Chapter 10 — Lab Rubric

Total: **100 points** for one integrated lab artifact. Standard, linear, spoken, dictated, tactile and typed evidence are assessed equally. Grade reproducible reasoning, not typing speed or drawing skill. The supplied code is complete and remains unchanged.

## 1. Explain priority selection — 10 points

- 5: distinguishes FIFO from the comparison-based next item.
- 5: explains strict comparison, stable ties in this source, and the abstract queue's unspecified tie order.

## 2. Trace queue state — 20 points

- 8: records correct front/rear, live indices, IDs and associated logout keys.
- 8: explains insertion shifts, pos > front, and constant-time removal.
- 4: distinguishes cumulative writes from peak membership and prevents invalid operations.

## 3. Trace the canonical survey — 20 points

- 10: records all six advances and correct candidate/earliest-logout sequence.
- 6: returns 12, demonstrates all three containing intervals, and records final front=7/rear=8/live IDs [2,1]/selected ID 0.
- 4: reports nine insertions, seven removals and six successful advances with an honest trace-based counting method.

## 4. Justify advancement and endings — 15 points

- 5: candidate is greatest current login and never decreases.
- 5: logout equality fails; a blocking interval can be discarded without losing a solution.
- 5: only the removed user's priority changes; exhaustion returns -1 with epoch advanced and endpoints retained.

## 5. Test the actual lab — 20 points

- 6: records reproducible compilation and supplied-suite output.
- 10: supplies one original focused regression with a prediction, assertions and a plausible detected defect.
- 4: demonstrates repeated calls and restores sample input after custom fixtures.

The supplied smoke test is not an original regression. A copied loop trace must also be checked against actual survey(). Invalid full/empty calls have no defined rejection behavior.

## 6. State contracts, comparison and costs — 15 points

- 5: states nonnegative chronological half-open intervals, valid IDs, capacity and nonempty-removal preconditions.
- 5: compares the sorted queue and linear logout scan on the same inputs, with an independent combination oracle.
- 5: gives O(k) insertion/O(1) removal, O(U² + AU) survey versus O(U + AU) scan, and at most U * E cumulative slots; identifies the actual 3/3/10 bounds.

No additional programming assignment, heap backend, inverse map, graph path or dynamic allocation is assessed.
