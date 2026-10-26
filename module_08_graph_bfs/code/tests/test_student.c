#include "graph_bfs.h"

#include <stdbool.h>
#include <stdio.h>

/*
 * Replace all three bodies. Use only small synthetic graphs and explain in
 * one comment what each test adds beyond the supplied visible examples.
 */

static bool test_cycle_merge_state(void)
{
    /*
     * TODO 1: Test exact visit order, discovered values, distances, and
     * predecessors on a graph containing both a merge and a cycle.
     */
    return false;
}

static bool test_reachable_source_and_unreachable_paths(void)
{
    /*
     * TODO 2: Test one multi-hop path, the one-vertex source path, and an
     * unreachable result that preserves a previously marked path.
     */
    return false;
}

static bool test_representation_equality_and_queue_boundary(void)
{
    /*
     * TODO 3: Build equivalent matrix/list graphs, compare every result
     * field, and test one too-small Queue limit with output preservation.
     */
    return false;
}

typedef bool (*TestFunction)(void);

static int run_test(TestFunction function, const char *name)
{
    bool passed = function();

    printf("%s: %s\n", name, passed ? "PASS" : "TODO/FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_cycle_merge_state,
        "student cycle/merge state test"
    );
    failures += run_test(
        test_reachable_source_and_unreachable_paths,
        "student path and unreachable test"
    );
    failures += run_test(
        test_representation_equality_and_queue_boundary,
        "student representation/boundary test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
