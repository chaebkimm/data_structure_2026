# Student Question Bank — Weeks 1–7

> This is the consolidated question-only view. The canonical weekly pages,
> including vocabulary and required-scope notes, are linked from the
> [all-week bank index](../Data_Structures_Course_2026_Student_Question_Bank.md).

## Week 1 — ArrayList and Linked-Node Preview

### Meaning and mental model

- What exactly is an ArrayList, and how is it different from an ordinary C array?
- If the elements remain in one block of memory, what part of the list actually “grows”?
- What is the difference between the list’s logical size and its physical capacity?
- Why should we describe the ArrayList behavior separately from the `IntList` representation?

### Representation and invariants

- Which `data`, `size`, and `capacity` combinations form the canonical empty state?
- Why must `size` never be greater than `capacity`?
- When may `data` legally be `NULL`, and what other fields must agree with it?
- What important facts about liveness, allocation extent, initialized elements, and unique ownership can `int_list_is_valid` not prove?

### Operations, C API, and ownership

- When is it legal to call `int_list_init`, and what happens if the object already owns storage?
- Why does `int_list_reserve` promise not to shrink the list or change its size?
- Why must `int_list_get` reject an output pointer that points inside the list’s own allocation?
- After a failed append or reserve, which pointer, size, capacity, and existing values must remain unchanged?

### Tracing

- Starting from `{NULL, 0, 0}`, how do the fields and memory contents change across several appends that trigger growth?
- What should a trace show when an append fits within the existing capacity?
- What should a trace show when `realloc` returns a different address from the original allocation?
- What happens to the original allocation and list state when a forced growth allocation fails?

### Tests and debugging

- Which empty-list, singleton, exact-capacity, and first-growth tests reveal different defects?
- How can a test prove that allocation failure preserves every part of the old list?
- What warning, sanitizer, or debugger evidence would help distinguish an out-of-bounds write from a stale-pointer use?
- In the Segfault Autopsy, why is assigning `realloc` directly to the owned pointer dangerous?

### Complexity

- Why is checked indexing `O(1)` even though the list may contain many elements?
- Why is one growth append `O(n)` while append is still described as amortized `O(1)`?
- What sequence of copied element counts supports the geometric-growth argument?
- How do contiguous storage and separately allocated linked nodes differ for indexing, insertion, cache locality, and pointer stability?

### Cybersecurity and interpretation

- How could an untrusted element count cause integer overflow before an allocation request?
- How could a stale interior pointer become a security or reliability problem after growth?
- Could repeated requests for enormous capacity become a denial-of-service concern even if memory access remains in bounds?
- Why does safe storage of synthetic event codes not prove that the codes themselves are trustworthy?

### Assignment and evidence

- Which functions are required in the Week 1 core, and which functions are not required?
- Why must each student-authored test add evidence beyond the supplied tests instead of renaming one?
- What must the saved test, warning, and sanitizer or debugger evidence demonstrate?
- If my program passes the happy-path tests but leaks memory on an error path, which rubric criteria are still unmet?

### Transfer and prerequisites

- Which C pointer, array, `struct`, and allocation ideas should I review before this lab?
- How will the `size`/`capacity` invariant return when we implement a Stack?
- Why does the linked-node preview matter before we study trees?
- When would stable node addresses matter more than constant-time indexing?

### Extension questions — optional

- Is `int_list_insert` at index `size` equivalent to append, and which boundary indexes must it reject?
- Why does `int_list_remove` shift later elements but leave capacity unchanged?
- How should insertion remain failure-atomic if growth is needed before shifting?
- Are insertion and removal required for the Week 1 submission or only for optional extension credit?

## Week 2 — Binary-Tree Foundations and BST Seed

### Meaning and mental model

- What makes a collection of linked nodes a tree rather than merely a set of pointers?
- What is the difference among a root, parent, child, leaf, subtree, path, depth, and height?
- Can the same node be a leaf, a subtree root, and someone else’s child at the same time?
- Why does a binary tree limit child positions without requiring binary-search ordering?

