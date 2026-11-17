#include <stdio.h>
#include "survey_fixtures.h"

static int smaller(int x, int y) { return x < y; }
static int larger(int x, int y) { return x > y; }
static int smaller_last_digit(int x, int y) { return x % 10 < y % 10; }

static void check_queue(void)
{
    assert(front >= 0 && front <= rear + 1 && rear < CAPACITY);
    for (int i = front + 1; i <= rear; ++i) {
        assert(!compare(queue[i], queue[i - 1]));
    }
}

static void test_queue(void)
{
    init_queue(smaller);
    assert(front == 0 && rear == -1 && compare == smaller);
    enqueue(7); enqueue(2); enqueue(5); check_queue();
    assert(dequeue() == 2);
    enqueue(1); check_queue();
    assert(dequeue() == 1 && dequeue() == 5 && dequeue() == 7);
    enqueue(9); assert(dequeue() == 9); /* Empty after consumption; no reset. */
    assert(front == 5 && rear == 4);

    init_queue(smaller_last_digit);
    const int input[] = {21, 11, 32, 1, 22};
    const int expected[] = {21, 11, 1, 32, 22};
    for (int i = 0; i < 5; ++i) { enqueue(input[i]); check_queue(); }
    for (int i = 0; i < 5; ++i) assert(dequeue() == expected[i]);

    init_queue(larger);
    for (int i = 0; i < CAPACITY; ++i) { enqueue(i); check_queue(); }
    assert(rear == CAPACITY - 1);
    for (int i = CAPACITY - 1; i >= 0; --i) assert(dequeue() == i);
    assert(front == CAPACITY && rear == CAPACITY - 1);
    /* Consumed storage is not reusable until init_queue resets both indices. */
    init_queue(smaller);
    enqueue(42); assert(dequeue() == 42);
}

static void test_user_state(void)
{
    restore_sample(); init_users();
    assert(latest_login_time() == 5);
    for (int id = 0; id < N_USERS; ++id) {
        assert(users[id].epoch == 0);
        assert(users[id].login == timelogs[id][0]);
        assert(users[id].logout == timelogs[id][1]);
    }
    assert(first_logout_id() == 2);
    assert(front == 1 && rear == 2 && queue[front] == 1 && queue[rear] == 0);
    assert(next_epoch(2) == 0 && users[2].login == 5 && users[2].logout == 7);
    assert(next_epoch(2) == 0 && users[2].login == 9 && users[2].logout == 14);
    assert(next_epoch(2) == -1);
    assert(users[2].epoch == N_EPOCHS); /* Failure increments epoch, retains times. */
    assert(users[2].login == 9 && users[2].logout == 14);
}

static void test_sample_trace(void)
{
    const int next_out[] = {1, 0, 2, 1, 0, 0};
    const int candidates[] = {5, 7, 8, 9, 12, 12};
    restore_sample(); init_users();
    int candidate = latest_login_time();
    int out = first_logout_id();
    int insertions = N_USERS, removals = 1, advances = 0;
    assert(out == 2 && candidate == 5);
    for (int step = 0; step < 6; ++step) {
        assert(candidate >= users[out].logout);
        assert(next_epoch(out) == 0); ++advances;
        if (users[out].login > candidate) candidate = users[out].login;
        enqueue(out); ++insertions; check_queue();
        out = dequeue(); ++removals;
        assert(out == next_out[step] && candidate == candidates[step]);
    }
    assert(candidate < users[out].logout && candidate == 12);
    assert(insertions == 9 && removals == 7 && advances == 6);
    assert(front == 7 && rear == 8 && queue[front] == 2 && queue[rear] == 1);
    assert(survey() == candidate && survey() == candidate); /* Test actual run too. */
}

static void test_boundaries(void)
{
    const int immediate[N_USERS][N_EPOCHS * 2] = {
        {0, 3, 4, 7, 8, 10}, {0, 3, 4, 7, 8, 10}, {0, 3, 4, 7, 8, 10}
    };
    const int endpoints[N_USERS][N_EPOCHS * 2] = {
        {0, 2, 4, 6, 8, 10}, {2, 4, 6, 8, 10, 12}, {0, 20, 21, 22, 23, 24}
    };
    const int exhausted[N_USERS][N_EPOCHS * 2] = {
        {0, 1, 2, 3, 4, 5}, {6, 7, 8, 9, 10, 11}, {6, 7, 8, 9, 10, 11}
    };
    load_logs(&immediate[0][0]); assert_valid_logs(); assert(survey() == 0);
    load_logs(&endpoints[0][0]); assert_valid_logs(); assert(survey() == -1);
    load_logs(&exhausted[0][0]); assert_valid_logs(); assert(survey() == -1);
    /* All users meet just below INT_MAX; no endpoint arithmetic in the lab. */
    for (int id = 0; id < N_USERS; ++id) {
        for (int e = 0; e < N_EPOCHS; ++e) {
            timelogs[id][2 * e] = INT_MAX - 6 + 2 * e;
            timelogs[id][2 * e + 1] = INT_MAX - 5 + 2 * e;
        }
    }
    assert_valid_logs(); assert(survey() == INT_MAX - 6);
    restore_sample(); assert(survey() == 12);
}

static void test_reference_schedules(void)
{
    uint32_t state = UINT32_C(20261114);
    int meetings = 0, misses = 0;
    for (int trial = 0; trial < 10000; ++trial) {
        generate_logs(&state); assert_valid_logs();
        int expected = interval_oracle();
        int before[N_USERS][N_EPOCHS * 2];
        memcpy(before, timelogs, sizeof before);
        assert(survey() == expected);
        assert(memcmp(before, timelogs, sizeof before) == 0);
        assert(rear < CAPACITY && rear + 1 <= N_USERS * N_EPOCHS);
        assert(front <= rear + 1);
        assert(survey() == expected);
        if (expected == -1) ++misses; else ++meetings;
    }
    assert(meetings > 0 && misses > 0);
    restore_sample(); assert(survey() == 12);
    printf("10000 independent reference schedules passed (%d meetings, %d misses).\n",
           meetings, misses);
}

int main(void)
{
    test_queue(); test_user_state(); test_sample_trace();
    test_boundaries(); test_reference_schedules();
    puts("Chapter 10 core passed: sorted queue, stable ties, epochs, trace and survey.");
    return 0;
}
