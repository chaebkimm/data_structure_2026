# Module 2 Vocabulary — Stage B Reference

Open this page after completing and preserving the Stage A initial inquiry.
Some definitions state the exact rules that Stage A asks you to derive.

| Term | Plain-language definition |
|---|---|
| hierarchy | An arrangement in levels, with some items above other items |
| relationship | A stated connection between two items |
| immediate relationship | A connection with no item between the two items |
| node | One item in a tree or tree-like arrangement |
| tree | An empty structure, or a hierarchy with one starting node, exactly one parent for every other node, a route from the start to every node, and no route that loops back |
| binary tree | A tree in which each node has at most two child positions |
| root | The one starting node; it has no parent |
| parent | The node directly above another node |
| child | The node directly below another node |
| leaf | A node with no children |
| path | A sequence of nodes connected by relationships |
| ancestor | A node above another node on a path |
| descendant | A node below another node on a path |
| depth | The number of links from the root to a node |
| height | The greatest number of downward links from a node to a leaf |
| subtree | One node together with everything below it |
| reachable | Able to be arrived at by following links from the root |
| cycle | A route that follows links and returns to an earlier node on that route |
| state | The values and relationships currently stored by a program |
| invariant | A rule that must be true in every valid state |
| structurally valid | Following every required rule about how tree nodes are connected |
| malformed | Breaking at least one required rule about how tree nodes are connected |
| representation | A chosen way to store or show information |
| object | One stored item that groups related values |
| C | The programming language used in this course |
| type | A description of the kind of value C stores |
| variable | Named storage for a value |
| computer memory | Working storage in which a running program keeps values |
| array | A numbered row of matching objects |
| index | An array position; C begins numbering at zero |
| field | One named value inside a grouped object |
| key | A value used to identify or compare a node |
| address | A value identifying a location in computer memory |
| pointer | A variable that stores an address |
| `NULL` | A pointer value meaning “no object here” |
| arena | A prepared storage area from which a program uses objects |
| fixed arena | An arena whose size does not change during the activity |
| ownership | Responsibility for deciding how long storage remains usable and when it is released |
| local validation | Checking one object and its immediate relationships |
| global validation | Checking the entire structure |
| binary search tree (BST) | A binary tree in which every left-subtree key is smaller and every right-subtree key is larger at every node |
| duplicate key | A key equal to one already present; this course rejects it |
| status code | A named result that reports success or a kind of failure |
| `TREE_ERR_INVALID_STRUCTURE` | The result for a malformed tree shape |
| `TREE_ERR_NOT_BST` | The result for a valid tree shape whose keys break BST ordering or the no-duplicate rule |
| graph | A general relationship structure that may allow sharing or cycles |
| vertex | One object in a graph |
| edge | One relationship in a graph |
