#include "avl_tree.h"

#include <stddef.h>

static int maximum_int(int left, int right)
{
    return left > right ? left : right;
}

static void refresh_height(TreeNode *node)
{
    if (node != NULL) {
        node->height = 1 + maximum_int(
            avl_node_height(node->left),
            avl_node_height(node->right)
        );
    }
}

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

/*
 * TODO 1: Complete both left and right rotations. Preserve the middle
 * subtree, then refresh the lower node before the new upper node.
 */
TreeNode *avl_rotate_left(TreeNode *root)
{
    return root;
}

TreeNode *avl_rotate_right(TreeNode *root)
{
    return root;
}

/*
 * TODO 2: Refresh node, detect its balance factor, and implement all four
 * repairs: LL, RR, LR, and RL.
 */
TreeNode *avl_rebalance(TreeNode *node)
{
    refresh_height(node);
    return node;
}
