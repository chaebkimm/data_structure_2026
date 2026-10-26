# Consolidated Weeks 1–7 Questions

These questions match the current weekly pages. Optional clusters remain optional.

## Week 1 — Keeping Data Together in One Place

[Weekly vocabulary and scope](week_01_arraylist.md)
## Core questions


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

## Lab and testing questions

These questions connect the textbook actions to the required lab. Extra
boundary and operation-sequence tests are the optional extension.

- How do the textbook's array, size, and capacity map to the function arguments?
- Which test distinguishes an unused array slot from a valid list index?
- How can a snapshot prove that a rejected operation changed no array slot?
- What happens when size is negative or greater than capacity?
- Why must the caller ensure capacity does not exceed the actual array length?
- Which operation sequence demonstrates that deletion makes room for another addition?
- How does the guard-slot autopsy expose a bad full check without accessing outside its physical array?

## Week 2 — Array-Index Expression Trees

[Weekly vocabulary and scope](week_02_binary_tree.md)


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

[Weekly vocabulary and scope](week_03_graph_representations.md)


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

## Week 4 — Integer Stack and Postfix Evaluation

[Weekly vocabulary and scope](week_04_stack.md)


### Meaning and mental model

- Why must the newest saved item leave before older items?
- How do push, peek, and pop differ?
- Why can LIFO behavior stay the same when array indexes grow in a different direction?
- How is the explicit integer Stack different from runtime call bookkeeping?

### Representation and invariants

- Which indexes are active when `top == 2`, and how many items are stored?
- Why does push increment `top` before writing, while peek reads `stack[top]`?
- Why may an inactive cell still contain a character after pop?
- Why are `top == -1` and `top == 9` the empty and full states respectively?

### Operations and C API

- Why must callers avoid full push even though `is_full()` exists?
- Which out-of-bounds index would empty peek/pop select, and why is no return value promised?
- Why does `pop()` read `stack[top]` before decrementing, without erasing the old cell?
- How does `capacity` control the full check without resizing the actual ten-position array?

### Tracing

- What indexes and states result from pushing `'A'`, `'B'`, and `'C'`?
- What do peek and two pops return after those three pushes?
- Why is `top` the last active index, while `top + 1` is the item count?
- How can a snapshot show that a boundary predicate preserves state without calling an invalid operation?

### Expression conversion and evaluation

- How does `1-2*3+4` become `123*-4+` before any numeric evaluation occurs?
- Why does incoming `+` cause both waiting `*` and `-` to be emitted?
- Why must evaluation pop right operand `num2` before left operand `num1`?
- How do shared global `top`, local output cursor `pos`, and token length describe different state?
- Why does the explicit terminator write change `pos` from 7 to 8 after the Stack is already empty?
- Why does the closing-parenthesis loop pop `(` before `break`, without writing it?
- Why does `1+(2+3)` produce five postfix tokens `123++` and evaluate to 6?
- Why are balanced parentheses required even though the dedicated converter handles grouping?

### Tests and debugging

- Which tests distinguish empty, one-item, and full Stack states?
- How can `8-3-2+1` distinguish left associativity from right associativity?
- Why can a faulty top read stay inside the physical array and still be wrong?
- Why do repeated conversions of different lengths and prior active items test shared-state reset and termination?

### Complexity

- Why do push, peek, and pop each take `O(1)` time?
- Why does pop require no shifting?
- Why is conversion `O(n)` despite its inner operator-pop loop?
- Why is evaluation `O(n)`, and how do the current fixed buffers bound storage?

### Safety and interpretation

- Why do the null-terminated scans accept a one-digit expression such as `7`?
- Which syntax restrictions are assumptions rather than validated rejections in this source?
- Why must divisors be nonzero and intermediate integer results be representable?
- How does `!is_empty()` prevent conversion from peeking or popping an empty Stack?

### Assignment and evidence

- How do the lab driver and current tests use `student/lab.c`?
- What LIFO, boundary, and valid-expression cases provide three distinct additions to `test_lab.c`?
- Which warning and sanitizer outputs should accompany the trace evidence?
- What must an autopsy explanation distinguish about physical bounds and the active prefix?

