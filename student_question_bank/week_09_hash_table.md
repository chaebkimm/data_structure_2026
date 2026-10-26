# Week 09 — Chained Hashing and Two Sum: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

These questions follow [Module 09's lab.c](../module_09_hash_table/student/lab.c)
and its included [Module 07 node pool](../module_07_linked_list/student/lab.c).
Use the supplied ten-element `nums` unless a question specifies a separate
fixture. Preserve a prediction before running code. These prompts support
one Week 9 submission; they are not extra implementation assignments.

## Vocabulary students will learn

| Term | Working meaning |
| --- | --- |
| target | The requested sum of two input values. |
| pair | Two different input positions chosen together. |
| input index | A position in `nums`, distinct from its stored value. |
| brute force | Testing all earlier positions for each current position. |
| hash function | A repeatable calculation selecting a small bucket index from a value. |
| normalized remainder | A remainder adjusted into 0–9 even when the input is negative. |
| bucket | One selected group of candidate entries. |
| bucket head | The first node index in a bucket's chain, or -1. |
| collision | Different values selecting the same bucket. |
| separate chaining | Keeping colliding entries in a linked chain for their bucket. |
| node | One pool record containing `data` and `next`. |
| node index | A position in `lnodes`, distinct from an input index. |
| payload | The meaning assigned by the caller to a node's `data`. |
| next link | A node index leading to the next record, or -1 at the end. |
| sentinel | A special value such as -1 marking an empty head, an end, or failure. |
| node pool | The fixed ten-node array shared by the active and free chains. |
| free chain | Nodes available for future allocation. |
| free head | `free_head`, the first available node index or -1. |
| pool exhaustion | The state in which no free node remains. |
| prepend | Make a new node the first node of a chain. |
| lookup | Follow a selected chain to find an equal payload or value. |
| complement | `target-nums[i]`, the earlier value needed for a pair. |
| recycling | Returning a detached active chain to the free chain. |
| earlier-index invariant | At iteration entry, every stored two-sum index is smaller than the current `i`. |
| load factor | Stored entry count divided by bucket count, used to describe average chain length. |
| expected cost | Work averaged under a stated distribution assumption. |
| worst-case cost | The largest work among allowed inputs of a given size. |
| ownership | The rule assigning each pool node to one active chain, free chain, or temporary caller. |

## Find two different positions

1. For target 0, trace the order of `i` and `j` in `two_sum_bf`. Which pair
   is returned? Give both the indices and values.
2. Why does `j<i` prevent using the same input position twice? How many
   additions does a complete miss require for ten values?
3. For target 100, why is even the largest possible pair insufficient? What is written
   into both elements of `answer` on a miss?
4. Does `two_sum_bf` alter bucket heads or the node pool? Design an
   assertion that distinguishes its answer from its storage side effects.

## Select a bucket

5. Calculate `hash_func` for -16, -8, -1, 0, 2, 10, and 16. Show the C
   remainder and the returned index separately.
6. Why is the negative-remainder adjustment necessary before indexing
   `hashtable`? Why does a value divisible by 10 need no adjustment?
7. -8 and 2 select the same bucket. Does that make them equal? Which
   later comparison decides equality?
8. Why can a small bucket array represent values outside the range 0–9?
   Explain which numbers are array indices and which are stored values.
9. A caller passes `hash=10` to `save_data`. Does that function correct
   or reject the index? State the caller precondition without running an
   invalid access.

## Follow collision chains

For questions 10–15, begin with empty bucket heads and a fresh
`init_lnodes_pool()`. Save payloads 12, 22, and -8 into bucket 2 in that order.

10. Record each returned node index, each node's `data` and `next`, bucket
    2's head, and `free_head` after every save.
11. Why does the final data order differ from insertion order? Does any
    collision move an entry into bucket 1?
12. List the visited node indices for `find_data(2,12)`,
    `find_data(2,22)`, and `find_data(2,32)`. Give each return value.
13. What does `-1` mean as a bucket head, a `next`, an allocation result,
    and a lookup result? Why must it never be used as an array index?
14. Save another payload 22 into bucket 2. Is the existing node updated?
    Which node does the next `find_data(2,22)` return?
15. Does `find_data(1,12)` search every bucket? Explain why its caller must
    select the bucket that was used for storage.

## Reuse the fixed pool

16. What is the initial value of `free_head` before `init_lnodes_pool()` runs?
    Why is an all--1 bucket array insufficient for the first insertion?
17. After ten successful saves, try an eleventh valid save. State its
    return value and which bucket, node, and free-chain fields must remain
    unchanged. Can the pool be exhausted with nine buckets still empty?
18. Starting from the three-node collision fixture, trace
    `init_hashtable()`. Give the complete new free chain. Are node data
    fields cleared?
19. What does a second reset do? Does reset clear `nums` or `answer`?
20. Why is `free_lnode_chunk` slower for a longer chain even though it
    changes only two links? Why must its input chain be acyclic?
21. Explain how calling `init_lnodes_pool()` while bucket heads still point
    into the pool can give one node two owners. Predict on paper; do not
    execute corrupted-state experiments.
22. If the Module 07 linked queue reused in Module 08 shares this pool, which ownership condition must
    hold before hash-table reset or allocation is valid?

## Store indices and compare values

23. In `save_data(hash_func(nums[i]),i)`, what selects the bucket and what
    becomes the node payload? Give all three numbers for input index 1.
24. At `i=5` for target 0, calculate `j_num`, the bucket, the candidate node,
    the stored `j`, and `nums[j]`. What becomes `answer`?
25. Why is `lnodes[j_node].data == j_num` incorrect in two sum? Give a
    bounded example where an index and a value differ.
26. Why is `find_data(hash_func(j_num),j_num)` not a substitute for the
    supplied complement-search loop?
27. State the table's meaning at the beginning of outer iteration `i`.
    Use that statement to prove a returned pair has different positions.
28. Predict the defect if the current index is saved before searching.
    Explain the target-2 self-pair risk at `i=5` without changing the supplied code.
29. After a fresh successful target-0 call, which input indices remain
    stored? Has the current index 5 been saved? What is `free_head`?
30. After a fresh target-100 miss, list the nonempty buckets and their node
    chains. Which payload and physical-node numbers happen to coincide?
31. Run target 0 again after the target-100 run. Why can the returned input
    indices remain the same even when physical-node indices change?
32. Explain why `two_sum_ht` uses `break` after an allocation failure.
    Does `answer={-1,-1}` distinguish exhaustion from a genuine miss?

## Compare valid results and work

33. Use a separate bounded input fixture containing duplicate values. Must
    both algorithms return the identical earlier `j`? Compare ascending
    brute-force search with newest-first chain traversal.
34. What assertions establish pair validity without requiring the same
    `j`? How should a test decide whether both algorithms agree that no
    pair exists?
35. Explain why all tested sums and complement subtractions must fit in
    `int`. Does the supplied source check signed overflow?
36. Count the work for `save_data`, `find_data`, `free_lnode_chunk`, and
    `init_hashtable`. Separate node visits from link changes.
37. Let `n` be stored items and `b` bucket heads. Explain average chain
    length `n/b`. Which distribution condition gives expected
    `O(1+n/b)` lookup?
38. Which bucket-count and pool-capacity conditions justify expected
    `O(n)` hash two sum? Why does fixing `b=10` while increasing `n` not
    preserve that claim?
39. If every stored value selects one bucket, how many previous candidates
    might a complete sequence inspect? Compare with brute force.
40. Does the current source allocate heap memory or resize its arrays?
    Distinguish recycling pool nodes from calling C `free`.

## Build evidence

41. A driver beside `lab.c` includes it and defines `main`. Why must a
    repository-root compile use `-I.`? Why must the included `.c` files not
    also be compiled separately?
42. Propose exactly three original test groups: hashing/chains, pool
    lifecycle, and two sum. For each, state a claim, a smallest fixture,
    exact assertions, and a reset strategy.
43. Which failed-operation assertions would detect a bucket head changing
    after exhausted insertion? Which repeated-call test would detect lost
    pool nodes?
44. Explain one correction to your initial model using a specific returned
    value or before/after state. Keep the original prediction visible.

The retained open-addressing library and delete-to-empty autopsy use a
different representation. Tombstones, compaction, growth, and map updates
are optional comparisons, not required answers for this source-based lesson.