### Representation and invariants

- How do a tree diagram, an arena index table, and `left`/`right` pointer fields describe the same state?
- Why must the root have no parent while every other active node has exactly one parent?
- Why must every arena node be reachable from the root in a completed valid tree?
- Which shared-node, cycle, out-of-arena, and orphan configurations violate the whole-tree invariant?

### Operations, C API, and ownership

- Who owns the node array passed to `tree_arena_init`, and how long must that storage remain alive?
- Why may `storage` and `keys` be `NULL` for an empty tree but not for a nonempty tree?
- What does `tree_assign_child` check locally, and why can it return `TREE_OK` for a structure that is globally invalid?
- Why must `tree_immediate_family` validate the entire structure before reporting one node’s parent?

### Tracing

- Given keys, a root index, and several child assignments, what pointers and index relationships result after each operation?
- How do I translate a pointer value back to the corresponding arena index without confusing an address with a key?
- What does a validation trace record when two parents point to the same child?
- How can a tree satisfy every local child-slot check yet still contain a cycle or unreachable node?

### Tests and debugging

- Which tests distinguish an empty tree, a singleton leaf, a one-child node, and a two-child node?
- How can a regression test expose a child pointer that accidentally points outside the arena?
- What test separates a direct self-link defect from a longer ancestor cycle?
- In the Tree Structure Autopsy, which address and parent-count evidence identifies the first broken invariant?

### Complexity

- Why can a local leaf or child-count query be constant time?
- Why does whole-structure validation need to examine more than the selected node?
- What work is required to find a node’s parent when nodes store only child pointers?
- How might adding parent pointers change operation costs, storage, and invariant complexity?

### Cybersecurity and interpretation

- How could an unchecked child index become an out-of-bounds pointer or memory-corruption defect?
- Why can shared ownership of one node lead to double cleanup later?
- How might an attacker-controlled insertion order preview poor BST performance even when ordering remains correct?
- Why should a hierarchy inferred from security records be validated rather than assumed to be a tree?

### Assignment and evidence

- Which local query and link operations must I implement for the Week 2 core?
- Am I expected to write recursion, general traversal, dynamic node allocation, rotations, or balancing this week?
- What three distinct student-authored tests would add structural evidence beyond the supplied cases?
- What should my corrected Cognitive Pause explain if my original diagram accidentally created a graph?

### Transfer and prerequisites

- Which Week 1 ideas about addresses, `NULL`, invariants, and failure preservation are reused here?
- Why will depth-first traversal require more than the local family queries implemented this week?
- Which tree restriction disappears when we generalize relationships to a graph in Week 3?
- How does the strict BST seed prepare us for later search and AVL balancing?

### Extension and deferred questions — optional or later

- Could the arena be resized safely, and which stored pointers would become invalid if it moved?
- How would individually allocated nodes change ownership and cleanup compared with the fixed arena?
- Can we write a traversal now, or is traversal intentionally deferred to Week 5?
- Are rotations and balancing part of Week 2 evidence or reserved for the later AVL unit?

## Week 3 — Graph Models and Representations

### Meaning and mental model

- What can a graph represent that a tree cannot represent safely?
- What is the difference among a vertex, edge, neighbor, path, cycle, degree, and connected component?
- How do directed and undirected relationships differ in meaning?
- How is an unweighted graph different from a weighted graph even if both have the same endpoints?

### Representation and invariants

- What does `adjacency[from][to] == true` mean in a directed graph?
- Why must an undirected adjacency matrix be symmetric?
- Why must active diagonal cells be false under this course’s no-self-loop contract?
- What must be true of `vertex_count`, `kind`, active cells, and inactive cells immediately after `graph_init`, and which facts does later validation inspect?

### Operations, C API, and ownership

- Which indexes are valid after `graph_init` with `vertex_count == V`?
- Why do undirected add and remove operations need to update two matrix cells as one logical change?
- When must `graph_has_edge`, degree queries, and neighbor queries leave caller output unchanged?
- Why can an edge operation check only one selected pair while `graph_validate` checks the whole active graph?

