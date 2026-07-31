#include "char_stack.h"
#include "delimiter_validator.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef CHAR_STACK_TESTING
#error "Core tests require -DCHAR_STACK_TESTING."
#endif

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;
static CharStack *active_stack = NULL;

static void track_stack(CharStack *stack)
{
    active_stack = stack;
}

static void release_stack(void)
{
    if (active_stack != NULL) {
        char_stack_destroy(active_stack);
        active_stack = NULL;
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
            release_stack();                                                 \
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

static bool test_initialization_limits_and_destroy(void)
{
    CharStack stack;
    CharStack unchanged;
    CharStack before;
    char marker = 'x';

    unchanged.data = &marker;
    unchanged.size = 1U;
    unchanged.capacity = 1U;
    unchanged.limit = 1U;
    before = unchanged;

    REQUIRE(
        char_stack_init(NULL, 3U) == STACK_INVALID_ARGUMENT
    );
    REQUIRE(
        char_stack_init(
            &unchanged,
            (size_t)CHAR_STACK_MAX_LIMIT + 1U
        ) == STACK_LIMIT
    );
    REQUIRE(unchanged.data == before.data);
    REQUIRE(unchanged.size == before.size);
    REQUIRE(unchanged.capacity == before.capacity);
    REQUIRE(unchanged.limit == before.limit);

    REQUIRE(char_stack_init(&stack, 7U) == STACK_OK);
    track_stack(&stack);
    REQUIRE(char_stack_validate(&stack) == STACK_OK);
    REQUIRE(stack.data == NULL);
    REQUIRE(stack.size == 0U);
    REQUIRE(stack.capacity == 0U);
    REQUIRE(stack.limit == 7U);

    REQUIRE(char_stack_push(&stack, 'q') == STACK_OK);
    release_stack();
    REQUIRE(stack.data == NULL);
    REQUIRE(stack.size == 0U);
    REQUIRE(stack.capacity == 0U);
    REQUIRE(stack.limit == 0U);
    REQUIRE(char_stack_validate(&stack) == STACK_OK);

    char_stack_destroy(&stack);
    char_stack_destroy(NULL);
    REQUIRE(char_stack_validate(&stack) == STACK_OK);
    return true;
}

static bool test_zero_limit_and_empty_outputs(void)
{
    CharStack stack;
    char output = 'z';

    REQUIRE(char_stack_init(&stack, 0U) == STACK_OK);
    track_stack(&stack);
    REQUIRE(char_stack_push(&stack, 'a') == STACK_LIMIT);
    REQUIRE(stack.data == NULL);
    REQUIRE(stack.size == 0U);
    REQUIRE(stack.capacity == 0U);

    REQUIRE(char_stack_peek(&stack, &output) == STACK_UNDERFLOW);
    REQUIRE(output == 'z');
    REQUIRE(char_stack_pop(&stack, &output) == STACK_UNDERFLOW);
    REQUIRE(output == 'z');
    REQUIRE(
        char_stack_peek(&stack, NULL) == STACK_INVALID_ARGUMENT
    );
    REQUIRE(
        char_stack_pop(&stack, NULL) == STACK_INVALID_ARGUMENT
    );
    REQUIRE(
        char_stack_peek(NULL, &output) == STACK_INVALID_ARGUMENT
    );
    REQUIRE(
        char_stack_pop(NULL, &output) == STACK_INVALID_ARGUMENT
    );
    REQUIRE(output == 'z');

    release_stack();
    return true;
}

static bool test_lifo_push_peek_and_pop(void)
{
    CharStack stack;
    char output = '?';

    REQUIRE(char_stack_init(&stack, 6U) == STACK_OK);
    track_stack(&stack);
    REQUIRE(char_stack_push(&stack, 'A') == STACK_OK);
    REQUIRE(char_stack_push(&stack, 'B') == STACK_OK);
    REQUIRE(char_stack_push(&stack, 'C') == STACK_OK);
    REQUIRE(stack.size == 3U);
    REQUIRE(stack.data[stack.size - 1U] == 'C');

    REQUIRE(char_stack_peek(&stack, &output) == STACK_OK);
    REQUIRE(output == 'C');
    REQUIRE(stack.size == 3U);

    REQUIRE(char_stack_pop(&stack, &output) == STACK_OK);
    REQUIRE(output == 'C');
    REQUIRE(char_stack_pop(&stack, &output) == STACK_OK);
    REQUIRE(output == 'B');
    REQUIRE(char_stack_pop(&stack, &output) == STACK_OK);
    REQUIRE(output == 'A');
    REQUIRE(stack.size == 0U);

    output = '!';
    REQUIRE(char_stack_pop(&stack, &output) == STACK_UNDERFLOW);
    REQUIRE(output == '!');
    release_stack();
    return true;
}

static bool test_geometric_growth_and_clipping(void)
{
    CharStack stack;
    char *pointer_at_limit;
    size_t index;
    size_t capacity_at_limit;

    REQUIRE(char_stack_init(&stack, 10U) == STACK_OK);
    track_stack(&stack);

    for (index = 0U; index < 10U; ++index) {
        REQUIRE(
            char_stack_push(
                &stack,
                (char)('a' + (char)index)
            ) == STACK_OK
        );

        if (index == 0U) {
            REQUIRE(stack.capacity == 4U);
        } else if (index == 4U) {
            REQUIRE(stack.capacity == 8U);
        } else if (index == 8U) {
            REQUIRE(stack.capacity == 10U);
        }
    }

    REQUIRE(stack.size == 10U);
    REQUIRE(stack.capacity == stack.limit);
    pointer_at_limit = stack.data;
    capacity_at_limit = stack.capacity;
    REQUIRE(char_stack_push(&stack, 'x') == STACK_LIMIT);
    REQUIRE(stack.data == pointer_at_limit);
    REQUIRE(stack.size == 10U);
    REQUIRE(stack.capacity == capacity_at_limit);

    for (index = 10U; index > 0U; --index) {
        char output = '\0';

        REQUIRE(char_stack_pop(&stack, &output) == STACK_OK);
        REQUIRE(output == (char)('a' + (char)(index - 1U)));
        REQUIRE(stack.data == pointer_at_limit);
        REQUIRE(stack.capacity == capacity_at_limit);
    }

    release_stack();
    return true;
}

static bool test_small_limits_clip_first_growth(void)
{
    CharStack stack;
    char output = '\0';

    REQUIRE(char_stack_init(&stack, 1U) == STACK_OK);
    track_stack(&stack);
    REQUIRE(char_stack_push(&stack, '1') == STACK_OK);
    REQUIRE(stack.capacity == 1U);
    REQUIRE(char_stack_push(&stack, '2') == STACK_LIMIT);
    REQUIRE(char_stack_pop(&stack, &output) == STACK_OK);
    REQUIRE(output == '1');
    release_stack();

    REQUIRE(char_stack_init(&stack, 3U) == STACK_OK);
    track_stack(&stack);
    REQUIRE(char_stack_push(&stack, 'a') == STACK_OK);
    REQUIRE(stack.capacity == 3U);
    REQUIRE(char_stack_push(&stack, 'b') == STACK_OK);
    REQUIRE(char_stack_push(&stack, 'c') == STACK_OK);
    REQUIRE(char_stack_push(&stack, 'd') == STACK_LIMIT);
    release_stack();
    return true;
}

static bool test_allocation_failure_preserves_stack(void)
{
    CharStack stack;
    char *old_data;
    size_t index;

    REQUIRE(char_stack_init(&stack, 8U) == STACK_OK);
    track_stack(&stack);
    char_stack_test_fail_next_allocation();
    REQUIRE(char_stack_push(&stack, 'a') == STACK_ALLOCATION);
    REQUIRE(stack.data == NULL);
    REQUIRE(stack.size == 0U);
    REQUIRE(stack.capacity == 0U);
    REQUIRE(stack.limit == 8U);

    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            char_stack_push(&stack, (char)('a' + (char)index)) ==
            STACK_OK
        );
    }
    old_data = stack.data;
    char_stack_test_fail_next_allocation();
    REQUIRE(char_stack_push(&stack, 'e') == STACK_ALLOCATION);
    REQUIRE(stack.data == old_data);
    REQUIRE(stack.size == 4U);
    REQUIRE(stack.capacity == 4U);
    REQUIRE(stack.limit == 8U);
    REQUIRE(memcmp(stack.data, "abcd", 4U) == 0);

    release_stack();
    return true;
}

