# Module 5 Vocabulary

These terms describe [`lab.c`](lab.c) and [the lab slides](ppt_lab_material.md).

| Term | Meaning |
| --- | --- |
| Node index | An integer selecting a slot in `nodes[10]`. |
| Child link | A left or right index; `-1` means absent. |
| Root | Starting node index of a tree or subtree. |
| Reachable node | A node reached by following links from the root. |
| `nodes_size` | Initialized or constructed node count, including unconnected alphabet entries. |
| Leaf | A node whose children are both absent. |
| Visit hook | A marked position where a node-processing action can be placed; the traversal source currently contains comments there. |
| Visit trace | Symbols recorded at successive visits; one overwritten value would keep only the last symbol. |
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
| Postfix | Operator follows its operands; the shared input is `postfix[8]`. |
| Expression tree | Digit leaves and binary operators with two children. |
| Infix | Operator is written between its operands. |
| Precedence | `prec()` returns 1 for `+ -`, 2 for `* / %`, 0 otherwise; `prec2()` returns 3 for digits and delegates other characters to `prec()`. |
| Left associativity | Equal-precedence operators group left to right. |
| Output position | `infix_pos`, the next free character slot; final value includes the terminator. |
| Null terminator | `'\0'`, marking a C string's end. |
| Wrapper | `write_infix()`, which resets the cursor, calls `_write_infix()`, then appends the terminator. |
| Traversal reset | Reset `progress` before another stack traversal; the traversal wrapper resets `top` only. |
| Capacity | Ten node, stack, and progress slots; twenty output characters; eight postfix characters. |
| Input assumption | A condition relied on without validation. |
| Auxiliary space | Working storage, including call frames, path stack, and progress. |
| Reconstruction | Optional recovery of links from traversal orders, assuming distinct labels. |

The current writer implements grouping parentheses and resets its position
for every complete write. Traversal and writing are linear in reachable
nodes; construction is linear in tokens. Used path storage is `O(h + 1)`,
with separate per-node progress storage for stack traversal.
