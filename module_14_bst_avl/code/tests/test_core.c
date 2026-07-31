#include "avl_tree.h"
#include "bst_baseline.h"
#include "tree_model.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static Tree *active_first = NULL;
static Tree *active_second = NULL;

static void cleanup_active_trees(void)
{
    if (active_first != NULL) {
        tree_destroy_iterative(active_first);
        active_first = NULL;
    }
    if (active_second != NULL) {
        tree_destroy_iterative(active_second);
        active_second = NULL;
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
            cleanup_active_trees();                                          \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool insert_sequence(
    Tree *tree,
    const int *keys,
    size_t count,
    bool use_avl
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        TreeStatus status = use_avl
            ? avl_insert(tree, keys[index])
            : bst_insert_baseline(tree, keys[index]);

        if (status != TREE_OK) {
            return false;
        }
        if (!tree_validate_bst(tree)) {
            return false;
        }
        if (use_avl && !tree_validate_avl(tree)) {
            return false;
        }
    }
    return true;
}

static bool is_canonical_perfect_tree(const Tree *tree)
{
    static const int level_order[15] = {
        8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15
    };
    const TreeNode *queue[15];
    size_t front = 0U;
    size_t back = 0U;

    if (tree == NULL || tree->root == NULL || tree->size != 15U) {
        return false;
    }

    queue[back] = tree->root;
    back += 1U;
    while (front < back) {
        const TreeNode *node = queue[front];
        size_t index = front;

        front += 1U;
        if (node == NULL || node->key != level_order[index]) {
            return false;
        }
        if (node->left != NULL) {
            if (back >= 15U) {
                return false;
            }
            queue[back] = node->left;
            back += 1U;
        }
        if (node->right != NULL) {
            if (back >= 15U) {
                return false;
            }
            queue[back] = node->right;
            back += 1U;
        }
    }
    return back == 15U;
}

static bool check_search(
    const Tree *tree,
    int key,
    bool expected_found,
    size_t expected_comparisons
)
{
    bool found = !expected_found;
    size_t comparisons = 999U;

    return bst_search(
        tree,
        key,
        &found,
        &comparisons
    ) == TREE_OK &&
        found == expected_found &&
        comparisons == expected_comparisons;
}

static bool test_raw_rotations_preserve_middle_subtrees(void)
{
    TreeNode left_lower = {20, 2, NULL, NULL};
    TreeNode left_upper = {30, 1, NULL, NULL};
    TreeNode left_middle = {25, 0, NULL, NULL};
    TreeNode right_lower = {30, 2, NULL, NULL};
    TreeNode right_upper = {20, 1, NULL, NULL};
    TreeNode right_middle = {25, 0, NULL, NULL};
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
    return true;
}

static bool test_four_canonical_rotation_cases(void)
{
    static const int cases[4][3] = {
        {30, 20, 10},
        {10, 20, 30},
        {30, 10, 20},
        {10, 30, 20}
    };
    size_t baseline = tree_test_live_node_count();
    size_t case_index;

    for (case_index = 0U; case_index < 4U; ++case_index) {
        Tree tree;

        REQUIRE(tree_init(&tree) == TREE_OK);
        active_first = &tree;
        REQUIRE(insert_sequence(&tree, cases[case_index], 3U, true));
        REQUIRE(tree_validate_avl(&tree));
        REQUIRE(tree.size == 3U);
        REQUIRE(tree.root != NULL && tree.root->key == 20);
        REQUIRE(tree.root->height == 1);
        REQUIRE(tree.root->left != NULL);
        REQUIRE(tree.root->left->key == 10);
        REQUIRE(tree.root->left->height == 0);
        REQUIRE(tree.root->right != NULL);
        REQUIRE(tree.root->right->key == 30);
        REQUIRE(tree.root->right->height == 0);
        REQUIRE(tree.root->left->left == NULL);
        REQUIRE(tree.root->left->right == NULL);
        REQUIRE(tree.root->right->left == NULL);
        REQUIRE(tree.root->right->right == NULL);
        REQUIRE(tree_actual_height(tree.root) == 1);

        tree_destroy_iterative(&tree);
        active_first = NULL;
        REQUIRE(tree.root == NULL && tree.size == 0U);
        REQUIRE(tree_test_live_node_count() == baseline);
    }
    return true;
}

static bool test_three_height_and_comparison_traces(void)
{
    static const int sequences[3][15] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15}
    };
    static const int targets[3] = {15, 1, 15};
    static const int misses[3] = {16, 0, 16};
    static const int baseline_heights[3] = {14, 14, 3};
    static const size_t baseline_comparisons[3] = {15U, 15U, 4U};
    size_t baseline_live = tree_test_live_node_count();
    size_t sequence_index;

    for (sequence_index = 0U;
         sequence_index < 3U;
         ++sequence_index) {
        Tree baseline;
        Tree avl;

        REQUIRE(tree_init(&baseline) == TREE_OK);
        REQUIRE(tree_init(&avl) == TREE_OK);
        active_first = &baseline;
        active_second = &avl;
        REQUIRE(insert_sequence(
            &baseline,
            sequences[sequence_index],
            15U,
            false
        ));
        REQUIRE(insert_sequence(
            &avl,
            sequences[sequence_index],
            15U,
            true
        ));

        REQUIRE(tree_validate_bst(&baseline));
        REQUIRE(!tree_validate_avl(&baseline));
        REQUIRE(tree_actual_height(baseline.root) ==
            baseline_heights[sequence_index]);
        REQUIRE(check_search(
            &baseline,
            targets[sequence_index],
            true,
            baseline_comparisons[sequence_index]
        ));
        REQUIRE(check_search(
            &baseline,
            misses[sequence_index],
            false,
            baseline_comparisons[sequence_index]
        ));

        REQUIRE(tree_validate_bst(&avl));
        REQUIRE(tree_validate_avl(&avl));
        REQUIRE(tree_actual_height(avl.root) == 3);
        REQUIRE(is_canonical_perfect_tree(&avl));
        REQUIRE(check_search(
            &avl,
            targets[sequence_index],
            true,
            4U
        ));
        REQUIRE(check_search(
            &avl,
            misses[sequence_index],
            false,
            4U
        ));

        tree_destroy_iterative(&baseline);
        active_first = NULL;
        tree_destroy_iterative(&avl);
        active_second = NULL;
        REQUIRE(tree_test_live_node_count() == baseline_live);
    }
    return true;
}

