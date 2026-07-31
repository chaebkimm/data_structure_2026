#include "int_list.h"

#include <stdbool.h>
#include <stdio.h>

#ifndef INT_LIST_TESTING
#error "Compile this instructor test with INT_LIST_TESTING defined."
#endif

#define CHECK(condition)                                                     \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "requirement failed at %s:%d: %s\n",                        \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            goto cleanup;                                                    \
        }                                                                    \
    } while (false)

int main(void)
{
    const int expected[] = { 11, 22, 33, 44 };
    IntList list;
    IntListStatus status;
    int *old_data;
    size_t old_size;
    size_t old_capacity;
    size_t i;
    bool initialized = false;
    int exit_code = 1;

    CHECK(int_list_init(&list) == INT_LIST_OK);
    initialized = true;

    for (i = 0U; i < sizeof expected / sizeof expected[0]; ++i) {
        CHECK(int_list_append(&list, expected[i]) == INT_LIST_OK);
    }
    CHECK(list.size == list.capacity);

    old_data = list.data;
    old_size = list.size;
    old_capacity = list.capacity;

    int_list_test_fail_next_allocation();
    status = int_list_append(&list, 55);

    CHECK(status == INT_LIST_ERR_ALLOCATION);
    CHECK(int_list_is_valid(&list));
    CHECK(list.data == old_data);
    CHECK(list.size == old_size);
    CHECK(list.capacity == old_capacity);

    for (i = 0U; i < old_size; ++i) {
        int actual = 0;

        CHECK(int_list_get(&list, i, &actual) == INT_LIST_OK);
        CHECK(actual == expected[i]);
    }

    exit_code = 0;

cleanup:
    if (initialized) {
        int_list_destroy(&list);
    }

    if (exit_code == 0) {
        (void)printf(
            "PASS forced allocation failure preserves the entire list\n"
        );
    } else {
        (void)printf(
            "FAIL forced allocation failure preserves the entire list\n"
        );
    }

    return exit_code;
}
