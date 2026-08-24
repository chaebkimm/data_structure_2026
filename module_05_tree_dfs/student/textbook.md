# Chapter 5. Following One Branch to the End

## Thinking Logically

### How do we remember the remaining branches while going down one path?

Imagine we want to read every single item in a tree exactly once. If we start at the very top and decide to travel down the left path, we must temporarily memorize the right path so we can explore it later. The deeper we travel down the left side, the more right-side branches we have to memorize to come back to.

Following one continuous path all the way down until it hits a dead end, and *then* returning to check the branches we skipped, is a specific style of searching. Every time you move down to a lower level, you simply need to remember the item you are currently at and which path to take next.

### What happens if we give the exact same task to the next level?

The job we do at our current item looks exactly the same as the job we need to do for the items below it. If a set of instructions simply tells the computer to run *those exact same instructions again* for the next level down, it perfectly handles this repeating pattern.

```text
read_item(current item):
    If there is no item here, just stop and go back.
    Write down the information for this item.
    Run read_item on the left path.
    Run read_item on the right path.
```

The simple rule to stop and go back when there is no item is an incredibly important stopping condition so the process doesn't run forever. When the computer jumps to the left path, it safely sets aside the unfinished instructions. It perfectly remembers where it was and exactly what line to run next when it eventually comes back to finish the right path.

### What changes depending on when we write down the information?

We will always visit the current item, the left path, and the right path. However, simply changing *when* we write down the information from the current item creates three completely different reading orders.

```text
          50
          / \
        30   70
       /  \
     20    40
```

* **Write First:** Write down the current item, then check left, then check right. (Order: `50, 30, 20, 40, 70`)
* **Write in the Middle:** Check left, write down the current item, then check right. (Order: `20, 30, 40, 50, 70`)
* **Write Last:** Check left, check right, and only write down the current item at the very end. (Order: `20, 40, 30, 70, 50`)

In this chapter, our items contain a number and a simple true/false tag. Our reading process will visit every item and copy both pieces of information to a final list, no matter what the tag says.

### Where do we save the final list?

To avoid accidentally changing the original tree, we copy the information we read into a separate, safe list. In our setup, this list can hold a maximum of exactly 64 records.

```c
typedef struct {
    int key;
    bool flagged;
} TreeVisit;

typedef struct {
    TreeVisit items[TREE_DFS_MAX_NODES];
    size_t count;
} TreeOrder;
```

If we are given an empty tree, we successfully return an empty list. But if we try to read a 65th item, the process completely fails and triggers an error. Even if we aren't planning to *write down* that item until later, we check if we have hit the 64 limit the very moment we arrive at it.

We build our final list in a temporary, hidden workspace first. We only copy it out for the user to see if the entire reading process finishes perfectly. This way, if it fails halfway through, it doesn't leave the user with a broken, half-finished list.

Our instructions assume the tree is built correctly—meaning there are no circles looping back around, and two different items never connect downward to the exact same item. A broken tree might cause the computer to get stuck in an endless loop.

### Can we create the same order without repeating the instructions?

We can recreate the "Write First" order using a normal repeating loop by creating our own temporary container to hold the locations of the items we need to check later.

We take an item out of our container, write its information down, drop its right path into the container *first*, and then drop its left path in *last*. Because the left path went in last, it will be sitting on top, meaning it will be the very first one we take out next.

```text
After checking 50: 70 is waiting, 30 is waiting
After checking 30: 70 is waiting, 40 is waiting, 20 is waiting
After checking 20: 70 is waiting, 40 is waiting
After checking 40: 70 is waiting
After checking 70: Container is empty
```

This temporary container only owns its own memory space. It does not own the actual tree items themselves. If the container runs out of room while trying to hold locations, the process fails safely without ruining the existing output.

### How do we build a tree without knowing the total number of items in advance?

We can ask the computer for memory space to build one single item at the exact moment we need it. We save the number and the tag, and create an item with empty left and right connections. Once we successfully attach this new item to the tree, the tree becomes its owner.

