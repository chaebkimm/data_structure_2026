#include "expression_evaluator.h"
#include "int_stack.h"

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

static bool test_push_adds_at_top(void)
{
    int stack[4] = { 71, 72, 73, 74 };
    int size = 0;

    size = int_stack_push(stack, size, 4, 10);
    REQUIRE(size == 1);
    REQUIRE(stack[0] == 10);
    REQUIRE(stack[1] == 72);

    size = int_stack_push(stack, size, 4, 20);
    REQUIRE(size == 2);
    REQUIRE(stack[0] == 10);
    REQUIRE(stack[1] == 20);
    REQUIRE(stack[2] == 73);
    return true;
}

static bool test_peek_reads_without_mutation(void)
{
    int stack[3] = { 4, 7, 91 };
    const int before[3] = { 4, 7, 91 };
    int output = -1;

    REQUIRE(int_stack_peek(stack, 2, 3, &output) == 1);
    REQUIRE(output == 7);
    REQUIRE(arrays_equal(stack, before, 3U));
    return true;
}

static bool test_pop_reports_lifo_without_erasing(void)
{
    int stack[3] = { 4, 7, 91 };
    const int before[3] = { 4, 7, 91 };
    int output = -1;
    int size = 2;

    size = int_stack_pop(stack, size, 3, &output);
    REQUIRE(size == 1);
    REQUIRE(output == 7);
    REQUIRE(arrays_equal(stack, before, 3U));

    size = int_stack_pop(stack, size, 3, &output);
    REQUIRE(size == 0);
    REQUIRE(output == 4);
    REQUIRE(arrays_equal(stack, before, 3U));
    return true;
}

static bool test_full_push_preserves_array(void)
{
    int stack[2] = { 11, 22 };
    const int before[2] = { 11, 22 };

    REQUIRE(int_stack_push(stack, 2, 2, 33) == 2);
    REQUIRE(arrays_equal(stack, before, 2U));
    return true;
}

static bool test_empty_and_zero_capacity_fail_safely(void)
{
    int stack[1] = { 37 };
    const int before[1] = { 37 };
    int output = 81;

    REQUIRE(int_stack_peek(stack, 0, 1, &output) == 0);
    REQUIRE(output == 81);
    REQUIRE(int_stack_pop(stack, 0, 1, &output) == 0);
    REQUIRE(output == 81);
    REQUIRE(arrays_equal(stack, before, 1U));

    REQUIRE(int_stack_push(NULL, 0, 0, 5) == 0);
    REQUIRE(int_stack_peek(NULL, 0, 0, &output) == 0);
    REQUIRE(int_stack_pop(NULL, 0, 0, &output) == 0);
    REQUIRE(output == 81);
    return true;
}

static bool test_invalid_arguments_preserve_state(void)
{
    int stack[3] = { 8, 9, 10 };
    const int before[3] = { 8, 9, 10 };
    int output = 123;

    REQUIRE(int_stack_push(stack, -1, 3, 55) == -1);
    REQUIRE(int_stack_push(stack, 0, -1, 55) == 0);
    REQUIRE(int_stack_push(stack, 4, 3, 55) == 4);
    REQUIRE(int_stack_push(NULL, 0, 3, 55) == 0);

    REQUIRE(int_stack_peek(stack, -1, 3, &output) == 0);
    REQUIRE(int_stack_peek(stack, 4, 3, &output) == 0);
    REQUIRE(int_stack_peek(NULL, 1, 3, &output) == 0);
    REQUIRE(int_stack_peek(stack, 1, 3, NULL) == 0);

    REQUIRE(int_stack_pop(stack, -1, 3, &output) == -1);
    REQUIRE(int_stack_pop(stack, 4, 3, &output) == 4);
    REQUIRE(int_stack_pop(NULL, 1, 3, &output) == 1);
    REQUIRE(int_stack_pop(stack, 1, 3, NULL) == 1);

    REQUIRE(output == 123);
    REQUIRE(arrays_equal(stack, before, 3U));
    return true;
}

static bool test_expression_precedence_and_associativity(void)
{
    int result = -1;

    REQUIRE(expression_evaluate("1+2*3", &result) == 1);
    REQUIRE(result == 7);
    REQUIRE(expression_evaluate("2*3+4", &result) == 1);
    REQUIRE(result == 10);
    REQUIRE(expression_evaluate("2+3*4+5", &result) == 1);
    REQUIRE(result == 19);
    REQUIRE(expression_evaluate("7", &result) == 1);
    REQUIRE(result == 7);
    return true;
}

static bool test_invalid_expressions_preserve_result(void)
{
    static const char *const invalid_expressions[] = {
        "",
        "+1",
        "1+",
        "12",
        "1 2",
        "1-2",
        "1++2",
        "(1+2)"
    };
    size_t index;
    int result = 404;

    REQUIRE(expression_evaluate(NULL, &result) == 0);
    REQUIRE(result == 404);
    REQUIRE(expression_evaluate("1", NULL) == 0);
    REQUIRE(result == 404);

    for (index = 0U;
         index < sizeof invalid_expressions / sizeof invalid_expressions[0];
         ++index) {
        REQUIRE(
            expression_evaluate(invalid_expressions[index], &result) == 0
        );
        REQUIRE(result == 404);
    }
    return true;
}

int main(void)
{
    run_test("push adds at the top", test_push_adds_at_top);
    run_test("peek reads without mutation", test_peek_reads_without_mutation);
    run_test(
        "pop reports LIFO without erasing",
        test_pop_reports_lifo_without_erasing
    );
    run_test("full push preserves array", test_full_push_preserves_array);
    run_test(
        "empty and zero capacity fail safely",
        test_empty_and_zero_capacity_fail_safely
    );
    run_test(
        "invalid arguments preserve state",
        test_invalid_arguments_preserve_state
    );
    run_test(
        "expression precedence and associativity",
        test_expression_precedence_and_associativity
    );
    run_test(
        "invalid expressions preserve result",
        test_invalid_expressions_preserve_result
    );

    (void)printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
