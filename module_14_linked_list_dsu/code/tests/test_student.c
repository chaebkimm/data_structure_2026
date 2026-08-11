#include "dsu.h"
#include "linked_list.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace all three bodies. Use only small synthetic values and identifiers.
 * Destroy every successfully initialized list on every return path.
 */
static bool test_list_lifecycle_deletion_allocation_and_cleanup(void)
{
    /*
     * TODO 1: Build a bounded list with duplicates. Test head, middle, tail,
     * and absent removal; exact first-match behavior; full rejection; forced
     * allocation failure with complete preservation; and leak-free destroy.
     */
    return false;
}

static bool test_tall_compression_equal_size_and_invalid_id(void)
{
    /*
     * TODO 2: Build the eight-element teaching forest. Verify exact parents
     * before and after two-pass compression, the smaller-root equal-size
     * rule, and unchanged DSU/output after an invalid identifier.
     */
    return false;
}

static bool test_relationship_cycles_components_and_claim_boundaries(void)
{
    /*
     * TODO 3: Process a relationship stream with a repeated connection and
     * a self-loop. Mark the first cycle, check component counts and connected
     * queries, then explain why shared membership does not grant trust.
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
        test_list_lifecycle_deletion_allocation_and_cleanup,
        "student list ownership test"
    );
    failures += run_test(
        test_tall_compression_equal_size_and_invalid_id,
        "student DSU compression test"
    );
    failures += run_test(
        test_relationship_cycles_components_and_claim_boundaries,
        "student relationship/cycle test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
