#include "support.h"
#include <stdlib.h>

#ifdef LQ_TESTING
static bool fail_next;
static size_t live_nodes;
void lq_test_fail_next_allocation(void) { fail_next = true; }
size_t lq_test_live_nodes(void) { return live_nodes; }
#endif

QueueNode *lq_node_create(int value)
{
    QueueNode *node;
#ifdef LQ_TESTING
    if (fail_next) { fail_next = false; return NULL; }
#endif
    node = malloc(sizeof *node);
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
#ifdef LQ_TESTING
    ++live_nodes;
#endif
    return node;
}

void lq_node_release(QueueNode *node)
{
    if (node == NULL) return;
#ifdef LQ_TESTING
    --live_nodes;
#endif
    free(node);
}

LqStatus lq_peek(const LinkedQueue *q, int *out)
{
    if (q == NULL || out == NULL) return LQ_ARGUMENT;
    if (q->head == NULL) return LQ_EMPTY;
    *out = q->head->value;
    return LQ_OK;
}

void lq_destroy(LinkedQueue *q)
{
    QueueNode *node;
    if (q == NULL) return;
    node = q->head;
    while (node != NULL) {
        QueueNode *next = node->next;
        lq_node_release(node);
        node = next;
    }
    *q = (LinkedQueue){0};
}

bool lq_is_valid(const LinkedQueue *q)
{
    const QueueNode *node;
    const QueueNode *last = NULL;
    size_t count = 0;
    if (q == NULL) return false;
    if (q->size == 0) return q->head == NULL && q->tail == NULL;
    if (q->head == NULL || q->tail == NULL) return false;
    node = q->head;
    while (node != NULL && count < q->size) {
        last = node;
        node = node->next;
        ++count;
    }
    return count == q->size && node == NULL && last == q->tail;
}
