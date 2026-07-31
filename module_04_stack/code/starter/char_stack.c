#include "char_stack.h"

#include <stdbool.h>
#include <stdlib.h>

enum {
    CHAR_STACK_INITIAL_CAPACITY = 4
};

#ifdef CHAR_STACK_TESTING
static bool char_stack_fail_next_allocation = false;

void char_stack_test_fail_next_allocation(void)
{
    char_stack_fail_next_allocation = true;
}
#endif

static void *char_stack_reallocate(
    void *old_pointer,
    size_t new_bytes
)
{
#ifdef CHAR_STACK_TESTING
    if (char_stack_fail_next_allocation) {
        char_stack_fail_next_allocation = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

StackStatus char_stack_init(CharStack *stack, size_t limit)
{
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    if (limit > (size_t)CHAR_STACK_MAX_LIMIT) {
        return STACK_LIMIT;
    }

    stack->data = NULL;
    stack->size = 0U;
    stack->capacity = 0U;
    stack->limit = limit;
    return STACK_OK;
}

StackStatus char_stack_validate(const CharStack *stack)
{
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    if (stack->limit > (size_t)CHAR_STACK_MAX_LIMIT ||
        stack->size > stack->capacity ||
        stack->capacity > stack->limit) {
        return STACK_INVALID_STATE;
    }

    if (stack->capacity == 0U) {
        if (stack->data != NULL || stack->size != 0U) {
            return STACK_INVALID_STATE;
        }
    } else if (stack->data == NULL) {
        return STACK_INVALID_STATE;
    }

    return STACK_OK;
}

static size_t char_stack_next_capacity(const CharStack *stack)
{
    size_t next_capacity;

    if (stack->capacity == 0U) {
        next_capacity = (size_t)CHAR_STACK_INITIAL_CAPACITY;
    } else {
        next_capacity = stack->capacity * 2U;
    }

    if (next_capacity > stack->limit) {
        next_capacity = stack->limit;
    }

    return next_capacity;
}

StackStatus char_stack_push(CharStack *stack, char value)
{
    StackStatus status;

    status = char_stack_validate(stack);
    if (status != STACK_OK) {
        return status;
    }

    if (stack->size == stack->limit) {
        return STACK_LIMIT;
    }

    if (stack->size == stack->capacity) {
        size_t new_capacity = char_stack_next_capacity(stack);
        char *candidate = NULL;

        /*
         * TODO(core): Call char_stack_reallocate with the currently owned
         * pointer and the byte count for new_capacity characters. Keep the
         * result in candidate so a failed call cannot erase stack->data.
         */
        (void)char_stack_reallocate;
        if (candidate == NULL) {
            return STACK_ALLOCATION;
        }

        /*
         * TODO(core): Commit successful growth. Store candidate in data and
         * new_capacity in capacity. Do not change size here.
         */
        (void)candidate;
        (void)new_capacity;
    }

    /*
     * TODO(core): Store value at the old size, then increase size. The top
     * after success must be data[size - 1].
     */
    (void)value;
    return STACK_INVALID_STATE;
}

StackStatus char_stack_pop(CharStack *stack, char *out_value)
{
    StackStatus status;

    if (out_value == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    status = char_stack_validate(stack);
    if (status != STACK_OK) {
        return status;
    }

    if (stack->size == 0U) {
        return STACK_UNDERFLOW;
    }

    /*
     * TODO(core): Read data[size - 1], decrease size, and change *out_value
     * only after all failure checks. Do not shrink capacity.
     */
    return STACK_INVALID_STATE;
}

StackStatus char_stack_peek(
    const CharStack *stack,
    char *out_value
)
{
    StackStatus status;

    if (out_value == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    status = char_stack_validate(stack);
    if (status != STACK_OK) {
        return status;
    }

    if (stack->size == 0U) {
        return STACK_UNDERFLOW;
    }

    /*
     * TODO(core): Copy data[size - 1] to *out_value without changing size.
     */
    return STACK_INVALID_STATE;
}

void char_stack_destroy(CharStack *stack)
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

const char *stack_status_name(StackStatus status)
{
    switch (status) {
        case STACK_OK:
            return "ok";
        case STACK_INVALID_ARGUMENT:
            return "invalid argument";
        case STACK_LIMIT:
            return "stack limit reached or requested limit too large";
        case STACK_UNDERFLOW:
            return "stack is empty";
        case STACK_ALLOCATION:
            return "allocation failed";
        case STACK_INVALID_STATE:
            return "stack representation is invalid";
        default:
            return "unknown StackStatus";
    }
}
