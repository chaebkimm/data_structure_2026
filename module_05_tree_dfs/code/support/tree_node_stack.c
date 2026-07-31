#include "tree_node_stack.h"

#include <stdbool.h>
#include <stdlib.h>

enum {
    TREE_NODE_STACK_INITIAL_CAPACITY = 4
};

#ifdef TREE_DFS_TESTING
static bool node_stack_fail_next_allocation = false;

void tree_node_stack_test_fail_next_allocation(void)
{
    node_stack_fail_next_allocation = true;
}
#endif

static void *node_stack_reallocate(void *old_pointer, size_t new_bytes)
{
#ifdef TREE_DFS_TESTING
    if (node_stack_fail_next_allocation) {
        node_stack_fail_next_allocation = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

NodeStackStatus tree_node_stack_init(
    TreeNodeStack *stack,
    size_t limit
)
{
    if (stack == NULL) {
        return NODE_STACK_INVALID_ARGUMENT;
    }

    if (limit > (size_t)TREE_NODE_STACK_MAX_LIMIT) {
        return NODE_STACK_LIMIT;
    }

    stack->data = NULL;
    stack->size = 0U;
    stack->capacity = 0U;
    stack->limit = limit;
    return NODE_STACK_OK;
}

NodeStackStatus tree_node_stack_validate(const TreeNodeStack *stack)
{
    if (stack == NULL) {
        return NODE_STACK_INVALID_ARGUMENT;
    }

    if (stack->limit > (size_t)TREE_NODE_STACK_MAX_LIMIT ||
        stack->size > stack->capacity ||
        stack->capacity > stack->limit) {
        return NODE_STACK_INVALID_STATE;
    }

    if (stack->capacity == 0U) {
        if (stack->data != NULL || stack->size != 0U) {
            return NODE_STACK_INVALID_STATE;
        }
    } else if (stack->data == NULL) {
        return NODE_STACK_INVALID_STATE;
    }

    return NODE_STACK_OK;
}

static size_t node_stack_next_capacity(const TreeNodeStack *stack)
{
    size_t next_capacity;

    if (stack->capacity == 0U) {
        next_capacity = (size_t)TREE_NODE_STACK_INITIAL_CAPACITY;
    } else {
        next_capacity = stack->capacity * 2U;
    }

    if (next_capacity > stack->limit) {
        next_capacity = stack->limit;
    }

    return next_capacity;
}

NodeStackStatus tree_node_stack_push(
    TreeNodeStack *stack,
    const TreeNode *node
)
{
    NodeStackStatus status = tree_node_stack_validate(stack);

    if (status != NODE_STACK_OK) {
        return status;
    }

    if (node == NULL) {
        return NODE_STACK_INVALID_ARGUMENT;
    }

    if (stack->size == stack->limit) {
        return NODE_STACK_LIMIT;
    }

    if (stack->size == stack->capacity) {
        size_t new_capacity = node_stack_next_capacity(stack);
        const TreeNode **candidate = node_stack_reallocate(
            stack->data,
            new_capacity * sizeof *stack->data
        );

        if (candidate == NULL) {
            return NODE_STACK_ALLOCATION;
        }

        stack->data = candidate;
        stack->capacity = new_capacity;
    }

    stack->data[stack->size] = node;
    stack->size += 1U;
    return NODE_STACK_OK;
}

NodeStackStatus tree_node_stack_pop(
    TreeNodeStack *stack,
    const TreeNode **out_node
)
{
    NodeStackStatus status;
    const TreeNode *result;

    if (out_node == NULL) {
        return NODE_STACK_INVALID_ARGUMENT;
    }

    status = tree_node_stack_validate(stack);
    if (status != NODE_STACK_OK) {
        return status;
    }

    if (stack->size == 0U) {
        return NODE_STACK_UNDERFLOW;
    }

    result = stack->data[stack->size - 1U];
    stack->size -= 1U;
    *out_node = result;
    return NODE_STACK_OK;
}

void tree_node_stack_destroy(TreeNodeStack *stack)
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

const char *node_stack_status_name(NodeStackStatus status)
{
    switch (status) {
        case NODE_STACK_OK:
            return "ok";
        case NODE_STACK_INVALID_ARGUMENT:
            return "invalid argument";
        case NODE_STACK_LIMIT:
            return "Stack limit reached or requested limit too large";
        case NODE_STACK_UNDERFLOW:
            return "Stack is empty";
        case NODE_STACK_ALLOCATION:
            return "allocation failed";
        case NODE_STACK_INVALID_STATE:
            return "Stack representation is invalid";
        default:
            return "unknown NodeStackStatus";
    }
}
