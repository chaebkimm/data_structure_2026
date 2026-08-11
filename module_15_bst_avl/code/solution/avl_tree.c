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

static TreeNode *insert_recursive(
    TreeNode *node,
    int key,
    TreeStatus *status
)
{
    if (node == NULL) {
        TreeNode *created = NULL;

        *status = tree_node_create(key, &created);
        return created;
    }

    if (key < node->key) {
        TreeNode *new_left = insert_recursive(
            node->left,
            key,
            status
        );

        if (*status != TREE_OK) {
            return node;
        }
        node->left = new_left;
    } else {
        TreeNode *new_right = insert_recursive(
            node->right,
            key,
            status
        );

        if (*status != TREE_OK) {
            return node;
        }
        node->right = new_right;
    }

    return avl_rebalance(node);
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