### Tracing

- How do I translate the same graph among a drawing, an edge set, and an adjacency matrix?
- What matrix cells change when adding or removing one directed edge versus one undirected edge?
- How do I trace out-degree and in-degree without swapping rows and columns?
- In what order should `graph_out_neighbors` report neighbors, and how is that order visible in the matrix?

### Tests and debugging

- Which tests distinguish duplicate-edge, absent-edge, self-loop, and out-of-range failures?
- How can a test detect that an undirected add changed `[a][b]` but forgot `[b][a]`?
- What malformed graph should make a whole-graph validator fail even though an unrelated local query looks valid?
- In the Matrix Symmetry Autopsy, what two regression tests would prove both mutation and query behavior are repaired?

### Complexity

- Why is one adjacency-matrix edge lookup `O(1)`?
- Why does listing all outgoing neighbors from one vertex take `O(V)` with a matrix?
- Why does full matrix validation take `O(V^2)` even when the graph has few edges?
- For which dense or sparse workloads would a matrix, edge list, or adjacency list be the more plausible choice?

### Cybersecurity and interpretation

- Would a directed edge between two hosts mean communication, trust, authorization, or merely an observed record?
- How could silently treating a directed relation as undirected create a false security conclusion?
- Why must vertex identifiers be range-checked before any matrix access?
- Why are the course’s synthetic relationships unsuitable as evidence for scanning or exploiting live systems?

### Assignment and evidence

- Which graph operations and reports are required in the Week 3 core lab?
- Is DFS, BFS, weighted search, or dynamic adjacency-list construction required this week?
- What must the embedded Spiral 1 comparison say about choosing an ArrayList, tree, or graph?
- What evidence belongs in the Week 3 artifact and capstone skeleton without becoming a second submission?

### Transfer and prerequisites

- Which tree invariants become unnecessary, and which graph invariants must replace them?
- How will the neighbor order supplied by this representation affect later DFS and BFS traces?
- Why will graph traversal need separate visited state when tree traversal did not?
- What capstone decisions should remain representation-independent so the backend can change later?

### Extension and deferred questions — optional or later

- How would supporting self-loops change validation, degree definitions, and tests?
- How would weights change the matrix representation and the meaning of “no edge”?
- Could an adjacency list reduce work on a sparse graph, and what ownership problems would it introduce?
- Are graph searches and dynamically allocated adjacency lists part of Week 3 grading or later work?

## Week 4 — Stack and Nested Delimiters

### Meaning and mental model

- What behavior makes a collection a Stack regardless of how it is stored?
- Why does “last in, first out” match nested opening and closing delimiters?
- What is the difference among the Stack ADT, the C runtime call stack, and a stack-allocated array?
- Why is the top at `data[size - 1]` rather than `data[size]`?

### Representation and invariants

- Which relationships among `data`, `size`, `capacity`, and `limit` must always hold?
- What is the valid representation of a zero-limit Stack?
- Why may capacity be below limit without making the Stack invalid?
- What facts about pointer liveness, allocation extent, and unique ownership can `char_stack_validate` not establish?

### Operations, C API, and ownership

- What must `push`, `pop`, and `peek` do when passed an invalid Stack or invalid output pointer?
- Why must `pop` and `peek` leave `out_value` unchanged on underflow or any other failure?
- Why must `out_value` not point into the Stack’s character allocation?
- How does `char_stack_destroy` reset ownership, and when is calling it legal?

### Tracing

- How do `data`, `size`, `capacity`, and top change across pushes that trigger growth?
- What Stack trace results from the text `a[(b)]`, including ignored characters?
- At which index should the validator report an unmatched close, mismatch, unclosed open, or depth-limit failure?
- What state should remain after a forced allocation failure during `push`?

### Tests and debugging

