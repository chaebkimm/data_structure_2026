#include "hash_table.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/* Replace all three bodies and destroy every initialized table on all paths. */
static bool test_collision_wrap_and_exact_probes(void)
{
    /*
     * TODO 1: Insert colliding keys 10, 18, and 26, then a wrapping group
     * 7, 15, and 23 in a fresh table. Verify placement, lookup results, and
     * every exact probe count, including a terminating EMPTY on a miss.
     */
    return false;
}

static bool test_tombstone_reachability_and_duplicate_prevention(void)
{
    /*
     * TODO 2: Delete the middle of a collision chain. Prove a later key is
     * still reachable, updating it does not create a duplicate, and a new
     * colliding key reuses the first tombstone only after a complete search.
     */
    return false;
}

static bool test_maintenance_and_failure_preservation(void)
{
    /*
     * TODO 3: Trigger one doubling and one same-capacity compaction. Verify
     * all mappings and counts, then force a maintenance allocation failure
     * and prove the table and result output remain completely unchanged.
     */
    return false;
}

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();

    (void)printf("%s: %s\n", name, passed ? "PASS" : "INCOMPLETE/FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_collision_wrap_and_exact_probes,
        "student collision/wrap/probe test"
    );
    failures += run_test(
        test_tombstone_reachability_and_duplicate_prevention,
        "student tombstone/duplicate test"
    );
    failures += run_test(
        test_maintenance_and_failure_preservation,
        "student maintenance/preservation test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored test groups.");
        return 1;
    }
    puts("All student-authored hash-table tests passed.");
    return 0;
}
