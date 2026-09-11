# Module 2 Vocabulary — Stage B Reference

Open this page after completing and preserving the Stage A initial inquiry.
Some definitions state rules that Stage A asks you to derive.

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
| `char data` | The member storing one digit or operator character |
| child index | An integer selecting a node in the nodes array |
| `nodes[root].data` | Select the node at root, then read its data member |
| `-1` | The marker for an absent child, never an array position to access |
| `size` | The count of used nodes and the next unused array index |
| `eq` | The fixed-size array storing the expression string |
| `pos` | The index of the next unread character in eq |
| `'\0'` | The character marking the end of a C string; different from digit `'0'` |
| consume | Read a character and advance pos |
| parse | Read an expression and build the hierarchy it describes |
| term | One digit followed by zero or more multiplication-and-digit pairs |
| precedence | The priority that makes multiplication group before addition here |
| left association | Group equal operators from left to right, making each new operator a parent of the previous subtree |
| caller | The code that asks a function to run |
| precondition | A condition assumed to hold before a function runs |
| recursion | A function calling itself on a smaller part of a problem |
| base case | A case handled without another recursive call; evaluation stops at a digit |
| evaluation | Computing and returning the integer represented by a subtree |
| nonmutation | Leaving stored members and shared state unchanged during an operation |

Index 0 is valid. The digit character `'0'` is valid data and evaluates to
integer 0. The child marker -1 and string terminator `'\0'` have different
jobs. A general binary tree may have only one child, while a completed
operator in this expression model needs both operand children.
