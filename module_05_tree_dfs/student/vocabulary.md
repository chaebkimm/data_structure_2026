# Module 5 Vocabulary — Tree Depth-First Traversal

Open this reference after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| algorithm | A precise, repeatable set of steps |
| visit | Perform the current task at one reached node |
| visit order | The sequence in which nodes receive the visit task |
| tree traversal | An algorithm that visits tree nodes in a stated order |
| subtree | One node together with every node below it |
| depth-first search (DFS) | A method that explores one subtree as far as possible before returning to unfinished choices |
| backtrack | Return to an earlier unfinished choice |
| preorder | Visit the node, then its left subtree, then its right subtree |
| inorder | Visit the left subtree, then the node, then its right subtree |
| postorder | Visit the left subtree, then its right subtree, then the node |
| function | A named group of instructions that performs one task |
| function call | One request for a function to run |
| recursion | A function calling itself directly or through other functions |
| recursive call | A function call made as part of recursion |
| base case | An input that stops further recursive calls |
| `NULL` subtree | A missing subtree; the traversal base case that visits nothing |
| active call | A call that has started but has not yet returned |
| return | Finish one function call and continue the caller’s saved work |
| caller | The function or program part that requested another function call |
| call frame | Saved information for one active function call, including where it must resume |
| runtime call stack | Bookkeeping commonly used by a C implementation to manage active calls |
| Stack abstract data type (Stack ADT) | A collection defined by last-in, first-out access |
| explicit Stack | A Stack object created and directly operated by the program |
| iterative algorithm | An algorithm that repeats steps with a loop instead of recursive calls |
| pointer | A value that stores a memory address |
| `TreeNode *` | A pointer to one tree node |
| `const TreeNode *` | A pointer through which code may inspect, but not change, one tree node |
| TreeNode-pointer Stack | An explicit Stack whose items are `const TreeNode *` values |
| `TreeNode **` | The address of a tree-node pointer, allowing a function to replace that pointer |
| last in, first out (LIFO) | The most recently pushed item is the first item popped |
| `push` | Add one item to the top of a Stack |
| `pop` | Remove and report the top Stack item |
| bottom-to-top order | A listing that begins with the oldest Stack item and ends with the accessible top |
| data type | A description of what kind of value is stored |
| struct | A C type that groups named fields |
| field | One named value inside a struct |
| `bool` | C’s yes-or-no type, with values `true` and `false` |
| flag | A stored yes-or-no marker |
| `TreeNode` | A node containing a key, a flag, and left/right child pointers |
| `TreeVisit` | A copied key-and-flag record made during one visit |
| `TreeOrder` | An array of up to 64 visit records plus their count |
| `TREE_DFS_MAX_NODES` | The public maximum of 64 visit records |
| output parameter | Caller-provided storage in which a function writes a result |
| contract | Rules stating what a function accepts, changes, reports, and preserves |
| status code | A named result reporting success or one kind of failure |
| failure atomicity | A failed operation leaves the complete prior valid output or structure unchanged |
| dynamic allocation | Obtaining storage while a program runs |
| allocation failure | The program could not obtain requested storage |
| ownership | Responsibility for eventually releasing allocated storage |
| `free` | The low-level C operation that releases an allocation; student traversal code uses the supplied function instead |
| `tree_node_release` | The supplied function that releases one node after its children have been handled |
| `tree_destroy_postorder` | The public operation that releases a whole tree child-before-parent and resets the root to `NULL` |
| dangling pointer | An address of storage that has already been released |
| binary search tree (BST) | A binary tree whose entire left subtree has lower keys and entire right subtree has higher keys at every node |
| strict ordering | Ordering that rejects duplicate keys |
| search | A procedure for finding a requested target |
| constructor | A function that prepares a new object; here, `tree_node_create` |
| insertion baseline | Supplied starting code that adds a new key while preserving strict BST ordering |
| auxiliary space | Extra working storage used by an algorithm |
| time complexity | A description of how work grows as input grows |
| `O(n)` | Work that can grow in proportion to node count `n` |
| `O(h)` | Work or storage that can grow in proportion to tree height `h` |
| graph | A general structure of nodes and relationships that may include sharing or cycles |
| alias | Another relationship or name that reaches an already represented object |
| symbolic link | A directory entry that refers to another location |
| cycle | A route that can return to an already reached node |
| visited set | Stored marks showing which nodes have already been reached |
| synthetic | Invented for safe practice rather than taken from a real system |
| policy | A set of rules |
| directory | An organization of entries that helps locate stored items |
| `TREE_DFS_OK` | The requested operation succeeded |
| `TREE_DFS_INVALID_ARGUMENT` | A required pointer was `NULL` |
| `TREE_DFS_LIMIT` | The 64-visit limit or explicit Stack limit prevents completion |
| `TREE_DFS_ALLOCATION` | Requested node or Stack storage could not be obtained |
| `TREE_DFS_DUPLICATE` | Strict BST insertion found the requested key already present |
| `TREE_DFS_NOT_FOUND` | BST search reached a missing subtree without finding the target |

## Three uses of “stack”

- The Stack ADT is the general last-in, first-out rule.
- An explicit TreeNode-pointer Stack is a program-created use of that ADT.
- The runtime call stack is implementation bookkeeping for active calls.

These terms are related by a last-finished-first pattern, but they do not
name the same stored object.
