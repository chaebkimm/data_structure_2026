#include "avl_tree.h"

#include <stdbool.h>
#include <stddef.h>

static bool locate_key_recursive(
    const TreeNode *node,
    int key,
    size_t *remaining_steps,
    bool *out_exists
)
{
    if (node == NULL) {
        *out_exists = false;
        return true;
    }
    if (*remaining_steps == 0U) {
        return false;
    }

    *remaining_steps -= 1U;
    if (key == node->key) {
        *out_exists = true;
        return true;
    }
    if (key < node->key) {
        return locate_key_recursive(
            node->left,
            key,
            remaining_steps,
            out_exists
        );
    }
    return locate_key_recursive(
        node->right,
        key,
        remaining_steps,
        out_exists
    );
}

/*
 * TODO 3: Complete recursive AVL insertion. Allocate only at a NULL link.
 * On success, reconnect the returned child, refresh while unwinding, and
 * return the rebalanced subtree root. On failure, preserve every old link.
 */
static TreeNode *insert_recursive(
    TreeNode *node,
    int key,
    TreeStatus *status
)
{
    (void)key;
    *status = TREE_INVALID_STATE;
    return node;
}

TreeStatus avl_insert(Tree *tree, int key)
{
    size_t remaining_steps;
    bool exists = false;
    TreeStatus status = TREE_INVALID_STATE;
    TreeNode *new_root;

    if (tree == NULL) {
        return TREE_INVALID_ARGUMENT;
    }
    if (tree->size > (size_t)BST_AVL_MAX_NODES ||
        ((tree->root == NULL) != (tree->size == 0U))) {
        return TREE_INVALID_STATE;
    }
    remaining_steps = tree->size;
    if (!locate_key_recursive(
            tree->root,
            key,
            &remaining_steps,
            &exists
        )) {
        return TREE_INVALID_STATE;
    }
    if (exists) {
        return TREE_DUPLICATE;
    }
    if (tree->size >= (size_t)BST_AVL_MAX_NODES) {
        return TREE_FULL;
    }

    new_root = insert_recursive(tree->root, key, &status);
    if (status != TREE_OK) {
        return status;
    }

    tree->root = new_root;
    tree->size += 1U;
    return TREE_OK;
}
