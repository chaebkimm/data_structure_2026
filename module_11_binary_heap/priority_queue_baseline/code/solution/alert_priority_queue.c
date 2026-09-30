#include "alert_priority_queue.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum {
    ALERT_PRIORITY_QUEUE_INITIAL_CAPACITY = 4
};

#ifdef ALERT_PRIORITY_QUEUE_TESTING
static bool alert_priority_queue_fail_next_growth = false;

void alert_priority_queue_test_fail_next_growth(void)
{
    alert_priority_queue_fail_next_growth = true;
}
#endif

static void *alert_priority_queue_reallocate(
    void *old_pointer,
    size_t new_bytes
)
{
#ifdef ALERT_PRIORITY_QUEUE_TESTING
    if (alert_priority_queue_fail_next_growth) {
        alert_priority_queue_fail_next_growth = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

static bool alert_priority_queue_is_zero(
    const AlertPriorityQueue *queue
)
{
    return queue->data == NULL &&
        queue->size == 0U &&
        queue->capacity == 0U &&
        queue->next_sequence == 0U &&
        queue->comparison_count == 0U;
}

static bool is_supported_capacity(size_t capacity)
{
    return capacity == 0U ||
        capacity == 4U ||
        capacity == 8U ||
        capacity == 16U ||
        capacity == 32U ||
        capacity == 64U;
}

static bool alert_record_precedes(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    if (left->priority != right->priority) {
        return left->priority < right->priority;
    }
    return left->arrival_sequence < right->arrival_sequence;
}

static void count_record_comparison(AlertPriorityQueue *queue)
{
    if (queue->comparison_count < SIZE_MAX) {
        queue->comparison_count += 1U;
    }
}

static size_t find_minimum_index(AlertPriorityQueue *queue)
{
    size_t minimum_index = 0U;
    size_t index;

    for (index = 1U; index < queue->size; ++index) {
        count_record_comparison(queue);
        if (alert_record_precedes(
                &queue->data[index],
                &queue->data[minimum_index]
            )) {
            minimum_index = index;
        }
    }
    return minimum_index;
}

AlertPriorityQueueStatus alert_priority_queue_init(
    AlertPriorityQueue *queue
)
{
    if (queue == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT;
    }
    if (!alert_priority_queue_is_zero(queue)) {
        return ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }
    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_validate(
    const AlertPriorityQueue *queue
)
{
    if (queue == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT;
    }

    if (!is_supported_capacity(queue->capacity) ||
        queue->size > queue->capacity) {
        return ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }

    if (queue->capacity == 0U) {
        return alert_priority_queue_is_zero(queue)
            ? ALERT_PRIORITY_QUEUE_OK
            : ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }

    if (queue->data == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }

    if (queue->size == 0U) {
        return queue->next_sequence == 0U
            ? ALERT_PRIORITY_QUEUE_OK
            : ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }

    if (queue->next_sequence == 0U ||
        queue->next_sequence < queue->size) {
        return ALERT_PRIORITY_QUEUE_INVALID_STATE;
    }

    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_insert(
    AlertPriorityQueue *queue,
    int alert_id,
    size_t priority
)
{
    AlertPriorityQueueStatus status =
        alert_priority_queue_validate(queue);

    if (status != ALERT_PRIORITY_QUEUE_OK) {
        return status;
    }

    if (queue->size ==
        (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY) {
        return ALERT_PRIORITY_QUEUE_FULL;
    }

    if (queue->next_sequence == SIZE_MAX) {
        return ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED;
    }

    if (queue->size == queue->capacity) {
        size_t new_capacity = queue->capacity == 0U
            ? (size_t)ALERT_PRIORITY_QUEUE_INITIAL_CAPACITY
            : queue->capacity * 2U;
        AlertRecord *candidate;

        if (new_capacity >
            (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY) {
            new_capacity =
                (size_t)ALERT_PRIORITY_QUEUE_MAX_CAPACITY;
        }

        candidate = alert_priority_queue_reallocate(
            queue->data,
            new_capacity * sizeof *queue->data
        );
        if (candidate == NULL) {
            return ALERT_PRIORITY_QUEUE_ALLOCATION;
        }

        queue->data = candidate;
        queue->capacity = new_capacity;
    }

    queue->data[queue->size].alert_id = alert_id;
    queue->data[queue->size].priority = priority;
    queue->data[queue->size].arrival_sequence =
        queue->next_sequence;
    queue->size += 1U;
    queue->next_sequence += 1U;
    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_peek_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
)
{
    AlertPriorityQueueStatus status;
    AlertRecord result;
    size_t minimum_index;

    if (out_record == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT;
    }

    status = alert_priority_queue_validate(queue);
    if (status != ALERT_PRIORITY_QUEUE_OK) {
        return status;
    }

    if (queue->size == 0U) {
        return ALERT_PRIORITY_QUEUE_EMPTY;
    }

    minimum_index = find_minimum_index(queue);
    result = queue->data[minimum_index];
    *out_record = result;
    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_extract_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
)
{
    AlertPriorityQueueStatus status;
    AlertRecord result;
    size_t minimum_index;
    size_t final_index;

    if (out_record == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT;
    }

    status = alert_priority_queue_validate(queue);
    if (status != ALERT_PRIORITY_QUEUE_OK) {
        return status;
    }

    if (queue->size == 0U) {
        return ALERT_PRIORITY_QUEUE_EMPTY;
    }

    minimum_index = find_minimum_index(queue);
    final_index = queue->size - 1U;
    result = queue->data[minimum_index];

    if (minimum_index != final_index) {
        queue->data[minimum_index] = queue->data[final_index];
    }
    queue->size = final_index;
    if (queue->size == 0U) {
        queue->next_sequence = 0U;
    }

    *out_record = result;
    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_reset_comparisons(
    AlertPriorityQueue *queue
)
{
    AlertPriorityQueueStatus status =
        alert_priority_queue_validate(queue);

    if (status != ALERT_PRIORITY_QUEUE_OK) {
        return status;
    }

    queue->comparison_count = 0U;
    return ALERT_PRIORITY_QUEUE_OK;
}

void alert_priority_queue_destroy(AlertPriorityQueue *queue)
{
    if (queue == NULL) {
        return;
    }

    free(queue->data);
    queue->data = NULL;
    queue->size = 0U;
    queue->capacity = 0U;
    queue->next_sequence = 0U;
    queue->comparison_count = 0U;
}

const char *alert_priority_queue_status_name(
    AlertPriorityQueueStatus status
)
{
    switch (status) {
        case ALERT_PRIORITY_QUEUE_OK:
            return "ok";
        case ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT:
            return "invalid argument";
        case ALERT_PRIORITY_QUEUE_FULL:
            return "Priority Queue is full";
        case ALERT_PRIORITY_QUEUE_EMPTY:
            return "Priority Queue is empty";
        case ALERT_PRIORITY_QUEUE_ALLOCATION:
            return "allocation failed";
        case ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED:
            return "arrival sequence exhausted";
        case ALERT_PRIORITY_QUEUE_INVALID_STATE:
            return "Priority Queue representation is invalid";
        default:
            return "unknown AlertPriorityQueueStatus";
    }
}
