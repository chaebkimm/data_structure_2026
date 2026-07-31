#include "event_queue.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace the three TODO bodies. Destroy every successfully initialized
 * Queue on every return path.
 */
static bool test_fifo_including_capacity_one(void)
{
    /* TODO: check FIFO behavior, including a capacity-one Queue. */
    return false;
}

static bool test_wraparound_and_repeated_cycle(void)
{
    /* TODO: force wrap-around, then complete another enqueue/dequeue cycle. */
    return false;
}

static bool test_full_and_empty_failure_preservation(void)
{
    /*
     * TODO: prove a full enqueue failure preserves every field and
     * established slot. Then drain the Queue and prove an empty peek or
     * dequeue also preserves every field, stale slot, and prior output.
     */
    return false;
}

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
        test_fifo_including_capacity_one,
        "student FIFO/capacity-one test"
    );
    failures += run_test(
        test_wraparound_and_repeated_cycle,
        "student wrap-around/repeated-cycle test"
    );
    failures += run_test(
        test_full_and_empty_failure_preservation,
        "student full/empty failure-preservation test"
    );

    if (failures != 0) {
        puts("Complete all three student-authored tests.");
        return 1;
    }

    puts("All student-authored tests passed.");
    return 0;
}
