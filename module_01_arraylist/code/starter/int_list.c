#include "int_list.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

static size_t int_list_max_capacity(void)
{
    return SIZE_MAX / sizeof(int);
}

static IntListStatus int_list_choose_capacity(
    const IntList *list,
    size_t minimum_capacity,
    size_t *out_capacity
)
{
    size_t maximum_capacity;
    size_t new_capacity;

    if (!int_list_is_valid(list) || out_capacity == NULL) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (minimum_capacity <= list->capacity) {
        *out_capacity = list->capacity;
        return INT_LIST_OK;
    }

    maximum_capacity = int_list_max_capacity();
    if (list->capacity > maximum_capacity ||
        minimum_capacity > maximum_capacity) {
        return INT_LIST_ERR_OVERFLOW;
    }

    new_capacity = list->capacity == 0U ? 4U : list->capacity;
    while (new_capacity < minimum_capacity) {
        if (new_capacity > maximum_capacity / 2U) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2U;
    }

    *out_capacity = new_capacity;
    return INT_LIST_OK;
}

IntListStatus int_list_reserve(
    IntList *list,
    size_t minimum_capacity
)
{
    IntListStatus status;
    size_t new_capacity;
    size_t new_bytes;
    int *candidate;

    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    status = int_list_choose_capacity(
        list,
        minimum_capacity,
        &new_capacity
    );
    if (status != INT_LIST_OK) {
        return status;
    }

    if (new_capacity == list->capacity) {
        return INT_LIST_OK;
    }

    new_bytes = new_capacity * sizeof *list->data;

    /*
     * TODO(core): Replace the NULL placeholder with the address of the
     * currently owned allocation. The ordered scaffold has already selected
     * an overflow-safe capacity and byte count.
     */
    candidate = int_list_reallocate(NULL, new_bytes);

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

    /* TODO(core): copy the logical element to out_value. */
    return INT_LIST_ERR_INVALID_ARGUMENT;
}

IntListStatus int_list_append(
    IntList *list,
    int value
)
{
    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    (void)value;

    /*
     * TODO(core):
     * 1. Check that size + 1 is representable.
     * 2. Reserve before writing.
     * 3. Write at the old size.
     * 4. Increment size last.
     */
    return INT_LIST_ERR_ALLOCATION;
}

IntListStatus int_list_insert(
    IntList *list,
    size_t index,
    int value
)
{
    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (index > list->size) {
        return INT_LIST_ERR_OUT_OF_RANGE;
    }

    (void)value;

    /*
     * TODO(extension): reserve, shift the overlapping suffix right with
     * memmove, store value, and increment size. <string.h> is included.
     */
    return INT_LIST_ERR_INVALID_ARGUMENT;
}

IntListStatus int_list_remove(
    IntList *list,
    size_t index,
    int *out_value
)
{
    if (!int_list_is_valid(list)) {
        return INT_LIST_ERR_INVALID_ARGUMENT;
    }

    if (index >= list->size) {
        return INT_LIST_ERR_OUT_OF_RANGE;
    }

    (void)out_value;

    /*
     * TODO(extension): optionally copy the removed value, shift the
     * overlapping suffix left with memmove, and decrement size.
     */
    return INT_LIST_ERR_INVALID_ARGUMENT;
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
