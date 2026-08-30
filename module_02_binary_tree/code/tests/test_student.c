#include "binary_tree.h"

#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

/*
 * Replace each placeholder with a test you designed. Keep every linked node
 * variable alive throughout the test. Normal recursive tests must use finite,
 * acyclic trees without shared children. Do not test an actual cycle by
 * passing it to tree_find or tree_clear.
 */
static int test_student_case_1(void)
{
    /* TODO: test a justified search boundary or duplicate-value preorder. */
    return 0;
}

static int test_student_case_2(void)
{
    /* TODO: test expression-node linking, an occupied side, or detachment. */
    return 0;
}

static int test_student_case_3(void)
{
    /* TODO: test cascading clearance and reuse of still-live node objects. */
    return 0;
}

static void run_test(const char *name, int (*test)(void))
{
    int passed;

    tests_run = tests_run + 1;
    passed = test();
    if (passed) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed = tests_failed + 1;
        (void)printf("FAIL %s\n", name);
    }
}

int main(void)
{
    run_test("student-designed case 1", test_student_case_1);
    run_test("student-designed case 2", test_student_case_2);
    run_test("student-designed case 3", test_student_case_3);

    (void)printf(
        "\n%d student test(s), %d failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0 ? 0 : 1;
}
