#ifndef INT_LIST_H
#define INT_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

typedef enum {
    INT_LIST_OK = 0,
    INT_LIST_ERR_INVALID_ARGUMENT,
    INT_LIST_ERR_OUT_OF_RANGE,
    INT_LIST_ERR_ALLOCATION,
    INT_LIST_ERR_OVERFLOW
} IntListStatus;

/*
 * Creates the canonical empty state: { NULL, 0, 0 }.
 * Call only for an uninitialized or previously destroyed IntList.
 */
IntListStatus int_list_init(IntList *list);

/*
 * Releases owned storage and restores the canonical empty state.
 * Passing NULL is a no-op. A non-NULL argument must refer to a valid
 * initialized or previously destroyed IntList, not arbitrary storage.
 */
void int_list_destroy(IntList *list);

/*
 * Checks the observable shape of the representation. It cannot prove
 * allocation extent, pointer liveness, initialized elements, or unique
 * ownership.
 */
bool int_list_is_valid(const IntList *list);

/*
 * Ensures capacity is at least minimum_capacity. Never shrinks or changes
 * size. On failure, the previous valid list remains unchanged.
 */
IntListStatus int_list_reserve(
    IntList *list,
    size_t minimum_capacity
);

/*
 * Copies the element at index into out_value.
 * Requires index < size and a non-NULL output pointer.
 * out_value must not point anywhere inside the list's allocation.
 */
IntListStatus int_list_get(
    const IntList *list,
    size_t index,
    int *out_value
);

/*
 * Adds value at the end. On failure, the previous valid list remains
 * unchanged.
 */
IntListStatus int_list_append(
    IntList *list,
    int value
);

/*
 * Extension: inserts at index. The valid insertion range is [0, size].
 */
IntListStatus int_list_insert(
    IntList *list,
    size_t index,
    int value
);

/*
 * Extension: removes the element at index. out_value may be NULL when the
 * caller does not need the removed integer. A non-NULL out_value must not
 * point inside the list's allocation. Removal does not shrink.
 */
IntListStatus int_list_remove(
    IntList *list,
    size_t index,
    int *out_value
);

const char *int_list_status_name(IntListStatus status);

#ifdef INT_LIST_TESTING
/*
 * Instructor-test seam. The next allocation request returns NULL.
 * This declaration and its implementation are absent from production builds.
 */
void int_list_test_fail_next_allocation(void);
#endif

#endif
