#include <stdio.h>
#include "survey_fixtures.h"

/* Select the earliest current logout with a fresh linear scan. Local epochs
   and direct input reads avoid the lab queue, comparator and user helpers. */
static int scan_survey(void)
{
    int epochs[N_USERS] = {0};
    int candidate = 0;
    for (int id = 0; id < N_USERS; ++id) {
        if (timelogs[id][0] > candidate) candidate = timelogs[id][0];
    }
    for (;;) {
        int out = 0;
        for (int id = 1; id < N_USERS; ++id) {
            if (timelogs[id][epochs[id] * 2 + 1] <
                timelogs[out][epochs[out] * 2 + 1]) out = id;
        }
        if (candidate < timelogs[out][epochs[out] * 2 + 1]) return candidate;
        if (++epochs[out] == N_EPOCHS) return -1;
        int on = timelogs[out][epochs[out] * 2];
        if (on > candidate) candidate = on;
    }
}

int main(void)
{
    restore_sample();
    assert(survey() == 12 && scan_survey() == 12 && interval_oracle() == 12);
    puts("Sample: sorted queue = linear logout scan = interval oracle = 12.");
    const int endpoints[N_USERS][N_EPOCHS * 2] = {
        {0, 2, 4, 6, 8, 10}, {2, 4, 6, 8, 10, 12}, {0, 20, 21, 22, 23, 24}
    };
    load_logs(&endpoints[0][0]);
    assert(survey() == -1 && scan_survey() == -1 && interval_oracle() == -1);
    uint32_t state = UINT32_C(10026);
    for (int trial = 0; trial < 1000; ++trial) {
        generate_logs(&state); assert_valid_logs();
        int expected = interval_oracle();
        assert(survey() == expected && scan_survey() == expected);
    }
    restore_sample();
    puts("Endpoint-only contact and 1000 generated comparisons passed.");
    puts("For U users and A advances: sorted queue O(U^2 + A*U), scan O(U + A*U).");
    puts("Both advance the same kind of blocking interval; no speedup is claimed.");
    return 0;
}
