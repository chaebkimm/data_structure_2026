# Chapter 5. Following One Path to the End

## Starting Question

> "To go down the left path and then come back to the right path, what do we need to remember?"

**Expected Answer:** Students should explain that for every unfinished spot, we must remember the current node and the exact place to continue when we come back.

## Why We Need This

If we only remember one current node, we cannot go deep down and then return to the remaining paths. By letting each function call hold onto the unfinished spots, we can process one path all the way to the end and then come back. We give this method the name "depth-first search."

## Board Walkthrough

We will use the same tree until the end. Even if `flagged` is `false`, we still process the node.

```text
          50(false)
          ↙       ↘
    30(true)      70(true)
      ↙   ↘
20(false) 40(true)

```

When the preorder traversal reaches 20, write down the unfinished calls.

```text
50: Right 70 is left
30: Right 40 is left
20: Processing now

```

By just moving the line of code that records the node, we can make three different results.

| Traversal | Recorded Keys |
| --- | --- |
| Preorder | `50, 30, 20, 40, 70` |
| Inorder | `20, 30, 40, 50, 70` |
| Postorder | `20, 40, 30, 70, 50` |

Let's predict:

* If we record the node between the left call and the right call, what order do we get?
* After the call for 20 comes back, where does the call for 30 continue?
* If we delete the parent first, what happens to the child addresses we still need to read?

## Common First Thoughts

* "We skip nodes in the traversal if `flagged == false`."
* "The moment we record a node, its call is also finished."
* "If the traversal time is `O(n)`, the extra call space is also always `O(n)`."
* "Even if we delete the parent first, we can still read the child addresses inside it."

## Neutral Questions

* Can you separately tell me the nodes we have recorded so far and the calls that are not finished yet?
* Where is the line that records the node located compared to the two child calls?
* Right before deleting a node, what addresses do we need to read first?

## Vocabulary Rules

**Words we can use:** Binary tree, node, root, left and right child, subtree,
height, recursion, stopping case, current-node/left/right search, and stack.

**Names we will introduce in this chapter:** Tree traversal, depth-first
search, active call, call frame, running call stack, preorder, inorder,
postorder, binary-search-tree ordering, allocated-node destruction, and call
space `O(h)`. Preorder names the current-node/left/right pattern already
traced in Chapter 2; the three named orders are compared here.

**Words we won't use yet:** Graph visit history, graph depth-first search, queue, breadth-first search, or balance and rotation. Iterative preorder traversal using a separate stack is optional and should not be included in required coding or testing.

## Final Check

> "When the preorder traversal reaches 20, what do the calls for 50 and 30 remember, and why is the extra call space `O(h)`?"

**Minimum Expected Answer:** Students should say that 50 remembers the place to go back to the right 70, and 30 remembers the place to go back to the right 40. At the same time, the number of active calls grows based on the number of nodes in a single path from the root to the current node (which is related to the height `h`).
