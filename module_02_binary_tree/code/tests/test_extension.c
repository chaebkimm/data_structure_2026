#include "test_helpers.h"

static int check_expression(const char *expression, int answer)
{
    begin_expression(expression);
    int root = terms();
    int length = (int)strlen(expression);
    REQUIRE(size == length && pos == length && eq[pos] == '\0');
    REQUIRE(complete_tree(root));
    REQUIRE(eval_tree(root) == answer);
    return 1;
}

static int test_nineteen_character_sum(void)
{
    REQUIRE(check_expression("0+1+2+3+4+5+6+7+8+9", 45));
    return 1;
}

static int test_nineteen_character_product(void)
{
    /* 1024 fits even the smallest int range guaranteed by C. */
    REQUIRE(check_expression("2*2*2*2*2*2*2*2*2*2", 1024));
    return 1;
}

static int test_mixed_precedence_and_zero_terms(void)
{
    REQUIRE(check_expression("1+2*3+4*5", 27));
    REQUIRE(check_expression("2*3+4*5+6", 32));
    REQUIRE(check_expression("9*0+8*1+2", 10));
    REQUIRE(check_expression("0+0*9+0", 0));
    REQUIRE(check_expression("1*2*3+4*5*6+7", 133));
    return 1;
}

static int test_term_continues_from_shared_cursor(void)
{
    begin_expression("1+2*3+4");
    int first = term();
    REQUIRE(leaf_is(first, '1') && pos == 1);
    pos++; /* The caller consumes '+', then asks for just the next term. */
    int second = term();
    REQUIRE(valid_index(second) && size == 4 && pos == 5 && eq[pos] == '+');
    REQUIRE(nodes[second].data == '*');
    REQUIRE(leaf_is(nodes[second].left, '2'));
    REQUIRE(leaf_is(nodes[second].right, '3'));
    REQUIRE(leaf_is(first, '1'));
    REQUIRE(eval_tree(second) == 6);
    return 1;
}

static int test_repeated_builds_reinitialize_used_slots(void)
{
    for (int iteration = 0; iteration < 4; iteration++) {
        REQUIRE(check_expression("1+2*3+4*5+6*7+8*9+0", 141));
        REQUIRE(check_expression("8", 8));
        REQUIRE(leaf_is(0, '8'));
        REQUIRE(check_expression("0*9+1", 1));
    }
    return 1;
}

int main(void)
{
    run_test("nineteen-character sum", test_nineteen_character_sum);
    run_test("nineteen-character product", test_nineteen_character_product);
    run_test("mixed precedence and zero terms", test_mixed_precedence_and_zero_terms);
    run_test("term continues from shared cursor", test_term_continues_from_shared_cursor);
    run_test("repeated builds reinitialize used slots",
             test_repeated_builds_reinitialize_used_slots);
    return finish_tests("extension");
}
