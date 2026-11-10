# Consolidated Weeks 8–14 Questions

These questions match the current weekly pages. Optional clusters remain optional.

## Week 8 — Processing data in stored order

[Weekly vocabulary and scope](week_08_bfs.md)

### FIFO and the linear array queue

1. Requests 17, 23, and 31 arrive in order. How do a Stack and a queue differ in which request leaves first?
2. What do `front = 0` and `rear = -1` mean before the first insertion?
3. Why does `queue[++rear] = data` increase the write index first while `queue[front++]` reads before increasing the index?
4. How does `0 <= front <= rear + 1 <= N*N` describe valid queue positions, which positions are active, and why does `front > rear` mean empty?
5. After 25 insertions and 25 removals, what are `front` and `rear`, and why is another insertion invalid despite the empty queue?
6. What does `dequeue()` return in the current lab, and why does it need neither a node index nor a call to `free_lnode()`?

### Circular queue comparison

7. How does `(index + 1) % 25` move from index 24 to index 0?
8. When `front` identifies the first queued data’s index and `rear` the last queued data’s index in a nonempty queue, why are empty and full respectively `front == (rear + 1) % 25` and `front == (rear + 2) % 25`?
9. Why do these predicates reserve one position and allow only 24 waiting values in 25 slots?
10. Start at `front=0, rear=-1`, insert 0 through 23, remove two values, and insert 24 and 25. What are the new indices and removal order? Does the supplied maze lab use this circular implementation?

### Tree levels before graph search

11. In the workbook tree A(B(D,E),C(F)), what queue remains after processing A, then B, then C with left-before-right insertion?
12. What are the complete BFS order, corresponding depths, and maximum number of waiting nodes in this tree?
13. Why does a stack with right-before-left child insertion give A, B, D, E, C, F instead? In the graph-stack comparison, why may an unprocessed neighbor be pushed again, and why must an already processed node be skipped when popped?
14. How do setting the root's distance to zero and recording each child's distance as its parent's distance plus one before enqueue show which level is being processed?
15. Why does child-only traversal of a valid tree schedule each node once, while graph cycles and merging routes require a discovery record?

### Maze representation

16. How do passage cells and orthogonal moves define a graph without storing an adjacency list or matrix?
17. For `(struct point){2,3}`, what are `y`, `x`, and the array access used by `is_wall()`?
18. How can `enqueue` receive a whole `struct point`, `queue[N * N]` store it, and `dequeue` return it without converting the coordinate into an integer ID?
19. How does each inner brace pair initialize one row of `maze[N][N]`, and how do the two indices select a row and column? Review how `enum { N = 5 };` names the dimension.
20. How do the zero border and an in-bounds start keep neighbor accesses within the array, and which condition does `is_wall()` itself fail to check?

### Neighbor iteration

21. Starting from `{2,2}`, which four coordinates do `init_iter()`, `has_next_iter()`, and `next_iter()` produce, and in what order?
22. Why does every `next_iter()` call begin with a fresh copy of `cur_point`, and why does changing `p.x` leave `cur_point.x` unchanged?
23. What point would the first call return if only the first switch `break` were missing?
24. Why must one cell's four neighbors be finished before `init_iter()` starts another cell's iteration?

### Distance and initialization

25. Why is `INF = N * N` distinct from every possible shortest distance in this grid?
26. Which queue and distance state does `init_bfs()` reset before each independent search?
27. What happens when an in-bounds wall is supplied as the start, and why is an out-of-bounds start a different case?
28. Which state is changed by `set_distance()` and returned by `get_distance()`?
29. Why can the distance array replace a separate discovered array for both waiting and processed passages?

### Trace the supplied maze

30. Starting from `{1,1}`, what remains in the queue after `{1,1}`, `{2,1}`, and `{2,2}` are processed?
31. Why does the encounter from `{3,1}` to `{3,2}` leave both the stored distance and queue unchanged?
32. What are the complete removal order and final distance grid for the supplied maze?
33. What are the distance to `{3,3}`, the number of reached passages, and the final `front` and `rear`?
34. How do `||` and `continue` skip a wall or recorded neighbor without ending BFS? When does short-circuit OR omit `get_distance(p)`, and which operand rejects the encounter from `{3,2}` to `{3,3}`?

