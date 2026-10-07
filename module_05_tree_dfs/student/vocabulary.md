# Module 5 Vocabulary

These terms describe [`lab.c`](lab.c) and the slides' extension exercises.

| Term | Meaning |
| --- | --- |
| Node index | An integer selecting a slot in `nodes[10]`. |
| Child link | A left or right index; `-1` means absent. |
| Root | Starting node index of a tree or subtree. |
| Reachable node | A node reached by following links from the root. |
| `nodes_size` | Initialized or constructed node count, including unconnected alphabet entries. |
| Leaf | A node whose children are both absent. |
| Visit | Work at a node; here, assigning a character to a global. |
| Assignment trace | All assigned values in order, unlike the final global value. |
| DFS | Finish one branch before returning to another. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| Call frame | Saved state for an unfinished function call. |
| Base case | Return immediately for a negative recursive index. |
| Explicit stack | Shared `stack[10]`, holding unfinished traversal nodes or completed expression roots. |
| Progress | Per-node next step: 0 preorder, 1 inorder, 2 postorder; 3 after completion. |
| Sentinel | A special value, here `-1`, representing an absent child. |
| `top` | Last occupied stack slot; `-1` means empty. |
| Height | Maximum root-to-leaf edge count; a path has `h + 1` real nodes. |
| Reconstruction | Recovering links from traversal orders, assuming distinct labels. |
| Postfix | Operator follows its operands; the shared input is `postfix[8]`. |
| Expression tree | Digit leaves and binary operators with two children. |
| Infix | Operator is written between its operands. |
| Precedence | Priority returned by `prec()`: 1 for `+ -`, 2 for `* / %`, 0 otherwise. |
| Left associativity | Equal-precedence operators group left to right. |
| Output position | `infix_pos`, the next free character slot; final value includes the terminator. |
| Null terminator | `'\0'`, marking a C string's end. |
| Wrapper | `write_infix()`, which calls `_write_infix()` and terminates, without resetting. |
| Single-run assumption | Progress and output position start fresh and are not reset by their wrappers. |
| Capacity | Reserved space: ten nodes, stack entries, progress entries, and output characters; eight postfix characters. |
| Input assumption | A condition relied on without validation. |
| Auxiliary space | Working storage, including call frames, path stack, and progress. |

The current writer adds no parentheses. The slides' grouping rules and
repeated-run resets are extensions. Traversal and writing are linear in
reachable nodes; construction is linear in input tokens. Used path storage
is `O(h + 1)`, with separate per-node progress storage for stack traversal.