static bool test_invalid_states_preserve_outputs(void)
{
    CharStack invalid_size = { NULL, 1U, 1U, 1U };
    CharStack missing_data = { NULL, 0U, 1U, 1U };
    CharStack too_much_capacity = { NULL, 0U, 2U, 1U };
    CharStack too_large_limit = {
        NULL,
        0U,
        0U,
        (size_t)CHAR_STACK_MAX_LIMIT + 1U
    };
    CharStack stray_pointer;
    char marker = 'm';
    char output = 'k';

    stray_pointer.data = &marker;
    stray_pointer.size = 0U;
    stray_pointer.capacity = 0U;
    stray_pointer.limit = 0U;

    REQUIRE(
        char_stack_validate(&invalid_size) == STACK_INVALID_STATE
    );
    REQUIRE(
        char_stack_validate(&missing_data) == STACK_INVALID_STATE
    );
    REQUIRE(
        char_stack_validate(&too_much_capacity) ==
        STACK_INVALID_STATE
    );
    REQUIRE(
        char_stack_validate(&too_large_limit) ==
        STACK_INVALID_STATE
    );
    REQUIRE(
        char_stack_validate(&stray_pointer) == STACK_INVALID_STATE
    );

    REQUIRE(
        char_stack_push(&invalid_size, 'x') ==
        STACK_INVALID_STATE
    );
    REQUIRE(
        char_stack_peek(&missing_data, &output) ==
        STACK_INVALID_STATE
    );
    REQUIRE(output == 'k');
    REQUIRE(
        char_stack_pop(&too_much_capacity, &output) ==
        STACK_INVALID_STATE
    );
    REQUIRE(output == 'k');
    return true;
}

