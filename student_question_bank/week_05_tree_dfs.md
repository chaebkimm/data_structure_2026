# Week 5 — Tree DFS and Expression Trees: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

Lecture scope: trace the current array-based [`lab.c`](../module_05_tree_dfs/student/lab.c),
explain its three recursive visit positions, construct expression trees
from postfix, and write infix with parentheses and a complete C string.
Use the [textbook](../module_05_tree_dfs/student/textbook.md),
[vocabulary](../module_05_tree_dfs/student/vocabulary.md), and
[lecture demo](../module_05_tree_dfs/code/lecture/lab_demo.c).

## Vocabulary students will learn

| Term | Working meaning |
| --- | --- |
| Node index | An integer selecting a slot in `nodes[10]`. |
| Root | The starting index for a tree or subtree. |
| Absent child | A child link containing `-1`. |
| Reachable node | An entry reached by following links from the chosen root. |
| Visit | Work at a reached node; here, assigning a character to a global. |
| Assignment trace | The sequence of assigned values, which a single final variable does not retain. |
| Depth-first search | Finish one branch before returning to another. |
| Preorder | Current node, left subtree, right subtree. |
| Inorder | Left subtree, current node, right subtree. |
| Postorder | Left subtree, right subtree, current node. |
| Active call | A call that has started but has not returned. |
| Call frame | One active call's saved state and continuation. |
| Runtime call stack | Storage used to remember unfinished calls. |
| Height (`h`) | Maximum number of edges from root to leaf; a deepest path has `h + 1` nodes. |
| Explicit stack | `eq_tree()`'s array of completed subexpression root indices. |
| Postfix | Place each binary operator after its operands. |
| Expression tree | Digit leaves joined by binary operator nodes. |
| Infix | Place each binary operator between its operands. |
| Precedence | Priority that determines grouping among operator levels. |
| Left associativity | Group equal-precedence operators from left to right. |
| Output position | Next character slot during writing; the final `pos` includes the terminator. |
| Null terminator | `'\0'`, the end marker for a C string. |
| Wrapper | `start_write_infix()`, which resets, invokes the writer, and terminates. |
| Capacity | Reserved array space, including room for a string's terminator. |
| Input assumption | A condition the code relies on without validating it. |

## Anticipated student questions

### Representation and visits

- Why do `left`, `right`, and a root hold integers while `data` holds a character?
- Why does `tree_connect()` return 5, and why is `size` 10 when only seven
  alphabet nodes are reachable?
- Does changing a child index move any node in the array?
- How do the three assignment positions produce preorder, inorder, and postorder?
- Why do the globals end as `G`, `G`, and `F` instead of containing complete sequences?
- Why does a parent skip `-1`, and why is `tree_traversal(-1)` unsupported?
- What assumptions about valid indices, cycles, and multiple parents make this recursion work?

### Calls and storage

- What work is saved in the calls for `F`, `A`, and `B` while `D` is active?
- If height counts edges, why is the maximum number of active node calls `h + 1`?
- Why does traversal take `O(n)` time for `n` reachable nodes?
- Why do traversal and writing use `O(h + 1)` call-stack space?
- How do the runtime call stack and `eq_tree()`'s explicit stack differ?
- What is the difference between reserved capacity and the number of slots currently used?

### Constructing the expression

- Why does input position `i` become node index `i` in `eq_tree()`?
- What subtree does each stack entry represent after every token of `123*+`?
- Why is the first popped root the right child? What would reversal do to `12-`?
- Why is `size` 5 while `top` is 0 at the end of the default construction?
- Why do digits remain characters rather than being converted with `c - '0'`?
- Does construction evaluate the expression, and what happens to the previous alphabet tree?
- Why must every operator have two available roots and the final stack have exactly one root?
- Which assumptions permit `eq_tree()` to omit validation? Are empty input, spaces,
  multidigit operands, and unary operators within that contract?

### Writing infix

- Why do `123*+` and `12+3*` need different infix strings despite the same
  unparenthesized inorder symbols?
- Why are the parentheses conditions `>` on the left and `>=` on the right?
- What distinguishes the grouping of `12-3-` and `123--`?
- Why does `123++` become `1+(2+3)` even when arithmetic simplification is possible?
- How are `/` and `%` handled by the same precedence rules?
- Why does giving digits precedence 3 avoid unnecessary parentheses?
- Does `prec()` returning 0 make an unsupported token valid?
- Why can the alphabet tree be traversed but not passed to the infix writer?

### Wrapper, bounds, and observation

- Why must a complete formatting operation start with `start_write_infix()`?
- What would resetting `pos` inside every recursive call do to the output?
- Why are both the reset and `'\0'` needed when a shorter expression replaces a longer one?
- Why does the final `pos` include the terminator?
- How do five input tokens imply at most two operators and one added pair of parentheses?
- Why do eight characters suffice under the current input limit, and why does
  that not guarantee every larger tree fitting `nodes[10]` fits `infix[10]`?
- How can a trace or debugger show full assignment sequences that the demo's
  `Last visits` line cannot show?
- Which valid examples distinguish left parentheses, right parentheses,
  repeated formatting, and replacement by a shorter string?

### Transfer and optional extensions

- How does Chapter 4's value stack become a stack of subtree roots here?
- Why will graph DFS need visited state when a valid tree has no cycles or shared children?
- How would increasing input capacity change the node, stack, and output capacity analysis?
- What additional checks would a generalized builder need before accepting untrusted input?
- How could an explicit stack reproduce the same visit order as recursion?

The lecture uses well-formed, nonempty postfix strings of at most five
single-character tokens: digits and binary `+`, `-`, `*`, `/`, or `%`, with
no spaces. Extensions to validation, input size, or traversal implementation
are discussion topics beyond the current lab's behavior.
