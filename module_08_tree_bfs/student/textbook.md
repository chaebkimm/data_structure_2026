# Chapter 8. Visiting Items Starting from the Closest to the Top

## Thinking Logically

### Why is following one path to the end not enough?

The search method we used before follows one branch all the way down to a dead end. Even if there are items right near the top sitting on other branches, that method will ignore them and visit much deeper items first.

This time, we want to look at all the items exactly one step away from the top before we look at any items two steps away. We can make this order happen if we simply process the tasks in the exact order we discovered them.

### How do we check the closest items first?

We put the top item into a waiting line. Every time we take an item out of the line, we put its left child and right child at the very back of the line. Because the items that were already waiting in the line will come out before the newly added children, a deeper item can never jump ahead of a shallower item.

This naturally lets us sweep across the tree level by level, from top to bottom.

### How do we remember the distance as well?

The distance (or depth) is simply the number of connections you have to pass through from the top to reach a specific item. The distance of the top item itself is exactly 0.

If we only put the item's location into our waiting line, it's very hard to figure out its distance again when we take it out. Because of this, the waiting line in this chapter holds a package containing both the item's location and its exact distance.

```text
Put (top item, distance 0) in.

Repeat until the waiting line is empty:
    Take out the front package (current item, distance).
    Write down the current item and its distance in the final list.
    If there is a left child, put (left child, distance + 1) in.
    If there is a right child, put (right child, distance + 1) in.
```

### How do we decide the order for items at the same distance?

We strictly put the left child into the waiting line before the right child. This guarantees that two children sharing the same parent are always checked from left to right. Because the parents themselves are also checked from left to right, the entire order for everyone at the exact same distance is perfectly fixed from left to right.

The following tree is checked in the exact order: `42, 17, 68, 23, 17`. Even though the number 17 appears in two different places, they are completely separate items.

```text
        42
       /  \
     17    68
    /      /
   23     17
```

Their distances are `0, 1, 1, 2, 2`. Notice that while the process is running, the distance never goes down.

### Do we need "discovered" checkmarks like we do for free-flowing maps?

In a properly built tree, there is only one downward path to reach any item. Two parents never point downward to the exact same item, and the paths never loop back up. Therefore, as we follow the children downward, we will never accidentally put the exact same item into the waiting line twice. We don't need a separate true/false checklist to mark what we've already found!

Connections that break these rules simply do not make a tree. The tool in this chapter does not check for or fix loops, so you must give it a perfectly valid tree from the start.

### If there are multiple identical numbers, how do we find the closest one?

In a basic tree, the exact same number can appear multiple times. Because our waiting line naturally checks the closest items first, if we check the number the exact moment we take it out of the line, the very first match we find is absolutely guaranteed to be the closest one to the top!

If two matching numbers are at the exact same distance, our strict rule of putting the left child in first decides the winner. Our search tool gives back the location and the distance of the item it found. The location points to the actual item inside your tree, so you cannot use it if you delete the tree later.

### How do we find the total height of the tree?

Because we check items level by level, the distance of the very last item taken out of the waiting line is the total height of the tree. The height of a completely empty tree is mathematically considered -1, and the height of a tree with exactly one item is 0. Our height calculating tool simply tracks this value.

### What if our waiting line runs out of space?

Our code stores waiting tasks in a fixed-size line that holds up to 64 items. You get to choose the exact number of slots you want to use. If the number of waiting tasks tries to go over your chosen limit at any moment, the process safely fails and returns an error.

The final list of checked items is also strictly limited to a maximum of 64. Even if your waiting line has empty space left, arriving at a 65th item will instantly fail with an error.

A completely empty tree will successfully return an empty list even if your line limit is set to 0. However, if there is even one single item, you cannot start with a limit of 0. Whenever a failure happens, your old results are perfectly protected and never changed.

## Calculating Efficiency

### Efficiency of checking items level by level?

If there are `n` items, we put each item into the waiting line exactly once and take it out exactly once. The total amount of work is proportional to the number of items, $O(n)$.

### Efficiency of finding the closest matching number?

If you find the number right away at the very top, it finishes instantly. But if the number doesn't exist at all, or is sitting at the very bottom right, you have to look at absolutely every single item. The worst-case work is $O(n)$.

### Efficiency of calculating the tree's height?

To find the very last distance, you are forced to visit absolutely every item. The amount of work is $O(n)$.

### How much extra space is needed for the waiting line?

