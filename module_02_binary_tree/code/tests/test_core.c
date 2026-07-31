#include "tree_arena.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

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
            return false;                                                    \
        }                                                                    \
    } while (false)

static void run_test(const char *name, TestFunction test)
{
    bool passed;

    tests_run += 1U;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        (void)printf("FAIL %s\n", name);
    }
}

static bool test_empty_and_single_node_initialization(void)
{
    TreeArena empty;
    TreeArena one;
    TreeNode storage[1];
    const int keys[1] = { 42 };
    bool is_leaf = false;
    size_t child_count = 99U;

    REQUIRE(
        tree_arena_init(
            &empty,
            NULL,
            NULL,
            0U,
            TREE_NO_INDEX
        ) == TREE_OK
    );
    REQUIRE(empty.nodes == NULL);
    REQUIRE(empty.count == 0U);
    REQUIRE(empty.root == NULL);
    REQUIRE(tree_validate_structure(&empty) == TREE_OK);
    REQUIRE(tree_validate_bst(&empty) == TREE_OK);

    REQUIRE(
        tree_arena_init(&one, storage, keys, 1U, 0U) == TREE_OK
    );
    REQUIRE(one.nodes == storage);
    REQUIRE(one.count == 1U);
    REQUIRE(one.root == &storage[0]);
    REQUIRE(storage[0].key == 42);
    REQUIRE(storage[0].left == NULL);
    REQUIRE(storage[0].right == NULL);

    REQUIRE(tree_node_is_leaf(&storage[0], &is_leaf) == TREE_OK);
    REQUIRE(is_leaf);
    REQUIRE(
        tree_node_child_count(&storage[0], &child_count) == TREE_OK
    );
    REQUIRE(child_count == 0U);
    REQUIRE(tree_validate_structure(&one) == TREE_OK);
    REQUIRE(tree_validate_bst(&one) == TREE_OK);
    return true;
}

static bool test_init_errors_preserve_previous_state(void)
{
    TreeNode storage[3];
    const int keys[3] = { 7, 8, 9 };
    TreeArena arena;
    TreeNode *old_nodes;
    TreeNode *old_root;
    size_t old_count;
    int old_key;

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 3U, 1U) == TREE_OK
    );
    old_nodes = arena.nodes;
    old_count = arena.count;
    old_root = arena.root;
    old_key = storage[0].key;

    REQUIRE(
        tree_arena_init(
            NULL,
            storage,
            keys,
            3U,
            0U
        ) == TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        tree_arena_init(
            &arena,
            NULL,
            keys,
            3U,
            0U
        ) == TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        tree_arena_init(
            &arena,
            storage,
            NULL,
            3U,
            0U
        ) == TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        tree_arena_init(
            &arena,
            storage,
            keys,
            3U,
            3U
        ) == TREE_ERR_OUT_OF_RANGE
    );
    REQUIRE(
        tree_arena_init(
            &arena,
            storage,
            keys,
            (size_t)TREE_ARENA_MAX_NODES + 1U,
            0U
        ) == TREE_ERR_OUT_OF_RANGE
    );
    REQUIRE(
        tree_arena_init(
            &arena,
            NULL,
            NULL,
            0U,
            0U
        ) == TREE_ERR_OUT_OF_RANGE
    );

    REQUIRE(arena.nodes == old_nodes);
    REQUIRE(arena.count == old_count);
    REQUIRE(arena.root == old_root);
    REQUIRE(storage[0].key == old_key);
    return true;
}