### Shortest-distance reasoning and paths

35. Why must a newly found distance be recorded before the coordinate enters the queue?
36. Why do pending distances never decrease from front to back, and how do FIFO processing and equal movement costs make first discovery shortest? What can no longer be guaranteed if a stack is used or movement costs differ?
37. If the first-discovering parent were stored as a conceptual extension, which five coordinates would reconstruct a four-move route to `{3,3}` in this neighbor order?
38. Which path records and printing operations would need to be added, given that the supplied lab records distances only?

### Work and storage

39. How many cells are initialized, how many coordinates are inserted and removed, and how many direction candidates are checked in the baseline run?
40. Why does a peak of three waiting coordinates still require eight total writes in the linear array queue?
41. For an `R` by `C` grid with `P` reached passages, why are initialization, traversal, and reserved search storage respectively `O(RC)`, `O(P)`, and `O(RC)`?
42. Why is a queue with room for all cells sufficient for one search, even though `enqueue()` does not check for overflow?

### Checks and evidence

43. Why can `lab.c` be compiled to an object with `-c` but need a separate `main()` driver for execution?
44. Which observations distinguish a successful fresh reverse-start run from one that accidentally retains the previous distances?
45. In a separate driver, temporarily block `maze[2][1]` and start at `{1,1}`. Which distance and queue states show that the target is unreachable, and what must be restored afterward?
46. Which traces, corrected predictions, and checks should appear together in the single queue, tree, and maze submission?

### Optional extension questions

47. How would initializing several passages at distance 0 change the meaning of each final distance?
48. How could repeated BFS searches cover every component when interior walls disconnect the passages?

## Week 9 — Chained Hashing and Two Sum

[Weekly vocabulary and scope](week_09_hash_table.md)

### Find two different positions

1. Trace `two_sum_bf(0)` in its exact `i` and `j` order. Give the returned
   positions, their values, and the number of pair comparisons.
2. Why does `j<i` prevent reusing one position? How many pair comparisons
   does a complete miss make for ten values?
3. Why can no pair in the supplied input reach 100? What does each method
   write to both elements of `answer` after that miss?
4. Does brute force change bucket heads, node records, or the allocation
   counter? Design assertions separating answer changes from table state.

### Select a bucket

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

### Follow collision chains

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

### Reuse fixed node storage

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

### Store keys and retrieve indices

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

### Compare results and work

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

### Build evidence

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

## Week 10 — Integer Heaps and Shared On-Time

[Weekly vocabulary and scope](week_10_priority_queue_heap.md)

### Meaning and representation

- How does priority selection differ from FIFO arrival order?
- What complete-tree shape does the active array prefix represent?
- Why can a valid min Heap have siblings in either numeric order?
- What does is_min_heap select, and why is it not an invariant checker?
- How do parent, left, and right distinguish a missing position with -1?
- Why does proper_parent return a position rather than a stored value?
- What does the first-argument tie behavior guarantee, and why is FIFO stability not guaranteed?

### Integer operations and tracing

- Where does add place a new value before heapify_up begins?
- Which parent relationships change while adding 1 after 7,3,5?
- What active prefix results from adding 7,3,5,1,9,4?
- Which replacement and child choices produce the first root removal?
- How does heapify_down avoid reading a missing right child?
- Why does singleton removal safely call heapify_down with size zero?
- Why must a caller prevent empty removal and insertion into ten live slots?
- Why must changing the min/max flag on existing values be followed by heapify?
- Why does bottom-up heapify begin at parent(size-1)?

### Interval input and Heap callbacks

- What do the paired cells in toggle_info[id] contain?
- How do interval_size and epoch differ?
- Why must every ID have one through five chronologically ordered valid intervals?
- What do max_on_heap.array and min_off_heap.array store?
- Why do full-Heap comparators receive IDs while basic comp receives positions?
- What function choices are stored in Heap_Full.comp and Heap_Full.swap?
- Why are the fixed full-Heap child helpers different from the size-based helpers?

