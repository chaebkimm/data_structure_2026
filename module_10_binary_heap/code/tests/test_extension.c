#include "alert_priority_queue.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef ALERT_PRIORITY_QUEUE_TESTING
#error "Extension tests require -DALERT_PRIORITY_QUEUE_TESTING."
#endif

typedef bool (*TestFunction)(void);

static AlertPriorityQueue *active_queue = NULL;
static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

static void track_queue(AlertPriorityQueue *queue)
{
    active_queue = queue;
}

static void release_queue(void)
{
    if (active_queue != NULL) {
        alert_priority_queue_destroy(active_queue);
        active_queue = NULL;
    }
}

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            release_queue();                                                 \
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool records_equal(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    return left->alert_id == right->alert_id &&
        left->priority == right->priority &&
        left->arrival_sequence == right->arrival_sequence;
}

static bool record_precedes(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    if (left->priority != right->priority) {
        return left->priority < right->priority;
    }
    return left->arrival_sequence < right->arrival_sequence;
}

static size_t reference_minimum_index(
    const AlertRecord *records,
    size_t count
)
{
    size_t minimum = 0U;
    size_t index;

    for (index = 1U; index < count; ++index) {
        if (record_precedes(&records[index], &records[minimum])) {
            minimum = index;
        }
    }
    return minimum;
}