static bool test_checked_outputs_stay_unchanged_on_error(void)
{
    TreeArena arena;
    TreeNode storage[1];
    const int keys[1] = { 5 };
    bool is_leaf = true;
    size_t child_count = 77U;
    TreeFamily family = { 11U, 12U, 13U };

    REQUIRE(
        tree_node_is_leaf(NULL, &is_leaf) ==
        TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(is_leaf);
    REQUIRE(
        tree_node_is_leaf(&storage[0], NULL) ==
        TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(
        tree_node_child_count(NULL, &child_count) ==
        TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(child_count == 77U);

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 1U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_immediate_family(&arena, 1U, &family) ==
        TREE_ERR_OUT_OF_RANGE
    );
    REQUIRE(family.parent_index == 11U);
    REQUIRE(family.left_child_index == 12U);
    REQUIRE(family.right_child_index == 13U);
    REQUIRE(
        tree_immediate_family(&arena, 0U, NULL) ==
        TREE_ERR_INVALID_ARGUMENT
    );

    REQUIRE(strcmp(tree_status_name(TREE_OK), "ok") == 0);
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_INVALID_ARGUMENT),
            "invalid argument"
        ) == 0
    );
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_OUT_OF_RANGE),
            "index or count out of range"
        ) == 0
    );
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_OCCUPIED),
            "child position already occupied"
        ) == 0
    );
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_SELF_LINK),
            "node cannot be its own direct child"
        ) == 0
    );
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_INVALID_STRUCTURE),
            "arena does not satisfy the required tree rules"
        ) == 0
    );
    REQUIRE(
        strcmp(
            tree_status_name(TREE_ERR_NOT_BST),
            "tree keys do not satisfy strict BST ordering"
        ) == 0
    );
    return true;
}

static bool test_local_assignment_checks_and_preservation(void)
{
    TreeArena arena;
    TreeNode storage[3];
    const int keys[3] = { 8, 3, 10 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 3U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 1U) ==
        TREE_OK
    );
    REQUIRE(storage[0].left == &storage[1]);
    REQUIRE(storage[0].right == NULL);

    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 2U) ==
        TREE_ERR_OCCUPIED
    );
    REQUIRE(storage[0].left == &storage[1]);
    REQUIRE(
        tree_assign_child(&arena, 2U, TREE_SIDE_RIGHT, 2U) ==
        TREE_ERR_SELF_LINK
    );
    REQUIRE(storage[2].right == NULL);
    REQUIRE(
        tree_assign_child(
            &arena,
            0U,
            (TreeSide)99,
            2U
        ) == TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(storage[0].right == NULL);
    REQUIRE(
        tree_assign_child(&arena, 3U, TREE_SIDE_RIGHT, 2U) ==
        TREE_ERR_OUT_OF_RANGE
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_RIGHT, 3U) ==
        TREE_ERR_OUT_OF_RANGE
    );
    REQUIRE(storage[0].right == NULL);

    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_RIGHT, 2U) ==
        TREE_OK
    );
    REQUIRE(storage[0].right == &storage[2]);
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);
    return true;
}

static bool test_node_queries_and_immediate_family(void)
{
    TreeArena arena;
    TreeNode storage[5];
    const int keys[5] = { 8, 3, 10, 1, 6 };
    bool is_leaf = true;
    size_t child_count = 99U;
    TreeFamily family;
    TreeNode left_only;
    TreeNode right_only;

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 5U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 1U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_RIGHT, 2U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 1U, TREE_SIDE_LEFT, 3U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 1U, TREE_SIDE_RIGHT, 4U) ==
        TREE_OK
    );
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);

    REQUIRE(tree_node_is_leaf(&storage[0], &is_leaf) == TREE_OK);
    REQUIRE(!is_leaf);
    REQUIRE(
        tree_node_child_count(&storage[0], &child_count) == TREE_OK
    );
    REQUIRE(child_count == 2U);
    REQUIRE(tree_node_is_leaf(&storage[4], &is_leaf) == TREE_OK);
    REQUIRE(is_leaf);
    REQUIRE(
        tree_node_child_count(&storage[4], &child_count) == TREE_OK
    );
    REQUIRE(child_count == 0U);

    left_only.key = 20;
    left_only.left = &storage[4];
    left_only.right = NULL;
    REQUIRE(tree_node_is_leaf(&left_only, &is_leaf) == TREE_OK);
    REQUIRE(!is_leaf);
    REQUIRE(
        tree_node_child_count(&left_only, &child_count) == TREE_OK
    );
    REQUIRE(child_count == 1U);

    right_only.key = 21;
    right_only.left = NULL;
    right_only.right = &storage[4];
    REQUIRE(tree_node_is_leaf(&right_only, &is_leaf) == TREE_OK);
    REQUIRE(!is_leaf);
    REQUIRE(
        tree_node_child_count(&right_only, &child_count) == TREE_OK
    );
    REQUIRE(child_count == 1U);

    REQUIRE(
        tree_immediate_family(&arena, 0U, &family) == TREE_OK
    );
    REQUIRE(family.parent_index == TREE_NO_INDEX);
    REQUIRE(family.left_child_index == 1U);
    REQUIRE(family.right_child_index == 2U);

    REQUIRE(
        tree_immediate_family(&arena, 1U, &family) == TREE_OK
    );
    REQUIRE(family.parent_index == 0U);
    REQUIRE(family.left_child_index == 3U);
    REQUIRE(family.right_child_index == 4U);

    REQUIRE(
        tree_immediate_family(&arena, 4U, &family) == TREE_OK
    );
    REQUIRE(family.parent_index == 1U);
    REQUIRE(family.left_child_index == TREE_NO_INDEX);
    REQUIRE(family.right_child_index == TREE_NO_INDEX);
    return true;
}