### Maps and local repair

- What does array[position_map[id]] == id assert?
- Why does each Heap need its own inverse position map?
- Which two map entries must __swap__ update?
- How can stale maps break a later repair even when current Heap order looks valid?
- Why does one epoch change require repairs in both Heaps?
- When does _reheapify choose up, and when does it choose down?
- What assumptions make one-direction repair sufficient after a key change?

### Overlap and correctness

- Why do the latest current on-time and earliest current off-time decide overlap?
- Why does equality count as success for closed intervals?
- Which ID must advance when latest on is greater than earliest off?
- Why can advancing an earliest-off interval not skip a valid common time?
- Which bounds occur in the canonical trace before the answer 8?
- Why does exhaustion return before reading the next endpoint?
- Why must callers avoid current-time accessors after an exhaustion return?
- What does a fresh all_on_time call reset?

### Testing, costs, and transfer

- Which tests check duplicates, max mode, singleton removal, and a left-only child?
- How can a driver check both Heap order and inverse-map consistency?
- Which ten-ID fixtures distinguish immediate overlap, delayed overlap, endpoint equality, and exhaustion?
- Why is bottom-up build O(n) while repeated insertion can take O(n log n)?
- Why is the generalized search O(n + A log n) with O(n) auxiliary storage?
- How do fixed ten-ID storage and at most five intervals bound the literal program?
- How does Heap parent-child order differ from the BST search order taught later?
- What belongs in the single Week 10 driver, trace, test, and correction submission?
- Which allocation, stable-tie, and counter claims belong only to the optional alert library?

## Week 11 — Indexed-Heap Dijkstra and Practical 2

[Weekly vocabulary and scope](week_11_dijkstra.md)

### Meaning and mental model

- Why can BFS return A,E at cost 14 while a three-edge route costs6?
- What does a tentative distance mean before its node is removed?
- Why does choosing the smallest queued distance allow finalization under positive weights?
- What question does relaxation ask about one outgoing adjacency?
- What does `-1` mean before and after the run finishes?

### Representation and invariants

- Why do adjacency rows store only IDs while `edge_length` stores weights separately?
- Does assigning `edge_length[u][v]` create a connection without an adjacency entry?
- How do a node ID, heap position, and distance key differ after C is processed?
- What does `comp(i,j)` read before it compares two costs?
- Which inverse-map identity holds for every live heap position?
- Why must a swap update two map entries?
- Why can a removed node retain a nonnegative map value that no longer proves membership?
- Why is `[D,E,B]` a valid heap for keys `[4,14,5]` even though the keys are not sorted?

### Operations and source behavior

- Which arrays does `init_dist` reset, and which graph data does it retain?
- Why is the source explicitly inserted with distance0?
- Why does first discovery call `add_node`, while a later improvement calls `update_value`?
- How does `update_value` find the node and choose upward or downward repair?
- Why must downward repair keep the selected child position across its swap?
- Why is a singleton removal valid even though downward repair is called after `size` becomes0?
- Why is the heap helper called `heap_parent` rather than `parent` in this combined source?

### Canonical tracing

- After A, why are the distances B9,C2,E14 and the live heap `[C,B,E]`?
- After C, how do B9→5 and the insertion of D4 produce `[D,E,B]`?
- Why does D leave before B, and how does D improve E14→6?
- Why do B's candidate costs D6 and E13 cause no change?
- Which five nodes are removed, and why does F never enter the heap?
- How can the cost 6 route A,C,D,E be checked manually when the lab stores no predecessor array?

### Testing and debugging

- What focused regression distinguishes a node ID from its heap position?
- How can a driver check active heap order and inverse maps after every operation?
- What should tied-key tests assert when the source promises no stable removal order?
- Which fixtures exercise a left-only child, a singleton, and active-key changes in both directions?
- How can an independent linear shortest-distance reference check all final distances?
- Why should repeated runs and nonzero or isolated sources appear in the test evidence?

