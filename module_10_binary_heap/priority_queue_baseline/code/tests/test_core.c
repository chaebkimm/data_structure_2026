#include "alert_priority_queue.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef ALERT_PRIORITY_QUEUE_TESTING
#error "Core tests require -DALERT_PRIORITY_QUEUE_TESTING."
#endif

typedef bool (*TestFunction)(void);

typedef struct {
    AlertRecord *data_identity;
    size_t size;
    size_t capacity;
    size_t next_sequence;
    size_t comparison_count;
} QueueSnapshot;

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

static QueueSnapshot snapshot_queue(const AlertPriorityQueue *queue)
{
    QueueSnapshot snapshot;

    snapshot.data_identity = queue->data;
    snapshot.size = queue->size;
    snapshot.capacity = queue->capacity;
    snapshot.next_sequence = queue->next_sequence;
    snapshot.comparison_count = queue->comparison_count;
    return snapshot;
}

static bool queue_matches_snapshot(
    const AlertPriorityQueue *queue,
    const QueueSnapshot *snapshot
)
{
    return queue->data == snapshot->data_identity &&
        queue->size == snapshot->size &&
        queue->capacity == snapshot->capacity &&
        queue->next_sequence == snapshot->next_sequence &&
        queue->comparison_count == snapshot->comparison_count;
}

static bool records_equal(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    return left->alert_id == right->alert_id &&
        left->priority == right->priority &&
        left->arrival_sequence == right->arrival_sequence;
}

static void snapshot_records(
    const AlertRecord *records,
    size_t count,
    AlertRecord *out_snapshot
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        out_snapshot[index] = records[index];
    }
}

static bool records_match(
    const AlertRecord *records,
    const AlertRecord *snapshot,
    size_t count
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        if (!records_equal(&records[index], &snapshot[index])) {
            return false;
        }
    }
    return true;
}

