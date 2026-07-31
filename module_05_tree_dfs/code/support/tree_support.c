#include "tree_dfs.h"

#include <stdbool.h>
#include <stdlib.h>

#ifdef TREE_DFS_TESTING
static bool tree_fail_next_node_allocation = false;
static size_t tree_live_node_count = 0U;

void tree_dfs_test_fail_next_node_allocation(void)
{
    tree_fail_next_node_allocation = true;
}

size_t tree_dfs_test_live_node_count(void)
{
    return tree_live_node_count;
}
#endif

static TreeNode *tree_allocate_node(void)
{
#ifdef TREE_DFS_TESTING
    if (tree_fail_next_node_allocation) {
        tree_fail_next_node_allocation = false;
        return NULL;
    }
#endif

    return malloc(sizeof(TreeNode));
}

TreeDfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
)
{
    TreeNode *candidate;

    if (out_node == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    candidate = tree_allocate_node();
    if (candidate == NULL) {
        return TREE_DFS_ALLOCATION;
    }

    candidate->key = key;
    candidate->flagged = flagged;
    candidate->left = NULL;
    candidate->right = NULL;

#ifdef TREE_DFS_TESTING
    tree_live_node_count += 1U;
#endif

    *out_node = candidate;
    return TREE_DFS_OK;
}

void tree_node_release(TreeNode *node)
{
    if (node == NULL) {
        return;
    }

#ifdef TREE_DFS_TESTING
    if (tree_live_node_count > 0U) {
        tree_live_node_count -= 1U;
    }
#endif

    free(node);
}

TreeDfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
)
{
    TreeNode **link;
    TreeNode *candidate;
    TreeDfsStatus status;

    if (root == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }

    link = root;
    while (*link != NULL) {
        if (key < (*link)->key) {
            link = &(*link)->left;
        } else if (key > (*link)->key) {
            link = &(*link)->right;
        } else {
            return TREE_DFS_DUPLICATE;
        }
    }

    candidate = NULL;
    status = tree_node_create(key, flagged, &candidate);
    if (status != TREE_DFS_OK) {
        return status;
    }

    *link = candidate;
    return TREE_DFS_OK;
}

const char *tree_dfs_status_name(TreeDfsStatus status)
{
    switch (status) {
        case TREE_DFS_OK:
            return "ok";
        case TREE_DFS_INVALID_ARGUMENT:
            return "invalid argument";
        case TREE_DFS_LIMIT:
            return "tree or Stack limit reached";
        case TREE_DFS_ALLOCATION:
            return "allocation failed";
        case TREE_DFS_DUPLICATE:
            return "duplicate key";
        case TREE_DFS_NOT_FOUND:
            return "key not found";
        default:
            return "unknown TreeDfsStatus";
    }
}
