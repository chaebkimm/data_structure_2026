# Week 09 — Chained Hashing and Two Sum: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

These questions follow the current self-contained
[Module 09 lab.c](../module_09_hash_table/student/lab.c). Use its ten-number
`nums` unless a question gives a separate fixture. The PPTs illustrate the
same key/data/next design with smaller capacities; use the current lab's
ten nodes, fifteen buckets, identifiers, and loop order for required traces.
Preserve predictions before running code. These prompts support one Week 9
submission rather than extra implementation assignments.

## Vocabulary students will learn

| Term | Working meaning |
| --- | --- |
| target | Requested sum of two input values |
| pair | Two different input positions chosen together |
| input index | Position in `nums`, distinct from its value |
| brute force | Testing earlier positions for each current position |
| direct addressing | Using a suitable value directly as a table index |
| key | Value used to hash and compare an entry |
| data / payload | Information associated with a key; an input index in two sum |
| hash function | Repeatable calculation selecting a bounded bucket index |
| normalized remainder | Remainder adjusted into 0–14 for this table |
| bucket | One selected group of candidate entries |
| bucket head | First node index in that group, or -1 |
| collision | Different keys selecting the same bucket |
| separate chaining | Keeping colliding entries in a linked chain |
| node | One `hnode` record with `key`, `data`, and `next` |
| node index | Position in `hnodes`, distinct from bucket and input indices |
| next link | Another node index or -1 at the end |
| sentinel | Special marker such as -1 for an empty head, chain end, or failure |
| allocation counter | `hnodes_unused`, also the next unused node index |
| capacity exhaustion | All ten node slots have been allocated |
| prepend | Make a new node the first node of a chain |
| lookup | Search the selected chain for an equal key |
| duplicate key | Another allocated entry with the same key |
| reset | Clear heads and restart allocation at node 0 using `initialize` |
| complement | `target-nums[i]`, the earlier value needed for a pair |
| earlier-index invariant | Every stored two-sum position is less than current `i` |
| load factor | Allocated entry count divided by bucket count |
| expected cost | Work under a stated distribution assumption |
| worst-case cost | Greatest work among allowed inputs of a given size |
| open addressing | Resolve collisions by searching other table positions |
| Robin Hood hashing | An open-addressing policy that favors entries displaced farther from home |

## Find two different positions

1. Trace `two_sum_bf(0)` in its exact `i` and `j` order. Give the returned
   positions, their values, and the number of pair comparisons.
2. Why does `j<i` prevent reusing one position? How many pair comparisons
   does a complete miss make for ten values?
3. Why can no pair in the supplied input reach 100? What does each method
   write to both elements of `answer` after that miss?
4. Does brute force change bucket heads, node records, or the allocation
   counter? Design assertions separating answer changes from table state.

## Select a bucket

5. Calculate `hash_func` for -16, -8, -1, 0, 2, -15, and 16. Show the C
   remainder modulo `TABLE_CAPACITY` and final bucket separately.
6. Why adjust a negative remainder before indexing `hashtable`? Why does
   a key divisible by 15 need no adjustment?
7. -16 and -1 select bucket 14. Does that make them equal? Identify the
   exact comparison that decides a match in `find`.
8. Compare direct addressing with hashing for negative or very large
   keys. Which stored numbers are indices and which are keys?
9. Does the caller pass a bucket to `insert` or `find`? Explain how both
   operations select the same bucket for equal keys.

## Follow collision chains

For questions 10–15, call `initialize()`, then execute `insert(12,120)`,
`insert(27,270)`, and `insert(-3,-30)` in that order. All keys select bucket 12.

10. Record each insertion's status, the allocated node index, all three
    fields, head 12, and `hnodes_unused` after each operation.
11. Why is chain order the reverse of insertion order? Does a collision
    move an entry into a neighboring bucket?
12. List visited nodes and return values for `find(12)`, `find(27)`, and
    missing `find(42)`. How do you retrieve associated data after a match?
13. Distinguish the `0/-1` return status of `insert` from the node-index/-1
    result of `find` and `new_hnode`. When must -1 be checked before indexing?
14. Insert `(27,271)`. Is the old key-27 node updated? Which node and data
    does the next `find(27)` return? How many slots are now allocated?
