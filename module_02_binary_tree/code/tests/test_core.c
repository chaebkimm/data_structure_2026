#include "binary_tree.h"

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

static int test_expression_initialization_and_occupied_side_guard(void)
{
    struct TreeNode root;
    struct TreeNode plus;
    struct TreeNode three;
    struct TreeNode five;
    struct TreeNode two;
    struct TreeNode replacement;

    root.data = '*';
    root.left = NULL;
    root.right = NULL;
    plus.data = '+';
    plus.left = NULL;
    plus.right = NULL;
    three.data = 3;
    three.left = NULL;
    three.right = NULL;
    five.data = 5;
    five.left = NULL;
    five.right = NULL;
    two.data = 2;
    two.left = NULL;
    two.right = NULL;
    replacement.data = '-';
    replacement.left = NULL;
    replacement.right = NULL;

    REQUIRE(root.data == '*');
    REQUIRE(root.left == NULL);
    REQUIRE(root.right == NULL);

    if (root.left == NULL) {
        root.left = &plus;
    }
    if (root.left == NULL) {
        root.left = &replacement;
    }
    if (root.right == NULL) {
        root.right = &two;
    }
    if (plus.left == NULL) {
        plus.left = &three;
    }
    if (plus.right == NULL) {
        plus.right = &five;
    }

    REQUIRE(root.left == &plus);
    REQUIRE(root.right == &two);
    REQUIRE(plus.left == &three);
    REQUIRE(plus.right == &five);
    REQUIRE(replacement.data == '-');
    return 1;
}

static int test_canonical_expression_preorder_search_preserves_nodes(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode five = { 5, NULL, NULL };
    struct TreeNode plus = { '+', &three, &five };
    struct TreeNode two = { 2, NULL, NULL };
    struct TreeNode root = { '*', &plus, &two };

    REQUIRE(tree_find(&root, '*') == &root);
    REQUIRE(tree_find(&root, '+') == &plus);
    REQUIRE(tree_find(&root, 3) == &three);
    REQUIRE(tree_find(&root, 5) == &five);
    REQUIRE(tree_find(&root, 2) == &two);
    REQUIRE(tree_find(&root, 999) == NULL);

    REQUIRE(root.data == '*' && root.left == &plus && root.right == &two);
    REQUIRE(plus.data == '+' && plus.left == &three && plus.right == &five);
    REQUIRE(three.data == 3 && three.left == NULL && three.right == NULL);
    REQUIRE(five.data == 5 && five.left == NULL && five.right == NULL);
    REQUIRE(two.data == 2 && two.left == NULL && two.right == NULL);
    return 1;
}

static int test_preorder_duplicates_and_generic_unsorted_values(void)
{
    struct TreeNode deep_match = { 10, NULL, NULL };
    struct TreeNode left = { 70, &deep_match, NULL };
    struct TreeNode repeated_root_value = { 50, NULL, NULL };
    struct TreeNode right = { 10, NULL, &repeated_root_value };
    struct TreeNode root = { 50, &left, &right };

    REQUIRE(tree_find(&root, 50) == &root);
    REQUIRE(tree_find(&root, 10) == &deep_match);
    REQUIRE(tree_find(&root, 70) == &left);
    REQUIRE(tree_find(&root, 999) == NULL);
    return 1;
}

static int test_right_only_child_null_and_missing_search(void)
{
    struct TreeNode leaf = { 60, NULL, NULL };
    struct TreeNode right = { 70, &leaf, NULL };
    struct TreeNode root = { 50, NULL, NULL };

    if (root.right == NULL) {
        root.right = &right;
    }

    REQUIRE(root.left == NULL);
    REQUIRE(tree_find(NULL, 50) == NULL);
    REQUIRE(tree_find(&root, 123) == NULL);
    REQUIRE(tree_find(&root, 70) == &right);
    REQUIRE(tree_find(&root, 60) == &leaf);
    return 1;
}

static int test_zero_is_ordinary_data(void)
{
    struct TreeNode node = { 0, NULL, NULL };

    REQUIRE(tree_find(&node, 0) == &node);
    tree_clear(NULL);
    tree_clear(&node);
    REQUIRE(node_is_cleared(&node));
    REQUIRE(tree_find(&node, 0) == &node);
    REQUIRE(tree_find(NULL, 0) == NULL);
    return 1;
}

static int test_clear_expression_branch_and_explicit_detachment(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode five = { 5, NULL, NULL };
    struct TreeNode plus = { '+', &three, &five };
    struct TreeNode two = { 2, NULL, NULL };
    struct TreeNode root = { '*', &plus, &two };

    tree_clear(root.left);

    REQUIRE(root.left == &plus);
    REQUIRE(node_is_cleared(&plus));
    REQUIRE(node_is_cleared(&three));
    REQUIRE(node_is_cleared(&five));
    REQUIRE(root.data == '*' && root.right == &two);
    REQUIRE(two.data == 2 && two.left == NULL && two.right == NULL);

    root.left = NULL;
    REQUIRE(root.left == NULL);
    REQUIRE(root.right == &two);
    REQUIRE(tree_find(&root, '+') == NULL);
    REQUIRE(tree_find(&root, 2) == &two);
    return 1;
}

static int test_whole_expression_clear_keeps_objects_live(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode five = { 5, NULL, NULL };
    struct TreeNode plus = { '+', &three, &five };
    struct TreeNode two = { 2, NULL, NULL };
    struct TreeNode root = { '*', &plus, &two };
    struct TreeNode separate = { 333, NULL, NULL };

    tree_clear(&root);

    REQUIRE(node_is_cleared(&root));
    REQUIRE(node_is_cleared(&plus));
    REQUIRE(node_is_cleared(&three));
    REQUIRE(node_is_cleared(&five));
    REQUIRE(node_is_cleared(&two));
    REQUIRE(separate.data == 333);
    return 1;
}

static int test_reinitialize_and_reuse_cleared_nodes(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode plus = { '+', &three, NULL };
    struct TreeNode root = { '*', &plus, NULL };

    tree_clear(&root);
    REQUIRE(node_is_cleared(&root));
    REQUIRE(node_is_cleared(&plus));
    REQUIRE(node_is_cleared(&three));

    root.data = '-';
    root.left = NULL;
    root.right = NULL;
    plus.data = 8;
    plus.left = NULL;
    plus.right = NULL;
    if (root.right == NULL) {
        root.right = &plus;
    }

    REQUIRE(tree_find(&root, 8) == &plus);
    REQUIRE(root.left == NULL);
    REQUIRE(root.right == &plus);
    REQUIRE(node_is_cleared(&three));
    return 1;
}

int main(void)
{
    run_test(
        "expression initialization and occupied-side guard",
        test_expression_initialization_and_occupied_side_guard
    );
    run_test(
        "canonical expression preorder search preserves nodes",
        test_canonical_expression_preorder_search_preserves_nodes
    );
    run_test(
        "preorder duplicates and generic unsorted values",
        test_preorder_duplicates_and_generic_unsorted_values
    );
    run_test(
        "right-only child, null, and missing search",
        test_right_only_child_null_and_missing_search
    );
    run_test("zero is ordinary data", test_zero_is_ordinary_data);
    run_test(
        "clear expression branch and explicit detachment",
        test_clear_expression_branch_and_explicit_detachment
    );
    run_test(
        "whole expression clear keeps objects live",
        test_whole_expression_clear_keeps_objects_live
    );
    run_test(
        "reinitialize and reuse cleared nodes",
        test_reinitialize_and_reuse_cleared_nodes
    );

    (void)printf(
        "\n%d core test(s), %d failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0 ? 0 : 1;
}
