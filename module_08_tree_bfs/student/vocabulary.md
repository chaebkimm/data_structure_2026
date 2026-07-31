# Module 8 Vocabulary

Use this page after Stage A. Keep it closed during the Cognitive Pause until
all three target responses are preserved.

| Term | Working definition |
|---|---|
| algorithm | A precise, repeatable set of steps |
| traversal | A planned procedure for visiting nodes |
| breadth-first search (BFS) | A method that visits smaller depths before larger depths |
| level order | Tree BFS order, grouped by equal depth |
| depth | Number of child links from the root to a node |
| level | All nodes at one depth |
| Queue | A collection that removes the earliest-added waiting item first |
| discovered | Reached and placed in the waiting Queue |
| frontier | Discovered nodes waiting to be visited |
| work record | One waiting node pointer paired with its depth |
| shallowest | Having the smallest depth |
| left-first tie | Choosing the left-discovered match first when matching nodes have equal depth |
| width | Number of nodes at one level |
| maximum width (`w`) | Greatest level width in the tree |
| edge height (`h`) | Greatest downward-link count from a node to a leaf |
| auxiliary space | Temporary working storage separate from input and output |
| time complexity | A description of how work grows with input size |
| `O(n)` | Work grows in proportion to the number `n` of nodes |
| `O(w)` | Working space grows in proportion to maximum width |
| `O(h)` | Working space grows in proportion to tree height |
| balance factor | Left-child height minus right-child height |
| rotation | A small link rearrangement that preserves binary-search order |
| subtree | One node together with everything below it |
| binary search tree (BST) | A binary tree with lower keys throughout each left subtree and higher keys throughout each right subtree |
| strict BST | A BST that rejects equal keys |
| AVL tree | A BST kept within balance factors -1 through 1 |
| visited record | A stored mark saying an item was reached before |
| contract | What a function accepts, changes, reports, and preserves |
| status code | A named result reporting success or one kind of failure |
| failure preservation | A failed operation leaves caller output unchanged |
| nonmutation | Inspecting an input without changing it |
| ownership | Responsibility for releasing requested storage |
| allocation | Storage requested while a program runs |
| valid course tree | An acyclic, unshared tree in which each nonroot node has one parent |
