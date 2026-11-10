# Stage C — Investigate Chaining and Two Sum

Name: ____________________  Date: ____________________

Preserve predictions in A–F before opening Stage D. Use the Stage B
representation and Stage A input. Treat these call sequences as hand traces.
When Stage E opens, inspect [lab.c](lab.c), run the same experiments in a
separate driver, and label observations and corrections. Operations are
supplied; there are no implementation TODOs.

## A. Choose a bucket for a signed key

The current source has 10 node slots and 15 bucket heads.

| Key | `key % 15` in C | `hash_func` bucket |
| ---: | ---: | ---: |
| -16 | | |
| -8 | | |
| -1 | | |
| 0 | | |
| 12 | | |
| 27 | | |
| -3 | | |

What range can a bucket occupy? Why correct negative remainders? Explain
why the number -1 can be a legal key while a next link of -1 ends a chain.

Prediction: ________________________________________________________

## B. Insert and search a collision chain

Call `initialize()`, then `insert(12,120)`, `insert(27,270)`, and
`insert(-3,-30)`. Record each insertion's status separately from its node
index. Keep key and payload distinct.

| Call | Status | New node | Key | Data | Next | Bucket/head | `hnodes_unused` |
| --- | ---: | ---: | ---: | ---: | ---: | --- | ---: |
| `insert(12,120)` | | | | | | | |
| `insert(27,270)` | | | | | | | |
| `insert(-3,-30)` | | | | | | | |

Trace `find(27)` and missing `find(42)`. List visited node indices, key
comparisons, returned node, and payload if found. Then call `insert(27,271)`.
Which duplicate does `find(27)` return? Does the old record change?
Why would comparing `data` instead of `key` give the wrong lookup?

Prediction: ________________________________________________________

## C. Reset and exhaust the node array

Snapshot the state from B, then call `initialize()`. Predict all 15 heads,
`hnodes_unused`, old node fields, and `answer`. Which fields change, and
which remain? Explain why resetting only the heads would not restore capacity.

In a separate experiment, call `initialize()` and insert ten colliding keys
`0,15,30,45,60,75,90,105,120,135`, each with a chosen payload. Snapshot all
heads, node fields, and the counter. Predict `insert(150,1500)` and identify
the state that must remain unchanged. Reset and prove another insertion
reuses node 0. Does reset need to traverse any old chain?

Prediction: ________________________________________________________

## D. Compare complete pair search with complement lookup

Use unchanged `nums` and target 0. Trace `two_sum_bf`: `i` increases, and
`j` descends from `i-1` to 0. Record the comparisons through the first match.
Then trace `two_sum_ht`, which resets at entry:

| `i` | `nums[i]` | Complement | Search bucket | Visited nodes / keys | Result or insertion |
| ---: | ---: | ---: | ---: | --- | --- |
| 0 | | | | | |
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |
| 5 | | | | | |

What is stored as the key? What is stored as `data`? How does `find` use the
key, and how does the caller recover earlier position `j`? Why is the answer
ordered `{j,i}`? Why is successful position `i` not inserted?

Prediction: ________________________________________________________

## E. Test boundaries and repeated calls

Predict both methods' position answers for targets 2, 3, and 100. Run
`two_sum_ht(100)` followed by `two_sum_ht(0)` without a manual reset.
Explain what the function resets at entry and what remains after success.

In a driver, temporarily use `{1,1,5,0,0,0,0,0,0,0}` with target 6.
Record each method's answer and explain why descending `j` and newest-first
chains choose the same earlier duplicate. Restore `nums` afterward.

For every success require `0 <= answer[0] < answer[1] < NUMS_SIZE` and the
requested sum. Include one lone 5 with target 10 to expose self-pairing,
then two 5s to test equal values at different positions. All sums and
complement subtractions must fit in C `int`.

Prediction: ________________________________________________________

## F. Explain work and revise the model

Count the maximum pair comparisons for ten inputs and the comparisons until
target 0 succeeds. Count the hash version's key comparisons through its
first target-0 match. How can many colliding keys change total search work?

Explain hashing, slot allocation, head insertion, chain search of length
`k`, resetting 15 heads, and complete two-sum costs separately. State the
key-distribution and load assumptions needed for expected short chains.
The actual arrays have 10 nodes and 15 buckets and never grow.

Choose three test claims: (1) signed hashing, keys/payloads, and chains;
(2) reset, exhaustion, unchanged failed insertion, and reuse;
(3) valid two-sum answers, no self-pair, duplicates, and repeated calls.
Keep initial predictions and add observed corrections in Stage E.

Revised explanation: ________________________________________________

Question still open: ________________________________________________
