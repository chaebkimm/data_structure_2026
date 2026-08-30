#include "binary_tree.h"

struct TreeNode *tree_find(struct TreeNode *node, int target)
{
    if (node == NULL) {
        return NULL;
    }

    /*
     * TODO(core): Check this node's data first. Then recursively search the
     * left subtree. Return that match if found; otherwise search the right
     * subtree. Return NULL when the target is absent. Do not change nodes.
     */
    (void)target;
    return NULL;
}

void tree_clear(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    /*
     * TODO(core): Recursively clear the left and right subtrees, set both
     * child links to NULL, and set this node's data to 0. The node object
     * remains alive. Its outside parent link is the caller's responsibility.
     */
}