15. Does `find(120)` find key 12 because its data is 120? Explain the
    difference between searching a key and retrieving associated data.

## Reuse fixed node storage

16. Why must manual table experiments start with `initialize()` even
    though globals are statically initialized? What are the correct empty heads?
17. Initialize and insert keys `0,15,...,135`, with data `0,...,9`.
    Predict an eleventh insertion's return value and every field that must
    stay unchanged. Can nodes be exhausted with fourteen empty buckets?
18. After the three-node collision fixture, trace `initialize()`. Which
    heads and counter change, and which old node fields remain?
19. What does a second reset do? Does either reset clear `nums` or `answer`?
20. Does initialization follow old chains? Count the heads visited and
    explain why its work is independent of active-chain length.
21. Why should a saved node index no longer be treated as an active entry
    after reset? Which index does the next successful allocation overwrite?
22. Does this lab import Module 07 or use a free list? Explain how its
    allocation counter differs from a linked free-node chain.

## Store keys and retrieve indices

23. In `insert(nums[i],i)`, what becomes the key and what becomes data?
    Give the bucket, key, and data for input index 1.
24. At `i=5` for target 0, calculate complement, bucket, matching node,
    stored data `j`, and ordered `answer`. Which equality was tested by `find`?
25. Why is comparing a node's data directly with the complement wrong?
    Give a bounded example where the associated index differs from its key.
26. Why does `find(complement)` work here without a separate traversal
    comparing `nums[j]`? Identify the fields stored by insertion.
27. State the table's meaning at the beginning of iteration `i`. Use it
    to prove that every returned pair uses different input positions.
28. Predict the defect if insertion occurs before lookup. Explain the
    target-2 self-pair risk at index 5 without modifying the supplied code.
29. After a fresh target-0 success, list nonempty bucket heads, the chain
    in bucket 14, and the counter. Was current position 5 inserted?
30. After a target-100 miss, list all nonempty bucket chains. Which node
    indices happen to equal their stored input indices, and why?
31. Call target 0 after target 100 without a manual reset between calls.
    What resets the table, and why does allocation begin at node 0 again?
32. Why does the hash method break after insertion failure? Does the
    failure answer distinguish exhaustion from a fully searched miss?

## Compare results and work

33. For `{1,1,5,0,0,0,0,0,0,0}` and target 6, predict both ordered answers.
    Compare descending brute-force `j` with newest-first key lookup.
34. Give assertions for exact answer agreement, valid `0<=j<i<NUMS_SIZE`,
    correct sum, and a miss. Why do these implementations choose the same
    earlier duplicate when several answers are possible?
35. Why must every evaluated sum and complement subtraction fit in `int`?
    Does the source guard signed overflow?
36. Count work for `new_hnode`, `insert`, `find`, and `initialize`.
    Distinguish head assignments from key comparisons and node visits.
37. For `n` entries and `b` buckets, explain `n/b` average chain length.
    What distribution assumption supports expected `O(1+n/b)` lookup?
38. Which bucket-count and node-capacity conditions justify expected
    `O(n)` complete hash two sum, including initialization? Why does fixing
    fifteen buckets while increasing input size not preserve that claim?
39. If all keys collide, how many previous candidates could successive
    lookups inspect? Compare with brute force's worst-case growth.
40. Does this source allocate heap memory, grow, or delete individual
    entries? Contrast its chains with the PPT's open-addressing and Robin
    Hood alternatives without implementing those alternatives.

## Build evidence

41. A driver beside `lab.c` includes it and defines `main`. Why compile
    only the driver? Does this self-contained source require a Module 07
    include path or another `lab.c` translation unit?
42. Propose three original assertion groups: hashing/chains, capacity/reset,
    and two sum. For each, give a claim, small fixture, exact assertions,
    and reset strategy.
43. Which snapshot assertions detect changes after exhausted insertion?
    Which repeated-call tests expose failure to reset heads or the counter?
44. Correct one initial prediction using a returned value or exact state
    change, keeping the original prediction visible.

The legacy open-addressing library and delete-to-empty autopsy use a
different representation. Tombstones, growth, and unique-key updates are
optional comparisons rather than required answers for the current lab.
