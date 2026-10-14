/*
 * Execute the current classroom source under its valid-input assumptions.
 * Compile this driver alone with the repository root on the include path.
 * Stack traversal needs zeroed progress and room for a missing-child sentinel.
 * Postfix input is nonempty, valid, and fits postfix[8].
 */
#include <stdio.h>
#include <string.h>

#include "../../student/lab.c"

#define CHECK(condition) do { \
    if (!(condition)) { \
        printf("  line %d: %s\n", __LINE__, #condition); \
        return 0; \
    } \
} while (0)

static int missing_root(void) {
    (void)memset(progress, 0, sizeof progress);
    top = -1;
    push(99);
    tree_traversal(-1);
    tree_traversal_with_stack(-1);
    CHECK(is_empty());
    for (int i = 0; i < capacity; ++i) {
        CHECK(progress[i] == 0);
    }
    (void)strcpy(infix, "old output");
    infix_pos = 10;
    write_infix(-1);
    CHECK(infix[0] == '\0' && infix_pos == 1);
    return 1;
}

static int stack_resume_and_sentinel(void) {
    nodes_size = 3;
    nodes[0] = (struct TreeNode){'A', 1, 2};
    nodes[1] = (struct TreeNode){'B', -1, -1};
    nodes[2] = (struct TreeNode){'C', -1, -1};
    (void)memset(progress, 0, sizeof progress);
    top = -1;
    push(0);

    tree_traversal_proceed(peek());
    CHECK(top == 1 && stack[0] == 0 && peek() == 1);
    CHECK(progress[0] == 1 && progress[1] == 0);
    tree_traversal_proceed(peek());
    CHECK(top == 2 && peek() == -1 && progress[1] == 1);
    tree_traversal_proceed(peek());
    CHECK(top == 1 && peek() == 1 && progress[1] == 1);
    tree_traversal_proceed(peek());
    CHECK(top == 2 && peek() == -1 && progress[1] == 2);
    tree_traversal_proceed(peek());
    tree_traversal_proceed(peek());
    CHECK(top == 0 && peek() == 0 && progress[1] == 3);
    tree_traversal_proceed(peek());
    CHECK(top == 1 && peek() == 2 && progress[0] == 2);

    while (!is_empty()) {
        tree_traversal_proceed(peek());
    }
    CHECK(progress[0] == 3 && progress[1] == 3 && progress[2] == 3);
    return 1;
}

static int alphabet_tree_and_fresh_runs(void) {
    alphabet_init();
    int root = tree_connect();
    CHECK(root == 5 && capacity == 10 && stack_capacity == 10);
    tree_traversal(root); /* Visit positions are comments in the supplied lab. */
    for (int run = 0; run < 2; ++run) {
        (void)memset(progress, 0, sizeof progress);
        top = -1;
        push(99); /* The traversal resets top itself. */
        tree_traversal_with_stack(root);
        CHECK(top == -1);
        for (int i = 0; i < nodes_size; ++i) {
            CHECK(progress[i] == (i < 7 ? 3 : 0));
        }
    }
    return 1;
}

static int deepest_chain_with_sentinel_room(void) {
    nodes_size = 9;
    for (int i = 0; i < nodes_size; ++i) {
        nodes[i] = (struct TreeNode){'A', i < nodes_size - 1 ? i + 1 : -1, -1};
    }
    (void)memset(progress, 0, sizeof progress);
    tree_traversal(0);
    tree_traversal_with_stack(0);
    CHECK(top == -1);
    for (int i = 0; i < nodes_size; ++i) {
        CHECK(progress[i] == 3);
    }
    return 1;
}

