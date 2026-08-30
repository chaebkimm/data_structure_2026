#ifndef INT_LIST_H
#define INT_LIST_H

/*
 * A list uses a caller-owned array and two separate integers:
 * size counts active elements; capacity is the fixed usable array bound.
 * Valid metadata satisfies 0 <= size <= capacity. Capacity may be zero.
 *
 * Every array argument must refer to a live array with at least capacity
 * elements. The functions cannot discover the actual array extent. The
 * caller is responsible for meeting this precondition.
 */

/* Returns 1 for valid metadata and 0 <= index < size; otherwise returns 0. */
int int_list_valid_index(int size, int capacity, int index);

/*
 * Appends value when metadata is valid and size < capacity.
 * Returns size + 1 on success. On rejection, returns the original size and
 * leaves the entire array unchanged. The caller stores the returned size.
 */
int int_list_append(int array[], int size, int capacity, int value);

/*
 * Inserts value at an index in [0, size], shifting the suffix right.
 * Requires valid metadata and spare capacity. Returns size + 1 on success;
 * otherwise returns the original size and leaves the array unchanged.
 */
int int_list_insert(
    int array[],
    int size,
    int capacity,
    int index,
    int value
);

/*
 * Removes the element at an index in [0, size), shifting the suffix left.
 * Returns size - 1 on success. Invalid metadata or an invalid index leaves
 * the array unchanged and returns the original size. The inactive tail
 * does not need to be cleared.
 */
int int_list_remove(int array[], int size, int capacity, int index);

/*
 * Read-only linear search. Returns the first matching active index or -1
 * when value is absent or metadata is invalid.
 */
int int_list_find(const int array[], int size, int capacity, int value);

#endif
