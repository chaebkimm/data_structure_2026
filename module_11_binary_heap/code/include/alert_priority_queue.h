#ifndef ALERT_PRIORITY_QUEUE_H
#define ALERT_PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#define ALERT_PRIORITY_QUEUE_MAX_CAPACITY 64U

/*
 * A smaller priority number is processed first. arrival_sequence is assigned
 * by the Queue; callers do not choose it. For equal priorities, the smaller
 * arrival sequence is processed first.
 */
typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} AlertRecord;

/*
 * This backend owns a dynamic array representing one complete binary
 * minimum Heap. Live records occupy data[0] through data[size - 1].
 * comparison_count saturates at SIZE_MAX instead of wrapping.
 */
typedef struct {
    AlertRecord *data;
    size_t size;
    size_t capacity;
    size_t next_sequence;
    size_t comparison_count;
} AlertPriorityQueue;

typedef enum {
    ALERT_PRIORITY_QUEUE_OK = 0,
    ALERT_PRIORITY_QUEUE_INVALID_ARGUMENT,
    ALERT_PRIORITY_QUEUE_FULL,
    ALERT_PRIORITY_QUEUE_EMPTY,
    ALERT_PRIORITY_QUEUE_ALLOCATION,
    ALERT_PRIORITY_QUEUE_SEQUENCE_EXHAUSTED,
    ALERT_PRIORITY_QUEUE_INVALID_STATE
} AlertPriorityQueueStatus;

/*
 * Accepts only an all-zero Queue object. Initialization performs no
 * allocation. Every failure leaves the object unchanged.
 */
AlertPriorityQueueStatus alert_priority_queue_init(
    AlertPriorityQueue *queue
);

/*
 * Checks constant-time field relationships. Capacity must be exactly
 * 0, 4, 8, 16, 32, or 64. This shape check does not scan Heap order.
 */
AlertPriorityQueueStatus alert_priority_queue_validate(
    const AlertPriorityQueue *queue
);

/*
 * Checks every nonroot record against its parent, even after finding a
 * violation. A valid shape returns OK and writes true or false. A null output
 * is rejected before Queue validation. Failure preserves the output and
 * comparison counter. Success adds one diagnostic comparison per nonroot
 * record (zero when empty, otherwise size - 1), saturating at SIZE_MAX,
 * without changing records or other fields. The bool output must be separate
 * caller-owned storage, not a location inside the Queue allocation.
 */
AlertPriorityQueueStatus alert_priority_queue_is_min_heap(
    AlertPriorityQueue *queue,
    bool *out_is_min_heap
);

/*
 * Appends a record at the complete-tree end and sifts it toward the root.
 * Capacity grows 0, 4, 8, 16, 32, 64. Every failure preserves all fields
 * and allocated slots.
 */
AlertPriorityQueueStatus alert_priority_queue_insert(
    AlertPriorityQueue *queue,
    int alert_id,
    size_t priority
);

/*
 * Reports data[0] without removing it or comparing records. The output
 * changes only on success and must not point inside the Queue allocation.
 */
AlertPriorityQueueStatus alert_priority_queue_peek_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

/*
 * Removes the root, repairs one downward path, and reports the old root.
 * The output changes only on success and must not point inside the Queue
 * allocation.
 */
AlertPriorityQueueStatus alert_priority_queue_extract_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

/*
 * Resets only the diagnostic comparison counter.
 */
AlertPriorityQueueStatus alert_priority_queue_reset_comparisons(
    AlertPriorityQueue *queue
);

/*
 * Releases owned storage and restores the all-zero state. Passing NULL does
 * nothing. A non-NULL argument must be initialized or already destroyed.
 */
void alert_priority_queue_destroy(AlertPriorityQueue *queue);

const char *alert_priority_queue_status_name(
    AlertPriorityQueueStatus status
);

#ifdef ALERT_PRIORITY_QUEUE_TESTING
/* Makes the next attempted growth allocation fail once. */
void alert_priority_queue_test_fail_next_growth(void);
#endif

#endif
