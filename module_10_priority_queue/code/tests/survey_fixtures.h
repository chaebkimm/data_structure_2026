#ifndef SURVEY_FIXTURES_H
#define SURVEY_FIXTURES_H
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include "lab.c"

static const int sample_logs[N_USERS][N_EPOCHS * 2] = {
    {5, 6, 8, 9, 11, 13},
    {2, 5, 7, 8, 12, 15},
    {1, 3, 5, 7, 9, 14}
};

static inline void load_logs(const int *logs)
{
    memcpy(timelogs, logs, sizeof timelogs);
}

static inline void restore_sample(void)
{
    load_logs(&sample_logs[0][0]);
}

/* Enumerate interval combinations, independently of priority selection and
   epoch advancement. A combination overlaps exactly when max(login)<min(logout).
   No time stepping or arithmetic on endpoint values is needed. */
static inline int interval_oracle(void)
{
    int epochs[N_USERS] = {0};
    int best = -1;
    for (;;) {
        int latest = 0;
        int earliest = INT_MAX;
        for (int id = 0; id < N_USERS; ++id) {
            int e = epochs[id];
            if (timelogs[id][2 * e] > latest) latest = timelogs[id][2 * e];
            if (timelogs[id][2 * e + 1] < earliest) earliest = timelogs[id][2 * e + 1];
        }
        if (latest < earliest && (best == -1 || latest < best)) best = latest;
        int id = 0;
        while (id < N_USERS) {
            if (++epochs[id] < N_EPOCHS) break;
            epochs[id++] = 0;
        }
        if (id == N_USERS) return best;
    }
}

static inline void assert_valid_logs(void)
{
    for (int id = 0; id < N_USERS; ++id) {
        for (int e = 0; e < N_EPOCHS; ++e) {
            int on = timelogs[id][2 * e];
            int off = timelogs[id][2 * e + 1];
            assert(on >= 0 && on < off);
            if (e > 0) assert(timelogs[id][2 * e - 1] <= on);
        }
    }
}

static inline uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static inline void generate_logs(uint32_t *state)
{
    for (int id = 0; id < N_USERS; ++id) {
        int t = (int)(next_random(state) % UINT32_C(5));
        for (int e = 0; e < N_EPOCHS; ++e) {
            timelogs[id][2 * e] = t;
            t += 1 + (int)(next_random(state) % UINT32_C(5));
            timelogs[id][2 * e + 1] = t;
            t += (int)(next_random(state) % UINT32_C(5));
        }
    }
}
#endif
