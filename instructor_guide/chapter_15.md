# Chapter 15. Fixing a Search Tree that Collapses to One Side

## Starting Question

> "If putting in the exact same keys makes the search tree become a single line because of the order they arrived, how can we fix its shape while keeping the sorting rule?"

**Expected Answer:** Students should say that we must compare the longest lengths of the two sides, and change the links only at the spot where the difference gets too big to return it to a shorter shape.

## Why We Need This

A binary search tree's sorting rule only decides the direction of the search. If we put in numbers from `1` to `15` in order, it becomes a single line with a height of 14. We can keep the search path short only if we limit the height difference between the two subtrees and fix the links after putting a new value in.

A search tree that keeps the height difference of all its nodes strictly to `-1`, `0`, or `1` is called an "AVL tree." The action of fixing only the shape using links while leaving the sorting order exactly as it is, is called a "rotation."

In week 13, we cover height, balance difference, rotation, and AVL insertion and checking. We do not code AVL deletion.

## Board Walkthrough

We count height by the number of edges.

```text
height(NULL) = -1
height(leaf) = 0
balance difference = left height - right height

```

Put in `30, 10, 20` in order.

```text
    30
   /
 10
   \
    20

```

We do a left rotation at 10, and then a right rotation at 30.

```text
    20
   /  \
 10    30

```

Write down the two directions taken from the node where the balance was first broken, going down to the new key. `L` stands for left and `R` stands for right. The final shape for all four of these inputs is the same.

```text
30, 20, 10  LL  Right rotation
10, 20, 30  RR  Left rotation
30, 10, 20  LR  Left rotation then right rotation
10, 30, 20  RL  Right rotation then left rotation

```

Ask these questions before changing the state:

* Right after putting in 20, which node is the first one to go out of the safe balance range?
* In `30, 10, 20`, what is the root of the subtree that must be rotated first?
* After a rotation, from which node do we calculate the height again?

## Common First Thoughts

* "If we just follow the binary search tree rule, the height will automatically be short."
* "There are four completely different basic rotations for the four imbalances." (There are only left and right; LR and RL just use them twice).
* "If we rotate, the in-order traversal (the sorted order) changes too."
* "We fix the height of the new subtree root before fixing the nodes below it."

## Neutral Questions

* What are the left and right heights of the current node right now?
* What is the address of the middle subtree that we need to safely save before rotating?
* After changing the links, how do we check the in-order traversal and the saved height?

## Vocabulary Rules

**Words we can use:** Binary search tree, subtree, height counted by edges, in-order traversal, and recursive call.

**Names we will introduce in this chapter:** Balance difference (balance factor), AVL tree, rotation, left rotation, right rotation, LL, RR, LR, and RL.

**Words we won't use yet:** AVL deletion, other balanced search trees, or advanced features that change many actions at once.

## Final Check

> "After putting in `30, 10, 20`, why do we need to rotate twice, and what must stay exactly the same?"

**Minimum Expected Answer:** Students should mention the LR shape, the specific order of the two rotations, and that the in-order sorting rule and height conditions must remain correct.