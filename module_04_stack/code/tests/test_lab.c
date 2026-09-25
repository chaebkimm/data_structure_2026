/*
 * Core checks for student/lab.c under its documented input assumptions.
 * Add three justified cases and record their predictions in the evidence file.
 * Invalid expressions are discussion/extension cases, not safe rejection tests
 * for this version: the supplied evaluator has no error-status interface.
 */
#include <stdio.h>
#include <string.h>

extern char stack[10];
extern int top;
extern char infix[8];
extern char postfix[8];
extern int size;

int is_full(void);
int is_empty(void);
void push(char data);
char peek(void);
char pop(void);
void infix_to_postfix(void);
int eval_postfix(void);

#define CHECK(condition) do { \
    if (!(condition)) { \
        (void)printf("  line %d: %s\n", __LINE__, #condition); \
        return 0; \
    } \
} while (0)

static int character_lifo(void)
{
    top = 10;
    push('A');
    push('B');
    push('C');
    CHECK(top == 7);
    CHECK(peek() == 'C' && top == 7);
    CHECK(pop() == 'C' && top == 8);
    CHECK(stack[7] == 'C'); /* Logical removal does not erase the cell. */
    CHECK(pop() == 'B');
    CHECK(pop() == 'A');
    CHECK(is_empty());
    return 1;
}

static int full_empty_boundaries(void)
{
    char saved[10];
    top = 10;
    (void)memset(stack, '?', sizeof stack);
    (void)memcpy(saved, stack, sizeof saved);
    CHECK(peek() == '\0' && pop() == '\0');
    CHECK(top == 10 && memcmp(saved, stack, sizeof saved) == 0);
    for (int i = 0; i < 10; ++i) {
        push((char)('0' + i));
    }
    CHECK(is_full());
    (void)memcpy(saved, stack, sizeof saved);
    push('X');
    CHECK(top == 0 && memcmp(saved, stack, sizeof saved) == 0);
    for (int i = 9; i >= 0; --i) {
        CHECK(pop() == (char)('0' + i));
    }
    CHECK(is_empty() && pop() == '\0' && top == 10);
    return 1;
}

/* Copy only fixtures that fit the actual input buffer. Leave top alone so
 * successive calls test the converter's own restoration of empty state. */
static int expression_case(const char *input, const char *output, int result)
{
    CHECK(strlen(input) < sizeof infix);
    CHECK(is_empty());
    (void)strcpy(infix, input);
    infix_to_postfix();
    CHECK(size == (int)strlen(output));
    CHECK(size >= 0 && size < (int)sizeof postfix);
    CHECK(postfix[size] == '\0');
    CHECK(strcmp(postfix, output) == 0);
    CHECK(is_empty());
    CHECK(eval_postfix() == result);
    return 1;
}

static int canonical_conversion(void)
{
    top = 10;
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(size == 7);
    return 1;
}

static int precedence_and_operand_order(void)
{
    const struct {
        const char *input;
        const char *output;
        int result;
    } cases[] = {
        { "1+2*3", "123*+", 7 },
        { "8-3-2", "83-2-", 3 },
        { "8/2*3", "82/3*", 12 },
        { "7%4+1", "74%1+", 4 },
        { "7/2", "72/", 3 },
        { "1-8/3", "183/-", -1 },
        { "1-8-2", "18-2-", -9 },
        { "0*9+2", "09*2+", 2 }
    };
    top = 10;
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        CHECK(expression_case(cases[i].input, cases[i].output, cases[i].result));
    }
    return 1;
}

static int repeated_and_shorter_conversion(void)
{
    top = 10;
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    CHECK(expression_case("1+2*3", "123*+", 7));
    CHECK(expression_case("5", "5", 5));
    CHECK(size == 1 && postfix[1] == '\0');
    CHECK(expression_case("1-2*3+4", "123*-4+", -1));
    return 1;
}

static int character_digits_and_integer_values(void)
{
    top = 10;
    CHECK(expression_case("0", "0", 0));
    CHECK(expression_case("9", "9", 9));
    CHECK(expression_case("9*9*9*9", "99*9*9*", 6561));
    return 1;
}

int main(void)
{
    const struct {
        const char *name;
        int (*run)(void);
    } tests[] = {
        { "character stack LIFO", character_lifo },
        { "full and empty boundaries", full_empty_boundaries },
        { "canonical infix and postfix", canonical_conversion },
        { "precedence and operand order", precedence_and_operand_order },
        { "repeated and shorter conversion", repeated_and_shorter_conversion },
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
