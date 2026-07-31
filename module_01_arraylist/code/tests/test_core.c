#include "int_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;
static IntList *active_list = NULL;

static void track_active_list(IntList *list)
{
    active_list = list;
}

static void release_active_list(void)
{
    if (active_list != NULL) {
        int_list_destroy(active_list);
        active_list = NULL;
    }
}

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            release_active_list();                                           \
            return false;                                                    \
        }                                                                    \
    } while (false)

static void run_test(const char *name, TestFunction test)
{
    bool passed;

    tests_run += 1U;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        (void)printf("FAIL %s\n", name);
    }
}

static bool test_null_arguments(void)
{
    IntList list;
    int output = 71;

    REQUIRE(int_list_init(NULL) == INT_LIST_ERR_INVALID_ARGUMENT);
    int_list_destroy(NULL);
    REQUIRE(!int_list_is_valid(NULL));
    REQUIRE(int_list_reserve(NULL, 4U) == INT_LIST_ERR_INVALID_ARGUMENT);
    REQUIRE(int_list_append(NULL, 9) == INT_LIST_ERR_INVALID_ARGUMENT);
    REQUIRE(
        int_list_get(NULL, 0U, &output) ==
        INT_LIST_ERR_INVALID_ARGUMENT
    );

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(
        int_list_get(&list, 0U, NULL) ==
        INT_LIST_ERR_INVALID_ARGUMENT
    );
    REQUIRE(output == 71);
    release_active_list();
    return true;
}

static bool test_initialization_and_destroy(void)
{
    IntList list;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_is_valid(&list));
    REQUIRE(list.data == NULL);
    REQUIRE(list.size == 0U);
    REQUIRE(list.capacity == 0U);

    release_active_list();
    REQUIRE(int_list_is_valid(&list));
    REQUIRE(list.data == NULL);
    REQUIRE(list.size == 0U);
    REQUIRE(list.capacity == 0U);

    int_list_destroy(&list);
    REQUIRE(int_list_is_valid(&list));
    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    release_active_list();
    return true;
}

static bool test_empty_access_and_reserve_zero(void)
{
    IntList list;
    int output = 1234;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(
        int_list_get(&list, 0U, &output) ==
        INT_LIST_ERR_OUT_OF_RANGE
    );
    REQUIRE(output == 1234);

    REQUIRE(int_list_reserve(&list, 0U) == INT_LIST_OK);
    REQUIRE(list.data == NULL);
    REQUIRE(list.size == 0U);
    REQUIRE(list.capacity == 0U);

    release_active_list();
    return true;
}

static bool test_first_append(void)
{
    IntList list;
    int output = 0;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_append(&list, 42) == INT_LIST_OK);
    REQUIRE(int_list_is_valid(&list));
    REQUIRE(list.data != NULL);
    REQUIRE(list.size == 1U);
    REQUIRE(list.capacity >= 1U);
    REQUIRE(int_list_get(&list, 0U, &output) == INT_LIST_OK);
    REQUIRE(output == 42);

    release_active_list();
    return true;
}

static bool test_repeated_growth_and_values(void)
{
    IntList list;
    size_t i;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);

    for (i = 0U; i < 512U; ++i) {
        int value = (int)i * 3 - 7;

        REQUIRE(int_list_append(&list, value) == INT_LIST_OK);
        REQUIRE(int_list_is_valid(&list));
        REQUIRE(list.size == i + 1U);
    }

    for (i = 0U; i < 512U; ++i) {
        int actual = 0;
        int expected = (int)i * 3 - 7;

        REQUIRE(int_list_get(&list, i, &actual) == INT_LIST_OK);
        REQUIRE(actual == expected);
    }

    release_active_list();
    return true;
}

static bool test_reserve_preserves_and_does_not_shrink(void)
{
    IntList list;
    int first = 0;
    int second = 0;
    int *pointer_after_growth;
    size_t capacity_after_growth;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_append(&list, 10) == INT_LIST_OK);
    REQUIRE(int_list_append(&list, 20) == INT_LIST_OK);

    REQUIRE(int_list_reserve(&list, 100U) == INT_LIST_OK);
    REQUIRE(int_list_is_valid(&list));
    REQUIRE(list.capacity >= 100U);
    REQUIRE(list.size == 2U);
    REQUIRE(int_list_get(&list, 0U, &first) == INT_LIST_OK);
    REQUIRE(int_list_get(&list, 1U, &second) == INT_LIST_OK);
    REQUIRE(first == 10);
    REQUIRE(second == 20);

    pointer_after_growth = list.data;
    capacity_after_growth = list.capacity;
    REQUIRE(int_list_reserve(&list, 2U) == INT_LIST_OK);
    REQUIRE(list.data == pointer_after_growth);
    REQUIRE(list.capacity == capacity_after_growth);
    REQUIRE(list.size == 2U);

    release_active_list();
    return true;
}

static bool test_boundaries_and_invalid_shape(void)
{
    IntList list;
    IntList invalid = { NULL, 1U, 1U };
    int output = 900;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_append(&list, 5) == INT_LIST_OK);
    REQUIRE(
        int_list_get(&list, list.size, &output) ==
        INT_LIST_ERR_OUT_OF_RANGE
    );
    REQUIRE(output == 900);
    REQUIRE(
        int_list_get(&list, SIZE_MAX, &output) ==
        INT_LIST_ERR_OUT_OF_RANGE
    );
    REQUIRE(output == 900);

    REQUIRE(!int_list_is_valid(&invalid));
    REQUIRE(
        int_list_append(&invalid, 7) ==
        INT_LIST_ERR_INVALID_ARGUMENT
    );

    release_active_list();
    return true;
}

static bool test_overflow_rejection_preserves_state(void)
{
    IntList list;
    int *old_data;
    size_t old_size;
    size_t old_capacity;
    int output = 0;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_append(&list, 88) == INT_LIST_OK);

    old_data = list.data;
    old_size = list.size;
    old_capacity = list.capacity;

    if (SIZE_MAX / sizeof(int) < SIZE_MAX) {
        REQUIRE(
            int_list_reserve(&list, SIZE_MAX) ==
            INT_LIST_ERR_OVERFLOW
        );
        REQUIRE(list.data == old_data);
        REQUIRE(list.size == old_size);
        REQUIRE(list.capacity == old_capacity);
        REQUIRE(int_list_get(&list, 0U, &output) == INT_LIST_OK);
        REQUIRE(output == 88);
    }

    release_active_list();
    return true;
}

int main(void)
{
    run_test("null arguments", test_null_arguments);
    run_test("initialization and destroy", test_initialization_and_destroy);
    run_test(
        "empty access and reserve zero",
        test_empty_access_and_reserve_zero
    );
    run_test("first append", test_first_append);
    run_test("repeated growth and values", test_repeated_growth_and_values);
    run_test(
        "reserve preservation and no shrink",
        test_reserve_preserves_and_does_not_shrink
    );
    run_test(
        "boundaries and invalid shape",
        test_boundaries_and_invalid_shape
    );
    run_test(
        "overflow rejection preserves state",
        test_overflow_rejection_preserves_state
    );

    (void)printf(
        "\n%u test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
