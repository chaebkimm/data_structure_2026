#include "tree_dfs.h"

void node_pool_init(NodePool *pool)
{
    if (pool != NULL) {
        pool->used = 0U;
    }
}

TreeDfsStatus tree_node_create(NodePool *pool, char data, Node **out_node)
{
    Node *node;

    if (pool == NULL || out_node == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }
    if (pool->used >= (size_t)TREE_DFS_POOL_CAPACITY) {
        return TREE_DFS_POOL_FULL;
    }
    node = &pool->nodes[pool->used++];
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    *out_node = node;
    return TREE_DFS_OK;
}

const char *tree_dfs_status_name(TreeDfsStatus status)
{
    switch (status) {
        case TREE_DFS_OK: return "ok";
        case TREE_DFS_INVALID_ARGUMENT: return "invalid argument";
        case TREE_DFS_POOL_FULL: return "node pool is full";
        case TREE_DFS_INVALID_EXPRESSION: return "invalid expression tree";
        case TREE_DFS_OUTPUT_TOO_SMALL: return "output buffer is too small";
        case TREE_DFS_ARITHMETIC_OVERFLOW: return "arithmetic overflow";
        default: return "unknown TreeDfsStatus";
    }
}
