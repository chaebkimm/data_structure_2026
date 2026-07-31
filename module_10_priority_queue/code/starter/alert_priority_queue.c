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

/*
 * TODO 1: Complete the stable record comparator and minimum-index scan.
 * A smaller priority wins; equal priorities use the smaller arrival
 * sequence. Count exactly one record comparison for each candidate examined
 * after index zero, saturating comparison_count at SIZE_MAX.
 */
static bool alert_record_precedes(
    const AlertRecord *left,
    const AlertRecord *right
)
{
    (void)left;
    (void)right;
    return false;
}

static size_t find_minimum_index(AlertPriorityQueue *queue)
{
    (void)alert_record_precedes;
    (void)queue;
    return 0U;
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
    /*
     * TODO 2: Validate first; reject full before sequence exhaustion. Grow
     * geometrically with a temporary realloc result. Append the new record
     * with next_sequence, then advance size and sequence. Insert performs
     * zero record comparisons, and every failure preserves the whole Queue.
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
    /*
     * TODO 3: Reject a null output first, then validate and reject empty.
     * Find the stable minimum, save it locally, replace its slot with the
     * final live record when needed, and decrease size. Reset next_sequence
     * to zero only when the Queue becomes empty. Commit output last.
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