### Assumptions and interpretation

- Which ID, row-size, heap-capacity, and active-entry conditions must the caller establish?
- Why must every candidate addition fit in `int`, even when that candidate will be rejected as too large?
- Where is `found` written, and why does correctness rely on the positive-weight argument rather than a `found` guard?
- Why should negative weights or signed overflow not be executed as tests expecting rejection from this source?
- What does F's unreachable result say about the loaded model, and what does it not establish about real availability?

### Complexity and comparison

- Why is each reachable node inserted and removed at most once in the indexed strategy?
- Why do the canonical counts give five adds, five removals, two updates, and eight adjacency inspections?
- Why can generalized indexed-heap Dijkstra use `O(V + (V+E) log V)` work and `O(V)` heap-related state?
- How does the separate weight matrix contribute `O(V²)` storage?
- How do BFS, a linear minimum scan, and a heap differ in objective, selection work, and representation?
- Why should fixed ten-node storage be distinguished from a generalized asymptotic analysis?

### Assignment and transfer

- Which supplied functions must students trace rather than reimplement for Practical 2?
- Which driver, output, trace, same-graph comparison, and corrected explanation belong in the single submission?
- Why do the five teaching checkpoints not create five assignments or extra contact time?
- Which Week 10 heap and inverse-map ideas transfer to the changing distance keys?
- Which Priority Queue properties describe the ADT, and which depend on the indexed-heap implementation?
- How does Dijkstra's source-to-node objective differ from a minimum-spanning-tree objective in Week 14?

### Optional extension questions

- How would a lazy-duplicate frontier replace the inverse map and change pending storage?
- Which stale-snapshot check would the optional strategy need before inspecting outgoing arcs?
- What additional state and API would be needed to return predecessor paths from this lab?
- What validation and arithmetic checks would be needed before accepting untrusted graph input?

## Week 12 — BST-to-AVL with the Supplied Indexed Lab

[Weekly vocabulary and scope](week_12_avl.md)

### Meaning and mental model

- Why can the same seven labels produce a chain or a short plain BST?
- Which whole-subtree ordering rule permits directed lookup with duplicate keys?
- What does edge height count, and why are missing height -1 and leaf height 0 consistent?
- What does left height minus right height reveal about a node's shape?
- How does an AVL rotation repair shape while preserving nondecreasing inorder?

### Representation and invariants

- Which declarations come from Module 2, and how do a node ID, character key, and separate stored height differ?
- What does -1 mean for a child or root, and why does `get_height(-1)` avoid invalid array access?
- Why can rotations place equal data on either side even though new equal keys descend left?
- What exact height formula and balance-factor bounds must hold for every reachable record?
- Why must each inserted ID remain reachable exactly once, and why does `_add` not maintain `nodes_size`?
- How does Heap parent-child priority differ from the lab's whole-subtree search order?

### Operations and source behavior

- Which fresh-ID, child-link, capacity, and initial-AVL conditions must the caller establish?
- Why must the caller save `root = _add(root,id)` rather than ignore the return?
- What link changes do LL and RR make while preserving a captured middle subtree?
- Why do LR and RL capture two inner grandchildren and directly rewire four links?
- Why are recursive child-root assignments and lower-node-before-root height updates both necessary?

### Canonical tracing

- Why do CBA and ABC select LL and RR respectively?
- Why do CAB and ACB select LR and RL respectively?
- With stable alphabet IDs, what root, child IDs, heights, and inorder finish all four canonical repairs?
- In `F D G B E A`, where does middle record E end up, and which records' heights change?
- How do three fresh IDs holding B illustrate the difference between equal data and a repeated live ID?
- Why do the three seven-label orders yield plain heights 6/6/2 but AVL root D and height 2?

### Testing and debugging

- Which exact link and height assertions should isolate the four repairs and a nonempty middle subtree?
- How can a driver derive actual heights and check order, balance, and the inserted-ID set independently?
- Which valid empty, singleton, duplicate-data, ten-ID, and repeated-build cases belong in tests?
- Why are an eleventh ID or repeated live ID not valid tests expecting source rejection?
- Which defects can sanitizers reveal, and why do sorted order and exact height still require assertions?

