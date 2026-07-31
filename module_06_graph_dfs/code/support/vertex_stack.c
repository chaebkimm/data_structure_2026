#include "vertex_stack.h"

#include <stdbool.h>
#include <stdlib.h>

enum {
    VERTEX_STACK_INITIAL_CAPACITY = 4
};

#ifdef GRAPH_DFS_TESTING
static bool vertex_stack_fail_next_allocation = false;

void vertex_stack_test_fail_next_allocation(void)
{
    vertex_stack_fail_next_allocation = true;
}
#endif

static void *vertex_stack_reallocate(
    void *old_pointer,
    size_t new_bytes
)
{
#ifdef GRAPH_DFS_TESTING
    if (vertex_stack_fail_next_allocation) {
        vertex_stack_fail_next_allocation = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

VertexStackStatus vertex_stack_init(
    VertexStack *stack,
    size_t limit
)
{
    if (stack == NULL) {
        return VERTEX_STACK_INVALID_ARGUMENT;
    }

    if (limit > (size_t)VERTEX_STACK_MAX_LIMIT) {
        return VERTEX_STACK_LIMIT;
    }

    stack->data = NULL;
    stack->size = 0U;
    stack->capacity = 0U;
    stack->limit = limit;
    return VERTEX_STACK_OK;
}

VertexStackStatus vertex_stack_validate(const VertexStack *stack)
{
    if (stack == NULL) {
        return VERTEX_STACK_INVALID_ARGUMENT;
    }

    if (stack->limit > (size_t)VERTEX_STACK_MAX_LIMIT ||
        stack->size > stack->capacity ||
        stack->capacity > stack->limit) {
        return VERTEX_STACK_INVALID_STATE;
    }

    if (stack->capacity == 0U) {
        if (stack->data != NULL || stack->size != 0U) {
            return VERTEX_STACK_INVALID_STATE;
        }
    } else if (stack->data == NULL) {
        return VERTEX_STACK_INVALID_STATE;
    }

    return VERTEX_STACK_OK;
}

static size_t vertex_stack_next_capacity(const VertexStack *stack)
{
    size_t next_capacity;

    if (stack->capacity == 0U) {
        next_capacity = (size_t)VERTEX_STACK_INITIAL_CAPACITY;
    } else {
        next_capacity = stack->capacity * 2U;
    }

    if (next_capacity > stack->limit) {
        next_capacity = stack->limit;
    }

    return next_capacity;
}

VertexStackStatus vertex_stack_push(
    VertexStack *stack,
    size_t vertex
)
{
    VertexStackStatus status = vertex_stack_validate(stack);

    if (status != VERTEX_STACK_OK) {
        return status;
    }

    if (vertex >= (size_t)GRAPH_MAX_VERTICES) {
        return VERTEX_STACK_INVALID_ARGUMENT;
    }

    if (stack->size == stack->limit) {
        return VERTEX_STACK_LIMIT;
    }

    if (stack->size == stack->capacity) {
        size_t new_capacity = vertex_stack_next_capacity(stack);
        size_t *candidate = vertex_stack_reallocate(
            stack->data,
            new_capacity * sizeof *stack->data
        );

        if (candidate == NULL) {
            return VERTEX_STACK_ALLOCATION;
        }

        stack->data = candidate;
        stack->capacity = new_capacity;
    }

    stack->data[stack->size] = vertex;
    stack->size += 1U;
    return VERTEX_STACK_OK;
}

VertexStackStatus vertex_stack_pop(
    VertexStack *stack,
    size_t *out_vertex
)
{
    VertexStackStatus status;
    size_t result;

    if (out_vertex == NULL) {
        return VERTEX_STACK_INVALID_ARGUMENT;
    }

    status = vertex_stack_validate(stack);
    if (status != VERTEX_STACK_OK) {
        return status;
    }

    if (stack->size == 0U) {
        return VERTEX_STACK_UNDERFLOW;
    }

    result = stack->data[stack->size - 1U];
    stack->size -= 1U;
    *out_vertex = result;
    return VERTEX_STACK_OK;
}

void vertex_stack_destroy(VertexStack *stack)
{
    if (stack == NULL) {
        return;
    }

    free(stack->data);
    stack->data = NULL;
    stack->size = 0U;
    stack->capacity = 0U;
    stack->limit = 0U;
}

const char *vertex_stack_status_name(VertexStackStatus status)
{
    switch (status) {
        case VERTEX_STACK_OK:
            return "ok";
        case VERTEX_STACK_INVALID_ARGUMENT:
            return "invalid argument";
        case VERTEX_STACK_LIMIT:
            return "Stack limit reached or requested limit too large";
        case VERTEX_STACK_UNDERFLOW:
            return "Stack is empty";
        case VERTEX_STACK_ALLOCATION:
            return "allocation failed";
        case VERTEX_STACK_INVALID_STATE:
            return "Stack representation is invalid";
        default:
            return "unknown VertexStackStatus";
    }
}