- Which separate tests exercise underflow, exact limit, growth to a clipped capacity, and allocation failure?
- How can a test prove `peek` observes the top without removing it?
- In the Stack Autopsy, why does reading `data[size]` inspect the slot after the top?
- Which stack-level and delimiter-level regression tests would catch that off-by-one defect?

### Complexity

- Why are `pop` and `peek` worst-case `O(1)`?
- Why is `push` amortized `O(1)` but not worst-case `O(1)` in this representation?
- For text length `n` and maximum nesting depth `d`, why are the validator’s time and extra space expressed separately?
- How would a linked Stack change growth behavior, allocation frequency, and cache locality?

### Cybersecurity and interpretation

- Why is an explicit nesting-depth limit useful when input is untrusted?
- Could a syntactically balanced delimiter string still contain malicious or invalid content?
- How can ignored non-delimiter characters affect what security claim the validator is allowed to make?
- Why must allocation failure and excessive nesting produce distinct, checked statuses?

### Assignment and evidence

- Which `char_stack.c` and `delimiter_validator.c` TODOs are required for Week 4?
- What three student-test categories would demonstrate distinct Stack and validator claims?
- Why must every initialized temporary Stack be destroyed on every return path?
- What should the Stack-to-depth-first-exploration explanation establish without implementing DFS yet?

### Transfer and prerequisites

- Which ArrayList growth and failure-atomicity ideas are reused in the Stack backend?
- What changes when a later typed Stack stores vertex IDs or node pointers instead of characters?
- How can a Stack remember unfinished branches during depth-first exploration?
- Which C concepts should I review if pointer/output contracts in `pop` and `peek` are unclear?

### Extension questions — optional

- How would a fixed-array Stack differ from this growable Stack when the limit is known in advance?
- Could the validator report the matching opening index as well as the closing error index?
- How would quoted strings or escaped delimiters change the parsing state beyond a simple Stack?
- Are parser features beyond `()`, `[]`, `{}`, ignored characters, and the depth policy required this week?

## Week 5 — Tree DFS with Recursive Core

### Meaning and mental model

- What makes a traversal depth-first rather than breadth-first?
- How does recursion remember the node, next child, and return location for each unfinished branch?
- What is the difference among preorder, inorder, and postorder?
- Why is `NULL` a stopping case rather than a node that should be recorded?

### Representation and invariants

- What assumptions about cycles, shared children, and ownership do the recursive traversal functions make?
- Why can a `TreeOrder` hold at most `TREE_DFS_MAX_NODES` visits?
- What is the relationship between tree height and the number of simultaneously active recursive calls?
- Why does strict BST ordering apply to entire subtrees rather than only immediate children?

### Operations, C API, and ownership

- Which recursive traversals must I implement in the required Week 5 core?
- Why must `out_order` remain unchanged if traversal encounters a limit or invalid argument?
- What is the difference between `tree_node_release` and `tree_destroy_postorder`?
- Why must `tree_destroy_postorder` receive a pointer to the root pointer and set the caller’s root to `NULL`?

### Tracing

- For one asymmetric tree, what visit sequences result from preorder, inorder, and postorder?
- What active call frames exist immediately before and after returning from a leaf?
- How does a recursive preorder trace correspond to push/pop-like behavior on the runtime call stack?
- What branch decisions does `tree_bst_search` make for a present key and for a missing key?

### Tests and debugging

- Which tests distinguish an empty tree, singleton tree, left chain, right chain, and branching tree?
- How can a test prove that traversal records both each node’s key and its `flagged` value?
- In the Tree DFS Autopsy, what missing or misplaced base case causes the first incorrect recursive action?
- How can the live-node-count test seam reveal a leak after an insertion allocation failure or incomplete destruction?

### Complexity

- Why does a complete traversal take `O(n)` time regardless of visit order?
- Why is recursive traversal’s extra space `O(h)` rather than always `O(n)`?
- How do balanced and completely skewed shapes change `h` and BST-search time?
- Why can a very deep but valid tree still exhaust the C runtime call stack?

### Cybersecurity and interpretation

