#include "alert_priority_queue.h"

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

static void copy_records(
    const AlertRecord *records,
    size_t count,
    AlertRecord *out_copy
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        out_copy[index] = records[index];
    }
}

static bool record_arrays_equal(
    const AlertRecord *left,
    const AlertRecord *right,
    size_t count
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        if (!records_equal(&left[index], &right[index])) {
            return false;
        }
    }
    return true;
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

static size_t add_scan_comparisons(size_t old_count, size_t size)
{
    size_t index;
    size_t result = old_count;

    for (index = 1U; index < size; ++index) {
        if (result < SIZE_MAX) {
            result += 1U;
        }
    }
    return result;
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

static bool test_exact_growth_steps_and_full_precedence(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord before[ALERT_PRIORITY_QUEUE_MAX_CAPACITY];
    AlertRecord output = {0, 0U, 0U};
    AlertRecord *pointer;
    size_t comparison_before;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U;
         index < (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY;
         ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                (int)index,
                index % 7U
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
    }
    REQUIRE(queue.size == 64U);
    REQUIRE(queue.next_sequence == 64U);
    REQUIRE(queue.comparison_count == 0U);
    pointer = queue.data;
    copy_records(queue.data, 64U, before);

    queue.next_sequence = SIZE_MAX;
    REQUIRE(
        alert_priority_queue_validate(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 999, 0U) ==
        ALERT_PRIORITY_QUEUE_FULL
    );
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.size == 64U);
    REQUIRE(queue.capacity == 64U);
    REQUIRE(queue.next_sequence == SIZE_MAX);
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(record_arrays_equal(queue.data, before, 64U));

    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.size == 63U);
    comparison_before = queue.comparison_count;
    copy_records(queue.data, 64U, before);
    REQUIRE(
        alert_priority_queue_insert(&queue, 1000, 0U) ==
        ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
    );
    REQUIRE(queue.size == 63U);
    REQUIRE(queue.next_sequence == SIZE_MAX);
    REQUIRE(queue.comparison_count == comparison_before);
    REQUIRE(record_arrays_equal(queue.data, before, 64U));
    release_queue();
    return true;
}

