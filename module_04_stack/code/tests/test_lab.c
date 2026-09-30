/*
 * Core checks for student/lab.c under its documented input assumptions.
 * Add three justified cases and record their predictions in the evidence file.
 * Stack operations are unchecked: test boundary predicates without performing
 * a full push or an empty read. Expressions must fit their eight-character, null-terminated buffers.
 */
#include <stdio.h>
#include <string.h>

extern int stack[10];
extern int capacity;
extern int top;
extern char eq[8];
extern char postfix[8];
extern char eq_paren[8];

int is_full(void);
int is_empty(void);
void push(int data);
int peek(void);
int pop(void);
void convert_to_postfix(void);
void infix_to_postfix_parentheses(void);
int eval_postfix(void);

#define CHECK(condition) do { \
    if (!(condition)) { \
        (void)printf("  line %d: %s\n", __LINE__, #condition); \
        return 0; \
    } \
} while (0)

static int integer_lifo(void)
{
    top = -1;
    push('A');
    push('B');
    push('C');
    CHECK(top == 2);
    CHECK(stack[0] == 'A' && stack[1] == 'B' && stack[2] == 'C');
    CHECK(peek() == 'C' && top == 2);
    CHECK(pop() == 'C' && top == 1);
    CHECK(stack[2] == 'C'); /* Logical removal does not erase the cell. */
    push(300);
    CHECK(top == 2 && stack[2] == 300);
    CHECK(pop() == 300 && top == 1);
    CHECK(pop() == 'B');
    CHECK(pop() == 'A');
    CHECK(is_empty());
    return 1;
}

static int full_empty_predicates(void)
{
    int saved[10];
    top = -1;
    CHECK(capacity == 10 && is_empty() && !is_full());
    for (int i = 0; i < capacity; ++i) {
        push(i - 5);
    }
    CHECK(top == 9 && is_full() && !is_empty());
    (void)memcpy(saved, stack, sizeof saved);
    CHECK(is_full() && top == 9);
    CHECK(memcmp(saved, stack, sizeof saved) == 0);
    for (int i = capacity - 1; i >= 0; --i) {
        CHECK(peek() == i - 5 && top == i);
        CHECK(pop() == i - 5);
    }
    CHECK(is_empty() && top == -1);
    /* Do not call peek/pop here, or push while full: lab.c has no guards. */
    return 1;
}

static int conversion_case(const char *input, const char *output, int result,
                           int with_parentheses)
{
    CHECK(strlen(input) > 0 && strlen(input) < sizeof eq);
    CHECK(strlen(output) > 0 && strlen(output) < sizeof postfix);
    (void)strcpy(with_parentheses ? eq_paren : eq, input);
    (void)memset(postfix, '?', sizeof postfix);
    if (with_parentheses) {
        infix_to_postfix_parentheses();
    } else {
        convert_to_postfix();
    }
    CHECK(postfix[strlen(output)] == '\0'); /* Conversion explicitly terminates the output after draining operators. */
    CHECK(strcmp(postfix, output) == 0);
    CHECK(top == -1);
    CHECK(eval_postfix() == result);
    CHECK(top == -1 && stack[0] == result); /* Final pop leaves its cell. */
    return 1;
}

static int expression_case(const char *input, const char *output, int result)
{
    return conversion_case(input, output, result, 0);
}

static int canonical_conversion(void)
{
    (void)strcpy(eq, "1-2*3+4");
    convert_to_postfix();
    CHECK(strcmp(postfix, "123*-4+") == 0 && postfix[7] == '\0');
    CHECK(top == -1);
    /* No bottom marker was stored: popped operator codes remain inactive. */
    CHECK(stack[0] == '+' && stack[1] == '*');
    CHECK(eval_postfix() == -1 && top == -1);
    return 1;
}

static int precedence_and_operand_order(void)
{
    const struct {
        const char *input;
        const char *output;
        int result;
    } cases[] = {
        { "1+2*3+4", "123*+4+", 11 },
        { "8-3-2-1", "83-2-1-", 2 },
        { "8/2*3+1", "82/3*1+", 13 },
        { "7%4+1*2", "74%12*+", 5 },
        { "7/2+0+0", "72/0+0+", 3 },
        { "1-8/3+0", "183/-0+", -1 },
        { "1-8-2+0", "18-2-0+", -9 },
        { "0*9+2+0", "09*2+0+", 2 }
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        CHECK(expression_case(cases[i].input, cases[i].output, cases[i].result));
    }
    return 1;
}

static int repeated_calls_reset_shared_stack(void)
{
    top = -1;
    push(99);
    push(100);
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(expression_case("8-3-2-1", "83-2-1-", 2));
    push(777);
    CHECK(eval_postfix() == 2); /* Evaluation resets top independently. */
    CHECK(top == -1 && stack[0] == 2);
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    return 1;
}

static int character_digits_and_integer_values(void)
{
    CHECK(expression_case("0+0+0+0", "00+0+0+", 0));
    CHECK(expression_case("9+0+0+0", "90+0+0+", 9));
    CHECK(expression_case("9*9*9*9", "99*9*9*", 6561));
    return 1;
}

static int shorter_null_terminated_inputs(void)
{
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(expression_case("2+3", "23+", 5));
    CHECK(expression_case("7", "7", 7));
    CHECK(expression_case("8-3-2", "83-2-", 3));
    /* A new terminator must stop evaluation before stale buffer characters. */
    (void)strcpy(eq, "9");
    (void)memcpy(postfix, "123*-4+", sizeof postfix);
    stack[0] = 777;
    convert_to_postfix();
    CHECK(postfix[0] == '9' && postfix[1] == '\0');
    CHECK(top == -1 && stack[0] == 777); /* A digit-only conversion stores no stack item. */
    CHECK(eval_postfix() == 9 && top == -1);
    return 1;
}

static int balanced_parentheses(void)
{
    CHECK(conversion_case("1+(2+3)", "123++", 6, 1));
    CHECK(conversion_case("(1+2)*3", "12+3*", 9, 1));
    CHECK(conversion_case("8/(3-1)", "831-/", 4, 1));
    CHECK(conversion_case("((7))", "7", 7, 1));
    CHECK(conversion_case("(8-3)-2", "83-2-", 3, 1));
    CHECK(conversion_case("8-(3-2)", "832--", 7, 1));
    CHECK(conversion_case("1", "1", 1, 1));
    /* Both converters reset and reuse the same stack and output buffer. */
    top = -1;
    push(999);
    CHECK(conversion_case("1+(2+3)", "123++", 6, 1));
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    return 1;
}

int main(void)
{
    const struct {
        const char *name;
        int (*run)(void);
    } tests[] = {
        { "integer stack LIFO", integer_lifo },
        { "full and empty predicates", full_empty_predicates },
        { "canonical infix and postfix", canonical_conversion },
        { "precedence and operand order", precedence_and_operand_order },
        { "repeated calls reset shared stack", repeated_calls_reset_shared_stack },
        { "character digits and integer values", character_digits_and_integer_values },
        { "shorter null-terminated inputs", shorter_null_terminated_inputs },
        { "balanced parentheses", balanced_parentheses }
    };
    int failures = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; ++i) {
        int passed = tests[i].run();
        (void)printf("%s %s\n", passed ? "PASS" : "FAIL", tests[i].name);
        if (!passed) {
            ++failures;
        }
    }
    (void)printf("\n%zu lab test(s), %d failure(s)\n",
                 sizeof tests / sizeof tests[0], failures);
    return failures == 0 ? 0 : 1;
}
