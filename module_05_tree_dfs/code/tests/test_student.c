#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>

/*
 * Replace each TODO body with one focused test. Keep the three categories:
 *
 * 1. traversal order or flag preservation;
 * 2. a boundary or failure that preserves an output; and
 * 3. BST search or postorder cleanup.
 *
 * Add a short comment above each test explaining what it adds beyond the
 * supplied core tests.
 */

static bool test_traversal_or_flags(void)
{
    /* TODO: construct a small synthetic tree and check exact visits. */
    return false;
}

static bool test_boundary_or_failure_preservation(void)
{
    /* TODO: mark an output, cause one failure, and prove it stayed marked. */
    return false;
}

static bool test_search_or_cleanup(void)
{
    /* TODO: test one BST search path or complete ownership cleanup. */
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
        test_traversal_or_flags,
        "student traversal/flags test"
    );
    failures += run_test(
        test_boundary_or_failure_preservation,
        "student boundary/failure test"
    );
    failures += run_test(
        test_search_or_cleanup,
        "student search/cleanup test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
