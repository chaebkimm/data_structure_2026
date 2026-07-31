#include "event_queue.h"

#include <stdbool.h>
#include <stdlib.h>

#ifdef EVENT_QUEUE_TESTING
static bool event_queue_fail_next_allocation = false;

void event_queue_test_fail_next_allocation(void)
{
    event_queue_fail_next_allocation = true;
}
#endif

static void *event_queue_allocate(size_t byte_count)
{
#ifdef EVENT_QUEUE_TESTING
    if (event_queue_fail_next_allocation) {
        event_queue_fail_next_allocation = false;
        return NULL;
    }
#endif

    return malloc(byte_count);
}

static bool event_queue_is_zero(const EventQueue *queue)
{
    return queue->data == NULL &&
        queue->capacity == 0U &&
        queue->head == 0U &&
        queue->size == 0U;
}

EventQueueStatus event_queue_init(
    EventQueue *queue,
    size_t capacity
)
{
    int *candidate;

    if (queue == NULL) {
        return EVENT_QUEUE_INVALID_ARGUMENT;
    }

    if (!event_queue_is_zero(queue)) {
        return EVENT_QUEUE_INVALID_STATE;
    }

    if (capacity > (size_t)EVENT_QUEUE_MAX_CAPACITY) {
        return EVENT_QUEUE_LIMIT;
    }

    if (capacity == 0U) {
        return EVENT_QUEUE_OK;
    }

    candidate = event_queue_allocate(capacity * sizeof *candidate);
    if (candidate == NULL) {
        return EVENT_QUEUE_ALLOCATION;
    }

    queue->data = candidate;
    queue->capacity = capacity;
    return EVENT_QUEUE_OK;
}

EventQueueStatus event_queue_validate(const EventQueue *queue)
{
    /*
     * TODO 1: Check the exact public representation rules. Capacity zero
     * requires the all-zero state. Positive capacity requires live-looking
     * storage, size no greater than capacity, and a valid head. An empty
     * positive-capacity Queue must have head zero.
     */
    (void)queue;
    return EVENT_QUEUE_INVALID_STATE;
}

EventQueueStatus event_queue_enqueue(
    EventQueue *queue,
    int event_code
)
{
    /*
     * TODO 2: Validate, reject a full Queue without changing it, derive the
     * circular tail, write event_code there, and increase size last. Never
     * evaluate modulo when capacity is zero.
     */
    (void)queue;
    (void)event_code;
    return EVENT_QUEUE_INVALID_STATE;
}

EventQueueStatus event_queue_dequeue(
    EventQueue *queue,
    int *out_event_code
)
{
    /*
     * TODO 3: Reject a null output, validate, and report an empty Queue
     * before reading. Remove the head event, advance circularly, reset head
     * to zero for the required empty form after removing the last item, and
     * change the output only on success.
     */
    (void)queue;
    (void)out_event_code;
    return EVENT_QUEUE_INVALID_STATE;
}

EventQueueStatus event_queue_peek(
    const EventQueue *queue,
    int *out_event_code
)
{
    EventQueueStatus status;
    int result;

    if (out_event_code == NULL) {
        return EVENT_QUEUE_INVALID_ARGUMENT;
    }

    status = event_queue_validate(queue);
    if (status != EVENT_QUEUE_OK) {
        return status;
    }

    if (queue->size == 0U) {
        return EVENT_QUEUE_EMPTY;
    }

    result = queue->data[queue->head];
    *out_event_code = result;
    return EVENT_QUEUE_OK;
}

void event_queue_destroy(EventQueue *queue)
{
    if (queue == NULL) {
        return;
    }

    free(queue->data);
    queue->data = NULL;
    queue->capacity = 0U;
    queue->head = 0U;
    queue->size = 0U;
}

const char *event_queue_status_name(EventQueueStatus status)
{
    switch (status) {
        case EVENT_QUEUE_OK:
            return "ok";
        case EVENT_QUEUE_INVALID_ARGUMENT:
            return "invalid argument";
        case EVENT_QUEUE_LIMIT:
            return "requested Queue capacity exceeds maximum";
        case EVENT_QUEUE_FULL:
            return "Queue is full";
        case EVENT_QUEUE_EMPTY:
            return "Queue is empty";
        case EVENT_QUEUE_ALLOCATION:
            return "allocation failed";
        case EVENT_QUEUE_INVALID_STATE:
            return "Queue representation is invalid";
        default:
            return "unknown EventQueueStatus";
    }
}
