/*
 * Core checks for student/lab.c under its documented input assumptions.
 * Add three justified cases and record their predictions in the evidence file.
 * Stack operations are unchecked: test boundary predicates without performing
 * a full push or an empty read. Expressions must contain exactly seven tokens.
 */
#include <stdio.h>
#include <string.h>

extern int stack[10];
extern int capacity;
extern int size;
extern char eq[8];
extern char eq_re[8];

int is_full(void);
int is_empty(void);
void push(int data);
int peek(void);
int pop(void);
void infix_to_postfix(void);
int eval_postfix(void);

#define CHECK(condition) do { \
    if (!(condition)) { \
        (void)printf("  line %d: %s\n", __LINE__, #condition); \
        return 0; \
    } \
} while (0)

static int integer_lifo(void)
{
    size = 0;
    push('A');
    push('B');
    push('C');
    CHECK(size == 3);
    CHECK(stack[0] == 'A' && stack[1] == 'B' && stack[2] == 'C');
    CHECK(peek() == 'C' && size == 3);
    CHECK(pop() == 'C' && size == 2);
    CHECK(stack[2] == 'C'); /* Logical removal does not erase the cell. */
    push(300);
    CHECK(size == 3 && stack[2] == 300);
    CHECK(pop() == 300 && size == 2);
    CHECK(pop() == 'B');
    CHECK(pop() == 'A');
    CHECK(is_empty());
    return 1;
}

static int full_empty_predicates(void)
{
    int saved[10];
    size = 0;
    CHECK(capacity == 10 && is_empty() && !is_full());
    for (int i = 0; i < capacity; ++i) {
        push(i - 5);
    }
    CHECK(size == 10 && is_full() && !is_empty());
    (void)memcpy(saved, stack, sizeof saved);
    CHECK(is_full() && size == 10);
    CHECK(memcmp(saved, stack, sizeof saved) == 0);
    for (int i = capacity - 1; i >= 0; --i) {
        CHECK(peek() == i - 5 && size == i + 1);
        CHECK(pop() == i - 5);
    }
    CHECK(is_empty() && size == 0);
    /* Do not call peek/pop here, or push while full: lab.c has no guards. */
    return 1;
}

static int expression_case(const char *input, const char *output, int result)
{
    CHECK(strlen(input) == 7 && strlen(output) == 7);
    (void)strcpy(eq, input);
    (void)memset(eq_re, '?', sizeof eq_re);
    infix_to_postfix();
    CHECK(eq_re[7] == '\0'); /* The drained sentinel supplies the terminator. */
    CHECK(strcmp(eq_re, output) == 0);
    CHECK(size == 0 && stack[0] == '\0');
    CHECK(eval_postfix() == result);
    CHECK(size == 0 && stack[0] == result); /* Final pop leaves its cell. */
    return 1;
}

static int canonical_conversion(void)
{
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
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
    size = 0;
    push(99);
    push(100);
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(expression_case("8-3-2-1", "83-2-1-", 2));
    push(777);
    CHECK(eval_postfix() == 2); /* Evaluation resets size independently. */
    CHECK(size == 0 && stack[0] == 2);
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
        { "character digits and integer values", character_digits_and_integer_values }
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
