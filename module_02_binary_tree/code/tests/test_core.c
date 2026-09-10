#include "test_helpers.h"

static int test_node_allocation_and_empty_links(void)
{
    begin_expression("7");
    int first = new_node('7');
    REQUIRE(first == 0 && size == 1);
    REQUIRE(leaf_is(first, '7'));
    int second = new_node('+');
    REQUIRE(second == 1 && size == 2);
    REQUIRE(nodes[second].data == '+');
    REQUIRE(nodes[second].left == -1 && nodes[second].right == -1);
    REQUIRE(leaf_is(first, '7')); /* Reserving a parent preserves the leaf. */
    REQUIRE(pos == 0 && strcmp(eq, "7") == 0);
    return 1;
}

static int test_term_leaves_plus_unread(void)
{
    begin_expression("4+5");
    int root = term();
    REQUIRE(root == 0 && size == 1);
    REQUIRE(leaf_is(root, '4'));
    REQUIRE(pos == 1 && eq[pos] == '+');
    return 1;
}

static int test_multiplication_chain_keeps_previous_root(void)
{
    begin_expression("2*3*4+5");
    int root = term();
    REQUIRE(size == 5 && pos == 5 && eq[pos] == '+');
    REQUIRE(complete_tree(root));
    REQUIRE(nodes[root].data == '*');
    REQUIRE(leaf_is(nodes[root].right, '4'));
    int left = nodes[root].left;
    REQUIRE(nodes[left].data == '*');
    REQUIRE(leaf_is(nodes[left].left, '2'));
    REQUIRE(leaf_is(nodes[left].right, '3'));
    return 1;
}

static int test_textbook_precedence_and_complete_input(void)
{
    begin_expression("1+2*3");
    int root = terms();
    REQUIRE(size == 5 && pos == 5 && eq[pos] == '\0');
    REQUIRE(complete_tree(root));
    REQUIRE(nodes[root].data == '+');
    REQUIRE(leaf_is(nodes[root].left, '1'));
    int right = nodes[root].right;
    REQUIRE(nodes[right].data == '*');
    REQUIRE(leaf_is(nodes[right].left, '2'));
    REQUIRE(leaf_is(nodes[right].right, '3'));
    REQUIRE(eval_tree(root) == 7);
    return 1;
}

static int test_addition_chain_keeps_previous_root(void)
{
    begin_expression("1+2+3");
    int root = terms();
    REQUIRE(size == 5 && pos == 5 && eq[pos] == '\0');
    REQUIRE(complete_tree(root));
    REQUIRE(nodes[root].data == '+');
    REQUIRE(leaf_is(nodes[root].right, '3'));
    int left = nodes[root].left;
    REQUIRE(nodes[left].data == '+');
    REQUIRE(leaf_is(nodes[left].left, '1'));
    REQUIRE(leaf_is(nodes[left].right, '2'));
    REQUIRE(eval_tree(root) == 6);
    return 1;
}

static int test_digit_evaluation_including_zero(void)
{
    for (int digit = 0; digit <= 9; digit++) {
        char expression[2] = { (char)('0' + digit), '\0' };
        begin_expression(expression);
        /* Direct fixture isolates eval_tree from the allocator/parser. */
        nodes[0] = (struct TreeNode){ expression[0], -1, -1 };
        size = 1;
        REQUIRE(eval_tree(0) == digit);
        REQUIRE(leaf_is(0, expression[0]));
    }
    return 1;
}

static int test_recursive_evaluation_preserves_nodes(void)
{
    begin_expression("1+2*3");
    /* Root index 1 is deliberately different from the first allocated node. */
    nodes[0] = (struct TreeNode){ '1', -1, -1 };
    nodes[1] = (struct TreeNode){ '+', 0, 3 };
    nodes[2] = (struct TreeNode){ '2', -1, -1 };
    nodes[3] = (struct TreeNode){ '*', 2, 4 };
    nodes[4] = (struct TreeNode){ '3', -1, -1 };
    size = 5;
    pos = 5;
    struct TreeNode before[5];
    for (int i = 0; i < size; i++) before[i] = nodes[i];

    REQUIRE(eval_tree(3) == 6); /* A subtree can be evaluated independently. */
    REQUIRE(eval_tree(1) == 7);
    REQUIRE(eval_tree(1) == 7); /* Evaluation must not replace '+' with 7. */
    REQUIRE(size == 5 && pos == 5 && strcmp(eq, "1+2*3") == 0);
    for (int i = 0; i < size; i++) {
        REQUIRE(nodes[i].data == before[i].data);
        REQUIRE(nodes[i].left == before[i].left);
        REQUIRE(nodes[i].right == before[i].right);
    }
    return 1;
}

static int test_reset_and_reuse_for_another_expression(void)
{
    begin_expression("2*3+4*5");
    int root = terms();
    REQUIRE(size == 7 && pos == 7 && eq[pos] == '\0');
    REQUIRE(complete_tree(root));
    REQUIRE(eval_tree(root) == 26);

    /* The largest valid input leaves one slot for the string's '\0'. */
    begin_expression("0+1+2+3+4+5+6+7+8+9");
    root = terms();
    REQUIRE(size == 19 && pos == 19 && eq[pos] == '\0');
    REQUIRE(complete_tree(root));
    REQUIRE(eval_tree(root) == 45);

    /* Only the new used prefix belongs to the current expression tree. */
    begin_expression("0");
    root = terms();
    REQUIRE(size == 1 && pos == 1 && eq[pos] == '\0');
    REQUIRE(root == 0 && leaf_is(root, '0'));
    REQUIRE(eval_tree(root) == 0);
    return 1;
}

int main(void)
{
    run_test("node allocation and empty links", test_node_allocation_and_empty_links);
    run_test("term leaves plus unread", test_term_leaves_plus_unread);
    run_test("multiplication chain keeps previous root",
             test_multiplication_chain_keeps_previous_root);
    run_test("textbook precedence and complete input",
             test_textbook_precedence_and_complete_input);
    run_test("addition chain keeps previous root",
             test_addition_chain_keeps_previous_root);
    run_test("digit evaluation including zero", test_digit_evaluation_including_zero);
    run_test("recursive evaluation preserves nodes",
             test_recursive_evaluation_preserves_nodes);
    run_test("reset and reuse for another expression",
             test_reset_and_reuse_for_another_expression);
    return finish_tests("core");
}
