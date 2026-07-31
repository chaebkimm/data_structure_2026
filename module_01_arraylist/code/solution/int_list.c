#include "int_list.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum {
    INT_LIST_INITIAL_CAPACITY = 4
};

#ifdef INT_LIST_TESTING
static bool int_list_should_fail_next_allocation = false;

void int_list_test_fail_next_allocation(void)
{
    int_list_should_fail_next_allocation = true;
}
#endif

static void *int_list_reallocate(void *old_pointer, size_t new_bytes)
{
#ifdef INT_LIST_TESTING
    if (int_list_should_fail_next_allocation) {
        int_list_should_fail_next_allocation = false;
        return NULL;
    }
#endif

    return realloc(old_pointer, new_bytes);
}

static size_t int_list_max_capacity(void)
{
    return SIZE_MAX / sizeof(int);
}

IntListStatus int_list_init(IntList *list)
{
    if (list == NULL) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    list->data = NULL;
    list->size = 0U;
    list->capacity = 0U;
    return INT_LIST_OK;
}

void int_list_destroy(IntList *list)
{
    if (list == NULL) {
        return;
    }

    free(list->data);
    list->data = NULL;
    list->size = 0U;
    list->capacity = 0U;
}

bool int_list_is_valid(const IntList *list)
{
    if (list == NULL || list->size > list->capacity) {
        return false;
    }

    if (list->capacity == 0U) {
        return list->data == NULL && list->size == 0U;
    }

    return list->data != NULL;
}

IntListStatus int_list_reserve(
    IntList *list,
    size_t minimum_capacity
)
{
    size_t maximum_capacity;
    size_t new_capacity;
    size_t new_bytes;
    int *candidate;

    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (minimum_capacity <= list->capacity) {
        return INT_LIST_OK;
    }

    maximum_capacity = int_list_max_capacity();
    if (list->capacity > maximum_capacity ||
        minimum_capacity > maximum_capacity) {
        return INT_LIST_ERR_OVERFLOW;
    }

    new_capacity = list->capacity == 0U
        ? (size_t)INT_LIST_INITIAL_CAPACITY
        : list->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > maximum_capacity / 2U) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2U;
    }

    if (new_capacity > maximum_capacity) {
        return INT_LIST_ERR_OVERFLOW;
    }

    new_bytes = new_capacity * sizeof *list->data;
    candidate = int_list_reallocate(list->data, new_bytes);
    if (candidate == NULL) {
        return INT_LIST_ERR_ALLOCATION;
    }

    list->data = candidate;
    list->capacity = new_capacity;
    return INT_LIST_OK;
}

IntListStatus int_list_get(
    const IntList *list,
    size_t index,
    int *out_value
)
{
    if (!int_list_is_valid(list) || out_value == NULL) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (index >= list->size) {
        return INT_LIST_ERR_OUT_OF_RANGE;
    }

    *out_value = list->data[index];
    return INT_LIST_OK;
}

IntListStatus int_list_append(
    IntList *list,
    int value
)
{
    IntListStatus status;

    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (list->size >= int_list_max_capacity()) {
        return INT_LIST_ERR_OVERFLOW;
    }

    status = int_list_reserve(list, list->size + 1U);
    if (status != INT_LIST_OK) {
        return status;
    }

    list->data[list->size] = value;
    list->size += 1U;
    return INT_LIST_OK;
}

IntListStatus int_list_insert(
    IntList *list,
    size_t index,
    int value
)
{
    IntListStatus status;
    size_t elements_to_move;

    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (index > list->size) {
        return INT_LIST_ERR_OUT_OF_RANGE;
    }

    if (list->size >= int_list_max_capacity()) {
        return INT_LIST_ERR_OVERFLOW;
    }

    status = int_list_reserve(list, list->size + 1U);
    if (status != INT_LIST_OK) {
        return status;
    }

    elements_to_move = list->size - index;
    if (elements_to_move > 0U) {
        memmove(
            &list->data[index + 1U],
            &list->data[index],
            elements_to_move * sizeof *list->data
        );
    }

    list->data[index] = value;
    list->size += 1U;
    return INT_LIST_OK;
}

IntListStatus int_list_remove(
    IntList *list,
    size_t index,
    int *out_value
)
{
    size_t elements_to_move;

    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (index >= list->size) {
        return INT_LIST_ERR_OUT_OF_RANGE;
    }

    if (out_value != NULL) {
        *out_value = list->data[index];
    }

    elements_to_move = list->size - index - 1U;
    if (elements_to_move > 0U) {
        memmove(
            &list->data[index],
            &list->data[index + 1U],
            elements_to_move * sizeof *list->data
        );
    }

    list->size -= 1U;
    return INT_LIST_OK;
}

const char *int_list_status_name(IntListStatus status)
{
    switch (status) {
        case INT_LIST_OK:
            return "ok";
        case INT_LIST_ERR_INVALID_ARGUMENT:
            return "invalid argument or representation";
        case INT_LIST_ERR_OUT_OF_RANGE:
            return "index out of range";
        case INT_LIST_ERR_ALLOCATION:
            return "allocation failed";
        case INT_LIST_ERR_OVERFLOW:
            return "capacity or byte-count overflow";
        default:
            return "unknown IntList status";
    }
}
