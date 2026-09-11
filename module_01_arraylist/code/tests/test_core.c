#include "int_list.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

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
            return false;                                                    \
        }                                                                    \
    } while (false)

static bool same_values(const int actual[], const int expected[], int count)
{
    int index;

    for (index = 0; index < count; index = index + 1) {
        if (actual[index] != expected[index]) {
            return false;
        }
    }
    return true;
}

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

static bool test_checked_index_and_metadata(void)
{
    REQUIRE(int_list_valid_index(3, 10, 0) == 1);
    REQUIRE(int_list_valid_index(3, 10, 2) == 1);
    REQUIRE(int_list_valid_index(3, 10, 3) == 0);
    REQUIRE(int_list_valid_index(3, 10, -1) == 0);
    REQUIRE(int_list_valid_index(0, 10, 0) == 0);
    REQUIRE(int_list_valid_index(0, 0, 0) == 0);
    REQUIRE(int_list_valid_index(-1, 10, 0) == 0);
    REQUIRE(int_list_valid_index(3, -1, 0) == 0);
    REQUIRE(int_list_valid_index(11, 10, 0) == 0);
    return true;
}

static bool test_append_and_caller_size_update(void)
{
    int array[10] = { 0 };
    int size = 0;
    int capacity = 10;
    int index;

    size = int_list_append(array, size, capacity, 100);
    REQUIRE(size == 1);
    size = int_list_append(array, size, capacity, 200);
    REQUIRE(size == 2);
    size = int_list_append(array, size, capacity, 300);
    REQUIRE(size == 3);
    REQUIRE(array[0] == 100);
    REQUIRE(array[1] == 200);
    REQUIRE(array[2] == 300);

    for (index = 3; index < capacity; index = index + 1) {
        size = int_list_append(array, size, capacity, (index + 1) * 100);
        REQUIRE(size == index + 1);
    }
    REQUIRE(size == capacity);
    REQUIRE(array[9] == 1000);
    return true;
}

static bool test_direct_checked_read_and_update(void)
{
    int array[10] = { 100, 200, 300 };
    int size = 3;
    int capacity = 10;
    int index = 1;
    int value = -1;

    REQUIRE(int_list_valid_index(size, capacity, index) == 1);
    if (int_list_valid_index(size, capacity, index)) {
        value = array[index];
        array[index] = 500;
    }
    REQUIRE(value == 200);
    REQUIRE(array[0] == 100);
    REQUIRE(array[1] == 500);
    REQUIRE(array[2] == 300);

    index = size;
    if (int_list_valid_index(size, capacity, index)) {
        array[index] = 999;
    }
    REQUIRE(array[3] == 0);
    REQUIRE(size == 3);
    return true;
}

static bool test_find_first_active_match(void)
{
    const int array[10] = { 100, 200, 100, 300, 777 };

    REQUIRE(int_list_find(array, 4, 10, 100) == 0);
    REQUIRE(int_list_find(array, 4, 10, 300) == 3);
    REQUIRE(int_list_find(array, 4, 10, 999) == -1);
    REQUIRE(int_list_find(array, 4, 10, 777) == -1);
    REQUIRE(int_list_find(array, 0, 10, 100) == -1);
    REQUIRE(int_list_find(array, -1, 10, 100) == -1);
    REQUIRE(int_list_find(array, 11, 10, 100) == -1);
    REQUIRE(int_list_find(array, 4, -1, 100) == -1);
    return true;
}

static bool test_insert_front_middle_and_end(void)
{
    int array[10] = { 0 };
    const int expected[5] = { 5, 10, 15, 20, 25 };
    int size = 0;

    size = int_list_insert(array, size, 10, 0, 15);
    REQUIRE(size == 1);
    size = int_list_insert(array, size, 10, 0, 10);
    REQUIRE(size == 2);
    size = int_list_insert(array, size, 10, 0, 5);
    REQUIRE(size == 3);
    size = int_list_insert(array, size, 10, 3, 25);
    REQUIRE(size == 4);
    size = int_list_insert(array, size, 10, 3, 20);
    REQUIRE(size == 5);
    REQUIRE(same_values(array, expected, size));
    return true;
}