static bool test_duplicate_and_allocation_failure_are_atomic(void)
{
    Tree tree;
    TreeNode *root_before;
    TreeNode *left_before;
    TreeNode *right_before;
    size_t baseline = tree_test_live_node_count();

    REQUIRE(tree_init(&tree) == TREE_OK);
    active_first = &tree;
    REQUIRE(avl_insert(&tree, 20) == TREE_OK);
    REQUIRE(avl_insert(&tree, 10) == TREE_OK);
    REQUIRE(avl_insert(&tree, 30) == TREE_OK);
    root_before = tree.root;
    left_before = tree.root->left;
    right_before = tree.root->right;

    tree_test_fail_next_allocation();
    REQUIRE(avl_insert(&tree, 20) == TREE_DUPLICATE);
    REQUIRE(tree.root == root_before && tree.size == 3U);
    REQUIRE(tree.root->left == left_before);
    REQUIRE(tree.root->right == right_before);
    REQUIRE(tree_validate_avl(&tree));

    REQUIRE(avl_insert(&tree, 25) == TREE_ALLOCATION_FAILED);
    REQUIRE(tree.root == root_before && tree.size == 3U);
    REQUIRE(tree.root->left == left_before);
    REQUIRE(tree.root->right == right_before);
    REQUIRE(tree.root->height == 1);
    REQUIRE(tree_validate_avl(&tree));
    REQUIRE(tree_test_live_node_count() == baseline + 3U);

    REQUIRE(avl_insert(&tree, 25) == TREE_OK);
    REQUIRE(tree.size == 4U);
    REQUIRE(tree_validate_avl(&tree));

    tree_destroy_iterative(&tree);
    active_first = NULL;
    REQUIRE(tree_test_live_node_count() == baseline);
    return true;
}