When attaching a new item, we follow strict sorting rules: smaller numbers must always go to the left, and larger numbers must always go to the right. If we try to add a number that already exists, or if the computer refuses to give us memory for the new item, we safely leave the tree exactly as it was.

### Do we have to read all the items to find a specific number?

Because of our strict sorting rules, we never have to read everything. By comparing the number we are looking for with the number in our current item, we instantly know which single path to follow.

```text
Finding 40: 50 → 30 → 40 → Success
Finding 35: 50 → 30 → 40 → Empty space → Not found
```

If we successfully find the number, we give back the location of that item. If we hit an empty space without finding it, we return a "not found" error and leave the user's variables exactly as they were.

### In what order should we clean up the items?

Since the tree owns the items we created, we have to clean them up properly. You should never use this cleanup process on items that weren't created one by one by the computer's memory allocator.

If you delete a parent item first, the connections to its children are destroyed, and you can no longer find them to clean them up! You must completely clean up both the left and right children *before* you delete the parent item. This perfectly matches the "Write Last" order we learned earlier.

After everything is deleted, we change the starting point of the tree to empty. Cleaning up an already empty tree is also considered a success. This cleanup process doesn't have a 64-item limit, but if the tree is incredibly deep, the computer's background memory for holding the set-aside instructions might run out of space.

## Calculating Efficiency

### How long does it take to read all the items?

Since the "Write First", "Write in the Middle", and "Write Last" methods all visit every single item exactly once, the time it takes grows steadily based on the total number of items. If there are `n` items, the time is `O(n)`.

### How much extra space is needed while reading?

If the tree is `h` levels deep, the maximum number of paths we have to memorize at one time is `h + 1`. This means the extra memory space needed grows based on the depth of the tree, `O(h)`. If a tree is completely unbalanced and leans entirely to one single side, the depth `h` could be almost as large as the total number of items.

### How long does it take to find a single number?

Because the search follows one single downward path, the time depends entirely on the depth of the tree, taking `O(h)` time. A nicely balanced tree keeps this path very short, but a poorly built tree leaning entirely to one side can make the search take as long as `O(n)`.

### How long does it take to delete the entire tree?

Because every single item must be deleted exactly once, it takes `O(n)` time, and requires `O(h)` extra memory space to remember the return paths.

## Glossary

### Tree Traversal

A procedure that processes every node in a tree exactly once according to a specific order.

### Depth-First Search (DFS)

A search method that follows one branch all the way to the end before returning to check the remaining branches.

### Recursion

A technique where a function calls itself while it is running.

### Base Case

An input condition that makes the function return without making any more recursive calls.

### Call Frame

Information stored in memory that holds the local values of an unfinished function call and the exact location to return to.

### Preorder Traversal

A traversal that processes the current node *before* its two subtrees (Write First).

### Inorder Traversal

A traversal that processes the current node *between* its left and right subtrees (Write in the Middle).

### Postorder Traversal

A traversal that processes the current node *after* its two subtrees (Write Last).

### Binary Search Tree (BST)

A binary tree that keeps smaller keys on the left, larger keys on the right, and does not allow duplicate keys.

## Coding Plan

### Recursive Traversal (Repeating Instructions)

* **Stop:** If the node is empty (`NULL`), succeed and return.
* **Limit:** Check the 64-node limit the instant you arrive at a node.
* **Progress:** Arrange the data-saving step and the two child calls according to your desired order (Preorder, Inorder, or Postorder).
* **Complete:** Only copy the temporary workspace result to the final output after the entire process finishes perfectly.

### Iterative Preorder Traversal (Using a Container)

* **Start:** An empty tree succeeds immediately; otherwise, put the starting address into the container.
* **Loop:** Take an address out of the container and save its data.
* **Reserve:** Put the right child in first, and the left child in last.
* **Clean up:** Free the container's memory whether the process succeeds or fails.

### Creating and Inserting Nodes into a BST

* **Create:** Save the key and the tag, and set both child addresses to empty (`NULL`).
* **Compare:** Go left if the key is smaller, or right if it is larger.
* **Connect:** Only attach the new node after finding an empty spot.
* **Fail:** Leave the original tree alone if the key already exists or if the computer refuses to give memory.

