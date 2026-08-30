#include "binary_tree.h"

#include <limits.h>
#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            return 0;                                                        \
        }                                                                    \
    } while (0)

static int node_is_cleared(const struct TreeNode *node)
{
    return node->data == 0 && node->left == NULL && node->right == NULL;
}

static void run_test(const char *name, int (*test)(void))
{
    int passed;

    tests_run = tests_run + 1;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed = tests_failed + 1;
        (void)printf("FAIL %s\n", name);
    }
}

static int test_deep_finite_left_chain(void)
{
    enum { NODE_COUNT = 128 };
    struct TreeNode nodes[NODE_COUNT];
    int index;

    for (index = 0; index < NODE_COUNT; index = index + 1) {
        nodes[index].data = index + 1;
        nodes[index].left = NULL;
        nodes[index].right = NULL;
    }
    for (index = 0; index + 1 < NODE_COUNT; index = index + 1) {
        nodes[index].left = &nodes[index + 1];
    }

    REQUIRE(tree_find(&nodes[0], NODE_COUNT) == &nodes[NODE_COUNT - 1]);
    REQUIRE(tree_find(&nodes[0], -1) == NULL);
    tree_clear(&nodes[0]);
    for (index = 0; index < NODE_COUNT; index = index + 1) {
        REQUIRE(node_is_cleared(&nodes[index]));
    }
    return 1;
}

static int test_alternating_left_and_right_chain(void)
{
    enum { NODE_COUNT = 33 };
    struct TreeNode nodes[NODE_COUNT];
    int index;

    for (index = 0; index < NODE_COUNT; index = index + 1) {
        nodes[index].data = index + 1;
        nodes[index].left = NULL;
        nodes[index].right = NULL;
    }
    for (index = 0; index + 1 < NODE_COUNT; index = index + 1) {
        if (index % 2 == 0) {
            nodes[index].left = &nodes[index + 1];
        } else {
            nodes[index].right = &nodes[index + 1];
        }
    }

    for (index = 0; index < NODE_COUNT; index = index + 1) {
        REQUIRE(tree_find(&nodes[0], index + 1) == &nodes[index]);
    }
    tree_clear(&nodes[0]);
    for (index = 0; index < NODE_COUNT; index = index + 1) {
        REQUIRE(node_is_cleared(&nodes[index]));
    }
    return 1;
}

static int test_integer_extremes_are_unsorted_data(void)
{
    struct TreeNode left = { INT_MAX, NULL, NULL };
    struct TreeNode right = { INT_MIN, NULL, NULL };
    struct TreeNode root = { 0, &left, &right };

    REQUIRE(tree_find(&root, INT_MAX) == &left);
    REQUIRE(tree_find(&root, INT_MIN) == &right);
    REQUIRE(tree_find(&root, 0) == &root);
    tree_clear(&root);
    REQUIRE(node_is_cleared(&root));
    REQUIRE(node_is_cleared(&left));
    REQUIRE(node_is_cleared(&right));
    return 1;
}

static int test_repeated_clear_preserves_independent_tree(void)
{
    struct TreeNode child = { 20, NULL, NULL };
    struct TreeNode root = { 10, &child, NULL };
    struct TreeNode other_child = { 40, NULL, NULL };
    struct TreeNode other_root = { 30, NULL, &other_child };

    tree_clear(&root);
    tree_clear(&root);
    tree_clear(NULL);

    REQUIRE(node_is_cleared(&root));
    REQUIRE(node_is_cleared(&child));
    REQUIRE(other_root.data == 30);
    REQUIRE(other_root.left == NULL);
    REQUIRE(other_root.right == &other_child);
    REQUIRE(other_child.data == 40);
    REQUIRE(tree_find(&other_root, 40) == &other_child);
    return 1;
}

static int test_clear_saved_detached_subtree(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode five = { 5, NULL, NULL };
    struct TreeNode plus = { '+', &three, &five };
    struct TreeNode two = { 2, NULL, NULL };
    struct TreeNode root = { '*', &plus, &two };
    struct TreeNode *selected = root.left;

    root.left = NULL;
    tree_clear(selected);

    REQUIRE(node_is_cleared(&plus));
    REQUIRE(node_is_cleared(&three));
    REQUIRE(node_is_cleared(&five));
    REQUIRE(root.data == '*');
    REQUIRE(root.left == NULL);
    REQUIRE(root.right == &two);
    REQUIRE(two.data == 2);
    REQUIRE(tree_find(&root, '+') == NULL);
    REQUIRE(tree_find(&root, 2) == &two);
    return 1;
}

int main(void)
{
    run_test("deep finite left chain", test_deep_finite_left_chain);
    run_test(
        "alternating left and right chain",
        test_alternating_left_and_right_chain
    );
    run_test(
        "integer extremes are unsorted data",
        test_integer_extremes_are_unsorted_data
    );
    run_test(
        "repeated clear preserves independent tree",
        test_repeated_clear_preserves_independent_tree
    );
    run_test("clear saved detached subtree", test_clear_saved_detached_subtree);

    (void)printf(
        "\n%d extension test(s), %d failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0 ? 0 : 1;
}
