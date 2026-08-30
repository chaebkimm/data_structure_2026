# Module 2 Vocabulary — Stage B Reference

Open this page after completing and preserving the Stage A initial inquiry.
Some definitions state rules that Stage A asks you to derive.

| Term | Plain-language definition |
|---|---|
| hierarchy | An arrangement in levels, with some items above others |
| node | One object that stores data and links to related nodes |
| tree | An empty structure, or one connected hierarchy with a root, one incoming link per other node, and no cycle |
| binary tree | A tree with distinct left and right child positions at each node |
| expression tree | A tree that represents an expression; in this chapter's completed examples, operators have two operand children and numbers are leaves |
| root | The starting node chosen by the caller |
| parent | A node directly above another node; this relationship is not stored in an upward field |
| child | A node directly below another node |
| sibling | A different node with the same parent |
| leaf | A node whose left and right links are both `NULL` |
| path | A sequence of nodes connected by links |
| ancestor | An earlier node on the path from the root to another node |
| descendant | A node reached by following one or more child links downward |
| depth | The number of links from the root to a node; the root has depth zero |
| height | The greatest number of downward links from a node to a leaf; a leaf has height zero |
| subtree | One node together with all its descendants |
| cycle | A route that returns to a node already on that route |
| sharing | More than one incoming link to the same node, including both sides of one parent |
| invariant | A rule followed by every valid state |
| representation | A chosen way to store or show information |
| object | A stored item that groups related values |
| `struct` | A C type that groups named fields |
| field | One named value inside a struct |
| address | A value identifying a location in memory |
| pointer | A variable that stores an address |
| `&node` | The address of the variable named `node` |
| `node.data` | The data field of a node variable |
| `link->data` | The data field reached through a node pointer |
| `NULL` | A pointer value meaning that no node is linked at that position |
| local variable | A variable declared within a function or block |
| lifetime | The time during which an object exists and its address remains usable |
| dangling pointer | A pointer to an object whose lifetime has ended |
| caller | The code that asks a function to run |
| precondition | A condition the caller must ensure before an operation |
| recursion | A function calling itself on a smaller part of a problem |
| base case | A case handled without another recursive call |
| search order | Check the current node, then its left subtree, then its right subtree |
| clearing | Resetting node data to zero and child links to `NULL` while the objects remain alive |
| detaching | Removing the incoming link from a parent to a child |
| cascading clearance | Clearing every node in a selected subtree |

The values do not determine the sides. A right-only child is valid in a
general binary tree, even though it is not a completed binary operator. The
`int` data field stores both numbers and portable C character constants such
as `'*'` and `'+'`. Clearing a live node does not make zero a special
“missing node” value.