### Searching in a BST

* **Compare:** If the target is smaller than the current key, go left. If larger, go right.
* **Success:** If you find the exact matching key, give back that node's address.
* **Fail:** If you hit an empty spot (`NULL`), do not change the user's existing output variable.

### Freeing the Entire Tree

* **Go Down:** Travel down to free the left and right children first.
* **Free:** Delete the current node's memory only after both of its children are completely gone.
* **Finish:** Change the starting root to empty (`NULL`) when all deleting is complete.

## C Code

### How do we build a tree with dynamic nodes?

```c
TreeNode *root = NULL;

if (tree_bst_insert(&root, 50, false) != TREE_DFS_OK ||
    tree_bst_insert(&root, 30, true) != TREE_DFS_OK ||
    tree_bst_insert(&root, 70, true) != TREE_DFS_OK ||
    tree_bst_insert(&root, 20, false) != TREE_DFS_OK ||
    tree_bst_insert(&root, 40, true) != TREE_DFS_OK) {
    tree_destroy_postorder(&root);
    return 1;
}

```

### How do we write a Preorder Traversal?

```c
static TreeDfsStatus preorder_fill(
    const TreeNode *node,
    TreeOrder *order
)
{
    TreeDfsStatus status;

    if (node == NULL) {
        return TREE_DFS_OK;
    }
    if (order->count == TREE_DFS_MAX_NODES) {
        return TREE_DFS_LIMIT;
    }

    order->items[order->count].key = node->key;
    order->items[order->count].flagged = node->flagged;
    order->count += 1U;

    status = preorder_fill(node->left, order);
    if (status != TREE_DFS_OK) {
        return status;
    }
    return preorder_fill(node->right, order);
}

TreeDfsStatus tree_preorder_recursive(
    const TreeNode *root,
    TreeOrder *out_order
)
{
    TreeOrder candidate = {0};
    TreeDfsStatus status;

    if (out_order == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    status = preorder_fill(root, &candidate);
    if (status == TREE_DFS_OK) {
        *out_order = candidate;
    }
    return status;
}
```

Inorder traversal simply moves the data-saving step below the left call, and Postorder traversal moves it below both child calls. Both functions still check the 64-visit limit the moment they arrive at a node, preventing a 65th visit.

### How do we keep the order in an Iterative Preorder Traversal?

```c
while (stack.size > 0U) {
    const TreeNode *node;

    if (tree_node_stack_pop(&stack, &node) != NODE_STACK_OK) {
        status = TREE_DFS_INVALID_ARGUMENT;
        break;
    }

    candidate.items[candidate.count].key = node->key;
    candidate.items[candidate.count].flagged = node->flagged;
    candidate.count += 1U;

    if (node->right != NULL &&
        tree_node_stack_push(&stack, node->right) != NODE_STACK_OK) {
        status = TREE_DFS_LIMIT;
        break;
    }
    if (node->left != NULL &&
        tree_node_stack_push(&stack, node->left) != NODE_STACK_OK) {
        status = TREE_DFS_LIMIT;
        break;
    }
}
```

The real function checks whether a container error is a limit issue or a memory failure and converts it to the correct error code. It also strictly checks the 64-visit limit before saving data, and only copies the temporary `candidate` workspace to the final output when it completely succeeds.

### How do we search in a Binary Search Tree?

```c
const TreeNode *current = root;

while (current != NULL) {
    if (target == current->key) {
        *out_node = current;
        return TREE_DFS_OK;
    }
    current = target < current->key
        ? current->left
        : current->right;
}

return TREE_DFS_NOT_FOUND;
```

### How do we free the tree starting from the children?

```c
static void destroy_nodes_postorder(TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    destroy_nodes_postorder(node->left);
    destroy_nodes_postorder(node->right);
    tree_node_release(node);
}

TreeDfsStatus tree_destroy_postorder(TreeNode **root)
{
    if (root == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    destroy_nodes_postorder(*root);
    *root = NULL;
    return TREE_DFS_OK;
}
```