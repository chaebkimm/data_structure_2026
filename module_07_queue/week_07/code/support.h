#ifndef LINKED_QUEUE_SUPPORT_H
#define LINKED_QUEUE_SUPPORT_H
#include "linked_queue.h"
QueueNode *lq_node_create(int value);
void lq_node_release(QueueNode *node);
#endif
