# Student Question Bank — Weeks 1–7

> This is the consolidated question-only view. The canonical weekly pages,
> including vocabulary and required-scope notes, are linked from the
> [all-week bank index](../Data_Structures_Course_2026_Student_Question_Bank.md).

## Week 1 — Keeping Data Together in One Place

### Memory and access

- Why can an item be found directly when its index is known?
- Why can searching for a value require checking every stored item?
- Which positions belong to the list when size is 3 and capacity is 10?
- Why do stored items begin at index 0 in this design?

### Insertion and deletion

- After deleting index 1 from `[100, 500, 300]`, which items must move?
- Why does insertion shift items from back to front?
- How much work can insertion at the front require?
- How much work can deletion at the end require?

### Fixed capacity and invariants

- How do size and capacity differ?
- What must remain unchanged when an addition is attempted on a full list?
- Why is index 10 not a slot in `int array[10]`?
- How does deleting an item make room without changing capacity?
- Why can zero be a stored value rather than an empty-slot marker?
- What goes wrong if size includes a slot that has not been initialized as a list item?

### C connection

- Which conditions must be checked before reading or updating `array[index]`?
- Why can insertion accept index equal to size while removal cannot?
- Why must the caller assign the size returned by a mutating function?
- What does `int_list_find` return for a missing value or duplicate matches?
- What does `const` promise about the array passed to `int_list_find`?

### Lab and testing questions

- How do the textbook's array, size, and capacity map to the function arguments?
- Which test distinguishes an unused array slot from a valid list index?
- How can a snapshot prove that a rejected operation changed no array slot?
- What happens when size is negative or greater than capacity?
- Why must the caller ensure capacity does not exceed the actual array length?
- Which operation sequence demonstrates that deletion makes room for another addition?
- How does the guard-slot autopsy expose a bad full check without accessing outside its physical array?

## Week 2 — Array-Index Expression Trees

### Meaning and mental model

- How does `1+2*3` become an addition root with a multiplication subtree?
- How do root, parent, child, ancestor, descendant, and subtree differ?
- Why can a general binary tree have a right child without a left child?
- Why does a completed operator node in this expression model require two children?

### Representation and invariants

- How do the expression string, node-array table, and hierarchy describe the same expression?
- Why is node index 0 valid while child index -1 means no child?
- Why must each non-root node occur in exactly one child position, with no downward cycles?
- How does attaching disjoint subtrees under a fresh operator preserve the tree rules?

### Node creation and C

- What does `new_node` store, initialize, increment, and return?
- How do a stored digit character, a node index, and an integer answer differ?
- How do I read `nodes[nodes[root].right].data` one step at a time?
- Why does returning the old value of `size` identify the new node correctly?

### Parsing and precedence

- What does `term()` consume, and why does it leave the next `'+'` unread?
- Why does `terms()` call `term()` for a whole operand instead of reading one digit?
- How do `eq[pos]` and `eq[pos++]` differ when tracing the next unread character?
- Why do repeated equal operators make each new operator the parent of the previous subtree?

### Recursive evaluation

- What is the digit-leaf base case, and why does subtracting `'0'` produce its integer value?
- What unfinished work waits while `eval_tree` evaluates a child subtree?
- Why do the canonical completed calls return 1, 2, 3, 6, and 7?
- Why do the operator characters and parser state remain unchanged after evaluation?

### Tests and debugging

- Which test shows that a digit-only expression can return root index 0?
- How can checking links reveal an association error that an answer-only test misses?
- How can member snapshots and a second evaluation establish nonmutation?
- Why must every independent test build reset both size and pos and copy a valid expression?

### Complexity

- Why do reserving a node and assigning one child link each take constant work?
- Why does the two-level parser take time proportional to the number of characters?
- Why does evaluation visit every expression-tree node once?
- How do the fixed 20-node array, its occupied slots, and the evaluator's call-stack depth differ?

### Input contract and autopsy

