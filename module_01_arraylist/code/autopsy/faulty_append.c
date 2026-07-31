/*
 * INTENTIONALLY BROKEN TRAINING PROGRAM.
 *
 * Build and run separately from the normal library tests. Identify the
 * earliest invalid state before focusing on the line where a fault appears.
 */

#include "int_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *simulated_failed_realloc(
    void *old_pointer,
    size_t requested_bytes
)
{
    (void)old_pointer;
    (void)requested_bytes;
    return NULL;
}

static int broken_grow(IntList *list, size_t new_capacity)
{
    list->data = simulated_failed_realloc(
        list->data,
        new_capacity * sizeof *list->data
    );
    list->capacity = new_capacity;

    if (list->data == NULL) {
        return 0;
    }

    return 1;
}

static int has_valid_shape(const IntList *list)
{
    if (list == NULL || list->size > list->capacity) {
        return 0;
    }

    if (list->capacity == 0U) {
        return list->data == NULL && list->size == 0U;
    }

    return list->data != NULL;
}

int main(int argc, char **argv)
{
    IntList list;
    int *diagnostic_original;

    list.data = malloc(4U * sizeof *list.data);
    if (list.data == NULL) {
        (void)fprintf(stderr, "setup allocation failed\n");
        return 2;
    }

    list.size = 4U;
    list.capacity = 4U;
    list.data[0] = 11;
    list.data[1] = 22;
    list.data[2] = 33;
    list.data[3] = 44;
    diagnostic_original = list.data;

    (void)printf(
        "before: data=%p size=%zu capacity=%zu first=%d\n",
        (void *)list.data,
        list.size,
        list.capacity,
        list.data[0]
    );

    (void)broken_grow(&list, 8U);

    (void)printf(
        "after failed growth: data=%p size=%zu capacity=%zu valid=%s\n",
        (void *)list.data,
        list.size,
        list.capacity,
        has_valid_shape(&list) ? "yes" : "no"
    );
    (void)printf(
        "diagnostic: original allocation address was %p\n",
        (void *)diagnostic_original
    );

    if (argc > 1 && strcmp(argv[1], "--inspect-only") == 0) {
        free(diagnostic_original);
        return 0;
    }

    (void)printf("continuing to the next list write...\n");
    (void)fflush(stdout);

    list.data[0] = 99;

    free(diagnostic_original);
    return 0;
}
