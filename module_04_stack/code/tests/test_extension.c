#include "char_stack.h"
#include "delimiter_validator.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef CHAR_STACK_TESTING
#error "Extension tests require -DCHAR_STACK_TESTING."
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

static bool test_every_small_limit_and_capacity_step(void)
{
    size_t limit;

    for (limit = 0U; limit <= 33U; ++limit) {
        CharStack stack;
        size_t expected_capacity = 0U;
        size_t index;

        REQUIRE(char_stack_init(&stack, limit) == STACK_OK);
        track_stack(&stack);

        for (index = 0U; index < limit; ++index) {
            if (index == expected_capacity) {
                expected_capacity = expected_capacity == 0U
                    ? 4U
                    : expected_capacity * 2U;
                if (expected_capacity > limit) {
                    expected_capacity = limit;
                }
            }

            REQUIRE(
                char_stack_push(
                    &stack,
                    (char)('A' + (char)(index % 26U))
                ) == STACK_OK
            );
            REQUIRE(stack.size == index + 1U);
            REQUIRE(stack.capacity == expected_capacity);
        }

        REQUIRE(char_stack_push(&stack, '!') == STACK_LIMIT);
        REQUIRE(stack.size == limit);
        REQUIRE(stack.capacity == expected_capacity);
        release_stack();
    }

    return true;
}

static bool test_deterministic_stack_model(void)
{
    CharStack stack;
    char model[31];
    size_t model_size = 0U;
    unsigned int state = 2463534242U;
    size_t step;

    REQUIRE(char_stack_init(&stack, 31U) == STACK_OK);
    track_stack(&stack);

    for (step = 0U; step < 1000U; ++step) {
        unsigned int choice;
        char output = '#';

        state = state * 1664525U + 1013904223U;
        choice = state % 3U;

        if (choice == 0U) {
            char value = (char)('a' + (char)(step % 26U));
            StackStatus expected = model_size == 31U
                ? STACK_LIMIT
                : STACK_OK;

            REQUIRE(char_stack_push(&stack, value) == expected);
            if (expected == STACK_OK) {
                model[model_size] = value;
                model_size += 1U;
            }
        } else if (choice == 1U) {
            StackStatus expected = model_size == 0U
                ? STACK_UNDERFLOW
                : STACK_OK;

            REQUIRE(char_stack_pop(&stack, &output) == expected);
            if (expected == STACK_OK) {
                model_size -= 1U;
                REQUIRE(output == model[model_size]);
            } else {
                REQUIRE(output == '#');
            }
        } else {
            StackStatus expected = model_size == 0U
                ? STACK_UNDERFLOW
                : STACK_OK;

            REQUIRE(char_stack_peek(&stack, &output) == expected);
            if (expected == STACK_OK) {
                REQUIRE(output == model[model_size - 1U]);
            } else {
                REQUIRE(output == '#');
            }
        }

        REQUIRE(char_stack_validate(&stack) == STACK_OK);
        REQUIRE(stack.size == model_size);
        if (model_size > 0U) {
            REQUIRE(memcmp(stack.data, model, model_size) == 0);
        }
    }

    release_stack();
    return true;
}

static bool test_maximum_delimiter_depth(void)
{
    char text[2U * CHAR_STACK_MAX_LIMIT + 1U];
    size_t index;
    size_t error_index = 42U;

    for (index = 0U;
         index < (size_t)CHAR_STACK_MAX_LIMIT;
         ++index) {
        text[index] = '(';
        text[(size_t)CHAR_STACK_MAX_LIMIT + index] = ')';
    }
    text[2U * (size_t)CHAR_STACK_MAX_LIMIT] = '\0';

    REQUIRE(
        delimiter_validate(
            text,
            (size_t)CHAR_STACK_MAX_LIMIT,
            &error_index
        ) == DELIMITER_OK
    );
    REQUIRE(error_index == SIZE_MAX);

    error_index = 42U;
    REQUIRE(
        delimiter_validate(
            text,
            (size_t)CHAR_STACK_MAX_LIMIT - 1U,
            &error_index
        ) == DELIMITER_DEPTH_LIMIT
    );
    REQUIRE(
        error_index ==
        (size_t)CHAR_STACK_MAX_LIMIT - 1U
    );
    return true;
}

static bool test_delimiter_case_table(void)
{
    struct DelimiterCase {
        const char *text;
        size_t limit;
        DelimiterStatus expected_status;
        size_t expected_index;
    };
    static const struct DelimiterCase cases[] = {
        { "[]{}()", 1U, DELIMITER_OK, SIZE_MAX },
        { "{[()]}", 3U, DELIMITER_OK, SIZE_MAX },
        { "x]y", 4U, DELIMITER_UNMATCHED_CLOSE, 1U },
        { "{)", 4U, DELIMITER_MISMATCH, 1U },
        { "[}", 4U, DELIMITER_MISMATCH, 1U },
        { "prefix{[", 4U, DELIMITER_UNCLOSED_OPEN, 8U },
        { "{{x}}", 1U, DELIMITER_DEPTH_LIMIT, 1U },
        { "no delimiters", 0U, DELIMITER_OK, SIZE_MAX }
    };
    size_t case_index;

    for (case_index = 0U;
         case_index < sizeof cases / sizeof cases[0];
         ++case_index) {
        size_t error_index = 700U;
        DelimiterStatus actual = delimiter_validate(
            cases[case_index].text,
            cases[case_index].limit,
            &error_index
        );

        REQUIRE(actual == cases[case_index].expected_status);
        REQUIRE(error_index == cases[case_index].expected_index);
    }

    return true;
}

static bool test_status_names_cover_public_values(void)
{
    StackStatus stack_status;
    DelimiterStatus delimiter_status;

    for (stack_status = STACK_OK;
         stack_status <= STACK_INVALID_STATE;
         stack_status = (StackStatus)((int)stack_status + 1)) {
        REQUIRE(stack_status_name(stack_status) != NULL);
        REQUIRE(strlen(stack_status_name(stack_status)) > 0U);
    }
    REQUIRE(
        strcmp(
            stack_status_name((StackStatus)999),
            "unknown StackStatus"
        ) == 0
    );

    for (delimiter_status = DELIMITER_OK;
         delimiter_status <= DELIMITER_ALLOCATION;
         delimiter_status =
            (DelimiterStatus)((int)delimiter_status + 1)) {
        REQUIRE(delimiter_status_name(delimiter_status) != NULL);
        REQUIRE(strlen(delimiter_status_name(delimiter_status)) > 0U);
    }
    REQUIRE(
        strcmp(
            delimiter_status_name((DelimiterStatus)999),
            "unknown DelimiterStatus"
        ) == 0
    );
    return true;
}

int main(void)
{
    run_test(
        "every small limit and capacity step",
        test_every_small_limit_and_capacity_step
    );
    run_test(
        "deterministic stack model",
        test_deterministic_stack_model
    );
    run_test(
        "maximum delimiter depth",
        test_maximum_delimiter_depth
    );
    run_test(
        "delimiter case table",
        test_delimiter_case_table
    );
    run_test(
        "status names cover public values",
        test_status_names_cover_public_values
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
