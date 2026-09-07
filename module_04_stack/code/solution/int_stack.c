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

    stack[size] = value;
    return size + 1;
}

int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
)
{
    int result;

    if (!int_stack_metadata_is_valid(size, capacity) ||
        size == 0 || stack == NULL || out_value == NULL) {
        return 0;
    }

    result = stack[size - 1];
    *out_value = result;
    return 1;
}

int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
)
{
    int result;

    if (!int_stack_metadata_is_valid(size, capacity) ||
        size == 0 || stack == NULL || out_value == NULL) {
        return size;
    }

    result = stack[size - 1];
    *out_value = result;
    return size - 1;
}
