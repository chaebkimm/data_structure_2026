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

AlertPriorityQueueStatus alert_priority_queue_is_min_heap(
    AlertPriorityQueue *queue,
    bool *out_is_min_heap
)
{
    AlertPriorityQueueStatus status;

    if (out_is_min_heap == NULL) {
        return ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT;
    }

    status = alert_priority_queue_validate(queue);
    if (status != ALERT_PRIORITY_QUEUE_OK) {
        return status;
    }

    /*
     * TODO 1: Check every child index 1 through size - 1 against parent
     * (child - 1) / 2. Continue after a violation. Count each stable record
     * comparison, saturate at SIZE_MAX, and commit the bool output last.
     */
    (void)alert_record_precedes;
    (void)count_record_comparison;
    return ALERT_PRIORITY_QUEUE_INVALID_STATE;
}

AlertPriorityQueueStatus alert_priority_queue_insert(
    AlertPriorityQueue *queue,
    int alert_id,
    size_t priority
)
{
    /*
     * TODO 2: Validate; reject full before sequence exhaustion; grow safely
     * when needed; append a record with next_sequence; and sift it upward.
     * Count one comparison per parent test. Commit size and sequence only
     * after the upward repair has completed.
     */
    (void)queue;
    (void)alert_id;
    (void)priority;
    (void)alert_priority_queue_reallocate;
    return ALERT_PRIORITY_QUEUE_INVALID_STATE;
}

AlertPriorityQueueStatus alert_priority_queue_peek_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
)
{
    AlertPriorityQueueStatus status;
    AlertRecord result;

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

    result = queue->data[0];
    *out_record = result;
    return ALERT_PRIORITY_QUEUE_OK;
}

AlertPriorityQueueStatus alert_priority_queue_extract_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
)
{
    /*
     * TODO 3: Reject a null output first, then validate and reject empty.
     * Save the root and final record. Sift the final candidate downward,
     * choosing the better existing child before comparing it with the
     * candidate. Handle a lone left child. Reset sequence only after a drain
     * and commit output last.
     */
    (void)queue;
    (void)out_record;
    return ALERT_PRIORITY_QUEUE_INVALID_STATE;
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
