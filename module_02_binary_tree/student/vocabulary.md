# Module 2 Vocabulary — Stage B Reference

Open this page after completing and preserving the Stage A initial inquiry.
Some definitions state rules that Stage A asks you to derive. The shared
tree terms below also apply to the textbook's alphabet and addition models.
The final table contains the separate precedence application lab's terms.

| Term | Plain-language definition |
|---|---|
| hierarchy | An arrangement with some items above others |
| node | One object storing a character and two child indices |
| tree | A connected hierarchy with one root, one incoming child link per other node, and no cycle |
| binary tree | A tree with at most two children per node, distinguished as left and right |
| expression tree | A tree whose operators have operand subtrees; here digits are leaves and each operator has two children |
| root | The node that gives access to a tree; this program represents it by an index |
| parent | A node directly above another node; no upward member is stored |
| child | A node directly below a parent |
| sibling | A different node with the same parent |
| leaf | A node with both child indices equal to -1; a digit in a completed expression |
| path | A sequence of nodes connected by child links |
| ancestor | An earlier node on the path from the root to another node |
| descendant | A node reached by following one or more child links downward |
| depth | The number of links from the root to a node; the root has depth zero |
| height | The greatest number of downward links to a leaf; a leaf has height zero |
| subtree | One node together with all its descendants |
| cycle | A downward route returning to a node already on that route |
| shared child | One node appearing in more than one child position |
| invariant | A rule followed by every valid state |
| representation | A chosen way to store or show information |
| `struct` | A C type that groups named members |
| `char data` | The member storing one character: a letter in the alphabet example, or a digit/operator in an expression |
| child index | An integer selecting a node in the nodes array |
| `nodes[root].data` | Select the node at root, then read its data member |
| `-1` | The marker for an absent child, never an array position to access |
| caller | The code that asks a function to run |
| precondition | A condition assumed to hold before a function runs |
| recursion | A function calling itself on a smaller part of a problem |
| base case | A case handled without another recursive call; `tree_recursion` stops outside the active index range, and `eval` stops at a digit |
| evaluation | Computing and returning the integer represented by a subtree |
| nonmutation | Leaving stored members and shared state unchanged during an operation |

## Textbook storage and construction

The classroom examples initialize nodes before connecting them. The same
array holds the alphabet tree first and the addition tree afterward.

| Term | Plain-language definition |
|---|---|
| `capacity` | The ten physically reserved node slots |
| `nodes_size` | The initialized, in-use slot count; not the number reached from one root |
| reachable node | A node accessed from the selected root by following child links; the alphabet tree reaches seven of ten initialized letters |
| operand | A value or expression used by an operator; it can be a whole subtree |
| left association | Group from left to right; `1+2+3` becomes `(1+2)+3` by making each new plus the parent of the existing tree |
| `i++` | Use the old index value, then increment it |

Index 0 is valid. The digit character `'0'` is valid data and evaluates to
integer 0. The child marker -1 and string terminator `'\0'` have different
jobs. A general binary tree may have only one child, while a completed
operator in this expression model needs both operand children.

## Application-lab parsing terms

The staged lab adds multiplication precedence and a separate 20-slot
program. Its shared parser state is not part of the textbook's classroom
interface.

| Term | Plain-language definition |
|---|---|
| `size` | The count of used nodes and the next unused array index |
| `eq` | The fixed-size array storing the expression string |
| `pos` | The index of the next unread character in eq |
| `'\0'` | The character marking the end of a C string; different from digit `'0'` |
| consume | Read a character and advance pos |
| parse | Read an expression and build the hierarchy it describes |
| term | One digit followed by zero or more multiplication-and-digit pairs |
| precedence | The priority that makes multiplication group before addition here |
