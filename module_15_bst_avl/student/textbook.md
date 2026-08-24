# Chapter 15. Straightening a Leaning Sorting Tree

## Thinking Logically

### Is following the number rules always fast?

Our basic sorting tree follows a strict rule: place smaller numbers strictly on the left, and larger numbers strictly on the right. It completely refuses to store duplicate numbers.

Thanks to this clever rule, we just compare the number we are looking for with the current number and instantly know which single downward path to follow. However, that path isn't magically guaranteed to be short.

If we insert the numbers 1 through 15 in perfect order, every single new number is forced to go to the right, creating a terrible, long straight line.

```text
1
 \
  2
   \
    3
     \
      ... 15
```

To find the number 15, or to prove that 16 doesn't exist, we must exhaustively check all 15 items! But, if we take those exact same numbers and scramble the order before inserting them, the longest path suddenly becomes incredibly short:

```text
Arrival Order: 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
```

The sorting rule alone absolutely cannot protect the overall physical shape of the tree. The exact order the numbers arrive completely dictates how much work searching will take later.

### How do we measure how badly the tree is leaning?

We measure the "tallness" of any spot by counting the exact number of downward steps to its farthest bottom edge. To make the math work perfectly, a completely empty space has a tallness of -1, and an item at the very bottom with no children has a tallness of 0.

```text
Tallness of empty space = -1
Tallness of bottom item = 0
```

If our 15 items form a single, terrible straight line, the top item's tallness is 14. If they are perfectly grouped and spread out, the tallness is only 3! Since searching and adding both force us to follow a single downward path, this tallness measurement sets the absolute standard for how much work is needed.

### How much taller can one side safely be?

We measure the "tilt score" of any spot by simply taking the tallness of its left side and subtracting the tallness of its right side.

```text
Tilt score = left tallness - right tallness
```

If we enforce a strict law that the tilt score of every single spot must *always* stay exactly at -1, 0, or 1, then neither side can ever keep growing out of control! A tree that perfectly follows this strict law is a self-balancing tree.

Every single item in this special tree keeps a note saving its own current tallness. If its children change, it quickly recalculates its tallness using simple math:

```text
1 + whichever child is taller
```

### Can we change the shape without breaking the number rules?

When the tilt score dangerously hits 2 or -2, we fix it by "twisting" the connections. Let's look at a Left Twist.

```text
Before Twisting        After Twisting
    X                       Y
     \                     / \
      Y                   X   R
     / \                   \
    M   R                   M
```

Notice the middle group (M). M is sitting on Y's left side, which means it is smaller than Y. But it is also sitting on X's right side, which means it is larger than X! Therefore, pulling M over to X's right side perfectly obeys all our sorting rules!

You must carefully save M's memory address first! If you blindly connect X to Y's left side right away, you will permanently lose your only address to M! After safely changing the connections, you must update the tallness of the new lower item (X) *first*, and only then update the tallness of the new top item (Y).

A Right Twist applies the exact same brilliant logic, just perfectly mirrored in the opposite direction.

### How do we fix the four leaning shapes?

Look at the exact two directions the path grew longer from the dangerously leaning spot. We will write L for a left step and R for a right step.

| Arrival Order | Shape | How to Straighten It |
| --- | --- | --- |
| `30, 20, 10` | L then L | Twist Right at 30 |
| `10, 20, 30` | R then R | Twist Left at 10 |
| `30, 10, 20` | L then R | Twist Left at 10, then Twist Right at 30 |
| `10, 30, 20` | R then L | Twist Right at 30, then Twist Left at 10 |

No matter which of the four bad shapes happens, the twisting steps always result in this perfect final shape:

```text
    20
   /  \
 10    30
```

The sorting order reading from left to right is always safely `10, 20, 30`. Straight shapes (LL and RR) only need one twist, while zig-zag shapes (LR and RL) require two twists to straighten out.

### After dropping a new number in, where do we start fixing?

First, exactly like a normal sorting tree, we walk down and find the perfect empty spot for the new number. We build the new item there with a starting tallness of 0.

As the computer finishes the downward steps and starts returning backwards up the path toward the top, we stop at every single item we passed. We recalculate its tallness, check its tilt score, and immediately twist it if it is leaning dangerously.

```text
Build a new item in the empty spot
-> Step backwards up to the parent and update its tallness
-> Check its tilt score
-> Twist once or twice if needed
-> Hand the newly straightened address back up to the next parent
```

