#include "graph_matrix.h"

#include <stdio.h>

static int tests_run = 0;
static int tests_failed = 0;

/*
 * Replace each placeholder with a test you designed. Use only active
 * indexes when an operation is meant to succeed, and inspect the integer
 * grid directly when that best demonstrates direction or preservation.
 */
static int test_student_case_1(void)
{
    /*
     * TODO: State a one-sentence rationale. Test that graph_init clears the
     * active square and at least one physically stored inactive cell.
     */
    return 0;
}

static int test_student_case_2(void)
{
    /*
     * TODO: State a one-sentence rationale. In one coherent valid sequence,
     * test direction, idempotent add/remove, a guarded direct lookup, and an
     * out-degree change.
     */
    return 0;
}

static int test_student_case_3(void)
{
    /*
     * TODO: State a one-sentence rationale. Reject a self-loop or inactive
     * endpoint and prove the complete graph is unchanged, or reject an
     * out-degree request and prove its output is unchanged.
     */
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