static bool test_global_validator_rejects_shared_child(void)
{
    TreeArena arena;
    TreeNode storage[4];
    const int keys[4] = { 10, 5, 15, 3 };
    TreeFamily unchanged = { 20U, 21U, 22U };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 4U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 1U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_RIGHT, 2U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 1U, TREE_SIDE_LEFT, 3U) ==
        TREE_OK
    );
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);

    /*
     * The requested position is empty and is not a direct self-link, so the
     * local operation succeeds. The separate global check finds the defect.
     */
    REQUIRE(
        tree_assign_child(&arena, 2U, TREE_SIDE_RIGHT, 3U) ==
        TREE_OK
    );
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(
        tree_immediate_family(&arena, 3U, &unchanged) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(unchanged.parent_index == 20U);
    REQUIRE(unchanged.left_child_index == 21U);
    REQUIRE(unchanged.right_child_index == 22U);
    return true;
}

static bool test_global_validator_rejects_cycle(void)
{
    TreeArena arena;
    TreeNode storage[2];
    const int keys[2] = { 10, 5 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 2U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 1U) ==
        TREE_OK
    );
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);

    REQUIRE(
        tree_assign_child(&arena, 1U, TREE_SIDE_RIGHT, 0U) ==
        TREE_OK
    );
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    return true;
}

static bool test_bst_uses_whole_subtree_limits(void)
{
    TreeArena arena;
    TreeNode storage[4];
    const int keys[4] = { 10, 5, 15, 12 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 4U, 0U) == TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 1U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_RIGHT, 2U) ==
        TREE_OK
    );
    REQUIRE(
        tree_assign_child(&arena, 1U, TREE_SIDE_RIGHT, 3U) ==
        TREE_OK
    );
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);

    /*
     * 12 is greater than its immediate parent 5, but it is in the entire
     * left subtree of 10, so the global ordering rule rejects it.
     */
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_NOT_BST);
    storage[3].key = 7;
    REQUIRE(tree_validate_bst(&arena) == TREE_OK);
    storage[3].key = 10;
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_NOT_BST);
    return true;
}

int main(void)
{
    run_test(
        "empty and single-node initialization",
        test_empty_and_single_node_initialization
    );
    run_test(
        "initialization errors preserve state",
        test_init_errors_preserve_previous_state
    );
    run_test(
        "checked outputs stay unchanged on error",
        test_checked_outputs_stay_unchanged_on_error
    );
    run_test(
        "local assignment checks and preservation",
        test_local_assignment_checks_and_preservation
    );
    run_test(
        "node queries and immediate family",
        test_node_queries_and_immediate_family
    );
    run_test(
        "global validator rejects shared child",
        test_global_validator_rejects_shared_child
    );
    run_test(
        "global validator rejects cycle",
        test_global_validator_rejects_cycle
    );
    run_test(
        "BST uses whole-subtree limits",
        test_bst_uses_whole_subtree_limits
    );

    (void)printf(
        "\n%u test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
