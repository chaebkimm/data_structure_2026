# Chapter 8. Looking at Nodes Closest to the Root First

## Starting Question

> "To look at all nodes close to the root before going down to deeper nodes, in what order should we take out the waiting nodes?"

**Expected Answer:** If students say we should take out the first found node first, write it down. We will check why we need to save the depth together during the short board walkthrough.

## Why We Need This

Depth-first search follows one path to the end, so you might meet a far-away node first. This does not fit when we need to see nodes closest to the root first.

If we process the first discovered children first, we can look at all nodes at the same depth before moving down to the next depth. If we put the node's address and depth together into the queue, we don't have to calculate the depth again.

## Board Walkthrough

Draw only the top three levels of the tree from the main text.

```text
C0(42)
├─ C1(17)
│  ├─ C3(23)
│  └─ C4(91)
└─ C2(68)
   ├─ C5(17)
   └─ C6(5)

```

Write the queue from front to back order. Cover the next lines and ask first:

* Prediction 1: Right after visiting C0, what will be left in the queue?
* Prediction 2: After visiting C1, which will come out first between C2 at depth 1 and C3 at depth 2?
* Prediction 3: Right after visiting C2, what will be the order in the queue?

| Finished Visiting | Queue |
| --- | --- |
| Before start | `C0@0` |
| C0 | `C1@1, C2@1` |
| C1 | `C2@1, C3@2, C4@2` |
| C2 | `C3@2, C4@2, C5@2, C6@2` |

Check if the depth ever gets smaller (it shouldn't). Because we put the left child in first, the left node comes out first even at the same depth. Read the provided short code and just run it to see if it makes the same state.

## Common First Thoughts

* "We can just put the node address in the queue and count the depth later." But if we put the address and depth together as a pair, we don't need to go back up to count it.
* "Since C1's children were just discovered, they come out before C2." But C2 is already waiting at the front of the queue, so it comes out first.
* "A visit history is also strictly necessary for a tree." But a correct tree in this chapter has only one path to each node, so we don't need a visit history here.

## Neutral Questions

* What two values should we write in each queue item to know the current depth?
* How does C2's position in the queue change before and after putting C1's children in?
* If we swap the order of putting in the left child and right child, which part of the visit order changes?

## Vocabulary Rules

**Words we can use:** Binary tree, root, child, depth, depth-first search, queue, and First-In-First-Out (FIFO).

**Names we will introduce in this chapter:** Level, node-and-depth pair, waiting task, breadth-first search, and level-order traversal.

**Words we won't use yet:** We won't introduce the names for recording the first discovered distance and previous vertex in a graph until the next chapter. We also won't use the names from later chapters about fixing the tree's shape. Finding the shallowest value is only covered in optional activities.

## Final Check

> "Can you write the state of the queue right after visiting C2, and explain why the nodes at depth 2 could not jump ahead of C2 at depth 1?"

**Minimum Expected Answer:** Students should write the order `C3@2, C4@2, C5@2, C6@2` and explain the rule of taking out the first added item first.