### Complexity

- Why do insertion and directed lookup take O(h), with O(h) recursive insertion stack space?
- How can a plain BST reach O(n), while AVL limits operation cost to O(log n)?
- Why is each rotation O(1) even when its transferred middle region has many records?
- Why should O(n) diagnostic scans and generalized bounds be separated from operation work and the fixed ten-ID cap?

### Security and interpretation

- How can attacker-controlled valid arrival order force excessive plain-BST work?
- Why is degraded cost different from memory corruption and complete resource exhaustion?
- Which index, capacity, and input-validation risks remain caller responsibilities after AVL balancing?
- Why does a lost array link lose reachability without leaking allocated heap storage?

### Assignment and evidence

- Which driver, output, four traces, measurements, and explanations belong in the single Week 12 submission?
- What evidence establishes the exact heights and G/H, A/@, G/H lookup counts in the three required orders?
- Which three original test groups replace implementation TODOs in this complete-source lab?
- Why are AVL deletion, optional reference tests, and unsafe pointer autopsy execution outside the requirement?

### Transfer

- When could an AVL index be preferable to a hash index for the capstone?
- How does inorder DFS connect the ordering evidence to Module 5?
- How do local AVL repairs differ from the global edge-selection choices of MST algorithms?
- Which driver-supplied baseline and validation operations would become public-API work in a reusable container?

### Optional extension questions

- What additional cases would AVL deletion need during recursive unwind?
- How would allocated nodes and parent pointers change the current ID-based contract and cleanup responsibilities?
- How might a red-black tree trade a weaker balance rule for different update behavior?
- How would the separate pointer API reject duplicates and preserve failed insertions under adversarial inputs?


## Week 13 — Searching, Sorting, and Consolidation

[Weekly vocabulary and scope](week_13_search_sort_consolidation.md)

### Search contracts and candidate intervals

- What index does linear search return for 17 in `[31,23,17,8,17,42]`, and why does it stop before the second 17?
- Why does first-match binary search return index 1 after the same values are sorted?
- Why is a sorted-array result not necessarily the original record's index?
- Why must the binary-search array be nondecreasing before the first comparison?
- Which positions remain possible in the half-open interval `[lo,hi)`?
- Why does a middle value below the key permit `lo = mid + 1`?
- Why does a middle value equal to the key move the upper boundary instead of returning immediately?
- Why must the final lower-bound position be checked for equality before reporting a match?
- How do missing keys below all values, between values, and above all values end in `-1`?
- Why do empty and singleton inputs need explicit expected results even though the search code is short?

### Sorting actions and invariants

- What ordered prefix remains after inserting 23 into the canonical array's first two positions?
- Why must insertion sort save the current value before shifting larger values?
- Why does shifting only strictly larger values preserve the order of equal keys?
- Which eight shifts occur across the canonical insertion-sort run?
- Why does a zero- or one-element merge-sort range require no further split?
- How do two already-ordered halves make the next smallest merged value available at one of their fronts?
- Why does choosing the left value on an equal-key merge preserve stability?
- Why must merge sort's scratch buffer have at least `n` writable integer slots and not overlap the input?
- Why must the sorted merged range be copied back before its caller merges a larger range?
- Why can identical integer output fail to reveal whether the two original 17 records exchanged places?

### Tests, costs, and evidence

- Which assertions distinguish sorted order from preservation of every original value and duplicate count?
- Which independent oracle can check a search result without repeating the binary-search implementation?
- Which empty, singleton, duplicate-heavy, sorted, reverse, and signed-extreme fixtures exercise different behavior?
- Why are invalid sizes or overlapping merge buffers outside this lab's unchecked caller contract?
- How can paper labels `17A` and `17B` establish the equal-key order that integer-only output hides?
- Why does the canonical binary search use three interval comparisons and one final equality test rather than automatically beating every short linear query?
- When do repeated queries justify paying a sorting cost once?
- Why can insertion sort need quadratic shifts in reverse order while an already-ordered input needs no shifts?
- Why does merge sort combine logarithmically many levels of linear merging work?
- Why are merge scratch `O(n)` and active recursive calls `O(log n)` separate additional-storage terms?

