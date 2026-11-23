#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "tree_model.h"

#include <stdbool.h>

/*
 * Returns a cached edge height: -1 for NULL, otherwise node->height.
 * Balance factor is left height minus right height.
 */
int avl_node_height(const TreeNode *node);
int avl_balance_factor(const TreeNode *node);

/*
 * A rotation returns the new root of the same subtree. A missing required
 * child makes the helper return root unchanged. Rotations preserve the
 * middle subtree and refresh the lower node before the upper node.
 */
TreeNode *avl_rotate_left(TreeNode *root);
TreeNode *avl_rotate_right(TreeNode *root);

/*
 * Refreshes one node and applies the LL, RR, LR, or RL repair when needed.
 */
TreeNode *avl_rebalance(TreeNode *node);

/*
 * Checks every BST rule plus exact cached heights and a balance factor in
 * [-1, 1] at every node.
 */
bool tree_validate_avl(const Tree *tree);

/*
 * Recursively inserts one unique key, refreshes heights, and rebalances while
 * unwinding in O(h). The caller supplies a valid AVL tree; the operation uses
 * shallow and bounded search-path checks rather than the full diagnostic.
 * Every reported failure preserves the complete tree.
 */
TreeStatus avl_insert(Tree *tree, int key);

#endif
