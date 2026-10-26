# Stage C — Investigation, Linear Version

Name: ____________________  Date: ____________________

This version covers the same Sections A–F as `investigation_worksheet.md`.
Use numbered sentences instead of tables. Preserve hand predictions before
opening Stage D. Use Stage B's representation descriptions and Stage A's
input array; treat the call sequences below as hand traces. Inspect the
supplied `lab.c` and its Module 07 dependency when Stage E opens. Execute
the same experiments then and add observations and corrections.

## A. Choose a bucket for a signed number

1. For -16, -8, -1, 0, 12, and 22, state `value % 10` in C and the
   returned `hash_func` bucket separately.
2. State the range of returned bucket indices.
3. Explain the negative-remainder correction.
4. Distinguish stored data -1 from the link sentinel -1.

Prediction: ________________________________________________________

## B. Save and search a collision chain

1. Begin with empty buckets. Call `init_lnodes_pool()` before first allocation.
2. Save 12, 22, and -8 using `save_data(hash_func(value), value)`.
3. After each call, list returned node index, node data, next index,
   bucket head, and `free_head`.
4. Trace present 22 and missing 32 with `find_data`. List inspected nodes
   and final return values.
5. Save another 22. Predict which matching node is returned first.
   Explain why saving a duplicate does not update an existing node.

Prediction: ________________________________________________________

## C. Recycle and exhaust the shared pool

1. Predict every bucket head and the free-chain order after
   `init_hashtable()` clears B. Explain the chunk-tail link change.
2. In an independent experiment with empty buckets and a reset free pool,
   save `0,10,20,30,40,50,60,70,80,90`.
3. Snapshot all bucket heads, all node fields, and `free_head`.
4. Predict an eleventh save of 100. Identify the unchanged state.
5. Clear the table and prove that another allocation can reuse a record.
6. Explain why resetting the pool while bucket chains are live can create
   shared ownership. Explain the same concern for a concurrent linked queue.

Prediction: ________________________________________________________

## D. Compare complete pair search with earlier-number search

1. Begin with empty buckets and a freshly initialized pool. Use the
   unchanged `nums` and target 0. List brute-force comparisons
   through the first match in their actual order.
2. Trace `two_sum_ht` from position 0 through the first match. For each
   position, state `i`, `nums[i]`, `j_num`, searched bucket, visited node
   indices, stored earlier positions, and either the match or saved node.
3. Explain why node data contains an earlier position.
4. Explain why the equality reads `nums[j] == j_num`.
5. Explain why the successful current position has not been saved.

Prediction: ________________________________________________________

## E. Test boundaries and repeated calls

1. Predict both position answers for targets 2, 3, and 100.
2. Run target 100 and then target 0 without a manual pool reset between
   calls. Explain the clearing performed by `two_sum_ht` itself.
3. Temporarily use `{1,1,5,0,0,0,0,0,0,0}` and target 6. Record each
   method's positions. Explain their different earlier-position order.
   Restore the original array afterward.
4. Require `0 <= j < i < 10` and a correct target sum for every returned
   pair. Compare answer existence with brute force. Explain why duplicate
   values can allow different valid positions.
5. State the precondition that sums and complements fit in C `int`.

Prediction: ________________________________________________________

## F. Explain work and revise the model

1. Count the maximum brute-force comparisons on ten numbers.
2. Count allocations and node comparisons in a no-answer table search.
3. Explain how one long collision chain changes search work.
4. Give separate costs for hashing, prepending, searching `k` nodes,
   clearing ten buckets with `n` live nodes, and complete two-sum search.
5. State assumptions for expected short chains. The ten-bucket table and
   ten-record pool do not grow automatically.
6. Plan three original assertion groups: signed hashing/chains;
   recycling/exhaustion/failure preservation; and two-sum validity,
   no-self behavior, and repeated calls. Preserve predictions now; add
   observations and corrections when source inspection and execution open in Stage E.

Revised explanation: ________________________________________________

Question still open: ________________________________________________
