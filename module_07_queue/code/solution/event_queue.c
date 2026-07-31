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
    if (queue == NULL) {
        return EVENT_QUEUE_INVALID_ARGUMENT;
    }

    if (queue->capacity > (size_t)EVENT_QUEUE_MAX_CAPACITY ||
        queue->size > queue->capacity) {
        return EVENT_QUEUE_INVALID_STATE;
    }

    if (queue->capacity == 0U) {
        return event_queue_is_zero(queue)
            ? EVENT_QUEUE_OK
            : EVENT_QUEUE_INVALID_STATE;
    }

    if (queue->data == NULL) {
        return EVENT_QUEUE_INVALID_STATE;
    }

    if (queue->size == 0U) {
        return queue->head == 0U
            ? EVENT_QUEUE_OK
            : EVENT_QUEUE_INVALID_STATE;
    }

    return queue->head < queue->capacity
        ? EVENT_QUEUE_OK
        : EVENT_QUEUE_INVALID_STATE;
}

EventQueueStatus event_queue_enqueue(
    EventQueue *queue,
    int event_code
)
{
    EventQueueStatus status = event_queue_validate(queue);
    size_t tail;

    if (status != EVENT_QUEUE_OK) {
        return status;
    }

    if (queue->size == queue->capacity) {
        return EVENT_QUEUE_FULL;
    }

    tail = (queue->head + queue->size) % queue->capacity;
    queue->data[tail] = event_code;
    queue->size += 1U;
    return EVENT_QUEUE_OK;
}

EventQueueStatus event_queue_dequeue(
    EventQueue *queue,
    int *out_event_code
)
{
    EventQueueStatus status;
    int result;
    size_t new_size;
    size_t new_head;

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
    new_size = queue->size - 1U;
    new_head = new_size == 0U
        ? 0U
        : (queue->head + 1U) % queue->capacity;

    queue->head = new_head;
    queue->size = new_size;
    *out_event_code = result;
    return EVENT_QUEUE_OK;
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