static bool test_remove_front_middle_and_end(void)
{
    int array[10] = { 10, 20, 30, 40, 50 };
    const int expected[2] = { 20, 40 };
    int size = 5;

    size = int_list_remove(array, size, 10, 0);
    REQUIRE(size == 4);
    size = int_list_remove(array, size, 10, 1);
    REQUIRE(size == 3);
    size = int_list_remove(array, size, 10, size - 1);
    REQUIRE(size == 2);
    REQUIRE(same_values(array, expected, size));

    size = int_list_remove(array, size, 10, 0);
    REQUIRE(size == 1);
    REQUIRE(array[0] == 40);
    size = int_list_remove(array, size, 10, 0);
    REQUIRE(size == 0);
    REQUIRE(int_list_remove(array, size, 10, 0) == 0);
    return true;
}

static bool test_textbook_operation_trace(void)
{
    int array[10] = { 0 };
    const int expected[5] = { 100, 600, 300, 400, 500 };
    const int after_remove[4] = { 100, 300, 400, 500 };
    int size = 0;
    int capacity = 10;

    size = int_list_append(array, size, capacity, 100);
    size = int_list_append(array, size, capacity, 200);
    size = int_list_append(array, size, capacity, 300);
    size = int_list_append(array, size, capacity, 400);
    size = int_list_append(array, size, capacity, 500);
    REQUIRE(size == 5);
    REQUIRE(int_list_valid_index(size, capacity, 1) == 1);
    REQUIRE(array[1] == 200);
    array[1] = 500;
    REQUIRE(int_list_find(array, size, capacity, 300) == 2);

    size = int_list_remove(array, size, capacity, 1);
    REQUIRE(size == 4);
    REQUIRE(same_values(array, after_remove, size));

    size = int_list_insert(array, size, capacity, 1, 600);
    REQUIRE(size == 5);
    REQUIRE(same_values(array, expected, size));
    REQUIRE(int_list_find(array, size, capacity, 600) == 1);
    return true;
}

static bool test_rejected_mutations_preserve_entire_array(void)
{
    int array[10] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    const int expected[10] = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100
    };

    REQUIRE(int_list_append(array, 10, 10, 999) == 10);
    REQUIRE(same_values(array, expected, 10));
    REQUIRE(int_list_insert(array, 10, 10, 0, 999) == 10);
    REQUIRE(same_values(array, expected, 10));
    REQUIRE(int_list_insert(array, 3, 10, -1, 999) == 3);
    REQUIRE(same_values(array, expected, 10));
    REQUIRE(int_list_insert(array, 3, 10, 4, 999) == 3);
    REQUIRE(same_values(array, expected, 10));
    REQUIRE(int_list_remove(array, 3, 10, -1) == 3);
    REQUIRE(same_values(array, expected, 10));
    REQUIRE(int_list_remove(array, 3, 10, 3) == 3);
    REQUIRE(same_values(array, expected, 10));

    REQUIRE(int_list_append(array, -1, 10, 999) == -1);
    REQUIRE(int_list_append(array, 3, -1, 999) == 3);
    REQUIRE(int_list_append(array, 3, 2, 999) == 3);
    REQUIRE(int_list_insert(array, -1, 10, 0, 999) == -1);
    REQUIRE(int_list_insert(array, 3, -1, 0, 999) == 3);
    REQUIRE(int_list_insert(array, 3, 2, 0, 999) == 3);
    REQUIRE(int_list_remove(array, -1, 10, 0) == -1);
    REQUIRE(int_list_remove(array, 3, -1, 0) == 3);
    REQUIRE(int_list_remove(array, 3, 2, 0) == 3);
    REQUIRE(same_values(array, expected, 10));
    return true;
}

int main(void)
{
    run_test("checked index and metadata", test_checked_index_and_metadata);
    run_test(
        "append and caller size update",
        test_append_and_caller_size_update
    );
    run_test(
        "direct checked read and update",
        test_direct_checked_read_and_update
    );
    run_test("find first active match", test_find_first_active_match);
    run_test("insert front, middle, and end", test_insert_front_middle_and_end);
    run_test("remove front, middle, and end", test_remove_front_middle_and_end);
    run_test("textbook operation trace", test_textbook_operation_trace);
    run_test(
        "rejected mutations preserve entire array",
        test_rejected_mutations_preserve_entire_array
    );

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
