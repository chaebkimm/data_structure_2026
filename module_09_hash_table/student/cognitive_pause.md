# Stage B — Cognitive Pause

Keep Stage A. Answer exactly these three targets before the investigation.
Use a drawing or numbered prose. Label later corrections and retain the
initial prediction.

## Target 1 — Follow keys through a selected chain

There are 15 bucket heads and 10 nodes with `key`, `data`, and `next`.
Call `initialize()`, then `insert(12,120)`, `insert(27,270)`, and
`insert(-3,-30)`.

Predict buckets, insertion status, node indices, all node fields, bucket
heads, and `hnodes_unused`. Trace `find(27)` and missing `find(42)`.
Distinguish the returned node from its payload. Why does matching a bucket
alone fail to establish equality?

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________

## Target 2 — Reset heads and the allocation counter

After those insertions, predict `initialize()`: bucket heads, counter,
old node fields, and `answer`. Why does resetting both heads and counter
permit safe reuse without walking any chain? Why would clearing only heads
leave allocated capacity unavailable? State why initialization is required
before the first insertion or lookup.

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________

## Target 3 — Search before inserting the current position

Use the original `nums` and target 0. Trace the first successful
`two_sum_ht` iteration. Distinguish current position, value, complement,
bucket, returned node, node key, and payload holding the earlier position.
Explain `find(complement)`, `hnodes[node].data`, answer order `{j,i}`, and
why insertion follows a failed lookup.

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________
