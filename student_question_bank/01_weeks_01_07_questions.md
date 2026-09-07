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

## Week 2 — Expression-Tree Model, Binary-Tree Links, and Recursive Clearance

### Meaning and mental model

- How does `(3 + 5) * 2` become a root operation, a sub-expression, and operand leaves?
- How do root, parent, child, ancestor, descendant, and subtree differ?
- Why is a node with only a right child still a valid binary-tree node?
- How do a generic binary tree's zero/one/two-child possibilities differ from a completed binary expression?

### Representation and invariants

- How do a diagram and the data, left, and right fields describe the same state?
- Why are left and right operand positions not interchangeable for every operator?
- Why must every non-root node appear in exactly one child position?
- Which no-cycle and no-sharing rules are caller responsibilities rather than automatic checks?

### Direct operations and C

- Which fields must be initialized before a local node is linked into a tree?
- Why can the C character constants `'*'` and `'+'` be stored in an `int` data field in this simplified model?
- What does `&plus` provide, and how does `root.left` differ from `node->left`?
- What must remain unchanged when the chosen child position is already occupied?

### Recursive tracing

- What stopping cases does tree_find need?
- Why does the canonical search order begin `'*', '+', 3, 5, 2`?
- Which node address is returned when several nodes store the target value?
- What unfinished work remains after the search enters the left subtree?

### Clearing and lifetime

- What happens to the data and links of every node reached by tree_clear?
- Why does clearing root.left not automatically set root.left to NULL?
- Why does a cleared node remain a live object, and why is data zero not an empty-node marker?
- Why must every linked local node variable stay alive while the tree uses its address?

### Tests and debugging

- Which cases distinguish no children, a left-only child, and a right-only child?
- How can a snapshot test prove that an occupied-side attachment made no change?
- How can a test prove that clearing the `'+'` branch preserves the right operand `2` and its position?
- Why should cycle mistakes be analyzed with diagrams rather than passed to these recursive functions?

### Complexity

- Why do initialization and a guarded child-link assignment take constant work?
- Why can an unsuccessful search inspect every node?
- Why does clearing a subtree with k nodes require work proportional to k?
- Why can recursive search and clearance use temporary call-stack space proportional to height?

### Safety and interpretation

- How can a child link back to an ancestor prevent a recursive operation from finishing?
- In the shared-child autopsy, why does clearing one branch unexpectedly change the other branch's data?
- Why is the shared child's pointer still live after clearance rather than a pointer to released storage?
- What information can be lost if an occupied child link is overwritten without checking it?

### Assignment and evidence

- What must I implement in tree_find and tree_clear?
- How should my three student-authored tests demonstrate expression construction, searching, and clearance?
- What warning-enabled and diagnostic evidence belongs in the submission?
- What should my corrected Cognitive Pause explain about links, search order, and node lifetime?

### Transfer and deferred questions

- Which Chapter 1 ideas about fixed storage, checking before mutation, and invariants are reused?
- How will Module 3 change the no-sharing and no-cycle restrictions?
- When will Module 5 formalize and compare traversal orders and introduce binary-search ordering?
- Why are allocation, parent links, root-comparison helpers, rotations, and balancing outside this lab?

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

- Why does `graph_init` clear all 16 by 16 cells even when only three vertices are active?
- Which checks must occur before a direct grid lookup or update?
- Why may a repeated valid add or removal succeed without changing the final cell value?
- What do `size_t` and `GRAPH_MAX_VERTICES` contribute to the fixed representation?

### Tracing

- Which cells record the textbook edges `0 -> 1`, `1 -> 2`, and `1 -> 0`?
- Why is the App server's initial row `[1, 0, 1]`, and what is its out-degree?
- After removing `1 -> 2`, what is row 1 and what out-degree should be reported?
- How can `0 -> 1` and `1 -> 0` form a valid cycle while both diagonal cells remain zero?

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

## Week 4 — Fixed-Capacity Stack and Expression Precedence

### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why is only one end called the top?
- How is the course Stack related to, but different from, runtime call bookkeeping?

### Representation and invariants

- Which array indexes belong to a Stack with size 3 and capacity 10?
- Why is the top at `stack[size - 1]` rather than `stack[size]`?
- Why may an inactive slot still contain an old integer?
- What goes wrong when size is negative or greater than capacity?

### Operations and C API

- What does push return when the Stack is full or metadata is invalid?
- Why must peek leave size and every array slot unchanged?
- Why can pop remove an item by decreasing size without erasing its cell?
- Which failures must leave the caller's output value unchanged?

### Tracing

- What states result from pushing 100, 200, and 300 in that order?
- What do peek and two pops report after those three pushes?
- What remains active after the first pop, and what remains physically stored?
- How can a snapshot prove that a rejected push changed nothing?

### Expression evaluation

- Why does `1+2*3` evaluate to 7 rather than 9?
- What is stored in the number and operator Stacks after each character?
- When must a waiting operator be applied before a new operator is pushed?
- Why are spaces, parentheses, multi-digit numbers, and other operators rejected?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can a test prove that zero is ordinary Stack data?
- Why does the faulty-top autopsy read an inactive slot without leaving the array?
- Which malformed-expression tests exercise token order and unsupported characters?

### Complexity

- Why do checked push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why does evaluating an expression of length `n` take `O(n)` time?
- Why does this evaluator use bounded additional space even for a longer valid input?

### Safety and interpretation

- Why must the caller's array contain at least capacity elements?
- Why can a function validate metadata but not discover the array's physical length?
- How does checked integer arithmetic prevent undefined signed overflow?
- Why does a valid result establish only the supported arithmetic grammar and value?

### Assignment and evidence

- Which `int_stack.c` and `expression_evaluator.c` TODOs are required?
- What three student-test categories provide nonduplicate evidence?
- Which warning and sanitizer commands should be recorded?
- What must the corrected autopsy explanation distinguish about size and capacity?

### Transfer and prerequisites

- Which Chapter 1 active-prefix and rejection rules are reused?
- How will later Stacks change the item type while preserving LIFO behavior?
- How can LIFO storage remember unfinished choices in later traversal work?
- Which pointer concepts should I review for checked output parameters?

### Extension questions — optional

- How could a checked evaluator support subtraction while preserving operand order?
- What additional rules would multi-digit operands require?
- How would parentheses change the operator-Stack algorithm?
- How would a growable backend change the representation without changing LIFO behavior?

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
