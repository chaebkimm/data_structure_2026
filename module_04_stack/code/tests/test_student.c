#include "char_stack.h"
#include "delimiter_validator.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

/*
 * Replace each placeholder with a test you designed. A test is a small
 * experiment that compares an observed result with an expected result.
 * Use different inputs or combinations instead of copying a supplied case.
 * Destroy every initialized stack on every return path.
 */
static bool test_student_case_1(void)
{
    /*
     * TODO: Test a push/peek/pop sequence and explain how it demonstrates
     * last-in, first-out order.
     */
    return false;
}

static bool test_student_case_2(void)
{
    /*
     * TODO: Test one boundary or failure. Check both the returned status and
     * the promise that state or output is preserved.
     */
    return false;
}

static bool test_student_case_3(void)
{
    /*
     * TODO: Test a delimiter mismatch, unmatched close, unclosed open, or
     * depth limit. Verify the exact reported index.
     */
    return false;
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

int main(void)
{
    run_test("student-designed case 1", test_student_case_1);
    run_test("student-designed case 2", test_student_case_2);
    run_test("student-designed case 3", test_student_case_3);

    (void)printf(
        "\n%u student test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
