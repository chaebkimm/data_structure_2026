#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { if (!(condition)) {                         \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition);             \
    return false;                                                         \
} } while (false)

static bool test_pool_boundary(void)
{
    NodePool pool;
    Node *node = NULL;
    size_t index;

    node_pool_init(&pool);
    for (index = 0U; index < TREE_DFS_POOL_CAPACITY; index++) {
        CHECK(tree_node_create(&pool, '1', &node) == TREE_DFS_OK);
    }
    CHECK(tree_node_create(&pool, '2', &node) == TREE_DFS_POOL_FULL);
    CHECK(pool.used == TREE_DFS_POOL_CAPACITY);
    return true;
}

static bool test_parentheses(void)
{
    NodePool pool;
    Node *nodes[7];
    char output[32];
    size_t index;

    node_pool_init(&pool);
    for (index = 0U; index < 7U; index++) {
        CHECK(tree_node_create(&pool, '0', &nodes[index]) == TREE_DFS_OK);
    }
    nodes[0]->data = '+'; nodes[0]->left = nodes[1]; nodes[0]->right = nodes[2];
    nodes[1]->data = '1';
    nodes[2]->data = '*'; nodes[2]->left = nodes[3]; nodes[2]->right = nodes[4];
    nodes[3]->data = '2';
    nodes[4]->data = '+'; nodes[4]->left = nodes[5]; nodes[4]->right = nodes[6];
    nodes[5]->data = '3'; nodes[6]->data = '4';
    CHECK(tree_print_inorder(nodes[0], output, sizeof(output)) == TREE_DFS_OK);
    CHECK(strcmp(output, "1+2*(3+4)") == 0);
    return true;
}

static bool test_invalid_shapes(void)
{
    Node digit_with_child = {'3', NULL, NULL};
    Node child = {'1', NULL, NULL};
    Node unknown = {'-', &child, &child};
    char output[16];
    int value = 9;

    digit_with_child.left = &child;
    CHECK(tree_print_inorder(&digit_with_child, output, sizeof(output)) == TREE_DFS_INVALID_EXPRESSION);
    CHECK(tree_evaluate_postorder(&unknown, &value) == TREE_DFS_INVALID_EXPRESSION);
    CHECK(value == 9);
    return true;
}

int main(void)
{
    int failures = 0;
    failures += test_pool_boundary() ? 0 : 1;
    failures += test_parentheses() ? 0 : 1;
    failures += test_invalid_shapes() ? 0 : 1;
    puts(failures == 0 ? "All extension tests passed." : "Extension tests failed.");
    return failures == 0 ? 0 : 1;
}
