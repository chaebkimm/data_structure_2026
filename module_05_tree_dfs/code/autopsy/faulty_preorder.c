#include "tree_dfs.h"

#include <stdio.h>

static Node *faulty_copy(const Node *original, NodePool *pool)
{
    Node *copy = NULL;

    if (original == NULL) return NULL;
    (void)tree_node_create(pool, original->data, &copy);
    copy->left = faulty_copy(original->left, pool);
    copy->right = faulty_copy(original->right, pool);
    return copy;
}

int main(void)
{
    NodePool source;
    NodePool destination;
    Node *root;

    node_pool_init(&source);
    node_pool_init(&destination);
    (void)tree_node_create(&source, '7', &root);
    destination.used = TREE_DFS_POOL_CAPACITY;
    puts("The faulty copy ignores pool exhaustion and dereferences NULL.");
    (void)faulty_copy(root, &destination);
    return 0;
}
