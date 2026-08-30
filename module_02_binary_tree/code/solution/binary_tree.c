#include "binary_tree.h"

struct TreeNode *tree_find(struct TreeNode *node, int target)
{
    struct TreeNode *found;

    if (node == NULL) {
        return NULL;
    }
    if (node->data == target) {
        return node;
    }

    found = tree_find(node->left, target);
    if (found != NULL) {
        return found;
    }
    return tree_find(node->right, target);
}

void tree_clear(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    tree_clear(node->left);
    node->left = NULL;
    tree_clear(node->right);
    node->right = NULL;
    node->data = 0;
}
