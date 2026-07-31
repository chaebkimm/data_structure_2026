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

TreeNode *avl_rotate_left(TreeNode *root)
{
    TreeNode *upper;
    TreeNode *middle;

    if (root == NULL || root->right == NULL) {
        return root;
    }

    upper = root->right;
    middle = upper->left;
    root->right = middle;
    upper->left = root;
    refresh_height(root);
    refresh_height(upper);
    return upper;
}

TreeNode *avl_rotate_right(TreeNode *root)
{
    TreeNode *upper;
    TreeNode *middle;

    if (root == NULL || root->left == NULL) {
        return root;
    }

    upper = root->left;
    middle = upper->right;
    root->left = middle;
    upper->right = root;
    refresh_height(root);
    refresh_height(upper);
    return upper;
}

TreeNode *avl_rebalance(TreeNode *node)
{
    int balance;

    if (node == NULL) {
        return NULL;
    }

    refresh_height(node);
    balance = avl_balance_factor(node);

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
