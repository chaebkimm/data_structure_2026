#include "avl_tree.h"
#include "bst_baseline.h"
#include "tree_model.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef bool (*TestFunction)(void);

static Tree *active_tree = NULL;
static TreeNode *active_standalone_node = NULL;

static void cleanup_active_tree(void)
{
    if (active_tree != NULL) {
        tree_destroy_iterative(active_tree);
        active_tree = NULL;
    }
    if (active_standalone_node != NULL) {
        tree_node_release(active_standalone_node);
        active_standalone_node = NULL;
    }
}

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "Requirement failed at %s:%d: %s\n",                        \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            cleanup_active_tree();                                           \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool test_rotations_preserve_the_middle_subtree(void)
{
    TreeNode left_lower = {20, 2, NULL, NULL};
    TreeNode left_upper = {30, 1, NULL, NULL};
    TreeNode left_middle = {25, 0, NULL, NULL};
    TreeNode right_lower = {30, 2, NULL, NULL};
    TreeNode right_upper = {20, 1, NULL, NULL};
    TreeNode right_middle = {25, 0, NULL, NULL};
    TreeNode leaf = {1, 0, NULL, NULL};
    TreeNode *result;

    left_lower.right = &left_upper;
    left_upper.left = &left_middle;
    result = avl_rotate_left(&left_lower);
    REQUIRE(result == &left_upper);
    REQUIRE(result->left == &left_lower);
    REQUIRE(left_lower.right == &left_middle);
    REQUIRE(left_lower.height == 1);
    REQUIRE(left_upper.height == 2);

    right_lower.left = &right_upper;
    right_upper.right = &right_middle;
    result = avl_rotate_right(&right_lower);
    REQUIRE(result == &right_upper);
    REQUIRE(result->right == &right_lower);
    REQUIRE(right_lower.left == &right_middle);
    REQUIRE(right_lower.height == 1);
    REQUIRE(right_upper.height == 2);

    REQUIRE(avl_rotate_left(NULL) == NULL);
    REQUIRE(avl_rotate_right(NULL) == NULL);
    REQUIRE(avl_rotate_left(&leaf) == &leaf);
    REQUIRE(avl_rotate_right(&leaf) == &leaf);
    return true;
}

static bool test_full_duplicate_and_hook_precedence(void)
{
    Tree tree;
    size_t baseline = tree_test_live_node_count();
    size_t index;

    REQUIRE(tree_init(&tree) == TREE_OK);
    active_tree = &tree;
    for (index = 0U;
         index < (size_t)BST_AVL_MAX_NODES;
         ++index) {
        REQUIRE(avl_insert(&tree, (int)index) == TREE_OK);
    }
    REQUIRE(tree.size == (size_t)BST_AVL_MAX_NODES);
    REQUIRE(tree_validate_avl(&tree));

    tree_test_fail_next_allocation();
    REQUIRE(avl_insert(&tree, 0) == TREE_DUPLICATE);
    REQUIRE(avl_insert(
        &tree,
        (int)BST_AVL_MAX_NODES
    ) == TREE_FULL);
    REQUIRE(tree.size == (size_t)BST_AVL_MAX_NODES);
    REQUIRE(tree_validate_avl(&tree));

    tree_destroy_iterative(&tree);
    active_tree = NULL;
    REQUIRE(tree_test_live_node_count() == baseline);

    REQUIRE(tree_init(&tree) == TREE_OK);
    active_tree = &tree;
    REQUIRE(avl_insert(&tree, 7) == TREE_ALLOCATION_FAILED);
    REQUIRE(tree.root == NULL && tree.size == 0U);
    REQUIRE(avl_insert(&tree, 7) == TREE_OK);
    tree_destroy_iterative(&tree);
    active_tree = NULL;
    REQUIRE(tree_test_live_node_count() == baseline);
    return true;
}