We must always carefully reattach the straightened group back to the parent above it! If we twisted the very top of the entire tree, our main starting address variable must also be updated to point to the new top!

### Why do we check the child's tilt score again?

Even if the current spot is dangerously heavy on the left, deciding whether to use the single twist or the double twist depends entirely on the shape of its left child!

* If the current spot leans left (> 1) and the left child leans left or is balanced ($\ge 0$), do a single Right twist.
* If the current spot leans left (> 1) but the left child leans right (negative), Left twist the child first, then Right twist the current spot.
* If the current spot leans right (< -1) and the right child leans right or is balanced ($\le 0$), do a single Left twist.
* If the current spot leans right (< -1) but the right child leans left (positive), Right twist the child first, then Left twist the current spot.

### What happens if we fail to insert the number?

Our tool first checks if the exact same number already exists and ensures we haven't hit our strict 64-item limit. It stops and safely returns a "duplicate" error for identical numbers, or a "full" error if it hits 64.

If it completely fails to get memory from the computer for a new item, it safely returns an "allocation failed" error. Because we only ever change connections and twist things *after* the new item is successfully built and we are walking back up the path, failing halfway leaves the top address, connections, tallness notes, and total size perfectly untouched and safe!

*(Note: The code practice in this chapter only covers inserting and searching. Deleting items is incredibly complicated and is not included).*

### How much does straightening change the result for the same numbers?

Let's compare the results of putting 15 numbers in perfect ascending order, perfect descending order, and completely scrambled order.

| Tree Style & Arrival Order | Top Tallness | Checking the Last Number | Checking a Missing Number |
| --- | --- | --- | --- |
| Normal Tree, Ascending | 14 | 15 checks | 15 checks |
| Normal Tree, Descending | 14 | 15 checks | 15 checks |
| Normal Tree, Scrambled | 3 | 4 checks | 4 checks |
| Straightened Tree, Ascending | 3 | 4 checks | 4 checks |
| Straightened Tree, Descending | 3 | 4 checks | 4 checks |
| Straightened Tree, Scrambled | 3 | 4 checks | 4 checks |