static bool test_valid_delimiter_texts_and_ignored_characters(void)
{
    size_t error_index = 10U;

    REQUIRE(
        delimiter_validate("", 0U, &error_index) == DELIMITER_OK
    );
    REQUIRE(error_index == SIZE_MAX);

    error_index = 10U;
    REQUIRE(
        delimiter_validate(
            "if (items[2] == code) { return values[i]; }",
            8U,
            &error_index
        ) == DELIMITER_OK
    );
    REQUIRE(error_index == SIZE_MAX);

    error_index = 10U;
    REQUIRE(
        delimiter_validate(
            "<tag> words + 7",
            0U,
            &error_index
        ) == DELIMITER_OK
    );
    REQUIRE(error_index == SIZE_MAX);
    return true;
}

static bool test_delimiter_error_categories_and_indexes(void)
{
    size_t error_index = 99U;

    REQUIRE(
        delimiter_validate("abc)", 5U, &error_index) ==
        DELIMITER_UNMATCHED_CLOSE
    );
    REQUIRE(error_index == 3U);

    error_index = 99U;
    REQUIRE(
        delimiter_validate("a{b(c]d}", 5U, &error_index) ==
        DELIMITER_MISMATCH
    );
    REQUIRE(error_index == 5U);

    error_index = 99U;
    REQUIRE(
        delimiter_validate("open([", 5U, &error_index) ==
        DELIMITER_UNCLOSED_OPEN
    );
    REQUIRE(error_index == 6U);
    return true;
}

static bool test_delimiter_depth_limit(void)
{
    size_t error_index = 77U;

    REQUIRE(
        delimiter_validate("text()", 0U, &error_index) ==
        DELIMITER_DEPTH_LIMIT
    );
    REQUIRE(error_index == 4U);

    error_index = 77U;
    REQUIRE(
        delimiter_validate("a((b))", 1U, &error_index) ==
        DELIMITER_DEPTH_LIMIT
    );
    REQUIRE(error_index == 2U);

    error_index = 77U;
    REQUIRE(
        delimiter_validate("(x)", 1U, &error_index) ==
        DELIMITER_OK
    );
    REQUIRE(error_index == SIZE_MAX);
    return true;
}

static bool test_delimiter_nonreporting_failures_preserve_output(void)
{
    size_t error_index = 321U;

    REQUIRE(
        delimiter_validate(NULL, 4U, &error_index) ==
        DELIMITER_INVALID_ARGUMENT
    );
    REQUIRE(error_index == 321U);
    REQUIRE(
        delimiter_validate(
            "()",
            (size_t)CHAR_STACK_MAX_LIMIT + 1U,
            &error_index
        ) == DELIMITER_INVALID_ARGUMENT
    );
    REQUIRE(error_index == 321U);
    REQUIRE(
        delimiter_validate("()", 4U, NULL) ==
        DELIMITER_INVALID_ARGUMENT
    );
    REQUIRE(error_index == 321U);

    char_stack_test_fail_next_allocation();
    REQUIRE(
        delimiter_validate("(", 1U, &error_index) ==
        DELIMITER_ALLOCATION
    );
    REQUIRE(error_index == 321U);
    return true;
}

int main(void)
{
    run_test(
        "initialization, limits, and destroy",
        test_initialization_limits_and_destroy
    );
    run_test(
        "zero limit and empty outputs",
        test_zero_limit_and_empty_outputs
    );
    run_test(
        "LIFO push, peek, and pop",
        test_lifo_push_peek_and_pop
    );
    run_test(
        "geometric growth and clipping",
        test_geometric_growth_and_clipping
    );
    run_test(
        "small limits clip first growth",
        test_small_limits_clip_first_growth
    );
    run_test(
        "allocation failure preserves stack",
        test_allocation_failure_preserves_stack
    );
    run_test(
        "invalid states preserve outputs",
        test_invalid_states_preserve_outputs
    );
    run_test(
        "valid delimiter texts and ignored characters",
        test_valid_delimiter_texts_and_ignored_characters
    );
    run_test(
        "delimiter error categories and indexes",
        test_delimiter_error_categories_and_indexes
    );
    run_test(
        "delimiter depth limit",
        test_delimiter_depth_limit
    );
    run_test(
        "delimiter nonreporting failures preserve output",
        test_delimiter_nonreporting_failures_preserve_output
    );

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
