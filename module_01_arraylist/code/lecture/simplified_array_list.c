#define CAPACITY 10

struct array_list {
    int array[CAPACITY];
    int size;
};

typedef struct array_list ArrayList;

int check_capacity(ArrayList *list)
{
    if (list->size >= CAPACITY) {
        return -1;
    }
    return 0;
}

int increase_size(ArrayList *list)
{
    if (check_capacity(list) < 0) {
        return -1;
    }
    list->size += 1;
    return 0;
}

void update_data(ArrayList *list, int where, int data)
{
    list->array[where] = data;
}

int append(ArrayList *list, int data)
{
    int len = list->size;

    if (increase_size(list) < 0) {
        return -1;
    }
    update_data(list, len, data);
    return 0;
}

int rectify_index(int where, int min, int max)
{
    if (where < min) {
        where = min;
    }
    if (where > max) {
        where = max;
    }
    return where;
}

int shift_right(ArrayList *list, int start, int last)
{
    int i;

    for (i = last; i >= start; i -= 1) {
        list->array[i + 1] = list->array[i];
    }
    return 0;
}

int insert(ArrayList *list, int where, int data)
{
    int n = list->size;

    if (increase_size(list) < 0) {
        return -1;
    }
    where = rectify_index(where, 0, n);
    shift_right(list, where, n - 1);
    update_data(list, where, data);
    return 0;
}

int shift_left(ArrayList *list, int start, int last)
{
    int i;

    for (i = start; i <= last; i += 1) {
        list->array[i - 1] = list->array[i];
    }
    return 0;
}

int decrease_size(ArrayList *list)
{
    if (list->size <= 0) {
        return -1;
    }
    list->size -= 1;
    return 0;
}

int check_index(int where, int min, int max)
{
    if (where < min || where > max) {
        return -1;
    }
    return 0;
}

int delete(ArrayList *list, int where)
{
    int n = list->size;

    if (check_index(where, 0, n - 1) < 0) {
        return -1;
    }
    shift_left(list, where + 1, n - 1);
    return decrease_size(list);
}

int contains(ArrayList *list, int data)
{
    int i;

    for (i = 0; i < list->size; i += 1) {
        if (list->array[i] == data) {
            return 1;
        }
    }
    return 0;
}

int find_index(ArrayList *list, int data)
{
    int i;

    for (i = 0; i < list->size; i += 1) {
        if (list->array[i] == data) {
            return i;
        }
    }
    return -1;
}