Amazingly, all three Straightened attempts end up building the exact same, perfectly balanced 15-item shape where the number 8 sits exactly at the top! *(However, this doesn't guarantee that absolutely every single combination of numbers will magically create the exact same shape every time).*

### Is the tree perfect just because the tallness looks right?

You absolutely cannot prove the entire tree is built correctly just by looking at the tallness numbers and counting how fast it searches. Our heavy diagnostic tool checks all of these vital signs together:

* Are absolutely all numbers on the left strictly smaller than the current number?
* Are absolutely all numbers on the right strictly larger than the current number?
* Does the saved tallness sticky note perfectly match the real, counted physical tallness?
* Are all tilt scores strictly locked between -1 and 1?
* Is the tree completely free of dangerous loops and shared parents, and does the physical item count exactly match the official size?

This is a massive, heavy diagnostic that checks the entire structure. It is almost never run every single time during normal, everyday insertions and searches!

## Calculating Efficiency

### Efficiency of searching and inserting in a normal Sorting Tree?

If there are `n` items and the top tallness is `h`, searching and inserting follow a single path, taking $O(h)$ work. If the tree becomes a terrible straight line, $h$ becomes $n - 1$, so the work explodes to $O(n)$.

### Efficiency of searching in a self-balancing tree?

The strict straightening rules guarantee that the tallness only grows a tiny bit even when the total number of items grows massively. The tallness is locked tightly at $O(\log n)$, so searching is always guaranteed to be blazing fast, taking $O(\log n)$ work.

### Efficiency of inserting in a self-balancing tree?

Finding the empty spot and fixing the tallness notes on the walk back up both follow that exact same short path, taking $O(\log n)$ work. A single twist action just swaps a few fixed addresses and updates two tallness notes, so the twisting itself is instantly fast, $O(1)$.

### Efficiency of double-checking the total tallness and state?

The heavy diagnostic tools that recount the total tallness and verify every single rule must visit every single item in the tree, so they take $O(n)$ work. Safely destroying the entire tree also takes $O(n)$ work.

### What happens if we don't keep the balance?

A clever attacker could intentionally feed you totally valid numbers in a specific order designed to make your normal tree lean heavily to one side, drastically slowing down your computer! Our straightening rules perfectly prevent the problem where searching slows down to $O(n)$ just because of a bad shape. However, it does not magically fix totally broken memory addresses, illegal inputs, or memory failures.

## Glossary

### Binary Search Tree

A binary tree that places smaller keys on the left and larger keys on the right.

### Height

The number of edges going down from a specific node to its farthest leaf.

### Balance Factor

The value calculated by subtracting the height of the right subtree from the height of the left subtree.

### AVL Tree

A Binary Search Tree that strictly keeps the balance factor of every node between -1 and 1.

### Rotation

An operation that changes specific parent-child links while perfectly preserving the inorder sequence of the keys.

### LL, RR, LR, RL

The four shapes that show which two directions the path grew longer from the node where the balance broke.

### Cached Height

The current height saved inside the node so we don't have to recalculate the whole subtree every single time.

## Coding Plan

### Finding the Spot for a New Key

* **Shallow check:** Securely check the main starting address, `size`, and the strict maximum 64-node limit.
* **Check duplicate:** Follow one downward path to see if the exact same key already exists.
* **Choose direction:** Go left for a smaller key, right for a larger key.
* **Make new leaf:** Create a node in the empty spot with a height of 0 and both children safely set to `NULL`.

### Updating Node Height

* **Read child heights:** Use -1 for a completely empty `NULL` spot, and use the saved `height` for real living nodes.
* **Pick larger height:** Add exactly 1 to the larger value between the left and right heights.
* **Save current node:** Record this calculated value firmly into the current `node->height`.

### Rotating (Twisting) One Side

* **Pick new root:** Choose the right child for a left rotation, and the left child for a right rotation.
* **Save middle part:** Put the subtree sitting between the two nodes safely into a temporary variable.
* **Change links:** Connect the middle subtree to the lower node, and connect the lower node entirely to the new root.
* **Update heights:** Always fix the height of the lower node first, then the new root.
* **Return new root:** Return the new starting address of this straightened subtree so its parent can connect to it.

### Rebalancing (Straightening)

* **Update current height:** First, recalculate the height of the current node since its child just finished changing.
* **Calculate balance factor:** Find the math for `left height - right height`.
* **Choose single rotation:** Right rotate if LL shape; left rotate if RR shape.
* **Choose double rotation:** If LR or RL shape, rotate the child in the exact opposite direction first.

### Finalizing the Insertion Result

* **Check recursive result:** If the insertion attempt down below failed, immediately return the current link exactly as it is.
* **Connect new subtree root:** Securely attach the successful child's address back to the current node.
* **Repair on return:** Pass the final straightened result back up the chain to the calling function.
* **Update tree:** If absolutely everything succeeds perfectly, update the main `tree->root` and increase `size` by one.

## C Code

### Calculating Height and Balance Factor

```c
int avl_node_height(const TreeNode *node)
{
        return node == NULL ? -1 : node->height;
}

int avl_balance_factor(const TreeNode *node)
{
        if (node == NULL) {
                return 0;
        }

        return avl_node_height(node->left) -
                avl_node_height(node->right);
}
```

### Rotating Left

```c
TreeNode *avl_rotate_left(TreeNode *root)
{
        if (root == NULL || root->right == NULL) {
                return root;
        }

        TreeNode *upper = root->right;
        TreeNode *middle = upper->left;

        root->right = middle;
        upper->left = root;

        refresh_height(root);
        refresh_height(upper);
        return upper;
}
```

`refresh_height` is a clever helper function hidden inside the implementation file that safely reads the heights of the two children and updates the current node's `height` sticky note.

### Fixing Balance for the Four Shapes

```c
TreeNode *avl_rebalance(TreeNode *node)
{
        if (node == NULL) {
                return NULL;
        }

        refresh_height(node);
        int balance = avl_balance_factor(node);

        if (balance > 1) {
                if (avl_balance_factor(node->left) < 0) {
                        node->left = avl_rotate_left(node->left);
                }
                return avl_rotate_right(node);
        }

        if (balance < -1) {
                if (avl_balance_factor(node->right) > 0) {
                        node->right = avl_rotate_right(node->right);
                }
                return avl_rotate_left(node);
        }

        return node;
}
```

### Receiving the New Subtree Root After Stepping Up

```c
if (key < node->key) {
        TreeNode *new_left = insert_recursive(node->left, key, status);

        if (*status != TREE_OK) {
                return node;
        }
        node->left = new_left;
} else {
        TreeNode *new_right = insert_recursive(node->right, key, status);

        if (*status != TREE_OK) {
                return node;
        }
        node->right = new_right;
}

return avl_rebalance(node);
```