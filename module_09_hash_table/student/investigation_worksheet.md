# Stage C — Investigate Chaining and Two Sum

Current pool contract: `new_lnode()` takes no arguments, returns an isolated index with retained data, and initializes the pool only on first use. `save_data` checks the index, writes data/next, then publishes the bucket head. Later `init_lnodes_pool()` calls are no-ops; `init_hashtable()` recycles owned bucket chains.


Name: ____________________  Date: ____________________

Preserve hand predictions in Sections A–F before opening the Stage D
explanation. Use the Stage B representation descriptions and Stage A input
array for these predictions. Treat the call sequences below as hand traces.
When Stage E opens, inspect [lab.c](lab.c) and its Module 07 dependency,
then execute the same experiments and record observations and corrections.
The supplied operations are complete; no implementation TODOs are required.

## A. Choose a bucket for a signed number

A negative number must still select a valid array position. Complete the
calculation used by `hash_func`.

| Value | `value % 10` in C | Returned bucket |
| ---: | ---: | ---: |
| -16 | | |
| -8 | | |
| -1 | | |
| 0 | | |
| 12 | | |
| 22 | | |

What range can the returned bucket occupy? Why does a negative remainder
need correction? Is `-1` forbidden as stored data, or only used as a link
sentinel?

Prediction: ________________________________________________________

## B. Save and search a collision chain

Begin with empty buckets and call `init_lnodes_pool()` before first use.
Save each value with `save_data(hash_func(value), value)` in order
12, 22, -8. Record every node and the bucket head after each call.

| Saved value | Returned node | Node data | Node next | Bucket head | `free_head` |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 12 | | | | | |
| 22 | | | | | |
| -8 | | | | | |

Trace `find_data(hash_func(22), 22)` and
`find_data(hash_func(32), 32)`. Record inspected node indices and the result.
Then save 22 once more. Which copy does `find_data` return? Does `save_data`
replace an earlier record or allocate another node?

Prediction: ________________________________________________________

## C. Recycle and exhaust the shared pool

Predict the free chain after `init_hashtable()` clears the experiment in B.
Bucket heads are visited in increasing bucket order. Nodes within a returned
chunk retain their chain order. Trace how the chunk tail joins the previous
free head.

In an independent experiment with empty buckets and a reset free pool,
save ten colliding values `0,10,20,30,40,50,60,70,80,90`.
Snapshot buckets, nodes, and `free_head`. Predict an eleventh save of 100.
Which state must remain unchanged? Clear the table and allocate again.

Explain why resetting `lnodes` while active buckets still reference it can
make one node belong to two chains. Explain why a linked queue cannot use
the same pool concurrently unless ownership is kept disjoint.

Prediction: ________________________________________________________

## D. Compare complete pair search with earlier-number search

Begin an independent experiment with empty buckets and a freshly initialized
pool. Use the unchanged `nums` array. For target 0, trace the complete-search
comparison order until the first match. For the hash-table method, complete
one row for each current position through the first match.

| `i` | `nums[i]` | `j_num` | Searched bucket | Visited nodes / stored `j` | Result or saved node |
| ---: | ---: | ---: | ---: | --- | --- |
| 0 | | | | | |
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |
| 5 | | | | | |

Why does a node store `i` rather than `nums[i]`? Why does the comparison use
`nums[j] == j_num` instead of `j == j_num`? Why does the successful current
position remain unsaved?

Prediction: ________________________________________________________

## E. Test boundaries and repeated calls

Predict answers for targets 2, 3, and 100. Each answer contains positions,
not numbers. Run 100 followed by 0 without manually resetting the pool in
between. Explain what `two_sum_ht` clears at its start.

Temporarily use `{1,1,5,0,0,0,0,0,0,0}` with target 6 in your driver.
Record the answer from each method. Explain the effect of ascending earlier
positions versus newest-first chain traversal. Restore `nums` afterward.

For each successful answer require `0 <= j < i < 10` and
`nums[i] + nums[j] == target`. Compare existence with brute force; require
identical positions only when the fixture fixes the same first match.
Use values whose sums and `target - nums[i]` fit in C `int`.

Prediction: ________________________________________________________

## F. Explain work and revise the model

Count the maximum pair comparisons made by `two_sum_bf` on ten numbers.
Count the allocations and bucket-node comparisons in a no-answer run of
`two_sum_ht`. What happens when many numbers select one bucket?

Describe these costs separately: choosing a bucket; prepending a node;
searching a chain of length `k`; clearing ten buckets with `n` live nodes;
and the complete two-sum search. State the assumptions behind an expected
short-chain claim. The source has ten buckets and ten pool records; it does
not grow automatically.

Choose three claims to test: (1) signed hashing and chains; (2) recycling,
exhaustion, and unchanged state on a failed save; (3) valid two-sum answers,
no self-pair, and repeated calls. Write assertions that could detect an
incorrect result. Preserve predictions now; add observations and corrections
after inspecting and running the actual source in Stage E.

Revised explanation: ________________________________________________

Question still open: ________________________________________________
