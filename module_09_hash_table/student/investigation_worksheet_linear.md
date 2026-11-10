# Stage C — Investigation, Linear Version

Name: ____________________  Date: ____________________

This version covers the same Sections A–F as `investigation_worksheet.md`.
Use numbered sentences instead of tables. Preserve predictions before Stage
D. Use Stage B's representation and Stage A's inputs; treat call sequences
as hand traces. Inspect and run `lab.c` in Stage E, then add observations
and corrections. There is no Module 07 source dependency.

## A. Choose a bucket for a signed key

1. For -16, -8, -1, 0, 12, 27, and -3, give the C remainder `% 15` and
   normalized bucket separately.
2. State the range of 15 bucket indices and the range of 10 node indices.
3. Explain the negative-remainder correction.
4. Distinguish a key of -1 from a next-link sentinel of -1.

Prediction: ________________________________________________________

## B. Insert and search a collision chain

1. Call `initialize()`, then `insert(12,120)`, `insert(27,270)`, and
   `insert(-3,-30)`.
2. After each call, list status, new node index, key, data, next, bucket
   head, and `hnodes_unused`. Distinguish success status 0 from a node index.
3. Trace `find(27)` and missing `find(42)`: list nodes, compared keys,
   return values, and found payloads.
4. Insert `(27,271)` and predict which duplicate is found first.
5. Explain why the old node is retained and why lookup compares keys rather
   than payloads.

Prediction: ________________________________________________________

## C. Reset and exhaust the node array

1. Snapshot B's state and call `initialize()`. State the new 15 heads and
   counter, and whether old node fields and `answer` change.
2. Explain why clearing only the heads would not restore node capacity.
3. In a separate initialized experiment, insert keys
   `0,15,30,45,60,75,90,105,120,135` with chosen payloads.
4. Snapshot heads, all node fields, and counter. Predict the status of
   `insert(150,1500)` and identify unchanged state.
5. Reset and show that a new insertion uses node 0. Explain why reset
   traverses no old chain.

Prediction: ________________________________________________________

## D. Compare complete pair search with complement lookup

1. Use unchanged `nums` and target 0. Trace ascending `i` and descending
   `j = i-1` through the first brute-force match.
2. Trace `two_sum_ht` through its first match. For each position give `i`,
   value, complement, search bucket, visited nodes and keys, and either the
   answer or inserted key/payload.
3. Explain the roles of the stored key and payload in two-sum.
4. Explain `find(complement)` followed by `hnodes[node].data`.
5. Explain the answer order `{j,i}` and why successful `i` stays unsaved.

Prediction: ________________________________________________________

## E. Test boundaries and repeated calls

1. Predict both answers for targets 2, 3, and 100.
2. Run hash target 100 followed by 0 without a manual reset. Explain the
   reset at entry and state after success.
3. Temporarily use `{1,1,5,0,0,0,0,0,0,0}` and target 6. Explain why both
   descending brute force and newest-first chains choose the same duplicate.
   Restore `nums`.
4. For successes require `0 <= answer[0] < answer[1] < NUMS_SIZE` and the
   target sum. Test a lone 5 with target 10, then two 5s, to distinguish
   self-pairing from valid equal values at different positions.
5. State the precondition that additions and complements fit in C `int`.

Prediction: ________________________________________________________

## F. Explain work and revise the model

1. Count maximum brute-force comparisons and those until target 0 succeeds.
2. Count the hash version's key comparisons through its first target-0 match.
3. Explain hashing, slot allocation, head insertion, searching `k` nodes,
   resetting 15 heads, and complete two-sum work separately.
4. State the assumptions behind expected short chains. Explain a worst-case
   long chain and fixed limits of 10 nodes and 15 buckets without growth.
5. Choose three assertion claims: hashing/keys/payloads/chains; reset,
   exhaustion and unchanged failure state; two-sum validity, no self-pair,
   duplicates and repeated calls. Add observations/corrections in Stage E.

Revised explanation: ________________________________________________

Question still open: ________________________________________________
