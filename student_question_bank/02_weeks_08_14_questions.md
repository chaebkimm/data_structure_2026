# Consolidated Weeks 8–14 Questions

These questions match the current weekly pages. Optional clusters remain optional.

## Week 8 — Queues, Tree BFS, and Graph BFS

[Weekly vocabulary and scope](week_08_bfs.md)

### Reuse the linked queue from Module 7

- How does Module 8 import the same linked-queue implementation taught as a list example in Module 7?
- Why does BFS pass a tree-node or maze-cell ID directly to public `enqueue(id)` rather than pass a pool-slot index?
- How does public `dequeue()` return the queued ID and recycle its slot without exposing the slot to BFS?
- Why must BFS avoid a separate `free_lnode` after public dequeue, and how does internal recycling make room before children or neighbors are enqueued?
- Which pool and endpoint state proves that a completed search returned all worklist nodes for reuse?
- Why can a search process 20 or 25 different passage IDs with only ten reusable queue slots?

### Linear array queue

- What do `front = 0` and `rear = -1` mean before the first array enqueue?
- Why does `enqueue_linear` increment `rear` before writing while `dequeue_linear` increments `front` after reading?
- Why is the linear empty condition `front == rear + 1`?
- Why can a linear queue remain full at `rear == 24` after some earlier items have been removed?
- Which full/empty checks must callers perform because the array queue operations are unchecked?
- Why must `front` and `rear` be reset before switching between the linear and circular variants that share `queue[25]`?

### Circular array queue

- How does `(index + 1) % 25` move from index 24 back to index 0?
- Why is this circular queue empty when `front == (rear + 1) % 25`?
- Why is this circular queue full when `front == (rear + 2) % 25`?
- Why do 25 reserved array positions hold only 24 queued values under these predicates?
- How does removing two values from a full circular queue permit two more enqueues across wraparound while preserving FIFO order?
- Which boundary traces distinguish array capacity, current queued count, and the 24-value circular limit?


### Tree BFS bridge

- Starting with Module 2's root F (index 5), which pending node indices remain after processing F, A, and G in turn?
- Why does left-before-right scheduling produce F, A, G, B, C, D, E rather than the DFS order?
- How does `tree_bfs(root, order)` use the queue's integer payloads to find each tree node's data and children?
- What count and output prefix should an empty-root test and the seven-node tree test verify?
- Why does the tree's unique-parent condition avoid repeated scheduling, while a graph needs discovery recorded before enqueue?
- Why must a fresh tree run initialize the otherwise-unused linked pool and reset `head` and `tail`, and why do three pending slots suffice for the F-root fixture?

### Meaning and mental model

- What does breadth-first search mean when moving through this maze?
- What is the frontier, and why does BFS keep it in a FIFO queue?
- Why do queued passages leave in nondecreasing distance from the start?
- How do the maze's passages and four-direction moves form a graph without a separate edge table?
- Why does a shortest route with eight moves contain nine points?

### Representation and invariants

- Why does point `{3,2}` access `maze[2][3]` rather than `maze[3][2]`?
- How does `7*y+x` map `{4,3}` to cell ID 25, and why is that ID different from distance sentinel 25?
- Why does `points[50]` contain only 49 initialized mappings when the maze has 20 passages?
- What do `prev[4]` and `prev_size` record, and which entries may be read?
- How does `distance` record discovery for waiting and processed passages without a separate discovered array?
- Why is 25 a valid unseen-distance marker for this maze, and what would need reconsideration for a larger maze?

### Operations, C API, and ownership

- Which functions are already complete in `lab.c`, and which caller setup, tests, and route reconstruction must students add?
- How do `set_distance` and `add_prev` change the shared `info` array instead of a local copy?
- Why must the caller call `init_info()`, prepare an otherwise-unused linked pool with empty endpoints, and select an interior passage before each independent search?
- How do `cur_point`, `state`, and the switch `break` statements generate right, left, down, then up?
- Why does the maze include its local `queue.c`, which imports Module 7's linked queue, and why must a build avoid duplicate definitions?

