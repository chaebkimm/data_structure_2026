#include "int_list.h"

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
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

static bool test_zero_usable_capacity(void)
{
    int array[1] = { 77 };

    REQUIRE(int_list_append(array, 0, 0, 10) == 0);
    REQUIRE(int_list_insert(array, 0, 0, 0, 10) == 0);
    REQUIRE(int_list_remove(array, 0, 0, 0) == 0);
    REQUIRE(int_list_find(array, 0, 0, 77) == -1);
    REQUIRE(array[0] == 77);
    return true;
}

static bool test_smaller_capacity_preserves_guard_slots(void)
{
    int array[5] = { 0, 0, 0, 777, 888 };
    const int expected[5] = { 10, 20, 30, 777, 888 };
    int size = 0;
    int capacity = 3;

    size = int_list_append(array, size, capacity, 10);
    size = int_list_append(array, size, capacity, 20);
    size = int_list_append(array, size, capacity, 30);
    REQUIRE(size == 3);
    REQUIRE(int_list_append(array, size, capacity, 40) == 3);
    REQUIRE(int_list_insert(array, size, capacity, 1, 40) == 3);
    REQUIRE(same_values(array, expected, 5));

    size = int_list_remove(array, size, capacity, 1);
    REQUIRE(size == 2);
    size = int_list_insert(array, size, capacity, 1, 20);
    REQUIRE(size == 3);
    REQUIRE(same_values(array, expected, 5));
    return true;
}

static bool test_integer_extremes_and_invalid_metadata(void)
{
    int array[3] = { INT_MIN, 0, INT_MAX };
    const int expected[3] = { INT_MIN, 0, INT_MAX };

    REQUIRE(int_list_find(array, 3, 3, INT_MIN) == 0);
    REQUIRE(int_list_find(array, 3, 3, INT_MAX) == 2);
    REQUIRE(int_list_valid_index(INT_MAX, INT_MAX, INT_MAX - 1) == 1);
    REQUIRE(int_list_valid_index(INT_MIN, 3, 0) == 0);
    REQUIRE(int_list_valid_index(3, INT_MIN, 0) == 0);
    REQUIRE(int_list_insert(array, 3, 3, INT_MAX, 1) == 3);
    REQUIRE(int_list_remove(array, 3, 3, INT_MIN) == 3);
    REQUIRE(int_list_append(array, INT_MAX, 3, 1) == INT_MAX);
    REQUIRE(int_list_find(array, INT_MAX, 3, 0) == -1);
    REQUIRE(same_values(array, expected, 3));
    return true;
}

static bool test_inactive_tail_is_not_part_of_the_list(void)
{
    int array[4] = { 10, 20, 30, 999 };
    int size = 3;

    size = int_list_remove(array, size, 4, 1);
    REQUIRE(size == 2);
    REQUIRE(array[0] == 10);
    REQUIRE(array[1] == 30);

    array[2] = 777;
    REQUIRE(int_list_find(array, size, 4, 777) == -1);
    size = int_list_append(array, size, 4, 40);
    REQUIRE(size == 3);
    REQUIRE(array[2] == 40);
    REQUIRE(array[3] == 999);
    return true;
}

static bool test_deterministic_differential_sequence(void)
{
    enum { CAPACITY = 10, PHYSICAL_SLOTS = 12, STEPS = 1000 };
    int array[PHYSICAL_SLOTS] = { 0 };
    int before[PHYSICAL_SLOTS];
    int reference[CAPACITY] = { 0 };
    int size = 0;
    int reference_size = 0;
    uint32_t state = UINT32_C(0xC0FFEE);
    int step;

    array[CAPACITY] = 12345;
    array[CAPACITY + 1] = -12345;

    for (step = 0; step < STEPS; step = step + 1) {
        int operation;
        int index;
        int value;
        int position;
        bool rejected = false;

        state = state * UINT32_C(1664525) + UINT32_C(1013904223);
        operation = (int)(state % UINT32_C(5));
        value = (int)((state >> 8U) % UINT32_C(41)) - 20;
        index = (int)(state % (uint32_t)(reference_size + 3)) - 1;
        for (position = 0;
             position < PHYSICAL_SLOTS;
             position = position + 1) {
            before[position] = array[position];
        }

        if (operation == 0) {
            size = int_list_append(array, size, CAPACITY, value);
            if (reference_size < CAPACITY) {
                reference[reference_size] = value;
                reference_size = reference_size + 1;
            } else {
                rejected = true;
            }
        } else if (operation == 1) {
            size = int_list_insert(array, size, CAPACITY, index, value);
            if (reference_size < CAPACITY &&
                index >= 0 && index <= reference_size) {
                for (position = reference_size;
                     position > index;
                     position = position - 1) {
                    reference[position] = reference[position - 1];
                }
                reference[index] = value;
                reference_size = reference_size + 1;
            } else {
                rejected = true;
            }
        } else if (operation == 2) {
            size = int_list_remove(array, size, CAPACITY, index);
            if (index >= 0 && index < reference_size) {
                for (position = index + 1;
                     position < reference_size;
                     position = position + 1) {
                    reference[position - 1] = reference[position];
                }
                reference_size = reference_size - 1;
            } else {
                rejected = true;
            }
        } else if (operation == 3) {
            if (int_list_valid_index(size, CAPACITY, index)) {
                array[index] = value;
            }
            if (index >= 0 && index < reference_size) {
                reference[index] = value;
            }
        } else {
            int expected_index = -1;

            for (position = 0;
                 position < reference_size;
                 position = position + 1) {
                if (reference[position] == value) {
                    expected_index = position;
                    break;
                }
            }
            REQUIRE(
                int_list_find(array, size, CAPACITY, value) == expected_index
            );
            REQUIRE(same_values(array, before, PHYSICAL_SLOTS));
        }

        REQUIRE(size == reference_size);
        REQUIRE(size >= 0 && size <= CAPACITY);
        REQUIRE(same_values(array, reference, size));
        REQUIRE(array[CAPACITY] == 12345);
        REQUIRE(array[CAPACITY + 1] == -12345);
        if (rejected) {
            REQUIRE(same_values(array, before, PHYSICAL_SLOTS));
        }
    }
    return true;
}

int main(void)
{
    run_test("zero usable capacity", test_zero_usable_capacity);
    run_test(
        "smaller capacity preserves guard slots",
        test_smaller_capacity_preserves_guard_slots
    );
    run_test(
        "integer extremes and invalid metadata",
        test_integer_extremes_and_invalid_metadata
    );
    run_test(
        "inactive tail is not part of the list",
        test_inactive_tail_is_not_part_of_the_list
    );
    run_test(
        "deterministic differential sequence",
        test_deterministic_differential_sequence
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
