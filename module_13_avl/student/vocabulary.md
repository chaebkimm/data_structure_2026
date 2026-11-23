# Module 12 Vocabulary

- **Algorithmic-complexity denial of service:** valid chosen input forces
  substantially more work; a plain BST chain is this module's model.
- **AVL tree:** a BST with exact stored heights and balance factors -1,
  0, or 1 at every node.
- **Assertion:** a check in a test that must be true.
- **Balance factor:** left-subtree height minus right-subtree height;
  `get_balance(l,r)` reads the two child IDs.
- **Binary Heap:** a tree-shaped priority structure with a parent-priority
  rule, without whole-subtree search order.
- **Binary search tree (BST):** a binary tree ordered by whole subtrees.
  For this lab, left keys are at most the node key and right keys at least
  it; repeated keys are allowed in separate nodes.
- **Child:** a node directly below another node.
- **Comparison count:** one comparison per visited record in a search;
  the missing link itself adds no comparison.
- **Edge height:** links on a longest downward route; missing subtree -1,
  leaf 0.
- **Fresh node:** a valid unused ID whose key is loaded and child links
  are both -1 before insertion.
- **Index / node ID:** an integer position in `nodes[10]`, from 0 to 9;
  it identifies a record, not its ordering value.
- **Inorder traversal:** left subtree, current node, right subtree.
- **Invariant:** a rule that holds for each valid state.
- **Key:** `nodes[i].data`, the `char` value used to choose a branch.
- **Leaf:** a node whose left and right links are both -1.
- **Local root:** the starting ID of one subtree, which a rotation may
  replace even when the tree's other parts remain connected.
- **Memory corruption:** an invalid memory read or write; shape-based
  slowdown alone does not demonstrate it.
- **Middle subtree:** a subtree between the rotated keys in sorted order,
  whose link moves to the former root.
- **Nondecreasing:** each next value is at least the previous one;
  equality is allowed.
- **Precondition:** a rule the caller must satisfy before an operation.
- **Recursion:** a function calls itself on a smaller problem.
- **Regression test:** a test for a defect that has already been fixed.
- **Relink:** replace an integer child link with another node ID.
- **Resource exhaustion:** consuming a limited resource until it is used up.
- **Root:** the first node of a tree or subtree; -1 for an empty tree.
- **Rotation:** a local relinking that preserves inorder order.
- **Sanitizer:** a runtime checker for defects such as invalid memory access.
- **Stored height:** an edge height saved in the separate `height[10]`
  array; it must agree with a measurement made from the actual links.
- **Subtree:** a node and all nodes reachable below it.
- **Validator:** diagnostic test support that independently checks tree
  rules; the supplied lab itself exports no validator API.

LL and RR name one geometric rotation each. LR and RL name double
rotations; this lab expresses each using one direct helper. The separate
optional pointer library has different interfaces and a unique-key policy.
