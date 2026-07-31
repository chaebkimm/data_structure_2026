#include "tree_arena.h"

#include <limits.h>
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

static bool test_links_and_root_must_stay_inside_arena(void)
{
    TreeArena arena;
    TreeNode storage[1];
    TreeNode outside = { 99, NULL, NULL };
    const int keys[1] = { 10 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 1U, 0U) == TREE_OK
    );
    storage[0].left = &outside;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_INVALID_STRUCTURE);

    storage[0].left = NULL;
    arena.root = &outside;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    return true;
}

static bool test_maximum_length_chain(void)
{
    TreeArena arena;
    TreeNode storage[TREE_ARENA_MAX_NODES];
    int keys[TREE_ARENA_MAX_NODES];
    size_t index;
    TreeFamily family;

    for (index = 0U;
         index < (size_t)TREE_ARENA_MAX_NODES;
         ++index) {
        keys[index] = (int)index;
    }

    REQUIRE(
        tree_arena_init(
            &arena,
            storage,
            keys,
            (size_t)TREE_ARENA_MAX_NODES,
            0U
        ) == TREE_OK
    );

    for (index = 0U;
         index + 1U < (size_t)TREE_ARENA_MAX_NODES;
         ++index) {
        storage[index].right = &storage[index + 1U];
    }

    REQUIRE(tree_validate_structure(&arena) == TREE_OK);
    REQUIRE(tree_validate_bst(&arena) == TREE_OK);
    REQUIRE(
        tree_immediate_family(
            &arena,
            (size_t)TREE_ARENA_MAX_NODES - 1U,
            &family
        ) == TREE_OK
    );
    REQUIRE(
        family.parent_index ==
        (size_t)TREE_ARENA_MAX_NODES - 2U
    );
    REQUIRE(family.left_child_index == TREE_NO_INDEX);
    REQUIRE(family.right_child_index == TREE_NO_INDEX);
    return true;
}

static bool test_integer_extremes_and_duplicate_policy(void)
{
    TreeArena arena;
    TreeNode storage[3];
    const int keys[3] = { INT_MIN, 0, INT_MAX };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 3U, 1U) == TREE_OK
    );
    storage[1].left = &storage[0];
    storage[1].right = &storage[2];
    REQUIRE(tree_validate_structure(&arena) == TREE_OK);
    REQUIRE(tree_validate_bst(&arena) == TREE_OK);

    storage[2].key = 0;
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_NOT_BST);
    return true;
}

static bool test_unreachable_node_is_rejected(void)
{
    TreeArena arena;
    TreeNode storage[3];
    const int keys[3] = { 10, 5, 15 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 3U, 0U) == TREE_OK
    );
    storage[0].left = &storage[1];

    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_INVALID_STRUCTURE);
    return true;
}

static bool test_disconnected_cycle_is_rejected(void)
{
    TreeArena arena;
    TreeNode storage[4];
    const int keys[4] = { 10, 5, 20, 30 };

    REQUIRE(
        tree_arena_init(&arena, storage, keys, 4U, 0U) == TREE_OK
    );

    storage[0].left = &storage[1];
    storage[2].right = &storage[3];
    storage[3].left = &storage[2];

    /*
     * Every non-root node has one incoming link, but nodes 2 and 3 cannot
     * be reached by following child links from the root.
     */
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_INVALID_STRUCTURE);
    return true;
}

static bool test_malformed_container_states_and_unknown_status(void)
{
    TreeNode storage[1] = { { 10, NULL, NULL } };
    TreeNode outside = { 20, NULL, NULL };
    TreeArena arena;
    TreeFamily unchanged = { 70U, 71U, 72U };

    REQUIRE(
        tree_validate_structure(NULL) == TREE_ERR_INVALID_ARGUMENT
    );
    REQUIRE(tree_validate_bst(NULL) == TREE_ERR_INVALID_ARGUMENT);

    arena.nodes = storage;
    arena.count = 0U;
    arena.root = NULL;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );

    arena.nodes = NULL;
    arena.count = 0U;
    arena.root = &outside;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );

    arena.nodes = NULL;
    arena.count = 1U;
    arena.root = NULL;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );

    arena.nodes = storage;
    arena.count = 1U;
    arena.root = NULL;
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );

    arena.nodes = storage;
    arena.count = (size_t)TREE_ARENA_MAX_NODES + 1U;
    arena.root = &storage[0];
    REQUIRE(
        tree_validate_structure(&arena) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(tree_validate_bst(&arena) == TREE_ERR_INVALID_STRUCTURE);
    REQUIRE(
        tree_assign_child(&arena, 0U, TREE_SIDE_LEFT, 0U) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(
        tree_immediate_family(&arena, 0U, &unchanged) ==
        TREE_ERR_INVALID_STRUCTURE
    );
    REQUIRE(unchanged.parent_index == 70U);
    REQUIRE(unchanged.left_child_index == 71U);
    REQUIRE(unchanged.right_child_index == 72U);

    REQUIRE(
        strcmp(
            tree_status_name((TreeStatus)999),
            "unknown TreeStatus"
        ) == 0
    );
    return true;
}

int main(void)
{
    run_test(
        "links and root stay inside arena",
        test_links_and_root_must_stay_inside_arena
    );
    run_test("maximum-length chain", test_maximum_length_chain);
    run_test(
        "integer extremes and duplicate policy",
        test_integer_extremes_and_duplicate_policy
    );
    run_test(
        "unreachable node is rejected",
        test_unreachable_node_is_rejected
    );
    run_test(
        "disconnected cycle is rejected",
        test_disconnected_cycle_is_rejected
    );
    run_test(
        "malformed containers and unknown status",
        test_malformed_container_states_and_unknown_status
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