- Why do valid inputs use single digits, no spaces or parentheses, at most 19 characters, and int-sized results?
- Why does treating every operator alike turn `1+2*3` into a tree whose answer is 9?
- Why can the faulty tree satisfy the general tree rules and pass memory diagnostics while expressing the wrong grouping?
- Why should the precedence defect be repaired in construction rather than by ignoring the tree during evaluation?

### Assignment and evidence

- What must I implement in `new_node`, `term`, `terms`, and `eval_tree`?
- What new evidence should my creation, construction, and evaluation tests provide?
- What warning-enabled and diagnostic evidence belongs in the submission?
- What should my corrected Cognitive Pause explain about indices, term boundaries, and returned values?

### Transfer and deferred questions

- Which Chapter 1 ideas about fixed storage and occupied slots apply to the nodes array?
- How will a later graph model change the no-sharing and no-cycle restrictions?
- How can later traversal topics describe the child-before-parent completion order used by evaluation?
- Why are malformed-input validation, extra public functions, rotations, and balancing outside this lab?

## Week 3 — Directed Adjacency Matrices

## Anticipated student questions

### Meaning and mental model

- What can a graph represent that Chapter 2's tree cannot represent as a valid tree?
- What is the difference among a vertex, an edge, a path, and a cycle?
- Why are `u -> v` and `v -> u` separate facts in a directed graph?
- What information does this unweighted graph omit from an edge?

### Representation and invariants

- What does `grid[from][to] == 1` mean?
- How does `vertex_count` distinguish an isolated active vertex from an inactive index?
- Why must every inactive row and column remain zero?
- Why is a self-loop forbidden here even though a cycle through two or more vertices is valid?

### Operations and C

- Why does `graph_init` clear all 16 by 16 cells even when only seven accounts are active?
- Which checks must occur before a direct grid lookup or update?
- Why may a repeated valid add or removal succeed without changing the final cell value?
- What do `size_t` and `GRAPH_MAX_VERTICES` contribute to the fixed representation?

### Tracing

- Which cells record the follows `0 -> 1`, `1 -> 2`, `2 -> 0`, `2 -> 3`, `4 -> 5`, and `5 -> 4` for Mina, Joon, Sora, Dae, Hana, Leo, and Nuri?
- Why is Sora's initial row `[1, 0, 0, 1, 0, 0, 0]`, and what is her out-degree?
- After removing `2 -> 3`, what is row 2 and what out-degree should be reported?
- How can `0 -> 1 -> 2 -> 0` form a valid cycle while every diagonal cell remains zero?
- Why is Nuri initially isolated while Dae, who also follows nobody, is not?

### Components and feeds — after the Stage C attempt

- What does maximal mean when identifying a connected component?
- Why do weak components ignore arrow directions while strong components require directed paths in both directions?
- Why do Mina, Joon, and Sora form a strong component without every pair following each other directly?
- Why does Dae share their weak component but form a separate strong component?
- Which components change when Sora unfollows Dae?
- How could component membership help select candidate posts without determining their ranking?
- Why can restricting Sora's feed to her strong component exclude a directly followed account?
- How could an isolated account such as Nuri receive recommendations, and why does connectivity not grant permission to view a post?

### Tests and debugging

- How can a test prove that initialization clears cells outside the active square?
- Which test distinguishes a directed edge from its reverse edge?
- How can a test prove that a rejected bound or self-loop addition changes no matrix cell?
- How can a test prove that a failed out-degree request leaves its output unchanged?

### Complexity

- Why does reading, adding, or removing one checked edge take constant work?
- Why does out-degree counting inspect every active cell in one row?
- Why does inspecting an active matrix take work proportional to the vertex count squared?
- Why can a fixed adjacency matrix waste storage when few edges exist?

### Safety and interpretation

- What can happen if a vertex index is used before it is checked against `vertex_count`?
- Why do the four functions assume the rest of the supplied matrix already satisfies its invariant?
- How can a stale 1 in an inactive row reappear as a ghost connection later?
- Why does an all-zero row mean no outgoing edges rather than no vertex?

