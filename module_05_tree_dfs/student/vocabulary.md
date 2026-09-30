# Module 5 Vocabulary

These terms describe the array-based implementation in [`lab.c`](lab.c).

| Term | Meaning in this lab |
| --- | --- |
| Node index | An integer selecting an entry in `nodes[10]`. |
| Child link | A `left` or `right` index; `-1` marks an absent child. |
| Root | The valid starting index for a tree or subtree. |
| Leaf | A node whose left and right child indices are both `-1`. |
| Reachable node | A node that can be followed from the supplied root through child links. |
| `size` | The initialized or constructed node count; after alphabet initialization it includes three entries unreachable from root 5. |
| Tree traversal | Processing every node reachable from a valid tree root in a chosen order. |
| Visit | The selected action at a node; here, assigning its character to a global variable. |
| Assignment trace | All values assigned in order; different from a variable's final stored value. |
| Depth-first search (DFS) | Finishing one branch before returning to another. |
| Recursion | A function calling itself on a smaller part of its task. |
| Stopping case | Work completed without another recursive call; leaves make no child calls. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| Active call | A call that has started but has not returned. |
| Call frame | Saved state for one active call, including its node index and where it will resume. |
| Runtime call stack | Storage for unfinished function calls, managed by the runtime. |
| Tree height (`h`) | The maximum number of edges from root to leaf; a deepest path has `h + 1` node calls. |
| Explicit stack | The local `stack[10]` in `eq_tree()`, holding indices of completed subexpression roots. |
| `top` | The index of the last occupied explicit-stack slot; `-1` means empty and `top + 1` counts entries. |
| Postfix | Notation placing an operator after its two operands, as in `12+`. |
| Expression tree | Digit leaves joined by supported binary operator nodes, each with two children. |
| Infix | Notation placing an operator between operands, as in `1+2`. |
| Precedence | Priority used to decide grouping between operators at different levels. |
| Left associativity | Grouping equal-precedence operators from left to right. |
| Output position (`pos`) | The next character slot during writing; after the wrapper returns it also counts the terminator. |
| Null terminator (`'\0'`) | The character marking the end of a C string. |
| Wrapper | `start_write_infix()`, which prepares and finishes the work around the recursive writer. |
| Input assumption | A condition the code relies on without checking, such as a nonempty valid postfix string fitting `post_eq[6]`. |
| Capacity | Reserved space: ten nodes, ten explicit-stack entries, six input characters, and ten output characters. |
| Auxiliary space | Temporary working storage, such as the explicit stack and active recursive calls. |

For `n` reachable nodes, traversal and formatting take `O(n)` time. For
`t` input tokens, construction takes `O(t)` time. Recursion uses
`O(h + 1)` call-stack space when height counts edges. The lab's arrays
reserve fixed storage; a builder generalized to growing inputs may need
`O(t)` explicit-stack entries.