### Consolidation and transfer

- When is a sorted array with binary search suitable for many queries over rarely changed data?
- When do frequent exact-key updates favor a hash index, and which distribution assumptions affect its expected cost?
- When do ordered range queries justify an AVL index rather than a hash table?
- Why does a Heap support repeated minimum selection without keeping its whole array sorted?
- Why do linked-list insertion after a known predecessor and searching for that predecessor have different costs?
- How does Module 8 store and return whole coordinates in its linear array queue, and why does capacity follow total discoveries rather than peak pending work?
- Why does FIFO unweighted BFS answer a different path question from indexed-Heap Dijkstra?
- How can sorting prepare Kruskal's edge scan without deciding which edges form cycles?
- Which trace, original assertions, costs, and corrected explanation belong in the single Week 13 artifact?
- How does a structure-choice claim change when query frequency, mutation frequency, memory, or ordering requirements change?

## Week 14 — Union-Find, Kruskal, and Capstone Integration

[Weekly vocabulary and scope](week_14_dsu_mst_capstone.md)


### DSU representation and operations

- Why learn Union-Find immediately before Kruskal?
- How does parent[] encode a forest without node pointers?
- What distinguishes a representative root from another member?
- Why are component sizes positive only at roots?
- What does make-set supply before the first graph edge is processed?
- Why does find locate a valid root before compressing the path?
- Which old parent must be saved during the compression pass?
- Why must union locate both roots before mutating either path?
- How does union by size choose the winning root, including ties?
- What changes after a merge, and what stays unchanged after same-set union?
- Why does compression preserve group membership, root sizes, and component count?
- How are invalid IDs rejected while preserving state and outputs?

### Kruskal and correctness

- Why do equal roots mean that the candidate edge would create a cycle?
- Why is sorting necessary in addition to DSU connectivity checks?
- What does the cut property establish about accepting a lightest safe edge?
- How do accepted edges and DSU components describe the same forest?
- Why does the edge builder retain distinct parallel edges?
- Why are self-loops skipped even if their weights are negative?
- Why does the comparator use relational tests instead of subtracting weights?
- What belongs in the edge-examination and skip ledger?
- Why does a disconnected result have V−c edges?
- Why can equal-weight MSTs use different edges with the same total?
- Why are negative weights accepted here but rejected by Dijkstra?
- Why does the scaffold publish the result only after checked total calculation?

### Tests, complexity, and comparison

- Which test verifies path compression as well as the returned root?
- How do I test same-set unions without confusing them with invalid input?
- How can a disconnected fixture include an isolated vertex?
- How can parallel edges or self-loops expose a wrong cycle decision?
- What evidence covers invalid endpoints, empty input, and large totals?
- What does amortized O(alpha(V)) mean for DSU operations?
- Why is sorting the usual dominant term in Kruskal?
- Why is diagnostic forest validation excluded from ordinary algorithm costs?
- What distinguishes the supplied Prim boundary growth from Kruskal merging?
- Why does neither MST construction guarantee redundant routes?

### Assignment, synthesis, and integration

- Which three functions are the required DSU/Kruskal TODOs?
- Are make-set, sorting, graph loading, checked totals, and Prim supplied?
- Do I submit another list repair, Prim implementation, or full package lab?
- Which DSU trace, edge ledger, tests, and compiler output accompany the two C files?
- How does the brief individual synthesis retrieve hash/AVL selection?
- How is the capstone integration checkpoint folded into the one weekly artifact?
- Which connected and disconnected runs show integration with existing graph IDs?
- How are lab correctness criteria separated from later capstone integration and defense?
- Why does DSU membership not imply trust, authorization, or an available path?
- Why can this DSU not directly handle arbitrary graph-edge deletions?
