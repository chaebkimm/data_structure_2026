#ifndef VERTEX_QUEUE_H
#define VERTEX_QUEUE_H

#include "graph_matrix.h"

#include <stddef.h>

#define VERTEX_QUEUE_MAX_LIMIT GRAPH_MAX_VERTICES

/*
 * Allocation-free circular Queue of graph vertex IDs. limit selects the
 * active prefix of data; head identifies the oldest queued vertex.
 */
typedef struct {
    size_t data[GRAPH_MAX_VERTICES];
    size_t limit;
    size_t head;
    size_t size;
} VertexQueue;

typedef enum {
    VERTEX_QUEUE_OK = 0,
    VERTEX_QUEUE_INVALID_ARGUMENT,
    VERTEX_QUEUE_LIMIT,
    VERTEX_QUEUE_UNDERFLOW,
    VERTEX_QUEUE_INVALID_STATE
} VertexQueueStatus;

VertexQueueStatus vertex_queue_init(
    VertexQueue *queue,
    size_t limit
);

VertexQueueStatus vertex_queue_validate(
    const VertexQueue *queue
);

/*
 * Enqueue and dequeue use constant-time shape checks. Their Queue argument
 * must already satisfy the full validator; dequeue also checks the current
 * head ID before reporting it. The dequeue output must not point to any
 * element of queue->data; it must be separate caller-owned storage.
 */
VertexQueueStatus vertex_queue_enqueue(
    VertexQueue *queue,
    size_t vertex
);

VertexQueueStatus vertex_queue_dequeue(
    VertexQueue *queue,
    size_t *out_vertex
);

const char *vertex_queue_status_name(VertexQueueStatus status);

#endif
