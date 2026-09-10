#include "test_helpers.h"

/*
 * Replace all three placeholders with tests you designed. Start every
 * independent build with begin_expression("your valid expression"), which
 * resets size and pos and copies the text into eq. Keep expressions within
 * the header's input contract; invalid-input handling is not required.
 * After terms(), use REQUIRE(complete_tree(root)) before following links or
 * evaluating a returned root. Use REQUIRE for your predicted shape/result.
 */
static int test_student_case_1(void)
{
    /* TODO: Creation. Check new_node's returned indices, stored characters,
     * child initialization, and size updates. Explain why index 0 is valid
     * while -1 means no child. */
    return 0;
}

static int test_student_case_2(void)
{
    /* TODO: Construction. Choose an expression that checks multiplication
     * precedence or left grouping within an operator level. Draw its tree,
     * then check the root, child roles, and consumed input. */
    return 0;
}

static int test_student_case_3(void)
{
    /* TODO: Evaluation. Predict a subtree's integer answer and evaluate it
     * repeatedly. Check that node data/links and all globals (size, pos,
     * and eq) remain unchanged. */
    return 0;
}

int main(void)
{
    run_test("student-designed case 1", test_student_case_1);
    run_test("student-designed case 2", test_student_case_2);
    run_test("student-designed case 3", test_student_case_3);
    return finish_tests("student");
}
