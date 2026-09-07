#ifndef TREE_DFS_H
#define TREE_DFS_H

#include <stddef.h>

#define TREE_DFS_POOL_CAPACITY 100U

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node nodes[TREE_DFS_POOL_CAPACITY];
    size_t used;
} NodePool;

typedef enum {
    TREE_DFS_OK = 0,
    TREE_DFS_INVALID_ARGUMENT,
    TREE_DFS_POOL_FULL,
    TREE_DFS_INVALID_EXPRESSION,
    TREE_DFS_OUTPUT_TOO_SMALL,
    TREE_DFS_ARITHMETIC_OVERFLOW
} TreeDfsStatus;

void node_pool_init(NodePool *pool);
TreeDfsStatus tree_node_create(NodePool *pool, char data, Node **out_node);
TreeDfsStatus tree_copy_preorder(
    const Node *original,
    NodePool *destination,
    Node **out_copy
);
TreeDfsStatus tree_print_inorder(
    const Node *root,
    char *output,
    size_t output_capacity
);
TreeDfsStatus tree_evaluate_postorder(const Node *root, int *out_value);
const char *tree_dfs_status_name(TreeDfsStatus status);

#endif
