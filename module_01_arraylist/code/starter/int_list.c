#include "int_list.h"

/* Supplied metadata check: size counts active slots within a fixed bound. */
static int int_list_valid_metadata(int size, int capacity)
{
    return size >= 0 && capacity >= 0 && size <= capacity;
}

int int_list_valid_index(int size, int capacity, int index)
{
    if (!int_list_valid_metadata(size, capacity)) {
        return 0;
    }

    /* TODO(core): Return 1 exactly when 0 <= index < size. */
    (void)index;
    return 0;
}

int int_list_append(int array[], int size, int capacity, int value)
{
    if (!int_list_valid_metadata(size, capacity)) {
        return size;
    }

    /*
     * TODO(core): Reject a full array without writing. Otherwise store value
     * at the old size and return size + 1. The caller updates its size.
     */
    (void)array;
    (void)value;
    return size;
}

int int_list_insert(
    int array[],
    int size,
    int capacity,
    int index,
    int value
)
{
    if (!int_list_valid_metadata(size, capacity)) {
        return size;
    }

    /*
     * TODO(core): Check 0 <= index <= size and reject a full array. Shift
     * right from the last active value toward index, store value, and
     * return size + 1. Rejected operations change no array element.
     */
    (void)array;
    (void)index;
    (void)value;
    return size;
}

int int_list_remove(int array[], int size, int capacity, int index)
{
    if (!int_list_valid_metadata(size, capacity)) {
        return size;
    }

    /*
     * TODO(core): Check 0 <= index < size. Shift every later active value
     * one position left and return size - 1. The inactive tail need not be
     * cleared.
     */
    (void)array;
    (void)index;
    return size;
}

int int_list_find(const int array[], int size, int capacity, int value)
{
    if (!int_list_valid_metadata(size, capacity)) {
        return -1;
    }

    /*
     * TODO(core): Scan active indexes from 0 upward. Return the first index
     * whose value matches, or -1 when no active value matches.
     */
    (void)array;
    (void)value;
    return -1;
}
