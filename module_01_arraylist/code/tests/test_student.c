#include "int_list.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

/*
 * Replace each placeholder body with a test you designed. If a test
 * initializes a list, destroy it on every return path.
 */
static bool test_student_case_1(void)
{
    /* TODO: add a nonduplicate boundary or malformed-input test. */
    return false;
}

static bool test_student_case_2(void)
{
    /* TODO: add a state-preservation or sequence-property test. */
    return false;
}

static bool test_student_case_3(void)
{
    /* TODO: test another justified API-contract risk. */
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
    run_test(
        "student-designed case 1",
        test_student_case_1
    );
    run_test(
        "student-designed case 2",
        test_student_case_2
    );
    run_test(
        "student-designed case 3",
        test_student_case_3
    );

    (void)printf(
        "\n%u student test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