### Transfer and prerequisites

- How does this top-index representation differ from Chapter 1's stored item count?
- How can a later Stack use pointer items while preserving the same LIFO rule?
- How does delaying operators illustrate remembering unfinished work?
- Why does `c - '0'` turn a digit character into a numeric operand?

### Extension questions — optional

- How could explicit error reporting safely reject unsupported characters and missing operands?
- What additional parsing rules and buffers would multi-digit operands require?
- How does the optional legacy caller-owned integer API share the active-prefix layout but differ in ownership and error reporting?

## Week 5 — Tree DFS and Expression Trees

[Weekly vocabulary and scope](week_05_tree_dfs.md)
## Representation and recursive visits


- Why are child links integers while node data is a character?
- Why is root 5 `F`, and why is `nodes_size` 10 when seven nodes are reachable?
- Does changing a child index move a node?
- How do the three visit positions produce their complete orders?
- Which data-processing actions could be added at the preorder, inorder, and postorder comments?
- Does the current lab record or print visit data at those comments?
- How does recording only the last visited character differ from retaining a complete sequence?
- Where is a negative index checked, and why does `tree_traversal(-1)` return safely?
- How many empty-child calls does a leaf make?
- Which calls are waiting while `D` is active, and what must they resume?
- How many real-node frames and extra empty-child frames can be active?
- What assumptions exclude cycles, shared children, and invalid positive indices?

## Explicit traversal

- Why must an explicit traversal remember both node index and progress?
- What do steps 0, 1, and 2 do, and why advance before pushing a child?
- How does `int step = progress[i]++;` distinguish the old step from the saved next step?
- Why does the wrapper pass `peek()` to `tree_traversal_proceed(int i)` on every iteration?
- What happens when the top is `-1`, and why must it be checked before indexing progress?
- What are the final progress values for reached and unconnected nodes?
- Why does a second unchanged traversal have no terminating step-3 case?
- What reset makes another run possible, and does resetting `top` reset progress?
- How many stack entries does a ten-node chain need with its sentinel?
- How does progress storage differ from used path storage?

## Postfix construction

- Why must the initially empty `postfix` be prepared before building?
- What does Chapter 4's default expression convert to?
- Why does token index become node index in `build_tree_from_postfix()`?
- What does each stack entry represent after every token of `123*+`?
- Why is the first pop the right child, and what would reversal do to `12-`?
- What are the returned root, `nodes_size`, and `top` after the final pop?
- Why are digits stored as characters, and does construction calculate values?
- What happens to the earlier alphabet tree?
- Why need two roots per operator and exactly one before returning?
- Does the builder validate malformed input, empty input, or capacity?

## Precedence-aware inorder output

- What does the current writer output for `123*+`, `12+3*`, and `123--`?
- How would omitting parentheses lose grouping in the latter two examples?
- Why does the implemented writer use child `<` parent on the left and child `<=` parent on the right?
- How does left associativity distinguish `1-2-3` from `1-(2-3)`?
- Why does the writer retain `1+(2+3)` without simplifying it?
- How do `prec()` and `prec2()` differ for digits, and why does precedence 3 avoid digit parentheses?
- Where do opening and closing parentheses surround each child call?
- How do the writer's preorder, inorder, and postorder comment positions relate to its actions?
- What does `write_char()` do to the shared cursor?
- Why can the alphabet tree be traversed but not passed to the writer?
- How does `write_infix(-1)` produce an empty string, and why does that not validate malformed operator nodes?

## State, capacity, and efficiency

- How does `write_infix()` reset `infix_pos` before each complete output?
- Why must child calls share the advancing position?
- Why does final `infix_pos` include the null terminator?
- How can a shorter output replace a longer previous expression?
- Which wrapper supports repeated calls itself, and which requires a caller reset?
- How many tokens fit `postfix[8]`?
- Why does grouped `1234+++` fit the current `infix[20]` buffer?
- Why can a valid seven-token binary expression require at most twelve output bytes including its terminator?
- Why are traversal and writing linear in reachable nodes, and building linear in tokens?
- Why is used path/call storage `O(h + 1)` despite separate progress storage?
- How do fixed reserved arrays differ from used space and generalized bounds?
- What do the demo's completion and progress lines show, and how can breakpoints recover visit orders?