static bool test_bounded_path_checks_preserve_outputs_and_tree(void)
{
    TreeNode cycle = {10, 0, NULL, NULL};
    Tree cycle_tree;
    Tree root_size_mismatch = {NULL, 1U};
    bool found = true;
    size_t comparisons = 777U;

    cycle.left = &cycle;
    cycle_tree = (Tree){&cycle, 1U};

    REQUIRE(bst_search(
        &cycle_tree,
        5,
        &found,
        &comparisons
    ) == TREE_INVALID_STATE);
    REQUIRE(found);
    REQUIRE(comparisons == 777U);
    REQUIRE(cycle.left == &cycle);
    REQUIRE(bst_insert_baseline(&cycle_tree, 5) ==
        TREE_INVALID_STATE);
    REQUIRE(avl_insert(&cycle_tree, 5) == TREE_INVALID_STATE);
    REQUIRE(cycle_tree.root == &cycle && cycle_tree.size == 1U);

    REQUIRE(bst_insert_baseline(&root_size_mismatch, 1) ==
        TREE_INVALID_STATE);
    REQUIRE(avl_insert(&root_size_mismatch, 1) ==
        TREE_INVALID_STATE);
    REQUIRE(!tree_validate_bst(&root_size_mismatch));
    REQUIRE(!tree_validate_avl(&root_size_mismatch));
    return true;
}

static bool test_argument_boundaries_and_status_names(void)
{
    Tree tree;
    Tree oversized = {NULL, (size_t)BST_AVL_MAX_NODES + 1U};
    TreeNode sentinel = {99, 0, NULL, NULL};
    TreeNode *node = NULL;
    TreeNode *unchanged = &sentinel;
    bool found = false;
    size_t comparisons = 42U;
    size_t baseline = tree_test_live_node_count();

    REQUIRE(tree_init(NULL) == TREE_INVALID_ARGUMENT);
    REQUIRE(tree_init(&tree) == TREE_OK);
    active_tree = &tree;
    REQUIRE(bst_insert_baseline(NULL, 1) == TREE_INVALID_ARGUMENT);
    REQUIRE(avl_insert(NULL, 1) == TREE_INVALID_ARGUMENT);
    REQUIRE(bst_search(NULL, 1, &found, &comparisons) ==
        TREE_INVALID_ARGUMENT);
    REQUIRE(bst_search(&tree, 1, NULL, &comparisons) ==
        TREE_INVALID_ARGUMENT);
    REQUIRE(bst_search(&tree, 1, &found, NULL) ==
        TREE_INVALID_ARGUMENT);
    REQUIRE(comparisons == 42U);
    REQUIRE(!tree_validate_bst(NULL));
    REQUIRE(!tree_validate_avl(NULL));
    REQUIRE(!tree_validate_bst(&oversized));
    REQUIRE(!tree_validate_avl(&oversized));

    REQUIRE(tree_node_create(5, NULL) == TREE_INVALID_ARGUMENT);
    REQUIRE(tree_node_create(5, &node) == TREE_OK);
    active_standalone_node = node;
    REQUIRE(node != NULL && node->key == 5 && node->height == 0);
    REQUIRE(node->left == NULL && node->right == NULL);
    REQUIRE(tree_test_live_node_count() == baseline + 1U);
    tree_node_release(node);
    active_standalone_node = NULL;
    node = unchanged;
    tree_test_fail_next_allocation();
    REQUIRE(tree_node_create(6, &node) == TREE_ALLOCATION_FAILED);
    REQUIRE(node == unchanged);
    REQUIRE(tree_test_live_node_count() == baseline);
    tree_node_release(NULL);

    REQUIRE(strcmp(
        tree_status_name(TREE_ALLOCATION_FAILED),
        "TREE_ALLOCATION_FAILED"
    ) == 0);
    REQUIRE(strcmp(
        tree_status_name((TreeStatus)99),
        "TREE_UNKNOWN_STATUS"
    ) == 0);

    tree_destroy_iterative(&tree);
    active_tree = NULL;
    tree_destroy_iterative(&tree);
    tree_destroy_iterative(NULL);
    REQUIRE(tree_test_live_node_count() == baseline);
    return true;
}

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();

    (void)printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_rotations_preserve_the_middle_subtree,
        "rotations preserve the middle subtree"
    );
    failures += run_test(
        test_full_duplicate_and_hook_precedence,
        "full, duplicate, and allocation-hook precedence"
    );
    failures += run_test(
        test_bounded_path_checks_preserve_outputs_and_tree,
        "bounded path checks preserve outputs and topology"
    );
    failures += run_test(
        test_argument_boundaries_and_status_names,
        "argument boundaries, allocation helpers, and status names"
    );

    if (failures != 0) {
        (void)fprintf(
            stderr,
            "%d extension test(s) failed.\n",
            failures
        );
        return 1;
    }

    puts("All Module 15 extension tests passed.");
    return 0;
}
