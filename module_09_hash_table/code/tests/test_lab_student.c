#include <assert.h>
#include <stdio.h>
#include "../../student/lab.c"

int main(void)
{
    /* Smoke test only. Add three original groups with claims and assertions:
       1. Signed hashes, key/data distinction, collision chains, find, and
          duplicate-key insertion (the newest matching node is returned).
       2. All ten slots, unchanged failed insertion, initialize, and reuse.
       3. Both two-sum methods: earlier/later index order, misses, duplicates,
          no self-pair, and repeated calls after a hit and a full miss.
       Keep sums and target - nums[i] representable as int. */
    two_sum_ht(0); /* This function calls initialize itself. */
    assert(answer[0] == 4 && answer[1] == 5);
    assert(hnodes_unused == 5);
    initialize();
    assert(hnodes_unused == 0);
    puts("Module 09 student smoke test passed; add three original groups.");
    return 0;
}
