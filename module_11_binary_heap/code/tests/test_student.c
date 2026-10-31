#include "alert_priority_queue.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace all three bodies. Use synthetic alert IDs only. Destroy every
 * successfully initialized Queue on every return path.
 */
static bool test_sift_up_and_stable_ties(void)
{
    /*
     * TODO 1: Build a small Heap whose priorities require more than one
     * sift-up move and whose nonordering IDs include stable ties. Verify the
     * exact array trace, returned records, normal-operation comparisons, and
     * the separate size - 1 checker delta.
     */
    return false;
}

static bool test_better_child_and_missing_right(void)
{
    /*
     * TODO 2: Start from priorities [5,41,17,55,70], extract the root, and
     * verify [17,41,70,55], not the faulty left-first result. Also test an
     * extraction path with a lone left child and verify exact comparisons.
     */
    return false;
}

static bool test_growth_full_and_complete_preservation(void)
{
    /*
     * TODO 3: Cross at least two growth boundaries, check Heap order after
     * each mutation, fill all 64 slots, then prove a rejected insertion
     * preserves every field and all live records.
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
        test_sift_up_and_stable_ties,
        "student sift-up/stability test"
    );
    failures += run_test(
        test_better_child_and_missing_right,
        "student sift-down/child-boundary test"
    );
    failures += run_test(
        test_growth_full_and_complete_preservation,
        "student growth/full-preservation test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
