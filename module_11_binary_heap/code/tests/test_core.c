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

static bool require_ids(
    const AlertPriorityQueue *queue,
    const int *expected,
    size_t count
)
{
    size_t index;

    REQUIRE(queue->size == count);
    for (index = 0U; index < count; ++index) {
        REQUIRE(queue->data[index].alert_id == expected[index]);
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

static bool test_init_shape_checker_and_destroy(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord storage[65];
    AlertPriorityQueue invalid_cases[] = {
        {storage, 0U, 0U, 0U, 0U},
        {NULL, 0U, 4U, 0U, 0U},
        {storage, 0U, 1U, 0U, 0U},
        {storage, 0U, 2U, 0U, 0U},
        {storage, 0U, 3U, 0U, 0U},
        {storage, 0U, 12U, 0U, 0U},
        {storage, 0U, 63U, 0U, 0U},
        {storage, 0U, 65U, 0U, 0U},
        {storage, 5U, 4U, 5U, 0U},
        {storage, 0U, 4U, 1U, 0U},
        {storage, 1U, 4U, 0U, 0U},
        {storage, 3U, 4U, 2U, 0U}
    };
    bool is_heap = false;
    size_t index;

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
    REQUIRE(
        alert_priority_queue_is_min_heap(&queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(is_heap);
    REQUIRE(queue.comparison_count == 0U);

    for (index = 0U;
         index < sizeof invalid_cases / sizeof invalid_cases[0];
         ++index) {
        bool output = true;
        QueueSnapshot before = snapshot_queue(&invalid_cases[index]);

        REQUIRE(
            alert_priority_queue_validate(&invalid_cases[index]) ==
            ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(
            alert_priority_queue_is_min_heap(
                &invalid_cases[index],
                NULL
            ) == ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
        );
        REQUIRE(
            alert_priority_queue_is_min_heap(
                &invalid_cases[index],
                &output
            ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
        );
        REQUIRE(output);
        REQUIRE(queue_matches_snapshot(&invalid_cases[index], &before));
    }

    REQUIRE(
        alert_priority_queue_insert(&queue, 8, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
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

static bool test_empty_singleton_and_output_preservation(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {-9, 77U, 88U};
    AlertRecord before = output;
    AlertRecord *allocation;
    bool is_heap = false;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&output, &before));
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_EMPTY
    );
    REQUIRE(records_equal(&output, &before));
    REQUIRE(
        alert_priority_queue_peek_min(&queue, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_extract_min(&queue, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );

    REQUIRE(
        alert_priority_queue_insert(&queue, 44, 5U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(queue.data[0].arrival_sequence == 0U);
    allocation = queue.data;
    REQUIRE(
        alert_priority_queue_is_min_heap(&queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(is_heap);
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 44);
    REQUIRE(queue.comparison_count == 0U);
    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 44);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.capacity == 4U);
    REQUIRE(queue.data == allocation);
    REQUIRE(queue.next_sequence == 0U);
    REQUIRE(queue.comparison_count == 0U);
    release_queue();
    return true;
}

static bool test_preserved_receiver_and_output_precedence(void)
{
    AlertRecord full_storage[64];
    AlertRecord full_before[64];
    AlertRecord empty_storage[4];
    AlertRecord empty_before[4];
    AlertPriorityQueue invalid_full = {
        full_storage, 64U, 63U, SIZE_MAX, 31U
    };
    AlertPriorityQueue invalid_empty = {
        empty_storage, 0U, 4U, 1U, 32U
    };
    QueueSnapshot full_snapshot;
    QueueSnapshot empty_snapshot;
    AlertRecord output = {-90, 901U, 902U};
    AlertRecord output_before = output;
    size_t index;

    for (index = 0U; index < 64U; ++index) {
        full_storage[index].alert_id = 700 + (int)index;
        full_storage[index].priority = 800U + index;
        full_storage[index].arrival_sequence = 900U + index;
    }
    for (index = 0U; index < 4U; ++index) {
        empty_storage[index].alert_id = 100 + (int)index;
        empty_storage[index].priority = 200U + index;
        empty_storage[index].arrival_sequence = 300U + index;
    }
    full_snapshot = snapshot_queue(&invalid_full);
    empty_snapshot = snapshot_queue(&invalid_empty);
    copy_records(full_storage, 64U, full_before);
    copy_records(empty_storage, 4U, empty_before);

    REQUIRE(
        alert_priority_queue_insert(NULL, 1, 1U) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        alert_priority_queue_insert(&invalid_full, 2, 2U) ==
        ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(queue_matches_snapshot(&invalid_full, &full_snapshot));
    REQUIRE(record_arrays_equal(full_storage, full_before, 64U));

    REQUIRE(
        alert_priority_queue_extract_min(NULL, &output) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(records_equal(&output, &output_before));
    REQUIRE(
        alert_priority_queue_extract_min(&invalid_empty, NULL) ==
        ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(queue_matches_snapshot(&invalid_empty, &empty_snapshot));
    REQUIRE(record_arrays_equal(empty_storage, empty_before, 4U));
    REQUIRE(
        alert_priority_queue_extract_min(
            &invalid_empty,
            &output
        ) == ALERT_PRIORITY_QUEUE_INVALID_STATE
    );
    REQUIRE(records_equal(&output, &output_before));
    REQUIRE(queue_matches_snapshot(&invalid_empty, &empty_snapshot));
    REQUIRE(record_arrays_equal(empty_storage, empty_before, 4U));
    return true;
}

static bool test_canonical_heap_traces_and_separate_metrics(void)
{
    static const int ids[] = {71, 88, 42, 17, 26, 9, 63};
    static const size_t priorities[] = {3U, 1U, 2U, 1U, 4U, 2U, 1U};
    static const size_t insert_comparisons[] = {
        0U, 1U, 1U, 2U, 1U, 1U, 2U
    };
    static const int insert_1[] = {71};
    static const int insert_2[] = {88, 71};
    static const int insert_3[] = {88, 71, 42};
    static const int insert_4[] = {88, 17, 42, 71};
    static const int insert_5[] = {88, 17, 42, 71, 26};
    static const int insert_6[] = {88, 17, 42, 71, 26, 9};
    static const int insert_7[] = {88, 17, 63, 71, 26, 9, 42};
    static const int *insert_states[] = {
        insert_1, insert_2, insert_3, insert_4,
        insert_5, insert_6, insert_7
    };
    static const size_t extract_comparisons[] = {
        4U, 2U, 3U, 2U, 1U, 0U, 0U
    };
    static const int extraction_ids[] = {88, 17, 63, 42, 9, 71, 26};
    static const int extract_1[] = {17, 42, 63, 71, 26, 9};
    static const int extract_2[] = {63, 42, 9, 71, 26};
    static const int extract_3[] = {42, 71, 9, 26};
    static const int extract_4[] = {9, 71, 26};
    static const int extract_5[] = {71, 26};
    static const int extract_6[] = {26};
    static const int *extract_states[] = {
        extract_1, extract_2, extract_3,
        extract_4, extract_5, extract_6
    };
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    size_t normal_insert_total = 0U;
    size_t normal_extract_total = 0U;
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    for (index = 0U; index < 7U; ++index) {
        bool is_heap = false;
        size_t before_check;

        REQUIRE(queue.comparison_count == 0U);
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                ids[index],
                priorities[index]
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(
            queue.comparison_count == insert_comparisons[index]
        );
        normal_insert_total += queue.comparison_count;
        REQUIRE(require_ids(
            &queue,
            insert_states[index],
            index + 1U
        ));

        before_check = queue.comparison_count;
        REQUIRE(
            alert_priority_queue_is_min_heap(
                &queue,
                &is_heap
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(is_heap);
        REQUIRE(
            queue.comparison_count - before_check == queue.size - 1U
        );
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(normal_insert_total == 8U);

    REQUIRE(
        alert_priority_queue_peek_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(output.alert_id == 88);
    REQUIRE(output.arrival_sequence == 1U);
    REQUIRE(queue.comparison_count == 0U);

    for (index = 0U; index < 7U; ++index) {
        bool is_heap = false;
        size_t before_check;

        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.alert_id == extraction_ids[index]);
        REQUIRE(
            queue.comparison_count == extract_comparisons[index]
        );
        normal_extract_total += queue.comparison_count;
        if (index < 6U) {
            REQUIRE(require_ids(
                &queue,
                extract_states[index],
                6U - index
            ));
        } else {
            REQUIRE(queue.size == 0U);
        }

        before_check = queue.comparison_count;
        REQUIRE(
            alert_priority_queue_is_min_heap(
                &queue,
                &is_heap
            ) == ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(is_heap);
        REQUIRE(
            queue.comparison_count - before_check ==
            (queue.size == 0U ? 0U : queue.size - 1U)
        );
        REQUIRE(
            alert_priority_queue_reset_comparisons(&queue) ==
            ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(normal_extract_total == 12U);
    REQUIRE(queue.capacity == 8U);
    REQUIRE(queue.next_sequence == 0U);
    release_queue();
    return true;
}

static bool test_missing_right_child_and_stable_ties(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord output = {0, 0U, 0U};
    static const int missing_right_state[] = {1, 3, 2, 4};
    static const int tied_ids[] = {90, 10, 70, 20};
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U; index < 5U; ++index) {
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
    REQUIRE(output.alert_id == 0);
    REQUIRE(queue.comparison_count == 3U);
    REQUIRE(require_ids(&queue, missing_right_state, 4U));
    release_queue();

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                tied_ids[index],
                7U
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_extract_min(&queue, &output) ==
            ALERT_PRIORITY_QUEUE_OK
        );
        REQUIRE(output.alert_id == tied_ids[index]);
        REQUIRE(output.arrival_sequence == index);
    }
    release_queue();
    return true;
}

static bool test_growth_and_allocation_failure_preservation(void)
{
    AlertPriorityQueue queue = {0};
    QueueSnapshot before;
    AlertRecord records_before[8];
    size_t index;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);

    before = snapshot_queue(&queue);
    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 1, 1U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));

    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                10 + (int)index,
                10U - index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.capacity == 4U);
    before = snapshot_queue(&queue);
    copy_records(queue.data, 4U, records_before);
    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 99, 0U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 4U));

    REQUIRE(
        alert_priority_queue_insert(&queue, 20, 20U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.capacity == 8U);

    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 21, 21U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 22, 22U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(
        alert_priority_queue_insert(&queue, 23, 23U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.size == 8U);
    before = snapshot_queue(&queue);
    copy_records(queue.data, 8U, records_before);
    REQUIRE(
        alert_priority_queue_insert(&queue, 24, 24U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 8U));
    release_queue();
    return true;
}

static bool test_full_sequence_and_failure_precedence(void)
{
    AlertPriorityQueue queue = {0};
    AlertRecord records_before[ALERT_PRIORITY_QUEUE_MAX_CAPACITY];
    AlertRecord output = {0, 0U, 0U};
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
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                (int)index,
                index % 9U
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.capacity == 64U);
    queue.next_sequence = SIZE_MAX;
    before = snapshot_queue(&queue);
    copy_records(queue.data, 64U, records_before);
    REQUIRE(
        alert_priority_queue_insert(&queue, 900, 0U) ==
        ALERT_PRIORITY_QUEUE_FULL
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 64U));

    REQUIRE(
        alert_priority_queue_extract_min(&queue, &output) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    before = snapshot_queue(&queue);
    copy_records(queue.data, 64U, records_before);
    REQUIRE(
        alert_priority_queue_insert(&queue, 901, 0U) ==
        ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 64U));
    release_queue();
    return true;
}

static bool test_checker_corruption_saturation_and_statuses(void)
{
    AlertPriorityQueue queue = {0};
    bool is_heap = true;
    size_t index;
    AlertPriorityQueueStatus status;

    REQUIRE(
        alert_priority_queue_init(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    track_queue(&queue);
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                50 + (int)index,
                10U + index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }

    queue.data[3].priority = 0U;
    queue.comparison_count = 10U;
    REQUIRE(
        alert_priority_queue_is_min_heap(&queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(!is_heap);
    REQUIRE(queue.comparison_count == 13U);

    queue.data[3].priority = 13U;
    queue.comparison_count = SIZE_MAX - 1U;
    REQUIRE(
        alert_priority_queue_is_min_heap(&queue, &is_heap) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(is_heap);
    REQUIRE(queue.comparison_count == SIZE_MAX);
    REQUIRE(
        alert_priority_queue_reset_comparisons(&queue) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.comparison_count == 0U);

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
    release_queue();
    return true;
}

static bool test_sequence_exhaustion_before_growth(void)
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
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            alert_priority_queue_insert(
                &queue,
                300 + (int)index,
                10U + index
            ) == ALERT_PRIORITY_QUEUE_OK
        );
    }
    REQUIRE(queue.size == 4U);
    REQUIRE(queue.capacity == 4U);

    queue.next_sequence = SIZE_MAX;
    before = snapshot_queue(&queue);
    copy_records(queue.data, 4U, records_before);
    alert_priority_queue_test_fail_next_growth();
    REQUIRE(
        alert_priority_queue_insert(&queue, 400, 1U) ==
        ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 4U));

    /*
     * Restoring the valid next sequence makes growth necessary. The pending
     * one-shot failure proves that the exhaustion path did not allocate.
     */
    queue.next_sequence = 4U;
    before = snapshot_queue(&queue);
    REQUIRE(
        alert_priority_queue_insert(&queue, 400, 1U) ==
        ALERT_PRIORITY_QUEUE_ALLOCATION
    );
    REQUIRE(queue_matches_snapshot(&queue, &before));
    REQUIRE(record_arrays_equal(queue.data, records_before, 4U));

    REQUIRE(
        alert_priority_queue_insert(&queue, 400, 1U) ==
        ALERT_PRIORITY_QUEUE_OK
    );
    REQUIRE(queue.size == 5U);
    REQUIRE(queue.capacity == 8U);
    REQUIRE(queue.next_sequence == 5U);
    release_queue();
    return true;
}

int main(void)
{
    run_test(
        "init, shape checker, and destroy",
        test_init_shape_checker_and_destroy
    );
    run_test(
        "empty, singleton, and output preservation",
        test_empty_singleton_and_output_preservation
    );
    run_test(
        "preserved receiver and output precedence",
        test_preserved_receiver_and_output_precedence
    );
    run_test(
        "canonical Heap traces and separate metrics",
        test_canonical_heap_traces_and_separate_metrics
    );
    run_test(
        "missing right child and stable ties",
        test_missing_right_child_and_stable_ties
    );
    run_test(
        "growth and allocation-failure preservation",
        test_growth_and_allocation_failure_preservation
    );
    run_test(
        "full, sequence, and failure precedence",
        test_full_sequence_and_failure_precedence
    );
    run_test(
        "checker corruption, saturation, and statuses",
        test_checker_corruption_saturation_and_statuses
    );
    run_test(
        "sequence exhaustion before growth",
        test_sequence_exhaustion_before_growth
    );

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