- How could a cycle or shared child turn trusted tree-recursion code into nontermination or double-free behavior?
- Why must tree shape and ownership be validated at a trust boundary before destructive traversal?
- How can adversarial key order make an unbalanced BST a performance risk?
- What does a `flagged` field demonstrate, and what security conclusion can it not establish by itself?

### Assignment and evidence

- Is recursive preorder alone required, or are recursive preorder, inorder, postorder, and postorder cleanup all core evidence?
- Is a complete explicit-Stack tree traversal required in the 14-week path?
- What must my three student-authored tests add beyond the supplied traversal cases?
- What should the tree-to-graph transfer explanation identify about assumptions that will no longer hold in Week 6?

### Transfer and prerequisites

- Which Week 2 vocabulary and strict BST rule must I understand before tracing these functions?
- How is the implicit runtime call stack related to, but different from, the Week 4 Stack ADT?
- Why will graph DFS need visited state even if tree DFS does not?
- How will inorder traversal and BST search reappear in the later AVL unit?

### Extension questions — optional

- How can an explicit Stack reproduce left-first preorder without recursion?
- Why would an iterative preorder implementation push the right child before the left child?
- What should happen if the explicit Stack’s configured limit is too small for the pending frontier?
- Is `tree_preorder_iterative` optional enrichment or required Week 5 evidence in the 14-week course?

## Week 6 — Graph DFS and Practical 1

### Meaning and mental model

- What changes when depth-first exploration moves from a tree to a graph?
- What is the difference between discovering, scheduling, popping, and processing a vertex?
- Why does a route back to an earlier vertex require persistent visited state?
- Why can DFS from one source leave valid vertices completely unvisited?

### Representation and invariants

- What must be true of `GraphDfsOrder` after a successful traversal?
- When should a vertex be marked visited so that it is never pushed twice?
- Why must the stored graph be validated before DFS begins?
- What invariant connects the Stack, visited array, and output order during iterative DFS?

### Operations, C API, and ownership

- Which DFS form is the required Week 6 implementation in the 14-week path?
- Why does iterative DFS inspect outgoing neighbors in descending index order?
- Why must `out_order` or `out_component_count` remain unchanged on every failure?
- Why does connected-component counting reject directed graphs under this API?

### Tracing

- What Stack, visited-array, and output states result at each step of a cyclic graph trace?
- How do ascending versus descending neighbor scans change the deterministic visit order?
- What happens when two pending routes lead to the same vertex before either route is processed?
- How does an outer scan over all vertices turn source DFS into connected-component counting?

### Tests and debugging

- Which tests separately exercise a self-loop rejection, a longer cycle, a disconnected graph, and an isolated vertex?
- How can a regression test prove that no vertex is scheduled or recorded twice?
- What test reveals a visited mark placed after `pop` instead of after a successful `push`?
- In the Graph DFS Autopsy, why does omitting or delaying the visited check cause repeated calls around a cycle?

### Complexity

- Why does full DFS over an adjacency matrix take `O(V^2)` time?
- Why can the same conceptual traversal take `O(V + E)` with adjacency lists?
- What is the maximum amount of Stack and visited storage needed by this bounded implementation?
- Why is a different visit order not automatically a complexity or correctness defect?

### Cybersecurity and interpretation

- What can reachability from a synthetic source tell us, and what can it not prove about authorization or exploitability?
- How could failing to validate a start vertex lead to unsafe array access?
- How might a deliberately dense graph amplify the cost difference between representations?
- Why should a disconnected vertex not be silently treated as absent from the dataset?

### Assignment and evidence

- Is Practical 1 the only required graded submission in Week 6?
- Do I also need to submit the standalone Module 6 Stage E lab?
- Which bounded iterative-DFS behavior, cycle test, and disconnection test can appear in Practical 1?
- What prior ArrayList, tree, graph, Stack, pointer, and bounds evidence may Practical 1 ask me to reconstruct or repair?

### Transfer and prerequisites

