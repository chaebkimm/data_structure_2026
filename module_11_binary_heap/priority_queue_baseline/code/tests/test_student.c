#include "alert_priority_queue.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace all three bodies. Use synthetic alert IDs only, and destroy every
 * successfully initialized Queue on every return path.
 */
static bool test_mixed_priorities_and_stable_ties(void)
{
    /*
     * TODO 1: Use nonordering alert IDs. Insert mixed priorities with at
     * least three ties, then verify every returned ID, priority, and arrival
     * sequence follows priority first and stable arrival order second.
     */
    return false;
}

static bool test_growth_swap_then_insert(void)
{
    /*
     * TODO 2: Cross a growth boundary, extract a minimum whose swap-with-last
     * removal scrambles physical storage, then insert another alert. Verify
     * that later extraction order still follows the abstract comparator.
     */
    return false;
}

static bool test_empty_and_full_failure_preservation(void)
{
    /*
     * TODO 3: Prove an empty peek or extraction preserves its prior output.
     * Then fill all 64 slots and prove one rejected insertion preserves every
     * Queue field and all 64 live records.
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
        test_mixed_priorities_and_stable_ties,
        "student priority/stability test"
    );
    failures += run_test(
        test_growth_swap_then_insert,
        "student growth/swap/insert test"
    );
    failures += run_test(
        test_empty_and_full_failure_preservation,
        "student empty/full preservation test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
