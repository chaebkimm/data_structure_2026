# Stage B — Five-Minute Cognitive Pause

Read the starting definitions with the instructor before timing begins. When
the instructor starts the timer, use no notes, slides, neighbors, or coding
tools for five minutes. You may draw, type, dictate, or answer in numbered
sentences.

An approved extended-time or asynchronous version uses the same starting
state and the same three targets. Speed, handwriting, and drawing quality are
not assessed. Preserve your first response when correction begins.

A **tree traversal** visits tree nodes in a stated order. **Preorder** means
node, left subtree, right subtree. **Inorder** means left subtree, node,
right subtree. **Postorder** means left subtree, right subtree, node.

**Recursion** occurs when a function calls itself. A **base case** stops the
repeated calls. This module uses a `NULL` subtree—no node—as its base case. A
**call frame** stores information for one active function call. **Active**
means started but not finished. Active call frames are commonly managed by
the **runtime call stack**.

An **explicit Stack** is a last-in, first-out collection directly operated by
the program. This activity lists its node pointers from bottom to top. A
pointer identifies a node’s memory address.

## Target 1 — Apply three orders

Use this tree:

```text
       12
      /  \
     5    17
    / \
   2   9
```

In linear form: root 12 has left child 5 and right child 17. Node 5 has left
child 2 and right child 9. Nodes 2, 9, and 17 have no children.

1. State the preorder keys.
2. State the inorder keys.
3. State the postorder keys.

Response:

____________________________________________________________________

## Target 2 — Explain active calls

Use the course tree:

```text
       50
      /  \
     30   70
    / \
   20 40
```

In linear form: root 50 has left child 30 and right child 70. Node 30 has
left child 20 and right child 40. Nodes 20, 40, and 70 have no children.

Recursive preorder has reached the active call for key 20.

1. What happens when the call for key 20 receives its `NULL` left subtree?
2. List the active non-`NULL` calls, oldest to newest.
3. What unfinished work must the calls for keys 30 and 50 remember?

Response:

____________________________________________________________________

## Target 3 — Trace explicit storage

Iterative left-first preorder begins by pushing the pointer to root key 50.
After a node is popped and visited, the method pushes its right child before
its left child. Missing children are not pushed.

1. After visiting 50 and pushing its children, list the Stack bottom to top.
2. After next visiting 30 and pushing its children, list the Stack bottom to
   top.
3. Explain why pushing right before left makes the left child come out next.

Response:

____________________________________________________________________
