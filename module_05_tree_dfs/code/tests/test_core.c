#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { if (!(condition)) {                         \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition);             \
    return false;                                                         \
} } while (false)

static bool build_example(NodePool *pool, Node **root)
{
    Node *plus;
    Node *times;
    Node *three;
    Node *five;
    Node *two;

    node_pool_init(pool);
    CHECK(tree_node_create(pool, '*', &times) == TREE_DFS_OK);
    CHECK(tree_node_create(pool, '+', &plus) == TREE_DFS_OK);
    CHECK(tree_node_create(pool, '3', &three) == TREE_DFS_OK);
    CHECK(tree_node_create(pool, '5', &five) == TREE_DFS_OK);
    CHECK(tree_node_create(pool, '2', &two) == TREE_DFS_OK);
    times->left = plus;
    times->right = two;
    plus->left = three;
    plus->right = five;
    *root = times;
    return true;
}

static bool test_preorder_copy(void)
{
    NodePool source;
    NodePool copy_pool;
    Node *root;
    Node *copy = NULL;

    CHECK(build_example(&source, &root));
    node_pool_init(&copy_pool);
    CHECK(tree_copy_preorder(root, &copy_pool, &copy) == TREE_DFS_OK);
    CHECK(copy_pool.used == 5U);
    CHECK(copy != root && copy->data == '*');
    CHECK(copy->left != root->left && copy->left->data == '+');
    CHECK(copy->left->left->data == '3');
    CHECK(copy->left->right->data == '5');
    CHECK(copy->right->data == '2');
    return true;
}

static bool test_inorder_print(void)
{
    NodePool pool;
    Node *root;
    char output[32];

    CHECK(build_example(&pool, &root));
    CHECK(tree_print_inorder(root, output, sizeof(output)) == TREE_DFS_OK);
    CHECK(strcmp(output, "(3+5)*2") == 0);
    return true;
}

static bool test_postorder_evaluate(void)
{
    NodePool pool;
    Node *root;
    int result = -1;

    CHECK(build_example(&pool, &root));
    CHECK(tree_evaluate_postorder(root, &result) == TREE_DFS_OK);
    CHECK(result == 16);
    return true;
}

static bool test_failures_preserve_outputs(void)
{
    NodePool source;
    NodePool destination;
    Node *root;
    Node marker = {'9', NULL, NULL};
    Node *copy = &marker;
    char output[4] = "old";
    int value = 77;

    CHECK(build_example(&source, &root));
    node_pool_init(&destination);
    destination.used = TREE_DFS_POOL_CAPACITY - 2U;
    CHECK(tree_copy_preorder(root, &destination, &copy) == TREE_DFS_POOL_FULL);
    CHECK(destination.used == TREE_DFS_POOL_CAPACITY - 2U);
    CHECK(copy == &marker);
    CHECK(tree_print_inorder(root, output, sizeof(output)) == TREE_DFS_OUTPUT_TOO_SMALL);
    CHECK(output[0] == '\0');
    root->left->right = NULL;
    CHECK(tree_evaluate_postorder(root, &value) == TREE_DFS_INVALID_EXPRESSION);
    CHECK(value == 77);
    return true;
}

typedef bool (*TestFunction)(void);

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();
    printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;
    failures += run_test(test_preorder_copy, "preorder copy");
    failures += run_test(test_inorder_print, "inorder print");
    failures += run_test(test_postorder_evaluate, "postorder evaluate");
    failures += run_test(test_failures_preserve_outputs, "failure contracts");
    return failures == 0 ? 0 : 1;
}