- How does the Week 4 Stack control the frontier in iterative graph DFS?
- Which Week 5 recursive-tree trace helps explain unfinished graph choices?
- What new visited invariant is added when a tree becomes a general graph?
- How will replacing the Stack with a Queue change exploration in the BFS arc?

### Extension questions — optional

- How does recursive graph DFS represent its frontier without an explicit vertex Stack?
- Can recursive and iterative DFS produce different valid orders on the same graph?
- What additional failure risk does recursion introduce on a very deep graph?
- Is recursive graph DFS required in Practical 1 or explicitly extension work?

## Week 7 — Queue and Circular Buffer

### Meaning and mental model

- What behavior makes a collection a Queue regardless of its storage representation?
- Why does first-in, first-out remove the event that has waited longest?
- How does Queue order differ from Stack order for the same arrival sequence?
- Why can logical Queue order differ from left-to-right physical array order?

### Representation and invariants

- Which relationships among `data`, `capacity`, `head`, and `size` define a valid Queue?
- What is the required canonical state of an empty Queue after initialization or complete draining?
- How is the next tail position derived from `head`, `size`, and `capacity`?
- What visible properties can `event_queue_validate` check, and which allocation and ownership facts remain unprovable?

### Operations, C API, and ownership

- Why does positive-capacity initialization allocate once while enqueue and dequeue allocate nothing?
- Which object fields, array slots, and output values must remain unchanged when an operation fails?
- Why must a dequeue or peek output pointer not point inside the Queue’s owned allocation?
- What is the difference between `peek` and `dequeue` in both behavior and permitted state changes?

### Tracing

- How do I compute the physical position of logical item `k` using modular arithmetic?
- What fields and slots result after filling, dequeuing several items, wrapping, and enqueuing again?
- When the final item is removed, what canonical empty fields should be restored?
- What should a trace show when enqueue is attempted on a full Queue under the reject-newest policy?

### Tests and debugging

- Which three required student-test categories cover validation, reuse, and failure preservation?
- How can one test prove the Queue can fill, drain, wrap, and then repeat the cycle correctly?
- What test distinguishes a full Queue from an empty Queue when head and tail positions coincide?
- In the Queue Autopsy, which missing modulo or boundary check first produces an invalid physical index?

### Complexity

- Why are validation, enqueue, dequeue, and peek `O(1)` in this fixed-capacity design?
- Why would shifting all surviving events after every dequeue make removal `O(n)`?
- What storage cost is paid at initialization even when the Queue is initially empty?
- How would a linked Queue change capacity policy, allocation costs, locality, and ownership complexity?

### Cybersecurity and interpretation

- What information-loss risk comes with reject-newest, discard-oldest, and backpressure policies?
- Why is silently overwriting the oldest event inappropriate for this course’s contract?
- How could a wrap-around bug corrupt or misorder security-event records?
- Why do correct Queue mechanics not guarantee that incoming event codes are authentic or correctly prioritized?

### Assignment and evidence

- Which validation, enqueue, and dequeue TODOs are required in the Week 7 core?
- Must the student tests assert exact fields and physical slots as well as returned values?
- What warning, test, and autopsy evidence must accompany the Queue implementation?
- Why is there one ordinary Week 7 lab even though the Queue will immediately be reused in Week 8?

### Transfer and prerequisites

- Which array-index, invariant, ownership, and failure-preservation skills from Weeks 1 and 4 are reused here?
- How will FIFO ordering produce nondecreasing depth during tree level-order traversal?
- Why will graph BFS need both this Queue and a visited or distance record?
- Which circular-buffer defect might reappear as a Practical 2 repair question?

### Extension questions — optional

- How would a dynamically growing circular Queue preserve logical order during reallocation?
- How could a linked Queue achieve unbounded logical capacity, and what allocation failures would appear?
- What synchronization would a Queue need if producers and consumers ran concurrently?
- Are discard-oldest, backpressure, dynamic growth, and concurrent Queue implementations required for Week 7?