static bool test_full_validators_reject_bad_representations(void)
{
    TreeNode cycle = {10, 0, NULL, NULL};
    TreeNode shared_root = {10, 2, NULL, NULL};
    TreeNode shared_left = {5, 1, NULL, NULL};
    TreeNode shared_right = {15, 1, NULL, NULL};
    TreeNode shared_node = {7, 0, NULL, NULL};
    TreeNode wrong_root = {10, 1, NULL, NULL};
    TreeNode wrong_left = {12, 0, NULL, NULL};
    TreeNode stale = {9, 4, NULL, NULL};
    TreeNode unbalanced_root = {3, 2, NULL, NULL};
    TreeNode unbalanced_middle = {2, 1, NULL, NULL};
    TreeNode unbalanced_leaf = {1, 0, NULL, NULL};
    Tree cycle_tree;
    Tree shared_tree;
    Tree wrong_order;
    Tree wrong_size;
    Tree stale_tree;
    Tree unbalanced_tree;

    cycle.left = &cycle;
    cycle_tree = (Tree){&cycle, 1U};
    REQUIRE(!tree_validate_bst(&cycle_tree));
    REQUIRE(!tree_validate_avl(&cycle_tree));

    shared_root.left = &shared_left;
    shared_root.right = &shared_right;
    shared_left.right = &shared_node;
    shared_right.left = &shared_node;
    shared_tree = (Tree){&shared_root, 4U};
    REQUIRE(!tree_validate_bst(&shared_tree));
    REQUIRE(!tree_validate_avl(&shared_tree));

    wrong_root.left = &wrong_left;
    wrong_order = (Tree){&wrong_root, 2U};
    REQUIRE(!tree_validate_bst(&wrong_order));
    REQUIRE(!tree_validate_avl(&wrong_order));

    wrong_size = (Tree){&stale, 2U};
    REQUIRE(!tree_validate_bst(&wrong_size));
    REQUIRE(!tree_validate_avl(&wrong_size));

    stale_tree = (Tree){&stale, 1U};
    REQUIRE(tree_validate_bst(&stale_tree));
    REQUIRE(!tree_validate_avl(&stale_tree));

    unbalanced_root.left = &unbalanced_middle;
    unbalanced_middle.left = &unbalanced_leaf;
    unbalanced_tree = (Tree){&unbalanced_root, 3U};
    REQUIRE(tree_validate_bst(&unbalanced_tree));
    REQUIRE(!tree_validate_avl(&unbalanced_tree));
    REQUIRE(tree_actual_height(unbalanced_tree.root) == 2);
    REQUIRE(tree_actual_height(NULL) == -1);
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
        test_raw_rotations_preserve_middle_subtrees,
        "raw rotations preserve non-NULL middle subtrees"
    );
    failures += run_test(
        test_four_canonical_rotation_cases,
        "LL, RR, LR, and RL canonical rotations"
    );
    failures += run_test(
        test_three_height_and_comparison_traces,
        "BST versus AVL height and comparison traces"
    );
    failures += run_test(
        test_duplicate_and_allocation_failure_are_atomic,
        "duplicate and allocation failures preserve the AVL tree"
    );
    failures += run_test(
        test_full_validators_reject_bad_representations,
        "full validators reject malformed representations"
    );

    if (failures != 0) {
        (void)fprintf(stderr, "%d core test(s) failed.\n", failures);
        return 1;
    }

    puts("All Module 14 core tests passed.");
    return 0;
}
