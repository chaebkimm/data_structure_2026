#include <assert.h>
#include <stdio.h>
#include "../../student/lab.c"

int main(void)
{
    /* Smoke test only. Add three original groups with claims and assertions:
       1. Normalized hashes, collisions, chain order, and find_data.
       2. Pool exhaustion, unchanged failure state, reset, and reuse.
       3. Two sum: valid earlier indices, misses, duplicates, repeated calls.
       Keep sums and target - nums[i] representable as int. */
    init_lnodes_pool();
    two_sum_ht(0);
    assert(answer[0] == 5 && answer[1] == 4);
    init_hashtable();
    puts("Module 09 student smoke test passed; add three original groups.");
    return 0;
}