At any given moment, the waiting line is mostly filled with items that are sitting at the exact same distance from the top. The temporary space needed depends on how wide the tree gets. If the maximum width of the tree is `w`, the typical space needed is $O(w)$. Our specific code here strictly limits this space to a maximum of 64 slots.

## Glossary

### Depth

The number of child connections you pass through from the root to reach a specific node.

### Level

A group of nodes that all share the exact same depth.

### Breadth-First Search (BFS)

A search method that visits items in order, starting from those closest to the starting point.

### Level-Order Traversal

A Breadth-First Search that visits a tree in order from the smallest depth to the largest.

### Work Item

A package containing a node's address and its depth, waiting in the queue because it hasn't been visited yet.

### Height

The number of connections going down from a node to its farthest leaf. In this chapter, the height of the tree means the height of its root.

## Coding Plan

### Traversing Level by Level

* **Prepare result:** Build the visit result strictly in a temporary, hidden workspace, not directly in the user's output variable.
* **Put top item in:** If there is a top item, put `(root, 0)` into the waiting line.
* **Take item out:** Take the front package from the line and write its key, true/false tag, and distance into the temporary workspace.
* **Put children in:** Put the left child in first, and the right child in second.
* **Confirm result:** Keep going until the waiting line is completely empty. If it fully succeeds, cleanly copy the temporary workspace to the user's output.

### Finding the Closest Matching Key

* **Start search:** Put the top item and distance 0 into the waiting line.
* **Compare keys:** Compare the target key with the current item's key the exact moment you take the package out of the line.
* **Save result:** Write the location and distance of the very first matching item to the output.
* **Report missing:** If the line completely empties without a match, safely return a `TREE_BFS_NOT_FOUND` error.

### Calculating the Tree's Height

* **Set starting value:** Set the temporary height answer exactly to -1 so it works correctly for an empty tree.
* **Update distance:** Every single time you take out an item, save its distance as the new height answer.
* **Save result:** When the search finishes completely, write the very last saved distance to the output.

### Protecting the Result on Failure

* **Check limit:** First, make sure the requested limit is 64 or less.
* **Use temporary result:** Do not ever change the caller's result while the search is running halfway.
* **Copy after success:** Only update the final output structure after absolutely all tasks finish perfectly.

## C Code

### Making an Example Tree

```c
#include "tree_bfs.h"

TreeNode left_left = {
        .key = 23, .flagged = false,
        .left = NULL, .right = NULL
};
TreeNode right_left = {
        .key = 17, .flagged = true,
        .left = NULL, .right = NULL
};
TreeNode left = {
        .key = 17, .flagged = false,
        .left = &left_left, .right = NULL
};
TreeNode right = {
        .key = 68, .flagged = false,
        .left = &right_left, .right = NULL
};
TreeNode root = {
        .key = 42, .flagged = false,
        .left = &left, .right = &right
};
```

These example items are simply created briefly as normal variables. Because the cleanup tool `tree_destroy_postorder` from Chapter 5 only frees items built by the computer's memory allocator, do not use it on these specific variables!

### Getting the Level-Order Result

```c
TreeBfsOrder order = {0};
TreeBfsStatus status;

status = tree_level_order(&root, 2U, &order);

if (status == TREE_BFS_OK) {
        /* key: 42, 17, 68, 23, 17 */
        /* depth: 0, 1, 1, 2, 2 */
}
```

### Finding the Closest Node and Height

```c
TreeBfsMatch match = {0};
int height = -1;

if (tree_find_shallowest(&root, 17, 2U, &match) ==
    TREE_BFS_OK) {
        /* match.node points exactly to 'left', and match.depth is 1. */
}

if (tree_height_bfs(&root, 2U, &height) == TREE_BFS_OK) {
        /* height is 2. */
}
```

### The Order for Putting Children in the Waiting Line

```c
#include "tree_work_queue.h"

TreeWorkQueue queue = {0};
TreeWorkItem item = {&root, 0U};
size_t child_depth = item.depth + 1U;

tree_work_queue_init(&queue, 2U);

if (item.node->left != NULL) {
        TreeWorkItem left_item = {
                item.node->left,
                child_depth
        };
        tree_work_queue_enqueue(&queue, left_item);
}

if (item.node->right != NULL) {
        TreeWorkItem right_item = {
                item.node->right,
                child_depth
        };
        tree_work_queue_enqueue(&queue, right_item);
}
```

The actual internal code strictly checks the success of every single attempt to add an item to the line. If dropping the left child in fails because the line is full, it immediately stops, does not attempt to put the right child in, and safely throws away the temporary workspace.