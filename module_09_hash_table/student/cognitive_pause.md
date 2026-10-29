# Stage B — Cognitive Pause

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


Keep the Stage A artifact. Answer exactly these three targets before opening
the investigation worksheet. Use a drawing or numbered prose. Label later
corrections without erasing the first prediction.

## Target 1 — Follow the selected chain

The table has ten starting indices. An empty starting index is `-1`.
Each linked node has `data` and `next`. Starting with an initialized free
pool, save 12, then 22, then -8 in their selected bucket.

Predict `hash_func` for all three values. Record the node indices, data,
next links, bucket head, and `free_head`. Trace both a successful search for
22 and a missing search for 32. Explain why the bucket alone cannot prove
that the requested value exists.

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________

## Target 2 — Return records before reusing the pool

After the three insertions, predict `init_hashtable()`. Which links become
part of the free chain? What happens to the bucket heads? Explain why
`init_lnodes_pool()` must run before first allocation and why calling it while
bucket chains are active would invalidate ownership.

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________

## Target 3 — Search earlier positions before saving the current one

Begin an independent experiment with empty buckets and a freshly initialized
pool. For target 0, trace the first successful iteration of `two_sum_ht`.
Distinguish the current position, current number, complement, bucket,
node index, stored earlier position, and earlier number. Explain why the
comparison reads `nums[j]` and why saving `i` occurs after the search.

Initial prediction: ________________________________________________

Correction and evidence: ____________________________________________
