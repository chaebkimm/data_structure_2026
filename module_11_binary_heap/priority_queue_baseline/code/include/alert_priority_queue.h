#ifndef ALERT_PRIORITY_QUEUE_H
#define ALERT_PRIORITY_QUEUE_H

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
 * This implementation owns an unsorted dynamic array. Live records occupy
 * data[0] through data[size - 1]. comparison_count counts record-comparator
 * calls and saturates at SIZE_MAX instead of wrapping.
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
 * Checks constant-time relationships among the public fields. Capacity must
 * be exactly 0, 4, 8, 16, 32, or 64. The check cannot prove pointer liveness,
 * allocation extent, record initialization, unique ownership, or that live
 * records were not changed outside this API.
 */
AlertPriorityQueueStatus alert_priority_queue_validate(
    const AlertPriorityQueue *queue
);

/*
 * Appends a record to the unsorted array and assigns its arrival sequence.
 * Capacity grows 0, 4, 8, 16, 32, 64. Insert performs zero record
 * comparisons. Every failure preserves all fields and allocated slots.
 */
AlertPriorityQueueStatus alert_priority_queue_insert(
    AlertPriorityQueue *queue,
    int alert_id,
    size_t priority
);

/*
 * Reports the minimum record without removing it. A successful scan of n
 * records adds n - 1 to comparison_count, saturating at SIZE_MAX. The output
 * changes only on success and must not point inside the Queue allocation.
 */
AlertPriorityQueueStatus alert_priority_queue_peek_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

/*
 * Removes and reports the minimum record. The vacated position is filled
 * from the final live slot, so physical array order is not an ADT promise.
 * A successful scan of n records adds n - 1 comparisons. The output changes
 * only on success and must not point inside the Queue allocation.
 */
AlertPriorityQueueStatus alert_priority_queue_extract_min(
    AlertPriorityQueue *queue,
    AlertRecord *out_record
);

/*
 * Resets only the diagnostic comparison counter. Records, capacity,
 * sequence state, and storage identity do not change.
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