static bool queue_matches_reference(
    const AlertPriorityQueue *queue,
    const AlertRecord *reference,
    size_t reference_size
)
{
    bool matched[ALERT_PRIORITY_QUEUE_MAX_CAPACITY] = {false};
    size_t heap_index;

    if (queue->size != reference_size) {
        return false;
    }

    for (heap_index = 0U;
         heap_index < queue->size;
         ++heap_index) {
        size_t reference_index;
        bool found = false;

        for (reference_index = 0U;
             reference_index < reference_size;
             ++reference_index) {
            if (!matched[reference_index] &&
                records_equal(
                    &queue->data[heap_index],
                    &reference[reference_index]
                )) {
                matched[reference_index] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

static bool check_heap_and_separate_delta(AlertPriorityQueue *queue)
{
    bool is_heap = false;
    size_t before = queue->comparison_count;
    size_t expected = queue->size == 0U
        ? 0U
        : queue->size - 1U;

    REQUIRE(
        alert_priority_queue_is_min_heap(queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(is_heap);
    REQUIRE(queue->comparison_count - before == expected);
    return true;
}

static void run_test(const char *name, TestFunction test)
{
    bool passed;

    tests_run += 1U;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        (void)printf("FAIL %s\n", name);
    }
}

static size_t insertion_depth(size_t index)
{
    size_t depth = 0U;

    while (index > 0U) {
        index = (index - 1U) / 2U;
        depth += 1U;
    }
    return depth;
}

static bool test_ascending_descending_and_equal_workloads(void)
{
    enum {
        WORKLOAD_COUNT = 64
    };

    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    size_t total;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    total = 0U;
    for (index = 0U; index < (size_t)WORKLOAD_COUNT; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                (int)index,
                index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        if (index == 0U) {
            REQUIRE(queue.capacity == 4U);
        } else if (index == 4U) {
            REQUIRE(queue.capacity == 8U);
        } else if (index == 8U) {
            REQUIRE(queue.capacity == 16U);
        } else if (index == 16U) {
            REQUIRE(queue.capacity == 32U);
        } else if (index == 32U) {
            REQUIRE(queue.capacity == 64U);
        }
        total += queue.comparison_count;
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(total == 63U);
    for (index = 0U; index < (size_t)WORKLOAD_COUNT; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.priority == index);
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    release_queue();

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    total = 0U;
    for (index = 0U; index < (size_t)WORKLOAD_COUNT; ++index) {
        size_t priority = (size_t)WORKLOAD_COUNT - index;

        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                (int)index,
                priority
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        total += queue.comparison_count;
        REQUIRE(queue.comparison_count == insertion_depth(index));
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(total > 63U);
    for (index = 1U; index <= (size_t)WORKLOAD_COUNT; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.priority == index);
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    release_queue();

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    total = 0U;
    for (index = 0U; index < (size_t)WORKLOAD_COUNT; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                1000 - (int)index,
                7U
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        total += queue.comparison_count;
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(total == 63U);
    for (index = 0U; index < (size_t)WORKLOAD_COUNT; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.alert_id == 1000 - (int)index);
        REQUIRE(output.arrival_sequence == index);
        REQUIRE(check_heap_and_separate_delta(&queue));
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    release_queue();
    return true;
}

static bool test_every_size_and_lone_left_paths(void)
{
    AlertPriorityQueue queue = {0};
    size_t count;

    for (count = 2U;
         count <= (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY;
         ++count) {
        AlertRecord output = {0, 0U, 0U};
        bool is_heap = false;
        size_t index;

        REQUIRE(
            alert_priority_queue_init(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        track_queue(&queue);
        for (index = 0U; index < count; ++index) {
            REQUIRE(
                alert_priority_queue_insert(
                    &queue,
                    (int)index,
                    index
                ) == ALERT_PRIORITY_QUEUE_OK
            );
        }
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.priority == 0U);
        REQUIRE(
            alert_priority_queue_is_min_heap(
                &queue,
                &is_heap
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(is_heap);
        release_queue();
    }
    return true;
}

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static bool test_deterministic_differential_sequence(void)
{
    enum {
        STEPS = 5000
    };

    AlertPriorityQueue queue = {0};
    AlertRecord reference[ALERT_PRIORITY_QUEUE_MAX_CAPACITY];
    size_t reference_size = 0U;
    size_t reference_next_sequence = 0U;
    uint32_t state = UINT32_C(0xB1A2E026);
    int step;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    for (step = 0; step < STEPS; ++step) {
        uint32_t random_value = next_random(&state);
        unsigned int operation =
            (unsigned int)(random_value % 3U);

        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );

        if (operation == 0U) {
            int alert_id =
                (int)(random_value & UINT32_C(0x7FFF));
            size_t priority =
                (size_t)(next_random(&state) % UINT32_C(17));
            AlertPriorityQueueStatus expected =
                reference_size ==
                    (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY
                ? ALERT_PRIORITY_QUEUE_FULL
                : ALERT_PRIORITY_QUEUE_OK;

            REQUIRE(
                alert_priority_queue_insert(
                    &queue,
                    alert_id,
                    priority
                ) == expected
            );
            if (expected == ALERT_PRIORITY_QUEUE_OK) {
                reference[reference_size].alert_id = alert_id;
                reference[reference_size].priority = priority;
                reference[reference_size].arrival_sequence =
                    reference_next_sequence;
                reference_size += 1U;
                reference_next_sequence += 1U;
            } else {
                REQUIRE(queue.comparison_count == 0U);
            }
        } else if (operation == 1U) {
            AlertRecord output = {-1, 700U, 800U};
            AlertRecord before = output;

            if (reference_size == 0U) {
                REQUIRE(
                    alert_priority_queue_peek_min(
                        &queue,
                        &output
                    ) == ALERT_PRIORITY_QUEUE_EMPTY
                );
                REQUIRE(records_equal(&output, &before));
            } else {
                size_t minimum = reference_minimum_index(
                    reference,
                    reference_size
                );

                REQUIRE(
                    alert_priority_queue_peek_min(
                        &queue,
                        &output
                    ) == ALERT_PRIORITY_QUEUE_OK
                );
                REQUIRE(records_equal(
                    &output,
                    &reference[minimum]
                ));
                REQUIRE(queue.comparison_count == 0U);
            }
        } else {
            AlertRecord output = {-2, 900U, 1000U};
            AlertRecord before = output;

            if (reference_size == 0U) {
                REQUIRE(
                    alert_priority_queue_extract_min(
                        &queue,
                        &output
                    ) == ALERT_PRIORITY_QUEUE_EMPTY
                );
                REQUIRE(records_equal(&output, &before));
            } else {
                size_t minimum = reference_minimum_index(
                    reference,
                    reference_size
                );
                AlertRecord expected = reference[minimum];
                size_t index;

                REQUIRE(
                    alert_priority_queue_extract_min(
                        &queue,
                        &output
                    ) == ALERT_PRIORITY_QUEUE_OK
                );
                REQUIRE(records_equal(&output, &expected));
                for (index = minimum;
                     index + 1U < reference_size;
                     ++index) {
                    reference[index] = reference[index + 1U];
                }
                reference_size -= 1U;
                if (reference_size == 0U) {
                    reference_next_sequence = 0U;
                }
            }
        }

        REQUIRE(
            alert_priority_queue_validate(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(queue.next_sequence == reference_next_sequence);
        REQUIRE(queue_matches_reference(
            &queue,
            reference,
            reference_size
        ));
        REQUIRE(check_heap_and_separate_delta(&queue));
    }

    release_queue();
    return true;
}

static bool test_extreme_values_and_checker_continues(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    bool is_heap = true;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, INT_MAX, SIZE_MAX) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, INT_MIN, 0U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, -1, 0U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == INT_MIN);
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == -1);

    REQUIRE(
        alert_priority_queue_insert(&queue, 4, 3U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 5, 4U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 6, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    queue.data[1].priority = 0U;
    queue.comparison_count = 20U;
    REQUIRE(
        alert_priority_queue_is_min_heap(&queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(!is_heap);
    REQUIRE(queue.comparison_count == 23U);
    release_queue();
    return true;
}

int main(void)
{
    run_test(
        "ascending, descending, and equal workloads",
        test_ascending_descending_and_equal_workloads
    );
    run_test(
        "every size and lone-left paths",
        test_every_size_and_lone_left_paths
    );
    run_test(
        "deterministic differential sequence",
        test_deterministic_differential_sequence
    );
    run_test(
        "extreme values and checker continuation",
        test_extreme_values_and_checker_continues
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
