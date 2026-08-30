#include "int_list.h"

static int int_list_valid_metadata(int size, int capacity)
{
    return size >= 0 && capacity >= 0 && size <= capacity;
}

int int_list_valid_index(int size, int capacity, int index)
{
    return int_list_valid_metadata(size, capacity) &&
        index >= 0 && index < size;
}

int int_list_append(int array[], int size, int capacity, int value)
{
    if (!int_list_valid_metadata(size, capacity) || size == capacity) {
        return size;
    }

    array[size] = value;
    return size + 1;
}

int int_list_insert(
    int array[],
    int size,
    int capacity,
    int index,
    int value
)
{
    int position;

    if (!int_list_valid_metadata(size, capacity) ||
        index < 0 || index > size || size == capacity) {
        return size;
    }

    for (position = size; position > index; position = position - 1) {
        array[position] = array[position - 1];
    }
    array[index] = value;
    return size + 1;
}

int int_list_remove(int array[], int size, int capacity, int index)
{
    int position;

    if (!int_list_valid_index(size, capacity, index)) {
        return size;
    }

    for (position = index + 1; position < size; position = position + 1) {
        array[position - 1] = array[position];
    }
    return size - 1;
}

int int_list_find(const int array[], int size, int capacity, int value)
{
    int index;

    if (!int_list_valid_metadata(size, capacity)) {
        return -1;
    }

    for (index = 0; index < size; index = index + 1) {
        if (array[index] == value) {
            return index;
        }
    }
    return -1;
}
