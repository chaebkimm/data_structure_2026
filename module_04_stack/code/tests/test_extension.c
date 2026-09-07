#include "expression_evaluator.h"
#include "int_stack.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
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

static bool arrays_equal(
    const int left[],
    const int right[],
    size_t length
)
{
    size_t index;

    for (index = 0U; index < length; ++index) {
        if (left[index] != right[index]) {
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

static bool test_every_capacity_through_ten(void)
{
    int capacity;

    for (capacity = 0; capacity <= 10; ++capacity) {
        int stack[10] = {
            -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1
        };
        int snapshot[10];
        int size = 0;
        int index;

        for (index = 0; index < capacity; ++index) {
            int next_size = int_stack_push(
                stack,
                size,
                capacity,
                100 + index
            );

            REQUIRE(next_size == size + 1);
            size = next_size;
            REQUIRE(stack[size - 1] == 99 + size);
        }

        for (index = 0; index < 10; ++index) {
            snapshot[index] = stack[index];
        }
        REQUIRE(int_stack_push(stack, size, capacity, 999) == size);
        REQUIRE(arrays_equal(stack, snapshot, 10U));

        while (size > 0) {
            int output = -1;
            int old_size = size;

            size = int_stack_pop(stack, size, capacity, &output);
            REQUIRE(size == old_size - 1);
            REQUIRE(output == 99 + old_size);
            REQUIRE(arrays_equal(stack, snapshot, 10U));
        }
    }
    return true;
}

static bool test_deterministic_stack_model(void)
{
    int stack[17] = { 0 };
    int model[17] = { 0 };
    int size = 0;
    unsigned int state = 2463534242U;
    unsigned int step;

    for (step = 0U; step < 1000U; ++step) {
        unsigned int choice;
        int output = -777;

        state = state * 1664525U + 1013904223U;
        choice = state % 3U;

        if (choice == 0U) {
            int value = (int)(step % 101U);
            int expected_size = size == 17 ? size : size + 1;
            int actual_size = int_stack_push(stack, size, 17, value);

            REQUIRE(actual_size == expected_size);
            if (size < 17) {
                model[size] = value;
            }
            size = actual_size;
        } else if (choice == 1U) {
            int expected_size = size == 0 ? 0 : size - 1;
            int actual_size = int_stack_pop(stack, size, 17, &output);

            REQUIRE(actual_size == expected_size);
            if (size == 0) {
                REQUIRE(output == -777);
            } else {
                REQUIRE(output == model[size - 1]);
            }
            size = actual_size;
        } else {
            int success = int_stack_peek(stack, size, 17, &output);

            REQUIRE(success == (size > 0 ? 1 : 0));
            if (size == 0) {
                REQUIRE(output == -777);
            } else {
                REQUIRE(output == model[size - 1]);
            }
        }

        REQUIRE(arrays_equal(stack, model, 17U));
    }
    return true;
}

static bool test_valid_expression_case_table_and_long_input(void)
{
    struct ExpressionCase {
        const char *expression;
        int expected;
    };
    static const struct ExpressionCase cases[] = {
        { "0", 0 },
        { "9", 9 },
        { "0*9+8", 8 },
        { "1+2*3+4*5", 27 },
        { "9*9*9", 729 },
        { "1+2+3+4", 10 }
    };
    char long_expression[202];
    size_t case_index;
    size_t operand_index;
    size_t write_index = 0U;
    int result = -1;

    for (case_index = 0U;
         case_index < sizeof cases / sizeof cases[0];
         ++case_index) {
        REQUIRE(
            expression_evaluate(cases[case_index].expression, &result) == 1
        );
        REQUIRE(result == cases[case_index].expected);
    }

    for (operand_index = 0U; operand_index < 101U; ++operand_index) {
        if (operand_index > 0U) {
            long_expression[write_index] = '+';
            write_index += 1U;
        }
        long_expression[write_index] = '0';
        write_index += 1U;
    }
    long_expression[write_index] = '\0';

    REQUIRE(expression_evaluate(long_expression, &result) == 1);
    REQUIRE(result == 0);
    return true;
}

static bool test_invalid_expression_case_table(void)
{
    static const char *const invalid_expressions[] = {
        " ",
        "1\t+2",
        "1/2",
        "1*",
        "*1",
        "1**2",
        "01",
        "a",
        "1+(2)",
        "-1"
    };
    size_t index;
    int result = 808;

    for (index = 0U;
         index < sizeof invalid_expressions / sizeof invalid_expressions[0];
         ++index) {
        REQUIRE(
            expression_evaluate(invalid_expressions[index], &result) == 0
        );
        REQUIRE(result == 808);
    }
    return true;
}

static bool test_checked_integer_overflow(void)
{
    char expression[2U * sizeof(int) * CHAR_BIT + 4U];
    size_t length = 0U;
    int expected = 1;
    int result = -1;

    expression[length] = '1';
    length += 1U;
    while (expected <= INT_MAX / 2) {
        expression[length] = '*';
        expression[length + 1U] = '2';
        length += 2U;
        expected *= 2;
    }
    expression[length] = '\0';

    REQUIRE(expression_evaluate(expression, &result) == 1);
    REQUIRE(result == expected);

    expression[length] = '*';
    expression[length + 1U] = '2';
    expression[length + 2U] = '\0';
    result = 909;
    REQUIRE(expression_evaluate(expression, &result) == 0);
    REQUIRE(result == 909);
    return true;
}

int main(void)
{
    run_test(
        "every capacity through ten",
        test_every_capacity_through_ten
    );
    run_test(
        "deterministic stack model",
        test_deterministic_stack_model
    );
    run_test(
        "valid expression table and long input",
        test_valid_expression_case_table_and_long_input
    );
    run_test(
        "invalid expression table",
        test_invalid_expression_case_table
    );
    run_test(
        "checked integer overflow",
        test_checked_integer_overflow
    );

    (void)printf(
        "\n%u extension test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