### Assignment and evidence

- Which four functions are implementation tasks, and which guarded lookup remains a direct operation?
- What three distinct student-designed tests are required?
- What build, diagnostic, and explanation evidence belongs in the submission?
- Why are Boolean graph kinds, validators, DFS, BFS, and dynamic adjacency lists outside this lab?

### Representation comparison

- How would an undirected connection differ from the directed matrix operation implemented here?
- How would an edge list and an adjacency list store the same relationships differently?
- When might a matrix be preferable to a list representation, and when might it be wasteful?
- Why are weights and connected-component algorithms discussed without being implemented here?

### Transfer to later modules

- Why will a later traversal need visited state when this graph contains a cycle?
- How will scanning matrix columns in increasing order influence later traversal traces?
- What new support must Module 6 add before it can operate on undirected graphs?
- How do the ArrayList, tree, and graph representations differ in their central invariant?

## Week 4 — Character Stack and Postfix Evaluation

### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why can LIFO behavior stay the same when array indexes grow in a different direction?
- How is the explicit character Stack different from runtime call bookkeeping?

### Representation and invariants

- Which indexes are active when `top == 7`, and how many characters are stored?
- Why does push decrement `top` before writing, while peek reads `stack[top]`?
- Why may an inactive cell still contain a character after pop?
- Why are `top == 10` and `top == 0` the empty and full states respectively?

### Operations and C API

- What does a full push do, and why does it return no value?
- What do empty peek and pop return, and which state stays unchanged?
- Why does a successful pop increment `top` without erasing its old cell?
- Why does changing `capacity` alone not change the actual ten-position Stack?

### Tracing

- What indexes and states result from pushing `'A'`, `'B'`, and `'C'`?
- What do peek and two pops return after those three pushes?
- How do `top` and `10 - top` change in opposite directions?
- How can an array snapshot prove that a full push changed nothing?

### Expression conversion and evaluation

- How does `1-2*3+4` become `123*-4+` before any numeric evaluation occurs?
- Why does incoming `+` cause both waiting `*` and `-` to be emitted?
- Why must evaluation pop right operand `num2` before left operand `num1`?
- How do `top`, global `size`, and local `pos` describe different state?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can `8-3-2` distinguish left associativity from right associativity?
- Why can a faulty top read stay inside the physical array and still be wrong?
- Why do repeated conversion and a shorter replacement expression test both reset and termination?

### Complexity

- Why do push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why is conversion `O(n)` despite its inner operator-pop loop?
- Why is evaluation `O(n)`, and how do the current fixed buffers bound storage?

### Safety and interpretation

- Why do eight-character input and output arrays allow at most seven token characters?
- Which syntax restrictions are assumptions rather than validated rejections in this source?
- Why must divisors be nonzero and intermediate integer results be representable?
- Why can an empty-read sentinel be ambiguous if a caller stores `'\0'` as data?

### Assignment and evidence

- How do the lab driver and current tests use `student/lab.c`?
- What LIFO, boundary, and valid-expression cases provide three distinct additions to `test_lab.c`?
- Which warning and sanitizer outputs should accompany the trace evidence?
- What must an autopsy explanation distinguish about physical bounds and the active suffix?

### Transfer and prerequisites

- How does this active suffix compare with Chapter 1's active prefix?
- How can a later Stack use integer or pointer items while preserving LIFO?
- How does delaying operators illustrate remembering unfinished work?
- Why does `c - '0'` turn a digit character into a numeric operand?

### Extension questions — optional

- How could explicit error reporting safely reject unsupported characters and missing operands?
- What additional parsing rules and buffers would multi-digit operands require?
- How would parentheses change the operator-Stack algorithm?
- How does the optional legacy caller-owned integer API differ in layout and error reporting?

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

- Which Week 2 tree, ownership, and recursion ideas must I retrieve before learning formal traversal orders and BST rules?
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

- How does the Week 4 LIFO rule control which frontier item leaves next in iterative graph DFS?
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
