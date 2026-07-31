#include "tree_bfs.h"

#include <stdbool.h>
#include <stdlib.h>

#ifdef TREE_BFS_TESTING
static bool tree_fail_next_node_allocation = false;
static size_t tree_live_node_count = 0U;

void tree_bfs_test_fail_next_node_allocation(void)
{
    tree_fail_next_node_allocation = true;
}

size_t tree_bfs_test_live_node_count(void)
{
    return tree_live_node_count;
}
#endif

static TreeNode *tree_allocate_node(void)
{
#ifdef TREE_BFS_TESTING
    if (tree_fail_next_node_allocation) {
        tree_fail_next_node_allocation = false;
        return NULL;
    }
#endif

    return malloc(sizeof(TreeNode));
}

TreeBfsStatus tree_node_create(
    int key,
    bool flagged,
    TreeNode **out_node
)
{
    TreeNode *candidate;

    if (out_node == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    candidate = tree_allocate_node();
    if (candidate == NULL) {
        return TREE_BFS_ALLOCATION;
    }

    candidate->key = key;
    candidate->flagged = flagged;
    candidate->left = NULL;
    candidate->right = NULL;

#ifdef TREE_BFS_TESTING
    tree_live_node_count += 1U;
#endif

    *out_node = candidate;
    return TREE_BFS_OK;
}

void tree_node_release(TreeNode *node)
{
    if (node == NULL) {
        return;
    }

#ifdef TREE_BFS_TESTING
    if (tree_live_node_count > 0U) {
        tree_live_node_count -= 1U;
    }
#endif

    free(node);
}

TreeBfsStatus tree_bst_insert(
    TreeNode **root,
    int key,
    bool flagged
)
{
    TreeNode **link;
    TreeNode *candidate = NULL;
    TreeBfsStatus status;

    if (root == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    link = root;
    while (*link != NULL) {
        if (key < (*link)->key) {
            link = &(*link)->left;
        } else if (key > (*link)->key) {
            link = &(*link)->right;
        } else {
            return TREE_BFS_DUPLICATE;
        }
    }

    status = tree_node_create(key, flagged, &candidate);
    if (status != TREE_BFS_OK) {
        return status;
    }

    *link = candidate;
    return TREE_BFS_OK;
}

static void destroy_nodes_postorder(TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    destroy_nodes_postorder(node->left);
    destroy_nodes_postorder(node->right);
    tree_node_release(node);
}

TreeBfsStatus tree_destroy_postorder(TreeNode **root)
{
    if (root == NULL) {
        return TREE_BFS_INVALID_ARGUMENT;
    }

    destroy_nodes_postorder(*root);
    *root = NULL;
    return TREE_BFS_OK;
}

const char *tree_bfs_status_name(TreeBfsStatus status)
{
    switch (status) {
        case TREE_BFS_OK:
            return "ok";
        case TREE_BFS_INVALID_ARGUMENT:
            return "invalid argument";
        case TREE_BFS_LIMIT:
            return "tree or Queue limit reached";
        case TREE_BFS_ALLOCATION:
            return "allocation failed";
        case TREE_BFS_DUPLICATE:
            return "duplicate key";
        case TREE_BFS_NOT_FOUND:
            return "key not found";
        default:
            return "unknown TreeBfsStatus";
    }
}
