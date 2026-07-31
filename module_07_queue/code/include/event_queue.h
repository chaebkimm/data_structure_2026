#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stddef.h>

#define EVENT_QUEUE_MAX_CAPACITY 64U

/*
 * EventQueue owns one fixed-capacity array of synthetic integer event codes.
 * head is the physical index of the oldest event when size is positive.
 * capacity never changes after successful initialization.
 */
typedef struct {
    int *data;
    size_t capacity;
    size_t head;
    size_t size;
} EventQueue;

typedef enum {
    EVENT_QUEUE_OK = 0,
    EVENT_QUEUE_INVALID_ARGUMENT,
    EVENT_QUEUE_LIMIT,
    EVENT_QUEUE_FULL,
    EVENT_QUEUE_EMPTY,
    EVENT_QUEUE_ALLOCATION,
    EVENT_QUEUE_INVALID_STATE
} EventQueueStatus;

/*
 * Initializes an all-zero Queue variable or one previously reset by destroy.
 * Capacity may be zero and may not exceed 64. Positive capacity allocates
 * exactly once. Every failure leaves the complete Queue object unchanged.
 */
EventQueueStatus event_queue_init(
    EventQueue *queue,
    size_t capacity
);

/*
 * Checks relationships among visible fields. It cannot prove that a
 * non-NULL pointer still refers to usable storage, that the storage has
 * capacity integer slots, that live values were initialized, or that only
 * this Queue owns the storage.
 */
EventQueueStatus event_queue_validate(
    const EventQueue *queue
);

/*
 * Adds event_code after the newest queued event. A full Queue rejects the
 * new event. Every failure leaves all Queue fields and slots unchanged.
 */
EventQueueStatus event_queue_enqueue(
    EventQueue *queue,
    int event_code
);

/*
 * Removes and reports the oldest event. The output changes only on success
 * and must not point inside the Queue's owned allocation.
 */
EventQueueStatus event_queue_dequeue(
    EventQueue *queue,
    int *out_event_code
);

/*
 * Reports the oldest event without removing it. The Queue and output change
 * only as stated by success: the Queue never changes, and the output changes
 * only on success. The output must not point inside the owned allocation.
 */
EventQueueStatus event_queue_peek(
    const EventQueue *queue,
    int *out_event_code
);

/*
 * Releases owned storage and resets every field to zero/NULL. Passing NULL
 * does nothing. Every other argument must be initialized or already
 * destroyed.
 */
void event_queue_destroy(EventQueue *queue);

const char *event_queue_status_name(EventQueueStatus status);

#ifdef EVENT_QUEUE_TESTING
/* Makes the next positive-capacity initialization allocation fail once. */
void event_queue_test_fail_next_allocation(void);
#endif

#endif
