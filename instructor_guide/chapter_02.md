# Chapter 2. Making a Hierarchy with Addresses

## Starting Question

> "How can we show the up-and-down relationship of items using just a single-line array?"

**Expected Answer:** Students should explain that the addresses saved inside each item decide the relationship, not their side-by-side position in the array.

## Why We Need This

The list in Chapter 1 lines up values in a single row. A shape where one item is placed under another—like an organization chart or computer folders—cannot be shown with just one line. Each item needs to remember the address of the item below it. We also have to check the overall shape made by these addresses. Here, we introduce the name "binary tree."

## Board Walkthrough

First, just show a fixed array with five keys.

| Array Position | 0 | 1 | 2 | 3 | 4 |
| --- | --- | --- | --- | --- | --- |
| Key | 50 | 30 | 70 | 20 | 40 |

Next, connect the saved addresses step by step.

```text
root → 50
50.left → 30, 50.right → 70
30.left → 20, 30.right → 40
```

The completed shape looks like this:

```text
       50
      ↙  ↘
    30    70
   ↙  ↘
 20    40
```

Let's predict:

* When 20 and 40 are next to each other in the array, what decides the relationship between these two nodes?
* If we change `20.left` to point to 50, what kind of path is created along the addresses?
* If we change the key of 40 to 60, what happens to its relationship with the root 50?

## Common First Thoughts

* "Two nodes next to each other in the array are automatically parent and child."
* "If setting one child address is successful, the finished tree is also correct."
* "If a key's rule is correct with just its direct parent, it is a binary search tree."
* "It is okay to separately `free` (delete) a single node inside an arena."

## Neutral Questions

* Where is the information that decides the parent and child relationship?
* After looking at just one connection, what overall condition have we not checked yet?
* Can you explain the correct position of key 60 by comparing it step by step starting from the root?

## Vocabulary Rules

**Words we can use:** Array-based list, address, pointer, ownership, and valid shape conditions.

**Names we will introduce in this chapter:** Hierarchy, node, root, parent, child, ancestor, leaf, path, depth, height, subtree, binary tree, arena, reachable node, cycle, partial check, overall check, and binary search tree.

**Words we won't use yet:** Depth-first search, recursive calls, graph vertices and edges, or balance and rotation.

## Final Check

> "Even if every `tree_assign_child` call is successful, why do we still need `tree_validate_structure`?"

**Minimum Expected Answer:** Students should say that checking single connections one by one cannot catch overall problems—like a node having two parents, a long endless loop (cycle), or a node that cannot be reached from the root.