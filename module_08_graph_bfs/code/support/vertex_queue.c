#include "vertex_queue.h"

VertexQueueStatus vertex_queue_init(
    VertexQueue *queue,
    size_t limit
)
{
    if (queue == NULL) {
        return VERTEX_QUEUE_INVALID_ARGUMENT;
    }
    if (limit > (size_t)VERTEX_QUEUE_MAX_LIMIT) {
        return VERTEX_QUEUE_LIMIT;
    }

    queue->limit = limit;
    queue->head = 0U;
    queue->size = 0U;
    return VERTEX_QUEUE_OK;
}

static VertexQueueStatus vertex_queue_check_shape(
    const VertexQueue *queue
)
{
    if (queue == NULL) {
        return VERTEX_QUEUE_INVALID_ARGUMENT;
    }
    if (queue->limit > (size_t)VERTEX_QUEUE_MAX_LIMIT ||
        queue->size > queue->limit) {
        return VERTEX_QUEUE_INVALID_STATE;
    }
    if (queue->size == 0U) {
        return queue->head == 0U
            ? VERTEX_QUEUE_OK
            : VERTEX_QUEUE_INVALID_STATE;
    }
    if (queue->limit == 0U || queue->head >= queue->limit) {
        return VERTEX_QUEUE_INVALID_STATE;
    }
    return VERTEX_QUEUE_OK;
}

VertexQueueStatus vertex_queue_validate(
    const VertexQueue *queue
)
{
    VertexQueueStatus status = vertex_queue_check_shape(queue);
    size_t offset;

    if (status != VERTEX_QUEUE_OK) {
        return status;
    }

    for (offset = 0U; offset < queue->size; ++offset) {
        size_t index = (queue->head + offset) % queue->limit;

        if (queue->data[index] >= (size_t)GRAPH_MAX_VERTICES) {
            return VERTEX_QUEUE_INVALID_STATE;
        }
    }
    return VERTEX_QUEUE_OK;
}

VertexQueueStatus vertex_queue_enqueue(
    VertexQueue *queue,
    size_t vertex
)
{
    VertexQueueStatus status = vertex_queue_check_shape(queue);
    size_t tail;

    if (status != VERTEX_QUEUE_OK) {
        return status;
    }
    if (vertex >= (size_t)GRAPH_MAX_VERTICES) {
        return VERTEX_QUEUE_INVALID_ARGUMENT;
    }
    if (queue->size == queue->limit) {
        return VERTEX_QUEUE_LIMIT;
    }

    tail = (queue->head + queue->size) % queue->limit;
    queue->data[tail] = vertex;
    queue->size += 1U;
    return VERTEX_QUEUE_OK;
}

VertexQueueStatus vertex_queue_dequeue(
    VertexQueue *queue,
    size_t *out_vertex
)
{
    VertexQueueStatus status;
    size_t candidate;
    size_t new_size;

    if (out_vertex == NULL) {
        return VERTEX_QUEUE_INVALID_ARGUMENT;
    }

    status = vertex_queue_check_shape(queue);
    if (status != VERTEX_QUEUE_OK) {
        return status;
    }
    if (queue->size == 0U) {
        return VERTEX_QUEUE_UNDERFLOW;
    }
    if (queue->data[queue->head] >=
        (size_t)GRAPH_MAX_VERTICES) {
        return VERTEX_QUEUE_INVALID_STATE;
    }

    candidate = queue->data[queue->head];
    new_size = queue->size - 1U;
    queue->head = new_size == 0U
        ? 0U
        : (queue->head + 1U) % queue->limit;
    queue->size = new_size;
    *out_vertex = candidate;
    return VERTEX_QUEUE_OK;
}

const char *vertex_queue_status_name(VertexQueueStatus status)
{
    switch (status) {
        case VERTEX_QUEUE_OK:
            return "ok";
        case VERTEX_QUEUE_INVALID_ARGUMENT:
            return "invalid argument";
        case VERTEX_QUEUE_LIMIT:
            return "vertex Queue limit reached";
        case VERTEX_QUEUE_UNDERFLOW:
            return "vertex Queue is empty";
        case VERTEX_QUEUE_INVALID_STATE:
            return "vertex Queue representation is invalid";
        default:
            return "unknown VertexQueueStatus";
    }
}
