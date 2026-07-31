#include "tree_bfs.h"

#include <stdbool.h>
#include <stdio.h>

/*
 * Replace all three bodies. Each test should use a small synthetic tree and
 * explain in one comment what it adds beyond the supplied core tests.
 */

static bool test_level_order_and_depths(void)
{
    /* TODO: verify an exact left-first level order with exact depths. */
    return false;
}

static bool test_shallowest_duplicate_and_missing_preservation(void)
{
    /*
     * TODO: repeat a key at two locations, then test both the selected
     * shallowest match and one missing-key output-preservation case.
     */
    return false;
}

static bool test_height_and_queue_boundary(void)
{
    /*
     * TODO: check edge height and one too-small Queue failure that preserves
     * its prior height output.
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
        test_level_order_and_depths,
        "student level-order/depth test"
    );
    failures += run_test(
        test_shallowest_duplicate_and_missing_preservation,
        "student shallowest/missing test"
    );
    failures += run_test(
        test_height_and_queue_boundary,
        "student height/boundary test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