static bool require_live_ids(
    const AlertPriorityQueue *queue,
    const int *ids,
    size_t count
)
{
    size_t index;

    REQUIRE(queue->size == count);
    for (index = 0U; index < count; ++index) {
        REQUIRE(queue->data[index].alert_id == ids[index]);
    }
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

static bool test_all_zero_init_validate_and_destroy(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord marker = {19, 7U, 3U};
    AlertPriorityQueue live_looking = {
        &marker, 1U, 4U, 1U, 0U
    };
    QueueSnapshot before = snapshot_queue(&live_looking);

    REQUIRE(
        alert_priority_queue_init(NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_validate(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.data == NULL);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.capacity == 0U);
    REQUIRE(queue.next_sequence == 0U);
    REQUIRE(queue.comparison_count == 0U);

    /* The canonical all-zero state may be initialized again. */
    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );

    REQUIRE(
        alert_priority_queue_init(&live_looking) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(queue_matches_snapshot(&live_looking, &before));

    REQUIRE(
        alert_priority_queue_insert(&queue, 1, 4U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    release_queue();
    REQUIRE(
        alert_priority_queue_validate(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.data == NULL);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.capacity == 0U);
    REQUIRE(queue.next_sequence == 0U);
    REQUIRE(queue.comparison_count == 0U);

    alert_priority_queue_destroy(&queue);
    alert_priority_queue_destroy(NULL);
    return true;
}

static bool test_constant_time_representation_rules(void)
{
    AlertRecord storage[65];
    AlertPriorityQueue valid_empty = {
        storage, 0U, 4U, 0U, SIZE_MAX
    };
    AlertPriorityQueue valid_live = {
        storage, 2U, 4U, 9U, 7U
    };
    AlertPriorityQueue invalid_cases[] = {
        {storage, 0U, 0U, 0U, 0U},
        {NULL, 0U, 4U, 0U, 0U},
        {storage, 2U, 1U, 2U, 0U},
        {storage, 0U, 2U, 0U, 0U},
        {storage, 0U, 3U, 0U, 0U},
        {storage, 0U, 5U, 0U, 0U},
        {storage, 0U, 63U, 0U, 0U},
        {storage, 0U, 65U, 0U, 0U},
        {storage, 5U, 4U, 5U, 0U},
        {storage, 0U, 4U, 1U, 0U},
        {storage, 1U, 4U, 0U, 0U},
        {storage, 3U, 4U, 2U, 0U}
    };
    size_t capacity;
    size_t index;

    REQUIRE(
        alert_priority_queue_validate(NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_validate(&valid_empty) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_validate(&valid_live) ==
        ALERT_PRIORITY_QUEUE_OK
    );

    for (capacity = 1U; capacity <= 64U; ++capacity) {
        AlertPriorityQueue candidate = {
            storage, 0U, capacity, 0U, 0U
        };

        if (capacity == 4U ||
            capacity == 8U ||
            capacity == 16U ||
            capacity == 32U ||
            capacity == 64U) {
            REQUIRE(
                alert_priority_queue_validate(&candidate) ==
                ALERT_PRIORITY_QUEUE_OK
            );
        } else {
            REQUIRE(
                alert_priority_queue_validate(&candidate) ==
                ALERT_PRIORITY_QUEUE_INVALID_STATE
            );
        }
    }

    for (index = 0U;
         index < sizeof invalid_cases / sizeof invalid_cases[0];
         ++index) {
        AlertRecord output = {-71, 91U, 81U};
        AlertRecord output_before = output;
        QueueSnapshot before = snapshot_queue(&invalid_cases[index]);

        REQUIRE(
            alert_priority_queue_validate(&invalid_cases[index]) ==
            ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(
            alert_priority_queue_insert(
                &invalid_cases[index],
                8,
                1U
            ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(queue_matches_snapshot(&invalid_cases[index], &before));
        REQUIRE(
            alert_priority_queue_peek_min(
                &invalid_cases[index],
                &output
            ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(records_equal(&output, &output_before));
        REQUIRE(queue_matches_snapshot(&invalid_cases[index], &before));
        REQUIRE(
            alert_priority_queue_extract_min(
                &invalid_cases[index],
                &output
            ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(records_equal(&output, &output_before));
        REQUIRE(queue_matches_snapshot(&invalid_cases[index], &before));
        REQUIRE(
            alert_priority_queue_reset_comparisons(
                &invalid_cases[index]
            ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(queue_matches_snapshot(&invalid_cases[index], &before));
    }
    return true;
}

static bool test_empty_and_null_output_preservation(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {-4, 77U, 88U};
    AlertRecord output_before = output;
    QueueSnapshot before;
    AlertRecord storage[4];
    AlertPriorityQueue invalid = {
        storage, 5U, 4U, 5U, 12U
    };

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    before = snapshot_queue(&queue);
    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&output, &output_before));
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&output, &output_before));
    REQUIRE(queue_matches_snapshot(&queue, &before));

    REQUIRE(
        alert_priority_queue_peek_min(NULL, &output) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_extract_min(NULL, &output) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_peek_min(&invalid, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_extract_min(&invalid, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(records_equal(&output, &output_before));
    return true;
}

static bool test_canonical_stability_swaps_and_metrics(void)
{
    static const int ids[] = {71, 88, 42, 17, 26, 9, 63};
    static const size_t priorities[] = {3U, 1U, 2U, 1U, 4U, 2U, 1U};
    static const int extraction_ids[] = {88, 17, 63, 42, 9, 71, 26};
    static const size_t extraction_sequences[] = {
        1U, 3U, 6U, 2U, 5U, 0U, 4U
    };
    static const int live_after_1[] = {71, 63, 42, 17, 26, 9};
    static const int live_after_2[] = {71, 63, 42, 9, 26};
    static const int live_after_3[] = {71, 26, 42, 9};
    static const int live_after_4[] = {71, 26, 9};
    static const int live_after_5[] = {71, 26};
    static const int live_after_6[] = {26};
    const int *states[] = {
        live_after_1,
        live_after_2,
        live_after_3,
        live_after_4,
        live_after_5,
        live_after_6
    };
    const size_t state_sizes[] = {6U, 5U, 4U, 3U, 2U, 1U};
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    AlertRecord empty_output = {-303, 404U, 505U};
    AlertRecord empty_output_before = empty_output;
    AlertRecord drained_slots[8];
    AlertRecord *allocation;
    QueueSnapshot drained;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U; index < 7U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                ids[index],
                priorities[index]
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(queue.data[index].arrival_sequence == index);
        REQUIRE(queue.comparison_count == 0U);
    }
    REQUIRE(queue.capacity == 8U);
    REQUIRE(queue.next_sequence == 7U);
    allocation = queue.data;
    queue.data[7].alert_id = 707;
    queue.data[7].priority = 707U;
    queue.data[7].arrival_sequence = 707U;

    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 88);
    REQUIRE(output.priority == 1U);
    REQUIRE(output.arrival_sequence == 1U);
    REQUIRE(queue.size == 7U);
    REQUIRE(queue.comparison_count == 6U);

    REQUIRE(
        alert_priority_queue_reset_comparisons(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    for (index = 0U; index < 7U; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.alert_id == extraction_ids[index]);
        REQUIRE(
            output.arrival_sequence == extraction_sequences[index]
        );
        if (index < 6U) {
            REQUIRE(require_live_ids(
                &queue,
                states[index],
                state_sizes[index]
            ));
        }
    }

    REQUIRE(queue.comparison_count == 21U);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.capacity == 8U);
    REQUIRE(queue.data == allocation);
    REQUIRE(queue.next_sequence == 0U);

    drained = snapshot_queue(&queue);
    snapshot_records(queue.data, 8U, drained_slots);
    REQUIRE(
        alert_priority_queue_peek_min(&queue, &empty_output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&empty_output, &empty_output_before));
    REQUIRE(queue_matches_snapshot(&queue, &drained));
    REQUIRE(records_match(queue.data, drained_slots, 8U));
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &empty_output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&empty_output, &empty_output_before));
    REQUIRE(queue_matches_snapshot(&queue, &drained));
    REQUIRE(records_match(queue.data, drained_slots, 8U));

    REQUIRE(
        alert_priority_queue_insert(&queue, 501, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.data[0].arrival_sequence == 0U);
    REQUIRE(queue.comparison_count == 21U);
    release_queue();
    return true;
}

static bool test_growth_and_allocation_failure_preservation(void)
{
    AlertPriorityQueue queue = {0};
    QueueSnapshot before;
    AlertRecord slots_before[8];
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    alert_priority_queue_test_fail_next_growth();
    before = snapshot_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 1, 1U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));

    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                (int)(10U + index),
                20U - index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.capacity == 4U);
    before = snapshot_queue(&queue);
    snapshot_records(queue.data, 4U, slots_before);
    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 99, 0U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(records_match(queue.data, slots_before, 4U));

    REQUIRE(
        alert_priority_queue_insert(&queue, 14, 6U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.capacity == 8U);

    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 15, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 16, 4U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 17, 3U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.size == 8U);
    before = snapshot_queue(&queue);
    snapshot_records(queue.data, 8U, slots_before);
    REQUIRE(
        alert_priority_queue_insert(&queue, 18, 2U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(records_match(queue.data, slots_before, 8U));
    release_queue();
    return true;
}

static bool test_capacity_ladder_full_and_preservation(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord records_before[ALERT_PRIORITY_QUEUE_MAX_CAPACITY];
    QueueSnapshot before;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    for (index = 0U;
         index < (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY;
         ++index) {
        size_t expected_capacity;

        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                1000 + (int)index,
                index % 9U
            ) == ALERT_PRIORITY_QUEUE_OK
        );

        if (index < 4U) {
            expected_capacity = 4U;
        } else if (index < 8U) {
            expected_capacity = 8U;
        } else if (index < 16U) {
            expected_capacity = 16U;
        } else if (index < 32U) {
            expected_capacity = 32U;
        } else {
            expected_capacity = 64U;
        }
        REQUIRE(queue.capacity == expected_capacity);
        REQUIRE(queue.size == index + 1U);
        REQUIRE(queue.next_sequence == index + 1U);
        REQUIRE(queue.comparison_count == 0U);
    }

    snapshot_records(
        queue.data,
        (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY,
        records_before
    );
    queue.next_sequence = SIZE_MAX;
    before = snapshot_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 9999, 0U) ==
        ALERT_PRIORITY_QUEUE_FULL
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(records_match(
        queue.data,
        records_before,
        (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY
    ));

    release_queue();
    return true;
}

static bool test_sequence_exhaustion_preservation(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord records_before[4];
    QueueSnapshot before;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 41, 3U) ==
        ALERT_PRIORITY_QUEUE_OK
    );

    for (index = 1U; index < 4U; ++index) {
        queue.data[index].alert_id = 700 + (int)index;
        queue.data[index].priority = 800U + index;
        queue.data[index].arrival_sequence = 900U + index;
    }
    queue.next_sequence = SIZE_MAX;
    before = snapshot_queue(&queue);
    snapshot_records(queue.data, 4U, records_before);

    REQUIRE(
        alert_priority_queue_insert(&queue, 42, 1U) ==
        ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(records_match(queue.data, records_before, 4U));

    release_queue();
    return true;
}

static bool test_priority_extremes_and_stable_epoch(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};

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
    REQUIRE(output.arrival_sequence == 1U);
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == -1);
    REQUIRE(output.arrival_sequence == 2U);
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == INT_MAX);
    REQUIRE(output.priority == SIZE_MAX);
    REQUIRE(queue.next_sequence == 0U);

    REQUIRE(
        alert_priority_queue_insert(&queue, 7, 0U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.data[0].arrival_sequence == 0U);
    release_queue();
    return true;
}

static bool test_saturating_metric_and_reset(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    AlertRecord *pointer;
    size_t capacity;
    size_t next_sequence;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 10, 3U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 20, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 30, 2U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    queue.comparison_count = SIZE_MAX - 1U;

    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 20);
    REQUIRE(queue.comparison_count == SIZE_MAX);
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 20);
    REQUIRE(queue.comparison_count == SIZE_MAX);

    pointer = queue.data;
    capacity = queue.capacity;
    next_sequence = queue.next_sequence;
    REQUIRE(
        alert_priority_queue_reset_comparisons(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.capacity == capacity);
    REQUIRE(queue.next_sequence == next_sequence);
    REQUIRE(queue.size == 2U);
    release_queue();
    return true;
}

static bool test_status_names(void)
{
    AlertPriorityQueueStatus status;

    for (status = ALERT_PRIORITY_QUEUE_OK;
         status <= ALERT_PRIORITY_QUEUE_INVALID_STATE;
         status = (AlertPriorityQueueStatus)((int)status + 1)) {
        const char *name =
            alert_priority_queue_status_name(status);

        REQUIRE(name != NULL);
        REQUIRE(strlen(name) > 0U);
    }
    REQUIRE(
        strcmp(
            alert_priority_queue_status_name(
                (AlertPriorityQueueStatus)999
            ),
            "unknown AlertPriorityQueueStatus"
        ) == 0
    );
    return true;
}

int main(void)
{
    run_test(
        "all-zero init, validation, and destroy",
        test_all_zero_init_validate_and_destroy
    );
    run_test(
        "constant-time representation rules",
        test_constant_time_representation_rules
    );
    run_test(
        "empty and null-output preservation",
        test_empty_and_null_output_preservation
    );
    run_test(
        "canonical stability, swaps, and metrics",
        test_canonical_stability_swaps_and_metrics
    );
    run_test(
        "growth and allocation-failure preservation",
        test_growth_and_allocation_failure_preservation
    );
    run_test(
        "capacity ladder, full limit, and preservation",
        test_capacity_ladder_full_and_preservation
    );
    run_test(
        "sequence-exhaustion preservation",
        test_sequence_exhaustion_preservation
    );
    run_test(
        "priority extremes and stable epoch",
        test_priority_extremes_and_stable_epoch
    );
    run_test(
        "saturating metric and reset",
        test_saturating_metric_and_reset
    );
    run_test("status names", test_status_names);

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
