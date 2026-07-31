#include "tree_work_queue.h"

TreeWorkQueueStatus tree_work_queue_init(
    TreeWorkQueue *queue,
    size_t limit
)
{
    if (queue == NULL) {
        return WORK_QUEUE_INVALID_ARGUMENT;
    }

    if (limit > (size_t)TREE_BFS_MAX_NODES) {
        return WORK_QUEUE_LIMIT;
    }

    queue->limit = limit;
    queue->head = 0U;
    queue->size = 0U;
    return WORK_QUEUE_OK;
}

TreeWorkQueueStatus tree_work_queue_validate(
    const TreeWorkQueue *queue
)
{
    if (queue == NULL) {
        return WORK_QUEUE_INVALID_ARGUMENT;
    }

    if (queue->limit > (size_t)TREE_BFS_MAX_NODES ||
        queue->size > queue->limit) {
        return WORK_QUEUE_INVALID_STATE;
    }

    if (queue->size == 0U) {
        return queue->head == 0U
            ? WORK_QUEUE_OK
            : WORK_QUEUE_INVALID_STATE;
    }

    if (queue->limit == 0U || queue->head >= queue->limit) {
        return WORK_QUEUE_INVALID_STATE;
    }

    return WORK_QUEUE_OK;
}

TreeWorkQueueStatus tree_work_queue_enqueue(
    TreeWorkQueue *queue,
    TreeWorkItem item
)
{
    TreeWorkQueueStatus status = tree_work_queue_validate(queue);
    size_t tail;

    if (status != WORK_QUEUE_OK) {
        return status;
    }

    if (item.node == NULL) {
        return WORK_QUEUE_INVALID_ARGUMENT;
    }

    if (queue->size == queue->limit) {
        return WORK_QUEUE_LIMIT;
    }

    tail = (queue->head + queue->size) % queue->limit;
    queue->data[tail] = item;
    queue->size += 1U;
    return WORK_QUEUE_OK;
}

TreeWorkQueueStatus tree_work_queue_dequeue(
    TreeWorkQueue *queue,
    TreeWorkItem *out_item
)
{
    TreeWorkQueueStatus status;
    TreeWorkItem result;
    size_t new_size;
    size_t new_head;

    if (out_item == NULL) {
        return WORK_QUEUE_INVALID_ARGUMENT;
    }

    status = tree_work_queue_validate(queue);
    if (status != WORK_QUEUE_OK) {
        return status;
    }

    if (queue->size == 0U) {
        return WORK_QUEUE_UNDERFLOW;
    }

    result = queue->data[queue->head];
    new_size = queue->size - 1U;
    new_head = new_size == 0U
        ? 0U
        : (queue->head + 1U) % queue->limit;

    queue->head = new_head;
    queue->size = new_size;
    *out_item = result;
    return WORK_QUEUE_OK;
}

const char *tree_work_queue_status_name(TreeWorkQueueStatus status)
{
    switch (status) {
        case WORK_QUEUE_OK:
            return "ok";
        case WORK_QUEUE_INVALID_ARGUMENT:
            return "invalid argument";
        case WORK_QUEUE_LIMIT:
            return "Queue limit reached";
        case WORK_QUEUE_UNDERFLOW:
            return "Queue is empty";
        case WORK_QUEUE_INVALID_STATE:
            return "Queue representation is invalid";
        default:
            return "unknown TreeWorkQueueStatus";
    }
}
