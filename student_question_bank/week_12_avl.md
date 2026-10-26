# Week 12 — BST-to-AVL with the Supplied Indexed Lab

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope for the 14-week course

The supplied [Module 12 lab](../module_12_bst_avl/student/lab.c) is complete.
Students predict and trace its states, write assertion tests, and compare
plain BST and AVL behavior in one Week 12 artifact within 180 minutes.
There are no required implementation TODOs or AVL deletion assignment.

The source reuses Module 2's ten character records and integer child IDs,
with -1 for a missing link and a separate `height[10]` array. Equal keys
descend left, but rotations preserve nondecreasing inorder and may place
equals on either side. The four helpers rewire links; `_add` refreshes
heights and returns the new local root. The driver supplies baseline
insertion, lookup, measurement, and validation. The retained allocated
64-node unique-key library is a separate optional reference.

## Vocabulary students will learn

| Term | Working meaning |
|---|---|
| binary tree | Records with at most two child links each. |
| node | One record in `nodes[10]`, holding character data and child IDs. |
| node ID | The record's integer array position, distinct from its key and height. |
| key | The character data used to choose a search direction. |
| root | The first record's ID, or -1 for an empty tree. |
| child | A next record reached through a left or right link. |
| subtree | A record and all records reachable below it. |
| link | An integer child ID in this lab, rather than an allocated-node pointer. |
| sentinel | A reserved marker; -1 means no child or root here. |
| binary search tree (BST) | A tree whose whole left and right regions follow the search-order rule. |
| whole-subtree ordering | Every left-region key is no larger, and every right-region key no smaller, than the current key. |
| invariant | A property required of every valid tree state. |
| inorder traversal | Visit the left subtree, current key, then right subtree. |
| nondecreasing | Each next key is at least the previous key, allowing equals. |
| duplicate key | Equal character data in distinct records; accepted by this lab. |
| edge height | The longest downward route counted in links; missing height is -1. |
| leaf | A record with two -1 child links and height 0. |
| stored height | The cached value in `height[id]`, which must match link-derived height. |
| metadata | Information about other data, such as a record's stored height. |
| balance factor | Left subtree height minus right subtree height. |
| AVL tree | A search tree whose balance factors are all -1, 0, or 1. |
| rotation | Local link changes that preserve inorder while repairing shape. |
| LL case | Left-heavy shape repaired by promoting the left child. |
| RR case | Right-heavy shape repaired by promoting the right child. |
| LR case | Left-heavy inner shape repaired by promoting the left child's right child. |
| RL case | Right-heavy inner shape repaired by promoting the right child's left child. |
| middle subtree | A region transferred between the demoted and promoted records during repair. |
| capture | Save a child or grandchild ID before overwriting its old link. |
| relink | Assign a child field to a different record ID. |
| recursion | A function calls itself for a smaller subtree. |
| base case | The missing-link case that installs a fresh leaf and stops descent. |
| recursive unwind | Returning through the earlier calls while reconnecting and repairing. |
| local root | The possibly changed root ID of the current subtree. |
| caller precondition | A condition the driver must establish because the source does not check it. |
| capacity | The ten available record IDs; insertion does not enforce this limit. |
| reachability | A record can be followed from the root through stored links. |
| cycle | A link route returns to a record already on that route. |
| validator | A diagnostic traversal checking IDs, reachability, order, heights, and balance. |
| assertion | An executable check of a test's expected property. |
| regression test | A test that detects the return of a previously identified defect. |
| comparison count | One key comparison per visited record in the driver's lookup. |
| skewed | Shaped mainly as one long branch. |
| algorithmic-complexity denial of service | Valid chosen input forces excessive operation work. |
| memory corruption | An invalid memory read, write, or release, distinct from slow valid work. |
| resource exhaustion | A finite resource such as memory or processing time is used up. |

### Optional reference vocabulary

| Term | Working meaning |
|---|---|
| AVL deletion | Remove a record and repair heights and balance toward the root. |
| parent pointer | An upward memory-address link in a different tree representation. |
| red-black tree | A search tree with color rules that enforce a looser logarithmic height bound. |

## Anticipated student questions

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

## Sources

- [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
- [Master spiral curriculum](../Data_Structures_Course_2026_Spiral_Curriculum.md)
- [Module 12 current source](../module_12_bst_avl/student/lab.c)
- [Module 12 vocabulary reference](../module_12_bst_avl/student/vocabulary.md)
- [Module 12 lab and submission](../module_12_bst_avl/student/lab.md)
- [Models with linear equivalents](../module_12_bst_avl/diagrams/bst_avl_models.md)
