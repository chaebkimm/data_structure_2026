#include "int_stack.h"

#include <stddef.h>

static int int_stack_metadata_is_valid(int size, int capacity)
{
    return size >= 0 && capacity >= 0 && size <= capacity;
}

int int_stack_push(int stack[], int size, int capacity, int value)
{
    if (!int_stack_metadata_is_valid(size, capacity) ||
        size == capacity || stack == NULL) {
        return size;
    }

    /*
     * TODO(core): Store value at stack[size], then return the new size.
     * Do not change the array on any rejected call.
     */
    (void)value;
    return size;
}

int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
)
{
    if (!int_stack_metadata_is_valid(size, capacity) ||
        size == 0 || stack == NULL || out_value == NULL) {
        return 0;
    }

    /*
     * TODO(core): Copy stack[size - 1] to *out_value without changing the
     * stack, then report success.
     */
    return 0;
}

int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
)
{
    if (!int_stack_metadata_is_valid(size, capacity) ||
        size == 0 || stack == NULL || out_value == NULL) {
        return size;
    }

    /*
     * TODO(core): Copy stack[size - 1] to *out_value, then return size - 1.
     * Do not write to any stack slot.
     */
    return size;
}
