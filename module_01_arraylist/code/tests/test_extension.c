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

static bool require_values(
    const IntList *list,
    const int *expected,
    size_t expected_size
)
{
    size_t i;

    REQUIRE(int_list_is_valid(list));
    REQUIRE(list->size == expected_size);
    for (i = 0U; i < expected_size; ++i) {
        int actual = 0;

        REQUIRE(int_list_get(list, i, &actual) == INT_LIST_OK);
        REQUIRE(actual == expected[i]);
    }

    return true;
}

static bool test_insert_positions(void)
{
    IntList list;
    const int expected[] = { 5, 10, 15, 20, 25 };

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_insert(&list, 0U, 15) == INT_LIST_OK);
    REQUIRE(int_list_insert(&list, 0U, 10) == INT_LIST_OK);
    REQUIRE(int_list_insert(&list, 0U, 5) == INT_LIST_OK);
    REQUIRE(int_list_insert(&list, 3U, 25) == INT_LIST_OK);
    REQUIRE(int_list_insert(&list, 3U, 20) == INT_LIST_OK);
    REQUIRE(
        require_values(
            &list,
            expected,
            sizeof expected / sizeof expected[0]
        )
    );

    release_active_list();
    return true;
}

static bool test_remove_positions_and_discard(void)
{
    IntList list;
    const int before[] = { 10, 20, 30, 40, 50 };
    const int after[] = { 20, 40 };
    size_t i;
    int removed = 0;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    for (i = 0U; i < sizeof before / sizeof before[0]; ++i) {
        REQUIRE(int_list_append(&list, before[i]) == INT_LIST_OK);
    }

    REQUIRE(int_list_remove(&list, 0U, &removed) == INT_LIST_OK);
    REQUIRE(removed == 10);
    REQUIRE(int_list_remove(&list, 1U, &removed) == INT_LIST_OK);
    REQUIRE(removed == 30);
    REQUIRE(
        int_list_remove(&list, list.size - 1U, NULL) ==
        INT_LIST_OK
    );
    REQUIRE(
        require_values(
            &list,
            after,
            sizeof after / sizeof after[0]
        )
    );

    release_active_list();
    return true;
}

static bool test_invalid_operations_preserve_state(void)
{
    IntList list;
    int *old_data;
    size_t old_size;
    size_t old_capacity;
    int output = 123;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);
    REQUIRE(int_list_append(&list, 7) == INT_LIST_OK);
    REQUIRE(int_list_append(&list, 8) == INT_LIST_OK);

    old_data = list.data;
    old_size = list.size;
    old_capacity = list.capacity;

    REQUIRE(
        int_list_insert(&list, list.size + 1U, 9) ==
        INT_LIST_ERR_OUT_OF_RANGE
    );
    REQUIRE(list.data == old_data);
    REQUIRE(list.size == old_size);
    REQUIRE(list.capacity == old_capacity);

    REQUIRE(
        int_list_remove(&list, list.size, &output) ==
        INT_LIST_ERR_OUT_OF_RANGE
    );
    REQUIRE(output == 123);
    REQUIRE(list.data == old_data);
    REQUIRE(list.size == old_size);
    REQUIRE(list.capacity == old_capacity);

    release_active_list();
    return true;
}

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static bool test_deterministic_differential_sequence(void)
{
    enum {
        REFERENCE_CAPACITY = 256,
        STEPS = 1000
    };

    IntList list;
    int reference[REFERENCE_CAPACITY];
    size_t reference_size = 0U;
    uint32_t state = UINT32_C(0xC0FFEE);
    int step;

    REQUIRE(int_list_init(&list) == INT_LIST_OK);
    track_active_list(&list);

    for (step = 0; step < STEPS; ++step) {
        uint32_t random_value = next_random(&state);
        unsigned int operation = (unsigned int)(random_value % 3U);

        if (reference_size == 0U) {
            operation = 0U;
        } else if (reference_size >= (size_t)REFERENCE_CAPACITY) {
            operation = 2U;
        }

        if (operation == 0U) {
            int value = (int)(random_value & UINT32_C(0x7FFF));

            REQUIRE(int_list_append(&list, value) == INT_LIST_OK);
            reference[reference_size] = value;
            reference_size += 1U;
        } else if (operation == 1U) {
            size_t index =
                (size_t)(random_value % (uint32_t)(reference_size + 1U));
            int value = (int)(next_random(&state) & UINT32_C(0x7FFF));
            size_t i;

            REQUIRE(
                int_list_insert(&list, index, value) ==
                INT_LIST_OK
            );

            for (i = reference_size; i > index; --i) {
                reference[i] = reference[i - 1U];
            }
            reference[index] = value;
            reference_size += 1U;
        } else {
            size_t index =
                (size_t)(random_value % (uint32_t)reference_size);
            int removed = 0;
            size_t i;

            REQUIRE(
                int_list_remove(&list, index, &removed) ==
                INT_LIST_OK
            );
            REQUIRE(removed == reference[index]);

            for (i = index; i + 1U < reference_size; ++i) {
                reference[i] = reference[i + 1U];
            }
            reference_size -= 1U;
        }

        REQUIRE(require_values(&list, reference, reference_size));
    }

    release_active_list();
    return true;
}

int main(void)
{
    run_test("insert positions", test_insert_positions);
    run_test(
        "remove positions and discard",
        test_remove_positions_and_discard
    );
    run_test(
        "invalid operations preserve state",
        test_invalid_operations_preserve_state
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
