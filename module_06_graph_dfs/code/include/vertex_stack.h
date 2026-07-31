#ifndef VERTEX_STACK_H
#define VERTEX_STACK_H

#include "graph_matrix.h"

#include <stddef.h>

#define VERTEX_STACK_MAX_LIMIT GRAPH_MAX_VERTICES

/*
 * This Stack stores vertex IDs. It owns its growable size_t array. The top
 * vertex is data[size - 1] when size is positive.
 */
typedef struct {
    size_t *data;
    size_t size;
    size_t capacity;
    size_t limit;
} VertexStack;

typedef enum {
    VERTEX_STACK_OK = 0,
    VERTEX_STACK_INVALID_ARGUMENT,
    VERTEX_STACK_LIMIT,
    VERTEX_STACK_UNDERFLOW,
    VERTEX_STACK_ALLOCATION,
    VERTEX_STACK_INVALID_STATE
} VertexStackStatus;

/*
 * Creates an empty Stack. limit may be zero and may not exceed 16.
 * Call only for an uninitialized or previously destroyed object.
 * Failure leaves the object unchanged.
 */
VertexStackStatus vertex_stack_init(
    VertexStack *stack,
    size_t limit
);

/*
 * Checks visible representation rules. It cannot prove that a non-NULL
 * address still refers to valid storage, is large enough, or belongs only
 * to this Stack.
 */
VertexStackStatus vertex_stack_validate(
    const VertexStack *stack
);

/*
 * Push accepts only a possible graph vertex ID, from 0 through 15. Storage
 * is requested only when needed. Capacity follows 0, 4, 8, and 16, with the
 * final increase shortened when the limit is smaller. Every failure leaves
 * the Stack unchanged.
 */
VertexStackStatus vertex_stack_push(
    VertexStack *stack,
    size_t vertex
);

/*
 * Pop changes out_vertex only on success. An empty Stack reports underflow.
 * out_vertex must not point into the Stack's owned array.
 */
VertexStackStatus vertex_stack_pop(
    VertexStack *stack,
    size_t *out_vertex
);

/*
 * Releases the owned array and resets every field. Passing NULL is a no-op.
 */
void vertex_stack_destroy(VertexStack *stack);

const char *vertex_stack_status_name(VertexStackStatus status);

#ifdef GRAPH_DFS_TESTING
/* Makes the next vertex-array allocation attempt fail once. */
void vertex_stack_test_fail_next_allocation(void);
#endif

#endif