### Tracing

- What are the start's distance, predecessor count, and queued cell-ID payload when a fresh search begins at `{1,1}`?
- Which distances and remaining queue IDs follow processing `{1,1}` and then `{1,2}`?
- How do encounters from `{3,4}` and `{2,5}` create two predecessors for `{3,5}` while enqueueing it only once?
- What changes in each branch when the neighbor distance is at most the current distance, exactly one greater, or still 25?
- Why does ID 24 leave the queue before ID 10 even though the traversal distances never decrease?
- Why does goal `{5,5}` have distance 8 and two immediate predecessors but three complete shortest routes?

### Testing and debugging

- Which payload trace and final free-chain/endpoint state verify 20 baseline work items and complete recycling after the queue drains?
- How can a start-as-target test verify distance 0, no predecessor, and a one-point reconstructed route?
- How does a fully reset run from `{5,5}` check reachability and the reverse distance to `{1,1}`?
- How can a temporary isolated-passage test preserve the zero border and verify distance 25 with `prev_size==0`?
- How can a test check that every stored predecessor is an adjacent passage with distance exactly one less?

### Complexity

- Why does `init_info()` initialize 49 records here and require `O(R*C)` work for an R-by-C grid?
- Why do 20 dequeues lead to 80 direction checks here and `O(V_reached)` traversal work in general?
- Why does the linked worklist need capacity for four pending baseline items rather than all 20 discovered passages, while the comparison linear queue needs space for total writes?
- Why can enumerating all shortest routes require more work than computing distances and predecessor lists?

### Security and interpretation

- How does the valid-start and zero-border condition protect neighbor accesses even though `is_wall()` has no bounds check?
- Why does a larger maze require a new live-frontier bound even though public enqueue reports pool exhaustion and the current BFS asserts that its enqueue succeeded?
- Why do maze reachability and a small move count establish neither access authorization nor real-world risk?

### Assignment and evidence

- What caller code, tests, predictions, corrections, and traces belong in the single Week 8 queue, tree BFS, and graph BFS submission?
- Why are the optional checked matrix/list API and its sentinel 16 outside the required maze implementation?
- Which evidence establishes queue order, all shortest predecessors, an unreachable target, and three shortest goal routes?
- How do Module 7's linked-queue endpoint and recycling rules explain safe reuse between tree BFS and maze BFS?

### Transfer

- When can DFS establish reachability without guaranteeing that its first route uses the fewest moves?
- Why does following shortest predecessors always decrease distance and avoid a cycle during reconstruction?
- How does shortest-route reconstruction prepare you for later paths with unequal movement costs?
- Why can direct grid indexing and recorded distances replace a separate hash lookup for discovered state here?

### Extension questions

- How would multi-source BFS find each passage's distance from the nearest chosen start?
- How could repeated BFS searches cover all components after interior walls disconnect the maze?
- How do the optional checked API's single predecessor, sentinel 16, and failure-preservation rules differ from the maze records?
- How could optional matrix/list equivalence tests compare two backends under their own shared neighbor-order rule?

## Week 9 — Chained Hashing and Two Sum

[Weekly vocabulary and scope](week_09_hash_table.md)

### Find two different positions

1. For target 0, trace the order of `i` and `j` in `two_sum_bf`. Which pair
   is returned? Give both the indices and values.
2. Why does `j<i` prevent using the same input position twice? How many
   additions does a complete miss require for ten values?
3. For target 100, why is even the largest possible pair insufficient? What is written
   into both elements of `answer` on a miss?
4. Does `two_sum_bf` alter bucket heads or the node pool? Design an
   assertion that distinguishes its answer from its storage side effects.

### Select a bucket

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

### Follow collision chains

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

### Reuse the fixed pool

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

### Store indices and compare values

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

### Compare valid results and work

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

### Build evidence

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
- Which public linked-queue API did Module 8 use for BFS, and where does dequeue recycle its pool slot before expansion?
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
