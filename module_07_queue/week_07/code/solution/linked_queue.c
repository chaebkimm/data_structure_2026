#include "support.h"
#include <stdint.h>

LqStatus lq_enqueue(LinkedQueue *q, int value)
{
    QueueNode *node;
    if (q == NULL) return LQ_ARGUMENT;
    if (q->size == SIZE_MAX) return LQ_LIMIT;
    node = lq_node_create(value);
    if (node == NULL) return LQ_ALLOCATION;
    if (q->tail == NULL) q->head = node;
    else q->tail->next = node;
    q->tail = node;
    ++q->size;
    return LQ_OK;
}

LqStatus lq_dequeue(LinkedQueue *q, int *out)
{
    QueueNode *old;
    int value;
    if (q == NULL || out == NULL) return LQ_ARGUMENT;
    if (q->head == NULL) return LQ_EMPTY;
    old = q->head;
    value = old->value;
    q->head = old->next;
    --q->size;
    if (q->head == NULL) q->tail = NULL;
    lq_node_release(old);
    *out = value;
    return LQ_OK;
}