static int canonical_postfix_tree(void) {
    (void)strcpy(eq, "1-2*3+4");
    convert_to_postfix();
    CHECK(strcmp(postfix, "123*-4+") == 0);
    push(99); /* The builder discards old stack contents. */
    nodes_size = 10;
    int root = build_tree_from_postfix();
    CHECK(root == 6 && nodes_size == 7 && top == -1);
    for (int i = 0; i < nodes_size; ++i) {
        CHECK(nodes[i].data == postfix[i]);
    }
    CHECK(nodes[0].left == -1 && nodes[0].right == -1);
    CHECK(nodes[1].left == -1 && nodes[1].right == -1);
    CHECK(nodes[2].left == -1 && nodes[2].right == -1);
    CHECK(nodes[3].left == 1 && nodes[3].right == 2);
    CHECK(nodes[4].left == 0 && nodes[4].right == 3);
    CHECK(nodes[5].left == -1 && nodes[5].right == -1);
    CHECK(nodes[6].left == 4 && nodes[6].right == 5);
    write_infix(root);
    CHECK(strcmp(infix, "1-2*3+4") == 0);
    CHECK(eval_postfix() == -1 && top == -1);
    return 1;
}

static int grouped_infix_and_operator_order(void) {
    const struct {
        const char *input;
        const char *output;
    } cases[] = {
        {"7", "7"},
        {"83-", "8-3"},
        {"82/", "8/2"},
        {"74%", "7%4"},
        {"12+3*", "(1+2)*3"},
        {"12+34+*", "(1+2)*(3+4)"},
        {"831-/", "8/(3-1)"},
        {"832--", "8-(3-2)"},
        {"83-2-", "8-3-2"},
        {"12+3+", "1+2+3"},
        {"123++", "1+(2+3)"},
        {"1234+++", "1+(2+(3+4))"},
        {"823/*", "8*(2/3)"},
        {"82*3/", "8*2/3"},
        {"823%%", "8%(2%3)"}
    };
    CHECK(prec2('0') == 3 && prec2('9') == 3);
    CHECK(prec2('*') == 2 && prec2('/') == 2 && prec2('%') == 2);
    CHECK(prec2('+') == 1 && prec2('-') == 1);
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        (void)strcpy(postfix, cases[i].input);
        int root = build_tree_from_postfix();
        CHECK(nodes_size == (int)strlen(cases[i].input));
        CHECK(root == nodes_size - 1 && top == -1);
        write_infix(root);
        CHECK(strcmp(infix, cases[i].output) == 0);
        CHECK(infix_pos == (int)strlen(cases[i].output) + 1);
    }
    return 1;
}

static int repeated_writes_and_smaller_tree(void) {
    (void)strcpy(postfix, "1234+++");
    int root = build_tree_from_postfix();
    write_infix(root);
    CHECK(strcmp(infix, "1+(2+(3+4))") == 0);
    write_infix(root); /* No caller reset of infix_pos is necessary. */
    CHECK(strcmp(infix, "1+(2+(3+4))") == 0 && infix_pos == 12);
    (void)strcpy(postfix, "9");
    root = build_tree_from_postfix();
    CHECK(root == 0 && nodes_size == 1 && top == -1);
    CHECK(nodes[0].left == -1 && nodes[0].right == -1);
    write_infix(root);
    CHECK(strcmp(infix, "9") == 0 && infix_pos == 2);
    return 1;
}

int main(void) {
    const struct {
        const char *name;
        int (*run)(void);
    } tests[] = {
        {"missing root", missing_root},
        {"stack resume state and missing-child sentinel", stack_resume_and_sentinel},
        {"alphabet tree and fresh traversal runs", alphabet_tree_and_fresh_runs},
        {"nine-node chain with sentinel room", deepest_chain_with_sentinel_room},
        {"canonical postfix tree and child order", canonical_postfix_tree},
        {"precedence and equal-precedence grouping", grouped_infix_and_operator_order},
        {"repeated writes and smaller rebuilt tree", repeated_writes_and_smaller_tree}
    };
    int failures = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; ++i) {
        int passed = tests[i].run();
        printf("%s %s\n", passed ? "PASS" : "FAIL", tests[i].name);
        if (!passed) ++failures;
    }
    printf("\n%zu lab test(s), %d failure(s)\n",
           sizeof tests / sizeof tests[0], failures);
    return failures == 0 ? 0 : 1;
}