## Supplemental reconstruction

The companion [concept slides](../module_05_tree_dfs/student/ppt_material.md)
use an `A`-rooted tree for this activity.

- How do `ABDECFG` and `DBEAFCG` reconstruct that tree?
- Why must subtree sizes determine the preorder segments?
- Why do distinct labels matter, and why is preorder alone insufficient?
- Which examples have root `A` and which have root `F`?
- Is reconstruction implemented in the current lab?
- Why can reconstruction by inorder scans take quadratic time, and how does a map help?

Use nonempty valid postfix of up to seven single-character tokens, digits
and binary `+ - * / %`, with no spaces. Keep implemented parentheses and
writer resets separate from proposed validation/progress-reset extensions
and the legacy pointer-based exercise's contracts.

## Week 6 — Graph DFS and Practical 1

[Weekly vocabulary and scope](week_06_graph_dfs.md)


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


## Week 7 — Linked Lists with a Linked Queue Example

[Weekly vocabulary and scope](week_07_linked_list.md)

### Representation and free-chain initialization

- How does a linked sequence in `lnodes[10]` differ from an ArrayList's active prefix even though both use contiguous arrays?
- Why is a node's index different from the integer stored in its `data` field?
- What chain does `init_lnodes_pool()` create, and why does slot 9 end in `-1`?
- Why must traversal stop at `-1` before indexing `lnodes[]`?
- What happens to live links if `init_lnodes_pool()` is called while the pool is still in use?
- Why does initialization visit every reserved slot while one allocation uses a fixed number of updates?

### Allocation, detachment, and recycling

- How do `free_head` and the chosen node change when `new_lnode(17, -1)` succeeds?
- What remains unchanged when an eleventh allocation returns `-1` from an exhausted pool?
- Why does `free_lnode(node)` change the free chain without releasing C array storage?
- Why must a node leave every live list before it is recycled?
- Why can recycling the same valid index twice corrupt the free chain even though the bounds check passes?
- Which returned index is used next after allocating slots 0 and 1, recycling slot 0, and allocating again?

### Predecessor link changes

- Why must `link_lnode(prev, node)` copy the predecessor's old next link before replacing it?
- Which links change when a new node is inserted between two existing nodes?
- What does `delete_next_lnode(prev)` return when the predecessor has no following node?
- Why does `delete_next_lnode(prev)` neither recycle the detached node nor clear its old next link?
- Why must the caller manage a separate list-head change instead of passing `-1` as a predecessor?
- Why are known-predecessor insertion and detachment constant work while finding that predecessor can take O(n)?

### Linked queue as a linked-list example

- How does FIFO order differ from the Stack's LIFO order for values 17, 23, and 31?
- How does the first `enqueue(value)` allocate a node and set both `head` and `tail` to its pool slot?
- Why does public `enqueue` allocate with next `-1`, and what remains unchanged when it returns `false` from an exhausted pool?
- Which tail link changes when `enqueue_lnode` appends another detached node, and why is no tail search needed?
- How does removing the only queued value restore both endpoints to `-1` and return its slot to the free chain?
- How do the raw `dequeue_lnode()` pool-slot result and the public `dequeue()` value result differ, especially when the stored value is `-1`?
- Why does public `dequeue()` copy the payload before recycling, and why must the caller avoid recycling that slot a second time?
- Why must the caller check `is_empty_queue()` before public dequeue even though a debug assertion diagnoses an empty request?
- Why must `enqueue(value)` run outside an `assert` expression when builds may define `NDEBUG`?
- Which endpoint, live-chain, free-chain, and full-queue traces show public FIFO behavior and automatic slot reuse in the single Week 7 artifact?