static bool test_sequence_exhaustion_preserves_every_slot(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord before[4];
    AlertRecord output = {0, 0U, 0U};
    AlertRecord *pointer;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                31 + (int)index,
                2U + index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.size == 4U);
    REQUIRE(queue.capacity == 4U);
    queue.next_sequence = SIZE_MAX;
    pointer = queue.data;
    copy_records(queue.data, 4U, before);

    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 35, 1U) ==
        ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
    );
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.size == 4U);
    REQUIRE(queue.capacity == 4U);
    REQUIRE(queue.next_sequence == SIZE_MAX);
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(record_arrays_equal(queue.data, before, 4U));

    /*
     * Restore the actual next sequence. The still-pending hook proves that
     * sequence exhaustion was reported before any growth attempt.
     */
    queue.next_sequence = 4U;
    REQUIRE(
        alert_priority_queue_insert(&queue, 35, 1U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.size == 4U);
    REQUIRE(queue.capacity == 4U);
    REQUIRE(queue.next_sequence == 4U);
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(record_arrays_equal(queue.data, before, 4U));

    REQUIRE(
        alert_priority_queue_insert(&queue, 35, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.size == 5U);
    REQUIRE(queue.capacity == 8U);
    REQUIRE(queue.next_sequence == 5U);
    REQUIRE(queue.data[4].arrival_sequence == 4U);

    queue.next_sequence = SIZE_MAX;
    for (index = 0U; index < 5U; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.next_sequence == 0U);
    REQUIRE(
        alert_priority_queue_insert(&queue, 36, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.data[0].arrival_sequence == 0U);
    release_queue();
    return true;
}

static bool test_equal_priority_stability_after_swaps(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    int expected[] = {10, 20, 30, 40, 50, 60};
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 10, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 20, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 30, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 40, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == expected[0]);
    REQUIRE(
        alert_priority_queue_insert(&queue, 50, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 60, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );

    for (index = 1U; index < 6U; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.alert_id == expected[index]);
    }
    REQUIRE(queue.next_sequence == 0U);
    release_queue();
    return true;
}

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static bool queue_matches_reference(
    const AlertPriorityQueue *queue,
    const AlertRecord *reference,
    size_t reference_size
)
{
    bool matched[ALERT_PRIORITY_QUEUE_MAX_CAPACITY] = {false};
    size_t queue_index;

    if (queue->size != reference_size) {
        return false;
    }

    for (queue_index = 0U;
         queue_index < queue->size;
         ++queue_index) {
        size_t reference_index;
        bool found = false;

        for (reference_index = 0U;
             reference_index < reference_size;
             ++reference_index) {
            if (!matched[reference_index] &&
                records_equal(
                    &queue->data[queue_index],
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

static bool test_deterministic_differential_sequence(void)
{
    enum {
        STEPS = 4000
    };

    AlertPriorityQueue queue = {0};
    AlertRecord reference[ALERT_PRIORITY_QUEUE_MAX_CAPACITY];
    size_t reference_size = 0U;
    size_t reference_next_sequence = 0U;
    size_t reference_comparisons = 0U;
    size_t maximum_size = 0U;
    bool saw_tied_priority = false;
    bool saw_multi_record_peek = false;
    bool saw_multi_record_extract = false;
    uint32_t state = UINT32_C(0xA17E2026);
    int step;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    for (step = 0; step < STEPS; ++step) {
        uint32_t random_value = next_random(&state);
        unsigned int operation =
            (unsigned int)((random_value >> 16) % 4U);

        if (operation == 0U) {
            int alert_id =
                (int)(random_value & UINT32_C(0x7FFF));
            size_t priority =
                (size_t)((random_value >> 4) % UINT32_C(13));
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
                for (size_t index = 0U;
                     index < reference_size;
                     ++index) {
                    if (reference[index].priority == priority) {
                        saw_tied_priority = true;
                    }
                }
                reference_size += 1U;
                reference_next_sequence += 1U;
                if (reference_size > maximum_size) {
                    maximum_size = reference_size;
                }
            }
        } else if (operation == 1U) {
            AlertRecord output = {-1, 777U, 888U};
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

                if (reference_size > 1U) {
                    saw_multi_record_peek = true;
                }
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
                reference_comparisons = add_scan_comparisons(
                    reference_comparisons,
                    reference_size
                );
            }
        } else if (operation == 2U) {
            AlertRecord output = {-2, 999U, 1000U};
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

                if (reference_size > 1U) {
                    saw_multi_record_extract = true;
                }
                REQUIRE(
                    alert_priority_queue_extract_min(
                        &queue,
                        &output
                    ) == ALERT_PRIORITY_QUEUE_OK
                );
                REQUIRE(records_equal(&output, &expected));
                reference_comparisons = add_scan_comparisons(
                    reference_comparisons,
                    reference_size
                );
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
        } else {
            REQUIRE(
                alert_priority_queue_reset_comparisons(&queue) ==
                ALERT_PRIORITY_QUEUE_OK
            );
            reference_comparisons = 0U;
        }

        REQUIRE(
            alert_priority_queue_validate(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(queue.next_sequence == reference_next_sequence);
        REQUIRE(queue.comparison_count == reference_comparisons);
        REQUIRE(queue_matches_reference(
            &queue,
            reference,
            reference_size
        ));
    }

    REQUIRE(maximum_size >= 9U);
    REQUIRE(saw_tied_priority);
    REQUIRE(saw_multi_record_peek);
    REQUIRE(saw_multi_record_extract);
    release_queue();
    return true;
}

static bool test_unsupported_capacity_and_error_precedence(void)
{
    AlertRecord storage[12];
    AlertPriorityQueue invalid = {
        storage, 1U, 12U, 1U, 4U
    };
    AlertRecord output = {55, 66U, 77U};
    AlertRecord before = output;

    REQUIRE(
        alert_priority_queue_validate(&invalid) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(
        alert_priority_queue_peek_min(&invalid, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_extract_min(&invalid, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_peek_min(&invalid, &output) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(records_equal(&output, &before));
    REQUIRE(
        alert_priority_queue_extract_min(&invalid, &output) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(records_equal(&output, &before));
    return true;
}

int main(void)
{
    run_test(
        "exact growth steps and full precedence",
        test_exact_growth_steps_and_full_precedence
    );
    run_test(
        "sequence exhaustion preserves every slot",
        test_sequence_exhaustion_preserves_every_slot
    );
    run_test(
        "equal-priority stability after swaps",
        test_equal_priority_stability_after_swaps
    );
    run_test(
        "deterministic differential sequence",
        test_deterministic_differential_sequence
    );
    run_test(
        "unsupported capacity and error precedence",
        test_unsupported_capacity_and_error_precedence
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
