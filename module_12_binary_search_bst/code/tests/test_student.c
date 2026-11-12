#include "avl_tree.h"
#include "bst_baseline.h"
#include "tree_model.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace all three bodies. Use small, synthetic keys. Destroy every tree
 * that successfully receives an allocated node on every return path.
 */
static bool test_rotations_middle_subtrees_and_height_order(void)
{
    /*
     * TODO 1: Test left and right rotations with a non-NULL middle subtree.
     * Then test the LL, RR, LR, and RL three-key examples and exact heights.
     */
    return false;
}

static bool test_recursive_insert_balance_and_comparison_traces(void)
{
    /*
     * TODO 2: Insert ascending, descending, and fixed mixed keys 1 through
     * 15 into both trees. Verify actual heights, AVL root 8, validation, and
     * target/miss comparison counts.
     */
    return false;
}

static bool test_atomic_failures_validation_and_cleanup(void)
{
    /*
     * TODO 3: Check duplicate, full, and forced-allocation preservation.
     * Forge cycle, shared-node, ordering, size, stale-height, and unbalanced
     * examples for the validators, then prove cleanup returns to zero leaks.
     */
    return false;
}

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();

    (void)printf(
        "%s: %s\n",
        name,
        passed ? "PASS" : "TODO/FAIL"
    );
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_rotations_middle_subtrees_and_height_order,
        "student rotation test"
    );
    failures += run_test(
        test_recursive_insert_balance_and_comparison_traces,
        "student insertion and comparison test"
    );
    failures += run_test(
        test_atomic_failures_validation_and_cleanup,
        "student atomicity, validation, and cleanup test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
