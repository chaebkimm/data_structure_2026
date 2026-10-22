#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H
#include <stdbool.h>
#include <stddef.h>

typedef struct QueueNode {
    int value;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
    size_t size;
} LinkedQueue;

typedef enum { LQ_OK, LQ_EMPTY, LQ_ALLOCATION, LQ_ARGUMENT, LQ_LIMIT } LqStatus;

/* Initialize with LinkedQueue q = {0}. Never shallow-copy a live Queue.
 * All operations require a valid Queue. Outputs must not alias its storage.
 * Empty: head == tail == NULL and size == 0.
 * Nonempty: exactly size uniquely owned nodes; tail is the last, next == NULL.
 * Failure preserves Queue and output. Allocation belongs to Queue on enqueue;
 * dequeue releases the node and copies its integer value to caller storage.
 */
LqStatus lq_enqueue(LinkedQueue *q, int value);
LqStatus lq_dequeue(LinkedQueue *q, int *out);
LqStatus lq_peek(const LinkedQueue *q, int *out);
void lq_destroy(LinkedQueue *q);
/* O(n) diagnostic on valid, live node pointers; cannot validate arbitrary addresses. */
bool lq_is_valid(const LinkedQueue *q);
#ifdef LQ_TESTING
void lq_test_fail_next_allocation(void);
size_t lq_test_live_nodes(void);
#endif
#endif
