#ifndef TREE_WORK_QUEUE_H
#define TREE_WORK_QUEUE_H

#include "tree_bfs.h"

#include <stddef.h>

typedef struct {
    const TreeNode *node;
    size_t depth;
} TreeWorkItem;

/*
 * Allocation-free circular Queue for BFS work. It owns no tree nodes.
 * limit is the active number of slots within the fixed 64-item array.
 */
typedef struct {
    TreeWorkItem data[TREE_BFS_MAX_NODES];
    size_t limit;
    size_t head;
    size_t size;
} TreeWorkQueue;

typedef enum {
    WORK_QUEUE_OK = 0,
    WORK_QUEUE_INVALID_ARGUMENT,
    WORK_QUEUE_LIMIT,
    WORK_QUEUE_UNDERFLOW,
    WORK_QUEUE_INVALID_STATE
} TreeWorkQueueStatus;

/*
 * Initializes or clears a Queue. limit may be zero and may not exceed 64.
 * Failure leaves the complete Queue unchanged.
 */
TreeWorkQueueStatus tree_work_queue_init(
    TreeWorkQueue *queue,
    size_t limit
);

TreeWorkQueueStatus tree_work_queue_validate(
    const TreeWorkQueue *queue
);

/*
 * Copies one non-NULL node/depth record to the back. A full Queue returns
 * WORK_QUEUE_LIMIT. Every failure preserves all fields and array slots.
 */
TreeWorkQueueStatus tree_work_queue_enqueue(
    TreeWorkQueue *queue,
    TreeWorkItem item
);

/*
 * Removes the front item. out_item must not point inside queue->data and
 * changes only on success. Empty removal returns WORK_QUEUE_UNDERFLOW.
 */
TreeWorkQueueStatus tree_work_queue_dequeue(
    TreeWorkQueue *queue,
    TreeWorkItem *out_item
);

const char *tree_work_queue_status_name(TreeWorkQueueStatus status);

#endif
